import assert from 'node:assert/strict';
import {DatabaseSync} from 'node:sqlite';
import {randomUUID} from 'node:crypto';
import {mkdtemp,readFile,writeFile} from 'node:fs/promises';
import {resolve} from 'node:path';
import {createInventoryStore} from '../../../server/inventory-store.mjs';
import {createLegacyRecords,planLegacyRecords,migrateLegacyRecords} from '../../../server/legacy-records.mjs';
import {legacyPayload,legacyToInventory} from '../../../server/account-records.mjs';
import {migrateDatabase} from '../../migrate-records.mjs';

const directory=await mkdtemp(resolve('build/tmp/record-migration-')),database=resolve(directory,'source.sqlite');
function schema(db) {
  db.exec(`PRAGMA foreign_keys=ON;
    CREATE TABLE users(id TEXT PRIMARY KEY);
    INSERT INTO users VALUES ('owner'),('other');
    CREATE TABLE records(id TEXT PRIMARY KEY,user_id TEXT NOT NULL REFERENCES users(id),kind TEXT NOT NULL,name TEXT NOT NULL,data TEXT NOT NULL,version INTEGER NOT NULL,updated_at TEXT NOT NULL);`);
}
const piece={type:'지팡이',attack:100,refinement:15,stability:60,options:[{key:'MATK',value:20}],crystas:[],lockedCrystaSlots:[]};
const item={schema:'toram.account-item.v1',slot:'mainWeapon',equipment:piece};
let db=new DatabaseSync(database);schema(db);
const original=[];
function add(kind,data,{owner='owner',name='보관한 구성',version=7}={}) {
  const row={id:randomUUID(),user_id:owner,kind,name,data:typeof data==='string'?data:JSON.stringify(data),version,updated_at:'2026-10-27T01:02:03.000Z'};
  db.prepare('INSERT INTO records VALUES (?,?,?,?,?,?,?)').run(row.id,row.user_id,row.kind,row.name,row.data,row.version,row.updated_at);original.push(row);return row;
}
for(const file of ['마법) 인힘 마도구 - pelio s.json','마법) 지팡이 크법 세팅 - pelio s.json','미완성 서포터 세팅 (톱스타 포툼 없음) - oo o.json','서폿) 그냥 지금 세팅 - pelio s.json']) {
  const saved=JSON.parse(await readFile(new URL('../../../samples/'+file,import.meta.url),'utf8'));
  const converted=legacyToInventory({kind:'builds',name:file,data:saved});
  assert.deepEqual(legacyPayload(converted.object,converted.metadata),saved,'Real saved samples convert without loss');
  add('builds',saved,{name:file});
}
const equipment=add('items',item),other=add('items',item,{owner:'other'});
add('items','not JSON');
add('favorites',{...item,equipment:{...piece,catalogItem:{gameItemId:123}}});
add('builds',{format:'toram-auto-build-document',schemaVersion:1});
const sourceRows=db.prepare('SELECT * FROM records ORDER BY id').all().map(row=>({...row}));db.close();

const reportPath=resolve(directory,'plan.json');
const dry=await migrateDatabase(database,{reportPath});
assert.deepEqual(JSON.parse(await readFile(reportPath,'utf8')).counts,dry.counts);
await assert.rejects(migrateDatabase(database,{apply:true,backupPath:resolve(directory,'unused.sqlite'),reportPath}),{code:'EEXIST'},'An existing report fails before any database mutation');
assert.equal(dry.mode,'dry-run');assert.deepEqual(dry.counts,{ready:6,skipped:0,blocked:3});
db=new DatabaseSync(database,{readOnly:true});
assert.equal(db.prepare("SELECT count(*) AS total FROM sqlite_master WHERE name='record_links'").get().total,0,'Dry-run creates no schema');
assert.deepEqual(db.prepare('SELECT * FROM records ORDER BY id').all().map(row=>({...row})),sourceRows);db.close();
const occupied=resolve(directory,'existing-backup.sqlite');await writeFile(occupied,'keep');
await assert.rejects(migrateDatabase(database,{apply:true,backupPath:occupied}),{code:'EEXIST'});
assert.equal(await readFile(occupied,'utf8'),'keep');
const backupPath=resolve(directory,'before.sqlite');
const applied=await migrateDatabase(database,{apply:true,backupPath});
assert.deepEqual(applied.counts,dry.counts);
const restored=new DatabaseSync(backupPath,{readOnly:true});
assert.deepEqual(restored.prepare('SELECT * FROM records ORDER BY id').all().map(row=>({...row})),sourceRows);
assert.equal(restored.prepare("SELECT count(*) AS total FROM sqlite_master WHERE name='record_links'").get().total,0,'Backup is the pre-migration database');restored.close();

db=new DatabaseSync(database);db.exec('PRAGMA foreign_keys=ON');
const inventory=createInventoryStore(db),legacy=createLegacyRecords(db,inventory);
assert.deepEqual(db.prepare('SELECT * FROM records ORDER BY id').all().map(row=>({...row})),sourceRows,'No legacy row is deleted or overwritten');
assert.deepEqual(db.prepare('PRAGMA foreign_key_check').all(),[]);
for(const entry of applied.entries.filter(row=>row.status==='ready')) {
  const old=original.find(row=>row.id===entry.legacyId),record=inventory.get(old.user_id,entry.inventoryId);
  assert.equal(record.revision,old.version);assert.equal(record.updatedAt,old.updated_at);
  assert.deepEqual(legacy.get(old.user_id,old.kind,old.id).data,JSON.parse(old.data));
  assert.ok(!JSON.stringify(record).includes(old.id),'Private legacy IDs live only in the mapping ledger');
}
assert.equal(planLegacyRecords(db).counts.skipped,6);
assert.equal(migrateLegacyRecords(db,inventory).counts.ready,0,'Rerunning never creates a second object');
const id=applied.entries.find(row=>row.legacyId===equipment.id).inventoryId;
assert.throws(()=>legacy.get('other','items',equipment.id),error=>error.status===404);
assert.throws(()=>inventory.get('other',id),error=>error.status===404);
const current=inventory.get('owner',id);
assert.deepEqual(current.data.equipment.crystas,['',''],'Historical zero-length arrays have an explicit empty-slot meaning');
inventory.update('owner',id,{type:current.type,schemaVersion:1,name:'수정한 지팡이',revision:current.revision,data:{...current.data,equipment:{...current.data.equipment,attack:222}}});
const shared=legacy.get('owner','items',equipment.id);
assert.equal(shared.version,8);assert.equal(shared.data.equipment.attack,222);assert.deepEqual(shared.data.equipment.crystas,[]);
assert.throws(()=>legacy.remove('owner','items',equipment.id,{version:7}),error=>error.status===409);
legacy.remove('owner','items',equipment.id,{version:8});
assert.throws(()=>legacy.get('owner','items',equipment.id),error=>error.status===404);
migrateLegacyRecords(db,inventory);
assert.throws(()=>inventory.get('owner',id),error=>error.status===404,'A tombstone prevents resurrection from the preserved archive');

const changed=original.find(row=>row.id===other.id);
db.prepare('UPDATE records SET name=? WHERE id=?').run('externally changed',changed.id);
assert.equal(planLegacyRecords(db).entries.find(row=>row.legacyId===changed.id).status,'blocked','Changed mapped sources are never silently overwritten');
const collision=add('items',item,{name:'collision'}),collisionPlan=planLegacyRecords(db).entries.find(row=>row.legacyId===collision.id);
inventory.importRecord('other',{type:'equipment',schemaVersion:1,name:'keep existing',data:{slot:'mainWeapon',equipment:{...piece,crystas:['',''],lockedCrystaSlots:[false,false]}}},{id:collisionPlan.inventoryId,revision:1,createdAt:'old',updatedAt:'old'});
assert.equal(planLegacyRecords(db).entries.find(row=>row.legacyId===collision.id).status,'blocked');
assert.equal(inventory.get('other',collisionPlan.inventoryId).name,'keep existing');db.close();

// Fail the second write after the first real insert to prove rollback of objects and mappings together.
const rollback=new DatabaseSync(':memory:');schema(rollback);
for(let index=0;index<2;index++) rollback.prepare('INSERT INTO records VALUES (?,?,?,?,?,?,?)').run(randomUUID(),'owner','items','fixture',JSON.stringify(item),1,'old');
const rollbackStore=createInventoryStore(rollback);let writes=0;
assert.throws(()=>migrateLegacyRecords(rollback,{importRecord(...args){if(++writes===2)throw new Error('injected failure');return rollbackStore.importRecord(...args);}}),/injected failure/);
assert.equal(rollback.prepare('SELECT count(*) AS total FROM inventory_objects').get().total,0);
assert.equal(rollback.prepare('SELECT count(*) AS total FROM record_links').get().total,0);
assert.equal(rollback.prepare('SELECT count(*) AS total FROM records').get().total,2);rollback.close();
const grandfathered=new DatabaseSync(':memory:');schema(grandfathered);
const insertOld=grandfathered.prepare('INSERT INTO records VALUES (?,?,?,?,?,?,?)');
for(let index=0;index<201;index++) insertOld.run(randomUUID(),'owner','items','existing-'+index,JSON.stringify(item),1,'old');
const grandfatheredStore=createInventoryStore(grandfathered);
assert.equal(migrateLegacyRecords(grandfathered,grandfatheredStore).counts.ready,201,'Existing rows are never discarded to meet a new collection quota');
assert.equal(createLegacyRecords(grandfathered,grandfatheredStore).list('owner','items').length,201);
assert.throws(()=>createLegacyRecords(grandfathered,grandfatheredStore).create('owner','items','extra',item),error=>error.status===409,'The old per-kind quota is preserved');
const normal=grandfatheredStore.create('owner',{type:'equipment',schemaVersion:1,name:'new inventory',data:{slot:'mainWeapon',equipment:{...piece,crystas:['',''],lockedCrystaSlots:[false,false]}}});
assert.equal(normal.revision,1,'Backfill does not consume the independently existing inventory quota');grandfathered.close();
console.log('Record migration: PASS (4 real samples, dry-run/no schema writes, reserved backup + restore, stable ID map, idempotence, owner/revision gates, shared edits, deletion tombstones, blocked unknowns/collisions, transaction rollback)');
