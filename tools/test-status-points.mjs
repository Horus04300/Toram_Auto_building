import { readFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import vm from 'node:vm';

const root = resolve(import.meta.dirname, '..');
const context = { window: {}, console };
context.window.window = context.window;
vm.createContext(context);
vm.runInContext(await readFile(resolve(root, 'assets/js/status-points.js'), 'utf8'), context, { filename: 'assets/js/status-points.js' });

const points = context.window.ToramStatusPoints;
function assert(condition, message) {
  if (!condition) throw new Error(message);
}

assert(points.officialLevelCap() === 325, '공식 최대 레벨은 Lv.325여야 함');
assert(points.playerLevelEmblemPoints(325) === 165, 'Lv.325 훈장은 165pt여야 함');
assert(points.pointBreakdown(325, 325).total === 840, 'Lv.325 기존 총 포인트를 보존해야 함');
const lowLevel = points.pointBreakdown(100, 325);
assert(lowLevel.levelPoints === 200, '낮은 캐릭터의 레벨업 포인트는 현재 레벨 기준이어야 함');
assert(lowLevel.emblemPoints === 165, '낮은 캐릭터도 최고 파라미터 Lv.325 훈장을 받아야 함');
assert(lowLevel.total === 390, 'Lv.100 / 최고 Lv.325 총 포인트');
assert(points.pointBreakdown(100, 100).total === 275, '최고 파라미터도 Lv.100이면 기존 결과를 유지해야 함');
console.log('Status point highest-parameter emblem regressions: PASS');
const providerContext = {
  window: {
    fetch: async () => ({ ok: true, text: async () => '<a href="/information/detail/?information_id=12000">new</a>' }),
    localStorage: { getItem: () => null, setItem: () => {} },
    dispatchEvent: () => {}
  },
  console,
  CustomEvent: class CustomEvent { constructor(type, init) { this.type = type; this.detail = init.detail; } }
};
providerContext.window.window = providerContext.window;
vm.createContext(providerContext);
vm.runInContext(await readFile(resolve(root, 'assets/js/official-level-cap.js'), 'utf8'), providerContext, { filename: 'assets/js/official-level-cap.js' });
assert(providerContext.window.ToramOfficialLevelCap.extractConfirmedLevelCap('Lv上限「330」の開放') === 330, '완료된 공식 최대 레벨 공지를 읽어야 함');
assert(providerContext.window.ToramOfficialLevelCap.extractConfirmedLevelCap('Lv上限「330」の開放予定') === 0, '개방 예정 공지는 현재 최대 레벨로 쓰면 안 됨');
console.log('Official level-cap notice parser regressions: PASS');
function input(value) {
  return {
    value: String(value),
    addEventListener: () => {},
    setAttribute(name, value) { this[name] = value; },
    focus: () => {}
  };
}
const elements = {
  charLevel: input(100), strBase: input(1), intBase: input(1), vitBase: input(1), agiBase: input(1), dexBase: input(1),
  statusPointSummary: input(''), statusResetBtn: input('')
};
const domContext = {
  window: { ToramOfficialLevelCap: { getCurrent: () => ({ level: 325 }) }, addEventListener: () => {} },
  document: {
    getElementById: id => elements[id],
    querySelectorAll: () => []
  },
  console
};
domContext.window.window = domContext.window;
vm.createContext(domContext);
vm.runInContext(await readFile(resolve(root, 'assets/js/status-points.js'), 'utf8'), domContext, { filename: 'assets/js/status-points.js' });
assert(elements.charLevel.max === 325, '캐릭터 레벨 입력 상한을 공식 최대 레벨로 설정해야 함');
assert(elements.statusPointSummary.textContent === '5 / 390', 'Lv.100 설계 화면은 최고 파라미터 Lv.325 훈장을 반영해야 함');
assert(elements.statusPointSummary.title.includes('Lv.325 기준 +165pt'), '화면에 적용한 훈장 기준을 설명해야 함');
console.log('Status point DOM initialization regression: PASS');