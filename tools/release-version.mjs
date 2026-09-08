import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import { resolve } from 'node:path';
import { pathToFileURL } from 'node:url';

export function verifyVersion(root = resolve(import.meta.dirname, '..'), tag = process.env.RELEASE_TAG) {
  const read = path => readFileSync(resolve(root, path), 'utf8');
  const pkg = JSON.parse(read('package.json'));
  const lock = JSON.parse(read('package-lock.json'));
  const config = JSON.parse(read('src-tauri/tauri.conf.json'));
  const cargo = read('src-tauri/Cargo.toml').match(/\[package\][\s\S]*?^version = "([^"]+)"/m)?.[1];
  const cargoLock = read('src-tauri/Cargo.lock').match(/name = "toram-online-auto-build-calculator"\r?\nversion = "([^"]+)"/)?.[1];
  assert.match(pkg.version, /^(0|[1-9]\d*)\.(0|[1-9]\d*)\.(0|[1-9]\d*)$/, 'Only regular release versions are allowed');
  for (const [name, value] of Object.entries({ cargo, cargoLock, tauri:config.version, packageLock:lock.version, lockRoot:lock.packages[''].version })) {
    assert.equal(value, pkg.version, `${name} version mismatch`);
  }
  if (tag !== undefined) assert.equal(tag, `v${pkg.version}`, 'Release tag must match source');
  assert.equal(config.bundle.createUpdaterArtifacts, true);
  assert.deepEqual(config.plugins.updater.endpoints, ['https://github.com/Horus04300/Toram_Auto_building/releases/latest/download/latest.json']);
  assert.ok(Buffer.from(config.plugins.updater.pubkey, 'base64').toString().startsWith('untrusted comment: minisign public key:'), 'Real updater public key required');
  return pkg.version;
}
if (process.argv[1] && import.meta.url === pathToFileURL(resolve(process.argv[1])).href) {
  console.log(`Release version: PASS (${verifyVersion()})`);
}
