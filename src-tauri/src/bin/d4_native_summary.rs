//! Development-only JSON-lines bridge for JavaScript/Rust evaluator parity.
//!
//! This binary is intentionally not registered as a Tauri command.  The Node
//! parity test starts it once, sends a batch of frozen D4 aggregate cases, and
//! compares the returned summaries with the JavaScript kernel.

#[path = "../d4_native_evaluator.rs"]
mod d4_native_evaluator;

use std::io::{self, Read};

use serde::Deserialize;
use serde_json::{json, Value};

#[derive(Deserialize)]
struct Request {
    cases: Vec<Case>,
}

#[derive(Deserialize)]
struct Case {
    id: String,
    #[serde(rename = "baseContext")]
    base_context: Value,
    stats: Value,
}

fn main() -> Result<(), String> {
    let mut input = String::new();
    io::stdin()
        .read_to_string(&mut input)
        .map_err(|error| format!("D4 parity input read failed: {error}"))?;
    let request: Request = serde_json::from_str(&input)
        .map_err(|error| format!("D4 parity input is invalid: {error}"))?;
    let mut results = Vec::with_capacity(request.cases.len());
    for case in request.cases {
        let summary = d4_native_evaluator::evaluate_summary(&case.base_context, &case.stats)
            .map_err(|error| format!("D4 parity case {} failed: {error}", case.id))?;
        let prepared = d4_native_evaluator::PreparedContext::from(case.base_context.clone());
        let stats = serde_json::from_value(case.stats.clone())
            .map_err(|error| format!("D4 parity stats failed: {error}"))?;
        let cached = d4_native_evaluator::evaluate_summary_from_map(&prepared, &stats)?;
        let native_stats = serde_json::from_value(case.stats.clone())
            .map_err(|error| format!("Native stats: {error}"))?;
        let native =
            d4_native_evaluator::evaluate_summary_from_native_stats(&prepared, &native_stats)?;
        if summary != cached || summary != native {
            return Err(format!("D4 prepared context mismatch in {}", case.id));
        }
        results.push(json!({ "id": case.id, "summary": summary }));
    }
    println!(
        "{}",
        serde_json::to_string(
            &json!({ "schema": "toram.d4-native-summary.v1", "results": results })
        )
        .map_err(|error| format!("D4 parity output serialization failed: {error}"))?
    );
    Ok(())
}
