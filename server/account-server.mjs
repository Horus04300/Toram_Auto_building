import {createLegacyRecords} from './legacy-records.mjs';
import {RECORD_KINDS as kinds} from './account-records.mjs';
import {APP_PATHS,contentType,staticHeaders,containedFile} from './static-assets.mjs';
import { createServer } from 'node:http';
import { DatabaseSync } from 'node:sqlite';
import { createHash, randomBytes, randomUUID } from 'node:crypto';
import { mkdirSync } from 'node:fs';
import { readFile, realpath } from 'node:fs/promises';
import { dirname, extname, resolve, sep } from 'node:path';
import { pathToFileURL } from 'node:url';
import { createInventoryStore } from './inventory-store.mjs';
import { createPostStore } from './post-store.mjs';

const hash = value => createHash('sha256').update(value).digest('hex');
const random = () => randomBytes(32).toString('base64url');
const object = value => value && typeof value === 'object' && !Array.isArray(value);
const fail = (status, message) => Object.assign(new Error(message), { status });
const maxBody = 1024 * 1024;

function name(value, length = 80) {
  if (typeof value !== 'string' || !value.trim() || value.trim().length > length || /[\x00-\x1f\x7f]/u.test(value)) throw fail(400, '이름을 올바르게 입력하세요.');
  return value.trim();
}

async function body(req) {
  if (!/^application\/json(?:;|$)/iu.test(req.headers['content-type'] || '')) throw fail(415, 'JSON 요청이 필요합니다.');
  if (Number(req.headers['content-length']) > maxBody) throw fail(413, '저장 데이터는 1 MiB 이하여야 합니다.');
  let size = 0;
  const chunks = [];
  for await (const chunk of req) {
    size += chunk.length;
    if (size > maxBody) throw fail(413, '저장 데이터는 1 MiB 이하여야 합니다.');
    chunks.push(chunk);
  }
  try { const value = JSON.parse(Buffer.concat(chunks).toString()); if (!object(value)) throw new Error(); return value; }
  catch { throw fail(400, 'JSON 형식이 올바르지 않습니다.'); }
}

export function createAccountServer({ publicOrigin, clientId = '', clientSecret = '', database = ':memory:', frontend = resolve(import.meta.dirname, '../build/web'), fetchImpl = fetch } = {}) {
  const origin = new URL(publicOrigin);
  if (origin.origin !== publicOrigin || origin.username || origin.password || (origin.protocol !== 'https:' && !(origin.protocol === 'http:' && ['localhost','127.0.0.1'].includes(origin.hostname)))) throw new Error('PUBLIC_ORIGIN must be an HTTPS origin (HTTP loopback is allowed for local testing).');
  if (database !== ':memory:') mkdirSync(dirname(database), { recursive:true });
  const db = new DatabaseSync(database);
  db.exec(`PRAGMA foreign_keys=ON; PRAGMA journal_mode=WAL; PRAGMA busy_timeout=5000;
    CREATE TABLE IF NOT EXISTS users (id TEXT PRIMARY KEY, google_sub TEXT NOT NULL UNIQUE, nickname TEXT NOT NULL);
    CREATE TABLE IF NOT EXISTS sessions (token_hash TEXT PRIMARY KEY, user_id TEXT NOT NULL REFERENCES users(id) ON DELETE CASCADE, kind TEXT NOT NULL, expires_at INTEGER NOT NULL);
    CREATE INDEX IF NOT EXISTS sessions_expiry ON sessions(expires_at);
    CREATE TABLE IF NOT EXISTS desktop_logins (id TEXT PRIMARY KEY, challenge TEXT NOT NULL, user_id TEXT REFERENCES users(id) ON DELETE CASCADE, expires_at INTEGER NOT NULL);
    CREATE TABLE IF NOT EXISTS oauth_states (state_hash TEXT PRIMARY KEY, verifier TEXT NOT NULL, desktop_id TEXT, expires_at INTEGER NOT NULL);
    CREATE TABLE IF NOT EXISTS records (id TEXT PRIMARY KEY, user_id TEXT NOT NULL REFERENCES users(id) ON DELETE CASCADE, kind TEXT NOT NULL, name TEXT NOT NULL, data TEXT NOT NULL, version INTEGER NOT NULL DEFAULT 1, updated_at TEXT NOT NULL);
    CREATE INDEX IF NOT EXISTS records_owner ON records(user_id,kind);`);
  const inventory = createInventoryStore(db);
  const records = createLegacyRecords(db,inventory);
  const posts = createPostStore(db,inventory);
  const configured = Boolean(clientId && clientSecret);
  const cookieName = origin.protocol === 'https:' ? '__Host-toram_session' : 'toram_session';
  const loginCookie = origin.protocol === 'https:' ? '__Host-toram_login' : 'toram_login';
  const desktopOrigins = new Set(['http://tauri.localhost', 'https://tauri.localhost', 'tauri://localhost']);
  const limits = new Map();
  const cookie = (key, value, seconds) => `${key}=${value}; Path=/; HttpOnly; SameSite=Lax; Max-Age=${seconds}${origin.protocol === 'https:' ? '; Secure' : ''}`;
  function cookies(req) { return Object.fromEntries((req.headers.cookie || '').split(';').map(part => part.trim().split('='))); }
  function json(res, status, value) { res.writeHead(status, { 'Content-Type':'application/json; charset=utf-8' }); res.end(JSON.stringify(value)); }
  function redirect(res, path) { res.writeHead(302, { Location:path }); res.end(); }
  function session(req) {
    const bearer = req.headers.authorization?.match(/^Bearer ([A-Za-z0-9_-]{43})$/u)?.[1];
    const token = bearer || cookies(req)[cookieName];
    if (!token) return null;
    return db.prepare('SELECT s.token_hash, s.kind, u.id, u.nickname FROM sessions s JOIN users u ON u.id=s.user_id WHERE token_hash=? AND expires_at>? AND kind=?').get(hash(token), Date.now(), bearer ? 'desktop' : 'web') || null;
  }
  function createSession(userId, kind) {
    const token = random();
    db.prepare('INSERT INTO sessions VALUES (?,?,?,?)').run(hash(token), userId, kind, Date.now() + 7 * 86400000);
    return token;
  }
  function cleanup() {
    const now = Date.now();
    for (const table of ['sessions', 'desktop_logins', 'oauth_states']) db.prepare(`DELETE FROM ${table} WHERE expires_at<=?`).run(now);
    for (const [key, limit] of limits) if (limit.until < now) limits.delete(key);
  }
  function rate(req, bucket, max) {
    const key = bucket + ':' + req.socket.remoteAddress;
    let limit = limits.get(key);
    if (!limit || limit.until < Date.now()) {
      if (limits.size > 5000) throw fail(503, '서버가 혼잡합니다. 잠시 후 다시 시도하세요.');
      limit = { count:0, until:Date.now() + 600000 }; limits.set(key, limit);
    }
    if (++limit.count > max) throw fail(429, '요청이 너무 많습니다. 잠시 후 다시 시도하세요.');
  }
  async function google(url, options) {
    const response = await fetchImpl(url, { ...options, signal:AbortSignal.timeout(10000), redirect:'error' });
    if (!response.ok) throw fail(502, 'Google 인증에 실패했습니다. 다시 로그인해 주세요.');
    return response.json();
  }
  async function staticFile(req, res, pathname) {
    if (pathname === '/favicon.ico' && req.method === 'GET') { res.writeHead(204); res.end(); return; }
    const entry = APP_PATHS.has(pathname);
    if (!['GET','HEAD'].includes(req.method) || (!entry && !pathname.startsWith('/assets/'))) throw fail(404, '찾을 수 없습니다.');
    const base = await realpath(frontend);
    const file = await containedFile(base,resolve(base,'.'+(entry ? '/index.html' : pathname)));
    const content = await readFile(file);
    res.writeHead(200, { 'Content-Type':contentType(file) });
    res.end(req.method === 'HEAD' ? undefined : content);
  }
  const server = createServer({ maxHeaderSize:16384, requestTimeout:20000 }, async (req, res) => {
    staticHeaders(res);
    res.setHeader('Referrer-Policy', 'no-referrer');
    res.setHeader('Vary', 'Origin');
    const requestOrigin = req.headers.origin;
    try {
      const url = new URL(req.url, publicOrigin);
      const path = url.pathname;
      if (!path.startsWith('/api/')) { await staticFile(req, res, decodeURIComponent(path)); return; }
      if (requestOrigin && requestOrigin !== publicOrigin && !desktopOrigins.has(requestOrigin)) throw fail(403, '허용되지 않은 출처입니다.');
      if (desktopOrigins.has(requestOrigin)) {
        res.setHeader('Access-Control-Allow-Origin', requestOrigin);
        res.setHeader('Access-Control-Allow-Headers', 'Content-Type, Authorization, Idempotency-Key');
        res.setHeader('Access-Control-Allow-Methods', 'GET, POST, PUT, PATCH, DELETE, OPTIONS');
      }
      if (req.method === 'OPTIONS') { res.writeHead(204); res.end(); return; }
      if (!['GET','HEAD'].includes(req.method) && !requestOrigin) throw fail(403, '요청 출처가 필요합니다.');
      cleanup(); rate(req, 'api', 1000);
      const user = session(req);
      if (path === '/api/session' && req.method === 'GET') { json(res, 200, { configured, user:user ? { id:user.id, nickname:user.nickname } : null }); return; }
      const postPath = path.match(/^\/api\/posts\/([a-f0-9-]{36})(?:\/(releases|favorite)(?:\/(\d+))?)?$/u);
      if (req.method === 'GET') {
        if (path === '/api/posts') { json(res,200,posts.list(user?.id,url.searchParams)); return; }
        if (postPath && !postPath[2]) { json(res,200,posts.get(postPath[1],user?.id)); return; }
        if (postPath?.[2] === 'releases') {
          json(res,200,postPath[3] ? posts.get(postPath[1],user?.id,Number(postPath[3])) : posts.history(postPath[1],user?.id,url.searchParams)); return;
        }
      }
      if (path === '/api/auth/desktop' && req.method === 'POST') {
        if (!configured) throw fail(503, 'Google 로그인 서버 설정이 필요합니다.');
        rate(req, 'login', 30);
        const { challenge } = await body(req);
        if (!/^[a-f0-9]{64}$/u.test(challenge || '')) throw fail(400, '로그인 요청이 올바르지 않습니다.');
        const id = random(), expiresAt = Date.now() + 300000;
        db.prepare('INSERT INTO desktop_logins (id,challenge,expires_at) VALUES (?,?,?)').run(id, challenge, expiresAt);
        json(res, 201, { id, expiresAt }); return;
      }
      if (path.startsWith('/api/auth/desktop/') && req.method === 'POST') {
        const { secret } = await body(req);
        if (typeof secret !== 'string' || secret.length < 43 || secret.length > 200) throw fail(400, '로그인 요청이 올바르지 않습니다.');
        const login = db.prepare('SELECT * FROM desktop_logins WHERE id=? AND challenge=?').get(path.split('/').at(-1), hash(secret));
        if (!login) throw fail(410, '로그인 요청이 만료됐습니다. 다시 시도하세요.');
        if (!login.user_id) { json(res, 200, { pending:true }); return; }
        db.prepare('DELETE FROM desktop_logins WHERE id=?').run(login.id);
        const member = db.prepare('SELECT id,nickname FROM users WHERE id=?').get(login.user_id);
        json(res, 200, { token:createSession(member.id, 'desktop'), user:member }); return;
      }
      if (path === '/api/auth/google' && req.method === 'GET') {
        if (!configured) throw fail(503, 'Google 로그인 서버 설정이 필요합니다.');
        rate(req, 'login', 30);
        const desktopId = url.searchParams.get('desktop');
        if (desktopId && !db.prepare('SELECT id FROM desktop_logins WHERE id=? AND user_id IS NULL').get(desktopId)) throw fail(410, '로그인 요청이 만료됐습니다.');
        const state = random(), verifier = random();
        db.prepare('INSERT INTO oauth_states VALUES (?,?,?,?)').run(hash(state), verifier, desktopId, Date.now() + 300000);
        const googleUrl = new URL('https://accounts.google.com/o/oauth2/v2/auth');
        googleUrl.search = new URLSearchParams({ client_id:clientId, redirect_uri:publicOrigin + '/api/auth/google/callback', response_type:'code', scope:'openid profile', state, code_challenge:createHash('sha256').update(verifier).digest('base64url'), code_challenge_method:'S256', prompt:'select_account' }).toString();
        res.setHeader('Set-Cookie', cookie(loginCookie, state, 300));
        redirect(res, googleUrl.href); return;
      }
      if (path === '/api/auth/google/callback' && req.method === 'GET') {
        const state = url.searchParams.get('state'), savedState = cookies(req)[loginCookie];
        if (!state || state !== savedState) throw fail(400, '로그인 요청이 일치하지 않습니다. 다시 로그인해 주세요.');
        const pending = db.prepare('DELETE FROM oauth_states WHERE state_hash=? RETURNING *').get(hash(state));
        res.setHeader('Set-Cookie', cookie(loginCookie, '', 0));
        if (!pending || !url.searchParams.get('code') || url.searchParams.has('error')) throw fail(400, '로그인이 취소되었거나 만료됐습니다.');
        const tokens = await google('https://oauth2.googleapis.com/token', { method:'POST', headers:{ 'Content-Type':'application/x-www-form-urlencoded' }, body:new URLSearchParams({ code:url.searchParams.get('code'), client_id:clientId, client_secret:clientSecret, redirect_uri:publicOrigin + '/api/auth/google/callback', grant_type:'authorization_code', code_verifier:pending.verifier }) });
        if (typeof tokens.access_token !== 'string' || !tokens.access_token) throw fail(502, 'Google 인증 응답이 올바르지 않습니다.');
        const info = await google('https://openidconnect.googleapis.com/v1/userinfo', { headers:{ Authorization:'Bearer ' + tokens.access_token } });
        if (typeof info.sub !== 'string' || !info.sub || info.sub.length > 255) throw fail(502, 'Google 계정을 확인할 수 없습니다.');
        const nickname = (typeof info.name === 'string' ? info.name.replace(/[\x00-\x1f\x7f]/gu, '').trim().slice(0, 40) : '') || '토람 모험가';
        db.prepare('INSERT INTO users VALUES (?,?,?) ON CONFLICT(google_sub) DO NOTHING').run(randomUUID(), info.sub, nickname);
        const member = db.prepare('SELECT id,nickname FROM users WHERE google_sub=?').get(info.sub);
        if (pending.desktop_id) {
          const result = db.prepare('UPDATE desktop_logins SET user_id=? WHERE id=? AND user_id IS NULL AND expires_at>?').run(member.id, pending.desktop_id, Date.now());
          if (!result.changes) throw fail(410, '앱 로그인 대기 시간이 끝났습니다.');
          res.writeHead(200, { 'Content-Type':'text/html; charset=utf-8', 'Content-Security-Policy':"default-src 'none'; frame-ancestors 'none'" });
          res.end('<!doctype html><html lang="ko"><meta charset="utf-8"><meta name="viewport" content="width=device-width"><title>Google 로그인 완료</title><h1>로그인했습니다.</h1><p>토람 계산기 앱으로 돌아가세요. 이 창은 닫아도 됩니다.</p></html>'); return;
        }
        const old = session(req);
        if (old) db.prepare('DELETE FROM sessions WHERE token_hash=?').run(old.token_hash);
        res.setHeader('Set-Cookie', [cookie(loginCookie, '', 0), cookie(cookieName, createSession(member.id, 'web'), 604800)]);
        redirect(res, '/?account=connected'); return;
      }
      if (!user) throw fail(401, '로그인이 필요합니다.');
      if (path === '/api/me/posts' && req.method === 'GET') { json(res,200,posts.list(user.id,url.searchParams,true)); return; }
      if (path === '/api/posts' && req.method === 'POST') { json(res,201,posts.publish(user.id,await body(req),req.headers['idempotency-key'])); return; }
      if (path === '/api/inventory/copies' && req.method === 'POST') { json(res,201,posts.copy(user.id,await body(req),req.headers['idempotency-key'])); return; }
      if (postPath && !postPath[3]) {
        if (!postPath[2] && req.method === 'PATCH') { json(res,200,posts.manage(user.id,postPath[1],await body(req))); return; }
        if (postPath[2] === 'releases' && req.method === 'POST') { json(res,201,posts.publish(user.id,await body(req),req.headers['idempotency-key'],postPath[1])); return; }
        if (postPath[2] === 'favorite' && ['PUT','DELETE'].includes(req.method)) { await body(req); json(res,200,posts.favorite(user.id,postPath[1],req.method === 'PUT')); return; }
      }
      if (req.method === 'POST' && path === '/api/inventory/merges/preview') { json(res,200,inventory.preview(user.id,await body(req))); return; }
      if (req.method === 'POST' && path === '/api/inventory/merges') { json(res,201,inventory.merge(user.id,await body(req),req.headers['idempotency-key'])); return; }
      if (path === '/api/inventory') {
        if (req.method === 'GET') { json(res, 200, inventory.list(user.id, url.searchParams)); return; }
        if (req.method === 'POST') { json(res, 201, inventory.create(user.id, await body(req))); return; }
        throw fail(405, '지원하지 않는 요청입니다.');
      }
      const inventoryId = path.match(/^\/api\/inventory\/([a-f0-9-]{36})$/u)?.[1];
      if (inventoryId) {
        if (req.method === 'GET') { json(res, 200, inventory.get(user.id, inventoryId)); return; }
        if (req.method === 'PUT') { json(res, 200, inventory.update(user.id, inventoryId, await body(req))); return; }
        if (req.method === 'DELETE') { json(res, 200, inventory.remove(user.id, inventoryId, await body(req))); return; }
        throw fail(405, '지원하지 않는 요청입니다.');
      }
      if (path === '/api/logout' && req.method === 'POST') {
        db.prepare('DELETE FROM sessions WHERE token_hash=?').run(user.token_hash);
        if (user.kind === 'web') res.setHeader('Set-Cookie', cookie(cookieName, '', 0));
        json(res, 200, { ok:true }); return;
      }
      if (path === '/api/me' && req.method === 'PATCH') {
        const nickname = name((await body(req)).nickname, 40);
        db.prepare('UPDATE users SET nickname=? WHERE id=?').run(nickname, user.id);
        json(res, 200, { id:user.id, nickname }); return;
      }
      const parts = path.split('/'), kind = parts[2], id = parts[3];
      if (!kinds.has(kind) || parts.length > 4 || id === '') throw fail(404, '찾을 수 없습니다.');
      if (!id && req.method==='GET') {json(res,200,records.list(user.id,kind));return;}
      if (!id && req.method==='POST') {
        const input=await body(req);
        json(res,201,records.create(user.id,kind,name(input.name),input.data));return;
      }
      if(!id) throw fail(404,'저장 항목을 찾을 수 없습니다.');
      if(req.method==='GET') {json(res,200,records.get(user.id,kind,id));return;}
      if(req.method==='DELETE') {json(res,200,records.remove(user.id,kind,id,await body(req)));return;}
      records.get(user.id,kind,id);
      throw fail(405, '지원하지 않는 요청입니다.');
    } catch (error) {
      if (res.headersSent) { res.end(); return; }
      const missing = ['ENOENT','ENOTDIR','EISDIR','EINVAL'].includes(error.code);
      const status = error.status || (missing ? 404 : 500);
      json(res, status, { error:error.status ? error.message : missing ? '찾을 수 없습니다.' : '서버 처리에 실패했습니다.',
        ...(req.url.startsWith('/api/inventory') || req.url.startsWith('/api/posts') || req.url.startsWith('/api/me/posts') ? { code:error.apiCode || ({400:'INVALID_INPUT',401:'AUTH_REQUIRED',403:'ORIGIN_REJECTED',404:'OBJECT_UNAVAILABLE',413:'BODY_TOO_LARGE',415:'JSON_REQUIRED',429:'RATE_LIMITED'})[status] || 'REQUEST_FAILED' } : {}) });
    }
  });
  server.on('close', () => db.close());
  return server;
}

if (process.argv[1] && import.meta.url === pathToFileURL(resolve(process.argv[1])).href) {
  const port = Number(process.env.PORT || 8787);
  if (!Number.isInteger(port) || port < 1 || port > 65535) throw new Error('PORT must be between 1 and 65535.');
  const server = createAccountServer({ publicOrigin:process.env.PUBLIC_ORIGIN, clientId:process.env.GOOGLE_CLIENT_ID, clientSecret:process.env.GOOGLE_CLIENT_SECRET,
    database:process.env.DATABASE_PATH || resolve(import.meta.dirname, 'data/accounts.sqlite') });
  server.listen(port, '0.0.0.0', () => console.log(`Account server listening on ${port}`));
}
