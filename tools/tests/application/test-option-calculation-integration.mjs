import assert from 'node:assert/strict';
import {readFile} from 'node:fs/promises';
import {loadSavedBuildEnvironment} from '../../support/saved-build-headless-environment.mjs';
const environment=await loadSavedBuildEnvironment();
const input=JSON.parse(await readFile(new URL('../../../samples/마법) 지팡이 크법 세팅 - pelio s.json',import.meta.url),'utf8'));
input.build.externalOptions=[{key:'DEF',value:100},{key:'DEFP',value:10},{key:'ACCP',value:50},{key:'ACCP',value:-25},{key:'PHYS_RES',value:20},{key:'FIRE_RES',value:10},{key:'HP_REGEN',value:20}];
input.scenario.optionCalculation={equipmentDefense:100,incomingDamage:1000,incomingType:'physical',incomingElement:1,incomingActionType:0,mentality:255,baseItemCooldownSeconds:10};
const result=environment.ToramApplication.CalculateBuild(input).calculation;
assert.deepEqual(Array.from(result.ctx.preservedStatContributions.ACCP),[50,-25]);
assert.ok(result.supplementalStats.values.defense>100);
assert.ok(result.supplementalStats.values.accuracy>0);
assert.equal(result.optionEvents.outcomes.damageAfterBodyAndShape,800);
assert.equal(result.optionEvents.outcomes.damageAfterElement,720);
assert.equal(result.ctx.optionCalculationInputs.equipmentDefense,100);
environment.ToramBuildDraftStore={read:()=>input};
const saved=JSON.parse(environment.ToramSettingsRepository.serializeSavedBuild('나머지 옵션 계산'));
assert.equal(environment.ToramSettingsRepository.validateSavedBuild(saved),true);
assert.equal(JSON.stringify(environment.ToramSettingsRepository.parseSavedBuild(JSON.stringify(saved)).scenario.optionCalculation),JSON.stringify(input.scenario.optionCalculation));
for(const bad of [[],null,{incomingDamage:-1},{unknown:1},{incomingType:'other'},{incomingDamage:'1000'},{absoluteDodgeRoll:100}]){
 const document=structuredClone(saved);document.scenario.optionCalculation=bad;
 assert.equal(environment.ToramSettingsRepository.validateSavedBuild(document),false);
}
const old=structuredClone(saved);delete old.scenario.optionCalculation;
assert.equal(environment.ToramSettingsRepository.validateSavedBuild(old),true);
const noInputs=structuredClone(input);delete noInputs.scenario.optionCalculation;
assert.equal(environment.ToramApplication.CalculateBuild(noInputs).calculation.supplementalStats.values.defense,null);
console.log('Option calculation integration: PASS (source contributions, kernel/Scenario, saved/legacy validation, native resistance stages)');
