import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { dirname, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import vm from 'node:vm';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const read = (path) => readFile(resolve(root, path), 'utf8');
const draft = {
  character:{ level:300, attributes:{ STR:100, INT:20, VIT:30, AGI:40, DEX:50, CRT:60 } },
  equipment:{ mainWeapon:{ type:'한손검', attack:500, refinement:15, stability:80, options:[{ key:'ATK', value:10 }], crystas:['fixture', ''], lockedCrystaSlots:[true, false] }, subWeapon:{ type:'방패', attack:0, refinement:15, stability:0, options:[], crystas:[], lockedCrystaSlots:[] }, armor:{ type:'일반', attack:null, refinement:null, stability:null, options:[], crystas:[], lockedCrystaSlots:[] }, additional:{ type:null, attack:null, refinement:null, stability:null, options:[], crystas:[], lockedCrystaSlots:[] }, special:{ type:null, attack:null, refinement:null, stability:null, options:[], crystas:[], lockedCrystaSlots:[] } },
  externalOptions:[{ key:'MAXMP', value:100 }], skillLevels:{ Blade:{ 0:10 } }, activeBuffs:{ 'Blade:16':{ active:true, stacks:3 } }, combo:[{ skillId:'Blade:0', tag:'none', includeSpecialAttack:false, inputs:{} }]
};
const captured = { build:draft, scenario:{ target:{ bossLevel:300, bossDef:1000, bossMdef:500, bossCritResist:10, bossPhysResist:20, bossMagResist:30 }, conditions:{}, optimizationPreferences:{ rangeOverride:'LONG', requirements:{ maxHp:null }, bannedCrystas:['fixture-ban'] } }, request:{ selectedSkillId:'Blade:0', selectedHitId:'main', overrides:{ appliedComboHit:{ skillId:'Blade:0', hitId:'main', skillMult:2, skillConst:100, atkType:'PHYS', rangeType:'SHORT' } } } };
let passiveCalls = 0;
const window = {
  ToramBuildDraftStore:{ read:() => captured },
  getCrystaByName:(name) => name === 'fixture' ? { name } : null,
  applyPassiveSkillStats:(context) => { passiveCalls += 1; context.passiveApplied = true; },
  getBaseContext:() => {
    const scope = window.ToramCalculationInputScope;
    assert.ok(scope, 'Application은 명시적 계산 입력 스코프를 제공해야 합니다.');
    assert.equal(scope.kernelInput.controls.charLevel, 300);
    assert.equal(scope.kernelInput.controls.bossDef, 1000);
    assert.equal(scope.kernelInput.controls.mainWeaponType, '한손검');
    assert.equal(scope.kernelInput.options.length, 2);
    assert.equal(scope.skillLevels.Blade[0], 10);
    assert.equal(scope.activeBuffs['Blade:16'].stacks, 3);
    assert.equal(scope.kernelInput.rangeOverride, 'LONG', '사용자가 고른 거리 판정은 계산 커널 입력으로 전달돼야 합니다.');
    return { level:scope.kernelInput.controls.charLevel, strBase:scope.kernelInput.controls.strBase, crtBase:scope.kernelInput.controls.crtBase, scopedOptions:scope.kernelInput.options.length };
  },
  simulateWithCrystas:(base, crystas) => ({ finalSTR:base.strBase, finalINT:0, finalVIT:0, finalAGI:0, finalDEX:0, finalATK:base.scopedOptions, finalMATK:0, finalASPD:0, finalCSPD:0, finalStab:0, finalWeaponAttack:0, crystas })
};
window.window = window;
const context = { window, console };
vm.createContext(context);
vm.runInContext(await read('assets/js/application-use-cases.js'), context, { filename:'application-use-cases.js' });
const result = window.ToramApplication.CalculateBuild();
assert.equal(passiveCalls, 1, '패시브 적용은 Snapshot 생성에서 한 번이어야 합니다.');
assert.equal(result.snapshot.source, 'build-draft');
assert.equal(result.calculation.finalATK, 2);
assert.equal(window.ToramCalculationInputScope, undefined, '계산 입력 스코프는 계산 뒤 전역에 남으면 안 됩니다.');
draft.character.attributes.STR = 999;
assert.equal(result.snapshot.build.character.attributes.STR, 100, 'Snapshot은 이후 BuildDraft 변경에 영향받지 않아야 합니다.');

const contracts = await read('frontend/domain/calculation-contracts.ts');
assert.match(contracts, /externalOptions: readonly StatOptionDraft\[\]/);
assert.match(contracts, /includeSpecialAttack: boolean/);
assert.match(contracts, /optimizationPreferences\?/);
const storeSource = await read('assets/js/build-draft-store.js');
assert.match(storeSource, /ToramUiState/);
assert.match(storeSource, /ToramRuntimeState/);
assert.doesNotMatch(storeSource, /d4UiRunVersion|d4LastOptimizationRequest/);
const applicationSource = await read('assets/js/application-use-cases.js');
assert.doesNotMatch(applicationSource, /document\./, 'Application은 DOM을 직접 읽으면 안 됩니다.');
assert.doesNotMatch(applicationSource, /ToramComboUi|getCurrentCrystas|ToramActiveBuffs/, 'Application은 암묵적 UI 전역값을 계산 입력으로 읽으면 안 됩니다.');
const optimizerSource = await read('assets/js/optimizer.js');
assert.match(optimizerSource, /ToramRuntimeState/);

console.log('R4 BuildDraft single-source state verification: PASS');
