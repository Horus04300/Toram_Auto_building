import {spawnSync} from 'node:child_process';
import {createHash} from 'node:crypto';
import {readFile,writeFile,mkdir,mkdtemp,copyFile,stat} from 'node:fs/promises';
import {resolve,dirname} from 'node:path';
import {pathToFileURL} from 'node:url';
import {parseEnv} from 'node:util';
import {prepareFrontend} from './prepare-frontend.mjs';
import {sourceModuleFiles} from './support/frontend-paths.mjs';
import {artifactFiles} from './support/build-artifacts.mjs';

const root=resolve(import.meta.dirname,'..'),remote='/srv/compose/toram';
const hash=bytes=>createHash('sha256').update(bytes).digest('hex');
function run(command,args,options={}) {
  const result=spawnSync(command,args,{cwd:root,windowsHide:true,stdio:'inherit',...options});
  if(result.error) throw result.error;
  if(result.status!==0) throw new Error(`${command} failed (${result.status}).`);
  return result.stdout;
}
const ssh=(command,options)=>run('ssh',['-o','BatchMode=yes','-o','ConnectTimeout=10','nimp',command],options);

export async function stageWebRelease(stage) {
  const sources=['package.json','.dockerignore','server/Dockerfile',...await sourceModuleFiles(['server/account-server.mjs'])];
  const files=[...sources,...[...await artifactFiles(resolve(root,'build/web'))].map(path=>'build/web/'+path)].sort();
  const hashes={};
  for(const path of files) {
    const bytes=await readFile(resolve(root,path)),destination=resolve(stage,path);
    await mkdir(dirname(destination),{recursive:true});await writeFile(destination,bytes);
    hashes[path]=hash(bytes);
  }
  const id=hash(JSON.stringify(hashes));
  await writeFile(resolve(stage,'release.json'),JSON.stringify({schema:1,id,files:hashes})+'\n');
  return {id,files:files.length};
}

export async function verifyPublicDeployment(fetcher=fetch) {
  const paths=['/','/assets/css/style.css','/assets/js/app-entry.mjs','/assets/wasm/crysta_bg.wasm','/api/session'];
  await Promise.all(paths.map(async path=>{
    let response;
    try {response=await fetcher('https://toram.nimp.dev'+path,{signal:AbortSignal.timeout(20000)});}
    catch(error) {throw new Error(`Public HTTPS check failed: ${path} (${error.message}).`,{cause:error});}
    if(!response.ok) throw new Error(`Public HTTPS check failed: ${path} (HTTP ${response.status}).`);
    if(response.headers.get('cross-origin-opener-policy')!=='same-origin'||response.headers.get('cross-origin-embedder-policy')!=='require-corp') throw new Error(`Isolation headers missing: ${path}.`);
    if(path==='/api/session') {
      if((await response.json()).configured!==true) throw new Error('Public OAuth configuration check failed.');
    } else await response.arrayBuffer();
  }));
}

async function prepareSetup() {
  // Only OAuth keys cross SSH; development origins and local account data stay local.
  const env=parseEnv(await readFile(resolve(root,'server/.env'),'utf8'));
  const keys=['GOOGLE_CLIENT_ID','GOOGLE_CLIENT_SECRET'];
  for(const key of keys) if(!env[key]||!/^[-A-Za-z0-9._:]+$/u.test(env[key])) throw new Error(`Configure ${key} in server/.env before setup.`);
  const home=ssh('pwd',{stdio:['ignore','pipe','inherit'],encoding:'utf8'}).trim();
  if(!/^\/home\/[A-Za-z0-9_-]+$/u.test(home)) throw new Error('Unexpected SSH home directory.');
  ssh(`install -d -m 700 ${remote}/bootstrap`);
  for(const file of ['setup.sh','activate.sh','verify-release.py','compose.yaml','Caddyfile.toram']) {
    run('scp',[resolve(root,'server/deploy',file),`nimp:${remote}/bootstrap/${file}`]);
  }
  ssh(`umask 077; cat > ${remote}/bootstrap/oauth.env`,{stdio:['pipe','inherit','inherit'],input:keys.map(key=>`${key}=${env[key]}\n`).join('')});
  console.log(`Create the toram tunnel in Cloudflare first. The server setup will prompt for its token without echoing it.\nRun once in PowerShell (enter your server sudo password there):\nssh -t nimp "sudo bash ${remote}/bootstrap/setup.sh"\nThen publish toram.nimp.dev with service URL https://caddy:443, Origin Server Name toram.nimp.dev, TLS verification enabled.\nFinally run: npm run web:deploy`);
}

async function deploy() {
  ssh('sudo -n /usr/local/sbin/toram-deploy --check');
  run(process.execPath,['tools/run-regression-suite.mjs']);
  await prepareFrontend('web');
  run(process.execPath,['tools/verification/verify-es-module-entry.mjs','--web']);
  await mkdir(resolve(root,'build/tmp'),{recursive:true});
  const stage=await mkdtemp(resolve(root,'build/tmp/web-release-'));
  const release=await stageWebRelease(stage),archive=resolve(stage,'../'+release.id+'.tar.gz');
  run('tar',['-czf',archive,'-C',stage,'.']);
  console.log(`Uploading ${release.files} files (${(await stat(archive)).size} compressed bytes), release ${release.id}.`);
  run('scp',[archive,`nimp:${remote}/incoming/${release.id}.tar.gz`]);
  ssh(`sudo -n /usr/local/sbin/toram-deploy ${release.id}`);
  await verifyPublicDeployment();
  console.log('Deployed: https://toram.nimp.dev (public TLS and OAuth configuration verified).');
}

if(process.argv[1]&&import.meta.url===pathToFileURL(resolve(process.argv[1])).href) {
  if(process.argv.length>3||process.argv[2]&&!['--setup'].includes(process.argv[2])) throw new Error('Usage: npm run web:deploy [-- --setup]');
  try {if(process.argv[2]==='--setup') await prepareSetup();else await deploy();}
  catch(error) {console.error(error.message);process.exitCode=1;}
}
