// Optional real-browser gate; use an existing Playwright installation.
import assert from 'node:assert/strict';
import { createServer } from 'node:http';
import { readFile, writeFile } from 'node:fs/promises';
import { createRequire } from 'node:module';
import { extname, resolve, sep } from 'node:path';
import { createWebDevServer } from '../web-dev.mjs';
import { loadHeadlessEnvironment } from '../support/crysta-headless-environment.mjs';

const require = createRequire(import.meta.url);
if (!process.env.CODEX_PLAYWRIGHT_PATH) throw new Error('Set CODEX_PLAYWRIGHT_PATH to the installed playwright module.');
const { chromium } = require(process.env.CODEX_PLAYWRIGHT_PATH);
const root = resolve(import.meta.dirname, '../../build/web');
const mime = { '.html':'text/html', '.js':'text/javascript', '.mjs':'text/javascript', '.css':'text/css', '.svg':'image/svg+xml', '.woff2':'font/woff2', '.png':'image/png', '.wasm':'application/wasm' };
const built = createServer(async (req, res) => {
  res.setHeader('Cross-Origin-Opener-Policy', 'same-origin');
  res.setHeader('Cross-Origin-Embedder-Policy', 'require-corp');
  try {
    const pathname = decodeURIComponent(new URL(req.url, 'http://localhost').pathname);
    if (!pathname.startsWith('/calculator/')) throw new Error('path');
    const path = resolve(root, pathname.slice('/calculator/'.length) || 'index.html');
    if (!path.startsWith(root + sep)) throw new Error('path');
    res.setHeader('Content-Type', mime[extname(path)] || 'application/octet-stream');
    res.end(await readFile(path));
  } catch { res.writeHead(404); res.end(); }
});
const dev = createWebDevServer();
const fixture = JSON.parse(await readFile(new URL('../fixtures/crysta-native-runtime-26min-revenir.json', import.meta.url), 'utf8'));
const environment = await loadHeadlessEnvironment();
const benchmarkProblem = environment.compile(fixture.resolvedExecutionContext);
const timings = [];
let browser;
try {
  for (const server of [dev, built]) await new Promise(resolve => server.listen(0, '127.0.0.1', resolve));
  browser = await chromium.launch({ channel:'chrome', headless:true });
  for (const [server, path] of [[dev, '/'], [built, '/calculator/']]) {
    const page = await browser.newPage({ viewport:{ width:1280, height:900 } });
    const errors = [], workers = [], bossRequests = [];
    page.on('request', request => { if (request.url().includes('/assets/game-data/bosses/')) bossRequests.push(request.url()); });
    page.on('pageerror', error => errors.push(error.message));
    page.on('response', response => {
      if (response.status() >= 400 && new URL(response.url()).pathname.includes('/assets/')) errors.push(`${response.status()} ${response.url()}`);
    });
    page.on('worker', worker => workers.push(worker.url()));
    await page.goto(`http://127.0.0.1:${server.address().port}${path}?view=calculator`);
    await page.waitForFunction(() => window.ToramUiFeatures?.settings);
    assert.equal(bossRequests.length, 0, 'Boss data must remain lazy at startup.');
    const targetBefore = await page.evaluate(() => ['bossLevel','bossDef','bossMdef','bossCritResist','bossPhysResist','bossMagResist'].map(id => document.getElementById(id).value));
    const bossSearch = await page.evaluate(() => window.ToramApp.bosses.search('기드론','kr'));
    assert.equal(bossSearch.at(0).gameMonsterId, 540);
    assert.equal(bossRequests.length, 3);
    const grimuckus = await page.evaluate(() => window.ToramApp.bosses.get(540,'kr'));
    assert.ok(grimuckus.variants.some(row => row.key === '23000:10' && Number.isFinite(row.baseStats.def)));
    assert.equal(grimuckus.variants.find(row => row.key === '23000:10').classification,'field-boss');
    assert.deepEqual(grimuckus.variants.find(row => row.key === '23000:10').entry,{model:'single',difficulty:null});
    assert.equal(bossRequests.length, 4);
    await page.evaluate(() => window.ToramApp.bosses.get(540,'kr'));
    assert.equal(bossRequests.length, 4);
    for (const [id,name] of [[1001,'Altadar'],[1187,'Merzehal'],[974,'Falburrows'],[888,'Trickster Dragon Mimyugon']]) {
      const boss = await page.evaluate(id => window.ToramApp.bosses.get(id,'us'), id);
      assert.equal(boss.name, name); assert.ok(boss.variants.length);
      assert.equal(new Set(boss.variants.map(row => row.key)).size,boss.variants.length);
      assert.ok(boss.variants.some(row => row.classification === ([1001,1187].includes(id) ? 'high-raid-boss' : 'entry-boss')));
      assert.ok(boss.variants.some(row => row.entry.model === ([1001,1187].includes(id) ? 'level-select' : 'difficulty-select')));
    }
    assert.deepEqual(await page.evaluate(() => ['bossLevel','bossDef','bossMdef','bossCritResist','bossPhysResist','bossMagResist'].map(id => document.getElementById(id).value)),targetBefore);
    async function chooseBoss(query, id, key) {
      await page.locator('#bossSearch').fill(query);
      await page.waitForFunction(id => [...document.querySelector('#bossSearchResults').options].some(option => option.value === id), String(id));
      await page.locator('#bossSearchResults').selectOption(String(id));
      await page.waitForFunction(id => window.ToramApp.bossTarget.getSelection()?.gameMonsterId === id, id);
      await page.locator('#bossVariant').selectOption(key);
    }
    await chooseBoss('블랑',1314,'107602:1000');
    assert.equal(await page.locator('#bossDifficultyField').isVisible(),false);
    assert.equal(await page.locator('#bossLevel').inputValue(),'320');
    assert.equal(await page.locator('#bossDef').inputValue(),'1280');
    assert.equal(await page.locator('#bossMdef').inputValue(),'1280');
    assert.equal(await page.locator('#bossPhysResist').inputValue(),'12');
    assert.equal(await page.locator('#bossMagResist').inputValue(),'12');
    await chooseBoss('콜론 보스',41,'3300:10');
    assert.equal(await page.locator('#bossDifficultyField').isVisible(),true);
    await page.locator('#bossDifficulty').selectOption('0');
    assert.equal(await page.locator('#bossLevel').inputValue(),'10');
    assert.equal(await page.locator('#bossDef').inputValue(),'7');
    await page.locator('#bossDifficulty').selectOption('3');
    assert.equal(await page.locator('#bossDef').inputValue(),'42');
    await chooseBoss('기드론',540,'23000:10');
    assert.equal(await page.locator('#bossDifficultyField').isVisible(),false);
    assert.equal(await page.locator('#bossEntryLevelField').isVisible(),false);
    assert.deepEqual(await page.evaluate(() => window.ToramBuildDraftStore.read().scenario.target),{bossLevel:195,bossDef:429,bossMdef:390,bossCritResist:0,bossPhysResist:7,bossMagResist:7,targetElement:2});
    assert.match(await page.locator('#bossProration').textContent(),/통상 20%p · 물리 30%p · 마법 30%p/u);
    await chooseBoss('미뮤',888,'32700:1');
    assert.equal(await page.locator('#bossDifficultyField').isVisible(),true);
    assert.equal(await page.locator('#bossDef').inputValue(),'2620');
    assert.equal(await page.locator('#bossCritResist').inputValue(),'35');
    await page.locator('#bossDifficulty').selectOption('2');
    assert.equal(await page.locator('#bossLevel').inputValue(),'258');
    assert.equal(await page.locator('#bossDef').inputValue(),'10480');
    assert.equal(await page.locator('#bossPhysResist').inputValue(),'9');
    await chooseBoss('알타달',1001,'101100:1');
    assert.equal(await page.locator('#bossDifficultyField').isVisible(),false);
    assert.equal(await page.locator('#bossEntryLevelField').isVisible(),true);
    assert.equal(await page.locator('#bossDef').inputValue(),'1740');
    assert.equal(await page.locator('#bossPhysResist').inputValue(),'25');
    await page.locator('#bossEntryLevel').fill('300');
    await page.locator('#bossEntryLevel').dispatchEvent('change');
    assert.equal(await page.locator('#bossDef').inputValue(),'1800');
    assert.equal(await page.locator('#bossCritResist').inputValue(),'60');
    for (const [query,id,key,expected] of [
      ['셀디테',916,'100100:1',[125,125,30,20,10]],
      ['바이슨',741,'100200:1',[150,75,35,10,0]],
      ['구름전차',802,'100300:1',[100,25,25,25,0]],
      ['키마이라',830,'100400:1',[200,100,20,30,25]],
      ['용골의 마인',742,'100600:1',[75,150,10,35,0]],
      ['소테리아',1195,'100500:1',[175,350,25,40,10]]
    ]) {
      await chooseBoss(query,id,key);
      assert.equal(await page.locator('#bossDifficultyField').isVisible(),false);
      assert.equal(await page.locator('#bossEntryLevelLabel').textContent(),'현재 보스 레벨');
      await page.locator('#bossEntryLevel').fill('100'); await page.locator('#bossEntryLevel').dispatchEvent('change');
      assert.deepEqual(await page.evaluate(() => ['bossDef','bossMdef','bossPhysResist','bossMagResist','bossCritResist'].map(id=>Number(document.getElementById(id).value))),expected);
      assert.match(await page.locator('#bossTargetStatus').textContent(),/서버 랜덤 옵션/u);
    }
    assert.match(await page.locator('#bossVariant option:checked').textContent(),/남자 소테리아/u);
    await page.locator('#bossEntryLevel').fill('41'); await page.locator('#bossEntryLevel').dispatchEvent('change');
    assert.equal(await page.locator('#bossEntryLevel').inputValue(),'100','Invalid guild gauge levels preserve the previous selection.');
    await page.locator('#bossEntryLevel').fill('200'); await page.locator('#bossEntryLevel').dispatchEvent('change');
    await page.locator('#bossVariant').selectOption('100500:2');
    assert.equal(await page.locator('#bossEntryLevel').inputValue(),'200','Both actors share the selected guild combat level.');
    assert.match(await page.locator('#bossVariant option:checked').textContent(),/여자 소테리아/u);
    assert.equal(await page.locator('#bossDef').inputValue(),'600'); assert.equal(await page.locator('#bossMdef').inputValue(),'250');
    await page.locator('#bossVariant').selectOption('100500:102');
    assert.equal(await page.locator('#bossDef').inputValue(),'600');
    await page.locator('#bossDef').fill('777');
    const guildRequests = bossRequests.length;
    await page.evaluate(() => window.ToramSettingsRepository.importSavedBuild(window.ToramSettingsRepository.serializeSavedBuild('guild-test')));
    assert.equal(bossRequests.length,guildRequests,'A pinned guild selection must restore without fresh catalog requests.');
    assert.equal(await page.locator('#bossDef').inputValue(),'777');
    assert.equal(await page.locator('#bossEntryLevel').inputValue(),'200');
    assert.match(await page.locator('#bossTargetStatus').textContent(),/여자 소테리아/u);
    await page.screenshot({path:resolve(import.meta.dirname,'../../build/tmp/guild-raid-target.png'),fullPage:true});
    await chooseBoss('메르제하르',1187,'90965:1');
    assert.equal(await page.locator('#bossDef').inputValue(),'1950');
    assert.equal(await page.locator('#bossMagResist').inputValue(),'27');
    assert.equal(await page.locator('#bossCritResist').inputValue(),'70');
    const bossContext = await page.evaluate(() => { const context = window.ToramApplication.CreateCalculationSnapshot().baseContext; return ['bossLevel','bossDef','bossMdef','bossPhysResist','bossMagResist','bossCritResist'].map(key => context[key]); });
    assert.deepEqual(bossContext,[325,1950,1950,27,27,70],'Selected target scalars must reach the existing calculation kernel.');
    await page.locator('#bossDef').fill('2222');
    assert.match(await page.locator('#bossTargetStatus').textContent(),/수동 수정/u);
    await page.screenshot({path:resolve(import.meta.dirname,'../../build/tmp/target-desktop.png'),fullPage:true});
    await page.setViewportSize({width:390,height:844});
    assert.ok(await page.evaluate(() => document.documentElement.scrollWidth <= window.innerWidth),'Target controls must fit a narrow viewport.');
    await page.screenshot({path:resolve(import.meta.dirname,'../../build/tmp/target-mobile.png'),fullPage:true});
    await page.setViewportSize({width:1280,height:900});
    const itemRequests = [];
    page.on('request', request => { if (request.url().includes('/assets/game-data/items/')) itemRequests.push(request.url()); });
    const gameItem = await page.evaluate(() => window.ToramApp.items.getItem(9911, 'kr'));
    assert.equal(gameItem.name, 'G이코노스');
    assert.equal(gameItem.stats.MAXHP, 1000);
    assert.equal(gameItem.stats.CHARGE_RED, 10);
    assert.equal(itemRequests.length, 2, 'Startup already caches the joined crysta shard and manifest.');
    assert.ok(itemRequests.every(url => !url.includes('.details.') && !url.includes('/us/')));
    await page.evaluate(() => window.ToramApp.items.getItem(9911, 'kr'));
    assert.equal(itemRequests.length, 2);
    const blancCrysta = await page.evaluate(() => window.ToramApp.items.getItem(80453, 'kr'));
    assert.equal(blancCrysta.name,'블랑');
    assert.equal(blancCrysta.fullyMapped,true);
    assert.deepEqual(blancCrysta.stats,{SRW:10,STABILITY:5,AVOID_RECHARGE:5,LRW:-15});
    await page.locator('#appTabButton-equipment').click();
    await page.locator('#armorType').selectOption('일반옷');
    await page.locator('#cr_arm_1').fill('댄드라이언');
    await page.locator('#cr_arm_1').dispatchEvent('change');
    assert.equal(await page.evaluate(() => window.ToramApp.crystas.getById(9776) === getCrystaByName('Dandolion')),true);
    assert.match(await page.locator('#cr_arm_1_info').textContent(),/최대MP \+500/u);
    assert.doesNotMatch(await page.locator('#cr_arm_1_info').textContent(),/안정률/u);
    await page.locator('#armorType').selectOption('경량옷');
    assert.match(await page.locator('#cr_arm_1_info').textContent(),/안정률% \+6/u);
    await page.locator('#gameItemEquipment summary').click();
    await page.locator('[data-add-option="spcOpts"]').click();
    await page.locator('#spcOpts .opt-type').selectOption('ATK');
    await page.locator('#spcOpts .opt-val').fill('7');
    await page.locator('#gameItemTarget').selectOption('special');
    await page.waitForFunction(() => document.querySelector('#gameItemResults').options.length > 0);
    await page.locator('#gameItemSearch').fill('22001');
    await page.locator('#gameItemResults').selectOption('22001');
    await page.waitForFunction(() => !document.querySelector('#gameItemApply').disabled);
    const beforeGameMp = await page.evaluate(() => window.ToramApplication.CreateCalculationSnapshot().baseContext.maxMpF);
    await page.locator('#gameItemApply').click();
    await page.waitForFunction(() => window.ToramBuildDraftStore.read().build.equipment.special.catalogItem?.gameItemId === 22001);
    assert.equal(await page.evaluate(() => window.ToramApplication.CreateCalculationSnapshot().baseContext.maxMpF), beforeGameMp + 200);
    assert.deepEqual(await page.evaluate(() => window.ToramBuildDraftStore.read().build.equipment.special.options), [{key:'ATK',value:7}]);
    assert.match(await page.locator('[data-game-equipment="special"]').textContent(), /MAXMP \+200/u);
    // Applying another locale keeps the game ID; no name-based legacy crysta migration occurs.
    await page.locator('#gameItemLocale').selectOption('us');
    await page.waitForFunction(() => document.querySelector('#gameItemResults').options.length > 0);
    await page.locator('#gameItemResults').selectOption('22001');
    await page.waitForFunction(() => !document.querySelector('#gameItemApply').disabled);
    await page.locator('#gameItemApply').click();
    await page.waitForFunction(() => window.ToramBuildDraftStore.read().build.equipment.special.catalogItem?.name === 'Talisman');
    await page.locator('#subWeaponType').selectOption('방패');
    await page.locator('#subAtk').fill('37'); await page.locator('#subStab').fill('11');
    await page.locator('#subRefine').selectOption('11');
    await page.locator('[data-add-option="subOpts"]').click();
    await page.locator('#subOpts .opt-type').selectOption('ATK'); await page.locator('#subOpts .opt-val').fill('3');
    await page.locator('#gameItemTarget').selectOption('subWeapon');
    await page.locator('#gameItemLocale').selectOption('kr');
    await page.locator('#gameItemSearch').fill('17002');
    await page.waitForFunction(() => document.querySelector('#gameItemResults').options.length > 0);
    await page.locator('#gameItemResults').selectOption('17002');
    await page.waitForFunction(() => !document.querySelector('#gameItemApply').disabled);
    const beforeShieldHp = await page.evaluate(() => window.ToramApplication.CreateCalculationSnapshot().baseContext.maxHpF);
    await page.locator('#gameItemApply').click();
    await page.waitForFunction(() => window.ToramBuildDraftStore.read().build.equipment.subWeapon.catalogItem?.gameItemId === 17002);
    assert.equal(await page.evaluate(() => window.ToramApplication.CreateCalculationSnapshot().baseContext.maxHpF), beforeShieldHp + 30);
    assert.equal(await page.locator('#subAtk').inputValue(), '37'); assert.equal(await page.locator('#subStab').inputValue(), '11');
    assert.equal(await page.locator('#subRefine').inputValue(), '11');
    assert.deepEqual(await page.evaluate(() => window.ToramBuildDraftStore.read().build.equipment.subWeapon.options), [{key:'ATK',value:3}]);

    await page.locator('#appTabButton-buffs').click();
    await page.locator('#gameConsumableBuffs summary').click();
    await page.locator('[data-add-option="buffOpts"]').click();
    await page.locator('#buffOpts .opt-type').selectOption('ATK'); await page.locator('#buffOpts .opt-val').fill('7');
    await page.locator('#gameConsumableLoad').click();
    await page.waitForFunction(() => document.querySelector('#gameConsumableResults').options.length > 0);
    const beforeVitaHp = await page.evaluate(() => window.ToramApplication.CreateCalculationSnapshot().baseContext.maxHpF);
    for (const id of ['2000','2001','2537']) {
      await page.locator('#gameConsumableSearch').fill(id);
      await page.locator('#gameConsumableResults').selectOption(id);
      await page.waitForFunction(() => !document.querySelector('#gameConsumableApply').disabled);
      await page.locator('#gameConsumableApply').click();
      await page.waitForFunction(id => window.ToramBuildDraftStore.read().build.consumableBuffs.some(item => item.gameItemId === id), Number(id));
      if (id === '2000') assert.equal(await page.evaluate(() => window.ToramApplication.CreateCalculationSnapshot().baseContext.maxHpF), beforeVitaHp + 500);
      if (id === '2001') assert.equal(await page.evaluate(() => window.ToramBuildDraftStore.read().build.consumableBuffs.length), 1, 'Same-group buff replaces its predecessor.');
    }
    assert.deepEqual(await page.evaluate(() => window.ToramBuildDraftStore.read().build.externalOptions), [{key:'ATK',value:7}]);
    await page.locator('#appTabButton-stats-target').click();
    assert.equal(await page.locator('html').getAttribute('data-runtime'), 'web');
    assert.equal(await page.locator('.update-toolbar').isVisible(), false);
    assert.equal(await page.evaluate(() => typeof window.ToramCrystaOptimizationNativeClient), 'undefined');
    assert.equal(await page.evaluate(() => typeof window.ToramUpdateService), 'undefined');
    assert.equal(await page.evaluate(() => window.ToramCrystaOptimizationExecutionAdapter.isAvailable()), true);

    await page.locator('#charLevel').fill('321');
    await page.locator('#appBuildStorageButton').click();
    assert.equal(await page.locator('#buildNativeFileFunctions').isVisible(), false);
    assert.equal(await page.locator('#buildBackupName').evaluate(el => el === document.activeElement), true);
    const downloaded = page.waitForEvent('download');
    await page.locator('#buildSettingExport').click();
    const download = await downloaded;
    const document = JSON.parse(await readFile(await download.path(), 'utf8'));
    assert.equal(document.schemaVersion, 2);
    assert.equal(document.scenario.bossSelection.gameMonsterId,1187);
    assert.equal(document.scenario.bossSelection.variant.key,'90965:1');
    assert.equal(document.scenario.target.bossDef,2222,'Manual target overrides must survive export.');
    assert.equal(document.build.character.level, 321);
    assert.equal(document.build.equipment.armor.crystas[0],'댄드라이언');
    assert.equal(document.build.equipment.special.catalogItem.gameItemId, 22001);
    assert.equal(document.build.equipment.special.catalogItem.stats.MAXMP, 200);
    assert.deepEqual(document.build.equipment.special.options, [{key:'ATK',value:7}]);
    assert.equal(document.build.equipment.subWeapon.catalogItem.gameItemId, 17002);
    assert.deepEqual(document.build.equipment.subWeapon.options, [{key:'ATK',value:3}]);
    assert.deepEqual(document.build.consumableBuffs.map(item => item.gameItemId), [2001,2537]);
    assert.deepEqual(document.build.externalOptions, [{key:'ATK',value:7}]);
    document.build.character.level = 222;
    document.scenario.optimizationPreferences = { requirements:{ maxHp:null, maxMp:null, amprBeforeDual:null, normalAttackCrit:null, aspd:null } };
    await page.locator('#buildSettingImport').setInputFiles({
      name:'web-build.json', mimeType:'application/json', buffer:Buffer.from(JSON.stringify(document))
    });
    await page.waitForFunction(() => document.querySelector('#charLevel').value === '222');
    await page.reload();
    await page.waitForFunction(() => window.ToramUiFeatures?.settings);
    assert.equal(await page.locator('#charLevel').inputValue(), '222');
    assert.equal(await page.locator('#cr_arm_1').inputValue(),'댄드라이언');
    console.log(`Joined data browser: PASS (${path}, Dandelion ID/options/light-armor/JSON/reload, Colon Boss entry/difficulty)`);
    assert.equal(await page.locator('#bossDef').inputValue(),'2222');
    assert.equal(await page.evaluate(() => window.ToramApp.bossTarget.getSelection().gameMonsterId),1187);
    assert.match(await page.locator('#bossTargetStatus').textContent(),/메르제하르/u);
    await page.locator('#bossTargetClear').click();
    assert.equal(await page.locator('#bossDef').inputValue(),'2222');
    assert.equal(await page.evaluate(() => window.ToramBuildDraftStore.read().scenario.bossSelection),undefined,'Clearing the catalog link preserves manual numbers.');
    assert.equal(await page.evaluate(() => window.ToramBuildDraftStore.read().build.equipment.special.catalogItem.gameItemId), 22001);
    assert.match(await page.locator('[data-game-equipment="special"]').textContent(), /Talisman/u);
    assert.deepEqual(await page.evaluate(() => window.ToramBuildDraftStore.read().build.equipment.special.options), [{key:'ATK',value:7}]);
    assert.equal(await page.evaluate(() => window.ToramBuildDraftStore.read().build.equipment.subWeapon.catalogItem.gameItemId), 17002);
    assert.deepEqual(await page.evaluate(() => window.ToramBuildDraftStore.read().build.consumableBuffs.map(item => item.gameItemId)), [2001,2537]);
    await page.locator('#appTabButton-buffs').click();
    const speedBefore = await page.evaluate(() => window.ToramApplication.CreateCalculationSnapshot().baseContext.aspdF);
    if (await page.locator('#gameConsumableBuffs').getAttribute('open') === null) await page.locator('#gameConsumableBuffs summary').click();
    await page.locator('[data-consumable-id="2537"] button').click();
    assert.equal(await page.evaluate(() => window.ToramBuildDraftStore.read().build.consumableBuffs.length), 1);
    assert.equal(await page.evaluate(() => window.ToramApplication.CreateCalculationSnapshot().baseContext.aspdF), speedBefore - 1000);
    assert.deepEqual(await page.evaluate(() => window.ToramBuildDraftStore.read().build.externalOptions), [{key:'ATK',value:7}]);
    await page.locator('#appTabButton-equipment').click();
    await page.locator('[data-game-equipment="special"] button').click();
    assert.equal(await page.evaluate(() => window.ToramBuildDraftStore.read().build.equipment.special.catalogItem), undefined);
    assert.deepEqual(await page.evaluate(() => window.ToramBuildDraftStore.read().build.equipment.special.options), [{key:'ATK',value:7}]);
    assert.equal(await page.evaluate(() => window.ToramApplication.CreateCalculationSnapshot().baseContext.maxMpF), beforeGameMp);

    // Keep one real catalog slot open so this UI/Worker lifecycle gate has a bounded input size.
    for (const id of ['lock_wpn_1','lock_wpn_2','lock_arm_1','lock_arm_2','lock_add_1','lock_add_2','lock_spc_1']) await page.locator('#'+id).check();
    await page.locator('#appTabButton-results').click();
    await page.waitForFunction(() => window.ToramRuntimeState.get().crystaOptimization.lastOptimizationResult);
    assert.equal(await page.evaluate(() => window.ToramRuntimeState.get().crystaOptimization.lastOptimizationResult.engine), 'rust-wasm');
    assert.ok(workers.some(url => url.endsWith(path + 'assets/js/optimization/wasm-worker.js')));
    assert.equal(await page.evaluate(() => typeof window.ToramCrystaOptimizationGlobalOptimizer), 'undefined');
    const previewWorkers = workers.filter(url => url.endsWith('/optimization/wasm-worker.js')).length;
    const previewScore = await page.evaluate(() => window.ToramRuntimeState.get().crystaOptimization.lastOptimizationResult.score);
    await page.locator('#optimizationRunPreciseOptimization').click();
    try {
      await page.waitForFunction(() => window.ToramRuntimeState.get().crystaOptimization.lastOptimizationResult?.status === 'exact');
    } catch (error) {
      const result = await page.evaluate(() => {
        const value = window.ToramRuntimeState.get().crystaOptimization.lastOptimizationResult;
        return value && { status:value.status, score:value.score, elapsedMs:value.elapsedMs, visitedNodes:value.visitedNodes, diagnostics:value.diagnostics };
      });
      throw new Error(`${error.message}; ${path}: ${JSON.stringify({ result, errors })}`);
    }
    assert.equal(workers.filter(url => url.endsWith('/optimization/wasm-worker.js')).length, previewWorkers, 'UI precision must keep the preview Worker');
    assert.ok(await page.evaluate(score => window.ToramRuntimeState.get().crystaOptimization.lastOptimizationResult.score >= score, previewScore));
    const result = await page.evaluate(async () => {
      const baseContext = window.ToramApplication.CreateCalculationSnapshot().baseContext;
      const scenarioSnapshot = window.ToramBuildEvaluator.createScenarioSnapshot(baseContext, {
        requirements:{ maxHp:null, maxMp:null, amprBeforeDual:null, normalAttackCrit:null, aspd:null }
      });
      const problem = {
        schema:'toram.crysta-problem.v1', baseContext,
        scenarioSnapshot, metadata:{},
        groups:['weapon', 'armor', 'additional', 'special'].map(id => ({ id, packages:[
          { id:id + '-1', slot:id, statDelta:{ ATKP:1 }, candidateNames:[], evaluatorCandidates:[] },
          { id:id + '-2', slot:id, statDelta:{ ATKP:2 }, candidateNames:[], evaluatorCandidates:[] }
        ] }))
      };
      const adapter = window.ToramCrystaOptimizationExecutionAdapter;
      const pending = adapter.execute(problem, {}, { timeLimitMs:1000 });
      if (!adapter.cancel('browser test')) throw new Error('WASM cancel unavailable');
      if ((await pending).status !== 'cancelled') throw new Error('WASM cancel did not settle');
      return adapter.execute(problem, {}, { timeLimitMs:1000 });
    });
    assert.equal(result.status, 'exact', JSON.stringify(result.diagnostics));
    assert.equal(result.engine, 'rust-wasm');
    assert.ok(result.bestBuild);
    assert.ok(Number.isFinite(result.score));
    assert.deepEqual(errors, []);
    console.log(`Web browser: PASS (${path}, loading, calculation, JSON export/import, reload, real Worker exact/cancel, desktop controls excluded)`);
    if (server === built) {
      const resumed = await page.evaluate(async problem => {
        const adapter = window.ToramCrystaOptimizationExecutionAdapter;
        await adapter.disposeContinuation();
        const pending = adapter.execute(problem, {}, { timeLimitMs:10000 });
        if (!adapter.pause()) throw new Error('WASM pause unavailable');
        const paused = await pending;
        if (paused.status !== 'paused' || !adapter.hasContinuation()) throw new Error('WASM did not preserve its paused frontier');
        return adapter.resume({}, { timeLimitMs:10000 });
      }, benchmarkProblem);
      assert.equal(resumed.status, 'exact');
      for (let repeat = 0; repeat < 3; repeat++) {
        const measurement = await page.evaluate(async problem => {
          const adapter = window.ToramCrystaOptimizationExecutionAdapter;
          await adapter.disposeContinuation();
          const started = performance.now();
          const preview = await adapter.preview(problem);
          const previewMs = performance.now() - started;
          const preciseStarted = performance.now();
          const result = await adapter.execute(problem, {}, { timeLimitMs:10000 });
          return { previewMs, preciseMs:performance.now() - preciseStarted, totalMs:performance.now() - started,
            initialScore:preview.score, score:result.score, status:result.status, id:result.bestBuild && result.bestBuild.id,
            feasible:result.outcomes && result.outcomes.constraints.feasible,
            reevaluated:result.outcomes && result.outcomes.damage.expected };
        }, benchmarkProblem);
        assert.equal(measurement.status, 'exact');
        assert.equal(measurement.feasible, true);
        assert.equal(measurement.score, measurement.reevaluated);
        if (timings.length) {
          assert.equal(measurement.score, timings[0].score);
          assert.equal(measurement.id, timings[0].id);
        }
        timings.push(measurement);
      }
    }
    await page.close();
  }
  await writeFile(new URL('../../desktop/target/rust-wasm-browser-measurements.json', import.meta.url), JSON.stringify({
    browser:await browser.version(), fixture:'crysta-native-runtime-26min-revenir.json',
    note:'Three fresh Worker runs in one isolated Chrome context; includes WASM loading, preparation and final JS evaluation; excludes UI rendering and initial problem compilation.',
    timings
  }, null, 2) + '\n');
  console.log('WASM browser fixture: PASS ' + JSON.stringify(timings));
} finally {
  if (browser) await browser.close();
  for (const server of [dev, built]) if (server.listening) await new Promise(resolve => server.close(resolve));
}
