import {policies} from '../calculation/calculation-policies.js';
export function createOptimizationResults(document,crystaUi) {
  const root=document.defaultView;
const buildGroupedTagsHtml=crystaUi.buildGroupedTagsHtml;

'use strict';
function resultDamageScore(result) { return result.optimizationDamageFactor === undefined ? result.damageFactor : result.optimizationDamageFactor; }

function optimizationEscape(value) {
            return String(value === undefined || value === null ? '' : value).replace(/[&<>"']/g, function(character) {
                return {'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#39;'}[character];
            });
        }

function optimizationFormatNumber(value) {
            var number = Number(value);
            return Number.isFinite(number) ? Math.floor(number).toLocaleString() : '-';
        }

function optimizationFormatMetric(value, unit, precision) {
            var number = Number(value);
            if (!Number.isFinite(number)) return '-';
            var digits = precision === undefined ? 0 : precision;
            var text = digits > 0 ? number.toFixed(digits) : Math.floor(number).toLocaleString();
            return text + (unit || '');
        }

function optimizationMetricDelta(current, recommended, unit, precision) {
            var before = Number(current), after = Number(recommended);
            if (!Number.isFinite(before) || !Number.isFinite(after)) return { text:'-', direction:'same' };
            var delta = after - before;
            var threshold = precision ? Math.pow(10, -precision) / 2 : 0.5;
            if (Math.abs(delta) < threshold) return { text:'유지', direction:'same' };
            var absolute = optimizationFormatMetric(Math.abs(delta), unit, precision);
            var percent = Math.abs(before) > 1e-9 ? ' · ' + (delta > 0 ? '+' : '-') + (Math.abs(delta) / Math.abs(before) * 100).toFixed(2) + '%' : '';
            return { text:(delta > 0 ? '+' : '-') + absolute + percent, direction:delta > 0 ? 'positive' : 'negative' };
        }

function optimizationOutcomeMetric(outcome, path) {
            var value = outcome;
            for (var index = 0; index < path.length && value; index++) value = value[path[index]];
            return value;
        }

function optimizationSlotNames(item) {
            var names = item && item.candidateNames || [];
            var first = names[0] || '비어있음';
            var second = names[1] || '비어있음';
            return first + ' + ' + second;
        }

function optimizationCurrentSlotNames(crystas, groupIndex) {
            var first = crystas && crystas[groupIndex * 2] && crystas[groupIndex * 2].name || '비어있음';
            var second = crystas && crystas[groupIndex * 2 + 1] && crystas[groupIndex * 2 + 1].name || '비어있음';
            return first + ' + ' + second;
        }

function optimizationComparisonCard(label, current, recommended, unit, precision) {
            var delta = optimizationMetricDelta(current, recommended, unit, precision);
            return '<div class="optimization-stat-change is-' + delta.direction + '"><span>' + optimizationEscape(label) + '</span><b>' + optimizationFormatMetric(current, unit, precision) + ' → ' + optimizationFormatMetric(recommended, unit, precision) + '</b><small>' + optimizationEscape(delta.text) + '</small></div>';
        }

function setCrystaOptimizationRecommendationApplyAvailability(available) {
            var button = document.getElementById('optimizationApplyRecommendedCrystas');
            if (!button) return;
            button.hidden = !available;
            button.disabled = !available;
        }

function optimizationGapText(value) {
            if (value === null || value === undefined || value === '') return '계산 중';
            var gap = Number(value);
            return Number.isFinite(gap) ? (gap * 100).toFixed(gap < 0.001 ? 3 : 2) + '%' : '계산 중';
        }

function optimizationEngineText(state) {
            if (state.engine === 'rust-native') return 'Rust CPU';
            if (state.engine === 'rust-wasm') return 'Rust WASM';
            return null;
        }

function renderCurrent(calculationSnapshot, curEvaluation, locks, mode) {
  var baseCtx = calculationSnapshot.baseContext, currentCrystas = calculationSnapshot.crystas, curRes = curEvaluation.calculation;
  var basis = document.getElementById('optimizationBasisLabel');
  if (basis) basis.textContent = '[' + (baseCtx.optimizationBasisName || '평타') + '] 기준 ' + (mode === 'precise' ? '정밀 검사' : '빠른 추천');
            document.getElementById('resultArea').style.display = 'block';
            var tCtx = curRes.ctx;

            document.getElementById('defWarning').style.display = curRes.isPierced ? 'none' : 'block';

            var totalCombinedStats = {};
            for(var x=0; x<currentCrystas.length; x++) {
                var c = currentCrystas[x];
                if(c) {
                    if(c.stats) {
                        for(var k in c.stats) totalCombinedStats[k] = (totalCombinedStats[k] || 0) + c.stats[k];
                    }
                    if(c.conditionalStats) {
                        for(var k=0; k<c.conditionalStats.length; k++) {
                            if(policies.matchesCrystaCondition(tCtx, c.conditionalStats[k].when)) {
                                for(var sk in c.conditionalStats[k].stats) totalCombinedStats[sk] = (totalCombinedStats[sk] || 0) + c.conditionalStats[k].stats[sk];
                            }
                        }
                    }
                }
            }
            Object.values(calculationSnapshot.build.equipment).flatMap(function (piece) {return piece.options;}).concat(calculationSnapshot.build.externalOptions || []).forEach(function (option) {
                totalCombinedStats[option.key] = (totalCombinedStats[option.key] || 0) + option.value;
            });

// 1. [적용된 총 보너스 수치 요약] 에 그룹화 적용
            var combinedTagsHtml = buildGroupedTagsHtml(totalCombinedStats);

            document.getElementById('resSumBonus').innerHTML =
                '<li>ATK 증가량 <span>' + tCtx.atkP + '% / +' + tCtx.atkF + '</span></li>' +
                '<li>MATK 증가량 <span>' + tCtx.matkP + '% / +' + tCtx.matkF + '</span></li>' +
                '<li>크리티컬데미지 <span>' + tCtx.cdmgP + '% / +' + tCtx.cdmgF + '</span></li>' +
                '<li>무기ATK 옵션 <span>' + tCtx.watkP + '% / +' + tCtx.watkF + '</span></li>' +
                '<li style="flex-direction:column; align-items:flex-start; border-top:1px dashed #d5dbdb; padding-top:8px; margin-top:4px;">' +
                '<span style="font-weight:bold; color:#2c3e50;">🔗 크리스타 + 장비 옵션 총합</span>' + combinedTagsHtml + '</li>';

            var strAdd = tCtx.strP > 0 ? '<div class="stat-pct-tag">(+' + tCtx.strP + '%)</div>' : '';
            var intAdd = tCtx.intP > 0 ? '<div class="stat-pct-tag">(+' + tCtx.intP + '%)</div>' : '';
            var vitAdd = tCtx.vitP > 0 ? '<div class="stat-pct-tag">(+' + tCtx.vitP + '%)</div>' : '';
            var agiAdd = tCtx.agiP > 0 ? '<div class="stat-pct-tag">(+' + tCtx.agiP + '%)</div>' : '';
            var dexAdd = tCtx.dexP > 0 ? '<div class="stat-pct-tag">(+' + tCtx.dexP + '%)</div>' : '';
            document.getElementById('resBaseStat').innerHTML =
                '<div class="stat-mini-card">STR <b>' + curRes.finalSTR + '</b>' + strAdd + '</div>' +
                '<div class="stat-mini-card">INT <b>' + curRes.finalINT + '</b>' + intAdd + '</div>' +
                '<div class="stat-mini-card">VIT <b>' + curRes.finalVIT + '</b>' + vitAdd + '</div>' +
                '<div class="stat-mini-card">AGI <b>' + curRes.finalAGI + '</b>' + agiAdd + '</div>' +
                '<div class="stat-mini-card">DEX <b>' + curRes.finalDEX + '</b>' + dexAdd + '</div>';

            var dualSwordExtraHtml = '';
            if (curRes.isDualSword) {
                dualSwordExtraHtml = `<li>서브 무기 ATK <span style="color:#8e44ad; font-weight:bold;">${curRes.finalSubAtk}</span> <span style="font-size:11px; color:#7f8c8d;">(서브안정률 ${curRes.finalSubStab}%)</span></li>`;
            }

            document.getElementById('resAtkData').innerHTML =
                `<li>최종 물리 ATK <span class="has-tooltip">${curRes.finalATK}<span class="tooltip-text">${curRes.tooltips.atkTip}</span></span></li>` +
                dualSwordExtraHtml +
                `<li>최종 마법 MATK <span class="has-tooltip">${curRes.finalMATK}<span class="tooltip-text">${curRes.tooltips.matkTip}</span></span></li>` +
                '<li>적용 공격 유형 <span style="color:#c0392b;">' + (tCtx.atkType==='MAG'?'마법 공격':'물리 공격') + '</span></li>';

            var appliedRangeDmg = tCtx.rangeType === 'SHORT' ? tCtx.srw : tCtx.lrw;
            var appliedRangeLabel = tCtx.rangeType === 'SHORT' ? '근거리위력' : '원거리위력';

            var procDamageLabel = curRes.procDamageProfile.sources.map(function(item) { return item.source + ' Lv.' + item.level; }).join('·');
            document.getElementById('resDmgFactor').innerHTML =
                '<li>최종 크리티컬데미지 <span class="has-tooltip highlight">' + curRes.finalCDMG + '%<span class="tooltip-text">' + curRes.tooltips.cdmgTip + '</span></span></li>' +
                '<li>최종 크리티컬확률 <span class="has-tooltip">' + curRes.finalCrit + '<span class="tooltip-text">' + curRes.tooltips.critTip + '</span></span></li>' +
                '<li>최종 안정률 <span>' + curRes.finalStab + '%</span></li>' +
                '<li>' + appliedRangeLabel + ' / 속성에 유리 <span class="has-tooltip">+' + appliedRangeDmg + '% / +' + tCtx.elemP + '%<span class="tooltip-text">' + curRes.tooltips.elemTip + '</span></span></li>' +
                (curRes.procDamageProfile.sources.length ? '<li>' + procDamageLabel + ' 미적용 기본 대미지 <span>' + Math.floor(curRes.damageFactor).toLocaleString() + '</span></li>' +
                '<li>' + procDamageLabel + ' 발동 시 대미지 <span>' + Math.floor(curRes.procTriggeredDamageFactor).toLocaleString() + '</span></li>' +
                '<li>' + procDamageLabel + ' 확률 반영 기대 대미지 <span>' + Math.floor(curRes.procExpectedDamageFactor).toLocaleString() + '</span></li>' +
                '<li>적용 확률 효과 <span>' + curRes.procDamageProfile.sources.map(function(item) { return item.source + ' Lv.' + item.level + ' · ' + item.chancePercent + '% ×' + Number(item.multiplier.toFixed(4)); }).join(', ') + '</span></li>' : '');

            document.getElementById('resPierce').innerHTML =
                '<li>물리관통 <span>' + tCtx.physPierce + '%</span></li>' +
                '<li>마법관통 <span>' + tCtx.magPierce + '%</span></li>' +
                '<li>타겟 DEF / MDEF <span>' + tCtx.bossDef + ' / ' + tCtx.bossMdef + '</span></li>';

// 1. ASPD 보정분 및 장비 행동속도 합산
            var baseActSpeed = curRes.finalASPD > 1000 ? Math.min(50, (curRes.finalASPD - 1000)/180) : 0;
            var equipMotionSpeed = tCtx.motionSpeed || 0; // 크리스타/장비 행동속도
            var totalActSpeed = Math.min(50, baseActSpeed + equipMotionSpeed);

            // 2. CSPD 보정분 및 장비 시전감소 합산 (최대 100% 제한)
            var baseCastReduc = curRes.finalCSPD <= 1000 ? curRes.finalCSPD/20 : Math.min(100, 50 + (curRes.finalCSPD - 1000)/180);
            var equipCastRed = tCtx.castRed || 0; // 크리스타/장비 영창감소
            var totalCastReduc = Math.min(100, baseCastReduc + equipCastRed);

            // 3. 화면 출력부
            document.getElementById('resSpeed').innerHTML =
                `<li>ASPD <span class="has-tooltip">${curRes.finalASPD}<span class="tooltip-text">${curRes.tooltips.aspdTip}</span></span> <span style="font-size:11px; color:#7f8c8d;">(스탯보정 +${baseActSpeed.toFixed(1)}%)</span></li>` +
                `<li style="color:#d35400; font-weight:bold; margin-bottom: 8px;"> ↳ 최종 행동속도: +${totalActSpeed.toFixed(1)}% <span style="font-size:11px; font-weight:normal; color:#7f8c8d;">(장비옵션 +${equipMotionSpeed}%)</span></li>` +
                `<li>CSPD <span class="has-tooltip">${curRes.finalCSPD}<span class="tooltip-text">${curRes.tooltips.cspdTip}</span></span> <span style="font-size:11px; color:#7f8c8d;">(스탯보정 -${baseCastReduc.toFixed(1)}%)</span></li>` +
                `<li style="color:#d35400; font-weight:bold;"> ↳ 최종 시전시간 감소: -${totalCastReduc.toFixed(1)}% <span style="font-size:11px; font-weight:normal; color:#7f8c8d;">(장비옵션 -${equipCastRed}%)</span></li>`;


  var badge = document.getElementById('top3CurrentDmgBadge');
  if (badge) { badge.textContent = (curRes.procDamageProfile.sources.length ? '현재 세팅 기대 데미지: ' : '현재 세팅 데미지: ') + Math.floor(resultDamageScore(curRes)).toLocaleString(); badge.style.display = 'inline-block'; }
}

function renderCrystaOptimizationRecommendationOverview(result, currentEvaluation, locks, currentCrystas) {
            var overview = document.getElementById('optimizationRecommendationOverview');
            var summary = document.getElementById('optimizationRecommendationSummary');
            if (!overview || !summary || !result || !result.outcomes || !result.bestBuild || !currentEvaluation) {
                if (overview) overview.hidden = true;
                return;
            }
            var currentOutcome = currentEvaluation;
            var recommendedOutcome = result.outcomes;
            var currentScore = resultDamageScore(currentOutcome.calculation || {});
            var recommendedScore = resultDamageScore(recommendedOutcome.calculation || {});
            var absoluteGain = Number(recommendedScore) - Number(currentScore);
            var relativeGain = Number(currentScore) > 0 ? absoluteGain / Number(currentScore) * 100 : 0;
            var scoreLabel = recommendedOutcome.calculation && recommendedOutcome.calculation.procDamageProfile && recommendedOutcome.calculation.procDamageProfile.sources.length ? '기대 대미지' : '대미지';
            var packages = result.bestBuild.packages || [];
            var slots = ['무기', '방어구', '추가 장비', '특수 장비'];
            var buildRows = '';
            for (var groupIndex = 0; groupIndex < 4; groupIndex++) {
                var before = optimizationCurrentSlotNames(currentCrystas, groupIndex);
                var after = optimizationSlotNames(packages[groupIndex]);
                var locked = locks && locks[groupIndex * 2] && locks[groupIndex * 2 + 1];
                buildRows += '<div class="optimization-build-row"><span class="optimization-build-slot">' + slots[groupIndex] + (locked ? ' 🔒' : '') + '</span><span class="optimization-build-value">' + optimizationEscape(before) + '</span><span class="optimization-build-arrow">→</span><span class="optimization-build-value' + (before === after ? '' : ' is-change') + '">' + optimizationEscape(after) + '</span></div>';
            }
            var rawCurrent = currentOutcome.calculation || {};
            var attackType = rawCurrent.ctx && rawCurrent.ctx.atkType === 'MAG' ? '마법' : '물리';
            var rangeLabel = rawCurrent.ctx && rawCurrent.ctx.rangeType === 'LONG' ? '원거리위력' : '근거리위력';
            var rangeKey = rawCurrent.ctx && rawCurrent.ctx.rangeType === 'LONG' ? 'lrw' : 'srw';
            var attackMetric = attackType === '마법' ? 'MATK' : 'ATK';
            var attackPath = attackType === '마법' ? ['offense', 'matk'] : ['offense', 'atk'];
            var utilityMetrics = [
                ['최대 HP', ['utility', 'maxHp'], '', 0],
                ['최대 MP', ['utility', 'maxMpAfterBuff'], '', 0],
                ['공격 MP 회복', ['utility', 'finalAmpr'], '', 0],
                ['ASPD', ['utility', 'aspd'], '', 0],
                ['행동속도', ['utility', 'motionSpeed'], '%', 1],
                ['CSPD', ['utility', 'cspd'], '', 0],
                ['시전시간 감소', ['utility', 'castReduction'], '%', 1]
            ];
            var offenseMetrics = [
                [attackMetric, attackPath, '', 0],
                ['크리티컬데미지', ['offense', 'criticalDamage'], '%', 0],
                ['선택 타격 크리', ['offense', 'selectedAttackCritical'], '', 0],
                ['안정률', ['offense', 'stability'], '%', 0],
                [rangeLabel, ['calculation', 'ctx', rangeKey], '%', 0],
                [attackType + ' 관통', [ 'offense', attackType === '마법' ? 'magicPierce' : 'physicalPierce' ], '%', 0]
            ];
            var utilityHtml = '', offenseHtml = '';
            utilityMetrics.forEach(function(metric) {
                utilityHtml += optimizationComparisonCard(metric[0], optimizationOutcomeMetric(currentOutcome, metric[1]), optimizationOutcomeMetric(recommendedOutcome, metric[1]), metric[2], metric[3]);
            });
            offenseMetrics.forEach(function(metric) {
                offenseHtml += optimizationComparisonCard(metric[0], optimizationOutcomeMetric(currentOutcome, metric[1]), optimizationOutcomeMetric(recommendedOutcome, metric[1]), metric[2], metric[3]);
            });
            summary.innerHTML = '<div class="optimization-damage-summary"><div class="optimization-damage-card"><span>현재 ' + scoreLabel + '</span><b>' + optimizationFormatNumber(currentScore) + '</b></div><div class="optimization-damage-card is-recommended"><span>추천 ' + scoreLabel + '</span><b>' + optimizationFormatNumber(recommendedScore) + '</b></div><div class="optimization-damage-card is-gain"><span>상승량</span><b>' + (absoluteGain >= 0 ? '+' : '') + optimizationFormatNumber(absoluteGain) + ' <small>(' + (relativeGain >= 0 ? '+' : '') + relativeGain.toFixed(2) + '%)</small></b></div></div><div class="optimization-comparison-grid"><section class="optimization-comparison-card"><h3>교체 항목</h3>' + buildRows + '</section><section class="optimization-comparison-card"><h3>주요 공격 스탯</h3><div class="optimization-stat-list">' + offenseHtml + '</div></section><section class="optimization-comparison-card"><h3>실전 유틸리티</h3><div class="optimization-stat-list">' + utilityHtml + '</div></section></div>';
            overview.hidden = false;
        }

function updateCrystaOptimizationProgress(progress, statusOverride, fromCache) {
            var state = progress || {};
            var status = statusOverride || state.status || 'running';
            var panel = document.getElementById('crystaOptimizationProgress');
            var statusEl = document.getElementById('crystaOptimizationStatus');
            var metaEl = document.getElementById('crystaOptimizationMeta');
            var track = document.getElementById('crystaOptimizationTrack');
            var bar = document.getElementById('crystaOptimizationBar');
            var cancel = document.getElementById('crystaOptimizationCancel');
            var continueButton = document.getElementById('crystaOptimizationContinue');
            var pause = document.getElementById('crystaOptimizationPause');
            if (!panel || !statusEl || !metaEl || !track || !bar || !cancel || !continueButton || !pause) return;
            panel.hidden = false;
            panel.className = 'optimization-progress-panel' + (status !== 'running' ? ' optimization-status-' + status : '');
            var labels = {
                running:state.stage === 'preparing' ? '전역 후보를 축약하고 있습니다.' : '전체 장비 조합을 백그라운드에서 계산 중입니다.',
                exact:'전역 최적해를 증명했습니다.',
                bounded:'제한 시간 내 최선 추천을 찾았습니다.',
                'no-incumbent-yet':'시간 제한 안에 유효 추천을 아직 찾지 못했습니다.',
                paused:'전역 계산을 일시 정지했습니다.',
                heuristic:'유효한 추천을 찾았지만 최적성 상한은 아직 없습니다.',
                cancelled:'전역 계산을 취소했습니다.',
                invalid:'현재 입력에서는 유효한 추천을 만들 수 없습니다.'
            };
            statusEl.textContent = (fromCache ? '캐시 재사용 · ' : '') + (labels[status] || labels.running);
            cancel.hidden = status !== 'running';
            pause.hidden = status !== 'running' || !(state.native || state.resumable);
            continueButton.hidden = !((status === 'bounded' || status === 'no-incumbent-yet' || status === 'paused') && state.continuationId);
            continueButton.textContent = status === 'paused' ? '계산 재개' : '정밀 계산 계속';
            var gap = state.optimalityGap === null || state.optimalityGap === undefined || state.optimalityGap === '' ? NaN : Number(state.optimalityGap);
            var determinate = status !== 'running' || (Number.isFinite(gap) && state.lowerBound !== null && state.lowerBound !== undefined);
            track.classList.toggle('is-indeterminate', !determinate);
            var percent = status === 'exact' ? 100 : Number.isFinite(gap) ? Math.max(5, Math.min(status === 'running' ? 99 : 100, (1 - Math.min(1, gap)) * 100)) : (status === 'running' ? 8 : 100);
            bar.style.width = determinate ? percent.toFixed(1) + '%' : '';
            track.setAttribute('aria-valuenow', String(Math.round(percent)));
            track.setAttribute('aria-valuetext', status === 'exact' ? '전역 최적 증명 완료' : '현재 최적성 보장 오차 ' + optimizationGapText(state.optimalityGap));
            var parts = [];
            if (Number.isFinite(Number(state.elapsedMs))) parts.push('경과 ' + (Number(state.elapsedMs) / 1000).toFixed(2) + '초');
            if (Number.isFinite(Number(state.evaluations))) parts.push('완성식 평가 ' + Number(state.evaluations).toLocaleString() + '회');
            if (Number.isFinite(Number(state.visitedNodes))) parts.push('탐색 노드 ' + Number(state.visitedNodes).toLocaleString() + '개');
            if (Number.isFinite(gap)) parts.push('최적해 대비 보장 오차 ≤ ' + optimizationGapText(gap));
            if (Number.isFinite(Number(state.deadlineRemainingMs))) parts.push('남은 예산 ' + Math.max(0, Number(state.deadlineRemainingMs) / 1000).toFixed(2) + '초');
            if (Number.isFinite(Number(state.threadsActive)) && Number.isFinite(Number(state.threadsTotal))) parts.push('활성 스레드 ' + Math.max(0, Math.floor(Number(state.threadsActive))) + '/' + Math.max(1, Math.floor(Number(state.threadsTotal))));
            if (Number.isFinite(Number(state.readyWorkItems))) parts.push('대기 작업 ' + Number(state.readyWorkItems).toLocaleString() + '개');
            var engine = optimizationEngineText(state);
            if (engine) parts.push('엔진 ' + engine);
            if (Number.isFinite(Number(state.threadsUsed))) parts.push('스레드 ' + Math.max(1, Math.floor(Number(state.threadsUsed))) + '개');
            if (state.gpuPolicy) parts.push('GPU ' + (state.gpuPolicy === 'cpu-only.v1' ? '미사용' : String(state.gpuPolicy)));
            metaEl.textContent = parts.length ? parts.join(' · ') : '입력 스냅샷과 캐시를 확인하고 있습니다.';
        }

function renderCrystaOptimizationGlobalResult(result, currentEvaluation, locks, metadata, currentCrystas) {
            var status = result && result.status || 'invalid';
            var isPreview = Boolean(metadata && metadata.preview);
            var progressPanel = document.getElementById('crystaOptimizationProgress');
            if (isPreview) { if (progressPanel) progressPanel.hidden = true; }
            else updateCrystaOptimizationProgress(result, status, metadata && metadata.cached);
            var preciseButton = document.getElementById('optimizationRunPreciseOptimization');
            if (preciseButton) preciseButton.disabled = false;
            var overview = document.getElementById('optimizationRecommendationOverview');
            var list = document.getElementById('top3ListContainer');
            var finalText = document.getElementById('finalRecText');
            var badge = document.getElementById('globalEffTextBadge');
            var tags = document.getElementById('finalRecTags');
            var finalContainer = document.getElementById('finalRecContainer');
            var optionCount = document.getElementById('optimizationRecommendationOptionCount');
            var hasRecommendation = status !== 'cancelled' && result && result.bestBuild && result.outcomes;
            if (finalContainer) finalContainer.hidden = !hasRecommendation;
            if (!hasRecommendation) {
                if (finalText) finalText.textContent = '';
                if (tags) tags.textContent = '';
                if (optionCount) optionCount.textContent = '';
            }
            if (status === 'cancelled') {
                setCrystaOptimizationRecommendationApplyAvailability(false);
                if (overview) overview.hidden = true;
                if (list) list.innerHTML = '<div class="top3-row"><b>계산이 취소되어 현재 세팅을 유지합니다.</b></div>';
                if (badge) badge.textContent = '계산 취소됨';
                return;
            }
            if (!result || !result.bestBuild || !result.outcomes) {
                setCrystaOptimizationRecommendationApplyAvailability(false);
                if (overview) overview.hidden = true;
                var diagnostic = result && result.diagnostics && result.diagnostics[0];
                var message = diagnostic && diagnostic.code === 'NO_FEASIBLE_GREEDY_BUILD'
                    ? '빠른 추천에서 요구조건을 만족하는 조합을 찾지 못했습니다. 정밀 계산을 시작하거나 요구조건·잠금·추천 제외 설정을 조정해 주세요. 가능한 조합이 없는 것으로 확정된 것은 아닙니다.'
                    : diagnostic && diagnostic.message || '추천 결과를 만들지 못했습니다. 요구조건·잠금·추천 제외 설정을 확인하고 다시 계산해 주세요.';
                if (list) list.innerHTML = '<div class="top3-row"><b>' + optimizationEscape(message) + '</b></div>';
                if (badge) badge.textContent = status === 'cancelled' ? '계산 취소됨' : '추천 불가';
                return;
            }
            var packages = result.bestBuild.packages || [];
            setCrystaOptimizationRecommendationApplyAvailability(true);
            renderCrystaOptimizationRecommendationOverview(result, currentEvaluation, locks, currentCrystas || []);
            var eyebrow = document.getElementById('optimizationRecommendationEyebrow');
            if (eyebrow) eyebrow.textContent = status === 'heuristic' ? '빠른 크리스타 추천' : '전역 최적 크리스타 추천';
            var labels = {weapon:'무기', armor:'방어구', additional:'추가', special:'특수'};
            var recommendation = '';
            packages.forEach(function (item, groupIndex) {
                var names = (item.candidateNames || []).slice(0, 2);
                while (names.length < 2) names.push('비어있음');
                recommendation += '<div>• ' + optimizationEscape(labels[item.slot] || item.metadata && item.metadata.label || item.slot) + ': <b>' + optimizationEscape(names[0]) + (locks[groupIndex * 2] ? ' 🔒' : '') + '</b> + <b>' + optimizationEscape(names[1]) + (locks[groupIndex * 2 + 1] ? ' 🔒' : '') + '</b></div>';
            });
            finalText.innerHTML = recommendation;
            var currentScore = resultDamageScore(currentEvaluation.calculation);
            var finalScore = Number(result.score);
            var gain = currentScore > 0 ? (finalScore - currentScore) / currentScore * 100 : 0;
            var scoreLabel = result.outcomes.calculation && result.outcomes.calculation.procDamageProfile && result.outcomes.calculation.procDamageProfile.sources.length ? '최종 기대 데미지: ' : '최종 데미지: ';
            var certification = status === 'exact' ? ' · 전역 최적 증명' : status === 'bounded' ? ' · 보장 오차 ≤ ' + optimizationGapText(result.optimalityGap) : status === 'heuristic' ? ' · 빠른 추천 · 최적성 미검사' : '';
            badge.textContent = scoreLabel + optimizationFormatNumber(finalScore) + ' / 현재 대비 ' + (gain > 0 ? '+' : '') + gain.toFixed(2) + '%' + certification;
            tags.style.display = 'block';
            tags.innerHTML = '<span style="display:block; font-size:14px; color:#27ae60; font-weight:bold; margin-bottom:4px; padding-bottom:4px;">[' + (status === 'heuristic' ? '빠른 추천' : '전역 추천') + ' 크리스타 옵션 합산]</span>' + buildGroupedTagsHtml(result.bestBuild.statDelta || {});
            if (optionCount) optionCount.textContent = '· 적용 옵션 ' + Object.keys(result.bestBuild.statDelta || {}).filter(function(key) { return Number(result.bestBuild.statDelta[key]) !== 0; }).length + '개';
            var summaryLabel = status === 'exact' ? '모든 남은 가지의 상한을 넘어 전역 최적임을 증명했습니다.' : status === 'paused' ? '계산을 일시 정지했습니다. 같은 탐색 상태에서 재개할 수 있습니다.' : status === 'heuristic' ? '빠르게 찾은 초기해입니다. 전역 최적성은 아직 검사하지 않았습니다.' : '시간 제한에서 찾은 최선해입니다. 표시된 gap보다 실제 최적해와의 차이가 클 수 없습니다.';
            var runtimeSummary = '';
            if (optimizationEngineText(result)) runtimeSummary += '<span>엔진 <b>' + optimizationEscape(optimizationEngineText(result)) + '</b></span>';
            if (Number.isFinite(Number(result.threadsUsed))) runtimeSummary += '<span>스레드 <b>' + Math.max(1, Math.floor(Number(result.threadsUsed))) + '개</b></span>';
            if (result.gpuPolicy) runtimeSummary += '<span>GPU <b>' + optimizationEscape(result.gpuPolicy === 'cpu-only.v1' ? '미사용' : String(result.gpuPolicy)) + '</b></span>';
            list.innerHTML = '<details class="result-detail-panel optimization-calculation-detail"><summary>계산 상세 및 최적화 검증</summary><div class="top3-row optimization-global-summary"><b>' + optimizationEscape(summaryLabel) + '</b><div class="optimization-global-summary-grid"><span>상태 <b>' + optimizationEscape(status) + '</b></span><span>대미지 <b>' + optimizationFormatNumber(finalScore) + '</b></span><span>평가 <b>' + Number(result.evaluations || 0).toLocaleString() + '회</b></span><span>보장 오차 <b>' + (status === 'heuristic' ? '미검사' : optimizationGapText(result.optimalityGap)) + '</b></span>' + runtimeSummary + '</div></div></details>';
        }

function renderMarginalUtility(results) {
            results.sort(function(a,b) { return b.gain - a.gain; });
            var maxGain = results[0] ? results[0].gain : 1;
            if(maxGain <= 0) maxGain = 1;

            var barsHtml = '';
            for(var j=0; j<results.length; j++) {
                var r = results[j];
                var widthPct = (r.gain / maxGain * 100).toFixed(1);
                if(widthPct < 0) widthPct = 0;
                barsHtml += '<div class="eff-item-container">' +
                    '<div class="eff-label"><span>' + r.label + '</span><span style="color:#d35400;">+' + r.gain.toFixed(3) + '%</span></div>' +
                    '<div class="eff-bar-bg"><div class="eff-bar-fill" style="width: ' + widthPct + '%;"></div></div></div>';
            }
            document.getElementById('effBars').innerHTML = barsHtml;
        }

function renderPreparing(mode) {
  setCrystaOptimizationRecommendationApplyAvailability(false);
  var overview = document.getElementById('optimizationRecommendationOverview'); if (overview) overview.hidden = true;
  var final = document.getElementById('finalRecContainer'); if (final) final.hidden = true;
  var precise = document.getElementById('optimizationRunPreciseOptimization'); if (precise) precise.disabled = mode === 'precise';
  document.getElementById('top3ListContainer').innerHTML = '<div class="top3-row">' + (mode === 'preview' ? '빠른 추천 초기해를 준비하고 있습니다.' : '각 부위를 따로 고르지 않고 8개 슬롯 전체를 하나의 빌드로 계산합니다.') + '</div>';
  document.getElementById('globalEffTextBadge').textContent = mode === 'preview' ? '빠른 추천 계산 중…' : '전역 계산 중…';
}
return Object.freeze({current:renderCurrent,preparing:renderPreparing,progress:updateCrystaOptimizationProgress,result:renderCrystaOptimizationGlobalResult,marginal:renderMarginalUtility});

}
