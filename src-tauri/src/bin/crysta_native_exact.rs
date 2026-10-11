//! Development bridge for the native exact native exact-solver parity gate.

#[path = "../optimization/evaluator.rs"]
mod crysta_native_evaluator;
#[allow(dead_code)]
#[path = "../optimization/solver.rs"]
mod crysta_native_solver;
#[allow(dead_code)]
#[path = "../optimization/parallel_runtime.rs"]
mod crysta_parallel_runtime;

use std::io::{self, Read};

fn main() -> Result<(), String> {
    let mut input = String::new();
    io::stdin()
        .read_to_string(&mut input)
        .map_err(|error| error.to_string())?;
    let problem = serde_json::from_str::<crysta_native_solver::NativeProblem>(&input)
        .map_err(|error| format!("CrystaOptimization native exact input is invalid: {error}"))?;
    let result = crysta_native_solver::solve_exact(&problem)?;
    println!(
        "{}",
        serde_json::to_string(&result).map_err(|error| error.to_string())?
    );
    Ok(())
}
