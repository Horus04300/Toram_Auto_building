// Real Tauri/WebView2 IPC audit in isolated filesystem and browser profiles.
import assert from 'node:assert/strict';
import { spawn } from 'node:child_process';
import { mkdir, readFile, writeFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import { createRequire } from 'node:module';
const require=createRequire(import.meta.url);
if(!process.env.CODEX_PLAYWRIGHT_PATH) throw new Error('Set CODEX_PLAYWRIGHT_PATH');
const {chromium}=require(process.env.CODEX_PLAYWRIGHT_PATH);
const output=resolve('src-tauri/target/desktop-e2e',String(Date.now()));
const local=resolve(output,'local'), profile=resolve(output,'webview');
await mkdir(local,{recursive:true}); await mkdir(profile,{recursive:true});
const endpoint='http://127.0.0.1:9224';
// Never attach to an existing user process.
try { await fetch(endpoint+'/json/version'); throw new Error('CDP port 9224 is already occupied'); }
catch(e) { if(e.message.includes('occupied')) throw e; }
const executable=resolve('src-tauri/target/release/toram-online-auto-build-calculator.exe');
let child,browser,page;
const report={output,executable,checks:[],errors:[],dialogs:[]};
const delay=ms=>new Promise(r=>setTimeout(r,ms));
async function launch(){
  child=spawn(executable,[],{windowsHide:true,env:{...process.env,LOCALAPPDATA:local,WEBVIEW2_USER_DATA_FOLDER:profile,WEBVIEW2_ADDITIONAL_BROWSER_ARGUMENTS:'--remote-debugging-port=9224 --remote-debugging-address=127.0.0.1'},stdio:['ignore','pipe','pipe']});
  child.stdout.on('data',b=>console.log('APP '+b));child.stderr.on('data',b=>console.log('APP '+b));
  child.on('exit',(code,signal)=>console.log('APP EXIT '+JSON.stringify({code,signal})));
  child.on('error',e=>report.errors.push(e.message));
  for(let i=0;i<80;i++){try{const targets=await(await fetch(endpoint+'/json/list')).json();if(targets.some(t=>t.type==='page'))break;await delay(250);}catch{await delay(250);}}
  browser=await chromium.connectOverCDP(endpoint);
  page=browser.contexts()[0].pages()[0]; page.setDefaultTimeout(20000);
  page.on('pageerror',e=>report.errors.push(e.message));
  page.on('dialog',async d=>{report.dialogs.push(d.message());await d.accept();});
  await page.waitForFunction(()=>window.ToramSettingsRepository && window.ToramD4NativeClient);
}
async function stop(){
  if(page) await page.evaluate(()=>window.ToramD4ExecutionAdapter?.cancel('E2E cleanup')).catch(()=>{});
  // Closing the owned main window allows normal Tauri shutdown.
  if(child && child.exitCode===null){
    const closer=spawn('powershell.exe',['-NoProfile','-Command',`(Get-Process -Id ${child.pid}).CloseMainWindow()`],{windowsHide:true,stdio:'ignore'});
    await new Promise(r=>closer.once('exit',r));
  }
  if(child && child.exitCode===null){await Promise.race([new Promise(r=>child.once('exit',r)),delay(3000)]);if(child.exitCode===null)child.kill();}
  if(browser) await browser.close().catch(()=>{});
}
async function check(name,fn){try{report.checks.push({name,status:'PASS',detail:await fn()});}catch(e){report.checks.push({name,status:'FAIL',error:e.message});await page?.screenshot({path:resolve(output,`failure-${report.checks.length}.png`)}).catch(()=>{});}console.log(JSON.stringify(report.checks.at(-1)));}
const tab=id=>page.locator('#appTabButton-'+id).click();
const state=()=>page.evaluate(()=>window.ToramRuntimeState.get().d4.lastOptimizationResult);
try{
  await launch();
  await check('real native bridge and isolated settings directory',async()=>{
    const directory=await page.evaluate(()=>window.ToramSettingsRepository.directory());
    assert.equal(directory,resolve(local,'ToramOnlineAutoBuildCalculator'));
    assert.equal(await page.evaluate(()=>window.ToramD4NativeClient.isAvailable()),true);
    return {directory,version:await page.evaluate(()=>window.__TAURI__.app.getVersion()),hardware:await page.evaluate(()=>window.__TAURI__.core.invoke('d4_hardware_profile'))};
  });
  await check('native save duplicate overwrite load delete and disk contract',async()=>{
    await page.locator('#charLevel').fill('111');
    await page.locator('#appBuildStorageButton').click();
    await page.locator('#buildSettingName').fill('DesktopE2E');await page.locator('#buildSettingSave').click();
    await page.waitForFunction(()=>document.querySelector('#buildFileStorageStatus').textContent.includes('DesktopE2E.json 저장 완료'));
    const file=resolve(local,'ToramOnlineAutoBuildCalculator/DesktopE2E.json');
    assert.equal(JSON.parse(await readFile(file,'utf8')).build.character.level,111);
    await page.locator('#buildSettingSave').click();await page.waitForFunction(()=>document.querySelector('#buildFileStorageStatus').textContent.includes('같은 이름'));
    await page.locator('#buildFileDialogClose').click();await page.locator('#charLevel').fill('222');
    await page.locator('#appBuildStorageButton').click();await page.locator('#buildSettingList').selectOption('DesktopE2E.json');await page.locator('#buildSettingOverwrite').click();
    await page.waitForFunction(()=>document.querySelector('#buildFileStorageStatus').textContent.includes('덮어쓰기 완료'));
    assert.equal(JSON.parse(await readFile(file,'utf8')).build.character.level,222);
    await page.locator('#buildFileDialogClose').click();await page.locator('#charLevel').fill('300');
    await page.locator('#appBuildStorageButton').click();await page.locator('#buildSettingList').selectOption('DesktopE2E.json');await page.locator('#buildSettingLoad').click();
    await page.waitForFunction(()=>document.querySelector('#charLevel').value==='222');
    await page.locator('#buildSettingDelete').click();await page.waitForFunction(()=>document.querySelector('#buildFileStorageStatus').textContent.includes('삭제 완료'));
    await assert.rejects(readFile(file),{code:'ENOENT'});
    await page.locator('#buildFileDialogClose').click();
  });
  await check('application restart restores build and update preference',async()=>{
    await tab('stats-target');await page.locator('#bossDef').fill('123');await page.locator('#updateCheckOnStartup').uncheck();
    await page.locator('#appBuildStorageButton').click();await page.locator('#buildSettingName').fill('RestartE2E');await page.locator('#buildSettingSave').click();
    await page.waitForFunction(()=>document.querySelector('#buildFileStorageStatus').textContent.includes('RestartE2E.json 저장 완료'));
    const file=resolve(local,'ToramOnlineAutoBuildCalculator/RestartE2E.json'),before=await readFile(file,'utf8');
    await page.locator('#buildFileDialogClose').click();
    await page.waitForFunction(()=>JSON.parse(localStorage.getItem('toram.auto-build.application-state.v2')).lastSession.scenario.target.bossDef===123);
    await stop();await launch();
    assert.equal(await page.locator('#charLevel').inputValue(),'222');assert.equal(await page.locator('#bossDef').inputValue(),'123');assert.equal(await page.locator('#updateCheckOnStartup').isChecked(),false);
    assert.equal(await readFile(file,'utf8'),before);
  });
  await check('native pause resume unrelated edit and input invalidation',async()=>{
    await tab('results');await page.locator('#d4RunPreciseOptimization').click();
    await page.waitForFunction(()=>window.ToramD4NativeClient.isRunning());
    await page.locator('#d4OptimizationPause').click();
    await page.waitForFunction(()=>window.ToramD4NativeClient.hasContinuation()&&!window.ToramD4NativeClient.isRunning());
    const paused=await page.locator('#d4OptimizationMeta').innerText();
    assert.equal(await page.evaluate(()=>window.ToramRuntimeState.get().d4.executionStatus),'paused');
    await delay(2000);assert.equal(await page.locator('#d4OptimizationMeta').innerText(),paused);
    await page.locator('#appBuildStorageButton').click();await page.locator('#buildSettingName').fill('unrelated-name');await page.locator('#buildFileDialogClose').click();
    assert.equal(await page.evaluate(()=>window.ToramD4NativeClient.hasContinuation()),true);
    await page.locator('#d4OptimizationContinue').click();await page.waitForFunction(()=>window.ToramD4NativeClient.isRunning());
    await page.locator('#d4OptimizationPause').click();await page.waitForFunction(()=>window.ToramD4NativeClient.hasContinuation()&&!window.ToramD4NativeClient.isRunning());
    const resumed=await page.locator('#d4OptimizationMeta').innerText();
    assert.equal(await page.evaluate(()=>window.ToramRuntimeState.get().d4.executionStatus),'paused');
    const elapsed=text=>Number(text.match(/경과 ([\d.]+)초/)[1]);
    assert.ok(elapsed(resumed)>=elapsed(paused));assert.ok(elapsed(resumed)-elapsed(paused)<2,'paused wall time must not count as execution');
    await tab('stats-target');await page.locator('#bossDef').fill('124');await page.waitForFunction(()=>!window.ToramD4NativeClient.hasContinuation());
    return {paused,resumed};
  });
  await check('native cancellation',async()=>{
    await tab('results');await page.locator('#d4RunPreciseOptimization').click();await page.waitForFunction(()=>window.ToramD4NativeClient.isRunning());
    await page.locator('#d4OptimizationCancel').click();await page.waitForFunction(()=>!window.ToramD4NativeClient.isRunning());
    assert.equal(await page.evaluate(()=>window.ToramD4NativeClient.hasContinuation()),false);
  });
  await check('native exact with eight empty locked slots',async()=>{
    await tab('equipment');for(const g of ['wpn','arm','add','spc'])for(const n of [1,2])await page.locator(`#lock_${g}_${n}`).check();
    await tab('results');await page.locator('#optimizationRequirementsButton').click();
    const boxes=page.locator('#optimizationRequirementsOverlay input[type=checkbox]');for(let i=0;i<await boxes.count();i++)await boxes.nth(i).uncheck();
    await page.locator('#optimizationRequirementsApply').click();await page.locator('#d4RunPreciseOptimization').click();
    await page.waitForFunction(()=>window.ToramRuntimeState.get().d4.lastOptimizationResult?.status==='exact');
    const result=await state();assert.equal(result.engine,'rust-native');return {status:result.status,engine:result.engine,threadsUsed:result.threadsUsed,score:result.score};
  });
  await check('manual native update check reports outcome',async()=>{
    await page.locator('#updateCheck').click();
    await page.waitForFunction(()=>!document.querySelector('#updateCheck').disabled,{},{timeout:25000});
    return await page.locator('#updatePanel').innerText();
  });
  await check('existing native storage E2E runs without SKIP',async()=>{
    await tab('stats-target');
    await browser.close();
    const test=spawn(process.execPath,['tools/test-tauri-native-storage-e2e.mjs'],{windowsHide:true,env:{...process.env,TORAM_E2E_CDP:endpoint,TORAM_E2E_DIRECTORY:resolve(local,'ToramOnlineAutoBuildCalculator')},stdio:['ignore','pipe','pipe']});
    let log='';test.stdout.on('data',b=>log+=b);test.stderr.on('data',b=>log+=b);
    const exit=await new Promise(r=>test.once('exit',r));
    browser=await chromium.connectOverCDP(endpoint);page=browser.contexts()[0].pages()[0];
    assert.equal(exit,0,log);assert.ok(!log.includes('SKIP'));return log.trim();
  });
  await page.screenshot({path:resolve(output,'final.png')});
}finally{await stop();await writeFile(resolve(output,'report.json'),JSON.stringify(report,null,2));console.log('REPORT '+resolve(output,'report.json'));}
if(report.checks.some(c=>c.status==='FAIL')||report.errors.length)process.exitCode=1;
