
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BossMobBattleStatus_get_AvoidProbability(undefined *self,undefined *methodInfo)

{
  int iVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  longlong lVar5;
  int iVar6;
  undefined8 uStack_50;
  undefined8 *puStack_48;
  longlong lStack_40;
  undefined8 uStack_38;
  undefined8 *puStack_30;
  longlong lStack_28;
  
  if (DAT_7fff625e4933 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62406640);
    FUN_7fff5f47d450(&DAT_7fff6243e768);
    FUN_7fff5f47d450(&DAT_7fff6243e830);
    FUN_7fff5f47d450(0x7fff6243e8f0);
    FUN_7fff5f47d450(&DAT_7fff62400b90);
    DAT_7fff625e4933 = '\x01';
  }
  iVar6 = 0;
  if ((*(longlong *)(self + 0x30) != 0) &&
     (lVar5 = FUN_7fff607dcb60(*(longlong *)(self + 0x30),_DAT_7fff62406640), lVar5 != 0)) {
    FUN_7fff60a4b980(&uStack_50,lVar5,_DAT_7fff62400b90);
    uStack_38 = uStack_50;
    puStack_30 = puStack_48;
    lStack_28 = lStack_40;
    uStack_50 = 0;
    puStack_48 = &uStack_38;
    while (cVar3 = FUN_7fff60941650(&uStack_38,_DAT_7fff6243e830), lVar5 = lStack_28, cVar3 != '\0')
    {
      if (lStack_28 == 0) goto LAB_7fff5fdb1438;
      cVar3 = func_0x7fff5fe666a0(lStack_28,0);
      if (cVar3 == '\0') {
        if (*(longlong *)(lVar5 + 0x28) == 0) goto LAB_7fff5fdb1432;
        iVar6 = iVar6 + *(int *)(*(longlong *)(lVar5 + 0x28) + 0x50);
      }
    }
    func_0x7fff5f4d3920(&uStack_38,_DAT_7fff6243e768);
    if (*(longlong *)(self + 0x10) != 0) {
      iVar1 = *(int *)(*(longlong *)(self + 0x10) + 0x50);
      if (*(longlong *)(self + 0x20) != 0) {
        iVar4 = FUN_7fff5fdb72d0(*(longlong *)(self + 0x20),5);
        iVar4 = iVar6 + iVar1 + iVar4;
        if (*(longlong *)(self + 0x10) != 0) {
          if (*(int *)(*(longlong *)(self + 0x10) + 0x50) < 100) {
            if (*(longlong *)(self + 0x18) == 0) goto LAB_7fff5fdb142c;
            cVar3 = FUN_7fff5ffe5620(*(longlong *)(self + 0x18),0xe);
            if (cVar3 != '\0') {
              iVar4 = (int)((float)iVar4 * _DAT_7fff61b52b4c);
            }
          }
          return iVar4;
        }
      }
    }
  }
LAB_7fff5fdb142c:
  FUN_7fff5f47d660();
LAB_7fff5fdb1432:
  FUN_7fff5f47d660();
LAB_7fff5fdb1438:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar2 = (code *)swi(3);
  iVar6 = (*pcVar2)();
  return iVar6;
}

