import {DatabaseSync,backup} from 'node:sqlite';
import {parseArgs} from 'node:util';
import {open} from 'node:fs/promises';
import {resolve} from 'node:path';
import {pathToFileURL} from 'node:url';
import {createInventoryStore} from '../server/inventory-store.mjs';
import {planLegacyRecords,migrateLegacyRecords} from '../server/legacy-records.mjs';

// Apply during a maintenance window with the server stopped; online migration is outside this tool's scope.
export async function migrateDatabase(database,{apply=false,backupPath,reportPath}={}) {
  database=resolve(database);
  const reportFile=reportPath?await open(resolve(reportPath),'wx',0o600):null;
  try {
    const source=new DatabaseSync(database,{readOnly:true});
    let report;
    try {
      if(source.prepare('PRAGMA integrity_check').get().integrity_check!=='ok') throw new Error('Source database integrity check failed');
      report=planLegacyRecords(source);
      if(apply) {
        backupPath=resolve(backupPath||database+'.before-inventory-'+Date.now()+'.sqlite');
        if(backupPath===database) throw new Error('Backup must not overwrite the source database');
        const reserved=await open(backupPath,'wx',0o600);await reserved.close();
        await backup(source,backupPath);
        const verification=new DatabaseSync(backupPath,{readOnly:true});
        try {if(verification.prepare('PRAGMA integrity_check').get().integrity_check!=='ok')throw new Error('Backup integrity check failed');} finally {verification.close();}
      }
    } finally {source.close();}
    if(apply) {
      const db=new DatabaseSync(database);
      try {
        db.exec('PRAGMA foreign_keys=ON; PRAGMA busy_timeout=5000');
        if(db.prepare('PRAGMA foreign_key_check').all().length) throw new Error('Source foreign-key check failed');
        report=migrateLegacyRecords(db,createInventoryStore(db));
        if(db.prepare('PRAGMA foreign_key_check').all().length) throw new Error('Migration foreign-key check failed');
      } finally {db.close();}
    }
    const result={mode:apply?'applied':'dry-run',database,...(apply?{backup:backupPath}:{}),...report};
    if(reportFile) await reportFile.writeFile(JSON.stringify(result,null,2)+'\n');
    return result;
  } finally {await reportFile?.close();}
}
if(process.argv[1]&&import.meta.url===pathToFileURL(resolve(process.argv[1])).href) {
  try {
    const {values}=parseArgs({options:{database:{type:'string'},apply:{type:'boolean'},backup:{type:'string'},report:{type:'string'}}});
    if(!values.database) throw new Error('Use --database PATH [--apply --backup NEW_PATH] [--report NEW_PATH]. Default: dry-run; stop the server before apply.');
    const report=await migrateDatabase(values.database,{apply:values.apply,backupPath:values.backup,reportPath:values.report});
    console.log(JSON.stringify({mode:report.mode,counts:report.counts,backup:report.backup,report:values.report}));
  } catch(error) {console.error(error.message);process.exitCode=1;}
}
