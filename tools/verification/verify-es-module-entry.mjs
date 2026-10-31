import assert from 'node:assert/strict';
import {access,readFile} from 'node:fs/promises';
import {resolve} from 'node:path';
import {frontendModuleGraph,frontendSourcePath,sourceModuleFiles} from '../support/frontend-paths.mjs';
import ts from 'typescript';
const root=resolve(import.meta.dirname,'../..'),dist=process.argv.includes('--dist'),web=process.argv.includes('--web');
for(const target of dist?['desktop']:web?['web']:['web','desktop']) {
 const graph=await frontendModuleGraph(target),directory=resolve(root,'build',target);
 const html=await readFile(dist||web?resolve(directory,'index.html'):resolve(root,'web/index.html'),'utf8');
 assert.equal((html.match(/<script\b/g)||[]).length,1,'One module entry owns startup');
 assert.match(html,/<script type="module" src="assets\/js\/app-entry\.mjs"><\/script>/);
 if(dist||web)assert.ok(!html.includes('{{APP_VERSION}}'));
 for(const url of graph.files) {
  await access(dist||web?resolve(directory,url):resolve(root,frontendSourcePath(url)));
  if((dist||web)&&graph.rendered.has(url))assert.equal(await readFile(resolve(directory,url),'utf8'),graph.rendered.get(url),'Deployment module is stale: '+url);
 }
 const native=[...graph.files].filter(url=>/desktop\/|build\/generated\/desktop\//u.test(frontendSourcePath(url)));
 assert.equal(native.length>0,target==='desktop','Native modules must only be deployed to the desktop target');
 assert.ok(graph.files.has('assets/js/optimization/wasm-worker.js'),'Worker is reachable from real imports');
 assert.ok(graph.files.has('assets/pages/calculator.html'),'Lazy calculator HTML is in the graph');
 console.log(`ES module entry: PASS (${target}, ${graph.files.size} graph assets, ${native.length} Native modules)`);
}
const kernel=await sourceModuleFiles(['web/src/calculation/calculator.js']);
assert.ok(!kernel.some(path=>/\/ui\/|\/data\/skills\//u.test(path)),'Worker evaluation must not load UI or skill authoring data');
console.log(`Headless kernel: PASS (${kernel.length} modules; no UI/skill-data dependency)`);
if(!dist&&!web) {
 const application=await sourceModuleFiles(['web/src/application/application-use-cases.js']);
 assert.ok(!application.some(path=>path.includes('/ui/')),'Application input cannot depend on UI');
 const renderer=await sourceModuleFiles(['web/src/ui/optimization-results.js']);
 assert.ok(!renderer.some(path=>/application-use-cases|build-evaluator|\/calculator\.js|execution-adapter|optimizer-ui-controller|optimization-client|wasm-client|problem-compiler|candidate-preparation/.test(path)),'Result rendering consumes values without calculation/execution owners');
 const execution=await sourceModuleFiles(['web/src/optimization/execution-adapter.js']);
 assert.ok(!execution.some(path=>/\/calculation\/|problem-compiler|candidate-preparation|\/ui\//.test(path)),'Runtime selection cannot compile or evaluate a problem');
 const worker=await sourceModuleFiles(['web/src/optimization/wasm-worker.js']);
 assert.ok(!worker.some(path=>path.includes('/ui/')),'Worker is headless');
 const docker=await readFile(resolve(root,'server/Dockerfile'),'utf8');
 const copied=docker.split(/\r?\n/).filter(line=>line.startsWith('COPY ')).flatMap(line=>line.split(/\s+/).slice(1,-1).filter(part=>!part.startsWith('--')));
 const dockerAllowed=new Set((await readFile(resolve(root,'.dockerignore'),'utf8')).split(/\r?\n/));
 for(const path of ['package.json',...await sourceModuleFiles(['server/account-server.mjs'])]) {
  for(let entry=path;entry;entry=entry.includes('/')?entry.slice(0,entry.lastIndexOf('/')):'') assert.ok(dockerAllowed.has('!'+entry+(entry===path?'':'/')),'Docker context omits runtime dependency or parent: '+entry);
 }
 for(const path of await sourceModuleFiles(['server/account-server.mjs'])) assert.ok(copied.includes(path),'Docker omits runtime dependency: '+path);
 assert.ok(copied.includes('package.json'),'Docker preserves the ESM boundary');
 // Public IPC registration is a wire contract, independent of internal Rust module layout.
 const main=await readFile(resolve(root,'desktop/src/main.rs'),'utf8'),handlers=main.match(/generate_handler!\[([\s\S]*?)\]/)?.[1];
 assert.ok(handlers,'Tauri command registration is present');
 const registered=new Set(handlers.split(',').map(name=>name.trim()));
 for(const path of ['desktop/adapters/optimization-client.js','desktop/adapters/saved-build-storage.ts','desktop/adapters/update.ts','web/src/application/account-client.mjs']) {
  const source=ts.createSourceFile(path,await readFile(resolve(root,path),'utf8'),ts.ScriptTarget.Latest,true);
  function visit(node) {
   if(ts.isCallExpression(node)&&/^(?:invoke|run)$|\.invoke$/.test(node.expression.getText(source))&&node.arguments[0]&&ts.isStringLiteral(node.arguments[0])) assert.ok(registered.has(node.arguments[0].text),'Unregistered frontend IPC: '+node.arguments[0].text);
   ts.forEachChild(node,visit);
  }
  visit(source);
 }
 console.log('Module boundaries: PASS (calculation/rendering/execution/Worker direction, Docker closure/context allowlist, public IPC registration)');
}
