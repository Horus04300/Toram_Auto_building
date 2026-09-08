import assert from 'node:assert/strict';
import { mkdtempSync, mkdirSync, readFileSync, writeFileSync, rmSync } from 'node:fs';
import { tmpdir } from 'node:os';
import { resolve } from 'node:path';
import { verifyVersion } from './release-version.mjs';
const root = resolve(import.meta.dirname, '..');
const version = verifyVersion(root);
assert.throws(() => verifyVersion(root, 'v0.0.1'), /tag/);
assert.equal(verifyVersion(root, `v${version}`), version);
const dir = mkdtempSync(resolve(tmpdir(), 'toram-version-test-'));
try {
  mkdirSync(resolve(dir, 'src-tauri'));
  for (const path of ['package.json', 'package-lock.json', 'src-tauri/Cargo.toml', 'src-tauri/Cargo.lock', 'src-tauri/tauri.conf.json']) {
    writeFileSync(resolve(dir, path), readFileSync(resolve(root, path)));
  }
  const configPath = resolve(dir, 'src-tauri/tauri.conf.json');
  const config = JSON.parse(readFileSync(configPath));
  config.version = '0.0.1';
  writeFileSync(configPath, JSON.stringify(config));
  assert.throws(() => verifyVersion(dir), /tauri version mismatch/);
  config.version = version;
  config.plugins.updater.pubkey = 'PLACEHOLDER';
  writeFileSync(configPath, JSON.stringify(config));
  assert.throws(() => verifyVersion(dir), /public key/);
} finally { rmSync(dir, { recursive:true, force:true }); }
console.log('Update release gates: PASS (source/locks/tag mismatch, real public key)');
