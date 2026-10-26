import { createHash } from 'node:crypto';

function canonical(value) { return Array.isArray(value) ? value.map(canonical) : value && typeof value === 'object' ? Object.fromEntries(Object.keys(value).sort().map(key => [key,canonical(value[key])])) : value; }
export function withRequestReceipt(db,owner,key,input,work,operation) {
  if (typeof key !== 'string' || !/^[A-Za-z0-9_-]{16,120}$/u.test(key)) throw Object.assign(new Error('저장에는 요청 키가 필요합니다.'),{status:400,apiCode:'REQUEST_KEY_REQUIRED'});
  // Existing merge receipts keep their original fingerprint format.
  const fingerprint = createHash('sha256').update(JSON.stringify(canonical(operation ? {operation,input} : input))).digest('hex');
  db.exec('BEGIN IMMEDIATE');
  try {
    const cached = db.prepare('SELECT * FROM request_receipts WHERE owner_id=? AND request_key=?').get(owner,key);
    if (cached) {
      if (cached.fingerprint !== fingerprint) throw Object.assign(new Error('같은 요청 키로 다른 내용을 저장할 수 없습니다.'),{status:409,apiCode:'REQUEST_KEY_CONFLICT'});
      db.exec('COMMIT'); return JSON.parse(cached.result_json);
    }
    const result = work();
    db.prepare('INSERT INTO request_receipts VALUES (?,?,?,?,?)').run(owner,key,fingerprint,JSON.stringify(result),new Date().toISOString());
    db.exec('COMMIT'); return result;
  } catch (error) { db.exec('ROLLBACK'); throw error; }
}
