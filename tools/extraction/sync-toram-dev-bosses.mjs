import {resolve} from 'node:path';
import {fileURLToPath,pathToFileURL} from 'node:url';
import {syncDevelopmentCatalog,parseSyncArguments} from './project-catalog-store.mjs';
import {publishLatestProjectBosses} from './convert-toram-project-bosses.mjs';
const root=fileURLToPath(new URL('../..',import.meta.url));
const defaultStore=resolve(root,'data/sources/toram-monsters/pipeline');
export function syncDevelopmentBosses({store=defaultStore,output=resolve(root,'web/public/game-data/bosses'),...options}={}) {
  return syncDevelopmentCatalog('bosses',publishLatestProjectBosses,{store,output,...options});
}
if(process.argv[1]&&import.meta.url===pathToFileURL(resolve(process.argv[1])).href) {
  try {const report=await syncDevelopmentBosses(parseSyncArguments(process.argv.slice(2),defaultStore));console.log(JSON.stringify(report));process.exitCode=report.exitCode;}
  catch(error) {console.error(JSON.stringify({status:'failed',developmentApplied:false,error:error.message}));process.exitCode=1;}
}
