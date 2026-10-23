
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte FieldScriptLoader_ReadEventIndex(undefined *self,int eventIndex,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  byte bVar3;
  short sVar4;
  undefined4 uVar5;
  
  *(undefined4 *)(self + 0x2c) = 0;
  lVar1 = *(longlong *)(self + 0x20);
  uVar5 = 0xffffffff;
  if (lVar1 == 0) {
    *(undefined4 *)(self + 0x18) = 0;
    sVar4 = -1;
  }
  else {
    if (*(int *)(lVar1 + 0x18) == 0) {
      FUN_7fff5f47d650();
      pcVar2 = (code *)swi(3);
      bVar3 = (*pcVar2)();
      return bVar3;
    }
    *(uint *)(self + 0x18) = (uint)*(byte *)(lVar1 + 0x20);
    *(undefined4 *)(self + 0x2c) = 1;
    sVar4 = FUN_7fff60f8cfd0(lVar1,*(undefined4 *)(self + 0x2c),0);
    *(int *)(self + 0x2c) = *(int *)(self + 0x2c) + 2;
  }
  if (eventIndex < sVar4) {
    *(int *)(self + 0x2c) = *(int *)(self + 0x2c) + eventIndex * 4;
    if (*(longlong *)(self + 0x20) != 0) {
      uVar5 = FUN_7fff60f8d040(*(longlong *)(self + 0x20),*(undefined4 *)(self + 0x2c),0);
    }
    *(undefined4 *)(self + 0x2c) = uVar5;
    return 1;
  }
  return 0;
}

