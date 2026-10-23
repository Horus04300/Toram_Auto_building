
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BossMobBattleStatus_get_GuardProbability(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  undefined *puVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  longlong lVar6;
  int iVar7;
  longlong *plStackX_20;
  undefined8 uStack_60;
  undefined8 *puStack_58;
  undefined *puStack_50;
  undefined8 uStack_48;
  undefined8 *puStack_40;
  undefined *puStack_38;
  
  if (DAT_7ffe9cadd1d7 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8ff610);
    FUN_7ffe9996d590(&DAT_7ffe9c937818);
    FUN_7ffe9996d590(&DAT_7ffe9c9378d8);
    FUN_7ffe9996d590(0x7ffe9c9379a0);
    FUN_7ffe9996d590(&DAT_7ffe9c91aa80);
    FUN_7ffe9996d590(&DAT_7ffe9c8f9b60);
    DAT_7ffe9cadd1d7 = '\x01';
  }
  iVar7 = 0;
  plStackX_20 = (longlong *)0x0;
  if ((*(longlong *)(self + 0x30) != 0) &&
     (lVar6 = FUN_7ffe9acd27a0(*(longlong *)(self + 0x30),_DAT_7ffe9c8ff610), lVar6 != 0)) {
    FUN_7ffe9af415c0(&uStack_60,lVar6,_DAT_7ffe9c8f9b60);
    uStack_48 = uStack_60;
    puStack_40 = puStack_58;
    puStack_38 = puStack_50;
    uStack_60 = 0;
    puStack_58 = &uStack_48;
    while (cVar3 = FUN_7ffe9ae37290(&uStack_48), puVar2 = puStack_38, cVar3 != '\0') {
      if (puStack_38 == (undefined *)0x0) goto LAB_7ffe9a2a6f18;
      bVar4 = MobPartsStatus_get_IsDead(puStack_38,(undefined *)0x0);
      if (bVar4 == 0) {
        if (*(longlong *)(puVar2 + 0x28) == 0) goto LAB_7ffe9a2a6f12;
        iVar7 = iVar7 + *(int *)(*(longlong *)(puVar2 + 0x28) + 0x4c);
      }
    }
    func_0x7ffe999c3920(&uStack_48,_DAT_7ffe9c937818);
    if (*(longlong *)(self + 0x10) != 0) {
      iVar7 = *(int *)(*(longlong *)(self + 0x10) + 0x4c) + iVar7;
      lVar6 = *(longlong *)(self + 0x20);
      if (lVar6 != 0) {
        if (DAT_7ffe9cadd1e6 == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c929598);
          DAT_7ffe9cadd1e6 = '\x01';
        }
        lVar6 = *(longlong *)(lVar6 + 0x10);
        if (lVar6 != 0) {
          cVar3 = FUN_7ffe9ad8e670(lVar6,4,&plStackX_20,_DAT_7ffe9c929598);
          if (cVar3 != '\0') {
            if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a2a6f0c;
            if (((*(byte *)(*plStackX_20 + 0x130) < *(byte *)(_DAT_7ffe9c91aa80 + 0x130)) ||
                (*(longlong *)
                  (*(longlong *)(*plStackX_20 + 200) + -8 +
                  (ulonglong)*(byte *)(_DAT_7ffe9c91aa80 + 0x130) * 8) != _DAT_7ffe9c91aa80)) ||
               (plStackX_20 == (longlong *)0x0)) {
              FUN_7ffe9996c950(plStackX_20);
              pcVar1 = (code *)swi(3);
              iVar7 = (*pcVar1)();
              return iVar7;
            }
            iVar5 = FUN_7ffe9a2e3390(plStackX_20,0);
            iVar7 = iVar7 + iVar5;
          }
          if (*(longlong *)(self + 0x10) != 0) {
            if (*(int *)(*(longlong *)(self + 0x10) + 0x4c) < 100) {
              if (*(longlong *)(self + 0x18) == 0) goto LAB_7ffe9a2a6f0c;
              cVar3 = FUN_7ffe9a4daa60(*(longlong *)(self + 0x18),0xe);
              if (cVar3 != '\0') {
                iVar7 = (int)((float)iVar7 * _DAT_7ffe9c049b4c);
              }
            }
            return iVar7;
          }
        }
      }
    }
  }
LAB_7ffe9a2a6f0c:
  FUN_7ffe9996d7a0();
LAB_7ffe9a2a6f12:
  FUN_7ffe9996d7a0();
LAB_7ffe9a2a6f18:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar1 = (code *)swi(3);
  iVar7 = (*pcVar1)();
  return iVar7;
}

