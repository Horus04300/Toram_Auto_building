
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BossMobBattleStatus_get_AvoidProbability(undefined *self,undefined *methodInfo)

{
  int iVar1;
  code *pcVar2;
  undefined *puVar3;
  char cVar4;
  byte bVar5;
  int iVar6;
  longlong lVar7;
  int iVar8;
  undefined8 uStack_50;
  undefined8 *puStack_48;
  undefined *puStack_40;
  undefined8 uStack_38;
  undefined8 *puStack_30;
  undefined *puStack_28;
  
  if (DAT_7ffe9cadd1d8 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8ff610);
    FUN_7ffe9996d590(&DAT_7ffe9c937818);
    FUN_7ffe9996d590(&DAT_7ffe9c9378d8);
    FUN_7ffe9996d590(0x7ffe9c9379a0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f9b60);
    DAT_7ffe9cadd1d8 = '\x01';
  }
  iVar8 = 0;
  if ((*(longlong *)(self + 0x30) != 0) &&
     (lVar7 = FUN_7ffe9acd27a0(*(longlong *)(self + 0x30),_DAT_7ffe9c8ff610), lVar7 != 0)) {
    FUN_7ffe9af415c0(&uStack_50,lVar7,_DAT_7ffe9c8f9b60);
    uStack_38 = uStack_50;
    puStack_30 = puStack_48;
    puStack_28 = puStack_40;
    uStack_50 = 0;
    puStack_48 = &uStack_38;
    while (cVar4 = FUN_7ffe9ae37290(&uStack_38), puVar3 = puStack_28, cVar4 != '\0') {
      if (puStack_28 == (undefined *)0x0) goto LAB_7ffe9a2a65f8;
      bVar5 = MobPartsStatus_get_IsDead(puStack_28,(undefined *)0x0);
      if (bVar5 == 0) {
        if (*(longlong *)(puVar3 + 0x28) == 0) goto LAB_7ffe9a2a65f2;
        iVar8 = iVar8 + *(int *)(*(longlong *)(puVar3 + 0x28) + 0x50);
      }
    }
    func_0x7ffe999c3920(&uStack_38,_DAT_7ffe9c937818);
    if (*(longlong *)(self + 0x10) != 0) {
      iVar1 = *(int *)(*(longlong *)(self + 0x10) + 0x50);
      if (*(longlong *)(self + 0x20) != 0) {
        iVar6 = FUN_7ffe9a2ac490(*(longlong *)(self + 0x20),5);
        iVar6 = iVar8 + iVar1 + iVar6;
        if (*(longlong *)(self + 0x10) != 0) {
          if (*(int *)(*(longlong *)(self + 0x10) + 0x50) < 100) {
            if (*(longlong *)(self + 0x18) == 0) goto LAB_7ffe9a2a65ec;
            cVar4 = FUN_7ffe9a4daa60(*(longlong *)(self + 0x18),0xe);
            if (cVar4 != '\0') {
              iVar6 = (int)((float)iVar6 * _DAT_7ffe9c049b4c);
            }
          }
          return iVar6;
        }
      }
    }
  }
LAB_7ffe9a2a65ec:
  FUN_7ffe9996d7a0();
LAB_7ffe9a2a65f2:
  FUN_7ffe9996d7a0();
LAB_7ffe9a2a65f8:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar2 = (code *)swi(3);
  iVar8 = (*pcVar2)();
  return iVar8;
}

