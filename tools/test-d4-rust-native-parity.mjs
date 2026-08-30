import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { createRequire } from 'node:module';
import { resolve } from 'node:path';
import { spawn } from 'node:child_process';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const require = createRequire(import.meta.url);
const registry = require(resolve(root, 'assets/js/stat-registry.js'));

function base(overrides={}) {
  return Object.assign({
    level:325, strBase:255, intBase:0, vitBase:0, agiBase:0, dexBase:500, crtBase:0,
    mainType:'한손검', wpnAtk:600, wpnRefine:15, wpnStab:80, subType:'없음', subAtk:0, subRefine:0, subStab:0, armorType:'경량옷',
    bossLevel:325, bossDef:2000, bossMdef:2000, bossCritResist:0, bossPhysResist:0, bossMagResist:0,
    skillMult:1, skillConst:0, procDamageModifiers:[], atkType:'PHYS', rangeType:'SHORT', chkIsUnsheathe:false, chkGuaranteedCrit:false,
    conversionLevel:0, conversionActive:false, dualBringerLevel:0, dualBringerActive:false, spellBurstLevel:0, godspeedWieldLevel:0,
    poisonSources:[], weakenSources:[], targetWeakened:false, attackElement:'none', attackPowerMode:'default', useHigherRangeDamage:false,
    noCritical:false, criticalChanceBonus:0, criticalChanceMultiplier:1, fixedCriticalChance:null, minimumCriticalDamage:0,
    stabilityBonus:0, physicalPierceSkillBonus:0, magicPierceSkillBonus:0, ignoreDefense:false, ignoreMdef:false, halfMdefIgnored:false,
    strP:0, strF:0, dexP:0, dexF:0, intP:0, intF:0, agiP:0, agiF:0, vitP:0, vitF:0,
    atkP:0, atkF:0, matkP:0, matkF:0, cdmgP:0, cdmgF:0, critP:0, critF:200, srw:0, lrw:0, unsheatheP:0, unsheatheF:0, elemP:0, damageP:0, watkP:0, watkF:0, baseWpnAtkF:0,
    physPierce:0, magPierce:0, aspdF:3000, aspdP:0, cspdF:0, cspdP:0, stability:0, motionSpeed:0, castRed:0, maxHpF:20000, maxHpP:0, maxMpF:3000, amprF:200, amprP:0,
    elementAwakening:false, magicElement:false, atkUpSTR:0, atkUpDEX:0, atkUpINT:0, atkUpAGI:0, atkUpVIT:0, matkUpSTR:0, matkUpDEX:0,matkUpINT:0,matkUpAGI:0,matkUpVIT:0,
    preservedStats:{}, statDiagnostics:[], activeBuildConversions:[]
  }, overrides);
}

function matchesCondition(context, condition) {
  if (!condition) return true;
  return (!condition.main || condition.main.split('/').includes(context.mainType))
    && (!condition.sub || condition.sub.split('/').includes(context.subType))
    && (!condition.armor || condition.armor.split('/').includes(context.armorType));
}

function effectiveStats(crysta, context) {
  const result = {};
  const add = stats => Object.entries(stats || {}).forEach(([key, value]) => {
    const canonical = registry.normalize(key) || key;
    result[canonical] = (result[canonical] || 0) + Number(value || 0);
  });
  if (matchesCondition(context, crysta.cond)) add(crysta.stats);
  for (const item of crysta.condStats || []) if (matchesCondition(context, item.cond)) add(item.stats);
  return result;
}

function runNative(cases) {
  return new Promise((resolvePromise, reject) => {
    const child = spawn('cargo', ['run', '--quiet', '--manifest-path', 'src-tauri/Cargo.toml', '--bin', 'd4_native_summary'], { cwd:root, stdio:['pipe','pipe','pipe'] });
    let stdout = '';
    let stderr = '';
    child.stdout.on('data', chunk => { stdout += chunk; });
    child.stderr.on('data', chunk => { stderr += chunk; });
    child.on('error', reject);
    child.on('close', code => {
      if (code !== 0) return reject(new Error(`native parity bridge exited ${code}: ${stderr}`));
      try { resolvePromise(JSON.parse(stdout)); } catch (error) { reject(new Error(`native parity bridge returned invalid JSON: ${error.message}\n${stdout}\n${stderr}`)); }
    });
    child.stdin.end(JSON.stringify({ cases }));
  });
}

function isDefaultD4Feasible(summary, context) {
  return (context.rangeType === 'LONG' || summary.finalMaxHP >= 10000)
    && summary.finalMaxMP >= (Number(context.godspeedWieldLevel) === 10 ? 2300 : 2000)
    && summary.amprBeforeDual >= 100
    && summary.normalAttackCrit >= 100
    && summary.finalASPD >= 1000;
}

const calculatorContext = { window:{ ToramStatRegistry:registry }, console };
calculatorContext.window.window = calculatorContext.window;
vm.createContext(calculatorContext);
vm.runInContext('var BASE_ASPD_MAP={"한손검":100,"양손검":50,"활":75,"자동활":30,"지팡이":60,"마도구":90,"권갑":120,"선풍창":25,"발도검":200,"맨손":1000};', calculatorContext);
vm.runInContext(await readFile(resolve(root, 'assets/js/calculator.js'), 'utf8'), calculatorContext, { filename:'calculator.js' });
const dataContext = {};
vm.createContext(dataContext);
vm.runInContext(`${await readFile(resolve(root, 'assets/js/data/crysta-data.js'), 'utf8')}\nglobalThis.__crystas=crystaDataJson;`, dataContext);

const allCrystas = dataContext.__crystas;
const upgradedNames = new Set(allCrystas.map(item => item.prev).filter(Boolean));
const finalCrystas = allCrystas.filter(item => !upgradedNames.has(item.name));
assert.ok(finalCrystas.length > 100 && finalCrystas.length < allCrystas.length, '최종 강화 크리스타 선별이 실제 데이터 계보를 사용해야 합니다.');

const scenarios = [
  { id:'physical', baseContext:base() },
  { id:'magic', baseContext:base({mainType:'지팡이',wpnAtk:450,wpnRefine:10,wpnStab:60,strBase:50,intBase:500,agiBase:100,dexBase:200,atkType:'MAG',rangeType:'LONG',bossMdef:2500,bossMagResist:20,spellBurstLevel:10,targetWeakened:true}) },
  { id:'dual', baseContext:base({subType:'한손검(듀얼소드)',subAtk:420,subRefine:12,subStab:70,agiBase:300,armorType:'중량옷'}) },
  { id:'arrow', baseContext:base({mainType:'활',subType:'화살',subAtk:180,subStab:20,strBase:150,intBase:200,agiBase:100,dexBase:350,wpnAtk:470,wpnStab:55,rangeType:'LONG'}) },
  { id:'shield-heavy', baseContext:base({mainType:'양손검',subType:'방패',armorType:'중량옷',strBase:400,agiBase:100,dexBase:150}) },
  { id:'scroll', baseContext:base({mainType:'발도검',subType:'인술 두루마리',strBase:350,dexBase:400,chkIsUnsheathe:true}) }
];
const kernel = calculatorContext.window.ToramCalculationKernel.evaluateContext;
const cases = [];
const expected = new Map();
for (const scenario of scenarios) for (const crysta of finalCrystas) {
  const stats = effectiveStats(crysta, scenario.baseContext);
  const id = `${scenario.id}:${crysta.name}`;
  const raw = kernel(scenario.baseContext, [{ name:crysta.name, stats }], true);
  expected.set(id, raw);
  cases.push({ id, baseContext:scenario.baseContext, stats });
}
const aggregateCasesPerScenario = 32;
for (const scenario of scenarios) for (let sample = 0; sample < aggregateCasesPerScenario; sample++) {
  const stats = {};
  for (let offset = 0; offset < 8; offset++) {
    const crysta = finalCrystas[(sample * 37 + offset * 53 + offset * sample) % finalCrystas.length];
    for (const [key, value] of Object.entries(effectiveStats(crysta, scenario.baseContext))) {
      stats[key] = (stats[key] || 0) + value;
    }
  }
  const id = `${scenario.id}:aggregate:${sample}`;
  expected.set(id, kernel(scenario.baseContext, [{ name:'D4 deterministic aggregate', stats }], true));
  cases.push({ id, baseContext:scenario.baseContext, stats });
}
const response = await runNative(cases);
assert.equal(response.schema, 'toram.d4-native-summary.v1');
assert.equal(response.results.length, cases.length, 'native evaluator가 모든 실제 최종 크리스타 사례를 반환해야 합니다.');
for (const result of response.results) {
  const js = expected.get(result.id);
  assert.ok(js, `알 수 없는 native 결과 ${result.id}`);
  const native = result.summary;
  for (const [nativeKey, jsKey] of Object.entries({ optimizationDamageFactor:'optimizationDamageFactor', finalMaxHP:'finalMaxHP', finalMaxMP:'finalMaxMP', amprBeforeDual:'amprBeforeDual', normalAttackCrit:'normalAttackCrit', finalASPD:'finalASPD' })) {
    assert.equal(native[nativeKey], js[jsKey], `${result.id} ${nativeKey} must match JavaScript`);
  }
  const baseContext = cases.find(item => item.id === result.id).baseContext;
  assert.equal(isDefaultD4Feasible(native, baseContext), isDefaultD4Feasible(js, baseContext), `${result.id} default D4 feasibility must match JavaScript`);
}
console.log(`D4 Rust native parity: PASS (${finalCrystas.length} final crystas × ${scenarios.length} scenarios + ${aggregateCasesPerScenario * scenarios.length} deterministic aggregates = ${cases.length} cases)`);
