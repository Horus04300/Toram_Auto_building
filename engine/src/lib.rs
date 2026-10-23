// Native and WASM compile these same sources; no second solver implementation.
#[path = "evaluator.rs"]
pub mod crysta_native_evaluator;
#[path = "solver.rs"]
pub mod crysta_native_solver;

#[cfg(target_arch = "wasm32")]
mod wasm;
