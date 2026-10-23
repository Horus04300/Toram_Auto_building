import { readFile, writeFile, mkdir } from 'node:fs/promises';
import { resolve, dirname } from 'node:path';
import { fileURLToPath } from 'node:url';
import { gzipSync } from 'node:zlib';
import { performance } from 'node:perf_hooks';
import vm from 'node:vm';
import { readProjectManifest } from '../extraction/convert-toram-project-items.mjs';
import { createItemCatalog } from '../../web/src/application/item-catalog.mjs';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '../..');
const store = resolve(root, 'data/sources/toram-items/pipeline/releaseB');
const pointer = JSON.parse(await readFile(resolve(store, 'latest.json')));
const source = (await readFile(resolve(store, pointer.snapshot, 'items.connected.json'))).toString('utf8');
const full = JSON.parse(source), minified = JSON.stringify(full);
const legacyJson = await readFile(resolve(root, 'tools/fixtures/crysta-legacy-data.json'), 'utf8');
const legacy = `const crystaDataJson = ${legacyJson};`;
const legacyRows = JSON.parse(legacyJson);
const directory = resolve(root, 'web/public/game-data/items'), manifest = await readProjectManifest(directory);
const texts = new Map([['manifest.json', await readFile(resolve(directory,'manifest.json'), 'utf8')]]);
for (const path of Object.keys(manifest.files)) texts.set(path, await readFile(resolve(directory,path), 'utf8'));
const names = new Map();
for (const item of full.items) if (item.names.kr) names.set(item.names.kr, (names.get(item.names.kr) || 0) + 1);

function median(parse) {
  const values = [];
  for (let i = 0; i < 11; i++) { const start = performance.now(); parse(); values.push(performance.now() - start); }
  values.sort((a,b) => a-b);
  return Number(values[5].toFixed(3));
}
function metrics(label, values, parse = () => values.forEach(value => JSON.parse(value))) {
  return { label, files:values.length, bytes:values.reduce((sum,value) => sum + Buffer.byteLength(value),0),
    gzipBytes:values.reduce((sum,value) => sum + gzipSync(value).length,0), parseMedianMs:median(parse) };
}
const requested = [], origin = 'https://benchmark.test/items/';
const loader = createItemCatalog(origin + 'manifest.json', async url => {
  const path = url.href.slice(origin.length); requested.push(path);
  return { ok:true, json:async () => JSON.parse(texts.get(path)) };
});
await loader.getItem(9911, 'kr');
const initial = requested.slice();
await loader.getItem(9911, 'kr');
const repeatAdditionalRequests = requested.length - initial.length;
await loader.getDetails(9911, 'kr');
const detail = requested.slice(initial.length);
const listRequests = [];
await createItemCatalog(origin + 'manifest.json', async url => {
  const path = url.href.slice(origin.length); listRequests.push(path);
  return { ok:true, json:async () => JSON.parse(texts.get(path)) };
}).listItems('crystas', 'kr');
const formats = [
  metrics('historical 425-item classic script fixture', [legacy], () => vm.runInNewContext(legacy)),
  metrics('full 11723-item connected source', [source]),
  metrics('same full source minified', [minified]),
  metrics('project export, all kinds and six locales', [...texts.values()]),
  metrics('first Korean crysta ID lookup, only fetched files', initial.map(path => texts.get(path))),
  metrics('optional Korean crysta details, additional files', detail.map(path => texts.get(path))),
  metrics('Korean crysta names list without stat data', listRequests.map(path => texts.get(path)))
];
const result = { node:process.version, items:full.items.length, legacyItems:legacyRows.length,
  method:'11 parses/evaluations in one Node process; median; input strings prepared outside timing. No browser/network latency or full-app speed claim.',
  duplicateKoreanNameGroups:[...names.values()].filter(count => count > 1).length,
  formats, firstLookupFiles:initial, repeatAdditionalRequests,
  firstLookupByteReductionPercent:Number((100 * (1 - formats[4].bytes / formats[1].bytes)).toFixed(2)), mappingCoverage:manifest.counts };
const output = resolve(root, 'build/tmp/toram-item-format-assessment.json');
await mkdir(dirname(output), { recursive:true });
await writeFile(output, JSON.stringify(result,null,2) + '\n');
console.log(JSON.stringify(result,null,2));
