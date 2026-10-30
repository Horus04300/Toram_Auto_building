
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BossMobBattleStatus_get_NecessaryHit(undefined *self,undefined *methodInfo)

{
  short sVar1;
  undefined4 uVar2;
  code *pcVar3;
  longlong *plVar4;
  char cVar5;
  int iVar6;
  longlong lVar7;
  int iVar8;
  undefined8 uStack_50;
  undefined8 uStack_48;
  longlong *plStack_40;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
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
    FUN_7ffe9af415c0(&uStack_50,lVar7,_DAT_7ffe9c8f9b60);
    uStack_38 = (undefined4)uStack_50;
    uStack_34 = uStack_50._4_4_;
    uStack_30 = (undefined4)uStack_48;
    uStack_2c = uStack_48._4_4_;
    plStack_28 = plStack_40;
    uStack_50 = 0;
    uStack_48 = &uStack_38;
    while (cVar5 = FUN_7ffe9ae37290(&uStack_38,_DAT_7ffe9c9378d8), plVar4 = plStack_28,
          cVar5 != '\0') {
      if (plStack_28 == (longlong *)0x0) goto LAB_7ffe9a2a7626;
      cVar5 = func_0x7ffe9a35ba60(plStack_28,0);
      if (cVar5 == '\0') {
        lVar7 = *plVar4;
        iVar6 = (**(code **)(lVar7 + 0x178))(plVar4,*(undefined8 *)(lVar7 + 0x180));
        iVar8 = iVar8 + iVar6;
      }
    }
    AvoidBreaker_Reset((undefined *)&uStack_38,_DAT_7ffe9c937818);
    if (*(longlong *)(self + 0x10) != 0) {
      uVar2 = *(undefined4 *)(*(longlong *)(self + 0x10) + 0x38);
      sVar1 = *(short *)(self + 0x28);
      if (*(int *)(_DAT_7ffe9c949540 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      iVar6 = FUN_7ffe9bc88740(uVar2,(int)sVar1,0);
      return iVar6 + iVar8;
    }
  }
  FUN_7ffe9996d7a0();
LAB_7ffe9a2a7626:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar3 = (code *)swi(3);
  iVar8 = (*pcVar3)();
  return iVar8;
}

