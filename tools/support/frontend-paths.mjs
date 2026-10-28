import {readFile,access} from 'node:fs/promises';
import {resolve,relative,posix} from 'node:path';
import ts from 'typescript';
const root=resolve(import.meta.dirname,'../..');
const slash=value=>value.replaceAll('\\','/');
const desktopSources={
 'assets/js/optimization/native-client.js':'desktop/adapters/optimization-client.js',
 'assets/js/storage/tauri-build-storage-adapter.js':'build/generated/desktop/saved-build-storage.js',
 'assets/js/update/tauri-update-adapter.js':'build/generated/desktop/update.js',
 'assets/js/update/update-controller.js':'desktop/adapters/update/update-controller.js',
 'assets/js/ui/update-ui-controller.js':'desktop/adapters/update/ui-controller.js',
 'assets/js/desktop-runtime.mjs':'desktop/adapters/calculator-runtime.mjs'
};
export function frontendSourcePath(url) {
 if(desktopSources[url])return desktopSources[url];
 if(url==='assets/pages/calculator.html')return 'web/src/pages/calculator/calculator.html';
 if(url.startsWith('assets/js/'))return url.replace('assets/js/','web/src/');
 if(url.startsWith('assets/wasm/'))return url.replace('assets/wasm/','build/generated/wasm/');
 if(url.startsWith('assets/'))return url.replace('assets/','web/public/');
 return url;
}
function frontendUrl(file) {
 const alias=Object.entries(desktopSources).find(([,source])=>source===file);if(alias)return alias[0];
 if(file==='web/src/pages/calculator/calculator.html')return 'assets/pages/calculator.html';
 if(file.startsWith('web/src/'))return file.replace('web/src/','assets/js/');
 if(file.startsWith('web/public/'))return file.replace('web/public/','assets/');
 if(file.startsWith('build/generated/wasm/'))return file.replace('build/generated/wasm/','assets/wasm/');
 throw new Error('No deployment path for '+file);
}
function parseDependencies(source) {
 const syntax=ts.createSourceFile('module.js',source,ts.ScriptTarget.Latest,true),result=[];
 function add(literal,kind){if(literal&&ts.isStringLiteralLike(literal))result.push({specifier:literal.text,start:literal.getStart(syntax),end:literal.end,kind});}
 function visit(node){
  if(ts.isImportDeclaration(node)||ts.isExportDeclaration(node))add(node.moduleSpecifier,'static');
  if(ts.isCallExpression(node)&&node.expression.kind===ts.SyntaxKind.ImportKeyword)add(node.arguments[0],'dynamic');
  if(ts.isNewExpression(node)&&node.expression.getText(syntax)==='URL'&&node.arguments?.[1]?.getText(syntax)==='import.meta.url')add(node.arguments[0],'url');
  ts.forEachChild(node,visit);
 }visit(syntax);return result;
}
async function sourceDependency(file,reference) {
 const specifier=reference.specifier;
 if(!specifier.startsWith('.'))return null;
 const candidate=slash(relative(root,resolve(root,posix.dirname(file),specifier)));
 try {await access(resolve(root,candidate));return candidate;}catch(error){if(error.code!=='ENOENT')throw error;}
 // Generated WASM and HTML paths are deployment-relative, unlike normal source imports.
 return frontendSourcePath(posix.normalize(posix.join(posix.dirname(frontendUrl(file)),specifier)));
}
export async function sourceModuleFiles(entries) {
 const seen=new Set();
 async function walk(file){
  if(seen.has(file))return;seen.add(file);
  const source=await readFile(resolve(root,file),'utf8');
  for(const dependency of parseDependencies(source)){
   const next=await sourceDependency(file,dependency);
   if(next&&/\.(?:m?js)$/u.test(next))await walk(next);
  }
 }
 for(const file of entries)await walk(file);
 return [...seen].sort();
}
export async function renderFrontendModule(url) {
 const file=frontendSourcePath(url),dependencies=[];
 let source=await readFile(resolve(root,file),'utf8');const edits=[];
 for(const dependency of parseDependencies(source)){
  const next=await sourceDependency(file,dependency);if(!next)continue;
  const nextUrl=frontendUrl(next);dependencies.push({url:nextUrl,kind:dependency.kind});
  let specifier=posix.relative(posix.dirname(url),nextUrl);if(!specifier.startsWith('.'))specifier='./'+specifier;
  if(specifier!==dependency.specifier)edits.push({...dependency,value:JSON.stringify(specifier)});
 }
 for(const edit of edits.sort((a,b)=>b.start-a.start))source=source.slice(0,edit.start)+edit.value+source.slice(edit.end);
 return {source,dependencies};
}
export async function frontendModuleGraph(target) {
 if(!['web','desktop'].includes(target))throw new Error('Unknown frontend target');
 const files=new Set(),rendered=new Map();
 async function walk(url){
  if(files.has(url))return;
  const file=frontendSourcePath(url),desktop=file.startsWith('desktop/')||file.startsWith('build/generated/desktop/');
  if(target==='web'&&desktop)return;
  files.add(url);
  if(!/\.(?:m?js)$/u.test(file))return;
  const module=await renderFrontendModule(url);
  for(const dependency of module.dependencies){
   const next=frontendSourcePath(dependency.url),native=next.startsWith('desktop/')||next.startsWith('build/generated/desktop/');
   if(target==='web'&&native&&dependency.kind==='static')throw new Error('Web entry imports a Native module: '+file);
   await walk(dependency.url);
  }
  rendered.set(url,module.source);
 }
 await walk('assets/js/app-entry.mjs');
 return {files,rendered};
}
