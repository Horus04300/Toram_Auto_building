import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { dirname, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import vm from 'node:vm';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const read = (path) => readFile(resolve(root, path), 'utf8');

const policyWindow = {
  TORAM_SKILL_EFFECT_DATA:{ skills:[
    { id:'Demo:0', kind:'buff', value:'base' },
    { id:'Demo:0', kind:'buff', stackControl:{ maxStacks:3 }, value:'stack' },
    { id:'Demo:1', kind:'attack' }
  ] },
  ToramSkillEffectRegistry:{ all:() => [{ id:'Demo:2', kind:'attack' }] },
  ToramStatRegistry:{ apply:(context, key, value) => { context[key] = (context[key] || 0) + value; return context; } }
};
policyWindow.window = policyWindow;
const policyContext = { window:policyWindow, console };
vm.createContext(policyContext);
vm.runInContext(await read('assets/js/calculation-policies.js'), policyContext, { filename:'calculation-policies.js' });

const policies = policyWindow.ToramCalculationPolicies;
assert.equal(policies.resolveSkillDefinition('Demo:0').value, 'base', '계산용 스킬 선택은 기존과 같이 첫 정의를 사용해야 합니다.');
assert.equal(policies.resolveSkillDefinition('Demo:0', { preferStackControl:true }).value, 'stack', '버프 표시는 스택 보강 정의를 명시적으로 선택해야 합니다.');
assert.equal(policies.matchesCrystaCondition({ mainType:'한손검', subType:'방패', armorType:'일반' }, { main:'한손검', sub:'방패' }), true);
assert.equal(policies.matchesCrystaCondition({ mainType:'한손검' }, { main:'활' }), false);
const statContext = {};
policies.applyStat(statContext, 'ATK', 5);
assert.equal(statContext.ATK, 5, 'StatRegistry 적용은 정책 경로를 통과해야 합니다.');

let passiveCalls = 0;
const applicationWindow = {
  getBaseContext:() => ({ level:300, strBase:100 }),
  ToramActiveBuffs:{ getSelections:() => ({ 'Demo:0':{ active:true, stacks:2 } }) },
  applyPassiveSkillStats:(context) => { passiveCalls += 1; context.passiveApplied = true; },
  simulateWithCrystas:(baseContext, crystas) => ({ finalSTR:110, finalINT:120, finalVIT:130, finalAGI:140, finalDEX:150, finalATK:1000, finalMATK:800, finalASPD:1200, finalCSPD:900, finalStab:85, finalWeaponAttack:300, finalMaxMP:1200, baseContext, crystas })
};
applicationWindow.ToramBuildDraftStore = { read:() => ({
  build:{ character:{ level:300, attributes:{ STR:100, INT:100, VIT:100, AGI:100, DEX:100, CRT:50 } }, equipment:{ mainWeapon:{ crystas:[] }, armor:{ crystas:[] }, additional:{ crystas:[] }, special:{ crystas:[] } }, externalOptions:[], skillLevels:{}, activeBuffs:{ 'Demo:0':{ active:true, stacks:2 } }, combo:[] },
  scenario:{ target:{}, conditions:{} }, request:{ selectedSkillId:null, selectedHitId:null, overrides:{} }
}) };
applicationWindow.window = applicationWindow;
const applicationContext = { window:applicationWindow, console };
vm.createContext(applicationContext);
vm.runInContext(await read('assets/js/application-use-cases.js'), applicationContext, { filename:'application-use-cases.js' });

const application = applicationWindow.ToramApplication;
const buildResult = application.CalculateBuild();
assert.equal(passiveCalls, 1, 'Snapshot 생성에서 패시브 계산은 한 번만 적용해야 합니다.');
assert.equal(buildResult.snapshot.baseContext.passiveApplied, true);
assert.equal(JSON.stringify(buildResult.snapshot.crystas), JSON.stringify([null, null, null, null, null, null, null, null]));
assert.equal(buildResult.combat.ATK, 1000);
assert.equal(buildResult.combat.MAXMP, undefined, '전투 스냅샷은 기존 콤보 계약처럼 MAXMP를 별도 반환해야 합니다.');
assert.equal(JSON.stringify(application.ResolveActiveBuffs()), JSON.stringify({ 'Demo:0':{ active:true, stacks:2 } }));

const applied = application.ApplyComboHit({
  id:'hit-1', multiplier:1.5, constant:200, damageType:'physical', flags:{ forceLongRange:true, unsheathe:true },
  passiveDamageModifiers:[{ stackGroup:'activeGlobalDamage', value:1.1 }], procDamageModifiers:[{ source:'fixture' }]
}, 2, {}, { id:'Demo:1', nameKo:'검증 공격' });
assert.equal(applied.skillMult, 3);
assert.equal(applied.rangeType, 'LONG');
assert.equal(applied.embeddedActiveGlobalDamagePercent, 10);
assert.equal(applied.skillName, '검증 공격');

for (const path of ['assets/js/optimizer.js', 'assets/js/active-buff-ui.js', 'assets/js/combo-ui.js']) {
  const source = await read(path);
  assert.match(source, /ToramApplication/, path + ': Application 유스케이스를 사용해야 합니다.');
}
const optimizerSource = await read('assets/js/optimizer.js');
assert.doesNotMatch(optimizerSource, /var baseCtx\s*=\s*getBaseContext\(\);[\s\S]*applyPassiveSkillStats\(baseCtx\)/, '최적화 UI가 계산 조립 순서를 직접 소유하면 안 됩니다.');
const comboSource = await read('assets/js/combo-ui.js');
assert.doesNotMatch(comboSource, /var base\s*=\s*window\.getBaseContext\(\);[\s\S]*window\.simulateWithCrystas/, '콤보 UI가 DOM 계산 조립을 직접 수행하면 안 됩니다.');
const activeBuffSource = await read('assets/js/active-buff-ui.js');
assert.doesNotMatch(activeBuffSource, /var base\s*=\s*window\.getBaseContext\(\);[\s\S]*window\.simulateWithCrystas/, '버프 UI가 DOM 계산 조립을 직접 수행하면 안 됩니다.');

console.log('R3 Application use-case and policy verification: PASS');
