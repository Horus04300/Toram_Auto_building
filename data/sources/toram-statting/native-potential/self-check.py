from pathlib import Path
import hashlib,json,struct
f32=lambda value:struct.unpack('<f',struct.pack('<f',value))[0]
i16=lambda value:(value+32768)%65536-32768
def div0(a,b):
    assert b>0
    return (abs(a)//b)*(-1 if a<0 else 1)
def potential(old,delta,cost=3,threshold=20,over_rate=1,tec=255):
    target=old+delta
    if delta>=0:
        lower=min(delta,-threshold-old) if old < -threshold else 0
        rest=delta-lower
        upper=min(rest,target-threshold) if target>threshold else 0
        return i16(cost*(div0(lower,over_rate)+rest-upper+2*div0(upper,over_rate)))
    upper=max(delta,threshold-old) if old>threshold else 0
    rest=delta-upper
    lower=max(rest,target+threshold) if target < -threshold else 0
    score=f32(f32(f32(div0(lower,over_rate))*f32(.5))+f32(div0(upper,over_rate)-lower+rest))
    refund=f32(f32(f32(tec)/f32(1000))+f32(.05))
    return i16(int(f32(f32(refund*score)*f32(cost))))
assert potential(0,25,cost=1)==30
assert potential(-25,50,cost=1)==55
assert potential(25,-50,cost=1)==-14
assert potential(0,-10)==-9
assert potential(0,-5)+potential(-5,-5)==-8
assert potential(0,22,cost=1,over_rate=2)==22
assert potential(-22,22,cost=1,over_rate=2)==21
assert potential(0,-22,cost=1,over_rate=2)==-6
assert potential(0,-10,tec=0)==-1
assert potential(0,5)==15 and potential(5,-5)==-4
assert i16(32768)==-32768 and div0(-3,2)==-1
for old in range(-30,31):
    for delta in range(-30,31):
        value=potential(old,delta)
        assert -32768<=value<=32767
        if delta==0:assert value==0
root=Path(__file__).parent
for entry in json.loads((root/'index.json').read_text(encoding='utf-8'))['files']:
    data=(root/entry['file']).read_bytes()
    assert len(data)==entry['size'] and hashlib.sha256(data).hexdigest()==entry['sha256']
print('PASS: 3721 transition bounds, signed threshold cases, TEC/per-step truncation, all evidence hashes')
