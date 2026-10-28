import ts from 'typescript';
import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';

const root = resolve(import.meta.dirname, '../..');
const tsconfig = JSON.parse(await readFile(resolve(root, 'tsconfig.json'), 'utf8'));
const compilerOptions = tsconfig.compilerOptions || {};
assert.equal(compilerOptions.strict, true, 'Type boundary 타입 검사는 strict여야 합니다.');
assert.equal(compilerOptions.noEmit, true, '기본 타입 검사는 런타임 파일을 출력하면 안 됩니다.');
assert.equal(compilerOptions.allowJs, false, '기존 JavaScript 전체를 검증 대상으로 강제하지 않습니다.');

const sources = [
  'web/src/contracts/boundary-dtos.d.ts',
  'web/src/contracts/boundary-dto-fixtures.ts',
  'desktop/adapters/saved-build-storage.ts',
  'web/src/contracts/update-boundary.d.ts',
  'desktop/adapters/update.ts'
];
for (const path of sources) {
  const source = await readFile(resolve(root, path), 'utf8');
  const check = node => {
    assert.notEqual(node.kind, ts.SyntaxKind.AnyKeyword, `${path}: any를 사용하면 안 됩니다.`);
    ts.forEachChild(node, check);
  };
  check(ts.createSourceFile(path, source, ts.ScriptTarget.Latest, true));
}

console.log('Type boundary: PASS (strict storage/update adapters, no explicit any)');
