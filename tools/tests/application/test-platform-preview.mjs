import assert from 'node:assert/strict';
import {mkdtemp,rm} from 'node:fs/promises';
import {tmpdir} from 'node:os';
import {join} from 'node:path';
import {request} from 'node:http';
import {startPlatformPreview} from '../../preview-platform.mjs';
import {createAccountServer} from '../../../server/account-server.mjs';

const directory = await mkdtemp(join(tmpdir(),'toram-preview-'));
let preview, production;
try {
  preview = await startPlatformPreview({port:18785,directory});
  const {origin} = preview;
  assert.equal(preview.server.address().address,'127.0.0.1');
  let response = await fetch(origin + '/api/inventory'); assert.equal(response.status,401);
  assert.match(await (await fetch(origin + '/__preview')).text(),/체험 계정으로 인벤토리 열기/);
  assert.equal((await fetch(origin + '/__preview/login')).status,405);
  for (const headers of [{},{Origin:'https://foreign.test'},{Origin:origin,'Sec-Fetch-Site':'cross-site'},{Origin:origin,Host:'foreign.test'}]) {
    const status = await new Promise((done,reject) => { const req = request(origin + '/__preview/login',{method:'POST',headers},res => { res.resume(); res.on('end',() => done(res.statusCode)); }); req.on('error',reject); req.end(); });
    assert.equal(status,403,JSON.stringify(headers));
  }
  async function login() {
    const result = await fetch(origin + '/__preview/login',{method:'POST',headers:{Origin:origin,Connection:'close'},redirect:'manual'});
    assert.equal(result.status,303); assert.equal(result.headers.get('location'),'/inventory?type=equipment');
    const cookie = result.headers.get('set-cookie'); assert.match(cookie,/HttpOnly; SameSite=Lax/);
    return cookie.split(';')[0];
  }
  let cookie = await login();
  const call = (path,method = 'GET',data) => fetch(origin + path,{method,headers:{Cookie:cookie,Origin:origin,Connection:'close','Content-Type':'application/json'},...(data ? {body:JSON.stringify(data)} : {})});
  assert.equal((await (await call('/api/session')).json()).user.nickname,'로컬 체험 계정');
  const record = {type:'status',schemaVersion:1,name:'보존할 체험 스테이터스',data:{character:{level:325,attributes:{STR:1,INT:1,VIT:1,AGI:1,DEX:1,CRT:0}}}};
  response = await call('/api/inventory','POST',record); assert.equal(response.status,201); const saved = await response.json();
  assert.equal((await (await call('/api/inventory/' + saved.id)).json()).name,record.name);
  assert.equal((await call('/api/logout','POST',{})).status,200);
  assert.equal((await call('/api/inventory')).status,401);
  cookie = await login();
  await new Promise(done => preview.server.close(done)); preview = null;
  preview = await startPlatformPreview({port:18785,directory});
  assert.equal((await (await call('/api/inventory/' + saved.id)).json()).name,record.name,'Restart must preserve the separate preview DB');
  production = createAccountServer({publicOrigin:'http://127.0.0.1:18786'});
  await new Promise(done => production.listen(18786,'127.0.0.1',done));
  assert.equal((await fetch('http://127.0.0.1:18786/__preview')).status,404);
  assert.equal((await fetch('http://127.0.0.1:18786/api/inventory',{headers:{Cookie:cookie}})).status,401,'Preview cookie must not authorize another DB');
  console.log('Platform preview: PASS (loopback/Host/Origin, explicit local session, real inventory persistence, logout/reentry, production has no preview route or shared session)');
} finally {
  if (preview) await new Promise(done => preview.server.close(done));
  if (production) await new Promise(done => production.close(done));
  await rm(directory,{recursive:true,force:true});
}
