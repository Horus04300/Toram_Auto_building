import {realpath} from 'node:fs/promises';
import {extname,sep} from 'node:path';

export const APP_PATHS=new Set(['/','/index.html','/inventory','/calculator','/board','/catalog']);
const mime={'.html':'text/html; charset=utf-8','.js':'text/javascript','.mjs':'text/javascript','.css':'text/css','.json':'application/json',
  '.svg':'image/svg+xml','.png':'image/png','.jpg':'image/jpeg','.jpeg':'image/jpeg','.webp':'image/webp','.ico':'image/x-icon',
  '.woff':'font/woff','.woff2':'font/woff2','.ttf':'font/ttf','.wasm':'application/wasm'};
export const contentType=path=>mime[extname(path)]||'application/octet-stream';
export function staticHeaders(response) {
  for(const [key,value] of Object.entries({'Cache-Control':'no-store','X-Content-Type-Options':'nosniff','Cross-Origin-Opener-Policy':'same-origin','Cross-Origin-Embedder-Policy':'require-corp'})) response.setHeader(key,value);
}
export async function containedFile(base,path) {
  const file=await realpath(path);
  if(!file.startsWith(base+sep)) throw Object.assign(new Error('Asset escapes its root'),{code:'ENOENT'});
  return file;
}
