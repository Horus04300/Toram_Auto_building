//! Native, single-threaded implementation of the D4 CandidateTree search.
//!
//! This deliberately mirrors the JavaScript optimizer's prepared-problem
//! search: identical heuristic seeds, CandidateTree splitting, two-dimensional
//! box expansion, safe envelope bounds, small-box enumeration, and lexical
//! build-ID tie breaking. It is the P4 reference for later parallel work.

use std::cmp::Ordering;
use std::collections::{BTreeMap, BinaryHeap, HashSet};
use std::sync::atomic::{AtomicBool, AtomicU64, AtomicUsize, Ordering as AtomicOrdering};
use std::sync::{Arc, Mutex};
use std::time::Instant;

use serde::{Deserialize, Serialize};
use serde_json::Value;

use crate::d4_native_evaluator::{evaluate_summary_from_map, D4NativeSummary};

const EPSILON: f64 = 1e-9;
const GROUP_COUNT: usize = 4;
const SMALL_BOX_LIMIT: usize = 64;
const HEURISTIC_CANDIDATE_LIMIT: usize = 192;
const HEURISTIC_PASSES: usize = 2;
type Stats = BTreeMap<String, f64>;

#[derive(Clone, Deserialize)]
pub struct NativePackage {
    pub id: String,
    #[serde(rename = "statDelta", default)]
    pub stat_delta: Stats,
}

#[derive(Clone, Deserialize)]
pub struct NativeGroup {
    #[serde(rename = "id")]
    pub _id: String,
    pub packages: Vec<NativePackage>,
}

#[derive(Clone, Deserialize)]
pub struct NativeProblem {
    #[serde(rename = "baseContext")]
    pub base_context: Value,
    #[serde(rename = "scenarioSnapshot", default)]
    pub scenario_snapshot: Value,
    #[serde(default)]
    pub metadata: NativeMetadata,
    pub groups: Vec<NativeGroup>,
}

#[derive(Clone, Default, Deserialize)]
pub struct NativeMetadata {
    #[serde(rename = "modeledKeys", default)]
    pub modeled_keys: Vec<String>,
    #[serde(rename = "initialPackageIds", default)]
    pub initial_package_ids: Vec<String>,
}

#[derive(Clone, Debug, Serialize)]
pub struct NativeBuild {
    pub id: String,
    #[serde(rename = "packageIds")]
    pub package_ids: Vec<String>,
    #[serde(rename = "statDelta")]
    pub stat_delta: Stats,
}

#[derive(Clone, Debug, Serialize)]
pub struct NativeSolveResult {
    pub status: String,
    pub exact: bool,
    pub score: Option<f64>,
    #[serde(rename = "bestBuild")]
    pub best_build: Option<NativeBuild>,
    #[serde(rename = "upperBound")]
    pub upper_bound: Option<f64>,
    #[serde(rename = "elapsedMs")]
    pub elapsed_ms: u128,
    #[serde(rename = "visitedNodes")]
    pub visited_nodes: u64,
    pub evaluations: u64,
    #[serde(rename = "prunedByBound")]
    pub pruned_by_bound: u64,
    #[serde(rename = "prunedByConstraint")]
    pub pruned_by_constraint: u64,
    #[serde(rename = "enumeratedCompletions")]
    pub enumerated_completions: u64,
}

#[derive(Clone, Debug, Serialize)]
pub struct NativeParallelSolveResult {
    #[serde(flatten)]
    pub result: NativeSolveResult,
    #[serde(rename = "threadsUsed")]
    pub threads_used: usize,
    #[serde(rename = "scheduledShards")]
    pub scheduled_shards: usize,
    #[serde(rename = "completedShards")]
    pub completed_shards: usize,
}

#[derive(Clone)]
struct TreeNode {
    path: String,
    size: usize,
    envelope: Stats,
    package: Option<usize>,
    left: Option<Arc<TreeNode>>,
    right: Option<Arc<TreeNode>>,
}

/// D4 always has weapon/armor/additional/special groups. An array keeps one
/// frontier item inline: no Vec allocation and no box-path String per node.
#[derive(Clone)]
struct WorkItem {
    upper: f64,
    clusters: [Arc<TreeNode>; GROUP_COUNT],
}

#[derive(Default)]
struct SearchState {
    evaluations: u64,
    best_score: f64,
    best_id: String,
    best_selected: Option<[usize; GROUP_COUNT]>,
}

struct SharedIncumbent {
    score_bits: AtomicU64,
    record: Mutex<SearchState>,
}

struct ParallelCounters {
    evaluations: AtomicU64,
    visited: AtomicU64,
    pruned_by_bound: AtomicU64,
    pruned_by_constraint: AtomicU64,
    enumerated: AtomicU64,
}

impl PartialEq for WorkItem {
    fn eq(&self, other: &Self) -> bool {
        self.upper.total_cmp(&other.upper) == Ordering::Equal
            && self
                .clusters
                .iter()
                .zip(other.clusters.iter())
                .all(|(left, right)| left.path == right.path)
    }
}
impl Eq for WorkItem {}
impl PartialOrd for WorkItem {
    fn partial_cmp(&self, other: &Self) -> Option<Ordering> {
        Some(self.cmp(other))
    }
}
impl Ord for WorkItem {
    fn cmp(&self, other: &Self) -> Ordering {
        let by_upper = self.upper.total_cmp(&other.upper);
        if by_upper != Ordering::Equal {
            return by_upper;
        }
        // JS MaxHeap prefers lexical-smaller boxPathId when upper bounds tie.
        for (left, right) in self.clusters.iter().zip(other.clusters.iter()) {
            let comparison = right.path.cmp(&left.path);
            if comparison != Ordering::Equal {
                return comparison;
            }
        }
        Ordering::Equal
    }
}

fn add_stats(mut left: Stats, right: &Stats) -> Stats {
    for (key, value) in right {
        *left.entry(key.clone()).or_default() += value;
    }
    left
}

fn heuristic_score(stats: &Stats, mode: &str) -> f64 {
    let number = |key: &str| stats.get(key).copied().unwrap_or(0.0);
    let utility = number("MAXHP") / 10000.0
        + number("MAXHPP") / 100.0
        + number("MAXMP") / 2000.0
        + number("AMPR") / 100.0
        + number("AMPRP") / 100.0
        + number("ASPD") / 1000.0
        + number("ASPD_P") / 100.0
        + number("CRIT") / 100.0
        + number("CRIT_P") / 100.0;
    let damage = number("ATKP")
        + number("MATKP")
        + number("SRW")
        + number("LRW")
        + number("UNSHEATHE")
        + number("UNSHEATHEP")
        + number("CDMG_P")
        + number("CDMGP")
        + number("PHYS_PIERCE")
        + number("MAG_PIERCE")
        + number("WATKP")
        + number("DAMAGE_P")
        + number("ATK") / 100.0
        + number("MATK") / 100.0
        + number("CDMG") / 3.0;
    if mode == "utility" {
        utility * 1_000_000.0 + damage
    } else {
        damage * 1000.0 + utility
    }
}

fn split_importance(key: &str, context: &Value) -> f64 {
    let mut weight = match key {
        "ATKP" | "MATKP" | "SRW" | "LRW" | "UNSHEATHE" | "UNSHEATHEP" | "DAMAGE_P" => 12.0,
        "CDMG_P" | "CDMGP" | "PHYS_PIERCE" | "MAG_PIERCE" => 10.0,
        "CDMG" | "WATKP" | "ELEM_P" => 8.0,
        "ATK" | "MATK" | "WATK" => 5.0,
        "CRIT" | "CRIT_P" | "CRITP" => 7.0,
        "STABILITY" => 6.0,
        "MAXHP" | "MAXHPP" | "MAXMP" | "AMPR" | "AMPRP" | "ASPD" | "ASPD_P" => 8.0,
        _ => 3.0,
    };
    let attack_type = context
        .get("atkType")
        .and_then(Value::as_str)
        .unwrap_or("PHYS")
        .to_ascii_uppercase();
    if attack_type == "PHYS"
        && (matches!(key, "MATKP" | "MATK" | "MAG_PIERCE") || key.starts_with("MATK_UP_"))
    {
        weight *= 0.05;
    }
    if attack_type == "MAG"
        && (matches!(key, "ATKP" | "ATK" | "PHYS_PIERCE") || key.starts_with("ATK_UP_"))
    {
        weight *= 0.05;
    }
    let range_type = context
        .get("rangeType")
        .and_then(Value::as_str)
        .unwrap_or("SHORT")
        .to_ascii_uppercase();
    if (range_type == "SHORT" && key == "LRW") || (range_type == "LONG" && key == "SRW") {
        weight *= 0.05;
    }
    let uses_unsheathe = context
        .get("chkIsUnsheathe")
        .and_then(Value::as_bool)
        .unwrap_or(false)
        || context
            .get("activeBuildConversions")
            .and_then(Value::as_array)
            .is_some_and(|effects| {
                effects.iter().any(|effect| {
                    effect.get("conversion").and_then(Value::as_str) == Some("unsheatheToAtk")
                })
            });
    if !uses_unsheathe && matches!(key, "UNSHEATHE" | "UNSHEATHEP") {
        weight *= 0.05;
    }
    weight
}

fn group_envelope(packages: &[NativePackage], indices: &[usize], keys: &[String]) -> Stats {
    let mut result = Stats::new();
    for key in keys {
        let maximum = indices
            .iter()
            .map(|index| packages[*index].stat_delta.get(key).copied().unwrap_or(0.0))
            .fold(0.0_f64, f64::max);
        if maximum != 0.0 {
            result.insert(key.clone(), maximum);
        }
    }
    result
}

fn global_ranges(packages: &[NativePackage], keys: &[String]) -> BTreeMap<String, f64> {
    keys.iter()
        .map(|key| {
            let (low, high) =
                packages
                    .iter()
                    .fold((f64::INFINITY, f64::NEG_INFINITY), |range, item| {
                        let value = item.stat_delta.get(key).copied().unwrap_or(0.0);
                        (range.0.min(value), range.1.max(value))
                    });
            (key.clone(), (high - low).max(0.0))
        })
        .collect()
}

fn build_tree(
    packages: &[NativePackage],
    indices: Vec<usize>,
    keys: &[String],
    ranges: &BTreeMap<String, f64>,
    context: &Value,
    path: String,
) -> Arc<TreeNode> {
    let envelope = group_envelope(packages, &indices, keys);
    if indices.len() <= 1 {
        return Arc::new(TreeNode {
            path,
            size: indices.len(),
            envelope,
            package: indices.first().copied(),
            left: None,
            right: None,
        });
    }
    let mut split_key: Option<&str> = None;
    let mut best_spread = f64::NEG_INFINITY;
    for key in keys {
        let global_range = ranges.get(key).copied().unwrap_or(0.0);
        if global_range <= EPSILON {
            continue;
        }
        let (low, high) =
            indices
                .iter()
                .fold((f64::INFINITY, f64::NEG_INFINITY), |range, index| {
                    let value = packages[*index].stat_delta.get(key).copied().unwrap_or(0.0);
                    (range.0.min(value), range.1.max(value))
                });
        let spread = (high - low) / global_range * split_importance(key, context);
        if spread > best_spread + EPSILON
            || ((spread - best_spread).abs() <= EPSILON
                && key.as_str() < split_key.unwrap_or("\u{ffff}"))
        {
            best_spread = spread;
            split_key = Some(key);
        }
    }
    let mut sorted = indices;
    sorted.sort_by(|left, right| {
        let value_order = split_key
            .map(|key| {
                packages[*left]
                    .stat_delta
                    .get(key)
                    .copied()
                    .unwrap_or(0.0)
                    .total_cmp(&packages[*right].stat_delta.get(key).copied().unwrap_or(0.0))
            })
            .unwrap_or(Ordering::Equal);
        if value_order != Ordering::Equal {
            return value_order;
        }
        let heuristic_order = heuristic_score(&packages[*left].stat_delta, "damage")
            .total_cmp(&heuristic_score(&packages[*right].stat_delta, "damage"));
        if heuristic_order != Ordering::Equal {
            return heuristic_order;
        }
        packages[*left].id.cmp(&packages[*right].id)
    });
    let middle = (sorted.len() / 2).max(1);
    let right = sorted.split_off(middle);
    Arc::new(TreeNode {
        path: path.clone(),
        size: sorted.len() + right.len(),
        envelope,
        package: None,
        left: Some(build_tree(
            packages,
            sorted,
            keys,
            ranges,
            context,
            format!("{path}0"),
        )),
        right: Some(build_tree(
            packages,
            right,
            keys,
            ranges,
            context,
            format!("{path}1"),
        )),
    })
}

fn requirement(requirements: &Value, key: &str) -> Option<f64> {
    requirements.get(key).and_then(Value::as_f64)
}

fn feasible(summary: &D4NativeSummary, requirements: &Value) -> bool {
    requirement(requirements, "maxHp").is_none_or(|value| summary.final_max_hp as f64 >= value)
        && requirement(requirements, "maxMp")
            .is_none_or(|value| summary.final_max_mp as f64 >= value)
        && requirement(requirements, "amprBeforeDual")
            .is_none_or(|value| summary.ampr_before_dual as f64 >= value)
        && requirement(requirements, "normalAttackCrit")
            .is_none_or(|value| summary.normal_attack_crit as f64 >= value)
        && requirement(requirements, "aspd").is_none_or(|value| summary.final_aspd as f64 >= value)
}

fn build_id(groups: &[NativeGroup], selected: &[usize; GROUP_COUNT]) -> String {
    groups
        .iter()
        .zip(selected)
        .map(|(group, index)| group.packages[*index].id.as_str())
        .collect::<Vec<_>>()
        .join("||")
}

fn selection_stats(problem: &NativeProblem, selected: &[usize; GROUP_COUNT]) -> Stats {
    problem
        .groups
        .iter()
        .zip(selected)
        .fold(Stats::new(), |stats, (group, index)| {
            add_stats(stats, &group.packages[*index].stat_delta)
        })
}

fn box_stats(clusters: &[Arc<TreeNode>; GROUP_COUNT]) -> Stats {
    clusters
        .iter()
        .fold(Stats::new(), |stats, node| add_stats(stats, &node.envelope))
}

fn box_combinations(clusters: &[Arc<TreeNode>; GROUP_COUNT], limit: usize) -> usize {
    clusters.iter().fold(1_usize, |total, node| {
        total.saturating_mul(node.size).min(limit.saturating_add(1))
    })
}

fn split_slack(node: &TreeNode) -> f64 {
    let (Some(left), Some(right)) = (&node.left, &node.right) else {
        return f64::NEG_INFINITY;
    };
    heuristic_score(&node.envelope, "damage")
        - heuristic_score(&left.envelope, "damage").max(heuristic_score(&right.envelope, "damage"))
}

fn split_indices(clusters: &[Arc<TreeNode>; GROUP_COUNT]) -> Vec<usize> {
    let mut available = clusters
        .iter()
        .enumerate()
        .filter(|(_, node)| node.left.is_some() || node.right.is_some())
        .map(|(index, node)| (index, split_slack(node), node.size))
        .collect::<Vec<_>>();
    available.sort_by(|left, right| {
        right
            .1
            .total_cmp(&left.1)
            .then_with(|| right.2.cmp(&left.2))
            .then_with(|| left.0.cmp(&right.0))
    });
    available.into_iter().take(2).map(|entry| entry.0).collect()
}

fn better(score: f64, id: &str, best_score: f64, best_id: &str) -> bool {
    score > best_score + EPSILON || ((score - best_score).abs() <= EPSILON && id < best_id)
}

fn consider(
    problem: &NativeProblem,
    requirements: &Value,
    state: &mut SearchState,
    selected: &[usize; GROUP_COUNT],
    stats: &Stats,
) -> Result<(), String> {
    state.evaluations += 1;
    let summary = evaluate_summary_from_map(&problem.base_context, stats)?;
    if !feasible(&summary, requirements) {
        return Ok(());
    }
    let id = build_id(&problem.groups, selected);
    if better(
        summary.optimization_damage_factor,
        &id,
        state.best_score,
        &state.best_id,
    ) {
        state.best_score = summary.optimization_damage_factor;
        state.best_id = id;
        state.best_selected = Some(*selected);
    }
    Ok(())
}

fn cluster_indices(node: &TreeNode, output: &mut Vec<usize>) {
    if let Some(index) = node.package {
        output.push(index);
        return;
    }
    if let Some(left) = &node.left {
        cluster_indices(left, output);
    }
    if let Some(right) = &node.right {
        cluster_indices(right, output);
    }
}

#[allow(clippy::too_many_arguments)] // Recursive complete enumeration shares its immutable search inputs.
fn enumerate_box(
    index: usize,
    clusters: &[Arc<TreeNode>; GROUP_COUNT],
    problem: &NativeProblem,
    requirements: &Value,
    selected: &mut [usize; GROUP_COUNT],
    stats: &Stats,
    state: &mut SearchState,
    enumerated: &mut u64,
) -> Result<(), String> {
    if index == GROUP_COUNT {
        *enumerated += 1;
        return consider(problem, requirements, state, selected, stats);
    }
    let mut indices = Vec::with_capacity(clusters[index].size);
    cluster_indices(&clusters[index], &mut indices);
    for package_index in indices {
        selected[index] = package_index;
        let next = add_stats(
            stats.clone(),
            &problem.groups[index].packages[package_index].stat_delta,
        );
        enumerate_box(
            index + 1,
            clusters,
            problem,
            requirements,
            selected,
            &next,
            state,
            enumerated,
        )?;
    }
    Ok(())
}

fn heuristic_candidate_pool(group: &NativeGroup, current: usize) -> Vec<usize> {
    let each = HEURISTIC_CANDIDATE_LIMIT.div_ceil(2);
    let mut result = vec![current];
    let mut seen = HashSet::from([group.packages[current].id.as_str()]);
    for mode in ["damage", "utility"] {
        let mut candidates = (0..group.packages.len()).collect::<Vec<_>>();
        candidates.sort_by(|left, right| {
            heuristic_score(&group.packages[*right].stat_delta, mode)
                .total_cmp(&heuristic_score(&group.packages[*left].stat_delta, mode))
                .then_with(|| group.packages[*left].id.cmp(&group.packages[*right].id))
        });
        for index in candidates.into_iter().take(each) {
            if seen.insert(group.packages[index].id.as_str()) {
                result.push(index);
            }
        }
    }
    result
}

fn initial_selections(problem: &NativeProblem) -> Vec<[usize; GROUP_COUNT]> {
    let mut result = Vec::new();
    if problem.metadata.initial_package_ids.len() == GROUP_COUNT {
        let indices = std::array::from_fn(|group_index| {
            problem.groups[group_index]
                .packages
                .iter()
                .position(|item| item.id == problem.metadata.initial_package_ids[group_index])
        });
        if indices.iter().all(Option::is_some) {
            result.push(indices.map(Option::unwrap));
        }
    }
    for mode in ["utility", "damage"] {
        result.push(std::array::from_fn(|group_index| {
            (0..problem.groups[group_index].packages.len())
                .max_by(|left, right| {
                    heuristic_score(
                        &problem.groups[group_index].packages[*left].stat_delta,
                        mode,
                    )
                    .total_cmp(&heuristic_score(
                        &problem.groups[group_index].packages[*right].stat_delta,
                        mode,
                    ))
                    .then_with(|| {
                        problem.groups[group_index].packages[*right]
                            .id
                            .cmp(&problem.groups[group_index].packages[*left].id)
                    })
                })
                .unwrap_or(0)
        }));
    }
    result
}

pub fn solve_exact(problem: &NativeProblem) -> Result<NativeSolveResult, String> {
    if !problem.base_context.is_object()
        || problem.groups.len() != GROUP_COUNT
        || problem.groups.iter().any(|group| group.packages.is_empty())
    {
        return Err("D4 native solver requires four nonempty prepared groups".to_string());
    }
    let started = Instant::now();
    let mut keys = problem.metadata.modeled_keys.clone();
    if keys.is_empty() {
        keys = problem
            .groups
            .iter()
            .flat_map(|group| group.packages.iter())
            .flat_map(|package| package.stat_delta.keys().cloned())
            .collect();
    }
    keys.sort();
    keys.dedup();
    let trees = problem
        .groups
        .iter()
        .map(|group| {
            build_tree(
                &group.packages,
                (0..group.packages.len()).collect(),
                &keys,
                &global_ranges(&group.packages, &keys),
                &problem.base_context,
                "r".to_string(),
            )
        })
        .collect::<Vec<_>>();
    let clusters: [Arc<TreeNode>; GROUP_COUNT] = trees
        .try_into()
        .map_err(|_| "D4 native solver expected four trees".to_string())?;
    let requirements = problem
        .scenario_snapshot
        .get("requirements")
        .unwrap_or(&Value::Null);
    let mut state = SearchState {
        best_score: f64::NEG_INFINITY,
        ..SearchState::default()
    };
    let mut visited = 0_u64;
    let mut pruned_by_bound = 0_u64;
    let mut pruned_by_constraint = 0_u64;
    let mut enumerated = 0_u64;

    for selected in initial_selections(problem) {
        let stats = selection_stats(problem, &selected);
        consider(problem, requirements, &mut state, &selected, &stats)?;
    }
    if let Some(mut selected) = state.best_selected {
        for _ in 0..HEURISTIC_PASSES {
            let mut changed = false;
            for group_index in 0..GROUP_COUNT {
                let baseline = selected;
                let before_id = state.best_id.clone();
                for package_index in
                    heuristic_candidate_pool(&problem.groups[group_index], baseline[group_index])
                {
                    let mut trial = baseline;
                    trial[group_index] = package_index;
                    let stats = selection_stats(problem, &trial);
                    consider(problem, requirements, &mut state, &trial, &stats)?;
                }
                if state.best_id != before_id {
                    changed = true;
                    selected = state.best_selected.unwrap_or(selected);
                }
            }
            if !changed {
                break;
            }
        }
    }

    let root_stats = box_stats(&clusters);
    state.evaluations += 1;
    let root = evaluate_summary_from_map(&problem.base_context, &root_stats)?;
    if !feasible(&root, requirements) {
        return Ok(NativeSolveResult {
            status: "invalid".to_string(),
            exact: false,
            score: None,
            best_build: None,
            upper_bound: Some(root.optimization_damage_factor),
            elapsed_ms: started.elapsed().as_millis(),
            visited_nodes: 0,
            evaluations: state.evaluations,
            pruned_by_bound,
            pruned_by_constraint,
            enumerated_completions: enumerated,
        });
    }
    let mut heap = BinaryHeap::new();
    heap.push(WorkItem {
        upper: root.optimization_damage_factor,
        clusters,
    });
    while let Some(node) = heap.pop() {
        visited += 1;
        if node.upper < state.best_score - EPSILON {
            pruned_by_bound += 1;
            continue;
        }
        if box_combinations(&node.clusters, SMALL_BOX_LIMIT) <= SMALL_BOX_LIMIT {
            enumerate_box(
                0,
                &node.clusters,
                problem,
                requirements,
                &mut [0; GROUP_COUNT],
                &Stats::new(),
                &mut state,
                &mut enumerated,
            )?;
            continue;
        }
        let splits = split_indices(&node.clusters);
        if splits.is_empty() {
            continue;
        }
        let mut child_boxes = vec![node.clusters.clone()];
        for split in splits {
            let mut expanded = Vec::with_capacity(child_boxes.len() * 2);
            for box_clusters in child_boxes {
                for child in [
                    box_clusters[split].left.clone(),
                    box_clusters[split].right.clone(),
                ]
                .into_iter()
                .flatten()
                {
                    let mut next = box_clusters.clone();
                    next[split] = child;
                    expanded.push(next);
                }
            }
            child_boxes = expanded;
        }
        for child_clusters in child_boxes {
            let stats = box_stats(&child_clusters);
            state.evaluations += 1;
            let bound = evaluate_summary_from_map(&problem.base_context, &stats)?;
            if !feasible(&bound, requirements) {
                pruned_by_constraint += 1;
            } else if bound.optimization_damage_factor < state.best_score - EPSILON {
                pruned_by_bound += 1;
            } else {
                heap.push(WorkItem {
                    upper: bound.optimization_damage_factor,
                    clusters: child_clusters,
                });
            }
        }
    }
    let best_build = state.best_selected.as_ref().map(|selected| NativeBuild {
        id: state.best_id.clone(),
        package_ids: selected
            .iter()
            .enumerate()
            .map(|(group, index)| problem.groups[group].packages[*index].id.clone())
            .collect(),
        stat_delta: selection_stats(problem, selected),
    });
    Ok(NativeSolveResult {
        status: if best_build.is_some() {
            "exact".to_string()
        } else {
            "invalid".to_string()
        },
        exact: best_build.is_some(),
        score: best_build.as_ref().map(|_| state.best_score),
        best_build,
        upper_bound: state.best_selected.as_ref().map(|_| state.best_score),
        elapsed_ms: started.elapsed().as_millis(),
        visited_nodes: visited,
        evaluations: state.evaluations,
        pruned_by_bound,
        pruned_by_constraint,
        enumerated_completions: enumerated,
    })
}

fn atomic_score(value: f64) -> f64 {
    f64::from_bits(value.to_bits())
}

fn shared_best_score(incumbent: &SharedIncumbent) -> f64 {
    atomic_score(f64::from_bits(
        incumbent.score_bits.load(AtomicOrdering::Acquire),
    ))
}

fn consider_parallel(
    problem: &NativeProblem,
    requirements: &Value,
    incumbent: &SharedIncumbent,
    counters: &ParallelCounters,
    selected: &[usize; GROUP_COUNT],
    stats: &Stats,
) -> Result<(), String> {
    counters.evaluations.fetch_add(1, AtomicOrdering::Relaxed);
    let summary = evaluate_summary_from_map(&problem.base_context, stats)?;
    if !feasible(&summary, requirements) {
        return Ok(());
    }
    let score = summary.optimization_damage_factor;
    // Most completed candidates are below the current lower bound. Avoid a
    // mutex acquisition for that common case; equality still takes the lock
    // so lexical build-ID ties remain deterministic.
    if score < shared_best_score(incumbent) - EPSILON {
        return Ok(());
    }
    let id = build_id(&problem.groups, selected);
    let mut current = incumbent
        .record
        .lock()
        .map_err(|_| "D4 incumbent mutex was poisoned".to_string())?;
    if better(score, &id, current.best_score, &current.best_id) {
        current.best_score = score;
        current.best_id = id;
        current.best_selected = Some(*selected);
        incumbent
            .score_bits
            .store(score.to_bits(), AtomicOrdering::Release);
    }
    Ok(())
}

#[allow(clippy::too_many_arguments)]
fn enumerate_box_parallel(
    index: usize,
    clusters: &[Arc<TreeNode>; GROUP_COUNT],
    problem: &NativeProblem,
    requirements: &Value,
    incumbent: &SharedIncumbent,
    counters: &ParallelCounters,
    cancel: Option<&AtomicBool>,
    selected: &mut [usize; GROUP_COUNT],
    stats: &Stats,
) -> Result<bool, String> {
    if cancel.is_some_and(|signal| signal.load(AtomicOrdering::Acquire)) {
        return Ok(false);
    }
    if index == GROUP_COUNT {
        counters.enumerated.fetch_add(1, AtomicOrdering::Relaxed);
        consider_parallel(problem, requirements, incumbent, counters, selected, stats)?;
        return Ok(true);
    }
    let mut indices = Vec::with_capacity(clusters[index].size);
    cluster_indices(&clusters[index], &mut indices);
    for package_index in indices {
        selected[index] = package_index;
        let next = add_stats(
            stats.clone(),
            &problem.groups[index].packages[package_index].stat_delta,
        );
        if !enumerate_box_parallel(
            index + 1,
            clusters,
            problem,
            requirements,
            incumbent,
            counters,
            cancel,
            selected,
            &next,
        )? {
            return Ok(false);
        }
    }
    Ok(true)
}

fn search_parallel_shard(
    root: WorkItem,
    problem: &NativeProblem,
    requirements: &Value,
    incumbent: &SharedIncumbent,
    counters: &ParallelCounters,
    cancel: Option<&AtomicBool>,
) -> Result<bool, String> {
    let mut heap = BinaryHeap::new();
    heap.push(root);
    while let Some(node) = heap.pop() {
        if cancel.is_some_and(|signal| signal.load(AtomicOrdering::Acquire)) {
            return Ok(false);
        }
        counters.visited.fetch_add(1, AtomicOrdering::Relaxed);
        if node.upper < shared_best_score(incumbent) - EPSILON {
            counters
                .pruned_by_bound
                .fetch_add(1, AtomicOrdering::Relaxed);
            continue;
        }
        if box_combinations(&node.clusters, SMALL_BOX_LIMIT) <= SMALL_BOX_LIMIT {
            if !enumerate_box_parallel(
                0,
                &node.clusters,
                problem,
                requirements,
                incumbent,
                counters,
                cancel,
                &mut [0; GROUP_COUNT],
                &Stats::new(),
            )? {
                return Ok(false);
            }
            continue;
        }
        let splits = split_indices(&node.clusters);
        if splits.is_empty() {
            continue;
        }
        let mut child_boxes = vec![node.clusters.clone()];
        for split in splits {
            let mut expanded = Vec::with_capacity(child_boxes.len() * 2);
            for box_clusters in child_boxes {
                for child in [
                    box_clusters[split].left.clone(),
                    box_clusters[split].right.clone(),
                ]
                .into_iter()
                .flatten()
                {
                    let mut next = box_clusters.clone();
                    next[split] = child;
                    expanded.push(next);
                }
            }
            child_boxes = expanded;
        }
        for child_clusters in child_boxes {
            let stats = box_stats(&child_clusters);
            counters.evaluations.fetch_add(1, AtomicOrdering::Relaxed);
            let bound = evaluate_summary_from_map(&problem.base_context, &stats)?;
            if !feasible(&bound, requirements) {
                counters
                    .pruned_by_constraint
                    .fetch_add(1, AtomicOrdering::Relaxed);
            } else if bound.optimization_damage_factor < shared_best_score(incumbent) - EPSILON {
                counters
                    .pruned_by_bound
                    .fetch_add(1, AtomicOrdering::Relaxed);
            } else {
                heap.push(WorkItem {
                    upper: bound.optimization_damage_factor,
                    clusters: child_clusters,
                });
            }
        }
    }
    Ok(true)
}

fn create_parallel_shards(
    root: WorkItem,
    target: usize,
    problem: &NativeProblem,
    requirements: &Value,
    state: &mut SearchState,
) -> Result<Vec<WorkItem>, String> {
    let mut frontier = BinaryHeap::new();
    frontier.push(root);
    while frontier.len() < target {
        let Some(node) = frontier.pop() else {
            break;
        };
        if node.upper < state.best_score - EPSILON {
            continue;
        }
        if box_combinations(&node.clusters, SMALL_BOX_LIMIT) <= SMALL_BOX_LIMIT {
            frontier.push(node);
            break;
        }
        let splits = split_indices(&node.clusters);
        if splits.is_empty() {
            frontier.push(node);
            break;
        }
        let mut child_boxes = vec![node.clusters.clone()];
        for split in splits {
            let mut expanded = Vec::with_capacity(child_boxes.len() * 2);
            for box_clusters in child_boxes {
                for child in [
                    box_clusters[split].left.clone(),
                    box_clusters[split].right.clone(),
                ]
                .into_iter()
                .flatten()
                {
                    let mut next = box_clusters.clone();
                    next[split] = child;
                    expanded.push(next);
                }
            }
            child_boxes = expanded;
        }
        for child_clusters in child_boxes {
            let stats = box_stats(&child_clusters);
            state.evaluations += 1;
            let bound = evaluate_summary_from_map(&problem.base_context, &stats)?;
            if !feasible(&bound, requirements) {
                continue;
            }
            if bound.optimization_damage_factor >= state.best_score - EPSILON {
                frontier.push(WorkItem {
                    upper: bound.optimization_damage_factor,
                    clusters: child_clusters,
                });
            }
        }
    }
    Ok(frontier.into_vec())
}

/// Run the exact D4 tree using every thread the caller authorizes. Candidate
/// packages, trees and the base context stay shared; only compact box handles
/// and local heaps belong to workers.
pub fn solve_exact_parallel(
    problem: &NativeProblem,
    requested_threads: usize,
) -> Result<NativeParallelSolveResult, String> {
    solve_exact_parallel_with_control(problem, requested_threads, None)
}

/// The cancellable native path returns a valid incumbent with `cancelled`
/// status.  It deliberately never calls an interrupted search exact.
pub fn solve_exact_parallel_cancellable(
    problem: &NativeProblem,
    requested_threads: usize,
    cancel: &AtomicBool,
) -> Result<NativeParallelSolveResult, String> {
    solve_exact_parallel_with_control(problem, requested_threads, Some(cancel))
}

fn solve_exact_parallel_with_control(
    problem: &NativeProblem,
    requested_threads: usize,
    cancel: Option<&AtomicBool>,
) -> Result<NativeParallelSolveResult, String> {
    if !problem.base_context.is_object()
        || problem.groups.len() != GROUP_COUNT
        || problem.groups.iter().any(|group| group.packages.is_empty())
    {
        return Err("D4 native solver requires four nonempty prepared groups".to_string());
    }
    let started = Instant::now();
    let mut keys = problem.metadata.modeled_keys.clone();
    if keys.is_empty() {
        keys = problem
            .groups
            .iter()
            .flat_map(|group| group.packages.iter())
            .flat_map(|package| package.stat_delta.keys().cloned())
            .collect();
    }
    keys.sort();
    keys.dedup();
    let trees = problem
        .groups
        .iter()
        .map(|group| {
            build_tree(
                &group.packages,
                (0..group.packages.len()).collect(),
                &keys,
                &global_ranges(&group.packages, &keys),
                &problem.base_context,
                "r".to_string(),
            )
        })
        .collect::<Vec<_>>();
    let clusters: [Arc<TreeNode>; GROUP_COUNT] = trees
        .try_into()
        .map_err(|_| "D4 native solver expected four trees".to_string())?;
    let requirements = problem
        .scenario_snapshot
        .get("requirements")
        .unwrap_or(&Value::Null);
    let mut seed = SearchState {
        best_score: f64::NEG_INFINITY,
        ..SearchState::default()
    };
    for selected in initial_selections(problem) {
        let stats = selection_stats(problem, &selected);
        consider(problem, requirements, &mut seed, &selected, &stats)?;
    }
    if let Some(mut selected) = seed.best_selected {
        for _ in 0..HEURISTIC_PASSES {
            let mut changed = false;
            for group_index in 0..GROUP_COUNT {
                let baseline = selected;
                let before_id = seed.best_id.clone();
                for package_index in
                    heuristic_candidate_pool(&problem.groups[group_index], baseline[group_index])
                {
                    let mut trial = baseline;
                    trial[group_index] = package_index;
                    let stats = selection_stats(problem, &trial);
                    consider(problem, requirements, &mut seed, &trial, &stats)?;
                }
                if seed.best_id != before_id {
                    changed = true;
                    selected = seed.best_selected.unwrap_or(selected);
                }
            }
            if !changed {
                break;
            }
        }
    }
    let root_stats = box_stats(&clusters);
    seed.evaluations += 1;
    let root = evaluate_summary_from_map(&problem.base_context, &root_stats)?;
    if !feasible(&root, requirements) {
        return Ok(NativeParallelSolveResult {
            result: NativeSolveResult {
                status: "invalid".to_string(),
                exact: false,
                score: None,
                best_build: None,
                upper_bound: Some(root.optimization_damage_factor),
                elapsed_ms: started.elapsed().as_millis(),
                visited_nodes: 0,
                evaluations: seed.evaluations,
                pruned_by_bound: 0,
                pruned_by_constraint: 0,
                enumerated_completions: 0,
            },
            threads_used: 0,
            scheduled_shards: 0,
            completed_shards: 0,
        });
    }
    let threads = requested_threads.max(1);
    let shards = create_parallel_shards(
        WorkItem {
            upper: root.optimization_damage_factor,
            clusters,
        },
        threads.saturating_mul(8).max(threads),
        problem,
        requirements,
        &mut seed,
    )?;
    let scheduled_shards = shards.len();
    if shards.is_empty() {
        let best_build = seed.best_selected.as_ref().map(|selected| NativeBuild {
            id: seed.best_id.clone(),
            package_ids: selected
                .iter()
                .enumerate()
                .map(|(group, index)| problem.groups[group].packages[*index].id.clone())
                .collect(),
            stat_delta: selection_stats(problem, selected),
        });
        return Ok(NativeParallelSolveResult {
            result: NativeSolveResult {
                status: if best_build.is_some() {
                    "exact".to_string()
                } else {
                    "invalid".to_string()
                },
                exact: best_build.is_some(),
                score: best_build.as_ref().map(|_| seed.best_score),
                best_build,
                upper_bound: seed.best_selected.as_ref().map(|_| seed.best_score),
                elapsed_ms: started.elapsed().as_millis(),
                visited_nodes: 0,
                evaluations: seed.evaluations,
                pruned_by_bound: 0,
                pruned_by_constraint: 0,
                enumerated_completions: 0,
            },
            threads_used: 0,
            scheduled_shards: 0,
            completed_shards: 0,
        });
    }
    let used_threads = threads.min(scheduled_shards);
    let incumbent = Arc::new(SharedIncumbent {
        score_bits: AtomicU64::new(seed.best_score.to_bits()),
        record: Mutex::new(seed),
    });
    let counters = Arc::new(ParallelCounters {
        evaluations: AtomicU64::new(0),
        visited: AtomicU64::new(0),
        pruned_by_bound: AtomicU64::new(0),
        pruned_by_constraint: AtomicU64::new(0),
        enumerated: AtomicU64::new(0),
    });
    let next = AtomicUsize::new(0);
    let completed = AtomicUsize::new(0);
    let failure = Mutex::new(None::<String>);
    std::thread::scope(|scope| {
        for _ in 0..used_threads {
            let incumbent = Arc::clone(&incumbent);
            let counters = Arc::clone(&counters);
            let next = &next;
            let completed = &completed;
            let failure = &failure;
            let shards = &shards;
            scope.spawn(move || loop {
                if failure.lock().expect("D4 failure mutex poisoned").is_some() {
                    break;
                }
                if cancel.is_some_and(|signal| signal.load(AtomicOrdering::Acquire)) {
                    break;
                }
                let index = next.fetch_add(1, AtomicOrdering::Relaxed);
                if index >= shards.len() {
                    break;
                }
                match search_parallel_shard(
                    shards[index].clone(),
                    problem,
                    requirements,
                    &incumbent,
                    &counters,
                    cancel,
                ) {
                    Ok(true) => {
                        completed.fetch_add(1, AtomicOrdering::Relaxed);
                    }
                    Ok(false) => break,
                    Err(error) => {
                        *failure.lock().expect("D4 failure mutex poisoned") = Some(error);
                        break;
                    }
                }
            });
        }
    });
    if let Some(error) = failure
        .lock()
        .map_err(|_| "D4 failure mutex was poisoned".to_string())?
        .take()
    {
        return Err(error);
    }
    let completed_shards = completed.load(AtomicOrdering::Relaxed);
    let cancelled = cancel.is_some_and(|signal| signal.load(AtomicOrdering::Acquire));
    let final_state = incumbent
        .record
        .lock()
        .map_err(|_| "D4 incumbent mutex was poisoned".to_string())?;
    let best_build = final_state
        .best_selected
        .as_ref()
        .map(|selected| NativeBuild {
            id: final_state.best_id.clone(),
            package_ids: selected
                .iter()
                .enumerate()
                .map(|(group, index)| problem.groups[group].packages[*index].id.clone())
                .collect(),
            stat_delta: selection_stats(problem, selected),
        });
    let seed_evaluations = final_state.evaluations;
    let best_score = final_state.best_score;
    Ok(NativeParallelSolveResult {
        result: NativeSolveResult {
            status: if cancelled {
                "cancelled".to_string()
            } else if completed_shards == scheduled_shards && best_build.is_some() {
                "exact".to_string()
            } else {
                "invalid".to_string()
            },
            exact: !cancelled && completed_shards == scheduled_shards && best_build.is_some(),
            score: best_build.as_ref().map(|_| best_score),
            best_build,
            upper_bound: if !cancelled && completed_shards == scheduled_shards {
                Some(best_score)
            } else {
                None
            },
            elapsed_ms: started.elapsed().as_millis(),
            visited_nodes: counters.visited.load(AtomicOrdering::Relaxed),
            evaluations: seed_evaluations + counters.evaluations.load(AtomicOrdering::Relaxed),
            pruned_by_bound: counters.pruned_by_bound.load(AtomicOrdering::Relaxed),
            pruned_by_constraint: counters.pruned_by_constraint.load(AtomicOrdering::Relaxed),
            enumerated_completions: counters.enumerated.load(AtomicOrdering::Relaxed),
        },
        threads_used: used_threads,
        scheduled_shards,
        completed_shards,
    })
}

#[cfg(test)]
mod tests {
    use super::*;
    use serde_json::json;

    fn small_problem() -> NativeProblem {
        serde_json::from_value(json!({
            "baseContext":{"level":100,"mainType":"한손검","subType":"없음","armorType":"일반옷","wpnAtk":100,"wpnRefine":0,"wpnStab":100,"strBase":0,"dexBase":0,"intBase":0,"agiBase":0,"vitBase":100,"critF":100,"atkType":"PHYS","rangeType":"SHORT","bossLevel":100,"bossDef":0,"bossMdef":0,"aspdF":1000,"maxHpF":10000,"maxMpF":2000,"amprF":100},
            "scenarioSnapshot":{"requirements":{"maxHp":10000,"maxMp":2000,"amprBeforeDual":100,"normalAttackCrit":100,"aspd":1000}},
            "groups":[
              {"id":"a","packages":[{"id":"a","statDelta":{"ATKP":1}},{"id":"z","statDelta":{"ATKP":1}}]},
              {"id":"b","packages":[{"id":"b","statDelta":{"ATKP":1}}]},
              {"id":"c","packages":[{"id":"c","statDelta":{"ATKP":1}}]},
              {"id":"d","packages":[{"id":"d","statDelta":{"ATKP":1}}]}
            ]
        }))
        .unwrap()
    }

    #[test]
    fn solves_small_problem_exactly_with_lexical_tie() {
        let problem = small_problem();
        let result = solve_exact(&problem).unwrap();
        assert!(result.exact);
        assert_eq!(result.best_build.unwrap().id, "a||b||c||d");
    }

    #[test]
    fn cancelled_parallel_search_never_claims_exact() {
        let cancelled = AtomicBool::new(true);
        let result = solve_exact_parallel_cancellable(&small_problem(), 2, &cancelled).unwrap();
        assert_eq!(result.result.status, "cancelled");
        assert!(!result.result.exact);
        assert!(result.result.upper_bound.is_none());
    }

    #[test]
    fn parallel_scheduler_preserves_exact_result_at_supported_thread_counts() {
        for threads in [1, 2, 4, 8, 16, 64] {
            let result = solve_exact_parallel(&small_problem(), threads).unwrap();
            assert!(result.result.exact, "{threads} threads must remain exact");
            assert_eq!(result.result.best_build.unwrap().id, "a||b||c||d");
            assert!(result.threads_used <= threads);
        }
    }
}
