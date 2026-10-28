import {crystaIdentity} from '../application/crysta-identity.js';
export let crystaCatalog;
export function initializeCrystaCatalog(records) {
  if (!records || !Object.keys(records).length) throw new Error('크리스타 ID 데이터가 준비되지 않았습니다.');
  const items = Object.values(records).filter(item => item.category && item.fullyMapped).map(item => ({...item,name:item.aliases[0] || item.names.kr || '#' + item.gameItemId}));
  const index = crystaIdentity.createIndex(items);
  crystaCatalog = Object.freeze({records,items:Object.freeze(items),getById:id => index.byId[id] || null,resolve:index.resolve,conflict:index.ancestorRelated});
  return crystaCatalog;
}
