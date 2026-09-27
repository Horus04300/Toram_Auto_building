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
use std::time::{Duration, Instant};

use serde::{Deserialize, Serialize};
use serde_json::Value;

#[cfg(test)]
use crate::d4_native_evaluator::D4NativeSummary;
use crate::d4_native_evaluator::{
    evaluate_summary_from_native_stats as evaluate_summary_from_map,
    evaluate_utility_feasible_score as evaluate_feasible_summary, utility_values, NativeStats,
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
type Stats = NativeStats;

#[derive(Clone, Serialize, Deserialize)]
pub struct NativePackage {
    pub id: String,
    #[serde(rename = "statDelta", default)]
    pub stat_delta: Stats,
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
        trees
            .nodes
            .try_reserve_exact(capacity)
            .map_err(|error| format!("D4 tree allocation failed: {error}"))?;
        for (index, group) in self.groups.iter().enumerate() {
            trees.roots[index] = build_tree(
                &mut trees,
                &group.packages,
                (0..group.packages.len()).collect(),
                &keys,
                &global_ranges(&group.packages, &keys),
                &self.base_context,
                "r".into(),
            );
        }
        let roots = trees.roots;
        self.trees = Arc::new(trees);
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
    package: Option<usize>,
    left: Option<NodeId>,
    right: Option<NodeId>,
}

/// D4 always has weapon/armor/additional/special groups. An array keeps one
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
    upper: f64,
    paths: [String; GROUP_COUNT],
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
                .name("d4-search".into())
                .spawn(move || loop {
                    let job = receiver.lock().expect("D4 job receiver poisoned").recv();
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
                            .unwrap_or_else(|_| Err("D4 search worker panicked".into()));
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
                .map_err(|error| format!("D4 worker creation failed: {error}"))?;
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
                .map_err(|_| "D4 pool stopped".to_string())?;
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
            return Err("D4 worker result missing".into());
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
}
trait SearchCounters {
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

fn tree_capacity(counts: impl IntoIterator<Item = usize>) -> Result<usize, String> {
    counts.into_iter().try_fold(0_usize, |total, leaves| {
        let nodes = leaves.checked_mul(2).and_then(|n| n.checked_sub(1));
        nodes
            .and_then(|n| total.checked_add(n))
            .filter(|n| *n <= u32::MAX as usize)
            .ok_or_else(|| "D4 tree exceeds the supported node index range".to_string())
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
    // Keep the established split ordering independent of tighter signed bounds.
    // Cache it once: each node participates in many Cartesian search boxes.
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
        package: (indices.len() <= 1)
            .then(|| indices.first().copied())
            .flatten(),
        left: None,
        right: None,
    });
    if indices.len() <= 1 {
        return id;
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
fn feasible(summary: &D4NativeSummary, requirements: &Requirements) -> bool {
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
    clusters
        .iter()
        .skip(1)
        .fold(trees[clusters[0]].envelope.clone(), |stats, node| {
            add_stats(stats, &trees[*node].envelope)
        })
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

fn split_slack(trees: &TreeArena, node: &TreeNode) -> f64 {
    let (Some(left), Some(right)) = (&node.left, &node.right) else {
        return f64::NEG_INFINITY;
    };
    node.split_score - trees[*left].split_score.max(trees[*right].split_score)
}

fn split_indices(trees: &TreeArena, clusters: &[NodeId; GROUP_COUNT]) -> [Option<usize>; 2] {
    let mut available: [Option<(usize, f64, usize)>; GROUP_COUNT] = std::array::from_fn(|index| {
        let node = &trees[clusters[index]];
        (node.left.is_some() || node.right.is_some())
            .then(|| (index, split_slack(trees, node), node.size))
    });
    available.sort_by(|left, right| match (left, right) {
        (Some(left), Some(right)) => right
            .1
            .total_cmp(&left.1)
            .then_with(|| right.2.cmp(&left.2))
            .then_with(|| left.0.cmp(&right.0)),
        (Some(_), None) => Ordering::Less,
        (None, Some(_)) => Ordering::Greater,
        (None, None) => Ordering::Equal,
    });
    [
        available[0].map(|entry| entry.0),
        available[1].map(|entry| entry.0),
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
    state.evaluations += 1;
    let Some(summary) = evaluate_feasible_summary(&problem.base_context, stats, |i, v| {
        requirements.accepts_value(i, v)
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

    let root_stats = box_stats(&problem.trees, &clusters);
    state.evaluations += 1;
    let root = evaluate_summary_from_map(&problem.base_context, &root_stats)?;
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
        let child_boxes = ChildBoxes::new(&problem.trees, &node.clusters);
        if child_boxes.len() == 0 {
            continue;
        }
        for child_clusters in child_boxes {
            let stats = box_stats(&problem.trees, &child_clusters);
            state.evaluations += 1;
            let Some(bound) = evaluate_feasible_summary(&problem.base_context, &stats, |i, v| {
                requirements.accepts_value(i, v)
            })?
            else {
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

/// A resumable single-frontier native search.  N2 keeps this independent from
/// the P5 shard scheduler: N3 will decide how ready work is shared by workers,
/// while this type owns the complete checkpointable search state.
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
            return Err("D4 native solver requires four nonempty prepared groups".to_string());
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
        let root_stats = box_stats(&problem.trees, &clusters);
        state.evaluations += 1;
        let root = evaluate_summary_from_map(&problem.base_context, &root_stats)?;
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
            schema: "toram.d4-native-search-checkpoint.v8".to_string(),
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
        if checkpoint.schema != "toram.d4-native-search-checkpoint.v8" {
            return Err("D4 native checkpoint schema is invalid".to_string());
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
                        "D4 native checkpoint references an unknown frontier path".to_string()
                    })?
                    .try_into()
                    .map_err(|_| "D4 native checkpoint requires four frontier paths".to_string())?;
                heap.push(WorkItem {
                    upper: item.upper,
                    clusters,
                });
            }
        } else if !checkpoint.frontier.is_empty() {
            return Err("D4 native checkpoint has frontier without searchable roots".to_string());
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
            if !item.upper.is_finite() || !seen.insert(item.paths.join("|")) {
                return Err("D4 native checkpoint frontier is incomplete or duplicated".to_string());
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
                let child_boxes = ChildBoxes::new(&self.problem.trees, &node.clusters);
                if child_boxes.len() == 0 {
                    continue;
                }
                for child_clusters in child_boxes {
                    let stats = box_stats(&self.problem.trees, &child_clusters);
                    self.state.evaluations += 1;
                    let Some(bound) =
                        evaluate_feasible_summary(&self.problem.base_context, &stats, |i, v| {
                            self.requirements.accepts_value(i, v)
                        })?
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
                .map_err(|_| "D4 incumbent mutex was poisoned".to_string())?
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
            } else if self.terminal_invalid_upper.is_some() {
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
    counters.count_evaluations();
    let Some(summary) = evaluate_feasible_summary(&problem.base_context, stats, |i, v| {
        requirements.accepts_value(i, v)
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
    if suffix.is_some()
        && index > 0
        && candidates[index..]
            .iter()
            .map(|items| items.len())
            .product::<usize>()
            >= 4
    {
        if let Some(suffix) = suffix {
            let upper = add_stats(stats.clone(), &suffix[index]);
            counters.count_evaluations();
            let mut possible = true;
            evaluate_feasible_summary(&problem.base_context, &upper, |i, v| {
                possible = requirements.accepts_value(i, v);
                possible && i != 4 // Stop before damage, including on success.
            })?;
            if !possible {
                counters.count_pruned_by_constraint();
                return Ok(true);
            }
        }
    }
    for &package_index in candidates[index] {
        selected[index] = package_index;
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
    let child_boxes = ChildBoxes::new(&problem.trees, &node.clusters);
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
        let stats = box_stats(&problem.trees, &child_clusters);
        counters.count_evaluations();
        let Some(bound) = evaluate_feasible_summary(&problem.base_context, &stats, |i, v| {
            requirements.accepts_value(i, v)
        })?
        else {
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
        let child_boxes = ChildBoxes::new(&problem.trees, &node.clusters);
        if child_boxes.len() == 0 {
            frontier.push(node);
            break;
        }
        for child_clusters in child_boxes {
            let stats = box_stats(&problem.trees, &child_clusters);
            state.evaluations += 1;
            let Some(bound) = evaluate_feasible_summary(&problem.base_context, &stats, |i, v| {
                requirements.accepts_value(i, v)
            })?
            else {
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
    let root_stats = box_stats(&problem.trees, &clusters);
    seed.evaluations += 1;
    let root = evaluate_summary_from_map(&problem.base_context, &root_stats)?;
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
                    if failure.lock().expect("D4 failure mutex poisoned").is_some() {
                        break;
                    }
                    if cancel.is_some_and(|signal| signal.load(AtomicOrdering::Acquire)) {
                        break;
                    }
                    let mut waited_for_frontier = false;
                    let node = loop {
                        let mut ready = frontier.lock().expect("D4 frontier mutex poisoned");
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
                                let mut ready =
                                    frontier.lock().expect("D4 frontier mutex poisoned");
                                ready.extend(children.drain(..));
                            }
                            processed.fetch_add(1, AtomicOrdering::Relaxed);
                        }
                        Ok(false) => {}
                        Err(error) => {
                            *failure.lock().expect("D4 failure mutex poisoned") = Some(error);
                        }
                    }
                    active.fetch_sub(1, AtomicOrdering::AcqRel);
                    if failure.lock().expect("D4 failure mutex poisoned").is_some() {
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
        let summary = D4NativeSummary {
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
                    id: format!("{}:flat", group._id),
                    stat_delta: serde_json::from_value(json!({"MAXHP":1000})).unwrap(),
                },
                NativePackage {
                    evaluation_delta: None,
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
        for version in [4, 5, 6, 7] {
            let mut checkpoint = session.checkpoint().unwrap();
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
}
