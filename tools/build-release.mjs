import { readdir, readFile, writeFile } from 'node:fs/promises';
import { dirname, relative, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';

const version = process.argv[2];
if (!version || !/^[a-zA-Z0-9][a-zA-Z0-9._-]*$/.test(version)) {
  throw new Error('Usage: node tools/build-release.mjs <version>');
}

const root = resolve(dirname(fileURLToPath(import.meta.url)), '..');
const outputPath = resolve(root, 'Versions', `${version}.html`);
const iconRoot = resolve(root, 'coryn_skill_icons');

async function collectPngAssets(directory) {
  const entries = await readdir(directory, { withFileTypes: true });
  const assets = {};
  for (const entry of entries) {
    const fullPath = resolve(directory, entry.name);
    if (entry.isDirectory()) {
      Object.assign(assets, await collectPngAssets(fullPath));
    } else if (entry.isFile() && entry.name.toLowerCase().endsWith('.png')) {
      const key = relative(root, fullPath).replaceAll('\\', '/');
      const encoded = (await readFile(fullPath)).toString('base64');
      assets[key] = `data:image/png;base64,${encoded}`;
    }
  }
  return assets;
}

let html = await readFile(resolve(root, 'index.html'), 'utf8');
const versionToken = '{{APP_VERSION}}';
const versionTokenCount = html.split(versionToken).length - 1;
if (versionTokenCount !== 3) {
  throw new Error(`Expected three ${versionToken} placeholders, found ${versionTokenCount}.`);
}
html = html.replaceAll(versionToken, version);
let css = await readFile(resolve(root, 'assets/css/style.css'), 'utf8');
const fontPath = resolve(root, 'assets/fonts/PretendardVariable.woff2');
const localFontUrl = "url('../fonts/PretendardVariable.woff2')";
const fontDataUrl = `data:font/woff2;base64,${(await readFile(fontPath)).toString('base64')}`;
if (!css.includes(localFontUrl)) {
  throw new Error('The local Pretendard font declaration was not found in the stylesheet.');
}
css = css.replaceAll(localFontUrl, `url('${fontDataUrl}')`);
html = html.replace(
  '    <link rel="stylesheet" href="assets/css/style.css">',
  `    <style>\n${css}\n    </style>`,
);

const assets = await collectPngAssets(iconRoot);
const assetBootstrap = `    <script>window.TORAM_ASSETS = ${JSON.stringify(assets)};</script>`;
html = html.replace('    <script src="assets/js/data/skill-tree-data.js"></script>', `${assetBootstrap}\n    <script src="assets/js/data/skill-tree-data.js"></script>`);

const scriptPattern = /    <script src="([^"]+)"><\/script>/g;
const scriptMatches = [...html.matchAll(scriptPattern)];
for (const match of scriptMatches) {
  const scriptPath = resolve(root, match[1]);
  let source = await readFile(scriptPath, 'utf8');
  if (match[1] === 'assets/js/skill-tree.js') {
    source = source.replace(
      'function iconPath(path) { return encodeURI(path); }',
      'function iconPath(path) { return window.TORAM_ASSETS[path] || encodeURI(path); }',
    );
  }
  html = html.replace(match[0], `    <script>\n${source}\n    </script>`);
}

await writeFile(outputPath, html, 'utf8');
console.log(`Created ${relative(root, outputPath)} with ${Object.keys(assets).length} embedded icons.`);