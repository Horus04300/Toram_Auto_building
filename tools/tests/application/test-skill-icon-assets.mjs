import assert from 'node:assert/strict';
import {access} from 'node:fs/promises';
import {resolve} from 'node:path';
import {skillTreeData} from '../../../web/src/data/skill-tree-data.js';
import {frontendSourcePath} from '../../support/frontend-paths.mjs';
const root=resolve(import.meta.dirname,'../../..'),paths=[];
function visit(value) {
  if(!value||typeof value!=='object')return;
  if(typeof value.icon==='string')paths.push(value.icon);
  Object.values(value).forEach(visit);
}
visit(skillTreeData);
assert.ok(paths.length,'Skill data must reference usable icons');
for(const path of paths) await access(resolve(root,frontendSourcePath(path)));
console.log(`Skill icon assets: PASS (${paths.length} referenced files exist)`);
