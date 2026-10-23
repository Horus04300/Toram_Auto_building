import assert from 'node:assert/strict';
import { createHash } from 'node:crypto';
import { mkdir, readFile, writeFile } from 'node:fs/promises';
import path from 'node:path';
import { fileURLToPath } from 'node:url';

const root = fileURLToPath(new URL('../..', import.meta.url));
const output = path.resolve(root, process.argv[2] || 'build/tmp/toram-item-extraction/coryn');
const digest = bytes => createHash('sha256').update(bytes).digest('hex');

function validatePage(value, offset, total) {
    assert.equal(value.success, true);
    assert.ok(Array.isArray(value.data));
    assert.equal(value.meta.offset, offset);
    assert.equal(value.meta.limit, 100);
    assert.ok(Number.isSafeInteger(value.meta.total) && value.meta.total > 0);
    if (total !== undefined) assert.equal(value.meta.total, total, 'Catalogue changed during extraction; rerun.');
    assert.equal(value.data.length, Math.min(100, value.meta.total - offset));
    for (const item of value.data) {
        assert.ok(Number.isSafeInteger(item.id) && item.id > 0);
        assert.equal(typeof item.name, 'string');
    }
    return value;
}

function readCrysta(source) {
    assert.match(source, /^\s*const crystaDataJson\s*=\s*\[/);
    const values = JSON.parse(source.slice(source.indexOf('['), source.lastIndexOf(']') + 1));
    assert.ok(Array.isArray(values));
    for (const value of values) {
        assert.equal(typeof value.name, 'string');
        assert.ok(value.stats && typeof value.stats === 'object');
    }
    return values;
}

function selfTest() {
    const valid = { success: true, data: [{ id: 1, name: 'Item' }], meta: { offset: 0, limit: 100, total: 1 } };
    assert.equal(validatePage(valid, 0).data[0].id, 1);
    assert.throws(() => validatePage(valid, 100));
    assert.throws(() => validatePage(valid, 0, 2));
    assert.deepEqual(readCrysta('const crystaDataJson = [{"name":"한글","stats":{"ATK":1}}];'), [{ name: '한글', stats: { ATK: 1 } }]);
    assert.throws(() => readCrysta('runCode();'));
    console.log('PASS: API pagination validation and non-executing local data parser');
}

if (process.argv.includes('--self-test')) {
    selfTest();
} else {
    await mkdir(path.join(output, 'raw'), { recursive: true });
    const sources = [];
    async function capture(url, filename) {
        const response = await fetch(url, { signal: AbortSignal.timeout(30000) });
        assert.equal(response.status, 200, `HTTP ${response.status}: ${url}`);
        const bytes = Buffer.from(await response.arrayBuffer());
        await writeFile(path.join(output, 'raw', filename), bytes);
        sources.push({ url, finalUrl: response.url, filename: `raw/${filename}`, fetchedAt: new Date().toISOString(), sha256: digest(bytes), bytes: bytes.length, contentType: response.headers.get('content-type') });
        return bytes.toString('utf8');
    }
    const startedAt = new Date().toISOString();
    await capture('https://coryn.club/api/', 'api-docs.html');
    await capture('https://coryn.club/item.php?id=8416', 'item-8416.html');
    const sample = JSON.parse(await capture('https://coryn.club/api/v1/items.php?id=8416', 'item-8416.json'));
    assert.equal(sample.success, true);
    assert.equal(sample.data.id, 8416);
    assert.ok(Array.isArray(sample.data.stats));
    for (const language of ['ja', 'ko']) {
        await capture(`https://coryn.club/api/v1/items.php?id=8416&lang=${language}`, `item-8416-lang-${language}.json`);
    }
    const items = [];
    let total;
    for (let offset = 0; total === undefined || offset < total; offset += 100) {
        const raw = await capture(`https://coryn.club/api/v1/items.php?limit=100&offset=${offset}`, `items-${String(offset).padStart(5, '0')}.json`);
        const page = validatePage(JSON.parse(raw), offset, total);
        total = page.meta.total;
        items.push(...page.data);
        if (offset % 1000 === 0) console.log(`${items.length}/${total} Coryn catalogue items`);
        await new Promise(resolve => setTimeout(resolve, 350));
    }
    assert.equal(new Set(items.map(item => item.id)).size, total, 'Duplicate IDs; catalogue may have changed.');
    assert.equal(items.length, total);
    const localPath = 'tools/fixtures/crysta-legacy-data.json';
    const localBytes = await readFile(path.join(root, localPath));
    const crysta = readCrysta('const crystaDataJson = ' + localBytes.toString('utf8') + ';');
    const catalog = items.map(item => ({ source: 'coryn.club', corynItemId: item.id, gameItemId: null, sourceUrl: `https://coryn.club/item.php?id=${item.id}`, language: 'en', ...item }));
    await writeFile(path.join(output, 'items.json'), `${JSON.stringify(catalog, null, 2)}\n`);
    await writeFile(path.join(output, 'existing-ko-crysta.json'), `${JSON.stringify({ source: localPath, sha256: digest(localBytes), gameItemIdsVerified: false, items: crysta }, null, 2)}\n`);
    const typeCounts = {};
    for (const item of items) {
        const key = `${item.type_id}: ${item.type_label}`;
        typeCounts[key] = (typeCounts[key] || 0) + 1;
    }
    const manifest = {
        startedAt, finishedAt: new Date().toISOString(), itemCount: items.length, apiTotal: total, uniqueIds: total, typeCounts,
        localCrystaCount: crysta.length, sources,
        limitations: [
            'Coryn IDs are site database IDs. No game object ID mapping is established.',
            'List responses omit stats. Only raw/item-8416.json is a stat-bearing exact-ID sample; do not treat absent list stats as an item having no stats.',
            'Catalogue names are English. lang=ja and lang=ko are undocumented probes; compare retained bodies. They do not establish a supported localization API.',
            'Historical Korean crysta fixture is preserved unchanged and has no verified game/Coryn ID linkage; it is not the live ID-keyed catalog.',
            'Paginated HTTP requests are not an atomic database snapshot; stable totals and unique IDs do not prove every record stayed unchanged.'
        ]
    };
    await writeFile(path.join(output, 'manifest.json'), `${JSON.stringify(manifest, null, 2)}\n`);
    console.log(JSON.stringify({ output, itemCount: items.length, localCrystaCount: crysta.length, typeCounts }));
}
