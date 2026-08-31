//! Development bridge for the P4 native exact-solver parity gate.

#[path = "../d4_native_evaluator.rs"]
mod d4_native_evaluator;
#[allow(dead_code)]
#[path = "../d4_native_solver.rs"]
mod d4_native_solver;
#[allow(dead_code)]
#[path = "../d4_parallel_runtime.rs"]
mod d4_parallel_runtime;

use std::io::{self, Read};

fn main() -> Result<(), String> {
    let mut input = String::new();
    io::stdin()
        .read_to_string(&mut input)
        .map_err(|error| error.to_string())?;
    let problem = serde_json::from_str::<d4_native_solver::NativeProblem>(&input)
        .map_err(|error| format!("D4 native exact input is invalid: {error}"))?;
    let result = d4_native_solver::solve_exact(&problem)?;
    println!(
        "{}",
        serde_json::to_string(&result).map_err(|error| error.to_string())?
    );
    Ok(())
}
