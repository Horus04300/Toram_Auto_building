import { cp, mkdir, readFile, writeFile } from 'node:fs/promises';
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

console.log(`Prepared Tauri frontend v${packageJson.version} in dist/.`);
