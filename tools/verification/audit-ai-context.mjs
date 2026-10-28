import assert from 'node:assert/strict';
import { execFileSync } from 'node:child_process';
import { readFileSync, statSync } from 'node:fs';
import { dirname, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '../..');
function files(args) {
  return execFileSync('rg', ['--files', '--hidden', '-0', ...args], {
    cwd: root, encoding: 'utf8', maxBuffer: 8 * 1024 * 1024,
  }).split('\0').filter(Boolean).map(path => path.replaceAll('\\', '/'));
}
function bytes(paths) {
  return paths.reduce((sum, path) => sum + statSync(resolve(root, path)).size, 0);
}
const baseline = files(['-g', '!.git']);
const filtered = files(['--ignore-file', '.aiignore']);
const visible = new Set(filtered);
const required = [
  'AGENTS.md', 'docs/handoff/current-development-handoff.md',
  'docs/ai-context-guide.md', 'docs/skill-tree-verification-standard.md',
  'docs/architecture/crysta-optimization-contract.md', 'docs/verification/unimplemented.md',
  'web/src/calculation/calculator.js', 'tools/support/crysta-exhaustive-oracle.mjs',
  'web/src/optimization/candidate-preparation.js', 'web/src/optimization/wasm-worker.js',
  'web/src/optimization/rust-bridge.js', 'engine/Cargo.toml',
  'web/src/data/skill-tree-data.js', 'data/sources/coryn-skill-simulator/skill_tree_data.js',
  'engine/src/solver.rs', 'web/src/contracts/boundary-dtos.d.ts',
  'tools/run-regression-suite.mjs', 'tools/fixtures/crysta-native-runtime-26min-revenir.json',
];
for (const path of required) assert(visible.has(path), `Required context hidden: ${path}`);
for (const path of baseline.filter(path => /^(docs\/sources\/|data\/sources\/skill-registration\/)/.test(path))) {
  assert(visible.has(path), `Source evidence hidden: ${path}`);
}
const excluded = [
  'package-lock.json', 'desktop/Cargo.lock', 'web/public/fonts/PretendardVariable.woff2',
  'data/sources/game-icon-skill-match-candidates.json',
];
for (const path of excluded) assert(!visible.has(path), `Noise still visible: ${path}`);
assert(!filtered.some(path => /^(\.git|node_modules|build|desktop\/target|engine\/target)\//.test(path)), 'Build/Git output visible');
const handoff = 'docs/handoff/current-development-handoff.md';
const handoffBytes = bytes([handoff]);
assert(handoffBytes <= 12 * 1024, `Handoff exceeds 12 KiB: ${handoffBytes}`);
const documentBudgets = {
  'docs/architecture/crysta-optimization-contract.md': 12 * 1024,
  'docs/architecture/native-optimization-runtime.md': 8 * 1024,
  'docs/verification/unimplemented.md': 12 * 1024,
};
for (const [path, budget] of Object.entries(documentBudgets)) {
  assert(bytes([path]) <= budget, `Context document exceeds budget: ${path}`);
}
// All backtick-quoted repository paths in these entry documents must resolve.
for (const doc of ['AGENTS.md', handoff, 'docs/ai-context-guide.md', ...Object.keys(documentBudgets)]) {
  const content = readFileSync(resolve(root, doc), 'utf8');
  for (const [, path] of content.matchAll(/`((?:docs|web|desktop|engine|data|tools)\/[^`\s*]+)`/g)) {
    assert(statSync(resolve(root, path)), `Broken path in ${doc}: ${path}`);
  }
}
console.log(JSON.stringify({
  checks: 'PASS: required sources, exclusions, handoff budget, entry-document paths',
  defaultSearch: { files: baseline.length, bytes: bytes(baseline) },
  aiSearch: { files: filtered.length, bytes: bytes(filtered) },
  handoff: { bytes: handoffBytes, budgetBytes: 12 * 1024 },
  contextDocuments: Object.keys(documentBudgets).map(path => ({ path, bytes: bytes([path]), budgetBytes: documentBudgets[path] })),
  note: 'File bytes measure searchable context, not billed tokens or automatic model ingestion.',
}, null, 2));
