//! D4 native parallel runtime primitives.
//!
//! This module deliberately contains no damage formula.  It owns the parts
//! that must be correct independently of a JavaScript/Rust evaluator port:
//! one shared immutable task store, dynamic all-thread scheduling, and exact
//! lower/upper-bound result merging with deterministic build-ID ties.

use std::cmp::min;
use std::collections::VecDeque;
use std::sync::atomic::{AtomicUsize, Ordering};
use std::sync::Arc;
use std::sync::Mutex;

const EPSILON: f64 = 1e-9;

#[derive(Clone, Debug, PartialEq)]
pub struct D4CandidateScore {
    pub score: f64,
    pub build_id: String,
}

#[derive(Clone, Debug, PartialEq)]
pub struct D4ShardResult {
    pub shard_id: String,
    pub best: Option<D4CandidateScore>,
    pub upper_bound: f64,
    pub completed: bool,
    pub failed: bool,
}

#[derive(Clone, Debug, PartialEq)]
pub struct D4MergedResult {
    pub best: Option<D4CandidateScore>,
    pub upper_bound: Option<f64>,
    pub unresolved_shards: usize,
    pub failed_shards: usize,
    pub exact: bool,
}

pub fn is_better_candidate(
    candidate: &D4CandidateScore,
    current: Option<&D4CandidateScore>,
) -> bool {
    if !candidate.score.is_finite() {
        return false;
    }
    match current {
        None => true,
        Some(current) if candidate.score > current.score + EPSILON => true,
        Some(current) if (candidate.score - current.score).abs() <= EPSILON => {
            candidate.build_id < current.build_id
        }
        Some(_) => false,
    }
}

/// Merge a feasible global seed and independent shard certificates.  A seed
/// improves only the lower bound; it never masks an unfinished shard upper.
pub fn merge_shard_results(
    initial: Option<D4CandidateScore>,
    shard_results: impl IntoIterator<Item = D4ShardResult>,
) -> D4MergedResult {
    let mut best = initial.filter(|candidate| candidate.score.is_finite());
    let mut upper_bound = None::<f64>;
    let mut unresolved_shards = 0;
    let mut failed_shards = 0;

    for shard in shard_results {
        if let Some(candidate) = shard.best.as_ref() {
            if is_better_candidate(candidate, best.as_ref()) {
                best = Some(candidate.clone());
            }
        }
        if shard.failed {
            failed_shards += 1;
        }
        if !shard.completed {
            unresolved_shards += 1;
        }
        if shard.upper_bound.is_finite() {
            upper_bound =
                Some(upper_bound.map_or(shard.upper_bound, |upper| upper.max(shard.upper_bound)));
        }
    }

    let exact = failed_shards == 0
        && unresolved_shards == 0
        && best.as_ref().is_some_and(|candidate| {
            upper_bound.is_some_and(|upper| upper <= candidate.score + EPSILON)
        });
    D4MergedResult {
        best,
        upper_bound,
        unresolved_shards,
        failed_shards,
        exact,
    }
}

/// Execute each item once while sharing `tasks` by reference.  The caller's
/// task type can hold compact candidate-tree paths into an immutable `Arc`
/// store, so no per-thread candidate copy is required.
pub fn run_shared_tasks<T, R, F>(tasks: &[T], requested_threads: usize, evaluate: F) -> Vec<R>
where
    T: Sync,
    R: Send,
    F: Fn(&T) -> R + Sync,
{
    if tasks.is_empty() {
        return Vec::new();
    }
    let workers = min(tasks.len(), requested_threads.max(1));
    let next = AtomicUsize::new(0);
    let results = Mutex::new((0..tasks.len()).map(|_| None).collect::<Vec<Option<R>>>());

    std::thread::scope(|scope| {
        for _ in 0..workers {
            scope.spawn(|| loop {
                let index = next.fetch_add(1, Ordering::Relaxed);
                if index >= tasks.len() {
                    break;
                }
                let result = evaluate(&tasks[index]);
                // Every index is claimed once by fetch_add, so this short
                // critical section stores a result without cloning task data.
                results.lock().expect("D4 task result mutex poisoned")[index] = Some(result);
            });
        }
    });

    results
        .into_inner()
        .expect("D4 task result mutex poisoned")
        .into_iter()
        .map(|result| result.expect("every D4 task must have one result"))
        .collect()
}

#[derive(Clone, Debug, PartialEq, Eq)]
pub struct WorkStealingReport {
    pub completed: usize,
    pub spawned: usize,
    pub steals: usize,
}

/// A shared frontier scheduler for tasks that split while running. A worker
/// only exits when both the ready queue and active count are zero, so work
/// created by another worker remains stealable instead of becoming a tail.
pub fn run_work_stealing<T, F>(
    initial: Vec<T>,
    requested_threads: usize,
    split: F,
) -> WorkStealingReport
where
    T: Send,
    F: Fn(T) -> Vec<T> + Sync + Send,
{
    if initial.is_empty() {
        return WorkStealingReport {
            completed: 0,
            spawned: 0,
            steals: 0,
        };
    }
    let initial_count = initial.len();
    let queue = Arc::new(Mutex::new(VecDeque::from(initial)));
    let active = AtomicUsize::new(0);
    let completed = AtomicUsize::new(0);
    let spawned = AtomicUsize::new(initial_count);
    let steals = AtomicUsize::new(0);
    let workers = requested_threads.max(1);
    std::thread::scope(|scope| {
        let active = &active;
        let completed = &completed;
        let spawned = &spawned;
        let steals = &steals;
        let split = &split;
        for worker in 0..workers {
            let queue = Arc::clone(&queue);
            scope.spawn(move || loop {
                let task = {
                    let mut ready = queue.lock().expect("D4 work queue mutex poisoned");
                    let task = ready.pop_front();
                    if task.is_some() {
                        active.fetch_add(1, Ordering::AcqRel);
                    }
                    task
                };
                let Some(task) = task else {
                    if active.load(Ordering::Acquire) == 0 {
                        break;
                    }
                    std::thread::yield_now();
                    continue;
                };
                if worker > 0 {
                    steals.fetch_add(1, Ordering::Relaxed);
                }
                let children = split(task);
                completed.fetch_add(1, Ordering::Relaxed);
                if !children.is_empty() {
                    spawned.fetch_add(children.len(), Ordering::Relaxed);
                    queue
                        .lock()
                        .expect("D4 work queue mutex poisoned")
                        .extend(children);
                }
                active.fetch_sub(1, Ordering::Release);
            });
        }
    });
    WorkStealingReport {
        completed: completed.load(Ordering::Relaxed),
        spawned: spawned.load(Ordering::Relaxed),
        steals: steals.load(Ordering::Relaxed),
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn candidate(score: f64, build_id: &str) -> D4CandidateScore {
        D4CandidateScore {
            score,
            build_id: build_id.to_string(),
        }
    }

    #[test]
    fn merge_preserves_seed_and_never_marks_pending_work_exact() {
        let merged = merge_shard_results(
            Some(candidate(100.0, "seed")),
            [
                D4ShardResult {
                    shard_id: "a".to_string(),
                    best: Some(candidate(110.0, "a")),
                    upper_bound: 110.0,
                    completed: true,
                    failed: false,
                },
                D4ShardResult {
                    shard_id: "b".to_string(),
                    best: None,
                    upper_bound: 125.0,
                    completed: false,
                    failed: false,
                },
            ],
        );
        assert_eq!(merged.best, Some(candidate(110.0, "a")));
        assert_eq!(merged.upper_bound, Some(125.0));
        assert_eq!(merged.unresolved_shards, 1);
        assert!(!merged.exact);
    }

    #[test]
    fn merge_uses_lexical_id_for_equal_scores() {
        let merged = merge_shard_results(
            Some(candidate(100.0, "z")),
            [D4ShardResult {
                shard_id: "a".to_string(),
                best: Some(candidate(100.0, "a")),
                upper_bound: 100.0,
                completed: true,
                failed: false,
            }],
        );
        assert_eq!(merged.best, Some(candidate(100.0, "a")));
        assert!(merged.exact);
    }

    #[test]
    fn shared_scheduler_covers_each_task_once_at_all_thread_counts() {
        let tasks = (0_u32..128).collect::<Vec<_>>();
        for threads in [1, 2, 16, 64] {
            let result = run_shared_tasks(&tasks, threads, |value| value * value);
            assert_eq!(result.len(), tasks.len());
            assert_eq!(result[0], 0);
            assert_eq!(result[127], 127 * 127);
        }
    }

    #[test]
    fn work_stealing_consumes_tasks_created_after_workers_start() {
        let report = run_work_stealing(vec![(0_u8, 0_u8)], 8, |(depth, value)| {
            // Keep the first worker active briefly so the remaining workers
            // enter the wait-for-active path before it publishes descendants.
            if depth == 0 {
                std::thread::sleep(std::time::Duration::from_millis(5));
            }
            if depth >= 6 {
                Vec::new()
            } else {
                vec![(depth + 1, value * 2), (depth + 1, value * 2 + 1)]
            }
        });
        assert_eq!(report.completed, 127);
        assert_eq!(report.spawned, 127);
    }
}
