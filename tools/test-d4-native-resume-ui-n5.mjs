import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';

const root = resolve(import.meta.dirname, '..');
const client = await readFile(resolve(root, 'assets/js/d4-native-client.js'), 'utf8');
const optimizer = await readFile(resolve(root, 'assets/js/optimizer.js'), 'utf8');

assert.match(client, /run\('resume_d4_optimization'/, 'native client must invoke the Rust continuation command');
assert.match(client, /pause_d4_optimization/, 'native client must expose a distinct pause command that keeps the frontier');
assert.match(client, /dispose_d4_optimization/, 'native client must release stale continuation sessions');
assert.match(client, /D4_CONTINUATION_UNAVAILABLE/, 'expired native sessions must surface an explicit error');
assert.match(optimizer, /status === 'bounded' \|\| status === 'no-incumbent-yet' \|\| status === 'paused'/, 'all resumable terminal states must expose a continuation control');
assert.match(optimizer, /d4OptimizationPause/, 'native execution must expose an explicit pause button');
const continueStart = optimizer.indexOf("d4Continue.addEventListener('click'");
const continueEnd = optimizer.indexOf('// A continuation', continueStart);
assert.ok(continueStart >= 0 && continueEnd > continueStart, 'continue button handler must remain present');
const continueHandler = optimizer.slice(continueStart, continueEnd);
assert.match(continueHandler, /ToramD4NativeClient\.resume/, 'continue button must resume rather than launch a new search');
assert.doesNotMatch(continueHandler, /launchD4Worker\(/, 'continue button must not restart d4_optimize_parallel');
assert.match(continueHandler, /resumeUntilExact/, 'one precision action must automatically chain bounded 30-second slices until terminal or paused');
assert.match(optimizer, /discardD4ContinuationForInputChange/, 'input changes must discard stale continuations');
assert.match(optimizer, /pagehide/, 'closing the window must release a stored continuation');

console.log('D4 native N5 UI continuation wiring: PASS');
