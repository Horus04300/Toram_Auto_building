import {isDeepStrictEqual} from 'node:util';
import {captureObject,sections} from '../web/src/application/inventory-objects.mjs';
import {validateBuild,validateScenario} from '../web/src/application/build-values.mjs';
import {inventoryRules as rules} from './inventory-rules.mjs';
import {validateInventoryInput} from './inventory-store.mjs';

const buildKeys=['character','equipment','skillLevels','activeBuffs','externalOptions','myRoomFood','guildFoodBuff','consumableBuffs','combo'];
export const RECORD_KINDS=new Set(['builds','items','favorites']);
const requireValue=(value,message)=>{if(!value)throw new Error(message);};

// Old empty slot arrays mean empty slots, not unknown crystas. Keep their wire shape in metadata.
function normalizeEquipment(slot,piece,metadata) {
  const value=structuredClone(piece);
  for(const [key,empty] of [['crystas',''],['lockedCrystaSlots',false]]) if(slot!=='subWeapon'&&Array.isArray(value?.[key])&&value[key].length===0) {
    (metadata.emptySlots||=[]).push(slot+'.'+key);value[key]=[empty,empty];
  }
  return value;
}
function wireEquipment(slot,piece,metadata) {
  const value=structuredClone(piece);
  for(const key of ['crystas','lockedCrystaSlots']) if(metadata.emptySlots?.includes(slot+'.'+key)&&value[key].every(item=>key==='crystas'?item==='':item===false)) value[key]=[];
  return value;
}

export function legacyPayload(record,metadata={}) {
  if(record.type==='equipment') return {...structuredClone(metadata.header||{schema:'toram.account-item.v1'}),slot:record.data.slot,equipment:wireEquipment(record.data.slot,record.data.equipment,metadata)};
  requireValue(record.type==='build','This inventory type has no legacy record representation.');
  const {values}=sections(record);
  requireValue(['status','equipment','skills','consumables','combos','context'].every(key=>Object.hasOwn(values,key)),'Partial builds stay in inventory; a legacy build requires all sections.');
  requireValue(values.combos.length<=1&&Object.values(values.equipment).every(Boolean)&&Object.values(values.skills).every(Boolean),'This build cannot be represented by the legacy saved-build format.');
  const {scenario,...context}=values.context;
  const build={...structuredClone(metadata.buildExtras||{}),character:values.status,
    equipment:Object.fromEntries(Object.entries(values.equipment).map(([slot,piece])=>[slot,wireEquipment(slot,piece,metadata)])),
    skillLevels:Object.fromEntries(Object.entries(values.skills).map(([id,item])=>[id,item.levels])),
    activeBuffs:Object.assign({},...Object.values(values.skills).map(item=>item.activeBuffs)),
    ...context,combo:values.combos[0]?.steps||[]};
  if(metadata.scroll!==undefined) build.skillLevels.Scroll=structuredClone(metadata.scroll);
  const consumables=Object.values(values.consumables).filter(Boolean);
  if(!metadata.omitConsumables||consumables.length) build.consumableBuffs=consumables;
  return {...structuredClone(metadata.header||{format:'toram-auto-build-document',schemaVersion:2,documentType:'saved-build',name:record.name,createdAt:record.createdAt,updatedAt:record.updatedAt}),build,scenario};
}

export function legacyToInventory({kind,name,data}) {
  requireValue(RECORD_KINDS.has(kind)&&data&&typeof data==='object','Unsupported account record.');
  let object,metadata={};
  if(kind==='builds') {
    requireValue(data.format==='toram-auto-build-document'&&data.schemaVersion===2&&data.documentType==='saved-build'&&['name','createdAt','updatedAt'].every(key=>typeof data[key]==='string'),'This legacy build needs manual version review.');
    const {build:original,scenario,...header}=structuredClone(data),build=structuredClone(original);
    metadata.header=header;
    metadata.buildExtras=Object.fromEntries(Object.entries(build).filter(([key])=>!buildKeys.includes(key)));
    metadata.omitConsumables=!Object.hasOwn(build,'consumableBuffs');
    if(Object.hasOwn(build.skillLevels,'Scroll')) {
      requireValue(Object.values(build.skillLevels.Scroll).every(value=>value===0),'Nonempty legacy Scroll investment needs review.');metadata.scroll=build.skillLevels.Scroll;
    }
    build.equipment=Object.fromEntries(Object.entries(build.equipment).map(([slot,piece])=>[slot,normalizeEquipment(slot,piece,metadata)]));
    validateBuild(build,rules);validateScenario(scenario);
    object={type:'build',schemaVersion:1,name,data:captureObject('build',{build,scenario})};
  } else {
    requireValue(data.schema==='toram.account-item.v1','Unsupported legacy item schema.');
    const {equipment,...header}=structuredClone(data);metadata.header=header;
    const piece=normalizeEquipment(data.slot,equipment,metadata);
    requireValue(kind!=='favorites'||piece.catalogItem,'Favorites require a pinned game item.');
    object={type:'equipment',schemaVersion:1,name,data:{slot:data.slot,equipment:piece}};
  }
  validateInventoryInput(object);
  requireValue(isDeepStrictEqual(legacyPayload(object,metadata),data),'Record is not losslessly representable; preserve it for review.');
  return {object,metadata};
}
