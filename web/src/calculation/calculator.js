import {policies} from './calculation-policies.js';
import init,* as core from '../../../build/generated/wasm/crysta.js';
const binary=new URL('../../../build/generated/wasm/crysta_bg.wasm',import.meta.url);
await init({module_or_path:binary.protocol==='file:' && typeof process!=='undefined' && process.versions?.node ? await (await import('node:fs/promises')).readFile(binary) : binary});
export const ToramExactMath=Object.freeze({ratio:(value,rate,divisor=1,flat=0)=>core.exact_ratio(value,rate,divisor,flat),percent:(value,rate,flat=0)=>core.exact_percent(value,rate,flat),proportionalAttack:(ctx,prefix)=>core.proportional_attack_json(JSON.stringify(ctx),prefix==='matk')});
function applyStat(ctx,key,value){return policies.applyStat(ctx,key,value);}
function resolveNormalAttackAmpr(value,profile){return JSON.parse(core.normal_attack_ampr_json(value,JSON.stringify(profile||{})));}
function calculateResistanceProfile(components){return JSON.parse(core.resistance_profile_json(JSON.stringify(Array.isArray(components)?components:[components])));}
function calculateEffectiveResistance(components){return calculateResistanceProfile(components).effective;}
        function removeEmbeddedActiveGlobalDamage(ctx, appliedComboHit) {
            var embeddedPercent = Number(appliedComboHit && appliedComboHit.embeddedActiveGlobalDamagePercent) || 0;
            if (embeddedPercent) ctx.damageP = Math.round(((Number(ctx.damageP) || 0) - embeddedPercent + Number.EPSILON) * 1e6) / 1e6;
            return ctx;
        }


        function numericFlag(flags, key, fallback) {
            var value = Number(flags && flags[key]);
            return Number.isFinite(value) ? value : (fallback === undefined ? 0 : fallback);
        }
        function applyAttackProfileToContext(ctx, appliedComboHit) {
            var profile = appliedComboHit && appliedComboHit.hitProfile || null;
            var flags = Object.assign({}, profile && profile.flags || {});
            ctx.attackProfile = profile ? { damageType:profile.damageType, count:Number(profile.count) || 1, multiplier:Number(profile.multiplier) || 0, constant:Number(profile.constant) || 0, flags:flags } : null;
            ctx.optimizationBasisName = appliedComboHit && appliedComboHit.skillName || '평타';
            if (!profile) return ctx;
            ctx.atkType = profile.damageType === 'magic' ? 'MAG' : 'PHYS';
            if (flags.forceLongRange || flags.longRange) ctx.rangeType = 'LONG';
            else if (flags.forceShortRange || flags.shortRange) ctx.rangeType = 'SHORT';
            ctx.chkIsUnsheathe = Boolean(flags.unsheathe);
            ctx.chkGuaranteedCrit = Boolean(flags.guaranteedCritical);
            ctx.noCritical = Boolean(flags.noCritical || flags.nonCritical);
            ctx.criticalChanceBonus = numericFlag(flags, 'criticalChanceBonus') + numericFlag(flags, 'criticalBonus') - numericFlag(flags, 'criticalChancePenalty');
            ctx.criticalChanceMultiplier = numericFlag(flags, 'criticalChanceMultiplier', 1);
            ctx.fixedCriticalChance = Number.isFinite(Number(flags.fixedCriticalChance)) ? Number(flags.fixedCriticalChance) : null;
            ctx.minimumCriticalDamage = numericFlag(flags, 'minimumCriticalDamage');
            ctx.stabilityBonus = numericFlag(flags, 'stabilityBonus');
            ctx.physicalPierceSkillBonus = numericFlag(flags, 'physicalPierceBonus') - numericFlag(flags, 'physicalPiercePenalty');
            ctx.magicPierceSkillBonus = numericFlag(flags, 'magicPierceBonus');
            ctx.ignoreDefense = Boolean(flags.ignoreDefense);
            ctx.ignoreMdef = Boolean(flags.ignoreMdef);
            ctx.halfMdefIgnored = Boolean(flags.halfMdefIgnored);
            ctx.useHigherRangeDamage = Boolean(flags.shortOrLongRangeHigher || flags.useHigherRangeDamage);
            ctx.attackPowerMode = flags.usesAtkPlusMatk ? 'sum' : (flags.usesHigherAtkOrMatk ? 'higher' : (flags.usesAtkInsteadOfMatk ? 'atk' : (flags.wizardMatkBlend ? 'wizardBlend' : 'default')));
            ctx.attackElement = flags.element === undefined ? 'weapon' : (flags.element === 'none' ? 'neutral' : String(flags.element));
            ctx.attackProfileDiagnostics = Object.keys(flags).filter(function (key) {
                return /When$/.test(key) && typeof flags[key] === 'string';
            });
            return ctx;
        }
        function cloneContextValue(value) {
            if (value === null || value === undefined || typeof value !== 'object') return value;
            if (Array.isArray(value)) return value.map(cloneContextValue);
            var result = {};
            for (var key in value) result[key] = cloneContextValue(value[key]);
            return result;
        }
        function cloneCtx(baseCtx) {
            return cloneContextValue(baseCtx);
        }

function formatFull(result) {
 const {ctx:c,breakdown:b}=result;
 let critTip=`기초 크리율: 25 + 스탯보정(${b.crtCorrection}) = ${b.baseCrit}\n옵션 보정: +${c.critP}%, +${c.critF}\n`;
 let cdmgTip=`기초 크뎀: ${b.baseCDMG}\n옵션 보정: +${c.cdmgP}%, +${c.cdmgF}\n`;
 if(c.atkType==='MAG') {
  critTip+=`마법 크리 반영률: ${b.magicCritReflect}% (스펠 버스트 ${b.spellReflect}%${b.weakenReflect?' + 쇠약 50%':''}, 최종: ${result.finalCrit})`;
  cdmgTip+=`마법 크뎀 반영률: ${b.magicCdmgReflect}% (최종: ${result.finalCDMG}%)`;
 } else {critTip+=`최종 확률: ${result.finalCrit}`;cdmgTip+=`최종 크뎀: ${result.finalCDMG}%`;}
 if(c.chkGuaranteedCrit)critTip='특성/스킬에 의해 크리티컬 확률이 확정(100% 이상)으로 고정되었습니다.\n(적 크리티컬 저항 무시)';
 if(c.noCritical)critTip='선택한 공격은 크리티컬이 발생하지 않습니다.';
 let elemTip=`기본 장비 속성에 유리: +${b.baseElem}%\n`;
 if(b.targetBonus)elemTip+=`대상 속성 추가 위력: ${b.targetBonus}%\n`;
 if(b.attacksWeakness)elemTip+='약점 속성 공격 보너스: +25%\n';
 if(b.awakening||b.magicElement||b.weaponMagicElement)elemTip+=`기본 INT 비례 보너스(INT ${c.intBase} / 10): +${b.intElemBonus}%\n`;
 elemTip+=`최종 적용 속성에 유리: +${b.elem}%`;
 const full={...result};delete full.breakdown;
 full.tooltips={
  atkTip:`무기ATK(${b.weapon}) + 스탯ATK(${b.statAtk}) + 레벨(${c.level}) ${b.atkUp>0?'+스탯ATK업('+b.atkUp+')':''} = ${b.preAtk}\n최종비율/고정: +${c.atkP}%, +${c.atkF}`,
  matkTip:`무기ATK(${b.wpnMatkContrib}) + 스탯MATK(${b.statMatk}) + 레벨(${c.level}) ${b.matkUp>0?'+스탯MATK업('+b.matkUp+')':''} = ${b.preMatk}\n최종비율/고정: +${c.matkP}%, +${c.matkF}${b.conversionFlatMatk>0?', 컨버전 MATK(+) +'+b.conversionFlatMatk:''}`,
  motionTip:`ASPD보정(+${b.motionBonus}%) + 장비/크리스타(+${c.motionSpeed}%) = +${full.finalMotionSpeed}%`,
  aspdTip:`기초(${b.baseASPD}) + 스탯ASP(${b.statASPD}) + 레벨(${c.level}) = ${b.preASPD}\n비율/고정: +${b.totalAspdP}%, +${c.aspdF}`,
  cspdTip:`레벨(${c.level}) + AGI보정(${b.agiCspdTip}) + DEX보정(${b.dexCspdTip}) = ${b.preCSPD}\n비율/고정: +${c.cspdP}%, +${c.cspdF}`,
  critTip,cdmgTip,elemTip
 };
 return full;
}

function candidateContext(base,candidates){
    const ctx=cloneCtx(base);
    for(const candidate of candidates||[]){
        if(!candidate)continue;
        for(const [key,value] of Object.entries(candidate.stats||{}))applyStat(ctx,key,parseFloat(value)||0);
        for(const row of candidate.conditionalStats||[])if(policies.matchesCrystaCondition(ctx,row.when))for(const [key,value] of Object.entries(row.stats))applyStat(ctx,key,parseFloat(value)||0);
    }
    return ctx;
}
function simulateWithCrystas(base,candidates,snapshotOnly,summaryOnly,supplyOnly){
    const ctx=candidateContext(base,candidates);
    // Skill effects are already assembled; the investment table is output metadata, not numeric input.
    const hasLevels=Object.hasOwn(ctx,'skillLevels');
    const input=hasLevels?{...ctx}:ctx;
    if(hasLevels)delete input.skillLevels;
    if(supplyOnly)return JSON.parse(core.candidate_supply_bases_json(JSON.stringify(input)));
    const result=JSON.parse(core.evaluate_context_json(JSON.stringify(input),summaryOnly===true));
    if(!summaryOnly&&hasLevels)result.ctx.skillLevels=ctx.skillLevels;
    return summaryOnly ? result : formatFull(result);
}
export const calculationKernel=Object.freeze({evaluateContext:(base,candidates,summaryOnly)=>simulateWithCrystas(base,candidates,true,summaryOnly===true),candidateSupplyBases:(base,stats)=>simulateWithCrystas(base,[{stats:stats||{}}],true,false,true),cloneContext:cloneCtx,applyStat,resolveNormalAttackAmpr});
export {applyStat,resolveNormalAttackAmpr,calculateResistanceProfile,calculateEffectiveResistance,removeEmbeddedActiveGlobalDamage,numericFlag,applyAttackProfileToContext,cloneContextValue,cloneCtx,simulateWithCrystas};
