// Isolated ablations of optimizations 6/7/12; never edits production Rust.
import assert from 'node:assert/strict';
import {readFile, writeFile, mkdir, copyFile} from 'node:fs/promises';
import {spawn} from 'node:child_process';
import {resolve} from 'node:path';
import {createHash} from 'node:crypto';

const root = resolve(import.meta.dirname, '..');
const dir = resolve(root, 'src-tauri/target/regression-audit');
const mode = process.argv[2];
const variants = ['current', 'no12', 'no6', 'no7'];
const fixtures = {
  basic: {},
  hp40000: {requirements:{maxHp:40000,maxMp:null,amprBeforeDual:null,normalAttackCrit:null,aspd:null}},
  magic: {patch:{mainType:'지팡이',wpnAtk:450,wpnRefine:10,wpnStab:60,strBase:50,intBase:500,agiBase:100,dexBase:200,atkType:'MAG',rangeType:'LONG',bossMdef:2500,bossMagResist:20,spellBurstLevel:10,targetWeakened:true}},
  dual: {patch:{subType:'한손검(듀얼소드)',subAtk:420,subRefine:12,subStab:70,agiBase:300,armorType:'중량옷'}},
};
await mkdir(dir, {recursive:true});
function run(command,args,{env={},input,timeout=180000}={}) {
  return new Promise((res,rej)=>{
    const child=spawn(command,args,{cwd:root,env:{...process.env,...env},stdio:['pipe','pipe','pipe']});
    let out='',err='';const timer=setTimeout(()=>{child.kill();rej(new Error('timeout '+command));},timeout);
    child.stdout.on('data',d=>out+=d);child.stderr.on('data',d=>err+=d);
    child.on('error',e=>{clearTimeout(timer);rej(e);});
    child.on('close',code=>{clearTimeout(timer);code===0?res(out):rej(new Error(`${command}: ${code}\n${err}\n${out}`));});
    child.stdin.end(input);
  });
}
function replaceOnce(text,from,to) {assert.ok(text.includes(from),'missing ablation anchor');return text.replace(from,to);}
if(mode==='build' || mode==='build-snapshot') {
  const crate=resolve(dir,'crate');await mkdir(resolve(crate,'src/bin'),{recursive:true});
  await writeFile(resolve(crate,'Cargo.toml'),'[package]\nname="d4-regression-audit"\nversion="0.0.0"\nedition="2021"\n[dependencies]\nserde={version="1",features=["derive"]}\nserde_json="1"\n');
  await copyFile(resolve(root,'src-tauri/Cargo.lock'),resolve(crate,'Cargo.lock'));
  const names=['d4_native_evaluator.rs','d4_native_solver.rs','d4_native_stats.rs','d4_parallel_runtime.rs','bin/d4_native_parallel.rs'];
  const sources=Object.fromEntries(await Promise.all(names.map(async name=>[name,await readFile(resolve(root,'src-tauri/src',name),'utf8')])));
  await writeFile(resolve(dir,'source-hashes.json'),JSON.stringify(Object.fromEntries(names.map(n=>[n,createHash('sha256').update(sources[n]).digest('hex')])),null,2));
  for(const variant of mode==='build-snapshot'?['snapshot-control']:variants) {
    let evaluator=sources['d4_native_evaluator.rs'];let bridge=sources['bin/d4_native_parallel.rs'];
    if(variant==='no12') evaluator=replaceOnce(evaluator,'    evaluate_filtered_summary(base, stats, accepts)',`    let mut accepts = accepts;
    let mut values = [0; 5];
    evaluate_filtered_summary(base, stats, |index, value| {
        values[index] = value;
        index != 4 || values.iter().enumerate().all(|(i, &v)| accepts(i, v))
    })`);
    if(variant==='no6') evaluator=replaceOnce(evaluator,'    evaluate_filtered_summary(base, stats, accepts)',`    let summary = evaluate_summary_from_lookup(base, stats)?;
    let mut accepts = accepts;
    let values = [summary.final_max_hp, summary.final_max_mp, summary.ampr_before_dual, summary.normal_attack_crit, summary.final_aspd];
    Ok(values.into_iter().enumerate().all(|(i,v)| accepts(i,v)).then_some(summary))`);
    if(variant==='no7') bridge=replaceOnce(bridge,'session.advance_parallel_slice_with_control(','session.run_parallel_slice_with_control(');
    if(variant==='snapshot-control') {
      bridge=replaceOnce(bridge,'let mut batches = 0_u64;', 'let mut batches = 0_u64;\n        let eager = std::env::var_os("D4_AUDIT_EAGER_SNAPSHOT").is_some();');
      bridge=replaceOnce(bridge,'            batches += 1;', '            if eager { std::hint::black_box(session.snapshot()); }\n            batches += 1;');
    }
    for(const name of names) await writeFile(resolve(crate,'src',name),name==='d4_native_evaluator.rs'?evaluator:name==='bin/d4_native_parallel.rs'?bridge:sources[name]);
    await run('cargo',['build','--offline','--release','--manifest-path',resolve(crate,'Cargo.toml'),'--bin','d4_native_parallel']);
    await copyFile(resolve(crate,'target/release/d4_native_parallel.exe'),resolve(dir,variant+'.exe'));
    console.log('built '+variant);
  }
} else if(mode==='prepare') {
  for(const [name,config] of Object.entries(fixtures)) {
    console.log(await run(process.execPath,['tools/benchmark-d4-native-p6.mjs'],{env:{D4_P6_EXPORT_INPUT:resolve(dir,name+'.json'),D4_P6_THREAD:'16',D4_P6_CONTEXT_PATCH:JSON.stringify(config.patch||{}),D4_P6_REQUIREMENTS:config.requirements?JSON.stringify(config.requirements):''}}));
  }
} else if(mode==='verify') {
  for(const [fixture,config] of Object.entries(fixtures)) {
    const file=resolve(dir,fixture+'-oracle.json');
    await run(process.execPath,['tools/benchmark-d4-native-p6.mjs'],{env:{D4_P6_EXPORT_INPUT:file,D4_P6_PACKAGE_LIMIT:'16',D4_P6_THREAD:'16',D4_P6_CONTEXT_PATCH:JSON.stringify(config.patch||{}),D4_P6_REQUIREMENTS:config.requirements?JSON.stringify(config.requirements):''}});
    const problem=JSON.parse(await readFile(file,'utf8'));
    for(const variant of variants) {
      const result=JSON.parse(await run(resolve(dir,variant+'.exe'),[],{input:JSON.stringify({...problem,threads:16}),env:{D4_SESSION_BENCH_MS:'30000'}}));
      assert.equal(result.status,'exact');
      assert.equal(result.score,problem.auditOracle.score);
      assert.equal(result.bestBuild?.id,problem.auditOracle.id);
    }
    console.log(`${fixture}: all four variants match JS exhaustive oracle (${16**4} combinations)`);
  }
} else if(mode==='run') {
  const repeats=Number(process.env.D4_AUDIT_REPEATS||3);
  const threadsList=(process.env.D4_AUDIT_THREADS||'8,16').split(',').map(Number);
  const fixtureNames=(process.env.D4_AUDIT_FIXTURES||Object.keys(fixtures).join(',')).split(',');
  const selected=(process.env.D4_AUDIT_VARIANTS||variants.join(',')).split(',');
  assert.ok(Number.isInteger(repeats) && repeats > 0);
  assert.ok(threadsList.every(n=>Number.isInteger(n) && n>0 && n<=64));
  assert.ok(fixtureNames.every(name=>Object.hasOwn(fixtures,name)));
  assert.ok(selected.every(name=>variants.includes(name)));
  const runs=[];const oracle=new Map();
  const report=resolve(dir,process.env.D4_AUDIT_REPORT||'measurements.json');
  for(const fixture of fixtureNames) {
    const problem=JSON.parse(await readFile(resolve(dir,fixture+'.json'),'utf8'));
    for(const threads of threadsList) for(let repeat=0;repeat<repeats;repeat++) {
      const order=repeat%2?[...selected].reverse():selected;
      for(const variant of order) {
        const inputPath=resolve(dir,'input.json'),outputPath=resolve(dir,'output.json'),errorPath=resolve(dir,'error.txt');
        await writeFile(inputPath,JSON.stringify({...problem,threads}));
        const sameBinary=process.env.D4_AUDIT_SNAPSHOT_CONTROL==='1';
        if(sameBinary) assert.ok(['current','no7'].includes(variant));
        const env={D4_SESSION_BENCH_MS:process.env.D4_AUDIT_BUDGET||'30000',D4_AUDIT_EAGER_SNAPSHOT:undefined};
        if(sameBinary && variant==='no7') env.D4_AUDIT_EAGER_SNAPSHOT='1';
        const measure=JSON.parse(await run('powershell.exe',['-NoProfile','-NonInteractive','-ExecutionPolicy','Bypass','-File',resolve(root,'tools/measure-d4-native-p6.ps1'),'-Binary',resolve(dir,(sameBinary?'snapshot-control':variant)+'.exe'),'-InputPath',inputPath,'-Output',outputPath,'-ErrorOutput',errorPath],{env}));
        const result=JSON.parse(await readFile(outputPath,'utf8'));
        assert.equal(result.status,'exact',`${fixture}/${variant} did not finish; do not compare bounded timing`);
        const key=JSON.stringify([result.score,result.bestBuild?.id,result.upperBound]);
        if(!oracle.has(fixture)) oracle.set(fixture,key);
        assert.equal(key,oracle.get(fixture),'ablation changed exact result');
        const {samples,...metrics}=measure;
        runs.push({fixture,threads,repeat:repeat+1,variant,sameBinary,packages:problem.groups.map(g=>g.packages.length),...metrics,...result});
        await writeFile(report,JSON.stringify({date:'2026-09-22',runs},null,2));
        console.log(`${fixture} ${threads} ${repeat+1} ${variant} ${result.sessionWallMs.toFixed(1)}ms score=${result.score}`);
      }
    }
  }
} else throw new Error('Use build, build-snapshot, prepare, verify, or run');
