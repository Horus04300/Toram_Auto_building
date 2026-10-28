import {createCatalogReader} from './catalog-assets.mjs';
export const BOSS_CATALOG_SCHEMA = 'toram.project-bosses.v1';

function requireValue(value, message) { if (!value) throw new Error(message); }

// The catalog exposes original variants; choosing a combat phase/difficulty is a separate operation.
export function createBossCatalog(manifestUrl, fetchImpl = globalThis.fetch) {
  const {read}=createCatalogReader(manifestUrl,fetchImpl,async (response,path,expected)=>{
    requireValue(response.ok,'Boss catalog request failed: '+path);
    const bytes=await response.arrayBuffer();
    if(expected) {
      requireValue(bytes.byteLength===expected.bytes,'Boss asset size differs.');
      const digest=[...new Uint8Array(await globalThis.crypto.subtle.digest('SHA-256',bytes))].map(v=>v.toString(16).padStart(2,'0')).join('');
      requireValue(digest===expected.sha256,'Boss asset hash differs.');
    }
    return JSON.parse(new TextDecoder().decode(bytes));
  });
  function request(path,expected) {
    requireValue(/^[a-z0-9][a-z0-9/.-]*$/u.test(path)&&!path.includes('..'),'Invalid boss asset path.');
    return read(path,expected);
  }
  async function manifest() {
    const value = await request('manifest.json');
    requireValue(value.schema === BOSS_CATALOG_SCHEMA && /^[a-f0-9]{64}$/u.test(value.revision), 'Unsupported boss catalog.');
    return value;
  }
  async function asset(path, value) {
    requireValue(value.files[path]?.sha256 && Number.isSafeInteger(value.files[path].bytes), 'Unlisted boss asset.');
    return request(path, value.files[path]);
  }
  async function localized(value, locale) {
    requireValue(Object.hasOwn(value.locales, locale), 'Unsupported boss language.');
    return asset(value.locales[locale], value);
  }
  return Object.freeze({
    manifest,
    async search(query = '', locale = 'kr', {classification} = {}) {
      const value = await manifest(), [index, names] = await Promise.all([asset(value.index, value), localized(value, locale)]);
      const text = String(query).toLocaleLowerCase();
      const ids = classification ? new Set((await Promise.all(Object.values(value.groups).map(path => asset(path,value)))).flat().filter(row => row.classification === classification).map(row => row.gameMonsterId)) : null;
      return Object.keys(index).map(Number).filter(id => (!ids || ids.has(id)) && (!text || String(id).includes(text) || (names.monsters[id] || '').toLocaleLowerCase().includes(text)))
        .map(gameMonsterId => ({ gameMonsterId, name:names.monsters[gameMonsterId] ?? null }));
    },
    async get(gameMonsterId, locale = 'kr') {
      requireValue(Number.isSafeInteger(gameMonsterId) && gameMonsterId >= 0, 'Invalid game monster ID.');
      const value = await manifest(), index = await asset(value.index, value);
      if (!Object.hasOwn(index, gameMonsterId)) return null;
      const [rows, names] = await Promise.all([asset(value.groups[index[gameMonsterId]], value), localized(value, locale)]);
      return { gameMonsterId, revision:value.revision, name:names.monsters[gameMonsterId] ?? null,
        variants:rows.filter(row => row.gameMonsterId === gameMonsterId).map(row => ({ ...row, fieldName:names.fields[row.fieldId] ?? null })) };
    }
  });
}
