
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PlayerAttackBase_CheckAbnormalSubEffect
               (undefined *self,undefined *abnormalType,undefined *actor,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  uint uVar3;
  int iVar4;
  int iVar5;
  longlong *plVar6;
  longlong *plVar7;
  longlong lVar8;
  int iVar9;
  longlong *plStackX_20;
  
  if (DAT_7ffe9cadee0f == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c963da8);
    FUN_7ffe9996d590(&DAT_7ffe9c9573c0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    DAT_7ffe9cadee0f = '\x01';
  }
  iVar9 = 0;
  iVar5 = (int)abnormalType;
  plStackX_20 = (longlong *)0x0;
  if (2 < iVar5 - 1U) {
    return;
  }
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar2 = FUN_7ffe9bda1fa0(actor,0,0);
  if (cVar2 != '\0') {
    return;
  }
  if (actor != (undefined *)0x0) {
    plVar6 = (longlong *)FUN_7ffe9ab9c3a0(actor,_DAT_7ffe9c963da8);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar2 = FUN_7ffe9bda1fa0(plVar6,0,0);
    if (cVar2 != '\0') {
      return;
    }
    if (((plVar6 == (longlong *)0x0) ||
        (plVar7 = (longlong *)
                  (**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0)),
        plVar7 == (longlong *)0x0)) ||
       (lVar8 = (**(code **)(*plVar7 + 0x1b8))(plVar7,*(undefined8 *)(*plVar7 + 0x1c0)), lVar8 == 0)
       ) goto LAB_7ffe9a6ac423;
    uVar3 = FUN_7ffe9a7fd580(lVar8,0x20b,1,0);
    if ((int)uVar3 < 1) {
      return;
    }
    plVar7 = (longlong *)(**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0));
    if (((plVar7 == (longlong *)0x0) ||
        (lVar8 = (**(code **)(*plVar7 + 0x1f8))(plVar7,*(undefined8 *)(*plVar7 + 0x200)), lVar8 == 0
        )) || (*(longlong *)(lVar8 + 0x20) == 0)) goto LAB_7ffe9a6ac423;
    iVar4 = func_0x7ffe99c1ed70(*(longlong *)(lVar8 + 0x20),0);
    if (iVar4 != 0x11) {
      return;
    }
    if (iVar5 == 1) {
      iVar4 = 1;
    }
    else if (iVar5 == 2) {
      iVar4 = 3;
    }
    else {
      iVar4 = iVar9;
      if (iVar5 == 3) {
        iVar4 = 5;
      }
    }
    plVar7 = (longlong *)(**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0));
    if ((plVar7 == (longlong *)0x0) ||
       (lVar8 = (**(code **)(*plVar7 + 0x1c8))(plVar7,*(undefined8 *)(*plVar7 + 0x1d0)), lVar8 == 0)
       ) goto LAB_7ffe9a6ac423;
    cVar2 = FUN_7ffe9a7cbb30(lVar8,0x20b,&plStackX_20,0);
    if (cVar2 != '\0') {
      if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a6ac423;
      if (*(byte *)(plStackX_20 + 2) == uVar3) goto LAB_7ffe9a6ac3aa;
      iVar5 = (**(code **)(*plStackX_20 + 0x1f8))
                        (plStackX_20,0x14,*(undefined8 *)(*plStackX_20 + 0x200));
      iVar4 = iVar4 + iVar5;
      plVar7 = (longlong *)(**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0));
      if ((plVar7 == (longlong *)0x0) ||
         (lVar8 = (**(code **)(*plVar7 + 0x1c8))(plVar7,*(undefined8 *)(*plVar7 + 0x1d0)),
         lVar8 == 0)) goto LAB_7ffe9a6ac423;
      FUN_7ffe9a7cafa0(lVar8,0x20b,0);
    }
    plVar7 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c9573c0);
    FUN_7ffe9a7967c0(plVar7,uVar3 & 0xff,0);
    plStackX_20 = plVar7;
    plVar6 = (longlong *)(**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0));
    if ((plVar6 != (longlong *)0x0) &&
       (lVar8 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)), lVar8 != 0)
       ) {
      FUN_7ffe9a7c26c0(lVar8,plStackX_20,0,0);
LAB_7ffe9a6ac3aa:
      if (0 < iVar4) {
        do {
          if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a6ac423;
          if (((*(byte *)(*plStackX_20 + 0x130) < *(byte *)(_DAT_7ffe9c9573c0 + 0x130)) ||
              (*(longlong *)
                (*(longlong *)(*plStackX_20 + 200) + -8 +
                (ulonglong)*(byte *)(_DAT_7ffe9c9573c0 + 0x130) * 8) != _DAT_7ffe9c9573c0)) ||
             (plStackX_20 == (longlong *)0x0)) {
            FUN_7ffe9996c950(plStackX_20);
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
          (**(code **)(*plStackX_20 + 0x2a8))(plStackX_20,*(undefined8 *)(*plStackX_20 + 0x2b0));
          iVar9 = iVar9 + 1;
        } while (iVar9 < iVar4);
      }
      return;
    }
  }
LAB_7ffe9a6ac423:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

