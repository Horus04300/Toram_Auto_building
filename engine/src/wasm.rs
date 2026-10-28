use crate::crysta_native_solver::{NativeProblem, NativeSearchSession};
use wasm_bindgen::prelude::*;

#[cfg(feature = "wasm-threads")]
#[allow(unused_imports)]
pub use wasm_bindgen_rayon::init_thread_pool;

#[wasm_bindgen]
pub struct SearchSession {
    session: NativeSearchSession,
}

#[wasm_bindgen]
impl SearchSession {
    #[wasm_bindgen(constructor)]
    pub fn new(json: &str) -> Result<SearchSession, JsValue> {
        let problem: NativeProblem =
            serde_json::from_str(json).map_err(|e| JsValue::from_str(&e.to_string()))?;
        let session = NativeSearchSession::new(problem).map_err(|e| JsValue::from_str(&e))?;
        Ok(Self { session })
    }

    pub fn snapshot(&self) -> Result<String, JsValue> {
        serde_json::to_string(&self.session.snapshot())
            .map_err(|e| JsValue::from_str(&e.to_string()))
    }

    pub fn step(&mut self, nodes: u32) -> Result<bool, JsValue> {
        self.session
            .advance_slice(nodes.clamp(1, 256) as usize)
            .map_err(|e| JsValue::from_str(&e))?;
        Ok(self.session.is_complete())
    }

    pub fn is_complete(&self) -> bool {
        self.session.is_complete()
    }

    #[cfg(feature = "wasm-threads")]
    pub fn step_parallel(&mut self, nodes: u32, threads: u32) -> Result<bool, JsValue> {
        self.session
            .advance_parallel_slice_with_control(
                nodes.clamp(1, 4096) as usize,
                threads.clamp(1, 64) as usize,
                None,
                Some(web_time::Instant::now() + web_time::Duration::from_millis(16)),
            )
            .map_err(|e| JsValue::from_str(&e))?;
        Ok(self.session.is_complete())
    }
}

#[wasm_bindgen]
pub fn evaluate_context_json(input: &str, summary_only: bool) -> Result<String, JsValue> {
    let base: serde_json::Value =
        serde_json::from_str(input).map_err(|e| JsValue::from_str(&e.to_string()))?;
    let result = crate::crysta_native_evaluator::evaluate_context(&base, summary_only)
        .map_err(|e| JsValue::from_str(&e))?;
    serde_json::to_string(&result).map_err(|e| JsValue::from_str(&e.to_string()))
}
#[wasm_bindgen]
pub fn candidate_supply_bases_json(input: &str) -> Result<String, JsValue> {
    let base: serde_json::Value =
        serde_json::from_str(input).map_err(|e| JsValue::from_str(&e.to_string()))?;
    let result = crate::crysta_native_evaluator::candidate_supply_bases(&base)
        .map_err(|e| JsValue::from_str(&e))?;
    serde_json::to_string(&result).map_err(|e| JsValue::from_str(&e.to_string()))
}
#[wasm_bindgen]
pub fn exact_ratio(value: f64, rate: f64, divisor: f64, flat: f64) -> f64 {
    crate::crysta_native_evaluator::decimal_math::floor_ratio(value, rate, divisor, flat)
}
#[wasm_bindgen]
pub fn exact_percent(value: f64, rate: f64, flat: f64) -> f64 {
    crate::crysta_native_evaluator::decimal_math::floor_percent(value, rate, flat)
}
#[wasm_bindgen]
pub fn proportional_attack_json(input: &str, magic: bool) -> Result<f64, JsValue> {
    let base: serde_json::Value =
        serde_json::from_str(input).map_err(|e| JsValue::from_str(&e.to_string()))?;
    let prefix = if magic { "matkUp" } else { "atkUp" };
    let rates = ["STR", "INT", "VIT", "AGI", "DEX"].map(|key| {
        base.get(format!("{prefix}{key}"))
            .and_then(serde_json::Value::as_f64)
            .unwrap_or(0.0)
    });
    Ok(crate::crysta_native_evaluator::proportional_attack(
        &base, rates,
    ))
}
#[wasm_bindgen]
pub fn normal_attack_ampr_json(value: f64, input: &str) -> Result<String, JsValue> {
    let profile = serde_json::from_str(input).map_err(|e| JsValue::from_str(&e.to_string()))?;
    serde_json::to_string(&crate::crysta_native_evaluator::normal_attack_ampr(
        value, &profile,
    ))
    .map_err(|e| JsValue::from_str(&e.to_string()))
}
#[wasm_bindgen]
pub fn resistance_profile_json(input: &str) -> Result<String, JsValue> {
    let values = serde_json::from_str(input).map_err(|e| JsValue::from_str(&e.to_string()))?;
    serde_json::to_string(&crate::crysta_native_evaluator::resistance_profile(&values))
        .map_err(|e| JsValue::from_str(&e.to_string()))
}
