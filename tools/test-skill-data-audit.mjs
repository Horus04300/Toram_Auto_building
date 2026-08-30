import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { dirname, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';
import vm from 'node:vm';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const html = await readFile(resolve(root, 'index.html'), 'utf8');
const scripts = [...html.matchAll(/<script src="([^"]+)"><\/script>/g)]
  .map(match => match[1])
  .filter(path => path.startsWith('assets/js/data/'));
const context = { window:{}, console };
context.window.window = context.window;
vm.createContext(context);
for (const path of scripts) vm.runInContext(await readFile(resolve(root, path), 'utf8'), context, { filename:path });
vm.runInContext(await readFile(resolve(root, 'assets/js/skill-data-validator.js'), 'utf8'), context, { filename:'assets/js/skill-data-validator.js' });

const audit = context.window.ToramSkillData.audit();
assert.deepEqual([...audit.errors], [], `스킬 데이터 감사 오류:\n${[...audit.errors].join('\n')}`);
assert.ok(audit.shadowedDefinitions.length > 0, '의도된 보강 레이어 수를 진단 정보로 보존해야 합니다.');

context.window.ToramSkillEffectRegistry.register('Audit-invalid-fixture', [{
  id:'Invalid:999', treeId:'Invalid', skillId:999, nameKo:'감사 오류 검증', kind:'invalid', dataStatus:'partial'
}]);
const invalidAudit = context.window.ToramSkillData.audit();
assert.ok(invalidAudit.errors.some(error => error.includes('전투 카탈로그에 없는 스킬 정의: Invalid:999')), '카탈로그 밖 정의를 감지해야 합니다.');
assert.ok(invalidAudit.errors.some(error => error.includes('알 수 없는 스킬 종류: Invalid:999')), '잘못된 스킬 종류를 감지해야 합니다.');
assert.ok(invalidAudit.errors.some(error => error.includes('출처 키 누락: Invalid:999')), '출처 누락을 감지해야 합니다.');

console.log(`Skill data audit: PASS (catalog ${audit.scoped}, effective ${audit.detailed}, layered ${audit.layered})`);
