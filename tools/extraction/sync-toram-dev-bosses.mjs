import { spawn } from 'node:child_process';
import { readFile, mkdir, open, unlink } from 'node:fs/promises';
import { resolve } from 'node:path';
import { fileURLToPath, pathToFileURL } from 'node:url';
import { itemPython } from './sync-toram-dev-items.mjs';
import { publishLatestProjectBosses } from './convert-toram-project-bosses.mjs';

const root = fileURLToPath(new URL('../..', import.meta.url));
export async function syncDevelopmentBosses({ pipelineArgs = [], application = 'releaseC',
  store = resolve(root,'data/sources/toram-monsters/pipeline'), output = resolve(root,'web/public/game-data/bosses') } = {}) {
  await mkdir(output, { recursive:true });
  const lockPath = resolve(output,'.development-sync.lock'), lock = await open(lockPath,'wx');
  try {
    const python = await itemPython();
    const result = await new Promise((accept, reject) => {
      const worker = spawn(python, [resolve(root,'tools/extraction/update-toram-bosses.py'), '--application', application, '--store', store, ...pipelineArgs],
        { cwd:root, windowsHide:true, stdio:['ignore','pipe','pipe'] });
      let stdout = '', stderr = '';
      worker.stdout.on('data', data => { stdout += data.toString('utf8'); });
      worker.stderr.on('data', data => { stderr = (stderr + data.toString('utf8')).slice(-12000); process.stderr.write(data); });
      worker.on('error', reject);
      worker.on('close', code => accept({ code, stdout, stderr }));
    });
    let status;
    try { status = JSON.parse(result.stdout.trim().split(/\r?\n/u).at(-1)); }
    catch { status = { status:'failed', error:result.stderr || result.stdout || 'No boss pipeline status.' }; }
    const check = pipelineArgs.includes('--check');
    if (result.code !== 0 || !(check ? ['update-available','unchanged'] : ['ready','unchanged']).includes(status.status))
      return { ...status, application, exitCode:result.code || 1, developmentApplied:false };
    if (check) return { ...status, application, exitCode:0, developmentApplied:false };
    const path = resolve(output,'manifest.json');
    const before = await readFile(path).catch(error => { if (error.code !== 'ENOENT') throw error; return null; });
    const manifest = await publishLatestProjectBosses(resolve(store, application), output), after = await readFile(path);
    return { status:before?.equals(after) ? 'unchanged' : 'development-updated', exitCode:0, developmentApplied:true,
      application, revision:manifest.revision, counts:manifest.counts, output };
  } finally { await lock.close(); await unlink(lockPath); }
}

async function main() {
  const input = process.argv.slice(2), pipelineArgs = [];
  let application = 'releaseC', store = resolve(root,'data/sources/toram-monsters/pipeline');
  for (let i = 0; i < input.length; i++) {
    const arg = input[i];
    if (arg === '--application') { application = input[++i]; if (!/^release[A-F]$/u.test(application)) throw new Error('Invalid application.'); }
    else if (arg === '--store') { if (!input[i+1]) throw new Error('Missing store.'); store = resolve(input[++i]); }
    else if (['--offline','--install','--unitypy-path'].includes(arg)) { if (!input[i+1]) throw new Error('Missing argument.'); pipelineArgs.push(arg, resolve(input[++i])); }
    else if (arg === '--check') pipelineArgs.push(arg);
    else throw new Error('Unknown boss sync argument: ' + arg);
  }
  const report = await syncDevelopmentBosses({ pipelineArgs, application, store });
  console.log(JSON.stringify(report)); process.exitCode = report.exitCode;
}

if (process.argv[1] && import.meta.url === pathToFileURL(resolve(process.argv[1])).href) {
  try { await main(); }
  catch (error) { console.error(JSON.stringify({ status:'failed', developmentApplied:false, error:error.message })); process.exitCode = 1; }
}
