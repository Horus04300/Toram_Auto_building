
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BossMobBattleStatus_get_NecessaryHit(undefined *self,undefined *methodInfo)

{
  short sVar1;
  code *pcVar2;
  longlong *plVar3;
  char cVar4;
  int iVar5;
  longlong lVar6;
  int iVar7;
  undefined8 uStack_50;
  undefined8 uStack_48;
  longlong *plStack_40;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  longlong *plStack_28;
  
  if (DAT_7fff625e492d == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62450e80);
    FUN_7fff5f47d450(&DAT_7fff62406640);
    FUN_7fff5f47d450(&DAT_7fff6243e768);
    FUN_7fff5f47d450(&DAT_7fff6243e830);
    FUN_7fff5f47d450(0x7fff6243e8f0);
    FUN_7fff5f47d450(&DAT_7fff62400b90);
    DAT_7fff625e492d = '\x01';
  }
  iVar7 = 0;
  if ((*(longlong *)(self + 0x30) != 0) &&
     (lVar6 = FUN_7fff607dcb60(*(longlong *)(self + 0x30),_DAT_7fff62406640), lVar6 != 0)) {
    FUN_7fff60a4b980(&uStack_50,lVar6);
    uStack_38 = (undefined4)uStack_50;
    uStack_34 = uStack_50._4_4_;
    uStack_30 = (undefined4)uStack_48;
    uStack_2c = uStack_48._4_4_;
    plStack_28 = plStack_40;
    uStack_50 = 0;
    uStack_48 = &uStack_38;
    while (cVar4 = FUN_7fff60941650(&uStack_38,_DAT_7fff6243e830), plVar3 = plStack_28,
          cVar4 != '\0') {
      if (plStack_28 == (longlong *)0x0) goto LAB_7fff5fdb2466;
      cVar4 = func_0x7fff5fe666a0(plStack_28,0);
      if (cVar4 == '\0') {
        lVar6 = *plVar3;
        iVar5 = (**(code **)(lVar6 + 0x178))(plVar3,*(undefined8 *)(lVar6 + 0x180));
        iVar7 = iVar7 + iVar5;
      }
    }
    func_0x7fff5f4d3920(&uStack_38,_DAT_7fff6243e768);
    if (*(longlong *)(self + 0x10) != 0) {
      iVar5 = *(int *)(*(longlong *)(self + 0x10) + 0x38);
      sVar1 = *(short *)(self + 0x28);
      if (*(int *)(_DAT_7fff62450e80 + 0xe0) == 0) {
        func_0x7fff5f47d6f0();
      }
      iVar5 = Toram_Common_Rooms_BossDifficultyLevelMethods_GetStatusRate
                        (iVar5,(int)sVar1,(undefined *)0x0);
      return iVar5 + iVar7;
    }
  }
  FUN_7fff5f47d660();
LAB_7fff5fdb2466:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar2 = (code *)swi(3);
  iVar7 = (*pcVar2)();
  return iVar7;
}

