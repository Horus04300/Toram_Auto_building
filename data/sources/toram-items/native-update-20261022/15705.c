
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BonusManager_SetDurationBonus(undefined *self,undefined *bonus,undefined *methodInfo)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  undefined8 uVar4;
  char cVar5;
  
  if (DAT_7ffe9cade108 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9450f0);
    FUN_7ffe9996d590(&DAT_7ffe9c945278);
    FUN_7ffe9996d590(&DAT_7ffe9c9454c0);
    FUN_7ffe9996d590(&DAT_7ffe9c945648);
    FUN_7ffe9996d590(&DAT_7ffe9c907d80);
    FUN_7ffe9996d590(&DAT_7ffe9c9080c0);
    DAT_7ffe9cade108 = '\x01';
  }
  if ((bonus != (undefined *)0x0) && (*(int *)(bonus + 0x44) != 0)) {
    if (*(longlong *)(self + 0x30) == 0) goto LAB_7ffe9a4ec7e1;
    cVar5 = FUN_7ffe9ad5f0a0(*(longlong *)(self + 0x30),*(int *)(bonus + 0x44),_DAT_7ffe9c945278);
    lVar1 = *(longlong *)(self + 0x30);
    if (cVar5 == '\0') {
      if (lVar1 == 0) goto LAB_7ffe9a4ec7e1;
      FUN_7ffe9ad82760(lVar1,*(undefined4 *)(bonus + 0x44),bonus,_DAT_7ffe9c9450f0);
    }
    else {
      lVar2 = *(longlong *)(self + 0x78);
      if (lVar1 == 0) goto LAB_7ffe9a4ec7e1;
      uVar4 = FUN_7ffe9ad723c0(lVar1,*(undefined4 *)(bonus + 0x44),_DAT_7ffe9c9454c0);
      if (lVar2 == 0) goto LAB_7ffe9a4ec7e1;
      FUN_7ffe9afdbfb0(lVar2,uVar4,_DAT_7ffe9c9080c0);
      if (*(longlong *)(self + 0x30) == 0) goto LAB_7ffe9a4ec7e1;
      FUN_7ffe9ad94d20(*(longlong *)(self + 0x30),*(undefined4 *)(bonus + 0x44),bonus,
                       _DAT_7ffe9c945648);
    }
    if (*(longlong *)(self + 0x78) == 0) {
LAB_7ffe9a4ec7e1:
      FUN_7ffe9996d7a0();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    FUN_7ffe99743100(*(longlong *)(self + 0x78),bonus,_DAT_7ffe9c907d80);
  }
  return;
}

