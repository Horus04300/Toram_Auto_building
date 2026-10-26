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
