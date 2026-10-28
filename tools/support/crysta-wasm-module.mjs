import {readFile} from 'node:fs/promises';
let instance=0;
export async function loadWasmModule() {
  const url=new URL('../../build/generated/wasm/crysta.js',import.meta.url);
  url.searchParams.set('instance',String(++instance));
  const module=await import(url.href);
  await module.default({module_or_path:await readFile(new URL('../../build/generated/wasm/crysta_bg.wasm',import.meta.url))});
  return module;
}
