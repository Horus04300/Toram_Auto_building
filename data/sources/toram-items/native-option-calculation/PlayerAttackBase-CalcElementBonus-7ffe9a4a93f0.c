
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float PlayerAttackBase_CalcElementBonus
                (undefined *self,undefined *status,undefined *attackType,undefined *playerType,
                undefined *targetType,undefined *weak,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  undefined *self_00;
  int iVar7;
  undefined *type;
  float fVar8;
  longlong *plStackX_10;
  
  type = (undefined *)((ulonglong)playerType & 0xffffffff);
  if (DAT_7ffe9caddebd == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c951f28);
    FUN_7ffe9996d590(&DAT_7ffe9c94c0a0);
    DAT_7ffe9caddebd = '\x01';
  }
  bVar2 = false;
  plStackX_10 = (longlong *)0x0;
  fVar8 = 0.0;
  *weak = 0;
  iVar4 = 0;
  iVar7 = 100;
  if (status != (undefined *)0x0) {
    lVar6 = (**(code **)(*(longlong *)status + 0x1c8))
                      (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
    if (lVar6 == 0) goto LAB_7ffe9a4a96c8;
    cVar3 = FUN_7ffe9a7cbb30(lVar6,0x306,&plStackX_10,0);
    if (cVar3 != '\0') {
      if (plStackX_10 == (longlong *)0x0) goto LAB_7ffe9a4a96c8;
      iVar4 = (**(code **)(*plStackX_10 + 0x1f8))
                        (plStackX_10,0x32,*(undefined8 *)(*plStackX_10 + 0x200));
    }
    lVar6 = (**(code **)(*(longlong *)status + 0x1f8))
                      (status,*(undefined8 *)(*(longlong *)status + 0x200));
    if ((lVar6 == 0) || (*(longlong *)(lVar6 + 0x18) == 0)) goto LAB_7ffe9a4a96c8;
    iVar5 = func_0x7ffe99c1ed70(*(longlong *)(lVar6 + 0x18),0);
    if ((iVar5 == 0xe) || (iVar5 == 0xf)) {
      iVar5 = 7;
      if ((int)playerType != 0) {
        iVar5 = (int)playerType;
      }
      if ((iVar5 != 7) && ((int)attackType == 2)) {
        lVar6 = (**(code **)(*(longlong *)status + 0x1a8))
                          (status,*(undefined8 *)(*(longlong *)status + 0x1b0));
        if (lVar6 == 0) goto LAB_7ffe9a4a96c8;
        iVar7 = FUN_7ffe99742ec0(0x1e,_DAT_7ffe9c940d40);
        iVar7 = iVar7 + 100;
      }
      if (*(int *)(_DAT_7ffe9c94c0a0 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      cVar3 = func_0x7ffe9a812710(type,(ulonglong)targetType & 0xffffffff);
      if (cVar3 == '\0') goto LAB_7ffe9a4a9662;
      *weak = 1;
      iVar7 = iVar7 + 0x19;
    }
    else {
      if (*(int *)(_DAT_7ffe9c94c0a0 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      cVar3 = func_0x7ffe9a812710(type,(ulonglong)targetType & 0xffffffff);
      if (cVar3 == '\0') goto LAB_7ffe9a4a9662;
      *weak = 1;
      iVar7 = 0x7d;
      if ((int)attackType == 2) {
        lVar6 = (**(code **)(*(longlong *)status + 0x1a8))
                          (status,*(undefined8 *)(*(longlong *)status + 0x1b0));
        if (lVar6 == 0) goto LAB_7ffe9a4a96c8;
        iVar7 = FUN_7ffe99742ec0(0x1e,_DAT_7ffe9c940d40);
        iVar7 = iVar7 + 0x7d;
      }
    }
    bVar2 = true;
    lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
    if (lVar6 != 0) {
      iVar5 = FUN_7ffe9a872680(lVar6,0);
      if (iVar5 == 0x1d) {
        self_00 = (undefined *)
                  (**(code **)(*(longlong *)status + 0x1d8))
                            (status,*(undefined8 *)(*(longlong *)status + 0x1e0));
        if (self_00 == (undefined *)0x0) goto LAB_7ffe9a4a96c8;
        iVar5 = BonusManager_GetGuildFacilityElementBonus(self_00,type,(undefined *)0x0);
        iVar7 = iVar7 + iVar5;
      }
LAB_7ffe9a4a9662:
      if (((int)targetType == 7) || (bVar2)) {
        fVar8 = (float)iVar4 + 0.0;
      }
      iVar4 = PlayerAttackBase_CalcElementKillerBonus
                        (status,(undefined *)((ulonglong)targetType & 0xffffffff),(undefined *)0x0);
      return ((float)iVar4 + fVar8 + (float)iVar7) * _DAT_7ffe9c049b34;
    }
  }
LAB_7ffe9a4a96c8:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  fVar8 = (float)(*pcVar1)();
  return fVar8;
}

