/* 스킬 효과 데이터: 식은 skill-effect-engine.js의 제한된 AST로만 표현한다. */
(function () {
  'use strict';
  var v=function(n){return {op:'value',value:n};}, r=function(p){return {op:'ref',path:p};};
  var l=function(){return r('skill.level');}, a=function(){return {op:'add',args:[].slice.call(arguments)};};
  var m=function(){return {op:'multiply',args:[].slice.call(arguments)};}, d=function(x,y){return {op:'divide',left:x,right:y};};
  var q=function(c,y,n){return {op:'if',when:c,then:y,else:n||v(0)};}, e=function(x,y){return {op:'eq',left:x,right:y};};
  var between=function(min,max,result){return {when:{op:'all',args:[{op:'gte',left:l(),right:v(min)},{op:'lte',left:l(),right:v(max)}]},value:v(result)};};
  var tier=function(cases){return {op:'tier',cases:cases};};
  var mainIs=function(){return {op:'in',value:r('equipment.mainWeapon'),values:[].slice.call(arguments)};};

  window.TORAM_SKILL_EFFECT_SCHEMA_VERSION=2;
  window.TORAM_SKILL_EFFECT_DATA=Object.freeze({
    schemaVersion:2,
    sources:Object.freeze({
      shot:'https://gall.dcinside.com/mgallery/board/view/?id=toramonline&no=39514',
      magic:'https://gall.dcinside.com/mgallery/board/view/?id=toramonline&no=39522',
      blade:'https://gall.dcinside.com/mgallery/board/view/?id=toramonline&no=39513',
      battle:'https://gall.dcinside.com/mgallery/board/view/?id=toramonline&no=40368',
      survival:'https://gall.dcinside.com/mgallery/board/view/?id=toramonline&no=40367',
      guard:'https://gall.dcinside.com/mgallery/board/view/?id=toramonline&no=40324',
      support:'https://gall.dcinside.com/mgallery/board/view/?id=toramonline&no=40366'
    }),
    snapshots:Object.freeze({
      baseStats:'순수 스탯 배분값',
      buildStats:'장비·크리스타·패시브 반영 후 스탯',
      combatStats:'활성 버프까지 반영한 공격 시점 스탯'
    }),
    catalog:window.TORAM_SKILL_COMBAT_CATALOG,
    effectPhases:Object.freeze(['build','combat','cast','hit','afterHit','expiration']),
    dataStates:Object.freeze(['unreviewed','partial','verified']),
    skills:Object.freeze([
      {id:'Shot:16',treeId:'Shot',skillId:16,nameKo:'슈트 마스터리',kind:'passive',source:'shot',dataStatus:'partial',effects:[
        {type:'stat',key:'WATKP',when:mainIs('bow','bowgun'),value:m(v(3),l())},
        {type:'stat',key:'ATKP',when:mainIs('bow','bowgun'),value:tier([between(1,2,1),between(3,7,2),between(8,10,3)])}
      ]},
      {id:'Magic:13',treeId:'Magic',skillId:13,nameKo:'매직 마스터리',kind:'passive',source:'magic',dataStatus:'partial',effects:[
        {type:'stat',key:'WATKP',when:mainIs('staff','magicDevice'),value:m(v(3),l())},
        {type:'stat',key:'MATKP',when:mainIs('staff','magicDevice'),value:tier([between(1,2,1),between(3,7,2),between(8,10,3)])}
      ]},
      {id:'Shot:17',treeId:'Shot',skillId:17,nameKo:'롱 레인지',kind:'passive',source:'shot',dataStatus:'partial',effects:[
        {type:'damageMultiplier',target:'attack',when:{op:'truthy',value:r('attack.flags.longRange')},value:a(v(1),d(l(),v(100)))}
      ]},
      {id:'Shot:4',treeId:'Shot',skillId:4,nameKo:'크로스 파이어',kind:'attack',source:'shot',dataStatus:'partial',
       requirements:{mainWeapons:['bow','bowgun']},inputs:[{id:'charge',label:'차지 수',type:'number',min:1,max:5,default:5},{id:'decoyActive',label:'디코이 설치',type:'boolean',default:false}],
       attacks:[
        {id:'mainBullet',count:v(1),damageType:'physical',multiplier:m(q(e(r('equipment.mainWeapon'),v('bow')),a(v(4.5),m(v(.5),l()),d(r('baseStats.DEX'),v(500))),a(v(4),m(v(.5),l()))),r('attack.inputs.charge')),constant:a(v(300),m(v(10),l())),flags:{longRange:true,unsheathe:false}},
        {id:'subBullet',damageType:'physical',count:{op:'max',args:[v(0),a(r('attack.inputs.charge'),v(-1))]},multiplier:a(v(2),q(e(r('equipment.mainWeapon'),v('bowgun')),v(1))),constant:a(v(300),m(v(10),l())),flags:{longRange:false,unsheathe:false}},
        {id:'decoyBullet',when:{op:'truthy',value:r('attack.inputs.decoyActive')},count:v(1),damageType:'physical',multiplier:m(a(v(.8),m(v(.1),l())),r('attack.inputs.charge')),constant:a(v(60),m(v(2),l())),flags:{longRange:true,unsheathe:false}}
       ]},
      {id:'Magic:4',treeId:'Magic',skillId:4,nameKo:'술식/피날레',kind:'attack',source:'magic',dataStatus:'partial',attacks:[
        {id:'hit1',count:v(1),damageType:'magic',multiplier:a(v(30),q(e(r('equipment.mainWeapon'),v('staff')),a(v(7.5),d(r('baseStats.INT'),v(100)))),q(e(r('equipment.mainWeapon'),v('magicDevice')),d(r('baseStats.INT'),v(100)))),constant:m(v(300),l()),flags:{longRange:true,unsheathe:false}},
        {id:'hit2',count:v(1),damageType:'magic',multiplier:v(20),constant:m(v(30),l()),flags:{longRange:true,unsheathe:false}},
        {id:'hit3',count:v(1),damageType:'magic',multiplier:v(10),constant:m(v(3),l()),flags:{longRange:true,unsheathe:false}}
      ]},
      {id:'Magic:2',treeId:'Magic',skillId:2,nameKo:'술식/랜서',kind:'attack',source:'magic',dataStatus:'partial',attacks:[
        {id:'main',damageType:'magic',count:a(tier([between(1,5,2),between(6,10,3)]),q(e(r('equipment.mainWeapon'),v('magicDevice')),v(2))),multiplier:a(v(2.5),m(v(.15),l()),q(e(r('equipment.mainWeapon'),v('staff')),a(v(1.5),d(r('combatStats.INT'),v(500)))),q(e(r('equipment.mainWeapon'),v('magicDevice')),d(r('combatStats.INT'),v(500)))),constant:a(v(300),m(v(40),l())),flags:{longRange:true,unsheathe:false}}
      ]},
      {id:'Blade:17',treeId:'Blade',skillId:17,nameKo:'블레이드 마스터리',kind:'passive',source:'blade',dataStatus:'partial',effects:[
        {phase:'build',type:'stat',key:'WATKP',when:mainIs('한손검','양손검'),value:m(v(3),l())},
        {phase:'build',type:'stat',key:'ATKP',when:mainIs('한손검','양손검'),value:tier([between(1,2,1),between(3,7,2),between(8,10,3)])}
      ]},
      {id:'Blade:18',treeId:'Blade',skillId:18,nameKo:'재빠른 참격',kind:'passive',source:'blade',dataStatus:'partial',effects:[
        {phase:'build',type:'stat',key:'ASPDP',when:mainIs('한손검','양손검'),value:l()},
        {phase:'build',type:'stat',key:'ASPD',when:mainIs('한손검','양손검'),value:m(v(10),l())}
      ]},
      {id:'Blade:19',treeId:'Blade',skillId:19,nameKo:'장인의 검술',kind:'passive',source:'blade',dataStatus:'partial',effects:[
        {phase:'hit',type:'damageMultiplier',target:'skillCategory:Blade',when:mainIs('한손검','양손검'),value:a(v(1),d(m(v(2),l()),v(100)))}
      ]},
      {id:'Blade:6',treeId:'Blade',skillId:6,nameKo:'아스튜트',kind:'attack',source:'blade',dataStatus:'partial',
       requirements:{when:mainIs('한손검','양손검')},cost:{mp:{timing:'cast',value:q(e(r('equipment.mainWeapon'),v('한손검')),v(100),v(200))}},
       attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(v(1.5),m(v(.1),l()),q(e(r('equipment.mainWeapon'),v('양손검')),v(.5),v(0))),constant:a(v(150),m(v(5),l())),flags:{longRange:false,unsheathe:false}}],
       effects:[{phase:'cast',type:'skillModifier',key:'motionSpeed',value:m(v(5),l())}],
       stateTransitions:[{event:'cast',operation:'grant',stateId:'blade.astute.critical',stacks:v(1),maxStacks:v(1),durationSeconds:tier([between(1,5,5),between(6,10,10)]),effects:[{phase:'combat',type:'stat',key:'CRIT',value:a(v(25),q(e(r('equipment.mainWeapon'),v('양손검')),v(25),v(0)))}]}]
      },
      {id:'Blade:7',treeId:'Blade',skillId:7,nameKo:'트리거 슬래시',kind:'attack',source:'blade',dataStatus:'partial',
       requirements:{when:mainIs('한손검','양손검')},cost:{mp:{timing:'cast',value:q({op:'gte',left:l(),right:v(6)},v(200),v(300))}},
       attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(v(1.5),m(v(.05),l()),q(e(r('equipment.mainWeapon'),v('양손검')),v(1),v(0))),constant:a(v(200),m(v(10),l())),flags:{longRange:false,unsheathe:false}}],
       stateTransitions:[{event:'cast',operation:'grant',stateId:'blade.triggerSlash',stacks:v(1),maxStacks:v(1),durationSeconds:v(0),effects:[{phase:'combat',type:'stat',key:'AMPR',value:m(v(2),l())},{phase:'cast',type:'nextSkillModifier',key:'motionSpeed',value:v(50)}]}]
      },
      {id:'Blade:13',treeId:'Blade',skillId:13,nameKo:'스파이럴 에어',kind:'attack',source:'blade',dataStatus:'partial',
       requirements:{when:mainIs('한손검','양손검')},cost:{mp:{timing:'cast',value:v(300)}},
       attacks:[{id:'main',damageType:'physical',count:v(10),multiplier:a(v(.1),m(v(.03),l()),q(e(r('equipment.mainWeapon'),v('양손검')),v(.5),v(0))),constant:v(30),flags:{longRange:false,unsheathe:false},stateTransitions:[{event:'hit',operation:'grant',stateId:'blade.spiralAir.criticalDamage',stacks:v(1),maxStacks:v(1),durationSeconds:l(),effects:[{phase:'combat',type:'stat',key:'CDMG',value:q(e(r('equipment.mainWeapon'),v('양손검')),d(a(v(.5),m(v(.5),l()),d(r('combatStats.DEX'),v(50))),v(2)),a(v(.5),m(v(.5),l()),d(r('combatStats.DEX'),v(50))))}]}]}]
      },
      {id:'Blade:20',treeId:'Blade',skillId:20,nameKo:'워 크라이',kind:'buff',source:'blade',dataStatus:'partial',
       inputs:[{id:'active',label:'활성',type:'boolean',default:false}],cost:{mp:{timing:'cast',value:v(300)}},
       stateTransitions:[{event:'cast',operation:'grant',stateId:'blade.warCry',stacks:v(1),maxStacks:v(1),durationSeconds:a(v(15),l()),effects:[{phase:'combat',type:'stat',key:'ATKP',scope:'party',value:q(e(r('equipment.mainWeapon'),v('양손검')),a(l(),v(5)),l())}]}],
       effects:[{phase:'combat',type:'stat',key:'ATKP',when:{op:'truthy',value:r('buff.active')},value:q(e(r('equipment.mainWeapon'),v('양손검')),a(l(),v(5)),l())}]
      }
    ])
  });
}());
