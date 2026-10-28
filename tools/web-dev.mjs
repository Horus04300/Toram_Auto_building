import {APP_PATHS,contentType,staticHeaders,containedFile} from '../server/static-assets.mjs';
import {buildWasm} from './build-wasm.mjs';
import { createServer } from 'node:http';
import { readFile, realpath } from 'node:fs/promises';
import { extname, resolve, sep } from 'node:path';
import { pathToFileURL } from 'node:url';
import { renderFrontendHtml } from './prepare-frontend.mjs';
import {frontendSourcePath,renderFrontendModule} from './support/frontend-paths.mjs';

const root = resolve(import.meta.dirname, '..');

export function createWebDevServer() {
  return createServer(async (req, res) => {
    staticHeaders(res);
    if (req.method !== 'GET' && req.method !== 'HEAD') {
      res.writeHead(405, { Allow:'GET, HEAD' });
      res.end();
      return;
    }
    let pathname;
    try { pathname = decodeURIComponent(new URL(req.url, 'http://localhost').pathname); }
    catch { res.writeHead(400); res.end(); return; }
    try {
      let content;
      if (APP_PATHS.has(pathname)) {
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
  });
}

if (process.argv[1] && import.meta.url === pathToFileURL(resolve(process.argv[1])).href) {
  await buildWasm();
  const port = Number(process.env.PORT || 5173);
  if (!Number.isInteger(port) || port < 1 || port > 65535) throw new Error('PORT must be an integer from 1 to 65535.');
  const server = createWebDevServer();
  server.on('error', error => { console.error(error.message); process.exitCode = 1; });
  server.listen(port, '127.0.0.1', () => console.log(`Web development: http://127.0.0.1:${port}/ (refresh after editing)`));
}
