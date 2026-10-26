import assert from 'node:assert/strict';
import { createRequire } from 'node:module';
import { randomBytes, createHash } from 'node:crypto';
import { mkdtemp, rm } from 'node:fs/promises';
import { tmpdir } from 'node:os';
import { join } from 'node:path';
import { DatabaseSync } from 'node:sqlite';
import { createAccountServer } from '../../server/account-server.mjs';

if (!process.env.CODEX_PLAYWRIGHT_PATH) throw new Error('Set CODEX_PLAYWRIGHT_PATH to the installed playwright module.');
const {chromium} = createRequire(import.meta.url)(process.env.CODEX_PLAYWRIGHT_PATH);
const directory = await mkdtemp(join(tmpdir(),'toram-posts-')), database = join(directory,'accounts.sqlite'), origin = 'http://127.0.0.1:18787';
const server = createAccountServer({publicOrigin:origin,database}), db = new DatabaseSync(database), tokens = {};
for (const name of ['author','reader']) {
  tokens[name] = randomBytes(32).toString('base64url');
  db.prepare('INSERT INTO users VALUES (?,?,?)').run(name,'fixture-' + name,name === 'author' ? '공유 작성자' : '복사 사용자');
  db.prepare('INSERT INTO sessions VALUES (?,?,?,?)').run(createHash('sha256').update(tokens[name]).digest('hex'),name,'web',Date.now() + 3600000);
}
db.close(); let browser;
const errors = [], screenshots = [];
try {
  await new Promise((done,reject) => {server.once('error',reject); server.listen(18787,'127.0.0.1',done);});
  browser = await chromium.launch({channel:'chrome',headless:true});
  async function context(name) {
    const value = await browser.newContext({viewport:{width:1280,height:900}});
    if (name) await value.addCookies([{name:'toram_session',value:tokens[name],url:origin,httpOnly:true,sameSite:'Lax'}]); return value;
  }
  const author = await context('author'), reader = await context('reader'), guest = await context();
  assert.equal((await guest.request.post(origin + '/api/posts',{headers:{Origin:origin},data:{}})).status(),401);
  assert.equal((await guest.request.get(origin + '/api/posts',{headers:{Origin:'https://foreign.test'}})).status(),403);
  const page = await author.newPage(), other = await reader.newPage(), anonymous = await guest.newPage();
  for (const tab of [page,other,anonymous]) {tab.on('pageerror',error => errors.push(error.message)); tab.on('console',event => {if (['error','warning'].includes(event.type()) && !/404 \(Not Found\)|409 \(Conflict\)/u.test(event.text())) errors.push(event.text());}); tab.on('dialog',dialog => dialog.accept());}
  async function api(context,path,method = 'GET',data) {
    const response = await context.request.fetch(origin + '/api/' + path,{method,headers:{Origin:origin,'Idempotency-Key':crypto.randomUUID()},...(data === undefined ? {} : {data})});
    assert.ok(response.ok(),`${method} ${path}: ${await response.text()}`); return response.json();
  }
  const status = {type:'status',schemaVersion:1,name:'내 스테이터스',data:{character:{level:325,attributes:{STR:1,INT:1,VIT:1,AGI:1,DEX:1,CRT:0}}},provenance:[]};
  const source = await api(author,'inventory','POST',{type:'build',schemaVersion:1,name:'내 빌드',data:{status}});
  const wait = async (tab,id) => {await tab.locator('#' + id).waitFor({state:'visible'}); await tab.waitForFunction(id => !document.getElementById(id).hasAttribute('aria-busy'),id);};
  async function capture(tab,name) {const path = join(directory,name + '.png'); await tab.screenshot({path}); screenshots.push(path);}
  await page.goto(origin + '/inventory?type=build&selected=' + source.id); await wait(page,'inventoryWorkspace');
  await page.locator('#inventoryWorkspace [data-action="publish"]').click();
  const publish = page.locator('.publish-dialog'); await publish.waitFor({state:'visible'}); await page.waitForFunction(() => !document.querySelector('.publish-dialog').hasAttribute('aria-busy'));
  await publish.locator('[name="title"]').fill('<b>첫 공유 빌드</b>'); await publish.locator('[name="description"]').fill('검색할 수 있는 소개'); await publish.locator('[name="tags"]').fill('입문, 실험');
  await publish.locator('[name="gameVersion"]').fill('작성자가 입력한 버전'); await publish.locator('.publish-form [type="submit"]').click();
  await wait(page,'boardWorkspace'); await page.locator('.board-title').filter({hasText:'첫 공유 빌드'}).waitFor();
  const postId = new URL(page.url()).searchParams.get('post'); assert.ok(postId);
  assert.equal((await reader.request.patch(origin + '/api/posts/' + postId,{headers:{Origin:origin},data:{revision:1,visibility:'private'}})).status(),404);
  assert.equal(await page.locator('.board-title b').count(),0,'Titles must be text, not HTML');
  assert.equal((await api(guest,'posts/' + postId)).release.snapshot.data.status.data.character.level,325);
  await capture(page,'published');
  await anonymous.goto(origin + '/'); await anonymous.locator('.home-rank-row').waitFor({state:'visible'});
  assert.match(await anonymous.locator('.home-rank-row').innerText(),/첫 공유 빌드/);
  await anonymous.locator('.home-rank-row').click(); await wait(anonymous,'boardWorkspace');
  assert.ok(await anonymous.locator('[data-action="copy"]').isVisible());
  await other.goto(origin + '/board?post=' + postId); await wait(other,'boardWorkspace');
  const boardAction = name => other.locator(`#boardWorkspace [data-action="${name}"]`);
  await boardAction('favorite').click(); await other.waitForFunction(() => document.querySelector('#boardWorkspace [data-action="favorite"]').getAttribute('aria-pressed') === 'true');
  assert.equal((await api(guest,'posts/' + postId)).favoriteCount,1);
  await other.locator('.board-search [name="favorites"]').check(); await other.locator('.board-search [type="submit"]').click(); await wait(other,'boardWorkspace');
  assert.equal(await other.locator('.board-list [data-post-id]').count(),1);
  await other.locator('.board-list [data-post-id]').click(); await wait(other,'boardWorkspace');
  await boardAction('copy').click(); await other.getByRole('button',{name:'내 사본 열기',exact:true}).click(); await wait(other,'inventoryWorkspace');
  const copyId = new URL(other.url()).searchParams.get('selected'), copied = await api(reader,'inventory/' + copyId);
  assert.equal(copied.provenance[0].releaseNumber,1);
  copied.data.status.data.character.level = 200;
  await api(reader,'inventory/' + copyId,'PUT',{type:copied.type,schemaVersion:1,name:copied.name,data:copied.data,revision:copied.revision});
  assert.equal((await api(guest,'posts/' + postId)).release.snapshot.data.status.data.character.level,325);
  source.data.status.data.character.level = 300;
  await api(author,'inventory/' + source.id,'PUT',{type:source.type,schemaVersion:1,name:source.name,data:source.data,revision:source.revision});
  await page.locator('.board-owner summary').click(); await page.locator('#boardWorkspace [data-action="release"]').click(); await page.waitForFunction(() => !document.querySelector('.publish-dialog').hasAttribute('aria-busy'));
  await publish.locator('.publish-sources button').filter({hasText:'내 빌드'}).click(); await page.waitForFunction(() => !document.querySelector('.publish-dialog').hasAttribute('aria-busy'));
  await publish.locator('[name="releaseName"]').fill('레벨 변경'); await publish.locator('.publish-form [type="submit"]').click();
  await page.locator('.board-release-heading strong').filter({hasText:'v2'}).waitFor();
  assert.equal((await api(guest,'posts/' + postId)).favoriteCount,1);
  assert.equal((await api(reader,'inventory/' + copyId)).data.status.data.character.level,200);
  await page.locator('#boardWorkspace [data-action="history"]').click(); await page.locator('.board-history-list button').filter({hasText:'v1'}).click();
  await page.locator('.board-release-heading strong').filter({hasText:'v1'}).waitFor(); assert.ok(await page.locator('#boardWorkspace [data-action="latest"]').isVisible());
  await capture(page,'release-history');
  await page.reload(); await wait(page,'boardWorkspace'); assert.match(await page.locator('.board-release-heading strong').innerText(),/v1/);
  await page.locator('#boardWorkspace [data-action="latest"]').click(); await page.locator('.board-release-heading strong').filter({hasText:'v2'}).waitFor();
  await page.locator('.board-owner summary').click(); await page.locator('#boardWorkspace [data-action="visibility"]').click(); await page.locator('.board-visibility').filter({hasText:'비공개'}).waitFor();
  await other.reload(); await wait(other,'inventoryWorkspace'); await other.locator('[data-detail-tab="source"]').click(); await other.getByRole('button',{name:'원본 v1 보기',exact:true}).click(); await wait(other,'boardWorkspace');
  assert.match(await other.locator('.board-status').innerText(),/비공개\/삭제/);
  assert.equal((await guest.request.get(origin + '/api/posts/' + postId + '/releases')).status(),404);
  assert.equal((await guest.request.post(origin + '/api/inventory/copies',{headers:{Origin:origin,'Idempotency-Key':crypto.randomUUID()},data:{postId,releaseNumber:1}})).status(),401);
  assert.equal((await api(reader,'inventory/' + copyId)).data.status.data.character.level,200);
  const privatePost = await api(author,'posts/' + postId); await api(author,'posts/' + postId,'PATCH',{revision:privatePost.revision,visibility:'public'});
  await anonymous.goto(origin + '/'); await anonymous.locator('.home-rank-row').waitFor({state:'visible'}); assert.match(await anonymous.locator('.home-rank-row small').innerText(),/v2/);
  assert.equal(await anonymous.locator('.home-rank-row b').innerText(),'1'); await capture(anonymous,'home-ranking');
  await page.reload(); await wait(page,'boardWorkspace'); await page.locator('.board-owner summary').click();
  const changedPost = await api(author,'posts/' + postId);
  await api(author,'posts/' + postId,'PATCH',{revision:changedPost.revision,title:'다른 창에서 수정'});
  await page.locator('.board-manage [name="title"]').fill('보존할 제목 초안'); await page.locator('.board-manage [type="submit"]').click(); await wait(page,'boardWorkspace');
  assert.match(await page.locator('.board-status').innerText(),/변경/);
  assert.equal(await page.locator('.board-manage [name="title"]').inputValue(),'보존할 제목 초안');
  await page.goto(origin + '/inventory?type=build&selected=' + source.id); await wait(page,'inventoryWorkspace'); await page.locator('#inventoryWorkspace [data-action="publish"]').click();
  await page.waitForFunction(() => !document.querySelector('.publish-dialog').hasAttribute('aria-busy'));
  await publish.locator('[name="title"]').fill('원본 충돌 뒤에도 남을 초안');
  const changedSource = await api(author,'inventory/' + source.id);
  await api(author,'inventory/' + source.id,'PUT',{type:changedSource.type,schemaVersion:1,name:changedSource.name,revision:changedSource.revision,data:changedSource.data});
  await publish.locator('.publish-form [type="submit"]').click(); await page.waitForFunction(() => !document.querySelector('.publish-dialog').hasAttribute('aria-busy'));
  assert.match(await publish.locator('.publish-status').innerText(),/변경/); assert.equal(await publish.locator('[name="title"]').inputValue(),'원본 충돌 뒤에도 남을 초안');
  await publish.locator('.publish-close').click();
  await other.goto(origin + '/board?post=' + postId); await wait(other,'boardWorkspace'); await other.setViewportSize({width:390,height:844});
  assert.ok(await other.evaluate(() => document.documentElement.scrollWidth <= innerWidth)); await capture(other,'mobile-post');
  await anonymous.setViewportSize({width:390,height:844}); assert.ok(await anonymous.evaluate(() => document.documentElement.scrollWidth <= innerWidth)); await capture(anonymous,'mobile-home-ranking');
  assert.deepEqual(errors,[]);
  console.log('Posts browser: PASS (Chrome, inventory publication, guest browse + home ranking, escaped text, post favorites, independent copy/edit, immutable v1/new v2/history/reload, private source link, mobile)');
  console.log('Screenshots: ' + screenshots.join(' | '));
} finally {
  await browser?.close(); await new Promise(done => server.close(done));
  for (const suffix of ['', '-wal','-shm']) await rm(database + suffix,{force:true});
}
