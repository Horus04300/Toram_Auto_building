import assert from 'node:assert/strict';
import { createHash } from 'node:crypto';
import { readFile, writeFile } from 'node:fs/promises';
import { createRequire } from 'node:module';
import { fileURLToPath } from 'node:url';

const root = new URL('../..', import.meta.url);
const require = createRequire(import.meta.url);
const registry = require('../../web/src/calculation/stat-registry.js');
const sha256 = bytes => createHash('sha256').update(bytes).digest('hex');
const normalizeName = name => name.normalize('NFKC').toLowerCase().replace(/\s+/gu, '');
const normalizeNumericSuffix = name => normalizeName(name).replace(/(?:viii|vii|iii|vi|iv|ii|ix|x|v|i)$/u,
    suffix => ({ i: '1', ii: '2', iii: '3', iv: '4', v: '5', vi: '6', vii: '7', viii: '8', ix: '9', x: '10' })[suffix]);
const categoryRows = [
    [31, 'NormalBlueCrista', '노말', 9708066, '3e'],
    [32, 'WeaponRedCrista', '무기', 9708067, '40'],
    [33, 'ArmorGreenCrista', '방어구', 9708068, '42'],
    [34, 'AddEquipYellowCrista', '추가', 9708069, '44'],
    [35, 'SpecialPurpleCrista', '특수', 9708070, '46'],
    [61, 'PowerUpNormalCrista', '노말', 9708075, '7a'],
    [62, 'PowerUpWeaponCrista', '무기', 9708076, '7c'],
    [63, 'PowerUpArmorCrista', '방어구', 9708077, '7e'],
    [64, 'PowerUpAddEquipCrista', '추가', 9708078, '8080'],
    [65, 'PowerUpSpecialCrista', '특수', 9708080, '8082']
];
const categories = new Map(categoryRows.map(([id, enumName, category]) => [id, { enumName, category }]));
const conditionRanges = [[96, 103], [108, 109], [115, 120]];

// Only direct numeric meanings shared by BonusType, the Korean template and the app registry/tagMap.
const capStats = {
    bStr: 'STR', bInt: 'INT', bVit: 'VIT', bAgi: 'AGI', bDex: 'DEX',
    bStrRate: 'STRP', bIntRate: 'INTP', bVitRate: 'VITP', bAgiRate: 'AGIP', bDexRate: 'DEXP',
    bMaxHp: 'MAXHP', bMaxHpTo10: 'MAXHP', bMaxHpRate: 'MAXHPP', bMaxMp: 'MAXMP', bMaxMpTo10: 'MAXMP',
    bEqAtk: 'WATK', bEqAtkRate: 'WATKP', bAtk: 'ATK', bAtkRate: 'ATKP', bMatk: 'MATK', bMatkRate: 'MATKP',
    bSta: 'STABILITY', bHit: 'ACC', bHitRate: 'ACCP', bFlee: 'FLEE', bFleeRate: 'FLEEP',
    bDef: 'DEF', bDefRate: 'DEFP', bMdef: 'MDEF', bMdefRate: 'MDEFP',
    bAspd: 'ASPD', bAspdRate: 'ASPD_P', bCspd: 'CSPD', bCspdRate: 'CSPD_P',
    bHpRecovery: 'HP_REGEN', bHpRecoveryRate: 'HP_REGENP', bMpRecovery: 'MP_REGEN', bMpRecoveryRate: 'MP_REGENP',
    bAtkMpRecovery: 'AMPR', bAtkMpRecoveryRate: 'AMPRP', bCritical: 'CRIT', bCriticalRate: 'CRITP',
    bCriticalDmg: 'CDMG', bCriticalDmgRate: 'CDMGP', bAntiVirus: 'AILMENT_RES',
    bGuard: 'GUARD_RECHARGE', bGuardPower: 'GUARD_POWER', bAvoid: 'AVOID_RECHARGE',
    bPowerResist: 'PHYS_RES', bMagicResist: 'MAG_RES', bPowerResistBreaker: 'PHYS_PIERCE', bMagicResistBreaker: 'MAG_PIERCE',
    bFireKiller: 'FIRE_DMG', bAquaKiller: 'WATER_DMG', bWindKiller: 'WIND_DMG', bEarthKiller: 'EARTH_DMG',
    bLightKiller: 'LIGHT_DMG', bDarkKiller: 'DARK_DMG', bNormalKiller: 'NEUTRAL_DMG',
    bHateRate: 'AGGRO', bExpRate: 'EXP', bDropRate: 'DROP_RATE',
    bFireShield: 'FIRE_RES', bAquaShield: 'WATER_RES', bWindShield: 'WIND_RES', bEarthShield: 'EARTH_RES',
    bLightShield: 'LIGHT_RES', bDarkShield: 'DARK_RES', bNormalShield: 'NEUTRAL_RES',
    bMotionSpeed: 'MOTIONSPEED', bLongRange: 'LRW', bShortRange: 'SRW',
    bFirstAttack: 'UNSHEATHE', bFirstAttackRate: 'UNSHEATHEP',
    bSurroundingsResist: 'AROUND_RES', bRangeResist: 'AREA_RES', bLineResist: 'LINE_RED',
    bMoveAttackResist: 'CHARGE_RED', bBreathResist: 'BULLET_RES', bWallResist: 'AOE_RES',
    bAbsoluteHitRate: 'ABS_ACC', bAbsoluteFreeRate: 'ABS_DODGE', bAvoidbreaker: 'ANTICIPATE', bGuardbreaker: 'GUARD_BREAK',
    bPhysicalPursuit: 'PHYS_PURSUIT', bMagicPursuit: 'MAG_PURSUIT',
    bPhysicalBarrier: 'PHYS_BARR', bMagicBarrier: 'MAG_BARR', bRateBarrier: 'FRAC_BARR', bBarrierSpeed: 'BARR_SPEED'
};

function readExisting(source) {
    if (source.trimStart().startsWith('[')) source = 'const crystaDataJson = ' + source;
    assert.match(source, /^\s*const crystaDataJson\s*=\s*\[/u);
    const entries = JSON.parse(source.slice(source.indexOf('['), source.lastIndexOf(']') + 1));
    for (const entry of entries) {
        assert.equal(typeof entry.name, 'string');
        assert.equal(typeof entry.category, 'string');
        for (const value of Object.values(entry.stats)) assert.ok(Number.isFinite(value));
    }
    return entries;
}

function existingStats(entry) {
    const values = new Map();
    for (const [key, value] of Object.entries(entry.stats)) {
        const id = registry.normalize(key);
        assert.ok(id, `Unregistered existing stat: ${key}`);
        const group = values.get(id) || [];
        group.push({ key, value });
        values.set(id, group);
    }
    return values;
}

function classifyOptions(options) {
    const numeric = new Map();
    const unresolved = [];
    let conditional = false;
    for (const option of options) {
        if (conditionRanges.some(([start, end]) => option.capId >= start && option.capId <= end)) {
            conditional = true;
            unresolved.push({ ...option, reason: 'equipment-or-event-condition-marker; scope not reconstructed' });
            continue;
        }
        const statId = capStats[option.enumName];
        if (conditional || !statId || option.formattingMode !== 'ordinary-template') {
            unresolved.push({ ...option, proposedStatId: statId || null, reason: conditional ? 'after-condition-marker; scope not reconstructed' : 'special-formatting-or-unmapped-meaning' });
            continue;
        }
        const values = numeric.get(statId) || [];
        values.push(option);
        numeric.set(statId, values);
    }
    return { numeric, unresolved };
}

function compare(entry, item, options) {
    const gameCategory = categories.get(item.master.type_id) || null;
    const app = existingStats(entry);
    const game = classifyOptions(options || []);
    const comparedStats = [];
    const unresolvedExistingStats = [];
    const unrepresentedGameStats = [];
    for (const [statId, values] of app) {
        const caps = game.numeric.get(statId) || [];
        if (values.length !== 1 || caps.length > 1) {
            unresolvedExistingStats.push({ statId, existing: values, reason: 'duplicate stat keys/options; no aggregation assumed' });
        } else if (caps.length === 1) {
            const option = caps[0];
            comparedStats.push({ statId, existingKey: values[0].key, existingValue: values[0].value, gameValue: option.scaledValueFloat32,
                capId: option.capId, enumName: option.enumName, slot: option.slot, rawValue: option.rawValue,
                multiplierFloat32: option.multiplierFloat32, templateKr: option.templateKr,
                result: values[0].value === option.scaledValueFloat32 ? 'equal' : 'value-mismatch' });
        } else {
            unresolvedExistingStats.push({ statId, existing: values, reason: Object.values(capStats).includes(statId)
                ? 'not present among confirmed unconditional game options' : 'no direct reviewed cap mapping' });
        }
    }
    for (const [statId, optionsForStat] of game.numeric) if (!app.has(statId)) {
        unrepresentedGameStats.push({ statId, options: optionsForStat });
    }
    const categoryResult = gameCategory?.category === entry.category ? 'equal' : 'category-mismatch-or-unknown';
    const valuesDiffer = comparedStats.some(stat => stat.result === 'value-mismatch');
    const optionSetDiffers = unrepresentedGameStats.length > 0 || unresolvedExistingStats.some(stat => stat.reason.startsWith('not present'));
    const partial = game.unresolved.length > 0 || unresolvedExistingStats.length > 0 || (entry.condStats || []).length > 0 || !item.propertyRecord || !options;
    return {
        gameItemId: item.gameItemId, nameKr: item.names.kr, typeId: item.master.type_id, typeEnumName: gameCategory?.enumName || null,
        category: { existing: entry.category, game: gameCategory?.category || null, result: categoryResult },
        masterDecodedOffset: item.master.decoded_offset, propertyDecodedOffset: item.propertyRecord?.decoded_offset ?? null,
        identityVerified: false,
        result: categoryResult !== 'equal' ? 'category-conflict' : valuesDiffer ? 'mapped-value-conflict' : optionSetDiffers
            ? 'confirmed-unconditional-option-difference' : partial ? 'partial-consistency-with-unresolved-options' : 'category-and-ordinary-options-agree',
        hasUnresolvedOptions: partial,
        comparedStats, unresolvedExistingStats, unrepresentedGameStats, unresolvedGameOptions: game.unresolved,
        unresolvedExistingConditions: entry.condStats || [],
        upgradePredecessor: entry.prev ? { existingName: entry.prev, gameRelationshipVerified: false } : null
    };
}

function fingerprint(stats) {
    return JSON.stringify([...stats].sort(([a], [b]) => a.localeCompare(b)).map(([id, values]) => [id, values.length === 1 ? values[0] : null]));
}

function makeAudit(existing, items, scaledRows) {
    const optionsById = new Map(scaledRows.map(row => [row.gameItemId, row.options]));
    const names = new Map();
    const normalized = new Map();
    const numericSuffixNames = new Map();
    const statHints = new Map();
    for (const item of items) {
        if (typeof item.names.kr === 'string' && item.names.kr) {
            const group = names.get(item.names.kr) || [];
            group.push(item);
            names.set(item.names.kr, group);
            if (categories.has(item.master.type_id)) {
                const key = normalizeName(item.names.kr);
                normalized.set(key, [...(normalized.get(key) || []), item]);
                const suffixKey = normalizeNumericSuffix(item.names.kr);
                numericSuffixNames.set(suffixKey, [...(numericSuffixNames.get(suffixKey) || []), item]);
            }
        }
        if (categories.has(item.master.type_id)) {
            const options = classifyOptions(optionsById.get(item.gameItemId) || []);
            if (options.unresolved.length === 0 && options.numeric.size >= 3 && [...options.numeric.values()].every(group => group.length === 1)) {
                const key = categories.get(item.master.type_id).category + fingerprint(new Map([...options.numeric].map(([id, values]) => [id, values.map(value => value.scaledValueFloat32)])));
                statHints.set(key, [...(statHints.get(key) || []), item]);
            }
        }
    }
    const results = existing.map((entry, index) => {
        const exact = names.get(entry.name) || [];
        let hints = [];
        let hintMethod = null;
        if (exact.length === 0) {
            hints = normalized.get(normalizeName(entry.name)) || [];
            if (hints.length) hintMethod = 'NFKC-case-and-whitespace-only-name-hint';
            else {
                hints = numericSuffixNames.get(normalizeNumericSuffix(entry.name)) || [];
                if (hints.length) hintMethod = 'Roman-I-to-X-versus-numeric-suffix-name-hint';
            }
            if (!hints.length && !(entry.condStats || []).length) {
                const app = existingStats(entry);
                if (app.size >= 3 && [...app].every(([id, values]) => Object.values(capStats).includes(id) && values.length === 1)) {
                    hints = statHints.get(entry.category + fingerprint(new Map([...app].map(([id, values]) => [id, values.map(value => value.value)])))) || [];
                    if (hints.length) hintMethod = 'category-and-complete-ordinary-stat-fingerprint-hint';
                }
            }
        }
        return { existingIndex: index, existing: entry, exactNameCandidateCount: exact.length,
            identityVerified: false, nameStatus: exact.length === 1 ? 'unique-exact-name-candidate' : exact.length > 1 ? 'ambiguous-exact-name' : 'exact-name-not-found',
            candidates: exact.map(item => compare(entry, item, optionsById.get(item.gameItemId))),
            hintMethod, hints: hints.map(item => compare(entry, item, optionsById.get(item.gameItemId))) };
    });
    const existingNames = new Map();
    for (const [index, entry] of existing.entries()) existingNames.set(entry.name, [...(existingNames.get(entry.name) || []), index]);
    const resultCounts = {};
    for (const row of results) for (const candidate of row.candidates) resultCounts[candidate.result] = (resultCounts[candidate.result] || 0) + 1;
    return {
        counts: { existing: existing.length, exactNameUnique: results.filter(row => row.exactNameCandidateCount === 1).length,
            exactNameAmbiguous: results.filter(row => row.exactNameCandidateCount > 1).length, exactNameMissing: results.filter(row => row.exactNameCandidateCount === 0).length,
            normalizedNameHintEntries: results.filter(row => row.hintMethod?.startsWith('NFKC')).length,
            numericSuffixNameHintEntries: results.filter(row => row.hintMethod?.startsWith('Roman-')).length,
            statFingerprintHintEntries: results.filter(row => row.hintMethod?.startsWith('category-')).length,
            entriesWithoutAnyCandidateOrHint: results.filter(row => !row.candidates.length && !row.hints.length).length,
            verifiedIdentities: 0, exactCandidateComparisons: resultCounts },
        duplicateExistingNames: [...existingNames].filter(([, indices]) => indices.length > 1).map(([name, indices]) => ({ name, indices })),
        duplicateGameCrystaNames: [...names].filter(([, entries]) => entries.length > 1 && entries.some(item => categories.has(item.master.type_id)))
            .map(([name, entries]) => ({ name, items: entries.map(item => ({ gameItemId: item.gameItemId, typeId: item.master.type_id })) })),
        missingGameCrystaNames: items.filter(item => categories.has(item.master.type_id) && !item.names.kr).map(item => ({ gameItemId: item.gameItemId, typeId: item.master.type_id })),
        results
    };
}

function selfTest() {
    const option = (capId, enumName, rawValue, multiplierFloat32 = 1) => ({ capId, enumName, rawValue, multiplierFloat32, scaledValueFloat32: Math.fround(rawValue * multiplierFloat32), formattingMode: 'ordinary-template', slot: capId, templateKr: '{0}' });
    const item = (id, name, type = 34) => ({ gameItemId: id, names: { kr: name }, master: { type_id: type }, propertyRecord: {} });
    const entry = { name: 'G이코노스', category: '추가', stats: { MaxHP: 1000, CHARGE_RED: 1 } };
    const actual = item(9911, entry.name);
    const options = [option(12, 'bMaxHpTo10', 100, 10), option(124, 'bMoveAttackResist', 10)];
    assert.equal(compare(entry, actual, options).result, 'mapped-value-conflict');
    assert.equal(compare(entry, actual, options).comparedStats.find(stat => stat.statId === 'MAXHP').result, 'equal');
    assert.equal(compare({ ...entry, stats: { CHARGE_RED: 10 } }, actual, [options[1]]).result, 'category-and-ordinary-options-agree');
    assert.equal(compare({ ...entry, stats: { CHARGE_RED: 10 } }, actual, [option(96, 'bNinjutsuScrollLimit', 1), options[1]]).comparedStats.length, 0);
    assert.equal(compare({ ...entry, stats: { AVOID_RATE: 2 } }, actual, [option(47, 'bAvoid', 2)]).unrepresentedGameStats[0].statId, 'AVOID_RECHARGE');
    assert.equal(compare(entry, item(9, entry.name, 31), options).result, 'category-conflict');
    const duplicate = makeAudit([entry], [actual, { ...actual, gameItemId: 9 }], []);
    assert.equal(duplicate.counts.exactNameAmbiguous, 1);
    assert.equal(duplicate.counts.verifiedIdentities, 0);
    const normalized = makeAudit([{ name: '제가II', category: '무기', stats: {} }], [item(1, '제가 Ⅱ', 62)], []);
    assert.equal(normalized.counts.exactNameMissing, 1);
    assert.equal(normalized.counts.normalizedNameHintEntries, 1);
    assert.equal(normalized.results[0].hints[0].identityVerified, false);
    const suffix = makeAudit([{ name: '포무찬2', category: '무기', stats: {} }], [item(1, '포무찬 Ⅱ', 62)], []);
    assert.equal(suffix.counts.numericSuffixNameHintEntries, 1);
    assert.equal(suffix.results[0].hints[0].identityVerified, false);
    assert.equal(readExisting('const crystaDataJson = [{"name":"a","category":"추가","stats":{}}];').length, 1);
    console.log('crysta link audit self-test PASS (scaling, conflicts, conditions, category, alias separation, duplicates, name hints)');
}

if (process.argv.includes('--self-test')) {
    selfTest();
} else {
    const files = {
        existing: 'tools/fixtures/crysta-legacy-data.json', registry: 'web/src/calculation/stat-registry.js', labels: 'web/src/application/stat-labels.mjs',
        catalog: 'data/sources/toram-items/items.kr.77596232.json', scaled: 'data/sources/toram-items/item-options.scaled.kr.77596232.json',
        bonusEnum: 'data/sources/toram-items/bonus-types.current.json',
        conditionConstants: 'build/tmp/toram-item-extraction/code-trace/runtime/item-connections/formatter-constants.json'
    };
    const bytes = Object.fromEntries(await Promise.all(Object.entries(files).map(async ([key, path]) => [key, await readFile(new URL(path, root))])));
    const existing = readExisting(bytes.existing.toString('utf8'));
    const catalog = JSON.parse(bytes.catalog);
    const scaled = JSON.parse(bytes.scaled);
    const bonus = JSON.parse(bytes.bonusEnum);
    const conditionConstants = JSON.parse(bytes.conditionConstants);
    assert.deepEqual(conditionConstants.limitList, conditionRanges.flat());
    assert.equal(catalog.cacheVersion, '77596232');
    assert.equal(scaled.evidence.catalogSha256, sha256(bytes.catalog));
    assert.equal(bonus.source.sha256, catalog.bonusEnumSource.sha256);
    const metadata = await readFile(bonus.source.path);
    assert.equal(sha256(metadata), bonus.source.sha256);
    assert.equal(bonus.source.sha256, 'f0cf212a7c7dca1973a401bda6d208549c13f57f0bbdb8782e5d607ed7e8789f', 'Review category evidence for a new metadata build');
    for (const [, , , offset, hex] of categoryRows) assert.equal(metadata.subarray(offset, offset + hex.length / 2).toString('hex'), hex);
    const bonusById = new Map(bonus.values.map(value => [value.id, value.name]));
    for (const [enumName, statId] of Object.entries(capStats)) {
        assert.ok(bonus.values.some(value => value.name === enumName), `Missing cap enum ${enumName}`);
        assert.equal(registry.normalize(statId), statId);
    }
    const catalogById = new Map(catalog.items.map(item => [item.gameItemId, item]));
    assert.equal(catalogById.size, catalog.items.length);
    assert.equal(new Set(scaled.items.map(item => item.gameItemId)).size, scaled.items.length);
    for (const row of scaled.items) {
        const raw = catalogById.get(row.gameItemId)?.propertyRecord;
        assert.ok(raw, `No raw properties for ${row.gameItemId}`);
        for (const option of row.options) {
            const cap = raw.caps.find(cap => cap.slot === option.slot);
            assert.equal(bonusById.get(option.capId), option.enumName);
            assert.equal(cap.cap_id, option.capId);
            assert.equal(cap.value, option.rawValue);
            assert.equal(Math.fround(Math.fround(option.rawValue) * option.multiplierFloat32), option.scaledValueFloat32);
        }
    }
    const audit = makeAudit(existing, catalog.items, scaled.items);
    const report = {
        schemaVersion: 1, authority: 'local name/category/ordinary-displayed-number audit; no app data changes', cacheVersion: catalog.cacheVersion,
        sources: Object.fromEntries(Object.entries(files).map(([key, path]) => [key, { path, sha256: sha256(bytes[key]) }])),
        categoryEvidence: { metadataSha256: bonus.source.sha256, enumName: 'ItemType', typeDefinitionIndex: 2000, typeDefinitionOffset: 24706308,
            source: 'saved metadata; reviewed default bytes use IL2CPP compressed Int32 encoding',
            rows: categoryRows.map(([id, enumName, category, metadataDefaultOffset, encodedHex]) => ({ id, enumName, category, metadataDefaultOffset, encodedHex })) },
        conditionMarkerEvidence: { ranges: conditionRanges, source: files.conditionConstants, sha256: sha256(bytes.conditionConstants) },
        statMapping: Object.entries(capStats).map(([enumName, statId]) => ({ capId: bonus.values.find(value => value.name === enumName).id, enumName, statId, registryUnit: registry.get(statId).unit })),
        rules: [
            'Every result remains an unverified identity candidate, including category/ordinary-option agreement. No joins are written into application data.',
            'Exact names are compared without normalization. NFKC/case/whitespace, Roman-I-to-X versus numeric suffixes and complete ordinary-stat fingerprints only generate separate hints.',
            'Fingerprint hints require at least three mapped ordinary stats, matching category, no conditional/special options and no duplicate stat keys.',
            'Cap values use the native-derived float32 display-number sidecar. These are not final combat values or rendered UI strings.',
            'Only native limitList ranges 96..103, 108..109 and 115..120 are equipment condition markers. After the first marker all later slots conservatively remain unresolved here; condition span/target reconciliation is separate.',
            'Special-format branches and absent mappings (including respawn, reflection, item delay and stat-conversion caps) remain unresolved.',
            'AVOID_RATE and AVOID_RECHARGE are distinct registry keys and UI labels. bAvoid/Avoid 회복 maps only to AVOID_RECHARGE.',
            'Duplicate mapped stats are not summed. Existing predecessor names are preserved without claiming a game upgrade relationship.',
            'No numeric tolerance or implicit unit/alias conversion is applied beyond the existing registry normalization and reviewed display multiplier.'
        ],
        ...audit
    };
    const output = new URL('data/sources/toram-items/crysta-link-audit.json', root);
    await writeFile(output, `${JSON.stringify(report, null, 2)}\n`);
    console.log(JSON.stringify({ output: fileURLToPath(output), ...audit.counts }));
}
