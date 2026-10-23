/* 마셜: 22개 원문 출처·종류·무기 조건과 아수라 오라의 양방향 상태·스택 규칙. */
(function () {
  'use strict';
  var registry = window.ToramSkillEffectRegistry;
  var catalog = window.TORAM_SKILL_COMBAT_CATALOG;
  if (!registry || !catalog) throw new Error('마셜 스킬 데이터는 등록기와 전투 카탈로그 뒤에 로드되어야 합니다.');
  var v=function(n){return {op:'value',value:n};}, r=function(path){return {op:'ref',path:path};};
  var l=function(){return r('skill.level');}, m=function(){return {op:'multiply',args:[].slice.call(arguments)};};
  var a=function(){return {op:'add',args:[].slice.call(arguments)};}, d=function(x,y){return {op:'divide',left:x,right:y};}, i=function(w,y,n){return {op:'if',when:w,then:y,else:n||v(0)};};
  var input=function(id){return r('attack.inputs.'+id);}, total=function(k){return r('combatStats.'+k);}, base=function(k){return r('baseStats.'+k);};
  var gte=function(x,y){return {op:'gte',left:x,right:y};}, tier=function(c){return {op:'tier',cases:c};}, between=function(x,y,z){return {when:{op:'all',args:[gte(l(),v(x)),{op:'lte',left:l(),right:v(y)}]},value:z};};
  var active=function(){return {op:'truthy',value:r('buff.active')};};
  var hasStacks=function(){return {op:'gt',left:r('buff.stacks'),right:v(0)};};
  var mainKnuckle={op:'eq',left:r('equipment.mainWeapon'),right:v('권갑')};
  var mainBarehand={op:'eq',left:r('equipment.mainWeapon'),right:v('맨손')};
  var knuckleOrMainBarehand={op:'any',args:[mainKnuckle,mainBarehand]};
  function skeleton(skillId, kind, anchor, requirements, notes) {
    var item=catalog.skills.find(function(candidate){return candidate.id===skillId;});
    if(!item) throw new Error('마셜 카탈로그 스킬을 찾지 못했습니다: '+skillId);
    var definition={id:item.id,treeId:'Martial',skillId:item.skillId,nameKo:item.nameKo,kind:kind,source:'martial',dataStatus:'partial',sourceRef:{file:'docs/sources/skills/Martial.txt',anchor:anchor},requirements:{when:requirements},notes:notes};
    if(kind==='attack') definition.attacks=[];
    else definition.effects=[];
    return definition;
  }
  var definitions=[
    skeleton('Martial:0','attack','스매시 물리 액티브 / 모든 무기 사용 가능',null,'S1/S2 완료. 공격식·기절·권갑 보너스는 S3 대기.'),
    skeleton('Martial:1','attack','배쉬 물리 액티브 / 모든 무기 사용 가능',null,'S1/S2 완료. 공격식·넘어짐·권갑 보너스는 S3 대기.'),
    skeleton('Martial:2','attack','셸 브레이크 물리 액티브 / 모든 무기 사용 가능',null,'S1/S2 완료. 공격식·파괴·MP 회복은 S3 대기.'),
    skeleton('Martial:3','attack','헤비 스매시 물리 액티브 / 모든 무기 사용 가능',null,'S1/S2 완료. 공격식·기절·권갑 보너스는 S3 대기.'),
    skeleton('Martial:4','attack','채리엇 물리 액티브 / 모든 무기 사용 가능',null,'S1/S2 완료. 공격식·시전시간·권갑 보너스는 S3 대기.'),
    skeleton('Martial:5','passive','심상천수 패시브 / 권갑 전용',mainKnuckle,'S1/S2 완료. 분신·수동 avoid·콤보 중단 전이는 S3 대기.'),
    skeleton('Martial:6','attack','첩산고 물리 액티브 / 권갑, 메인 맨손 전용',knuckleOrMainBarehand,'S1/S2 완료. 공격식·파티 스탯·추격 전이는 S3 대기.'),
    skeleton('Martial:7','attack','소닉 웨이브 물리 액티브 / 모든 무기 사용 가능',null,'S1/S2 완료. 공격식·거리·권갑 보너스는 S3 대기.'),
    skeleton('Martial:8','attack','어스 바인드 물리 액티브 / 모든 무기 사용 가능',null,'S1/S2 완료. 공격식·정지·파괴 MP 회복은 S3 대기.'),
    skeleton('Martial:9','attack','트라이 어츠 물리 액티브 / 모든 무기 사용 가능',null,'S1/S2 완료. 3타·타격별 크리티컬·권갑 보너스는 S3 대기.'),
    skeleton('Martial:10','attack','러쉬 물리 액티브 / 모든 무기 사용 가능',null,'S1/S2 완료. 공격식·행동속도 버프는 S3 대기.'),
    skeleton('Martial:12','attack','진각 물리 액티브 / 권갑, 메인 맨손 전용',knuckleOrMainBarehand,'S1/S2 완료. 공격식·상태이상·아수라 상호작용은 S3 대기.'),
    skeleton('Martial:13','attack','선휘 물리 액티브 / 권갑, 메인 맨손 전용',knuckleOrMainBarehand,'S1/S2 완료. 공격식·아수라 스택 MP 회복은 S3 대기.'),
    skeleton('Martial:14','attack','플래시 아트 물리 액티브 / 권갑 전용',mainKnuckle,'S1/S2 완료. avoid 기반 추가타는 S3 대기.'),
    skeleton('Martial:15','passive','머셜 마스터리 패시브 / 메인 권갑 전용',mainKnuckle,'S1/S2 완료. WATKP·ATKP 효과 연결은 S3 대기.'),
    skeleton('Martial:16','passive','체술 단련 패시브 / 권갑 전용',mainKnuckle,'S1/S2 완료. 마셜 피해·ASPD 효과 연결은 S3 대기.'),
    skeleton('Martial:17','buff','차크라 버프 / 모든 무기 사용 가능',null,'S1/S2 완료. AMPR·물리내성·피격 종료·MP 회복은 S3 대기.'),
    skeleton('Martial:18','buff','화경 버프 / 권갑 전용',mainKnuckle,'S1/S2 완료. 피해 감소 성공 시 화경·차크라 획득과 WATKP 공통 상한은 S3 대기.'),
    skeleton('Martial:19','passive','원 찬스 패시브 / 권갑, 메인 맨손 전용',knuckleOrMainBarehand,'S1/S2 완료. AMPR·통상 추가타는 S3 대기.'),
    skeleton('Martial:20','passive','강력한 추격 패시브 / 권갑, 메인 맨손 전용',knuckleOrMainBarehand,'S1/S2 완료. 원 찬스 보정·명중·관통은 S3 대기.'),
    skeleton('Martial:21','attack','슬라이딩 물리 액티브 / 메인 권갑 전용',mainKnuckle,'S1/S2 완료. 다음 스킬 명중 버프는 S3 대기.')
  ];
  definitions[0]=Object.assign(definitions[0],{cost:{mp:{timing:'cast',value:v(100)}},attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(v(.5),m(v(.02),l()),i(mainKnuckle,a(v(.5),m(v(.03),l())),v(0))),constant:a(m(v(5),l()),i(mainKnuckle,a(v(25),d(total('AGI'),v(10))),v(0))),flags:{longRange:false,unsheathe:false,castRange:1}}],effects:[{phase:'hit',type:'ailmentChance',key:'flinch',chance:a(tier([between(1,5,v(50)),between(6,10,v(75))]),i(mainKnuckle,v(25),v(0)))}]});
  definitions[1]=Object.assign(definitions[1],{cost:{mp:{timing:'cast',value:v(200)}},attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(v(1),m(v(.05),l()),i(mainKnuckle,a(v(1),d(total('AGI'),v(500))),v(0))),constant:a(m(v(10),l()),i(mainKnuckle,a(v(50),d(total('AGI'),v(5))),v(0))),flags:{longRange:false,unsheathe:false,castRange:1}}],effects:[{phase:'hit',type:'ailmentChance',key:'stun',chance:a(tier([between(1,5,v(25)),between(6,10,v(50))]),i(mainKnuckle,a(v(25),d(total('AGI'),v(10))),v(0)))}]});
  definitions[2]=Object.assign(definitions[2],{inputs:[{id:'targetDefenseDelta',type:'number',min:v(-50),max:v(250),default:v(0)}],cost:{mp:{timing:'cast',value:v(300)}},attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(v(1),m(v(.05),l()),i(mainKnuckle,a(v(.5),d(input('targetDefenseDelta'),v(50))),v(0))),constant:a(v(50),m(v(10),l()),i(mainKnuckle,a(v(150),m(v(2),input('targetDefenseDelta'))),v(0))),flags:{longRange:false,unsheathe:false,physicalPierceBonus:i(mainKnuckle,m(v(5),l()),v(0))}}],effects:[{phase:'hit',type:'ailmentChance',key:'break',chance:a(v(10),m(v(1.5),l()),i(mainKnuckle,v(25),v(0)))},{phase:'onAilmentSuccess',type:'mpRestore',value:v(400)}]});
  definitions[3]=Object.assign(definitions[3],{inputs:[{id:'targetBroken',type:'boolean',default:false}],cost:{mp:{timing:'cast',value:v(400)}},attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(v(1),m(v(.15),l()),i(mainKnuckle,v(1.5),v(0))),constant:a(v(100),m(v(10),l()),i(mainKnuckle,v(100),v(0))),flags:{longRange:false,unsheathe:false}},{id:'followup',when:{op:'truthy',value:input('targetBroken')},damageType:'physical',count:v(1),multiplier:a(v(1),m(v(.15),l()),i(mainKnuckle,v(5),v(0))),constant:a(v(100),m(v(10),l()),i(mainKnuckle,v(100),v(0))),flags:{guaranteedCritical:true}}]});
  definitions[4]=Object.assign(definitions[4],{cost:{mp:{timing:'cast',value:v(500)}},attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(v(9.9),m(v(.01),l()),i(mainKnuckle,a(v(2.5),d(base('AGI'),v(100))),v(0))),constant:a(v(50),m(v(20),l()),i(mainKnuckle,v(250),v(0))),flags:{longRange:true,unsheathe:false,castRange:12}}]});
  var def=function(id){return definitions.find(function(item){return item.id==='Martial:'+id;});};
  var subKnuckle={op:'eq',left:r('equipment.subWeapon'),right:v('권갑')};
  var hasKnuckle={op:'any',args:[mainKnuckle,subKnuckle]};
  var max=function(){return {op:'max',args:[].slice.call(arguments)};};
  definitions[5]=Object.assign(definitions[5],{stateModel:{mode:'manual-avoid-clone',cooldownSeconds:a(v(20),m(v(-1),l()),i(mainKnuckle,v(-10),v(0))),notes:'대부분의 마셜·크러셔 모션 중 수동 avoid로 분신이 남은 시전을 이어 한다. 분신 종료 뒤 쿨다운, 1개 제한, 콤보는 중단된다.'},effects:[{phase:'combat',type:'manualAvoidClone',notes:'슬라이딩·화경·아수라 오라에서는 사용 불가'}]});
  definitions[6]=Object.assign(definitions[6],{cost:{mp:{timing:'cast',value:v(500)}},attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(v(7.5),m(v(.25),l()),i(mainBarehand,d(max(total('AGI'),total('DEX')),v(100)),v(0))),constant:v(500),flags:{longRange:false,unsheathe:false,castRange:4.5}}],effects:[{phase:'hit',type:'ailmentChance',key:'stun',chance:i(mainKnuckle,v(100),m(v(10),l()))},{phase:'onAilmentResisted',type:'oneChanceEmpowerment',duration:'ailmentResistance',notes:'원 찬스 발동 확률 2배·크리 허용·발동 수당 계수 +0.1(최대 50)'}]});
  definitions[7]=Object.assign(definitions[7],{cost:{mp:{timing:'cast',value:v(100)}},attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(v(.75),m(v(.025),l()),i(mainKnuckle,v(.25),v(0))),constant:a(m(v(5),l()),i(mainKnuckle,v(25),v(0))),flags:{longRange:true,unsheathe:false,castRange:a(tier([between(1,3,v(4)),between(4,6,v(8)),between(7,9,v(12)),between(10,10,v(16))]),i(mainKnuckle,v(4),v(0))),longRangeEnabledAtCastRange:8}}],effects:[{phase:'hit',type:'ailmentChance',key:'tumble',chance:a(m(v(5),l()),i(mainKnuckle,v(50),v(0)))}]});
  definitions[8]=Object.assign(definitions[8],{cost:{mp:{timing:'cast',value:v(100)}},attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(v(1),m(v(.025),l()),i(mainKnuckle,a(v(.25),d(total('AGI'),v(500))),v(0))),constant:a(m(v(5),l()),i(mainKnuckle,v(25),v(0))),flags:{longRange:false,unsheathe:false,castRange:1,areaRadius:a(tier([between(1,2,v(1)),between(3,5,v(1.5)),between(6,8,v(2)),between(9,10,v(2.5))]),i(mainKnuckle,v(1.5),v(0)))}}],effects:[{phase:'hit',type:'ailmentChance',key:'stop',chance:a(m(v(5),l()),i(mainKnuckle,v(50),v(0)))},{phase:'afterHit',type:'hpRestorePercent',value:v(5),cap:i(mainKnuckle,v(1000),v(500))}]});
  definitions[9]=Object.assign(definitions[9],{cost:{mp:{timing:'cast',value:v(300)}},attacks:[{id:'hit1',damageType:'physical',count:v(1),multiplier:a(v(1),m(v(.1),l()),i(mainKnuckle,v(1),v(0))),constant:a(v(25),m(v(2),l())),flags:{longRange:false,unsheathe:false,castRange:3,criticalChanceBonus:i(mainKnuckle,v(50),v(0))}},{id:'hit2',damageType:'physical',count:v(1),multiplier:a(v(1),m(v(.1),l()),i(mainKnuckle,v(1),v(0))),constant:a(v(25),m(v(2),l())),flags:{longRange:false,unsheathe:false,criticalChanceBonus:a(m(v(2),l()),i(mainKnuckle,v(50),v(0)))}},{id:'hit3',damageType:'physical',count:v(1),multiplier:a(v(1),m(v(.1),l()),i(mainKnuckle,v(1),v(0))),constant:a(v(25),m(v(2),l())),flags:{longRange:false,unsheathe:false,criticalChanceBonus:a(m(v(4),l()),i(mainKnuckle,v(50),v(0)))}}]});
  definitions[10]=Object.assign(definitions[10],{activeBuff:true,cost:{mp:{timing:'cast',value:v(400)}},attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(v(3),m(v(.4),l()),i(mainKnuckle,a(v(2),d(base('AGI'),v(50))),v(0))),constant:a(m(v(20),l()),i(mainKnuckle,v(200),v(0))),flags:{longRange:false,unsheathe:false,castRange:1}}],stateTransitions:[{event:'cast',operation:'grant',stateId:'martial.rush',stacks:v(1),maxStacks:v(1),durationSeconds:v(10),effects:[{type:'stat',key:'MOTION_SPEED_P',value:m(tier([between(1,3,v(2)),between(4,6,v(3)),between(7,9,v(4)),between(10,10,v(5))]),i(mainKnuckle,v(2),v(1)))}]}],effects:[{phase:'combat',type:'stat',key:'MOTION_SPEED_P',when:active(),value:m(tier([between(1,3,v(2)),between(4,6,v(3)),between(7,9,v(4)),between(10,10,v(5))]),i(mainKnuckle,v(2),v(1)))}]});
  Object.assign(def(12),{cost:{mp:{timing:'cast',value:v(300)}},attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(v(7.5),m(v(.25),l()),i(mainBarehand,d(max(total('STR'),total('DEX')),v(100)),v(0))),constant:v(300),flags:{longRange:false,unsheathe:false,castRange:i(mainKnuckle,r('equipment.mainWeaponRange'),v(2))}}],effects:[{phase:'hit',type:'ailmentChance',key:'flinch',chance:m(v(10),l()),resistancePenaltySeconds:{normal:4,hard:2,lunatic:0,ultimate:0}},{phase:'onAilmentSuccess',type:'mpRestore',value:a(v(600),m(total('AMPR'),v(2)))}]});
  Object.assign(def(13),{cost:{mp:{timing:'cast',value:v(400)}},attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(v(2.5),m(v(.25),l()),i(mainBarehand,d(max(total('STR'),total('AGI')),v(100)),v(0))),constant:v(400),flags:{longRange:false,unsheathe:false,castRange:i(mainKnuckle,r('equipment.mainWeaponRange'),v(2))}},{id:'wheelKick',damageType:'physical',count:v(1),multiplier:a(v(5),m(v(.5),l()),i(mainKnuckle,d(base('AGI'),v(100)),v(0))),constant:a(v(400),m(v(40),l())),flags:{longRange:false,unsheathe:false}}],effects:[{phase:'hit',type:'ailmentChance',key:'tumble',chance:v(100),resistancePenaltySeconds:{normal:3,hard:0,lunatic:0,ultimate:0}},{phase:'afterHit',type:'avoidRecoveryAndImmunity',durationSeconds:a(v(2),d(l(),v(2))),notes:'차륜각 후 장비별 avoid 회복(주 권갑 3), 슬로우·정지·흡인 면역'}]});
  Object.assign(def(14),{cost:{mp:{timing:'cast',value:v(100)}},inputs:[{id:'avoidsUsed',type:'number',min:v(0),max:v(20),default:v(0)}],attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(v(3),m(v(.3),l()),i(mainKnuckle,d(base('AGI'),v(400)),v(0))),constant:v(100),flags:{longRange:false,unsheathe:false,castRange:6,inertia:'normal'}},{id:'avoidFollowups',damageType:'physical',count:input('avoidsUsed'),multiplier:v(.5),constant:v(0),flags:{longRange:false,unsheathe:false,eachHitHalfPreviousDamage:true}}],stateTransitions:[{event:'cast',operation:'grant',stateId:'martial.flashArt.nextShortRange',stacks:v(1),maxStacks:v(1),durationSeconds:v(0),effects:[{type:'nextSkillModifier',key:'shortRangeDamagePercent',value:l()}]}]});
  var floor=function(value){return {op:'floor',value:value};};
  Object.assign(def(15),{effects:[{phase:'build',type:'stat',key:'WATKP',value:m(v(3),l())},{phase:'build',type:'stat',key:'ATKP',value:tier([between(1,2,v(1)),between(3,7,v(2)),between(8,10,v(3))])}]});
  Object.assign(def(16),{effects:[{phase:'combat',type:'damageMultiplier',target:'skillCategory:Martial',value:a(v(1),d(l(),v(100)))},{phase:'build',type:'stat',key:'ASPD_P',value:l()},{phase:'build',type:'stat',key:'ASPD',value:m(v(10),l()),notes:'고정 공격 속도는 메인 권갑에만 적용'}]});
  Object.assign(def(17),{cost:{mp:{timing:'cast',value:v(200)}},stateTransitions:[{event:'cast',operation:'grant',stateId:'martial.chakra',stacks:v(1),maxStacks:v(1),durationSeconds:a(v(10),l(),i(mainKnuckle,v(10),v(0))),effects:[{type:'mpRestore',value:i(mainKnuckle,v(100),v(50))}]}],effects:[{phase:'combat',type:'stat',key:'AMPR',value:tier([between(1,5,l()),between(6,10,a(v(5),m(v(2),a(l(),v(-5)))))])},{phase:'combat',type:'damageReduction',value:a(v(10),m(v(2),l()),i(mainKnuckle,v(20),v(0)))},{phase:'combat',type:'partyFixedDamageReduction',value:m(base('VIT'),v(-.5)),scope:'partyExceptSelf',notes:'피격 시 종료. 파티원의 기본 VIT를 기준으로 한다.'}]});
  Object.assign(def(18),{cost:{mp:{timing:'cast',value:v(100)}},activeBuff:true,stateTransitions:[{event:'cast',operation:'grant',stateId:'martial.hwarang',stacks:v(1),maxStacks:v(1),durationSeconds:tier([between(1,1,v(30)),between(2,4,v(30)),between(5,5,v(45)),between(6,9,v(45)),between(10,10,v(90))])}],effects:[{phase:'combat',type:'stat',key:'STABILITY',value:v(10)},{phase:'combat',type:'stat',key:'WATKP',capGroup:'martialCrusherWeaponAtk',cap:v(50),value:m(v(5),l()),notes:'파괴자 스킬의 WATKP 증가와 합산하고 총 +50% 상한. 피격 피해 0 성공 시 자신에게 화경·차크라(낮은 레벨, MP 회복 없음) 부여.'},{phase:'combat',type:'motionDamageNullify',value:v(100),notes:'행동 불능 공격에는 해당 피격까지만 적용'}]});
  Object.assign(def(19),{effects:[{phase:'build',type:'stat',key:'AMPR',when:hasKnuckle,value:floor(d(a(l(),v(1)),v(2)))},{phase:'combat',type:'oneChanceFollowup',chance:m(v(5),l()),multiplier:m(v(.05),l()),constant:v(0),notes:'통상 적중 시; 필중·비크리·체술 단련 미적용. 권갑이 주/보조인 경우에만 AMPR 증가.'}]});
  Object.assign(def(20),{effects:[{phase:'combat',type:'oneChanceModifier',key:'multiplierBonus',value:m(v(.05),l())},{phase:'build',type:'stat',key:'HIT',value:m(l(),i(mainKnuckle,v(2),v(1)))},{phase:'combat',type:'oneChanceModifier',key:'physicalPiercePercent',when:mainKnuckle,value:m(v(5),l())}]});
  Object.assign(def(21),{cost:{mp:{timing:'cast',value:v(100)}},stateTransitions:[{event:'cast',operation:'grant',stateId:'martial.sliding.nextSkillHit',stacks:v(1),maxStacks:v(1),durationSeconds:v(0),effects:[{type:'nextSkillModifier',key:'hit',value:m(l(),l())}]}],effects:[{phase:'combat',type:'positionMove',value:v(1),notes:'8m 사거리에서 대상 1m 앞까지 이동'}]});
  var skill=catalog.skills.find(function(item){return item.id==='Martial:11';});
  if(!skill) throw new Error('아수라 오라를 카탈로그에서 찾지 못했습니다.');
  registry.register('Martial-stack-buff', definitions.concat([{
    id:skill.id, treeId:'Martial', skillId:11, nameKo:skill.nameKo, kind:'buff', source:'martial', dataStatus:'partial',
    sourceRef:{file:'docs/sources/skills/Martial.txt',anchor:'아수라 오라 버프 / 권갑 전용'}, requirements:{when:mainKnuckle}, cost:{mp:{timing:'cast',value:v(0)}}, combo:{canStart:false,canReceiveTag:true},
    stackRole:'combat-resource',
    stackControl:{stateId:'martialAsuraAura',minStacks:v(0),maxStacks:v(40),initialStacks:v(0),label:'아수라 스택',persistWhenDisabled:true,showWhenDisabled:true,applyWhenDisabled:true,resetStacksOnEnable:true},
    stackModel:{mode:'dual-mode-persistent',hardCap:v(40),onCastClearsStacks:true,offStatePreservesStacks:true,gain:{event:'mpSpent',perMp:v(100),stacks:v(1)},over20HpCostPerStackPercent:v(5),deathAtStacks:v(40),notes:'ON으로 전환하면 스택을 지우고, OFF로 전환하면 모은 스택을 유지한다.'},
    stateTransitions:[
      {event:'toggleOn',operation:'setStacks',stateId:'martialAsuraAura',stacks:v(0),maxStacks:v(40),durationSeconds:v(0),effects:[{type:'invincibility',durationSeconds:v(2)}]},
      {event:'mpSpent',operation:'addStacks',stateId:'martialAsuraAura',stacks:v(1),maxStacks:v(40),perResource:v(100)},
      {event:'toggleOff',operation:'preserveStacks',stateId:'martialAsuraAura'},
      {event:'normalAttackHit',operation:'consumeStacks',stateId:'martialAsuraAura',stacks:v(1),when:{op:'not',value:active()}}
    ],
    effects:[
      {phase:'combat',type:'stat',key:'CRIT',when:active(),value:m(v(7.5),l())},
      {phase:'combat',type:'globalSkillConstant',when:active(),value:m(v(20),l())},
      {phase:'combat',type:'damageMultiplier',target:'skillTrees:Martial,Crusher,Assassin,DarkPower',when:active(),value:v(1.3)},
      {phase:'combat',type:'damageMultiplier',target:'otherSkillTrees',when:active(),value:v(1.1)},
      {phase:'combat',type:'resourceCostModifier',key:'MP',target:'otherSkillTrees',when:active(),value:v(100),notes:'마셜·크러셔 이외 스킬, MP 반감 뒤·콤보 태그 전'},
      {phase:'combat',type:'asuraOnState',when:active(),notes:'현재 MP 기반 피해 감소/이상 내성, 공마회 차단, 아수라 블로는 전투 상태 엔진 구현 대기'}
    ],
    inactiveEffects:[
      {phase:'combat',type:'stat',key:'CRIT',when:hasStacks(),value:m(v(7.5),l())},
      {phase:'combat',type:'globalSkillConstant',when:hasStacks(),value:m(v(20),l())},
      {phase:'combat',type:'damageMultiplier',target:'attack',when:hasStacks(),value:v(1.1)},
      {phase:'combat',type:'asuraOffState',when:hasStacks(),notes:'아수라 블로는 통상 공격마다 스택 1을 소모하며 공마회 효과를 별도 계산해야 함'}
    ],
    specialAttacks:[{id:'asuraBlow',damageType:'physical',requiresTargetWithinMeters:v(3.5),multiplier:{op:'add',args:[v(.5),{op:'divide',left:r('baseStats.AGI'),right:{op:'subtract',left:v(2400),right:m(v(200),l())}}]},constant:v(0),hitIntervalSeconds:v(.25),flags:{guaranteedHit:true,longRange:false,unsheathe:false}}]
  }]));
}());