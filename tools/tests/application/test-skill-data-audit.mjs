import {skillRegistry} from '../../../web/src/data/skill-effect-registry.js';
import {skillData} from '../../../web/src/calculation/skill-data-validator.js';
import assert from 'node:assert/strict';

const context = { window:{}, console };
context.window.window = context.window;

const audit = skillData.audit();
assert.deepEqual([...audit.errors], [], `스킬 데이터 감사 오류:\n${[...audit.errors].join('\n')}`);
assert.equal(audit.shadowedDefinitions.length,0,'Canonical definitions must not shadow one another');

skillRegistry.register([{
  id:'Invalid:999', treeId:'Invalid', skillId:999, nameKo:'감사 오류 검증', kind:'invalid', dataStatus:'partial'
}]);
const invalidAudit = skillData.audit();
assert.ok(invalidAudit.errors.some(error => error.includes('전투 카탈로그에 없는 스킬 정의: Invalid:999')), '카탈로그 밖 정의를 감지해야 합니다.');
assert.ok(invalidAudit.errors.some(error => error.includes('알 수 없는 스킬 종류: Invalid:999')), '잘못된 스킬 종류를 감지해야 합니다.');
assert.ok(invalidAudit.errors.some(error => error.includes('출처 키 누락: Invalid:999')), '출처 누락을 감지해야 합니다.');

console.log(`Skill data audit: PASS (catalog ${audit.scoped}, effective ${audit.detailed}, layered ${audit.layered})`);
