import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import { readProjectManifest } from '../extraction/convert-toram-project-items.mjs';

export async function readCrystaCatalog(root = resolve(import.meta.dirname,'../..')) {
  const directory=resolve(root,'web/public/game-data/items'), manifest=await readProjectManifest(directory);
  return JSON.parse(await readFile(resolve(directory,manifest.kinds.crystas),'utf8'));
}
