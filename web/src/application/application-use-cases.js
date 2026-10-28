import {skillEffects} from '../calculation/skill-effect-engine.js';
import {buildStore} from './build-draft-store.js';
import {crystaCatalog} from '../data/crysta-data.js';
import {statRegistry} from '../calculation/stat-registry.js';
import {foodCatalog} from '../data/my-room-food.js';
import * as buildValues from './build-values.mjs';
import * as itemRules from './item-catalog.mjs';
import {simulateWithCrystas,applyStat,applyAttackProfileToContext,removeEmbeddedActiveGlobalDamage,cloneCtx} from '../calculation/calculator.js';
  'use strict';
  function clone(value) { if (value === null || value === undefined || typeof value !== 'object') return value; if (Array.isArray(value)) return value.map(clone); return Object.keys(value).reduce(function (result, key) { result[key] = clone(value[key]); return result; }, {}); }
  function freeze(value) { if (!value || typeof value !== 'object' || Object.isFrozen(value)) return value; Object.keys(value).forEach(function (key) { freeze(value[key]); }); return Object.freeze(value); }
  function emptyRequest() { return { selectedSkillId:null, selectedHitId:null, overrides:{} }; }
  function captureCurrentInput() { var store = buildStore; if (!store || typeof store.read !== 'function') throw new Error('BuildDraft 저장소가 준비되지 않았습니다.'); return store.read(); }
  function crystasFromBuild(build) {
    return ['mainWeapon', 'armor', 'additional', 'special'].reduce(function (result, slot) {
      var names = build.equipment && build.equipment[slot] && build.equipment[slot].crystas || [];
      var first = names[0] ? crystaCatalog.resolve(names[0]) : null;
      var second = names[1] ? crystaCatalog.resolve(names[1]) : null;
      if (first && second && crystaCatalog.conflict(first, second)) second = null;
      result.push(first, second); return result;
    }, []);
  }
  function resolveBuildOptions(build, scenario) {
    var equipment = build.equipment || {}, main = equipment.mainWeapon || {}, sub = equipment.subWeapon || {}, armor = equipment.armor || {}, target = scenario && scenario.target || {}, attributes = build.character && build.character.attributes || {};
    var itemContext = { mainType:main.type || '', subType:sub.type || '', armorType:armor.type || '', activeItemEventTypes:scenario && scenario.conditions && scenario.conditions.activeItemEventTypes || [] };
    var allOptions = Object.keys(equipment).reduce(function (items, slot) {
      var piece = equipment[slot], options = piece.options || [];
      if (piece.catalogItem) {
        var rules = itemRules;
        if (!rules) throw new Error('게임 장비 옵션 규칙이 준비되지 않았습니다.');
        options = options.concat(rules.resolveEquipmentOptions(piece.catalogItem, slot, itemContext, statRegistry));
      }
      return items.concat(options);
    }, []).concat(build.externalOptions || []);
    if (build.consumableBuffs !== undefined) {
      if (!itemRules) throw new Error('소모품 버프 규칙이 준비되지 않았습니다.');
      allOptions = allOptions.concat(itemRules.resolveConsumableBuffs(build.consumableBuffs, statRegistry));
    }
    if (foodCatalog) allOptions = allOptions.concat(foodCatalog.options(build.myRoomFood));
    if (build.guildFoodBuff !== false) allOptions = allOptions.concat([{key:'MAXHP',value:1000},{key:'MAXMP',value:100}]);
    var optimizationPreferences = scenario && scenario.optimizationPreferences || {};
    var equipmentRules = itemRules;
    var elements = {
      weaponElement:main.catalogItem ? equipmentRules.resolveEquipmentElement(main.catalogItem,'mainWeapon',itemContext,statRegistry) : 0,
      subWeaponElement:sub.catalogItem ? equipmentRules.resolveEquipmentElement(sub.catalogItem,'subWeapon',itemContext,statRegistry) : 0
    };
    return { ...elements, options:allOptions };
  }
  function createCalculationSnapshot(input) {
    var source = input || captureCurrentInput(), build = source.build, scenario = source.scenario || { target:{}, conditions:{} }, request = source.request || emptyRequest();
    if (!build || typeof build !== 'object') throw new Error('CalculationSnapshot에는 BuildDraft가 필요합니다.');
    buildValues.validateBuild(build, { registry:statRegistry, food:foodCatalog });
    buildValues.validateScenario(scenario);
    var baseContext = createCalculationContext(build, scenario, request, resolveBuildOptions(build, scenario));
    applyPassiveSkillStats(baseContext);
    return freeze({ build:clone(build), scenario:clone(scenario), request:clone(request), baseContext:baseContext, crystas:crystasFromBuild(build), source:'build-draft' });
  }
  function combatContext(snapshot, calculation) { var base = snapshot.baseContext; return { STR:calculation.finalSTR, INT:calculation.finalINT, VIT:calculation.finalVIT, AGI:calculation.finalAGI, DEX:calculation.finalDEX, CRT:base.crtBase, ATK:calculation.finalATK, MATK:calculation.finalMATK, ASPD:calculation.finalASPD, CSPD:calculation.finalCSPD, STABILITY:calculation.finalStab, WEAPON_ATK:calculation.finalWeaponAttack }; }
  function calculateBuild(input) { var snapshot = input && input.build && input.baseContext ? input : createCalculationSnapshot(input); if (typeof simulateWithCrystas !== 'function') throw new Error('계산 커널이 준비되지 않았습니다.'); var calculation = simulateWithCrystas(snapshot.baseContext, snapshot.crystas); return freeze({ snapshot:snapshot, calculation:calculation, combat:combatContext(snapshot, calculation) }); }
  function applyComboHit(hit, damageMultiplier, skill) {
    var selected = hit || {}, multiplier = selected.effectiveMultiplier === undefined ? Number(selected.multiplier) * Number(damageMultiplier) : Number(selected.effectiveMultiplier), layers = selected.damageMultiplierLayers ? clone(selected.damageMultiplierLayers) : { skill:Number.isFinite(Number(selected.baseMultiplier)) ? Number(selected.baseMultiplier) : Number(selected.multiplier) || 1, passive:Number.isFinite(Number(selected.passiveMultiplier)) ? Number(selected.passiveMultiplier) : 1, active:Number.isFinite(Number(selected.activeMultiplier)) ? Number(selected.activeMultiplier) : 1, combo:selected.effectiveMultiplier === undefined ? Number(damageMultiplier) : 1 }, flags = clone(selected.resolvedFlags || selected.flags || {}), activeGlobalDamagePercent = (selected.passiveDamageModifiers || []).filter(function (item) { return item.stackGroup === 'activeGlobalDamage'; }).reduce(function (sum, item) { return sum + (Number(item.value) - 1) * 100; }, 0);
    return { skillMult:multiplier, damageMultiplierLayers:layers, skillConst:selected.constant, skillId:skill && skill.id || '', skillName:skill && skill.nameKo || '선택 공격', hitId:selected.id || '', hitProfile:{ damageType:selected.damageType, count:Number(selected.count) || 1, multiplier:multiplier, constant:Number(selected.constant) || 0, flags:flags }, atkType:selected.damageType === 'magic' ? 'MAG' : 'PHYS', rangeType:flags.longRange || flags.forceLongRange ? 'LONG' : 'SHORT', unsheathe:Boolean(flags.unsheathe), guaranteedCritical:Boolean(flags.guaranteedCritical), guaranteedHit:Boolean(flags.guaranteedHit), hitBonus:Number(flags.hitBonus) || 0, embeddedActiveGlobalDamagePercent:Number(activeGlobalDamagePercent.toFixed(6)), procDamageModifiers:Array.isArray(selected.procDamageModifiers) ? selected.procDamageModifiers.map(clone) : [] };
  }
  export const application = Object.freeze({ CreateCalculationSnapshot:createCalculationSnapshot, CalculateBuild:calculateBuild, ApplyComboHit:applyComboHit });

function skillInvestment(levels, treeId, skillId) { return Math.max(0, Number(levels[treeId] && levels[treeId][skillId]) || 0); }

function activeBuffIsEnabled(selections, skillId) { var setting = selections[skillId]; return setting === true || Boolean(setting && setting.active); }

function createCalculationContext(build, scenario, request, resolved) {
            var equipment = build.equipment || {}, main = equipment.mainWeapon || {}, sub = equipment.subWeapon || {}, armor = equipment.armor || {};
            var character = build.character || {}, attributes = character.attributes || {}, target = scenario.target || {};
            var levels = build.skillLevels || {}, activeSelections = build.activeBuffs || {};
            var appliedComboHit = request && request.overrides && request.overrides.appliedComboHit || null;
            var poisonSources = skillEffects && typeof skillEffects.learnedAilmentSources === 'function'
                ? skillEffects.learnedAilmentSources('poison',levels) : [];
            var weakenSources = skillEffects && typeof skillEffects.learnedAilmentSources === 'function'
                ? skillEffects.learnedAilmentSources('weaken',levels) : [];
            var ctx = {
                skillLevels:cloneCtx(levels),
                level: parseFloat((character.level)) || 0,
                strBase: parseFloat((attributes.STR)) || 0,
                intBase: parseFloat((attributes.INT)) || 0,
                vitBase: parseFloat((attributes.VIT)) || 0,
                agiBase: parseFloat((attributes.AGI)) || 0,
                dexBase: parseFloat((attributes.DEX)) || 0,
                crtBase: parseFloat((attributes.CRT)) || 0,

                atkType: appliedComboHit ? appliedComboHit.atkType : 'PHYS',
                rangeType: appliedComboHit ? appliedComboHit.rangeType : 'SHORT',
                mainType: (main.type || ''),
                wpnAtk: (main.type || '') === '맨손' ? 0 : (parseFloat((main.attack)) || 0),
                wpnRefine: (main.type || '') === '맨손' ? 0 : (parseFloat((main.refinement)) || 0),
                wpnStab: (main.type || '') === '맨손' ? 1 : (parseFloat((main.stability)) || 80),
                subType: (sub.type || ''),
                weaponElement: Number(resolved.weaponElement) || 0,
                subWeaponElement: Number(resolved.subWeaponElement) || 0,
                subAtk: parseFloat((sub.attack)) || 0,
                subRefine: parseFloat((sub.refinement)) || 0,
                subStab: parseFloat((sub.stability)) || 0,
                armorType: (armor.type || ''),

                bossLevel: parseFloat((target.bossLevel)) || 0,
                bossDef: parseFloat((target.bossDef)) || 0,
                bossMdef: parseFloat((target.bossMdef)) || 0,
                bossCritResist: parseFloat((target.bossCritResist)) || 0,
                bossPhysResist: parseFloat((target.bossPhysResist)) || 0,
                bossMagResist: parseFloat((target.bossMagResist)) || 0,
                targetElement: Number((target.targetElement)) || 0,
                skillMult: appliedComboHit ? appliedComboHit.skillMult : 1,
                damageMultiplierLayers: appliedComboHit && appliedComboHit.damageMultiplierLayers ? Object.assign({}, appliedComboHit.damageMultiplierLayers) : null,
                skillConst: appliedComboHit ? appliedComboHit.skillConst : 0,
                optimizationBasisName: appliedComboHit && appliedComboHit.skillName || '평타',
                appliedSkillId: appliedComboHit && appliedComboHit.skillId || '',
                attackProfile: null,
                procDamageModifiers: appliedComboHit && Array.isArray(appliedComboHit.procDamageModifiers) ? appliedComboHit.procDamageModifiers.map(function(item) { return Object.assign({}, item); }) : [],

                chkIsUnsheathe: Boolean(appliedComboHit && appliedComboHit.unsheathe),
                conversionLevel: skillInvestment(levels,'MagicBlade', 1),
                conversionActive: activeBuffIsEnabled(activeSelections,'MagicBlade:1'),
                dualBringerLevel: skillInvestment(levels,'MagicBlade', 4),
                dualBringerActive: activeBuffIsEnabled(activeSelections,'MagicBlade:4'),
                spellBurstLevel: skillInvestment(levels,'Battle', 12),
                godspeedWieldLevel: skillInvestment(levels,'Halberd', 19),
                maximizerLevel: skillInvestment(levels,'Magic', 20),
                poisonSources: poisonSources,
                weakenSources: weakenSources,
                targetWeakened: weakenSources.length > 0,
                chkGuaranteedCrit: Boolean(appliedComboHit && appliedComboHit.guaranteedCritical),

                strP: 0, strF: 0, dexP: 0, dexF: 0, intP: 0, intF: 0, agiP: 0, agiF: 0, vitP: 0, vitF: 0,
                atkP: 0, atkF: 0, matkP: 0, matkF: 0, cdmgP: 0, cdmgF: 0,
                critP: 0, critF: 0, srw: 0, lrw: 0, unsheatheP: 0, unsheatheF: 0, elemP: 0, damageP: 0, watkP: 0, watkF: 0, baseWpnAtkF: 0,
                physPierce: 0, magPierce: 0, aspdF: 0, aspdP: 0, cspdF: 0, cspdP: 0, stability: 0, motionSpeed: 0, castRed: 0, maxMpF: 0, maxHpF: 0, maxHpP: 0, amprF: 0, amprP: 0,
                elementAwakening: false, magicElement: false,
                fireDmg: 0, waterDmg: 0, windDmg: 0, earthDmg: 0, lightDmg: 0, darkDmg: 0, neutralDmg: 0,
                attackElement: 'none', attackProfileDiagnostics: [], attackPowerMode: 'default', useHigherRangeDamage: false,
                noCritical: false, criticalChanceBonus: 0, criticalChanceMultiplier: 1, fixedCriticalChance: null, minimumCriticalDamage: 0,
                stabilityBonus: 0, physicalPierceSkillBonus: 0, magicPierceSkillBonus: 0,
                ignoreDefense: false, ignoreMdef: false, halfMdefIgnored: false,
                atkUpSTR: 0, atkUpDEX: 0, atkUpINT: 0, atkUpAGI: 0, atkUpVIT: 0,
                matkUpSTR: 0, matkUpDEX: 0, matkUpINT: 0, matkUpAGI: 0, matkUpVIT: 0,
                preservedStats: {}, statDiagnostics: []
            };
            applyAttackProfileToContext(ctx, appliedComboHit);
            var rangeOverride = scenario.optimizationPreferences && scenario.optimizationPreferences.rangeOverride;
            if (rangeOverride === 'SHORT' || rangeOverride === 'LONG') ctx.rangeType = rangeOverride;
            resolved.options.forEach(function (option) { applyStat(ctx, option.key, parseFloat(option.value) || 0); });
            // 스킬별 계수·상수는 콤보 탭에서 선택한 타격을 통해 주입한다.
            ctx.skillStats = [];
            if (skillEffects && typeof skillEffects.activeStatChanges === 'function') {
                skillEffects.activeStatChanges(ctx, ctx, {}, { activeBuffs:activeSelections }).forEach(function (change) {
                    applyStat(ctx, change.key, change.value);
                });
            }
            removeEmbeddedActiveGlobalDamage(ctx, appliedComboHit);
            ctx.activeBuildConversions = skillEffects && typeof skillEffects.activeBuildConversions === 'function'
                ? skillEffects.activeBuildConversions(ctx, {}, {}, { activeBuffs:activeSelections }).map(function (effect) { return Object.assign({}, effect); })
                : [];
            ctx.normalAttackAmprProfile = skillEffects && typeof skillEffects.normalAttackAmprModifiers === 'function'
                ? skillEffects.normalAttackAmprModifiers(ctx, {}, {}, { activeBuffs:activeSelections })
                : { passive:[], activeCandidates:[] };

            return ctx;
        }

function applyPassiveSkillStats(ctx) {
            if (!skillEffects) return;
            skillEffects.passiveStatChanges(ctx).forEach(function (change) {
                applyStat(ctx, change.key, change.value);
            });
        }
export {createCalculationContext,applyPassiveSkillStats};
