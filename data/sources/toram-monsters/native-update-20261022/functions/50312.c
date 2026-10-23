
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UIHighRaidEnterManager_OnBattleReady(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  undefined8 uVar5;
  longlong lVar6;
  undefined8 uVar7;
  uint uVar8;
  undefined8 unaff_RDI;
  
  if (DAT_7ffe9cada446 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92dbe0);
    FUN_7ffe9996d590(&DAT_7ffe9c952a50);
    FUN_7ffe9996d590(&DAT_7ffe9c954a30);
    FUN_7ffe9996d590(&DAT_7ffe9c91f830);
    FUN_7ffe9996d590(&DAT_7ffe9c916818);
    FUN_7ffe9996d590(&DAT_7ffe9c926480);
    DAT_7ffe9cada446 = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x148);
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe99b4fe62;
  cVar4 = (**(code **)(*plVar1 + 0x178))(plVar1,*(undefined8 *)(*plVar1 + 0x180));
  if (cVar4 != '\0') {
    if (DAT_7ffe9cada44b == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c91f830,0);
      FUN_7ffe9996d590(&DAT_7ffe9c92ff50);
      DAT_7ffe9cada44b = '\x01';
    }
    plVar1 = *(longlong **)(self + 0x148);
    if ((plVar1 != (longlong *)0x0) &&
       (cVar4 = (**(code **)(*plVar1 + 0x178))(plVar1,*(undefined8 *)(*plVar1 + 0x180)),
       cVar4 != '\0')) {
      plVar1 = *(longlong **)(self + 0x148);
      if (plVar1 == (longlong *)0x0) goto LAB_7ffe99b4ea1a;
      (**(code **)(*plVar1 + 0x1e8))(plVar1,*(undefined8 *)(*plVar1 + 0x1f0));
    }
    uVar5 = _DAT_7ffe9c91f830;
    lVar6 = *(longlong *)(self + 0x78);
    if (*(longlong *)(self + 0x20) != 0) {
      uVar7 = FUN_7ffe99a58320(*(longlong *)(self + 0x20),_DAT_7ffe9c92ff50,0);
      uVar5 = FUN_7ffe9b3675b0(uVar5,uVar7,0);
      if (lVar6 != 0) {
        FUN_7ffe9a404310(lVar6,uVar5,0);
        uVar8 = 0;
        lVar6 = *(longlong *)(self + 0x110);
        while (lVar6 != 0) {
          if (*(int *)(lVar6 + 0x18) <= (int)uVar8) {
            return;
          }
          if (lVar6 == 0) break;
          if (*(uint *)(lVar6 + 0x18) <= uVar8) {
            FUN_7ffe9996d790();
            pcVar3 = (code *)swi(3);
            (*pcVar3)();
            return;
          }
          lVar6 = *(longlong *)(lVar6 + 0x20 + (longlong)(int)uVar8 * 8);
          if (lVar6 == 0) break;
          FUN_7ffe999f2150(lVar6,1,0,uVar8,unaff_RDI);
          uVar8 = uVar8 + 1;
          lVar6 = *(longlong *)(self + 0x110);
        }
        FUN_7ffe9996d7a0();
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
    }
LAB_7ffe99b4ea1a:
    FUN_7ffe9996d7a0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  plVar1 = *(longlong **)(self + 0x148);
  if (plVar1 == (longlong *)0x0) {
    return;
  }
  cVar4 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
  uVar7 = _DAT_7ffe9c91f830;
  uVar5 = _DAT_7ffe9c916818;
  lVar6 = *(longlong *)(self + 0x78);
  lVar2 = *(longlong *)(self + 0x20);
  if (cVar4 == '\0') {
    if (lVar2 == 0) goto LAB_7ffe99b4fe62;
    uVar5 = FUN_7ffe99a58320(lVar2,_DAT_7ffe9c926480,0);
    uVar5 = FUN_7ffe9b3675b0(uVar7,uVar5,0);
    if (lVar6 == 0) goto LAB_7ffe99b4fe62;
    FUN_7ffe9a404310(lVar6,uVar5,0);
  }
  else {
    if (lVar2 == 0) goto LAB_7ffe99b4fe62;
    uVar7 = FUN_7ffe99a58320(lVar2,_DAT_7ffe9c926480,0);
    uVar5 = FUN_7ffe9b3675b0(uVar5,uVar7,0);
    if (lVar6 == 0) goto LAB_7ffe99b4fe62;
    FUN_7ffe9a404310(lVar6,uVar5,0);
    if (*(longlong *)(self + 0x70) == 0) goto LAB_7ffe99b4fe62;
    FUN_7ffe999f2150(*(longlong *)(self + 0x70),0,0);
    lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
    if (lVar6 == 0) goto LAB_7ffe99b4fe62;
    cVar4 = FUN_7ffe9a5a4650(lVar6,0);
    if (cVar4 != '\0') {
      lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
      if (lVar6 == 0) goto LAB_7ffe99b4fe62;
      cVar4 = FUN_7ffe9a5a4230(lVar6,0);
      if (cVar4 == '\0') goto LAB_7ffe99b4fdd3;
    }
    lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
    if (lVar6 == 0) goto LAB_7ffe99b4fe62;
    FUN_7ffe9a8b8d00(lVar6,*(undefined2 *)(self + 0x174),0);
  }
LAB_7ffe99b4fdd3:
  plVar1 = *(longlong **)(self + 0x148);
  if (*(longlong *)(self + 0x1b0) != 0) {
    uVar5 = FUN_7ffe9af89d20(*(longlong *)(self + 0x1b0),_DAT_7ffe9c92dbe0);
    if ((*(longlong *)(self + 0x1b8) != 0) &&
       (uVar7 = FUN_7ffe9af89d20(*(longlong *)(self + 0x1b8),_DAT_7ffe9c92dbe0),
       plVar1 != (longlong *)0x0)) {
      (**(code **)(*plVar1 + 0x1c8))(plVar1,uVar5,uVar7,*(undefined8 *)(*plVar1 + 0x1d0));
      FUN_7ffe99b4eb70(self,0,0);
      return;
    }
  }
LAB_7ffe99b4fe62:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

