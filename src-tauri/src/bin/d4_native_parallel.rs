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
use std::time::{Duration, Instant};

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
    if let Ok(budget) = std::env::var("D4_SESSION_BENCH_MS") {
        let budget = budget.parse::<u64>().map_err(|error| error.to_string())?;
        let started = Instant::now();
        let mut session = d4_native_solver::NativeSearchSession::new(request.problem)?;
        let preparation_ms = started.elapsed().as_secs_f64() * 1000.0;
        let deadline = started + Duration::from_millis(budget);
        let mut batches = 0_u64;
        while !session.is_complete() && Instant::now() < deadline {
            session.advance_parallel_slice_with_control(
                threads.saturating_mul(d4_native_solver::SESSION_NODES_PER_WORKER),
                threads,
                cancel.as_ref(),
                Some(deadline),
            )?;
            batches += 1;
            if cancel
                .as_ref()
                .is_some_and(|signal| signal.load(std::sync::atomic::Ordering::Acquire))
            {
                break;
            }
        }
        let mut snapshot = session.snapshot();
        if cancel
            .as_ref()
            .is_some_and(|signal| signal.load(std::sync::atomic::Ordering::Acquire))
        {
            snapshot.status = "cancelled".into();
            snapshot.exact = false;
            snapshot.upper_bound = None;
        }
        let mut output = serde_json::to_value(snapshot).map_err(|error| error.to_string())?;
        output["sessionPreparationMs"] = preparation_ms.into();
        output["sessionWallMs"] = (started.elapsed().as_secs_f64() * 1000.0).into();
        output["sessionBatches"] = batches.into();
        println!("{}", output);
        return Ok(());
    }
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
