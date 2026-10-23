use crate::crysta_native_solver::{NativeProblem, NativeSearchSession};
use wasm_bindgen::prelude::*;

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
}
