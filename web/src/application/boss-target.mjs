const f = Math.fround;
const DIFFICULTIES = [-1, 0, 1, 2, 3];
const STATUS_RATES = [.1, 1, 2, 4, 6].map(f), HP_RATES = [.1, 1, 2, 5, 10].map(f);
const LEVEL_OFFSETS = [-10, 0, 10, 20, 40];
const STAT_KEYS = ['level','maxHp','def','mdef','necessaryHit','cutAttack','cutMagicAttack','guard','avoid','elementRaw','expDefNormal','expDefSkill','expDefMagic'];
const SHA = /^[a-f0-9]{64}$/u;
function requireValue(value, message = '보스 대상 데이터 또는 선택 값이 올바르지 않습니다.') { if (!value) throw new Error(message); }
function integer(value) { return Number.isSafeInteger(value) && value >= -2147483648 && value <= 2147483647; }
function trunc(value) { const result = Math.trunc(value); return integer(result) ? result : null; }
function scaled(value, rate) { return trunc(f(f(value) * rate)); }
function add(left, right) { return left === null || right === null ? null : trunc(left + right); }
function properties(value) { return Array.isArray(value) && value.every(row => Number.isSafeInteger(row.uid) && integer(row.typeRaw) && Array.isArray(row.values) && row.values.length === 5 && row.values.every(integer)); }

export function bossKindLabel(kind) { return ({ 'entry-boss':'입장 보스', 'field-boss':'필드 보스', 'high-raid-boss':'고난도 보스', 'guild-raid-boss':'길드 레이드 보스', 'dungeon-boss':'던전 보스' })[kind] ?? '분류 미확인'; }
export function bossActorLabel(actor) { return ({ male:'남자 소테리아 · 마법 방어형', female:'여자 소테리아 · 물리 방어형' })[actor] ?? ''; }

export function validateBossSelection(value) {
  requireValue(value?.schema === 'toram.boss-selection.v1' && SHA.test(value.revision) && Number.isSafeInteger(value.gameMonsterId) && value.gameMonsterId >= 0 && (value.name === null || typeof value.name === 'string'));
  const row = value.variant;
  requireValue(row && Number.isSafeInteger(row.fieldId) && Number.isSafeInteger(row.masterId) && row.key === `${row.fieldId}:${row.masterId}` && row.gameMonsterId === value.gameMonsterId && SHA.test(row.sourceSha256) && SHA.test(row.rawRecordSha256));
  requireValue(STAT_KEYS.every(key => integer(row.baseStats?.[key])) && properties(row.properties));
  requireValue(Array.isArray(row.parts) && Array.isArray(row.partStats) && row.parts.length === row.partStats.length);
  for (let i = 0; i < row.parts.length; i++) {
    const part = row.partStats[i];
    requireValue(integer(part.partId) && integer(part.masterId) && part.partId === row.parts[i].partId && part.masterId === row.parts[i].value);
    requireValue(part.stats === null || (SHA.test(part.sourceSha256) && ['def','mdef','cutAttack','cutMagicAttack'].every(key => integer(part.stats[key])) && properties(part.properties)));
  }
  const model = ({ 'field-boss':'single', 'entry-boss':'difficulty-select', 'high-raid-boss':'level-select', 'guild-raid-boss':'level-select', 'dungeon-boss':'unresolved', unresolved:'unresolved' })[row.classification];
  requireValue(model && row.entry?.model === model && DIFFICULTIES.includes(value.difficulty) && Number.isSafeInteger(value.level) && value.level >= 1 && value.level <= 32767);
  if (model === 'level-select') requireValue(integer(row.entry.levelParameters?.minLevel) && integer(row.entry.levelParameters?.baseLevel) && value.level >= row.entry.levelParameters.minLevel);
  if (row.classification === 'guild-raid-boss') {
    requireValue(value.level >= 40 && value.level <= 1020 && value.level % 4 === 0, '길드 레이드 현재 보스 레벨은 HP 게이지 기준 40~1020 사이의 4단위 값입니다.');
    requireValue(row.entry.levelParameters.minLevel === 40 && row.entry.levelParameters.maxLevel === 1020 && row.entry.levelParameters.step === 4);
    requireValue(row.entry.actor === null || ['male','female'].includes(row.entry.actor));
  }
  return value;
}

export function createBossSelection(boss, variant) {
  const projected = Object.fromEntries(['key','gameMonsterId','fieldId','masterId','fieldName','classification','entry','baseStats','parts','partStats','properties','sourceSha256','rawRecordSha256'].map(key => [key, variant[key] ?? (key === 'fieldName' ? null : undefined)]));
  return validateBossSelection({ schema:'toram.boss-selection.v1', gameMonsterId:boss.gameMonsterId, revision:boss.revision, name:boss.name,
    variant:JSON.parse(JSON.stringify(projected)), difficulty:0, level:Math.max(1, variant.entry.levelParameters?.minLevel ?? 1, variant.entry.levelParameters?.baseLevel ?? variant.baseStats.level) });
}

export function resolveBossTarget(selection) {
  validateBossSelection(selection);
  const row = selection.variant, base = row.baseStats, index = selection.difficulty + 1;
  const target = { bossLevel:null, bossDef:null, bossMdef:null, bossPhysResist:null, bossMagResist:null, bossCritResist:null };
  const notes = [], model = row.entry.model, supported = model !== 'unresolved', guildRaid = row.classification === 'guild-raid-boss';
  let hp = base.maxHp, hit = base.necessaryHit;
  if (supported) {
    target.bossLevel = base.level;
    target.bossDef = base.def; target.bossMdef = base.mdef;
    target.bossPhysResist = base.cutAttack; target.bossMagResist = base.cutMagicAttack;
    target.bossCritResist = row.properties.find(property => property.typeRaw === 6)?.values[0] ?? 0;
    if (model === 'difficulty-select') {
      target.bossLevel = Math.max(1, ((base.level + LEVEL_OFFSETS[index] + 32768) & 65535) - 32768);
      target.bossDef = scaled(base.def, STATUS_RATES[index]); target.bossMdef = scaled(base.mdef, STATUS_RATES[index]);
      hp = scaled(base.maxHp, HP_RATES[index]); hit = scaled(base.necessaryHit, STATUS_RATES[index]);
    }
    if (guildRaid) {
      target.bossLevel = selection.level;
      target.bossDef = scaled(Math.imul(base.def, selection.level), f(.01));
      target.bossMdef = scaled(Math.imul(base.mdef, selection.level), f(.01));
      target.bossPhysResist = add(base.cutAttack, Math.trunc(selection.level / 10));
      target.bossMagResist = add(base.cutMagicAttack, Math.trunc(selection.level / 10));
      hp = null;
      hit = scaled(f(f(f(selection.level) * f(1.5)) * f(base.necessaryHit)), f(.01));
      if (selection.level >= 44) {
        const level = selection.level, gauges = level / 4;
        const hpInteger = Math.trunc(f(f(f(Math.imul(level, level)) / f(2.4)) + f(level + 81)));
        const hpFactor = f(f(hpInteger) * f(f(f(level) / f(10)) + f(30)));
        // For byte gauges 0..255, native Round(f32(n*n/100),2,ToEven) equals n*n/100.
        hp = trunc((gauges * gauges / 100 + 50) * hpFactor);
      }
      notes.push('현재 보스 레벨 = 남은 HP 게이지 수 × 4 (최소 40). 입장 시 레이드 레벨과 구분합니다.');
      notes.push('길드 레이드 서버 랜덤 옵션·스탯 보정은 제외한 기본값입니다. 실제 옵션이 있으면 직접 수정하세요.');
    } else if (model === 'level-select') {
      const flags = row.properties.find(property => property.typeRaw === 32)?.values[0] ?? 0, level = selection.level;
      target.bossLevel = level;
      target.bossDef = flags & 4 ? base.def : scaled(level, f(f(base.def) / f(100)));
      target.bossMdef = flags & 8 ? base.mdef : scaled(level, f(f(base.mdef) / f(100)));
      target.bossPhysResist = flags & 16 ? base.cutAttack : base.cutAttack - scaled(level, f(-.04));
      target.bossMagResist = flags & 32 ? base.cutMagicAttack : base.cutMagicAttack - scaled(level, f(-.04));
      const hpBase = f(f(base.maxHp) / f(100));
      const hpFactor = f(f(f(level + 81) + f(f(level * level) / f(2.4))) * f(f(f(level) / f(10)) + f(30)));
      hp = flags & 1 ? base.maxHp : trunc(f(f(hpBase * hpFactor) * f(level > 149 ? 1.5 : 1)));
      hit = flags & 2 ? base.necessaryHit : scaled(f(f(level) * f(1.5)), f(f(base.necessaryHit) / f(100)));
      notes.push('선택 레벨을 반영했습니다. 게임의 입장 가능 최대 레벨은 별도로 확인하세요.');
    }
    if (row.parts.length && model !== 'single') {
      if (guildRaid || row.partStats.some(part => part.stats === null)) {
        target.bossDef = null; target.bossMdef = null; target.bossPhysResist = null; target.bossMagResist = null;
        notes.push(guildRaid ? '길드 레이드 부위 보정 미확정: DEF/MDEF·내성은 기존 입력을 유지합니다.' : '부위 원본 연결 누락: DEF/MDEF·내성은 기존 입력을 유지합니다.');
      } else {
        for (const part of row.partStats) {
          const flags = part.properties.find(property => property.typeRaw === 32)?.values[0] ?? 0;
          const partDef = model === 'difficulty-select' ? scaled(part.stats.def, STATUS_RATES[index]) : flags & 4 ? part.stats.def : scaled(selection.level, f(f(part.stats.def) / f(100)));
          const partMdef = model === 'difficulty-select' ? scaled(part.stats.mdef, STATUS_RATES[index]) : flags & 8 ? part.stats.mdef : scaled(selection.level, f(f(part.stats.mdef) / f(100)));
          target.bossDef = add(target.bossDef, partDef);
          target.bossMdef = add(target.bossMdef, partMdef);
          for (const property of part.properties.filter(property => property.typeRaw === 8)) {
            target.bossPhysResist = add(target.bossPhysResist, property.values[0]); target.bossMagResist = add(target.bossMagResist, property.values[1]);
          }
        }
        notes.push(`등록 부위 ${row.parts.length}개 모두 미파괴 가정입니다. 실제 활성 부위·파괴 상태가 다르면 직접 수정하세요.`);
      }
    }
    if (Object.values(target).some(value => value === null)) notes.push('자동 계산이 확정되지 않은 항목은 기존 수동 값을 유지합니다.');
    notes.push('전투 버프·상태이상·보석 효과를 제외한 기본값입니다. 직접 수정할 수 있습니다.');
  } else notes.push('입장 경로의 계산 규칙이 미확인입니다. 원본만 표시하며 기존 계산 값을 유지합니다.');
  const details = [
    ['지역 / 개체', `${row.fieldName ?? '#' + row.fieldId} · ${row.key}`],
    ['본체 HP', hp ?? (guildRaid ? (selection.level === 40 ? 'Lv40은 남은 HP 게이지 0~10 중 어느 값인지 확인 필요' : 'int32 표현 범위 초과 · 자동값 미확정') : `미적용 (원본 ${base.maxHp})`)], ['회피', hit ?? `미적용 (원본 ${base.necessaryHit})`],
    ['관성 변동률 · 통상', `${base.expDefNormal}%p`], ['관성 변동률 · 물리', `${base.expDefSkill}%p`], ['관성 변동률 · 마법', `${base.expDefMagic}%p`],
    ['가드율 / 어보이드율 (원본)', `${base.guard}% / ${base.avoid}%`], ['속성 코드 (원본)', base.elementRaw],
    ['기본 DEF / MDEF', `${base.def} / ${base.mdef}`], ['기본 CutAttack / CutMagicAttack', `${base.cutAttack} / ${base.cutMagicAttack}`],
    ['부위 수', row.parts.length], ['기본 크리티컬 저항', target.bossCritResist ?? '미확인'], ['데이터 버전', selection.revision]
  ];
  return { target, details, notes };
}
