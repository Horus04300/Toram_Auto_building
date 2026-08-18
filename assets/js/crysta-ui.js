        var bannedCrystas = {"오로로 콜론": true};

        var subWeaponRules = {
            '한손검': ['없음', '방패', '단검', '화살', '마도구', '권갑', '인술 두루마리', '한손검(듀얼소드)'],
            '양손검': ['없음'],
            '활': ['없음', '화살', '발도검'],
            '자동활': ['없음', '방패', '단검', '화살', '마도구', '권갑'],
            '지팡이': ['없음', '방패', '단검', '화살', '마도구', '권갑', '인술 두루마리'],
            '마도구': ['없음', '인술 두루마리'],
            '권갑': ['없음', '방패', '단검', '화살', '마도구'],
            '선풍창': ['없음', '화살', '단검'],
            '발도검': ['없음', '단검', '인술 두루마리']
        };

        const tagMap = {
            "MaxHP": "최대HP", "MaxHPP": "최대HP%", "MaxMP": "최대MP", 
            "ATK": "ATK", "ATKP": "ATK%", "MATK": "MATK", "MATKP": "MATK%", 
            "SRW": "근거리위력%", "LRW": "원거리위력%", "PHYS_PIERCE": "물리관통%", "MAG_PIERCE": "마법관통%", 
            "CRIT": "크리티컬률", "CRITP": "크리티컬률%", "CDMG": "크리티컬데미지", "CDMGP": "크리티컬데미지%", 
            "ASPD": "ASPD", "ASPD_P": "ASPD%", "CSPD": "CSPD", "CSPD_P": "CSPD%", 
            "STABILITY": "안정률%", "UNSHEATHE": "발도공격", "UNSHEATHEP": "발도공격%", 
            "AGGRO": "어그로%", "PHYS_RES": "물리내성%", "MAG_RES": "마법내성%", "AILMENT_RES": "이상내성%", 
            "ANTICIPATE": "예측%", "GUARD_RECHARGE": "Guard회복%", "GUARD_POWER": "Guard력%", 
            "AVOID_RECHARGE": "Avoid회복%", "FRAC_BARR": "비율배리어%", "AMPR": "공격MP회복", 
            "AMPRP": "공격MP회복%", "MOTIONSPEED": "행동속도%", "STR": "STR", "STRP": "STR%", 
            "INT": "INT", "INTP": "INT%", "VIT": "VIT", "VITP": "VIT%", 
            "AGI": "AGI", "AGIP": "AGI%", "DEX": "DEX", "DEXP": "DEX%",
            "ELEM_P": "속성데미지%", "WATKP": "무기ATK%", "WATK": "무기ATK+",
            // --- 누락된 태그 추가 ---
            "FIRE_RES": "불내성%", "WATER_RES": "물내성%", "WIND_RES": "바람내성%", "EARTH_RES": "땅내성%", 
            "LIGHT_RES": "빛내성%", "DARK_RES": "어둠내성%", "NEUTRAL_RES": "무내성%",
            "MP_REGENP": "MP자연회복%", "MP_REGEN": "MP자연회복", "HP_REGENP": "HP자연회복%", "HP_REGEN": "HP자연회복",
            "ITEM_CD": "아이템쿨타임", "FIRE_DMG": "불속성대미지%", "WATER_DMG": "물속성대미지%", "WIND_DMG": "바람속성대미지%", 
            "EARTH_DMG": "땅속성대미지%", "LIGHT_DMG": "빛속성대미지%", "DARK_DMG": "어둠속성대미지%", "NEUTRAL_DMG": "무속성대미지%",
            "REFLECT": "반사대미지%", "BULLET_RES": "탄환경감%", "AOE_RES": "장판경감%", "AROUND_RES": "주위경감%", 
            "AREA_RES": "범위경감%", "FLOOR_RES": "지면경감%", "CHARGE_RED": "돌진경감%", "LINE_RED": "직선경감%", 
            "REVIVE_TIME": "부활시간%", "EXP": "획득EXP%", "DROP_RATE": "드랍률%", "ABS_DODGE": "절대회피%", 
            "ABS_ACC": "절대명중%", "PHYS_BARR": "물리배리어", "MAG_BARR": "마법배리어", "BARR_SPEED": "배리어속도%", 
            "PHYS_PURSUIT": "물리추격%", "MAG_PURSUIT": "마법추격%", "FLEE": "회피", "FLEEP": "회피%", 
            "ACC": "명중", "ACCP": "명중%", "DEF": "DEF", "DEFP": "DEF%", "MDEF": "MDEF", "MDEFP": "MDEF%",
            "GUARD_BREAK": "방어무너뜨리기%", "AVOID_RATE": "Avoid율%"
        };
// 태그명을 분석해 그룹을 반환하는 함수
        function getStatCategory(key) {
            var k = key.toUpperCase();
            if (k.includes('MP') || k.includes('SPD') || k.includes('MOTION') || k.includes('AGI') || k.includes('AMPR') || k.includes('REGEN') || k.includes('EXP') || k.includes('DROP') || k.includes('REVIVE') || k.includes('ITEM') || k.includes('AGGRO') || k.includes('ANTICIPATE')) {
                return '⚡ 유틸리티 (속도/MP/기타)';
            }
            if (k.includes('HP') || k.includes('VIT') || k.includes('DEF') || k.includes('RES') || k.includes('DODGE') || k.includes('FLEE') || k.includes('GUARD') || k.includes('BARR') || k.includes('RED') || k.includes('AVOID')) {
                return '🛡️ 방어 관련';
            }
            return '⚔️ 공격 관련';
        }

        // 스탯 객체를 그룹화된 HTML로 변환해주는 함수
        function buildGroupedTagsHtml(statsObj) {
            var groups = { '⚔️ 공격 관련': [], '🛡️ 방어 관련': [], '⚡ 유틸리티 (속도/MP/기타)': [] };
            for (var k in statsObj) {
                var v = statsObj[k];
                if (v === 0) continue;
                var cat = getStatCategory(k);
                var cssClass = v < 0 ? "stat-tag negative" : "stat-tag";
                var sign = v > 0 ? "+" : "";
                var dName = tagMap[k] || k;
                groups[cat].push('<span class="' + cssClass + '">' + dName + ' ' + sign + v + '</span>');
            }
            
            var html = '<div style="display:block; width:100%;">';
            for (var g in groups) {
                if (groups[g].length > 0) {
                    html += '<div style="margin-top:10px; margin-bottom:5px; font-size:13px; color:#2c3e50; font-weight:bold; border-bottom:1px dashed #d5dbdb; padding-bottom:3px;">[' + g + ']</div>';
                    html += '<div style="display:flex; flex-wrap:wrap; gap:5px; margin-bottom:8px;">' + groups[g].join('') + '</div>';
                }
            }
            html += '</div>';
            return html;
        }
        const BASE_ASPD_MAP = {
            "한손검": 100, "양손검": 50, "활": 75, "자동활": 30, "지팡이": 60,
            "마도구": 90, "권갑": 120, "선풍창": 25, "발도검": 200, "맨손": 1000
        };

        function getCategoryGroup(catStr) {
            if(!catStr) return '노말';
            if(catStr.indexOf('무기') !== -1) return '무기';
            if(catStr.indexOf('방어') !== -1 || catStr.indexOf('몸') !== -1) return '방어구';
            if(catStr.indexOf('추가') !== -1) return '추가';
            if(catStr.indexOf('특수') !== -1) return '특수';
            return '노말';
        }

        function populateRefineSelects() {
            var selects = document.querySelectorAll('.refine-select');
            var options = '<option value="15" selected>+S (15)</option><option value="14">+A (14)</option><option value="13">+B (13)</option><option value="12">+C (12)</option><option value="11">+D (11)</option><option value="10">+E (10)</option>';
            for(var i=9; i>=1; i--) options += '<option value="' + i + '">+' + i + '</option>';
            options += '<option value="0">+0</option>';
            for(var i=0; i<selects.length; i++) {
                var cur = selects[i].value;
                selects[i].innerHTML = options;
                if(cur) selects[i].value = cur;
            }
        }

        function updateSubWeaponList() {
            var mainWpn = document.getElementById('mainWeaponType').value;
            var subSelect = document.getElementById('subWeaponType');
            subSelect.innerHTML = '';
            
            var allowedSubs = subWeaponRules[mainWpn] || ['없음'];
            for(var i=0; i<allowedSubs.length; i++) {
                var opt = document.createElement('option');
                opt.value = allowedSubs[i];
                opt.textContent = allowedSubs[i];
                subSelect.appendChild(opt);
            }
            onSubWeaponChange();
        }

        function onSubWeaponChange() {
            var sub = document.getElementById('subWeaponType').value;
            var isMD = (sub === '마도구');
            
            // 피드백 1: 마도구 서브 장비일 때만 마법전사, 컨버전, 듀얼 브링거 표시
            var wrapMagic = document.getElementById('wrapMagicWarrior');
            var wrapConv = document.getElementById('wrapConversion');
            var wrapDual = document.getElementById('wrapDualBringer');
            
            if(wrapMagic) wrapMagic.style.display = isMD ? 'flex' : 'none';
            if(wrapConv) wrapConv.style.display = isMD ? 'flex' : 'none';
            if(wrapDual) wrapDual.style.display = isMD ? 'flex' : 'none';

            if(!isMD) {
                document.getElementById('chkMagicWarrior').checked = false;
                document.getElementById('chkConversion').checked = false;
                document.getElementById('chkDualBringer').checked = false;
            }

            refreshAllCrystaInfo();
        }

        function refreshAllCrystaInfo() {
            var selects = document.querySelectorAll('.cr-select');
            for(var i=0; i<selects.length; i++) {
                renderCrystaInfo(selects[i]);
            }
        }

        function checkCondition(ctx, cnd) {
            if(!cnd) return true;
            if(cnd.sub) {
                var subs = cnd.sub.split('/');
                if(subs.indexOf(ctx.subType) === -1) return false;
            }
            if(cnd.armor) {
                var armors = cnd.armor.split('/');
                if(armors.indexOf(ctx.armorType) === -1) return false;
            }
            if(cnd.main) {
                var mains = cnd.main.split('/');
                if(mains.indexOf(ctx.mainType) === -1) return false;
            }
            return true;
        }

        function renderCrystaInfo(inputEl) {
            var val = inputEl.value.trim();
            var infoDiv = document.getElementById(inputEl.id + "_info");
            if(!infoDiv) return;
            
            if(!val) { infoDiv.innerHTML = ""; return; }
            var c = null;
            for(var i=0; i<crystaDataJson.length; i++) {
                if(crystaDataJson[i].name === val) { c = crystaDataJson[i]; break; }
            }
            if(!c) { infoDiv.innerHTML = ""; return; } // 입력중에는 아무것도 띄우지 않음
            
            var ctx = {
                mainType: document.getElementById('mainWeaponType').value,
                subType: document.getElementById('subWeaponType').value,
                armorType: document.getElementById('armorType').value
            };

            var html = "";
            var isRootActive = checkCondition(ctx, c.cond);

            if(c.stats) {
                for(var k in c.stats) {
                    var v = c.stats[k];
                    var cssClass = v < 0 ? "stat-tag negative" : "stat-tag";
                    if (!isRootActive) cssClass += " disabled";
                    var sign = v > 0 ? "+" : "";
                    var displayKey = tagMap[k] || k;
                    html += '<span class="' + cssClass + '">' + displayKey + ' ' + sign + v + '</span>';
                }
            }
            
            if(c.cond && !isRootActive) {
                html = '<span style="font-size:12px; color:#c0392b; margin-right:5px; align-self:center;">(조건불만족)</span>' + html;
            }

            if (c.condStats) {
                for (var i = 0; i < c.condStats.length; i++) {
                    var cItem = c.condStats[i];
                    if (checkCondition(ctx, cItem.cond)) {
                        for(var k in cItem.stats) {
                            var v = cItem.stats[k];
                            var cssClass = v < 0 ? "stat-tag negative" : "stat-tag";
                            var sign = v > 0 ? "+" : "";
                            var displayKey = tagMap[k] || k;
                            html += '<span class="' + cssClass + '">' + displayKey + ' ' + sign + v + '</span>';
                        }
                    }
                }
            }

            infoDiv.innerHTML = html;
        }

        function addOptionRow(containerId) {
            var container = document.getElementById(containerId);
            var row = document.createElement('div');
            row.className = 'opt-row';
            row.innerHTML = '<select style="flex:2;" class="opt-type">' +
                '<option value="ATKP">ATK %</option><option value="ATK">ATK (+)</option>' +
                '<option value="MATKP">MATK %</option><option value="MATK">MATK (+)</option>' +
                '<option value="STRP">STR %</option><option value="STR">STR (+)</option>' +
                '<option value="DEXP">DEX %</option><option value="DEX">DEX (+)</option>' +
                '<option value="AGIP">AGI %</option><option value="AGI">AGI (+)</option>' +
                '<option value="INTP">INT %</option><option value="INT">INT (+)</option>' +
                '<option value="CDMG_P">크리티컬데미지 (%)</option><option value="CDMG">크리티컬데미지 (+)</option>' +
                '<option value="CRIT_P">크리티컬확률 (%)</option><option value="CRIT">크리티컬확률 (+)</option>' +
                '<option value="SRW">근거리위력 (%)</option><option value="LRW">원거리위력 (%)</option>' +
                '<option value="UNSHEATHE">발도위력 (%)</option>' +
                '<option value="PHYS_PIERCE">물리관통 (%)</option><option value="MAG_PIERCE">마법관통 (%)</option>' +
                '<option value="ELEM_P">속성데미지 (%)</option>' +
                '<option value="WATKP">무기ATK (%)</option><option value="WATK">무기ATK (+)</option>' +
                '<option value="ASPD">ASPD (+)</option><option value="ASPD_P">ASPD (%)</option>' +
                '<option value="CSPD">CSPD (+)</option><option value="CSPD_P">CSPD (%)</option>' +
                '<option value="STABILITY">안정률 (%)</option>' +
                '<option value="ATK_UP_STR">ATK업 (STR %)</option>' +
                '<option value="ATK_UP_DEX">ATK업 (DEX %)</option>' +
                '<option value="ATK_UP_INT">ATK업 (INT %)</option>' +
                '<option value="ATK_UP_AGI">ATK업 (AGI %)</option>' +
                '<option value="ATK_UP_VIT">ATK업 (VIT %)</option>' +
                '<option value="MATK_UP_STR">MATK업 (STR %)</option>' +
                '<option value="MATK_UP_DEX">MATK업 (DEX %)</option>' +
                '<option value="MATK_UP_INT">MATK업 (INT %)</option>' +
                '<option value="MATK_UP_AGI">MATK업 (AGI %)</option>' +
                '<option value="MATK_UP_VIT">MATK업 (VIT %)</option>' +
                '<option value="MOTIONSPEED">행동속도 (%)</option>' +
                '</select>' +
                '<input type="number" style="flex:1;" class="opt-val" value="0">' +
                '<button type="button" class="remove-option-row" style="cursor:pointer; color:#e74c3c; border:none; background:none; font-weight:bold;">✕</button>';
            row.querySelector('.remove-option-row').addEventListener('click', function () { row.remove(); });
            container.appendChild(row);
        }

        document.getElementById('banInput').addEventListener('keypress', function(e) { 
            if(e.key === 'Enter') { e.preventDefault(); addBanTag(); } 
        });
        
        function addBanTag() {
            var val = document.getElementById('banInput').value.trim();
            if(val && !bannedCrystas[val]) { 
                bannedCrystas[val] = true;
                document.getElementById('banInput').value = ''; 
                renderBanTags(); 
            }
        }
        function removeBanTag(val) { delete bannedCrystas[val]; renderBanTags(); }
        function renderBanTags() {
            var container = document.getElementById('banTagContainer');
            container.innerHTML = '';
            for (var val in bannedCrystas) {
                var tag = document.createElement('span');
                tag.className = 'ban-tag';
                tag.appendChild(document.createTextNode(val + ' '));
                var removeButton = document.createElement('button');
                removeButton.type = 'button';
                removeButton.className = 'remove-ban-tag';
                removeButton.textContent = '✕';
                removeButton.addEventListener('click', (function (value) {
                    return function () { removeBanTag(value); };
                }(val)));
                container.appendChild(tag);
            }
        }


// 무기 및 방어구 기본 옵션 3종 자동 세팅 함수
function addDefaultOptions(containerId) {
    // 추가할 옵션의 value 값: CRIT(크확+), CDMG(크뎀+), CDMG_P(크뎀%)
    var defaultOpts = ['CRIT', 'CDMG', 'CDMG_P']; 
    
    for (var i = 0; i < defaultOpts.length; i++) {
        addOptionRow(containerId); // 1. 기존 함수로 빈 행 추가
        
        var container = document.getElementById(containerId);
        var rows = container.querySelectorAll('.opt-row');
        var lastRow = rows[rows.length - 1]; // 방금 추가된 마지막 행 선택
        
        // 2. 생성된 행의 select 값을 기본 옵션으로 변경
        lastRow.querySelector('.opt-type').value = defaultOpts[i]; 
        // 3. 입력칸의 기본값을 0으로 설정 (필요 시 다른 숫자로 변경 가능)
        lastRow.querySelector('.opt-val').value = 0; 
    }
}



// 1. 문자열 내 모든 공백 제거 및 소문자화 (매칭 오류 방지)
function normCrystaName(s) {
    return s ? String(s).trim().replace(/\s+/g, '').toLowerCase() : '';
}

// 2. 전체 크리스타 고속 캐시 맵 & 검색 함수
var crystaMapCache = null;
function getCrystaByName(name) {
    if (!name) return null;
    var targetKey = normCrystaName(name);
    if (!targetKey) return null;

    // 캐시 맵 생성 (최초 1회)
    if (!crystaMapCache && typeof crystaDataJson !== 'undefined' && Array.isArray(crystaDataJson)) {
        crystaMapCache = {};
        for (var i = 0; i < crystaDataJson.length; i++) {
            var c = crystaDataJson[i];
            if (c && c.name) {
                crystaMapCache[normCrystaName(c.name)] = c;
            }
        }
    }

    if (crystaMapCache && crystaMapCache[targetKey]) {
        return crystaMapCache[targetKey];
    }
    return null;
}

// 3. 동일 및 상/하위(업그레이드) 관계 완벽 검사 함수
function isCrystaConflict(c1, c2) {
    if (!c1 || !c2) return false;

    var key1 = normCrystaName(c1.name);
    var key2 = normCrystaName(c2.name);

    if (!key1 || !key2) return false;
    if (key1 === key2) return true; // 1. 완전히 동일한 크리스타

    // 2. c1의 하위(prev) 트리를 끝까지 추적하여 c2가 존재하는지 검사
    var curr = c1;
    var visited = {};
    while (curr && curr.prev) {
        var pKey = normCrystaName(curr.prev);
        if (!pKey) break;
        if (pKey === key2) return true; // c2가 c1의 상위/하위 족보에 있음
        if (visited[pKey]) break; // 무한 루프 방지
        visited[pKey] = true;
        curr = getCrystaByName(pKey);
    }

    // 3. c2의 하위(prev) 트리를 끝까지 추적하여 c1이 존재하는지 검사
    curr = c2;
    visited = {};
    while (curr && curr.prev) {
        var pKey = normCrystaName(curr.prev);
        if (!pKey) break;
        if (pKey === key1) return true; // c1이 c2의 상위/하위 족보에 있음
        if (visited[pKey]) break;
        visited[pKey] = true;
        curr = getCrystaByName(pKey);
    }

    return false;
}

// --- 새로 추가할 즉시 검사 로직 ---
var prevCrystaSelections = {};

function instantCrystaCheck(inp, newValue) {
    if (!newValue) {
        prevCrystaSelections[inp.id] = "";
        inp.value = "";
        renderCrystaInfo(inp);
        return true;
    }

    // 반대쪽 슬롯 찾기 (ex: cr_wpn_1 이면 cr_wpn_2)
    var group = inp.id.substring(0, inp.id.length - 1);
    var slotNum = inp.id.slice(-1);
    var counterpartId = group + (slotNum === "1" ? "2" : "1");
    var counterpartVal = document.getElementById(counterpartId).value;

    var c1 = getCrystaByName(newValue);
    var c2 = counterpartVal ? getCrystaByName(counterpartVal) : null;

    // 중복 체크 및 팝업 (Alert)
    if (c1 && c2 && isCrystaConflict(c1, c2)) {
        alert("⚠️ 크리스타 장착 오류!\n같은 부위(무기, 방어구, 추가, 특수) 내에서는 상/하위 호환을 포함한 동일 계열의 크리스타를 중복 장착할 수 없습니다.");
        inp.value = prevCrystaSelections[inp.id] || ""; // 이전 값으로 롤백
        return false;
    }

    // 통과 시 값 저장 및 정보 렌더링
    prevCrystaSelections[inp.id] = newValue;
    inp.value = newValue;
    renderCrystaInfo(inp);
    return true;
}


// 스킬 계수/상수에 스탯 기반 보정을 추가하는 함수
        function addSkillStatRow() {
            var container = document.getElementById('skillStatOpts');
            var row = document.createElement('div');
            row.className = 'opt-row';
            row.innerHTML = '<select style="flex:1.2;" class="skill-target">' +
                '<option value="mult">계수(배율)에 추가</option>' +
                '<option value="const">상수에 추가</option>' +
                '</select>' +
                '<select style="flex:1;" class="skill-stat">' +
                '<option value="STR">순수 STR</option>' +
                '<option value="INT">순수 INT</option>' +
                '<option value="VIT">순수 VIT</option>' +
                '<option value="AGI">순수 AGI</option>' +
                '<option value="DEX">순수 DEX</option>' +
                '<option value="totalSTR">최종 STR</option>' +
                '<option value="totalINT">최종 INT</option>' +
                '<option value="totalVIT">최종 VIT</option>' +
                '<option value="totalAGI">최종 AGI</option>' +
                '<option value="totalDEX">최종 DEX</option>' +
                '</select>' +
                '<input type="number" step="any" style="flex:1;" class="skill-ratio" placeholder="비율 입력 (예: 0.01)">' +
                '<button type="button" class="remove-option-row" style="cursor:pointer; color:#e74c3c; border:none; background:none; font-weight:bold;">✕</button>';
            row.querySelector('.remove-option-row').addEventListener('click', function () { row.remove(); });
            container.appendChild(row);
        }


// HTML을 일일이 수정하지 않고 JS에서 자동으로 검색 래퍼를 생성해주는 함수
function wrapInputsForAutocomplete() {
    var inputs = document.querySelectorAll('.cr-select, #banInput');
    for (var i = 0; i < inputs.length; i++) {
        var inp = inputs[i];
        inp.removeAttribute('list'); // 기존 datalist 연결 해제
        inp.setAttribute('autocomplete', 'off');
        
        var wrapper = document.createElement('div');
        wrapper.className = 'autocomplete-wrapper';
        
        inp.parentNode.insertBefore(wrapper, inp);
        wrapper.appendChild(inp);
    }
}

// 커스텀 자동완성 및 검색 초기화 함수 (기존 populateCrystaSelects 대체)
function initAutocomplete() {
    wrapInputsForAutocomplete();

    var wpnList = [], armList = [], addList = [], spcList = [], allList = [];
    
    for (var i = 0; i < crystaDataJson.length; i++) {
        var c = crystaDataJson[i];
        if (!c || !c.name) continue;
        var grp = getCategoryGroup(c.category);
        
        allList.push(c.name);
        if (grp === '노말') {
            wpnList.push(c.name); armList.push(c.name); addList.push(c.name); spcList.push(c.name);
        } else if (grp === '무기') { wpnList.push(c.name); }
        else if (grp === '방어구') { armList.push(c.name); }
        else if (grp === '추가') { addList.push(c.name); }
        else if (grp === '특수') { spcList.push(c.name); }
    }

    setupAutocomplete(document.getElementById('cr_wpn_1'), wpnList);
    setupAutocomplete(document.getElementById('cr_wpn_2'), wpnList);
    setupAutocomplete(document.getElementById('cr_arm_1'), armList);
    setupAutocomplete(document.getElementById('cr_arm_2'), armList);
    setupAutocomplete(document.getElementById('cr_add_1'), addList);
    setupAutocomplete(document.getElementById('cr_add_2'), addList);
    setupAutocomplete(document.getElementById('cr_spc_1'), spcList);
    setupAutocomplete(document.getElementById('cr_spc_2'), spcList);
    setupAutocomplete(document.getElementById('banInput'), allList);
}

// 자동완성 핵심 엔진
function setupAutocomplete(inp, arr) {
    if (!inp) return;
    var currentFocus;

    // 1. 클릭 시에도 무조건 리스트 표출되도록 이벤트 적용
    inp.addEventListener("click", function(e) {
        triggerSearch(this.value);
    });

    // 2. 타이핑(검색) 시 실시간 필터링
    inp.addEventListener("input", function(e) {
        triggerSearch(this.value);
        if (inp.classList.contains('cr-select')) renderCrystaInfo(this);
    });

    function triggerSearch(val) {
        var a, b, i;
        closeAllLists(); // 기존에 열려있는 다른 리스트 모두 초기화
        currentFocus = -1;
        
        a = document.createElement("DIV");
        a.setAttribute("id", inp.id + "autocomplete-list");
        a.setAttribute("class", "autocomplete-items");
        inp.parentNode.appendChild(a);
        
        // 검색어에 맞는 항목만 생성 (검색어가 없으면 전체 리스트 생성)
        for (i = 0; i < arr.length; i++) {
            var matchIdx = arr[i].toUpperCase().indexOf(val.toUpperCase());
            if (!val || matchIdx > -1) {
                b = document.createElement("DIV");
                
                // 검색어 하이라이트 처리
                if (val && matchIdx > -1) {
                    b.innerHTML = arr[i].substring(0, matchIdx) + "<strong>" + arr[i].substring(matchIdx, matchIdx + val.length) + "</strong>" + arr[i].substring(matchIdx + val.length);
                } else {
                    b.innerHTML = arr[i];
                }
                b.innerHTML += "<input type='hidden' value='" + arr[i] + "'>";
                
                b.addEventListener("click", function(e) {
                    var selectedVal = this.getElementsByTagName("input")[0].value;
                    if (inp.classList.contains('cr-select')) {
                        instantCrystaCheck(inp, selectedVal); // 팝업 및 중복 검사 실행
                    } else {
                        inp.value = selectedVal;
                    }
                    closeAllLists();
                });
                a.appendChild(b);
            }
        }
    }

    // 키보드 방향키 및 엔터 조작 지원
    inp.addEventListener("keydown", function(e) {
        var x = document.getElementById(this.id + "autocomplete-list");
        if (x) x = x.getElementsByTagName("div");
        if (e.keyCode == 40) { // DOWN
            currentFocus++;
            addActive(x);
        } else if (e.keyCode == 38) { // UP
            currentFocus--;
            addActive(x);
        } else if (e.keyCode == 13) { // ENTER
            e.preventDefault();
            if (currentFocus > -1) {
                if (x) x[currentFocus].click();
            } else if (inp.id === 'banInput') {
                addBanTag(); 
                closeAllLists();
            } else if (inp.classList.contains('cr-select')) {
                instantCrystaCheck(inp, inp.value); // 직접 타이핑 후 엔터 쳤을 때 검사
                closeAllLists();
            }
        }
    });

    function addActive(x) {
        if (!x) return false;
        removeActive(x);
        if (currentFocus >= x.length) currentFocus = 0;
        if (currentFocus < 0) currentFocus = (x.length - 1);
        x[currentFocus].classList.add("autocomplete-active");
        x[currentFocus].scrollIntoView({ block: "nearest", behavior: "smooth" });
    }
    
    function removeActive(x) {
        for (var i = 0; i < x.length; i++) {
            x[i].classList.remove("autocomplete-active");
        }
    }
}

// ★ 다중 이벤트 충돌을 막기 위해 닫기 기능을 setupAutocomplete 함수 바깥으로 뺐습니다.
function closeAllLists(elmnt) {
    var x = document.getElementsByClassName("autocomplete-items");
    // HTMLCollection은 뒤에서부터 지워야 누락되지 않습니다.
    for (var i = x.length - 1; i >= 0; i--) {
        // 클릭된 요소가 해당 리스트의 입력창이 아닐 때만 삭제
        var inputOfThisList = x[i].previousElementSibling;
        if (elmnt !== x[i] && elmnt !== inputOfThisList) {
            x[i].parentNode.removeChild(x[i]);
        }
    }
}

// 바탕 화면 클릭 시 닫기
document.addEventListener("click", function (e) {
    closeAllLists(e.target);
});


window.ToramApp = window.ToramApp || {};
window.ToramApp.crystaUi = Object.freeze({
    addBanTag: addBanTag,
    addOptionRow: addOptionRow,
    addSkillStatRow: addSkillStatRow,
    onSubWeaponChange: onSubWeaponChange,
    refreshAllCrystaInfo: refreshAllCrystaInfo,
    updateSubWeaponList: updateSubWeaponList
});
