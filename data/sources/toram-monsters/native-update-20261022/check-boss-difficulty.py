import importlib.util
import hashlib
import json
from pathlib import Path
import re
import struct

root=Path.cwd()
base=root/'build/tmp/update-pipeline-20261022'
spec=importlib.util.spec_from_file_location('metadata',root/'tools/extraction/extract-il2cpp-item-schema.py')
module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
old_sources=json.loads((root/'assets/source-data/toram-monsters/native-schema/method-map.json').read_text())['sources']
old_metadata=module.Metadata(Path(old_sources['metadata']['path']).read_bytes())
new_metadata=module.Metadata((base/'installed-source/global-metadata.dat').read_bytes())
old_mapped=Path(old_sources['mapped_image']['path']).read_bytes()
new_mapped=(base/'snapshot/GameAssembly.mapped.bin').read_bytes()
assert hashlib.sha256(old_metadata.data).hexdigest()==old_sources['metadata']['sha256']
assert hashlib.sha256(old_mapped).hexdigest()==old_sources['mapped_image']['sha256']
new_map=json.loads((base/'new-method-map.json').read_text())
assert hashlib.sha256(new_mapped).hexdigest()==new_map['mappedSha256']
old_c=(root/'assets/source-data/toram-monsters/native-rules/Toram_Common_Rooms_BossDifficultyLevelMethods-_cctor-7fff61793e40.c').read_text()
new_c=(base/'native-review/90592.c').read_text()
def blobs(code, metadata, mapped, image_base):
    values=re.findall(r'FUN_[a-f0-9]+\(uVar4,_DAT_([a-f0-9]+),0\);',code)
    refs=metadata.records('field_refs',struct.Struct('<2i'))
    result=[]
    for ordinal,value in enumerate(values):
        address=int(value,16)
        encoded=struct.unpack_from('<Q',mapped,address-image_base)[0]
        usage=(encoded>>1)&0x1fffffff
        assert encoded>>29==4,hex(encoded)
        type_idx,field_idx=refs[usage]
        types=[t for t in metadata.types if t[2]==type_idx]
        assert len(types)==1,(type_idx,types)
        field=types[0][8]+field_idx
        name=metadata.string(metadata.fields[field][0])
        assert field in metadata.defaults,field
        default_type,data_index=metadata.defaults[field]
        data_offset=metadata.tables['default_data']['offset']+data_index
        raw=metadata.data[data_offset:data_offset+20]
        result.append({'slot':ordinal*8,'address':hex(address),'encodedUsage':hex(encoded),
                       'fieldReferenceIndex':usage,'fieldDefinitionIndex':field,'fieldName':name,
                       'metadataOffset':data_offset,'rawHex':raw.hex(),
                       'values':struct.unpack('<5i' if ordinal in [3,9] else '<5f',raw)})
    assert len(result)==10,len(result)
    return result
old=blobs(old_c,old_metadata,old_mapped,int('7fff5f250000',16))
new=blobs(new_c,new_metadata,new_mapped,int('7ffe99740000',16))
report={'old':old,'new':new,'allSame':all(a['rawHex']==b['rawHex'] for a,b in zip(old,new)),
        'oldMetadataSha256':hashlib.sha256(old_metadata.data).hexdigest(),
        'newMetadataSha256':hashlib.sha256(new_metadata.data).hexdigest(),
        'oldMappedSha256':hashlib.sha256(old_mapped).hexdigest(),
        'newMappedSha256':hashlib.sha256(new_mapped).hexdigest(),
        'notes':['Metadata usages decoded as FieldInfo (type 4); field_refs -> exact declaring type -> field default_data 20 bytes.',
                 'Slots 0x18 and 0x48 are int32 arrays; other slots are float32 arrays; all arrays have 5 elements in constructor.']}
(root/'assets/source-data/toram-monsters/native-update-20261022/difficulty-tables.json').write_text(json.dumps(report,indent=2)+'\n')
print(json.dumps({'allSame':report['allSame'],'tables':[{'slot':r['slot'],'values':r['values'],'offset':r['metadataOffset']} for r in new]},indent=2))
