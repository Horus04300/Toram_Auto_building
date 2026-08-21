import assert from 'node:assert/strict';
import fs from 'node:fs';
import vm from 'node:vm';

const calls = [];
const context = {
  window: {
    __TAURI__: {
      core: {
        invoke(command, args) {
          calls.push({ command, args });
          return Promise.resolve(command === 'settings_directory' ? 'C:\Native' : []);
        }
      }
    }
  }
};
vm.createContext(context);
vm.runInContext(fs.readFileSync('assets/js/tauri-build-storage-adapter.js', 'utf8'), context);

const adapter = context.window.ToramBuildStorageAdapter;
assert.ok(adapter, 'Tauri API가 있으면 저장 어댑터를 노출해야 한다.');
await adapter.directory();
await adapter.list();
await adapter.save('새 세팅', '{}');
await adapter.load('새 세팅.json');
await adapter.overwrite('새 세팅.json', '{"changed":true}');
await adapter.delete('새 세팅.json');

assert.deepEqual(JSON.parse(JSON.stringify(calls)), [
  { command: 'settings_directory' },
  { command: 'list_settings' },
  { command: 'save_setting', args: { name:'새 세팅', content:'{}' } },
  { command: 'load_setting', args: { name:'새 세팅.json' } },
  { command: 'overwrite_setting', args: { name:'새 세팅.json', content:'{"changed":true}' } },
  { command: 'delete_setting', args: { name:'새 세팅.json' } }
]);

const browserContext = { window:{} };
vm.createContext(browserContext);
vm.runInContext(fs.readFileSync('assets/js/tauri-build-storage-adapter.js', 'utf8'), browserContext);
assert.equal(browserContext.window.ToramBuildStorageAdapter, undefined, '브라우저에서는 네이티브 어댑터를 노출하지 않아야 한다.');

console.log('Tauri build storage adapter tests passed');