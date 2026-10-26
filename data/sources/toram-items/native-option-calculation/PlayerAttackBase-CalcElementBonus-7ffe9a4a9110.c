
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float PlayerAttackBase_CalcElementBonus
                (undefined *self,undefined *status,undefined *attackType,undefined *targetType,
                undefined *weak,undefined *methodInfo)

{
  undefined4 uVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  longlong lVar7;
  undefined *self_00;
  int iVar8;
  undefined *targetElement;
  float fVar9;
  longlong *plStackX_10;
  
  targetElement = (undefined *)((ulonglong)targetType & 0xffffffff);
  if (DAT_7ffe9caddebc == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c951f28);
    FUN_7ffe9996d590(&DAT_7ffe9c94c0a0);
    DAT_7ffe9caddebc = '\x01';
  }
  bVar3 = false;
  iVar5 = 0;
  plStackX_10 = (longlong *)0x0;
  fVar9 = 0.0;
  *weak = 0;
  iVar8 = 100;
  if (status != (undefined *)0x0) {
    lVar7 = (**(code **)(*(longlong *)status + 0x1c8))
                      (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
    if (lVar7 == 0) goto LAB_7ffe9a4a93e5;
    cVar4 = FUN_7ffe9a7cbb30(lVar7,0x306,&plStackX_10,0);
    if (cVar4 != '\0') {
      if (plStackX_10 == (longlong *)0x0) goto LAB_7ffe9a4a93e5;
      iVar5 = (**(code **)(*plStackX_10 + 0x1f8))
                        (plStackX_10,0x32,*(undefined8 *)(*plStackX_10 + 0x200));
    }
    lVar7 = (**(code **)(*(longlong *)status + 0x1f8))
                      (status,*(undefined8 *)(*(longlong *)status + 0x200));
    if ((lVar7 == 0) || (*(longlong *)(lVar7 + 0x18) == 0)) goto LAB_7ffe9a4a93e5;
    iVar6 = func_0x7ffe99c1ed70(*(longlong *)(lVar7 + 0x18),0);
    if ((iVar6 == 0xe) || (iVar6 == 0xf)) {
      if (((*(int *)(self + 0x30) != 0) && (*(int *)(self + 0x30) != 7)) && ((int)attackType == 2))
      {
        lVar7 = (**(code **)(*(longlong *)status + 0x1a8))
                          (status,*(undefined8 *)(*(longlong *)status + 0x1b0));
        if (lVar7 == 0) goto LAB_7ffe9a4a93e5;
        iVar8 = FUN_7ffe99742ec0(0x1e,_DAT_7ffe9c940d40);
        iVar8 = iVar8 + 100;
      }
      uVar1 = *(undefined4 *)(self + 0x30);
      if (*(int *)(_DAT_7ffe9c94c0a0 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      cVar4 = func_0x7ffe9a812710(uVar1,targetElement);
      if (cVar4 == '\0') goto LAB_7ffe9a4a937b;
      *weak = 1;
      iVar8 = iVar8 + 0x19;
    }
    else {
      uVar1 = *(undefined4 *)(self + 0x30);
      if (*(int *)(_DAT_7ffe9c94c0a0 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      cVar4 = func_0x7ffe9a812710(uVar1,targetElement);
      if (cVar4 == '\0') goto LAB_7ffe9a4a937b;
      *weak = 1;
      iVar8 = 0x7d;
      if ((int)attackType == 2) {
        lVar7 = (**(code **)(*(longlong *)status + 0x1a8))
                          (status,*(undefined8 *)(*(longlong *)status + 0x1b0));
        if (lVar7 == 0) goto LAB_7ffe9a4a93e5;
        iVar8 = FUN_7ffe99742ec0(0x1e,_DAT_7ffe9c940d40);
        iVar8 = iVar8 + 0x7d;
      }
    }
    bVar3 = true;
    lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
    if (lVar7 != 0) {
      iVar6 = FUN_7ffe9a872680(lVar7,0);
      if (iVar6 == 0x1d) {
        self_00 = (undefined *)
                  (**(code **)(*(longlong *)status + 0x1d8))
                            (status,*(undefined8 *)(*(longlong *)status + 0x1e0));
        if (self_00 == (undefined *)0x0) goto LAB_7ffe9a4a93e5;
        iVar6 = BonusManager_GetGuildFacilityElementBonus
                          (self_00,(undefined *)(ulonglong)*(uint *)(self + 0x30),(undefined *)0x0);
        iVar8 = iVar8 + iVar6;
      }
LAB_7ffe9a4a937b:
      if (((int)targetType == 7) || (bVar3)) {
        fVar9 = (float)iVar5 + 0.0;
      }
      iVar5 = PlayerAttackBase_CalcElementKillerBonus(status,targetElement,(undefined *)0x0);
      return ((float)iVar5 + fVar9 + (float)iVar8) * _DAT_7ffe9c049b34;
    }
  }
LAB_7ffe9a4a93e5:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  fVar9 = (float)(*pcVar2)();
  return fVar9;
}

