        function applyStat(ctx, key, val) {
            var policies = window.ToramCalculationPolicies;
            if (!policies || typeof policies.applyStat !== 'function') throw new Error('계산 정책이 준비되지 않았습니다.');
            return policies.applyStat(ctx, key, val);
        }


        function applyNormalAttackAmprModifier(value, modifier) {
            var result = Math.floor(Number(value) || 0);
            var percent = Number(modifier && modifier.percent) || 0;
            var multiplier = Number(modifier && modifier.multiplier);
            if (!Number.isFinite(multiplier)) multiplier = 1;
            if (percent) result = Math.floor(result * (100 + percent) / 100);
            if (multiplier !== 1) result = Math.floor(result * multiplier);
            result += Number(modifier && modifier.flat) || 0;
            return Math.floor(result);
        }
        function resolveNormalAttackAmpr(value, profile) {
            profile = profile || {};
            var beforePassive = Math.floor(Number(value) || 0);
            var afterPassive = (Array.isArray(profile.passive) ? profile.passive : []).reduce(function (current, modifier) {
                return applyNormalAttackAmprModifier(current, modifier);
            }, beforePassive);
            var candidates = (Array.isArray(profile.activeCandidates) ? profile.activeCandidates : []).map(function (modifier) {
                return Object.assign({}, modifier, { result:applyNormalAttackAmprModifier(afterPassive, modifier) });
            });
            var selected = candidates.reduce(function (best, candidate) {
                if (!best || candidate.result > best.result || (candidate.result === best.result && String(candidate.id) < String(best.id))) return candidate;
                return best;
            }, null);
            return {
                beforePassive:beforePassive,
                afterPassive:afterPassive,
                activeCandidates:candidates,
                selectedActive:selected,
                final:selected ? selected.result : afterPassive
            };
        }

        function calculateResistanceProfile(components) {
            var values = (Array.isArray(components) ? components : [components]).map(function(value) {
                value = Number(value);
                return Number.isFinite(value) ? value : 0;
            });
            var rawResistance = values.reduce(function(total, value) { return total + value; }, 0);
            var multiplier = Math.round((1 - rawResistance / 100) * 1e12) / 1e12;
            return { components:values, raw:rawResistance, effective:rawResistance, multiplier:multiplier };
        }
        function calculateEffectiveResistance(components) { return calculateResistanceProfile(components).effective; }
        function calculateProcDamageProfile(modifiers) {
            var sources = (Array.isArray(modifiers) ? modifiers : []).map(function(item) {
                var chancePercent = Math.min(100, Math.max(0, Number(item && item.chancePercent) || 0));
                var multiplier = Number(item && item.multiplier);
                if (!Number.isFinite(multiplier)) multiplier = 1;
                return { source:String(item && item.source || '확률 효과'), level:Math.max(0, Number(item && item.level) || 0), chancePercent:chancePercent, multiplier:multiplier, target:item && item.target || 'attack' };
            });
            return sources.reduce(function(result, item) {
                result.triggeredMultiplier *= item.multiplier;
                result.expectedMultiplier *= 1 + (item.chancePercent / 100) * (item.multiplier - 1);
                return result;
            }, { sources:sources, triggeredMultiplier:1, expectedMultiplier:1 });
        }
        function removeEmbeddedActiveGlobalDamage(ctx, appliedComboHit) {
            var embeddedPercent = Number(appliedComboHit && appliedComboHit.embeddedActiveGlobalDamagePercent) || 0;
            if (embeddedPercent) ctx.damageP = Math.round(((Number(ctx.damageP) || 0) - embeddedPercent + Number.EPSILON) * 1e6) / 1e6;
            return ctx;
        }


        function numericFlag(flags, key, fallback) {
            var value = Number(flags && flags[key]);
            return Number.isFinite(value) ? value : (fallback === undefined ? 0 : fallback);
        }
        function applyAttackProfileToContext(ctx, appliedComboHit) {
            var profile = appliedComboHit && appliedComboHit.hitProfile || null;
            var flags = Object.assign({}, profile && profile.flags || {});
            ctx.attackProfile = profile ? { damageType:profile.damageType, count:Number(profile.count) || 1, multiplier:Number(profile.multiplier) || 0, constant:Number(profile.constant) || 0, flags:flags } : null;
            ctx.optimizationBasisName = appliedComboHit && appliedComboHit.skillName || '평타';
            if (!profile) return ctx;
            ctx.atkType = profile.damageType === 'magic' ? 'MAG' : 'PHYS';
            if (flags.forceLongRange || flags.longRange) ctx.rangeType = 'LONG';
            else if (flags.forceShortRange || flags.shortRange) ctx.rangeType = 'SHORT';
            ctx.chkIsUnsheathe = Boolean(flags.unsheathe);
            ctx.chkGuaranteedCrit = Boolean(flags.guaranteedCritical);
            ctx.noCritical = Boolean(flags.noCritical || flags.nonCritical);
            ctx.criticalChanceBonus = numericFlag(flags, 'criticalChanceBonus') + numericFlag(flags, 'criticalBonus') - numericFlag(flags, 'criticalChancePenalty');
            ctx.criticalChanceMultiplier = numericFlag(flags, 'criticalChanceMultiplier', 1);
            ctx.fixedCriticalChance = Number.isFinite(Number(flags.fixedCriticalChance)) ? Number(flags.fixedCriticalChance) : null;
            ctx.minimumCriticalDamage = numericFlag(flags, 'minimumCriticalDamage');
            ctx.stabilityBonus = numericFlag(flags, 'stabilityBonus');
            ctx.physicalPierceSkillBonus = numericFlag(flags, 'physicalPierceBonus') - numericFlag(flags, 'physicalPiercePenalty');
            ctx.magicPierceSkillBonus = numericFlag(flags, 'magicPierceBonus');
            ctx.ignoreDefense = Boolean(flags.ignoreDefense);
            ctx.ignoreMdef = Boolean(flags.ignoreMdef);
            ctx.halfMdefIgnored = Boolean(flags.halfMdefIgnored);
            ctx.useHigherRangeDamage = Boolean(flags.shortOrLongRangeHigher || flags.useHigherRangeDamage);
            ctx.attackPowerMode = flags.usesAtkPlusMatk ? 'sum' : (flags.usesHigherAtkOrMatk ? 'higher' : (flags.usesAtkInsteadOfMatk ? 'atk' : (flags.wizardMatkBlend ? 'wizardBlend' : 'default')));
            ctx.attackElement = flags.element === undefined ? 'none' : String(flags.element);
            ctx.attackProfileDiagnostics = Object.keys(flags).filter(function (key) {
                return /When$/.test(key) && typeof flags[key] === 'string';
            });
            return ctx;
        }
        function skillInvestment(treeId, skillId) {
            var scoped = window.ToramCalculationInputScope && window.ToramCalculationInputScope.skillLevels;
            if (scoped) return Math.max(0, Number(scoped[treeId] && scoped[treeId][skillId]) || 0);
            var simulator = window.skillSimulatorState;
            var investments = simulator && typeof simulator.getInvestments === 'function' ? simulator.getInvestments() : {};
            return Math.max(0, Number(investments[treeId] && investments[treeId][skillId]) || 0);
        }
        function activeBuffIsEnabled(skillId) {
            var selections = window.ToramCalculationInputScope && window.ToramCalculationInputScope.activeBuffs ||
                (window.ToramActiveBuffs && typeof window.ToramActiveBuffs.getSelections === 'function' ? window.ToramActiveBuffs.getSelections() : {});
            var setting = selections[skillId];
            return setting === true || Boolean(setting && setting.active);
        }
        function getBaseContext() {
            var scopedInput = window.ToramCalculationInputScope && window.ToramCalculationInputScope.kernelInput;
            var controlValue = function (id) { var node = document.getElementById(id); return scopedInput && scopedInput.controls && scopedInput.controls[id] !== undefined ? scopedInput.controls[id] : (node ? node.value : ''); };
            var appliedComboHit = scopedInput && scopedInput.appliedComboHit !== undefined ? scopedInput.appliedComboHit :
                (window.ToramComboUi && typeof window.ToramComboUi.getAppliedHit === 'function' ? window.ToramComboUi.getAppliedHit() : null);
            var poisonSources = window.ToramSkillEffects && typeof window.ToramSkillEffects.learnedAilmentSources === 'function'
                ? window.ToramSkillEffects.learnedAilmentSources('poison') : [];
            var weakenSources = window.ToramSkillEffects && typeof window.ToramSkillEffects.learnedAilmentSources === 'function'
                ? window.ToramSkillEffects.learnedAilmentSources('weaken') : [];
            var ctx = {
                level: parseFloat(controlValue('charLevel')) || 0,
                strBase: parseFloat(controlValue('strBase')) || 0,
                intBase: parseFloat(controlValue('intBase')) || 0,
                vitBase: parseFloat(controlValue('vitBase')) || 0,
                agiBase: parseFloat(controlValue('agiBase')) || 0,
                dexBase: parseFloat(controlValue('dexBase')) || 0,
                crtBase: parseFloat(controlValue('crtBase')) || 0,

                atkType: appliedComboHit ? appliedComboHit.atkType : 'PHYS',
                rangeType: appliedComboHit ? appliedComboHit.rangeType : 'SHORT',
                mainType: controlValue('mainWeaponType'),
                wpnAtk: controlValue('mainWeaponType') === '맨손' ? 0 : (parseFloat(controlValue('wpnAtk')) || 0),
                wpnRefine: controlValue('mainWeaponType') === '맨손' ? 0 : (parseFloat(controlValue('wpnRefine')) || 0),
                wpnStab: controlValue('mainWeaponType') === '맨손' ? 1 : (parseFloat(controlValue('wpnStab')) || 80),
                subType: controlValue('subWeaponType'),
                subAtk: parseFloat(controlValue('subAtk')) || 0,
                subRefine: parseFloat(controlValue('subRefine')) || 0,
                subStab: parseFloat(controlValue('subStab')) || 0,
                armorType: controlValue('armorType'),

                bossLevel: parseFloat(controlValue('bossLevel')) || 0,
                bossDef: parseFloat(controlValue('bossDef')) || 0,
                bossMdef: parseFloat(controlValue('bossMdef')) || 0,
                bossCritResist: parseFloat(controlValue('bossCritResist')) || 0,
                bossPhysResist: parseFloat(controlValue('bossPhysResist')) || 0,
                bossMagResist: parseFloat(controlValue('bossMagResist')) || 0,
                skillMult: appliedComboHit ? appliedComboHit.skillMult : 1,
                damageMultiplierLayers: appliedComboHit && appliedComboHit.damageMultiplierLayers ? Object.assign({}, appliedComboHit.damageMultiplierLayers) : null,
                skillConst: appliedComboHit ? appliedComboHit.skillConst : 0,
                optimizationBasisName: appliedComboHit && appliedComboHit.skillName || '평타',
                appliedSkillId: appliedComboHit && appliedComboHit.skillId || '',
                attackProfile: null,
                procDamageModifiers: appliedComboHit && Array.isArray(appliedComboHit.procDamageModifiers) ? appliedComboHit.procDamageModifiers.map(function(item) { return Object.assign({}, item); }) : [],

                chkIsUnsheathe: Boolean(appliedComboHit && appliedComboHit.unsheathe),
                conversionLevel: skillInvestment('MagicBlade', 1),
                conversionActive: activeBuffIsEnabled('MagicBlade:1'),
                dualBringerLevel: skillInvestment('MagicBlade', 4),
                dualBringerActive: activeBuffIsEnabled('MagicBlade:4'),
                spellBurstLevel: skillInvestment('Battle', 12),
                godspeedWieldLevel: skillInvestment('Halberd', 19),
                maximizerLevel: skillInvestment('Magic', 20),
                poisonSources: poisonSources,
                weakenSources: weakenSources,
                targetWeakened: weakenSources.length > 0,
                chkGuaranteedCrit: Boolean(appliedComboHit && appliedComboHit.guaranteedCritical),

                strP: 0, strF: 0, dexP: 0, dexF: 0, intP: 0, intF: 0, agiP: 0, agiF: 0, vitP: 0, vitF: 0,
                atkP: 0, atkF: 0, matkP: 0, matkF: 0, cdmgP: 0, cdmgF: 0, 
                critP: 0, critF: 0, srw: 0, lrw: 0, unsheatheP: 0, unsheatheF: 0, elemP: 0, damageP: 0, watkP: 0, watkF: 0, baseWpnAtkF: 0,
                physPierce: 0, magPierce: 0, aspdF: 0, aspdP: 0, cspdF: 0, cspdP: 0, stability: 0, motionSpeed: 0, castRed: 0, maxMpF: 0, maxHpF: 0, maxHpP: 0, amprF: 0, amprP: 0,
                elementAwakening: false, magicElement: false,
                attackElement: 'none', attackProfileDiagnostics: [], attackPowerMode: 'default', useHigherRangeDamage: false,
                noCritical: false, criticalChanceBonus: 0, criticalChanceMultiplier: 1, fixedCriticalChance: null, minimumCriticalDamage: 0,
                stabilityBonus: 0, physicalPierceSkillBonus: 0, magicPierceSkillBonus: 0,
                ignoreDefense: false, ignoreMdef: false, halfMdefIgnored: false,
                atkUpSTR: 0, atkUpDEX: 0, atkUpINT: 0, atkUpAGI: 0, atkUpVIT: 0,
                matkUpSTR: 0, matkUpDEX: 0, matkUpINT: 0, matkUpAGI: 0, matkUpVIT: 0,
                preservedStats: {}, statDiagnostics: []
            };
            var optContainers = ['wpnOpts', 'subOpts', 'armOpts', 'addOpts', 'spcOpts', 'buffOpts'];
            applyAttackProfileToContext(ctx, appliedComboHit);
            if (scopedInput && Array.isArray(scopedInput.options)) {
                scopedInput.options.forEach(function (option) { applyStat(ctx, option.key, parseFloat(option.value) || 0); });
            } else {
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
            }
            // 스킬별 계수·상수는 콤보 탭에서 선택한 타격을 통해 주입한다.
            ctx.skillStats = [];
            var activeSelections = window.ToramCalculationInputScope && window.ToramCalculationInputScope.activeBuffs ||
                (window.ToramActiveBuffs && typeof window.ToramActiveBuffs.getSelections === 'function' ? window.ToramActiveBuffs.getSelections() : {});
            if (window.ToramSkillEffects && typeof window.ToramSkillEffects.activeStatChanges === 'function') {
                window.ToramSkillEffects.activeStatChanges(ctx, ctx, {}, { activeBuffs:activeSelections }).forEach(function (change) {
                    applyStat(ctx, change.key, change.value);
                });
            }
            removeEmbeddedActiveGlobalDamage(ctx, appliedComboHit);
            ctx.activeBuildConversions = window.ToramSkillEffects && typeof window.ToramSkillEffects.activeBuildConversions === 'function'
                ? window.ToramSkillEffects.activeBuildConversions(ctx, {}, {}, { activeBuffs:activeSelections }).map(function (effect) { return Object.assign({}, effect); })
                : [];
            ctx.normalAttackAmprProfile = window.ToramSkillEffects && typeof window.ToramSkillEffects.normalAttackAmprModifiers === 'function'
                ? window.ToramSkillEffects.normalAttackAmprModifiers(ctx, {}, {}, { activeBuffs:activeSelections })
                : { passive:[], activeCandidates:[] };

            return ctx;
        }
        function cloneContextValue(value) {
            if (value === null || value === undefined || typeof value !== 'object') return value;
            if (Array.isArray(value)) return value.map(cloneContextValue);
            var result = {};
            for (var key in value) result[key] = cloneContextValue(value[key]);
            return result;
        }
        function cloneCtx(baseCtx) {
            return cloneContextValue(baseCtx);
        }

        function applyPassiveSkillStats(ctx) {
            if (!window.ToramSkillEffects) return;
            window.ToramSkillEffects.passiveStatChanges(ctx).forEach(function (change) {
                applyStat(ctx, change.key, change.value);
            });
        }

        function applyActiveSkillStatConversions(ctx) {
            (Array.isArray(ctx.activeBuildConversions) ? ctx.activeBuildConversions : []).forEach(function (effect) {
                if (effect.conversion !== 'unsheatheToAtk') return;
                var rate = Number(effect.value) || 0;
                var unsheatheP = Number(ctx.unsheatheP) || 0;
                var unsheatheF = Number(ctx.unsheatheF) || 0;
                ctx.unsheatheP = 0;
                ctx.unsheatheF = 0;
                var convertedUnsheatheP = Math.floor(rate * unsheatheP);
                var convertedUnsheatheF = Math.floor(rate * unsheatheF);
                ctx.atkP += convertedUnsheatheP;
                ctx.baseWpnAtkF = (Number(ctx.baseWpnAtkF) || 0) + convertedUnsheatheP;
                ctx.atkF += convertedUnsheatheF;
            });
        }

        function simulateWithCrystas(baseCtx, crystas, snapshotOnly, summaryOnly) {
            var ctx = cloneCtx(baseCtx);
            var policies = window.ToramCalculationPolicies;
            if (!policies || typeof policies.matchesCrystaCondition !== 'function') throw new Error('크리스타 조건 정책이 준비되지 않았습니다.');
            var matchesCrystaCondition = policies.matchesCrystaCondition;
            var legacySelections = null;
            if ((!Array.isArray(ctx.activeBuildConversions) || !ctx.normalAttackAmprProfile) && !snapshotOnly && window.ToramActiveBuffs && typeof window.ToramActiveBuffs.getSelections === 'function') {
                legacySelections = window.ToramActiveBuffs.getSelections();
            }
            if (!Array.isArray(ctx.activeBuildConversions) && !snapshotOnly && window.ToramSkillEffects && typeof window.ToramSkillEffects.activeBuildConversions === 'function') {
                ctx.activeBuildConversions = window.ToramSkillEffects.activeBuildConversions(ctx, {}, {}, { activeBuffs:legacySelections || {} }).map(function (effect) { return Object.assign({}, effect); });
            }
            if (!ctx.normalAttackAmprProfile && !snapshotOnly && window.ToramSkillEffects && typeof window.ToramSkillEffects.normalAttackAmprModifiers === 'function') {
                ctx.normalAttackAmprProfile = window.ToramSkillEffects.normalAttackAmprModifiers(ctx, {}, {}, { activeBuffs:legacySelections || {} });
            }
            for(var i=0; i<crystas.length; i++) {
                var c = crystas[i];
                if(!c) continue;
                
                if(c.stats) {
                    if(!c.cond || matchesCrystaCondition(ctx, c.cond)) {
                        for(var key in c.stats) applyStat(ctx, key, parseFloat(c.stats[key]) || 0);
                    }
                }
                
                if (c.condStats) {
                    for(var k=0; k<c.condStats.length; k++) {
                        var cItem = c.condStats[k];
                        if (matchesCrystaCondition(ctx, cItem.cond)) {
                            for(var key in cItem.stats) applyStat(ctx, key, parseFloat(cItem.stats[key]) || 0);
                        }
                    }
                }
            }

            applyActiveSkillStatConversions(ctx);

            var totalSTR = Math.floor(ctx.strBase * (1 + ctx.strP/100) + ctx.strF);
            var totalDEX = Math.floor(ctx.dexBase * (1 + ctx.dexP/100) + ctx.dexF);
            var totalINT = Math.floor(ctx.intBase * (1 + ctx.intP/100) + ctx.intF);
            var totalAGI = Math.floor(ctx.agiBase * (1 + ctx.agiP/100) + ctx.agiF);
            var totalVIT = Math.floor(ctx.vitBase * (1 + ctx.vitP/100) + ctx.vitF);
            var finalMaxMP = Math.max(0, Math.floor(100 + Number(ctx.level) + totalINT * 0.1 + ctx.maxMpF));
            var finalMaxMPAfterBuff = finalMaxMP;
            var baseMaxHP = Math.floor((totalVIT + 22.41) * Number(ctx.level) / 3 + 93);
            var finalMaxHP = Math.min(99999, Math.max(0, Math.floor(baseMaxHP * (1 + ctx.maxHpP / 100)) + ctx.maxHpF));
            var baseAMPR = Math.floor(10 + finalMaxMP / 100);
            var equipmentAndBuffAMPR = Math.floor(baseAMPR * (100 + ctx.amprP) / 100) + ctx.amprF;
            var normalAttackAmpr = resolveNormalAttackAmpr(equipmentAndBuffAMPR, ctx.normalAttackAmprProfile);
            var amprBeforeDual = normalAttackAmpr.final;
            
            var statAtkUp = Math.floor(ctx.strBase * ctx.atkUpSTR / 100) +
                            Math.floor(ctx.dexBase * ctx.atkUpDEX / 100) +
                            Math.floor(ctx.intBase * ctx.atkUpINT / 100) +
                            Math.floor(ctx.agiBase * ctx.atkUpAGI / 100) +
                            Math.floor(ctx.vitBase * ctx.atkUpVIT / 100);

            var statMatkUp = Math.floor(ctx.strBase * ctx.matkUpSTR / 100) +
                            Math.floor(ctx.dexBase * ctx.matkUpDEX / 100) +
                            Math.floor(ctx.intBase * ctx.matkUpINT / 100) +
                            Math.floor(ctx.agiBase * ctx.matkUpAGI / 100) +
                            Math.floor(ctx.vitBase * ctx.matkUpVIT / 100);


            // 1. 최종 무기 공격력: 기본 무기 공격력 → 무기 ATK%·재련 → 무기 ATK(+)
            // 일진강풍의 발도공격% 변환은 이 첫 단계의 기본 무기 공격력에만 더한다.
            var effectiveBaseWpnAtk = Number(ctx.wpnAtk) + (Number(ctx.baseWpnAtkF) || 0);
            var mainWpnBase = effectiveBaseWpnAtk + Math.floor(effectiveBaseWpnAtk * ctx.watkP / 100) + ctx.watkF;
            var refineWpnBonus = Math.floor(effectiveBaseWpnAtk * Math.pow(ctx.wpnRefine, 2) / 100) + ctx.wpnRefine;
            var baseWpnAtk = mainWpnBase + refineWpnBonus;

            if (ctx.subType === '화살' && (ctx.mainType === '활' || ctx.mainType === '자동활')) {
                baseWpnAtk += Math.floor(ctx.subAtk);
            }

            var statAtk = 0;
            var statMatk = totalINT * 4 + totalDEX * 1; 
            var matkRatio = (ctx.mainType === '지팡이' || ctx.mainType === '마도구') ? 1.0 : 0.0;
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
            else if (m === '선풍창') { statAtk = Math.floor(totalSTR * 2.5) + Math.floor(totalAGI * 1.5); statMatk = totalINT*3 + totalDEX*1; }
            else if (m === '발도검') { statAtk = Math.floor(totalDEX * 2.5) + Math.floor(totalSTR * 1.5); statMatk = totalINT*3 + totalDEX*1; }
            else { statAtk = totalSTR*1; statMatk = totalINT*3 + totalDEX*1; }

            var conversionAddMatk = 0;
            var conversionIntMatk = 0;
            if (ctx.conversionLevel > 0 && ['한손검','양손검','자동활','권갑'].indexOf(ctx.mainType) >= 0) {
                conversionAddMatk = Math.floor(baseWpnAtk * Math.pow(ctx.conversionLevel, 2) / 100);
                if (ctx.mainType === '권갑') conversionAddMatk = Math.floor(conversionAddMatk / 2);
                else conversionIntMatk = Math.floor(totalINT * ctx.conversionLevel * .1);
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


            // 3. 무기별 MATK 반영률은 위 무기 분기에서 확정한다 (지팡이·마도구 100%, 권갑 50%).
            wpnMatkContrib = Math.floor(baseWpnAtk * matkRatio);

            // 4. 최종 물리 ATK 산출
            var preFinalAtk = baseWpnAtk + statAtk + Number(ctx.level) + statAtkUp;
            var finalATK = Math.floor(preFinalAtk * (1 + ctx.atkP / 100)) + ctx.atkF;

            // ---- 피드백 1: 듀얼소드(서브 한손검) 최종 ATK 및 서브 ATK 로직 추가 ----
            var finalSubAtk = 0;
            var finalSubStab = 0;
            var isDualSword = (ctx.mainType === '한손검' && ctx.subType === '한손검(듀얼소드)');
            var finalAMPR = amprBeforeDual * (isDualSword ? 2 : 1);
            
            if (isDualSword) {
                // 서브 무기 최종 공격력 (재련치 제곱을 200으로 나눔)
                var subWpnBase = Number(ctx.subAtk) + Math.floor(ctx.subAtk * ctx.watkP / 100) + Math.floor(ctx.subAtk * Math.pow(ctx.subRefine, 2) / 200) + Number(ctx.subRefine) + ctx.watkF;
                
                // 서브 스탯 공격력 (통상 듀얼소드 서브 스탯은 STR 1 + AGI 3)
                var subStatAtk = Math.floor((totalSTR * 1) + (totalAGI * 3));
                
                // 서브 ATK
                var preFinalSubAtk = subWpnBase + subStatAtk + ctx.level;
                finalSubAtk = Math.floor(preFinalSubAtk * (1 + ctx.atkP / 100)) + ctx.atkF;
                
                // 서브 안정률 (최대 100%)
                finalSubStab = Math.floor(ctx.subStab * 0.5) + Math.floor(totalSTR * 0.06) + Math.floor(totalAGI * 0.04) + ctx.stability;
                if (finalSubStab > 100) finalSubStab = 100;
                
                // 듀얼소드 최종 ATK 합산
                finalATK = finalATK + Math.floor(finalSubAtk * finalSubStab / 100);
            }
            // -------------------------------------------------------------


            // 최종 마법 MATK 산출 
            var preFinalMatk = wpnMatkContrib + statMatk + Number(ctx.level) + statMatkUp;
            var conversionFlatMatk = Math.floor(conversionAddMatk) + Math.floor(conversionIntMatk);
            var finalMATK = Math.floor(preFinalMatk * (1 + ctx.matkP / 100)) + ctx.matkF + conversionFlatMatk;
            
            
            var baseCDMG = (totalSTR >= totalAGI) ? 150 + Math.floor(totalSTR/5) : 150 + Math.floor((totalSTR+totalAGI)/10);
            var calcCDMG = Math.floor(baseCDMG * (1 + ctx.cdmgP/100)) + ctx.cdmgF;
            if (calcCDMG > 300) calcCDMG = 300 + Math.floor((calcCDMG - 300)/2);
            
            var baseCrit = 25 + Math.floor(ctx.crtBase / 3.4);
            var normalAttackCritRaw = Math.floor(baseCrit * (1 + ctx.critP/100)) + ctx.critF;
            var normalAttackCrit = normalAttackCritRaw - ctx.bossCritResist;
            var finalCrit = normalAttackCritRaw;
            var attackCritMultiplier = Number(ctx.criticalChanceMultiplier); if (!Number.isFinite(attackCritMultiplier)) attackCritMultiplier = 1;
            finalCrit = Math.floor((finalCrit + (Number(ctx.criticalChanceBonus) || 0)) * attackCritMultiplier);
            if (ctx.fixedCriticalChance !== null && ctx.fixedCriticalChance !== undefined && Number.isFinite(Number(ctx.fixedCriticalChance))) finalCrit = Number(ctx.fixedCriticalChance);
            if (Number(ctx.minimumCriticalDamage)) calcCDMG = Math.max(calcCDMG, Number(ctx.minimumCriticalDamage));
            
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
            var finalMotionSpeed = Math.min(50, aspdMotionFloor + (ctx.motionSpeed || 0));

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
            
            var physStab = ctx.wpnStab + ctx.stability + (Number(ctx.stabilityBonus) || 0) + Math.floor(statStab);
            if (ctx.subType === '화살' && (ctx.mainType === '활' || ctx.mainType === '자동활')) {
                physStab += ctx.subStab;
            }
            if(physStab > 100) physStab = 100;

// --- 1. 약점 속성 및 순수 기본 INT 기준 속성에 유리 보너스 계산 ---
    var hasElementAwakening = Boolean(ctx.elementAwakening);
    var hasMagicElement = Boolean(ctx.magicElement);
    var attacksWeakness = hasElementAwakening || ctx.attackElement === 'weakness';

    // 내부 엔진/외부 컨텍스트의 속성에 유리 안전 확보
    var baseElemDmg = 0;
    if (typeof tCtx !== 'undefined' && typeof tCtx.elemP !== 'undefined') {
        baseElemDmg = tCtx.elemP;
    } else if (typeof ctx !== 'undefined') {
        baseElemDmg = ctx.elemDmg || ctx.elemDmgP || ctx.elemP || 0;
    }

    var currentElemDmg = baseElemDmg;
    var elemTipText = `기본 장비 속성에 유리: +${baseElemDmg}%\n`;

    if (attacksWeakness) {
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
        var spellBurstReflect = 2.5 * (Number(ctx.spellBurstLevel) || 0);
        var weakenCriticalReflect = ctx.targetWeakened && (ctx.mainType === '지팡이' || ctx.mainType === '마도구' || attacksWeakness) ? 50 : 0;
        var magCritReflect = spellBurstReflect + weakenCriticalReflect;
        if (ctx.targetWeakened && ctx.dualBringerActive && ctx.subType === '마도구' && (totalSTR >= totalINT)) {
            magCritReflect += 2.5 * ctx.dualBringerLevel;
        }

        finalCritRate = Math.floor(finalCrit * (magCritReflect / 100));
        critTip += `마법 크리 반영률: ${magCritReflect}% (스펠 버스트 ${spellBurstReflect}%${weakenCriticalReflect ? ' + 쇠약 50%' : ''}, 최종: ${finalCritRate})`;
        
        var magCdmgReflect = 50 + spellBurstReflect;
        if (ctx.dualBringerActive && (totalINT > totalSTR)) {
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
    if (ctx.noCritical) {
        finalCritRate = 0;
        critTip = '선택한 공격은 크리티컬이 발생하지 않습니다.';
    }

    var effectiveCritRate = finalCritRate - ctx.bossCritResist;
    var critRateEv = Math.max(0, Math.min(effectiveCritRate, 100)) / 100;
    var evCdmgMult = (critRateEv * finalCdmgVal + (1 - critRateEv) * 100) / 100;
    var avgStabMult = (100 + finalStab) / 200;

    var targetDef = isMag ? ctx.bossMdef : ctx.bossDef;
    var targetPierce = isMag ? ctx.magPierce + (Number(ctx.magicPierceSkillBonus) || 0) : ctx.physPierce + (Number(ctx.physicalPierceSkillBonus) || 0);
    var targetResistanceComponents = [isMag ? ctx.bossMagResist : ctx.bossPhysResist];
    if (Array.isArray(ctx.additionalTargetResistances)) targetResistanceComponents = targetResistanceComponents.concat(ctx.additionalTargetResistances);
    var targetResistance = calculateResistanceProfile(targetResistanceComponents);
    var effectiveDef = Math.floor(targetDef * (1 - (targetPierce / 100)));
    if ((isMag && ctx.ignoreMdef) || (!isMag && ctx.ignoreDefense)) effectiveDef = 0;
    else if (isMag && ctx.halfMdefIgnored) effectiveDef = Math.floor(effectiveDef / 2);
    if (effectiveDef < 0) effectiveDef = 0;
    
    var damageMultiplierLayers = ctx.damageMultiplierLayers || {};
    var layeredSkillMultiplier = Number(damageMultiplierLayers.skill);
    var finalSkillMult = Number.isFinite(layeredSkillMultiplier) ? layeredSkillMultiplier : ctx.skillMult;
    var passiveDamageMult = Number(damageMultiplierLayers.passive); if (!Number.isFinite(passiveDamageMult)) passiveDamageMult = 1;
    var activeDamageLayerMult = Number(damageMultiplierLayers.active); if (!Number.isFinite(activeDamageLayerMult)) activeDamageLayerMult = 1;
    var comboDamageMult = Number(damageMultiplierLayers.combo); if (!Number.isFinite(comboDamageMult)) comboDamageMult = 1;
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
            if (ctx.attackPowerMode === 'sum') baseAtkRaw = finalATK + finalMATK;
            else if (ctx.attackPowerMode === 'higher') baseAtkRaw = Math.max(finalATK, finalMATK);
            else if (ctx.attackPowerMode === 'atk') baseAtkRaw = finalATK;
            else if (ctx.attackPowerMode === 'wizardBlend') baseAtkRaw = finalATK * .25 + finalMATK * .75;
            var lvDiff = ctx.level - ctx.bossLevel;

            // 원문 순서: (ATK+레벨 차)×내성 + 발도공격(+) + 상수 - 관통 후 방어력.
            var resistMult = targetResistance.multiplier;
            var rawAtkBase = Math.floor((baseAtkRaw + lvDiff) * resistMult);
            if (ctx.chkIsUnsheathe) rawAtkBase += Number(ctx.unsheatheF) || 0;
            rawAtkBase += finalSkillConst - effectiveDef;
            var isPierced = (rawAtkBase > 0);
            if(rawAtkBase < 1) rawAtkBase = 1;

            var rangeDmgPct = (ctx.rangeType === 'SHORT') ? ctx.srw : ctx.lrw;
            if (ctx.useHigherRangeDamage) rangeDmgPct = Math.max(ctx.srw, ctx.lrw);
            var rangeMult = 1 + (rangeDmgPct / 100);
            var unsheatheMult = ctx.chkIsUnsheathe ? (1 + ctx.unsheatheP / 100) : 1;
            var elemMult = 1 + (ctx.elemP / 100);
            var activeBuffDamageMult = 1 + (ctx.damageP / 100);

            // 원문에서 곱셈으로 표시된 각 단계는 단계마다 소수점을 버린다.
            var damageFactor = Math.floor(rawAtkBase * evCdmgMult);
            damageFactor = Math.floor(damageFactor * elemMult);
            damageFactor = Math.floor(damageFactor * finalSkillMult);
            damageFactor = Math.floor(damageFactor * unsheatheMult);
            damageFactor = Math.floor(damageFactor * avgStabMult);
            damageFactor = Math.floor(damageFactor * passiveDamageMult);
            damageFactor = Math.floor(damageFactor * rangeMult);
            damageFactor = Math.floor(damageFactor * activeDamageLayerMult);
            damageFactor = Math.floor(damageFactor * activeBuffDamageMult);
            damageFactor = Math.floor(damageFactor * comboDamageMult);
            var procDamage = calculateProcDamageProfile(ctx.procDamageModifiers);
            var procTriggeredDamageFactor = damageFactor * procDamage.triggeredMultiplier;
            var procExpectedDamageFactor = damageFactor * procDamage.expectedMultiplier;
            if (summaryOnly) return { ctx:{ statDiagnostics:ctx.statDiagnostics || [] }, finalMaxHP:finalMaxHP, finalMaxMP:finalMaxMP, amprBeforeDual:amprBeforeDual, normalAttackCrit:normalAttackCrit, finalASPD:finalASPD, optimizationDamageFactor:procExpectedDamageFactor };
            var poisonDefenseAverage = (Number(ctx.bossDef) + Number(ctx.bossMdef)) / 2;
            var poisonDefenseRatio = Number(ctx.bossLevel) > 0 ? Math.min(.5, poisonDefenseAverage / (Number(ctx.bossLevel) * 6)) : 0;
            var poisonResistanceAverage = (Number(ctx.bossPhysResist) + Number(ctx.bossMagResist)) / 2;
            var poisonDamageProfile = {
                available: Array.isArray(ctx.poisonSources) && ctx.poisonSources.length > 0,
                sources: Array.isArray(ctx.poisonSources) ? ctx.poisonSources.map(function (item) { return Object.assign({}, item); }) : [],
                defenseAverage: poisonDefenseAverage,
                defenseRatio: poisonDefenseRatio,
                resistanceAverage: poisonResistanceAverage,
                damage: null
            };
            if (poisonDamageProfile.available) poisonDamageProfile.damage = (totalDEX + (finalATK + finalMATK) * poisonDefenseRatio) * (1 - poisonResistanceAverage / 100);

            var extraAtkTip = isDualSword ? `\n\n[듀얼소드 합산]\n메인 + (서브ATK * 서브안정률)\n(서브 무기 ATK: ${finalSubAtk} / 서브 안정률: ${finalSubStab}%)` : '';

            return { 
                ctx: ctx, isPierced: isPierced, rawAtkBase: rawAtkBase,
                finalSTR: totalSTR, finalINT: totalINT, finalAGI: totalAGI, finalDEX: totalDEX, finalVIT: totalVIT,
                finalATK: finalATK, finalMATK: finalMATK, finalCDMG: finalCdmgVal, finalCrit: ctx.chkGuaranteedCrit ? "확정치명타" : finalCritRate,
                normalAttackCrit: normalAttackCrit,
                finalASPD: finalASPD, finalCSPD: finalCSPD, finalStab: finalStab,
                finalMaxHP: finalMaxHP, finalMaxMP: finalMaxMP, finalMaxMPAfterBuff: finalMaxMPAfterBuff,
                baseAMPR: baseAMPR, equipmentAndBuffAMPR: equipmentAndBuffAMPR,
                amprBeforeNormalAttackActive: normalAttackAmpr.afterPassive, normalAttackAmprActiveCandidates: normalAttackAmpr.activeCandidates, selectedNormalAttackAmprActive: normalAttackAmpr.selectedActive,
                amprBeforeDual: amprBeforeDual, finalAMPR: finalAMPR,
                finalMotionSpeed: finalMotionSpeed, finalCastReduction: totalCastRed,
                finalWeaponAttack: baseWpnAtk,
                finalSubAtk: finalSubAtk,    // 서브ATK 추가
                finalSubStab: finalSubStab,  // 서브안정률 추가
                isDualSword: isDualSword,    // 듀얼소드 여부 추가
                damageFactor: damageFactor,
                optimizationDamageFactor: procExpectedDamageFactor,
                procTriggeredDamageFactor: procTriggeredDamageFactor,
                procExpectedDamageFactor: procExpectedDamageFactor,
                procDamageProfile: procDamage,
                targetResistance: targetResistance,
                poisonDamageProfile: poisonDamageProfile,

                tooltips: {
                    atkTip: `무기ATK(${baseWpnAtk}) + 스탯ATK(${statAtk}) + 레벨(${ctx.level}) ${statAtkUp > 0 ? '+스탯ATK업(' + statAtkUp + ')' : ''} = ${preFinalAtk}\n최종비율/고정: +${ctx.atkP}%, +${ctx.atkF}`,
                    matkTip: `무기ATK(${wpnMatkContrib}) + 스탯MATK(${statMatk}) + 레벨(${ctx.level}) ${statMatkUp > 0 ? '+스탯MATK업(' + statMatkUp + ')' : ''} = ${preFinalMatk}\n최종비율/고정: +${ctx.matkP}%, +${ctx.matkF}${conversionFlatMatk > 0 ? ', 컨버전 MATK(+) +' + conversionFlatMatk : ''}`,
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

window.ToramCalculationKernel = Object.freeze({
    evaluateContext: function (baseContext, candidates, summaryOnly) { return simulateWithCrystas(baseContext, candidates || [], true, summaryOnly === true); },
    cloneContext: cloneCtx,
    applyStat: applyStat,
    resolveNormalAttackAmpr: resolveNormalAttackAmpr
});
