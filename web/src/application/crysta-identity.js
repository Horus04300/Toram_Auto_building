

  'use strict';
  function normalize(value) { return String(value || '').trim().replace(/\s+/g,'').toLowerCase(); }
  function createIndex(items) {
    var byId = Object.create(null), byName = Object.create(null), cache = Object.create(null);
    function identity(item) { if (!Number.isSafeInteger(item.gameItemId)) throw new Error('크리스타 게임 ID가 필요합니다.'); return String(item.gameItemId); }
    (items || []).forEach(function (item) {
      byId[identity(item)] = item;
      [item.name].concat(item.aliases || [],Object.values(item.names || {})).filter(Boolean).forEach(function (name) {
        var key = normalize(name);
        if (byName[key] === undefined) byName[key] = item;
        else if (byName[key] !== item) byName[key] = null;
      });
    });
    function resolve(value) { return byId[String(value)] || byName[normalize(value)] || null; }
    function lineage(item) {
      if (!item) return [];
      item = byId[identity(item)] || item;
      var id = identity(item); if (cache[id]) return cache[id];
      var result = [], seen = new Set();
      while (item && !seen.has(identity(item))) {
        var key = identity(item); seen.add(key); result.push(key); item = byId[String(item.previousId)];
      }
      return cache[id] = Object.freeze(result);
    }
    function conflict(left,right) {
      if (!left || !right) return false;
      var rightIds = new Set(lineage(right));
      return lineage(left).some(function (id) { return rightIds.has(id); });
    }
    function ancestorRelated(left,right) {
      return Boolean(left && right && (lineage(left).indexOf(identity(right)) >= 0 || lineage(right).indexOf(identity(left)) >= 0));
    }
    function obsoleteIds() {
      var result = Object.create(null);
      Object.values(byId).forEach(function (item) { lineage(item).slice(1).forEach(function (id) { result[id] = true; }); });
      return result;
    }
    return Object.freeze({byId:byId,resolve:resolve,lineage:lineage,conflict:conflict,ancestorRelated:ancestorRelated,obsoleteIds:obsoleteIds});
  }
  var api = Object.freeze({createIndex:createIndex});
  
  export const crystaIdentity = api;

