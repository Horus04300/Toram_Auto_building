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
      support:'https://gall.dcinside.com/mgallery/board/view/?id=toramonline&no=40366',
      darkPower:'https://gall.dcinside.com/mgallery/board/view/?id=toramonline&no=40846',
      dancer:'https://gall.dcinside.com/mgallery/board/view/?id=toramonline&no=40801',
      minstrel:'https://gall.dcinside.com/mgallery/board/view/?id=toramonline&no=40848'
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
      {id:'Shot:16',treeId:'Shot',skillId:16,nameKo:'슈트 마스터리',kind:'passive',source:'shot',dataStatus:'partial',sourceRef:{file:'docs/sources/skills/Shot.txt',anchor:'슈트 마스터리 패시브'},effects:[
        {type:'stat',key:'WATKP',when:mainIs('bow','bowgun'),value:m(v(3),l())},
        {type:'stat',key:'ATKP',when:mainIs('bow','bowgun'),value:tier([between(1,2,1),between(3,7,2),between(8,10,3)])}
      ]},
      {id:'Magic:13',treeId:'Magic',skillId:13,nameKo:'매직 마스터리',kind:'passive',source:'magic',dataStatus:'partial',sourceRef:{file:'docs/sources/skills/Magic.txt',anchor:'매직 마스터리 패시브'},effects:[
        {type:'stat',key:'WATKP',when:mainIs('staff','magicDevice'),value:m(v(3),l())},
        {type:'stat',key:'MATKP',when:mainIs('staff','magicDevice'),value:tier([between(1,2,1),between(3,7,2),between(8,10,3)])}
      ]},
      {id:'Shot:17',treeId:'Shot',skillId:17,nameKo:'롱 레인지',kind:'passive',source:'shot',dataStatus:'partial',sourceRef:{file:'docs/sources/skills/Shot.txt',anchor:'시전 가능 사거리가 8m 이상인 스킬 한정'},effects:[
        {type:'damageMultiplier',target:'attack',when:{op:'gte',left:r('attack.flags.castRange'),right:v(8)},value:a(v(1),d(l(),v(100)))}
      ]},
      {id:'Shot:4',treeId:'Shot',skillId:4,nameKo:'크로스 파이어',kind:'attack',source:'shot',dataStatus:'partial',sourceRef:{file:'docs/sources/skills/Shot.txt',anchor:'최대 차지 수 2 차지 (1 ~ 3 레벨)'},
       requirements:{when:mainIs('bow','bowgun')},cost:{mp:{timing:'charge',value:v(400)}},castModes:[{id:'charge',mp:v(400)},{id:'fire',mp:v(0)}],inputs:[{id:'charge',label:'차지 수',type:'number',min:1,max:tier([between(1,3,2),between(4,6,3),between(7,9,4),between(10,10,5)]),default:tier([between(1,3,2),between(4,6,3),between(7,9,4),between(10,10,5)])},{id:'decoyActive',label:'디코이 설치',type:'boolean',default:false}],stateModel:{mode:'chargeThenFire',chargeSeconds:[1,3,8,18,35],interruptions:['hit']},
       attacks:[
        {id:'mainBullet',count:v(1),damageType:'physical',multiplier:m(q(e(r('equipment.mainWeapon'),v('bow')),a(v(4.5),m(v(.5),l()),d(r('baseStats.DEX'),v(500))),a(v(4),m(v(.5),l()))),r('attack.inputs.charge')),constant:a(v(300),m(v(10),l())),flags:{longRange:true,unsheathe:false,castRange:12}},
        {id:'subBullet',damageType:'physical',count:{op:'max',args:[v(0),a(r('attack.inputs.charge'),v(-1))]},multiplier:a(v(2),q(e(r('equipment.mainWeapon'),v('bowgun')),v(1))),constant:a(v(300),m(v(10),l())),flags:{longRange:false,unsheathe:false,castRange:12,physicalPierceBonus:q(e(r('equipment.mainWeapon'),v('bowgun')),d(r('baseStats.DEX'),v(10)),v(0))}},
        {id:'decoyBullet',when:{op:'truthy',value:r('attack.inputs.decoyActive')},count:v(1),damageType:'physical',multiplier:m(a(v(.8),m(v(.1),l())),r('attack.inputs.charge')),constant:a(v(60),m(v(2),l())),flags:{longRange:true,unsheathe:false,castRange:12}}
       ]},
      {id:'Magic:4',treeId:'Magic',skillId:4,nameKo:'술식/피날레',kind:'attack',source:'magic',dataStatus:'partial',sourceRef:{file:'docs/sources/skills/Magic.txt',anchor:'술식/피날레 마법 액티브'},cost:{mp:{timing:'cast',value:v(1600)}},castTime:{type:'formula',seconds:{op:'subtract',left:{op:'subtract',left:v(13),right:l()},right:{op:'clamp',min:v(0),max:v(1),value:d(r('combatStats.CSPD'),v(10000))}}},attacks:[
        {id:'hit1',count:v(1),damageType:'magic',multiplier:a(v(30),q(e(r('equipment.mainWeapon'),v('staff')),a(v(7.5),d(r('baseStats.INT'),v(100)))),q(e(r('equipment.mainWeapon'),v('magicDevice')),d(r('baseStats.INT'),v(100)))),constant:m(v(300),l()),flags:{longRange:true,unsheathe:false,castRange:12}},
        {id:'hit2',count:v(1),damageType:'magic',multiplier:v(20),constant:m(v(30),l()),flags:{longRange:true,unsheathe:false,castRange:12}},
        {id:'hit3',count:v(1),damageType:'magic',multiplier:v(10),constant:m(v(3),l()),flags:{longRange:true,unsheathe:false,castRange:12}}
      ]},
      {id:'Magic:2',treeId:'Magic',skillId:2,nameKo:'술식/랜서',kind:'attack',source:'magic',dataStatus:'partial',sourceRef:{file:'docs/sources/skills/Magic.txt',anchor:'술식/랜서 마법 액티브'},cost:{mp:{timing:'cast',value:v(300)}},castTime:{type:'fixed',seconds:v(2)},attacks:[
        {id:'main',damageType:'magic',count:a(tier([between(1,5,2),between(6,10,3)]),q(e(r('equipment.mainWeapon'),v('magicDevice')),v(2))),multiplier:a(v(2.5),m(v(.15),l()),q(e(r('equipment.mainWeapon'),v('staff')),a(v(1.5),d(r('combatStats.INT'),v(500)))),q(e(r('equipment.mainWeapon'),v('magicDevice')),d(r('combatStats.INT'),v(500)))),constant:a(v(300),m(v(40),l())),flags:{longRange:true,unsheathe:false,castRange:14}}
      ]},
      {id:'Blade:17',treeId:'Blade',skillId:17,nameKo:'블레이드 마스터리',kind:'passive',source:'blade',dataStatus:'partial',sourceRef:{file:'docs/sources/skills/Blade.txt',anchor:'블레이드 마스터리 패시브'},requirements:{when:mainIs('한손검','양손검')},effects:[
        {phase:'build',type:'stat',key:'WATKP',when:mainIs('한손검','양손검'),value:m(v(3),l())},
        {phase:'build',type:'stat',key:'ATKP',when:mainIs('한손검','양손검'),value:tier([between(1,2,1),between(3,7,2),between(8,10,3)])}
      ]},
      {id:'Blade:18',treeId:'Blade',skillId:18,nameKo:'재빠른 참격',kind:'passive',source:'blade',dataStatus:'partial',sourceRef:{file:'docs/sources/skills/Blade.txt',anchor:'재빠른 참격 패시브'},requirements:{when:mainIs('한손검','양손검')},effects:[
        {phase:'build',type:'stat',key:'ASPD_P',when:mainIs('한손검','양손검'),value:l()},
        {phase:'build',type:'stat',key:'ASPD',when:mainIs('한손검','양손검'),value:m(v(10),l())}
      ]},
      {id:'Blade:19',treeId:'Blade',skillId:19,nameKo:'장인의 검술',kind:'passive',source:'blade',dataStatus:'partial',sourceRef:{file:'docs/sources/skills/Blade.txt',anchor:'장인의 검술 패시브'},requirements:{when:mainIs('한손검','양손검')},effects:[
        {phase:'hit',type:'damageMultiplier',target:'skillCategory:Blade',when:mainIs('한손검','양손검'),value:a(v(1),d(m(v(2),l()),v(100)))}
      ]},
      {id:'Blade:6',treeId:'Blade',skillId:6,nameKo:'아스튜트',kind:'attack',source:'blade',dataStatus:'partial',sourceRef:{file:'docs/sources/skills/Blade.txt',anchor:'아스튜트 물리 액티브'},
       requirements:{when:mainIs('한손검','양손검')},cost:{mp:{timing:'cast',value:q(e(r('equipment.mainWeapon'),v('한손검')),v(100),v(200))}},
       attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(v(1.5),m(v(.1),l()),q(e(r('equipment.mainWeapon'),v('양손검')),v(.5),v(0))),constant:a(v(150),m(v(5),l())),flags:{longRange:false,unsheathe:false}}],
       effects:[{phase:'cast',type:'skillModifier',key:'motionSpeed',value:m(v(5),l())}],
       stateTransitions:[{event:'cast',operation:'grant',stateId:'blade.astute.critical',stacks:v(1),maxStacks:v(1),durationSeconds:tier([between(1,5,5),between(6,10,10)]),effects:[{phase:'combat',type:'stat',key:'CRIT',value:a(v(25),q(e(r('equipment.mainWeapon'),v('양손검')),v(25),v(0)))}]}]
      },
      {id:'Blade:7',treeId:'Blade',skillId:7,nameKo:'트리거 슬래시',kind:'attack',source:'blade',dataStatus:'partial',sourceRef:{file:'docs/sources/skills/Blade.txt',anchor:'트리거 슬래시 물리 액티브'},
       requirements:{when:mainIs('한손검','양손검')},cost:{mp:{timing:'cast',value:q({op:'gte',left:l(),right:v(6)},v(200),v(300))}},
       attacks:[{id:'main',damageType:'physical',count:v(1),multiplier:a(v(1.5),m(v(.05),l()),q(e(r('equipment.mainWeapon'),v('양손검')),v(1),v(0))),constant:a(v(200),m(v(10),l())),flags:{longRange:false,unsheathe:false,guaranteedHitWhen:{op:'eq',left:r('equipment.mainWeapon'),right:v('한손검')}}}],
       stateTransitions:[{event:'cast',operation:'grant',stateId:'blade.triggerSlash',stacks:v(1),maxStacks:v(1),durationSeconds:v(0),effects:[{phase:'combat',type:'stat',key:'AMPR',value:m(v(2),l())},{phase:'cast',type:'nextSkillModifier',key:'motionSpeed',value:v(50)}]}]
      },
      {id:'Blade:13',treeId:'Blade',skillId:13,nameKo:'스파이럴 에어',kind:'attack',source:'blade',dataStatus:'partial',sourceRef:{file:'docs/sources/skills/Blade.txt',anchor:'스파이럴 에어 물리 액티브'},
       requirements:{when:mainIs('한손검','양손검')},cost:{mp:{timing:'cast',value:v(300)}},
       attacks:[{id:'main',damageType:'physical',count:v(10),multiplier:a(v(.1),m(v(.03),l()),q(e(r('equipment.mainWeapon'),v('양손검')),v(.5),v(0))),constant:v(30),flags:{longRange:false,unsheathe:false,perHitModifiers:{physicalPierceFromHit:2,perHitPercent:5.556}},stateTransitions:[{event:'hit',operation:'grant',stateId:'blade.spiralAir.criticalDamage',stacks:v(1),maxStacks:v(1),durationSeconds:l(),effects:[{phase:'combat',type:'stat',key:'CDMG',value:q(e(r('equipment.mainWeapon'),v('양손검')),d(a(v(.5),m(v(.5),l()),d(r('combatStats.DEX'),v(50))),v(2)),a(v(.5),m(v(.5),l()),d(r('combatStats.DEX'),v(50))))}]}]}]
      },
      {id:'Blade:20',treeId:'Blade',skillId:20,nameKo:'워 크라이',kind:'buff',source:'blade',dataStatus:'partial',sourceRef:{file:'docs/sources/skills/Blade.txt',anchor:'워 크라이 버프'},
       inputs:[{id:'active',label:'활성',type:'boolean',default:false}],cost:{mp:{timing:'cast',value:v(300)}},
       stateTransitions:[{event:'cast',operation:'grant',stateId:'blade.warCry',stacks:v(1),maxStacks:v(1),durationSeconds:a(v(15),l(),q(e(r('equipment.mainWeapon'),v('한손검')),v(50),v(0))),effects:[{phase:'combat',type:'stat',key:'ATKP',scope:'party',value:q(e(r('equipment.mainWeapon'),v('양손검')),a(l(),v(5)),l())}]}],
       effects:[{phase:'cast',type:'ailmentRemove',key:'fear',value:v(1)},{phase:'combat',type:'stat',key:'ATKP',scope:'party',when:{op:'truthy',value:r('buff.active')},value:q(e(r('equipment.mainWeapon'),v('양손검')),a(l(),v(5)),l())}]
      }
    ])
  });
}());
