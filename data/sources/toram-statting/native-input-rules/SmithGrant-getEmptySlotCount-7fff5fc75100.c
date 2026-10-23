
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SmithGrant_getEmptySlotCount(undefined *self,undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  undefined8 uVar7;
  
  if (DAT_7fff625e4222 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62409048);
    FUN_7fff5f47d450(&DAT_7fff62432448);
    FUN_7fff5f47d450(&DAT_7fff624539e0);
    FUN_7fff5f47d450(&DAT_7fff62416710);
    FUN_7fff5f47d450(&DAT_7fff6242a088);
    DAT_7fff625e4222 = '\x01';
  }
  iVar3 = SmithGrant_getUsableSlotCount(self,(undefined *)0x0);
  if (*(longlong *)(self + 0x120) != 0) {
    uVar7 = *(undefined8 *)(*(longlong *)(self + 0x120) + 0x10);
    if (*(int *)(_DAT_7fff6242a088 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    lVar6 = *(longlong *)(*(longlong *)(_DAT_7fff6242a088 + 0xb8) + 0x30);
    if (lVar6 == 0) {
      if (*(int *)(_DAT_7fff6242a088 + 0xe0) == 0) {
        func_0x7fff5f47d6f0();
      }
      uVar1 = **(undefined8 **)(_DAT_7fff6242a088 + 0xb8);
      lVar6 = func_0x7fff5f44ff00(_DAT_7fff624539e0);
      FUN_7fff60a1d7e0(lVar6,uVar1,_DAT_7fff62416710,0);
      *(longlong *)(*(longlong *)(_DAT_7fff6242a088 + 0xb8) + 0x30) = lVar6;
      thunk_FUN_7fff5f491fd0();
    }
    uVar7 = FUN_7fff6069d430(uVar7,lVar6,_DAT_7fff62432448);
    iVar4 = FUN_7fff6068aa20(uVar7,_DAT_7fff62409048);
    iVar5 = 0;
    if (-1 < iVar3 - iVar4) {
      iVar5 = iVar3 - iVar4;
    }
    return iVar5;
  }
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  iVar3 = (*pcVar2)();
  return iVar3;
}

