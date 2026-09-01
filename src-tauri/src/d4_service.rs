use crate::d4_native_solver;
use serde::{Deserialize, Serialize};
use std::collections::HashMap;
use std::num::NonZeroUsize;
use std::sync::atomic::{AtomicBool, AtomicU64, Ordering};
use std::sync::{Arc, Mutex};
use std::time::{Duration, Instant};

const SHARDS_PER_LOGICAL_THREAD: usize = 8;
const QUEUE_SAFETY_RESERVE_BYTES: u64 = 512 * 1024 * 1024;
const INITIAL_BUDGET_MS: u64 = 30_000;
const PROGRESS_INTERVAL_MS: u64 = 100;
const MAX_RESUMABLE_SESSIONS: usize = 4;
const NODES_PER_WORKER_BATCH: usize = 1;
static NEXT_CONTINUATION_ID: AtomicU64 = AtomicU64::new(1);

#[derive(Serialize)]
#[serde(rename_all = "camelCase")]
pub struct D4HardwareProfile {
    pub(crate) schema: &'static str,
    pub(crate) logical_threads: usize,
    pub(crate) total_memory_bytes: Option<u64>,
    pub(crate) available_memory_bytes: Option<u64>,
    pub(crate) initial_shard_target: usize,
    pub(crate) queue_memory_budget_bytes: Option<u64>,
}

#[derive(Default, Deserialize)]
#[serde(rename_all = "camelCase")]
pub struct D4NativeOptimizeOptions {
    pub(crate) remaining_budget_ms: Option<u64>,
    pub(crate) progress_interval_ms: Option<u64>,
}

#[derive(Clone, Serialize)]
#[serde(rename_all = "camelCase")]
pub struct D4NativeProgress {
    session_id: String,
    stage: &'static str,
    status: String,
    elapsed_ms: u128,
    deadline_remaining_ms: u64,
    lower_bound: Option<f64>,
    upper_bound: Option<f64>,
    evaluations: u64,
    visited_nodes: u64,
    pruned_by_bound: u64,
    pruned_by_constraint: u64,
    threads_total: usize,
    threads_active: usize,
    ready_work_items: usize,
    completed_work_items: u64,
}

#[derive(Serialize)]
#[serde(rename_all = "camelCase")]
pub struct D4NativeRuntimeResult {
    #[serde(flatten)]
    result: d4_native_solver::NativeSolveResult,
    continuation_id: Option<String>,
    threads_used: usize,
    ready_work_items: usize,
}

#[derive(Default)]
struct JobControl {
    cancel: AtomicBool,
    pause: AtomicBool,
}
struct StoredSession {
    session: d4_native_solver::NativeSearchSession,
    last_touched: Instant,
}

/// Owns only native D4 job signals and resumable frontiers. Its lifetime is
/// Tauri managed state; commands never create, clone, or replace it.
pub struct D4OptimizationService {
    signals: Arc<Mutex<HashMap<String, Arc<JobControl>>>>,
    sessions: Arc<Mutex<HashMap<String, StoredSession>>>,
}
impl Default for D4OptimizationService {
    fn default() -> Self {
        Self {
            signals: Arc::new(Mutex::new(HashMap::new())),
            sessions: Arc::new(Mutex::new(HashMap::new())),
        }
    }
}

fn valid_id(value: &str) -> bool {
    !value.is_empty()
        && value.len() <= 128
        && value
            .chars()
            .all(|c| c.is_ascii_alphanumeric() || matches!(c, '-' | '_'))
}
fn budget(options: &D4NativeOptimizeOptions) -> Duration {
    Duration::from_millis(
        options
            .remaining_budget_ms
            .unwrap_or(INITIAL_BUDGET_MS)
            .clamp(1, INITIAL_BUDGET_MS),
    )
}
fn progress_interval(options: &D4NativeOptimizeOptions) -> Duration {
    Duration::from_millis(
        options
            .progress_interval_ms
            .unwrap_or(PROGRESS_INTERVAL_MS)
            .clamp(50, 1_000),
    )
}
fn next_continuation_id() -> String {
    format!(
        "d4c-{}",
        NEXT_CONTINUATION_ID.fetch_add(1, Ordering::Relaxed)
    )
}
fn available_threads() -> usize {
    std::thread::available_parallelism()
        .map(NonZeroUsize::get)
        .unwrap_or(1)
}
fn initial_shard_target(logical_threads: usize) -> usize {
    logical_threads
        .max(1)
        .saturating_mul(SHARDS_PER_LOGICAL_THREAD)
        .max(logical_threads.max(1))
}
fn queue_memory_budget(total: Option<u64>, available: Option<u64>) -> Option<u64> {
    let limit = match (total, available) {
        (Some(total), Some(available)) => Some((total / 100 * 60).min(available / 100 * 75)),
        (Some(total), None) => Some(total / 100 * 60),
        (None, Some(available)) => Some(available / 100 * 75),
        (None, None) => None,
    }?;
    Some(limit.saturating_sub(QUEUE_SAFETY_RESERVE_BYTES))
}

#[cfg(windows)]
#[repr(C)]
struct MemoryStatusEx {
    dw_length: u32,
    dw_memory_load: u32,
    ull_total_phys: u64,
    ull_avail_phys: u64,
    ull_total_page_file: u64,
    ull_avail_page_file: u64,
    ull_total_virtual: u64,
    ull_avail_virtual: u64,
    ull_avail_extended_virtual: u64,
}
#[cfg(windows)]
#[link(name = "kernel32")]
extern "system" {
    fn GlobalMemoryStatusEx(buffer: *mut MemoryStatusEx) -> i32;
}
#[cfg(windows)]
fn physical_memory_status() -> (Option<u64>, Option<u64>) {
    let mut status = MemoryStatusEx {
        dw_length: std::mem::size_of::<MemoryStatusEx>() as u32,
        dw_memory_load: 0,
        ull_total_phys: 0,
        ull_avail_phys: 0,
        ull_total_page_file: 0,
        ull_avail_page_file: 0,
        ull_total_virtual: 0,
        ull_avail_virtual: 0,
        ull_avail_extended_virtual: 0,
    };
    if unsafe { GlobalMemoryStatusEx(&mut status) } == 0 {
        (None, None)
    } else {
        (Some(status.ull_total_phys), Some(status.ull_avail_phys))
    }
}
#[cfg(not(windows))]
fn physical_memory_status() -> (Option<u64>, Option<u64>) {
    (None, None)
}

fn progress_from(
    session_id: &str,
    result: &d4_native_solver::NativeSolveResult,
    ready_work_items: usize,
    deadline: Instant,
    threads_total: usize,
) -> D4NativeProgress {
    D4NativeProgress {
        session_id: session_id.to_string(),
        stage: "native-search",
        status: "running".to_string(),
        elapsed_ms: result.elapsed_ms,
        deadline_remaining_ms: deadline
            .saturating_duration_since(Instant::now())
            .as_millis() as u64,
        lower_bound: result.score,
        upper_bound: result.upper_bound,
        evaluations: result.evaluations,
        visited_nodes: result.visited_nodes,
        pruned_by_bound: result.pruned_by_bound,
        pruned_by_constraint: result.pruned_by_constraint,
        threads_total,
        threads_active: threads_total,
        ready_work_items,
        completed_work_items: result.visited_nodes,
    }
}
fn active_workers(complete: bool, threads: usize) -> usize {
    if complete {
        0
    } else {
        threads.max(1)
    }
}

fn run_budget(
    mut session: d4_native_solver::NativeSearchSession,
    session_id: String,
    deadline: Instant,
    interval: Duration,
    threads: usize,
    control: Arc<JobControl>,
    progress: tauri::ipc::Channel<D4NativeProgress>,
) -> Result<
    (
        d4_native_solver::NativeSolveResult,
        Option<d4_native_solver::NativeSearchSession>,
    ),
    String,
> {
    let mut last_progress = Instant::now() - interval;
    loop {
        if control.cancel.load(Ordering::Acquire) {
            let mut result = session.snapshot();
            result.status = "cancelled".to_string();
            result.exact = false;
            result.upper_bound = None;
            let _ = progress.send(D4NativeProgress {
                status: "cancelled".to_string(),
                threads_active: 0,
                deadline_remaining_ms: deadline
                    .saturating_duration_since(Instant::now())
                    .as_millis() as u64,
                ..progress_from(
                    &session_id,
                    &result,
                    session.ready_work_count(),
                    deadline,
                    threads,
                )
            });
            return Ok((result, None));
        }
        if control.pause.load(Ordering::Acquire) {
            let mut result = session.snapshot();
            result.status = "paused".to_string();
            result.exact = false;
            let _ = progress.send(D4NativeProgress {
                status: "paused".to_string(),
                threads_active: 0,
                deadline_remaining_ms: deadline
                    .saturating_duration_since(Instant::now())
                    .as_millis() as u64,
                ..progress_from(
                    &session_id,
                    &result,
                    session.ready_work_count(),
                    deadline,
                    threads,
                )
            });
            return Ok((result, (!session.is_complete()).then_some(session)));
        }
        if Instant::now() >= deadline {
            let result = session.snapshot();
            let _ = progress.send(D4NativeProgress {
                status: result.status.clone(),
                threads_active: 0,
                deadline_remaining_ms: 0,
                ..progress_from(
                    &session_id,
                    &result,
                    session.ready_work_count(),
                    deadline,
                    threads,
                )
            });
            return Ok((result, (!session.is_complete()).then_some(session)));
        }
        let result = session.run_parallel_slice_with_control(
            threads.saturating_mul(NODES_PER_WORKER_BATCH),
            threads,
            Some(&control.cancel),
            Some(deadline),
        )?;
        if control.cancel.load(Ordering::Acquire) {
            continue;
        }
        if last_progress.elapsed() >= interval || session.is_complete() {
            let status = if session.is_complete() {
                result.status.clone()
            } else {
                "running".to_string()
            };
            let _ = progress.send(D4NativeProgress {
                status,
                threads_active: active_workers(session.is_complete(), threads),
                ..progress_from(
                    &session_id,
                    &result,
                    session.ready_work_count(),
                    deadline,
                    threads,
                )
            });
            last_progress = Instant::now();
        }
        if session.is_complete() {
            return Ok((result, None));
        }
    }
}

impl D4OptimizationService {
    pub fn hardware_profile() -> D4HardwareProfile {
        let (total_memory_bytes, available_memory_bytes) = physical_memory_status();
        let logical_threads = available_threads();
        D4HardwareProfile {
            schema: "toram.d4-hardware-profile.v1",
            logical_threads,
            total_memory_bytes,
            available_memory_bytes,
            initial_shard_target: initial_shard_target(logical_threads),
            queue_memory_budget_bytes: queue_memory_budget(
                total_memory_bytes,
                available_memory_bytes,
            ),
        }
    }
    fn register(&self, job_id: &str) -> Result<Arc<JobControl>, String> {
        let signal = Arc::new(JobControl::default());
        let mut signals = self
            .signals
            .lock()
            .map_err(|_| "D4 작업 레지스트리가 손상되었습니다.".to_string())?;
        if signals.contains_key(job_id) {
            return Err("같은 D4 작업이 이미 실행 중입니다.".to_string());
        }
        signals.insert(job_id.to_string(), Arc::clone(&signal));
        Ok(signal)
    }
    fn remove(&self, job_id: &str) -> Result<(), String> {
        self.signals
            .lock()
            .map_err(|_| "D4 작업 레지스트리가 손상되었습니다.".to_string())?
            .remove(job_id);
        Ok(())
    }
    fn store(
        &self,
        id: String,
        session: d4_native_solver::NativeSearchSession,
    ) -> Result<(), String> {
        let mut sessions = self
            .sessions
            .lock()
            .map_err(|_| "D4 세션 레지스트리가 손상되었습니다.".to_string())?;
        if sessions.len() >= MAX_RESUMABLE_SESSIONS {
            if let Some(oldest) = sessions
                .iter()
                .min_by_key(|(_, value)| value.last_touched)
                .map(|(id, _)| id.clone())
            {
                sessions.remove(&oldest);
            }
        }
        sessions.insert(
            id,
            StoredSession {
                session,
                last_touched: Instant::now(),
            },
        );
        Ok(())
    }
    async fn run_session(
        &self,
        continuation_id: String,
        session: d4_native_solver::NativeSearchSession,
        options: D4NativeOptimizeOptions,
        progress: tauri::ipc::Channel<D4NativeProgress>,
        signal: Arc<JobControl>,
    ) -> Result<D4NativeRuntimeResult, String> {
        let deadline = Instant::now() + budget(&options);
        let interval = progress_interval(&options);
        let threads = available_threads();
        let run_id = continuation_id.clone();
        let joined = tauri::async_runtime::spawn_blocking(move || {
            run_budget(
                session, run_id, deadline, interval, threads, signal, progress,
            )
        })
        .await;
        let (result, session) = joined
            .map_err(|error| format!("D4 네이티브 작업을 기다리지 못했습니다: {error}"))??;
        let ready_work_items = session
            .as_ref()
            .map_or(0, d4_native_solver::NativeSearchSession::ready_work_count);
        let continuation_id = if let Some(session) = session {
            self.store(continuation_id.clone(), session)?;
            Some(continuation_id)
        } else {
            None
        };
        Ok(D4NativeRuntimeResult {
            result,
            continuation_id,
            threads_used: threads,
            ready_work_items,
        })
    }
    pub async fn optimize(
        &self,
        job_id: String,
        problem: d4_native_solver::NativeProblem,
        options: D4NativeOptimizeOptions,
        progress: tauri::ipc::Channel<D4NativeProgress>,
    ) -> Result<D4NativeRuntimeResult, String> {
        if !valid_id(&job_id) {
            return Err("D4 작업 식별자가 올바르지 않습니다.".to_string());
        }
        let signal = self.register(&job_id)?;
        let continuation_id = next_continuation_id();
        let run_id = continuation_id.clone();
        let deadline = Instant::now() + budget(&options);
        let interval = progress_interval(&options);
        let threads = available_threads();
        let joined = tauri::async_runtime::spawn_blocking(move || {
            let session = d4_native_solver::NativeSearchSession::new(problem)?;
            run_budget(
                session, run_id, deadline, interval, threads, signal, progress,
            )
        })
        .await;
        self.remove(&job_id)?;
        let (result, session) = joined
            .map_err(|error| format!("D4 네이티브 작업을 기다리지 못했습니다: {error}"))??;
        let ready_work_items = session
            .as_ref()
            .map_or(0, d4_native_solver::NativeSearchSession::ready_work_count);
        let continuation_id = if let Some(session) = session {
            self.store(continuation_id.clone(), session)?;
            Some(continuation_id)
        } else {
            None
        };
        Ok(D4NativeRuntimeResult {
            result,
            continuation_id,
            threads_used: threads,
            ready_work_items,
        })
    }
    pub async fn resume(
        &self,
        job_id: String,
        continuation_id: String,
        options: D4NativeOptimizeOptions,
        progress: tauri::ipc::Channel<D4NativeProgress>,
    ) -> Result<D4NativeRuntimeResult, String> {
        if !valid_id(&job_id) || !valid_id(&continuation_id) {
            return Err("D4 작업 또는 재개 식별자가 올바르지 않습니다.".to_string());
        }
        let stored = self
            .sessions
            .lock()
            .map_err(|_| "D4 세션 레지스트리가 손상되었습니다.".to_string())?
            .remove(&continuation_id)
            .ok_or_else(|| "D4 재개 세션이 만료되었거나 존재하지 않습니다.".to_string())?;
        let signal = match self.register(&job_id) {
            Ok(signal) => signal,
            Err(error) => {
                self.store(continuation_id, stored.session)?;
                return Err(error);
            }
        };
        let result = self
            .run_session(continuation_id, stored.session, options, progress, signal)
            .await;
        self.remove(&job_id)?;
        result
    }
    pub fn dispose(&self, continuation_id: String) -> Result<bool, String> {
        if !valid_id(&continuation_id) {
            return Err("D4 재개 식별자가 올바르지 않습니다.".to_string());
        }
        Ok(self
            .sessions
            .lock()
            .map_err(|_| "D4 세션 레지스트리가 손상되었습니다.".to_string())?
            .remove(&continuation_id)
            .is_some())
    }
    fn signal(&self, job_id: String, pause: bool) -> Result<bool, String> {
        if !valid_id(&job_id) {
            return Err("D4 작업 식별자가 올바르지 않습니다.".to_string());
        }
        let signals = self
            .signals
            .lock()
            .map_err(|_| "D4 작업 레지스트리가 손상되었습니다.".to_string())?;
        let Some(signal) = signals.get(&job_id) else {
            return Ok(false);
        };
        if pause {
            signal.pause.store(true, Ordering::Release);
        } else {
            signal.cancel.store(true, Ordering::Release);
        }
        Ok(true)
    }
    pub fn cancel(&self, job_id: String) -> Result<bool, String> {
        self.signal(job_id, false)
    }
    pub fn pause(&self, job_id: String) -> Result<bool, String> {
        self.signal(job_id, true)
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    fn small_problem() -> d4_native_solver::NativeProblem {
        serde_json::from_value(serde_json::json!({
            "baseContext":{"level":100,"mainType":"한손검","subType":"없음","armorType":"일반옷","wpnAtk":100,"wpnRefine":0,"wpnStab":100,"strBase":0,"dexBase":0,"intBase":0,"agiBase":0,"vitBase":100,"critF":100,"atkType":"PHYS","rangeType":"SHORT","bossLevel":100,"bossDef":0,"bossMdef":0,"aspdF":1000,"maxHpF":10000,"maxMpF":2000,"amprF":100},
            "scenarioSnapshot":{"requirements":{"maxHp":10000,"maxMp":2000,"amprBeforeDual":100,"normalAttackCrit":100,"aspd":1000}},
            "groups":[
                {"id":"a","packages":[{"id":"a","statDelta":{"ATKP":1}},{"id":"z","statDelta":{"ATKP":1}}]},
                {"id":"b","packages":[{"id":"b","statDelta":{"ATKP":1}}]},
                {"id":"c","packages":[{"id":"c","statDelta":{"ATKP":1}}]},
                {"id":"d","packages":[{"id":"d","statDelta":{"ATKP":1}}]}
            ]
        })).unwrap()
    }

    #[test]
    fn validates_job_and_continuation_ids() {
        assert!(valid_id("d4-abc_1"));
        assert!(!valid_id(""));
        assert!(!valid_id("d4/escape"));
    }

    #[test]
    fn clamps_budget_and_progress_interval() {
        assert_eq!(
            budget(&D4NativeOptimizeOptions {
                remaining_budget_ms: Some(0),
                progress_interval_ms: None
            }),
            Duration::from_millis(1)
        );
        assert_eq!(
            progress_interval(&D4NativeOptimizeOptions {
                remaining_budget_ms: None,
                progress_interval_ms: Some(1)
            }),
            Duration::from_millis(50)
        );
    }

    #[test]
    fn reports_hardware_and_memory_contract() {
        let profile = D4OptimizationService::hardware_profile();
        assert_eq!(profile.schema, "toram.d4-hardware-profile.v1");
        assert!(profile.logical_threads >= 1);
        assert!(profile.initial_shard_target >= profile.logical_threads);
    }

    #[test]
    fn keeps_existing_memory_budget_policy() {
        const MIB: u64 = 1024 * 1024;
        assert_eq!(initial_shard_target(16), 128);
        assert_eq!(
            queue_memory_budget(Some(16_000 * MIB), Some(4_000 * MIB)),
            Some(3_000 * MIB - QUEUE_SAFETY_RESERVE_BYTES)
        );
        assert_eq!(queue_memory_budget(None, None), None);
    }

    #[test]
    fn progress_reports_the_search_worker_pool() {
        assert_eq!(active_workers(false, 16), 16);
        assert_eq!(active_workers(false, 0), 1);
        assert_eq!(active_workers(true, 16), 0);
    }

    #[test]
    fn cancellation_discards_the_resumable_frontier() {
        let channel = tauri::ipc::Channel::<D4NativeProgress>::new(|_| Ok(()));
        let control = Arc::new(JobControl {
            cancel: AtomicBool::new(true),
            pause: AtomicBool::new(false),
        });
        let (result, preserved) = run_budget(
            d4_native_solver::NativeSearchSession::new(small_problem()).unwrap(),
            "d4c-cancel".to_string(),
            Instant::now() + Duration::from_secs(1),
            Duration::from_millis(50),
            2,
            control,
            channel,
        )
        .unwrap();
        assert_eq!(result.status, "cancelled");
        assert!(!result.exact);
        assert!(result.upper_bound.is_none());
        assert!(preserved.is_none());
    }

    #[test]
    fn pause_keeps_the_resumable_frontier() {
        let channel = tauri::ipc::Channel::<D4NativeProgress>::new(|_| Ok(()));
        let control = Arc::new(JobControl {
            cancel: AtomicBool::new(false),
            pause: AtomicBool::new(true),
        });
        let (paused, preserved) = run_budget(
            d4_native_solver::NativeSearchSession::new(small_problem()).unwrap(),
            "d4c-pause".to_string(),
            Instant::now() + Duration::from_secs(1),
            Duration::from_millis(50),
            2,
            control,
            channel,
        )
        .unwrap();
        assert_eq!(paused.status, "paused");
        assert!(!paused.exact);
        assert!(paused.upper_bound.is_some());
        let mut resumed = preserved.unwrap();
        while !resumed.is_complete() {
            resumed.run_slice(1).unwrap();
        }
        assert_eq!(resumed.snapshot().status, "exact");
    }
}
