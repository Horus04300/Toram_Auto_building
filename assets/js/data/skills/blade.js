/* 블레이드: 원문 대조가 끝난 오라 블레이드·램페이지 규칙. */
(function () {
  'use strict';
  var registry = window.ToramSkillEffectRegistry;
  var catalog = window.TORAM_SKILL_COMBAT_CATALOG;
  if (!registry || !catalog) throw new Error('블레이드 효과 데이터는 등록기와 전투 카탈로그 뒤에 로드되어야 합니다.');
  var v=function(n){return {op:'value',value:n};}, r=function(path){return {op:'ref',path:path};};
  var l=function(){return r('skill.level');}, a=function(){return {op:'add',args:[].slice.call(arguments)};};
  var m=function(){return {op:'multiply',args:[].slice.call(arguments)};}, e=function(left,right){return {op:'eq',left:left,right:right};};
  var all=function(){return {op:'all',args:[].slice.call(arguments)};}, not=function(value){return {op:'not',value:value};};
  var weapon=function(name){return e(r('equipment.mainWeapon'),v(name));};
  var dualSword=all(weapon('한손검'),e(r('equipment.subWeapon'),v('한손검(듀얼소드)')));
  var oneHand=all(weapon('한손검'),not(dualSword));
  var oneHandMain=weapon('한손검'), twoHand=weapon('양손검');
  var any=function(){return {op:'any',args:[].slice.call(arguments)};}, bladeWeapon=any(oneHandMain,twoHand);
  var s=function(left,right){return {op:'subtract',left:left,right:right};};
  var d=function(left,right){return {op:'divide',left:left,right:right};};
  var i=function(when,yes,no){return {op:'if',when:when,then:yes,else:no||v(0)};};
  var min=function(){return {op:'min',args:[].slice.call(arguments)};};
  var floor=function(value){return {op:'floor',value:value};};
  var truthy=function(value){return {op:'truthy',value:value};};
  var gte=function(left,right){return {op:'gte',left:left,right:right};};
  var between=function(low,high,result){return {when:all(gte(l(),v(low)),{op:'lte',left:l(),right:v(high)}),value:v(result)};};
  var tier=function(cases){return {op:'tier',cases:cases};};
  var input=function(id){return r('attack.inputs.'+id);};
  var base=function(key){return r('baseStats.'+key);}, total=function(key){return r('combatStats.'+key);};
  var shield=e(r('equipment.subWeapon'),v('방패'));
  function identity(id,kind,anchor){var item=catalog.skills.find(function(skill){return skill.id==='Blade:'+id;});if(!item)throw new Error('Blade:'+id+' 스킬을 찾지 못했습니다.');return {id:item.id,treeId:'Blade',skillId:id,nameKo:item.nameKo,kind:kind,source:'blade',dataStatus:'partial',sourceRef:{file:'docs/sources/skills/Blade.txt',anchor:anchor}};}
  var aura = catalog.skills.find(function (item) { return item.id === 'Blade:16'; });
  var rampage = catalog.skills.find(function (item) { return item.id === 'Blade:8'; });
  if (!aura || !rampage) throw new Error('블레이드 스킬을 카탈로그에서 찾지 못했습니다.');
  registry.register('Blade', [
    Object.assign(identity(0,'attack','해머 다운 물리 액티브 / 양손검 전용'),{
      requirements:{when:twoHand},inputs:[{id:'consecutive',label:'연속 사용',type:'boolean',default:false}],cost:{mp:{timing:'cast',value:i(truthy(input('consecutive')),v(0),v(100))}},
      attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(v(1),m(v(.5),l()),d(total('VIT'),v(100))),constant:v(100),flags:{longRange:false,unsheathe:false,areaRadius:3,guaranteedCriticalWhen:'target.incapacitated',normalProrationWhenConsecutive:true,comboDisabledWhenConsecutive:true}}]
    }),
    Object.assign(identity(1,'attack','클리브 어택 물리 액티브 / 양손검 전용'),{
      requirements:{when:twoHand},inputs:[{id:'targetsHit',label:'적중한 적 수',type:'number',min:v(1),max:v(4),default:v(1)}],cost:{mp:{timing:'cast',value:v(300)}},
      attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(v(1.5),m(v(.1),l()),m(d(total('STR'),v(200)),s(input('targetsHit'),v(1)))),constant:a(v(150),m(v(15),l()),total('VIT')),flags:{longRange:false,unsheathe:false,areaRadius:3}}],
      effects:[{phase:'afterHit',type:'mpRestore',value:min(v(300),m(v(100),s(input('targetsHit'),v(1))))}]
    }),
    Object.assign(identity(2,'attack','스톰 블레이저 물리 액티브 / 양손검 전용'),{
      requirements:{when:twoHand},inputs:[{id:'stacks',label:'소모 스택',type:'number',min:v(0),max:v(10),default:v(0)}],cost:{mp:{timing:'cast',value:v(200)}},
      stackModel:{mode:'combat-resource',stateId:'blade.stormBlazer',initialStacks:v(0),hardCap:a(v(10),floor(d(base('DEX'),v(25)))),castConsumeCap:v(10),gainEvents:[{event:'hammerDownHit',stacks:v(1)},{event:'normalAttackHit',stacks:v(1)},{event:'rampageNormalAttackHit',stacks:v(2)}],notes:'현재 엔진은 적중 이벤트에 따른 자동 누적·시전 소모를 처리하지 않는다.'},
      stateTransitions:[{event:'cast',operation:'consumeStacks',stateId:'blade.stormBlazer',stacks:input('stacks'),maxStacks:a(v(10),floor(d(base('DEX'),v(25))))}],
      attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:m(a(v(.5),m(v(.05),l())),input('stacks')),constant:a(v(100),m(v(10),l()),total('VIT')),flags:{longRange:true,unsheathe:false,castRange:16,lineLength:16,areaRadius:a(v(2),m(v(.4),input('stacks')))}}],
      effects:[{phase:'afterHit',type:'mpRestore',value:m(v(4),input('stacks'),input('stacks'))}]
    }),
    Object.assign(identity(3,'buff','가드 블레이드 버프 / 양손검 전용'),{
      requirements:{when:twoHand},cost:{mp:{timing:'cast',value:v(300)}},combo:{canStart:true,canReceiveTag:true},
      stateModel:{mode:'guard-resource',stateId:'blade.guardBlade',durationSeconds:v(70),initialGuardPower:min(v(10000),a(m(v(250),l()),m(total('VIT'),v(10)))),endsAtZero:true,recastBlockedUntilGuardEnabled:true,notes:'가드력 소진·저스트 가드 이벤트와 무기 제련 내성은 현재 엔진 미지원.'},
      stateTransitions:[{event:'cast',operation:'grant',stateId:'blade.guardBlade',stacks:v(1),maxStacks:v(1),durationSeconds:v(70)}],
      effects:[{phase:'combat',type:'stat',key:'PHYS_RES',value:l()},{phase:'combat',type:'stat',key:'MAG_RES',value:l()},{phase:'combat',type:'weaponRefinementAsArmorRefinement',notes:'무기 제련치만큼 제련 내성을 추가'},{phase:'combat',type:'justGuardAilmentImmunity',notes:'저스트 가드 성공 시 기죽음·넘어짐·기절·넉백 무효'}]
    }),
    Object.assign(identity(4,'attack','오거 슬래시 물리 액티브 / 양손검 전용'),{
      requirements:{when:twoHand},inputs:[{id:'stacks',label:'소모 스택',type:'number',min:v(0),max:v(10),default:v(0)}],cost:{mp:{timing:'cast',value:v(500)}},activeBuff:true,
      stackModel:{mode:'combat-resource',stateId:'blade.ogreSlash',initialStacks:d(l(),v(2)),hardCap:v(20),castConsumeCap:v(10),gainEvents:[{event:'enterWarningArea',stacks:v(1)},{event:'takeHit',stacks:v(1)},{event:'justGuard',stacks:v(1)}],notes:'전투 시작·피격·저스트 가드 이벤트 자동 누적은 현재 엔진 미지원.'},
      stateTransitions:[{event:'cast',operation:'consumeStacks',stateId:'blade.ogreSlash',stacks:input('stacks'),maxStacks:v(20)},{event:'cast',operation:'grant',stateId:'blade.ogreSlash.buff',stacks:v(1),maxStacks:v(1),durationSeconds:a(v(10),m(v(5),l()))}],
      attacks:[{id:'slash',damageType:'physical',count:v(1),multiplier:d(a(base('STR'),base('VIT')),v(100)),constant:total('DEX'),flags:{longRange:false,unsheathe:false,physicalPierceBonus:m(l(),input('stacks')),excessPhysicalPierceToMultiplier:.01,controlAilmentImmunityDuringCast:true}},{id:'explosion',damageType:'physical',count:v(1),multiplier:m(v(2),input('stacks')),constant:v(500),flags:{longRange:false,unsheathe:false,delaySeconds:4,areaRadius:2,physicalPierceBonus:m(l(),input('stacks'))}}],
      effects:[{phase:'combat',type:'mpSpendHpRecovery',notes:'MP 소모량/10의 제곱만큼 HP 회복'},{phase:'combat',type:'damageMultiplier',target:'rampageNormalAndFinish',value:v(2)},{phase:'combat',type:'berserkStabilityPenaltyMultiplier',value:v(.5)}]
    }),
    Object.assign(identity(5,'attack','하드 히트 물리 액티브 / 한손검, 양손검 전용'),{
      requirements:{when:bladeWeapon},cost:{mp:{timing:'cast',value:v(100)}},attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(v(1),m(v(.05),l()),i(twoHand,v(.5),v(0))),constant:a(v(50),m(v(5),l())),flags:{longRange:false,unsheathe:false}}],effects:[{phase:'hit',type:'ailmentChance',key:'flinch',chance:a(m(v(5),l()),i(oneHandMain,v(50),v(0)))}]
    }),
    Object.assign(identity(9,'attack','메테오 브레이커 물리 액티브 / 한손검, 양손검 전용'),{
      requirements:{when:bladeWeapon},cost:{mp:{timing:'cast',value:v(600)}},
      attacks:[{id:'hit1',damageType:'physical',count:v(1),multiplier:a(v(4),m(v(.2),l()),i(twoHand,a(v(2),d(base('STR'),v(1000))),v(0))),constant:a(v(400),m(v(20),l())),flags:{longRange:false,unsheathe:false}},{id:'hit2',damageType:'physical',count:v(1),multiplier:a(v(1),m(v(.5),l()),i(oneHandMain,d(base('DEX'),v(100)),v(0))),constant:v(0),flags:{longRange:false,unsheathe:false,areaRadius:tier([between(1,3,2),between(4,6,2.5),between(7,9,3),between(10,10,3.5)])}}],
      effects:[{phase:'hit',type:'ailmentChance',key:'dizzy',chance:a(m(v(2.5),l()),i(oneHandMain,v(75),v(0)))}],stateTransitions:[{event:'airborneMotion',operation:'grant',stateId:'blade.meteorBreaker.invulnerable',stacks:v(1),maxStacks:v(1),durationSeconds:v(0)}]
    }),
    Object.assign(identity(10,'attack','셧아웃 물리 액티브 / 한손검, 양손검 전용'),{
      requirements:{when:bladeWeapon},inputs:[{id:'targetIncapacitated',label:'대상 행동 불능',type:'boolean',default:false},{id:'bleedApplied',label:'출혈 부여 성공',type:'boolean',default:false}],cost:{mp:{timing:'cast',value:v(100)}},
      attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:i(all(truthy(input('targetIncapacitated')),truthy(input('bleedApplied'))),a(v(10),l(),i(oneHand,a(v(5),d(base('DEX'),v(100))),v(0)),i(dualSword,a(v(5),d(base('AGI'),v(200))),v(0))),a(v(5),i(oneHand,d(base('DEX'),v(200)),v(0)),i(twoHand,l(),v(0)),i(dualSword,d(base('AGI'),v(400)),v(0)))),constant:v(100),flags:{longRange:false,unsheathe:false,enhancedPhysicalPierceMultiplier:{oneHand:4,twoHand:2},motionSpeedDisabledWhenTwoHand:true}}],effects:[{phase:'hit',type:'ailmentChance',key:'bleed',when:truthy(input('targetIncapacitated')),chance:v(100),durationSeconds:v(10)}]
    }),
    Object.assign(identity(11,'attack','문 슬래시 물리 액티브 / 한손검, 양손검 전용'),{
      requirements:{when:bladeWeapon},inputs:[{id:'stacks',label:'양손검 추가타 스택',type:'number',min:v(0),max:v(9),default:v(0)}],cost:{mp:{timing:'cast',value:v(400)}},
      stackModel:{mode:'combo-position-resource',stateId:'blade.moonSlash',hardCap:v(9),gainRule:'콤보 없이 1, 콤보 사용 시 문 슬래시의 콤보 위치만큼 획득',consumeRule:'공격 스킬 적중 대상마다 1, 스킬 1회당 대상별 최대 1',notes:'콤보 위치·다중 대상 적중에 따른 자동 증감은 현재 엔진 미지원.'},stateTransitions:[{event:'attackSkillHit',when:all(twoHand,{op:'gt',left:input('stacks'),right:v(0)}),operation:'consumeStacks',stateId:'blade.moonSlash',stacks:v(1),maxStacks:v(9)}],
      attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:v(10),constant:v(400),flags:{longRange:false,unsheathe:false}},{id:'followup',damageType:'physical',count:v(1),multiplier:m(v(.001),l(),total('STR')),constant:d(base('INT'),v(2)),flags:{longRange:false,unsheathe:false}},{id:'twoHandExtra',when:all(twoHand,{op:'gt',left:input('stacks'),right:v(0)}),damageType:'physical',count:v(1),multiplier:m(v(.001),l(),total('STR')),constant:base('INT'),flags:{longRange:false,unsheathe:false,fixedCriticalChance:a(m(v(10),l()),base('CRT')),ignoresComboDamageChange:true}}],effects:[{phase:'hit',type:'ailmentChance',key:'fatigue',chance:m(v(6),l())}]
    }),
    Object.assign(identity(12,'attack','액셀 블레이드 물리 액티브 / 한손검, 양손검 전용'),{
      requirements:{when:bladeWeapon},inputs:[{id:'distance',label:'시전 거리(m)',type:'number',min:v(0),max:v(24),default:v(8)},{id:'hyper',label:'하이퍼 액셀블레이드',type:'boolean',default:false}],cost:{mp:{timing:'cast',value:v(200)}},
      attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:m(a(v(1),m(v(.05),l()),i(twoHand,v(.5),v(0)),i(gte(input('distance'),v(8)),m(v(.1),s(input('distance'),v(7))),v(0))),i(truthy(input('hyper')),v(2),v(1))),constant:a(v(100),m(v(5),l())),flags:{longRange:true,unsheathe:false,castRange:tier([between(1,3,8),between(4,6,12),between(7,9,16),between(10,10,20)]),oneHandCastRangeBonus:4,areaRadius:a(v(1),i(twoHand,v(2),v(0)),i(truthy(input('hyper')),v(1),v(0))),criticalChanceBonus:a(l(),i(oneHandMain,m(v(9),l()),v(0)))}}],stateTransitions:[{event:'cast',operation:'grant',stateId:'blade.accelBlade.hyper',stacks:v(1),maxStacks:v(1),durationSeconds:v(5),notes:'5초 동안 계수 2배·돌진 속도 증가·히트 범위 +1m'}]
    }),
    Object.assign(identity(14,'attack','소드 템페스트 물리 액티브 / 한손검, 양손검 전용'),{
      requirements:{when:bladeWeapon},cost:{mp:{timing:'cast',value:v(400)}},attacks:[{id:'bladeWave',damageType:'physical',count:v(1),multiplier:a(v(1.5),m(v(.1),l()),i(twoHand,a(v(1),d(base('STR'),v(500))),v(0))),constant:v(0),flags:{longRange:true,unsheathe:false,castRange:12,inertia:'physical'}},{id:'tornado',damageType:'physical',count:tier([between(1,2,2),between(3,4,3),between(5,6,4),between(7,8,5),between(9,10,6)]),multiplier:a(v(.5),m(v(.05),l()),i(oneHandMain,d(base('DEX'),v(500)),v(0))),constant:v(80),flags:{longRange:false,unsheathe:false,inertia:'magic',areaRadius:tier([between(1,2,3),between(3,5,4),between(6,8,5),between(9,10,6)])}}]
    }),
    Object.assign(identity(15,'attack','버스터 블레이드 물리 액티브 / 한손검, 양손검 전용'),{
      requirements:{when:bladeWeapon},activeBuff:true,inputs:[{id:'auraBladeLevel',label:'오라 블레이드 레벨',type:'number',min:v(0),max:v(10),default:v(0)},{id:'shieldRefinement',label:'방패 제련치',type:'number',min:v(0),max:v(15),default:v(0)}],cost:{mp:{timing:'cast',value:v(300)}},
      attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(m(v(.75),l()),i(oneHand,a(d(base('DEX'),v(200)),i(gte(input('auraBladeLevel'),v(1)),a(m(v(.2),input('auraBladeLevel')),d(base('DEX'),v(200))),v(0))),v(0)),i(twoHand,d(base('STR'),v(100)),v(0))),constant:m(v(30),l()),flags:{longRange:false,unsheathe:false,castRange:7,guaranteedCritical:true}}],
      stateTransitions:[{event:'castWhenBuffInactive',operation:'grant',stateId:'blade.busterBlade',stacks:v(1),maxStacks:v(1),durationSeconds:v(10),effects:[{phase:'combat',type:'stat',key:'WATKP',value:a(v(10),i(shield,input('shieldRefinement'),v(0)))}]}],effects:[{phase:'combat',type:'stat',key:'WATKP',when:truthy(r('buff.active')),value:a(v(10),i(shield,input('shieldRefinement'),v(0)))},{phase:'castWhenBuffInactive',type:'hpRestore',value:a(v(1000),i(oneHand,m(v(2),base('VIT')),v(0)),i(shield,base('VIT'),v(0)))}]
    }),
    Object.assign(identity(21,'buff','버서크 버프 / 모든 무기 사용 가능'),{
      cost:{mp:{timing:'cast',value:v(500)}},stateTransitions:[{event:'cast',operation:'grant',stateId:'blade.berserk',stacks:v(1),maxStacks:v(1),durationSeconds:a(v(10),i(bladeWeapon,v(20),v(0)))}],
      effects:[{phase:'combat',type:'normalAttackModifier',key:'multiplier',value:m(v(.1),l())},{phase:'combat',type:'stat',key:'ASPD_P',value:m(v(10),l())},{phase:'combat',type:'stat',key:'ASPD',value:m(v(100),l())},{phase:'combat',type:'stat',key:'CRIT',value:m(v(2.5),l(),i(twoHand,v(2),v(1)))},{phase:'combat',type:'stat',key:'STABILITY',value:m(v(-1),s(v(100),m(v(5),l())),i(bladeWeapon,v(.5),v(1))),notes:'듀얼소드 서브 안정률에는 적용하지 않음'},{phase:'combat',type:'stat',key:'DEF_P',value:m(v(-1),s(v(100),l()),i(oneHand,v(.5),v(1)))},{phase:'combat',type:'stat',key:'MDEF_P',value:m(v(-1),s(v(100),l()),i(oneHand,v(.5),v(1)))},{phase:'combat',type:'rampageAilmentEndImmunity',value:v(1)}]
    }),
    Object.assign(identity(22,'buff','글래디에이트 버프 / 한손검, 양손검 전용'),{
      requirements:{when:bladeWeapon},cost:{mp:{timing:'cast',value:v(0)}},combo:{canStart:false,canReceiveTag:true},stackControl:{stateId:'blade.gladiate',minStacks:v(0),maxStacks:l(),initialStacks:l(),label:'남은 경감 횟수'},
      stackModel:{mode:'finite-hits',hardCap:l(),consumeEvent:'takeHit',expirationMpRestorePerRemainingStack:v(10),notes:'피격 시 AMPR 비율 회복과 종료 시 잔여 횟수 MP 회복은 실시간 전투 이벤트 엔진 미지원.'},stateTransitions:[{event:'cast',operation:'grant',stateId:'blade.gladiate',stacks:l(),maxStacks:l(),durationSeconds:v(10)},{event:'takeHit',operation:'consumeStacks',stateId:'blade.gladiate',stacks:v(1),maxStacks:l()}],
      effects:[{phase:'combat',type:'damageReduction',value:m(l(),i(any(shield,dualSword,twoHand),v(2),v(1)))},{phase:'takeHit',type:'mpRestoreFromAmpr',value:i(twoHand,v(.75),i(dualSword,v(.25),v(1))),notes:'듀얼소드는 2배 적용 후 AMPR의 25%'},{phase:'expiration',type:'mpRestorePerRemainingStack',value:v(10)}]
    }),
    Object.assign(identity(23,'attack','퍼스트 어택 물리 액티브 / 한손검, 양손검 전용'),{
      requirements:{when:bladeWeapon},cost:{mp:{timing:'cast',value:i(dualSword,v(200),v(300))}},
      attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(min(v(.5),a(v(.05),m(v(.05),l()))),i(oneHand,d(total('DEX'),v(500)),v(0)),i(dualSword,d(total('AGI'),v(500)),v(0)),i(twoHand,d(total('STR'),v(500)),v(0))),constant:min(v(300),m(v(3),a(l(),v(1)),a(l(),v(1)))),flags:{longRange:false,unsheathe:false}}],effects:[{phase:'hit',type:'ailmentChance',key:'tumble',when:dualSword,chance:a(v(50),m(v(5),l()))}],
      stateTransitions:[{event:'cast',when:e(l(),v(10)),operation:'grant',stateId:'blade.firstAttack.nextSkillMpHalf',stacks:v(1),maxStacks:v(1),durationSeconds:v(0),effects:[{phase:'cast',type:'nextSkillModifier',key:'mpCostMultiplier',value:v(.5)}]}]
    }),
    {
      id:aura.id, treeId:'Blade', skillId:16, nameKo:aura.nameKo, kind:'attack', activeBuff:true,
      source:'blade', dataStatus:'partial', sourceRef:{file:'docs/sources/skills/Blade.txt',anchor:'오라 블레이드 물리 액티브'},
      requirements:{when:{op:'in',value:r('equipment.mainWeapon'),values:['한손검','양손검']}}, cost:{mp:{timing:'cast',value:v(200)}}, combo:{canStart:true,canReceiveTag:true},
      attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(v(5),l()),constant:v(200),flags:{longRange:true,unsheathe:false,castRange:null,areaRadius:3.5}}],
      stateTransitions:[{event:'cast',operation:'grant',stateId:'bladeAura',stacks:v(1),maxStacks:v(1),durationSeconds:v(40),endCondition:{event:'nextSkillCast',when:{op:'any',args:[weapon('양손검'),dualSword]}},extension:{event:'busterBladeBuffGranted',seconds:v(10)},notes:'양손검·듀얼소드는 다음 스킬 사용 시 종료; 버스터 블레이드 버프 획득 성공 시 10초 연장'}],
      effects:[
        {phase:'combat',type:'damageMultiplier',target:'attack',when:dualSword,value:v(1.1)},
        {phase:'combat',type:'damageMultiplier',target:'attack',when:oneHand,value:v(1.2)},
        {phase:'combat',type:'damageMultiplier',target:'attack',when:weapon('양손검'),value:v(1.3)},
        {phase:'combat',type:'physicalChaseDamage',when:dualSword,value:m(v(10),l())},
        {phase:'combat',type:'physicalChaseDamage',when:oneHand,value:m(v(10),l())},
        {phase:'combat',type:'physicalChaseDamage',when:weapon('양손검'),value:m(v(5),l())}
      ]
    },
    {
      id:rampage.id, treeId:'Blade', skillId:8, nameKo:rampage.nameKo, kind:'buff', source:'blade', dataStatus:'partial',
      sourceRef:{file:'docs/sources/skills/Blade.txt',anchor:'일정 시간 동안 다음 11회의 통상 공격의 모션을 변경한다.'},
      requirements:{when:{op:'in',value:r('equipment.mainWeapon'),values:['한손검','양손검']}}, cost:{mp:{timing:'cast',value:v(500)}}, combo:{canStart:true,canReceiveTag:false},
      stackControl:{stateId:'bladeRampage',minStacks:v(0),maxStacks:v(11),initialStacks:v(11),label:'남은 타격'},
      stateTransitions:[{event:'cast',operation:'grant',stateId:'bladeRampage',stacks:v(11),maxStacks:v(11),durationSeconds:v(600),endConditions:['allStacksConsumed','ailmentApplied'],recastAllowed:false}],
      stackModel:{mode:'finite-attacks',hardCap:v(11),endsOnAilment:true,recastAllowed:false,powerWaveDisabled:true,notes:'버서크 활성 중에는 상태이상으로 종료되지 않는다. 통상 공격·상태이상 이벤트 자동 소모는 현재 미지원.'},
      effects:[
        {phase:'combat',type:'stat',key:'AMPR',value:m(v(2.5),l())},
        {phase:'combat',type:'normalAttackModifier',key:'multiplier',value:a(v(.1),m(v(.04),l()),{op:'if',when:oneHandMain,then:m(v(.05),l()),else:v(0)})},
        {phase:'combat',type:'normalAttackModifier',key:'constant',value:m(v(10),l())},
        {phase:'combat',type:'disableSkill',key:'powerWave',value:v(1)}
      ],
      specialAttacks:[{trigger:'finalStack',id:'finishAttack',hits:[
        {multiplier:a(v(.5),m(v(.05),l()),{op:'if',when:weapon('양손검'),then:v(1),else:v(0)}),constant:a(v(300),m(v(20),l()))},
        {multiplier:a(v(.5),m(v(.05),l()),{op:'if',when:weapon('양손검'),then:v(1),else:v(0)}),constant:a(v(300),m(v(20),l()))},
        {multiplier:a(v(2.5),m(v(.05),l()),{op:'if',when:weapon('양손검'),then:v(3),else:v(0)}),constant:a(v(300),m(v(20),l()))}
      ],flags:{guaranteedHit:true,damageReductionDuringMotion:90,longRange:false,unsheathe:false},notes:'피니시 어택은 콤보 피해 변화·행동 속도·장인의 검술 영향을 받지 않음'}]
    }
  ]);
}());