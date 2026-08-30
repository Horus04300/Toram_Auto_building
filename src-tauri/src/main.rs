#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

// Native D4 is exposed only after the JS/Rust parity and exact-tie gates.
#[allow(dead_code)]
mod d4_native_evaluator;
#[allow(dead_code)]
mod d4_native_solver;
#[allow(dead_code)]
mod d4_parallel_runtime;

use serde::Serialize;
use serde_json::Value;
use std::collections::HashMap;
use std::fs::{self, OpenOptions};
use std::io::Write;
use std::num::NonZeroUsize;
use std::path::{Path, PathBuf};
use std::sync::atomic::{AtomicBool, Ordering};
use std::sync::{Arc, Mutex};
use std::time::UNIX_EPOCH;

const APP_STORAGE_DIRECTORY: &str = "ToramOnlineAutoBuildCalculator";
const SETTING_FORMAT: &str = "toram-auto-build-setting";
const SETTING_SCHEMA_VERSION: u64 = 1;
const D4_SHARDS_PER_LOGICAL_THREAD: usize = 8;
const D4_QUEUE_SAFETY_RESERVE_BYTES: u64 = 512 * 1024 * 1024;
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
struct D4JobRegistry {
    signals: Mutex<HashMap<String, Arc<AtomicBool>>>,
}

fn valid_d4_job_id(job_id: &str) -> bool {
    !job_id.is_empty()
        && job_id.len() <= 128
        && job_id
            .chars()
            .all(|character| character.is_ascii_alphanumeric() || matches!(character, '-' | '_'))
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
    jobs: tauri::State<'_, D4JobRegistry>,
) -> Result<d4_native_solver::NativeParallelSolveResult, String> {
    if !valid_d4_job_id(&job_id) {
        return Err("D4 작업 식별자가 올바르지 않습니다.".to_string());
    }
    let signal = Arc::new(AtomicBool::new(false));
    {
        let mut signals = jobs
            .signals
            .lock()
            .map_err(|_| "D4 작업 레지스트리가 손상되었습니다.".to_string())?;
        if signals.contains_key(&job_id) {
            return Err("같은 D4 작업이 이미 실행 중입니다.".to_string());
        }
        signals.insert(job_id.clone(), Arc::clone(&signal));
    }
    let threads = available_parallel_threads();
    let joined = tauri::async_runtime::spawn_blocking(move || {
        d4_native_solver::solve_exact_parallel_cancellable(&problem, threads, &signal)
    })
    .await;
    jobs.signals
        .lock()
        .map_err(|_| "D4 작업 레지스트리가 손상되었습니다.".to_string())?
        .remove(&job_id);
    let result =
        joined.map_err(|error| format!("D4 네이티브 작업을 기다리지 못했습니다: {error}"))?;
    result
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
    signal.store(true, Ordering::Release);
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
            cancel_d4_optimization,
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
}
