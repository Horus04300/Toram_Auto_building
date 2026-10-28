import {resolve} from 'node:path';
import {fileURLToPath,pathToFileURL} from 'node:url';
import {syncDevelopmentCatalog,parseSyncArguments} from './project-catalog-store.mjs';
import {publishLatestProjectItems} from './convert-toram-project-items.mjs';
const root=fileURLToPath(new URL('../..',import.meta.url));
const defaultStore=resolve(root,'data/sources/toram-items/pipeline');
export function syncDevelopmentItems({store=defaultStore,output=resolve(root,'web/public/game-data/items'),...options}={}) {
  return syncDevelopmentCatalog('items',publishLatestProjectItems,{store,output,...options});
}
if(process.argv[1]&&import.meta.url===pathToFileURL(resolve(process.argv[1])).href) {
  try {const report=await syncDevelopmentItems(parseSyncArguments(process.argv.slice(2),defaultStore));console.log(JSON.stringify(report));process.exitCode=report.exitCode;}
  catch(error) {console.error(JSON.stringify({status:'failed',developmentApplied:false,error:error.message}));process.exitCode=1;}
}
