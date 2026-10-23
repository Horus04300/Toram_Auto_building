from pathlib import Path
import hashlib,json,struct
f32=lambda value:struct.unpack('<f',struct.pack('<f',value))[0]
def defense(raw,level):
    product=(raw*level+2**31)%2**32-2**31
    return int(f32(f32(product)*f32(.01)))
def hp(gauge):
    assert 0<=gauge<=255
    x=gauge*4
    a=int(f32(f32(f32(x*x)/f32(2.4))+f32(x+81)))
    b=f32(f32(f32(x)/10)+30)
    c=f32(f32(a)*b)
    q=round(float(f32(f32(gauge*gauge)/100)),2)
    assert q==gauge*gauge/100
    return int((q+50)*c)
assert defense(175,100)==175 and defense(350,104)==364
assert defense(300,104)==312 and defense(125,200)==250
assert 15+int(104/10)==25 and 30+int(200/10)==50
assert hp(25)==9780750 and hp(26)==10756951
assert hp(50)==63551250 and hp(51)==67519683
assert hp(11)==1640072
assert all(max(40,n*4)==40 for n in range(11))
assert len({hp(n) for n in range(11)})==11
assert all(hp(n)<=2147483647 for n in range(132)) and hp(132)>2147483647
for gauge in range(256): hp(gauge)
root=Path(__file__).parent
index=json.loads((root/'index.json').read_text(encoding='utf-8'))
for entry in index['files']:
    data=(root/entry['file']).read_bytes()
    assert len(data)==entry['size']
    assert hashlib.sha256(data).hexdigest()==entry['sha256']
print('PASS: float32 defense cases, 256 HP factors, gauge ambiguity/overflow, all evidence hashes')
