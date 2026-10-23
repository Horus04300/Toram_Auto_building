import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { createRequire } from 'node:module';
import { createWebDevServer } from '../web-dev.mjs';

const require = createRequire(import.meta.url);
if (!process.env.CODEX_PLAYWRIGHT_PATH) throw new Error('Set CODEX_PLAYWRIGHT_PATH to the installed playwright module.');
const { chromium } = require(process.env.CODEX_PLAYWRIGHT_PATH);
const sample = JSON.parse(await readFile(new URL('../../samples/마법) 지팡이 크법 세팅 - pelio s.json', import.meta.url), 'utf8'));
sample.build.equipment.mainWeapon.refinement = 11;
Object.assign(sample.build.equipment.subWeapon, { attack:89, refinement:0, stability:34 });
sample.build.equipment.armor.type = '중량옷';
sample.build.equipment.mainWeapon.lockedCrystaSlots = [true, false];
sample.build.equipment.special.lockedCrystaSlots = [false, true];
sample.build.guildFoodBuff = false;
sample.scenario.optimizationPreferences = {
  rangeOverride:'LONG', requirements:{ maxHp:2345, maxMp:null, amprBeforeDual:21, normalAttackCrit:null, aspd:6789 },
  bannedCrystas:['오로로 콜론', '왕자 메기스톤']
};
const server = createWebDevServer();
let browser;
try {
  await new Promise(resolve => server.listen(0, '127.0.0.1', resolve));
  browser = await chromium.launch({ channel:'msedge', headless:true });
  const context = await browser.newContext();
  const errors = [];
  async function open() {
    const page = await context.newPage();
    page.on('pageerror', error => errors.push(error.message));
    await page.goto(`http://127.0.0.1:${server.address().port}/`);
    await page.waitForFunction(() => window.ToramUiFeatures?.settings);
    return page;
  }
  async function capture(page) {
    return page.evaluate(() => {
      const { build, scenario } = window.ToramBuildDraftStore.syncFromUi();
      return { build, scenario };
    });
  }
  async function saved(page, expected) {
    await page.waitForFunction(expected => {
      const session = JSON.parse(localStorage.getItem(window.ToramSettingsRepository.sessionStorageKey) || 'null')?.lastSession;
      return session && JSON.stringify({ build:session.build, scenario:session.scenario }) === JSON.stringify(expected);
    }, expected);
  }
  let page = await open();
  assert.equal(await page.locator('#wpnOpts .opt-row').count(), 0, 'A fresh build must start without default weapon options');
  assert.equal(await page.locator('#armOpts .opt-row').count(), 0, 'A fresh build must start without default armor options');
  await page.evaluate(sample => window.ToramApplication.Settings.import(JSON.stringify(sample)), sample);
  // Real input events must save without an explicit flush or a reload helper.
  await page.locator('#bossDef').fill('789');
  const expected = await capture(page);
  assert.equal(expected.build.equipment.subWeapon.type, '방패');
  assert.equal(expected.build.equipment.mainWeapon.refinement, 11);
  assert.equal(expected.build.equipment.subWeapon.refinement, 0);
  await saved(page, expected);
  for (let repeat = 1; repeat <= 3; repeat++) {
    await page.close();
    page = await open();
    const actual = await capture(page);
    assert.equal(actual.build.equipment.subWeapon.type, '방패', 'Reopening a tab must retain the shield');
    assert.deepEqual(actual, expected, 'Every BuildDraft/Scenario field must survive reopening without extra option rows');
    await saved(page, expected);
  }
  console.log('Session restore: PASS (shield and full BuildDraft/Scenario x3)');
  for (const [main, sub] of [['한손검','한손검(듀얼소드)'], ['활','화살'], ['지팡이','마도구'], ['마도구','인술 두루마리'], ['선풍창','단검'], ['양손검','없음'], ['맨손','없음']]) {
    await page.locator('#appTabButton-equipment').click();
    await page.locator('#mainWeaponType').selectOption(main);
    await page.locator('#subWeaponType').selectOption(sub);
    const expected = await capture(page);
    await saved(page, expected);
    await page.close();
    page = await open();
    assert.deepEqual(await capture(page), expected, `${main}/${sub} must survive reopening`);
    console.log(`Session restore: PASS (${main}/${sub})`);
  }
  await page.reload();
  await page.waitForFunction(() => window.ToramUiFeatures?.settings);
  assert.equal(await page.locator('#wpnAtk').isDisabled(), true);
  await page.locator('#appTabButton-equipment').click();
  await page.locator('#mainWeaponType').selectOption('한손검');
  await page.locator('#subWeaponType').selectOption('방패');
  // Empty option lists are intentional user input and must not get default rows.
  for (const id of ['wpnOpts', 'armOpts']) {
    while (await page.locator(`#${id} .remove-option-row`).count()) await page.locator(`#${id} .remove-option-row`).first().click();
  }
  const empty = await capture(page);
  await saved(page, empty);
  await page.close();
  page = await open();
  assert.deepEqual(await capture(page), empty, 'Deleted option rows must stay deleted');
  assert.deepEqual(errors, []);
  console.log('Session restore: PASS (shield x3, all build/scenario fields, refinements 0/11, options including empty lists, crystas/locks, skills/buffs/combo/food/preferences, 7 equipment combinations, reload and tab close/reopen)');
} finally {
  if (browser) await browser.close();
  if (server.listening) await new Promise(resolve => server.close(resolve));
}
