import assert from 'node:assert/strict';
import {createServer} from 'node:net';
import {mkdtemp,rm} from 'node:fs/promises';
import {tmpdir} from 'node:os';
import {join} from 'node:path';
import {createWebDevServer} from '../../web-dev.mjs';

const reservation=createServer();
await new Promise(done=>reservation.listen(0,'127.0.0.1',done));
const port=reservation.address().port;
await new Promise(done=>reservation.close(done));
const origin=`http://localhost:${port}`,directory=await mkdtemp(join(tmpdir(),'toram-web-dev-'));
const options={publicOrigin:origin,clientId:'dev-test-id',clientSecret:'dev-test-secret',database:join(directory,'accounts.sqlite'),fetchImpl:async(url,request)=>{
  if(url.endsWith('/token')) {
    assert.equal(request.body.get('client_secret'),'dev-test-secret');
    assert.equal(request.body.get('redirect_uri'),origin+'/api/auth/google/callback');
    assert.ok(request.body.get('code_verifier'));
    return {ok:true,json:async()=>({access_token:'dev-test-token'})};
  }
  assert.equal(url,'https://openidconnect.googleapis.com/v1/userinfo');
  return {ok:true,json:async()=>({sub:'dev-user',name:'개발 검사'})};
}};
let server;
async function start(){server=createWebDevServer(options);await new Promise((done,reject)=>{server.once('error',reject);server.listen(port,'127.0.0.1',done);});}
const call=(path,settings={})=>fetch(origin+path,{redirect:'manual',...settings,headers:{Connection:'close',...settings.headers}});
try {
  await start();
  assert.equal((await call('/')).status,200);
  assert.equal((await call('/assets/js/app-entry.mjs')).status,200);
  assert.deepEqual(await(await call('/api/session')).json(),{configured:true,user:null});
  assert.equal((await call('/api/inventory')).status,401);
  assert.equal((await call('/api/posts')).status,200);
  const canonical=await fetch(`http://127.0.0.1:${port}/calculator?test=1`,{redirect:'manual'});
  assert.equal(canonical.status,302);
  assert.equal(canonical.headers.get('location'),origin+'/calculator?test=1');
  const networkPath=await fetch(`http://127.0.0.1:${port}//evil.example/`,{redirect:'manual'});
  assert.equal(networkPath.headers.get('location'),origin+'/','Canonical redirects stay on the configured origin');
  for(const path of ['/server/.env','/server/data/accounts.sqlite','/package.json','/assets/../server/.env']) assert.equal((await call(path)).status,404,path);
  assert.equal((await call('/assets/%ZZ')).status,400);
  const login=await call('/api/auth/google'),authorization=new URL(login.headers.get('location'));
  assert.equal(login.status,302);
  assert.equal(authorization.origin,'https://accounts.google.com');
  assert.equal(authorization.searchParams.get('redirect_uri'),origin+'/api/auth/google/callback');
  assert.equal(authorization.searchParams.get('code_challenge_method'),'S256');
  const loginCookie=login.headers.getSetCookie()[0].split(';')[0];
  const callback='/api/auth/google/callback?code=dev-code&state='+authorization.searchParams.get('state');
  assert.equal((await call(callback)).status,400,'OAuth state requires the original browser cookie');
  const loggedIn=await call(callback,{headers:{Cookie:loginCookie}});
  assert.equal(loggedIn.status,302);
  const cookie=loggedIn.headers.getSetCookie().find(value=>value.startsWith('toram_session=')).split(';')[0];
  const user=(await(await call('/api/session',{headers:{Cookie:cookie}})).json()).user;
  assert.equal(user.nickname,'개발 검사');
  const equipment={type:'equipment',schemaVersion:1,name:'개발 저장',data:{slot:'mainWeapon',equipment:{type:'지팡이',attack:100,refinement:15,stability:60,options:[],crystas:['',''],lockedCrystaSlots:[false,false]}}};
  const headers={Cookie:cookie,Origin:origin,'Content-Type':'application/json'};
  assert.equal((await call('/api/inventory',{method:'POST',headers:{...headers,Origin:'http://evil.example'},body:JSON.stringify(equipment)})).status,403);
  const saved=await call('/api/inventory',{method:'POST',headers,body:JSON.stringify(equipment)});
  assert.equal(saved.status,201);
  const object=await saved.json();
  assert.deepEqual((await(await call('/api/inventory/'+object.id,{headers:{Cookie:cookie}})).json()).data,equipment.data);
  await new Promise(done=>server.close(done));server=null;
  await start();
  assert.equal((await(await call('/api/inventory/'+object.id,{headers:{Cookie:cookie}})).json()).name,equipment.name,'Restart preserves the actual account DB');
  assert.equal((await call('/api/logout',{method:'POST',headers,body:'{}'})).status,200);
  assert.equal((await(await call('/api/session',{headers:{Cookie:cookie}})).json()).user,null);
  console.log('Integrated web dev: PASS (source frontend, OAuth/PKCE/cookie callback, inventory save/restart, public API, canonical origin, auth/CSRF/private-file boundaries; Google endpoints mocked)');
}finally {
  if(server)await new Promise(done=>server.close(done));
  await rm(directory,{recursive:true,force:true});
}
