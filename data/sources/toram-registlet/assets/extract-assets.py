"""Extract retained releaseC Registlet bytes; no game/process/network access."""
import argparse,hashlib,json,runpy,sys,struct
from pathlib import Path

ROOT=Path(__file__).resolve().parents[4]
OUT=Path(__file__).resolve().parent
sys.path.insert(0,str(ROOT/'build/tmp/toram-item-extraction/python-deps'))
import UnityPy
game=runpy.run_path(str(ROOT/'tools/extraction/extract-toram-item-assets.py'))
loc=runpy.run_path(str(ROOT/'tools/extraction/extract-toram-localizations.py'))
ref=runpy.run_path(str(ROOT/'tools/extraction/extract-toram-item-reference-texts.py'))
CHECK=False

def parse_master(decoded):
 version,count=struct.unpack_from('<ih',decoded)
 if version!=1 or count<0 or len(decoded)!=6+count*8: raise ValueError('Master version/count/EOF mismatch')
 rows=[{'decodedOffset':6+i*8,'registletId':a,'levelCap':b,'enhancePowder':c} for i,(a,b,c) in enumerate(struct.iter_unpack('<hhi',decoded[6:]))]
 if len({r['registletId'] for r in rows})!=count: raise ValueError('Duplicate Registlet master ID')
 if any(r['registletId']<0 or r['levelCap']<1 or r['enhancePowder']<0 for r in rows): raise ValueError('Invalid Registlet master values')
 return {'version':version,'count':count,'rows':rows}

def ident(path,data=None):
 data=path.read_bytes() if data is None else data
 return {'file':path.relative_to(ROOT).as_posix(),'bytes':len(data),'sha256':hashlib.sha256(data).hexdigest()}

def write(path,data):
 if CHECK:
  if not path.exists() or path.read_bytes()!=data: raise ValueError('Retained extraction differs: '+str(path))
  return
 path.parent.mkdir(parents=True,exist_ok=True)
 path.write_bytes(data)

def main():
 source=ROOT/'data/sources/toram-items/pipeline/releaseC/snapshots/e99f6b32-e4542534930d404783ff8219d089e6ff/source'
 assert ident(source/'manifest.bytes')['sha256']=='32263a7b5f34a7259985f2c1f69db2bf1a6100b05cd62e0a79bd5f189a82ff54','Unreviewed manifest'
 manifest=loc['parse_manifest']((source/'manifest.bytes').read_bytes())
 sources=[]
 master_ids=None
 text_sets={}
 for bundle_name in ['BynaryData']+['GameScene_'+l for l in ['cnt','idn','jp','kr','th','us']]:
  asset_name='BynaryData' if bundle_name=='BynaryData' else 'Localize/'+bundle_name.split('_')[1]+'/'+bundle_name
  revision=loc['single_asset'](manifest,asset_name)
  bundle=source/(bundle_name+'.unity3d')
  env=UnityPy.load(bundle.read_bytes())
  desired=['RegistletMaster'] if bundle_name=='BynaryData' else ['Registlet_'+bundle_name.split('_')[1], 'System_'+bundle_name.split('_')[1]]
  found=[]
  for obj in env.objects:
   if obj.type.name!='TextAsset': continue
   asset=obj.parse_as_object()
   if asset.m_Name not in desired: continue
   raw=asset.m_Script.encode('utf-8','surrogateescape')
   decoded=game['decode'](raw,int(revision['cacheKey'],16))
   raw_path=OUT/(asset.m_Name+'.raw.bin'); decoded_path=OUT/(asset.m_Name+'.decoded.bin')
   # System is large; retain selected original rows plus source hashes and offsets.
   entry={'name':asset.m_Name,'pathId':obj.path_id,'raw':ident(raw_path,raw),'decoded':ident(decoded_path,decoded)}
   if asset.m_Name.startswith('System_'):
    rows=ref['parse'](decoded,False,game['Reader'])
    selected=[r for r in rows if any(t in (r['key']+' '+r['text']).lower() for t in ['registlet','treasurehunt','stoodie','stoodle','studie','젬 카트리지','스투디','분말'])]
    path=OUT/(asset.m_Name+'.selected.json')
    write(path,(json.dumps(selected,ensure_ascii=False,indent=2)+'\n').encode())
    entry.update({'allBytesConsumed':True,'totalRows':len(rows),'selectedRows':len(selected),'selectedFile':ident(path),'rawRetained':False,'decodedRetained':False})
   else:
    write(raw_path,raw);write(decoded_path,decoded)
    entry.update({'rawRetained':True,'decodedRetained':True})
    if asset.m_Name.startswith('Registlet_'):
     rows=[{'registletId':r['skillId'],**{k:v for k,v in r.items() if k!='skillId'}} for r in ref['parse'](decoded,True,game['Reader'])]
     assert {r['kind'] for r in rows}=={0,1,2}
     assert all({r['registletId'] for r in rows if r['kind']==kind}==master_ids for kind in [0,1])
     assert {r['registletId'] for r in rows if r['kind']==2}<=master_ids
     text_sets[asset.m_Name]=rows
     path=OUT/(asset.m_Name+'.parsed.json')
     write(path,(json.dumps(rows,ensure_ascii=False,indent=2)+'\n').encode())
     entry.update({'parsed':ident(path),'rows':len(rows),'allBytesConsumed':True,'layout':'int32 count; repeated int32 ID, byte kind (0=name,1=description,2=BaseValue as integer text), BinaryReader UTF-8 string'})
    else:
     parsed=parse_master(decoded)
     master_ids={r['registletId'] for r in parsed['rows']}
     path=OUT/(asset.m_Name+'.structural.json')
     write(path,(json.dumps(parsed,ensure_ascii=False,indent=2)+'\n').encode())
     entry.update({'parsed':ident(path),'rows':parsed['count'],'allBytesConsumed':True,'layout':'int32 version; int16 count; repeated int16 Id, int16 LevelCap, int32 EnhancePowder'})
   found.append(entry)
  assert len(found)==len(desired),(bundle_name,desired,found)
  sources.append({'bundle':ident(bundle),'manifestAsset':asset_name,'revision':revision,'textAssets':found})
 native=ROOT/'data/sources/toram-registlet/native'
 native_sources=[ident(native/(str(i)+'.c')) for i in [20077,20079,20081,20083,20085,46486,46493,65950,65962]]
 baseline={r['registletId']:r['text'] for r in text_sets['Registlet_kr'] if r['kind']==2}
 assert all({r['registletId']:r['text'] for r in rows if r['kind']==2}==baseline for rows in text_sets.values()),'Locale BaseValue mismatch'
 report={'schemaVersion':1,'authority':'retained-public-static-game-assets-and-native-loader','application':'releaseC','manifest':ident(source/'manifest.bytes'),'sources':sources,'nativeSchemaEvidence':native_sources,'verification':{'masterIds':len(master_ids),'localeNamesAndDescriptionsMatchMaster':True,'baseValuesIdenticalAcrossSixLocales':True,'baseValueRows':len(baseline)},'finalUiObserved':False,'activeServerObserved':False}
 write(OUT/'manifest.json',(json.dumps(report,ensure_ascii=False,indent=2)+'\n').encode())
 print(json.dumps({'check':CHECK,'bundles':len(sources),'assets':sum(len(s['textAssets']) for s in sources)},ensure_ascii=False))

if __name__=='__main__':
 parser=argparse.ArgumentParser(description=__doc__)
 parser.add_argument('--check',action='store_true',help='Compare all retained outputs without writing')
 parser.add_argument('--self-test',action='store_true',help='Check parser count/EOF/duplicates and invalid values')
 args=parser.parse_args();CHECK=args.check
 if args.self_test:
  sample=struct.pack('<ihhhi',1,1,12,30,50)
  assert parse_master(sample)['rows']==[{'decodedOffset':6,'registletId':12,'levelCap':30,'enhancePowder':50}]
  for bad in [sample[:-1],sample+b'\0',struct.pack('<ih',2,0),struct.pack('<ihhhi',1,1,12,0,50),struct.pack('<ih',1,2)+sample[6:]*2]:
   try: parse_master(bad)
   except (ValueError,struct.error): pass
   else: raise AssertionError('Malformed master accepted')
  print('PASS Registlet assets parser: version/count/EOF/duplicate IDs/invalid LevelCap')
 else: main()
