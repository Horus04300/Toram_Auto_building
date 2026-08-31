//! Development bridge for P5 shared-memory CPU exact search.

#[path = "../d4_native_evaluator.rs"]
mod d4_native_evaluator;
#[allow(dead_code)]
#[path = "../d4_native_solver.rs"]
mod d4_native_solver;
#[allow(dead_code)]
#[path = "../d4_parallel_runtime.rs"]
mod d4_parallel_runtime;

use serde::Deserialize;
use std::io::{self, Read};
use std::sync::atomic::AtomicBool;
use std::sync::Arc;
use std::time::Duration;

#[derive(Deserialize)]
struct ParallelRequest {
    #[serde(flatten)]
    problem: d4_native_solver::NativeProblem,
    #[serde(default)]
    threads: Option<usize>,
    #[serde(rename = "cancelAfterMs", default)]
    cancel_after_ms: Option<u64>,
}

fn main() -> Result<(), String> {
    let mut input = String::new();
    io::stdin()
        .read_to_string(&mut input)
        .map_err(|error| error.to_string())?;
    let request = serde_json::from_str::<ParallelRequest>(&input)
        .map_err(|error| format!("D4 native parallel input is invalid: {error}"))?;
    let threads = request.threads.unwrap_or_else(|| {
        std::thread::available_parallelism()
            .map(usize::from)
            .unwrap_or(1)
    });
    let cancel = request.cancel_after_ms.map(|delay| {
        let signal = Arc::new(AtomicBool::new(false));
        let timer_signal = Arc::clone(&signal);
        std::thread::spawn(move || {
            std::thread::sleep(Duration::from_millis(delay));
            timer_signal.store(true, std::sync::atomic::Ordering::Release);
        });
        signal
    });
    let result = match cancel.as_deref() {
        Some(signal) => {
            d4_native_solver::solve_exact_parallel_cancellable(&request.problem, threads, signal)?
        }
        None => d4_native_solver::solve_exact_parallel(&request.problem, threads)?,
    };
    println!(
        "{}",
        serde_json::to_string(&result).map_err(|error| error.to_string())?
    );
    Ok(())
}
