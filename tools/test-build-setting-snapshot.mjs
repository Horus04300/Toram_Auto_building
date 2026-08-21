import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const values = new Map([
  ['toram-auto-building.build-state.v1', '{"level":300}'],
  ['toram.combo-sequence.v1', '["Blade:0"]']
]);
let reloadCount = 0;
const localStorage = {
  getItem:key => values.has(key) ? values.get(key) : null,
  setItem:(key, value) => values.set(key, String(value)),
  removeItem:key => values.delete(key)
};
const context = {
  window:{ localStorage, location:{ reload:() => { reloadCount += 1; } } },
  console,
  Date,
  JSON,
  Object,
  Array,
  String
};
context.window.window = context.window;
vm.createContext(context);
vm.runInContext(await readFile(resolve(root, 'assets/js/build-setting-snapshot.js'), 'utf8'), context, {
  filename:'assets/js/build-setting-snapshot.js'
});

const settings = context.window.ToramBuildSettings;
const ok = (condition, message) => { if (!condition) throw new Error(message); };
const snapshot = settings.capture('  테스트:/세팅...  ');
ok(snapshot.name === '테스트--세팅', '파일명 정규화');
ok(snapshot.storage['toram-auto-building.build-state.v1'] === '{"level":300}', '스테이터스 캡처');
ok(snapshot.storage['toram.combo-sequence.v1'] === '["Blade:0"]', '콤보 캡처');
ok(settings.validate(snapshot), '정상 스냅샷 검증');
ok(!settings.validate({ format:settings.format, schemaVersion:99, storage:{} }), '다른 스키마 차단');

const serialized = settings.serialize('백업');
values.clear();
settings.apply(settings.parse(serialized), { reload:false });
ok(values.get('toram-auto-building.build-state.v1') === '{"level":300}', '스테이터스 복원');
ok(values.get('toram.combo-sequence.v1') === '["Blade:0"]', '콤보 복원');
ok(reloadCount === 0, '테스트 복원 시 새로고침 억제');

settings.apply(settings.parse(serialized));
ok(reloadCount === 1, '일반 복원 시 새로고침');

let downloadedBlob = null;
let clicked = false;
let removed = false;
let revokedUrl = null;
context.Blob = class BlobMock {
  constructor(parts, options) { this.parts = parts; this.type = options && options.type; downloadedBlob = this; }
};
context.URL = {
  createObjectURL:() => 'blob:setting-backup',
  revokeObjectURL:url => { revokedUrl = url; }
};
context.document = {
  createElement:() => ({ href:'', download:'', click:() => { clicked = true; }, remove:() => { removed = true; } }),
  body:{ appendChild:() => {} }
};
context.window.setTimeout = callback => callback();
const downloadName = settings.download('백업:/파일');
ok(downloadName === '백업--파일.json', '백업 파일명 정규화');
ok(clicked && removed, 'JSON 내보내기 링크 실행 및 정리');
ok(downloadedBlob && downloadedBlob.type === 'application/json', 'JSON MIME 형식');
ok(revokedUrl === 'blob:setting-backup', '백업 Blob URL 해제');
console.log('Build setting snapshot regressions: PASS');
