// Test/measurement access to the actual client projection without adding a
// production public API or duplicating its field allowlist.
import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
const source = await readFile(new URL('../assets/js/d4-native-client.js', import.meta.url), 'utf8');
const anchor = '  var client = new NativeParallelClient();';
assert.equal(source.split(anchor).length, 2);
const context = {};
new Function('window', source.replace(anchor, '  root.projectNativeProblem = nativeProblem;\n' + anchor))(context);
export const projectNativeProblem = context.projectNativeProblem;
