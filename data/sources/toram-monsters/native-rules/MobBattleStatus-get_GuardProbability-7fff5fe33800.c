
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobBattleStatus_get_GuardProbability(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  longlong *plStackX_8;
  
  if (DAT_7fff625e4ce8 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62422540);
    DAT_7fff625e4ce8 = '\x01';
  }
  plStackX_8 = (longlong *)0x0;
  if (*(longlong *)(self + 0x10) != 0) {
    iVar5 = *(int *)(*(longlong *)(self + 0x10) + 0x4c);
    if (*(longlong *)(self + 0x20) != 0) {
      cVar2 = FUN_7fff5fdb76c0(*(longlong *)(self + 0x20),4,&plStackX_8,0);
      if (cVar2 != '\0') {
        if (plStackX_8 == (longlong *)0x0) goto LAB_7fff5fe3391f;
        if (((*(byte *)(*plStackX_8 + 0x130) < *(byte *)(_DAT_7fff62422540 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*plStackX_8 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7fff62422540 + 0x130) * 8) != _DAT_7fff62422540)) ||
           (plStackX_8 == (longlong *)0x0)) {
          FUN_7fff5f47c810(plStackX_8);
          pcVar1 = (code *)swi(3);
          iVar5 = (*pcVar1)();
          return iVar5;
        }
        iVar4 = MobPropertyMaster_get_ValueA((undefined *)plStackX_8,(undefined *)0x0);
        iVar5 = iVar5 + iVar4;
      }
      if (*(longlong *)(self + 0x10) != 0) {
        if (*(int *)(*(longlong *)(self + 0x10) + 0x4c) < 100) {
          if (*(longlong *)(self + 0x18) == 0) goto LAB_7fff5fe3391f;
          cVar2 = FUN_7fff5ffe5620(*(longlong *)(self + 0x18),0xe);
          if (cVar2 != '\0') {
            bVar3 = MobStatusMasterEx_CheckMultiFlag
                              (*(undefined **)(self + 0x10),(undefined *)0x4,(undefined *)0x0);
            if (bVar3 == 0) {
              iVar5 = iVar5 + -100;
            }
            else {
              iVar5 = (int)((float)iVar5 * _DAT_7fff61b52b4c);
            }
          }
        }
        iVar4 = 0;
        if (-1 < iVar5) {
          iVar4 = iVar5;
        }
        return iVar4;
      }
    }
  }
LAB_7fff5fe3391f:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  iVar5 = (*pcVar1)();
  return iVar5;
}

