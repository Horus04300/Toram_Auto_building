import assert from 'node:assert/strict';
import {get} from 'node:https';
import {spawnSync} from 'node:child_process';
import {readFile,mkdtemp,access,writeFile} from 'node:fs/promises';
import {resolve} from 'node:path';
import {createAccountServer} from '../../../server/account-server.mjs';
import {stageWebRelease,verifyPublicDeployment} from '../../deploy-web.mjs';

const root=resolve(import.meta.dirname,'../../..');
// Public test-only key/certificate; never included in a deployment release.
const cert=await readFile(resolve(root,'tools/fixtures/https-test-cert.pem'));
const key=await readFile(resolve(root,'tools/fixtures/https-test-key.pem'));
const server=createAccountServer({publicOrigin:'https://localhost',tls:{cert,key}});
await new Promise(done=>server.listen(0,'127.0.0.1',done));
function request(trust) {
  return new Promise((done,reject)=>get({hostname:'127.0.0.1',port:server.address().port,path:'/api/session',servername:'localhost',...(trust?{ca:cert}:{})},response=>{
    let body='';response.on('data',chunk=>body+=chunk);response.on('end',()=>done({status:response.statusCode,body:JSON.parse(body)}));
  }).on('error',reject));
}
try {
  assert.deepEqual(await request(true),{status:200,body:{configured:false,user:null}});
  await assert.rejects(request(false),error=>error.code==='DEPTH_ZERO_SELF_SIGNED_CERT');
} finally {await new Promise(done=>server.close(done));}
const cli=spawnSync(process.execPath,['server/account-server.mjs'],{cwd:root,encoding:'utf8',env:{...process.env,TLS_CERT_PATH:'tools/fixtures/https-test-cert.pem',TLS_KEY_PATH:''}});
assert.equal(cli.status,1);assert.match(cli.stderr,/must be configured together/);
const publicResponse=url=>new Response(url.endsWith('/api/session')?'{"configured":true}':'asset',{headers:{'cross-origin-opener-policy':'same-origin','cross-origin-embedder-policy':'require-corp'}});
await verifyPublicDeployment(async url=>publicResponse(url));
await assert.rejects(verifyPublicDeployment(async url=>url.endsWith('/style.css')?new Response('TLS failed',{status:525}):publicResponse(url)),/style\.css.*525/);
await assert.rejects(verifyPublicDeployment(async()=>{throw new Error('timeout');}),/Public HTTPS check failed: \/ .*timeout/);

const stage=await mkdtemp(resolve(root,'build/tmp/deploy-test-'));
const release=await stageWebRelease(stage);
const manifest=JSON.parse(await readFile(resolve(stage,'release.json'),'utf8'));
assert.equal(manifest.id,release.id);
assert.ok(manifest.files['build/web/assets/wasm/crysta_bg.wasm']);
assert.ok(manifest.files['server/account-server.mjs']);
for(const path of ['server/.env','server/data/accounts.sqlite','tools/fixtures/https-test-key.pem']) await assert.rejects(access(resolve(stage,path)),{code:'ENOENT'});
const tar=resolve(stage,'../'+release.id+'.test.tar.gz');
function command(program,args) {
  const result=spawnSync(program,args,{cwd:root,encoding:'utf8'});
  assert.equal(result.status,0,result.stderr||result.stdout);return result;
}
command('tar',['-czf',tar,'-C',stage,'.']);
const verified=await mkdtemp(resolve(root,'build/tmp/verified-deploy-test-'));
command(process.platform==='win32'?'python':'python3',['server/deploy/verify-release.py',tar,release.id,verified]);
assert.equal(await readFile(resolve(verified,'build/web/index.html'),'utf8'),await readFile(resolve(stage,'build/web/index.html'),'utf8'));
await writeFile(resolve(stage,'server/account-server.mjs'),'corrupt upload');
command('tar',['-czf',tar,'-C',stage,'.']);
const corrupted=spawnSync(process.platform==='win32'?'python':'python3',['server/deploy/verify-release.py',tar,release.id,verified],{cwd:root,encoding:'utf8'});
assert.notEqual(corrupted.status,0);assert.match(corrupted.stderr,/checksum mismatch/);
command(process.platform==='win32'?'python':'python3',['-c',`
import importlib.util,io,pathlib,tarfile,tempfile
spec=importlib.util.spec_from_file_location('release','server/deploy/verify-release.py')
module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
with tempfile.TemporaryDirectory() as directory:
 for name,kind in [('../escape',tarfile.REGTYPE),('/absolute',tarfile.REGTYPE),('link',tarfile.SYMTYPE)]:
  archive=pathlib.Path(directory)/'unsafe.tar.gz'
  with tarfile.open(archive,'w:gz') as bundle:
   member=tarfile.TarInfo(name);member.type=kind;member.linkname='/etc/passwd';bundle.addfile(member,io.BytesIO())
  output=pathlib.Path(directory)/'output';output.mkdir(exist_ok=True)
  try: module.verify_release(archive,'a'*64,output)
  except ValueError: pass
  else: raise AssertionError('Unsafe archive accepted')
  assert list(output.iterdir())==[]
`]);
console.log('Web deployment: PASS (HTTPS certificate trust, incomplete TLS rejection, runtime-only package, complete archive checksum verification, corrupt upload rejection)');
