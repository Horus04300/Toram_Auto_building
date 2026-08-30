import { readFile } from 'node:fs/promises';
import { createRequire } from 'node:module';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const require = createRequire(import.meta.url);
const registry = require(resolve(root, 'assets/js/stat-registry.js'));
const context = { window:{ ToramStatRegistry:registry }, console };
context.window.window = context.window;
vm.createContext(context);
vm.runInContext('var BASE_ASPD_MAP={"한손검":100,"양손검":50,"활":75,"자동활":30,"지팡이":60,"마도구":90,"권갑":120,"선풍창":25,"발도검":200,"맨손":1000};', context);
vm.runInContext(await readFile(resolve(root, 'assets/js/calculator.js'), 'utf8'), context, { filename:'calculator.js' });

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

const cases = [
  { id:'physical-short', baseContext:base(), stats:{ ATKP:12, ATK:40, CDMG:25, CRIT:18, SRW:10, PHYS_PIERCE:8, MAXHP:1000, MAXMP:400, AMPR:20, ASPD:120 } },
  { id:'magic-long-boundaries', baseContext:base({ mainType:'지팡이', wpnAtk:450, wpnRefine:10, wpnStab:60, strBase:50, intBase:500, agiBase:100, dexBase:200, atkType:'MAG', rangeType:'LONG', bossMdef:2500, bossMagResist:20, spellBurstLevel:10, targetWeakened:true, attackElement:'weakness', magicElement:true, critF:120, maxHpF:0 }), stats:{ MATKP:20, MATK:80, CDMGP:15, CRITP:10, LRW:18, MAG_PIERCE:25, ELEM_P:12, MAXMP:600, AMPRP:20 } },
  { id:'dual-sword', baseContext:base({ subType:'한손검(듀얼소드)', subAtk:420, subRefine:12, subStab:70, agiBase:300, armorType:'중량옷' }), stats:{ ATKP:8, WATKP:5, STABILITY:12, AMPR:15, ASPD_P:20, CRIT:30 } },
  { id:'unsheathe-crit-cap', baseContext:base({ mainType:'발도검', chkIsUnsheathe:true, strBase:400, dexBase:400, critF:500, cdmgF:220, bossDef:1200 }), stats:{ UNSHEATHEP:15, UNSHEATHE:80, CDMG:130, CRIT:60, SRW:20, PHYS_PIERCE:10 } },
  { id:'physical-active-conversion-layers', baseContext:base({
    mainType:'한손검', subType:'마도구', strBase:300, intBase:210, agiBase:50, dexBase:200, wpnAtk:500, wpnRefine:12,
    bossDef:3500, bossPhysResist:15, additionalTargetResistances:[5,-2], chkIsUnsheathe:true, unsheatheP:14, unsheatheF:60,
    activeBuildConversions:[{ conversion:'unsheatheToAtk', value:.5 }], conversionLevel:5, fixedCriticalChance:70, minimumCriticalDamage:260,
    normalAttackAmprProfile:{ passive:[{percent:10},{flat:7}], activeCandidates:[{id:'zeta',percent:20},{id:'alpha',multiplier:1.2}] },
    ignoreDefense:true, useHigherRangeDamage:true, srw:8, lrw:18, attackPowerMode:'higher',
    damageMultiplierLayers:{skill:1.18,passive:1.05,active:1.1,combo:.8}, skillStats:[{stat:'totalSTR',target:'mult',ratio:.0005},{stat:'DEX',target:'const',ratio:.1}],
    procDamageModifiers:[{source:'half',chancePercent:50,multiplier:2},{source:'minus',chancePercent:25,multiplier:.5}]
  }), stats:{ATKP:9,ATK:30,MATKP:15,MATK:80,UNSHEATHEP:6,UNSHEATHE:20,MAXMP:200,AMPR:10,CRIT:15,CDMG:20,LRW:4} },
  { id:'magic-arrow-half-mdef', baseContext:base({
    mainType:'활', subType:'화살', subAtk:180, subStab:20, strBase:150, intBase:420, agiBase:100, dexBase:350, wpnAtk:470, wpnStab:55,
    atkType:'MAG', attackPowerMode:'wizardBlend', bossMdef:3200, bossMagResist:10, additionalTargetResistances:[7], halfMdefIgnored:true,
    spellBurstLevel:12, targetWeakened:true, attackElement:'weakness', fixedCriticalChance:160, magicPierceSkillBonus:12,
    rangeType:'LONG', damageMultiplierLayers:{passive:1.03,active:1.07,combo:.9}, skillStats:[{stat:'totalINT',target:'const',ratio:.2}]
  }), stats:{ATKP:5,MATKP:30,MATK:90,CRIT:25,CDMG:35,MAG_PIERCE:18,LRW:12,ELEM_P:8,STABILITY:5} },
  { id:'magic-dual-bringer-reflect', baseContext:base({
    mainType:'한손검', subType:'마도구', strBase:400, intBase:250, agiBase:80, dexBase:180, atkType:'MAG', attackPowerMode:'sum',
    bossMdef:1800, bossMagResist:8, spellBurstLevel:8, targetWeakened:true, dualBringerActive:true, dualBringerLevel:10,
    ignoreMdef:true, noCritical:false, criticalChanceMultiplier:1.1
  }), stats:{ATKP:10,ATK:20,MATKP:12,MATK:50,CRIT:80,CDMG:40,MAG_PIERCE:15} }
];

const kernel = context.window.ToramCalculationKernel.evaluateContext;
const result = {
  schema:'toram.d4-rust-evaluator-fixtures.v1',
  cases:cases.map(item => {
    const raw = kernel(item.baseContext, [{ name:'D4 aggregate', stats:item.stats }], true);
    return { id:item.id, baseContext:item.baseContext, stats:item.stats, expected:{
      optimizationDamageFactor:raw.optimizationDamageFactor, finalMaxHP:raw.finalMaxHP, finalMaxMP:raw.finalMaxMP,
      amprBeforeDual:raw.amprBeforeDual, normalAttackCrit:raw.normalAttackCrit, finalASPD:raw.finalASPD
    } };
  })
};
console.log(JSON.stringify(result, null, 2));
