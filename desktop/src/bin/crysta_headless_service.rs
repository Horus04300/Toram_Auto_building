use toram_optimization_core::crysta_native_solver;
// Shared Rust core test/measurement bridge.
#[allow(dead_code)]
#[path = "../optimization/parallel_runtime.rs"]
mod crysta_parallel_runtime;
#[allow(dead_code)]
#[path = "../optimization/service.rs"]
mod crysta_service;

use crysta_service::{
    CrystaOptimizationNativeOptimizeOptions, CrystaOptimizationNativeProgress,
    CrystaOptimizationService,
};
use serde::Deserialize;
use serde_json::{json, Value};
use std::io::{self, BufRead, Write};

#[derive(Deserialize)]
struct Request {
    id: u64,
    command: String,
    #[serde(default)]
    args: Value,
}

#[derive(Deserialize)]
#[serde(rename_all = "camelCase")]
struct OptimizeArgs {
    job_id: String,
    problem: crysta_native_solver::NativeProblem,
    options: CrystaOptimizationNativeOptimizeOptions,
}

#[derive(Deserialize)]
#[serde(rename_all = "camelCase")]
struct ResumeArgs {
    job_id: String,
    continuation_id: String,
    options: CrystaOptimizationNativeOptimizeOptions,
}

fn emit(value: &Value) -> io::Result<()> {
    let mut out = io::stdout().lock();
    serde_json::to_writer(&mut out, value)?;
    writeln!(out)?;
    out.flush()
}

fn progress(id: u64) -> tauri::ipc::Channel<CrystaOptimizationNativeProgress> {
    tauri::ipc::Channel::new(move |body| {
        let value: Value = match body {
            tauri::ipc::InvokeResponseBody::Json(text) => serde_json::from_str(&text)?,
            tauri::ipc::InvokeResponseBody::Raw(bytes) => serde_json::from_slice(&bytes)?,
        };
        emit(&json!({"id":id,"type":"progress","value":value}))?;
        Ok(())
    })
}

async fn dispatch(service: &CrystaOptimizationService, request: Request) -> Result<Value, String> {
    match request.command.as_str() {
        "crysta_hardware_profile" => {
            serde_json::to_value(CrystaOptimizationService::hardware_profile())
                .map_err(|e| e.to_string())
        }
        "crysta_optimize_parallel" => {
            let args: OptimizeArgs =
                serde_json::from_value(request.args).map_err(|e| e.to_string())?;
            let result = service
                .optimize(
                    args.job_id,
                    args.problem,
                    args.options,
                    progress(request.id),
                )
                .await?;
            serde_json::to_value(result).map_err(|e| e.to_string())
        }
        "resume_crysta_optimization" => {
            let args: ResumeArgs =
                serde_json::from_value(request.args).map_err(|e| e.to_string())?;
            let result = service
                .resume(
                    args.job_id,
                    args.continuation_id,
                    args.options,
                    progress(request.id),
                )
                .await?;
            serde_json::to_value(result).map_err(|e| e.to_string())
        }
        "dispose_crysta_optimization" => {
            let id = request.args["continuationId"]
                .as_str()
                .ok_or("Missing continuationId")?;
            service.dispose(id.to_owned()).map(Value::Bool)
        }
        _ => Err(format!(
            "Unsupported measurement command: {}",
            request.command
        )),
    }
}

fn main() -> Result<(), Box<dyn std::error::Error>> {
    let service = CrystaOptimizationService::default();
    for line in io::stdin().lock().lines() {
        let request: Request = serde_json::from_str(&line?)?;
        let id = request.id;
        let packet = match tauri::async_runtime::block_on(dispatch(&service, request)) {
            Ok(value) => json!({"id":id,"type":"result","value":value}),
            Err(error) => json!({"id":id,"type":"error","error":error}),
        };
        emit(&packet)?;
    }
    Ok(())
}
