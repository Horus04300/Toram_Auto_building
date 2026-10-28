import {skillEffects} from '../../../web/src/calculation/skill-effect-engine.js';
import {comboSequence} from '../../../web/src/calculation/combo-sequence-engine.js';

const context = { window:{}, console };
context.window.window = context.window;
context.window.skillSimulatorState = { getInvestments: () => ({ Magic:{} }) };

const effects = skillEffects;
const combo = comboSequence;
const ids = Array.from({ length:24 }, (_, id) => `Magic:${id}`);
const base = (mainType='지팡이') => ({get skillLevels(){return context.window.skillSimulatorState.getInvestments();}, mainType, subType:'없음', level:300, strBase:100, dexBase:100, intBase:500, vitBase:100, agiBase:100, crtBase:0 });
const combat = { STR:100, DEX:100, INT:600, VIT:100, AGI:100, MAXHP:10000, CSPD:1000, ATK:500, MATK:1200 };
const levels = (value, extra={}) => { context.window.skillSimulatorState.getInvestments = () => ({ Magic:Object.assign(Object.fromEntries(ids.map((id) => [id.slice(6), value])), extra) }); };
const assert = (condition, message) => { if (!condition) throw new Error(message); };
const close = (actual, expected, message) => assert(Math.abs(actual - expected) < 1e-9, `${message}: expected ${expected}, got ${actual}`);

levels(10);
let profile = effects.profile('Magic:11', base(), combat, { charge:153 });
assert(profile.hits.length === 5, '매직 캐논 153충전은 5타로 분할');
close(profile.hits[0].multiplier, 17, '매직 캐논 153충전 1타 계수');
close(profile.hits[2].multiplier, 14.9, '매직 캐논 153충전 3타 계수');
close(profile.hits[4].multiplier, 11, '매직 캐논 153충전 5타 계수');
profile = effects.profile('Magic:12', base(), combat, { mainMeteorHits:2, firstSplitHits:1 });
assert(profile.hits.map((hit) => hit.count).join(',') === '2,2,1', '폴 명중 운석 수가 분할타에 반영');
profile = effects.profile('Magic:14', base(), combat, {});
assert(profile.hits.length === 2 && profile.hits[0].count + profile.hits[1].count === 8, '매직 나이프 Lv.10 추가타');
profile = effects.profile('Magic:3', base(), combat, { spellTuningReinforce:true, spellTuningNextQuick:true });
close(profile.hits[0].multiplier, 5, '임팩트 리인포스 기본 계수 2배');
assert(profile.effects.some((effect) => effect.key === 'motionSpeed' && effect.value === 50), '임팩트 넥스트 퀵 다음 신속');

// Manual barrier activation represents remaining inside the barrier; its
// stat must reach build calculation without enabling position/hit simulation.
const barrierBuff = { activeBuffs:{'Magic:22':{active:true,stacks:0}} };
for(const weapon of ['지팡이','마도구']) {
  const changes=effects.activeStatChanges(base(weapon),combat,{},barrierBuff);
  close(changes.filter(change=>change.source.id==='Magic:22'&&change.key==='MOTIONSPEED').reduce((sum,change)=>sum+change.value,0),25,'결계 Lv.10 행동속도 전달');
}
assert(!effects.activeStatChanges(base('한손검'),combat,{},barrierBuff).some(change=>change.source.id==='Magic:22'),'결계 무기 제한');
assert(!effects.activeStatChanges(base(),combat,{}, {activeBuffs:{'Magic:22':{active:false}}}).some(change=>change.source.id==='Magic:22'),'비활성 결계는 행동속도 미적용');
levels(0,{22:1});
close(effects.activeStatChanges(base(),combat,{},barrierBuff).find(change=>change.key==='MOTIONSPEED').value,7,'결계 Lv.1 행동속도');
levels(0);
assert(!effects.activeStatChanges(base(),combat,{},barrierBuff).some(change=>change.source.id==='Magic:22'),'미습득 결계 미적용');

levels(0, { 0:10, 3:10, 5:10, 7:10, 15:10, 18:10 });
let result = combo.evaluate([{ skillId:'Magic:3', tag:'none' }, { skillId:'Magic:0', tag:'none' }], base(), combat, { maxMp:500 });
assert(result.entries[1].finalMp === 50, '임팩트 다음 스킬 MP 반감이 1회 소비');
result = combo.evaluate([{ skillId:'Magic:0', tag:'none' }, { skillId:'Magic:5', tag:'none' }], base('마도구'), combat, { maxMp:1000 });
assert(result.entries[1].finalMp === 100 && result.entries[1].copiedSkillId === 'Magic:0', '크로노스 시프트가 이전 매직의 실제 MP를 복사');
close(result.entries[1].hits[0].effectiveMultiplier, 1.25, '크로노스 시프트는 이전 매직 타격을 복사');
result = combo.evaluate([{ skillId:'Magic:15', tag:'none' }, { skillId:'Magic:0', tag:'none' }], base(), combat, { maxMp:500 });
assert(result.entries[1].finalMp === 50, '게달 다음 스킬 MP 반감');
assert(result.entries[1].hits[0].flags.guaranteedCritical, '게달 다음 스킬 확정 크리');
result = combo.evaluate([{ skillId:'Magic:0', tag:'none' }, { skillId:'Magic:7', tag:'none' }], base(), combat, { maxMp:500 });
assert(result.entries[1].appliedNextSkillModifiers.castTimeReductionPercent === 50, '체인 캐스트 애로 후 영창 감소');
close(result.entries[1].castTimeSeconds, .5, '체인 캐스트가 월 영창에 반영');

levels(0, { 5:10, 17:10, 20:10, 21:10 });
profile = effects.profile('Magic:17', base('마도구'), combat, {});
close(profile.castTime.seconds, 4, '차징 Lv.10 마도구 영창');
assert(profile.effects[0].value === 350, '차징 Lv.10 마도구 MP 회복');
profile = effects.profile('Magic:20', base(), combat, {});
assert(profile.effects[0].value === 1500, '맥시마이저 지팡이 회복 MP');
assert(effects.profile('Magic:5', base(), combat, {}).available === false, '크로노스 시프트 지팡이 사용 불가');
assert(effects.profile('Magic:5', base('마도구'), combat, {}).available, '크로노스 시프트 마도구 사용 가능');
console.log('Magic S4/S5 calculator-scope regressions: PASS');
