import { LEGACY_SCRIPT_PATHS } from './legacy-script-manifest.mjs';

export function loadLegacyScript(documentRef, path) {
  return new Promise((resolve, reject) => {
    const script = documentRef.createElement('script');
    script.type = 'text/javascript';
    script.async = false;
    script.src = new URL(path, documentRef.baseURI).href;
    script.onload = () => resolve();
    script.onerror = () => reject(new Error(`Legacy script failed to load: ${path}`));
    const target = documentRef.head || documentRef.body || documentRef.documentElement;
    if (!target) throw new Error('A document insertion target is required to load legacy scripts.');
    target.appendChild(script);
  });
}

export async function startLegacyApplication(documentRef = document, paths = LEGACY_SCRIPT_PATHS) {
  for (const path of paths) await loadLegacyScript(documentRef, path);
}

await startLegacyApplication();
