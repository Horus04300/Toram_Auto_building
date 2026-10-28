import * as buildValues from '../application/build-values.mjs';
import {statRegistry} from '../calculation/stat-registry.js';
import {foodCatalog} from '../data/my-room-food.js';
export function createSettingsRepository(root,store,files=null) {
  const document=root.document;
  'use strict';
  var FORMAT = 'toram-auto-build-document';
  var SCHEMA_VERSION = 2;
  var LEGACY_SCHEMA_VERSION = 1;
  var SESSION_STORAGE_KEY = 'toram.auto-build.application-state.v2';
  var LEGACY_SESSION_STORAGE_KEY = 'toram.auto-build.application-state.v1';
  var restoring = false, pendingSave = null;

  function clone(value) { return structuredClone(value); }
  function now() { return new Date().toISOString(); }
  function safeName(value) {
    var name = String(value || '').trim().replace(/[\/:*?"<>|]/g, '-').replace(/\s+/g, ' ').replace(/[. ]+$/g, '');
    return name || ('세팅-' + new Date().toISOString().slice(0, 19).replace(/[:T]/g, '-'));
  }
  function fileAdapter() { return files; }
  function storage() { try { return root.localStorage || null; } catch (_) { return null; } }
  function buildShape(value) {
    try { buildValues.validateBuild(value, { registry:statRegistry, food:foodCatalog }); return true; }
    catch (_) { return false; }
  }
  function scenarioShape(value) {
    try { buildValues.validateScenario(value); return true; }
    catch (_) { return false; }
  }
  function documentShape(document, documentType, schemaVersion) { return Boolean(document && document.format === FORMAT && document.schemaVersion === schemaVersion && document.documentType === documentType); }
  function validateSavedBuild(document) {
    return Boolean(documentShape(document, 'saved-build', SCHEMA_VERSION) && typeof document.name === 'string' && typeof document.createdAt === 'string' && typeof document.updatedAt === 'string' && buildShape(document.build) && scenarioShape(document.scenario));
  }
  function validateLegacySavedBuild(document) { return Boolean(documentShape(document, 'saved-build', LEGACY_SCHEMA_VERSION) && typeof document.name === 'string' && typeof document.createdAt === 'string' && typeof document.updatedAt === 'string' && buildShape(document.build) && scenarioShape(document.scenario)); }
  function validateApplicationState(document) {
    return Boolean(documentShape(document, 'application-state', SCHEMA_VERSION) && document.appSettings && typeof document.appSettings === 'object' && (!document.lastSession || (buildShape(document.lastSession.build) && scenarioShape(document.lastSession.scenario))));
  }
  function validateLegacyApplicationState(document) { return Boolean(documentShape(document, 'application-state', LEGACY_SCHEMA_VERSION) && document.appSettings && typeof document.appSettings === 'object' && (!document.lastSession || (buildShape(document.lastSession.build) && scenarioShape(document.lastSession.scenario)))); }
  function discardLegacyBuffOptionProxy(build) { return Object.assign({}, build || {}, { externalOptions:[] }); }
  function recoverLegacySession(session) {
    if (!session) return null;
    return { build:discardLegacyBuffOptionProxy(session.build), scenario:clone(session.scenario), savedAt:session.savedAt || now() };
  }
  function currentSession() {

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
    try {
      var parsed = JSON.parse(local.getItem(SESSION_STORAGE_KEY) || 'null');
      if (validateApplicationState(parsed)) return parsed;
      var legacy = JSON.parse(local.getItem(LEGACY_SESSION_STORAGE_KEY) || 'null');
      if (!validateLegacyApplicationState(legacy)) return applicationState(null, null);
      var recovered = applicationState(recoverLegacySession(legacy.lastSession), legacy);
      writeApplicationState(recovered);
      return recovered;
    } catch (_) { return applicationState(null, null); }
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
  function getUpdateSettings() {
    var update = readApplicationState().appSettings.update;
    return { checkOnStartup:!update || update.checkOnStartup !== false };
  }
  function flushApplicationState() {
    if (restoring || !storage()) throw new Error('현재 세팅을 저장할 수 없어 업데이트를 중단했습니다.');
    if (pendingSave !== null) { root.clearTimeout(pendingSave); pendingSave = null; }
    store.syncFromUi();
    saveLastSession();
  }
  function setUpdateSettings(settings) {
    if (!settings || typeof settings.checkOnStartup !== 'boolean') throw new Error('업데이트 설정이 올바르지 않습니다.');
    if (!storage()) throw new Error('설정 저장소를 사용할 수 없습니다.');
    var state = readApplicationState();
    state.appSettings.update = { checkOnStartup:settings.checkOnStartup };
    writeApplicationState(applicationState(state.lastSession, state));
  }
  function restoreSession(session) {
    if (!session || !buildShape(session.build) || !scenarioShape(session.scenario)) return;
    var ui = store;
    if (!ui || typeof ui.restoreSession !== 'function') throw new Error('Build 상태 UI 어댑터가 준비되지 않았습니다.');
    restoring = true;
    try { ui.restoreSession(session); } finally { restoring = false; }
  }
  function restoreLastSession() { var state = readApplicationState(); if (state.lastSession) restoreSession(state.lastSession); return clone(state.lastSession); }
  function savedBuild(name, existing) {
    var session = currentSession(), timestamp = now();
    return { format:FORMAT, schemaVersion:SCHEMA_VERSION, documentType:'saved-build', name:safeName(name), createdAt:existing && existing.createdAt || timestamp, updatedAt:timestamp, build:session.build, scenario:session.scenario };
  }
  function snapshot(name) { store.syncFromUi(); return savedBuild(name); }
  function parseSavedBuild(text) {
    var parsed = JSON.parse(text);
    if (validateSavedBuild(parsed)) return parsed;
    if (!validateLegacySavedBuild(parsed)) throw new Error('새 저장 계약의 빌드 JSON이 아닙니다.');
    return Object.assign({}, parsed, { schemaVersion:SCHEMA_VERSION, build:discardLegacyBuffOptionProxy(parsed.build) });
  }
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
  function applySession(session) {
    buildValues.validateBuild(session.build,{registry:statRegistry,food:foodCatalog});
    buildValues.validateScenario(session.scenario);
    restoreSession(clone({build:session.build,scenario:session.scenario}));
    writeApplicationState(applicationState(currentSession(),readApplicationState()));
  }
  function importSavedBuild(text) { var document = parseSavedBuild(text); applySession(document); return document; }
  function initialize() {
    restoreLastSession();
    ['toram:persistent-state-changed','toram:skill-investments-changed','toram:active-buffs-changed','toram:combo-changed','toram:build-options-changed'].forEach(function (eventName) { document.addEventListener(eventName, scheduleLastSessionSave); });
  }
  return Object.freeze({initialize:initialize, flushApplicationState:flushApplicationState, getUpdateSettings:getUpdateSettings, setUpdateSettings:setUpdateSettings, format:FORMAT, schemaVersion:SCHEMA_VERSION, sessionStorageKey:SESSION_STORAGE_KEY, safeName:safeName, validateSavedBuild:validateSavedBuild, validateApplicationState:validateApplicationState, snapshot:snapshot, parseSavedBuild:parseSavedBuild, list:list, directory:directory, save:save, overwrite:overwrite, load:load, remove:remove, exportCurrent:exportCurrent, importSavedBuild:importSavedBuild, applySession:applySession, restoreLastSession:restoreLastSession, saveLastSession:saveLastSession, isNativeAvailable:function () { return Boolean(fileAdapter()); } });
}
