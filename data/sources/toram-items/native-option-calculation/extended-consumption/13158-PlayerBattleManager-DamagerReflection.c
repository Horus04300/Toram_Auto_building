
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PlayerBattleManager_DamagerReflection(undefined *self,undefined *actMgr,undefined *methodInfo)

{
  uint uVar1;
  code *pcVar2;
  char cVar3;
  undefined2 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  longlong *plVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  longlong lVar10;
  undefined8 uStackX_20;
  
  if (DAT_7ffe9caddd07 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c952a50);
    DAT_7ffe9caddd07 = '\x01';
  }
  plVar7 = (longlong *)func_0x7ffe9a7fb2b0(10);
  if ((plVar7 != (longlong *)0x0) &&
     (FUN_7ffe9a8fe290(plVar7,*(undefined8 *)(self + 0x28),1,0), actMgr != (undefined *)0x0)) {
    uVar8 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c9724e0,actMgr);
    uVar9 = FUN_7ffe99742ec0(6,_DAT_7ffe9c9724e0,actMgr);
    (**(code **)(*(longlong *)self + 0x2f8))
              (self,uVar8,uVar9,plVar7,*(undefined8 *)(*(longlong *)self + 0x300));
    uVar8 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c9724e0,actMgr);
    uVar9 = FUN_7ffe99742ec0(6,_DAT_7ffe9c9724e0,actMgr);
    (**(code **)(*(longlong *)self + 0x338))
              (self,uVar8,uVar9,plVar7,*(undefined8 *)(*(longlong *)self + 0x340));
    lVar10 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
    if (lVar10 != 0) {
      FUN_7ffe9a89e600(lVar10,plVar7,0);
      if (DAT_7ffe9caddd03 == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c93dfa8,plVar7,0);
        FUN_7ffe9996d590(&DAT_7ffe9c93e130);
        FUN_7ffe9996d590(&DAT_7ffe9c962710);
        FUN_7ffe9996d590(&DAT_7ffe9c970c90);
        FUN_7ffe9996d590(&DAT_7ffe9c950390);
        FUN_7ffe9996d590(&DAT_7ffe9c949ca0);
        DAT_7ffe9caddd03 = '\x01';
      }
      if (plVar7 != (longlong *)0x0) {
        cVar3 = (**(code **)(*plVar7 + 0x228))(plVar7,*(undefined8 *)(*plVar7 + 0x230));
        if (cVar3 != '\0') {
          return;
        }
        lVar10 = FUN_7ffe9b141840(_DAT_7ffe9c950390);
        uVar4 = (**(code **)(*plVar7 + 0x188))(plVar7,*(undefined8 *)(*plVar7 + 400));
        uVar1 = *(uint *)(plVar7 + 2);
        uVar8 = func_0x7ffe99940040(_DAT_7ffe9c949ca0);
        FUN_7ffe9aac5330(uVar8,uVar4,uVar1 & 0xff,0);
        if (lVar10 != 0) {
          uVar5 = FUN_7ffe9aac4850(lVar10,uVar8,0);
          uVar6 = (**(code **)(*plVar7 + 0x188))(plVar7,*(undefined8 *)(*plVar7 + 400));
          func_0x7ffe9a41d5e0(&stack0x00000010,uVar6,(int)plVar7[2],_DAT_7ffe9c970c90);
          if (*(longlong *)(self + 0xe0) != 0) {
            cVar3 = FUN_7ffe9acce410(*(longlong *)(self + 0xe0),0,_DAT_7ffe9c93e130);
            if (cVar3 != '\0') {
              return;
            }
            lVar10 = *(longlong *)(self + 0xe0);
            uStackX_20 = 0;
            func_0x7ffe9a41d5e0(&uStackX_20,8,uVar5,_DAT_7ffe9c962710);
            if (lVar10 != 0) {
              FUN_7ffe9acce300(lVar10,0,uStackX_20,_DAT_7ffe9c93dfa8);
              return;
            }
            FUN_7ffe9996d7a0();
            pcVar2 = (code *)swi(3);
            (*pcVar2)();
            return;
          }
        }
      }
      FUN_7ffe9996d7a0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

