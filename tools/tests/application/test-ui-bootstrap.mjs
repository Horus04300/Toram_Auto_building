import assert from 'node:assert/strict';
import { readFileSync } from 'node:fs';
import vm from 'node:vm';

const source = readFileSync(new URL('../../../assets/js/ui-bootstrap.js', import.meta.url), 'utf8');
for (const readyState of ['loading', 'interactive', 'complete']) {
  const counts = { build:0, optimizer:0, preview:0, calculation:0 };
  const listeners = new Map();
  const app = {
    buildUi:{ bind() { counts.build++; } },
    optimizerUi:{ initialize() { counts.optimizer++; } },
    optimizer:{ runPreviewSafe() { counts.preview++; }, runCalculationSafe() { counts.calculation++; } }
  };
  const window = { ToramApp:app, ToramBuildFileUi:{}, ToramUpdateUi:{} };
  const document = { readyState, addEventListener(name, callback, options) {
    assert.equal(listeners.has(name), false, `Duplicate listener: ${name}`);
    listeners.set(name, { callback, options });
  } };
  vm.runInNewContext(source, { window, document });
  assert.equal(window.ToramUiFeatures.settings, window.ToramBuildFileUi);
  assert.equal(window.ToramUiFeatures.updates, window.ToramUpdateUi);
  assert.equal(Object.isFrozen(window.ToramUiFeatures), true);
  if (readyState === 'loading') {
    assert.equal(counts.build, 0);
    const ready = listeners.get('DOMContentLoaded');
    assert.equal(ready.options.once, true);
    ready.callback();
    ready.callback(); // A duplicate ready notification must not bind twice.
  }
  assert.equal(counts.build, 1);
  assert.equal(counts.optimizer, 1);
  listeners.get('toram:preview').callback();
  listeners.get('toram:calculate').callback();
  assert.equal(counts.preview, 1);
  assert.equal(counts.calculation, 1);
}
console.log('UI bootstrap: PASS (early/late DOM, single binding, settings/update registry)');
