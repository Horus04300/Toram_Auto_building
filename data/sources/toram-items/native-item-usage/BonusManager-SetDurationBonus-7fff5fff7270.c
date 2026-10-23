
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BonusManager_SetDurationBonus(undefined *self,undefined *bonus,undefined *methodInfo)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  undefined8 uVar4;
  char cVar5;
  
  if (DAT_7fff625e5860 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6244c040);
    FUN_7fff5f47d450(&DAT_7fff6244c1c8);
    FUN_7fff5f47d450(&DAT_7fff6244c418);
    FUN_7fff5f47d450(&DAT_7fff6244c5a0);
    FUN_7fff5f47d450(&DAT_7fff6240edb0);
    FUN_7fff5f47d450(&DAT_7fff6240f0f0);
    DAT_7fff625e5860 = '\x01';
  }
  if ((bonus != (undefined *)0x0) && (*(int *)(bonus + 0x44) != 0)) {
    if (*(longlong *)(self + 0x30) == 0) goto LAB_7fff5fff73a1;
    cVar5 = FUN_7fff60869460(*(longlong *)(self + 0x30),*(int *)(bonus + 0x44),_DAT_7fff6244c1c8);
    lVar1 = *(longlong *)(self + 0x30);
    if (cVar5 == '\0') {
      if (lVar1 == 0) goto LAB_7fff5fff73a1;
      FUN_7fff6088cb20(lVar1,*(undefined4 *)(bonus + 0x44),bonus,_DAT_7fff6244c040);
    }
    else {
      lVar2 = *(longlong *)(self + 0x78);
      if (lVar1 == 0) goto LAB_7fff5fff73a1;
      uVar4 = FUN_7fff6087c780(lVar1,*(undefined4 *)(bonus + 0x44),_DAT_7fff6244c418);
      if (lVar2 == 0) goto LAB_7fff5fff73a1;
      FUN_7fff60ae6370(lVar2,uVar4,_DAT_7fff6240f0f0);
      if (*(longlong *)(self + 0x30) == 0) goto LAB_7fff5fff73a1;
      FUN_7fff6089f0e0(*(longlong *)(self + 0x30),*(undefined4 *)(bonus + 0x44),bonus,
                       _DAT_7fff6244c5a0);
    }
    if (*(longlong *)(self + 0x78) == 0) {
LAB_7fff5fff73a1:
      FUN_7fff5f47d660();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    FUN_7fff5f253100(*(longlong *)(self + 0x78),bonus,_DAT_7fff6240edb0);
  }
  return;
}

