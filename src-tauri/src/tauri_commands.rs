use crate::crysta_native_solver::NativeProblem;
use crate::crysta_service::{
    CrystaOptimizationHardwareProfile, CrystaOptimizationNativeOptimizeOptions,
    CrystaOptimizationNativeProgress, CrystaOptimizationNativeRuntimeResult,
    CrystaOptimizationService,
};
use crate::settings::SettingFile;
use crate::settings::SettingsService;
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
pub fn crysta_hardware_profile() -> CrystaOptimizationHardwareProfile {
    CrystaOptimizationService::hardware_profile()
}
#[tauri::command]
pub async fn crysta_optimize_parallel(
    job_id: String,
    problem: NativeProblem,
    options: CrystaOptimizationNativeOptimizeOptions,
    progress: tauri::ipc::Channel<CrystaOptimizationNativeProgress>,
    service: tauri::State<'_, CrystaOptimizationService>,
) -> Result<CrystaOptimizationNativeRuntimeResult, String> {
    service.optimize(job_id, problem, options, progress).await
}
#[tauri::command]
pub async fn resume_crysta_optimization(
    job_id: String,
    continuation_id: String,
    options: CrystaOptimizationNativeOptimizeOptions,
    progress: tauri::ipc::Channel<CrystaOptimizationNativeProgress>,
    service: tauri::State<'_, CrystaOptimizationService>,
) -> Result<CrystaOptimizationNativeRuntimeResult, String> {
    service
        .resume(job_id, continuation_id, options, progress)
        .await
}
#[tauri::command]
pub fn dispose_crysta_optimization(
    continuation_id: String,
    service: tauri::State<'_, CrystaOptimizationService>,
) -> Result<bool, String> {
    service.dispose(continuation_id)
}
#[tauri::command]
pub fn cancel_crysta_optimization(
    job_id: String,
    service: tauri::State<'_, CrystaOptimizationService>,
) -> Result<bool, String> {
    service.cancel(job_id)
}
#[tauri::command]
pub fn pause_crysta_optimization(
    job_id: String,
    service: tauri::State<'_, CrystaOptimizationService>,
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
