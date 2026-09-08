import assert from 'node:assert/strict';
import { copyFileSync, mkdirSync, readFileSync, statSync, writeFileSync } from 'node:fs';
import { resolve } from 'node:path';
import { spawnSync } from 'node:child_process';
import { verifyVersion } from './release-version.mjs';

const root = resolve(import.meta.dirname, '..');
const version = verifyVersion(root);
const installer = resolve(root, `src-tauri/target/release/bundle/nsis/Toram Online Auto Build Calculator_${version}_x64-setup.exe`);
const signature = installer + '.sig';
assert.ok(statSync(installer).size > 0 && statSync(signature).size > 0, 'Installer and signature required');
const verified = spawnSync('cargo', ['run', '--locked', '--quiet', '--manifest-path', resolve(root, 'src-tauri/Cargo.toml'), '--bin', 'verify_updater_artifact', '--', resolve(root, 'src-tauri/tauri.conf.json'), installer, signature], { stdio:'inherit' });
assert.equal(verified.status, 0, 'Artifact signature must match bundled public key');
const output = resolve(root, 'release-assets');
mkdirSync(output, { recursive:true });
// GitHub rewrites spaces in uploaded names. Use a predictable ASCII name in the manifest.
const name = `ToramOnlineAutoBuildCalculator_${version}_x64-setup.exe`;
copyFileSync(installer, resolve(output, name));
copyFileSync(signature, resolve(output, name + '.sig'));
const manifest = {
  version,
  notes:process.env.RELEASE_NOTES_PATH ? readFileSync(process.env.RELEASE_NOTES_PATH, 'utf8') : '업데이트 알림 및 설치 기능을 추가했습니다.',
  pub_date:new Date().toISOString(),
  platforms:{ 'windows-x86_64':{
    signature:readFileSync(signature, 'utf8').trim(),
    url:`https://github.com/Horus04300/Toram_Auto_building/releases/download/v${version}/${name}`
  } }
};
writeFileSync(resolve(output, 'latest.json'), JSON.stringify(manifest, null, 2) + '\n');
console.log(`Release assets: PASS (${name}, signature, latest.json)`);
