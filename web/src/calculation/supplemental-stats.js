  'use strict';
  var f = Math.fround;
  function add(a,b) { return f(f(a)+f(b)); }
  function multiply(a,b) { return f(f(a)*f(b)); }
  function divide(a,b) { return f(f(a)/f(b)); }
  function integer(value) { return Math.trunc(value) || 0; }
  function finite(value) { return typeof value==='number'&&Number.isFinite(value); }
  function optional(inputs,key) { var rule=inputDefinitions[key]||{},value=inputs[key];return finite(value)&&(rule.min===undefined||value>=rule.min)&&(rule.max===undefined||value<=rule.max)?value:null; }
  function sum(values) { return values.reduce(function(total,value){return total+value;},0); }
  var supportedKeys=['DEF','DEFP','MDEF','MDEFP','ACC','ACCP','FLEE','FLEEP','HP_REGEN','HP_REGENP','MP_REGEN','MP_REGENP','REVIVE_TIME','ABS_ACC','ANTICIPATE','GUARD_BREAK','ITEM_DELAY','EXP','DROP_RATE','PET_EXP','GEM_DUST_DROP','AGGRO','PHYS_PURSUIT','MAG_PURSUIT'];
  var legacyKeys=['ITEM_CD'];
  var inputDefinitions={
    equipmentDefense:{key:'equipmentDefense',label:'장비 DEF 합계',unit:'DEF'},
    baseHitChance:{key:'baseHitChance',label:'절대명중 전 일반 적중 확률',unit:'%',min:0,max:100},
    targetAvoidChance:{key:'targetAvoidChance',label:'선행 판정 전 대상 Avoid 확률',unit:'%',min:0,max:100},
    targetGuardChance:{key:'targetGuardChance',label:'가드 무효 전 대상 Guard 확률',unit:'%',min:0,max:100},
    baseItemCooldownSeconds:{key:'baseItemCooldownSeconds',label:'기본 도구 대기시간',unit:'초',min:0},
    baseExperience:{key:'baseExperience',label:'기본 경험치 (보상 환산용)',unit:'EXP',min:0},
    basePetExperience:{key:'basePetExperience',label:'기본 펫 경험치 (보상 환산용)',unit:'EXP',min:0},
    baseDropValue:{key:'baseDropValue',label:'기본 드롭값 (보상 환산용)',min:0},
    baseGemDust:{key:'baseGemDust',label:'기본 마소 드롭값 (보상 환산용)',min:0},
    luck:{key:'luck',label:'기초 LUK',min:0}
  };
  function evaluate(calculation,inputs) {
    calculation=calculation||{};inputs=inputs||{};
    var ctx=calculation.ctx||{},stats=ctx.preservedStats||{},contributions=ctx.preservedStatContributions||{};
    var values={},outcomes={},rows=[],requirements={};
    function stat(key) { return Number(stats[key])||0; }
    function sources(key) { return Array.isArray(contributions[key])?contributions[key].filter(finite):[stat(key)]; }
    function cappedInstant(key,cap) { return sources(key).reduce(function(value,source){return (Math.min(value+((integer(source)<<16)>>16),cap)<<16)>>16;},0); }
    function total(name,attribute) { return finite(calculation[name])?calculation[name]:integer((Number(ctx[attribute+'Base'])||0)*(1+(Number(ctx[attribute+'P'])||0)/100))+(Number(ctx[attribute+'F'])||0); }
    function row(id,label,value,unit,required) {
      var missing=(required||[]).filter(function(key){return optional(inputs,key)===null;});
      missing.forEach(function(key){requirements[key]=inputDefinitions[key]||{key:key,label:key};});
      rows.push({id:id,label:label,value:value,unit:unit||'',requires:missing});
      values[id]=value;
    }
    function rate(key,start) { return sources(key).reduce(function(value,source){return add(value,multiply(source,f(.01)));},start); }
    function recovery(base,percent,flat) {
      var percentTotal=sources(percent).reduce(add,100),flatTotal=sources(flat).reduce(add,0);
      return integer(add(multiply(divide(percentTotal,100),base),flatTotal));
    }
    var level=Number(ctx.level)||0,vit=total('finalVIT','vit'),intelligence=total('finalINT','int'),dex=total('finalDEX','dex'),agi=total('finalAGI','agi');
    var armor=ctx.armorType,mode=armor==='경량옷'?'light':armor==='중량옷'?'heavy':armor==='없음'||armor==='맨몸'?'none':'normal';
    var equipment=optional(inputs,'equipmentDefense');
    function defense(attribute,magic) {
      var base;
      if(mode==='light')base=integer(add(add(multiply(attribute,.25),multiply(level,.8)),magic?0:equipment||0));
      else if(mode==='heavy')base=integer(add(add(multiply(level,1.2),attribute),attribute));
      else if(mode==='none')base=integer(add(divide(attribute,10),multiply(level,.4)));
      else base=integer(level+attribute);
      if(mode!=='light'||magic)base+=equipment||0;
      var percent=integer(stat(magic?'MDEFP':'DEFP'))+100-(ctx.subType==='화살'?25:0);
      return equipment===null?null:integer(Math.imul(integer(base),percent)/100)+integer(stat(magic?'MDEF':'DEF'));
    }
    row('defense','DEF',defense(vit,false),'DEF',['equipmentDefense']);
    row('magicDefense','MDEF',defense(intelligence,true),'MDEF',['equipmentDefense']);
    row('accuracy','명중',integer(multiply(level+dex,rate('ACCP',1)))+integer(sum(sources('ACC'))),'');
    var fleeBase;
    if(mode==='light')fleeBase=integer(add(add(multiply(agi,1.75),multiply(level,1.25)),30));
    else if(mode==='heavy')fleeBase=integer(add(add(multiply(agi,.75),multiply(level,.5)),-15));
    else if(mode==='none')fleeBase=integer(add(add(add(multiply(level,1.5),agi),agi),75));
    else fleeBase=integer(level+agi);
    row('flee','회피',integer(multiply(fleeBase,rate('FLEEP',1)))+integer(sum(sources('FLEE'))),'');
    var maxHp=finite(calculation.finalMaxHP)?Math.min(calculation.finalMaxHP,99999):null;
    var maxMp=finite(calculation.finalMaxMP)?Math.min(Math.max(calculation.finalMaxMP,0),2000):null;
    row('hpRecovery','비전투 HP 자연회복',maxHp===null?null:recovery(integer(maxHp/25)+10,'HP_REGENP','HP_REGEN'),'HP/회');
    row('mpRecovery','비전투 MP 자연회복',maxMp===null?null:recovery(integer(maxMp/100)+1,'MP_REGENP','MP_REGEN'),'MP/회');
    row('reviveSeconds','부활 대기시간',integer(add(multiply(add(1,-divide(Number(inputs.avatarRevivePercent)||0,100)),300),-stat('REVIVE_TIME'))),'초');
    function chance(value) { return Math.min(100,Math.max(0,integer(value))); }
    row('aggroPercent','어그로 증감',Math.max(-100,sum(sources('AGGRO'))),'%');
    row('physicalPursuitMultiplier','장비 물리추격 계수',divide(stat('PHYS_PURSUIT'),100),'배');
    row('magicalPursuitMultiplier','장비 마법추격 계수',divide(stat('MAG_PURSUIT'),100),'배');
    var hit=optional(inputs,'baseHitChance'),avoid=optional(inputs,'targetAvoidChance'),guard=optional(inputs,'targetGuardChance');
    row('hitChance','절대명중 포함 일반 적중 확률',hit===null?null:chance(hit)+(100-chance(hit))*chance(cappedInstant('ABS_ACC',30))/100,'%',['baseHitChance']);
    row('targetAvoidChance','선행 판정 후 대상 Avoid 확률',avoid===null?null:chance(avoid)*(100-chance(cappedInstant('ANTICIPATE',100)))/100,'%',['targetAvoidChance']);
    row('targetGuardChance','가드 무효 후 대상 Guard 확률',guard===null?null:chance(guard)*(100-chance(cappedInstant('GUARD_BREAK',100)))/100,'%',['targetGuardChance']);
    var itemBase=optional(inputs,'baseItemCooldownSeconds'),itemTime=itemBase;
    if(itemBase!==null&&Object.prototype.hasOwnProperty.call(stats,'ITEM_DELAY')) {
      var rawItemDelay=sources('ITEM_DELAY').reduce(function(value,source){return (Math.min(value+((Math.round(source*100)<<16)>>16),500)<<16)>>16;},0);
      itemTime=Math.max(5,multiply(add(1,-divide(divide(rawItemDelay,10),100)),itemBase));
    }
    row('itemCooldownSeconds','도구 대기시간',itemTime,'초',['baseItemCooldownSeconds']);
    outcomes.hitChance=values.hitChance;outcomes.targetAvoidChance=values.targetAvoidChance;outcomes.targetGuardChance=values.targetGuardChance;outcomes.itemCooldownSeconds=values.itemCooldownSeconds;
    var experienceWeight=100+integer(stat('EXP'))+(Number(inputs.otherExperiencePercent)||0);
    var petWeight=add(add(add(100,stat('EXP')),stat('PET_EXP')),Number(inputs.otherPetExperiencePercent)||0);
    var luck=finite(ctx.lukBase)?ctx.lukBase:optional(inputs,'luck');
    var dropWeight=luck===null?null:100+integer(stat('DROP_RATE'))+integer(luck/5)+(Number(inputs.otherDropPercent)||0);
    var dustWeight=100+integer(stat('GEM_DUST_DROP'));
    row('experienceWeight','장비·입력 경험치 비율',experienceWeight,'%');
    row('petExperienceWeight','장비·입력 펫 경험치 비율',petWeight,'%');
    row('dropWeight','장비·LUK·입력 드롭 비율',dropWeight,'%',finite(ctx.lukBase)?[]:['luck']);
    row('gemDustWeight','장비 마소 드롭 비율',dustWeight,'%');
    [['experienceEquivalent','경험치 환산값 (입력 기준)','baseExperience',experienceWeight],['petExperienceEquivalent','펫 경험치 환산값 (입력 기준)','basePetExperience',petWeight],['dropEquivalent','드롭 환산값 (입력 기준)','baseDropValue',dropWeight],['gemDustEquivalent','마소 드롭 환산값 (입력 기준)','baseGemDust',dustWeight]].forEach(function(item){
      var base=optional(inputs,item[2]);
      row(item[0],item[1],base===null||item[3]===null?null:base*item[3]/100,'',[item[2]].concat(item[3]===null?['luck']:[]));
      outcomes[item[0]]=values[item[0]];
    });
    var diagnostics=[];
    if(stat('ITEM_CD'))diagnostics.push({key:'ITEM_CD',code:'LEGACY_OPTION_WITHOUT_NATIVE_MAPPING',message:'구형 ITEM_CD는 현재 원본 옵션과 대응이 확인되지 않았습니다. 저장값은 보존하며 ITEM_DELAY로 임의 변환하지 않습니다.'});
    return {values:values,outcomes:outcomes,rows:rows,requirements:Object.keys(requirements).map(function(key){return requirements[key];}),diagnostics:diagnostics,notes:['보상 환산값은 입력한 기초값에 클라이언트 비율을 적용한 값입니다. 서버의 실제 지급·드롭 판정이나 정수 반올림을 예측하지 않습니다.']};
  }
  var api=Object.freeze({evaluate:evaluate,supportedKeys:Object.freeze(supportedKeys),legacyKeys:Object.freeze(legacyKeys),inputDefinitions:Object.freeze(inputDefinitions)});

export const supplementalStats=api;
export {evaluate,supportedKeys,legacyKeys,inputDefinitions};
