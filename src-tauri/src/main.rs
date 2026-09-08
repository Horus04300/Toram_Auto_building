#![cfg_attr(not(debug_assertions), windows_subsystem = "windows")]

// The executable root only composes modules and managed state. Command DTOs
// remain stable in tauri_commands; domain work stays in services/repositories.
#[allow(dead_code)]
mod d4_native_evaluator;
#[allow(dead_code)]
mod d4_native_solver;
#[allow(dead_code)]
mod d4_parallel_runtime;
mod d4_service;
mod settings_repository;
mod settings_service;
mod tauri_commands;
mod update_service;

use d4_service::D4OptimizationService;
use tauri_commands::*;

fn main() {
    tauri::Builder::default()
        .plugin(tauri_plugin_updater::Builder::new().build())
        .manage(D4OptimizationService::default())
        .manage(update_service::UpdateService::default())
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
            delete_setting,
            check_for_update,
            download_update,
            install_update
        ])
        .run(tauri::generate_context!())
        .expect("failed to run Toram Online Auto Build Calculator");
}
