import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';
import { loadSavedBuildEnvironment } from '../support/saved-build-headless-environment.mjs';

const root = resolve(import.meta.dirname, '../..');
const context = await loadSavedBuildEnvironment();

const summaries = [];
for (const name of ['마법) 인힘 마도구', '마법) 지팡이 크법 세팅', '서폿) 그냥 지금 세팅']) {
  const file = `samples/${name} - pelio s.json`;
  const sample = context.ToramSettingsRepository.parseSavedBuild(await readFile(resolve(root, file), 'utf8'));
  const original = JSON.stringify(sample);
  context.skillSimulatorState = { getInvestments:() => sample.build.skillLevels };
  const calculate = input => context.ToramApplication.CalculateBuild(input);
  const current = calculate(sample);
  const variant = edit => { const input = JSON.parse(original); edit(input); return calculate(input); };
  const metrics = result => ({ cspd:result.calculation.finalCSPD, motionSpeed:result.calculation.finalMotionSpeed,
    crit:result.calculation.finalCrit, srw:result.calculation.ctx.srw, critP:result.calculation.ctx.critP,
    critF:result.calculation.ctx.critF, cspdP:result.calculation.ctx.cspdP, cspdF:result.calculation.ctx.cspdF,
    elemP:result.calculation.ctx.elemP });
  const buffsOff = Object.fromEntries(['Magic:22', 'Wizard:12', 'Support:7'].map(id =>
    [id, metrics(variant(input => { input.build.activeBuffs[id] = { active:false, stacks:0 }; }))]));
  const withoutPerulu = variant(input => {
    input.build.equipment.additional.crystas = input.build.equipment.additional.crystas.filter(name => name !== '라지 페루루');
  });
  assert.equal(current.calculation.ctx.srw - withoutPerulu.calculation.ctx.srw, 10, `${name}: 라지 페루루 SRW`);
  assert.equal(current.calculation.ctx.critP - withoutPerulu.calculation.ctx.critP, 50, `${name}: 라지 페루루 CRIT%`);
  // Profile evaluation needs explicit investments after the scoped calculation ends.
  const profile = context.ToramSkillEffects.profile('Magic:11', current.snapshot.baseContext, current.combat,
    { charge:200 }, { activeBuffs:sample.build.activeBuffs });
  const combo = context.ToramComboSequence.evaluate(sample.build.combo, current.snapshot.baseContext, current.combat,
    { maxMp:current.calculation.finalMaxMP, activeBuffs:sample.build.activeBuffs });
  const passiveStats = context.ToramSkillEffects.passiveStatChanges(current.snapshot.baseContext)
    .filter(change => change.source.treeId === 'Wizard').map(change => ({ id:change.source.id, key:change.key, value:change.value }));
  const passiveApplied = context.ToramApplication.CreateCalculationSnapshot(sample).baseContext;
  const wizardLevels = Object.values(sample.build.skillLevels.Wizard);
  const wizardCount = wizardLevels.filter(level => level > 0).length;
  const wizardPoints = wizardLevels.reduce((sum, level) => sum + level, 0);
  const mastery = sample.build.skillLevels.Wizard[10];
  const expectedMasteryPercent = 1.5 * mastery + (wizardCount - 1) * mastery / 2;
  const expectedMasteryFlat = wizardPoints * mastery;
  const joko = context.ToramCrystaCatalog.resolve('죠코');
  const additiveJoko = context.ToramCalculationKernel.evaluateContext(current.snapshot.baseContext, [...current.snapshot.crystas, joko, joko]);
  assert.equal(additiveJoko.ctx.critF - current.calculation.ctx.critF, -18, '죠코 2개의 고정 CRIT 합');
  let sourceFormulaCspd = null;
  if (name.startsWith('서폿')) {
    const adjusted = context.ToramCalculationKernel.cloneContext(current.snapshot.baseContext);
    adjusted.cspdP += expectedMasteryPercent - passiveStats.find(change => change.key === 'CSPD_P').value;
    adjusted.cspdF += expectedMasteryFlat - 1000 + 50 * sample.build.skillLevels.Wizard[13];
    sourceFormulaCspd = context.ToramCalculationKernel.evaluateContext(adjusted, current.snapshot.crystas).finalCSPD;
  }
  assert.equal(JSON.stringify(sample), original, '샘플 원본 입력은 변하지 않아야 한다.');
  assert.equal(context.ToramCalculationInputScope, undefined, '계산 스코프는 복원되어야 한다.');
  summaries.push({ file, current:metrics(current), buffsOff, withoutPerulu:metrics(withoutPerulu),
    cannon:profile.hits.map(hit => ({ id:hit.id, base:hit.baseMultiplier, multiplier:hit.multiplier })),
    combo:combo.entries.map(entry => ({ id:entry.skillId, status:entry.executionStatus,
      hits:entry.hits.map(hit => ({ id:hit.id, base:hit.baseMultiplier, effective:hit.effectiveMultiplier })) })),
    wizardPassiveStats:passiveStats, passiveContext:{ cspdP:passiveApplied.cspdP, cspdF:passiveApplied.cspdF },
    wizardSourceFormula:{ learnedCount:wizardCount, totalPoints:wizardPoints, masteryPercent:expectedMasteryPercent,
      masteryFlat:expectedMasteryFlat, supportCspdWithMasteryAndOverLimit:sourceFormulaCspd },
    additiveJoko:{ crit: additiveJoko.finalCrit, critFlatDelta:additiveJoko.ctx.critF - current.calculation.ctx.critF } });
}
console.log(JSON.stringify(summaries, null, 2));
console.log('PASS: saved-build parsing, Perulu deltas, additive Joko -18, input/scope preservation (not browser E2E or full feedback verification)');
