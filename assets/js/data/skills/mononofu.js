/* 모노노푸: 원문 대조가 끝난 기본 패시브 규칙. */
(function () {
  'use strict';
  var registry = window.ToramSkillEffectRegistry;
  var catalog = window.TORAM_SKILL_COMBAT_CATALOG;
  if (!registry || !catalog) throw new Error('모노노푸 스킬 데이터는 등록기와 전투 카탈로그 뒤에 로드되어야 합니다.');
  var v = function (n) { return { op:'value', value:n }; };
  var r = function (path) { return { op:'ref', path:path }; };
  var l = function () { return r('skill.level'); };
  var m = function () { return { op:'multiply', args:[].slice.call(arguments) }; };
  var tier = function (cases) { return { op:'tier', cases:cases }; };
  var between = function (min, max, value) { return { when:{ op:'all', args:[{ op:'gte', left:l(), right:v(min) }, { op:'lte', left:l(), right:v(max) }] }, value:v(value) }; };
  var eq = function (left, right) { return { op:'eq', left:left, right:right }; };
  var katana = eq(r('equipment.mainWeapon'), v('발도검'));
  var noSub = eq(r('equipment.subWeapon'), v('없음'));
  function get(id) {
    var skill = catalog.skills.find(function (item) { return item.id === id; });
    if (!skill) throw new Error(id + '를 카탈로그에서 찾지 못했습니다.');
    return skill;
  }
  var bushido = get('Mononofu:11');
  var twoHanded = get('Mononofu:14');
  var atkPercentTier = tier([between(1, 2, 1), between(3, 7, 2), between(8, 10, 3)]);
  registry.register('Mononofu-passives', [
    {
      id:bushido.id, treeId:'Mononofu', skillId:11, nameKo:bushido.nameKo, kind:'passive', source:'mononofu', dataStatus:'partial',
      sourceRef:{ file:'docs/sources/skills/Mononofu.txt', anchor:'무사도 패시브 / 모든 무기 사용 가능' },
      effects:[
        { phase:'build', type:'stat', key:'MAXHP', value:m(v(10), l()) },
        { phase:'build', type:'stat', key:'MAXMP', value:m(v(10), l()) },
        { phase:'build', type:'stat', key:'HIT', value:l() },
        { phase:'build', type:'stat', key:'WATKP', when:katana, value:m(v(3), l()) },
        { phase:'build', type:'stat', key:'ATKP', when:katana, value:atkPercentTier }
      ]
    },
    {
      id:twoHanded.id, treeId:'Mononofu', skillId:14, nameKo:twoHanded.nameKo, kind:'passive', source:'mononofu', dataStatus:'partial',
      sourceRef:{ file:'docs/sources/skills/Mononofu.txt', anchor:'양손쥐기 패시브 / 모든 무기 사용 가능' },
      requirements:{ when:noSub },
      effects:[
        { phase:'build', type:'stat', key:'CRIT', value:m(v(.5), l()) },
        { phase:'build', type:'stat', key:'STABILITY', value:m(v(.5), l()) },
        { phase:'build', type:'stat', key:'HIT_P', value:l() },
        { phase:'build', type:'stat', key:'WATKP', value:l() },
        { phase:'build', type:'stat', key:'CRIT', when:katana, value:m(v(.5), l()) },
        { phase:'build', type:'stat', key:'STABILITY', when:katana, value:m(v(.5), l()) },
        { phase:'combat', type:'criticalFinalAtkMultiplier', when:katana, value:{ op:'add', args:[v(1), m(v(.05), l())] }, notes:'메인 발도검의 크리티컬 공격에만 적용. 공격 선택/치명 판정 엔진 연결 대기.' }
      ]
    }
  ]);
}());
