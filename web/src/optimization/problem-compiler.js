import {crystaIdentity} from '../application/crysta-identity.js';
import {statRegistry} from '../calculation/stat-registry.js';
import {policies} from '../calculation/calculation-policies.js';

  'use strict';

  var SCHEMA = 'toram.crysta-problem.v1';
  var compareNames = new Intl.Collator('ko').compare;
  var GROUPS = Object.freeze([
    Object.freeze({ id:'weapon', label:'무기', category:'무기', slots:[0,1] }),
    Object.freeze({ id:'armor', label:'방어구', category:'방어구', slots:[2,3] }),
    Object.freeze({ id:'additional', label:'추가', category:'추가', slots:[4,5] }),
    Object.freeze({ id:'special', label:'특수', category:'특수', slots:[6,7] })
  ]);

  function clone(value) {
    if (value === null || value === undefined || typeof value !== 'object') return value;
    if (Array.isArray(value)) return value.map(clone);
    var result = {};
    Object.keys(value).forEach(function (key) { result[key] = clone(value[key]); });
    return result;
  }

  function freeze(value) {
    if (!value || typeof value !== 'object' || Object.isFrozen(value)) return value;
    Object.keys(value).forEach(function (key) { freeze(value[key]); });
    return Object.freeze(value);
  }

  function normalizeName(value) {
    return String(value || '').trim().replace(/\s+/g, '').toLowerCase();
  }

  function categoryGroup(value) {
    var text = String(value || '');
    if (text.indexOf('무기') !== -1) return '무기';
    if (text.indexOf('방어') !== -1 || text.indexOf('몸') !== -1) return '방어구';
    if (text.indexOf('추가') !== -1) return '추가';
    if (text.indexOf('특수') !== -1) return '특수';
    return '노말';
  }

  function conditionMatches(structure, condition) {
    return policies.matchesCrystaCondition(structure,condition);
  }

  function createStructure(baseContext) {
    var ctx = baseContext || {};
    var structure = {
      mainType:String(ctx.mainType || ''),
      subType:String(ctx.subType || ''),
      armorType:String(ctx.armorType || '')
    };
    structure.signature = [structure.mainType, structure.subType, structure.armorType].join('|');
    return freeze(structure);
  }

  function addStat(target, key, value, registry, diagnostics, owner) {
    var amount = Number(value);
    if (!Number.isFinite(amount)) return;
    var normalized = registry && typeof registry.normalize === 'function' ? registry.normalize(key) : String(key || '').toUpperCase();
    if (!normalized) {
      diagnostics.push({ code:'UNKNOWN_STAT', key:String(key), owner:owner, message:'등록되지 않은 스탯 키입니다: ' + key });
      return;
    }
    target[normalized] = (Number(target[normalized]) || 0) + (registry && typeof registry.normalizeValue === 'function' ? registry.normalizeValue(normalized, amount) : amount);
  }

  function buildLineageIndex(crystas) {
    var identity = crystaIdentity;
    return identity.createIndex(crystas);
  }

  function resolveCrysta(crysta, structure, registry, lineageIndex, diagnostics) {
    if (!crysta) return null;
    var statDelta = {};
    var activeConditions = [];
    var inactiveConditions = [];
    Object.keys(crysta.stats || {}).forEach(function (key) { addStat(statDelta,key,crysta.stats[key],registry,diagnostics,crysta.name); });
    (crysta.conditionalStats || []).forEach(function (entry) {
      var active = conditionMatches(structure, entry && entry.when);
      (active ? activeConditions : inactiveConditions).push(clone(entry && entry.when || {}));
      if (active) Object.keys(entry && entry.stats || {}).forEach(function (key) {
        addStat(statDelta, key, entry.stats[key], registry, diagnostics, crysta.name);
      });
    });
    var line = lineageIndex.lineage(crysta);
    return freeze({
      id:'crysta:' + crysta.gameItemId,
      name:String(crysta.name),
      category:categoryGroup(crysta.category),
      statDelta:statDelta,
      evaluatorCandidate:{ name:String(crysta.name), category:String(crysta.category || ''), stats:clone(statDelta) },
      lineage:line,
      lineageRoot:line.length ? line[line.length - 1] : normalizeName(crysta.name),
      resolvedConditionMetadata:{ active:activeConditions, inactive:inactiveConditions },
      gameItemId:crysta.gameItemId
    });
  }

  function mergeStats(items) {
    var result = {};
    (items || []).forEach(function (item) {
      Object.keys(item && item.statDelta || {}).forEach(function (key) {
        result[key] = (Number(result[key]) || 0) + Number(item.statDelta[key] || 0);
      });
    });
    return result;
  }

  function makePackage(group, left, right, structure) {
    var selected = [left, right].filter(Boolean);
    var names = selected.map(function (item) { return item.name; });
    var idNames = names.slice().sort(compareNames);
    if (!idNames.length) idNames.push('empty');
    return freeze({
      id:group.id + ':' + idNames.join('+'),
      slot:group.id,
      source:'crysta',
      structureSignature:structure.signature,
      statDelta:mergeStats(selected),
      resolvedConditionMetadata:{
        active:selected.reduce(function (all,item) { return all.concat(item.resolvedConditionMetadata.active); }, []),
        inactive:selected.reduce(function (all,item) { return all.concat(item.resolvedConditionMetadata.inactive); }, [])
      },
      sockets:2,
      conflicts:[],
      resourceCost:{ sockets:selected.length },
      candidateIds:selected.map(function (item) { return item.id; }),
      candidateNames:names,
      // resolveCrysta deeply freezes these values; sharing them is immutable.
      evaluatorCandidates:selected.map(function (item) { return item.evaluatorCandidate; }),
      metadata:{ label:group.label, emptySlots:2-selected.length }
    });
  }

  function packageGroup(group, pool, lockedValues, lockFlags, structure, lineageIndex, registry, diagnostics) {
    var resolvedPool = pool.map(function (item) { return resolveCrysta(item, structure, registry, lineageIndex, diagnostics); });
    function lockedAt(index) {
      var value = lockedValues[index];
      if (!value) return null;
      var raw = typeof value === 'string' ? lineageIndex.resolve(value) : value;
      if (!raw) {
        diagnostics.push({ code:'UNKNOWN_LOCKED_CRYSTA', slot:group.slots[index], name:String(value && value.name || value), message:'잠긴 크리스타를 데이터에서 찾을 수 없습니다.' });
        return null;
      }
      var category = categoryGroup(raw.category);
      if (category !== '노말' && category !== group.category) diagnostics.push({ code:'INVALID_SLOT_CATEGORY', slot:group.slots[index], name:raw.name, message:'잠긴 크리스타의 부위가 맞지 않습니다.' });
      return resolveCrysta(raw, structure, registry, lineageIndex, diagnostics);
    }
    var leftLocked = Boolean(lockFlags[0]);
    var rightLocked = Boolean(lockFlags[1]);
    var lockedLeft = leftLocked ? lockedAt(0) : null;
    var lockedRight = rightLocked ? lockedAt(1) : null;
    var options = [null].concat(resolvedPool);
    var packages = [];
    function validPair(left, right) {
      if (!left || !right) return true;
      return !lineageIndex.conflict(left, right);
    }
    if (leftLocked && rightLocked) {
      if (!validPair(lockedLeft, lockedRight)) diagnostics.push({ code:'LOCKED_CRYSTA_CONFLICT', slot:group.id, message:'같은 장비에 잠긴 크리스타 계보가 충돌합니다.' });
      else packages.push(makePackage(group, lockedLeft, lockedRight, structure));
    } else if (leftLocked || rightLocked) {
      options.forEach(function (candidate) {
        var left = leftLocked ? lockedLeft : candidate;
        var right = rightLocked ? lockedRight : candidate;
        if (validPair(left, right)) packages.push(makePackage(group, left, right, structure));
      });
    } else {
      for (var i=0; i<options.length; i++) {
        for (var j=i; j<options.length; j++) {
          if (i === j && options[i]) continue;
          if (validPair(options[i], options[j])) packages.push(makePackage(group, options[i], options[j], structure));
        }
      }
    }
    packages.sort(function (a,b) { return compareNames(a.id, b.id); });
    return freeze({ id:group.id, label:group.label, slots:group.slots.slice(), packages:packages });
  }

  function compileCrystaProblem(input) {
    var options = input || {};
    var crystas = Array.isArray(options.crystas) ? options.crystas : [];
    var registry = options.registry || statRegistry;
    if (!registry || typeof registry.normalize !== 'function') throw new Error('CrystaOptimization StatRegistry가 필요합니다.');
    var baseContext = clone(options.baseContext || {});
    var structure = createStructure(baseContext);
    var diagnostics = [];
    var lineageIndex = buildLineageIndex(crystas);
    var obsolete = options.keepLowerUpgrades ? Object.create(null) : lineageIndex.obsoleteIds();
    var banned = Object.create(null);
    function ban(name) {
      var item = lineageIndex.resolve(name);
      if (item) banned[String(item.gameItemId)] = true;
    }
    Object.keys(options.banned || {}).forEach(function (name) { if (options.banned[name]) ban(name); });
    (options.excluded || []).forEach(ban);
    var current = Array.isArray(options.currentCrystas) ? options.currentCrystas : [];
    var locks = Array.isArray(options.locks) ? options.locks : [];
    var groups = GROUPS.map(function (group) {
      var pool = crystas.filter(function (crysta) {
        if (!crysta || !crysta.name) return false;
        var key = String(crysta.gameItemId);
        var category = categoryGroup(crysta.category);
        // User policy: basic flat-stat tutorial series is excluded from automatic picks.
        var tutorial = crysta.gameItemId >= 9401 && crysta.gameItemId <= 9504;
        return !tutorial && !banned[key] && !obsolete[key] && (category === '노말' || category === group.category);
      });
      return packageGroup(group, pool, [current[group.slots[0]], current[group.slots[1]]], [locks[group.slots[0]], locks[group.slots[1]]], structure, lineageIndex, registry, diagnostics);
    });
    var initialPackageIds = groups.map(function (group, groupIndex) {
      var definition = GROUPS[groupIndex];
      var desired = [current[definition.slots[0]], current[definition.slots[1]]].filter(Boolean).map(function (item) { return String(item.name || item); }).sort(compareNames);
      var match = group.packages.find(function (item) {
        var names = (item.candidateNames || []).slice().sort(compareNames);
        return names.length === desired.length && names.every(function (name,index) { return name === desired[index]; });
      });
      return match ? match.id : null;
    });
    var problem = {
      schema:SCHEMA,
      baseContext:baseContext,
      scenarioSnapshot:clone(options.scenarioSnapshot || null),
      structure:structure,
      groups:groups,
      diagnostics:diagnostics,
      metadata:{
        originalCrystaCount:crystas.length,
        removedLowerUpgradeCount:Object.keys(obsolete).length,
        lockedSlotCount:locks.filter(Boolean).length,
        initialPackageIds:initialPackageIds
      }
    };
    return freeze(problem);
  }

  var api = Object.freeze({
    schema:SCHEMA,
    groups:GROUPS,
    normalizeName:normalizeName,
    categoryGroup:categoryGroup,
    conditionMatches:conditionMatches,
    createStructure:createStructure,
    buildLineageIndex:buildLineageIndex,
    resolveCrysta:resolveCrysta,
    compileCrystaProblem:compileCrystaProblem
  });

  export const problemCompiler = api;
