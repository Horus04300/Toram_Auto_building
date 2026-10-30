import {APP_PATHS,contentType,containedFile} from '../server/static-assets.mjs';
import {createAccountServer} from '../server/account-server.mjs';
import {buildWasm} from './build-wasm.mjs';
import { readFile } from 'node:fs/promises';
import { resolve, sep } from 'node:path';
import { pathToFileURL } from 'node:url';
import { renderFrontendHtml } from './prepare-frontend.mjs';
import {frontendSourcePath,renderFrontendModule} from './support/frontend-paths.mjs';

const root = resolve(import.meta.dirname, '..');

export function createWebDevServer(options = {}) {
  return createAccountServer({...options,publicOrigin:options.publicOrigin || 'http://localhost:8787',serveFrontend:async (req, res, pathname) => {
    if (req.method !== 'GET' && req.method !== 'HEAD') {
      res.writeHead(405, { Allow:'GET, HEAD' });
      res.end();
      return;
    }
    if(pathname==='/favicon.ico') { res.writeHead(204);res.end();return; }
    try {
      let content;
      if (APP_PATHS.has(pathname)) {
        if(options.publicOrigin && req.headers.host !== new URL(options.publicOrigin).host) {
          const canonical=new URL(options.publicOrigin);
          canonical.pathname=pathname;canonical.search=new URL(req.url,options.publicOrigin).search;
          res.writeHead(302,{Location:canonical.href});res.end();return;
        }
        content = await renderFrontendHtml('web');
        res.setHeader('Content-Type', 'text/html; charset=utf-8');
      } else {
        const asset = pathname.slice(1);
        if (asset.includes('\\') || asset.split('/').includes('..') || !/^assets\/(js|pages|css|fonts|icons|game-data|wasm)\//u.test(asset) || asset.startsWith('assets/js/') && !/\.(?:m?js)$/u.test(asset)) {
          res.writeHead(404); res.end(); return;
        }
        const source = frontendSourcePath(asset);
        const sourceRoot = resolve(root, source.startsWith('web/src/') ? 'web/src' : source.startsWith('web/public/') ? 'web/public' : 'build/generated/wasm');
        const path = await containedFile(sourceRoot,resolve(root,source));
        if (!resolve(root,source).startsWith(sourceRoot + sep)) {
          res.writeHead(404); res.end(); return;
        }
        content = /\.(?:m?js)$/u.test(path) ? (await renderFrontendModule(asset)).source : await readFile(path);
        res.setHeader('Content-Type', contentType(path));
      }
      res.end(req.method === 'HEAD' ? undefined : content);
    } catch (error) {
      const missing = ['ENOENT', 'ENOTDIR', 'EISDIR', 'EINVAL'].includes(error.code);
      if (!missing) console.error(error);
      res.writeHead(missing ? 404 : 500);
      res.end();
    }
  }});
}

if (process.argv[1] && import.meta.url === pathToFileURL(resolve(process.argv[1])).href) {
  try { process.loadEnvFile(resolve(root,'server/.env')); }
  catch(error) { if(error.code!=='ENOENT') throw error; }
  const port = Number(process.env.PORT || 8787);
  if (!Number.isInteger(port) || port < 1 || port > 65535) throw new Error('PORT must be an integer from 1 to 65535.');
  const publicOrigin=process.env.PUBLIC_ORIGIN || `http://localhost:${port}`;
  const origin=new URL(publicOrigin);
  if(origin.origin!==publicOrigin || origin.protocol!=='http:' || !['localhost','127.0.0.1'].includes(origin.hostname) || Number(origin.port || 80)!==port) throw new Error('Web dev requires matching PORT and HTTP loopback PUBLIC_ORIGIN in server/.env.');
  await buildWasm();
  const clientId=process.env.GOOGLE_CLIENT_ID || '',clientSecret=process.env.GOOGLE_CLIENT_SECRET || '';
  const server = createWebDevServer({publicOrigin,clientId,clientSecret,database:process.env.DATABASE_PATH || resolve(root,'server/data/accounts.sqlite')});
  server.on('error', error => { console.error(error.message); process.exitCode = 1; });
  server.listen(port, '127.0.0.1', () => {
    console.log(`Web development: ${publicOrigin}/ (source frontend + account/inventory/posts API)`);
    console.log(clientId && clientSecret ? `Google login: ready; callback ${publicOrigin}/api/auth/google/callback` : 'Google login: configure GOOGLE_CLIENT_ID and GOOGLE_CLIENT_SECRET in server/.env.');
    console.log('Refresh after editing HTML/JS/CSS; restart after Rust or server changes.');
  });
}
