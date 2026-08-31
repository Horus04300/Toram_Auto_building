#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

// Native D4 is exposed only after the JS/Rust parity and exact-tie gates.
#[allow(dead_code)]
mod d4_native_evaluator;
#[allow(dead_code)]
mod d4_native_solver;
#[allow(dead_code)]
mod d4_parallel_runtime;

use serde::{Deserialize, Serialize};
use serde_json::Value;
use std::collections::HashMap;
use std::fs::{self, OpenOptions};
use std::io::Write;
use std::num::NonZeroUsize;
use std::path::{Path, PathBuf};
use std::sync::atomic::{AtomicBool, AtomicU64, Ordering};
use std::sync::{Arc, Mutex};
use std::time::{Duration, Instant, UNIX_EPOCH};

const APP_STORAGE_DIRECTORY: &str = "ToramOnlineAutoBuildCalculator";
const SETTING_FORMAT: &str = "toram-auto-build-setting";
const SETTING_SCHEMA_VERSION: u64 = 1;
const D4_SHARDS_PER_LOGICAL_THREAD: usize = 8;
const D4_QUEUE_SAFETY_RESERVE_BYTES: u64 = 512 * 1024 * 1024;
const D4_INITIAL_BUDGET_MS: u64 = 30_000;
const D4_PROGRESS_INTERVAL_MS: u64 = 100;
const D4_MAX_RESUMABLE_SESSIONS: usize = 4;
// A session batch is a cooperative deadline/cancel boundary.  Keeping one
// ready node per worker bounds the time spent inside a batch; a larger fixed
// multiple can make the coordinator miss its 30-second deadline while it
// waits for hundreds of nodes to drain.
const D4_NODES_PER_WORKER_BATCH: usize = 1;
static NEXT_D4_CONTINUATION_ID: AtomicU64 = AtomicU64::new(1);
const SETTING_STORAGE_KEYS: [&str; 5] = [
    "toram-auto-building.build-state.v1",
    "toram-auto-building.skill-tree.v1",
    "toram-auto-building.skill-tree-ui.v1",
    "toram-auto-active-buffs-v1",
    "toram.combo-sequence.v1",
];

#[derive(Serialize)]
#[serde(rename_all = "camelCase")]
struct SettingFile {
    name: String,
    last_modified: u64,
}

/// P3 native parallelization contract. It intentionally reports the logical
/// CPUs the current process may use rather than the developer machine's CPU.
#[derive(Serialize)]
#[serde(rename_all = "camelCase")]
struct D4HardwareProfile {
    schema: &'static str,
    logical_threads: usize,
    total_memory_bytes: Option<u64>,
    available_memory_bytes: Option<u64>,
    initial_shard_target: usize,
    queue_memory_budget_bytes: Option<u64>,
}

/// Per-window cancellation signals for native D4 searches.  The job id is
/// generated in the UI and exists only for the lifetime of one invocation.
#[derive(Default)]
struct D4JobControl {
    cancel: AtomicBool,
    pause: AtomicBool,
}

struct D4JobRegistry {
    signals: Arc<Mutex<HashMap<String, Arc<D4JobControl>>>>,
    sessions: Arc<Mutex<HashMap<String, D4StoredSession>>>,
}

impl Default for D4JobRegistry {
    fn default() -> Self {
        Self {
            signals: Arc::new(Mutex::new(HashMap::new())),
            sessions: Arc::new(Mutex::new(HashMap::new())),
        }
    }
}

struct D4StoredSession {
    session: d4_native_solver::NativeSearchSession,
    last_touched: Instant,
}

#[derive(Default, Deserialize)]
#[serde(rename_all = "camelCase")]
struct D4NativeOptimizeOptions {
    remaining_budget_ms: Option<u64>,
    progress_interval_ms: Option<u64>,
}

#[derive(Clone, Serialize)]
#[serde(rename_all = "camelCase")]
struct D4NativeProgress {
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
struct D4NativeRuntimeResult {
    #[serde(flatten)]
    result: d4_native_solver::NativeSolveResult,
    continuation_id: Option<String>,
    threads_used: usize,
    ready_work_items: usize,
}

fn valid_d4_job_id(job_id: &str) -> bool {
    !job_id.is_empty()
        && job_id.len() <= 128
        && job_id
            .chars()
            .all(|character| character.is_ascii_alphanumeric() || matches!(character, '-' | '_'))
}

fn d4_budget(options: &D4NativeOptimizeOptions) -> Duration {
    Duration::from_millis(
        options
            .remaining_budget_ms
            .unwrap_or(D4_INITIAL_BUDGET_MS)
            .clamp(1, D4_INITIAL_BUDGET_MS),
    )
}

fn d4_progress_interval(options: &D4NativeOptimizeOptions) -> Duration {
    Duration::from_millis(
        options
            .progress_interval_ms
            .unwrap_or(D4_PROGRESS_INTERVAL_MS)
            .clamp(50, 1_000),
    )
}

fn next_d4_continuation_id() -> String {
    format!(
        "d4c-{}",
        NEXT_D4_CONTINUATION_ID.fetch_add(1, Ordering::Relaxed)
    )
}

fn register_d4_job(jobs: &D4JobRegistry, job_id: &str) -> Result<Arc<D4JobControl>, String> {
    let signal = Arc::new(D4JobControl::default());
    let mut signals = jobs
        .signals
        .lock()
        .map_err(|_| "D4 작업 레지스트리가 손상되었습니다.".to_string())?;
    if signals.contains_key(job_id) {
        return Err("같은 D4 작업이 이미 실행 중입니다.".to_string());
    }
    signals.insert(job_id.to_string(), Arc::clone(&signal));
    Ok(signal)
}

fn remove_d4_job(jobs: &D4JobRegistry, job_id: &str) -> Result<(), String> {
    jobs.signals
        .lock()
        .map_err(|_| "D4 작업 레지스트리가 손상되었습니다.".to_string())?
        .remove(job_id);
    Ok(())
}

fn insert_d4_session(
    sessions: &Mutex<HashMap<String, D4StoredSession>>,
    continuation_id: String,
    session: d4_native_solver::NativeSearchSession,
) -> Result<(), String> {
    let mut sessions = sessions
        .lock()
        .map_err(|_| "D4 세션 레지스트리가 손상되었습니다.".to_string())?;
    if sessions.len() >= D4_MAX_RESUMABLE_SESSIONS {
        if let Some(oldest) = sessions
            .iter()
            .min_by_key(|(_, entry)| entry.last_touched)
            .map(|(id, _)| id.clone())
        {
            sessions.remove(&oldest);
        }
    }
    sessions.insert(
        continuation_id,
        D4StoredSession {
            session,
            last_touched: Instant::now(),
        },
    );
    Ok(())
}

fn progress_from_session(
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

fn active_d4_worker_count(session_is_complete: bool, threads: usize) -> usize {
    if session_is_complete {
        0
    } else {
        threads.max(1)
    }
}

fn run_d4_session_budget(
    mut session: d4_native_solver::NativeSearchSession,
    session_id: String,
    deadline: Instant,
    progress_interval: Duration,
    threads: usize,
    control: Arc<D4JobControl>,
    progress: tauri::ipc::Channel<D4NativeProgress>,
) -> Result<
    (
        d4_native_solver::NativeSolveResult,
        Option<d4_native_solver::NativeSearchSession>,
    ),
    String,
> {
    let mut last_progress = Instant::now() - progress_interval;
    loop {
        if control.cancel.load(Ordering::Acquire) {
            let mut result = session.snapshot();
            result.status = "cancelled".to_string();
            result.exact = false;
            result.upper_bound = None;
            let event = D4NativeProgress {
                status: "cancelled".to_string(),
                threads_active: 0,
                deadline_remaining_ms: deadline
                    .saturating_duration_since(Instant::now())
                    .as_millis() as u64,
                ..progress_from_session(
                    &session_id,
                    &result,
                    session.ready_work_count(),
                    deadline,
                    threads,
                )
            };
            let _ = progress.send(event);
            return Ok((result, None));
        }
        if control.pause.load(Ordering::Acquire) {
            let mut result = session.snapshot();
            result.status = "paused".to_string();
            result.exact = false;
            let event = D4NativeProgress {
                status: "paused".to_string(),
                threads_active: 0,
                deadline_remaining_ms: deadline
                    .saturating_duration_since(Instant::now())
                    .as_millis() as u64,
                ..progress_from_session(
                    &session_id,
                    &result,
                    session.ready_work_count(),
                    deadline,
                    threads,
                )
            };
            let _ = progress.send(event);
            return Ok((result, (!session.is_complete()).then_some(session)));
        }
        if Instant::now() >= deadline {
            let result = session.snapshot();
            let event = D4NativeProgress {
                status: result.status.clone(),
                threads_active: 0,
                deadline_remaining_ms: 0,
                ..progress_from_session(
                    &session_id,
                    &result,
                    session.ready_work_count(),
                    deadline,
                    threads,
                )
            };
            let _ = progress.send(event);
            return Ok((result, (!session.is_complete()).then_some(session)));
        }
        let result = session.run_parallel_slice_with_control(
            threads.saturating_mul(D4_NODES_PER_WORKER_BATCH),
            threads,
            Some(&control.cancel),
            Some(deadline),
        )?;
        // A worker may have observed cancellation inside a leaf. Re-enter the
        // loop so the cancelled terminal state is emitted before an empty
        // frontier can be interpreted as an exact result.
        if control.cancel.load(Ordering::Acquire) {
            continue;
        }
        if last_progress.elapsed() >= progress_interval || session.is_complete() {
            let status = if session.is_complete() {
                result.status.clone()
            } else {
                "running".to_string()
            };
            let event = D4NativeProgress {
                status,
                // A snapshot is emitted immediately after one bounded batch
                // has joined.  If work remains, the next batch launches the
                // same worker pool straight away; reporting the coordinator
                // itself as "1 active thread" made the live UI claim 1/16
                // despite the search using all requested workers.
                threads_active: active_d4_worker_count(session.is_complete(), threads),
                ..progress_from_session(
                    &session_id,
                    &result,
                    session.ready_work_count(),
                    deadline,
                    threads,
                )
            };
            let _ = progress.send(event);
            last_progress = Instant::now();
        }
        if session.is_complete() {
            return Ok((result, None));
        }
    }
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

fn available_parallel_threads() -> usize {
    std::thread::available_parallelism()
        .map(NonZeroUsize::get)
        .unwrap_or(1)
}

fn d4_initial_shard_target(logical_threads: usize) -> usize {
    logical_threads
        .max(1)
        .saturating_mul(D4_SHARDS_PER_LOGICAL_THREAD)
        .max(logical_threads.max(1))
}

fn d4_queue_memory_budget(total: Option<u64>, available: Option<u64>) -> Option<u64> {
    let limit = match (total, available) {
        (Some(total), Some(available)) => Some((total / 100 * 60).min(available / 100 * 75)),
        (Some(total), None) => Some(total / 100 * 60),
        (None, Some(available)) => Some(available / 100 * 75),
        (None, None) => None,
    }?;
    Some(limit.saturating_sub(D4_QUEUE_SAFETY_RESERVE_BYTES))
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
    // SAFETY: status is initialized with the documented struct size and is
    // valid for the duration of this Windows API call.
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

fn d4_hardware_profile_value() -> D4HardwareProfile {
    let (total_memory_bytes, available_memory_bytes) = physical_memory_status();
    let logical_threads = available_parallel_threads();
    D4HardwareProfile {
        schema: "toram.d4-hardware-profile.v1",
        logical_threads,
        total_memory_bytes,
        available_memory_bytes,
        initial_shard_target: d4_initial_shard_target(logical_threads),
        queue_memory_budget_bytes: d4_queue_memory_budget(
            total_memory_bytes,
            available_memory_bytes,
        ),
    }
}

fn storage_directory_path() -> Result<PathBuf, String> {
    let local_app_data = std::env::var_os("LOCALAPPDATA")
        .filter(|value| !value.is_empty())
        .ok_or_else(|| "LOCALAPPDATA 환경 변수를 찾을 수 없습니다.".to_string())?;
    Ok(PathBuf::from(local_app_data).join(APP_STORAGE_DIRECTORY))
}

fn ensure_storage_directory() -> Result<PathBuf, String> {
    let directory = storage_directory_path()?;
    fs::create_dir_all(&directory)
        .map_err(|error| format!("세팅 저장 폴더를 만들 수 없습니다: {error}"))?;
    if !directory.is_dir() {
        return Err("세팅 저장 경로가 폴더가 아닙니다.".to_string());
    }
    Ok(directory)
}

fn validate_stem(name: &str) -> Result<&str, String> {
    let stem = name.trim();
    if stem.is_empty() {
        return Err("세팅 이름을 입력하세요.".to_string());
    }
    if stem.chars().count() > 80 {
        return Err("세팅 이름은 80자 이하여야 합니다.".to_string());
    }
    if stem == "." || stem == ".." || stem.ends_with('.') || stem.ends_with(' ') {
        return Err("세팅 이름의 끝에는 점이나 공백을 사용할 수 없습니다.".to_string());
    }
    if stem
        .chars()
        .any(|character| character.is_control() || r#"\/:*?"<>|"#.contains(character))
    {
        return Err("세팅 이름에 Windows 금지 문자를 사용할 수 없습니다.".to_string());
    }

    let reserved_base = stem.split('.').next().unwrap_or(stem).to_ascii_uppercase();
    let reserved = matches!(reserved_base.as_str(), "CON" | "PRN" | "AUX" | "NUL")
        || reserved_base.strip_prefix("COM").is_some_and(|number| {
            matches!(number, "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9")
        })
        || reserved_base.strip_prefix("LPT").is_some_and(|number| {
            matches!(number, "1" | "2" | "3" | "4" | "5" | "6" | "7" | "8" | "9")
        });
    if reserved {
        return Err("Windows 예약 장치 이름은 사용할 수 없습니다.".to_string());
    }
    Ok(stem)
}

fn new_setting_path(directory: &Path, name: &str) -> Result<PathBuf, String> {
    Ok(directory.join(format!("{}.json", validate_stem(name)?)))
}

fn existing_setting_path(directory: &Path, file_name: &str) -> Result<PathBuf, String> {
    let file_name = file_name.trim();
    let stem = file_name
        .strip_suffix(".json")
        .ok_or_else(|| "JSON 세팅 파일만 사용할 수 있습니다.".to_string())?;
    validate_stem(stem)?;
    Ok(directory.join(format!("{stem}.json")))
}

fn validate_setting_json(content: &str) -> Result<(), String> {
    let value: Value = serde_json::from_str(content)
        .map_err(|error| format!("세팅 JSON을 해석할 수 없습니다: {error}"))?;
    let root = value
        .as_object()
        .ok_or_else(|| "세팅 JSON의 최상위 값은 객체여야 합니다.".to_string())?;
    if root.get("format").and_then(Value::as_str) != Some(SETTING_FORMAT)
        || root.get("schemaVersion").and_then(Value::as_u64) != Some(SETTING_SCHEMA_VERSION)
    {
        return Err("이 계산기의 세팅 JSON 형식이 아닙니다.".to_string());
    }
    let storage = root
        .get("storage")
        .and_then(Value::as_object)
        .ok_or_else(|| "세팅 JSON에 storage 객체가 없습니다.".to_string())?;
    for key in SETTING_STORAGE_KEYS {
        match storage.get(key) {
            None | Some(Value::Null) | Some(Value::String(_)) => {}
            Some(_) => return Err(format!("세팅 항목의 형식이 올바르지 않습니다: {key}")),
        }
    }
    Ok(())
}

fn reject_symlink(path: &Path) -> Result<(), String> {
    let metadata = fs::symlink_metadata(path)
        .map_err(|error| format!("세팅 파일 정보를 읽을 수 없습니다: {error}"))?;
    if metadata.file_type().is_symlink() || !metadata.is_file() {
        return Err("일반 JSON 세팅 파일만 사용할 수 있습니다.".to_string());
    }
    Ok(())
}

#[tauri::command]
fn settings_directory() -> Result<String, String> {
    Ok(ensure_storage_directory()?.to_string_lossy().into_owned())
}

#[tauri::command]
fn d4_hardware_profile() -> D4HardwareProfile {
    d4_hardware_profile_value()
}

#[tauri::command]
async fn d4_optimize_parallel(
    job_id: String,
    problem: d4_native_solver::NativeProblem,
    options: D4NativeOptimizeOptions,
    progress: tauri::ipc::Channel<D4NativeProgress>,
    jobs: tauri::State<'_, D4JobRegistry>,
) -> Result<D4NativeRuntimeResult, String> {
    if !valid_d4_job_id(&job_id) {
        return Err("D4 작업 식별자가 올바르지 않습니다.".to_string());
    }
    let signal = register_d4_job(&jobs, &job_id)?;
    let continuation_id = next_d4_continuation_id();
    let session_id = continuation_id.clone();
    let budget = d4_budget(&options);
    let progress_interval = d4_progress_interval(&options);
    let deadline = Instant::now() + budget;
    let threads = available_parallel_threads();
    let joined = tauri::async_runtime::spawn_blocking(move || {
        let session = d4_native_solver::NativeSearchSession::new(problem)?;
        run_d4_session_budget(
            session,
            session_id,
            deadline,
            progress_interval,
            threads,
            signal,
            progress,
        )
    })
    .await;
    remove_d4_job(&jobs, &job_id)?;
    let (result, session) =
        joined.map_err(|error| format!("D4 네이티브 작업을 기다리지 못했습니다: {error}"))??;
    let ready_work_items = session
        .as_ref()
        .map_or(0, d4_native_solver::NativeSearchSession::ready_work_count);
    let continuation_id = if let Some(session) = session {
        insert_d4_session(&jobs.sessions, continuation_id.clone(), session)?;
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

#[tauri::command]
async fn resume_d4_optimization(
    job_id: String,
    continuation_id: String,
    options: D4NativeOptimizeOptions,
    progress: tauri::ipc::Channel<D4NativeProgress>,
    jobs: tauri::State<'_, D4JobRegistry>,
) -> Result<D4NativeRuntimeResult, String> {
    if !valid_d4_job_id(&job_id) || !valid_d4_job_id(&continuation_id) {
        return Err("D4 작업 또는 재개 식별자가 올바르지 않습니다.".to_string());
    }
    let stored = jobs
        .sessions
        .lock()
        .map_err(|_| "D4 세션 레지스트리가 손상되었습니다.".to_string())?
        .remove(&continuation_id)
        .ok_or_else(|| "D4 재개 세션이 만료되었거나 존재하지 않습니다.".to_string())?;
    let signal = match register_d4_job(&jobs, &job_id) {
        Ok(signal) => signal,
        Err(error) => {
            insert_d4_session(&jobs.sessions, continuation_id, stored.session)?;
            return Err(error);
        }
    };
    let budget = d4_budget(&options);
    let progress_interval = d4_progress_interval(&options);
    let deadline = Instant::now() + budget;
    let threads = available_parallel_threads();
    let resume_id = continuation_id.clone();
    let joined = tauri::async_runtime::spawn_blocking(move || {
        run_d4_session_budget(
            stored.session,
            resume_id,
            deadline,
            progress_interval,
            threads,
            signal,
            progress,
        )
    })
    .await;
    remove_d4_job(&jobs, &job_id)?;
    let (result, session) = joined
        .map_err(|error| format!("D4 네이티브 재개 작업을 기다리지 못했습니다: {error}"))??;
    let ready_work_items = session
        .as_ref()
        .map_or(0, d4_native_solver::NativeSearchSession::ready_work_count);
    let continuation_id = if let Some(session) = session {
        insert_d4_session(&jobs.sessions, continuation_id.clone(), session)?;
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

#[tauri::command]
fn dispose_d4_optimization(
    continuation_id: String,
    jobs: tauri::State<'_, D4JobRegistry>,
) -> Result<bool, String> {
    if !valid_d4_job_id(&continuation_id) {
        return Err("D4 재개 식별자가 올바르지 않습니다.".to_string());
    }
    Ok(jobs
        .sessions
        .lock()
        .map_err(|_| "D4 세션 레지스트리가 손상되었습니다.".to_string())?
        .remove(&continuation_id)
        .is_some())
}

#[tauri::command]
fn cancel_d4_optimization(
    job_id: String,
    jobs: tauri::State<'_, D4JobRegistry>,
) -> Result<bool, String> {
    if !valid_d4_job_id(&job_id) {
        return Err("D4 작업 식별자가 올바르지 않습니다.".to_string());
    }
    let signals = jobs
        .signals
        .lock()
        .map_err(|_| "D4 작업 레지스트리가 손상되었습니다.".to_string())?;
    let Some(signal) = signals.get(&job_id) else {
        return Ok(false);
    };
    signal.cancel.store(true, Ordering::Release);
    Ok(true)
}

#[tauri::command]
fn pause_d4_optimization(
    job_id: String,
    jobs: tauri::State<'_, D4JobRegistry>,
) -> Result<bool, String> {
    if !valid_d4_job_id(&job_id) {
        return Err("D4 작업 식별자가 올바르지 않습니다.".to_string());
    }
    let signals = jobs
        .signals
        .lock()
        .map_err(|_| "D4 작업 레지스트리가 손상되었습니다.".to_string())?;
    let Some(signal) = signals.get(&job_id) else {
        return Ok(false);
    };
    signal.pause.store(true, Ordering::Release);
    Ok(true)
}

#[tauri::command]
fn list_settings() -> Result<Vec<SettingFile>, String> {
    let directory = ensure_storage_directory()?;
    let mut files = Vec::new();
    for entry in fs::read_dir(&directory)
        .map_err(|error| format!("세팅 파일 목록을 읽을 수 없습니다: {error}"))?
    {
        let entry = entry.map_err(|error| format!("세팅 파일 항목을 읽을 수 없습니다: {error}"))?;
        let metadata = fs::symlink_metadata(entry.path())
            .map_err(|error| format!("세팅 파일 정보를 읽을 수 없습니다: {error}"))?;
        if metadata.file_type().is_symlink() || !metadata.is_file() {
            continue;
        }
        let name = entry.file_name().to_string_lossy().into_owned();
        if !name.to_ascii_lowercase().ends_with(".json") {
            continue;
        }
        let last_modified = metadata
            .modified()
            .ok()
            .and_then(|value| value.duration_since(UNIX_EPOCH).ok())
            .map(|duration| duration.as_millis().min(u128::from(u64::MAX)) as u64)
            .unwrap_or(0);
        files.push(SettingFile {
            name,
            last_modified,
        });
    }
    files.sort_by(|left, right| {
        right
            .last_modified
            .cmp(&left.last_modified)
            .then_with(|| left.name.cmp(&right.name))
    });
    Ok(files)
}

#[tauri::command]
fn save_setting(name: String, content: String) -> Result<(), String> {
    validate_setting_json(&content)?;
    let directory = ensure_storage_directory()?;
    let path = new_setting_path(&directory, &name)?;
    let mut file = OpenOptions::new()
        .write(true)
        .create_new(true)
        .open(&path)
        .map_err(|error| {
            if error.kind() == std::io::ErrorKind::AlreadyExists {
                "같은 이름의 세팅이 이미 있습니다. 덮어쓰기를 사용하세요.".to_string()
            } else {
                format!("세팅 파일을 만들 수 없습니다: {error}")
            }
        })?;
    file.write_all(content.as_bytes())
        .map_err(|error| format!("세팅 파일을 저장할 수 없습니다: {error}"))
}

#[tauri::command]
fn load_setting(name: String) -> Result<String, String> {
    let directory = ensure_storage_directory()?;
    let path = existing_setting_path(&directory, &name)?;
    reject_symlink(&path)?;
    let content = fs::read_to_string(&path)
        .map_err(|error| format!("세팅 파일을 읽을 수 없습니다: {error}"))?;
    validate_setting_json(&content)?;
    Ok(content)
}

#[tauri::command]
fn overwrite_setting(name: String, content: String) -> Result<(), String> {
    validate_setting_json(&content)?;
    let directory = ensure_storage_directory()?;
    let path = existing_setting_path(&directory, &name)?;
    reject_symlink(&path)?;
    let mut file = OpenOptions::new()
        .write(true)
        .truncate(true)
        .open(&path)
        .map_err(|error| format!("덮어쓸 세팅 파일을 열 수 없습니다: {error}"))?;
    file.write_all(content.as_bytes())
        .map_err(|error| format!("세팅 파일을 덮어쓸 수 없습니다: {error}"))
}

#[tauri::command]
fn delete_setting(name: String) -> Result<(), String> {
    let directory = ensure_storage_directory()?;
    let path = existing_setting_path(&directory, &name)?;
    reject_symlink(&path)?;
    fs::remove_file(&path).map_err(|error| format!("세팅 파일을 삭제할 수 없습니다: {error}"))
}

fn main() {
    tauri::Builder::default()
        .manage(D4JobRegistry::default())
        .invoke_handler(tauri::generate_handler![
            settings_directory,
            d4_hardware_profile,
            d4_optimize_parallel,
            resume_d4_optimization,
            dispose_d4_optimization,
            cancel_d4_optimization,
            pause_d4_optimization,
            list_settings,
            save_setting,
            load_setting,
            overwrite_setting,
            delete_setting
        ])
        .run(tauri::generate_context!())
        .expect("failed to run Toram Online Auto Build Calculator");
}

#[cfg(test)]
mod tests {
    use super::*;

    fn valid_json() -> String {
        let storage = SETTING_STORAGE_KEYS
            .into_iter()
            .map(|key| (key.to_string(), Value::Null))
            .collect::<serde_json::Map<_, _>>();
        serde_json::json!({
            "format": SETTING_FORMAT,
            "schemaVersion": SETTING_SCHEMA_VERSION,
            "name": "test",
            "storage": storage
        })
        .to_string()
    }

    fn small_native_problem() -> d4_native_solver::NativeProblem {
        serde_json::from_value(serde_json::json!({
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
    fn accepts_valid_names_and_rejects_path_or_windows_names() {
        assert_eq!(validate_stem("내 세팅").unwrap(), "내 세팅");
        for invalid in [
            "",
            "..",
            "a/b",
            r"a\b",
            "a:b",
            "CON",
            "com1.txt",
            "trailing.",
        ] {
            assert!(
                validate_stem(invalid).is_err(),
                "{invalid} must be rejected"
            );
        }
    }

    #[test]
    fn requires_json_extension_for_existing_files() {
        let directory = Path::new("C:/example");
        assert!(existing_setting_path(directory, "valid.json").is_ok());
        assert!(existing_setting_path(directory, "valid.txt").is_err());
        assert!(existing_setting_path(directory, "../escape.json").is_err());
    }

    #[test]
    fn validates_snapshot_contract() {
        assert!(validate_setting_json(&valid_json()).is_ok());
        assert!(validate_setting_json("{}").is_err());
        assert!(validate_setting_json("not json").is_err());
        let wrong_value = serde_json::json!({
            "format": SETTING_FORMAT,
            "schemaVersion": SETTING_SCHEMA_VERSION,
            "storage": { SETTING_STORAGE_KEYS[0]: 42 }
        });
        assert!(validate_setting_json(&wrong_value.to_string()).is_err());
    }

    #[test]
    fn d4_hardware_profile_uses_at_least_one_logical_thread() {
        let profile = d4_hardware_profile_value();
        assert_eq!(profile.schema, "toram.d4-hardware-profile.v1");
        assert!(profile.logical_threads >= 1);
        assert!(profile.initial_shard_target >= profile.logical_threads);
        if let (Some(total), Some(available)) =
            (profile.total_memory_bytes, profile.available_memory_bytes)
        {
            assert!(total >= available);
        }
    }

    #[test]
    fn d4_memory_budget_uses_the_tighter_total_and_available_limits() {
        const MIB: u64 = 1024 * 1024;
        assert_eq!(d4_initial_shard_target(16), 128);
        assert_eq!(d4_initial_shard_target(0), D4_SHARDS_PER_LOGICAL_THREAD);
        assert_eq!(
            d4_queue_memory_budget(Some(16_000 * MIB), Some(4_000 * MIB)),
            Some(3_000 * MIB - D4_QUEUE_SAFETY_RESERVE_BYTES)
        );
        assert_eq!(d4_queue_memory_budget(None, None), None);
    }

    #[test]
    fn running_progress_reports_the_search_worker_pool_not_the_coordinator() {
        assert_eq!(active_d4_worker_count(false, 16), 16);
        assert_eq!(active_d4_worker_count(false, 0), 1);
        assert_eq!(active_d4_worker_count(true, 16), 0);
    }

    #[test]
    fn deadline_keeps_a_safe_resumable_frontier() {
        let session = d4_native_solver::NativeSearchSession::new(small_native_problem()).unwrap();
        let channel = tauri::ipc::Channel::<D4NativeProgress>::new(|_| Ok(()));
        let control = Arc::new(D4JobControl::default());
        let (bounded, preserved) = run_d4_session_budget(
            session,
            "d4c-test".to_string(),
            Instant::now(),
            Duration::from_millis(50),
            2,
            control,
            channel,
        )
        .unwrap();
        assert_eq!(bounded.status, "bounded");
        let mut resumed = preserved.expect("deadline must keep a nonterminal frontier");
        while !resumed.is_complete() {
            resumed.run_slice(1).unwrap();
        }
        assert_eq!(resumed.snapshot().status, "exact");
    }

    #[test]
    fn cancellation_discards_the_resumable_frontier() {
        let session = d4_native_solver::NativeSearchSession::new(small_native_problem()).unwrap();
        let channel = tauri::ipc::Channel::<D4NativeProgress>::new(|_| Ok(()));
        let control = Arc::new(D4JobControl {
            cancel: AtomicBool::new(true),
            pause: AtomicBool::new(false),
        });
        let (result, preserved) = run_d4_session_budget(
            session,
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
    fn pause_keeps_the_resumable_frontier_for_exact_resume() {
        let session = d4_native_solver::NativeSearchSession::new(small_native_problem()).unwrap();
        let channel = tauri::ipc::Channel::<D4NativeProgress>::new(|_| Ok(()));
        let control = Arc::new(D4JobControl {
            cancel: AtomicBool::new(false),
            pause: AtomicBool::new(true),
        });
        let (paused, preserved) = run_d4_session_budget(
            session,
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
        let mut resumed = preserved.expect("pause must preserve the frontier");
        while !resumed.is_complete() {
            resumed.run_slice(1).unwrap();
        }
        assert_eq!(resumed.snapshot().status, "exact");
    }

    #[test]
    fn session_registry_evicts_the_oldest_entry_at_capacity() {
        let sessions = Mutex::new(HashMap::new());
        for index in 0..=D4_MAX_RESUMABLE_SESSIONS {
            insert_d4_session(
                &sessions,
                format!("d4c-{index}"),
                d4_native_solver::NativeSearchSession::new(small_native_problem()).unwrap(),
            )
            .unwrap();
            std::thread::sleep(Duration::from_millis(1));
        }
        let sessions = sessions.lock().unwrap();
        assert_eq!(sessions.len(), D4_MAX_RESUMABLE_SESSIONS);
        assert!(!sessions.contains_key("d4c-0"));
        assert!(sessions.contains_key(&format!("d4c-{D4_MAX_RESUMABLE_SESSIONS}")));
    }
}
