        function applyStat(ctx, key, val) {
            if(!key || isNaN(val)) return;
            var k = key.toUpperCase().trim();
            if (k === 'ATKP' || k === 'ATK%' || k === 'ATK_P') ctx.atkP += val;
            else if (k === 'ATK' || k === 'ATK+') ctx.atkF += val;
            else if (k === 'MATKP' || k === 'MATK%' || k === 'MATK_P') ctx.matkP += val;
            else if (k === 'MATK' || k === 'MATK+') ctx.matkF += val;
            else if (k === 'STRP' || k === 'STR%' || k === 'STR_P') ctx.strP += val;
            else if (k === 'STR' || k === 'STR+') ctx.strF += val;
            else if (k === 'DEXP' || k === 'DEX%' || k === 'DEX_P') ctx.dexP += val;
            else if (k === 'DEX' || k === 'DEX+') ctx.dexF += val;
            else if (k === 'AGIP' || k === 'AGI%' || k === 'AGI_P') ctx.agiP += val;
            else if (k === 'AGI' || k === 'AGI+') ctx.agiF += val;
            else if (k === 'INTP' || k === 'INT%' || k === 'INT_P') ctx.intP += val;
            else if (k === 'INT' || k === 'INT+') ctx.intF += val;
            else if (k === 'CDMG_P' || k === 'CDMG%' || k === 'CDMG_PCT' || k === 'CDMGP') ctx.cdmgP += val;
            else if (k === 'CDMG' || k === 'CDMG+') ctx.cdmgF += val;
            else if (k === 'CRIT_P' || k === 'CRIT%' || k === 'CRITP') ctx.critP += val;
            else if (k === 'CRIT' || k === 'CRIT+') ctx.critF += val;
            else if (k === 'SRW' || k === '근거리위력') ctx.srw += val;
            else if (k === 'LRW' || k === '원거리위력') ctx.lrw += val;
            else if (k === 'UNSHEATHE' || k === '발도위력' || k === 'UNSHEATHEP') ctx.unsheathe += val;
            else if (k === 'PHYS_PIERCE' || k === '물리관통') ctx.physPierce += val;
            else if (k === 'MAG_PIERCE' || k === '마법관통') ctx.magPierce += val;
            else if (k === 'ELEM_P' || k === '속성데미지' || k === '속성에유리') ctx.elemP += val;
            else if (k === 'ELEM_AWAKENING') ctx.elementAwakening = ctx.elementAwakening || val > 0;
            else if (k === 'MAGIC_ELEMENT') ctx.magicElement = ctx.magicElement || val > 0;
            else if (k === 'DAMAGE_P' || k === 'DAMAGE%' || k === '스킬데미지') ctx.damageP += val;
            else if (k === 'MAXMP' || k === 'MAX_MP' || k === '최대MP') ctx.maxMpF += val;
            else if (k === 'WATKP' || k === '무기ATK%') ctx.watkP += val;
            else if (k === 'WATK' || k === '무기ATK+') ctx.watkF += val;
            else if (k === 'ASPD') ctx.aspdF += val;
            else if (k === 'ASPD_P' || k === 'ASPD%') ctx.aspdP += val;
            else if (k === 'CSPD') ctx.cspdF += val;
            else if (k === 'CSPD_P' || k === 'CSPD%') ctx.cspdP += val;
            else if (k === 'STABILITY' || k === '안정률') ctx.stability += val;
            else if (k === 'MOTIONSPEED' || k === 'MOTION_SPEED' || k === 'MS' || k === '행동속도') ctx.motionSpeed += val;
            else if (k === 'CAST_RED' || k === 'CHARGE_RED' || k === 'LINE_RED' || k === 'CAST_TIME' || k === 'CHARGE_TIME' || k === '영창' || k === '시전시간' || k === '영창감소' || k === '시전감소') ctx.castRed += val;
            else if (k === 'ATK_UP_STR') ctx.atkUpSTR += val;
            else if (k === 'ATK_UP_DEX') ctx.atkUpDEX += val;
            else if (k === 'ATK_UP_INT') ctx.atkUpINT += val;
            else if (k === 'ATK_UP_AGI') ctx.atkUpAGI += val;
            else if (k === 'ATK_UP_VIT') ctx.atkUpVIT += val;
            else if (k === 'MATK_UP_STR') ctx.matkUpSTR += val;
            else if (k === 'MATK_UP_DEX') ctx.matkUpDEX += val;
            else if (k === 'MATK_UP_INT') ctx.matkUpINT += val;
            else if (k === 'MATK_UP_AGI') ctx.matkUpAGI += val;
            else if (k === 'MATK_UP_VIT') ctx.matkUpVIT += val;
        }

        function skillInvestment(treeId, skillId) {
            var simulator = window.skillSimulatorState;
            var investments = simulator && typeof simulator.getInvestments === 'function' ? simulator.getInvestments() : {};
            return Math.max(0, Number(investments[treeId] && investments[treeId][skillId]) || 0);
        }
        function activeBuffIsEnabled(skillId) {
            var selections = window.ToramActiveBuffs && typeof window.ToramActiveBuffs.getSelections === 'function'
                ? window.ToramActiveBuffs.getSelections() : {};
            var setting = selections[skillId];
            return setting === true || Boolean(setting && setting.active);
        }
        function getBaseContext() {
            var appliedComboHit = window.ToramComboUi && typeof window.ToramComboUi.getAppliedHit === 'function'
                ? window.ToramComboUi.getAppliedHit() : null;
            var ctx = {
                level: parseFloat(document.getElementById('charLevel').value) || 0,
                strBase: parseFloat(document.getElementById('strBase').value) || 0,
                intBase: parseFloat(document.getElementById('intBase').value) || 0,
                vitBase: parseFloat(document.getElementById('vitBase').value) || 0,
                agiBase: parseFloat(document.getElementById('agiBase').value) || 0,
                dexBase: parseFloat(document.getElementById('dexBase').value) || 0,
                crtBase: parseFloat(document.getElementById('crtBase').value) || 0,

                atkType: appliedComboHit ? appliedComboHit.atkType : 'PHYS',
                rangeType: appliedComboHit ? appliedComboHit.rangeType : 'SHORT',
                mainType: document.getElementById('mainWeaponType').value,
                wpnAtk: document.getElementById('mainWeaponType').value === '맨손' ? 0 : (parseFloat(document.getElementById('wpnAtk').value) || 0),
                wpnRefine: document.getElementById('mainWeaponType').value === '맨손' ? 0 : (parseFloat(document.getElementById('wpnRefine').value) || 0),
                wpnStab: document.getElementById('mainWeaponType').value === '맨손' ? 1 : (parseFloat(document.getElementById('wpnStab').value) || 80),
                subType: document.getElementById('subWeaponType').value,
                subAtk: parseFloat(document.getElementById('subAtk').value) || 0,
                subRefine: parseFloat(document.getElementById('subRefine').value) || 0,
                subStab: parseFloat(document.getElementById('subStab').value) || 0,
                armorType: document.getElementById('armorType').value,

                bossLevel: parseFloat(document.getElementById('bossLevel').value) || 0,
                bossDef: parseFloat(document.getElementById('bossDef').value) || 0,
                bossMdef: parseFloat(document.getElementById('bossMdef').value) || 0,
                bossCritResist: parseFloat(document.getElementById('bossCritResist').value) || 0,
                bossPhysResist: parseFloat(document.getElementById('bossPhysResist').value) || 0,
                bossMagResist: parseFloat(document.getElementById('bossMagResist').value) || 0,
                skillMult: appliedComboHit ? appliedComboHit.skillMult : 1,
                skillConst: appliedComboHit ? appliedComboHit.skillConst : 1000,

                chkIsUnsheathe: Boolean(appliedComboHit && appliedComboHit.unsheathe),
                conversionLevel: skillInvestment('MagicBlade', 1),
                conversionActive: activeBuffIsEnabled('MagicBlade:1'),
                dualBringerLevel: skillInvestment('MagicBlade', 4),
                dualBringerActive: activeBuffIsEnabled('MagicBlade:4'),
                chkGuaranteedCrit: Boolean(appliedComboHit && appliedComboHit.guaranteedCritical),

                strP: 0, strF: 0, dexP: 0, dexF: 0, intP: 0, intF: 0, agiP: 0, agiF: 0, vitP: 0, vitF: 0,
                atkP: 0, atkF: 0, matkP: 0, matkF: 0, cdmgP: 0, cdmgF: 0, 
                critP: 0, critF: 0, srw: 0, lrw: 0, unsheathe: 0, elemP: 0, damageP: 0, watkP: 0, watkF: 0,
                physPierce: 0, magPierce: 0, aspdF: 0, aspdP: 0, cspdF: 0, cspdP: 0, stability: 0, motionSpeed: 0, castRed: 0, maxMpF: 0,
                elementAwakening: false, magicElement: false,
                atkUpSTR: 0, atkUpDEX: 0, atkUpINT: 0, atkUpAGI: 0, atkUpVIT: 0,
                matkUpSTR: 0, matkUpDEX: 0, matkUpINT: 0, matkUpAGI: 0, matkUpVIT: 0
            };
            var optContainers = ['wpnOpts', 'subOpts', 'armOpts', 'addOpts', 'spcOpts', 'buffOpts'];
            for(var i=0; i<optContainers.length; i++) {
                var container = document.getElementById(optContainers[i]);
                if(!container) continue;
                var rows = container.querySelectorAll('.opt-row');
                for(var j=0; j<rows.length; j++) {
                    var key = rows[j].querySelector('.opt-type').value;
                    var val = parseFloat(rows[j].querySelector('.opt-val').value) || 0;
                    applyStat(ctx, key, val);
                } // <-- 첫 번째 누락된 중괄호 복구
            } // <-- 두 번째 누락된 중괄호 복구
            // 스킬별 계수·상수는 콤보 탭에서 선택한 타격을 통해 주입한다.
            ctx.skillStats = [];

            return ctx;
        }
        function cloneCtx(baseCtx) {
            var newCtx = {};
            for(var key in baseCtx) { newCtx[key] = baseCtx[key]; }
            return newCtx;
        }

        function applyPassiveSkillStats(ctx) {
            if (!window.ToramSkillEffects) return;
            window.ToramSkillEffects.passiveStatChanges(ctx).forEach(function (change) {
                applyStat(ctx, change.key, change.value);
            });
        }

        function simulateWithCrystas(baseCtx, crystas) {
            var ctx = cloneCtx(baseCtx);
            for(var i=0; i<crystas.length; i++) {
                var c = crystas[i];
                if(!c) continue;
                
                if(c.stats) {
                    if(!c.cond || checkCondition(ctx, c.cond)) {
                        for(var key in c.stats) applyStat(ctx, key, parseFloat(c.stats[key]) || 0);
                    }
                }
                
                if (c.condStats) {
                    for(var k=0; k<c.condStats.length; k++) {
                        var cItem = c.condStats[k];
                        if (checkCondition(ctx, cItem.cond)) {
                            for(var key in cItem.stats) applyStat(ctx, key, parseFloat(cItem.stats[key]) || 0);
                        }
                    }
                }
            }

            var totalSTR = Math.floor(ctx.strBase * (1 + ctx.strP/100) + ctx.strF);
            var totalDEX = Math.floor(ctx.dexBase * (1 + ctx.dexP/100) + ctx.dexF);
            var totalINT = Math.floor(ctx.intBase * (1 + ctx.intP/100) + ctx.intF);
            var totalAGI = Math.floor(ctx.agiBase * (1 + ctx.agiP/100) + ctx.agiF);
            var totalVIT = Math.floor(ctx.vitBase * (1 + ctx.vitP/100) + ctx.vitF);
            var finalMaxMP = Math.max(0, Math.floor(100 + Number(ctx.level) + totalINT * 0.1 + ctx.maxMpF));
            
            var statAtkUp = Math.floor(totalSTR * ctx.atkUpSTR / 100) + 
                            Math.floor(totalDEX * ctx.atkUpDEX / 100) + 
                            Math.floor(totalINT * ctx.atkUpINT / 100) + 
                            Math.floor(totalAGI * ctx.atkUpAGI / 100) + 
                            Math.floor(totalVIT * ctx.atkUpVIT / 100);

            var statMatkUp = Math.floor(totalSTR * ctx.matkUpSTR / 100) + 
                            Math.floor(totalDEX * ctx.matkUpDEX / 100) + 
                            Math.floor(totalINT * ctx.matkUpINT / 100) + 
                            Math.floor(totalAGI * ctx.matkUpAGI / 100) + 
                            Math.floor(totalVIT * ctx.matkUpVIT / 100);


            // 1. 최종 무기 공격력 연산 (무기ATK% 적용 후 무기ATK+ 합산)
            var mainWpnBase = Math.floor(ctx.wpnAtk * (1 + ctx.watkP / 100)) + ctx.watkF;
            var refineWpnBonus = Math.floor(ctx.wpnAtk * Math.pow(ctx.wpnRefine, 2) / 100) + ctx.wpnRefine;
            var baseWpnAtk = mainWpnBase + refineWpnBonus;

            if (ctx.subType === '화살' && (ctx.mainType === '활' || ctx.mainType === '자동활')) {
                baseWpnAtk += Math.floor(ctx.subAtk) + Math.floor(ctx.subAtk * Math.pow(ctx.subRefine, 2)/100) + ctx.subRefine;
            }

            var statAtk = 0;
            var statMatk = totalINT * 4 + totalDEX * 1; 
            var matkRatio = (ctx.mainType === '지팡이' || ctx.mainType === '마도구' || (ctx.subType === '마도구' && ctx.isConversion)) ? 1.0 : 0.0;
            var wpnMatkContrib = Math.floor(mainWpnBase * matkRatio);
            var m = ctx.mainType;

            if (m === '한손검') { 
                if(ctx.subType === '한손검(듀얼소드)') {
                    // 듀얼소드 메인 무기 스탯 반영: STR 1, AGI 1, DEX 2
                    statAtk = totalSTR*1 + totalAGI*1 + totalDEX*2;
                } else {
                    // 일반 한손검 스탯 반영: STR 2, DEX 2
                    statAtk = totalSTR*2 + totalDEX*2; 
                }
                statMatk = totalINT*3 + totalDEX*1; 
            }
            else if (m === '양손검') { statAtk = totalSTR*3 + totalDEX*1; statMatk = totalINT*3 + totalDEX*1; }
            else if (m === '활') { statAtk = totalSTR*1 + totalDEX*3; statMatk = totalINT*3 + totalDEX*1; }
            else if (m === '자동활') { statAtk = totalDEX*4; statMatk = totalINT*3 + totalDEX*1; }
            else if (m === '지팡이') { statAtk = totalSTR*3 + totalINT*1; statMatk = totalINT*4 + totalDEX*1; matkRatio = 1.0; }
            else if (m === '마도구') { statAtk = totalINT*2 + totalAGI*2; statMatk = totalINT*4 + totalDEX*1; matkRatio = 1.0; }
            else if (m === '권갑') { statAtk = totalAGI*2 + totalDEX*0.5 + totalSTR*0.5; statMatk = totalINT*4 + totalDEX*1; matkRatio = 0.5; }
            else if (m === '선풍창') { statAtk = totalSTR*2.5 + totalAGI*1.5; statMatk = totalINT*3 + totalDEX*1; }
            else if (m === '발도검') { statAtk = totalDEX*2.5 + totalSTR*1.5; statMatk = totalINT*3 + totalDEX*1; }
            else { statAtk = totalSTR*1; statMatk = totalINT*3 + totalDEX*1; }

            var conversionAddMatk = 0;
            if (ctx.conversionActive && ctx.conversionLevel > 0) {
                conversionAddMatk = baseWpnAtk * Math.pow(ctx.conversionLevel, 2) / 100;
                if (ctx.mainType === '권갑') conversionAddMatk /= 2;
            }

            //  서브 마도구 페널티 및 '마법전사의 마음가짐' 연산 로직
            // =========================================================================
            var subMagDeviceAtkPenalty = 0;
            var magWarriorTooltip = '';

            if (ctx.subType === '마도구') {
                subMagDeviceAtkPenalty = -15; // 서브 마도구 기본 ATK -15% 페널티
                // 마음가짐의 ATK% 완화는 applyPassiveSkillStats가 투자 레벨에 따라 이미 더한다.
                var finalSubPenalty = subMagDeviceAtkPenalty;
                ctx.atkP += finalSubPenalty; // 최종 총 ATK%에 합산
                
                // 툴팁 출력용 텍스트 세팅
                if (finalSubPenalty < 0) {
                    magWarriorTooltip = `서브마도구 ATK ${finalSubPenalty}%`;
                }
            }


            // 3. 무기별 MATK 반영률 (지팡이, 마도구, 서브마도구+컨버전 시 1.0 / 그 외 0.0)     
            var matkRatio = (ctx.mainType === '지팡이' || ctx.mainType === '마도구' || (ctx.subType === '마도구' && ctx.isConversion)) ? 1.0 : 0.0;
            var wpnMatkContrib = Math.floor(baseWpnAtk * matkRatio);

            // 4. 최종 물리 ATK 산출
            var preFinalAtk = baseWpnAtk + statAtk + Number(ctx.level) + statAtkUp;
            var finalATK = Math.floor(preFinalAtk * (1 + ctx.atkP / 100)) + ctx.atkF;

            // ---- 피드백 1: 듀얼소드(서브 한손검) 최종 ATK 및 서브 ATK 로직 추가 ----
            var finalSubAtk = 0;
            var finalSubStab = 0;
            var isDualSword = (ctx.mainType === '한손검' && ctx.subType === '한손검(듀얼소드)');
            
            if (isDualSword) {
                // 서브 무기 최종 공격력 (재련치 제곱을 200으로 나눔)
                var subWpnBase = Math.floor(ctx.subAtk + (ctx.subAtk * ctx.watkP / 100) + (ctx.subAtk * Math.pow(ctx.subRefine, 2) / 200) + ctx.subRefine + ctx.watkF);
                
                // 서브 스탯 공격력 (통상 듀얼소드 서브 스탯은 STR 1 + AGI 3)
                var subStatAtk = Math.floor((totalSTR * 1) + (totalAGI * 3));
                
                // 서브 ATK
                var preFinalSubAtk = subWpnBase + subStatAtk + ctx.level;
                finalSubAtk = Math.floor(preFinalSubAtk * (1 + ctx.atkP / 100)) + ctx.atkF;
                
                // 서브 안정률 (최대 100%)
                finalSubStab = Math.floor(ctx.subStab * 0.5 + totalSTR * 0.06 + totalAGI * 0.04 + ctx.stability);
                if (finalSubStab > 100) finalSubStab = 100;
                
                // 듀얼소드 최종 ATK 합산
                finalATK = finalATK + Math.floor(finalSubAtk * finalSubStab / 100);
            }
            // -------------------------------------------------------------


            // 최종 마법 MATK 산출 
            var preFinalMatk = wpnMatkContrib + statMatk + Number(ctx.level) + (conversionAddMatk || 0) + statMatkUp;
            var finalMATK = Math.floor(preFinalMatk * (1 + ctx.matkP / 100)) + ctx.matkF;
            
            
            var baseCDMG = (totalSTR >= totalAGI) ? 150 + Math.floor(totalSTR/5) : 150 + Math.floor((totalSTR+totalAGI)/10);
            var calcCDMG = Math.floor(baseCDMG * (1 + ctx.cdmgP/100)) + ctx.cdmgF;
            if (calcCDMG > 300) calcCDMG = 300 + Math.floor((calcCDMG - 300)/2);
            
            var baseCrit = 25 + Math.floor(ctx.crtBase / 3.4);
            var finalCrit = Math.floor(baseCrit * (1 + ctx.critP/100)) + ctx.critF;
            
            var baseASPDConst = BASE_ASPD_MAP[m] || 100;
            var statAspd = 0;
            
            if (m === "한손검" || ctx.subType === "한손검(듀얼소드)") { statAspd = (totalAGI * 4.2) + (totalSTR * 0.2); }
            else if (m === "양손검") { statAspd = (totalAGI * 2.1) + (totalSTR * 0.2); }
            else if (m === "활") { statAspd = (totalAGI * 3.1) + (totalDEX * 0.2); }
            else if (m === "자동활") { statAspd = (totalAGI * 2.2) + (totalDEX * 0.2); }
            else if (m === "지팡이") { statAspd = (totalAGI * 1.8) + (totalINT * 0.2); }
            else if (m === "마도구") { statAspd = (totalAGI * 4.0) + (totalINT * 0.2); }
            else if (m === "권갑") { statAspd = (totalAGI * 4.6) + (totalDEX * 0.1) + (totalSTR * 0.1); }
            else if (m === "선풍창") { statAspd = (totalAGI * 3.5) + (totalSTR * 0.2); }
            else if (m === "발도검") { statAspd = (totalAGI * 3.9) + (totalDEX * 0.3); }
            else { statAspd = totalAGI * 9.6; }

            var armorAspdP = 0;
            if(ctx.armorType === '경량옷') armorAspdP = 50;
            else if(ctx.armorType === '중량옷') armorAspdP = -50;
            
            var preAspd = baseASPDConst + Math.floor(statAspd) + Number(ctx.level);
            var finalASPD = Math.floor(preAspd * (1 + (ctx.aspdP + armorAspdP) / 100)) + ctx.aspdF;

            var preCspd = Number(ctx.level) + Math.floor(1.16 * totalAGI) + Math.floor(2.94 * totalDEX);
            var finalCSPD = Math.floor(preCspd * (1 + ctx.cspdP / 100)) + ctx.cspdF;

            var aspdMotionBonus = finalASPD >= 1000 ? (finalASPD - 1000) / 180 : 0;
            var aspdMotionFloor = Math.min(50, Math.floor(aspdMotionBonus));
            var finalMotionSpeed = aspdMotionFloor + (ctx.motionSpeed || 0);

            var cspdCastRed = finalCSPD <= 1000 ? (finalCSPD / 20) : (50 + (finalCSPD - 1000) / 180);
            cspdCastRed = Math.min(100, cspdCastRed);
            var totalCastRed = Math.min(100, Math.floor(cspdCastRed) + (ctx.castRed || 0));


            var statStab = 0;
            if(m==='한손검') statStab = (totalSTR + totalDEX*3)/40;
            else if(m==='양손검') statStab = totalDEX/10;
            else if(m==='활') statStab = (totalSTR + totalDEX*3)/40;
            else if(m==='자동활') statStab = totalSTR/20; 
            else if(m==='지팡이') statStab = totalSTR/20;
            else if(m==='마도구') statStab = totalDEX/10;
            else if(m==='권갑') statStab = totalDEX/40;
            else if(m==='선풍창') statStab = (totalSTR + totalDEX)/40;
            else if(m==='발도검') statStab = (totalSTR*3 + totalDEX)/40;
            
            var physStab = ctx.wpnStab + ctx.stability + Math.floor(statStab);
            if (ctx.subType === '화살' && (ctx.mainType === '활' || ctx.mainType === '자동활')) {
                physStab += ctx.subStab;
            }
            if(physStab > 100) physStab = 100;

// --- 1. 약점 속성 및 순수 기본 INT 기준 속성에 유리 보너스 계산 ---
    var hasElementAwakening = Boolean(ctx.elementAwakening);
    var hasMagicElement = Boolean(ctx.magicElement);

    // 내부 엔진/외부 컨텍스트의 속성에 유리 안전 확보
    var baseElemDmg = 0;
    if (typeof tCtx !== 'undefined' && typeof tCtx.elemP !== 'undefined') {
        baseElemDmg = tCtx.elemP;
    } else if (typeof ctx !== 'undefined') {
        baseElemDmg = ctx.elemDmg || ctx.elemDmgP || ctx.elemP || 0;
    }

    var currentElemDmg = baseElemDmg;
    var elemTipText = `기본 장비 속성에 유리: +${baseElemDmg}%\n`;

    if (hasElementAwakening) {
        currentElemDmg += 25;
        elemTipText += `약점 속성 공격 보너스: +25%\n`;
    }
    if (hasElementAwakening || hasMagicElement) {
        var pureBaseINT = (typeof ctx !== 'undefined' && ctx.intBase) ? ctx.intBase : 0;
        var intElemBonus = Math.floor(pureBaseINT / 10);
        currentElemDmg += intElemBonus;
        elemTipText += `기본 INT 비례 보너스(INT ${pureBaseINT} / 10): +${intElemBonus}%\n`;
    }

    elemTipText += `최종 적용 속성에 유리: +${currentElemDmg}%`;

    // 변수 동기화
    if (typeof tCtx !== 'undefined') {
        tCtx.elemP = currentElemDmg;
        tCtx.elemDmg = currentElemDmg;
    }
    if (typeof ctx !== 'undefined') {
        ctx.elemDmg = currentElemDmg;
        ctx.elemDmgP = currentElemDmg;
        ctx.elemP = currentElemDmg;
    }

    // --- 2. 공격 유형별 크리티컬 및 데미지 연산 (기존 v1.0.3 구조 유지) ---
    var isMag = (ctx.atkType === 'MAG');
    var finalCritRate = finalCrit;
    var finalCdmgVal = calcCDMG;
    var finalStab = physStab;
    
    var critTip = `기초 크리율: 25 + 스탯보정(${Math.floor(ctx.crtBase / 3.4)}) = ${baseCrit}\n옵션 보정: +${ctx.critP}%, +${ctx.critF}\n`;
    var cdmgTip = `기초 크뎀: ${baseCDMG}\n옵션 보정: +${ctx.cdmgP}%, +${ctx.cdmgF}\n`;

    if (isMag) {
        // 마법 크리 반영률: 스펠 버스트(25%) + 쇠약(50%) = 기본 75% 상시 적용
        var magCritReflect = 25 + 50; 
        if (ctx.dualBringerActive && ctx.subType === '마도구' && (totalSTR >= totalINT)) {
            magCritReflect += 2.5 * ctx.dualBringerLevel;
        }
        if (ctx.mainType === '지팡이' && ctx.element === '무속성') {
            magCritReflect += 25;
        }

        finalCritRate = Math.floor(finalCrit * (magCritReflect / 100));
        critTip += `마법 크리 반영률: ${magCritReflect}% (최종: ${finalCritRate})`;
        
        var magCdmgReflect = 50 + 25; // 기본 50% + 스펠 버스트 25%
        if (ctx.dualBringerActive && ctx.subType === '마도구' && (totalINT > totalSTR)) {
            magCdmgReflect += 2.5 * ctx.dualBringerLevel;
        }
        
        finalCdmgVal = 100 + Math.floor((calcCDMG - 100) * (magCdmgReflect / 100));
        cdmgTip += `마법 크뎀 반영률: ${magCdmgReflect}% (최종: ${finalCdmgVal}%)`;

    finalStab = Math.floor(50 + physStab / 2);
        if (finalStab > 100) finalStab = 100;
    } else {
        critTip += `최종 확률: ${finalCritRate}`;
        cdmgTip += `최종 크뎀: ${finalCdmgVal}%`;
    }

    // 확정치명타 옵션 체크 시 처리 (크확 1000으로 고정, 툴팁 강제 수정)
    if (ctx.chkGuaranteedCrit) {
        finalCritRate = 1000;
        critTip = "특성/스킬에 의해 크리티컬 확률이 확정(100% 이상)으로 고정되었습니다.\n(적 크리티컬 저항 무시)";
    }

    var effectiveCritRate = finalCritRate - ctx.bossCritResist;
    var critRateEv = Math.max(0, Math.min(effectiveCritRate, 100)) / 100;
    var evCdmgMult = (critRateEv * finalCdmgVal + (1 - critRateEv) * 100) / 100;
    var avgStabMult = (100 + finalStab) / 200;

    var targetDef = isMag ? ctx.bossMdef : ctx.bossDef;
    var targetPierce = isMag ? ctx.magPierce : ctx.physPierce;
    var targetResist = isMag ? ctx.bossMagResist : ctx.bossPhysResist;
    var effectiveDef = Math.floor(targetDef * (1 - (targetPierce / 100)));
    if (effectiveDef < 0) effectiveDef = 0;
    
    var finalSkillMult = ctx.skillMult;
    var finalSkillConst = ctx.skillConst;

    if (ctx.skillStats) {
        for (var i = 0; i < ctx.skillStats.length; i++) {
            var ss = ctx.skillStats[i];
            var statVal = 0;
            switch(ss.stat) {
                case 'STR': statVal = ctx.strBase; break;
                case 'INT': statVal = ctx.intBase; break;
                case 'VIT': statVal = ctx.vitBase; break;
                case 'AGI': statVal = ctx.agiBase; break;
                case 'DEX': statVal = ctx.dexBase; break;
                case 'totalSTR': statVal = totalSTR; break;
                case 'totalINT': statVal = totalINT; break;
                case 'totalVIT': statVal = totalVIT; break;
                case 'totalAGI': statVal = totalAGI; break;
                case 'totalDEX': statVal = totalDEX; break;
            }
            if (ss.target === 'mult') {
                finalSkillMult += (statVal * ss.ratio);
            } else if (ss.target === 'const') {
                finalSkillConst += (statVal * ss.ratio);
            }
        }
    }


            var baseAtkRaw = isMag ? finalMATK : finalATK;
            var lvDiff = ctx.level - ctx.bossLevel;

            var rawAtkBase = baseAtkRaw + lvDiff + finalSkillConst - effectiveDef;
            var isPierced = (rawAtkBase > 0);
            if(rawAtkBase < 1) rawAtkBase = 1;

            var rangeDmgPct = (ctx.rangeType === 'SHORT') ? ctx.srw : ctx.lrw;
            var rangeMult = 1 + (rangeDmgPct / 100);
            var unsheatheMult = ctx.chkIsUnsheathe ? (1 + ctx.unsheathe / 100) : 1;
            var resistMult = 1 - (targetResist / 100);
            var elemMult = 1 + (ctx.elemP / 100);
            var activeBuffDamageMult = 1 + (ctx.damageP / 100);

            var damageFactor = rawAtkBase * finalSkillMult * evCdmgMult * rangeMult * unsheatheMult * elemMult * activeBuffDamageMult * resistMult * avgStabMult;

            var extraAtkTip = isDualSword ? `\n\n[듀얼소드 합산]\n메인 + (서브ATK * 서브안정률)\n(서브 무기 ATK: ${finalSubAtk} / 서브 안정률: ${finalSubStab}%)` : '';

            return { 
                ctx: ctx, isPierced: isPierced, rawAtkBase: rawAtkBase,
                finalSTR: totalSTR, finalINT: totalINT, finalAGI: totalAGI, finalDEX: totalDEX, finalVIT: totalVIT,
                finalATK: finalATK, finalMATK: finalMATK, finalCDMG: finalCdmgVal, finalCrit: ctx.chkGuaranteedCrit ? "확정치명타" : finalCritRate,
                finalASPD: finalASPD, finalCSPD: finalCSPD, finalStab: finalStab, finalMaxMP: finalMaxMP,
                finalWeaponAttack: baseWpnAtk,
                finalSubAtk: finalSubAtk,    // 서브ATK 추가
                finalSubStab: finalSubStab,  // 서브안정률 추가
                isDualSword: isDualSword,    // 듀얼소드 여부 추가
                damageFactor: damageFactor,

                tooltips: {
                    atkTip: `무기ATK(${baseWpnAtk}) + 스탯ATK(${statAtk}) + 레벨(${ctx.level}) ${statAtkUp > 0 ? '+스탯ATK업(' + statAtkUp + ')' : ''} = ${preFinalAtk}\n최종비율/고정: +${ctx.atkP}%, +${ctx.atkF}`,
                    matkTip: `무기ATK(${wpnMatkContrib}) + 스탯MATK(${statMatk}) + 레벨(${ctx.level}) ${(conversionAddMatk || 0) > 0 ? '+컨버전(' + conversionAddMatk + ')' : ''} ${statMatkUp > 0 ? '+스탯MATK업(' + statMatkUp + ')' : ''} = ${preFinalMatk}\n최종비율/고정: +${ctx.matkP}%, +${ctx.matkF}`,
                    motionTip: `ASPD보정(+${Math.min(50, aspdMotionBonus)}%) + 장비/크리스타(+${ctx.motionSpeed}%) = +${finalMotionSpeed}%`, // 👈 여기에 쉼표(,) 추가!!!
                    aspdTip: `기초(${baseASPDConst}) + 스탯ASP(${Math.floor(statAspd)}) + 레벨(${ctx.level}) = ${preAspd}\n비율/고정: +${ctx.aspdP + armorAspdP}%, +${ctx.aspdF}`,
                    cspdTip: `레벨(${ctx.level}) + AGI보정(${Math.floor(1.16*totalAGI)}) + DEX보정(${Math.floor(2.94*totalDEX)}) = ${preCspd}\n비율/고정: +${ctx.cspdP}%, +${ctx.cspdF}`,
                    critTip: critTip,
                    cdmgTip: cdmgTip, 
                    elemTip: elemTipText
                }
            };
        }

// 실시간 경고창 제어 및 검사 함수
