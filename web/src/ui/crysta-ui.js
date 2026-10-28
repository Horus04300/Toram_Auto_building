import {statRegistry} from '../calculation/stat-registry.js';
import {policies} from '../calculation/calculation-policies.js';
import {crystaCatalog} from '../data/crysta-data.js';
import {buildStore} from '../application/build-draft-store.js';
import {SUB_WEAPON_RULES} from '../application/equipment-object.mjs';
import {STAT_LABELS} from '../application/stat-labels.mjs';
export function createCrystaUi(document) {
const root=document.defaultView;
        var DEFAULT_BANNED_CRYSTAS = ["오로로 콜론"];

        var subWeaponRules = SUB_WEAPON_RULES;

        const tagMap = STAT_LABELS;
        function getCrystaStatLabel(key) {
            var definition = statRegistry && statRegistry.get(key);
            return (tagMap[key] || key) + (definition && definition.status === 'notModeled' ? ' (계산 미반영)' : '');
        }
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
                var dName = getCrystaStatLabel(k);
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

        function syncMainWeaponInputs() {
            var isBarehand = document.getElementById('mainWeaponType').value === '맨손';
            [
                { id:'wpnAtk', value:'0' },
                { id:'wpnRefine', value:'0' },
                { id:'wpnStab', value:'1' }
            ].forEach(function (setting) {
                var control = document.getElementById(setting.id);
                if (!control) return;
                if (isBarehand) {
                    if (!control.disabled) control.dataset.weaponValue = control.value;
                    control.value = setting.value;
                    control.disabled = true;
                } else {
                    if (control.disabled && control.dataset.weaponValue !== undefined) control.value = control.dataset.weaponValue;
                    delete control.dataset.weaponValue;
                    control.disabled = false;
                }
            });
        }
        function updateSubWeaponList() {
            syncMainWeaponInputs();
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
            refreshAllCrystaInfo();
        }

        function refreshAllCrystaInfo() {
            var selects = document.querySelectorAll('.cr-select');
            for(var i=0; i<selects.length; i++) {
                renderCrystaInfo(selects[i]);
            }
        }

        function matchesCrystaCondition(ctx, cnd) {
            if (!policies || typeof policies.matchesCrystaCondition !== 'function') throw new Error('크리스타 조건 정책이 준비되지 않았습니다.');
            return policies.matchesCrystaCondition(ctx, cnd);
        }

        function renderCrystaInfo(inputEl) {
            var val = inputEl.value.trim();
            var infoDiv = document.getElementById(inputEl.id + "_info");
            if(!infoDiv) return;

            if(!val) {
                inputEl.classList.remove('is-invalid');
                inputEl.removeAttribute('aria-invalid');
                infoDiv.classList.remove('is-error');
                infoDiv.innerHTML = "";
                return;
            }
            var c = crystaCatalog.resolve(val);
            if(!c) {
                inputEl.classList.add('is-invalid');
                inputEl.setAttribute('aria-invalid', 'true');
                infoDiv.classList.add('is-error');
                infoDiv.textContent = '목록에 없는 크리스타입니다. 이름을 확인해야 계산할 수 있습니다.';
                return;
            }
            inputEl.classList.remove('is-invalid'); inputEl.removeAttribute('aria-invalid');
            infoDiv.classList.remove('is-error');

            var ctx = {
                mainType: document.getElementById('mainWeaponType').value,
                subType: document.getElementById('subWeaponType').value,
                armorType: document.getElementById('armorType').value
            };

            var html = "";

            if(c.stats) {
                for(var k in c.stats) {
                    var v = c.stats[k];
                    var cssClass = v < 0 ? "stat-tag negative" : "stat-tag";
                    var sign = v > 0 ? "+" : "";
                    var displayKey = getCrystaStatLabel(k);
                    html += '<span class="' + cssClass + '">' + displayKey + ' ' + sign + v + '</span>';
                }
            }

            if (c.conditionalStats) {
                for (var i = 0; i < c.conditionalStats.length; i++) {
                    var cItem = c.conditionalStats[i];
                    if (matchesCrystaCondition(ctx, cItem.when)) {
                        for(var k in cItem.stats) {
                            var v = cItem.stats[k];
                            var cssClass = v < 0 ? "stat-tag negative" : "stat-tag";
                            var sign = v > 0 ? "+" : "";
                            var displayKey = getCrystaStatLabel(k);
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
                '<option value="VITP">VIT %</option><option value="VIT">VIT (+)</option>' +
                '<option value="CDMG_P">크리티컬데미지 (%)</option><option value="CDMG">크리티컬데미지 (+)</option>' +
                '<option value="CRIT_P">크리티컬확률 (%)</option><option value="CRIT">크리티컬확률 (+)</option>' +
                '<option value="SRW">근거리위력 (%)</option><option value="LRW">원거리위력 (%)</option>' +
                '<option value="UNSHEATHEP">발도위력 (%)</option><option value="UNSHEATHE">발도위력 (+)</option>' +
                '<option value="PHYS_PIERCE">물리관통 (%)</option><option value="MAG_PIERCE">마법관통 (%)</option>' +
                '<option value="ELEM_P">속성에 유리 (%)</option>' +
                '<option value="ELEM_AWAKENING">속성 각성</option><option value="MAGIC_ELEMENT">마력 속성</option>' +
                '<option value="WATKP">무기ATK (%)</option><option value="WATK">무기ATK (+)</option>' +
                '<option value="ASPD">ASPD (+)</option><option value="ASPD_P">ASPD (%)</option>' +
                '<option value="CSPD">CSPD (+)</option><option value="CSPD_P">CSPD (%)</option>' +
                '<option value="STABILITY">안정률 (%)</option>' +
                '<option value="MAXHP">최대 HP (+)</option><option value="MAXHPP">최대 HP (%)</option>' +
                '<option value="MAXMP">최대 MP (+)</option>' +
                '<option value="AMPR">공격 MP 회복 (+)</option><option value="AMPRP">공격 MP 회복 (%)</option>' +
                '<option value="PHYS_RES">물리 내성 (%)</option><option value="MAG_RES">마법 내성 (%)</option>' +
                '<option value="DEF">DEF (+)</option><option value="DEFP">DEF (%)</option>' +
                '<option value="MDEF">MDEF (+)</option><option value="MDEFP">MDEF (%)</option>' +
                '<option value="FLEE">회피 (+)</option><option value="FLEEP">회피 (%)</option>' +
                '<option value="ACC">명중 (+)</option><option value="ACCP">명중 (%)</option>' +
                '<option value="HP_REGEN">HP 자연회복 (+)</option><option value="HP_REGENP">HP 자연회복 (%)</option>' +
                '<option value="MP_REGEN">MP 자연회복 (+)</option><option value="MP_REGENP">MP 자연회복 (%)</option>' +
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
            var type = row.querySelector('.opt-type');
            var value = row.querySelector('.opt-val');
            function syncElementAttribute() {
                var isElementAttribute = type.value === 'ELEM_AWAKENING' || type.value === 'MAGIC_ELEMENT';
                value.readOnly = isElementAttribute;
                if (isElementAttribute) value.value = '1';
            }
            type.addEventListener('change', syncElementAttribute);
            row.querySelector('.remove-option-row').addEventListener('click', function () { row.remove(); document.dispatchEvent(new CustomEvent('toram:build-options-changed')); });
            container.appendChild(row);
            document.dispatchEvent(new CustomEvent('toram:build-options-changed'));
        }

        document.getElementById('banInput').addEventListener('keypress', function(e) {
            if(e.key === 'Enter') { e.preventDefault(); addBanTag(); }
        });

        function addBanTag() {
            var val = document.getElementById('banInput').value.trim();
            if(val && getBannedCrystas().indexOf(val) < 0) {
                setBannedCrystas(getBannedCrystas().concat(val));
                document.getElementById('banInput').value = '';
                renderBanTags();
                notifyOptimizationPreferencesChanged();
            }
        }
        function removeBanTag(val) { setBannedCrystas(getBannedCrystas().filter(function (value) { return value !== val; })); renderBanTags(); notifyOptimizationPreferencesChanged(); }
        function notifyOptimizationPreferencesChanged() {
            document.dispatchEvent(new CustomEvent('toram:optimization-preferences-changed'));
            document.dispatchEvent(new CustomEvent('toram:persistent-state-changed'));
        }
        function getBannedCrystas() { return (buildStore.getScenario().optimizationPreferences || {bannedCrystas:DEFAULT_BANNED_CRYSTAS}).bannedCrystas || []; }
        function setBannedCrystas(values) { var store=buildStore; store.commitScenario({optimizationPreferences:Object.assign({},store.getScenario().optimizationPreferences,{bannedCrystas:values.slice().sort()})}); }
        function restoreBannedCrystas(values) { setBannedCrystas(Array.isArray(values) ? values : DEFAULT_BANNED_CRYSTAS); renderBanTags(); }
        function renderBanTags() {
            var container = document.getElementById('banTagContainer');
            var count = document.getElementById('blacklistCount');
            if (count) count.textContent = getBannedCrystas().length + '개';
            container.innerHTML = '';
            for (var val of getBannedCrystas()) {
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

    var c1 = crystaCatalog.resolve(newValue);
    var c2 = counterpartVal ? crystaCatalog.resolve(counterpartVal) : null;

    // 중복 체크 및 팝업 (Alert)
    if (c1 && c2 && crystaCatalog.conflict(c1, c2)) {
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
function validateCrystaInputs() {
    var invalid = [];
    document.querySelectorAll('.cr-select').forEach(function (input) {
        var value = input.value.trim();
        renderCrystaInfo(input);
        if (value && !crystaCatalog.resolve(value)) invalid.push(input);
    });
    if (invalid.length) {
        var resultArea = document.getElementById('resultArea');
        if (resultArea) resultArea.style.display = 'none';
        invalid[0].focus();
    }
    return invalid.length === 0;
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

            row.querySelector('.remove-option-row').addEventListener('click', function () { row.remove(); document.dispatchEvent(new CustomEvent('toram:build-options-changed')); });
            container.appendChild(row);
            document.dispatchEvent(new CustomEvent('toram:build-options-changed'));
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

    for (var i = 0; i < crystaCatalog.items.length; i++) {
        var c = crystaCatalog.items[i];
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



const api = Object.freeze({initAutocomplete:initAutocomplete,renderBanTags:renderBanTags,validateCrystaInputs:validateCrystaInputs,buildGroupedTagsHtml:buildGroupedTagsHtml,
    addBanTag: addBanTag,
    addOptionRow: addOptionRow,
    addSkillStatRow: addSkillStatRow,
    getBannedCrystas: getBannedCrystas,
    restoreBannedCrystas: restoreBannedCrystas,
    onSubWeaponChange: onSubWeaponChange,
    refreshAllCrystaInfo: refreshAllCrystaInfo,
    updateSubWeaponList: updateSubWeaponList
});

// 저장 복원 전에 선택지를 만들고, 복원 후에는 다시 초기화하지 않는다.
function initializeEquipmentInputs() {
    document.querySelectorAll('[data-add-option]').forEach(function (button) {
      button.addEventListener('click', function () { api.addOptionRow(button.dataset.addOption); });
    });
    document.querySelector('[data-action="add-ban"]').addEventListener('click', api.addBanTag);
    document.querySelector('[data-action="main-weapon-change"]').addEventListener('change', function () {
      api.updateSubWeaponList();
      api.refreshAllCrystaInfo();
    });
    document.querySelector('[data-action="sub-weapon-change"]').addEventListener('change', api.onSubWeaponChange);
    document.querySelector('[data-action="armor-change"]').addEventListener('change', api.refreshAllCrystaInfo);
    populateRefineSelects();
    updateSubWeaponList();
}


function initCrystaEvents() {
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


initializeEquipmentInputs(); initCrystaEvents(); return api;
}
