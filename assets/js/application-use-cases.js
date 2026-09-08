/* R4 Application 경계: BuildDraft + Context + Request만 계산 입력으로 허용한다. */
(function (root) {
  'use strict';
  function clone(value) { if (value === null || value === undefined || typeof value !== 'object') return value; if (Array.isArray(value)) return value.map(clone); return Object.keys(value).reduce(function (result, key) { result[key] = clone(value[key]); return result; }, {}); }
  function freeze(value) { if (!value || typeof value !== 'object' || Object.isFrozen(value)) return value; Object.keys(value).forEach(function (key) { freeze(value[key]); }); return Object.freeze(value); }
  function emptyRequest() { return { selectedSkillId:null, selectedHitId:null, overrides:{} }; }
  function captureCurrentInput() { var store = root.ToramBuildDraftStore; if (!store || typeof store.read !== 'function') throw new Error('BuildDraft 저장소가 준비되지 않았습니다.'); return store.read(); }
  function resolveActiveBuffs(selections) { if (selections !== undefined) return clone(selections || {}); return clone(captureCurrentInput().build.activeBuffs || {}); }
  function crystasFromBuild(build) {
    return ['mainWeapon', 'armor', 'additional', 'special'].reduce(function (result, slot) {
      var names = build.equipment && build.equipment[slot] && build.equipment[slot].crystas || [];
      var first = names[0] && typeof root.getCrystaByName === 'function' ? root.getCrystaByName(names[0]) : null;
      var second = names[1] && typeof root.getCrystaByName === 'function' ? root.getCrystaByName(names[1]) : null;
      if (first && second && typeof root.isCrystaConflict === 'function' && root.isCrystaConflict(first, second)) second = null;
      result.push(first, second); return result;
    }, []);
  }
  function kernelInput(build, scenario, request) {
    var equipment = build.equipment || {}, main = equipment.mainWeapon || {}, sub = equipment.subWeapon || {}, armor = equipment.armor || {}, target = scenario && scenario.target || {}, attributes = build.character && build.character.attributes || {};
    var allOptions = Object.keys(equipment).reduce(function (items, slot) { return items.concat(equipment[slot].options || []); }, []).concat(build.externalOptions || []);
    var optimizationPreferences = scenario && scenario.optimizationPreferences || {};
    return { controls:{ charLevel:build.character && build.character.level, strBase:attributes.STR, intBase:attributes.INT, vitBase:attributes.VIT, agiBase:attributes.AGI, dexBase:attributes.DEX, crtBase:attributes.CRT, mainWeaponType:main.type || '', wpnAtk:main.attack, wpnRefine:main.refinement, wpnStab:main.stability, subWeaponType:sub.type || '', subAtk:sub.attack, subRefine:sub.refinement, subStab:sub.stability, armorType:armor.type || '', bossLevel:target.bossLevel, bossDef:target.bossDef, bossMdef:target.bossMdef, bossCritResist:target.bossCritResist, bossPhysResist:target.bossPhysResist, bossMagResist:target.bossMagResist }, options:allOptions, appliedComboHit:request && request.overrides && request.overrides.appliedComboHit || null, rangeOverride:optimizationPreferences.rangeOverride || null };
  }
  function withCalculationScope(build, scenario, request, work) {
    var previous = root.ToramCalculationInputScope;
    root.ToramCalculationInputScope = { skillLevels:clone(build.skillLevels || {}), activeBuffs:clone(build.activeBuffs || {}), kernelInput:kernelInput(build, scenario, request) };
    try { return work(); } finally { if (previous === undefined) delete root.ToramCalculationInputScope; else root.ToramCalculationInputScope = previous; }
  }
  function createCalculationSnapshot(input) {
    var source = input || captureCurrentInput(), build = source.build, scenario = source.scenario || { target:{}, conditions:{} }, request = source.request || emptyRequest();
    if (!build || typeof build !== 'object') throw new Error('CalculationSnapshot에는 BuildDraft가 필요합니다.');
    var baseContext = withCalculationScope(build, scenario, request, function () { if (typeof root.getBaseContext !== 'function') throw new Error('계산 커널 입력 어댑터가 준비되지 않았습니다.'); var base = root.getBaseContext(); if (typeof root.applyPassiveSkillStats === 'function') root.applyPassiveSkillStats(base); return base; });
    return freeze({ build:clone(build), scenario:clone(scenario), request:clone(request), baseContext:baseContext, crystas:crystasFromBuild(build), source:'build-draft' });
  }
  function combatContext(snapshot, calculation) { var base = snapshot.baseContext; return { STR:calculation.finalSTR, INT:calculation.finalINT, VIT:calculation.finalVIT, AGI:calculation.finalAGI, DEX:calculation.finalDEX, CRT:base.crtBase, ATK:calculation.finalATK, MATK:calculation.finalMATK, ASPD:calculation.finalASPD, CSPD:calculation.finalCSPD, STABILITY:calculation.finalStab, WEAPON_ATK:calculation.finalWeaponAttack }; }
  function calculateBuild(input) { var snapshot = input && input.build && input.baseContext ? input : createCalculationSnapshot(input); if (typeof root.simulateWithCrystas !== 'function') throw new Error('계산 커널이 준비되지 않았습니다.'); var calculation = withCalculationScope(snapshot.build, snapshot.scenario, snapshot.request, function () { return root.simulateWithCrystas(snapshot.baseContext, snapshot.crystas); }); return freeze({ snapshot:snapshot, calculation:calculation, combat:combatContext(snapshot, calculation) }); }
  function applyComboHit(hit, damageMultiplier, modifiers, skill) {
    var selected = hit || {}, multiplier = selected.effectiveMultiplier === undefined ? Number(selected.multiplier) * Number(damageMultiplier) : Number(selected.effectiveMultiplier), layers = selected.damageMultiplierLayers ? clone(selected.damageMultiplierLayers) : { skill:Number.isFinite(Number(selected.baseMultiplier)) ? Number(selected.baseMultiplier) : Number(selected.multiplier) || 1, passive:Number.isFinite(Number(selected.passiveMultiplier)) ? Number(selected.passiveMultiplier) : 1, active:Number.isFinite(Number(selected.activeMultiplier)) ? Number(selected.activeMultiplier) : 1, combo:selected.effectiveMultiplier === undefined ? Number(damageMultiplier) : 1 }, flags = clone(selected.resolvedFlags || selected.flags || {}), activeGlobalDamagePercent = (selected.passiveDamageModifiers || []).filter(function (item) { return item.stackGroup === 'activeGlobalDamage'; }).reduce(function (sum, item) { return sum + (Number(item.value) - 1) * 100; }, 0);
    return { skillMult:multiplier, damageMultiplierLayers:layers, skillConst:selected.constant, skillId:skill && skill.id || '', skillName:skill && skill.nameKo || '선택 공격', hitId:selected.id || '', hitProfile:{ damageType:selected.damageType, count:Number(selected.count) || 1, multiplier:multiplier, constant:Number(selected.constant) || 0, flags:flags }, atkType:selected.damageType === 'magic' ? 'MAG' : 'PHYS', rangeType:flags.longRange || flags.forceLongRange ? 'LONG' : 'SHORT', unsheathe:Boolean(flags.unsheathe), guaranteedCritical:Boolean(flags.guaranteedCritical), guaranteedHit:Boolean(flags.guaranteedHit), hitBonus:Number(flags.hitBonus) || 0, embeddedActiveGlobalDamagePercent:Number(activeGlobalDamagePercent.toFixed(6)), procDamageModifiers:Array.isArray(selected.procDamageModifiers) ? selected.procDamageModifiers.map(clone) : [] };
  }
  function settingsRepository() { var repository = root.ToramSettingsRepository; if (!repository) throw new Error('Settings Repository가 준비되지 않았습니다.'); return repository; }
  var settings = Object.freeze({
    flush:function () { return settingsRepository().flushApplicationState(); },
    getUpdateSettings:function () { return settingsRepository().getUpdateSettings(); },
    setUpdateSettings:function (value) { return settingsRepository().setUpdateSettings(value); },
    list:function () { return settingsRepository().list(); },
    directory:function () { return settingsRepository().directory(); },
    save:function (name) { return settingsRepository().save(name); },
    overwrite:function (name) { return settingsRepository().overwrite(name); },
    load:function (name) { return settingsRepository().load(name); },
    remove:function (name) { return settingsRepository().remove(name); },
    export:function (name) { return settingsRepository().exportCurrent(name); },
    import:function (text) { return settingsRepository().importSavedBuild(text); },
    isAvailable:function () { return settingsRepository().isNativeAvailable(); }
  });
  root.ToramApplication = Object.freeze({ CaptureCurrentInput:captureCurrentInput, CreateCalculationSnapshot:createCalculationSnapshot, CalculateBuild:calculateBuild, ResolveActiveBuffs:resolveActiveBuffs, ApplyComboHit:applyComboHit, Settings:settings });
}(typeof window !== 'undefined' ? window : globalThis));
