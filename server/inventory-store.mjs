import { randomUUID } from 'node:crypto';
import { withRequestReceipt } from './request-receipts.mjs';
import { equipmentType, EQUIPMENT_TYPES, EQUIPMENT_SLOTS } from '../web/src/application/equipment-object.mjs';
import { INVENTORY_TYPES, validateInventoryObject, validateProvenance, fields } from '../web/src/application/inventory-objects.mjs';
import { mergeInventoryObjects } from '../web/src/application/inventory-merge.mjs';
import { inventoryRules as rules } from './inventory-rules.mjs';
import { isConsumableGroupId } from '../web/src/application/item-catalog.mjs';

const fail = (status, code, message) => Object.assign(new Error(message), { status, apiCode:code });
function catalogSources(data) {
  const sources = new Map();
  function visit(value) {
    if (!value || typeof value !== 'object') return;
    if (value.schema === 'toram.registlet.v1') {
      const source = {kind:'registlet-catalog',registletId:value.registletId,cacheVersion:value.cacheVersion,sourceSha256:value.sourceSha256};
      sources.set(JSON.stringify(source),source); return;
    }
    if (['toram.equipment-item.v1','toram.consumable-buff.v1'].includes(value.schema)) {
      const source = {kind:'catalog',gameItemId:value.gameItemId,cacheVersion:value.cacheVersion,sourceSha256:value.sourceSha256};
      sources.set(JSON.stringify(source),source); return;
    }
    for (const item of Object.values(value)) visit(item);
  }
  visit(data); return [...sources.values()];
}
function row(value) {
  return { id:value.id, type:value.type, name:value.name, schemaVersion:value.schema_version, revision:value.revision,
    equipmentType:value.equipment_type, createdAt:value.created_at, updatedAt:value.updated_at,
    ...(value.data_json ? { data:JSON.parse(value.data_json), provenance:JSON.parse(value.provenance_json) } : {}) };
}

export function validateInventoryInput(input) {
  if (!Object.hasOwn(INVENTORY_TYPES,input.type) || input.schemaVersion !== 1) throw fail(400, 'UNSUPPORTED_SCHEMA', '지원하지 않는 인벤토리 형식입니다.');
  if (typeof input.name !== 'string' || !input.name.trim() || input.name.trim().length > 80 || /[\x00-\x1f\x7f]/u.test(input.name)) throw fail(400, 'INVALID_INPUT', '이름은 1~80자로 입력하세요.');
  if (Object.keys(input).some(key => !['name','type','schemaVersion','data','revision'].includes(key))) throw fail(400, 'INVALID_INPUT', '지원하지 않는 요청 필드입니다.');
  try { validateInventoryObject(input.type,input.data,rules); }
  catch (error) { throw fail(400, input.type === 'equipment' ? 'INVALID_EQUIPMENT' : 'INVALID_OBJECT', error.message); }
}

export function createInventoryStore(db) {
  db.exec(`CREATE TABLE IF NOT EXISTS inventory_objects (
    id TEXT PRIMARY KEY, owner_id TEXT NOT NULL REFERENCES users(id) ON DELETE CASCADE,
    type TEXT NOT NULL, name TEXT NOT NULL, schema_version INTEGER NOT NULL, revision INTEGER NOT NULL,
    equipment_type TEXT NOT NULL, data_json TEXT NOT NULL, provenance_json TEXT NOT NULL,
    created_at TEXT NOT NULL, updated_at TEXT NOT NULL);
    CREATE INDEX IF NOT EXISTS inventory_owner ON inventory_objects(owner_id,type,updated_at DESC,id);
    CREATE INDEX IF NOT EXISTS inventory_equipment ON inventory_objects(owner_id,type,equipment_type,updated_at DESC,id);
    CREATE TABLE IF NOT EXISTS request_receipts (owner_id TEXT NOT NULL REFERENCES users(id) ON DELETE CASCADE,
      request_key TEXT NOT NULL, fingerprint TEXT NOT NULL, result_json TEXT NOT NULL, created_at TEXT NOT NULL,
      PRIMARY KEY(owner_id,request_key));
    CREATE TABLE IF NOT EXISTS record_links (legacy_id TEXT PRIMARY KEY,
      owner_id TEXT NOT NULL REFERENCES users(id) ON DELETE CASCADE, kind TEXT NOT NULL,
      inventory_id TEXT UNIQUE REFERENCES inventory_objects(id) ON DELETE SET NULL,
      source_sha256 TEXT NOT NULL, metadata_json TEXT NOT NULL);
    CREATE INDEX IF NOT EXISTS record_links_owner ON record_links(owner_id,kind);`);
  function get(owner, id) {
    const value = db.prepare('SELECT * FROM inventory_objects WHERE id=? AND owner_id=?').get(id, owner);
    if (!value) throw fail(404, 'OBJECT_UNAVAILABLE', '구성을 찾을 수 없거나 접근할 수 없습니다.');
    return row(value);
  }
  function checkRevision(input, current) {
    if (!Number.isSafeInteger(input.revision) || input.revision < 1) throw fail(400, 'INVALID_REVISION', '수정 번호가 필요합니다.');
    if (input.revision !== current.revision) throw fail(409, 'REVISION_CONFLICT', '다른 곳에서 수정된 구성입니다. 최신 내용을 확인한 뒤 다시 저장하세요.');
  }
  function validateMergeInput(input) {
    try {
      fields(input,['left','right','choices','name']);
      for (const source of [input.left,input.right]) { fields(source,['objectId','revision']); if (typeof source.objectId !== 'string' || !/^[a-f0-9-]{36}$/u.test(source.objectId) || !Number.isSafeInteger(source.revision) || source.revision < 1) throw new Error('원본 ID·수정 번호를 확인하세요.'); }
      if (input.name !== undefined && (typeof input.name !== 'string' || input.name.length > 80)) throw new Error('새 구성 이름을 확인하세요.');
      if (input.choices !== undefined) {
        if (!Array.isArray(input.choices) || input.choices.length > 200) throw new Error('병합 선택 목록을 확인하세요.');
        for (const choice of input.choices) { fields(choice,['unit','take']); if (typeof choice.unit !== 'string' || choice.unit.length > 100 || !['left','right'].includes(choice.take)) throw new Error('병합 선택을 확인하세요.'); }
      }
    } catch (error) { throw fail(400,'INVALID_MERGE',error.message); }
  }
  function create(owner, input, provenance, imported) {
    validateInventoryInput(input); provenance ||= catalogSources(input.data); validateProvenance(provenance);
    if (Buffer.byteLength(JSON.stringify(input)) > 1024 * 1024) throw fail(413,'BODY_TOO_LARGE','구성은 1 MiB 이하여야 합니다.');
    // Legacy scopes retain their existing quotas; backfilled objects do not consume the independent inventory quota.
    if (!imported && db.prepare('SELECT count(*) AS total FROM inventory_objects i WHERE owner_id=? AND type=? AND NOT EXISTS (SELECT 1 FROM record_links l WHERE l.inventory_id=i.id)').get(owner, input.type).total >= 200) throw fail(409, 'INVENTORY_LIMIT', '종류별로 200개까지 보관할 수 있습니다.');
    const id = imported?.id || randomUUID(), now = new Date().toISOString();
    if(imported && (!/^[a-f0-9-]{36}$/u.test(id)||!Number.isSafeInteger(imported.revision)||imported.revision<1||typeof imported.createdAt!=='string'||typeof imported.updatedAt!=='string')) throw fail(400,'INVALID_IMPORT','이관 식별자·수정 번호·시각을 확인하세요.');
    db.prepare('INSERT INTO inventory_objects VALUES (?,?,?,?,?,?,?,?,?,?,?)').run(id, owner, input.type, input.name.trim(), 1, imported?.revision || 1,
      input.type === 'equipment' ? equipmentType(input.data) : '', JSON.stringify(input.data), JSON.stringify(provenance), imported?.createdAt || now, imported?.updatedAt || now);
    return get(owner,id);
  }
  function preview(owner, input) {
    validateMergeInput(input);
    const sources = [input.left,input.right].map(source => { const record = get(owner,source.objectId); checkRevision(source,record); return record; });
    try {
      const result = mergeInventoryObjects(...sources,input.choices);
      if (result.complete) validateInventoryObject(result.type,result.result.data,rules);
      return result;
    } catch (error) { throw fail(400,'INVALID_MERGE',error.message); }
  }
  function merge(owner, input, key) {
    validateMergeInput(input);
    return withRequestReceipt(db,owner,key,input,() => {
      const result = preview(owner,input);
      if (!result.complete) throw fail(409,'MERGE_UNRESOLVED','남은 충돌을 선택하세요.');
      const record = create(owner,{...result.result,name:input.name},[input.left,input.right].map(source => ({kind:'inventory',objectId:source.objectId,revision:source.revision})));
      return record;
    });
  }
  return Object.freeze({ get, create, preview, merge,
    importRecord:(owner,input,identity)=>create(owner,input,undefined,identity),
    list(owner, params) {
      const type = params.get('type') || 'equipment';
      if ([...params.keys()].some(key => !['type','equipmentType','slot','treeId','skillCategory','buffGroupId','q','page','pageSize'].includes(key)) || !Object.hasOwn(INVENTORY_TYPES,type)) throw fail(400, 'INVALID_QUERY', '지원하지 않는 목록 조건입니다.');
      const subtype = params.get('equipmentType') || '', q = (params.get('q') || '').trim();
      const slot = params.get('slot') || '', treeId = params.get('treeId') || '', category = params.get('skillCategory') || '', buffGroup = params.get('buffGroupId') || '';
      if (slot && (type !== 'equipment' || !Object.hasOwn(EQUIPMENT_SLOTS,slot))
        || treeId && (type !== 'skill_tree' || !rules.trees.trees.some(tree => tree.id === treeId))
        || category && (type !== 'skill_tree' || !rules.trees.trees.some(tree => tree.category === category))
        || buffGroup && (type !== 'consumable' || !/^\d+$/u.test(buffGroup) || !isConsumableGroupId(Number(buffGroup)))) throw fail(400,'INVALID_QUERY','장비 부위·스킬트리·도핑 계열을 확인하세요.');
      const page = params.has('page') ? Number(params.get('page')) : 1, pageSize = params.has('pageSize') ? Number(params.get('pageSize')) : 6;
      if (!Number.isSafeInteger(page) || page < 1 || page > 100000 || !Number.isSafeInteger(pageSize) || pageSize < 1 || pageSize > 50
        || q.length > 80 || (subtype && (type !== 'equipment' || !Object.hasOwn(EQUIPMENT_TYPES, subtype)))) throw fail(400, 'INVALID_QUERY', '검색·분류·페이지 범위를 확인하세요.');
      let where = 'owner_id=? AND type=?' + (subtype ? ' AND equipment_type=?' : '') + (q ? ' AND instr(lower(name),lower(?))>0' : '');
      const values = [owner, type, ...(subtype ? [subtype] : []), ...(q ? [q] : [])];
      for (const [path,value] of [['slot',slot],['treeId',treeId],['selection.buffGroupId',buffGroup]]) if (value) {where += ' AND json_extract(data_json,?)=?'; values.push('$.' + path,path === 'selection.buffGroupId' ? Number(value) : value);}
      if (category) {
        const ids = rules.trees.trees.filter(tree => tree.category === category).map(tree => tree.id);
        where += ` AND json_extract(data_json,'$.treeId') IN (${ids.map(() => '?').join(',')})`; values.push(...ids);
      }
      const total = db.prepare('SELECT count(*) AS total FROM inventory_objects WHERE ' + where).get(...values).total;
      const items = db.prepare('SELECT id,type,name,schema_version,revision,equipment_type,created_at,updated_at FROM inventory_objects WHERE ' + where + ' ORDER BY updated_at DESC,id LIMIT ? OFFSET ?').all(...values, pageSize, (page - 1) * pageSize).map(row);
      return { items, page, pageSize, total };
    },
    update(owner, id, input) {
      const current = get(owner, id); checkRevision(input, current); validateInventoryInput(input);
      if (input.type !== current.type) throw fail(400,'TYPE_MISMATCH','저장된 구성의 종류를 바꿀 수 없습니다. 새 구성으로 저장하세요.');
      const result = db.prepare('UPDATE inventory_objects SET name=?,equipment_type=?,data_json=?,revision=revision+1,updated_at=? WHERE id=? AND owner_id=? AND revision=?').run(
        input.name.trim(), input.type === 'equipment' ? equipmentType(input.data) : '', JSON.stringify(input.data), new Date().toISOString(), id, owner, input.revision);
      if (!result.changes) throw fail(409, 'REVISION_CONFLICT', '저장하는 동안 장비가 변경됐습니다. 최신 내용을 확인하세요.');
      return get(owner, id);
    },
    remove(owner, id, input) {
      checkRevision(input, get(owner, id));
      if (!db.prepare('DELETE FROM inventory_objects WHERE id=? AND owner_id=? AND revision=?').run(id, owner, input.revision).changes) throw fail(409, 'REVISION_CONFLICT', '삭제하는 동안 장비가 변경됐습니다. 최신 내용을 확인하세요.');
      return { ok:true };
    }
  });
}
