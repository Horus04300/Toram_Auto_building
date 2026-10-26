import { randomUUID } from 'node:crypto';
import { INVENTORY_TYPES, fields, validateInventoryObject } from '../web/src/application/inventory-objects.mjs';
import { equipmentType, EQUIPMENT_TYPES } from '../web/src/application/equipment-object.mjs';
import { inventoryRules as rules } from './inventory-rules.mjs';
import { withRequestReceipt } from './request-receipts.mjs';

const fail = (status,code,message) => Object.assign(new Error(message),{status,apiCode:code});
const unavailable = () => fail(404,'SOURCE_UNAVAILABLE','원본이 비공개/삭제되어 접근할 수 없습니다.');
function text(value,max,label,optional = false) {
  if (optional && (value === undefined || value === null)) return '';
  if (typeof value !== 'string' || value.length > max || (!optional && !value.trim()) || /[\x00-\x08\x0b\x0c\x0e-\x1f\x7f]/u.test(value)) throw fail(400,'INVALID_INPUT',`${label} 입력을 확인하세요.`);
  return value.trim();
}
function checkedFields(value,allowed) { try { fields(value,allowed); } catch (error) { throw fail(400,'INVALID_INPUT',error.message); } }
function revision(value,expected) {
  if (!Number.isSafeInteger(value) || value < 1) throw fail(400,'INVALID_REVISION','수정 번호가 필요합니다.');
  if (value !== expected) throw fail(409,'REVISION_CONFLICT','원본이나 게시글이 변경됐습니다. 최신 내용을 확인한 뒤 다시 시도하세요.');
}
function publicSnapshot(value) {
  if (Array.isArray(value)) return value.map(publicSnapshot);
  if (!value || typeof value !== 'object') return value;
  return Object.fromEntries(Object.entries(value).map(([key,item]) => [key,key === 'provenance' && Array.isArray(item) ? item.filter(source => source.kind !== 'inventory').map(publicSnapshot) : publicSnapshot(item)]));
}
function catalogVersions(value,found = new Set()) {
  if (value && typeof value === 'object') {
    if (['toram.equipment-item.v1','toram.consumable-buff.v1'].includes(value.schema)) found.add(value.cacheVersion);
    for (const item of Object.values(value)) catalogVersions(item,found);
  }
  return [...found].sort();
}
function weapon(snapshot) {
  const item = snapshot.type === 'equipment' && snapshot.data.slot === 'mainWeapon' ? snapshot.data
    : (snapshot.type === 'equipment_set' ? snapshot.data : snapshot.type === 'build' ? snapshot.data.equipment?.data : null)?.slots.mainWeapon?.data;
  return item ? equipmentType(item) : '';
}

export function createPostStore(db,inventory) {
  db.exec(`CREATE TABLE IF NOT EXISTS posts (
    id TEXT PRIMARY KEY, author_id TEXT NOT NULL REFERENCES users(id), content_type TEXT NOT NULL,
    title TEXT NOT NULL, description TEXT NOT NULL, visibility TEXT NOT NULL CHECK(visibility IN ('public','private','deleted')),
    latest_release_id TEXT, revision INTEGER NOT NULL, equipment_type TEXT NOT NULL,
    created_at TEXT NOT NULL, updated_at TEXT NOT NULL, deleted_at TEXT,
    FOREIGN KEY(latest_release_id,id) REFERENCES post_releases(id,post_id) DEFERRABLE INITIALLY DEFERRED);
    CREATE TABLE IF NOT EXISTS post_releases (
      id TEXT PRIMARY KEY, post_id TEXT NOT NULL REFERENCES posts(id), release_number INTEGER NOT NULL,
      name TEXT NOT NULL, change_notes TEXT NOT NULL, object_type TEXT NOT NULL, schema_version INTEGER NOT NULL,
      snapshot_json TEXT NOT NULL, game_version TEXT NOT NULL, catalog_version TEXT NOT NULL,
      calculation_rules_version TEXT, published_at TEXT NOT NULL, UNIQUE(post_id,release_number), UNIQUE(id,post_id));
    CREATE INDEX IF NOT EXISTS posts_public ON posts(visibility,content_type,updated_at DESC,id);
    CREATE INDEX IF NOT EXISTS posts_author ON posts(author_id,updated_at DESC,id);
    CREATE INDEX IF NOT EXISTS releases_history ON post_releases(post_id,release_number DESC);
    CREATE TABLE IF NOT EXISTS post_favorites (
      user_id TEXT NOT NULL REFERENCES users(id) ON DELETE CASCADE, post_id TEXT NOT NULL REFERENCES posts(id), created_at TEXT NOT NULL,
      PRIMARY KEY(user_id,post_id));
    CREATE INDEX IF NOT EXISTS favorites_post ON post_favorites(post_id);
    CREATE TABLE IF NOT EXISTS post_tags (post_id TEXT NOT NULL REFERENCES posts(id),tag TEXT NOT NULL,PRIMARY KEY(post_id,tag));
    CREATE INDEX IF NOT EXISTS tags_search ON post_tags(tag,post_id);`);
  const select = `SELECT p.*,u.nickname,
    (SELECT count(*) FROM post_favorites f WHERE f.post_id=p.id) AS favorite_count,
    EXISTS(SELECT 1 FROM post_favorites f WHERE f.post_id=p.id AND f.user_id=?) AS favorited
    FROM posts p JOIN users u ON u.id=p.author_id`;
  function postRow(id,viewer,manage = false) {
    const value = db.prepare(select + ' WHERE p.id=?').get(viewer || '',id);
    if (!value || value.visibility !== 'public' && !(manage && value.author_id === viewer)) throw unavailable();
    return value;
  }
  function owned(id,owner) { const value = postRow(id,owner,true); if (value.author_id !== owner || value.visibility === 'deleted') throw unavailable(); return value; }
  function releaseRow(value,withSnapshot = true) {
    return {id:value.id,number:value.release_number,name:value.name,changeNotes:value.change_notes,type:value.object_type,
      schemaVersion:value.schema_version,gameVersion:value.game_version,catalogVersions:JSON.parse(value.catalog_version),calculationRulesVersion:value.calculation_rules_version,publishedAt:value.published_at,
      ...(withSnapshot ? {snapshot:JSON.parse(value.snapshot_json)} : {})};
  }
  function present(value,viewer) {
    return {id:value.id,title:value.title,description:value.description,type:value.content_type,visibility:value.visibility,revision:value.revision,
      author:{nickname:value.nickname},isAuthor:value.author_id === viewer,favoriteCount:value.favorite_count,favorited:Boolean(value.favorited),equipmentType:value.equipment_type,
      tags:db.prepare('SELECT tag FROM post_tags WHERE post_id=? ORDER BY tag').all(value.id).map(row => row.tag),createdAt:value.created_at,updatedAt:value.updated_at,
      latestRelease:releaseRow(db.prepare('SELECT * FROM post_releases WHERE id=? AND post_id=?').get(value.latest_release_id,value.id),false)};
  }
  function get(id,viewer,number) {
    const value = postRow(id,viewer,true), post = present(value,viewer);
    const release = number === undefined ? db.prepare('SELECT * FROM post_releases WHERE id=? AND post_id=?').get(value.latest_release_id,id)
      : Number.isSafeInteger(number) && number > 0 ? db.prepare('SELECT * FROM post_releases WHERE post_id=? AND release_number=?').get(id,number) : null;
    if (!release) throw unavailable();
    return {...post,release:releaseRow(release)};
  }
  function tags(value = []) {
    if (!Array.isArray(value) || value.length > 10) throw fail(400,'INVALID_INPUT','태그는 최대 10개입니다.');
    return [...new Set(value.map(item => text(item,24,'태그')))];
  }
  function source(owner,input) {
    checkedFields(input,['source','scope','release','postRevision','title','description','tags']);
    checkedFields(input.source,['objectId','revision']); checkedFields(input.release,['name','changeNotes','gameVersion']);
    if (typeof input.source.objectId !== 'string' || !/^[a-f0-9-]{36}$/u.test(input.source.objectId)) throw fail(400,'INVALID_INPUT','공개할 원본을 선택하세요.');
    const record = inventory.get(owner,input.source.objectId); revision(input.source.revision,record.revision);
    const scope = input.scope || 'whole';
    let snapshot = {type:record.type,schemaVersion:1,name:record.name,data:record.data,provenance:record.provenance};
    if (scope !== 'whole') {
      if (!['status','equipment','skills','consumables','combos'].includes(scope) || record.type !== 'build' || !record.data[scope]) throw fail(400,'INVALID_SCOPE','이 구성에서 공개할 수 없는 영역입니다.');
      snapshot = record.data[scope];
    }
    snapshot = publicSnapshot(snapshot);
    validateInventoryObject(snapshot.type,snapshot.data,rules);
    return {snapshot,name:text(input.release.name,80,'릴리스 이름'),notes:text(input.release.changeNotes,2000,'변경 설명',true),gameVersion:text(input.release.gameVersion,80,'게임 버전',true)};
  }
  function addRelease(id,data,number) {
    const releaseId = randomUUID(), now = new Date().toISOString();
    db.prepare('INSERT INTO post_releases VALUES (?,?,?,?,?,?,?,?,?,?,?,?)').run(releaseId,id,number,data.name,data.notes,data.snapshot.type,1,JSON.stringify(data.snapshot),data.gameVersion,JSON.stringify(catalogVersions(data.snapshot)),null,now);
    db.prepare('UPDATE posts SET latest_release_id=?,revision=revision+1,equipment_type=?,updated_at=? WHERE id=?').run(releaseId,weapon(data.snapshot),now,id);
  }
  function publish(owner,input,key,id) {
    return withRequestReceipt(db,owner,key,input,() => {
      const previous = id ? owned(id,owner) : null;
      if (previous) revision(input.postRevision,previous.revision);
      const data = source(owner,input);
      if (previous && data.snapshot.type !== previous.content_type) throw fail(400,'TYPE_MISMATCH','게시글의 구성 종류를 바꿀 수 없습니다. 새 게시글로 공개하세요.');
      if (!previous) {
        const now = new Date().toISOString(); id = randomUUID();
        db.prepare('INSERT INTO posts VALUES (?,?,?,?,?,?,?,?,?,?,?,?)').run(id,owner,data.snapshot.type,text(input.title,80,'제목'),text(input.description,4000,'소개',true),'public',null,0,'',now,now,null);
        for (const tag of tags(input.tags)) db.prepare('INSERT INTO post_tags VALUES (?,?)').run(id,tag);
      } else if (['title','description','tags'].some(field => Object.hasOwn(input,field))) throw fail(400,'INVALID_INPUT','제목·소개·태그 수정은 게시글 관리에서 저장하세요.');
      const number = previous ? db.prepare('SELECT max(release_number) AS number FROM post_releases WHERE post_id=?').get(id).number + 1 : 1;
      addRelease(id,data,number); return get(id,owner);
    },id ? 'release:' + id : 'post');
  }
  function list(viewer,params,mine = false) {
    const favorites = params.get('favorites') || '';
    if (favorites === '1' && !viewer) throw fail(401,'AUTH_REQUIRED','내 즐겨찾기는 로그인 후 볼 수 있습니다.');
    const type = params.get('type') || '', q = (params.get('q') || '').trim(), tag = params.get('tag') || '', subtype = params.get('equipmentType') || '', sort = params.get('sort') || 'recent';
    const page = Number(params.get('page') || 1), pageSize = Number(params.get('pageSize') || 6);
    if ([...params.keys()].some(key => !['type','q','tag','equipmentType','sort','page','pageSize','favorites'].includes(key)) || !['','0','1'].includes(favorites) || type && !Object.hasOwn(INVENTORY_TYPES,type)
      || q.length > 80 || tag.length > 24 || subtype && !Object.hasOwn(EQUIPMENT_TYPES,subtype) || !['recent','favorites'].includes(sort)
      || !Number.isSafeInteger(page) || page < 1 || page > 100000 || !Number.isSafeInteger(pageSize) || pageSize < 1 || pageSize > 50) throw fail(400,'INVALID_QUERY','검색·분류·페이지 조건을 확인하세요.');
    const where = (mine ? 'p.author_id=?' : "p.visibility='public'") + (type ? ' AND p.content_type=?' : '')
      + (q ? ' AND (instr(lower(p.title),lower(?))>0 OR instr(lower(p.description),lower(?))>0)' : '')
      + (tag ? ' AND EXISTS(SELECT 1 FROM post_tags t WHERE t.post_id=p.id AND t.tag=?)' : '') + (subtype ? ' AND p.equipment_type=?' : '')
      + (favorites === '1' ? ' AND EXISTS(SELECT 1 FROM post_favorites f WHERE f.post_id=p.id AND f.user_id=?)' : '');
    const values = [...(mine ? [viewer] : []),...(type ? [type] : []),...(q ? [q,q] : []),...(tag ? [tag] : []),...(subtype ? [subtype] : []),...(favorites === '1' ? [viewer] : [])];
    const total = db.prepare('SELECT count(*) AS total FROM posts p WHERE ' + where).get(...values).total;
    const order = sort === 'favorites' ? 'favorite_count DESC,p.updated_at DESC,p.id' : 'p.updated_at DESC,p.id';
    const items = db.prepare(select + ' WHERE ' + where + ' ORDER BY ' + order + ' LIMIT ? OFFSET ?').all(viewer || '',...values,pageSize,(page - 1) * pageSize).map(value => present(value,viewer));
    return {items,page,pageSize,total};
  }
  return Object.freeze({get,list,publish,
    history(id,viewer,params) {
      postRow(id,viewer,true);
      const page = Number(params.get('page') || 1), pageSize = 6;
      if ([...params.keys()].some(key => key !== 'page') || !Number.isSafeInteger(page) || page < 1 || page > 100000) throw fail(400,'INVALID_QUERY','이력 페이지를 확인하세요.');
      const total = db.prepare('SELECT count(*) AS total FROM post_releases WHERE post_id=?').get(id).total;
      return {items:db.prepare('SELECT * FROM post_releases WHERE post_id=? ORDER BY release_number DESC LIMIT ? OFFSET ?').all(id,pageSize,(page - 1) * pageSize).map(value => releaseRow(value,false)),page,pageSize,total};
    },
    manage(owner,id,input) {
      checkedFields(input,['revision','title','description','tags','visibility']);
      const value = owned(id,owner); revision(input.revision,value.revision);
      const visibility = input.visibility ?? value.visibility;
      if (!['public','private','deleted'].includes(visibility)) throw fail(400,'INVALID_INPUT','공개 상태를 확인하세요.');
      const nextTags = input.tags === undefined ? null : tags(input.tags), title = input.title === undefined ? value.title : text(input.title,80,'제목'), description = input.description === undefined ? value.description : text(input.description,4000,'소개',true);
      db.exec('BEGIN IMMEDIATE');
      try {
        const changed = db.prepare('UPDATE posts SET title=?,description=?,visibility=?,revision=revision+1,updated_at=?,deleted_at=? WHERE id=? AND author_id=? AND revision=?').run(title,description,visibility,new Date().toISOString(),visibility === 'deleted' ? new Date().toISOString() : null,id,owner,input.revision);
        if (!changed.changes) throw fail(409,'REVISION_CONFLICT','게시글이 변경됐습니다. 최신 내용을 확인하세요.');
        if (nextTags) { db.prepare('DELETE FROM post_tags WHERE post_id=?').run(id); for (const tag of nextTags) db.prepare('INSERT INTO post_tags VALUES (?,?)').run(id,tag); }
        const result = get(id,owner); db.exec('COMMIT'); return result;
      } catch (error) { db.exec('ROLLBACK'); throw error; }
    },
    favorite(owner,id,enabled) {
      const value = postRow(id,owner);
      if (enabled) db.prepare('INSERT INTO post_favorites VALUES (?,?,?) ON CONFLICT DO NOTHING').run(owner,id,new Date().toISOString());
      else db.prepare('DELETE FROM post_favorites WHERE user_id=? AND post_id=?').run(owner,id);
      return present(postRow(value.id,owner),owner);
    },
    copy(owner,input,key) {
      checkedFields(input,['postId','releaseNumber','name']);
      if (typeof input.postId !== 'string' || !/^[a-f0-9-]{36}$/u.test(input.postId) || !Number.isSafeInteger(input.releaseNumber) || input.releaseNumber < 1) throw fail(400,'INVALID_INPUT','복사할 릴리스를 선택하세요.');
      return withRequestReceipt(db,owner,key,input,() => {
        const value = get(input.postId,owner,input.releaseNumber);
        const snapshot = value.release.snapshot;
        return inventory.create(owner,{type:snapshot.type,schemaVersion:1,name:input.name === undefined ? snapshot.name : text(input.name,80,'사본 이름'),data:snapshot.data},[{kind:'release',postId:input.postId,releaseNumber:input.releaseNumber}]);
      },'copy');
    }
  });
}
