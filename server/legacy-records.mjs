import {createHash,randomUUID} from 'node:crypto';
import {legacyPayload,legacyToInventory,RECORD_KINDS} from './account-records.mjs';

const hash=value=>createHash('sha256').update(value).digest('hex');
const fail=(status,message)=>Object.assign(new Error(message),{status});
const exists=(db,table)=>Boolean(db.prepare('SELECT 1 FROM sqlite_master WHERE type=? AND name=?').get('table',table));
function fingerprint(row) {return hash(JSON.stringify([row.id,row.user_id,row.kind,row.name,row.data,row.version,row.updated_at]));}
function targetId(row) {
  const bytes=Buffer.from(hash('toram-record-inventory-v1\0'+row.user_id+'\0'+row.kind+'\0'+row.id).slice(0,32),'hex');
  bytes[6]=(bytes[6]&15)|128;bytes[8]=(bytes[8]&63)|128;
  const hex=bytes.toString('hex');return [hex.slice(0,8),hex.slice(8,12),hex.slice(12,16),hex.slice(16,20),hex.slice(20)].join('-');
}
function link(db,row,id,metadata) {
  db.prepare('INSERT INTO record_links VALUES (?,?,?,?,?,?)').run(row.id,row.user_id,row.kind,id,fingerprint(row),JSON.stringify(metadata));
}
function wire(record,id,metadata) {return {id,name:record.name,version:record.revision,updatedAt:record.updatedAt,data:legacyPayload(record,metadata)};}

// Current writes have one owner. The old URLs are projections plus read compatibility for untouched archives.
export function createLegacyRecords(db,inventory) {
  function list(owner,kind) {
    const current=db.prepare('SELECT l.legacy_id AS id,i.name,i.revision AS version,i.updated_at AS updatedAt FROM record_links l JOIN inventory_objects i ON i.id=l.inventory_id AND i.owner_id=l.owner_id WHERE l.owner_id=? AND l.kind=?').all(owner,kind);
    const archived=db.prepare('SELECT id,name,version,updated_at AS updatedAt FROM records r WHERE user_id=? AND kind=? AND NOT EXISTS (SELECT 1 FROM record_links l WHERE l.legacy_id=r.id)').all(owner,kind);
    return [...current,...archived].sort((a,b)=>a.updatedAt===b.updatedAt ? a.id===b.id?0:a.id<b.id?-1:1 : a.updatedAt>b.updatedAt?-1:1);
  }
  function get(owner,kind,id) {
    const mapped=db.prepare('SELECT * FROM record_links WHERE legacy_id=? AND owner_id=? AND kind=?').get(id,owner,kind);
    if(mapped) {
      if(!mapped.inventory_id) throw fail(404,'저장 항목을 찾을 수 없습니다.');
      return wire(inventory.get(owner,mapped.inventory_id),id,JSON.parse(mapped.metadata_json));
    }
    const old=db.prepare('SELECT * FROM records WHERE id=? AND user_id=? AND kind=?').get(id,owner,kind);
    if(!old) throw fail(404,'저장 항목을 찾을 수 없습니다.');
    return {id:old.id,name:old.name,version:old.version,updatedAt:old.updated_at,data:JSON.parse(old.data)};
  }
  function create(owner,kind,name,data) {
    let converted;
    try {converted=legacyToInventory({kind,name,data});} catch(error) {throw fail(400,error.message);}
    db.exec('BEGIN IMMEDIATE');
    try {
      if(list(owner,kind).length>=200) throw fail(409,'보관함은 각각 200개까지 저장할 수 있습니다.');
      const id=randomUUID(),now=new Date().toISOString();
      const record=inventory.importRecord(owner,converted.object,{id,revision:1,createdAt:now,updatedAt:now});
      link(db,{id,user_id:owner,kind,name,data:JSON.stringify(data),version:1,updated_at:now},id,converted.metadata);
      db.exec('COMMIT');return {id:record.id,name:record.name,version:record.revision,updatedAt:record.updatedAt};
    } catch(error) {db.exec('ROLLBACK');throw error;}
  }
  function remove(owner,kind,id,input) {
    const current=get(owner,kind,id);
    if(input.version!==current.version) throw fail(409,'저장 목록이 변경됐습니다. 모달을 다시 열어 주세요.');
    const mapped=db.prepare('SELECT inventory_id FROM record_links WHERE legacy_id=? AND owner_id=? AND kind=?').get(id,owner,kind);
    if(mapped) return inventory.remove(owner,mapped.inventory_id,{revision:input.version});
    if(!db.prepare('DELETE FROM records WHERE id=? AND user_id=? AND kind=? AND version=?').run(id,owner,kind,input.version).changes) throw fail(409,'저장 목록이 변경됐습니다. 다시 확인하세요.');
    return {ok:true};
  }
  return Object.freeze({list,get,create,remove});
}

export function planLegacyRecords(db) {
  const entries=[];
  if(!exists(db,'records')) return {counts:{ready:0,skipped:0,blocked:0},entries};
  for(const row of db.prepare('SELECT * FROM records ORDER BY id').iterate()) {
    const entry={legacyId:row.id,ownerId:row.user_id,kind:row.kind,inventoryId:targetId(row),status:'ready'};
    try {
      const mapped=exists(db,'record_links')&&db.prepare('SELECT * FROM record_links WHERE legacy_id=?').get(row.id);
      if(mapped) {
        if(mapped.owner_id!==row.user_id||mapped.kind!==row.kind||mapped.source_sha256!==fingerprint(row)) throw new Error('Previously mapped source changed; manual review required.');
        entry.status='skipped';entry.inventoryId=mapped.inventory_id;entries.push(entry);continue;
      }
      if(!RECORD_KINDS.has(row.kind)||!Number.isSafeInteger(row.version)||row.version<1||typeof row.updated_at!=='string'||row.name!==row.name.trim()) throw new Error('Legacy identity, version or name needs review.');
      if(!db.prepare('SELECT 1 FROM users WHERE id=?').get(row.user_id)) throw new Error('Legacy owner is missing.');
      if(exists(db,'inventory_objects')&&db.prepare('SELECT 1 FROM inventory_objects WHERE id=?').get(entry.inventoryId)) throw new Error('Target inventory ID already exists; no overwrite allowed.');
      legacyToInventory({kind:row.kind,name:row.name,data:JSON.parse(row.data)});
    } catch(error) {entry.status='blocked';entry.reason=error.message;}
    entries.push(entry);
  }
  return {counts:Object.fromEntries(['ready','skipped','blocked'].map(status=>[status,entries.filter(row=>row.status===status).length])),entries};
}

export function migrateLegacyRecords(db,inventory) {
  db.exec('BEGIN IMMEDIATE');
  try {
    const report=planLegacyRecords(db);
    for(const entry of report.entries.filter(row=>row.status==='ready')) {
      const row=db.prepare('SELECT * FROM records WHERE id=? AND user_id=?').get(entry.legacyId,entry.ownerId);
      const converted=legacyToInventory({kind:row.kind,name:row.name,data:JSON.parse(row.data)});
      inventory.importRecord(row.user_id,converted.object,{id:entry.inventoryId,revision:row.version,createdAt:row.updated_at,updatedAt:row.updated_at});
      link(db,row,entry.inventoryId,converted.metadata);
    }
    db.exec('COMMIT');return report;
  } catch(error) {db.exec('ROLLBACK');throw error;}
}
