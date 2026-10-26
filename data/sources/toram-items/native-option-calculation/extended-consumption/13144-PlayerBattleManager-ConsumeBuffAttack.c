
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PlayerBattleManager_ConsumeBuffAttack
               (undefined *self,undefined *action,undefined *hitType,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  longlong *plVar6;
  longlong lVar7;
  longlong *plVar8;
  longlong *plStackX_10;
  
  if (DAT_7ffe9caddcfa == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c960fa0);
    FUN_7ffe9996d590(&DAT_7ffe9c9341c8);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c9228b0);
    DAT_7ffe9caddcfa = '\x01';
  }
  plVar8 = (longlong *)0x0;
  plStackX_10 = (longlong *)0x0;
  if (action != (undefined *)0x0) {
    if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c9228b0 + 0x130)) ||
       (plVar8 = (longlong *)action,
       *(longlong *)
        (*(longlong *)(*(longlong *)action + 200) + -8 +
        (ulonglong)*(byte *)(_DAT_7ffe9c9228b0 + 0x130) * 8) != _DAT_7ffe9c9228b0)) {
      FUN_7ffe9996c950(action);
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
  }
  plVar6 = *(longlong **)(self + 0x88);
  if ((((plVar6 == (longlong *)0x0) ||
       (plVar6 = (longlong *)(**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0))
       , plVar6 == (longlong *)0x0)) ||
      (lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)), lVar7 == 0))
     || ((*(longlong *)(lVar7 + 0x50) == 0 ||
         (cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x50),0x45,&plStackX_10,_DAT_7ffe9c934418),
         action == (undefined *)0x0)))) goto LAB_7ffe9a45b7bd;
  if (cVar3 != '\0') {
    uVar4 = (**(code **)(*(longlong *)action + 0x188))
                      (action,*(undefined8 *)(*(longlong *)action + 400));
    cVar3 = func_0x7ffe9a496210(uVar4,0);
    bVar2 = 1;
    if ((cVar3 != '\0') && (bVar2 = 1, (int)hitType == 0)) {
      bVar2 = 0;
    }
    if (plVar8 == (longlong *)0x0) goto LAB_7ffe9a45b7bd;
    cVar3 = (**(code **)(*plVar8 + 0x598))(plVar8,*(undefined8 *)(*plVar8 + 0x5a0));
    if ((bool)(bVar2 & cVar3 != '\0')) {
      if (plStackX_10 == (longlong *)0x0) goto LAB_7ffe9a45b7bd;
      if (((*(byte *)(*plStackX_10 + 0x130) < *(byte *)(_DAT_7ffe9c960fa0 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*plStackX_10 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7ffe9c960fa0 + 0x130) * 8) != _DAT_7ffe9c960fa0)) ||
         (plStackX_10 == (longlong *)0x0)) {
        FUN_7ffe9996c950(plStackX_10);
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      (**(code **)(*plStackX_10 + 0x2a8))(plStackX_10,*(undefined8 *)(*plStackX_10 + 0x2b0));
      if (plStackX_10 == (longlong *)0x0) goto LAB_7ffe9a45b7bd;
      if (*(char *)((longlong)plStackX_10 + 0x13) != '\0') {
        plVar6 = *(longlong **)(self + 0x88);
        if (((plVar6 == (longlong *)0x0) ||
            (plVar6 = (longlong *)
                      (**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0)),
            plVar6 == (longlong *)0x0)) ||
           (lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)),
           lVar7 == 0)) goto LAB_7ffe9a45b7bd;
        FUN_7ffe9a7ca6f0(lVar7,0x45);
      }
    }
  }
  uVar4 = (**(code **)(*(longlong *)action + 0x188))
                    (action,*(undefined8 *)(*(longlong *)action + 400));
  cVar3 = func_0x7ffe9a496210(uVar4,0);
  if ((cVar3 != '\0') && ((int)hitType != 0)) {
    iVar5 = (**(code **)(*(longlong *)action + 0x188))
                      (action,*(undefined8 *)(*(longlong *)action + 400));
    if (iVar5 == 0) {
      plVar6 = *(longlong **)(self + 0x88);
      if ((((plVar6 == (longlong *)0x0) ||
           (plVar6 = (longlong *)
                     (**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0)),
           plVar6 == (longlong *)0x0)) ||
          (lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)),
          lVar7 == 0)) || (*(longlong *)(lVar7 + 0x50) == 0)) goto LAB_7ffe9a45b7bd;
      cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x50),0x29,&plStackX_10,_DAT_7ffe9c934418);
      if (cVar3 != '\0') {
        if (plStackX_10 == (longlong *)0x0) goto LAB_7ffe9a45b7bd;
        if (((*(byte *)(*plStackX_10 + 0x130) < *(byte *)(_DAT_7ffe9c960fa0 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*plStackX_10 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c960fa0 + 0x130) * 8) != _DAT_7ffe9c960fa0)) ||
           (plStackX_10 == (longlong *)0x0)) {
          FUN_7ffe9996c950(plStackX_10);
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        (**(code **)(*plStackX_10 + 0x2a8))(plStackX_10,*(undefined8 *)(*plStackX_10 + 0x2b0));
        if (plStackX_10 == (longlong *)0x0) goto LAB_7ffe9a45b7bd;
        if (*(char *)((longlong)plStackX_10 + 0x13) != '\0') {
          plVar6 = *(longlong **)(self + 0x88);
          if (((plVar6 == (longlong *)0x0) ||
              (plVar6 = (longlong *)
                        (**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0)),
              plVar6 == (longlong *)0x0)) ||
             (lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)),
             lVar7 == 0)) goto LAB_7ffe9a45b7bd;
          FUN_7ffe9a7ca6f0(lVar7,0x29);
        }
      }
      plVar6 = *(longlong **)(self + 0x88);
      if ((((plVar6 == (longlong *)0x0) ||
           (plVar6 = (longlong *)
                     (**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0)),
           plVar6 == (longlong *)0x0)) ||
          (lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)),
          lVar7 == 0)) || (*(longlong *)(lVar7 + 0x50) == 0)) goto LAB_7ffe9a45b7bd;
      cVar3 = FUN_7ffe9ad5f0a0(*(longlong *)(lVar7 + 0x50),0x2a6,_DAT_7ffe9c9341c8);
      if (cVar3 != '\0') {
        plVar6 = *(longlong **)(self + 0x88);
        if (((plVar6 == (longlong *)0x0) ||
            (plVar6 = (longlong *)
                      (**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0)),
            plVar6 == (longlong *)0x0)) ||
           (lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)),
           lVar7 == 0)) goto LAB_7ffe9a45b7bd;
        FUN_7ffe9a7ca6f0(lVar7,0x2a6,0);
      }
    }
    plVar6 = *(longlong **)(self + 0x88);
    if (((plVar6 == (longlong *)0x0) ||
        (plVar6 = (longlong *)
                  (**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0)),
        plVar6 == (longlong *)0x0)) ||
       ((lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)), lVar7 == 0
        || (*(longlong *)(lVar7 + 0x50) == 0)))) goto LAB_7ffe9a45b7bd;
    cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x50),0x223,&plStackX_10,_DAT_7ffe9c934418);
    if (cVar3 != '\0') {
      if (plStackX_10 == (longlong *)0x0) goto LAB_7ffe9a45b7bd;
      if (((*(byte *)(*plStackX_10 + 0x130) < *(byte *)(_DAT_7ffe9c960fa0 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*plStackX_10 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7ffe9c960fa0 + 0x130) * 8) != _DAT_7ffe9c960fa0)) ||
         (plStackX_10 == (longlong *)0x0)) {
        FUN_7ffe9996c950(plStackX_10);
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      (**(code **)(*plStackX_10 + 0x2a8))(plStackX_10,*(undefined8 *)(*plStackX_10 + 0x2b0));
      if (plStackX_10 == (longlong *)0x0) goto LAB_7ffe9a45b7bd;
      if (*(char *)((longlong)plStackX_10 + 0x13) != '\0') {
        plVar6 = *(longlong **)(self + 0x88);
        if (((plVar6 == (longlong *)0x0) ||
            (plVar6 = (longlong *)
                      (**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0)),
            plVar6 == (longlong *)0x0)) ||
           (lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)),
           lVar7 == 0)) goto LAB_7ffe9a45b7bd;
        FUN_7ffe9a7ca6f0(lVar7,0x223,0);
      }
    }
    plVar6 = *(longlong **)(self + 0x88);
    if (((plVar6 == (longlong *)0x0) ||
        (plVar6 = (longlong *)
                  (**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0)),
        plVar6 == (longlong *)0x0)) ||
       ((lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)), lVar7 == 0
        || (FUN_7ffe9a7cafa0(lVar7,0x12a,0), plVar8 == (longlong *)0x0)))) {
LAB_7ffe9a45b7bd:
      FUN_7ffe9996d7a0();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    if ((*(byte *)((longlong)plVar8 + 0x104) & 4) != 0) {
      plVar8 = *(longlong **)(self + 0x88);
      if (((plVar8 == (longlong *)0x0) ||
          (plVar8 = (longlong *)
                    (**(code **)(*plVar8 + 0x298))(plVar8,*(undefined8 *)(*plVar8 + 0x2a0)),
          plVar8 == (longlong *)0x0)) ||
         (lVar7 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)),
         lVar7 == 0)) goto LAB_7ffe9a45b7bd;
      FUN_7ffe9a7c2b40(lVar7,0x12a,1,0,0);
    }
  }
  return;
}

