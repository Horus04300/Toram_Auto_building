function checkAndDisplayCrystaConflicts() {
    var gearNames = ["무기", "방어구", "추가 장비", "특수 장비"];
    var slotIds = [
        ['cr_wpn_1', 'cr_wpn_2'],
        ['cr_arm_1', 'cr_arm_2'],
        ['cr_add_1', 'cr_add_2'],
        ['cr_spc_1', 'cr_spc_2']
    ];

    var warnings = [];

    for (var i = 0; i < 4; i++) {
        var el1 = document.getElementById(slotIds[i][0]);
        var el2 = document.getElementById(slotIds[i][1]);

        var val1 = el1 ? el1.value : "";
        var val2 = el2 ? el2.value : "";

        var c1 = val1 ? getCrystaByName(val1) : null;
        var c2 = val2 ? getCrystaByName(val2) : null;

        if (c1 && c2 && isCrystaConflict(c1, c2)) {
            warnings.push('[' + gearNames[i] + '] ' + c1.name + ' + ' + c2.name);
        }
    }

    // 경고 박스 UI 요소 생성 및 제어
    var warnBox = document.getElementById('conflictWarningBox');
    if (!warnBox) {
        warnBox = document.createElement('div');
        warnBox.id = 'conflictWarningBox';
        warnBox.style.cssText = 'background-color:#fdedec; border:2px solid #c0392b; color:#c0392b; padding:15px; border-radius:8px; margin:15px 0; font-weight:bold; line-height:1.6; font-size:14px; box-shadow:0 2px 5px rgba(0,0,0,0.08);';

        // 크리스타 선택 영역 바로 위에 삽입 (페이지 상단에 즉시 보이도록)
        var targetAnchor = document.getElementById('crystaSection') || document.getElementById('resultArea') || document.body.firstChild;
        if (targetAnchor && targetAnchor.parentNode) {
            targetAnchor.parentNode.insertBefore(warnBox, targetAnchor);
        }
    }

    if (warnings.length > 0) {
        warnBox.innerHTML = '⚠️ <b>크리스타 장착 오류:</b> 같은 장비에 동일하거나 상/하위 관계인 크리스타가 장착되었습니다. (아래의 2슬롯 스탯은 계산에서 강제 제외됩니다.)<br>• ' + warnings.join('<br>• ');
        warnBox.style.display = 'block';
    } else {
        warnBox.style.display = 'none';
    }

    return warnings;
}

// 현재 장착 크리스타 가져오기 (계산용)
function getCurrentCrystas() {
    var slotIds = [
        ['cr_wpn_1', 'cr_wpn_2'],
        ['cr_arm_1', 'cr_arm_2'],
        ['cr_add_1', 'cr_add_2'],
        ['cr_spc_1', 'cr_spc_2']
    ];
    var results = [];

    //checkAndDisplayCrystaConflicts();

    for (var i = 0; i < 4; i++) {
        var el1 = document.getElementById(slotIds[i][0]);
        var el2 = document.getElementById(slotIds[i][1]);

        var val1 = el1 ? el1.value : "";
        var val2 = el2 ? el2.value : "";

        var c1 = val1 ? getCrystaByName(val1) : null;
        var c2 = val2 ? getCrystaByName(val2) : null;

        // 충돌 발생 시 2슬롯 스탯 제외
        if (c1 && c2 && isCrystaConflict(c1, c2)) {
            c2 = null;
        }

        results.push(c1);
        results.push(c2);
    }

    return results;
}

// 실시간 이벤트 리스너 등록 함수
function initCrystaEvents() {
    crystaMapCache = null; // 캐시 초기화
    var ids = ['cr_wpn_1','cr_wpn_2', 'cr_arm_1','cr_arm_2', 'cr_add_1','cr_add_2', 'cr_spc_1','cr_spc_2'];
    
    ids.forEach(function(id) {
        var el = document.getElementById(id);
        if (el) {
            prevCrystaSelections[id] = el.value || ""; // 로드 시 초기값 저장
            
            // 타이핑 후 다른 곳 클릭 시 검사
            el.addEventListener('change', function() {
                instantCrystaCheck(this, this.value);
            });
        }
    });
}

// 페이지 로드 시 이벤트 등록 실행
if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', initCrystaEvents);
} else {
    initCrystaEvents();
}

        function runCalculationSafe() {
            if (typeof revealResultTab === 'function') revealResultTab();
            try { runCalculation(); } 
            catch(e) { console.error(e); alert('계산 실행 중 오류가 발생했습니다.\n\n(내부 에러: ' + e.message + ')'); }
        }

        function runCalculation() {
            var baseCtx = getBaseContext();
            var currentCrystas = getCurrentCrystas();
            var curRes = simulateWithCrystas(baseCtx, currentCrystas);

            var locks = [
                document.getElementById('lock_wpn_1').checked, document.getElementById('lock_wpn_2').checked,
                document.getElementById('lock_arm_1').checked, document.getElementById('lock_arm_2').checked,
                document.getElementById('lock_add_1').checked, document.getElementById('lock_add_2').checked,
                document.getElementById('lock_spc_1').checked, document.getElementById('lock_spc_2').checked
            ];
            var categories = ['무기', '방어구', '추가', '특수'];
            var bestCrystas = currentCrystas.slice(0);
            var top3Results = [[], [], [], []];

            for(var i=0; i<4; i++) {
                var lock1 = locks[i*2];
                var lock2 = locks[i*2+1];
                
                if(lock1 && lock2) {
                    top3Results[i] = [{ c1: currentCrystas[i*2], c2: currentCrystas[i*2+1], score: curRes.damageFactor }];
                    continue; 
                }
                
                var cat = categories[i];
                var validList = [];
                for(var j=0; j<crystaDataJson.length; j++) {
                    var cc = crystaDataJson[j];
                    if(!cc || !cc.name) continue;
                    var grp = getCategoryGroup(cc.category);
                    if((grp === cat || grp === '노말') && !bannedCrystas[cc.name]) validList.push(cc);
                }
                validList.push(null);
                var c1List = lock1 ? [currentCrystas[i*2]] : validList;
                var c2List = lock2 ? [currentCrystas[i*2+1]] : validList;

                var localScores = [];
                var seenCombos = {}; // 중복 조합 체크용 객체 추가

                for(var m=0; m<c1List.length; m++) {
                    var c1 = c1List[m];
                    for(var n=0; n<c2List.length; n++) {
                        var c2 = c2List[n];
// c1.name === c2.name 대신 isCrystaConflict(c1, c2) 사용
                        if(c1 && c2 && isCrystaConflict(c1, c2)) {
                            var cur1Name = currentCrystas[i*2] ? currentCrystas[i*2].name : null;
                            var cur2Name = currentCrystas[i*2+1] ? currentCrystas[i*2+1].name : null;
                            // 사용자가 의도적으로 강제 고정(🔒)한 경우가 아니라면 해당 조합을 스킵
                            if (!(lock1 && lock2 && cur1Name === c1.name && cur2Name === c2.name)) continue;
                        }

                        // ---- 피드백 1: A+B 와 B+A 중복 방지 로직 ----
                        var n1 = c1 ? c1.name : "비어있음";
                        var n2 = c2 ? c2.name : "비어있음";
                        
                        // 이름순으로 정렬하여 고유 키(Key) 생성
                        var comboKey = n1 < n2 ? n1 + "_&_" + n2 : n2 + "_&_" + n1; 
                        
                        if (seenCombos[comboKey]) continue; // 이미 검사한 조합이면 스킵!
                        seenCombos[comboKey] = true;
                        // ---------------------------------------------
                        
                        var tempCrystas = currentCrystas.slice(0);
                        tempCrystas[i*2] = c1;
                        tempCrystas[i*2+1] = c2;
                        
                        var testRes = simulateWithCrystas(baseCtx, tempCrystas);
                        if(!isNaN(testRes.damageFactor)) {
                            localScores.push({ c1: c1, c2: c2, score: testRes.damageFactor });
                        }
                    }
                }
                localScores.sort(function(a,b){ return b.score - a.score; });
                if(localScores.length > 0) {
                    bestCrystas[i*2] = localScores[0].c1;
                    bestCrystas[i*2+1] = localScores[0].c2;
                    top3Results[i] = localScores.slice(0, 3);
                }
            }

            var optRes = simulateWithCrystas(baseCtx, bestCrystas);
            
            document.getElementById('resultArea').style.display = 'block';
            var tCtx = curRes.ctx; 

            document.getElementById('defWarning').style.display = curRes.isPierced ? 'none' : 'block';

            var totalCombinedStats = {};
            for(var x=0; x<currentCrystas.length; x++) {
                var c = currentCrystas[x];
                if(c) {
                    if(c.stats && (!c.cond || checkCondition(tCtx, c.cond))) {
                        for(var k in c.stats) totalCombinedStats[k] = (totalCombinedStats[k] || 0) + c.stats[k];
                    }
                    if(c.condStats) {
                        for(var k=0; k<c.condStats.length; k++) {
                            if(checkCondition(tCtx, c.condStats[k].cond)) {
                                for(var sk in c.condStats[k].stats) totalCombinedStats[sk] = (totalCombinedStats[sk] || 0) + c.condStats[k].stats[sk];
                            }
                        }
                    }
                }
            }
            var optContainers = ['wpnOpts', 'subOpts', 'armOpts', 'addOpts', 'spcOpts', 'buffOpts'];
            for(var i=0; i<optContainers.length; i++) {
                var container = document.getElementById(optContainers[i]);
                if(!container) continue;
                var rows = container.querySelectorAll('.opt-row');
                for(var j=0; j<rows.length; j++) {
                    var key = rows[j].querySelector('.opt-type').value;
                    var val = parseFloat(rows[j].querySelector('.opt-val').value) || 0;
                    totalCombinedStats[key] = (totalCombinedStats[key] || 0) + val;
                }
            }

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
            
            document.getElementById('resDmgFactor').innerHTML = 
                '<li>최종 크리티컬데미지 <span class="has-tooltip highlight">' + curRes.finalCDMG + '%<span class="tooltip-text">' + curRes.tooltips.cdmgTip + '</span></span></li>' +
                '<li>최종 크리티컬확률 <span class="has-tooltip">' + curRes.finalCrit + '<span class="tooltip-text">' + curRes.tooltips.critTip + '</span></span></li>' +
                '<li>최종 안정률 <span>' + curRes.finalStab + '%</span></li>' +
                '<li>' + appliedRangeLabel + ' / 속성데미지 <span class="has-tooltip">+' + appliedRangeDmg + '% / +' + tCtx.elemP + '%<span class="tooltip-text">' + curRes.tooltips.elemTip + '</span></span></li>';

            document.getElementById('resPierce').innerHTML = 
                '<li>물리관통 <span>' + tCtx.physPierce + '%</span></li>' +
                '<li>마법관통 <span>' + tCtx.magPierce + '%</span></li>' +
                '<li>타겟 DEF / MDEF <span>' + tCtx.bossDef + ' / ' + tCtx.bossMdef + '</span></li>';
            
            var actSpeed = curRes.finalASPD > 1000 ? Math.min(50, (curRes.finalASPD - 1000)/180) : 0;
            var castReduc = curRes.finalCSPD <= 1000 ? curRes.finalCSPD/20 : Math.min(100, 50 + (curRes.finalCSPD - 1000)/180);
            
// 1. ASPD 보정분 및 장비 행동속도 합산
            var baseActSpeed = curRes.finalASPD > 1000 ? Math.min(50, (curRes.finalASPD - 1000)/180) : 0;
            var equipMotionSpeed = tCtx.motionSpeed || 0; // 크리스타/장비 행동속도
            var totalActSpeed = baseActSpeed + equipMotionSpeed;

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
 
                var top3Html = '';
            for(var x=0; x<4; x++) {
                var cur1 = currentCrystas[x*2] ? currentCrystas[x*2].name : '비어있음';
                var cur2 = currentCrystas[x*2+1] ? currentCrystas[x*2+1].name : '비어있음';
                
                if (locks[x*2]) cur1 += ' 🔒';
                if (locks[x*2+1]) cur2 += ' 🔒';
                
                top3Html += '<div class="top3-row"><h5>🎯 ' + categories[x] + ' 슬롯 (Top 3 딜 효율)</h5>';
                top3Html += '<div style="font-size:13px; color:#7f8c8d; margin-bottom:6px; font-weight:bold;">▷ 현재 장착 중: [' + cur1 + '] + [' + cur2 + ']</div>';                if(locks[x*2] && locks[x*2+1]) {
                    top3Html += '<div style="font-size:13px; color:#c0392b;">해당 부위는 모두 고정(🔒)되어 최적화에서 제외되었습니다.</div></div>';
                    continue;
                }
                
                top3Html += '<ul class="top3-list">';
                var list = top3Results[x];
                var curDmg = curRes.damageFactor;

                for(var y=0; y<list.length; y++) {
                    var n1 = list[y].c1 ? list[y].c1.name : '비어있음';
                    var n2 = list[y].c2 ? list[y].c2.name : '비어있음';
                    var gainPct = curDmg > 0 ? ((list[y].score - curDmg)/curDmg * 100) : 0;
                    var sign = gainPct > 0 ? '+' : '';
                    var color = gainPct > 0 ? '#27ae60' : (gainPct < 0 ? '#c0392b' : '#7f8c8d');
                    var dmgStr = Math.floor(list[y].score).toLocaleString();
                    top3Html += '<li>' + (y+1) + '위: <b>' + n1 + '</b> + <b>' + n2 + '</b> <span style="font-size:13px; font-weight:bold; color:'+color+';">(데미지: ' + dmgStr + ' / 상승량: ' + sign + gainPct.toFixed(2) + '%)</span></li>';
                }
                top3Html += '</ul></div>';
            }
            document.getElementById('top3ListContainer').innerHTML = top3Html;

            // 🏆 메인 타이틀 우측 태그에 현재 데미지 1회만 업데이트
            var curDmgStr = Math.floor(curRes.damageFactor).toLocaleString();
            var top3BadgeEl = document.getElementById('top3CurrentDmgBadge');
            if (top3BadgeEl) {
                top3BadgeEl.innerHTML = '현재 세팅 데미지: ' + curDmgStr;
                top3BadgeEl.style.display = 'inline-block';
            }

            var finalRecHtml = '';
            for(var x=0; x<4; x++) {
                var n1 = bestCrystas[x*2] ? bestCrystas[x*2].name : "비어있음";
                var n2 = bestCrystas[x*2+1] ? bestCrystas[x*2+1].name : "비어있음";
                var l1 = locks[x*2] ? " 🔒" : "";
                var l2 = locks[x*2+1] ? " 🔒" : "";
                finalRecHtml += '<div>• ' + categories[x] + ': <b>' + n1 + l1 + '</b> + <b>' + n2 + l2 + '</b></div>';
            }
            document.getElementById('finalRecText').innerHTML = finalRecHtml;
            var totalGain = (curRes.damageFactor && curRes.damageFactor > 0) ? ((optRes.damageFactor - curRes.damageFactor) / curRes.damageFactor * 100) : 0;
            var totalSign = totalGain > 0 ? '+' : '';
            var optDmgStr = Math.floor(optRes.damageFactor).toLocaleString(); // 최종 데미지 가져오기
            document.getElementById('globalEffTextBadge').innerHTML = '최종 데미지: ' + optDmgStr + ' / 현재 대비 총 딜 상승률: ' + totalSign + totalGain.toFixed(2) + '%';
            var sumStats = {};
            for(var x=0; x<bestCrystas.length; x++) {
                var c = bestCrystas[x];
                if(c) {
                    if(c.stats && (!c.cond || checkCondition(optRes.ctx, c.cond))) {
                        for(var k in c.stats) sumStats[k] = (sumStats[k] || 0) + c.stats[k];
                    }
                    if(c.condStats) {
                        for(var k=0; k<c.condStats.length; k++) {
                            if(checkCondition(optRes.ctx, c.condStats[k].cond)) {
                                for(var sk in c.condStats[k].stats) sumStats[sk] = (sumStats[sk] || 0) + c.condStats[k].stats[sk];
                            }
                        }
                    }
                }
            }

            // 2. [최종 조합 크리스타 옵션 합산] 에 그룹화 적용 및 CSS 충돌 방지
            var tagHtml = '<span style="display:block; font-size:14px; color:#27ae60; font-weight:bold; margin-bottom:4px; padding-bottom:4px;">[최종 조합 크리스타 옵션 합산]</span>';
            tagHtml += buildGroupedTagsHtml(sumStats);
            
            var finalTagsContainer = document.getElementById('finalRecTags');
            finalTagsContainer.style.display = 'block'; // flex 속성 무력화하여 블록 구조 유지
            finalTagsContainer.innerHTML = tagHtml;

                // 효율 탭에서 재사용할 수 있도록 계산 데이터 임시 저장
                window.lastEffData = {
                    baseCtx: baseCtx,
                    curCrystas: currentCrystas,
                    curBaseDF: curRes.damageFactor
                };
                
                // 현재 선택된 탭의 단위(1, 5, 10)를 가져와서 효율 렌더링
                var activeTab = document.querySelector('.eff-tab-btn.active');
                var activeUnit = activeTab ? parseInt(activeTab.getAttribute('data-unit'), 10) : 1;
                renderMarginalUtility(activeUnit);
            }

        function renderMarginalUtility(unit) {
            if (!window.lastEffData) return;
            var baseCtx = window.lastEffData.baseCtx;
            var curCrystas = window.lastEffData.curCrystas;
            var curBaseDF = window.lastEffData.curBaseDF;

            var u = unit || 1; // 1, 5, 10 단위

            var isMag = baseCtx.atkType === 'MAG';
            var pierceKey = isMag ? 'MAG_PIERCE' : 'PHYS_PIERCE';
            var pierceLabel = isMag ? '마법관통 %p (+' + u + '%)' : '물리관통 %p (+' + u + '%)';
            var rangeKey = baseCtx.rangeType === 'SHORT' ? 'SRW' : 'LRW';
            var rangeLabel = baseCtx.rangeType === 'SHORT' ? '근거리위력 %p (+' + u + '%)' : '원거리위력 %p (+' + u + '%)';

            var targets = [
                { key: 'ATKP', label: 'ATK %p (+' + u + '%)' }, 
                { key: 'ATK', label: 'ATK 깡공 (+' + u + ')' },
                { key: 'MATKP', label: 'MATK %p (+' + u + '%)' }, 
                { key: 'MATK', label: 'MATK 깡공 (+' + u + ')' },
                { key: 'CDMG_P', label: '크리티컬데미지 %p (+' + u + '%)' },
                { key: 'CDMG', label: '크리티컬데미지 (+' + u + ')' },
                { key: 'CRIT_P', label: '크리티컬확률 %p (+' + u + '%)' },
                { key: 'CRIT', label: '크리티컬확률 (+' + u + ')' },
                { key: 'STRP', label: 'STR %p (+' + u + '%)' },
                { key: 'DEXP', label: 'DEX %p (+' + u + '%)' },
                { key: 'INTP', label: 'INT %p (+' + u + '%)' },
                { key: 'WATKP', label: '무기ATK %p (+' + u + '%)' },
                { key: 'WATK', label: '무기ATK (+' + u + ')' },
                { key: pierceKey, label: pierceLabel },
                { key: rangeKey, label: rangeLabel }, 
                { key: 'ELEM_P', label: '속성데미지 %p (+' + u + '%)' },
                { key: 'STABILITY', label: '안정률 %p (+' + u + '%)' }
            ];
            if (baseCtx.chkIsUnsheathe) {
                targets.push({ key: 'UNSHEATHE', label: '발도위력 %p (+' + u + '%)' });
            }
            
            var keyMap = { 
                'ATKP':'atkP', 'ATK':'atkF', 'MATKP':'matkP', 'MATK':'matkF', 
                'CDMG_P':'cdmgP', 'CDMG':'cdmgF', 'CRIT_P':'critP', 'CRIT':'critF',
                'STRP':'strP', 'DEXP':'dexP', 'INTP':'intP',
                'WATKP':'watkP', 'WATK':'watkF', 'STABILITY':'stability', 'ELEM_P':'elemP',
                'PHYS_PIERCE':'physPierce', 'MAG_PIERCE':'magPierce', 'SRW':'srw', 'LRW':'lrw', 'UNSHEATHE':'unsheathe' 
            };
            
            var results = [];
            for(var i=0; i<targets.length; i++) {
                var t = targets[i];
                var testCtx = cloneCtx(baseCtx);
                testCtx[keyMap[t.key]] += u; // 1단위가 아닌 선택된 단위(u)만큼 더하기
                
                var testRes = simulateWithCrystas(testCtx, curCrystas);
                var gain = (curBaseDF && curBaseDF > 0) ? ((testRes.damageFactor - curBaseDF) / curBaseDF * 100) : 0;
                
                if (gain >= 0.001) {
                    results.push({ label: t.label, gain: gain });
                }
            }

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

function initializeOptimizerUi() {
    populateRefineSelects();
    updateSubWeaponList();
    initAutocomplete();
    renderBanTags();
    addDefaultOptions('wpnOpts');
    addDefaultOptions('armOpts');
    var effTabs = document.getElementById('effTabs');
    if (effTabs) {
        effTabs.addEventListener('click', function(e) {
            if (e.target.classList.contains('eff-tab-btn')) {
                var btns = effTabs.querySelectorAll('.eff-tab-btn');
                btns.forEach(function(btn) { btn.classList.remove('active'); });
                e.target.classList.add('active');
                renderMarginalUtility(parseInt(e.target.getAttribute('data-unit'), 10));
            }
        });
    }
}

window.ToramApp = window.ToramApp || {};
window.ToramApp.optimizer = Object.freeze({
    initialize: initializeOptimizerUi,
    runCalculationSafe: runCalculationSafe
});