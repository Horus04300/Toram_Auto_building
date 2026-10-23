
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobBattleStatus_get_AvoidProbability(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  int iVar5;
  
  if (*(longlong *)(self + 0x10) != 0) {
    iVar5 = *(int *)(*(longlong *)(self + 0x10) + 0x50);
    if (*(longlong *)(self + 0x20) != 0) {
      iVar4 = FUN_7fff5fdb72d0(*(longlong *)(self + 0x20),5);
      iVar5 = iVar5 + iVar4;
      if (*(longlong *)(self + 0x10) != 0) {
        if (*(int *)(*(longlong *)(self + 0x10) + 0x50) < 100) {
          if (*(longlong *)(self + 0x18) == 0) goto LAB_7fff5fe336e5;
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
LAB_7fff5fe336e5:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  iVar5 = (*pcVar1)();
  return iVar5;
}

