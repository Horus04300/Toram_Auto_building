/**
 * R0 refactoring baseline.
 *
 * `normalValue` fixtures have expectations backed by a source, formula, or
 * explicit algorithmic invariant. `characterization` fixtures intentionally
 * record observable 37dae51 behaviour, including legacy boundaries scheduled
 * for removal only in later refactoring phases.
 */
export const BASELINE_COMMIT = '37dae51';

export const NORMAL_VALUE_FIXTURES = Object.freeze([
  'test-updates.mjs',
  'test-update-release.mjs',
  'test-active-buff-context.mjs',
  'test-assassin-s5.mjs',
  'test-barehand-s5.mjs',
  'test-battle-s5.mjs',
  'test-blade-s4-s5.mjs',
  'test-combo-tags.mjs',
  'test-crusher-s5.mjs',
  'test-d-sector.mjs',
  'test-d4-evaluator-stage1.mjs',
  'test-d4-global-optimizer-stage2.mjs',
  'test-d4-native-exact-p4.mjs',
  'test-d4-native-locks-n1.mjs',
  'test-d4-pair-frontier.mjs',
  'test-d4-pair-partition.mjs',
  'test-d4-parallel-shards.mjs',
  'test-d4-recommendation-apply.mjs',
  'test-d4-rust-native-parity.mjs',
  'test-d4-utility-dependencies.mjs',
  'test-dagger-s5.mjs',
  'test-dancer-s5.mjs',
  'test-dark-power-s5.mjs',
  'test-dual-sword-s5.mjs',
  'test-equipment-option-selector.mjs',
  'test-golem-s5.mjs',
  'test-guard-s5.mjs',
  'test-halberd-s3.mjs',
  'test-halberd-s4-s5.mjs',
  'test-hunter-s5.mjs',
  'test-knight-s5.mjs',
  'test-magic-blade-s5.mjs',
  'test-magic-s3.mjs',
  'test-magic-s4-s5.mjs',
  'test-martial-s4-s5.mjs',
  'test-minstrel-s5.mjs',
  'test-mononofu-s5.mjs',
  'test-necromancer-s5.mjs',
  'test-ninja-s5.mjs',
  'test-normal-attack-ampr-priority.mjs',
  'test-partisan-s5.mjs',
  'test-priest-s5.mjs',
  'test-proc-damage-results.mjs',
  'test-shield-s5.mjs',
  'test-shot-s4-s5.mjs',
  'test-skill-data-audit.mjs',
  'test-sprite-s5.mjs',
  'test-status-points.mjs',
  'test-support-s5.mjs',
  'test-survival-s5.mjs',
  'test-wizard-s5.mjs'
]);

export const CHARACTERIZATION_FIXTURES = Object.freeze([
  'test-active-buff-ui.mjs',
  'test-build-setting-snapshot.mjs',
  'test-combo-ui-loading.mjs',
  'test-d4-browser-worker-runtime.mjs',
  'test-d4-dynamic-marginal.mjs',
  'test-d4-dynamic-seed-builds.mjs',
  'test-d4-execution-adapter.mjs',
  'test-d4-full-stage3.mjs',
  'test-d4-native-client.mjs',
  'test-d4-native-resume-ui-n5.mjs',
  'test-d4-native-runtime-n0.mjs',
  'test-d4-parallel-worker-runtime.mjs',
  'test-d4-replacement-proof.mjs',
  'test-d4-worker-stage3.mjs',
  'test-qa-edge-cases.mjs',
  'test-skill-icon-assets.mjs',
  'test-tauri-build-storage-adapter.mjs',
  'test-tauri-native-storage-e2e.mjs'
]);
