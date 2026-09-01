/* D4 결과를 장비 입력에 반영하는 UI 경계. 탐색 결과·잠금 자체는 변경하지 않는다. */
(function (root) {
  'use strict';

  var GROUPS = Object.freeze([
    Object.freeze({ slot:'weapon', inputIds:['cr_wpn_1', 'cr_wpn_2'], lockIds:['lock_wpn_1', 'lock_wpn_2'] }),
    Object.freeze({ slot:'armor', inputIds:['cr_arm_1', 'cr_arm_2'], lockIds:['lock_arm_1', 'lock_arm_2'] }),
    Object.freeze({ slot:'additional', inputIds:['cr_add_1', 'cr_add_2'], lockIds:['lock_add_1', 'lock_add_2'] }),
    Object.freeze({ slot:'special', inputIds:['cr_spc_1', 'cr_spc_2'], lockIds:['lock_spc_1', 'lock_spc_2'] })
  ]);

  function input(documentRef, id) {
    var node = documentRef.getElementById(id);
    if (!node) throw new Error('크리스타 입력을 찾지 못했습니다: ' + id);
    return node;
  }

  function removeLockedName(names, lockedName, slot) {
    var index = names.indexOf(lockedName);
    if (index < 0) throw new Error('추천 결과가 잠긴 ' + slot + ' 크리스타를 포함하지 않습니다. 새 전역 계산을 실행해 주세요.');
    names.splice(index, 1);
  }

  function buildAssignments(result, documentRef) {
    var packages = result && result.bestBuild && result.bestBuild.packages;
    if (!Array.isArray(packages)) throw new Error('적용할 전역 최적화 결과가 없습니다.');
    var assignments = [];
    GROUPS.forEach(function (group) {
      var packageResult = packages.find(function (item) { return item && item.slot === group.slot; });
      if (!packageResult || !Array.isArray(packageResult.candidateNames)) throw new Error('추천 결과에 ' + group.slot + ' 크리스타 정보가 없습니다.');
      var names = packageResult.candidateNames.slice();
      if (names.length > group.inputIds.length) throw new Error('추천 결과의 크리스타 슬롯 수가 올바르지 않습니다.');
      var writable = [];
      group.inputIds.forEach(function (inputId, index) {
        var valueInput = input(documentRef, inputId);
        var lockInput = input(documentRef, group.lockIds[index]);
        if (lockInput.checked) {
          var lockedName = String(valueInput.value || '').trim();
          if (!lockedName) throw new Error('잠긴 크리스타 슬롯이 비어 있습니다. 잠금을 해제하거나 값을 입력해 주세요.');
          removeLockedName(names, lockedName, group.slot);
        } else {
          writable.push(valueInput);
        }
      });
      if (names.length > writable.length) throw new Error('추천 결과가 잠금 상태와 맞지 않습니다. 새 전역 계산을 실행해 주세요.');
      writable.forEach(function (valueInput, index) {
        assignments.push({ input:valueInput, value:names[index] || '' });
      });
    });
    return assignments;
  }

  function notifyChanged(documentRef, valueInput) {
    if (typeof valueInput.dispatchEvent !== 'function') return;
    var EventConstructor = documentRef.defaultView && documentRef.defaultView.Event || root.Event;
    if (typeof EventConstructor === 'function') valueInput.dispatchEvent(new EventConstructor('change', { bubbles:true }));
  }

  function apply(result, documentRef) {
    var targetDocument = documentRef || root.document;
    if (!targetDocument) throw new Error('장비 입력 화면을 찾지 못했습니다.');
    var assignments = buildAssignments(result, targetDocument);
    var changed = 0;
    assignments.forEach(function (assignment) {
      if (assignment.input.value === assignment.value) return;
      assignment.input.value = assignment.value;
      changed++;
    });
    assignments.forEach(function (assignment) { notifyChanged(targetDocument, assignment.input); });
    var crystaUi = root.ToramApp && root.ToramApp.crystaUi;
    if (crystaUi && typeof crystaUi.refreshAllCrystaInfo === 'function') crystaUi.refreshAllCrystaInfo();
    return { changed:changed, writableSlots:assignments.length };
  }

  root.ToramD4RecommendationApply = Object.freeze({ apply:apply, buildAssignments:buildAssignments });
}(typeof window !== 'undefined' ? window : globalThis));
