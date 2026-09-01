/* R6 단일 저장 경계: named build, app settings, last session. */
(function (root) {
  'use strict';
  var FORMAT = 'toram-auto-build-document';
  var SCHEMA_VERSION = 1;
  var SESSION_STORAGE_KEY = 'toram.auto-build.application-state.v1';
  var restoring = false, pendingSave = null;

  function clone(value) { return value === undefined ? undefined : JSON.parse(JSON.stringify(value)); }
  function now() { return new Date().toISOString(); }
  function safeName(value) {
    var name = String(value || '').trim().replace(/[\/:*?"<>|]/g, '-').replace(/\s+/g, ' ').replace(/[. ]+$/g, '');
    return name || ('세팅-' + new Date().toISOString().slice(0, 19).replace(/[:T]/g, '-'));
  }
  function fileAdapter() { return root.ToramSettingsFileRepositoryAdapter || null; }
  function storage() { try { return root.localStorage || null; } catch (_) { return null; } }
  function buildShape(value) { return Boolean(value && typeof value === 'object' && value.character && value.equipment && value.skillLevels && value.activeBuffs && Array.isArray(value.externalOptions) && Array.isArray(value.combo)); }
  function scenarioShape(value) { return Boolean(value && typeof value === 'object' && value.target && typeof value.target === 'object'); }
  function validateSavedBuild(document) {
    return Boolean(document && document.format === FORMAT && document.schemaVersion === SCHEMA_VERSION && document.documentType === 'saved-build' && typeof document.name === 'string' && typeof document.createdAt === 'string' && typeof document.updatedAt === 'string' && buildShape(document.build) && scenarioShape(document.scenario));
  }
  function validateApplicationState(document) {
    return Boolean(document && document.format === FORMAT && document.schemaVersion === SCHEMA_VERSION && document.documentType === 'application-state' && document.appSettings && typeof document.appSettings === 'object' && (!document.lastSession || (buildShape(document.lastSession.build) && scenarioShape(document.lastSession.scenario))));
  }
  function currentSession() {
    var store = root.ToramBuildDraftStore;
    if (!store || typeof store.read !== 'function') throw new Error('BuildDraft 저장소가 준비되지 않았습니다.');
    var source = store.read();
    return { build:clone(source.build), scenario:clone(source.scenario), savedAt:now() };
  }
  function applicationState(lastSession, existing) {
    return { format:FORMAT, schemaVersion:SCHEMA_VERSION, documentType:'application-state', appSettings:Object.assign({ lastOpenedBuildId:null }, existing && existing.appSettings || {}), lastSession:lastSession || null, updatedAt:now() };
  }
  function readApplicationState() {
    var local = storage();
    if (!local) return applicationState(null, null);
    try { var parsed = JSON.parse(local.getItem(SESSION_STORAGE_KEY) || 'null'); return validateApplicationState(parsed) ? parsed : applicationState(null, null); } catch (_) { return applicationState(null, null); }
  }
  function writeApplicationState(next) {
    var local = storage();
    if (!local) return;
    local.setItem(SESSION_STORAGE_KEY, JSON.stringify(next));
  }
  function saveLastSession() {
    if (restoring) return;
    var existing = readApplicationState();
    writeApplicationState(applicationState(currentSession(), existing));
  }
  function scheduleLastSessionSave() {
    if (restoring || pendingSave !== null) return;
    pendingSave = root.setTimeout(function () { pendingSave = null; try { saveLastSession(); } catch (error) { console.warn('마지막 세션 저장 실패', error); } }, 0);
  }
  function restoreSession(session) {
    if (!session || !buildShape(session.build) || !scenarioShape(session.scenario)) return;
    var ui = root.ToramBuildStateUi;
    if (!ui || typeof ui.restoreSession !== 'function') throw new Error('Build 상태 UI 어댑터가 준비되지 않았습니다.');
    restoring = true;
    try { ui.restoreSession(session); } finally { restoring = false; }
  }
  function restoreLastSession() { var state = readApplicationState(); if (state.lastSession) restoreSession(state.lastSession); return clone(state.lastSession); }
  function savedBuild(name, existing) {
    var session = currentSession(), timestamp = now();
    return { format:FORMAT, schemaVersion:SCHEMA_VERSION, documentType:'saved-build', name:safeName(name), createdAt:existing && existing.createdAt || timestamp, updatedAt:timestamp, build:session.build, scenario:session.scenario };
  }
  function serializeSavedBuild(name) { return JSON.stringify(savedBuild(name), null, 2); }
  function parseSavedBuild(text) { var parsed = JSON.parse(text); if (!validateSavedBuild(parsed)) throw new Error('새 저장 계약의 빌드 JSON이 아닙니다.'); return parsed; }
  async function list() { var adapter = fileAdapter(); return adapter ? adapter.list() : []; }
  async function directory() { var adapter = fileAdapter(); return adapter && adapter.directory ? adapter.directory() : ''; }
  async function save(name) { var adapter = fileAdapter(); if (!adapter) throw new Error('데스크톱 저장 기능이 아직 연결되지 않았습니다.'); var document = savedBuild(name); await adapter.save(document.name, JSON.stringify(document, null, 2)); return document; }
  async function overwrite(fileName) { var adapter = fileAdapter(); if (!adapter) throw new Error('데스크톱 저장 기능이 아직 연결되지 않았습니다.'); var current = parseSavedBuild(await adapter.load(fileName)); var document = savedBuild(current.name, current); await adapter.overwrite(fileName, JSON.stringify(document, null, 2)); return document; }
  async function load(fileName) { var adapter = fileAdapter(); if (!adapter) throw new Error('데스크톱 저장 기능이 아직 연결되지 않았습니다.'); var document = parseSavedBuild(await adapter.load(fileName)); restoreSession({ build:document.build, scenario:document.scenario }); var state = readApplicationState(); state.appSettings.lastOpenedBuildId = fileName; writeApplicationState(applicationState(currentSession(), state)); return document; }
  async function remove(fileName) { var adapter = fileAdapter(); if (!adapter) throw new Error('데스크톱 저장 기능이 아직 연결되지 않았습니다.'); return adapter.delete(fileName); }
  function exportCurrent(name) {
    var document = savedBuild(name), blob = new Blob([JSON.stringify(document, null, 2)], { type:'application/json' }), url = URL.createObjectURL(blob), link = documentRef().createElement('a');
    link.href = url; link.download = document.name + '.json'; documentRef().body.appendChild(link); link.click(); link.remove(); root.setTimeout(function () { URL.revokeObjectURL(url); }, 0); return link.download;
  }
  function documentRef() { return root.document || document; }
  function importSavedBuild(text) { var document = parseSavedBuild(text); restoreSession({ build:document.build, scenario:document.scenario }); writeApplicationState(applicationState(currentSession(), readApplicationState())); return document; }
  function initialize() {
    restoreLastSession();
    ['toram:persistent-state-changed','toram:skill-investments-changed','toram:active-buffs-changed','toram:combo-changed','toram:build-options-changed'].forEach(function (eventName) { document.addEventListener(eventName, scheduleLastSessionSave); });
  }
  root.ToramSettingsRepository = Object.freeze({ format:FORMAT, schemaVersion:SCHEMA_VERSION, sessionStorageKey:SESSION_STORAGE_KEY, safeName:safeName, validateSavedBuild:validateSavedBuild, validateApplicationState:validateApplicationState, serializeSavedBuild:serializeSavedBuild, parseSavedBuild:parseSavedBuild, list:list, directory:directory, save:save, overwrite:overwrite, load:load, remove:remove, exportCurrent:exportCurrent, importSavedBuild:importSavedBuild, restoreLastSession:restoreLastSession, saveLastSession:saveLastSession, isNativeAvailable:function () { return Boolean(fileAdapter()); } });
  if (document.readyState === 'loading') document.addEventListener('DOMContentLoaded', initialize, { once:true }); else initialize();
}(window));
