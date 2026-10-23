// Test/measurement access to the actual client projection without adding a
// production public API or duplicating its field allowlist.
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
const source = await readFile(new URL('../../web/src/optimization/rust-bridge.js', import.meta.url), 'utf8');
const context = {};
new Function('window', source)(context);
export const projectNativeProblem = context.ToramCrystaOptimizationRustBridge.projectProblem;
assert.equal(typeof projectNativeProblem, 'function');
