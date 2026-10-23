
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BossMobBattleStatus_get_GuardProbability(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  longlong lVar4;
  int iVar5;
  longlong *plStackX_20;
  undefined8 uStack_60;
  undefined8 *puStack_58;
  longlong lStack_50;
  undefined8 uStack_48;
  undefined8 *puStack_40;
  longlong lStack_38;
  
  if (DAT_7fff625e4932 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62406640);
    FUN_7fff5f47d450(&DAT_7fff6243e768);
    FUN_7fff5f47d450(&DAT_7fff6243e830);
    FUN_7fff5f47d450(0x7fff6243e8f0);
    FUN_7fff5f47d450(&DAT_7fff62422540);
    FUN_7fff5f47d450(&DAT_7fff62400b90);
    DAT_7fff625e4932 = '\x01';
  }
  iVar5 = 0;
  plStackX_20 = (longlong *)0x0;
  if ((*(longlong *)(self + 0x30) != 0) &&
     (lVar4 = FUN_7fff607dcb60(*(longlong *)(self + 0x30),_DAT_7fff62406640), lVar4 != 0)) {
    FUN_7fff60a4b980(&uStack_60,lVar4,_DAT_7fff62400b90);
    uStack_48 = uStack_60;
    puStack_40 = puStack_58;
    lStack_38 = lStack_50;
    uStack_60 = 0;
    puStack_58 = &uStack_48;
    while (cVar2 = FUN_7fff60941650(&uStack_48,_DAT_7fff6243e830), lVar4 = lStack_38, cVar2 != '\0')
    {
      if (lStack_38 == 0) goto LAB_7fff5fdb1d58;
      cVar2 = func_0x7fff5fe666a0(lStack_38,0);
      if (cVar2 == '\0') {
        if (*(longlong *)(lVar4 + 0x28) == 0) goto LAB_7fff5fdb1d52;
        iVar5 = iVar5 + *(int *)(*(longlong *)(lVar4 + 0x28) + 0x4c);
      }
    }
    func_0x7fff5f4d3920(&uStack_48,_DAT_7fff6243e768);
    if (*(longlong *)(self + 0x10) != 0) {
      iVar5 = *(int *)(*(longlong *)(self + 0x10) + 0x4c) + iVar5;
      lVar4 = *(longlong *)(self + 0x20);
      if (lVar4 != 0) {
        if (DAT_7fff625e4941 == '\0') {
          FUN_7fff5f47d450(&DAT_7fff62430518);
          DAT_7fff625e4941 = '\x01';
        }
        lVar4 = *(longlong *)(lVar4 + 0x10);
        if (lVar4 != 0) {
          cVar2 = FUN_7fff60898a30(lVar4,4,&plStackX_20,_DAT_7fff62430518);
          if (cVar2 != '\0') {
            if (plStackX_20 == (longlong *)0x0) goto LAB_7fff5fdb1d4c;
            if (((*(byte *)(*plStackX_20 + 0x130) < *(byte *)(_DAT_7fff62422540 + 0x130)) ||
                (*(longlong *)
                  (*(longlong *)(*plStackX_20 + 200) + -8 +
                  (ulonglong)*(byte *)(_DAT_7fff62422540 + 0x130) * 8) != _DAT_7fff62422540)) ||
               (plStackX_20 == (longlong *)0x0)) {
              FUN_7fff5f47c810(plStackX_20);
              pcVar1 = (code *)swi(3);
              iVar5 = (*pcVar1)();
              return iVar5;
            }
            iVar3 = MobPropertyMaster_get_ValueA((undefined *)plStackX_20,(undefined *)0x0);
            iVar5 = iVar5 + iVar3;
          }
          if (*(longlong *)(self + 0x10) != 0) {
            if (*(int *)(*(longlong *)(self + 0x10) + 0x4c) < 100) {
              if (*(longlong *)(self + 0x18) == 0) goto LAB_7fff5fdb1d4c;
              cVar2 = FUN_7fff5ffe5620(*(longlong *)(self + 0x18),0xe);
              if (cVar2 != '\0') {
                iVar5 = (int)((float)iVar5 * _DAT_7fff61b52b4c);
              }
            }
            return iVar5;
          }
        }
      }
    }
  }
LAB_7fff5fdb1d4c:
  FUN_7fff5f47d660();
LAB_7fff5fdb1d52:
  FUN_7fff5f47d660();
LAB_7fff5fdb1d58:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar1 = (code *)swi(3);
  iVar5 = (*pcVar1)();
  return iVar5;
}

