import { createServer } from 'node:http';
import { readFile, realpath } from 'node:fs/promises';
import { extname, resolve, sep } from 'node:path';
import { pathToFileURL } from 'node:url';
import { renderFrontendHtml } from './prepare-frontend.mjs';
import { WEB_CLASSIC_SCRIPT_PATHS } from '../web/src/classic-script-manifest.mjs';
import { frontendSourcePath, FRONTEND_MODULE_PATHS } from './support/frontend-paths.mjs';

const root = resolve(import.meta.dirname, '..');
const scripts = new Set([...WEB_CLASSIC_SCRIPT_PATHS, ...FRONTEND_MODULE_PATHS]);
const mime = {
  '.js':'text/javascript', '.mjs':'text/javascript', '.css':'text/css',
  '.json':'application/json', '.svg':'image/svg+xml', '.png':'image/png',
  '.jpg':'image/jpeg', '.jpeg':'image/jpeg', '.webp':'image/webp', '.ico':'image/x-icon',
  '.woff':'font/woff', '.woff2':'font/woff2', '.ttf':'font/ttf', '.wasm':'application/wasm'
};

export function createWebDevServer() {
  return createServer(async (req, res) => {
    res.setHeader('Cache-Control', 'no-store');
    res.setHeader('X-Content-Type-Options', 'nosniff');
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
      if (pathname === '/' || pathname === '/index.html') {
        content = await renderFrontendHtml('web');
        res.setHeader('Content-Type', 'text/html; charset=utf-8');
      } else {
        const asset = pathname.slice(1);
        if (asset.includes('\\') || asset.split('/').includes('..') || !(scripts.has(asset) || /^assets\/(css|fonts|icons|game-data|wasm)\//u.test(asset))) {
          res.writeHead(404); res.end(); return;
        }
        const source = frontendSourcePath(asset);
        const sourceRoot = resolve(root, source.startsWith('web/src/') ? 'web/src' : source.startsWith('web/public/') ? 'web/public' : 'build/generated/wasm');
        const path = resolve(root, source);
        if (!path.startsWith(sourceRoot + sep) || !(await realpath(path)).startsWith(sourceRoot + sep)) {
          res.writeHead(404); res.end(); return;
        }
        content = await readFile(path);
        res.setHeader('Content-Type', mime[extname(path)] || 'application/octet-stream');
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
  const port = Number(process.env.PORT || 5173);
  if (!Number.isInteger(port) || port < 1 || port > 65535) throw new Error('PORT must be an integer from 1 to 65535.');
  const server = createWebDevServer();
  server.on('error', error => { console.error(error.message); process.exitCode = 1; });
  server.listen(port, '127.0.0.1', () => console.log(`Web development: http://127.0.0.1:${port}/ (refresh after editing)`));
}
