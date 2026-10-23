import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import { readProjectManifest } from '../extraction/convert-toram-project-items.mjs';

export async function readCrystaDataSource(root = resolve(import.meta.dirname, '../..')) {
  const directory = resolve(root, 'web/public/game-data/items');
  const manifest = await readProjectManifest(directory);
  const records = await readFile(resolve(directory, manifest.kinds.crystas), 'utf8');
  const adapter = await readFile(resolve(root, 'web/src/data/crysta-data.js'), 'utf8');
  return `globalThis.TORAM_CRYSTA_CATALOG_DATA=${records};\nif(typeof window!=='undefined')window.TORAM_CRYSTA_CATALOG_DATA=globalThis.TORAM_CRYSTA_CATALOG_DATA;\n${adapter}`;
}
