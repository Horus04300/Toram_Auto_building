import assert from 'node:assert/strict';
import { createHash } from 'node:crypto';
import { readFile, writeFile, mkdir, rename, access, open, unlink } from 'node:fs/promises';
import { resolve, relative, dirname, isAbsolute } from 'node:path';
import {spawn} from 'node:child_process';
import {homedir} from 'node:os';
import {fileURLToPath} from 'node:url';

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

const projectRoot=fileURLToPath(new URL('../..',import.meta.url));
export async function pipelinePython() {
  if(process.env.TORAM_ITEM_PYTHON) return process.env.TORAM_ITEM_PYTHON;
  const bundled=resolve(homedir(),'.cache/codex-runtimes/codex-primary-runtime/dependencies/python/python.exe');
  try {await access(bundled);return bundled;}
  catch(error) {if(error.code!=='ENOENT') throw error;return 'python';}
}

export function parseSyncArguments(input,defaultStore) {
  const options={pipelineArgs:[],application:'releaseC',store:defaultStore};
  for(let i=0;i<input.length;i++) {
    const arg=input[i];
    if(arg==='--application') {options.application=input[++i];assert.match(options.application||'',/^release[A-F]$/u,'Invalid application.');}
    else if(arg==='--store') {assert.ok(input[i+1],'Missing store.');options.store=resolve(input[++i]);}
    else if(['--offline','--install','--unitypy-path'].includes(arg)) {assert.ok(input[i+1],'Missing argument.');options.pipelineArgs.push(arg,resolve(input[++i]));}
    else if(arg==='--check') options.pipelineArgs.push(arg);
    else throw new Error('Unknown sync argument: '+arg);
  }
  return options;
}

export async function syncDevelopmentCatalog(kind,publish,{pipelineArgs=[],python,store,application='releaseC',output}) {
  assert.ok(['items','bosses'].includes(kind),'Unknown catalog.');
  await mkdir(output,{recursive:true});
  const lockPath=resolve(output,'.development-sync.lock'), lock=await open(lockPath,'wx');
  try {
    const executable=python||await pipelinePython();
    const result=await new Promise((accept,reject)=>{
      const worker=spawn(executable,[resolve(projectRoot,`tools/extraction/update-toram-${kind}.py`),'--store',store,'--application',application,...pipelineArgs],{cwd:projectRoot,windowsHide:true,stdio:['ignore','pipe','pipe']});
      let stdout='',stderr='';
      worker.stdout.on('data',bytes=>{stdout+=bytes.toString('utf8');});
      worker.stderr.on('data',bytes=>{stderr=(stderr+bytes.toString('utf8')).slice(-12000);if(kind==='bosses') process.stderr.write(bytes);});
      worker.on('error',reject);
      worker.on('close',code=>accept({code,stdout,stderr}));
    });
    let status,report;
    try {status=JSON.parse(result.stdout.trim().split(/\r?\n/u).at(-1));}
    catch {status={status:'failed',error:result.stderr||result.stdout||'Pipeline returned no status.'};}
    const check=pipelineArgs.includes('--check');
    if(result.code!==0||!(check?['update-available','unchanged']:['ready','unchanged']).includes(status.status)) report={...status,exitCode:result.code||1,developmentApplied:false};
    else if(check) report={...status,exitCode:0,developmentApplied:false};
    else {
      const path=resolve(output,'manifest.json');
      const before=await readFile(path).catch(error=>{if(error.code!=='ENOENT') throw error;return null;});
      const manifest=await publish(resolve(store,application),output),after=await readFile(path);
      report={status:before?.equals(after)?'unchanged':'development-updated',exitCode:0,developmentApplied:true,
        ...(kind==='items'?{cacheVersion:manifest.cacheVersion}:{revision:manifest.revision}),counts:manifest.counts,output};
    }
    report.application=application;
    if(kind==='items') {
      const log=resolve(projectRoot,'build/tmp/toram-dev-item-sync.json');
      await mkdir(dirname(log),{recursive:true});
      await writeFile(log,JSON.stringify({...report,checkedUtc:new Date().toISOString()},null,2)+'\n');
    }
    return report;
  } finally {await lock.close();await unlink(lockPath);}
}
