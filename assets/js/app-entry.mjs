import { CLASSIC_SCRIPT_PATHS } from './classic-script-manifest.mjs';

export function loadClassicScript(documentRef, path) {
  return new Promise((resolve, reject) => {
    const script = documentRef.createElement('script');
    script.type = 'text/javascript';
    script.async = false;
    script.src = new URL(path, documentRef.baseURI).href;
    script.onload = () => resolve();
    script.onerror = () => reject(new Error(`Classic script failed to load: ${path}`));
    const target = documentRef.head || documentRef.body || documentRef.documentElement;
    if (!target) throw new Error('A document insertion target is required to load legacy scripts.');
    target.appendChild(script);
  });
}

export async function startApplication(documentRef = document, paths = CLASSIC_SCRIPT_PATHS) {
  for (const path of paths) await loadClassicScript(documentRef, path);
}

await startApplication();
