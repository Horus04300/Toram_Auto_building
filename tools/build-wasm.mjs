import { spawnSync } from 'node:child_process';
import { mkdir } from 'node:fs/promises';
import { resolve } from 'node:path';

const root = resolve(import.meta.dirname, '..');
const target = resolve(root, 'engine/target');
const output = resolve(root, 'build/generated/wasm');
await mkdir(output, { recursive:true });
for (const [command, args] of [
  ['cargo', ['build', '--locked', '--release', '--target', 'wasm32-unknown-unknown', '--manifest-path', 'engine/Cargo.toml']],
  ['wasm-bindgen', [resolve(target, 'wasm32-unknown-unknown/release/toram_optimization_core.wasm'), '--target', 'no-modules', '--no-typescript', '--out-dir', output, '--out-name', 'crysta']]
]) {
  const result = spawnSync(command, args, { cwd:root, stdio:'inherit', windowsHide:true });
  if (result.error) throw result.error;
  if (result.status !== 0) process.exit(result.status || 1);
}
