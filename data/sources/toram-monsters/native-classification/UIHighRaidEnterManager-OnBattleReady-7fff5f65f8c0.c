
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
  
  if (DAT_7fff625e1bc2 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62434b28);
    FUN_7fff5f47d450(&DAT_7fff62459938);
    FUN_7fff5f47d450(&DAT_7fff6245b918);
    FUN_7fff5f47d450(&DAT_7fff62425680);
    FUN_7fff5f47d450(&DAT_7fff6241c668);
    FUN_7fff5f47d450(&DAT_7fff6242cb68);
    DAT_7fff625e1bc2 = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x148);
  if (plVar1 == (longlong *)0x0) goto LAB_7fff5f65fb22;
  cVar4 = (**(code **)(*plVar1 + 0x178))(plVar1,*(undefined8 *)(*plVar1 + 0x180));
  if (cVar4 != '\0') {
    if (DAT_7fff625e1bc7 == '\0') {
      FUN_7fff5f47d450(&DAT_7fff62425680,0);
      FUN_7fff5f47d450(&DAT_7fff62436638);
      DAT_7fff625e1bc7 = '\x01';
    }
    plVar1 = *(longlong **)(self + 0x148);
    if ((plVar1 != (longlong *)0x0) &&
       (cVar4 = (**(code **)(*plVar1 + 0x178))(plVar1,*(undefined8 *)(*plVar1 + 0x180)),
       cVar4 != '\0')) {
      plVar1 = *(longlong **)(self + 0x148);
      if (plVar1 == (longlong *)0x0) goto LAB_7fff5f65e6da;
      (**(code **)(*plVar1 + 0x1e8))(plVar1,*(undefined8 *)(*plVar1 + 0x1f0));
    }
    uVar5 = _DAT_7fff62425680;
    lVar6 = *(longlong *)(self + 0x78);
    if (*(longlong *)(self + 0x20) != 0) {
      uVar7 = FUN_7fff5f568150(*(longlong *)(self + 0x20),_DAT_7fff62436638,0);
      uVar5 = FUN_7fff60e71970(uVar5,uVar7,0);
      if (lVar6 != 0) {
        FUN_7fff5ff0eed0(lVar6,uVar5,0);
        uVar8 = 0;
        lVar6 = *(longlong *)(self + 0x110);
        while (lVar6 != 0) {
          if (*(int *)(lVar6 + 0x18) <= (int)uVar8) {
            return;
          }
          if (lVar6 == 0) break;
          if (*(uint *)(lVar6 + 0x18) <= uVar8) {
            FUN_7fff5f47d650();
            pcVar3 = (code *)swi(3);
            (*pcVar3)();
            return;
          }
          lVar6 = *(longlong *)(lVar6 + 0x20 + (longlong)(int)uVar8 * 8);
          if (lVar6 == 0) break;
          FUN_7fff5f502150(lVar6,1,0,uVar8,unaff_RDI);
          uVar8 = uVar8 + 1;
          lVar6 = *(longlong *)(self + 0x110);
        }
        FUN_7fff5f47d660();
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
    }
LAB_7fff5f65e6da:
    FUN_7fff5f47d660();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  plVar1 = *(longlong **)(self + 0x148);
  if (plVar1 == (longlong *)0x0) {
    return;
  }
  cVar4 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
  uVar7 = _DAT_7fff62425680;
  uVar5 = _DAT_7fff6241c668;
  lVar6 = *(longlong *)(self + 0x78);
  lVar2 = *(longlong *)(self + 0x20);
  if (cVar4 == '\0') {
    if (lVar2 == 0) goto LAB_7fff5f65fb22;
    uVar5 = FUN_7fff5f568150(lVar2,_DAT_7fff6242cb68,0);
    uVar5 = FUN_7fff60e71970(uVar7,uVar5,0);
    if (lVar6 == 0) goto LAB_7fff5f65fb22;
    FUN_7fff5ff0eed0(lVar6,uVar5,0);
  }
  else {
    if (lVar2 == 0) goto LAB_7fff5f65fb22;
    uVar7 = FUN_7fff5f568150(lVar2,_DAT_7fff6242cb68,0);
    uVar5 = FUN_7fff60e71970(uVar5,uVar7,0);
    if (lVar6 == 0) goto LAB_7fff5f65fb22;
    FUN_7fff5ff0eed0(lVar6,uVar5,0);
    if (*(longlong *)(self + 0x70) == 0) goto LAB_7fff5f65fb22;
    FUN_7fff5f502150(*(longlong *)(self + 0x70),0,0);
    lVar6 = FUN_7fff60c4bc00(_DAT_7fff6245b918);
    if (lVar6 == 0) goto LAB_7fff5f65fb22;
    cVar4 = FUN_7fff600aeb00(lVar6,0);
    if (cVar4 != '\0') {
      lVar6 = FUN_7fff60c4bc00(_DAT_7fff6245b918);
      if (lVar6 == 0) goto LAB_7fff5f65fb22;
      cVar4 = FUN_7fff600ae6e0(lVar6,0);
      if (cVar4 == '\0') goto LAB_7fff5f65fa93;
    }
    lVar6 = FUN_7fff60c4bc00(_DAT_7fff62459938);
    if (lVar6 == 0) goto LAB_7fff5f65fb22;
    FUN_7fff603c3180(lVar6,*(undefined2 *)(self + 0x174),0);
  }
LAB_7fff5f65fa93:
  plVar1 = *(longlong **)(self + 0x148);
  if (*(longlong *)(self + 0x1b0) != 0) {
    uVar5 = FUN_7fff60a940e0(*(longlong *)(self + 0x1b0),_DAT_7fff62434b28);
    if ((*(longlong *)(self + 0x1b8) != 0) &&
       (uVar7 = FUN_7fff60a940e0(*(longlong *)(self + 0x1b8),_DAT_7fff62434b28),
       plVar1 != (longlong *)0x0)) {
      (**(code **)(*plVar1 + 0x1c8))(plVar1,uVar5,uVar7,*(undefined8 *)(*plVar1 + 0x1d0));
      FUN_7fff5f65e830(self,0,0);
      return;
    }
  }
LAB_7fff5f65fb22:
  FUN_7fff5f47d660();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

