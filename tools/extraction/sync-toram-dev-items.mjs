import { spawn } from 'node:child_process';
import { access, readFile, mkdir, writeFile, open, unlink } from 'node:fs/promises';
import { resolve, dirname } from 'node:path';
import { homedir } from 'node:os';
import { pathToFileURL, fileURLToPath } from 'node:url';
import { publishLatestProjectItems } from './convert-toram-project-items.mjs';

const root = fileURLToPath(new URL('../..', import.meta.url));
export async function itemPython() {
  if (process.env.TORAM_ITEM_PYTHON) return process.env.TORAM_ITEM_PYTHON;
  const bundled = resolve(homedir(), '.cache/codex-runtimes/codex-primary-runtime/dependencies/python/python.exe');
  try { await access(bundled); return bundled; }
  catch (error) { if (error.code !== 'ENOENT') throw error; return 'python'; }
}

function runPipeline(python, args) {
  return new Promise((accept, reject) => {
    const processRef = spawn(python, [resolve(root,'tools/extraction/update-toram-items.py'), ...args], { cwd:root, windowsHide:true, stdio:['ignore','pipe','pipe'] });
    let stdout = '', stderr = '';
    processRef.stdout.on('data', bytes => { stdout += bytes.toString('utf8'); });
    processRef.stderr.on('data', bytes => { stderr = (stderr + bytes.toString('utf8')).slice(-12000); });
    processRef.on('error', reject);
    processRef.on('close', code => accept({ code, stdout, stderr }));
  });
}

export async function syncDevelopmentItems({ pipelineArgs = [], python, store = resolve(root,'data/sources/toram-items/pipeline'), application = 'releaseC', output = resolve(root,'web/public/game-data/items') } = {}) {
  await mkdir(output, { recursive:true });
  const lockPath = resolve(output,'.development-sync.lock'), lock = await open(lockPath,'wx');
  try {
    const result = await runPipeline(python || await itemPython(), ['--store', store, '--application', application, ...pipelineArgs]);
    const lines = result.stdout.trim().split(/\r?\n/u);
    let status, report;
    try { status = JSON.parse(lines.at(-1)); }
    catch { status = { status:'failed', error:result.stderr || result.stdout || 'Pipeline returned no status.' }; }
    const check = pipelineArgs.includes('--check');
    if (result.code !== 0 || !(check ? ['update-available','unchanged'] : ['ready','unchanged']).includes(status.status)) report = { ...status, exitCode:result.code || 1, developmentApplied:false };
    else if (check) report = { ...status, exitCode:0, developmentApplied:false };
    else {
      const before = await readFile(resolve(output,'manifest.json')).catch(error => { if (error.code !== 'ENOENT') throw error; return null; });
      const manifest = await publishLatestProjectItems(resolve(store, application), output);
      const after = await readFile(resolve(output,'manifest.json'));
      report = { status:before?.equals(after) ? 'unchanged' : 'development-updated', exitCode:0, developmentApplied:true,
        cacheVersion:manifest.cacheVersion, counts:manifest.counts, output };
    }
    report.application = application;
    const log = resolve(root,'build/tmp/toram-dev-item-sync.json');
    await mkdir(dirname(log), { recursive:true });
    await writeFile(log, JSON.stringify({ ...report, checkedUtc:new Date().toISOString() },null,2) + '\n');
    return report;
  } finally { await lock.close(); await unlink(lockPath); }
}

async function main() {
  const input = process.argv.slice(2), pipelineArgs = [];
  let application = 'releaseC', store = resolve(root,'data/sources/toram-items/pipeline');
  for (let i = 0; i < input.length; i++) {
    const arg = input[i];
    if (arg === '--application') { application = input[++i]; if (!/^release[A-F]$/u.test(application)) throw new Error('Invalid application.'); }
    else if (arg === '--store') { if (!input[i+1]) throw new Error('Missing store.'); store = resolve(input[++i]); }
    else if (['--offline','--install','--unitypy-path'].includes(arg)) { if (!input[i+1]) throw new Error('Missing argument.'); pipelineArgs.push(arg, resolve(input[++i])); }
    else if (arg === '--check') pipelineArgs.push(arg);
    else throw new Error('Unknown sync argument: ' + arg);
  }
  const report = await syncDevelopmentItems({ pipelineArgs, application, store });
  console.log(JSON.stringify(report)); process.exitCode = report.exitCode;
}

if (process.argv[1] && import.meta.url === pathToFileURL(resolve(process.argv[1])).href) {
  try { await main(); }
  catch (error) { console.error(JSON.stringify({ status:'failed', developmentApplied:false, error:error.message })); process.exitCode = 1; }
}
