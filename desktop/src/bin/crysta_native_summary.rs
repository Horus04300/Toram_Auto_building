use toram_optimization_core::crysta_native_evaluator;
// Shared Rust core test/measurement bridge.
// Shared Rust core test/measurement bridge.
// Shared Rust core test/measurement bridge.
// Shared Rust core test/measurement bridge.
// Shared Rust core test/measurement bridge.

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
        .map_err(|error| format!("CrystaOptimization parity input read failed: {error}"))?;
    let request: Request = serde_json::from_str(&input)
        .map_err(|error| format!("CrystaOptimization parity input is invalid: {error}"))?;
    let mut results = Vec::with_capacity(request.cases.len());
    for case in request.cases {
        let summary = crysta_native_evaluator::evaluate_summary(&case.base_context, &case.stats)
            .map_err(|error| {
                format!("CrystaOptimization parity case {} failed: {error}", case.id)
            })?;
        let prepared = crysta_native_evaluator::PreparedContext::from(case.base_context.clone());
        let stats = serde_json::from_value(case.stats.clone())
            .map_err(|error| format!("CrystaOptimization parity stats failed: {error}"))?;
        let cached = crysta_native_evaluator::evaluate_summary_from_map(&prepared, &stats)?;
        let native_stats = serde_json::from_value(case.stats.clone())
            .map_err(|error| format!("Native stats: {error}"))?;
        let native =
            crysta_native_evaluator::evaluate_summary_from_native_stats(&prepared, &native_stats)?;
        if summary != cached || summary != native {
            return Err(format!(
                "CrystaOptimization prepared context mismatch in {}",
                case.id
            ));
        }
        let utility = [
            summary.final_max_hp,
            summary.final_max_mp,
            summary.ampr_before_dual,
            summary.normal_attack_crit,
            summary.final_aspd,
        ];
        for coordinate in 0..5 {
            for offset in [-0.5, 0.0, 0.5] {
                let minimum = utility[coordinate] as f64 + offset;
                let filtered = crysta_native_evaluator::evaluate_feasible_summary(
                    &prepared,
                    &native_stats,
                    |index, value| {
                        assert_eq!(value, utility[index], "utility mismatch in {}", case.id);
                        index != coordinate || value as f64 >= minimum
                    },
                )?;
                let expected = (utility[coordinate] as f64 >= minimum).then_some(&summary);
                if filtered.as_ref() != expected {
                    return Err(format!(
                        "CrystaOptimization utility precheck mismatch in {}",
                        case.id
                    ));
                }
            }
        }
        let cast = crysta_native_evaluator::candidate_cast_metrics(&prepared, &native_stats);
        results.push(json!({ "id": case.id, "summary": summary, "castMetrics": cast }));
    }
    println!(
        "{}",
        serde_json::to_string(
            &json!({ "schema": "toram.crysta-native-summary.v1", "results": results })
        )
        .map_err(|error| format!(
            "CrystaOptimization parity output serialization failed: {error}"
        ))?
    );
    Ok(())
}
