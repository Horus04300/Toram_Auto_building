/* 나이트 S1~S5 계산기 범위 정의. 피격·어그로·시간 전이는 메타데이터로 보존한다. */
(function () {
  'use strict';
  var R=window.ToramSkillEffectRegistry,C=window.TORAM_SKILL_COMBAT_CATALOG;
  if(!R||!C) throw new Error('Knight S5 data order');
  var v=function(x){return {op:'value',value:x};},r=function(x){return {op:'ref',path:x};},l=function(){return r('skill.level');};
  var a=function(){return {op:'add',args:[].slice.call(arguments)};},m=function(){return {op:'multiply',args:[].slice.call(arguments)};},d=function(x,y){return {op:'divide',left:x,right:y};},q=function(w,y,n){return {op:'if',when:w,then:y,else:n};};
  var i=function(x){return r('attack.inputs.'+x);},total=function(x){return r('combatStats.'+x);},base=function(x){return r('baseStats.'+x);};
  var eq=function(x,y){return {op:'eq',left:x,right:y};},lte=function(x,y){return {op:'lte',left:x,right:y};},truthy=function(x){return {op:'truthy',value:x};},all=function(){return {op:'all',args:[].slice.call(arguments)};};
  var one=eq(r('equipment.mainWeapon'),v('한손검')),two=eq(r('equipment.mainWeapon'),v('양손검')),blade={op:'any',args:[one,two]},shield=eq(r('equipment.subWeapon'),v('방패')),active=truthy(r('buff.active'));
  function D(id,kind,anchor,when){var s=C.skills.find(function(x){return x.id==='Knight:'+id;});if(!s)throw Error('Knight catalog missing: '+id);return {id:s.id,treeId:'Knight',skillId:id,nameKo:s.nameKo,kind:kind,source:'knight',dataStatus:'partial',sourceRef:{file:'docs/sources/skills/Knight.txt',anchor:anchor},requirements:{when:when},notes:'S1~S5 calculator scope; automatic aggro, hit, and time events remain metadata.'};}
  function hit(id,mult,constant,flags){return {id:id,damageType:'physical',count:v(1),multiplier:mult,constant:constant,flags:Object.assign({longRange:true,unsheathe:false},flags||{})};}
  function willBonus(mult){return q(eq(l(),v(10)),m(v(mult),r('investments.Knight.8'),q(shield,v(1),v(.5))),v(0));}
  var x=[
    D(0,'attack','1차 어솔트 어택 물리 액티브 / 모든 무기 사용 가능',null),
    D(1,'passive','2차 파리 패시브 / 모든 무기 사용 가능',null),
    D(2,'buff','3차P 디펜스 버프 / 방패 전용',shield),
    null,
    D(4,'passive','5차에프터 실드 패시브 / 한손검 전용',one),
    D(5,'utility','프로보크 액티브 / 모든 무기 사용 가능',null),
    D(6,'attack','레이지 소드 물리 액티브 / 한손검, 양손검 전용',blade),
    D(7,'attack','바인드 스트라이크 물리 액티브 / 한손검, 양손검 전용',blade),
    D(8,'passive','나이트 윌 패시브 / 모든 무기 사용 가능',null),
    D(9,'attack','블링크 소드 물리 액티브 / 한손검 전용',one),
    D(10,'attack','소닉 슬라스트 물리 액티브 / 한손검 전용',one),
    D(11,'attack','루브닐 물리 액티브 / 한손검 전용',one),
    D(12,'buff','나이트 스탠스 버프 / 한손검 전용',one),
    D(13,'passive','나이트 힐 패시브 / 한손검 전용',one),
    D(14,'buff','나이트 플레지 버프 / 한손검 전용',one)
  ];
  x[0]=Object.assign(x[0],{inputs:[],cost:{mp:{timing:'cast',value:v(100)}},attacks:[hit('main',a(v(.25),m(v(.1),l()),q(shield,v(.25),v(0)),willBonus(.6)),a(m(v(5),l()),q(shield,v(50),v(0))),{castRange:6,knockbackChance:a(m(v(10),l()),q(shield,v(50),v(0))),slowChance:m(v(10),l())})]});
  x[1]=Object.assign(x[1],{inputs:[],effects:[{phase:'combat',type:'physicalDamageReductionChance',chance:a(q(lte(l(),v(5)),m(v(5),l()),a(m(v(5),l()),v(-20))),willBonus(2)),reductionPercent:q(lte(l(),v(5)),v(10),v(20)),notes:'guard와 동시 발동하지 않으며 실제 피격 판정은 전투 상태 엔진이 필요하다.'}]});
  x[2]=Object.assign(x[2],{cost:{mp:{timing:'cast',value:v(100)}},activeBuff:true,stateTransitions:[{event:'cast',operation:'grant',stateId:'knight.pDefense',stacks:v(1),maxStacks:v(1),durationSeconds:v(1),effects:[{type:'damageNullify',value:v(100)}]}],effects:[{phase:'onDefenseSuccess',type:'fixedAggro',value:m(v(50),m(l(),l()))},{phase:'onDefenseSuccess',type:'hpRestorePercent',value:l(),notes:'레벨별 회복 상한 및 나이트 윌 Lv.10 보너스는 피격 성공 상태가 필요하다.'}]});
  x[4]=Object.assign(x[4],{effects:[{phase:'build',type:'stat',key:'NEUTRAL_RES',value:l()},{phase:'combat',type:'afterShieldState',durationSeconds:l(),damageReductionByRemainingSecondsPercent:v(5),lethalSingleHitNullify:true,cooldownSeconds:v(20),notes:'P 디펜스 종료·피격 이벤트에 따라 생성·소진한다.'}]});
  x[5]=Object.assign(x[5],{inputs:[],cost:{mp:{timing:'cast',value:q(lte(l(),v(5)),v(400),q(lte(l(),v(9)),v(300),v(200)))}},combo:{canStart:false,canReceiveTag:true},effects:[{phase:'cast',type:'fixedAggro',value:a(v(5000),m(v(500),l()),willBonus(500)),notes:'MP 사용·어그로% 옵션의 영향을 받지 않는다.'}]});
  x[6]=Object.assign(x[6],{inputs:[{id:'targetAggroSelf',label:'대상이 자신을 어그로 대상으로 함',type:'boolean',default:false}],cost:{mp:{timing:'cast',value:v(200)}},attacks:[hit('main',a(v(1.5),m(v(.1),l()),q(shield,a(v(.3),d(total('VIT'),v(200))),v(0)),willBonus(.5)),a(v(150),m(v(5),l())),{guaranteedCriticalWhen:'targetAggroSelf'})],stateTransitions:[{event:'cast',when:truthy(i('targetAggroSelf')),operation:'grant',stateId:'knight.rageSword.nextMpHalf',stacks:v(1),maxStacks:v(1),durationSeconds:v(0),effects:[{type:'nextSkillModifier',key:'mpCostMultiplier',value:v(.5)}]}],effects:[{phase:'cast',type:'additionalAggro',value:a(v(500),m(v(100),l()),willBonus(350))}]});
  x[7]=Object.assign(x[7],{inputs:[],cost:{mp:{timing:'cast',value:v(300)}},attacks:[hit('main',a(v(4.5),m(v(.05),l()),q(shield,a(v(1.5),d(total('VIT'),v(50))),v(0)),willBonus(.4)),a(v(50),m(v(10),l()),q(shield,v(150),v(0))),{areaRadius:q(eq(l(),v(10)),v(5),q(lte(l(),v(5)),v(3),v(4))),stopChance:m(v(10),l())})],effects:[{phase:'cast',type:'additionalAggro',value:a(v(1000),m(v(100),l()))}]});
  x[8]=Object.assign(x[8],{effects:[{phase:'combat',type:'aggroPercentWhenTargeted',value:m(v(2),l()),shieldMultiplier:v(.5),notes:'적이 자신을 어그로 대상으로 할 때만 적용. Lv.10이면 관련 기사 스킬의 보너스를 활성화한다.'}]});
  x[9]=Object.assign(x[9],{inputs:[{id:'flinchSuccess',label:'기죽음 부여 성공',type:'boolean',default:false}],cost:{mp:{timing:'cast',value:v(200)}},attacks:[hit('main',a(v(5),m(v(.75),l()),q(all(shield,truthy(i('flinchSuccess'))),d(base('VIT'),v(100)),v(0))),v(200),{castRange:14,flinchChance:a(m(v(5),l()),q(shield,v(50),v(0))),guaranteedHitWhen:'flinchSuccess'})],stateTransitions:[{event:'castWhenHit',operation:'grant',stateId:'knight.blinkSword',stacks:v(1),maxStacks:v(1),durationSeconds:v(3),effects:[{type:'percentageDamageReduction',value:m(v(3),l())},{type:'farethStackMoveProtection',value:v(1)}]}]});
  x[10]=Object.assign(x[10],{cost:{mp:{timing:'cast',value:v(200)}},attacks:[hit('main',a(v(1.5),m(v(.15),l()),q(shield,d(total('DEX'),v(100)),v(0))),v(200),{castRange:8,alwaysMaximumMotionSpeed:true,longRange:true,tumbleChance:m(v(10),l())})],effects:[{phase:'onAilmentResisted',type:'mpRestore',value:v(100),ailment:'tumble'}]});
  x[11]=Object.assign(x[11],{inputs:[{id:'consumedStacks',label:'소모할 루브닐 스택',type:'number',min:v(0),max:v(2),default:v(0)}],cost:{mp:{timing:'cast',value:v(400)}},stackControl:{stateId:'knight.revenir',minStacks:v(0),maxStacks:l(),initialStacks:v(0),label:'루브닐 스택'},stackModel:{mode:'combat-resource',hardCap:l(),gainEvents:['pDefenseSuccess:+1','flinch:+1','tumble:+3','stun:+5'],castConsumeCap:v(2),notes:'상태이상·무적 중 소비 불가와 피격/상태이상 자동 획득은 전투 상태 엔진이 필요하다.'},stateTransitions:[{event:'cast',operation:'consumeStacks',stateId:'knight.revenir',stacks:i('consumedStacks'),maxStacks:l()}],attacks:[Object.assign(hit('main',a(v(5),m(v(.1),l()),d(base('DEX'),v(50))),m(v(40),l()),{guaranteedCriticalWhen:'shield'}),{count:a(v(1),i('consumedStacks'))})]});
  x[12]=Object.assign(x[12],{cost:{mp:{timing:'cast',value:v(100)}},activeBuff:true,stateTransitions:[{event:'cast',operation:'grant',stateId:'knight.stance',stacks:v(1),maxStacks:v(1),durationSeconds:v(360)}],effects:[{phase:'combat',type:'stat',key:'AGGRO_P',when:active,value:a(m(v(2),l()),q(shield,l(),v(0)))},{phase:'combat',type:'stat',key:'VIT',when:active,value:l()},{phase:'combat',type:'targetedFractionalDamageReduction',when:active,value:m(v(.5),l()),shieldMultiplier:v(2),notes:'워크라이 중 공포 내성도 부여; 적·자신의 어그로 방향 일치가 필요하다.'}]});
  x[13]=Object.assign(x[13],{stackModel:{mode:'damage-storage',requires:'knight.stance',storePercent:l(),shieldTargetedMultiplier:v(3),consumeEvent:'knightStanceRecast',notes:'피격 피해와 어그로 방향 일치에 따른 저장/회복은 전투 상태 엔진이 필요하다.'},effects:[{phase:'combat',type:'knightHealStorage',value:l()}]});
  var minimumPledgeRefine=q(lte(l(),v(4)),v(1),q(lte(l(),v(8)),v(2),v(3)));
  x[14]=Object.assign(x[14],{cost:{mp:{timing:'cast',value:v(500)}},activeBuff:true,inputs:[{id:'durability',label:'플레지 원 내구도(%)',type:'number',min:v(0),max:a(v(45),m(v(4.5),l())),default:a(v(45),m(v(4.5),l()))}],stackModel:{mode:'area-barrier',initialDurabilityPercent:a(v(45),m(v(4.5),l())),durabilityLossPerHitPercent:v(10),endsOn:'durabilityZeroOrKnockback',notes:'파티원 수 분산과 피격/넉백에 따른 자동 내구도 변화는 전투 상태 엔진이 필요하다.'},stateTransitions:[{event:'partySkillCast',operation:'grant',stateId:'knight.pledgeCircle',stacks:v(1),maxStacks:v(1),durationSeconds:v(0)}],effects:[{phase:'combat',type:'damageMultiplier',target:'attack',when:active,value:a(v(1),d({op:'max',args:[r('equipment.subWeaponRefinement'),minimumPledgeRefine]},v(100))),notes:'방패 제련치가 레벨별 최소치보다 낮으면 최소 1/2/3%를 적용한다.'},{phase:'combat',type:'pledgeDamageReduction',selfPercent:d(i('durability'),v(10)),partyPercent:i('durability'),dividedByPartyMembers:true},{phase:'combat',type:'knockbackDistanceReduction',value:a(v(15),m(v(2.25),l())),shieldMultiplier:v(2)}]});
  R.register('Knight-s5',x.filter(Boolean));
}());
