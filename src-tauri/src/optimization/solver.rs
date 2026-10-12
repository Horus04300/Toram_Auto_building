//! Native, single-threaded implementation of the CrystaOptimization CandidateTree search.
//!
//! This deliberately mirrors the JavaScript optimizer's prepared-problem
//! search: identical heuristic seeds, CandidateTree splitting, two-dimensional
//! box expansion, safe envelope bounds, small-box enumeration, and lexical
//! build-ID tie breaking. It also provides the serial oracle for parallel search.

use std::cmp::Ordering;
use std::collections::{BTreeMap, BinaryHeap, HashSet};
use std::sync::atomic::{AtomicBool, AtomicU64, AtomicUsize, Ordering as AtomicOrdering};
use std::sync::{Arc, Mutex};
use std::time::{Duration, Instant};

use serde::{Deserialize, Serialize};
use serde_json::Value;

#[cfg(test)]
use crate::crysta_native_evaluator::evaluate_summary_from_native_stats as evaluate_summary_from_map;
use crate::crysta_native_evaluator::joint_supply::{Form, SupplyPlan};
#[cfg(test)]
use crate::crysta_native_evaluator::CrystaOptimizationNativeSummary;
use crate::crysta_native_evaluator::{
    evaluate_utility_feasible_bound, evaluate_utility_feasible_score as evaluate_feasible_summary,
    evaluate_utility_feasible_score_from_sum, normal_attack_crit_base, utility_values, NativeStats,
    PreparedContext,
};

const EPSILON: f64 = 1e-9;
const GROUP_COUNT: usize = 4;
const SMALL_BOX_LIMIT: usize = 64;
const LOOKAHEAD_RELATIVE_GAP: f64 = 0.05;
const LOOKAHEAD_MAX_DEPTH: usize = 2;
pub const SESSION_NODES_PER_WORKER: usize = 32;
const HEURISTIC_CANDIDATE_LIMIT: usize = 192;
const HEURISTIC_PASSES: usize = 2;
const PAIR_SEED_RANK_LIMIT: usize = 16;
type Stats = NativeStats;

#[derive(Clone, Serialize, Deserialize)]
pub struct NativePackage {
    pub id: String,
    #[serde(rename = "statDelta", default)]
    pub stat_delta: Stats,
    /// Ordering coordinates only. Bounds and exact evaluation always use raw stats.
    #[serde(
        rename = "searchValues",
        default,
        skip_serializing_if = "Vec::is_empty"
    )]
    pub search_values: Vec<f64>,
    /// Derived for search; never replaces or serializes over the original options.
    #[serde(skip)]
    evaluation_delta: Option<Stats>,
}

impl NativePackage {
    fn evaluation_stats(&self) -> &Stats {
        // Unprepared callers (including tree/oracle helpers) retain full semantics.
        self.evaluation_delta.as_ref().unwrap_or(&self.stat_delta)
    }
}

#[derive(Clone, Serialize, Deserialize)]
pub struct NativeGroup {
    #[serde(rename = "id")]
    pub _id: String,
    pub packages: Vec<NativePackage>,
}

#[derive(Clone, Serialize, Deserialize)]
pub struct NativeProblem {
    #[serde(rename = "baseContext")]
    pub base_context: PreparedContext,
    #[serde(rename = "scenarioSnapshot", default)]
    pub scenario_snapshot: Value,
    #[serde(default)]
    pub metadata: NativeMetadata,
    pub groups: Vec<NativeGroup>,
    #[serde(skip)]
    trees: Arc<TreeArena>,
}

impl NativeProblem {
    fn prepare_trees(&mut self) -> Result<[NodeId; GROUP_COUNT], String> {
        let mut keys = self.metadata.modeled_keys.clone();
        if keys.is_empty() {
            keys = self
                .groups
                .iter()
                .flat_map(|g| &g.packages)
                .flat_map(|p| p.stat_delta.keys().map(str::to_owned))
                .collect();
        }
        keys.sort();
        keys.dedup();
        let capacity = tree_capacity(self.groups.iter().map(|g| g.packages.len()))?;
        let mut trees = TreeArena::default();
        if !self.metadata.search_keys.is_empty()
            && self.groups.iter().flat_map(|g| &g.packages).all(|p| {
                p.search_values.len() == self.metadata.search_keys.len()
                    && p.search_values.iter().all(|v| v.is_finite())
            })
        {
            trees.ordering_keys = self.metadata.search_keys.clone();
        }
        trees
            .nodes
            .try_reserve_exact(capacity)
            .map_err(|error| format!("CrystaOptimization tree allocation failed: {error}"))?;
        for (index, group) in self.groups.iter().enumerate() {
            let ranges = ordering_ranges(
                &group.packages,
                if trees.ordering_keys.is_empty() {
                    &keys
                } else {
                    &trees.ordering_keys
                },
                !trees.ordering_keys.is_empty(),
            );
            trees.roots[index] = build_tree(
                &mut trees,
                &group.packages,
                (0..group.packages.len()).collect(),
                &keys,
                &ranges,
                &self.base_context,
                "r".into(),
            );
        }
        let roots = trees.roots;
        self.trees = Arc::new(trees);
        let supply = SupplyBounds::prepare(self, &roots);
        let joint = JointUtilityBounds::prepare(self, &roots)?;
        let trees = Arc::get_mut(&mut self.trees).unwrap();
        trees.joint = joint;
        trees.supply = Some(supply);
        Ok(roots)
    }

    fn prepare_evaluation_stats(&mut self) {
        for group in &mut self.groups {
            for package in &mut group.packages {
                package.evaluation_delta = Some(package.stat_delta.evaluation_projection());
            }
        }
    }
}

#[derive(Clone, Default, Serialize, Deserialize)]
pub struct NativeMetadata {
    #[serde(rename = "modeledKeys", default)]
    pub modeled_keys: Vec<String>,
    #[serde(rename = "initialPackageIds", default)]
    pub initial_package_ids: Vec<String>,
    #[serde(rename = "searchKeys", default, skip_serializing_if = "Vec::is_empty")]
    pub search_keys: Vec<String>,
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
    #[serde(rename = "scheduler")]
    pub scheduler: NativeSchedulerTelemetry,
}

#[derive(Clone, Debug, Default, Serialize)]
pub struct NativeSchedulerTelemetry {
    #[serde(rename = "splitCount")]
    pub split_count: u64,
    #[serde(rename = "stealCount")]
    pub steal_count: u64,
    #[serde(rename = "workBusyMicros")]
    pub work_busy_micros: u64,
    #[serde(rename = "workerBusyMicros")]
    pub worker_busy_micros: Vec<u64>,
    #[serde(rename = "longestWorkItemMicros")]
    pub longest_work_item_micros: u64,
}

/// Arena offsets are assigned in preorder, preserving lexical path order
/// within each equipment tree. Only the arena owns nodes, never queue entries.
#[derive(Clone, Copy, Debug, Default, PartialEq, Eq, PartialOrd, Ord)]
struct NodeId(u32);

#[derive(Clone, Default)]
struct TreeArena {
    nodes: Vec<TreeNode>,
    roots: [NodeId; GROUP_COUNT],
    joint: Option<JointUtilityBounds>,
    supply: Option<SupplyBounds>,
    ordering_keys: Vec<String>,
}

const SUPPLY_METRICS: usize = 6; // Display CSPD/cast planes do not enter the search objective.
const SUPPLY_BASE: usize = SUPPLY_METRICS + 6;
const SUPPLY_DIRECTIONS: usize = SUPPLY_BASE + 15;
#[derive(Clone)]
struct SupplyBounds {
    plan: Option<SupplyPlan>,
    maxima: Arc<Vec<[f64; SUPPLY_DIRECTIONS]>>,
    constants: [f64; SUPPLY_DIRECTIONS],
    direction_count: usize,
}
impl SupplyBounds {
    fn prepare(problem: &NativeProblem, roots: &[NodeId; GROUP_COUNT]) -> Self {
        let groups: Vec<Vec<_>> = problem
            .groups
            .iter()
            .map(|g| {
                g.packages
                    .iter()
                    .map(NativePackage::evaluation_stats)
                    .collect()
            })
            .collect();
        let plan = SupplyPlan::prepare(&problem.base_context, &groups);
        let mut result = Self {
            plan,
            maxima: Arc::new(vec![[0.0; SUPPLY_DIRECTIONS]; problem.trees.nodes.len()]),
            constants: [0.0; SUPPLY_DIRECTIONS],
            direction_count: SUPPLY_BASE,
        };
        let Some(plan) = result.plan.clone() else {
            result.constants.fill(f64::INFINITY);
            return result;
        };
        let mut directions: Vec<Form> = plan.upper[..SUPPLY_METRICS].to_vec();
        directions.extend_from_slice(&plan.stages);
        let goals = Requirements::new(
            problem
                .scenario_snapshot
                .get("requirements")
                .unwrap_or(&Value::Null),
        );
        let minima = [
            goals.max_hp,
            goals.max_mp,
            goals.ampr,
            goals.crit,
            goals.aspd,
        ];
        for (i, form) in directions.iter().enumerate() {
            result.constants[i] = form.constant + form.error;
        }
        for (i, root) in roots.iter().enumerate() {
            result.fill(problem, i, *root, &directions);
        }
        let root_upper = result.metric(roots, 0);
        for (i, minimum) in minima.into_iter().enumerate() {
            if let Some(minimum) = minimum.filter(|v| *v > 0.0) {
                // A universally satisfied goal, or constant upper form, cannot
                // tighten this damage plane by adding a nonnegative multiplier.
                if plan.lower[i + 1] >= minimum
                    || plan.upper[i + 1].coefficients.iter().all(|v| *v == 0.0)
                {
                    continue;
                }
                for scale in [0.25, 1.0, 4.0] {
                    let weight = root_upper.abs() / minimum * scale;
                    if !weight.is_finite() {
                        continue;
                    }
                    let mut form = plan.weighted(i + 1, weight);
                    form.constant -= weight * minimum;
                    form.error += 256.0 * f64::EPSILON * (1.0 + (weight * minimum).abs());
                    directions.push(form);
                }
            }
        }
        result.direction_count = directions.len();
        for (i, form) in directions.iter().enumerate() {
            result.constants[i] = form.constant + form.error;
        }
        for (i, root) in roots.iter().enumerate() {
            result.fill(problem, i, *root, &directions);
        }
        result
    }
    fn fill(&mut self, problem: &NativeProblem, group: usize, node: NodeId, directions: &[Form]) {
        let tree = &problem.trees[node];
        if let Some(package) = tree.package {
            for (i, form) in directions.iter().enumerate() {
                Arc::get_mut(&mut self.maxima).expect("unshared preparation")[node.0 as usize][i] =
                    form.package(problem.groups[group].packages[package].evaluation_stats());
            }
        } else if let (Some(left), Some(right)) = (tree.left, tree.right) {
            self.fill(problem, group, left, directions);
            self.fill(problem, group, right, directions);
            for i in 0..directions.len() {
                let maximum = self.maxima[left.0 as usize][i].max(self.maxima[right.0 as usize][i]);
                Arc::get_mut(&mut self.maxima).expect("unshared preparation")[node.0 as usize][i] =
                    maximum;
            }
        }
    }
    fn legacy_safe(&self) -> bool {
        self.plan.as_ref().is_some_and(|p| p.legacy_safe)
    }
    fn metric(&self, clusters: &[NodeId; GROUP_COUNT], metric: usize) -> f64 {
        let mut value = self.constants[metric];
        let mut magnitude = value.abs();
        for node in clusters {
            let term = self.maxima[node.0 as usize][metric];
            value += term;
            magnitude += term.abs();
        }
        value + 256.0 * f64::EPSILON * (1.0 + magnitude)
    }
    fn score(&self, clusters: &[NodeId; GROUP_COUNT]) -> f64 {
        (SUPPLY_BASE..self.direction_count).fold(self.metric(clusters, 0), |bound, i| {
            bound.min(self.metric(clusters, i))
        })
    }
}

struct BoxBound {
    optimization_damage_factor: f64,
}
fn evaluate_box(
    problem: &NativeProblem,
    clusters: &[NodeId; GROUP_COUNT],
    requirements: Option<&Requirements>,
) -> Result<Option<BoxBound>, String> {
    let supply = problem.trees.supply.as_ref();
    if let (Some(supply), Some(requirements)) = (supply, requirements) {
        if (0..5).any(|i| !requirements.accepts_value(i, supply.metric(clusters, i + 1))) {
            return Ok(None);
        }
    }
    let mut score = supply.map_or(f64::INFINITY, |s| s.score(clusters));
    if supply.is_none_or(SupplyBounds::legacy_safe) {
        let stats = box_stats(&problem.trees, clusters);
        let accepts = |i, v| requirements.is_none_or(|r| r.accepts_value(i, v));
        let old = if let Some(supply) = supply {
            let caps = std::array::from_fn(|i| supply.metric(clusters, SUPPLY_METRICS + i));
            evaluate_utility_feasible_bound(&problem.base_context, &stats, &caps, accepts)?
        } else {
            evaluate_feasible_summary(&problem.base_context, &stats, accepts)?
        };
        let Some(old) = old else {
            return Ok(None);
        };
        score = score.min(old.optimization_damage_factor);
    }
    Ok(Some(BoxBound {
        optimization_damage_factor: score,
    }))
}

// Nonnegative integer directions are a cost/strength choice, not game constants.
// The two axis directions retain tradeoffs when the other utility is slack.
const JOINT_WEIGHTS: [(f64, f64); 7] = [
    (1.0, 4.0),
    (1.0, 2.0),
    (1.0, 1.0),
    (2.0, 1.0),
    (4.0, 1.0),
    (1.0, 0.0),
    (0.0, 1.0),
];
const MIXED_DIRECTIONS: usize = 5;
const JOINT_DIRECTIONS: usize = JOINT_WEIGHTS.len();
const OFFENSE_SCALES: [f64; 3] = [1.0, 2.0, 4.0];
const OFFENSE_DIRECTIONS: usize = JOINT_WEIGHTS.len() * OFFENSE_SCALES.len();

/// Outward integer relaxation, never a change to the evaluator's raw options.
/// ceil(x/unit) bounds each package coordinate from above. Power-of-two units
/// keep scaling exact; bounded support sums remain exactly representable.
#[derive(Clone, Copy)]
struct BoundCoordinate {
    unit: f64,
    integral: bool,
    low: f64,
    high: f64,
}

impl BoundCoordinate {
    fn new(problem: &NativeProblem, key: &str) -> Option<Self> {
        let mut largest: f64 = 0.0;
        let mut integral = true;
        for group in &problem.groups {
            for package in &group.packages {
                let value = package.stat_delta.get(key).copied().unwrap_or(0.0);
                if !value.is_finite() {
                    return None;
                }
                largest = largest.max(value.abs());
                integral &= value.fract() == 0.0;
            }
        }
        let mut unit = if integral { 1.0 } else { 1.0 / 1024.0 };
        while largest / unit > 1_000_000.0 {
            unit *= 2.0;
        }
        let (mut low, mut high) = (0.0, 0.0);
        for group in &problem.groups {
            let (mut min, mut max) = (f64::INFINITY, f64::NEG_INFINITY);
            for package in &group.packages {
                let value = package.stat_delta.get(key).copied().unwrap_or(0.0) / unit;
                min = min.min(value.floor());
                max = max.max(value.ceil());
            }
            low += min;
            high += max;
        }
        ((low * unit).is_finite() && (high * unit).is_finite()).then_some(Self {
            unit,
            integral: integral && unit == 1.0,
            low,
            high,
        })
    }

    fn upper(self, value: f64) -> f64 {
        if self.integral {
            value
        } else {
            (value / self.unit).ceil()
        }
    }
}

/// Lagrangian coordinate bounds for feasible completions only. For positive
/// k and nonnegative a,c, max(k*D+a*M+c*C)-a*A-c*Cmin bounds k*D from above.
/// Integral inputs couple flat CRIT/CRITP in C and scale D/M by the same unit;
/// the fallback uses flat CRIT with the optimistic CRITP envelope.
/// All support arithmetic is bounded integer arithmetic; division is rounded
/// down only because the supported damage coordinates are integers as well.
#[derive(Clone)]
struct ConstrainedOffenseBounds {
    keys: [&'static str; 3],
    enabled: [bool; 3],
    axis_enabled: [bool; 3],
    coordinates: [Option<BoundCoordinate>; 3],
    maxima: Vec<[[f64; OFFENSE_DIRECTIONS]; 3]>,
}

/// With integral flat CRIT, base flat/resistance and a positive goal, the
/// evaluator's floor is equivalent to this necessary linear CRIT/CRITP sum.
#[derive(Clone, Copy)]
struct LinearCritBound {
    scale: f64,
    percent_weight: f64,
    minimum: f64,
}

impl LinearCritBound {
    fn prepare(problem: &NativeProblem, minimum: f64) -> Option<Self> {
        let base = normal_attack_crit_base(&problem.base_context);
        let number = |key| {
            problem
                .base_context
                .get(key)
                .and_then(Value::as_f64)
                .unwrap_or(0.0)
        };
        let (percent, flat, resistance) =
            (number("critP"), number("critF"), number("bossCritResist"));
        // This exact integer support budget is independent of weapon/skill IDs.
        // Fractional/large raw coordinates keep the existing outward relaxation.
        if !(0.0..=100.0).contains(&minimum)
            || minimum == 0.0
            || ![base, percent, flat, resistance]
                .iter()
                .all(|v| v.is_finite() && v.fract() == 0.0 && v.abs() <= 1_000_000.0)
            || !BoundCoordinate::new(problem, "CRIT")?.integral
            || !BoundCoordinate::new(problem, "CRITP")?.integral
        {
            return None;
        }
        let (mut divisor, mut remainder) = (100_u64, base.abs() as u64);
        while remainder != 0 {
            (divisor, remainder) = (remainder, divisor % remainder);
        }
        let scale = 100.0 / divisor as f64;
        let percent_weight = base / divisor as f64;
        Some(Self {
            scale,
            percent_weight,
            minimum: scale * (minimum.ceil() + resistance - flat)
                - percent_weight * (100.0 + percent),
        })
    }
}

/// Cache mixed AMPR/critical support over actual packages. Critical supply is
/// either the coupled CRIT/CRITP sum or the original outward flat-CRIT bound.
/// A support sum below the necessary supply proves the box infeasible even
/// when its separate utility envelopes pass.
/// No damage formula, package deletion, or heuristic score enters this proof.
#[derive(Clone)]
struct JointUtilityBounds {
    minima: Vec<[f64; JOINT_DIRECTIONS]>,
    crit_p_low: f64,
    crit_p_stride: f64,
    crit_p_ascending: bool,
    coordinates: [BoundCoordinate; 3],
    weights: [(f64, f64); JOINT_DIRECTIONS],
    crit_p: Vec<f64>,
    maxima: Vec<[f64; MIXED_DIRECTIONS]>,
    offense: ConstrainedOffenseBounds,
    linear_crit: Option<LinearCritBound>,
}

impl JointUtilityBounds {
    fn monotone_ampr(problem: &NativeProblem) -> bool {
        let profile = problem.base_context.get("normalAttackAmprProfile");
        ["passive", "activeCandidates"].iter().all(|key| {
            profile
                .and_then(|p| p.get(key))
                .and_then(Value::as_array)
                .is_none_or(|modifiers| {
                    modifiers.iter().all(|modifier| {
                        // Match the evaluator's defaults, including malformed/null
                        // numeric fields. Floors, nonnegative scales, composition
                        // and the maximum over active candidates are monotone.
                        let finite = |key, default| {
                            modifier
                                .get(key)
                                .and_then(Value::as_f64)
                                .filter(|v| v.is_finite())
                                .unwrap_or(default)
                        };
                        finite("percent", 0.0) >= -100.0 && finite("multiplier", 1.0) >= 0.0
                    })
                })
        })
    }

    fn required_stat(
        problem: &NativeProblem,
        envelope: &mut Stats,
        key: &str,
        utility: usize,
        minimum: f64,
        coordinate: BoundCoordinate,
    ) -> Result<f64, String> {
        // If r is the first integer probe satisfying the monotone utility, any
        // feasible real x/unit is > r-1, hence sum(ceil(package/unit)) >= r.
        // This also covers fractional options without rounding the raw input.
        let (mut low, mut high) = (coordinate.low, coordinate.high + 1.0);
        while low < high {
            let mid = (low + (high - low) / 2.0).floor();
            envelope.insert(key.into(), mid * coordinate.unit);
            if utility_values(&problem.base_context, envelope)?[utility] >= minimum {
                high = mid;
            } else {
                low = mid + 1.0;
            }
        }
        Ok(low)
    }

    fn prepare(
        problem: &NativeProblem,
        roots: &[NodeId; GROUP_COUNT],
    ) -> Result<Option<Self>, String> {
        let requirements = Requirements::new(
            problem
                .scenario_snapshot
                .get("requirements")
                .unwrap_or(&Value::Null),
        );
        let ampr = requirements
            .ampr
            .filter(|v| v.is_finite())
            .filter(|_| Self::monotone_ampr(problem));
        let crit = requirements.crit.filter(|v| v.is_finite() && *v > 0.0);
        // No useful restriction remains, rather than a build-specific bypass.
        if ampr.is_none() && crit.is_none() {
            return Ok(None);
        }
        let (Some(ampr_coordinate), Some(crit_coordinate), Some(crit_p_coordinate)) = (
            BoundCoordinate::new(problem, "AMPR"),
            BoundCoordinate::new(problem, "CRIT"),
            BoundCoordinate::new(problem, "CRITP"),
        ) else {
            return Ok(None);
        };
        let crit_p_low = crit_p_coordinate.low;
        let crit_p_high = crit_p_coordinate.high;
        // Wide/fractional CRITP domains use optimistic bucket endpoints; the
        // table budget controls strength, never whether the bound is enabled.
        let crit_p_stride = ((crit_p_high - crit_p_low) / 2048.0).ceil().max(1.0);
        let crit_p_ascending = problem
            .base_context
            .get("crtBase")
            .and_then(Value::as_f64)
            .unwrap_or(0.0)
            >= -85.0;
        let weights = JOINT_WEIGHTS.map(|(a, c)| {
            (
                if ampr.is_some() { a } else { 0.0 },
                if crit.is_some() { c } else { 0.0 },
            )
        });
        // Build only the utility dependencies, from raw packages. Do not rely on
        // caller-provided modeledKeys being complete for this additional bound.
        let keys = ["INT", "INTP", "MAXMP"].map(String::from);
        let mut envelope = problem.groups.iter().fold(Stats::new(), |sum, group| {
            add_stats(
                sum,
                &group_envelope(
                    &group.packages,
                    &(0..group.packages.len()).collect::<Vec<_>>(),
                    &keys,
                ),
            )
        });
        // INT percent moves in the opposite direction for negative base INT.
        if problem
            .base_context
            .get("intBase")
            .and_then(Value::as_f64)
            .unwrap_or(0.0)
            < 0.0
        {
            let minimum = problem
                .groups
                .iter()
                .map(|group| {
                    group
                        .packages
                        .iter()
                        .map(|p| p.stat_delta.get("INTP").copied().unwrap_or(0.0))
                        .reduce(f64::min)
                        .unwrap_or(0.0)
                })
                .sum();
            envelope.insert("INTP".into(), minimum);
        }
        let required_ampr = match ampr {
            Some(minimum) => {
                Self::required_stat(problem, &mut envelope, "AMPR", 2, minimum, ampr_coordinate)?
            }
            None => ampr_coordinate.low,
        };
        let buckets = ((crit_p_high - crit_p_low) / crit_p_stride).floor() as usize + 1;
        let mut minima = Vec::with_capacity(buckets);
        for index in 0..buckets {
            let p = if crit_p_ascending {
                (crit_p_low + (index as f64 + 1.0) * crit_p_stride).min(crit_p_high)
            } else {
                crit_p_low + index as f64 * crit_p_stride
            };
            // Preserve the exact per-integer table for ordinary integral CRITP.
            let p = if crit_p_stride == 1.0 && crit_p_coordinate.unit == 1.0 {
                crit_p_low + index as f64
            } else {
                p
            };
            envelope.insert("CRITP".into(), p * crit_p_coordinate.unit);
            let required_crit = match crit {
                Some(minimum) => Self::required_stat(
                    problem,
                    &mut envelope,
                    "CRIT",
                    3,
                    minimum,
                    crit_coordinate,
                )?,
                None => crit_coordinate.low,
            };
            minima.push(weights.map(|(a, c)| a * required_ampr + c * required_crit));
        }
        // If both constraints impose only the coordinate domain minima, no
        // support can beat the original envelope. Avoid a vacuous hot-loop cost.
        if minima.iter().all(|required| {
            required
                .iter()
                .zip(weights)
                .all(|(r, (a, c))| *r <= a * ampr_coordinate.low + c * crit_coordinate.low)
        }) {
            return Ok(None);
        }
        let attack_key = if problem
            .base_context
            .get("atkType")
            .and_then(Value::as_str)
            .is_some_and(|v| v.eq_ignore_ascii_case("MAG"))
        {
            "MATKP"
        } else {
            "ATKP"
        };
        let range_key = if problem
            .base_context
            .get("rangeType")
            .and_then(Value::as_str)
            .is_some_and(|v| v.eq_ignore_ascii_case("LONG"))
        {
            "LRW"
        } else {
            "SRW"
        };
        let keys = [attack_key, range_key, "CDMG"];
        let coordinates = keys.map(|key| BoundCoordinate::new(problem, key));
        let enabled = coordinates.map(|coordinate| coordinate.is_some_and(|c| c.low < c.high));
        let linear_crit = crit.and_then(|minimum| LinearCritBound::prepare(problem, minimum));
        let support_scale = linear_crit.map_or(1.0, |bound| bound.scale);
        let weights = weights.map(|(a, c)| (a * support_scale, c));
        if let Some(bound) = linear_crit {
            for required in &mut minima {
                *required = weights.map(|(a, c)| a * required_ampr + c * bound.minimum);
            }
        }
        let mut result = Self {
            minima,
            crit_p_low,
            crit_p_stride,
            crit_p_ascending,
            coordinates: [ampr_coordinate, crit_coordinate, crit_p_coordinate],
            weights,
            linear_crit,
            crit_p: vec![0.0; problem.trees.nodes.len()],
            maxima: vec![[0.0; MIXED_DIRECTIONS]; problem.trees.nodes.len()],
            offense: ConstrainedOffenseBounds {
                keys,
                enabled,
                axis_enabled: [false; 3],
                coordinates,
                maxima: vec![[[0.0; OFFENSE_DIRECTIONS]; 3]; problem.trees.nodes.len()],
            },
        };
        for (group, root) in problem.groups.iter().zip(roots) {
            result.fill(&problem.trees, group, *root);
        }
        // Budget the additional directions by their root-bound improvement,
        // independently for each coordinate. A skipped axis retains all old
        // directions. This choice is not evidence for deleting any package.
        let p = roots.iter().map(|n| result.crit_p[n.0 as usize]).sum();
        let minima = &result.minima[result.bucket_index(p)];
        for coordinate in 0..3 {
            if !result.offense.enabled[coordinate] {
                continue;
            }
            let key = result.offense.keys[coordinate];
            if !problem.metadata.modeled_keys.is_empty()
                && !problem.metadata.modeled_keys.iter().any(|k| k == key)
            {
                continue;
            }
            let original: f64 = roots
                .iter()
                .map(|n| problem.trees[*n].envelope.get(key).copied().unwrap_or(0.0))
                .sum();
            let mut legacy = f64::INFINITY;
            let mut axis = f64::INFINITY;
            for (scale, k) in OFFENSE_SCALES.into_iter().enumerate() {
                for (direction, minimum) in minima.iter().enumerate() {
                    let index = scale * JOINT_DIRECTIONS + direction;
                    let support: f64 = roots
                        .iter()
                        .map(|n| result.offense.maxima[n.0 as usize][coordinate][index])
                        .sum();
                    let upper = (support - minimum) / (k * support_scale);
                    if direction < MIXED_DIRECTIONS {
                        legacy = legacy.min(upper);
                    } else {
                        axis = axis.min(upper);
                    }
                }
            }
            let unit = result.offense.coordinates[coordinate].unwrap().unit;
            result.offense.axis_enabled[coordinate] =
                (axis.floor() * unit).min(original) < (legacy.floor() * unit).min(original);
        }
        Ok(Some(result))
    }

    fn fill(&mut self, trees: &TreeArena, group: &NativeGroup, node: NodeId) {
        let tree = &trees[node];
        let index = node.0 as usize;
        if let Some(package) = tree.package {
            let stats = &group.packages[package].stat_delta;
            let ampr = self.coordinates[0].upper(stats.get("AMPR").copied().unwrap_or(0.0));
            let crit = self.linear_crit.map_or_else(
                || self.coordinates[1].upper(stats.get("CRIT").copied().unwrap_or(0.0)),
                |bound| {
                    bound.scale * stats.get("CRIT").copied().unwrap_or(0.0)
                        + bound.percent_weight * stats.get("CRITP").copied().unwrap_or(0.0)
                },
            );
            self.maxima[index] = std::array::from_fn(|i| {
                let (a, c) = self.weights[i];
                a * ampr + c * crit
            });
            let p = stats.get("CRITP").copied().unwrap_or(0.0) / self.coordinates[2].unit;
            self.crit_p[index] = if self.crit_p_ascending {
                p.ceil()
            } else {
                p.floor()
            };
            for (coordinate, key) in self.offense.keys.iter().enumerate() {
                if !self.offense.enabled[coordinate] {
                    continue;
                }
                let value = self.offense.coordinates[coordinate]
                    .unwrap()
                    .upper(stats.get(key).copied().unwrap_or(0.0))
                    * self.linear_crit.map_or(1.0, |bound| bound.scale);
                for (scale, k) in OFFENSE_SCALES.into_iter().enumerate() {
                    for (direction, (a, c)) in self.weights.into_iter().enumerate() {
                        self.offense.maxima[index][coordinate]
                            [scale * JOINT_WEIGHTS.len() + direction] =
                            k * value + a * ampr + c * crit;
                    }
                }
            }
        } else if let (Some(left), Some(right)) = (tree.left, tree.right) {
            self.fill(trees, group, left);
            self.fill(trees, group, right);
            self.maxima[index] = std::array::from_fn(|i| {
                self.maxima[left.0 as usize][i].max(self.maxima[right.0 as usize][i])
            });
            self.crit_p[index] = if self.crit_p_ascending {
                self.crit_p[left.0 as usize].max(self.crit_p[right.0 as usize])
            } else {
                self.crit_p[left.0 as usize].min(self.crit_p[right.0 as usize])
            };
            for coordinate in 0..3 {
                for direction in 0..OFFENSE_DIRECTIONS {
                    self.offense.maxima[index][coordinate][direction] = self.offense.maxima
                        [left.0 as usize][coordinate][direction]
                        .max(self.offense.maxima[right.0 as usize][coordinate][direction]);
                }
            }
        }
    }

    fn possible(&self, clusters: &[NodeId; GROUP_COUNT]) -> bool {
        // All these operations are on bounded integers exactly representable
        // by f64. Equality must survive for feasible ties.
        let p = clusters
            .iter()
            .map(|n| self.crit_p[n.0 as usize])
            .sum::<f64>();
        let minima = &self.minima[self.bucket_index(p)];
        let [first, second, third, fourth] = clusters.map(|n| &self.maxima[n.0 as usize]);
        (0..MIXED_DIRECTIONS).all(|i| first[i] + second[i] + third[i] + fourth[i] >= minima[i])
    }

    fn tighten_offense(&self, clusters: &[NodeId; GROUP_COUNT], stats: &mut Stats) {
        if !self.offense.enabled.iter().any(|v| *v) {
            return;
        }
        let [a, b, c, d] = *clusters;
        let (a, b, c, d) = (a.0 as usize, b.0 as usize, c.0 as usize, d.0 as usize);
        let p = self.crit_p[a] + self.crit_p[b] + self.crit_p[c] + self.crit_p[d];
        let first = &self.offense.maxima[a];
        let second = &self.offense.maxima[b];
        let third = &self.offense.maxima[c];
        let fourth = &self.offense.maxima[d];
        let bucket = self.bucket_index(p);
        let minima = &self.minima[bucket];
        for coordinate in 0..3 {
            let key = self.offense.keys[coordinate];
            if !self.offense.enabled[coordinate] {
                continue;
            }
            // An omitted modeled coordinate must retain its existing semantics.
            let Some(&original) = stats.get(key) else {
                continue;
            };
            let mut encoded_upper = f64::INFINITY;
            let unit = self.offense.coordinates[coordinate].unwrap().unit;
            let (first, second, third, fourth) = (
                &first[coordinate],
                &second[coordinate],
                &third[coordinate],
                &fourth[coordinate],
            );
            // Compile-time guards make changes to the direction set explicit.
            // The macro expands in the same scale-major order as the reference.
            const _: [(); 7] = [(); JOINT_WEIGHTS.len()];
            const _: [(); 3] = [(); OFFENSE_SCALES.len()];
            macro_rules! tighten_scale {
                ($scale:expr; $($direction:expr),+ $(,)?) => {$(
                    {
                        const I: usize = $scale * JOINT_WEIGHTS.len() + $direction;
                        encoded_upper = encoded_upper.min(
                            (first[I] + second[I] + third[I] + fourth[I] - minima[$direction])
                                / (OFFENSE_SCALES[$scale] * self.linear_crit.map_or(1.0, |bound| bound.scale)),
                        );
                    }
                )+};
            }
            tighten_scale!(0; 0, 1, 2, 3, 4);
            tighten_scale!(1; 0, 1, 2, 3, 4);
            tighten_scale!(2; 0, 1, 2, 3, 4);
            if self.offense.axis_enabled[coordinate] {
                tighten_scale!(0; 5, 6);
                tighten_scale!(1; 5, 6);
                tighten_scale!(2; 5, 6);
            }
            // Bounded integer supports and integer divisors <= 400 preserve
            // floors (fraction spacing exceeds the quotient's f64 ULP).
            // The positive power-of-two unit and raw envelope cap stay intact.
            let upper = original.min(encoded_upper.floor() * unit);
            if upper < original {
                stats.insert(key.into(), upper);
            }
        }
    }

    #[cfg(test)]
    fn tighten_offense_reference(&self, clusters: &[NodeId; GROUP_COUNT], stats: &mut Stats) {
        let p = clusters
            .iter()
            .map(|n| self.crit_p[n.0 as usize])
            .sum::<f64>();
        let bucket = self.bucket_index(p);
        let minima = &self.minima[bucket];
        for (coordinate, key) in self.offense.keys.iter().enumerate() {
            if !self.offense.enabled[coordinate] {
                continue;
            }
            // An omitted modeled coordinate must retain its existing semantics.
            let Some(&original) = stats.get(key) else {
                continue;
            };
            let mut upper = original;
            let unit = self.offense.coordinates[coordinate].unwrap().unit;
            let [first, second, third, fourth] =
                clusters.map(|n| &self.offense.maxima[n.0 as usize][coordinate]);
            let supports: [f64; OFFENSE_DIRECTIONS] =
                std::array::from_fn(|i| first[i] + second[i] + third[i] + fourth[i]);
            for (scale, k) in OFFENSE_SCALES.into_iter().enumerate() {
                for (direction, &required) in
                    minima
                        .iter()
                        .enumerate()
                        .take(if self.offense.axis_enabled[coordinate] {
                            JOINT_DIRECTIONS
                        } else {
                            MIXED_DIRECTIONS
                        })
                {
                    upper = upper.min(
                        ((supports[scale * JOINT_WEIGHTS.len() + direction] - required)
                            / (k * self.linear_crit.map_or(1.0, |bound| bound.scale)))
                        .floor()
                            * unit,
                    );
                }
            }
            if upper < original {
                stats.insert((*key).into(), upper);
            }
        }
    }

    fn bucket_index(&self, p: f64) -> usize {
        (((p - self.crit_p_low) / self.crit_p_stride).floor() as usize).min(self.minima.len() - 1)
    }
}

impl TreeArena {
    fn joint_utilities_possible(&self, clusters: &[NodeId; GROUP_COUNT]) -> bool {
        self.joint
            .as_ref()
            .is_none_or(|joint| joint.possible(clusters))
    }
}

impl std::ops::Index<NodeId> for TreeArena {
    type Output = TreeNode;
    fn index(&self, id: NodeId) -> &Self::Output {
        &self.nodes[id.0 as usize]
    }
}

#[derive(Clone)]
struct TreeNode {
    path: String,
    size: usize,
    envelope: Stats,
    split_score: f64,
    split_slack: f64,
    split_worst_gain: f64,
    split_best_size: usize,
    split_total_gain: f64,
    package: Option<usize>,
    left: Option<NodeId>,
    right: Option<NodeId>,
}

/// CrystaOptimization always has weapon/armor/additional/special groups. An array keeps one
/// frontier item inline: no Vec allocation and no box-path String per node.
#[derive(Clone, Copy)]
struct WorkItem {
    upper: f64,
    clusters: [NodeId; GROUP_COUNT],
}

/// Four adjacent children reduce the number of distant frontier reads per pop.
/// Uses the unchanged WorkItem order, without caching keys or enlarging entries.
#[derive(Default)]
struct WorkHeap {
    items: Vec<WorkItem>,
}

impl WorkHeap {
    fn new() -> Self {
        Self::default()
    }
    fn len(&self) -> usize {
        self.items.len()
    }
    fn is_empty(&self) -> bool {
        self.items.is_empty()
    }
    fn peek(&self) -> Option<&WorkItem> {
        self.items.first()
    }
    fn iter(&self) -> std::slice::Iter<'_, WorkItem> {
        self.items.iter()
    }
    fn push(&mut self, item: WorkItem) {
        let mut index = self.items.len();
        self.items.push(item);
        while index > 0 {
            let parent = (index - 1) / 4;
            if self.items[parent] >= self.items[index] {
                break;
            }
            self.items.swap(parent, index);
            index = parent;
        }
    }
    fn pop(&mut self) -> Option<WorkItem> {
        let last = self.items.pop()?;
        if self.items.is_empty() {
            return Some(last);
        }
        let result = std::mem::replace(&mut self.items[0], last);
        let mut index = 0;
        // A Vec<WorkItem> cannot approach usize::MAX / 4 elements.
        loop {
            let first = index * 4 + 1;
            if first >= self.items.len() {
                break;
            }
            let mut best = first;
            for child in first + 1..(first + 4).min(self.items.len()) {
                if self.items[child] > self.items[best] {
                    best = child;
                }
            }
            if self.items[index] >= self.items[best] {
                break;
            }
            self.items.swap(index, best);
            index = best;
        }
        Some(result)
    }
    fn extend(&mut self, items: impl IntoIterator<Item = WorkItem>) {
        for item in items {
            self.push(item);
        }
    }
}

#[derive(Clone, Default, Serialize, Deserialize)]
struct SearchState {
    evaluations: u64,
    #[serde(with = "checkpoint_score")]
    best_score: f64,
    best_id: String,
    best_selected: Option<[usize; GROUP_COUNT]>,
}

#[derive(Clone, Serialize, Deserialize)]
pub struct NativeSearchCheckpoint {
    pub schema: String,
    pub problem: NativeProblem,
    state: SearchState,
    frontier: Vec<NativeCheckpointWorkItem>,
    visited: u64,
    pruned_by_bound: u64,
    pruned_by_constraint: u64,
    enumerated: u64,
    terminal_invalid_upper: Option<f64>,
    elapsed_ms: u128,
}

#[derive(Clone, Serialize, Deserialize)]
struct NativeCheckpointWorkItem {
    #[serde(with = "checkpoint_score")]
    upper: f64,
    paths: [String; GROUP_COUNT],
}

// JSON numbers cannot preserve the no-incumbent and unbounded sentinels.
mod checkpoint_score {
    use serde::{Deserialize, Deserializer, Serializer};
    pub fn serialize<S: Serializer>(value: &f64, serializer: S) -> Result<S::Ok, S::Error> {
        if value.is_finite() {
            serializer.serialize_f64(*value)
        } else if *value == f64::INFINITY {
            serializer.serialize_str("Infinity")
        } else if *value == f64::NEG_INFINITY {
            serializer.serialize_str("-Infinity")
        } else {
            Err(serde::ser::Error::custom("invalid checkpoint score"))
        }
    }
    pub fn deserialize<'de, D: Deserializer<'de>>(deserializer: D) -> Result<f64, D::Error> {
        let value = serde_json::Value::deserialize(deserializer)?;
        match value {
            serde_json::Value::Number(n) => n
                .as_f64()
                .ok_or_else(|| serde::de::Error::custom("invalid score")),
            serde_json::Value::String(s) if s == "Infinity" => Ok(f64::INFINITY),
            serde_json::Value::String(s) if s == "-Infinity" => Ok(f64::NEG_INFINITY),
            _ => Err(serde::de::Error::custom("invalid checkpoint score")),
        }
    }
}

struct NodeChildren {
    buffer: usize,
    range: std::ops::Range<usize>,
}
type NodeOutcome = Result<Option<NodeChildren>, String>;
type WorkerOutcome = Result<Option<std::ops::Range<usize>>, String>;
#[derive(Default)]
struct WorkerOutput {
    outcomes: Vec<(usize, WorkerOutcome)>,
    children: Vec<WorkItem>,
}
struct NodeBatch {
    nodes: Arc<Vec<WorkItem>>,
    next: AtomicUsize,
    incumbent: Arc<SharedIncumbent>,
    counters: Arc<ParallelCounters>,
    cancel: Option<Arc<AtomicBool>>,
    deadline: Option<Instant>,
}
struct NodeJob {
    batch: Arc<NodeBatch>,
    buffer: WorkerOutput,
    output: std::sync::mpsc::Sender<WorkerOutput>,
}
struct NodePool {
    input: Option<std::sync::mpsc::Sender<NodeJob>>,
    workers: Vec<std::thread::JoinHandle<()>>,
    buffers: Vec<WorkerOutput>,
}
impl NodePool {
    fn new(
        problem: &NativeProblem,
        requirements: Requirements,
        count: usize,
    ) -> Result<Self, String> {
        let (input, receiver) = std::sync::mpsc::channel::<NodeJob>();
        let receiver = Arc::new(Mutex::new(receiver));
        let problem = Arc::new(problem.clone());
        let mut pool = Self {
            input: Some(input),
            workers: Vec::new(),
            buffers: Vec::new(),
        };
        for _ in 0..count.max(1) {
            let receiver = Arc::clone(&receiver);
            let problem = Arc::clone(&problem);
            let worker = std::thread::Builder::new()
                .name("optimization-search".into())
                .spawn(move || loop {
                    let job = receiver
                        .lock()
                        .expect("CrystaOptimization job receiver poisoned")
                        .recv();
                    let Ok(job) = job else {
                        break;
                    };
                    let batch = &job.batch;
                    // Progress is published after the batch joins. Keep hot
                    // counter writes private instead of bouncing shared cache lines.
                    let mut local_counters = LocalSearchCounters::default();
                    let mut buffer = job.buffer;
                    loop {
                        // The message shares a batch, but claims stay node-sized
                        // so expensive nodes do not strand a fixed-size chunk.
                        let index = batch.next.fetch_add(1, AtomicOrdering::Relaxed);
                        let Some(node) = batch.nodes.get(index) else {
                            break;
                        };
                        let start = buffer.children.len();
                        let outcome =
                            std::panic::catch_unwind(std::panic::AssertUnwindSafe(|| {
                                expand_parallel_node_into(
                                    node,
                                    &problem,
                                    &requirements,
                                    &batch.incumbent,
                                    &mut local_counters,
                                    batch.cancel.as_deref(),
                                    batch.deadline,
                                    &mut buffer.children,
                                )
                            }))
                            .unwrap_or_else(|_| {
                                Err("CrystaOptimization search worker panicked".into())
                            });
                        // Cancellation, errors and panics must not publish a
                        // partially expanded node. Keep earlier nodes intact.
                        if !matches!(outcome, Ok(true)) {
                            buffer.children.truncate(start);
                        }
                        buffer.outcomes.push((
                            index,
                            outcome
                                .map(|completed| completed.then_some(start..buffer.children.len())),
                        ));
                    }
                    batch.counters.merge_search_counts(local_counters);
                    // Release shared input before announcing completion.
                    drop(job.batch);
                    if job.output.send(buffer).is_err() {
                        break;
                    }
                })
                .map_err(|error| format!("CrystaOptimization worker creation failed: {error}"))?;
            pool.workers.push(worker);
        }
        Ok(pool)
    }
    fn run(
        &mut self,
        nodes: &Arc<Vec<WorkItem>>,
        results: &mut Vec<Option<NodeOutcome>>,
        incumbent: &Arc<SharedIncumbent>,
        counters: &Arc<ParallelCounters>,
        cancel: Option<&Arc<AtomicBool>>,
        deadline: Option<Instant>,
    ) -> Result<(), String> {
        results.clear();
        results.resize_with(nodes.len(), || None);
        let (output, receiver) = std::sync::mpsc::channel();
        let batch = Arc::new(NodeBatch {
            nodes: Arc::clone(nodes),
            next: AtomicUsize::new(0),
            incumbent: Arc::clone(incumbent),
            counters: Arc::clone(counters),
            cancel: cancel.cloned(),
            deadline,
        });
        for _ in 0..self.workers.len().min(nodes.len()) {
            self.input
                .as_ref()
                .expect("live pool")
                .send(NodeJob {
                    batch: Arc::clone(&batch),
                    buffer: {
                        let mut buffer = self.buffers.pop().unwrap_or_default();
                        buffer.outcomes.clear();
                        buffer.children.clear();
                        buffer
                    },
                    output: output.clone(),
                })
                .map_err(|_| "CrystaOptimization pool stopped".to_string())?;
        }
        drop(output);
        for mut buffer in receiver {
            let buffer_index = self.buffers.len();
            for (index, outcome) in buffer.outcomes.drain(..) {
                results[index] = Some(outcome.map(|range| {
                    range.map(|range| NodeChildren {
                        buffer: buffer_index,
                        range,
                    })
                }));
            }
            self.buffers.push(buffer);
        }
        if results.iter().any(Option::is_none) {
            return Err("CrystaOptimization worker result missing".into());
        }
        Ok(())
    }
}
impl Drop for NodePool {
    fn drop(&mut self) {
        self.input.take();
        for worker in self.workers.drain(..) {
            let _ = worker.join();
        }
    }
}

struct SharedIncumbent {
    score_bits: AtomicU64,
    record: Mutex<SearchState>,
}

#[derive(Default)]
struct ParallelCounters {
    evaluations: AtomicU64,
    visited: AtomicU64,
    pruned_by_bound: AtomicU64,
    pruned_by_constraint: AtomicU64,
    enumerated: AtomicU64,
    splits: AtomicU64,
    steals: AtomicU64,
    work_busy_micros: AtomicU64,
    longest_work_item_micros: AtomicU64,
}

// Owned exclusively by one worker message; recursive calls borrow mutably.
#[derive(Default)]
struct LocalSearchCounters {
    evaluations: u64,
    visited: u64,
    pruned_by_bound: u64,
    pruned_by_constraint: u64,
    enumerated: u64,
    splits: u64,
    joint_probes: u64,
    joint_rejections: u64,
}
trait SearchCounters {
    fn joint_pressure(&self) -> bool {
        false
    }
    fn count_joint_probe(&mut self, _rejected: bool) {}
    fn utility_pressure(&self) -> bool {
        false
    }
    fn count_evaluations(&mut self);
    fn count_visited(&mut self);
    fn count_pruned_by_bound(&mut self);
    fn count_pruned_by_constraint(&mut self);
    fn count_enumerated(&mut self);
    fn count_splits(&mut self);
}
impl SearchCounters for LocalSearchCounters {
    fn joint_pressure(&self) -> bool {
        self.joint_probes >= 8 && self.joint_rejections > self.joint_probes / 8
    }
    fn count_joint_probe(&mut self, rejected: bool) {
        self.joint_probes = self.joint_probes.wrapping_add(1);
        self.joint_rejections = self.joint_rejections.wrapping_add(u64::from(rejected));
    }
    fn utility_pressure(&self) -> bool {
        self.pruned_by_constraint > self.evaluations / 4
    }
    #[inline]
    fn count_evaluations(&mut self) {
        self.evaluations = self.evaluations.wrapping_add(1);
    }
    #[inline]
    fn count_visited(&mut self) {
        self.visited = self.visited.wrapping_add(1);
    }
    #[inline]
    fn count_pruned_by_bound(&mut self) {
        self.pruned_by_bound = self.pruned_by_bound.wrapping_add(1);
    }
    #[inline]
    fn count_pruned_by_constraint(&mut self) {
        self.pruned_by_constraint = self.pruned_by_constraint.wrapping_add(1);
    }
    #[inline]
    fn count_enumerated(&mut self) {
        self.enumerated = self.enumerated.wrapping_add(1);
    }
    #[inline]
    fn count_splits(&mut self) {
        self.splits = self.splits.wrapping_add(1);
    }
}
// The standalone scheduler still shares these counters across workers.
impl SearchCounters for &ParallelCounters {
    #[inline]
    fn count_evaluations(&mut self) {
        self.evaluations.fetch_add(1, AtomicOrdering::Relaxed);
    }
    #[inline]
    fn count_visited(&mut self) {
        self.visited.fetch_add(1, AtomicOrdering::Relaxed);
    }
    #[inline]
    fn count_pruned_by_bound(&mut self) {
        self.pruned_by_bound.fetch_add(1, AtomicOrdering::Relaxed);
    }
    #[inline]
    fn count_pruned_by_constraint(&mut self) {
        self.pruned_by_constraint
            .fetch_add(1, AtomicOrdering::Relaxed);
    }
    #[inline]
    fn count_enumerated(&mut self) {
        self.enumerated.fetch_add(1, AtomicOrdering::Relaxed);
    }
    #[inline]
    fn count_splits(&mut self) {
        self.splits.fetch_add(1, AtomicOrdering::Relaxed);
    }
}

impl ParallelCounters {
    fn merge_search_counts(&self, local: LocalSearchCounters) {
        for (target, value) in [
            (&self.evaluations, local.evaluations),
            (&self.visited, local.visited),
            (&self.pruned_by_bound, local.pruned_by_bound),
            (&self.pruned_by_constraint, local.pruned_by_constraint),
            (&self.enumerated, local.enumerated),
            (&self.splits, local.splits),
        ] {
            target.fetch_add(value, AtomicOrdering::Relaxed);
        }
        // Scheduler timing/steal counters belong to the standalone scheduler,
        // not expand_parallel_node, and are not collected by the session pool.
    }
}

impl PartialEq for WorkItem {
    fn eq(&self, other: &Self) -> bool {
        self.upper.total_cmp(&other.upper) == Ordering::Equal && self.clusters == other.clusters
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
            let comparison = right.cmp(left);
            if comparison != Ordering::Equal {
                return comparison;
            }
        }
        Ordering::Equal
    }
}

fn add_stats(mut left: Stats, right: &Stats) -> Stats {
    left.add_assign(right);
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
    let key = key
        .strip_prefix('@')
        .and_then(|k| k.split(':').next())
        .unwrap_or(key);
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
            // Every completion selects one package, including its penalties.
            // An absent coordinate is zero; an absent zero-valued package is not.
            .reduce(f64::max)
            .unwrap_or(0.0);
        if maximum != 0.0 {
            result.insert(key.clone(), maximum);
        }
    }
    result
}

#[cfg(test)]
fn global_ranges(packages: &[NativePackage], keys: &[String]) -> BTreeMap<String, f64> {
    ordering_ranges(packages, keys, false)
}

fn ordering_value(package: &NativePackage, index: usize, key: &str, projected: bool) -> f64 {
    if projected {
        package.search_values[index]
    } else {
        package.stat_delta.get(key).copied().unwrap_or(0.0)
    }
}

fn ordering_ranges(
    packages: &[NativePackage],
    keys: &[String],
    projected: bool,
) -> BTreeMap<String, f64> {
    keys.iter()
        .enumerate()
        .map(|(index, key)| {
            let (low, high) =
                packages
                    .iter()
                    .fold((f64::INFINITY, f64::NEG_INFINITY), |range, item| {
                        let value = ordering_value(item, index, key, projected);
                        (range.0.min(value), range.1.max(value))
                    });
            (key.clone(), (high - low).max(0.0))
        })
        .collect()
}

fn tree_capacity(counts: impl IntoIterator<Item = usize>) -> Result<usize, String> {
    counts.into_iter().try_fold(0_usize, |total, leaves| {
        let nodes = leaves.checked_mul(2).and_then(|n| n.checked_sub(1));
        nodes
            .and_then(|n| total.checked_add(n))
            .filter(|n| *n <= u32::MAX as usize)
            .ok_or_else(|| {
                "CrystaOptimization tree exceeds the supported node index range".to_string()
            })
    })
}

#[allow(clippy::too_many_arguments)]
fn build_tree(
    trees: &mut TreeArena,
    packages: &[NativePackage],
    indices: Vec<usize>,
    keys: &[String],
    ranges: &BTreeMap<String, f64>,
    context: &Value,
    path: String,
) -> NodeId {
    let envelope = group_envelope(packages, &indices, keys);
    // Cache an ordering score independently of tighter signed bounds. Each
    // node participates in many Cartesian search boxes; this is not pruning.
    let ordering_envelope = envelope
        .iter()
        .map(|(key, value)| (key.to_owned(), value.max(0.0)))
        .collect();
    let split_score = heuristic_score(&ordering_envelope, "damage");
    let id = NodeId(u32::try_from(trees.nodes.len()).expect("validated tree index range"));
    trees.nodes.push(TreeNode {
        path: path.clone(),
        size: indices.len(),
        envelope,
        split_score,
        split_slack: f64::NEG_INFINITY,
        split_worst_gain: 0.0,
        split_best_size: 0,
        split_total_gain: 0.0,
        package: (indices.len() <= 1)
            .then(|| indices.first().copied())
            .flatten(),
        left: None,
        right: None,
    });
    if indices.len() <= 1 {
        return id;
    }
    let projected = !trees.ordering_keys.is_empty();
    let ordering_keys = if projected {
        &trees.ordering_keys
    } else {
        keys
    };
    let mut split_key: Option<(usize, &str)> = None;
    let mut best_spread = f64::NEG_INFINITY;
    for (coordinate, key) in ordering_keys.iter().enumerate() {
        let global_range = ranges.get(key).copied().unwrap_or(0.0);
        if global_range <= EPSILON {
            continue;
        }
        let (low, high) =
            indices
                .iter()
                .fold((f64::INFINITY, f64::NEG_INFINITY), |range, index| {
                    let value = ordering_value(&packages[*index], coordinate, key, projected);
                    (range.0.min(value), range.1.max(value))
                });
        let spread = (high - low) / global_range * split_importance(key, context);
        if spread > best_spread + EPSILON
            || ((spread - best_spread).abs() <= EPSILON
                && key.as_str() < split_key.map(|(_, k)| k).unwrap_or("\u{ffff}"))
        {
            best_spread = spread;
            split_key = Some((coordinate, key));
        }
    }
    let mut sorted = indices;
    sorted.sort_by(|left, right| {
        let value_order = split_key
            .map(|(coordinate, key)| {
                ordering_value(&packages[*left], coordinate, key, projected).total_cmp(
                    &ordering_value(&packages[*right], coordinate, key, projected),
                )
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
    let left_id = build_tree(
        trees,
        packages,
        sorted,
        keys,
        ranges,
        context,
        format!("{path}0"),
    );
    let right_id = build_tree(
        trees,
        packages,
        right,
        keys,
        ranges,
        context,
        format!("{path}1"),
    );
    trees.nodes[id.0 as usize].left = Some(left_id);
    trees.nodes[id.0 as usize].right = Some(right_id);
    // Reward a dimension that isolates one substantially weaker child, even
    // when its sibling retains the parent's envelope. Both children survive
    // until the ordinary safe utility/damage bounds prove they can be pruned.
    trees.nodes[id.0 as usize].split_slack =
        split_score - trees[left_id].split_score.min(trees[right_id].split_score);
    let left_gain = (split_score - trees[left_id].split_score).max(0.0);
    let right_gain = (split_score - trees[right_id].split_score).max(0.0);
    trees.nodes[id.0 as usize].split_worst_gain = left_gain.min(right_gain);
    trees.nodes[id.0 as usize].split_best_size = if left_gain >= right_gain {
        trees[left_id].size
    } else {
        trees[right_id].size
    };
    trees.nodes[id.0 as usize].split_total_gain =
        left_gain * trees[left_id].size as f64 + right_gain * trees[right_id].size as f64;
    id
}

#[derive(Clone, Copy, Default)]
struct Requirements {
    max_hp: Option<f64>,
    max_mp: Option<f64>,
    ampr: Option<f64>,
    crit: Option<f64>,
    aspd: Option<f64>,
}
impl Requirements {
    fn new(value: &Value) -> Self {
        let read = |key| value.get(key).and_then(Value::as_f64);
        Self {
            max_hp: read("maxHp"),
            max_mp: read("maxMp"),
            ampr: read("amprBeforeDual"),
            crit: read("normalAttackCrit"),
            aspd: read("aspd").map(|v| {
                if v > 1000.0 && v <= 10000.0 {
                    1000.0 + 180.0 * ((v - 1000.0) / 180.0).floor()
                } else {
                    v
                }
            }),
        }
    }
}
impl Requirements {
    fn shortfall(&self, values: [f64; 5]) -> f64 {
        [self.max_hp, self.max_mp, self.ampr, self.crit, self.aspd]
            .into_iter()
            .zip(values)
            .map(|(minimum, value)| match minimum {
                None => 0.0,
                Some(minimum) if value >= minimum => 0.0,
                Some(minimum) if value.is_finite() => (minimum - value) / minimum.abs().max(1.0),
                Some(_) => f64::INFINITY,
            })
            .sum()
    }

    fn accepts_value(&self, index: usize, value: f64) -> bool {
        [self.max_hp, self.max_mp, self.ampr, self.crit, self.aspd][index]
            .is_none_or(|minimum| value >= minimum)
    }
    #[cfg(test)]
    fn accepts(&self, values: [i64; 5]) -> bool {
        [self.max_hp, self.max_mp, self.ampr, self.crit, self.aspd]
            .into_iter()
            .zip(values)
            .all(|(minimum, value)| minimum.is_none_or(|v| value as f64 >= v))
    }
}
#[cfg(test)]
fn feasible(summary: &CrystaOptimizationNativeSummary, requirements: &Requirements) -> bool {
    requirements.accepts([
        summary.final_max_hp,
        summary.final_max_mp,
        summary.ampr_before_dual,
        summary.normal_attack_crit,
        summary.final_aspd,
    ])
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

fn selection_evaluation_stats(problem: &NativeProblem, selected: &[usize; GROUP_COUNT]) -> Stats {
    problem
        .groups
        .iter()
        .zip(selected)
        .fold(Stats::new(), |stats, (group, index)| {
            add_stats(stats, group.packages[*index].evaluation_stats())
        })
}

fn box_stats(trees: &TreeArena, clusters: &[NodeId; GROUP_COUNT]) -> Stats {
    let mut stats = clusters
        .iter()
        .skip(1)
        .fold(trees[clusters[0]].envelope.clone(), |stats, node| {
            add_stats(stats, &trees[*node].envelope)
        });
    if let Some(joint) = &trees.joint {
        joint.tighten_offense(clusters, &mut stats);
    }
    stats
}

fn box_combinations(trees: &TreeArena, clusters: &[NodeId; GROUP_COUNT], limit: usize) -> usize {
    clusters.iter().fold(1_usize, |total, node| {
        total
            .saturating_mul(trees[*node].size)
            .min(limit.saturating_add(1))
    })
}

/// Certify individually impossible goals before the damage search. Each queue
/// covers the unresolved space for one utility, not a fabricated joint build.
/// Exhausting the work budget means unknown; it must never delete candidates.
fn individual_utilities_possible(
    problem: &NativeProblem,
    clusters: &[NodeId; GROUP_COUNT],
    requirements: &Requirements,
    state: &mut SearchState,
) -> Result<bool, String> {
    if let Some(supply) = &problem.trees.supply {
        if !supply.legacy_safe() {
            state.evaluations += 1;
            return Ok(
                (0..5).all(|i| requirements.accepts_value(i, supply.metric(clusters, i + 1)))
            );
        }
    }
    let root_values = utility_values(&problem.base_context, &box_stats(&problem.trees, clusters))?;
    state.evaluations += 1;
    let minima = [
        requirements.max_hp,
        requirements.max_mp,
        requirements.ampr,
        requirements.crit,
        requirements.aspd,
    ];
    for (index, minimum) in minima.into_iter().enumerate() {
        let Some(minimum) = minimum else {
            continue;
        };
        if root_values[index] < minimum {
            return Ok(false);
        }
        // An actual feasible incumbent already witnesses all individual goals.
        if state.best_selected.is_some() {
            continue;
        }
        let mut queue = BinaryHeap::new();
        queue.push(WorkItem {
            upper: root_values[index],
            clusters: *clusters,
        });
        let mut witnessed = false;
        for _ in 0..256 {
            let Some(node) = queue.pop() else {
                return Ok(false);
            };
            if node.upper < minimum {
                return Ok(false);
            }
            if box_combinations(&problem.trees, &node.clusters, 1) == 1 {
                witnessed = true;
                break;
            }
            for child in ChildBoxes::new(&problem.trees, &node.clusters) {
                let values =
                    utility_values(&problem.base_context, &box_stats(&problem.trees, &child))?;
                state.evaluations += 1;
                if values[index] >= minimum {
                    queue.push(WorkItem {
                        upper: values[index],
                        clusters: child,
                    });
                }
            }
        }
        if !witnessed && queue.is_empty() {
            return Ok(false);
        }
    }
    Ok(true)
}

fn split_indices(trees: &TreeArena, clusters: &[NodeId; GROUP_COUNT]) -> [Option<usize>; 2] {
    split_indices_with_threshold(trees, clusters, None)
}

// Ordering only: translate the current relative damage gap into the existing
// heuristic's scale. The factor schedules work; it is not a damage formula,
// an option bonus, or a safe bound. Nonfinite/unavailable gaps keep v15 order.
fn split_score_threshold(
    trees: &TreeArena,
    clusters: &[NodeId; GROUP_COUNT],
    upper: f64,
    best: f64,
) -> Option<f64> {
    if !best.is_finite() || !upper.is_finite() || upper <= 0.0 || upper <= best {
        return None;
    }
    let score_sum: f64 = clusters.iter().map(|id| trees[*id].split_score).sum();
    let threshold = score_sum * ((upper - best) / upper) * 2.0;
    (threshold.is_finite() && threshold > EPSILON).then_some(threshold)
}

#[derive(Clone, Copy)]
struct SplitAxisPriority {
    group: usize,
    reduction: f64,
    balanced_reduction: f64,
    isolated_reduction: f64,
    size: usize,
}

fn split_indices_with_threshold(
    trees: &TreeArena,
    clusters: &[NodeId; GROUP_COUNT],
    threshold: Option<f64>,
) -> [Option<usize>; 2] {
    let mut available: [Option<SplitAxisPriority>; GROUP_COUNT] = std::array::from_fn(|index| {
        let node = &trees[clusters[index]];
        let (Some(_), Some(_)) = (node.left, node.right) else {
            return None;
        };
        let priority = threshold.map_or(node.split_slack, |threshold| {
            // A large gain in a tiny child must not stand in for the sibling's
            // remaining work. Sum the capped gains over both children's
            // candidate counts. The cap avoids rewarding surplus reduction.
            let weighted_gain = if threshold >= node.split_slack {
                node.split_total_gain
            } else if threshold <= node.split_worst_gain {
                threshold * node.size as f64
            } else {
                threshold * node.split_best_size as f64
                    + node.split_worst_gain * (node.size - node.split_best_size) as f64
            };
            if weighted_gain.is_finite() {
                weighted_gain
            } else {
                node.split_slack
            }
        });
        Some(SplitAxisPriority {
            group: index,
            reduction: priority,
            balanced_reduction: threshold.map_or(0.0, |_| node.split_worst_gain),
            isolated_reduction: node.split_slack,
            size: node.size,
        })
    });
    available.sort_by(|left, right| match (left, right) {
        (Some(left), Some(right)) => right
            .reduction
            .total_cmp(&left.reduction)
            .then_with(|| right.balanced_reduction.total_cmp(&left.balanced_reduction))
            .then_with(|| right.isolated_reduction.total_cmp(&left.isolated_reduction))
            .then_with(|| right.size.cmp(&left.size))
            .then_with(|| left.group.cmp(&right.group)),
        (Some(_), None) => Ordering::Less,
        (None, Some(_)) => Ordering::Greater,
        (None, None) => Ordering::Equal,
    });
    [
        available[0].map(|entry| entry.group),
        available[1].map(|entry| entry.group),
    ]
}

/// At most two binary dimensions: produce LL, LR, RL, RR without temporary
/// vectors or cloning parent handles that would immediately be replaced.
struct ChildBoxes<'a> {
    trees: &'a TreeArena,
    clusters: &'a [NodeId; GROUP_COUNT],
    splits: [Option<usize>; 2],
    next: usize,
}

impl<'a> ChildBoxes<'a> {
    fn new(trees: &'a TreeArena, clusters: &'a [NodeId; GROUP_COUNT]) -> Self {
        Self {
            clusters,
            trees,
            splits: split_indices(trees, clusters),
            next: 0,
        }
    }

    fn with_score_gap(
        trees: &'a TreeArena,
        clusters: &'a [NodeId; GROUP_COUNT],
        upper: f64,
        best: f64,
    ) -> Self {
        Self {
            clusters,
            trees,
            splits: split_indices_with_threshold(
                trees,
                clusters,
                split_score_threshold(trees, clusters, upper, best),
            ),
            next: 0,
        }
    }

    fn count_total(&self) -> usize {
        match self.splits {
            [None, _] => 0,
            [Some(_), None] => 2,
            [Some(_), Some(_)] => 4,
        }
    }
}

impl Iterator for ChildBoxes<'_> {
    type Item = [NodeId; GROUP_COUNT];

    fn next(&mut self) -> Option<Self::Item> {
        if self.next >= self.count_total() {
            return None;
        }
        let ordinal = self.next;
        self.next += 1;
        let first = self.splits[0].expect("nonempty child iterator has a split");
        let second = self.splits[1];
        let first_right = ordinal / if second.is_some() { 2 } else { 1 } != 0;
        Some(std::array::from_fn(|index| {
            let node = &self.trees[self.clusters[index]];
            let selected = if index == first {
                if first_right {
                    &node.right
                } else {
                    &node.left
                }
            } else if Some(index) == second {
                if ordinal % 2 == 1 {
                    &node.right
                } else {
                    &node.left
                }
            } else {
                return self.clusters[index];
            };
            *selected
                .as_ref()
                .expect("CandidateTree branches are binary")
        }))
    }

    fn size_hint(&self) -> (usize, Option<usize>) {
        let remaining = self.count_total() - self.next;
        (remaining, Some(remaining))
    }
}

impl ExactSizeIterator for ChildBoxes<'_> {}

fn better(score: f64, id: &str, best_score: f64, best_id: &str) -> bool {
    score > best_score + EPSILON || ((score - best_score).abs() <= EPSILON && id < best_id)
}

fn consider(
    problem: &NativeProblem,
    requirements: &Requirements,
    state: &mut SearchState,
    selected: &[usize; GROUP_COUNT],
    stats: &Stats,
) -> Result<(), String> {
    consider_with_extra(problem, requirements, state, selected, stats, None)
}

fn consider_with_extra(
    problem: &NativeProblem,
    requirements: &Requirements,
    state: &mut SearchState,
    selected: &[usize; GROUP_COUNT],
    stats: &Stats,
    extra: Option<&Stats>,
) -> Result<(), String> {
    state.evaluations += 1;
    let accepts = |i, v| requirements.accepts_value(i, v);
    let Some(summary) = (match extra {
        Some(right) => {
            evaluate_utility_feasible_score_from_sum(&problem.base_context, stats, right, accepts)
        }
        None => evaluate_feasible_summary(&problem.base_context, stats, accepts),
    })?
    else {
        return Ok(());
    };
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

fn visit_cluster_indices(trees: &TreeArena, id: NodeId, emit: &mut impl FnMut(usize)) {
    let node = &trees[id];
    if let Some(index) = node.package {
        emit(index);
        return;
    }
    if let Some(left) = &node.left {
        visit_cluster_indices(trees, *left, emit);
    }
    if let Some(right) = &node.right {
        visit_cluster_indices(trees, *right, emit);
    }
}

#[cfg(test)]
fn cluster_indices(trees: &TreeArena, id: NodeId, output: &mut Vec<usize>) {
    visit_cluster_indices(trees, id, &mut |index| output.push(index));
}

#[cfg(test)]
fn box_candidate_indices(
    trees: &TreeArena,
    clusters: &[NodeId; GROUP_COUNT],
) -> [Vec<usize>; GROUP_COUNT] {
    std::array::from_fn(|group| {
        let mut indices = Vec::with_capacity(trees[clusters[group]].size);
        cluster_indices(trees, clusters[group], &mut indices);
        indices
    })
}

// For positive sizes, sum(sizes) <= product(sizes) + GROUP_COUNT - 1.
// A small box therefore needs at most 67 indices, including a 64x1x1x1 box.
struct SmallBoxCandidates {
    indices: [usize; SMALL_BOX_LIMIT + GROUP_COUNT - 1],
    offsets: [usize; GROUP_COUNT + 1],
}
impl SmallBoxCandidates {
    fn new(trees: &TreeArena, clusters: &[NodeId; GROUP_COUNT]) -> Self {
        debug_assert!(box_combinations(trees, clusters, SMALL_BOX_LIMIT) <= SMALL_BOX_LIMIT);
        let mut result = Self {
            indices: [0; SMALL_BOX_LIMIT + GROUP_COUNT - 1],
            offsets: [0; GROUP_COUNT + 1],
        };
        let mut end = 0;
        for (group, &cluster) in clusters.iter().enumerate() {
            visit_cluster_indices(trees, cluster, &mut |index| {
                result.indices[end] = index;
                end += 1;
            });
            result.offsets[group + 1] = end;
        }
        result
    }

    fn as_slices(&self) -> [&[usize]; GROUP_COUNT] {
        std::array::from_fn(|group| &self.indices[self.offsets[group]..self.offsets[group + 1]])
    }
}

#[allow(clippy::too_many_arguments)] // Recursive complete enumeration shares its immutable search inputs.
fn enumerate_box(
    index: usize,
    candidates: &[&[usize]; GROUP_COUNT],
    problem: &NativeProblem,
    requirements: &Requirements,
    selected: &mut [usize; GROUP_COUNT],
    stats: &Stats,
    state: &mut SearchState,
    enumerated: &mut u64,
) -> Result<(), String> {
    if index == GROUP_COUNT {
        *enumerated += 1;
        return consider(problem, requirements, state, selected, stats);
    }
    for &package_index in candidates[index] {
        selected[index] = package_index;
        if index + 1 == GROUP_COUNT {
            *enumerated += 1;
            consider_with_extra(
                problem,
                requirements,
                state,
                selected,
                stats,
                Some(problem.groups[index].packages[package_index].evaluation_stats()),
            )?;
            continue;
        }
        let next = add_stats(
            stats.clone(),
            problem.groups[index].packages[package_index].evaluation_stats(),
        );
        enumerate_box(
            index + 1,
            candidates,
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
        let mut candidates = group
            .packages
            .iter()
            .enumerate()
            .map(|(index, package)| (heuristic_score(&package.stat_delta, mode), index))
            .collect::<Vec<_>>();
        candidates.sort_by(|(left, li), (right, ri)| {
            right
                .total_cmp(left)
                .then_with(|| group.packages[*li].id.cmp(&group.packages[*ri].id))
        });
        for (_, index) in candidates.into_iter().take(each) {
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

fn seed_shortfall(
    problem: &NativeProblem,
    requirements: &Requirements,
    state: &mut SearchState,
    selected: &[usize; GROUP_COUNT],
) -> Result<f64, String> {
    state.evaluations += 1;
    let stats = selection_evaluation_stats(problem, selected);
    let values = utility_values(&problem.base_context, &stats)?;
    if (0..5).all(|i| requirements.accepts_value(i, values[i])) {
        consider(problem, requirements, state, selected, &stats)?;
    }
    Ok(requirements.shortfall(values))
}

// Rank real complete combinations by missing goals until a feasible seed exists.
// The limited repair pool never removes candidates from the exact search.
fn repair_infeasible_seed(
    problem: &NativeProblem,
    requirements: &Requirements,
    state: &mut SearchState,
) -> Result<(), String> {
    if state.best_selected.is_some() {
        return Ok(());
    }
    for mut selected in initial_selections(problem) {
        let mut deficit = seed_shortfall(problem, requirements, state, &selected)?;
        for _ in 0..HEURISTIC_PASSES {
            let before = deficit;
            let mut pools: [Vec<usize>; GROUP_COUNT] = std::array::from_fn(|_| Vec::new());
            for (g, group) in problem.groups.iter().enumerate() {
                let mut ranked = Vec::new();
                for index in heuristic_candidate_pool(group, selected[g]) {
                    let mut trial = selected;
                    trial[g] = index;
                    let missing = seed_shortfall(problem, requirements, state, &trial)?;
                    if state.best_selected.is_some() {
                        return Ok(());
                    }
                    ranked.push((missing, index));
                }
                ranked.sort_by(|(a, ai), (b, bi)| {
                    a.total_cmp(b)
                        .then_with(|| group.packages[*ai].id.cmp(&group.packages[*bi].id))
                });
                if ranked[0].0 < deficit {
                    deficit = ranked[0].0;
                    selected[g] = ranked[0].1;
                }
                pools[g] = ranked
                    .into_iter()
                    .take(PAIR_SEED_RANK_LIMIT)
                    .map(|(_, i)| i)
                    .collect();
            }
            let baseline = selected;
            for left in 0..GROUP_COUNT {
                for right in left + 1..GROUP_COUNT {
                    for a in &pools[left] {
                        for b in &pools[right] {
                            let mut trial = baseline;
                            trial[left] = *a;
                            trial[right] = *b;
                            let missing = seed_shortfall(problem, requirements, state, &trial)?;
                            if state.best_selected.is_some() {
                                return Ok(());
                            }
                            if missing < deficit {
                                deficit = missing;
                                selected = trial;
                            }
                        }
                    }
                }
            }
            if deficit >= before {
                break;
            }
        }
    }
    Ok(())
}

/// A single-group improvement can be blocked by a complementary swap. Only
/// actual feasible completions raise the lower bound; all exact candidates stay.
fn improve_pair_seed(
    problem: &NativeProblem,
    requirements: &Requirements,
    state: &mut SearchState,
) -> Result<(), String> {
    if state.best_selected.is_none() {
        return Ok(());
    }
    if problem
        .groups
        .iter()
        .filter(|g| g.packages.len() > 1)
        .count()
        < 2
        || box_combinations(&problem.trees, &problem.trees.roots, SMALL_BOX_LIMIT)
            <= SMALL_BOX_LIMIT
    {
        return Ok(());
    }
    for _ in 0..HEURISTIC_PASSES {
        let baseline = state.best_selected.unwrap();
        let before = state.best_score;
        let mut pools: [Vec<usize>; GROUP_COUNT] = std::array::from_fn(|_| Vec::new());
        for (g, group) in problem.groups.iter().enumerate() {
            let mut ranked = Vec::new();
            for index in 0..group.packages.len() {
                let mut selected = baseline;
                selected[g] = index;
                let mut trial = SearchState {
                    best_score: f64::NEG_INFINITY,
                    ..SearchState::default()
                };
                consider(
                    problem,
                    requirements,
                    &mut trial,
                    &selected,
                    &selection_evaluation_stats(problem, &selected),
                )?;
                state.evaluations += trial.evaluations;
                if trial.best_selected.is_some() {
                    ranked.push((trial.best_score, index));
                }
            }
            ranked.sort_by(|(a, ai), (b, bi)| {
                b.total_cmp(a)
                    .then_with(|| group.packages[*ai].id.cmp(&group.packages[*bi].id))
            });
            pools[g].push(baseline[g]);
            for (_, index) in ranked.into_iter().take(PAIR_SEED_RANK_LIMIT) {
                if !pools[g].contains(&index) {
                    pools[g].push(index);
                }
            }
            // Keep utility/damage representatives even when a single swap fails.
            for mode in ["damage", "utility"] {
                let mut indices = group
                    .packages
                    .iter()
                    .enumerate()
                    .map(|(index, package)| (heuristic_score(&package.stat_delta, mode), index))
                    .collect::<Vec<_>>();
                indices.sort_by(|(a, ai), (b, bi)| {
                    b.total_cmp(a)
                        .then_with(|| group.packages[*ai].id.cmp(&group.packages[*bi].id))
                });
                for (_, index) in indices.into_iter().take(PAIR_SEED_RANK_LIMIT / 2) {
                    if !pools[g].contains(&index) {
                        pools[g].push(index);
                    }
                }
            }
        }
        for left in 0..GROUP_COUNT {
            for right in left + 1..GROUP_COUNT {
                if problem.groups[left].packages.len() == 1
                    || problem.groups[right].packages.len() == 1
                {
                    continue;
                }
                let baseline = state.best_selected.unwrap();
                for &a in &pools[left] {
                    for &b in &pools[right] {
                        let mut selected = baseline;
                        selected[left] = a;
                        selected[right] = b;
                        consider(
                            problem,
                            requirements,
                            state,
                            &selected,
                            &selection_evaluation_stats(problem, &selected),
                        )?;
                    }
                }
            }
        }
        if state.best_score <= before + EPSILON {
            break;
        }
    }
    Ok(())
}

pub fn solve_exact(problem: &NativeProblem) -> Result<NativeSolveResult, String> {
    if !problem.base_context.is_object()
        || problem.groups.len() != GROUP_COUNT
        || problem.groups.iter().any(|group| group.packages.is_empty())
    {
        return Err(
            "CrystaOptimization native solver requires four nonempty prepared groups".to_string(),
        );
    }
    let started = Instant::now();
    let mut prepared_problem = problem.clone();
    prepared_problem.prepare_evaluation_stats();
    let clusters = prepared_problem.prepare_trees()?;
    let problem = &prepared_problem;
    let requirements = &Requirements::new(
        problem
            .scenario_snapshot
            .get("requirements")
            .unwrap_or(&Value::Null),
    );
    let mut state = SearchState {
        best_score: f64::NEG_INFINITY,
        ..SearchState::default()
    };
    let mut visited = 0_u64;
    let mut pruned_by_bound = 0_u64;
    let mut pruned_by_constraint = 0_u64;
    let mut enumerated = 0_u64;

    for selected in initial_selections(problem) {
        let stats = selection_evaluation_stats(problem, &selected);
        consider(problem, requirements, &mut state, &selected, &stats)?;
    }
    repair_infeasible_seed(problem, requirements, &mut state)?;
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
                    let stats = selection_evaluation_stats(problem, &trial);
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

    improve_pair_seed(problem, requirements, &mut state)?;
    state.evaluations += 1;
    let root = evaluate_box(problem, &clusters, None)?.expect("unfiltered box");
    if !individual_utilities_possible(problem, &clusters, requirements, &mut state)? {
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
        if !problem.trees.joint_utilities_possible(&node.clusters) {
            pruned_by_constraint += 1;
            continue;
        }
        if box_combinations(&problem.trees, &node.clusters, SMALL_BOX_LIMIT) <= SMALL_BOX_LIMIT {
            enumerate_box(
                0,
                &SmallBoxCandidates::new(&problem.trees, &node.clusters).as_slices(),
                problem,
                requirements,
                &mut [0; GROUP_COUNT],
                &Stats::new(),
                &mut state,
                &mut enumerated,
            )?;
            continue;
        }
        let child_boxes = ChildBoxes::with_score_gap(
            &problem.trees,
            &node.clusters,
            node.upper,
            state.best_score,
        );
        if child_boxes.len() == 0 {
            continue;
        }
        for child_clusters in child_boxes {
            state.evaluations += 1;
            let Some(bound) = evaluate_box(problem, &child_clusters, Some(requirements))? else {
                pruned_by_constraint += 1;
                continue;
            };
            if bound.optimization_damage_factor < state.best_score - EPSILON {
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

/// Resumable search state, including frontier, incumbent and counters.
/// Parallel workers execute bounded batches; this session owns checkpoint state.
pub struct NativeSearchSession {
    pool: Option<NodePool>,
    batch_nodes: Arc<Vec<WorkItem>>,
    batch_outcomes: Vec<Option<NodeOutcome>>,
    problem: NativeProblem,
    requirements: Requirements,
    heap: WorkHeap,
    state: SearchState,
    visited: u64,
    pruned_by_bound: u64,
    pruned_by_constraint: u64,
    enumerated: u64,
    terminal_invalid_upper: Option<f64>,
    /// Search time accumulated while this session is actually executing.
    /// A resumable session can sit in the registry for minutes; wall-clock
    /// time between slices must never be reported as solver elapsed time.
    elapsed: Duration,
}

impl NativeSearchSession {
    pub fn new(mut problem: NativeProblem) -> Result<Self, String> {
        if !problem.base_context.is_object()
            || problem.groups.len() != GROUP_COUNT
            || problem.groups.iter().any(|group| group.packages.is_empty())
        {
            return Err(
                "CrystaOptimization native solver requires four nonempty prepared groups"
                    .to_string(),
            );
        }
        let started = Instant::now();
        problem.prepare_evaluation_stats();
        let clusters = problem.prepare_trees()?;
        let requirements = Requirements::new(
            problem
                .scenario_snapshot
                .get("requirements")
                .unwrap_or(&Value::Null),
        );
        let mut state = SearchState {
            best_score: f64::NEG_INFINITY,
            ..SearchState::default()
        };
        for selected in initial_selections(&problem) {
            let stats = selection_evaluation_stats(&problem, &selected);
            consider(&problem, &requirements, &mut state, &selected, &stats)?;
        }
        repair_infeasible_seed(&problem, &requirements, &mut state)?;
        if let Some(mut selected) = state.best_selected {
            for _ in 0..HEURISTIC_PASSES {
                let mut changed = false;
                for group_index in 0..GROUP_COUNT {
                    let baseline = selected;
                    let before_id = state.best_id.clone();
                    for package_index in heuristic_candidate_pool(
                        &problem.groups[group_index],
                        baseline[group_index],
                    ) {
                        let mut trial = baseline;
                        trial[group_index] = package_index;
                        consider(
                            &problem,
                            &requirements,
                            &mut state,
                            &trial,
                            &selection_evaluation_stats(&problem, &trial),
                        )?;
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
        improve_pair_seed(&problem, &requirements, &mut state)?;
        state.evaluations += 1;
        let root = evaluate_box(&problem, &clusters, None)?.expect("unfiltered box");
        let mut heap = WorkHeap::new();
        let terminal_invalid_upper =
            if individual_utilities_possible(&problem, &clusters, &requirements, &mut state)? {
                heap.push(WorkItem {
                    upper: root.optimization_damage_factor,
                    clusters,
                });
                None
            } else {
                Some(root.optimization_damage_factor)
            };
        Ok(Self {
            pool: None,
            batch_nodes: Arc::new(Vec::new()),
            batch_outcomes: Vec::new(),
            problem,
            requirements,
            heap,
            state,
            visited: 0,
            pruned_by_bound: 0,
            pruned_by_constraint: 0,
            enumerated: 0,
            terminal_invalid_upper,
            elapsed: started.elapsed(),
        })
    }

    pub fn is_complete(&self) -> bool {
        self.terminal_invalid_upper.is_some() || self.heap.is_empty()
    }
    pub fn ready_work_count(&self) -> usize {
        self.heap.len()
    }

    /// A checkpoint is only taken between nodes, so the frontier contains all
    /// unresolved work and has no hidden active item.
    pub fn checkpoint(&self) -> Result<NativeSearchCheckpoint, String> {
        let frontier = self
            .heap
            .iter()
            .map(|item| NativeCheckpointWorkItem {
                upper: item.upper,
                paths: std::array::from_fn(|index| {
                    self.problem.trees[item.clusters[index]].path.clone()
                }),
            })
            .collect::<Vec<_>>();
        Self::audit_frontier(&frontier)?;
        Ok(NativeSearchCheckpoint {
            schema: "toram.crysta-native-search-checkpoint.v21".to_string(),
            problem: self.problem.clone(),
            state: self.state.clone(),
            frontier,
            visited: self.visited,
            pruned_by_bound: self.pruned_by_bound,
            pruned_by_constraint: self.pruned_by_constraint,
            enumerated: self.enumerated,
            terminal_invalid_upper: self.terminal_invalid_upper,
            elapsed_ms: self.elapsed.as_millis(),
        })
    }

    pub fn from_checkpoint(checkpoint: NativeSearchCheckpoint) -> Result<Self, String> {
        // Bound-policy changes invalidate persisted frontiers and cache entries.
        if checkpoint.schema != "toram.crysta-native-search-checkpoint.v21" {
            return Err("CrystaOptimization native checkpoint schema is invalid".to_string());
        }
        Self::audit_frontier(&checkpoint.frontier)?;
        let mut session = Self::new(checkpoint.problem.clone())?;
        let roots = session.heap.peek().map(|item| item.clusters);
        let mut heap = WorkHeap::new();
        if let Some(roots) = roots {
            for item in checkpoint.frontier {
                let resolved: [Option<NodeId>; GROUP_COUNT] = std::array::from_fn(|index| {
                    find_tree_node(&session.problem.trees, roots[index], &item.paths[index])
                });
                let clusters: [NodeId; GROUP_COUNT] = resolved
                    .into_iter()
                    .collect::<Option<Vec<_>>>()
                    .ok_or_else(|| {
                        "CrystaOptimization native checkpoint references an unknown frontier path"
                            .to_string()
                    })?
                    .try_into()
                    .map_err(|_| {
                        "CrystaOptimization native checkpoint requires four frontier paths"
                            .to_string()
                    })?;
                heap.push(WorkItem {
                    upper: item.upper,
                    clusters,
                });
            }
        } else if !checkpoint.frontier.is_empty() {
            return Err(
                "CrystaOptimization native checkpoint has frontier without searchable roots"
                    .to_string(),
            );
        }
        session.heap = heap;
        session.state = checkpoint.state;
        session.visited = checkpoint.visited;
        session.pruned_by_bound = checkpoint.pruned_by_bound;
        session.pruned_by_constraint = checkpoint.pruned_by_constraint;
        session.enumerated = checkpoint.enumerated;
        session.terminal_invalid_upper = checkpoint.terminal_invalid_upper;
        session.elapsed = Duration::from_millis(checkpoint.elapsed_ms.min(u64::MAX as u128) as u64);
        Ok(session)
    }

    fn audit_frontier(frontier: &[NativeCheckpointWorkItem]) -> Result<(), String> {
        let mut seen = HashSet::new();
        for item in frontier {
            if item.upper.is_nan()
                || item.upper == f64::NEG_INFINITY
                || !seen.insert(item.paths.join("|"))
            {
                return Err(
                    "CrystaOptimization native checkpoint frontier is incomplete or duplicated"
                        .to_string(),
                );
            }
        }
        Ok(())
    }

    /// Process at most `node_budget` ready nodes.  A leaf box has at most 64
    /// completions by contract, so each yield happens after a complete safe box.
    pub fn run_slice(&mut self, node_budget: usize) -> Result<NativeSolveResult, String> {
        if self.terminal_invalid_upper.is_some() {
            return Ok(self.result());
        }
        let started = Instant::now();
        let outcome = (|| -> Result<(), String> {
            let mut processed = 0usize;
            while processed < node_budget.max(1) {
                let Some(node) = self.heap.pop() else {
                    break;
                };
                processed += 1;
                self.visited += 1;
                if node.upper < self.state.best_score - EPSILON {
                    self.pruned_by_bound += 1;
                    continue;
                }
                if !self.problem.trees.joint_utilities_possible(&node.clusters) {
                    self.pruned_by_constraint += 1;
                    continue;
                }
                if box_combinations(&self.problem.trees, &node.clusters, SMALL_BOX_LIMIT)
                    <= SMALL_BOX_LIMIT
                {
                    enumerate_box(
                        0,
                        &SmallBoxCandidates::new(&self.problem.trees, &node.clusters).as_slices(),
                        &self.problem,
                        &self.requirements,
                        &mut [0; GROUP_COUNT],
                        &Stats::new(),
                        &mut self.state,
                        &mut self.enumerated,
                    )?;
                    continue;
                }
                let child_boxes = ChildBoxes::with_score_gap(
                    &self.problem.trees,
                    &node.clusters,
                    node.upper,
                    self.state.best_score,
                );
                if child_boxes.len() == 0 {
                    continue;
                }
                for child_clusters in child_boxes {
                    self.state.evaluations += 1;
                    let Some(bound) =
                        evaluate_box(&self.problem, &child_clusters, Some(&self.requirements))?
                    else {
                        self.pruned_by_constraint += 1;
                        continue;
                    };
                    if bound.optimization_damage_factor < self.state.best_score - EPSILON {
                        self.pruned_by_bound += 1;
                    } else {
                        self.heap.push(WorkItem {
                            upper: bound.optimization_damage_factor,
                            clusters: child_clusters,
                        });
                    }
                }
            }
            Ok(())
        })();
        self.elapsed += started.elapsed();
        outcome?;
        Ok(self.result())
    }

    /// Drain a bounded batch from the persisted frontier with shared immutable
    /// trees and a shared incumbent.  The batch boundary is still a checkpoint
    /// boundary: every child is merged into `heap` before this method returns.
    pub fn run_parallel_slice(
        &mut self,
        node_budget: usize,
        requested_threads: usize,
    ) -> Result<NativeSolveResult, String> {
        self.run_parallel_slice_with_control(node_budget, requested_threads, None, None)
    }

    /// The runtime coordinator supplies cancellation and deadline controls.
    /// A stopped node is returned unchanged to the persisted frontier so a
    /// deadline never loses its safe upper bound.  Cancellation discards that
    /// session at the command layer, but follows the same path to avoid a
    /// transient false `exact` result.
    pub fn run_parallel_slice_with_control(
        &mut self,
        node_budget: usize,
        requested_threads: usize,
        cancel: Option<&Arc<AtomicBool>>,
        deadline: Option<Instant>,
    ) -> Result<NativeSolveResult, String> {
        self.advance_parallel_slice_with_control(node_budget, requested_threads, cancel, deadline)?;
        Ok(self.result())
    }

    /// Advance the same safe batch without materializing a build snapshot.
    /// Coordinators request `snapshot` only when publishing or returning a result.
    pub fn advance_parallel_slice_with_control(
        &mut self,
        node_budget: usize,
        requested_threads: usize,
        cancel: Option<&Arc<AtomicBool>>,
        deadline: Option<Instant>,
    ) -> Result<(), String> {
        if self.terminal_invalid_upper.is_some() || self.heap.is_empty() {
            return Ok(());
        }
        let started = Instant::now();
        let workers = requested_threads.max(1);
        let batch_size = self.heap.len().min(node_budget.max(workers));
        let nodes = Arc::make_mut(&mut self.batch_nodes);
        nodes.clear();
        nodes.extend((0..batch_size).filter_map(|_| self.heap.pop()));
        let incumbent = Arc::new(SharedIncumbent {
            score_bits: AtomicU64::new(self.state.best_score.to_bits()),
            record: Mutex::new(self.state.clone()),
        });
        let counters = Arc::new(ParallelCounters {
            evaluations: AtomicU64::new(0),
            visited: AtomicU64::new(0),
            pruned_by_bound: AtomicU64::new(0),
            pruned_by_constraint: AtomicU64::new(0),
            enumerated: AtomicU64::new(0),
            splits: AtomicU64::new(0),
            steals: AtomicU64::new(0),
            work_busy_micros: AtomicU64::new(0),
            longest_work_item_micros: AtomicU64::new(0),
        });
        if self
            .pool
            .as_ref()
            .is_none_or(|pool| pool.workers.len() != workers)
        {
            // Construct before dispatch; on any pool failure the parent frontier survives.
            match NodePool::new(&self.problem, self.requirements, workers) {
                Ok(pool) => self.pool = Some(pool),
                Err(error) => {
                    self.heap.extend(nodes.drain(..));
                    return Err(error);
                }
            }
        }
        if let Err(error) = self.pool.as_mut().unwrap().run(
            &self.batch_nodes,
            &mut self.batch_outcomes,
            &incumbent,
            &counters,
            cancel,
            deadline,
        ) {
            // Join outstanding jobs before reclaiming shared input on failure.
            self.pool = None;
            self.heap
                .extend(Arc::make_mut(&mut self.batch_nodes).drain(..));
            self.batch_outcomes.clear();
            return Err(error);
        }
        let nodes = Arc::get_mut(&mut self.batch_nodes).expect("completed batch releases input");
        if let Some(error) = self
            .batch_outcomes
            .iter()
            .find_map(|result| result.as_ref().and_then(|outcome| outcome.as_ref().err()))
        {
            let error = error.clone();
            self.heap.extend(nodes.drain(..));
            self.batch_outcomes.clear();
            return Err(error);
        }
        let outcome = (|| -> Result<(), String> {
            for (node, outcome) in nodes.drain(..).zip(self.batch_outcomes.drain(..)) {
                match outcome.expect("validated worker result")? {
                    Some(children) => self.heap.extend(
                        self.pool.as_ref().unwrap().buffers[children.buffer].children
                            [children.range]
                            .iter()
                            .copied(),
                    ),
                    None => self.heap.push(node),
                }
            }
            let state = incumbent
                .record
                .lock()
                .map_err(|_| "CrystaOptimization incumbent mutex was poisoned".to_string())?
                .clone();
            self.state = state;
            self.state.evaluations += counters.evaluations.load(AtomicOrdering::Relaxed);
            self.visited += counters.visited.load(AtomicOrdering::Relaxed);
            self.pruned_by_bound += counters.pruned_by_bound.load(AtomicOrdering::Relaxed);
            self.pruned_by_constraint +=
                counters.pruned_by_constraint.load(AtomicOrdering::Relaxed);
            self.enumerated += counters.enumerated.load(AtomicOrdering::Relaxed);
            Ok(())
        })();
        self.elapsed += started.elapsed();
        outcome
    }

    pub fn snapshot(&self) -> NativeSolveResult {
        self.result()
    }

    fn result(&self) -> NativeSolveResult {
        let best_build = self
            .state
            .best_selected
            .as_ref()
            .map(|selected| NativeBuild {
                id: self.state.best_id.clone(),
                package_ids: selected
                    .iter()
                    .enumerate()
                    .map(|(group, index)| self.problem.groups[group].packages[*index].id.clone())
                    .collect(),
                stat_delta: selection_stats(&self.problem, selected),
            });
        let upper = self
            .heap
            .peek()
            .map(|node| node.upper)
            .or(self.terminal_invalid_upper)
            .or_else(|| best_build.as_ref().map(|_| self.state.best_score))
            .map(|upper| {
                if best_build.is_some() {
                    upper.max(self.state.best_score)
                } else {
                    upper
                }
            });
        let exact =
            self.terminal_invalid_upper.is_none() && self.heap.is_empty() && best_build.is_some();
        NativeSolveResult {
            status: if exact {
                "exact".to_string()
            } else if self.terminal_invalid_upper.is_some() || self.heap.is_empty() {
                "invalid".to_string()
            } else if best_build.is_some() {
                "bounded".to_string()
            } else {
                "no-incumbent-yet".to_string()
            },
            exact,
            score: best_build.as_ref().map(|_| self.state.best_score),
            best_build,
            upper_bound: upper,
            elapsed_ms: self.elapsed.as_millis(),
            visited_nodes: self.visited,
            evaluations: self.state.evaluations,
            pruned_by_bound: self.pruned_by_bound,
            pruned_by_constraint: self.pruned_by_constraint,
            enumerated_completions: self.enumerated,
        }
    }
}

fn find_tree_node(trees: &TreeArena, root: NodeId, path: &str) -> Option<NodeId> {
    let suffix = path.strip_prefix(&trees[root].path)?;
    let mut id = root;
    for direction in suffix.bytes() {
        id = match direction {
            b'0' => trees[id].left?,
            b'1' => trees[id].right?,
            _ => return None,
        };
    }
    Some(id)
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
    requirements: &Requirements,
    incumbent: &SharedIncumbent,
    counters: &mut impl SearchCounters,
    selected: &[usize; GROUP_COUNT],
    stats: &Stats,
) -> Result<(), String> {
    consider_parallel_with_extra(
        problem,
        requirements,
        incumbent,
        counters,
        selected,
        stats,
        None,
    )
}

fn consider_parallel_with_extra(
    problem: &NativeProblem,
    requirements: &Requirements,
    incumbent: &SharedIncumbent,
    counters: &mut impl SearchCounters,
    selected: &[usize; GROUP_COUNT],
    stats: &Stats,
    extra: Option<&Stats>,
) -> Result<(), String> {
    counters.count_evaluations();
    let accepts = |i, v| requirements.accepts_value(i, v);
    let Some(summary) = (match extra {
        Some(right) => {
            evaluate_utility_feasible_score_from_sum(&problem.base_context, stats, right, accepts)
        }
        None => evaluate_feasible_summary(&problem.base_context, stats, accepts),
    })?
    else {
        return Ok(());
    };
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
        .map_err(|_| "CrystaOptimization incumbent mutex was poisoned".to_string())?;
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
fn should_stop_parallel_work(cancel: Option<&AtomicBool>, deadline: Option<Instant>) -> bool {
    cancel.is_some_and(|signal| signal.load(AtomicOrdering::Acquire))
        || deadline.is_some_and(|limit| Instant::now() >= limit)
}

#[allow(clippy::too_many_arguments)]
fn enumerate_box_parallel(
    index: usize,
    candidates: &[&[usize]; GROUP_COUNT],
    suffix: Option<&[Stats; GROUP_COUNT]>,
    problem: &NativeProblem,
    requirements: &Requirements,
    incumbent: &SharedIncumbent,
    counters: &mut impl SearchCounters,
    cancel: Option<&AtomicBool>,
    deadline: Option<Instant>,
    selected: &mut [usize; GROUP_COUNT],
    stats: &Stats,
) -> Result<bool, String> {
    if should_stop_parallel_work(cancel, deadline) {
        return Ok(false);
    }
    if index == GROUP_COUNT {
        counters.count_enumerated();
        consider_parallel(problem, requirements, incumbent, counters, selected, stats)?;
        return Ok(true);
    }
    if problem
        .trees
        .supply
        .as_ref()
        .is_none_or(SupplyBounds::legacy_safe)
        && suffix.is_some()
        && index > 0
        && candidates[index..]
            .iter()
            .map(|items| items.len())
            .product::<usize>()
            >= 4
    {
        if let Some(suffix) = suffix {
            counters.count_evaluations();
            let mut possible = true;
            evaluate_utility_feasible_score_from_sum(
                &problem.base_context,
                stats,
                &suffix[index],
                |i, v| {
                    possible = requirements.accepts_value(i, v);
                    possible && i != 4 // Stop before damage, including on success.
                },
            )?;
            if !possible {
                counters.count_pruned_by_constraint();
                return Ok(true);
            }
        }
    }
    for &package_index in candidates[index] {
        selected[index] = package_index;
        if index + 1 == GROUP_COUNT {
            if should_stop_parallel_work(cancel, deadline) {
                return Ok(false);
            }
            counters.count_enumerated();
            consider_parallel_with_extra(
                problem,
                requirements,
                incumbent,
                counters,
                selected,
                stats,
                Some(problem.groups[index].packages[package_index].evaluation_stats()),
            )?;
            continue;
        }
        let next = add_stats(
            stats.clone(),
            problem.groups[index].packages[package_index].evaluation_stats(),
        );
        if !enumerate_box_parallel(
            index + 1,
            candidates,
            suffix,
            problem,
            requirements,
            incumbent,
            counters,
            cancel,
            deadline,
            selected,
            &next,
        )? {
            return Ok(false);
        }
    }
    Ok(true)
}

/// Process one shared-frontier node.  Children are returned to the caller so
/// the parallel coordinator can put them back onto the common priority queue;
/// this is what lets an idle worker take work created by another worker.
fn should_look_ahead(trees: &TreeArena, node: &WorkItem, best: f64, depth: usize) -> bool {
    depth < LOOKAHEAD_MAX_DEPTH
        && best.is_finite()
        && node.upper <= best + best.abs() * LOOKAHEAD_RELATIVE_GAP
        && box_combinations(trees, &node.clusters, SMALL_BOX_LIMIT) > SMALL_BOX_LIMIT
}

#[cfg(test)]
fn expand_parallel_node(
    node: &WorkItem,
    problem: &NativeProblem,
    requirements: &Requirements,
    incumbent: &SharedIncumbent,
    counters: &mut impl SearchCounters,
    cancel: Option<&AtomicBool>,
    deadline: Option<Instant>,
) -> Result<Option<Vec<WorkItem>>, String> {
    let mut children = Vec::new();
    expand_parallel_node_into(
        node,
        problem,
        requirements,
        incumbent,
        counters,
        cancel,
        deadline,
        &mut children,
    )
    .map(|completed| completed.then_some(children))
}

#[allow(clippy::too_many_arguments)]
fn expand_parallel_node_into(
    node: &WorkItem,
    problem: &NativeProblem,
    requirements: &Requirements,
    incumbent: &SharedIncumbent,
    counters: &mut impl SearchCounters,
    cancel: Option<&AtomicBool>,
    deadline: Option<Instant>,
    children: &mut Vec<WorkItem>,
) -> Result<bool, String> {
    let start = children.len();
    let result = expand_parallel_node_inner(
        node,
        0,
        problem,
        requirements,
        incumbent,
        counters,
        cancel,
        deadline,
        children,
    );
    if !matches!(result, Ok(true)) {
        children.truncate(start);
    }
    result
}

#[allow(clippy::too_many_arguments)]
fn expand_parallel_node_inner(
    node: &WorkItem,
    depth: usize,
    problem: &NativeProblem,
    requirements: &Requirements,
    incumbent: &SharedIncumbent,
    counters: &mut impl SearchCounters,
    cancel: Option<&AtomicBool>,
    deadline: Option<Instant>,
    children: &mut Vec<WorkItem>,
) -> Result<bool, String> {
    if should_stop_parallel_work(cancel, deadline) {
        return Ok(false);
    }
    counters.count_visited();
    if node.upper < shared_best_score(incumbent) - EPSILON {
        counters.count_pruned_by_bound();
        return Ok(true);
    }
    let joint_possible = problem.trees.joint_utilities_possible(&node.clusters);
    counters.count_joint_probe(!joint_possible);
    if !joint_possible {
        counters.count_pruned_by_constraint();
        return Ok(true);
    }
    if box_combinations(&problem.trees, &node.clusters, SMALL_BOX_LIMIT) <= SMALL_BOX_LIMIT {
        // Scheduling heuristic only; every removal uses the ordinary safe
        // coordinate envelope. Skip the extra work on low-rejection inputs.
        let suffix: Option<[Stats; GROUP_COUNT]> = counters.utility_pressure().then(|| {
            std::array::from_fn(|start| {
                node.clusters[start..]
                    .iter()
                    .fold(Stats::new(), |sum, node| {
                        add_stats(sum, &problem.trees[*node].envelope)
                    })
            })
        });
        return enumerate_box_parallel(
            0,
            &SmallBoxCandidates::new(&problem.trees, &node.clusters).as_slices(),
            suffix.as_ref(),
            problem,
            requirements,
            incumbent,
            counters,
            cancel,
            deadline,
            &mut [0; GROUP_COUNT],
            &Stats::new(),
        );
    }
    let child_boxes = ChildBoxes::with_score_gap(
        &problem.trees,
        &node.clusters,
        node.upper,
        shared_best_score(incumbent),
    );
    if child_boxes.len() == 0 {
        return Ok(true);
    }
    counters.count_splits();
    // All recursion appends to the same reusable worker buffer.
    let mut utility_candidates: [Option<WorkItem>; 4] = std::array::from_fn(|_| None);
    let mut utility_candidate_count = 0;
    let mut constraint_rejections = 0;
    for child_clusters in child_boxes {
        if should_stop_parallel_work(cancel, deadline) {
            return Ok(false);
        }
        // Spend extra probes only where the worker observes joint rejections.
        // This ratio schedules checks, never deletes a branch by itself.
        if counters.joint_pressure() {
            let possible = problem.trees.joint_utilities_possible(&child_clusters);
            counters.count_joint_probe(!possible);
            if !possible {
                counters.count_pruned_by_constraint();
                constraint_rejections += 1;
                continue;
            }
        }
        counters.count_evaluations();
        let Some(bound) = evaluate_box(problem, &child_clusters, Some(requirements))? else {
            counters.count_pruned_by_constraint();
            constraint_rejections += 1;
            continue;
        };
        if bound.optimization_damage_factor < shared_best_score(incumbent) - EPSILON {
            counters.count_pruned_by_bound();
        } else {
            let child = WorkItem {
                upper: bound.optimization_damage_factor,
                clusters: child_clusters,
            };
            let best = shared_best_score(incumbent);
            // The relative window only chooses where to spend extra evaluation work.
            // Removal still requires each sub-box's ordinary safe bound; keep
            // all surviving sub-boxes, or requeue the original parent on stop.
            if should_look_ahead(&problem.trees, &child, best, depth) {
                if !expand_parallel_node_inner(
                    &child,
                    depth + 1,
                    problem,
                    requirements,
                    incumbent,
                    counters,
                    cancel,
                    deadline,
                    children,
                )? {
                    return Ok(false);
                }
            } else if depth == 0 && counters.utility_pressure() {
                utility_candidates[utility_candidate_count] = Some(child);
                utility_candidate_count += 1;
            } else {
                children.push(child);
            }
        }
    }
    // Sibling failures are a scheduling hint, never a deletion proof. Spend
    // one extra level only around observed constraint boundaries.
    let probe = depth == 0 && constraint_rejections >= 2 && counters.utility_pressure();
    for child in utility_candidates.into_iter().flatten() {
        if probe
            && box_combinations(&problem.trees, &child.clusters, SMALL_BOX_LIMIT) > SMALL_BOX_LIMIT
        {
            let coverage_count = ChildBoxes::new(&problem.trees, &child.clusters).len();
            let start = children.len();
            if !expand_parallel_node_inner(
                &child,
                LOOKAHEAD_MAX_DEPTH,
                problem,
                requirements,
                incumbent,
                counters,
                cancel,
                deadline,
                children,
            )? {
                return Ok(false);
            }
            // If no subspace was removed, keep the original compact box.
            if children.len() - start >= coverage_count {
                children.truncate(start);
                children.push(child);
            }
        } else {
            children.push(child);
        }
    }
    Ok(true)
}

fn create_parallel_shards(
    root: WorkItem,
    target: usize,
    problem: &NativeProblem,
    requirements: &Requirements,
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
        if box_combinations(&problem.trees, &node.clusters, SMALL_BOX_LIMIT) <= SMALL_BOX_LIMIT {
            frontier.push(node);
            break;
        }
        let child_boxes = ChildBoxes::with_score_gap(
            &problem.trees,
            &node.clusters,
            node.upper,
            state.best_score,
        );
        if child_boxes.len() == 0 {
            frontier.push(node);
            break;
        }
        for child_clusters in child_boxes {
            state.evaluations += 1;
            let Some(bound) = evaluate_box(problem, &child_clusters, Some(requirements))? else {
                continue;
            };
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

/// Run the exact CrystaOptimization tree using every thread the caller authorizes. Candidate
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
        return Err(
            "CrystaOptimization native solver requires four nonempty prepared groups".to_string(),
        );
    }
    let started = Instant::now();
    let mut prepared_problem = problem.clone();
    prepared_problem.prepare_evaluation_stats();
    let clusters = prepared_problem.prepare_trees()?;
    let problem = &prepared_problem;
    let requirements = &Requirements::new(
        problem
            .scenario_snapshot
            .get("requirements")
            .unwrap_or(&Value::Null),
    );
    let mut seed = SearchState {
        best_score: f64::NEG_INFINITY,
        ..SearchState::default()
    };
    for selected in initial_selections(problem) {
        let stats = selection_evaluation_stats(problem, &selected);
        consider(problem, requirements, &mut seed, &selected, &stats)?;
    }
    repair_infeasible_seed(problem, requirements, &mut seed)?;
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
                    let stats = selection_evaluation_stats(problem, &trial);
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
    improve_pair_seed(problem, requirements, &mut seed)?;
    seed.evaluations += 1;
    let root = evaluate_box(problem, &clusters, None)?.expect("unfiltered box");
    if !individual_utilities_possible(problem, &clusters, requirements, &mut seed)? {
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
            scheduler: NativeSchedulerTelemetry::default(),
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
            scheduler: NativeSchedulerTelemetry::default(),
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
        splits: AtomicU64::new(0),
        steals: AtomicU64::new(0),
        work_busy_micros: AtomicU64::new(0),
        longest_work_item_micros: AtomicU64::new(0),
    });
    // Initial shards only seed parallelism.  Unlike the former fixed-index
    // scheduler, every descendant returns to this common max-priority
    // frontier, so workers that finish early can keep taking newly split work.
    let frontier = Arc::new(Mutex::new(BinaryHeap::from(shards)));
    let active = AtomicUsize::new(0);
    let processed = AtomicU64::new(0);
    let worker_busy_micros = Arc::new(
        (0..used_threads)
            .map(|_| AtomicU64::new(0))
            .collect::<Vec<_>>(),
    );
    let failure = Mutex::new(None::<String>);
    std::thread::scope(|scope| {
        for worker_index in 0..used_threads {
            let incumbent = Arc::clone(&incumbent);
            let counters = Arc::clone(&counters);
            let frontier = Arc::clone(&frontier);
            let worker_busy_micros = Arc::clone(&worker_busy_micros);
            let active = &active;
            let processed = &processed;
            let failure = &failure;
            scope.spawn(move || {
                let mut children = Vec::new();
                loop {
                    if failure
                        .lock()
                        .expect("CrystaOptimization failure mutex poisoned")
                        .is_some()
                    {
                        break;
                    }
                    if cancel.is_some_and(|signal| signal.load(AtomicOrdering::Acquire)) {
                        break;
                    }
                    let mut waited_for_frontier = false;
                    let node = loop {
                        let mut ready = frontier
                            .lock()
                            .expect("CrystaOptimization frontier mutex poisoned");
                        if let Some(node) = ready.pop() {
                            // Claim while holding the same lock used to observe the
                            // queue: an empty queue is terminal only with no active
                            // worker that could still publish children.
                            active.fetch_add(1, AtomicOrdering::AcqRel);
                            if waited_for_frontier {
                                counters.steals.fetch_add(1, AtomicOrdering::Relaxed);
                            }
                            break Some(node);
                        }
                        drop(ready);
                        if active.load(AtomicOrdering::Acquire) == 0 {
                            break None;
                        }
                        waited_for_frontier = true;
                        std::thread::yield_now();
                    };
                    let Some(node) = node else {
                        break;
                    };
                    let work_started = Instant::now();
                    children.clear();
                    let outcome = expand_parallel_node_into(
                        &node,
                        problem,
                        requirements,
                        &incumbent,
                        &mut counters.as_ref(),
                        cancel,
                        None,
                        &mut children,
                    );
                    let work_micros = work_started.elapsed().as_micros() as u64;
                    counters
                        .work_busy_micros
                        .fetch_add(work_micros, AtomicOrdering::Relaxed);
                    worker_busy_micros[worker_index]
                        .fetch_add(work_micros, AtomicOrdering::Relaxed);
                    counters
                        .longest_work_item_micros
                        .fetch_max(work_micros, AtomicOrdering::Relaxed);
                    match outcome {
                        Ok(true) => {
                            if !children.is_empty() {
                                let mut ready = frontier
                                    .lock()
                                    .expect("CrystaOptimization frontier mutex poisoned");
                                ready.extend(children.drain(..));
                            }
                            processed.fetch_add(1, AtomicOrdering::Relaxed);
                        }
                        Ok(false) => {}
                        Err(error) => {
                            *failure
                                .lock()
                                .expect("CrystaOptimization failure mutex poisoned") = Some(error);
                        }
                    }
                    active.fetch_sub(1, AtomicOrdering::AcqRel);
                    if failure
                        .lock()
                        .expect("CrystaOptimization failure mutex poisoned")
                        .is_some()
                    {
                        break;
                    }
                }
            });
        }
    });
    if let Some(error) = failure
        .lock()
        .map_err(|_| "CrystaOptimization failure mutex was poisoned".to_string())?
        .take()
    {
        return Err(error);
    }
    let cancelled = cancel.is_some_and(|signal| signal.load(AtomicOrdering::Acquire));
    // `completed_shards` retains its public meaning as the initial work set
    // fully drained. A cancelled run must never report a completed frontier.
    let completed_shards = if cancelled || processed.load(AtomicOrdering::Relaxed) == 0 {
        0
    } else {
        scheduled_shards
    };
    let final_state = incumbent
        .record
        .lock()
        .map_err(|_| "CrystaOptimization incumbent mutex was poisoned".to_string())?;
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
        scheduler: NativeSchedulerTelemetry {
            split_count: counters.splits.load(AtomicOrdering::Relaxed),
            steal_count: counters.steals.load(AtomicOrdering::Relaxed),
            work_busy_micros: counters.work_busy_micros.load(AtomicOrdering::Relaxed),
            worker_busy_micros: worker_busy_micros
                .iter()
                .map(|busy| busy.load(AtomicOrdering::Relaxed))
                .collect(),
            longest_work_item_micros: counters
                .longest_work_item_micros
                .load(AtomicOrdering::Relaxed),
        },
    })
}

#[cfg(test)]
mod tests {
    use super::*;
    use serde_json::json;

    #[test]
    fn cached_split_gain_matches_stronger_child_envelope_reduction() {
        for mut problem in [wide_problem(), joint_problem()] {
            problem.prepare_trees().unwrap();
            let score = |node: &TreeNode| {
                let positive = node
                    .envelope
                    .iter()
                    .map(|(key, value)| (key.to_owned(), value.max(0.0)))
                    .collect();
                heuristic_score(&positive, "damage")
            };
            let mut nonzero = 0;
            for node in &problem.trees.nodes {
                let expected = match (node.left, node.right) {
                    (Some(left), Some(right)) => {
                        score(node) - score(&problem.trees[left]).min(score(&problem.trees[right]))
                    }
                    _ => f64::NEG_INFINITY,
                };
                assert_eq!(node.split_slack.to_bits(), expected.to_bits());
                nonzero += usize::from(expected.is_finite() && expected != 0.0);
            }
            if problem.trees.joint.is_some() {
                assert!(nonzero > 0);
            }
        }
    }

    #[test]
    fn split_order_isolates_a_weaker_child_and_preserves_cartesian_coverage() {
        let mut problem = small_problem();
        for (g, values) in [vec![1.0, 3.0], vec![0.0, 10.0], vec![2.0; 4], vec![1.0]]
            .into_iter()
            .enumerate()
        {
            problem.groups[g].packages = values
                .into_iter()
                .enumerate()
                .map(|(i, value)| NativePackage {
                    id: format!("{g}-{i}"),
                    evaluation_delta: None,
                    search_values: Vec::new(),
                    stat_delta: Stats::from([("ATKP".into(), value)]),
                })
                .collect();
        }
        let roots = problem.prepare_trees().unwrap();
        // The old max-child reduction is zero in all three available groups
        // and picks the four-package group. The new score exposes the 0/10
        // tradeoff first, followed by 1/3, with no per-box extra evaluations.
        for root in &roots[..3] {
            let node = &problem.trees[*root];
            assert_eq!(
                node.split_score
                    - problem.trees[node.left.unwrap()]
                        .split_score
                        .max(problem.trees[node.right.unwrap()].split_score),
                0.0
            );
        }
        assert_eq!(split_indices(&problem.trees, &roots), [Some(1), Some(0)]);
        let mut covered = HashSet::new();
        for child in ChildBoxes::new(&problem.trees, &roots) {
            let candidates: [Vec<usize>; 4] = std::array::from_fn(|g| {
                let mut out = Vec::new();
                cluster_indices(&problem.trees, child[g], &mut out);
                out
            });
            for a in &candidates[0] {
                for b in &candidates[1] {
                    for c in &candidates[2] {
                        for d in &candidates[3] {
                            assert!(covered.insert([*a, *b, *c, *d]), "overlapping child boxes");
                        }
                    }
                }
            }
        }
        assert_eq!(
            covered.len(),
            16,
            "every parent combination must survive the split"
        );
    }

    fn workload_branch_problem() -> NativeProblem {
        let mut problem = small_problem();
        let groups = [
            vec![Stats::new(), Stats::from([("ATKP".into(), 40.0)])],
            vec![
                Stats::from([("ATKP".into(), 20.0)]),
                Stats::from([("MATKP".into(), 20.0)]),
            ],
            vec![
                Stats::new(),
                Stats::new(),
                Stats::from([("ATKP".into(), 25.0)]),
                Stats::from([("ATKP".into(), 25.0)]),
            ],
            vec![Stats::from([("ATKP".into(), 1.0)])],
        ];
        for (g, stats) in groups.into_iter().enumerate() {
            problem.groups[g].packages = stats
                .into_iter()
                .enumerate()
                .map(|(i, stat_delta)| NativePackage {
                    id: format!("{g}-{i}"),
                    evaluation_delta: None,
                    search_values: Vec::new(),
                    stat_delta,
                })
                .collect();
        }
        problem
    }

    #[test]
    fn gap_branching_balances_children_and_accounts_for_candidate_counts() {
        let mut problem = workload_branch_problem();
        let roots = problem.prepare_trees().unwrap();
        // Group 0 isolates a 40k loss in one candidate; group 1 loses 20k
        // in both candidates; group 2 isolates a 25k loss in two candidates.
        // A far incumbent rewards group 2's larger reduction footprint.
        // Near the incumbent, surplus loss is capped and both group 1
        // children matter. The original one-child ranking does neither.
        assert_eq!(split_indices(&problem.trees, &roots), [Some(0), Some(2)]);
        assert_eq!(
            ChildBoxes::with_score_gap(&problem.trees, &roots, 100.0, 0.0).splits,
            [Some(2), Some(1)]
        );
        assert_eq!(
            ChildBoxes::with_score_gap(&problem.trees, &roots, 100.0, 99.0).splits,
            [Some(1), Some(2)]
        );
    }

    #[test]
    fn gap_branching_keeps_fallback_for_unavailable_nonfinite_and_closed_gaps() {
        let mut problem = workload_branch_problem();
        let roots = problem.prepare_trees().unwrap();
        let fallback = split_indices(&problem.trees, &roots);
        for (upper, best) in [
            (100.0, f64::NEG_INFINITY),
            (f64::INFINITY, 99.0),
            (100.0, f64::NAN),
            (f64::NAN, 99.0),
            (100.0, 100.0),
            (100.0, 101.0),
            (0.0, -1.0),
            (-1.0, -2.0),
        ] {
            assert_eq!(
                ChildBoxes::with_score_gap(&problem.trees, &roots, upper, best).splits,
                fallback
            );
        }
        for id in roots {
            Arc::make_mut(&mut problem.trees).nodes[id.0 as usize].split_score = 0.0;
        }
        assert_eq!(
            ChildBoxes::with_score_gap(&problem.trees, &roots, 100.0, 99.0).splits,
            fallback
        );
        Arc::make_mut(&mut problem.trees).nodes[roots[0].0 as usize].split_score = f64::INFINITY;
        assert_eq!(
            ChildBoxes::with_score_gap(&problem.trees, &roots, 100.0, 99.0).splits,
            fallback
        );
    }

    #[test]
    fn gap_branching_preserves_all_combinations_when_incumbent_changes() {
        let mut problem = workload_branch_problem();
        let roots = problem.prepare_trees().unwrap();
        for offset in 0..4 {
            let mut pending = vec![roots];
            let mut covered = HashSet::new();
            let mut visited = 0;
            while let Some(clusters) = pending.pop() {
                let best = [f64::NEG_INFINITY, 0.0, 99.0, 100.0][(visited + offset) % 4];
                visited += 1;
                let children = ChildBoxes::with_score_gap(&problem.trees, &clusters, 100.0, best);
                if children.len() == 0 {
                    let selected = std::array::from_fn::<_, GROUP_COUNT, _>(|g| {
                        problem.trees[clusters[g]].package.unwrap()
                    });
                    assert!(
                        covered.insert(selected),
                        "adaptive split overlaps another child"
                    );
                } else {
                    pending.extend(children);
                }
            }
            let expected: HashSet<_> = (0..2)
                .flat_map(|a| (0..2).flat_map(move |b| (0..4).map(move |c| [a, b, c, 0])))
                .collect();
            assert_eq!(
                covered, expected,
                "changing gap must preserve all 16 completions exactly once"
            );
        }
    }

    #[test]
    fn impossible_children_skip_stat_evaluation_and_frontier_insertion() {
        let mut problem = joint_problem();
        let roots = problem.prepare_trees().unwrap();
        let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
        let mut pending = vec![roots];
        let mut checked = 0;
        let incumbent = SharedIncumbent {
            score_bits: AtomicU64::new(f64::NEG_INFINITY.to_bits()),
            record: Mutex::new(SearchState {
                best_score: f64::NEG_INFINITY,
                ..SearchState::default()
            }),
        };
        while let Some(clusters) = pending.pop() {
            if !problem.trees.joint_utilities_possible(&clusters)
                || box_combinations(&problem.trees, &clusters, SMALL_BOX_LIMIT) <= SMALL_BOX_LIMIT
            {
                continue;
            }
            let boxes: Vec<_> = ChildBoxes::new(&problem.trees, &clusters).collect();
            let impossible = boxes
                .iter()
                .filter(|child| !problem.trees.joint_utilities_possible(child))
                .count();
            if impossible > 0 {
                let mut counters = LocalSearchCounters {
                    joint_probes: 8,
                    joint_rejections: 8,
                    ..LocalSearchCounters::default()
                };
                let mut children = Vec::new();
                assert!(expand_parallel_node_inner(
                    &WorkItem {
                        upper: f64::INFINITY,
                        clusters
                    },
                    LOOKAHEAD_MAX_DEPTH,
                    &problem,
                    &requirements,
                    &incumbent,
                    &mut counters,
                    None,
                    None,
                    &mut children
                )
                .unwrap());
                assert_eq!(counters.evaluations, (boxes.len() - impossible) as u64);
                assert!(counters.pruned_by_constraint >= impossible as u64);
                assert!(children
                    .iter()
                    .all(|child| problem.trees.joint_utilities_possible(&child.clusters)));
                checked += 1;
            }
            pending.extend(boxes);
        }
        assert!(
            checked > 0,
            "must exercise branches rejected before evaluator calls"
        );
    }

    #[test]
    fn joint_pressure_requires_observed_rejections_and_turns_off_when_rare() {
        let mut counters = LocalSearchCounters::default();
        for i in 0..8 {
            assert!(!counters.joint_pressure());
            counters.count_joint_probe(i < 2);
        }
        assert!(counters.joint_pressure());
        for _ in 0..8 {
            counters.count_joint_probe(false);
        }
        assert!(!counters.joint_pressure());
        counters.count_joint_probe(true);
        assert!(counters.joint_pressure());
        // Probe statistics do not fabricate full evaluations or deletions.
        assert_eq!(counters.evaluations, 0);
        assert_eq!(counters.pruned_by_constraint, 0);
    }

    fn joint_problem() -> NativeProblem {
        let mut problem = wide_problem();
        let mut base = serde_json::to_value(&problem.base_context).unwrap();
        base["critF"] = json!(0);
        base["amprF"] = json!(0);
        base["skillMult"] = json!(1);
        problem.base_context = PreparedContext::from(base);
        problem.scenario_snapshot =
            json!({"requirements":{"amprBeforeDual":66,"normalAttackCrit":100}});
        for (g, group) in problem.groups.iter_mut().enumerate() {
            for (i, package) in group.packages.iter_mut().enumerate() {
                // Conflicting supply, forced penalties, duplicate score/ID ties,
                // percentage critical contribution, and MP-dependent AMPR.
                let n = (i / 2) as f64;
                package.stat_delta = Stats::from([
                    ("AMPR".into(), n * 9.0 - 3.0),
                    ("CRIT".into(), 42.0 - n * 15.0),
                    ("CRITP".into(), if i % 2 == 0 { -20.0 } else { 0.0 }),
                    ("MAXMP".into(), if g % 2 == 0 { -100.0 } else { 100.0 }),
                    ("ATKP".into(), n * 7.0),
                ]);
            }
        }
        problem
    }

    #[test]
    fn joint_bound_covers_every_feasible_completion_and_cuts_conflicting_boxes() {
        let mut total_cuts = 0;
        for (crt, crit, ampr, mp) in [
            (0, 100.0, 66.0, 2000),
            (34, 95.5, 65.5, 1900),
            (100, 100.0, 70.0, 1500),
        ] {
            let mut problem = joint_problem();
            let mut base = serde_json::to_value(&problem.base_context).unwrap();
            base["crtBase"] = json!(crt);
            base["maxMpF"] = json!(mp);
            problem.base_context = PreparedContext::from(base);
            problem.scenario_snapshot["requirements"]["normalAttackCrit"] = json!(crit);
            problem.scenario_snapshot["requirements"]["amprBeforeDual"] = json!(ampr);
            let roots = problem.prepare_trees().unwrap();
            let joint = problem
                .trees
                .joint
                .as_ref()
                .expect("fixture must activate bound");
            let nodes: [Vec<NodeId>; 4] = std::array::from_fn(|g| {
                let end = roots
                    .get(g + 1)
                    .map_or(problem.trees.nodes.len(), |n| n.0 as usize);
                (roots[g].0 as usize..end)
                    .map(|i| NodeId(i as u32))
                    .collect()
            });
            let mut feasible_boxes = HashSet::new();
            let mut feasible_completions = 0;
            for a in 0..8 {
                for b in 0..8 {
                    for c in 0..8 {
                        for d in 0..8 {
                            let selected = [a, b, c, d];
                            let utility = utility_values(
                                &problem.base_context,
                                &selection_stats(&problem, &selected),
                            )
                            .unwrap();
                            if utility[2] < ampr || utility[3] < crit {
                                continue;
                            }
                            feasible_completions += 1;
                            let ancestors: [Vec<NodeId>; 4] = std::array::from_fn(|g| {
                                nodes[g]
                                    .iter()
                                    .copied()
                                    .filter(|n| {
                                        let mut indices = Vec::new();
                                        cluster_indices(&problem.trees, *n, &mut indices);
                                        indices.contains(&selected[g])
                                    })
                                    .collect()
                            });
                            for a in &ancestors[0] {
                                for b in &ancestors[1] {
                                    for c in &ancestors[2] {
                                        for d in &ancestors[3] {
                                            let box_ = [*a, *b, *c, *d];
                                            assert!(
                                                joint.possible(&box_),
                                                "feasible completion lost"
                                            );
                                            feasible_boxes.insert(box_.map(|n| n.0));
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            assert!(feasible_completions > 0);
            for a in &nodes[0] {
                for b in &nodes[1] {
                    for c in &nodes[2] {
                        for d in &nodes[3] {
                            let box_ = [*a, *b, *c, *d];
                            if joint.possible(&box_) {
                                continue;
                            }
                            assert!(!feasible_boxes.contains(&box_.map(|n| n.0)));
                            let utility = utility_values(
                                &problem.base_context,
                                &box_stats(&problem.trees, &box_),
                            )
                            .unwrap();
                            if utility[2] >= ampr && utility[3] >= crit {
                                total_cuts += 1;
                            }
                        }
                    }
                }
            }
        }
        assert!(total_cuts > 0, "must tighten independent utility envelopes");
    }

    #[test]
    fn joint_bound_preserves_oracle_ties_order_threads_and_checkpoint_resume() {
        let mut problem = joint_problem();
        problem.metadata.initial_package_ids =
            vec!["0-3".into(), "1-3".into(), "2-5".into(), "3-5".into()];
        let roots = problem.prepare_trees().unwrap();
        let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
        let mut oracle = SearchState {
            best_score: f64::NEG_INFINITY,
            ..SearchState::default()
        };
        enumerate_box_reference(
            0,
            &roots,
            &problem,
            &requirements,
            &mut [0; 4],
            &Stats::new(),
            &mut oracle,
            &mut 0,
        )
        .unwrap();
        assert!(oracle.best_selected.is_some());
        for reverse in [false, true] {
            if reverse {
                for group in &mut problem.groups {
                    group.packages.reverse();
                }
            }
            let serial = solve_exact(&problem).unwrap();
            assert_eq!(serial.score, Some(oracle.best_score));
            assert_eq!(serial.best_build.unwrap().id, oracle.best_id);
            for threads in [1, 2, 8, 16, 64] {
                let mut session = NativeSearchSession::new(problem.clone()).unwrap();
                let ready = session.ready_work_count();
                let cancel = Arc::new(AtomicBool::new(true));
                session
                    .run_parallel_slice_with_control(8, threads, Some(&cancel), None)
                    .unwrap();
                assert_eq!(session.ready_work_count(), ready);
                session
                    .run_parallel_slice_with_control(8, threads, None, Some(Instant::now()))
                    .unwrap();
                assert_eq!(session.ready_work_count(), ready);
                session.run_parallel_slice(1, threads).unwrap();
                let checkpoint = serde_json::from_str(
                    &serde_json::to_string(&session.checkpoint().unwrap()).unwrap(),
                )
                .unwrap();
                let mut restored = NativeSearchSession::from_checkpoint(checkpoint).unwrap();
                assert!(restored.problem.trees.joint.is_some());
                while !restored.is_complete() {
                    let result = restored.run_parallel_slice(8, threads).unwrap();
                    assert!(result.upper_bound.unwrap() >= oracle.best_score);
                }
                assert_eq!(restored.snapshot().score, Some(oracle.best_score));
                assert_eq!(restored.snapshot().best_build.unwrap().id, oracle.best_id);
            }
        }
    }

    #[test]
    fn constrained_offense_covers_feasible_scores_in_every_ancestor_box() {
        let mut tightened = 0;
        for (case, patch) in [
            json!({}),
            json!({"atkType":"MAG","mainType":"지팡이","intBase":200}),
            json!({"rangeType":"LONG","mainType":"발도검","chkIsUnsheathe":true}),
            json!({"subType":"한손검(듀얼소드)","subAtk":100,"subStab":80}),
            json!({"normalAttackAmprProfile":{"activeCandidates":[{"id":"Blade:8","flat":25,"percent":0,"multiplier":1}]}}),
            json!({"normalAttackAmprProfile":{"passive":[{"percent":13.7,"flat":-2.5,"multiplier":1.2}],"activeCandidates":[{"id":"a","multiplier":2},{"id":"b","flat":25}]}}),
            json!({"normalAttackAmprProfile":{"passive":[{"percent":-25,"multiplier":0.75,"flat":50}],"activeCandidates":[{"id":"a","multiplier":0,"flat":100}]}}),
            json!({"normalAttackAmprProfile":{"activeCandidates":[{"id":"a","multiplier":-1,"flat":200}]}}),
            json!({}),
            json!({}),
            json!({}),
            json!({"crtBase":-100,"critF":300}),
            json!({"intBase":-100,"maxMpF":1900}),
            json!({}),
        ].into_iter().enumerate() {
            let mut problem = joint_problem();
            let mut base = serde_json::to_value(&problem.base_context).unwrap();
            for (key, value) in patch.as_object().unwrap() {
                base[key] = value.clone();
            }
            problem.base_context = PreparedContext::from(base);
            problem.scenario_snapshot["requirements"]["normalAttackCrit"] = json!(95.5);
            problem.scenario_snapshot["requirements"]["amprBeforeDual"] = json!(65.5);
            if case == 9 { problem.scenario_snapshot["requirements"]["amprBeforeDual"] = Value::Null; }
            if case == 10 { problem.scenario_snapshot["requirements"]["normalAttackCrit"] = Value::Null; }
            for group in &mut problem.groups {
                for (i, package) in group.packages.iter_mut().enumerate() {
                    let n = (i / 2) as f64;
                    for (key, value) in [
                        ("ATKP", n * 7.0 - 4.0),
                        ("MATKP", n * 7.0 - 4.0),
                        ("SRW", 9.0 - n * 4.0),
                        ("LRW", 9.0 - n * 4.0),
                        ("CDMG", n * 3.0 - 7.0),
                    ] {
                        package.stat_delta.insert(key.into(), value);
                    }
                    if case >= 8 {
                        for (key, delta) in [("AMPR",0.1),("CRIT",-0.25),("CRITP",0.125),("ATKP",0.5),("CDMG",-0.1)] {
                            let value=package.stat_delta.get(key).copied().unwrap_or(0.0);
                            package.stat_delta.insert(key.into(),value+delta);
                        }
                    }
                    if case == 12 { package.stat_delta.insert("INTP".into(), n*20.0-30.0); }
                    if case == 13 {
                        package.stat_delta.insert("CRITP".into(),n*3000.125);
                        package.stat_delta.insert("ATKP".into(),n*1_000_001.5);
                    }
                }
            }
            let roots = problem.prepare_trees().unwrap();
            let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
            let joint = problem.trees.joint.as_ref().unwrap();
            let ancestors: [Vec<Vec<NodeId>>; 4] = std::array::from_fn(|g| {
                let end = roots
                    .get(g + 1)
                    .map_or(problem.trees.nodes.len(), |n| n.0 as usize);
                (0..8)
                    .map(|selected| {
                        (roots[g].0 as usize..end)
                            .map(|n| NodeId(n as u32))
                            .filter(|n| {
                                let mut indices = Vec::new();
                                cluster_indices(&problem.trees, *n, &mut indices);
                                indices.contains(&selected)
                            })
                            .collect()
                    })
                    .collect()
            });
            let mut bounds = BTreeMap::new();
            let mut feasible_count = 0;
            for a in 0..8 {
                for b in 0..8 {
                    for c in 0..8 {
                        for d in 0..8 {
                            let selected = [a, b, c, d];
                            let actual = selection_stats(&problem, &selected);
                            let Some(summary) = evaluate_feasible_summary(
                                &problem.base_context,
                                &actual,
                                |i, v| requirements.accepts_value(i, v),
                            )
                            .unwrap() else {
                                continue;
                            };
                            feasible_count += 1;
                            for a in &ancestors[0][a] {
                                for b in &ancestors[1][b] {
                                    for c in &ancestors[2][c] {
                                        for d in &ancestors[3][d] {
                                            let box_ = [*a, *b, *c, *d];
                                            assert!(joint.possible(&box_), "feasible completion pruned in case {case}");
                                            let (stats,upper)=bounds.entry(box_).or_insert_with(|| {
                        let mut plain = box_.iter().fold(Stats::new(),|sum,node|add_stats(sum,&problem.trees[*node].envelope));
                        let original=plain.clone();joint.tighten_offense(&box_,&mut plain);
                        let mut reference=original.clone();
                        joint.tighten_offense_reference(&box_,&mut reference);
                        for key in joint.offense.keys {
                            assert_eq!(plain.get(key).map(|v|v.to_bits()), reference.get(key).map(|v|v.to_bits()), "offense bound differs in case {case}: {key}");
                        }
                        if plain != original {tightened += 1;}
                        let score=evaluate_feasible_summary(&problem.base_context,&plain,|i,v|requirements.accepts_value(i,v)).unwrap().expect("feasible completion requires a feasible envelope").optimization_damage_factor;
                        (plain,score)
                    });
                                            for key in joint.offense.keys {
                                                assert!(
                                                    stats.get(key).copied().unwrap_or(0.0)
                                                        >= actual.get(key).copied().unwrap_or(0.0),
                                                    "feasible coordinate clipped: {key}"
                                                );
                                            }
                                            assert!(
                                                *upper >= summary.optimization_damage_factor,
                                                "feasible damage exceeds tightened upper"
                                            );
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            assert!(feasible_count > 0);
        }
        assert!(tightened > 0, "must tighten a coordinate envelope");
    }

    #[test]
    fn axis_offense_bounds_tighten_when_the_other_utility_is_slack() {
        for constrained in ["AMPR", "CRIT"] {
            let mut problem = joint_problem();
            // Synthetic proof fixture only: lower the other goal below base
            // supply, without adding bonuses to any measured user input.
            let slack_goal = if constrained == "AMPR" {
                "normalAttackCrit"
            } else {
                "amprBeforeDual"
            };
            problem.scenario_snapshot["requirements"][slack_goal] = json!(1);
            for group in &mut problem.groups {
                for (i, package) in group.packages.iter_mut().enumerate() {
                    let supply = (i / 2) as f64 * 10.0;
                    let slack = if i % 2 == 0 { 100.0 } else { 0.0 };
                    package.stat_delta = Stats::from([
                        (constrained.into(), supply),
                        (
                            (if constrained == "AMPR" {
                                "CRIT"
                            } else {
                                "AMPR"
                            })
                            .into(),
                            slack,
                        ),
                        ("ATKP".into(), 30.0 - supply),
                    ]);
                }
            }
            let roots = problem.prepare_trees().unwrap();
            let joint = problem.trees.joint.as_ref().unwrap();
            let p = roots.iter().map(|n| joint.crit_p[n.0 as usize]).sum();
            let minima = &joint.minima[joint.bucket_index(p)];
            let mut legacy = f64::INFINITY;
            for (scale, k) in OFFENSE_SCALES.into_iter().enumerate() {
                for (direction, minimum) in minima.iter().enumerate().take(MIXED_DIRECTIONS) {
                    let index = scale * JOINT_DIRECTIONS + direction;
                    let support: f64 = roots
                        .iter()
                        .map(|n| joint.offense.maxima[n.0 as usize][0][index])
                        .sum();
                    legacy = legacy.min(((support - minimum) / k).floor());
                }
            }
            let mut stats = roots.iter().fold(Stats::new(), |sum, node| {
                add_stats(sum, &problem.trees[*node].envelope)
            });
            legacy = legacy.min(stats["ATKP"]);
            joint.tighten_offense(&roots, &mut stats);
            assert!(
                stats["ATKP"] < legacy,
                "axis direction must tighten {constrained} tradeoff"
            );
            // Compare exact search with exhaustive completion enumeration as well.
            let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
            let mut expected = SearchState {
                best_score: f64::NEG_INFINITY,
                ..SearchState::default()
            };
            enumerate_box_reference(
                0,
                &roots,
                &problem,
                &requirements,
                &mut [0; 4],
                &Stats::new(),
                &mut expected,
                &mut 0,
            )
            .unwrap();
            assert!(expected.best_selected.is_some());
            let result = solve_exact(&problem).unwrap();
            assert_eq!(result.score, Some(expected.best_score));
            assert_eq!(result.best_build.unwrap().id, expected.best_id);
        }
    }

    #[test]
    fn offense_kernel_matches_reference_for_every_direction_and_raw_cap() {
        let mut problem = joint_problem();
        let roots = problem.prepare_trees().unwrap();
        let mut joint = problem.trees.joint.as_ref().unwrap().clone();
        joint.crit_p.fill(0.0);
        joint.minima.fill([0.0; JOINT_DIRECTIONS]);
        joint.offense.axis_enabled = [true; 3];
        for direction in 0..OFFENSE_DIRECTIONS {
            for support in [-9.0, -1.0, 0.0, 1.0, 9.0] {
                for (group, node) in roots.iter().enumerate() {
                    for maxima in &mut joint.offense.maxima[node.0 as usize] {
                        maxima.fill(1_000_000.0);
                        maxima[direction] = if group == 0 { support } else { 0.0 };
                    }
                }
                for unit in [1.0, 1.0 / 1024.0, 1_048_576.0] {
                    for coordinate in joint.offense.coordinates.iter_mut().flatten() {
                        coordinate.unit = unit;
                    }
                    for mask in 0..8 {
                        joint.offense.enabled = std::array::from_fn(|i| mask & (1 << i) != 0);
                        for original in [-0.0, 0.0, -64.125, 64.125] {
                            // Both omitted and present coordinates preserve their raw cap.
                            for omitted in 0..=3 {
                                let mut actual = Stats::new();
                                for (i, key) in joint.offense.keys.iter().enumerate() {
                                    if i != omitted {
                                        actual.insert((*key).into(), original);
                                    }
                                }
                                let mut reference = actual.clone();
                                joint.tighten_offense(&roots, &mut actual);
                                joint.tighten_offense_reference(&roots, &mut reference);
                                for key in joint.offense.keys {
                                    assert_eq!(actual.get(key).map(|v| v.to_bits()), reference.get(key).map(|v| v.to_bits()), "direction={direction}, unit={unit}, mask={mask}, cap={original}");
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    #[test]
    fn constrained_offense_relaxes_fractional_and_large_coordinates_without_changing_raw() {
        for value in [0.5, 1_000_001.0] {
            let mut problem = joint_problem();
            problem.groups[0].packages[0]
                .stat_delta
                .insert("ATKP".into(), value);
            let original = serde_json::to_value(&problem).unwrap();
            let roots = problem.prepare_trees().unwrap();
            let joint = problem.trees.joint.as_ref().unwrap();
            assert!(joint.offense.enabled[0]);
            let mut stats = roots.iter().fold(Stats::new(), |sum, node| {
                add_stats(sum, &problem.trees[*node].envelope)
            });
            joint.tighten_offense(&roots, &mut stats);
            assert!(stats.get("ATKP").copied().unwrap().is_finite());
            assert_eq!(serde_json::to_value(&problem).unwrap(), original);
        }
        let mut problem = joint_problem();
        problem.metadata.modeled_keys = vec!["CRIT".into()];
        let roots = problem.prepare_trees().unwrap();
        assert_eq!(box_stats(&problem.trees, &roots).get("ATKP"), None);
    }

    #[test]
    fn joint_bound_supports_previous_bypasses_without_changing_packages() {
        for patch in [
            json!({"AMPR":0.5}),
            json!({"CRIT":0.5}),
            json!({"CRITP":0.5}),
            json!({"CRITP":10000}),
            json!({"AMPR":1000001}),
        ] {
            let mut problem = joint_problem();
            for (key, value) in patch.as_object().unwrap() {
                problem.groups[0].packages[0]
                    .stat_delta
                    .insert(key.clone(), value.as_f64().unwrap());
            }
            let raw = serde_json::to_value(&problem).unwrap();
            problem.prepare_trees().unwrap();
            assert!(problem.trees.joint.is_some());
            assert_eq!(serde_json::to_value(&problem).unwrap(), raw);
        }
        for patch in [
            json!({"intBase":-1}),
            json!({"crtBase":-1}),
            json!({"amprF":1000}),
            json!({"normalAttackAmprProfile":{"passive":[{"percent":10}]}}),
        ] {
            let mut problem = joint_problem();
            let mut base = serde_json::to_value(&problem.base_context).unwrap();
            base.as_object_mut()
                .unwrap()
                .extend(patch.as_object().unwrap().clone());
            problem.base_context = PreparedContext::from(base);
            problem.prepare_trees().unwrap();
            assert!(problem.trees.joint.is_some());
        }
        // Additional bound does not inherit an incomplete split-key list.
        let mut problem = joint_problem();
        problem.metadata.modeled_keys = vec!["ATKP".into()];
        problem.prepare_trees().unwrap();
        assert!(problem.trees.joint.is_some());
    }

    #[test]
    fn generalized_bounds_match_oracle_and_resume_with_real_modifier_forms() {
        for profile in [
            json!({"activeCandidates":[{"id":"Blade:8","flat":25}]}),
            json!({"passive":[{"percent":-25,"flat":50,"multiplier":0.75}],"activeCandidates":[{"id":"z","multiplier":1.2},{"id":"a","flat":25}]}),
        ] {
            let mut problem = joint_problem();
            let mut base = serde_json::to_value(&problem.base_context).unwrap();
            base["normalAttackAmprProfile"] = profile;
            problem.base_context = PreparedContext::from(base);
            for group in &mut problem.groups {
                for package in &mut group.packages {
                    let ampr = package.stat_delta.get("AMPR").copied().unwrap();
                    package.stat_delta.insert("AMPR".into(), ampr + 0.125);
                    package.stat_delta.insert("CDMG".into(), 0.25);
                }
            }
            let roots = problem.prepare_trees().unwrap();
            assert!(problem.trees.joint.is_some());
            let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
            let mut oracle = SearchState {
                best_score: f64::NEG_INFINITY,
                ..SearchState::default()
            };
            enumerate_box_reference(
                0,
                &roots,
                &problem,
                &requirements,
                &mut [0; 4],
                &Stats::new(),
                &mut oracle,
                &mut 0,
            )
            .unwrap();
            assert!(oracle.best_selected.is_some());
            for group in &mut problem.groups {
                group.packages.reverse();
            }
            let serial = solve_exact(&problem).unwrap();
            assert_eq!(serial.score, Some(oracle.best_score));
            assert_eq!(serial.best_build.unwrap().id, oracle.best_id);
            for threads in [1, 4, 64] {
                let mut session = NativeSearchSession::new(problem.clone()).unwrap();
                session.run_parallel_slice(1, threads).unwrap();
                let mut session =
                    NativeSearchSession::from_checkpoint(session.checkpoint().unwrap()).unwrap();
                while !session.is_complete() {
                    let result = session.run_parallel_slice(16, threads).unwrap();
                    assert!(result.upper_bound.unwrap() >= oracle.best_score);
                }
                assert_eq!(session.snapshot().score, Some(oracle.best_score));
                assert_eq!(session.snapshot().best_build.unwrap().id, oracle.best_id);
            }
        }
    }

    #[test]
    fn joint_bound_proves_infeasibility_without_fabricating_an_incumbent() {
        let mut problem = joint_problem();
        for group in &mut problem.groups {
            for package in &mut group.packages {
                package
                    .stat_delta
                    .insert("CRIT".into(), package.stat_delta["CRIT"] - 4.0);
            }
        }
        let serial = solve_exact(&problem).unwrap();
        assert_eq!(serial.status, "invalid");
        assert!(serial.score.is_none());
        let mut session = NativeSearchSession::new(problem).unwrap();
        assert!(session.problem.trees.joint.is_some());
        assert_eq!(session.snapshot().status, "no-incumbent-yet");
        session
            .run_parallel_slice_with_control(8, 4, None, Some(Instant::now()))
            .unwrap();
        assert_eq!(session.snapshot().status, "no-incumbent-yet");
        while !session.is_complete() {
            session.run_parallel_slice(8, 4).unwrap();
        }
        let result = session.snapshot();
        assert_eq!(result.status, "invalid");
        assert!(result.best_build.is_none());
    }

    #[test]
    fn arena_layout_capacity_and_path_restore_are_checked() {
        assert_eq!(std::mem::size_of::<WorkItem>(), 24);
        assert_eq!(tree_capacity([1, 2, 3, 4]).unwrap(), 16);
        assert!(tree_capacity([0]).is_err());
        assert!(tree_capacity([usize::MAX]).is_err());
        assert!(tree_capacity([u32::MAX as usize, 1]).is_err());
        let mut problem = wide_problem();
        let roots = problem.prepare_trees().unwrap();
        let arena = &problem.trees;
        assert_eq!(arena.nodes.len(), 4 * (2 * 8 - 1));
        for group in 0..GROUP_COUNT {
            let start = roots[group].0 as usize;
            let end = roots
                .get(group + 1)
                .map_or(arena.nodes.len(), |id| id.0 as usize);
            for index in start..end {
                let id = NodeId(index as u32);
                let node = &arena[id];
                assert_eq!(find_tree_node(arena, roots[group], &node.path), Some(id));
                if let (Some(left), Some(right)) = (node.left, node.right) {
                    assert_eq!(left.0, id.0 + 1);
                    assert_eq!(right.0, left.0 + (2 * arena[left].size - 1) as u32);
                    assert_eq!(node.size, arena[left].size + arena[right].size);
                }
                for other in index..end {
                    assert_eq!(
                        id.cmp(&NodeId(other as u32)),
                        node.path.cmp(&arena.nodes[other].path)
                    );
                }
            }
            for invalid in ["", "x", "r2", "r0000", "r0x"] {
                assert_eq!(find_tree_node(arena, roots[group], invalid), None);
            }
        }
        let clone = problem.clone();
        assert!(Arc::ptr_eq(&clone.trees, &problem.trees));
        let wire = serde_json::to_value(&problem).unwrap();
        assert!(wire.get("trees").is_none());
        let restored: NativeProblem = serde_json::from_value(wire).unwrap();
        assert!(restored.trees.nodes.is_empty());
    }

    #[test]
    fn projected_search_preserves_raw_output_and_rebuilds_after_checkpoint() {
        let mut problem = wide_problem();
        for group in &mut problem.groups {
            for (index, package) in group.packages.iter_mut().enumerate() {
                package.stat_delta = Stats::from([
                    ("ATKP".into(), 1.0),
                    ("MAXMP".into(), -20.0),
                    ("MOTIONSPEED".into(), 7.5),
                    ("DROP_RATE".into(), index as f64 + 2.0),
                    ("PHYS_RES".into(), -3.25),
                    ("UNKNOWN_FUTURE".into(), -0.0),
                ]);
            }
        }
        // Tree/order metadata is deliberately narrower than evaluator dependencies.
        problem.metadata.modeled_keys = vec!["ATKP".into()];
        let original = serde_json::to_value(&problem).unwrap();
        let expected_stats = selection_stats(&problem, &[0; GROUP_COUNT]);
        let expected_score = evaluate_summary_from_map(&problem.base_context, &expected_stats)
            .unwrap()
            .optimization_damage_factor;
        let check = |result: NativeSolveResult| {
            assert!(result.exact);
            assert_eq!(result.score, Some(expected_score));
            assert_eq!(result.upper_bound, Some(expected_score));
            let build = result.best_build.unwrap();
            assert_eq!(build.id, build_id(&problem.groups, &[0; GROUP_COUNT]));
            assert_eq!(build.stat_delta, expected_stats);
        };
        check(solve_exact(&problem).unwrap());
        for threads in [1, 4, 64] {
            check(solve_exact_parallel(&problem, threads).unwrap().result);
            let mut session = NativeSearchSession::new(problem.clone()).unwrap();
            assert_eq!(serde_json::to_value(&session.problem).unwrap(), original);
            let package = &session.problem.groups[0].packages[0];
            assert_eq!(package.evaluation_stats().get("DROP_RATE"), None);
            assert_eq!(package.evaluation_stats().get("MAXMP"), Some(&-20.0));
            assert_eq!(package.evaluation_stats().get("MOTIONSPEED"), Some(&7.5));
            session.run_parallel_slice(1, threads).unwrap();
            let wire = serde_json::to_value(session.checkpoint().unwrap()).unwrap();
            assert_eq!(wire["problem"], original);
            let checkpoint: NativeSearchCheckpoint = serde_json::from_value(wire).unwrap();
            assert!(checkpoint.problem.groups[0].packages[0]
                .evaluation_delta
                .is_none());
            let mut restored = NativeSearchSession::from_checkpoint(checkpoint).unwrap();
            assert!(restored.problem.groups[0].packages[0]
                .evaluation_delta
                .is_some());
            while !restored.is_complete() {
                restored.run_parallel_slice(128, threads).unwrap();
            }
            check(restored.snapshot());
        }
        assert_eq!(serde_json::to_value(problem).unwrap(), original);
    }

    #[test]
    fn local_counter_overflow_and_merge_match_atomic_counts() {
        let mut local = LocalSearchCounters::default();
        let shared = ParallelCounters::default();
        macro_rules! check {
            ($field:ident, $increment:ident) => {
                local.$field = u64::MAX;
                shared.$field.store(u64::MAX, AtomicOrdering::Relaxed);
                local.$increment();
                (&shared).$increment();
                assert_eq!(local.$field, shared.$field.load(AtomicOrdering::Relaxed));
                assert_eq!(local.$field, 0);
                local.$increment();
            };
        }
        check!(evaluations, count_evaluations);
        check!(visited, count_visited);
        check!(pruned_by_bound, count_pruned_by_bound);
        check!(pruned_by_constraint, count_pruned_by_constraint);
        check!(enumerated, count_enumerated);
        check!(splits, count_splits);
        shared.merge_search_counts(local);
        for counter in [
            &shared.evaluations,
            &shared.visited,
            &shared.pruned_by_bound,
            &shared.pruned_by_constraint,
            &shared.enumerated,
            &shared.splits,
        ] {
            assert_eq!(counter.load(AtomicOrdering::Relaxed), 1);
        }
        assert_eq!(shared.steals.load(AtomicOrdering::Relaxed), 0);
    }

    #[test]
    fn prepared_requirements_preserve_missing_invalid_and_boundary_values() {
        let summary = CrystaOptimizationNativeSummary {
            optimization_damage_factor: 1.0,
            final_max_hp: 100,
            final_max_mp: 200,
            ampr_before_dual: 30,
            normal_attack_crit: 40,
            final_aspd: 500,
        };
        let keys = [
            "maxHp",
            "maxMp",
            "amprBeforeDual",
            "normalAttackCrit",
            "aspd",
        ];
        let values = [100., 200., 30., 40., 500.];
        for (key, limit) in keys.iter().zip(values) {
            for value in [
                Value::Null,
                json!("100"),
                json!(false),
                json!(limit - 0.5),
                json!(limit),
                json!(limit + 0.5),
            ] {
                let input = json!({*key: value});
                let expected = keys.iter().zip(values).all(|(key, actual)| {
                    input
                        .get(key)
                        .and_then(Value::as_f64)
                        .is_none_or(|required| actual >= required)
                });
                assert_eq!(feasible(&summary, &Requirements::new(&input)), expected);
            }
        }
    }

    #[test]
    fn individual_hp_bound_respects_real_two_slot_packages() {
        let mut problem = small_problem();
        problem.base_context = PreparedContext::from(
            json!({"level":100,"vitBase":1,"mainType":"한손검","wpnAtk":100,"strBase":100,"critF":100}),
        );
        problem.scenario_snapshot = json!({"requirements":{"maxHp":5000}});
        problem.metadata.modeled_keys = vec!["MAXHP".into(), "MAXHPP".into()];
        for group in &mut problem.groups {
            group.packages = vec![
                NativePackage {
                    evaluation_delta: None,
                    search_values: Vec::new(),
                    id: format!("{}:flat", group._id),
                    stat_delta: serde_json::from_value(json!({"MAXHP":1000})).unwrap(),
                },
                NativePackage {
                    evaluation_delta: None,
                    search_values: Vec::new(),
                    id: format!("{}:percent", group._id),
                    stat_delta: serde_json::from_value(json!({"MAXHPP":100})).unwrap(),
                },
            ];
        }
        // Coordinate envelope: 8365. Actual maximum with VIT=1: 4873.
        let session = NativeSearchSession::new(problem.clone()).unwrap();
        assert!(session.is_complete());
        assert_eq!(session.snapshot().status, "invalid");
        assert_eq!(session.snapshot().visited_nodes, 0);
        problem.scenario_snapshot["requirements"]["maxHp"] = json!(4873);
        let result = solve_exact(&problem).unwrap();
        assert!(result.exact);
    }

    #[test]
    fn utility_caps_reject_impossible_targets_and_allow_motion_equivalence() {
        for (key, value) in [
            ("maxMp", 2001.),
            ("normalAttackCrit", 101.),
            ("aspd", 10001.),
        ] {
            let mut problem = small_problem();
            problem.scenario_snapshot = json!({"requirements":{key:value}});
            let session = NativeSearchSession::new(problem).unwrap();
            assert!(session.is_complete(), "{key}");
            assert_eq!(session.snapshot().status, "invalid");
        }
        let mut problem = small_problem();
        let mut base = serde_json::to_value(&problem.base_context).unwrap();
        base["motionSpeed"] = json!(50);
        base["godspeedWieldLevel"] = json!(10);
        base["maxMpF"] = json!(3000);
        problem.base_context = PreparedContext::from(base);
        problem.scenario_snapshot = json!({"requirements":{"maxMp":2300,"aspd":10000}});
        assert!(solve_exact(&problem).unwrap().exact);
        problem.scenario_snapshot["requirements"]["maxMp"] = json!(2301);
        assert_eq!(
            NativeSearchSession::new(problem).unwrap().snapshot().status,
            "invalid"
        );
    }

    #[test]
    fn linear_crit_support_cuts_incompatible_flat_and_percent_suppliers() {
        let mut problem = small_problem();
        let mut base = serde_json::to_value(&problem.base_context).unwrap();
        base["critF"] = json!(0);
        base["skillMult"] = json!(1);
        problem.base_context = PreparedContext::from(base);
        for group in &mut problem.groups[..2] {
            group.packages = serde_json::from_value(json!([
                {"id":format!("{}-flat",group._id),"statDelta":{"CRIT":35}},
                {"id":format!("{}-percent",group._id),"statDelta":{"CRITP":100,"ATKP":40}}
            ]))
            .unwrap();
        }
        problem.prepare_trees().unwrap();
        let roots = problem.trees.roots;
        let independent = roots.iter().fold(Stats::new(), |stats, node| {
            add_stats(stats, &problem.trees[*node].envelope)
        });
        assert!(utility_values(&problem.base_context, &independent).unwrap()[3] >= 100.0);
        let joint = problem.trees.joint.as_ref().unwrap();
        assert!(joint.linear_crit.is_some());
        assert!(!joint.possible(&roots));
        assert_eq!(solve_exact(&problem).unwrap().status, "invalid");
        for group in &mut problem.groups[..2] {
            group.packages.push(NativePackage {
                id: format!("{}-both", group._id),
                stat_delta: Stats::from([
                    ("CRIT".into(), 20.0),
                    ("CRITP".into(), 80.0),
                    ("ATKP".into(), 10.0),
                ]),
                evaluation_delta: None,
                search_values: Vec::new(),
            });
        }
        problem.prepare_trees().unwrap();
        let roots = problem.trees.roots;
        assert!(problem.trees.joint_utilities_possible(&roots));
        assert!(
            box_stats(&problem.trees, &roots)
                .get("ATKP")
                .copied()
                .unwrap()
                < 82.0
        );
        let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
        let mut oracle = SearchState {
            best_score: f64::NEG_INFINITY,
            ..SearchState::default()
        };
        enumerate_box_reference(
            0,
            &roots,
            &problem,
            &requirements,
            &mut [0; GROUP_COUNT],
            &Stats::new(),
            &mut oracle,
            &mut 0,
        )
        .unwrap();
        for threads in [1, 2, 8, 64] {
            let result = solve_exact_parallel(&problem, threads).unwrap().result;
            assert!(result.exact);
            assert_eq!(result.score, Some(oracle.best_score));
            assert_eq!(result.best_build.unwrap().id, oracle.best_id);
        }
    }

    #[test]
    fn linear_crit_inequality_matches_evaluator_and_falls_back_outside_integer_budget() {
        for (crt, percent, flat, resistance, minimum) in [
            (0.0, -50.0, 120.0, 70.0, 100.0),
            (68.0, 0.0, 15.0, 8.0, 50.5),
            (13.0, 5.0, -3.0, 2.0, 12.2),
            (-100.0, 25.0, 80.0, 10.0, 30.1),
            (-85.0, 0.0, 80.0, 5.0, 25.0),
        ] {
            let mut problem = small_problem();
            let mut base = serde_json::to_value(&problem.base_context).unwrap();
            for (key, value) in [
                ("crtBase", crt),
                ("critP", percent),
                ("critF", flat),
                ("bossCritResist", resistance),
            ] {
                base[key] = json!(value);
            }
            problem.base_context = PreparedContext::from(base);
            let bound = LinearCritBound::prepare(&problem, minimum).unwrap();
            for f in [-100, -1, 0, 1, 37, 100, 1_000_000] {
                for p in [
                    -1_000_000, -300, -101, -100, -1, 0, 3, 40, 100, 500, 1_000_000,
                ] {
                    let stats =
                        Stats::from([("CRIT".into(), f as f64), ("CRITP".into(), p as f64)]);
                    let accepts =
                        utility_values(&problem.base_context, &stats).unwrap()[3] >= minimum;
                    assert_eq!(
                        accepts,
                        bound.scale * f as f64 + bound.percent_weight * p as f64 >= bound.minimum
                    );
                }
            }
            for key in ["critP", "critF", "bossCritResist"] {
                let mut copy = problem.clone();
                let mut base = serde_json::to_value(&copy.base_context).unwrap();
                base[key] = json!(0.25);
                copy.base_context = PreparedContext::from(base);
                assert!(LinearCritBound::prepare(&copy, minimum).is_none());
            }
            for (key, value) in [
                ("CRIT", 0.25),
                ("CRITP", 0.25),
                ("CRIT", 1_000_001.0),
                ("CRITP", 1_000_001.0),
            ] {
                let mut copy = problem.clone();
                copy.groups[0].packages[0]
                    .stat_delta
                    .insert(key.into(), value);
                assert!(LinearCritBound::prepare(&copy, minimum).is_none());
            }
            for minimum in [0.0, -1.0, 100.1, f64::INFINITY, f64::NAN] {
                assert!(LinearCritBound::prepare(&problem, minimum).is_none());
            }
        }
        // Exact integer oracle at both sides of divisibility boundaries.
        for numerator in [
            -20_000_000_000_000_i64,
            -1_000_000,
            0,
            1_000_000,
            20_000_000_000_000,
        ] {
            for divisor in 1..=400 {
                let multiple = numerator / divisor * divisor;
                for offset in [-1, 0, 1] {
                    let n = multiple + offset;
                    assert_eq!(
                        (n as f64 / divisor as f64).floor(),
                        n.div_euclid(divisor) as f64
                    );
                }
            }
        }
    }

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
    fn pair_seed_escapes_feasible_single_swap_local_optimum_and_preserves_oracle() {
        let mut problem = small_problem();
        let mut base = serde_json::to_value(&problem.base_context).unwrap();
        base["skillMult"] = json!(1);
        problem.base_context = PreparedContext::from(base);
        problem.groups[0].packages = serde_json::from_value(json!([
            {"id":"a0", "statDelta":{"ATKP":20}},
            {"id":"a1", "statDelta":{"AMPR":20}}
        ]))
        .unwrap();
        problem.groups[1].packages = serde_json::from_value(json!([
            {"id":"b0", "statDelta":{"AMPR":20}},
            {"id":"b1", "statDelta":{"ATKP":30}}
        ]))
        .unwrap();
        for group in &mut problem.groups[2..] {
            group.packages = (0..8)
                .map(|index| NativePackage {
                    id: format!("{}-{index}", group._id),
                    stat_delta: Stats::new(),
                    evaluation_delta: None,
                    search_values: Vec::new(),
                })
                .collect();
        }
        problem.scenario_snapshot["requirements"]["amprBeforeDual"] =
            json!(utility_values(&problem.base_context, &Stats::new()).unwrap()[2] + 20.0);
        problem.prepare_evaluation_stats();
        let roots = problem.prepare_trees().unwrap();
        let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
        let mut state = SearchState {
            best_score: f64::NEG_INFINITY,
            ..SearchState::default()
        };
        let baseline = [0; GROUP_COUNT];
        consider(
            &problem,
            &requirements,
            &mut state,
            &baseline,
            &selection_evaluation_stats(&problem, &baseline),
        )
        .unwrap();
        assert!(state.best_selected.is_some());
        let original_score = state.best_score;
        let mut single = state.clone();
        for group in 0..2 {
            let mut selected = baseline;
            selected[group] = 1;
            consider(
                &problem,
                &requirements,
                &mut single,
                &selected,
                &selection_evaluation_stats(&problem, &selected),
            )
            .unwrap();
        }
        assert_eq!(single.best_score, original_score);
        let original_packages = serde_json::to_value(&problem.groups).unwrap();
        improve_pair_seed(&problem, &requirements, &mut state).unwrap();
        assert!(state.best_score > original_score);
        assert_eq!(&state.best_selected.unwrap()[..2], &[1, 1]);
        assert_eq!(
            serde_json::to_value(&problem.groups).unwrap(),
            original_packages
        );
        assert!(state.evaluations <= 1 + 2 * (20 + 6 * 33 * 33));
        let mut oracle = SearchState {
            best_score: f64::NEG_INFINITY,
            ..SearchState::default()
        };
        let mut count = 0;
        enumerate_box_reference(
            0,
            &roots,
            &problem,
            &requirements,
            &mut [0; GROUP_COUNT],
            &Stats::new(),
            &mut oracle,
            &mut count,
        )
        .unwrap();
        assert_eq!(count, 256);
        assert_eq!(state.best_score, oracle.best_score);
        assert_eq!(state.best_id, oracle.best_id);
        for reverse in [false, true] {
            if reverse {
                for group in &mut problem.groups {
                    group.packages.reverse();
                }
            }
            let result = solve_exact(&problem).unwrap();
            assert!(result.exact);
            assert_eq!(result.score, Some(oracle.best_score));
            assert_eq!(result.best_build.unwrap().id, oracle.best_id);
            let result = solve_exact_parallel(&problem, 8).unwrap().result;
            assert!(result.exact);
            assert_eq!(result.score, Some(oracle.best_score));
            assert_eq!(result.best_build.unwrap().id, oracle.best_id);
            let mut session = NativeSearchSession::new(problem.clone()).unwrap();
            while !session.snapshot().exact {
                session
                    .run_parallel_slice_with_control(8, 32, None, None)
                    .unwrap();
            }
            assert_eq!(session.snapshot().best_build.unwrap().id, oracle.best_id);
        }
    }

    #[test]
    fn infeasible_seed_repair_handles_complementary_swaps_and_preserves_exact_search() {
        let mut problem = small_problem();
        let values = utility_values(&problem.base_context, &Stats::new()).unwrap();
        problem.scenario_snapshot =
            json!({"requirements":{"maxHp":values[0]*2.0,"amprBeforeDual":values[2]*2.0}});
        problem.groups[0].packages = serde_json::from_value(json!([
            {"id":"a0","statDelta":{}},
            {"id":"a1","statDelta":{"MAXHP":values[0]*2.0,"AMPR":-values[2],"ASPD":-100000}}
        ]))
        .unwrap();
        problem.groups[1].packages = serde_json::from_value(json!([
            {"id":"b0","statDelta":{}},
            {"id":"b1","statDelta":{"MAXHP":-values[0],"AMPR":values[2]*2.0,"ASPD":-100000}}
        ]))
        .unwrap();
        for group in &mut problem.groups[2..] {
            group.packages = (0..8)
                .map(|i| NativePackage {
                    id: format!("{}-{i}", group._id),
                    stat_delta: Stats::new(),
                    evaluation_delta: None,
                    search_values: Vec::new(),
                })
                .collect();
        }
        problem.prepare_evaluation_stats();
        let roots = problem.prepare_trees().unwrap();
        let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
        let mut state = SearchState {
            best_score: f64::NEG_INFINITY,
            ..SearchState::default()
        };
        for selected in initial_selections(&problem) {
            consider(
                &problem,
                &requirements,
                &mut state,
                &selected,
                &selection_evaluation_stats(&problem, &selected),
            )
            .unwrap();
        }
        assert!(state.best_selected.is_none());
        let packages = serde_json::to_value(&problem.groups).unwrap();
        repair_infeasible_seed(&problem, &requirements, &mut state).unwrap();
        assert!(state.best_selected.is_some());
        assert_eq!(&state.best_selected.unwrap()[..2], &[1, 1]);
        assert_eq!(serde_json::to_value(&problem.groups).unwrap(), packages);
        let mut oracle = SearchState {
            best_score: f64::NEG_INFINITY,
            ..SearchState::default()
        };
        let mut count = 0;
        enumerate_box_reference(
            0,
            &roots,
            &problem,
            &requirements,
            &mut [0; GROUP_COUNT],
            &Stats::new(),
            &mut oracle,
            &mut count,
        )
        .unwrap();
        assert_eq!(count, 256);
        for reverse in [false, true] {
            if reverse {
                for group in &mut problem.groups {
                    group.packages.reverse();
                }
            }
            let session = NativeSearchSession::new(problem.clone()).unwrap();
            assert!(
                session.snapshot().best_build.is_some(),
                "seed must exist before any node visit"
            );
            assert_eq!(session.snapshot().visited_nodes, 0);
            let result = solve_exact(&problem).unwrap();
            assert_eq!(result.score, Some(oracle.best_score));
            assert_eq!(result.best_build.unwrap().id, oracle.best_id);
            for threads in [1, 2, 4, 8, 16, 64] {
                let result = solve_exact_parallel(&problem, threads).unwrap().result;
                assert!(result.exact);
                assert_eq!(result.score, Some(oracle.best_score));
                assert_eq!(result.best_build.unwrap().id, oracle.best_id);
            }
            let restored: NativeSearchCheckpoint = serde_json::from_str(
                &serde_json::to_string(&session.checkpoint().unwrap()).unwrap(),
            )
            .unwrap();
            let mut session = NativeSearchSession::from_checkpoint(restored).unwrap();
            while !session.is_complete() {
                session.run_parallel_slice(8, 4).unwrap();
            }
            assert_eq!(session.snapshot().best_build.unwrap().id, oracle.best_id);
        }
        problem.scenario_snapshot["requirements"]["maxHp"] = json!(1000000);
        let session = NativeSearchSession::new(problem).unwrap();
        assert!(session.is_complete());
        assert_eq!(session.snapshot().status, "invalid");
        assert!(session.snapshot().best_build.is_none());
    }

    #[test]
    fn pair_seed_skips_tiny_or_infeasible_inputs() {
        let mut problem = small_problem();
        problem.prepare_evaluation_stats();
        problem.prepare_trees().unwrap();
        let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
        let mut state = SearchState {
            best_score: f64::NEG_INFINITY,
            ..SearchState::default()
        };
        improve_pair_seed(&problem, &requirements, &mut state).unwrap();
        assert_eq!(state.evaluations, 0);
        consider(
            &problem,
            &requirements,
            &mut state,
            &[0; GROUP_COUNT],
            &selection_evaluation_stats(&problem, &[0; GROUP_COUNT]),
        )
        .unwrap();
        let before = serde_json::to_value(&state).unwrap();
        improve_pair_seed(&problem, &requirements, &mut state).unwrap();
        assert_eq!(serde_json::to_value(&state).unwrap(), before);
    }

    #[allow(clippy::too_many_arguments)] // Recursive complete enumeration shares its immutable search inputs.
    fn enumerate_box_reference(
        index: usize,
        clusters: &[NodeId; GROUP_COUNT],
        problem: &NativeProblem,
        requirements: &Requirements,
        selected: &mut [usize; GROUP_COUNT],
        stats: &Stats,
        state: &mut SearchState,
        enumerated: &mut u64,
    ) -> Result<(), String> {
        if index == GROUP_COUNT {
            *enumerated += 1;
            return consider(problem, requirements, state, selected, stats);
        }
        let mut indices = Vec::with_capacity(problem.trees[clusters[index]].size);
        cluster_indices(&problem.trees, clusters[index], &mut indices);
        for package_index in indices {
            selected[index] = package_index;
            let next = add_stats(
                stats.clone(),
                &problem.groups[index].packages[package_index].stat_delta,
            );
            enumerate_box_reference(
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

    #[test]
    fn prepared_small_box_lists_match_tree_walking_enumeration() {
        for sizes in [
            [1, 1, 1, 1],
            [1, 1, 1, 64],
            [1, 1, 64, 1],
            [1, 64, 1, 1],
            [64, 1, 1, 1],
            [2, 2, 2, 8],
            [4, 4, 2, 2],
            [3, 1, 7, 3],
        ] {
            let mut problem = small_problem();
            for (group_index, group) in problem.groups.iter_mut().enumerate() {
                group.packages = (0..sizes[group_index])
                    .rev()
                    .map(|index| NativePackage {
                        evaluation_delta: None,
                        search_values: Vec::new(),
                        id: format!("{group_index}-{index}"),
                        stat_delta: Stats::from([
                            ("ATKP".into(), (index % 3) as f64 * 0.25),
                            ("MAXHP".into(), -(index as f64) * 200.0),
                        ]),
                    })
                    .collect();
            }
            let session = NativeSearchSession::new(problem.clone()).unwrap();
            let problem = session.problem.clone();
            let clusters = &session.heap.peek().unwrap().clusters;
            let candidates = SmallBoxCandidates::new(&problem.trees, clusters);
            assert_eq!(
                candidates.as_slices(),
                box_candidate_indices(&problem.trees, clusters)
                    .each_ref()
                    .map(|items| items.as_slice())
            );
            let mut actual = SearchState {
                best_score: f64::NEG_INFINITY,
                ..SearchState::default()
            };
            let mut expected = actual.clone();
            let (mut count, mut reference_count) = (0, 0);
            enumerate_box(
                0,
                &candidates.as_slices(),
                &problem,
                &session.requirements,
                &mut [0; GROUP_COUNT],
                &Stats::new(),
                &mut actual,
                &mut count,
            )
            .unwrap();
            enumerate_box_reference(
                0,
                clusters,
                &problem,
                &session.requirements,
                &mut [0; GROUP_COUNT],
                &Stats::new(),
                &mut expected,
                &mut reference_count,
            )
            .unwrap();
            assert_eq!(count, sizes.iter().product::<usize>() as u64);
            assert_eq!(count, reference_count);
            assert_eq!(
                serde_json::to_value(actual).unwrap(),
                serde_json::to_value(expected).unwrap()
            );
        }
    }

    fn wide_problem() -> NativeProblem {
        let mut problem = small_problem();
        for (group_index, group) in problem.groups.iter_mut().enumerate() {
            group.packages = (0..8)
                .map(|package_index| NativePackage {
                    evaluation_delta: None,
                    search_values: Vec::new(),
                    id: format!("{group_index}-{package_index}"),
                    stat_delta: Stats::new(),
                })
                .collect();
        }
        problem
    }

    #[test]
    fn deferred_snapshots_preserve_frontier_counters_and_control() {
        let mut eager = NativeSearchSession::new(wide_problem()).unwrap();
        let mut deferred = NativeSearchSession::new(wide_problem()).unwrap();
        let cancel = Arc::new(AtomicBool::new(true));
        for mode in 0..3 {
            let signal = (mode == 0).then_some(&cancel);
            let deadline = (mode == 1).then(Instant::now);
            let result = eager
                .run_parallel_slice_with_control(8, 1, signal, deadline)
                .unwrap();
            deferred
                .advance_parallel_slice_with_control(8, 1, signal, deadline)
                .unwrap();
            let mut expected = serde_json::to_value(result).unwrap();
            let mut actual = serde_json::to_value(deferred.snapshot()).unwrap();
            expected["elapsedMs"] = 0.into();
            actual["elapsedMs"] = 0.into();
            assert_eq!(actual, expected);
            let mut expected = serde_json::to_value(eager.checkpoint().unwrap()).unwrap();
            let mut actual = serde_json::to_value(deferred.checkpoint().unwrap()).unwrap();
            expected["elapsed_ms"] = 0.into();
            actual["elapsed_ms"] = 0.into();
            assert_eq!(actual, expected);
        }
        while !deferred.is_complete() {
            deferred
                .advance_parallel_slice_with_control(64, 1, None, None)
                .unwrap();
        }
        while !eager.is_complete() {
            eager.run_parallel_slice(64, 1).unwrap();
        }
        let mut expected = serde_json::to_value(eager.snapshot()).unwrap();
        let mut actual = serde_json::to_value(deferred.snapshot()).unwrap();
        expected["elapsedMs"] = 0.into();
        actual["elapsedMs"] = 0.into();
        assert_eq!(actual, expected);
        deferred
            .advance_parallel_slice_with_control(64, 1, None, None)
            .unwrap();
        assert!(deferred.snapshot().exact);
    }

    #[test]
    fn persistent_pool_reuses_workers_and_rebuilds_after_checkpoint() {
        let mut session = NativeSearchSession::new(wide_problem()).unwrap();
        session.run_parallel_slice(1, 2).unwrap();
        let ids = session
            .pool
            .as_ref()
            .unwrap()
            .workers
            .iter()
            .map(|worker| worker.thread().id())
            .collect::<Vec<_>>();
        session.run_parallel_slice(1, 2).unwrap();
        assert_eq!(
            ids,
            session
                .pool
                .as_ref()
                .unwrap()
                .workers
                .iter()
                .map(|worker| worker.thread().id())
                .collect::<Vec<_>>()
        );
        let checkpoint = session.checkpoint().unwrap();
        let mut restored = NativeSearchSession::from_checkpoint(checkpoint).unwrap();
        assert!(restored.pool.is_none());
        while !restored.is_complete() {
            restored.run_parallel_slice(128, 4).unwrap();
        }
        let expected = solve_exact(&wide_problem()).unwrap();
        assert_eq!(restored.snapshot().score, expected.score);
        assert_eq!(
            restored.snapshot().best_build.unwrap().id,
            expected.best_build.unwrap().id
        );
    }

    #[test]
    fn shared_messages_cover_ragged_batches_in_input_order() {
        let problem = wide_problem();
        let mut session = NativeSearchSession::new(problem.clone()).unwrap();
        let problem = session.problem.clone();
        let root = session.heap.pop().unwrap();
        let incumbent = Arc::new(SharedIncumbent {
            score_bits: AtomicU64::new(session.state.best_score.to_bits()),
            record: Mutex::new(session.state.clone()),
        });
        for workers in [1, 2, 8, 16, 64] {
            let mut pool = NodePool::new(&problem, session.requirements, workers).unwrap();
            let mut outcomes = Vec::new();
            for count in [0, 1, 7, 31, 33, 65, 257] {
                let nodes = (0..count)
                    .map(|index| {
                        let mut node = root;
                        if index % 3 != 0 {
                            node.upper = f64::NEG_INFINITY;
                        }
                        node
                    })
                    .collect::<Vec<_>>();
                let nodes = Arc::new(nodes);
                let counters = Arc::new(ParallelCounters::default());
                pool.run(&nodes, &mut outcomes, &incumbent, &counters, None, None)
                    .unwrap();
                assert_eq!(Arc::strong_count(&nodes), 1);
                let expected = ParallelCounters::default();
                for node in nodes.iter() {
                    expand_parallel_node(
                        node,
                        &problem,
                        &session.requirements,
                        &incumbent,
                        &mut &expected,
                        None,
                        None,
                    )
                    .unwrap();
                }
                for (actual, reference) in [
                    (&counters.evaluations, &expected.evaluations),
                    (&counters.visited, &expected.visited),
                    (&counters.pruned_by_bound, &expected.pruned_by_bound),
                    (
                        &counters.pruned_by_constraint,
                        &expected.pruned_by_constraint,
                    ),
                    (&counters.enumerated, &expected.enumerated),
                    (&counters.splits, &expected.splits),
                ] {
                    assert_eq!(
                        actual.load(AtomicOrdering::Relaxed),
                        reference.load(AtomicOrdering::Relaxed)
                    );
                }
                assert_eq!(outcomes.len(), count);
                for (index, outcome) in outcomes.drain(..).enumerate() {
                    assert_eq!(
                        outcome.unwrap().unwrap().unwrap().range.len(),
                        if index % 3 == 0 { 64 } else { 0 }
                    );
                }
                // One root visit per input plus 4+16 lookahead visits for each
                // unpruned root: detects duplicated or omitted execution too.
                assert_eq!(
                    counters.visited.load(AtomicOrdering::Relaxed),
                    (count + count.div_ceil(3) * 20) as u64
                );
                let cancelled = Arc::new(AtomicBool::new(true));
                for (signal, deadline) in [(Some(&cancelled), None), (None, Some(Instant::now()))] {
                    pool.run(
                        &nodes,
                        &mut outcomes,
                        &incumbent,
                        &counters,
                        signal,
                        deadline,
                    )
                    .unwrap();
                    assert_eq!(Arc::strong_count(&nodes), 1);
                    assert_eq!(outcomes.len(), count);
                    assert!(outcomes
                        .drain(..)
                        .all(|result| result.unwrap().unwrap().is_none()));
                }
            }
        }
    }

    #[test]
    fn worker_buffers_reuse_storage_and_preserve_child_order() {
        let session = NativeSearchSession::new(wide_problem()).unwrap();
        let root = *session.heap.peek().unwrap();
        let incumbent = Arc::new(SharedIncumbent {
            score_bits: AtomicU64::new(session.state.best_score.to_bits()),
            record: Mutex::new(session.state.clone()),
        });
        let expected = expand_parallel_node(
            &root,
            &session.problem,
            &session.requirements,
            &incumbent,
            &mut LocalSearchCounters::default(),
            None,
            None,
        )
        .unwrap()
        .unwrap();
        assert_eq!(expected.len(), 64);
        let mut pool = NodePool::new(&session.problem, session.requirements, 1).unwrap();
        let nodes = Arc::new(vec![root; 7]);
        let counters = Arc::new(ParallelCounters::default());
        let mut outcomes = Vec::new();
        let mut storage = None;
        for _ in 0..3 {
            pool.run(&nodes, &mut outcomes, &incumbent, &counters, None, None)
                .unwrap();
            assert_eq!(pool.buffers.len(), 1);
            let buffer = &pool.buffers[0];
            assert!(buffer.outcomes.is_empty());
            let current = (buffer.children.as_ptr(), buffer.outcomes.as_ptr());
            if let Some(previous) = storage {
                assert_eq!(current, previous);
            }
            storage = Some(current);
            for (index, outcome) in outcomes.drain(..).enumerate() {
                let children = outcome.unwrap().unwrap().unwrap();
                assert_eq!(children.buffer, 0);
                assert_eq!(children.range, index * 64..(index + 1) * 64);
                assert!(buffer.children[children.range].iter().eq(expected.iter()));
            }
        }
    }

    #[test]
    fn interrupted_expansion_rolls_back_only_current_buffer_suffix() {
        struct StopAfter<'a> {
            cancel: &'a AtomicBool,
            evaluations: usize,
        }
        impl SearchCounters for StopAfter<'_> {
            fn count_evaluations(&mut self) {
                self.evaluations += 1;
                if self.evaluations == 7 {
                    self.cancel.store(true, AtomicOrdering::Release);
                }
            }
            fn count_visited(&mut self) {}
            fn count_pruned_by_bound(&mut self) {}
            fn count_pruned_by_constraint(&mut self) {}
            fn count_enumerated(&mut self) {}
            fn count_splits(&mut self) {}
        }
        let session = NativeSearchSession::new(wide_problem()).unwrap();
        let root = *session.heap.peek().unwrap();
        let incumbent = SharedIncumbent {
            score_bits: AtomicU64::new(session.state.best_score.to_bits()),
            record: Mutex::new(session.state.clone()),
        };
        let cancel = AtomicBool::new(false);
        let mut counters = StopAfter {
            cancel: &cancel,
            evaluations: 0,
        };
        let mut children = vec![root];
        assert!(!expand_parallel_node_into(
            &root,
            &session.problem,
            &session.requirements,
            &incumbent,
            &mut counters,
            Some(&cancel),
            None,
            &mut children
        )
        .unwrap());
        assert_eq!(counters.evaluations, 7);
        assert_eq!(children.len(), 1);
        assert!(children[0] == root);
        // Four descendants were appended before cancellation; the retained
        // capacity proves this exercised rollback after actual output growth.
        assert!(children.capacity() > 1);
    }

    #[test]
    fn cancelled_batches_reuse_buffers_and_preserve_checkpoint() {
        let mut session = NativeSearchSession::new(wide_problem()).unwrap();
        let before = session.checkpoint().unwrap();
        let cancel = Arc::new(AtomicBool::new(true));
        session
            .advance_parallel_slice_with_control(64, 2, Some(&cancel), None)
            .unwrap();
        let nodes_ptr = session.batch_nodes.as_ptr();
        let results_ptr = session.batch_outcomes.as_ptr();
        for workers in [2, 8, 1, 16, 64, 2] {
            session
                .advance_parallel_slice_with_control(64, workers, Some(&cancel), None)
                .unwrap();
            assert!(session.batch_nodes.is_empty());
            assert!(session.batch_outcomes.is_empty());
            assert_eq!(session.batch_nodes.as_ptr(), nodes_ptr);
            assert_eq!(session.batch_outcomes.as_ptr(), results_ptr);
            let after = session.checkpoint().unwrap();
            assert_eq!(
                serde_json::to_value(&after.frontier).unwrap(),
                serde_json::to_value(&before.frontier).unwrap()
            );
            assert_eq!(
                serde_json::to_value(&after.state).unwrap(),
                serde_json::to_value(&before.state).unwrap()
            );
        }
    }

    #[test]
    fn worker_errors_preserve_parent_frontier() {
        let mut session = NativeSearchSession::new(wide_problem()).unwrap();
        let ready = session.ready_work_count();
        session.problem.base_context = PreparedContext::from(Value::Null);
        assert!(session.run_parallel_slice(8, 2).is_err());
        assert_eq!(session.ready_work_count(), ready);
        assert!(!session.snapshot().exact);
    }

    #[test]
    fn selective_lookahead_covers_equal_bound_space_without_duplicates() {
        let problem = wide_problem();
        let mut session = NativeSearchSession::new(problem.clone()).unwrap();
        let problem = session.problem.clone();
        let root = session.heap.pop().unwrap();
        let incumbent = SharedIncumbent {
            score_bits: AtomicU64::new(session.state.best_score.to_bits()),
            record: Mutex::new(session.state.clone()),
        };
        let children = expand_parallel_node(
            &root,
            &problem,
            &session.requirements,
            &incumbent,
            &mut &ParallelCounters::default(),
            None,
            None,
        )
        .unwrap()
        .unwrap();
        assert_eq!(children.len(), 64);
        let mut covered = HashSet::new();
        for child in children {
            assert!(child.upper >= session.state.best_score);
            let indices: [Vec<usize>; 4] = std::array::from_fn(|i| {
                let mut list = Vec::new();
                cluster_indices(&problem.trees, child.clusters[i], &mut list);
                list
            });
            for a in &indices[0] {
                for b in &indices[1] {
                    for c in &indices[2] {
                        for d in &indices[3] {
                            assert!(covered.insert([*a, *b, *c, *d]));
                        }
                    }
                }
            }
        }
        assert_eq!(covered.len(), 8_usize.pow(4));
    }

    #[test]
    fn lookahead_window_depth_and_small_box_boundaries() {
        let mut session = NativeSearchSession::new(wide_problem()).unwrap();
        let mut root = session.heap.pop().unwrap();
        for best in [-100.0_f64, 0.0, 100.0] {
            root.upper = best + best.abs() * LOOKAHEAD_RELATIVE_GAP;
            assert!(should_look_ahead(&session.problem.trees, &root, best, 0));
            assert!(should_look_ahead(&session.problem.trees, &root, best, 1));
            assert!(!should_look_ahead(&session.problem.trees, &root, best, 2));
            root.upper += 0.0001;
            assert!(!should_look_ahead(&session.problem.trees, &root, best, 0));
        }
        for best in [f64::INFINITY, f64::NEG_INFINITY, f64::NAN] {
            assert!(!should_look_ahead(&session.problem.trees, &root, best, 0));
        }
        let mut small = NativeSearchSession::new(small_problem()).unwrap();
        let node = small.heap.pop().unwrap();
        assert!(!should_look_ahead(
            &small.problem.trees,
            &node,
            node.upper,
            0
        ));
    }

    #[test]
    fn constraint_lookahead_removes_only_infeasible_space_and_keeps_upper() {
        let mut problem = wide_problem();
        for group in &mut problem.groups {
            for (i, package) in group.packages.iter_mut().enumerate() {
                package
                    .stat_delta
                    .insert("MAXHP".into(), -(i as f64) * 1200.0);
            }
        }
        let mut session = NativeSearchSession::new(problem.clone()).unwrap();
        let problem = session.problem.clone();
        let root = session.heap.pop().unwrap();
        let incumbent = SharedIncumbent {
            score_bits: AtomicU64::new(f64::NEG_INFINITY.to_bits()),
            record: Mutex::new(SearchState {
                best_score: f64::NEG_INFINITY,
                ..SearchState::default()
            }),
        };
        let mut coverage = Vec::new();
        for pressure in [false, true] {
            let mut counters = LocalSearchCounters {
                pruned_by_constraint: if pressure { 10000 } else { 0 },
                evaluations: 1000,
                ..LocalSearchCounters::default()
            };
            let children = expand_parallel_node(
                &root,
                &problem,
                &session.requirements,
                &incumbent,
                &mut counters,
                None,
                None,
            )
            .unwrap()
            .unwrap();
            let mut covered = HashSet::new();
            for child in children {
                let indices = box_candidate_indices(&problem.trees, &child.clusters);
                for &a in &indices[0] {
                    for &b in &indices[1] {
                        for &c in &indices[2] {
                            for &d in &indices[3] {
                                let selected = [a, b, c, d];
                                assert!(covered.insert(selected));
                                let stats = selection_stats(&problem, &selected);
                                if let Some(score) = evaluate_feasible_summary(
                                    &problem.base_context,
                                    &stats,
                                    |i, v| session.requirements.accepts_value(i, v),
                                )
                                .unwrap()
                                {
                                    assert!(child.upper >= score.optimization_damage_factor);
                                }
                            }
                        }
                    }
                }
            }
            coverage.push(covered);
        }
        assert!(coverage[1].len() < coverage[0].len());
        for selected in coverage[0].difference(&coverage[1]) {
            let stats = selection_stats(&problem, selected);
            assert!(
                evaluate_feasible_summary(&problem.base_context, &stats, |i, v| session
                    .requirements
                    .accepts_value(i, v))
                .unwrap()
                .is_none()
            );
        }
        let cancelled = AtomicBool::new(true);
        assert!(expand_parallel_node(
            &root,
            &problem,
            &session.requirements,
            &incumbent,
            &mut LocalSearchCounters::default(),
            Some(&cancelled),
            None
        )
        .unwrap()
        .is_none());
    }

    #[test]
    fn solves_small_problem_exactly_with_lexical_tie() {
        let problem = small_problem();
        let result = solve_exact(&problem).unwrap();
        assert!(result.exact);
        assert_eq!(result.best_build.unwrap().id, "a||b||c||d");
    }

    #[test]
    fn candidate_coordinates_only_order_trees_and_preserve_oracle_resume() {
        let mut problem = joint_problem();
        let oracle = solve_exact(&problem).unwrap();
        problem.metadata.search_keys = vec!["@CRIT:0".into(), "@ASPD:1".into()];
        // Deliberately unrelated to damage: these values can only order splits.
        for group in &mut problem.groups {
            for (index, package) in group.packages.iter_mut().enumerate() {
                package.search_values = vec![(index % 3) as f64, -(index as f64)];
            }
        }
        let raw = serde_json::to_value(&problem.groups).unwrap();
        for reverse in [false, true] {
            if reverse {
                for group in &mut problem.groups {
                    group.packages.reverse();
                }
            }
            for threads in [1, 2, 8, 64] {
                let mut session = NativeSearchSession::new(problem.clone()).unwrap();
                assert_eq!(
                    session.problem.trees.ordering_keys,
                    problem.metadata.search_keys
                );
                session.run_parallel_slice(1, threads).unwrap();
                let wire = serde_json::to_string(&session.checkpoint().unwrap()).unwrap();
                let mut restored =
                    NativeSearchSession::from_checkpoint(serde_json::from_str(&wire).unwrap())
                        .unwrap();
                assert_eq!(
                    restored.problem.trees.ordering_keys,
                    problem.metadata.search_keys
                );
                while !restored.is_complete() {
                    let result = restored.run_parallel_slice(8, threads).unwrap();
                    assert!(result.upper_bound.unwrap() >= oracle.score.unwrap());
                }
                let result = restored.snapshot();
                assert_eq!(result.score, oracle.score);
                assert_eq!(
                    serde_json::to_value(result.best_build).unwrap(),
                    serde_json::to_value(&oracle.best_build).unwrap()
                );
            }
        }
        for group in &mut problem.groups {
            group.packages.reverse();
        }
        assert_eq!(serde_json::to_value(&problem.groups).unwrap(), raw);
        for invalid in [Vec::new(), vec![f64::NAN, 0.0]] {
            problem.groups[0].packages[0].search_values = invalid;
            let session = NativeSearchSession::new(problem.clone()).unwrap();
            assert!(session.problem.trees.ordering_keys.is_empty());
            let result = solve_exact(&problem).unwrap();
            assert_eq!(result.score, oracle.score);
            assert_eq!(
                result.best_build.unwrap().id,
                oracle.best_build.as_ref().unwrap().id
            );
        }
    }

    #[test]
    fn envelope_preserves_forced_penalties_and_missing_coordinate_zero() {
        let packages: Vec<NativePackage> = serde_json::from_value(json!([
            {"id":"a","statDelta":{"ATKP":-10,"MAXMP":-200}},
            {"id":"b","statDelta":{"ATKP":-5}},
            {"id":"c","statDelta":{"ATKP":-5,"MAXMP":-100}}
        ]))
        .unwrap();
        let keys = vec!["ATKP".into(), "MAXMP".into()];
        let envelope = group_envelope(&packages, &[0, 1, 2], &keys);
        assert_eq!(envelope.get("ATKP"), Some(&-5.0));
        assert_eq!(envelope.get("MAXMP").copied().unwrap_or(0.0), 0.0);
        assert_eq!(
            group_envelope(&packages, &[0], &keys),
            packages[0].stat_delta
        );
        assert!(group_envelope(&packages, &[], &keys).is_empty());
    }

    #[test]
    fn bound_merge_preserves_group_order_and_sparse_penalties() {
        let mut problem = small_problem();
        for (group, atk) in problem.groups.iter_mut().zip([1e16, -1e16, 1.0, 0.0]) {
            group.packages = vec![NativePackage {
                evaluation_delta: None,
                search_values: Vec::new(),
                id: group._id.clone(),
                stat_delta: Stats::from([("ATK".into(), atk)]),
            }];
        }
        problem.groups[2].packages[0]
            .stat_delta
            .insert("MAXMP".into(), -100.0);
        let keys = vec!["ATK".into(), "MAXMP".into()];
        let mut arena = TreeArena::default();
        let trees = std::array::from_fn(|index| {
            build_tree(
                &mut arena,
                &problem.groups[index].packages,
                vec![0],
                &keys,
                &BTreeMap::new(),
                &problem.base_context,
                "r".into(),
            )
        });
        // ATK order matters: (1e16 + -1e16) + 1 is 1, not 0.
        let stats = box_stats(&arena, &trees);
        assert_eq!(stats["ATK"], 1.0);
        assert_eq!(stats["MAXMP"], -100.0);
        assert_eq!(
            add_stats(Stats::new(), &Stats::from([("ATK".into(), -0.0)]))["ATK"].to_bits(),
            0.0_f64.to_bits()
        );
    }

    #[test]
    fn numeric_path_order_matches_lexical_heap_order() {
        fn old_cmp(trees: &TreeArena, left: &WorkItem, right: &WorkItem) -> Ordering {
            left.upper.total_cmp(&right.upper).then_with(|| {
                for (a, b) in left.clusters.iter().zip(&right.clusters) {
                    let order = trees[*b].path.cmp(&trees[*a].path);
                    if order != Ordering::Equal {
                        return order;
                    }
                }
                Ordering::Equal
            })
        }
        // Include uneven trees, prefix/descendant pairs and empty/single roots.
        for count in 0..=65 {
            let packages = (0..count)
                .map(|index| NativePackage {
                    evaluation_delta: None,
                    search_values: Vec::new(),
                    id: index.to_string(),
                    stat_delta: Stats::new(),
                })
                .collect::<Vec<_>>();
            let mut arena = TreeArena::default();
            let root = build_tree(
                &mut arena,
                &packages,
                (0..count).collect(),
                &[],
                &BTreeMap::new(),
                &serde_json::json!({}),
                "r".into(),
            );
            let nodes = (0..arena.nodes.len())
                .map(|id| NodeId(id as u32))
                .collect::<Vec<_>>();
            assert_eq!(root, NodeId(0));
            for (rank, node) in nodes.iter().enumerate() {
                assert_eq!(node.0 as usize, rank);
                for other in &nodes {
                    assert_eq!(node.cmp(other), arena[*node].path.cmp(&arena[*other].path));
                }
            }
            let old_cmp = |a: &WorkItem, b: &WorkItem| old_cmp(&arena, a, b);
            let uppers = [
                0.0,
                -0.0,
                1.0,
                1.0,
                f64::INFINITY,
                f64::NEG_INFINITY,
                f64::NAN,
            ];
            let boxes = (0..128)
                .map(|index| WorkItem {
                    upper: uppers[index % uppers.len()],
                    clusters: std::array::from_fn(|group| {
                        nodes[(index * (group * 2 + 1) + group) % nodes.len()]
                    }),
                })
                .collect::<Vec<_>>();
            for a in &boxes {
                for b in &boxes {
                    assert_eq!(a.cmp(b), old_cmp(a, b));
                    assert_eq!(a == b, old_cmp(a, b) == Ordering::Equal);
                }
            }
            let mut expected = boxes.clone();
            expected.sort_by(old_cmp);
            let mut frontier = WorkHeap::new();
            let mut reference = BinaryHeap::new();
            // Mixed insertion/removal covers partial child groups, duplicates,
            // equal upper bounds, signed zero and the existing total NaN order.
            for (index, item) in boxes.iter().enumerate() {
                frontier.push(*item);
                reference.push(*item);
                if index % 3 == 0 {
                    assert_eq!(
                        old_cmp(&frontier.pop().unwrap(), &reference.pop().unwrap()),
                        Ordering::Equal
                    );
                }
                assert_eq!(frontier.len(), reference.len());
            }
            frontier.extend(boxes.iter().cloned());
            reference.extend(boxes.iter().cloned());
            while let Some(item) = reference.pop() {
                assert_eq!(old_cmp(frontier.peek().unwrap(), &item), Ordering::Equal);
                assert_eq!(old_cmp(&frontier.pop().unwrap(), &item), Ordering::Equal);
            }
            assert!(frontier.is_empty());
            assert!(frontier.pop().is_none());
            assert!(frontier.peek().is_none());
            frontier.push(boxes[0]);
            assert_eq!(
                old_cmp(&frontier.pop().unwrap(), &boxes[0]),
                Ordering::Equal
            );
            let mut heap = BinaryHeap::from(boxes);
            while let Some(actual) = heap.pop() {
                assert_eq!(old_cmp(&actual, &expected.pop().unwrap()), Ordering::Equal);
            }
        }
    }

    #[test]
    fn lazy_children_preserve_order_and_cover_each_binary_split_once() {
        // All 16 leaf/branch patterns across the four equipment groups.
        for mask in 0_u32..16 {
            let mut problem = small_problem();
            for (index, group) in problem.groups.iter_mut().enumerate() {
                group.packages = (0..if mask & (1 << index) != 0 { 2 } else { 1 })
                    .map(|value| NativePackage {
                        evaluation_delta: None,
                        search_values: Vec::new(),
                        id: value.to_string(),
                        stat_delta: Stats::new(),
                    })
                    .collect();
            }
            let mut arena = TreeArena::default();
            let roots = std::array::from_fn(|index| {
                build_tree(
                    &mut arena,
                    &problem.groups[index].packages,
                    (0..problem.groups[index].packages.len()).collect(),
                    &[],
                    &BTreeMap::new(),
                    &problem.base_context,
                    "r".into(),
                )
            });
            let selected: Vec<_> = (0..GROUP_COUNT)
                .filter(|index| mask & (1 << index) != 0)
                .take(2)
                .collect();
            let count = if selected.is_empty() {
                0
            } else {
                1 << selected.len()
            };
            let mut children = ChildBoxes::new(&arena, &roots);
            assert_eq!(children.len(), count);
            let mut covered = 0;
            for ordinal in 0..count {
                let child = children.next().unwrap();
                assert_eq!(children.len(), count - ordinal - 1);
                covered += child
                    .iter()
                    .map(|node| arena[*node].size)
                    .product::<usize>();
                for index in 0..GROUP_COUNT {
                    let expected = match selected.iter().position(|split| *split == index) {
                        None => &roots[index],
                        Some(position) => {
                            let right = (ordinal >> (selected.len() - position - 1)) & 1 != 0;
                            if right {
                                arena[roots[index]].right.as_ref().unwrap()
                            } else {
                                arena[roots[index]].left.as_ref().unwrap()
                            }
                        }
                    };
                    assert_eq!(&child[index], expected);
                }
            }
            assert!(children.next().is_none());
            assert!(children.next().is_none());
            if count > 0 {
                assert_eq!(
                    covered,
                    roots
                        .iter()
                        .map(|node| arena[*node].size)
                        .product::<usize>()
                );
            }
        }
    }

    #[test]
    fn old_bound_policy_checkpoint_is_rejected() {
        let session = NativeSearchSession::new(small_problem()).unwrap();
        for version in 4..=20 {
            let mut checkpoint = session.checkpoint().unwrap();
            checkpoint.schema = format!("toram.crysta-native-search-checkpoint.v{version}");
            assert!(NativeSearchSession::from_checkpoint(checkpoint.clone()).is_err());
            checkpoint.schema = format!("toram.d4-native-search-checkpoint.v{version}");
            assert!(NativeSearchSession::from_checkpoint(checkpoint).is_err());
        }
    }

    #[test]
    fn snapshot_upper_includes_incumbent_before_and_after_restore() {
        let mut session = NativeSearchSession::new(small_problem()).unwrap();
        let mut node = session.heap.pop().unwrap();
        node.upper = session.state.best_score - 1.0;
        session.heap.push(node);
        let result = session.snapshot();
        assert_eq!(result.status, "bounded");
        assert_eq!(result.upper_bound, result.score);
        let restored = NativeSearchSession::from_checkpoint(session.checkpoint().unwrap()).unwrap();
        assert_eq!(restored.snapshot().upper_bound, result.score);
    }

    #[test]
    fn partial_utility_pruning_matches_full_enumeration_with_penalties() {
        let mut problem = small_problem();
        for group in &mut problem.groups {
            group.packages = (0..4)
                .map(|i| NativePackage {
                    evaluation_delta: None,
                    search_values: Vec::new(),
                    id: format!("{}-{i}", group._id),
                    stat_delta: Stats::from([
                        ("MAXHP".into(), -6000.0 * i as f64),
                        ("ATKP".into(), 20.0 * i as f64),
                    ]),
                })
                .collect();
        }
        let session = NativeSearchSession::new(problem.clone()).unwrap();
        let problem = session.problem.clone();
        let root = session.heap.peek().unwrap();
        let candidates = box_candidate_indices(&problem.trees, &root.clusters);
        let suffix: [Stats; GROUP_COUNT] = std::array::from_fn(|start| {
            root.clusters[start..]
                .iter()
                .fold(Stats::new(), |sum, node| {
                    add_stats(sum, &problem.trees[*node].envelope)
                })
        });
        let mut results = Vec::new();
        let mut counts = Vec::new();
        for pruning in [false, true] {
            let incumbent = SharedIncumbent {
                score_bits: AtomicU64::new(f64::NEG_INFINITY.to_bits()),
                record: Mutex::new(SearchState {
                    best_score: f64::NEG_INFINITY,
                    ..SearchState::default()
                }),
            };
            let mut counters = LocalSearchCounters::default();
            assert!(enumerate_box_parallel(
                0,
                &candidates.each_ref().map(|items| items.as_slice()),
                pruning.then_some(&suffix),
                &problem,
                &session.requirements,
                &incumbent,
                &mut counters,
                None,
                None,
                &mut [0; GROUP_COUNT],
                &Stats::new()
            )
            .unwrap());
            let result = incumbent.record.lock().unwrap();
            results.push((result.best_score, result.best_id.clone()));
            counts.push(counters.enumerated);
        }
        assert_eq!(results[0], results[1]);
        assert_eq!(counts[0], 256);
        assert!(counts[1] < counts[0]);
    }

    #[test]
    fn resumable_session_preserves_frontier_and_exact_tie() {
        let uninterrupted = solve_exact(&small_problem()).unwrap();
        let mut session = NativeSearchSession::new(small_problem()).unwrap();
        let first = session.run_slice(1).unwrap();
        assert!(matches!(first.status.as_str(), "bounded" | "exact"));
        if !first.exact {
            assert!(session.ready_work_count() > 0);
            assert!(first.upper_bound.unwrap() >= first.score.unwrap());
        }
        while !session.is_complete() {
            session.run_slice(1).unwrap();
        }
        let resumed = session.run_slice(1).unwrap();
        assert!(resumed.exact);
        assert_eq!(resumed.score, uninterrupted.score);
        assert_eq!(
            resumed.best_build.unwrap().id,
            uninterrupted.best_build.unwrap().id
        );
    }

    #[test]
    fn serialized_checkpoint_resumes_without_frontier_loss_or_duplication() {
        let uninterrupted = solve_exact(&small_problem()).unwrap();
        let mut session = NativeSearchSession::new(small_problem()).unwrap();
        let bounded = session.run_slice(1).unwrap();
        assert!(matches!(bounded.status.as_str(), "bounded" | "exact"));
        let checkpoint = session.checkpoint().unwrap();
        let json = serde_json::to_string(&checkpoint).unwrap();
        let restored = serde_json::from_str(&json).unwrap();
        let mut resumed = NativeSearchSession::from_checkpoint(restored).unwrap();
        while !resumed.is_complete() {
            resumed.run_slice(1).unwrap();
        }
        let result = resumed.run_slice(1).unwrap();
        assert!(result.exact);
        assert_eq!(result.score, uninterrupted.score);
        assert_eq!(
            result.best_build.unwrap().id,
            uninterrupted.best_build.unwrap().id
        );
    }

    #[test]
    fn session_elapsed_excludes_time_parked_between_resumes() {
        let mut session = NativeSearchSession::new(wide_problem()).unwrap();
        let first = session.run_slice(1).unwrap();
        std::thread::sleep(Duration::from_millis(15));
        let parked = session.snapshot();
        assert_eq!(parked.elapsed_ms, first.elapsed_ms);
        let resumed = session.run_slice(1).unwrap();
        assert!(resumed.elapsed_ms >= parked.elapsed_ms);
        assert!(resumed.elapsed_ms < parked.elapsed_ms + 1_000);
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

    #[test]
    fn shared_parallel_frontier_drains_descendants_without_losing_exact_tie() {
        let problem = wide_problem();
        let expected = solve_exact(&problem).unwrap();
        let result = solve_exact_parallel(&problem, 2).unwrap();
        assert!(result.result.exact);
        assert_eq!(result.result.score, expected.score);
        assert_eq!(
            result.result.best_build.unwrap().id,
            expected.best_build.unwrap().id
        );
        assert!(result.scheduled_shards > 0);
        assert!(result.result.visited_nodes > result.scheduled_shards as u64);
        assert!(result.scheduler.split_count > 0);
        assert_eq!(
            result.scheduler.worker_busy_micros.len(),
            result.threads_used
        );
    }

    #[test]
    fn parallel_session_slices_resume_to_the_serial_exact_tie() {
        let problem = wide_problem();
        let expected = solve_exact(&problem).unwrap();
        for threads in [1, 2, 8, 64] {
            let mut session = NativeSearchSession::new(problem.clone()).unwrap();
            while !session.is_complete() {
                session.run_parallel_slice(8, threads).unwrap();
            }
            let result = session.snapshot();
            assert!(result.exact, "{threads} threads must finish exactly");
            assert_eq!(result.score, expected.score);
            assert_eq!(
                result.best_build.unwrap().id,
                expected.best_build.clone().unwrap().id
            );
        }
    }

    #[test]
    fn bounded_parallel_slices_keep_a_safe_upper_and_resume_after_input_reversal() {
        let original = wide_problem();
        let expected = solve_exact(&original).unwrap();
        let expected_score = expected.score.expect("wide oracle must be feasible");
        let expected_id = expected
            .best_build
            .expect("wide oracle must have a build")
            .id;
        let mut reversed = original.clone();
        for group in &mut reversed.groups {
            group.packages.reverse();
        }
        for threads in [1, 2, 4, 8, 16, 64] {
            let mut session = NativeSearchSession::new(reversed.clone()).unwrap();
            let bounded = session.run_parallel_slice(1, threads).unwrap();
            if !bounded.exact {
                assert!(
                    bounded
                        .upper_bound
                        .expect("bounded slice must certify an upper")
                        >= expected_score,
                    "{threads} threads must never understate an unexplored optimum"
                );
                assert!(session.ready_work_count() > 0);
            }
            while !session.is_complete() {
                session.run_parallel_slice(1, threads).unwrap();
            }
            let resumed = session.snapshot();
            assert!(
                resumed.exact,
                "{threads} threads must resume to exact completion"
            );
            assert_eq!(resumed.score, Some(expected_score));
            assert_eq!(resumed.best_build.expect("exact build").id, expected_id);
        }
    }

    #[test]
    fn controlled_parallel_slice_requeues_cancelled_or_deadline_work() {
        for (cancelled, deadline) in [(true, None), (false, Some(Instant::now()))] {
            let mut session = NativeSearchSession::new(wide_problem()).unwrap();
            let ready_before = session.ready_work_count();
            let cancel = Arc::new(AtomicBool::new(cancelled));
            let result = session
                .run_parallel_slice_with_control(8, 8, Some(&cancel), deadline)
                .unwrap();
            assert!(!result.exact);
            assert_eq!(session.ready_work_count(), ready_before);
        }
    }
    #[test]
    fn supply_budget_fallback_preserves_exhaustive_search_and_json_resume() {
        let mut problem = wide_problem();
        for group in &mut problem.groups {
            for package in &mut group.packages {
                package.stat_delta.insert("CSPD".into(), 1e13);
            }
        }
        let expected = solve_exact(&problem).unwrap();
        let mut session = NativeSearchSession::new(problem).unwrap();
        assert!(session
            .problem
            .trees
            .supply
            .as_ref()
            .unwrap()
            .plan
            .is_none());
        session.run_parallel_slice(1, 4).unwrap();
        let checkpoint =
            serde_json::from_str(&serde_json::to_string(&session.checkpoint().unwrap()).unwrap())
                .unwrap();
        let mut restored = NativeSearchSession::from_checkpoint(checkpoint).unwrap();
        while !restored.is_complete() {
            restored.run_parallel_slice(64, 4).unwrap();
        }
        assert_eq!(restored.snapshot().score, expected.score);
        assert_eq!(
            restored.snapshot().best_build.unwrap().id,
            expected.best_build.unwrap().id
        );
    }

    #[test]
    fn all_supply_planes_cover_future_options_and_nonlinear_boundaries() {
        use crate::crysta_native_evaluator::joint_supply::SupplyPlan;
        use crate::crysta_native_evaluator::{candidate_cast_metrics, joint_supply::METRICS};
        for case in 0..37 {
            let mut problem = small_problem();
            let mut base = serde_json::to_value(&problem.base_context).unwrap();
            for (key, value) in [
                ("strBase", 327.0),
                ("dexBase", 400.0),
                ("agiBase", 300.0),
                ("intBase", 320.0),
                ("vitBase", 50.0),
                ("skillMult", 2.1),
                ("wpnAtk", 650.0),
                ("bossDef", 2200.0),
                ("bossMdef", 3000.0),
                ("critF", 15.0),
                ("aspdF", 100.0),
                ("maxMpF", 600.0),
                ("amprF", 12.0),
            ] {
                base[key] = json!(value);
            }
            base["mainType"] = json!(
                [
                    "한손검",
                    "양손검",
                    "활",
                    "자동활",
                    "지팡이",
                    "마도구",
                    "권갑",
                    "선풍창",
                    "발도검",
                    "맨손"
                ][case % 10]
            );
            base["atkType"] = json!(if case % 2 == 0 { "PHYS" } else { "MAG" });
            base["attackPowerMode"] =
                json!(["default", "sum", "higher", "atk", "wizardBlend"][case % 5]);
            base["subType"] = json!(["없음", "한손검(듀얼소드)", "화살", "마도구"][case % 4]);
            base["subAtk"] = json!(450);
            base["subStab"] = json!(80);
            base["subRefine"] = json!(12);
            base["dualBringerActive"] = json!(case < 24);
            base["dualBringerLevel"] = json!(10);
            base["targetWeakened"] = json!(true);
            base["spellBurstLevel"] = json!(10);
            base["chkIsUnsheathe"] = json!(case % 3 == 0);
            base["conversionLevel"] = json!(7);
            base["activeBuildConversions"] = if case % 4 == 0 {
                json!([{"conversion":"unsheatheToAtk","value":0.7}])
            } else {
                json!([])
            };
            base["useHigherRangeDamage"] = json!(case % 3 == 1);
            base["halfMdefIgnored"] = json!(case % 5 == 1);
            base["ignoreDefense"] = json!(case % 5 == 2);
            base["ignoreMdef"] = json!(case % 5 == 3);
            base["criticalChanceMultiplier"] = json!(if case % 7 == 0 { -0.5 } else { 1.2 });
            base["cdmgF"] = json!(if case % 6 == 0 { 220.0 } else { 15.0 });
            base["skillStats"] = json!([{"stat":"totalDEX","target":"const","ratio":0.3},{"stat":"totalAGI","target":"mult","ratio":if case%6==1 {-0.001}else{0.001}}]);
            base["normalAttackAmprProfile"] = json!({"passive":[{"percent":12,"flat":3}],"activeCandidates":[{"id":"a","multiplier":1.1},{"id":"b","multiplier":if case%6==2 {-0.5}else{0.9},"flat":40}]});
            if case == 22 {
                base["aspdF"] = json!(-9000.25);
                base["maxHpF"] = json!(-20.75);
            }
            if case == 23 {
                base["crtBase"] = json!(-102);
                base["bossPhysResist"] = json!(130);
            }
            if case == 36 {
                base["wpnAtk"] = json!(10000);
                base["cdmgF"] = json!(2000);
            }
            problem.base_context = PreparedContext::from(base);
            problem.scenario_snapshot = json!({"requirements":{"maxHp":1000,"maxMp":100,"amprBeforeDual":10,"normalAttackCrit":10,"aspd":100}});
            for (g, group) in problem.groups.iter_mut().enumerate() {
                group.packages = (0..3)
                    .map(|p| {
                        let mut stats = Stats::new();
                        for (i, key) in crate::crysta_native_evaluator::NATIVE_STAT_KEYS
                            .iter()
                            .enumerate()
                        {
                            let n = ((i * 17 + p * 13 + g * 7 + case * 3) % 31) as f64 - 12.0;
                            let value = if case == 36 && *key == "STR" {
                                -600.0
                            } else if *key == "ELEM_AWAKENING" || *key == "MAGIC_ELEMENT" {
                                if case < 24 && p == (g + case) % 3 {
                                    1.0
                                } else {
                                    0.0
                                }
                            } else if key.starts_with("ATK_UP_") || key.starts_with("MATK_UP_") {
                                if case < 24 {
                                    n / 10.0
                                } else {
                                    0.0
                                }
                            } else if *key == "MAXHP"
                                || *key == "MAXMP"
                                || *key == "ASPD"
                                || *key == "CSPD"
                            {
                                n * 25.0 + 0.25
                            } else if case == 21 && key.ends_with('P') {
                                -40.0 + n
                            } else {
                                n + 0.125
                            };
                            stats.insert((*key).into(), value);
                        }
                        NativePackage {
                            id: format!("{g}-{p}"),
                            stat_delta: stats,
                            evaluation_delta: None,
                            search_values: Vec::new(),
                        }
                    })
                    .collect();
            }
            problem.prepare_evaluation_stats();
            let roots = problem.prepare_trees().unwrap();
            let supply = problem.trees.supply.as_ref().unwrap();
            assert!(supply.plan.is_some());
            let groups: Vec<Vec<_>> = problem
                .groups
                .iter()
                .map(|g| {
                    g.packages
                        .iter()
                        .map(NativePackage::evaluation_stats)
                        .collect()
                })
                .collect();
            let plan = SupplyPlan::prepare(&problem.base_context, &groups).unwrap();
            let requirements = Requirements::new(&problem.scenario_snapshot["requirements"]);
            let ancestors: [Vec<Vec<NodeId>>; 4] = std::array::from_fn(|g| {
                let end = roots
                    .get(g + 1)
                    .map_or(problem.trees.nodes.len(), |n| n.0 as usize);
                (0..3)
                    .map(|selected| {
                        (roots[g].0 as usize..end)
                            .map(|n| NodeId(n as u32))
                            .filter(|n| {
                                let mut indices = Vec::new();
                                cluster_indices(&problem.trees, *n, &mut indices);
                                indices.contains(&selected)
                            })
                            .collect()
                    })
                    .collect()
            });
            for a in 0..3 {
                for b in 0..3 {
                    for c in 0..3 {
                        for d in 0..3 {
                            let selected = [a, b, c, d];
                            let stats = selection_evaluation_stats(&problem, &selected);
                            let raw =
                                evaluate_summary_from_map(&problem.base_context, &stats).unwrap();
                            let goals = utility_values(&problem.base_context, &stats).unwrap();
                            let cast = candidate_cast_metrics(&problem.base_context, &stats);
                            let actual = [
                                raw.optimization_damage_factor,
                                goals[0],
                                goals[1],
                                goals[2],
                                goals[3],
                                goals[4],
                                cast[0],
                                cast[1],
                            ];
                            for (i, actual_value) in actual.iter().enumerate().take(METRICS) {
                                let form = &plan.upper[i];
                                let upper = form.constant
                                    + form.error
                                    + (0..4)
                                        .map(|g| {
                                            form.package(
                                                problem.groups[g].packages[selected[g]]
                                                    .evaluation_stats(),
                                            )
                                        })
                                        .sum::<f64>();
                                assert!(upper>=actual_value-1e-7,"case={case} selected={selected:?} metric={i}: plane={upper} actual={actual_value}");
                                if i < SUPPLY_METRICS {
                                    assert!(
                                        supply.metric(&roots, i) >= actual[i] - 1e-7,
                                        "root case={case} metric={i}"
                                    );
                                }
                            }
                            for aa in &ancestors[0][a] {
                                for bb in &ancestors[1][b] {
                                    for cc in &ancestors[2][c] {
                                        for dd in &ancestors[3][d] {
                                            let box_ = [*aa, *bb, *cc, *dd];
                                            for (i, actual_value) in
                                                actual.iter().enumerate().take(SUPPLY_METRICS)
                                            {
                                                assert!(
                                                    supply.metric(&box_, i) >= actual_value - 1e-7,
                                                    "ancestor case={case} metric={i}"
                                                );
                                            }
                                            if (0..5)
                                                .all(|i| requirements.accepts_value(i, goals[i]))
                                            {
                                                assert!(
                                                    problem.trees.joint_utilities_possible(&box_),
                                                    "joint pruned feasible case={case}"
                                                );
                                                let bound = evaluate_box(
                                                    &problem,
                                                    &box_,
                                                    Some(&requirements),
                                                )
                                                .unwrap()
                                                .expect("feasible ancestor");
                                                assert!(
                                                    bound.optimization_damage_factor
                                                        >= actual[0] - 1e-7,
                                                    "combined ancestor case={case}"
                                                );
                                            }
                                        }
                                    }
                                }
                            }
                            if (0..5).all(|i| requirements.accepts_value(i, goals[i])) {
                                assert!(
                                    supply.score(&roots) >= actual[0] - 1e-7,
                                    "weighted root case={case}"
                                );
                            }
                        }
                    }
                }
            }
            let mut oracle = SearchState {
                best_score: f64::NEG_INFINITY,
                ..SearchState::default()
            };
            enumerate_box_reference(
                0,
                &roots,
                &problem,
                &requirements,
                &mut [0; 4],
                &Stats::new(),
                &mut oracle,
                &mut 0,
            )
            .unwrap();
            let expected = oracle.best_selected.map(|_| oracle.best_score);
            let serial = solve_exact(&problem).unwrap();
            assert_eq!(serial.score, expected, "serial oracle case={case}");
            assert_eq!(
                serial.best_build.map(|b| b.id),
                oracle.best_selected.map(|_| oracle.best_id.clone())
            );
            for threads in [1, 2, 4, 8, 16, 64] {
                let mut reversed = problem.clone();
                for g in &mut reversed.groups {
                    g.packages.reverse();
                }
                let mut session = NativeSearchSession::new(reversed).unwrap();
                session.run_parallel_slice(1, threads).unwrap();
                let checkpoint = serde_json::from_str(
                    &serde_json::to_string(&session.checkpoint().unwrap()).unwrap(),
                )
                .unwrap();
                let mut restored = NativeSearchSession::from_checkpoint(checkpoint).unwrap();
                while !restored.is_complete() {
                    let partial = restored.run_parallel_slice(1, threads).unwrap();
                    if let Some(expected) = expected {
                        assert!(partial.upper_bound.unwrap() >= expected - 1e-7);
                    }
                }
                let result = restored.snapshot();
                assert_eq!(
                    result.score, expected,
                    "parallel oracle case={case} threads={threads}"
                );
                assert_eq!(
                    result.best_build.map(|b| b.id),
                    oracle.best_selected.map(|_| oracle.best_id.clone())
                );
            }
        }
    }
}
