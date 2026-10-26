/* Explicit native option stages for one supplied event; no automatic battle timeline. */
(function (root) {
  'use strict';
  var f = Math.fround;
  var elements = [['FIRE_RES','불'],['WATER_RES','물'],['WIND_RES','바람'],['EARTH_RES','땅'],['LIGHT_RES','빛'],['DARK_RES','어둠'],['NEUTRAL_RES','무속성']];
  var shapes = [['AROUND_RES','주위'],['AREA_RES','범위'],['LINE_RED','직선'],['CHARGE_RED','돌진'],['METEOR_RES','운석'],['BULLET_RES','탄환'],['TRANSLATION_RES','사인'],['AOE_RES','장판'],['WIDD_RES','방사'],['EXPLOSION_RES','폭발'],['SUCTION_RES','흡인']];
  var requirements = [
    {key:'incomingDamage',label:'각 경감 단계에 넣을 1회 피해',unit:'HP',type:'number',min:0},
    {key:'incomingType',label:'피해 종류',type:'select',options:[{value:'physical',label:'물리'},{value:'magic',label:'마법'}]},
    {key:'incomingElement',label:'피격 공격 속성',type:'select',options:[{value:0,label:'미지정 (무속성 내성)'},{value:1,label:'불'},{value:2,label:'물'},{value:3,label:'바람'},{value:4,label:'땅'},{value:5,label:'빛'},{value:6,label:'어둠'},{value:7,label:'무속성'}],min:0,max:7},
    {key:'incomingActionType',label:'피격 공격 형태',type:'select',options:[{value:0,label:'일반 / 기타'},{value:1,label:'주위'},{value:2,label:'범위'},{value:40,label:'돌진'},{value:50,label:'직선'},{value:150,label:'방사'},{value:1060,label:'운석'},{value:1070,label:'탄환'},{value:1080,label:'사인'},{value:1110,label:'장판'},{value:1170,label:'흡인'},{value:1180,label:'폭발'}],min:0},
    {key:'mentality',label:'MTL',unit:'',type:'number',min:0},
    {key:'baseGuardPower',label:'옵션 적용 전 Guard력 (10000 = 100%)',unit:'',type:'number',min:0},
    {key:'baseGuardRecharge',label:'옵션 적용 전 Guard 회복량',unit:'포인트/초',type:'number',min:0},
    {key:'baseAvoidRecharge',label:'옵션 적용 전 Avoid 회복량',unit:'',type:'number',min:0},
    {key:'baseBarrierCooldown',label:'배리어 기본 재사용 시간',unit:'초',type:'number',min:0},
    {key:'absoluteDodgeRoll',label:'절대회피 판정 난수 (0~99)',unit:'',type:'number',min:0,max:99},
    {key:'absoluteDodgeEligible',label:'절대회피 가능한 명중 공격',type:'boolean'},
    {key:'flinchAttempt',label:'기죽음 부여 시도',type:'boolean'},
    {key:'tumbleAttempt',label:'넘어짐 부여 시도',type:'boolean'},
    {key:'stunAttempt',label:'기절 부여 시도',type:'boolean'}
  ];
  function numeric(value, name) {
    if (typeof value !== 'number' || !Number.isFinite(value)) throw new Error(name + ': 유한한 숫자가 필요합니다.');
    return value;
  }
  function input(inputs, key) {
    if (inputs[key] === undefined || inputs[key] === null || inputs[key] === '') return null;
    var value = numeric(inputs[key], key), definition = requirements.find(function (row) { return row.key === key; });
    if (definition && (definition.min !== undefined && value < definition.min || definition.max !== undefined && value > definition.max)) throw new Error(key + ': 입력 범위가 올바르지 않습니다.');
    return value;
  }
  function booleanInput(inputs, key) {
    if (inputs[key] === undefined || inputs[key] === null) return null;
    if (typeof inputs[key] !== 'boolean') throw new Error(key + ': 참 또는 거짓 값이 필요합니다.');
    return inputs[key];
  }
  function nativeInt(value) {
    var amount = f(value);
    return amount >= 2147483648 || amount < -2147483648 ? -2147483648 : Math.trunc(amount);
  }
  // Native repeats 50-point resistance bands and truncates after every band.
  function resistDamage(damage, resistance) {
    var result = Math.trunc(damage), remaining = Math.trunc(resistance);
    if (Math.abs(remaining) > 2147483647) throw new Error('내성 옵션이 native 정수 범위를 벗어났습니다.');
    while (remaining >= 50 || remaining <= -50) {
      var positive = remaining > 0;
      result = nativeInt(f(f(result) * (positive ? .5 : 1.5)));
      remaining += positive ? -50 : 50;
      if (result === 0) return 0;
      if (result < 0) throw new Error('내성 계산이 native 정수 피해 범위를 벗어났습니다.');
    }
    return remaining === 0 ? result : nativeInt(f(f(f(100 - remaining) * f(result)) / 100));
  }
  function shapeStat(actionType) {
    var groups = [
      ['AROUND_RES',[1,11,210,211]],['AREA_RES',[2,12,250,251,270,271]],
      ['CHARGE_RED',[40,41,44,45]],['LINE_RED',[50,51,1220,1221]],['WIDD_RES',[150,151]],
      ['METEOR_RES',[1060,1061]],['BULLET_RES',[1070,1071,1230,1231]],
      ['TRANSLATION_RES',[1080,1081,1084,1085]],['AOE_RES',[1110,1111]],
      ['SUCTION_RES',[1170,1171,1174,1175]],['EXPLOSION_RES',[1180,1181]]
    ];
    var group = groups.find(function (entry) { return entry[1].indexOf(actionType) >= 0; });
    return group ? group[0] : null;
  }
  function evaluate(calculation, inputs) {
    var source = calculation || {}, ctx = source.ctx || {}, stats = ctx.preservedStats || {}, settings = inputs || {};
    var values = {}, outcomes = {}, rows = [];
    function stat(key) { return stats[key] === undefined ? 0 : numeric(stats[key], key); }
    function row(bucket, id, label, value, unit, requires) {
      if (typeof value === 'number' && !Number.isFinite(value)) throw new Error(id + ': 계산 결과가 유한한 범위를 벗어났습니다.');
      bucket[id] = value;
      rows.push({id:id,label:label,value:value,unit:unit || '',...(requires ? {requires:requires} : {})});
    }
    var damage = input(settings,'incomingDamage');
    if (damage !== null && (!Number.isSafeInteger(damage) || damage > 2147483647)) throw new Error('incomingDamage: native 정수 피해가 필요합니다.');
    [['PHYS_RES','물리'],['MAG_RES','마법']].concat(elements,shapes).forEach(function (entry) {
      row(outcomes,'damageAfter_' + entry[0],entry[1] + ' 내성만 적용한 피해',damage === null ? null : resistDamage(damage,stat(entry[0])),'HP',['incomingDamage']);
    });
    var type = settings.incomingType, element = input(settings,'incomingElement'), actionType = input(settings,'incomingActionType');
    if (type !== undefined && type !== null && type !== '' && type !== 'physical' && type !== 'magic') throw new Error('incomingType: 물리 또는 마법을 선택하세요.');
    [element,actionType].forEach(function (value) { if (value !== null && !Number.isSafeInteger(value)) throw new Error('공격 속성과 행동 유형은 정수여야 합니다.'); });
    var selectedShape = actionType === null ? null : shapeStat(actionType);
    var bodyDamage = damage === null || !type || actionType === null ? null : resistDamage(damage,stat(type === 'physical' ? 'PHYS_RES' : 'MAG_RES') + (selectedShape ? stat(selectedShape) : 0));
    row(outcomes,'damageAfterBodyAndShape','물리/마법 내성 + 공격 형태 경감 후 피해',bodyDamage,'HP',['incomingDamage','incomingType','incomingActionType']);
    row(outcomes,'damageAfterElement','위 내성 적용 후 속성 내성까지 적용한 피해',bodyDamage === null || element === null ? null : resistDamage(bodyDamage,stat(elements[element >= 1 && element <= 6 ? element - 1 : 6][0])),'HP',['incomingDamage','incomingType','incomingActionType','incomingElement']);
    var hp = Number.isFinite(source.finalMaxHP) ? source.finalMaxHP : null;
    [['PHYS_BARR','물리'],['MAG_BARR','마법'],['FRAC_BARR','비율']].forEach(function (entry) {
      var amount = entry[0] === 'FRAC_BARR' ? hp === null ? null : nativeInt(f(f(hp) * f(f(stat(entry[0])) / 100))) : Math.trunc(stat(entry[0]));
      row(values,'barrierAbsorption_' + entry[0],entry[1] + ' 배리어 흡수량',amount,'HP');
      row(outcomes,'damageAfter_' + entry[0],entry[1] + ' 배리어가 준비된 1회 피해',damage === null || amount === null ? null : Math.max(1,Math.max(1,damage) - amount),'HP',['incomingDamage']);
    });
    row(outcomes,'reflectedDamage','피격 피해에 따른 반사 피해',damage === null ? null : nativeInt(f(f(f(stat('REFLECT')) / 100) * f(damage))),'HP',['incomingDamage']);
    var basePower = input(settings,'baseGuardPower');
    var guardPower = basePower === null ? null : Math.max(100,Math.trunc((100 + stat('GUARD_POWER')) * basePower / 100));
    row(values,'guardPower','옵션 적용 후 Guard력',guardPower,'',['baseGuardPower']);
    row(outcomes,'damageAfterGuard','현재 Guard력으로 방어한 1회 피해',damage === null || guardPower === null ? null : Math.max(0,damage - nativeInt(f(f(damage) * f(Math.min(10000,guardPower) / 10000)))),'HP',['incomingDamage','baseGuardPower']);
    [['GUARD_RECHARGE','baseGuardRecharge','guardRecharge','Guard'],['AVOID_RECHARGE','baseAvoidRecharge','avoidRecharge','Avoid']].forEach(function (entry) {
      var base = input(settings,entry[1]);
      row(values,entry[2],entry[3] + ' 회복량',base === null ? null : Math.max(1,Math.trunc((100 + stat(entry[0])) * base / 100)),'',[entry[1]]);
    });
    var mentality = input(settings,'mentality');
    row(values,'ailmentResistance','MTL·옵션 적용 후 상태 이상 내성',mentality === null ? null : Math.min(100,Math.trunc(mentality * 10 / 34) + Math.trunc(stat('AILMENT_RES'))),'%',['mentality']);
    var barrierBase = input(settings,'baseBarrierCooldown');
    row(values,'barrierCooldown','옵션 적용 후 배리어 재사용 시간',barrierBase === null ? null : Math.trunc(barrierBase) - nativeInt(f(f(f(Math.min(100,stat('BARR_SPEED'))) * 20) / 100)),'초',['baseBarrierCooldown']);
    var dodgeChance = Math.max(0,Math.min(30,Math.trunc(stat('ABS_DODGE'))));
    var dodgeRoll = input(settings,'absoluteDodgeRoll'), dodgeEligible = booleanInput(settings,'absoluteDodgeEligible');
    if (dodgeRoll !== null && !Number.isInteger(dodgeRoll)) throw new Error('absoluteDodgeRoll: 0~99 정수 난수가 필요합니다.');
    row(values,'absoluteDodgeChance','옵션 절대회피 확률 (상한 30%)',dodgeChance,'%');
    row(outcomes,'absoluteDodge','해당 난수·공격 조건의 절대회피',dodgeEligible === null || dodgeRoll === null ? null : dodgeEligible && dodgeRoll < dodgeChance,'',['absoluteDodgeEligible','absoluteDodgeRoll']);
    return {values:values,outcomes:outcomes,rows:rows,requirements:requirements.map(function (entry) { return Object.assign({},entry); })};
  }
  var supportedKeys = ['PHYS_RES','MAG_RES'].concat(elements.map(function (entry) { return entry[0]; }),shapes.map(function (entry) { return entry[0]; }),
    ['PHYS_BARR','MAG_BARR','FRAC_BARR','GUARD_POWER','GUARD_RECHARGE','AVOID_RECHARGE','REFLECT','AILMENT_RES','BARR_SPEED','ABS_DODGE']);
  var inputDefinitions = Object.freeze(requirements.reduce(function (all, entry) { all[entry.key] = Object.freeze(Object.assign({},entry)); return all; },{}));
  var api = Object.freeze({evaluate:evaluate,resistDamage:resistDamage,shapeStat:shapeStat,supportedKeys:Object.freeze(supportedKeys),inputDefinitions:inputDefinitions});
  if (typeof module === 'object' && module.exports) module.exports = api;
  if (root) root.ToramOptionEvents = api;
}(typeof window !== 'undefined' ? window : globalThis));
