#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

// The executable root only composes modules and managed state. Command DTOs
// remain stable in tauri_commands; domain work stays in services/repositories.
use toram_optimization_core::crysta_native_solver;
mod account_browser;
#[path = "optimization/service.rs"]
mod crysta_service;
mod settings;
mod tauri_commands;
mod update_service;

use crysta_service::CrystaOptimizationService;
use tauri_commands::*;

fn main() {
    tauri::Builder::default()
        .plugin(tauri_plugin_updater::Builder::new().build())
        .manage(CrystaOptimizationService::default())
        .manage(update_service::UpdateService::default())
        .invoke_handler(tauri::generate_handler![
            open_account_login,
            settings_directory,
            crysta_hardware_profile,
            crysta_optimize_parallel,
            resume_crysta_optimization,
            dispose_crysta_optimization,
            cancel_crysta_optimization,
            pause_crysta_optimization,
            list_settings,
            save_setting,
            load_setting,
            overwrite_setting,
            delete_setting,
            check_for_update,
            download_update,
            install_update
        ])
        .run(tauri::generate_context!())
        .expect("failed to run Toram Online Auto Build Calculator");
}
