import { readFile } from 'node:fs/promises';
import vm from 'node:vm';

export async function loadWasmModule() {
  const glue = await readFile(new URL('../../build/generated/wasm/crysta.js', import.meta.url), 'utf8');
  const bytes = await readFile(new URL('../../build/generated/wasm/crysta_bg.wasm', import.meta.url));
  const context = vm.createContext({ console, performance, TextDecoder, TextEncoder, WebAssembly });
  vm.runInContext(glue + '\nglobalThis.api = wasm_bindgen;', context);
  context.bytes = bytes;
  await vm.runInContext('api({ module_or_path:bytes })', context);
  return context.api;
}
