import { createHash, randomBytes } from 'node:crypto';
import { DatabaseSync } from 'node:sqlite';
import { resolve } from 'node:path';
import { pathToFileURL } from 'node:url';
import { createAccountServer } from '../server/account-server.mjs';
import { prepareFrontend } from './prepare-frontend.mjs';

const userId = 'local-preview';
const landing = `<!doctype html><html lang="ko"><meta charset="utf-8"><meta name="viewport" content="width=device-width"><title>토람 로컬 체험</title><link rel="stylesheet" href="/assets/css/style.css"><main><h1>로컬 체험 계정</h1><p>Google 로그인 없이 인벤토리 저장·편집·조립을 테스트합니다.</p><p>이 컴퓨터의 체험 브라우저는 같은 계정을 사용합니다. 저장한 구성은 별도의 개발용 DB에 남으며 실제 계정과 연결되지 않습니다.</p><form method="post" action="/__preview/login"><button type="submit" class="result-secondary-button">체험 계정으로 인벤토리 열기</button></form><p>계산기에서 장비나 빌드를 설정한 뒤, 인벤토리의 ‘계산기 구성 담기’를 사용하세요. 로그아웃했다면 이 페이지에서 다시 들어올 수 있습니다.</p><p><a href="/">홈으로</a></p></main></html>`;

// This launcher is excluded from production/Docker; it owns a separate local test DB.
export async function startPlatformPreview({ port = 5182, directory = resolve(import.meta.dirname,'../build/tmp/platform-preview') } = {}) {
  if (process.env.NODE_ENV === 'production') throw new Error('Local preview cannot run in production.');
  if (!Number.isInteger(port) || port < 1 || port > 65535) throw new Error('Preview port must be 1–65535.');
  const origin = `http://127.0.0.1:${port}`, database = resolve(directory,'accounts.sqlite');
  const server = createAccountServer({publicOrigin:origin,database});
  function withDb(work) { const db = new DatabaseSync(database); try { db.exec('PRAGMA busy_timeout=5000;'); return work(db); } finally { db.close(); } }
  withDb(db => db.prepare('INSERT INTO users VALUES (?,?,?) ON CONFLICT(id) DO NOTHING').run(userId,'local-preview-only','로컬 체험 계정'));
  const accountHandler = server.listeners('request')[0];
  server.removeListener('request',accountHandler);
  server.on('request',(req,res) => {
    res.setHeader('Cache-Control','no-store');
    res.setHeader('X-Content-Type-Options','nosniff');
    if (req.headers.host !== new URL(origin).host) { res.writeHead(403); res.end('Local preview host only.'); return; }
    let path;
    try { path = new URL(req.url,origin).pathname; }
    catch { res.writeHead(400); res.end(); return; }
    if (!path.startsWith('/__preview')) { void accountHandler(req,res); return; }
    res.setHeader('Content-Security-Policy',"default-src 'self'; form-action 'self'; frame-ancestors 'none'");
    if (path === '/__preview' && ['GET','HEAD'].includes(req.method)) {
      res.writeHead(200,{'Content-Type':'text/html; charset=utf-8'}); res.end(req.method === 'HEAD' ? undefined : landing); return;
    }
    if (path !== '/__preview/login') { res.writeHead(404); res.end(); return; }
    if (req.method !== 'POST') { res.writeHead(405,{Allow:'POST'}); res.end(); return; }
    if (req.headers.origin !== origin || req.headers['sec-fetch-site'] === 'cross-site') { res.writeHead(403); res.end('Open the local preview page first.'); return; }
    try {
      const token = randomBytes(32).toString('base64url'), expires = Date.now() + 8 * 3600000;
      withDb(db => {
        db.prepare('DELETE FROM sessions WHERE expires_at<=?').run(Date.now());
        db.prepare('INSERT INTO sessions VALUES (?,?,?,?)').run(createHash('sha256').update(token).digest('hex'),userId,'web',expires);
      });
      res.writeHead(303,{Location:'/inventory?type=equipment','Set-Cookie':`toram_session=${token}; Path=/; HttpOnly; SameSite=Lax; Max-Age=28800`}); res.end();
    } catch { res.writeHead(500); res.end('Local preview session could not be created.'); }
  });
  try {
    await new Promise((done,reject) => { server.once('error',reject); server.listen(port,'127.0.0.1',done); });
  } catch (error) { server.emit('close'); throw error; }
  return {server,origin,database};
}

if (process.argv[1] && import.meta.url === pathToFileURL(resolve(process.argv[1])).href) {
  await prepareFrontend('web');
  const {origin,database} = await startPlatformPreview();
  console.log(`Local inventory preview: ${origin}/__preview\nDevelopment DB: ${database}\nGoogle login is not used. Bind: 127.0.0.1 only.`);
}
