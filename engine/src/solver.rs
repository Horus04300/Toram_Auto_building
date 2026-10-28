//! Shared CandidateTree search for Native and WASM, including deterministic
//! seeds, safe bounds, lexical tie breaking, and resumable search state.

use std::cmp::Ordering;
use std::collections::{BTreeMap, BinaryHeap, HashSet};
use std::sync::atomic::{AtomicBool, AtomicU64, AtomicUsize, Ordering as AtomicOrdering};
use std::sync::{Arc, Mutex};
#[cfg(not(target_arch = "wasm32"))]
use std::time::{Duration, Instant};
#[cfg(target_arch = "wasm32")]
use web_time::{Duration, Instant};

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
    // Retained only for v25 checkpoint identity; both experimental policies are retired.
    #[serde(
        rename = "experimentalLocalBounds",
        default,
        skip_serializing_if = "std::ops::Not::not"
    )]
    pub experimental_local_bounds: bool,
    #[serde(
        rename = "experimentalSupplyStates",
        default,
        skip_serializing_if = "std::ops::Not::not"
    )]
    pub experimental_supply_states: bool,
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
    product_start: Option<usize>,
    product_weights: [f64; 3],
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
            product_start: None,
            product_weights: [0.0; 3],
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
        // Extra objective directions paid off when no utility direction was
        // useful; otherwise keep the existing joint-constraint bounds and cost.
        if let Some(product) = plan
            .range_product
            .as_ref()
            .filter(|_| plan.legacy_safe && directions.len() == SUPPLY_BASE)
        {
            let weight = product.upper[0] / product.upper[1];
            if weight.is_finite()
                && weight > 0.0
                && product.upper.iter().all(|v| v.is_finite() && *v < 1e15)
                && product
                    .factors
                    .iter()
                    .all(|f| f.coefficients.iter().any(|v| *v != 0.0))
            {
                let weights = [weight * 0.25, weight, weight * 4.0];
                let extra: Vec<Form> = weights
                    .into_iter()
                    .filter_map(|w| plan.product_direction(w))
                    .collect();
                if extra.len() == weights.len() {
                    result.product_start = Some(directions.len());
                    directions.extend_from_slice(&product.factors);
                    result.product_weights = weights;
                    directions.extend(extra);
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
        let end = self.product_start.unwrap_or(self.direction_count);
        let mut bound = (SUPPLY_BASE..end).fold(self.metric(clusters, 0), |bound, i| {
            bound.min(self.metric(clusters, i))
        });
        if let Some(start) = self.product_start {
            let x = self.metric(clusters, start);
            let y = self.metric(clusters, start + 1);
            let tail = self
                .plan
                .as_ref()
                .unwrap()
                .range_product
                .as_ref()
                .unwrap()
                .tail;
            for (i, weight) in self.product_weights.into_iter().enumerate() {
                let upper =
                    correlated_product_upper(x, y, self.metric(clusters, start + 2 + i), weight)
                        * tail;
                bound = bound.min(upper + 1024.0 * f64::EPSILON * (1.0 + upper.abs()));
            }
        }
        bound
    }
}

// Maximum xy for 0<=x<=X, 0<=y<=Y and x+k*y<=S. The joint support S
// uses both factors from the same package, retaining their supply tradeoff.
fn correlated_product_upper(x: f64, y: f64, support: f64, weight: f64) -> f64 {
    if ![x, y, support, weight].iter().all(|v| v.is_finite())
        || x < 0.0
        || y < 0.0
        || support < 0.0
        || weight <= 0.0
    {
        return f64::INFINITY;
    }
    if support >= x + weight * y {
        return x * y + 1024.0 * f64::EPSILON * (1.0 + (x * y).abs());
    }
    let low = ((support - x) / weight).max(0.0);
    let high = y.min(support / weight).max(0.0);
    let b = (support / (2.0 * weight)).clamp(low.min(high), high);
    let a = x.min((support - weight * b).max(0.0));
    a * b + 1024.0 * f64::EPSILON * (1.0 + x * y + support * support / weight)
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
            let Some(original) = stats.get_mut(key) else {
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
            if upper < *original {
                *original = upper;
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
fn process_node_batch(
    problem: &NativeProblem,
    requirements: &Requirements,
    batch: &NodeBatch,
    buffer: &mut WorkerOutput,
) {
    let mut local_counters = LocalSearchCounters::default();
    loop {
        let index = batch.next.fetch_add(1, AtomicOrdering::Relaxed);
        let Some(node) = batch.nodes.get(index) else {
            break;
        };
        let start = buffer.children.len();
        let outcome = std::panic::catch_unwind(std::panic::AssertUnwindSafe(|| {
            expand_parallel_node_into(
                node,
                problem,
                requirements,
                &batch.incumbent,
                &mut local_counters,
                batch.cancel.as_deref(),
                batch.deadline,
                &mut buffer.children,
            )
        }))
        .unwrap_or_else(|_| Err("CrystaOptimization search worker panicked".into()));
        if !matches!(outcome, Ok(true)) {
            buffer.children.truncate(start);
        }
        buffer.outcomes.push((
            index,
            outcome.map(|completed| completed.then_some(start..buffer.children.len())),
        ));
    }
    batch.counters.merge_search_counts(local_counters);
}

#[cfg(not(all(target_arch = "wasm32", feature = "wasm-threads")))]
struct NodeJob {
    batch: Arc<NodeBatch>,
    buffer: WorkerOutput,
    output: std::sync::mpsc::Sender<WorkerOutput>,
}
#[cfg(not(all(target_arch = "wasm32", feature = "wasm-threads")))]
struct NodePool {
    input: Option<std::sync::mpsc::Sender<NodeJob>>,
    workers: Vec<std::thread::JoinHandle<()>>,
    buffers: Vec<WorkerOutput>,
}
#[cfg(not(all(target_arch = "wasm32", feature = "wasm-threads")))]
impl NodePool {
    fn worker_count(&self) -> usize {
        self.workers.len()
    }
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
                    let mut buffer = job.buffer;
                    process_node_batch(&problem, &requirements, &job.batch, &mut buffer);
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
#[cfg(not(all(target_arch = "wasm32", feature = "wasm-threads")))]
impl Drop for NodePool {
    fn drop(&mut self) {
        self.input.take();
        for worker in self.workers.drain(..) {
            let _ = worker.join();
        }
    }
}

#[cfg(all(target_arch = "wasm32", feature = "wasm-threads"))]
struct NodePool {
    problem: NativeProblem,
    requirements: Requirements,
    workers: usize,
    buffers: Vec<WorkerOutput>,
}

#[cfg(all(target_arch = "wasm32", feature = "wasm-threads"))]
impl NodePool {
    fn worker_count(&self) -> usize {
        self.workers
    }
    fn new(
        problem: &NativeProblem,
        requirements: Requirements,
        count: usize,
    ) -> Result<Self, String> {
        Ok(Self {
            problem: problem.clone(),
            requirements,
            workers: count.max(1),
            buffers: (0..count.max(1)).map(|_| WorkerOutput::default()).collect(),
        })
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
        use rayon::prelude::*;
        results.clear();
        results.resize_with(nodes.len(), || None);
        let batch = NodeBatch {
            nodes: Arc::clone(nodes),
            next: AtomicUsize::new(0),
            incumbent: Arc::clone(incumbent),
            counters: Arc::clone(counters),
            cancel: cancel.cloned(),
            deadline,
        };
        let problem = &self.problem;
        let requirements = &self.requirements;
        self.buffers
            .par_iter_mut()
            .take(nodes.len())
            .for_each(|buffer| {
                buffer.children.clear();
                buffer.outcomes.clear();
                process_node_batch(problem, requirements, &batch, buffer);
            });
        for (buffer_index, buffer) in self.buffers.iter_mut().enumerate() {
            for (index, outcome) in buffer.outcomes.drain(..) {
                results[index] = Some(outcome.map(|range| {
                    range.map(|range| NodeChildren {
                        buffer: buffer_index,
                        range,
                    })
                }));
            }
        }
        if results.iter().any(Option::is_none) {
            return Err("CrystaOptimization worker result missing".into());
        }
        Ok(())
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
    let stat = match key {
        "STR" | "STRP" => Some("strBase"),
        "DEX" | "DEXP" => Some("dexBase"),
        "AGI" | "AGIP" => Some("agiBase"),
        "INT" | "INTP" => Some("intBase"),
        "VIT" | "VITP" => Some("vitBase"),
        _ => None,
    };
    if let Some(stat) = stat {
        let base = |name| {
            context
                .get(name)
                .and_then(Value::as_f64)
                .unwrap_or(0.0)
                .abs()
        };
        let largest = ["strBase", "dexBase", "agiBase", "intBase", "vitBase"]
            .into_iter()
            .map(base)
            .fold(0.0_f64, f64::max);
        if largest > 0.0 {
            weight *= base(stat).max(1.0) / largest.max(1.0);
        }
    }
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
            schema: "toram.crysta-native-search-checkpoint.v25".to_string(),
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
        if checkpoint.schema != "toram.crysta-native-search-checkpoint.v25" {
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
        self.advance_slice(node_budget)?;
        Ok(self.result())
    }

    pub fn advance_slice(&mut self, node_budget: usize) -> Result<(), String> {
        if self.terminal_invalid_upper.is_some() {
            return Ok(());
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
        outcome
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
            .is_none_or(|pool| pool.worker_count() != workers)
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
#[path = "solver_tests.rs"]
mod tests;
