import {skillEffects} from '../../../web/src/calculation/skill-effect-engine.js';
const context={window:{},console};context.window.window=context.window;context.window.skillSimulatorState={getInvestments:()=>({Guard:{}})};
const E=skillEffects;
const base=(level,armorType)=>({mainType:'한손검',subType:'방패',armorType,level:300,skillLevels:{Guard:Object.fromEntries(Array.from({length:6},(_,id)=>[id,level]))}});
const assert=(ok,message)=>{if(!ok)throw Error(message);};
for(let level=0;level<=10;level++) {
  for(let id=0;id<6;id++) assert(E.profile(`Guard:${id}`,base(level,'중량옷'),{},{}).available===(level>0),`Guard:${id} Lv${level}`);
  if(!level)continue;
  const heavy=E.profile('Guard:1',base(level,'중량옷'),{},{}).effects;
  assert(heavy.find(effect=>effect.type==='guardRecoveryRate').value===level,'Heavy guard recovery');
  assert(heavy.find(effect=>effect.type==='guardPower').value===(level+1)/2,'Heavy guard power');
  assert(E.profile('Guard:1',base(level,'경량옷'),{},{}).effects.length===0,'Heavy effects require heavy armor');
  assert(E.profile('Guard:3',base(level,'경량옷'),{},{}).effects[0].value===level,'Light evasion recovery');
  assert(E.profile('Guard:3',base(level,'중량옷'),{},{}).effects.length===0,'Light effects require light armor');
  assert(E.profile('Guard:5',base(level,'일반옷'),{},{}).effects[0].value===20-level,'Mirage cooldown metadata');
}
console.log('Guard active-definition regression: PASS (Lv0~10, armor conditions, preserved combat metadata; actual hit simulation remains deferred)');
