
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte FieldScriptLoader_ReadByte(undefined *self,undefined *methodInfo)

{
  uint uVar1;
  longlong lVar2;
  code *pcVar3;
  byte bVar4;
  
  lVar2 = *(longlong *)(self + 0x20);
  if (lVar2 == 0) {
    return 0;
  }
  uVar1 = *(uint *)(self + 0x2c);
  if (uVar1 < *(uint *)(lVar2 + 0x18)) {
    bVar4 = *(byte *)((longlong)(int)uVar1 + 0x20 + lVar2);
    *(uint *)(self + 0x2c) = uVar1 + 1;
    return bVar4;
  }
  FUN_7ffe9996d790();
  pcVar3 = (code *)swi(3);
  bVar4 = (*pcVar3)();
  return bVar4;
}

