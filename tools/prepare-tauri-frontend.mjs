import { cp, mkdir, readFile, writeFile, readdir, access, unlink, realpath } from 'node:fs/promises';
import { dirname, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';

const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const packageJson = JSON.parse(await readFile(resolve(root, 'package.json'), 'utf8'));
const outputRoot = resolve(root, 'dist');
const versionToken = '{{APP_VERSION}}';

let html = await readFile(resolve(root, 'index.html'), 'utf8');
const tokenCount = html.split(versionToken).length - 1;
if (tokenCount !== 3) {
  throw new Error(`Expected three ${versionToken} placeholders, found ${tokenCount}.`);
}

html = html.replaceAll(versionToken, `v${packageJson.version}`);

await mkdir(outputRoot, { recursive: true });
await writeFile(resolve(outputRoot, 'index.html'), html, 'utf8');
await cp(resolve(root, 'assets'), resolve(outputRoot, 'assets'), {
  recursive: true,
  force: true,
});

// Renamed source files must not survive in the generated desktop package.
// Only unlink obsolete regular files inside the verified output assets tree.
const outputAssets = resolve(outputRoot, 'assets');
if (await realpath(outputAssets) !== outputAssets) throw new Error('dist/assets must be a real output directory');
async function pruneRemovedAssets(directory, sourceDirectory) {
  for (const entry of await readdir(directory, { withFileTypes:true })) {
    const output = resolve(directory, entry.name), source = resolve(sourceDirectory, entry.name);
    if (entry.isDirectory()) await pruneRemovedAssets(output, source);
    else if (entry.isFile()) {
      try { await access(source); }
      catch (error) { if (error.code !== 'ENOENT') throw error; await unlink(output); }
    }
  }
}
await pruneRemovedAssets(outputAssets, resolve(root, 'assets'));

console.log(`Prepared Tauri frontend v${packageJson.version} in dist/.`);
