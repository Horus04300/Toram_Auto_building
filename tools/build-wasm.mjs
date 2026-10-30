import {spawnSync} from 'node:child_process';
import {readFile,writeFile,mkdir,mkdtemp,rmdir} from 'node:fs/promises';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {createHash} from 'node:crypto';
import {artifactFiles,syncArtifacts} from './support/build-artifacts.mjs';

const root=resolve(import.meta.dirname,'..'),target=resolve(root,'engine/target');
const output=resolve(root,'build/generated/wasm'),stamp=resolve(root,'build/generated/wasm.bindings.json');
const hash=bytes=>createHash('sha256').update(bytes).digest('hex');
const threadedFlags=['-Ctarget-feature=+atomics,+bulk-memory','-Clink-arg=--shared-memory','-Clink-arg=--max-memory=1073741824','-Clink-arg=--import-memory',
  ...['__wasm_init_tls','__tls_size','__tls_align','__tls_base'].map(name=>'-Clink-arg=--export='+name)].join(' ');
function run(command,args,env) {
  const result=spawnSync(command,args,{cwd:root,windowsHide:true,stdio:'inherit',env});
  if(result.error) throw result.error;
  if(result.status!==0) throw new Error(command+' exited '+result.status);
}
async function outputHashes(directory) {
  const files=await artifactFiles(directory);
  return Object.fromEntries(await Promise.all([...files].sort().map(async path=>[path,hash(await readFile(resolve(directory,path)))])));
}
async function build() {
  const threadedTarget=resolve(target,'wasm-threads');
  // Cargo owns source, lockfile, compiler, configuration and environment freshness.
  run('cargo',['build','--lib','--locked','--release','--target','wasm32-unknown-unknown','--manifest-path','engine/Cargo.toml','--target-dir',target]);
  run('cargo',['+nightly-2025-11-15','build','--lib','--locked','--release','--target','wasm32-unknown-unknown','--manifest-path','engine/Cargo.toml','--target-dir',threadedTarget,'--features','wasm-threads','-Zbuild-std=panic_abort,std'],{...process.env,RUSTFLAGS:threadedFlags});
  const version=spawnSync('wasm-bindgen',['--version'],{cwd:root,encoding:'utf8',windowsHide:true});
  if(version.error) throw version.error;
  if(version.status!==0) throw new Error('Cannot read wasm-bindgen version');
  const inputs={tool:hash(await readFile(new URL(import.meta.url))),bindgen:version.stdout.trim(),
    single:hash(await readFile(resolve(target,'wasm32-unknown-unknown/release/toram_optimization_core.wasm'))),
    parallel:hash(await readFile(resolve(threadedTarget,'wasm32-unknown-unknown/release/toram_optimization_core.wasm')))};
  try {
    const previous=JSON.parse(await readFile(stamp,'utf8'));
    if(JSON.stringify(previous.inputs)===JSON.stringify(inputs)&&JSON.stringify(previous.files)===JSON.stringify(await outputHashes(output))) {
      console.log('WASM bindings: current (Cargo checked both targets; output hashes verified).');return {generated:false};
    }
  } catch(error) {if(!['ENOENT','ENOTDIR'].includes(error.code)&&!(error instanceof SyntaxError)) throw error;}
  const temporaryRoot=resolve(root,'build/tmp');await mkdir(temporaryRoot,{recursive:true});
  const stage=await mkdtemp(resolve(temporaryRoot,'wasm-bindings-'));
  try {
    for(const [directory,source] of [[stage,resolve(target,'wasm32-unknown-unknown/release/toram_optimization_core.wasm')],[resolve(stage,'parallel'),resolve(threadedTarget,'wasm32-unknown-unknown/release/toram_optimization_core.wasm')]]) {
      run('wasm-bindgen',[source,'--target','web','--no-typescript','--out-dir',directory,'--out-name','crysta']);
    }
    const files=await artifactFiles(stage),written=await syncArtifacts(output,files,path=>readFile(resolve(stage,path)));
    await writeFile(stamp,JSON.stringify({inputs,files:await outputHashes(output)})+'\n');
    console.log(written ? `WASM bindings: generated (${written} changed artifacts).` : 'WASM bindings: verified (unchanged output).');return {generated:true,written};
  } finally {await syncArtifacts(stage,new Set(),()=>Buffer.alloc(0));await rmdir(stage);}
}
let active;
export function buildWasm() {
  if(!active) active=build().finally(()=>{active=null;});
  return active;
}
if(process.argv[1]&&import.meta.url===pathToFileURL(resolve(process.argv[1])).href) await buildWasm();
