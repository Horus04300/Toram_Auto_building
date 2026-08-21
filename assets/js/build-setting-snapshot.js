/* 계산기 전체 세팅의 JSON 스냅샷 계약. 저장 위치와 UI에 의존하지 않는다. */
(function () {
  'use strict';

  var FORMAT = 'toram-auto-build-setting';
  var SCHEMA_VERSION = 1;
  var STATE_KEYS = [
    'toram-auto-building.build-state.v1',
    'toram-auto-building.skill-tree.v1',
    'toram-auto-building.skill-tree-ui.v1',
    'toram-auto-active-buffs-v1',
    'toram.combo-sequence.v1'
  ];

  function safeFileStem(value) {
    var name = String(value || '').trim()
      .replace(/[\/:*?"<>|]/g, '-')
      .replace(/\s+/g, ' ')
      .replace(/[. ]+$/g, '');
    return name || ('세팅-' + new Date().toISOString().slice(0, 19).replace(/[:T]/g, '-'));
  }

  function capture(name) {
    var storage = {};
    STATE_KEYS.forEach(function (key) {
      storage[key] = window.localStorage.getItem(key);
    });
    return {
      format:FORMAT,
      schemaVersion:SCHEMA_VERSION,
      name:safeFileStem(name),
      savedAt:new Date().toISOString(),
      storage:storage
    };
  }

  function validate(data) {
    if (!data || data.format !== FORMAT || data.schemaVersion !== SCHEMA_VERSION) return false;
    if (!data.storage || typeof data.storage !== 'object' || Array.isArray(data.storage)) return false;
    return STATE_KEYS.every(function (key) {
      var value = data.storage[key];
      return value === null || value === undefined || typeof value === 'string';
    });
  }

  function parse(text) {
    var data = JSON.parse(text);
    if (!validate(data)) throw new Error('이 계산기의 세팅 JSON 파일이 아닙니다.');
    return data;
  }

  function serialize(name) {
    return JSON.stringify(capture(name), null, 2);
  }

  function apply(data, options) {
    if (!validate(data)) throw new Error('이 계산기의 세팅 JSON 파일이 아닙니다.');
    STATE_KEYS.forEach(function (key) {
      var value = data.storage[key];
      if (typeof value === 'string') window.localStorage.setItem(key, value);
      else window.localStorage.removeItem(key);
    });
    if (!options || options.reload !== false) window.location.reload();
  }

  function download(name) {
    var fileStem = safeFileStem(name);
    var blob = new Blob([serialize(fileStem)], { type:'application/json' });
    var url = URL.createObjectURL(blob);
    var link = document.createElement('a');
    link.href = url;
    link.download = fileStem + '.json';
    document.body.appendChild(link);
    link.click();
    link.remove();
    window.setTimeout(function () { URL.revokeObjectURL(url); }, 0);
    return link.download;
  }

  window.ToramBuildSettings = Object.freeze({
    format:FORMAT,
    schemaVersion:SCHEMA_VERSION,
    stateKeys:STATE_KEYS.slice(),
    safeFileStem:safeFileStem,
    capture:capture,
    validate:validate,
    parse:parse,
    serialize:serialize,
    apply:apply,
    download:download
  });
}());
