import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { dirname, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import vm from 'node:vm';
import { LEGACY_SCRIPT_PATHS } from '../assets/js/legacy-script-manifest.mjs';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const dataScripts = LEGACY_SCRIPT_PATHS.filter(path => path.startsWith('assets/js/data/'));
let investments = {};
const context = { window:{ skillSimulatorState:{ getInvestments:() => investments } }, console };
context.window.window = context.window;
vm.createContext(context);
for (const path of dataScripts) vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename:path });
for (const path of ['assets/js/skill-effect-engine.js', 'assets/js/combo-sequence-engine.js', 'assets/js/stat-registry.js', 'assets/js/calculation-policies.js']) {
  vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename:path });
}

const E = context.window.ToramSkillEffects;
const Q = context.window.ToramComboSequence;
const learn = (ids) => {
  investments = {};
  for (const id of ids) {
    const [treeId, skillId] = id.split(':');
    (investments[treeId] ||= {})[skillId] = 10;
  }
};
const base = (mainType='한손검', subType='없음') => ({
  mainType, subType, subAtk:200, subRefine:15, subStab:80, level:300,
  strBase:100, intBase:100, vitBase:100, agiBase:100, dexBase:100, crtBase:50
});
const combat = { STR:120, INT:120, VIT:120, AGI:120, DEX:120, CRT:50, ATK:1000, MATK:800, MAXHP:10000, WEAPON_ATK:300 };

learn(['MagicBlade:1', 'MagicBlade:7']);
let profile = E.profile('MagicBlade:7', base('한손검', '마도구'), combat, {}, { activeBuffs:{ 'MagicBlade:1':{ active:true, stacks:0 } } });
assert.equal(profile.hits[0].damageType, 'magic', '컨버전 조건부 공격 유형은 문자열 magic으로 해석되어야 합니다.');
profile = E.profile('MagicBlade:7', base('한손검', '마도구'), combat, {}, { activeBuffs:{ 'MagicBlade:1':{ active:false, stacks:0 } } });
assert.equal(profile.hits[0].damageType, 'physical', '컨버전 비활성 공격 유형은 physical이어야 합니다.');

learn(['Shot:0']);
profile = E.profile('Shot:0', base('활', '화살'), combat, { targetSlowed:true });
assert.equal(typeof profile.hits[0].resolvedFlags.criticalChanceBonus, 'number', '타격 플래그의 조건식은 실행값으로 해석되어야 합니다.');
assert.equal(profile.hits[0].flags.criticalChanceBonus.op, 'if', '원문 플래그 AST도 회귀 검증을 위해 보존해야 합니다.');

learn(['Wizard:4', 'Knight:14']);
assert.equal(E.profile('Wizard:4', base('지팡이', '마도구'), combat, {}).inputs.triggeringElement, 'none', '문자열 입력 기본값을 보존해야 합니다.');
assert.equal(E.profile('Knight:14', base('한손검', '방패'), combat, {}).inputs.durability, 90, '동적 숫자 입력 기본값을 계산해야 합니다.');

learn(['Shot:0', 'Blade:0']);
let result = Q.evaluate([{ skillId:'Shot:0', tag:'none' }, { skillId:'Blade:0', tag:'none' }], base('한손검', '없음'), combat, { maxMp:1000 });
assert.equal(result.blockedAt, 1, '현재 장비에서 사용할 수 없는 스킬에서 콤보를 중단해야 합니다.');
assert.equal(result.entries[1].executionStatus, 'skipped', '사용 불가 스킬 이후 공격은 계산하지 않아야 합니다.');

learn(['Blade:22', 'Blade:0']);
result = Q.evaluate([{ skillId:'Blade:22', tag:'none' }, { skillId:'Blade:0', tag:'none' }], base('한손검', '없음'), combat, { maxMp:2000 });
assert.equal(result.blockedAt, 1, 'canStart:false 스킬은 콤보 기점으로 실행하지 않아야 합니다.');

learn(['Blade:5', 'Blade:8']);
result = Q.evaluate([{ skillId:'Blade:5', tag:'none' }, { skillId:'Blade:8', tag:'smite' }], base('한손검', '없음'), combat, { maxMp:2000 });
assert.equal(result.blockedAt, 2, 'canReceiveTag:false 스킬에 콤보 효과를 적용하지 않아야 합니다.');

learn(['Blade:0', 'Blade:11']);
result = Q.evaluate([{ skillId:'Blade:0', tag:'none' }, { skillId:'Blade:11', tag:'smite', inputs:{ stacks:1 } }], base('양손검', '없음'), combat, { maxMp:2000 });
const mainHit = result.entries[1].hits.find(hit => hit.id === 'main');
const ignoredHit = result.entries[1].hits.find(hit => hit.id === 'twoHandExtra');
assert.equal(mainHit.effectiveMultiplier, mainHit.multiplier * 1.5, '일반 타격에는 강타 배율을 적용해야 합니다.');
assert.equal(ignoredHit.effectiveMultiplier, ignoredHit.multiplier, '콤보 대미지 변화 무시 타격에는 강타 배율을 적용하지 않아야 합니다.');

learn(['Blade:5', 'Blade:16', 'Support:6', 'Knight:14']);
const inactiveBuffProfile = E.profile('Blade:5', base('한손검', '방패'), combat, {}, {});
const activeBuffProfile = E.profile('Blade:5', base('한손검', '방패'), combat, {}, { activeBuffs:{
  'Blade:16':{ active:true, stacks:0 },
  'Support:6':{ active:true, stacks:0 },
  'Knight:14':{ active:true, stacks:0 }
} });
assert.ok(Math.abs(activeBuffProfile.hits[0].multiplier / inactiveBuffProfile.hits[0].multiplier - 1.55) < 1e-9, '액티브 전역 대미지 증가는 오라 20%+브레이브 20%+플레지 15%=55%로 합산해야 합니다.');

const calculatorSource = await readFile(resolve(root, 'assets/js/calculator.js'), 'utf8');
vm.runInContext(calculatorSource, context, { filename:'assets/js/calculator.js' });
assert.equal(context.calculateEffectiveResistance([158]), 158, '같은 내성 항목은 합산값을 그대로 사용해야 합니다.');
assert.equal(context.calculateEffectiveResistance([50, 20]), 70, '속성 내성 50과 물리 내성 20은 감쇠 없이 합산해야 합니다.');
assert.equal(context.calculateEffectiveResistance([50, 50]), 100, '같은 적용군의 내성은 합산해야 합니다.');
const resistanceProfile = context.calculateResistanceProfile([50, 20]);
assert.deepEqual(JSON.parse(JSON.stringify(resistanceProfile)), { components:[50, 20], raw:70, effective:70, multiplier:.3 }, '내성 프로필은 원합계와 1-내성/100 배율을 보존해야 합니다.');
assert.doesNotMatch(calculatorSource, /Math\.max\(0,\s*finalStab\)/, '음수 안정률은 남용 입력으로 보고 별도 보정하지 않아야 합니다.');
const statContext = { vitP:0 };
context.window.ToramCalculationPolicies.applyStat(statContext, 'VITP', 12);
assert.equal(statContext.vitP, 12, 'VIT% 옵션 적용은 단일 계산 정책으로 위임해야 합니다.');
assert.match(calculatorSource, /if \(ctx\.conversionLevel > 0[\s\S]*conversionIntMatk = Math\.floor\(totalINT/, '컨버전 패시브 MATK는 액티브 토글과 분리하고 곱셈 뒤 내림해야 합니다.');
assert.match(calculatorSource, /conversionFlatMatk = Math\.floor\(conversionAddMatk\) \+ Math\.floor\(conversionIntMatk\)[\s\S]*finalMATK = Math\.floor\(preFinalMatk[\s\S]*\+ conversionFlatMatk/, '컨버전 무기·INT 보정은 MATK% 계산 뒤 MATK(+)로 적용되어야 합니다.');
const storageSource = await readFile(resolve(root, 'assets/js/build-state-storage.js'), 'utf8');
assert.doesNotMatch(storageSource, /localStorage/, 'R6 이후 빌드 UI 어댑터는 localStorage를 직접 읽거나 쓰면 안 됩니다.');
const optimizerSource = await readFile(resolve(root, 'assets/js/optimizer.js'), 'utf8');
assert.match(optimizerSource, /totalActSpeed = Math\.min\(50, baseActSpeed \+ equipMotionSpeed\)/, '최종 행동속도는 50%를 넘지 않아야 합니다.');

console.log('QA edge-case regressions: PASS');
