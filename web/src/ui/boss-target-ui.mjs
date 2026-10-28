import {buildStore} from '../application/build-draft-store.js';
import { createBossSelection, validateBossSelection, resolveBossTarget, bossKindLabel, bossActorLabel } from '../application/boss-target.mjs';

export function createBossTargetUi(documentRef, catalog) {
  const windowRef = documentRef.defaultView, node = id => documentRef.getElementById(id);
  let selection = null, boss = null, names = null, generation = 0, bound = false;
  const clone = value => JSON.parse(JSON.stringify(value));
  function option(value, label) { const item = documentRef.createElement('option'); item.value = String(value); item.textContent = label; return item; }
  function changed() {
    buildStore.commitScenario({bossSelection:selection || undefined});
    documentRef.dispatchEvent(new windowRef.CustomEvent('toram:build-options-changed'));
    documentRef.dispatchEvent(new windowRef.CustomEvent('toram:persistent-state-changed'));
  }
  function list() {
    if (!names) return;
    generation++;
    const query = node('bossSearch').value.trim().toLocaleLowerCase(), results = node('bossSearchResults');
    const matches = names.filter(item => `${item.name ?? ''} ${item.gameMonsterId}`.toLocaleLowerCase().includes(query));
    results.replaceChildren(...matches.map(item => option(item.gameMonsterId, `${item.name ?? '(이름 없음)'} · #${item.gameMonsterId}`)));
    results.selectedIndex = -1;
    node('bossSearchStatus').textContent = `${matches.length}개`;
  }
  async function search() {
    if (names) { list(); return; }
    const current = ++generation;
    node('bossSearchStatus').textContent = '보스 목록을 불러오는 중…';
    try {
      const loaded = await catalog.search('', node('bossLocale').value);
      if (current !== generation) return;
      names = loaded; list();
    } catch (error) { if (current === generation) node('bossSearchStatus').textContent = `불러오기 실패: ${error.message} · 검색 버튼으로 다시 시도하세요.`; }
  }
  function render() {
    if (!bound) return;
    node('bossTargetSelection').hidden = !selection;
    if (!selection) return;
    const variants = boss?.variants ?? [selection.variant];
    node('bossVariant').replaceChildren(...variants.map(row => option(row.key, `${bossKindLabel(row.classification)}${bossActorLabel(row.entry.actor) ? ' · ' + bossActorLabel(row.entry.actor) : ''} · ${row.fieldName ?? '지역 #' + row.fieldId}${row.classification === 'guild-raid-boss' ? '' : ' · Lv' + row.baseStats.level} · 개체 ${row.masterId} (${row.key})`)));
    node('bossVariant').value = selection.variant.key;
    node('bossVariant').disabled = !boss;
    node('bossDifficultyField').hidden = selection.variant.entry.model !== 'difficulty-select';
    node('bossEntryLevelField').hidden = selection.variant.entry.model !== 'level-select';
    node('bossDifficulty').value = String(selection.difficulty);
    node('bossEntryLevel').value = String(selection.level);
    node('bossEntryLevel').min = String(selection.variant.entry.levelParameters?.minLevel ?? 1);
    node('bossEntryLevel').max = String(selection.variant.entry.levelParameters?.maxLevel ?? 32767);
    node('bossEntryLevel').step = String(selection.variant.entry.levelParameters?.step ?? 1);
    node('bossEntryLevelLabel').textContent = selection.variant.classification === 'guild-raid-boss' ? '현재 보스 레벨' : '입장 레벨';
    const resolved = resolveBossTarget(selection), extra = node('bossTargetExtra');
    const base = selection.variant.baseStats;
    node('bossProration').textContent = `관성 변동률: 통상 ${base.expDefNormal}%p · 물리 ${base.expDefSkill}%p · 마법 ${base.expDefMagic}%p`;
    extra.replaceChildren();
    for (const [label, value] of resolved.details) {
      const term = documentRef.createElement('dt'), definition = documentRef.createElement('dd');
      term.textContent = label; definition.textContent = String(value); extra.append(term, definition);
    }
    const modified = Object.entries(resolved.target).filter(([id, value]) => value !== null && Number(node(id).value) !== value).map(([id]) => node(id).getAttribute('aria-label') ?? '보스 레벨');
    node('bossTargetStatus').textContent = `${selection.name ?? '#' + selection.gameMonsterId} · ${bossKindLabel(selection.variant.classification)}${bossActorLabel(selection.variant.entry.actor) ? ' · ' + bossActorLabel(selection.variant.entry.actor) : ''}\n`
      + resolved.notes.join('\n') + (modified.length ? `\n수동 수정: ${modified.join(', ')}` : '');
  }
  function apply() {
    const resolved = resolveBossTarget(selection);
    for (const [id, value] of Object.entries(resolved.target)) if (value !== null) node(id).value = String(value);
    const element = selection.variant.baseStats.elementRaw;
    node('bossElement').value = String(Number.isSafeInteger(element) && element >= 1 && element <= 7 ? element : 0);
    render(); changed();
  }
  async function selectBoss() {
    const current = ++generation, id = Number(node('bossSearchResults').value);
    if (!node('bossSearchResults').value) return;
    node('bossSearchStatus').textContent = '대상 데이터를 불러오는 중…';
    try {
      const loaded = await catalog.get(id, node('bossLocale').value);
      if (current !== generation) return;
      if (!loaded?.variants.length) throw new Error('선택 가능한 개체가 없습니다.');
      const nextBoss = loaded;
      // Prefer an evidenced route; the remaining source records stay explicitly selectable.
      nextBoss.variants.sort((a, b) => Number(a.entry.model === 'unresolved') - Number(b.entry.model === 'unresolved') || a.fieldId - b.fieldId || a.masterId - b.masterId);
      const nextSelection = createBossSelection(nextBoss, nextBoss.variants[0]);
      boss = nextBoss; selection = nextSelection;
      apply(); node('bossSearchStatus').textContent = '대상 적용 완료';
    } catch (error) { if (current === generation) node('bossSearchStatus').textContent = `대상 적용 실패: ${error.message}`; }
  }
  return Object.freeze({
    getSelection() { return buildStore.getScenario().bossSelection || null; },
    restoreSelection(value) {
      if (value) validateBossSelection(value);
      generation++; selection = value ? clone(value) : null; boss = null; buildStore.commitScenario({bossSelection:selection || undefined}); render();
    },
    bind() {
      if (!node('bossTargetSearch')) return;
      bound = true; render();
      node('bossSearch').addEventListener('input', search);
      node('bossSearchLoad').addEventListener('click', () => { names = null; search(); });
      node('bossLocale').addEventListener('change', () => { names = null; node('bossSearchResults').replaceChildren(); search(); });
      node('bossSearchResults').addEventListener('change', selectBoss);
      node('bossVariant').addEventListener('change', () => {
        try {
          const next = createBossSelection(boss, boss.variants.find(row => row.key === node('bossVariant').value));
          if (next.variant.classification === 'guild-raid-boss' && selection.variant.classification === 'guild-raid-boss' && next.variant.fieldId === selection.variant.fieldId) next.level = selection.level;
          selection = validateBossSelection(next); apply();
        }
        catch (error) { render(); node('bossTargetStatus').textContent = error.message; }
      });
      for (const id of ['bossDifficulty', 'bossEntryLevel']) node(id).addEventListener('change', () => {
        const next = { ...selection, difficulty:Number(node('bossDifficulty').value), level:Number(node('bossEntryLevel').value) };
        try { validateBossSelection(next); selection = next; apply(); }
        catch (error) { render(); node('bossTargetStatus').textContent = error.message; }
      });
      node('bossTargetClear').addEventListener('click', () => { generation++; selection = null; boss = null; render(); changed(); });
      for (const id of ['bossLevel','bossDef','bossMdef','bossPhysResist','bossMagResist','bossCritResist']) node(id).addEventListener('input', render);
      node('bossElement').addEventListener('change',render);
    }
  });
}
