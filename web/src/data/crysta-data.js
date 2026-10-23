// Compatibility view of the single ID-keyed catalog loaded by app-entry.mjs.
const crystaDataJson = (function (root) {
  'use strict';
  var records = root.TORAM_CRYSTA_CATALOG_DATA;
  if (!records || !Object.keys(records).length) throw new Error('크리스타 ID 데이터가 준비되지 않았습니다.');
  function name(item) { return item.aliases[0] || item.names.kr || '#' + item.gameItemId; }
  function condition(when) {
    if (when.kind === 'either-weapon-slot') return {eitherWeapon:when.types.slice()};
    if (when.kind === 'both-weapon-slots') return {main:when.main,sub:when.sub};
    if (when.kind === 'body-battle-customize') return {armor:when.armor};
    throw new Error('지원하지 않는 크리스타 조건입니다.');
  }
  var byId = Object.create(null);
  var aliasIds = Object.create(null);
  Object.values(records).filter(function (item) { return item.category && item.fullyMapped; }).forEach(function (item) {
    item.aliases.concat(Object.values(item.names).filter(Boolean)).forEach(function (alias) {
      var key = alias.replace(/\s+/g, '').toLowerCase();
      if (aliasIds[key] === undefined) aliasIds[key] = item.gameItemId;
      else if (aliasIds[key] !== item.gameItemId) aliasIds[key] = null;
    });
  });
  var items = Object.values(records).filter(function (item) { return item.category && item.fullyMapped; }).map(function (item) {
    var entry = {gameItemId:item.gameItemId,name:name(item),category:item.category,stats:item.stats,
      aliases:item.aliases.concat(Object.values(item.names).filter(Boolean)).filter(function (alias) {
        return aliasIds[alias.replace(/\s+/g, '').toLowerCase()] === item.gameItemId;
      }),
      condStats:item.conditionalStats.map(function (group) { return {cond:condition(group.when),stats:group.stats}; })};
    if (item.previousId !== null) entry.prev = name(records[item.previousId]);
    byId[item.gameItemId] = Object.freeze(entry);
    return entry;
  });
  root.ToramCrystaCatalog = Object.freeze({records:records,getById:function (id) { return byId[id] || null; }});
  return Object.freeze(items);
}(typeof window !== 'undefined' ? window : globalThis));
