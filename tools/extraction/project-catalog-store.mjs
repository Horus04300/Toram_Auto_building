import assert from 'node:assert/strict';
import { createHash } from 'node:crypto';
import { readFile, writeFile, mkdir, rename } from 'node:fs/promises';
import { resolve, relative, dirname, isAbsolute } from 'node:path';

export const hash = data => createHash('sha256').update(data).digest('hex');
export const encode = value => Buffer.from(JSON.stringify(value) + '\n');

export function child(directory, path) {
  const target = resolve(directory, path), part = relative(directory, target);
  assert.ok(part && !part.startsWith('..') && !isAbsolute(part), 'Artifact escapes its directory.');
  return target;
}

export async function saveImmutable(path, bytes) {
  await mkdir(dirname(path), { recursive:true });
  try { assert.deepEqual(await readFile(path), bytes, `Different artifact exists: ${path}`); }
  catch (error) { if (error.code !== 'ENOENT') throw error; await writeFile(path, bytes, { flag:'wx' }); }
}

export async function validateManifestFiles(directory, manifest, referenced) {
  assert.deepEqual([...new Set(referenced)].sort(), Object.keys(manifest.files).sort(), 'Manifest references differ from inventory.');
  for (const [path, expected] of Object.entries(manifest.files)) {
    const bytes = await readFile(child(directory, path));
    assert.equal(bytes.length, expected.bytes, `Item asset size mismatch: ${path}`);
    assert.equal(hash(bytes), expected.sha256, `Item asset hash mismatch: ${path}`);
  }
}

export async function publishProjectSnapshot(snapshot, output, readManifest) {
  const report = JSON.parse(await readFile(child(snapshot, 'report.json')));
  assert.equal(report.status, 'ready', 'Snapshot needs review.');
  assert.ok(report.outputHashes['project/manifest.json'], 'Snapshot has no project conversion; rerun the update pipeline.');
  for (const [path, expected] of Object.entries(report.outputHashes)) assert.equal(hash(await readFile(child(snapshot, path))), expected);
  const source = child(snapshot, 'project'), manifest = await readManifest(source);
  try {
    const existing = await readFile(child(output, 'manifest.json'));
    if (existing.equals(encode(manifest))) { await readManifest(output); return manifest; }
  } catch (error) { if (error.code !== 'ENOENT') throw error; }
  for (const path of Object.keys(manifest.files)) await saveImmutable(child(output, path), await readFile(child(source, path)));
  await mkdir(output, { recursive:true });
  const temporary = child(output, `manifest.${process.pid}.${Date.now()}.tmp`);
  await writeFile(temporary, encode(manifest), { flag:'wx' });
  await rename(temporary, child(output, 'manifest.json'));
  return manifest;
}

export async function publishLatestProjectSnapshot(store, output, readManifest) {
  const pointer = JSON.parse(await readFile(child(store, 'latest.json'))), snapshot = child(store, pointer.snapshot);
  assert.equal(hash(await readFile(child(snapshot, 'report.json'))), pointer.reportSha256);
  return publishProjectSnapshot(snapshot, output, readManifest);
}
