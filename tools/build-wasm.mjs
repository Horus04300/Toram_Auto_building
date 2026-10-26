import { spawnSync } from 'node:child_process';
import { mkdir } from 'node:fs/promises';
import { resolve } from 'node:path';

const root = resolve(import.meta.dirname, '..');
const target = resolve(root, 'engine/target');
const output = resolve(root, 'build/generated/wasm');
await mkdir(output, { recursive:true });
const threadedTarget = resolve(target, 'wasm-threads');
const threadedFlags = ['-Ctarget-feature=+atomics,+bulk-memory', '-Clink-arg=--shared-memory',
  '-Clink-arg=--max-memory=1073741824', '-Clink-arg=--import-memory',
  ...['__wasm_init_tls', '__tls_size', '__tls_align', '__tls_base'].map(name => '-Clink-arg=--export=' + name)].join(' ');
for (const [command, args, env] of [
  ['cargo', ['build', '--locked', '--release', '--target', 'wasm32-unknown-unknown', '--manifest-path', 'engine/Cargo.toml']],
  ['wasm-bindgen', [resolve(target, 'wasm32-unknown-unknown/release/toram_optimization_core.wasm'), '--target', 'no-modules', '--no-typescript', '--out-dir', output, '--out-name', 'crysta']],
  ['cargo', ['+nightly-2025-11-15', 'build', '--locked', '--release', '--target', 'wasm32-unknown-unknown',
    '--manifest-path', 'engine/Cargo.toml', '--target-dir', threadedTarget, '--features', 'wasm-threads', '-Zbuild-std=panic_abort,std'],
    { ...process.env, RUSTFLAGS:threadedFlags }],
  ['wasm-bindgen', [resolve(threadedTarget, 'wasm32-unknown-unknown/release/toram_optimization_core.wasm'),
    '--target', 'web', '--no-typescript', '--out-dir', resolve(output, 'parallel'), '--out-name', 'crysta']]
]) {
  const result = spawnSync(command, args, { cwd:root, stdio:'inherit', windowsHide:true, env });
  if (result.error) throw result.error;
  if (result.status !== 0) process.exit(result.status || 1);
}
