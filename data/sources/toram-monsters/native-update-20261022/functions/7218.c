
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BossMobBattleStatus_get_NecessaryHit(undefined *self,undefined *methodInfo)

{
  short sVar1;
  code *pcVar2;
  longlong *plVar3;
  char cVar4;
  byte bVar5;
  int iVar6;
  longlong lVar7;
  int iVar8;
  undefined8 uStack_50;
  undefined8 *puStack_48;
  longlong *plStack_40;
  undefined8 uStack_38;
  undefined8 *puStack_30;
  longlong *plStack_28;
  
  if (DAT_7ffe9cadd1d2 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949540);
    FUN_7ffe9996d590(&DAT_7ffe9c8ff610);
    FUN_7ffe9996d590(&DAT_7ffe9c937818);
    FUN_7ffe9996d590(&DAT_7ffe9c9378d8);
    FUN_7ffe9996d590(0x7ffe9c9379a0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f9b60);
    DAT_7ffe9cadd1d2 = '\x01';
  }
  iVar8 = 0;
  if ((*(longlong *)(self + 0x30) != 0) &&
     (lVar7 = FUN_7ffe9acd27a0(*(longlong *)(self + 0x30),_DAT_7ffe9c8ff610), lVar7 != 0)) {
    FUN_7ffe9af415c0(&uStack_50,lVar7);
    uStack_38 = uStack_50;
    puStack_30 = puStack_48;
    plStack_28 = plStack_40;
    uStack_50 = 0;
    puStack_48 = &uStack_38;
    while (cVar4 = FUN_7ffe9ae37290(&uStack_38), plVar3 = plStack_28, cVar4 != '\0') {
      if (plStack_28 == (longlong *)0x0) goto LAB_7ffe9a2a7626;
      bVar5 = MobPartsStatus_get_IsDead((undefined *)plStack_28,(undefined *)0x0);
      if (bVar5 == 0) {
        lVar7 = *plVar3;
        iVar6 = (**(code **)(lVar7 + 0x178))(plVar3,*(undefined8 *)(lVar7 + 0x180));
        iVar8 = iVar8 + iVar6;
      }
    }
    func_0x7ffe999c3920(&uStack_38,_DAT_7ffe9c937818);
    if (*(longlong *)(self + 0x10) != 0) {
      iVar6 = *(int *)(*(longlong *)(self + 0x10) + 0x38);
      sVar1 = *(short *)(self + 0x28);
      if (*(int *)(_DAT_7ffe9c949540 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      iVar6 = Toram_Common_Rooms_BossDifficultyLevelMethods_GetStatusRate
                        (iVar6,(int)sVar1,(undefined *)0x0);
      return iVar6 + iVar8;
    }
  }
  FUN_7ffe9996d7a0();
LAB_7ffe9a2a7626:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar2 = (code *)swi(3);
  iVar8 = (*pcVar2)();
  return iVar8;
}

