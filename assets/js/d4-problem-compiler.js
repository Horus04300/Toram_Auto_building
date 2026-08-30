(function (root) {
  'use strict';

  var SCHEMA = 'toram.d4-crysta-problem.v1';
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

  function splitCondition(value) {
    return String(value || '').split('/').map(function (item) { return item.trim(); }).filter(Boolean);
  }

  function conditionMatches(structure, condition) {
    if (!condition) return true;
    if (condition.main && splitCondition(condition.main).indexOf(structure.mainType) === -1) return false;
    if (condition.sub && splitCondition(condition.sub).indexOf(structure.subType) === -1) return false;
    if (condition.armor && splitCondition(condition.armor).indexOf(structure.armorType) === -1) return false;
    return true;
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
    target[normalized] = (Number(target[normalized]) || 0) + amount;
  }

  function buildLineageIndex(crystas) {
    var byName = Object.create(null);
    (Array.isArray(crystas) ? crystas : []).forEach(function (crysta) {
      if (crysta && crysta.name) byName[normalizeName(crysta.name)] = crysta;
    });
    var cache = Object.create(null);
    function lineage(crysta) {
      if (!crysta || !crysta.name) return [];
      var ownKey = normalizeName(crysta.name);
      if (cache[ownKey]) return cache[ownKey].slice();
      var result = [ownKey];
      var current = crysta;
      var visited = Object.create(null);
      visited[ownKey] = true;
      while (current && current.prev) {
        var previousKey = normalizeName(current.prev);
        if (!previousKey || visited[previousKey]) break;
        visited[previousKey] = true;
        result.push(previousKey);
        current = byName[previousKey] || null;
      }
      cache[ownKey] = result.slice();
      return result;
    }
    function conflict(left, right) {
      if (!left || !right) return false;
      var leftLine = lineage(left);
      var rightSet = Object.create(null);
      lineage(right).forEach(function (key) { rightSet[key] = true; });
      return leftLine.some(function (key) { return Boolean(rightSet[key]); });
    }
    function obsoleteNames() {
      var obsolete = Object.create(null);
      Object.keys(byName).forEach(function (key) {
        var line = lineage(byName[key]);
        for (var i=1; i<line.length; i++) if (byName[line[i]]) obsolete[line[i]] = true;
      });
      return obsolete;
    }
    return { byName:byName, lineage:lineage, conflict:conflict, obsoleteNames:obsoleteNames };
  }

  function resolveCrysta(crysta, structure, registry, lineageIndex, diagnostics) {
    if (!crysta) return null;
    var statDelta = {};
    var activeConditions = [];
    var inactiveConditions = [];
    var rootActive = conditionMatches(structure, crysta.cond);
    if (crysta.cond) (rootActive ? activeConditions : inactiveConditions).push(clone(crysta.cond));
    if (rootActive) Object.keys(crysta.stats || {}).forEach(function (key) {
      addStat(statDelta, key, crysta.stats[key], registry, diagnostics, crysta.name);
    });
    (crysta.condStats || []).forEach(function (entry) {
      var active = conditionMatches(structure, entry && entry.cond);
      (active ? activeConditions : inactiveConditions).push(clone(entry && entry.cond || {}));
      if (active) Object.keys(entry && entry.stats || {}).forEach(function (key) {
        addStat(statDelta, key, entry.stats[key], registry, diagnostics, crysta.name);
      });
    });
    var line = lineageIndex.lineage(crysta);
    return freeze({
      id:'crysta:' + normalizeName(crysta.name),
      name:String(crysta.name),
      category:categoryGroup(crysta.category),
      statDelta:statDelta,
      evaluatorCandidate:{ name:String(crysta.name), category:String(crysta.category || ''), stats:clone(statDelta) },
      lineage:line,
      lineageRoot:line.length ? line[line.length - 1] : normalizeName(crysta.name),
      resolvedConditionMetadata:{ active:activeConditions, inactive:inactiveConditions },
      original:clone(crysta)
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
    var idNames = names.slice().sort(function (a,b) { return a.localeCompare(b, 'ko'); });
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
      evaluatorCandidates:selected.map(function (item) { return clone(item.evaluatorCandidate); }),
      metadata:{ label:group.label, emptySlots:2-selected.length }
    });
  }

  function packageGroup(group, pool, lockedValues, lockFlags, structure, lineageIndex, registry, diagnostics) {
    var resolvedPool = pool.map(function (item) { return resolveCrysta(item, structure, registry, lineageIndex, diagnostics); });
    var byName = lineageIndex.byName;
    function lockedAt(index) {
      var value = lockedValues[index];
      if (!value) return null;
      var raw = typeof value === 'string' ? byName[normalizeName(value)] : value;
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
      return !lineageIndex.conflict(left.original, right.original);
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
    packages.sort(function (a,b) { return a.id.localeCompare(b.id, 'ko'); });
    return freeze({ id:group.id, label:group.label, slots:group.slots.slice(), packages:packages });
  }

  function compileCrystaProblem(input) {
    var options = input || {};
    var crystas = Array.isArray(options.crystas) ? options.crystas : [];
    var registry = options.registry || root.ToramStatRegistry;
    if (!registry || typeof registry.normalize !== 'function') throw new Error('D4 StatRegistry가 필요합니다.');
    var baseContext = clone(options.baseContext || {});
    var structure = createStructure(baseContext);
    var diagnostics = [];
    var lineageIndex = buildLineageIndex(crystas);
    var obsolete = options.keepLowerUpgrades ? Object.create(null) : lineageIndex.obsoleteNames();
    var banned = Object.create(null);
    Object.keys(options.banned || {}).forEach(function (name) { if (options.banned[name]) banned[normalizeName(name)] = true; });
    (options.excluded || []).forEach(function (name) { banned[normalizeName(name)] = true; });
    var current = Array.isArray(options.currentCrystas) ? options.currentCrystas : [];
    var locks = Array.isArray(options.locks) ? options.locks : [];
    var groups = GROUPS.map(function (group) {
      var pool = crystas.filter(function (crysta) {
        if (!crysta || !crysta.name) return false;
        var key = normalizeName(crysta.name);
        var category = categoryGroup(crysta.category);
        return !banned[key] && !obsolete[key] && (category === '노말' || category === group.category);
      });
      return packageGroup(group, pool, [current[group.slots[0]], current[group.slots[1]]], [locks[group.slots[0]], locks[group.slots[1]]], structure, lineageIndex, registry, diagnostics);
    });
    var initialPackageIds = groups.map(function (group, groupIndex) {
      var definition = GROUPS[groupIndex];
      var desired = [current[definition.slots[0]], current[definition.slots[1]]].filter(Boolean).map(function (item) { return String(item.name || item); }).sort(function (a,b) { return a.localeCompare(b, 'ko'); });
      var match = group.packages.find(function (item) {
        var names = (item.candidateNames || []).slice().sort(function (a,b) { return a.localeCompare(b, 'ko'); });
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
  if (typeof module === 'object' && module.exports) module.exports = api;
  if (root) root.ToramD4ProblemCompiler = api;
}(typeof window !== 'undefined' ? window : globalThis));
