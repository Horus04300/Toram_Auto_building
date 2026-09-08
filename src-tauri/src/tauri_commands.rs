use crate::d4_native_solver::NativeProblem;
use crate::d4_service::{
    D4HardwareProfile, D4NativeOptimizeOptions, D4NativeProgress, D4NativeRuntimeResult,
    D4OptimizationService,
};
use crate::settings_repository::SettingFile;
use crate::settings_service::SettingsService;
use crate::update_service::{UpdateFailure, UpdateInfo, UpdateProgress, UpdateService};

#[tauri::command]
pub async fn check_for_update(
    app: tauri::AppHandle,
    service: tauri::State<'_, UpdateService>,
) -> Result<Option<UpdateInfo>, UpdateFailure> {
    service.check(app).await
}
#[tauri::command]
pub async fn download_update(
    version: String,
    progress: tauri::ipc::Channel<UpdateProgress>,
    service: tauri::State<'_, UpdateService>,
) -> Result<(), UpdateFailure> {
    service.download(version, progress).await
}
#[tauri::command]
pub async fn install_update(
    version: String,
    service: tauri::State<'_, UpdateService>,
) -> Result<(), UpdateFailure> {
    service.install(version)
}

#[tauri::command]
pub fn settings_directory() -> Result<String, String> {
    SettingsService::directory()
}
#[tauri::command]
pub fn d4_hardware_profile() -> D4HardwareProfile {
    D4OptimizationService::hardware_profile()
}
#[tauri::command]
pub async fn d4_optimize_parallel(
    job_id: String,
    problem: NativeProblem,
    options: D4NativeOptimizeOptions,
    progress: tauri::ipc::Channel<D4NativeProgress>,
    service: tauri::State<'_, D4OptimizationService>,
) -> Result<D4NativeRuntimeResult, String> {
    service.optimize(job_id, problem, options, progress).await
}
#[tauri::command]
pub async fn resume_d4_optimization(
    job_id: String,
    continuation_id: String,
    options: D4NativeOptimizeOptions,
    progress: tauri::ipc::Channel<D4NativeProgress>,
    service: tauri::State<'_, D4OptimizationService>,
) -> Result<D4NativeRuntimeResult, String> {
    service
        .resume(job_id, continuation_id, options, progress)
        .await
}
#[tauri::command]
pub fn dispose_d4_optimization(
    continuation_id: String,
    service: tauri::State<'_, D4OptimizationService>,
) -> Result<bool, String> {
    service.dispose(continuation_id)
}
#[tauri::command]
pub fn cancel_d4_optimization(
    job_id: String,
    service: tauri::State<'_, D4OptimizationService>,
) -> Result<bool, String> {
    service.cancel(job_id)
}
#[tauri::command]
pub fn pause_d4_optimization(
    job_id: String,
    service: tauri::State<'_, D4OptimizationService>,
) -> Result<bool, String> {
    service.pause(job_id)
}
#[tauri::command]
pub fn list_settings() -> Result<Vec<SettingFile>, String> {
    SettingsService::list()
}
#[tauri::command]
pub fn save_setting(name: String, content: String) -> Result<(), String> {
    SettingsService::save(name, content)
}
#[tauri::command]
pub fn load_setting(name: String) -> Result<String, String> {
    SettingsService::load(name)
}
#[tauri::command]
pub fn overwrite_setting(name: String, content: String) -> Result<(), String> {
    SettingsService::overwrite(name, content)
}
#[tauri::command]
pub fn delete_setting(name: String) -> Result<(), String> {
    SettingsService::delete(name)
}
