
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_get_Mdef(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined *puVar8;
  longlong lVar9;
  longlong lVar10;
  float fVar11;
  longlong *plStackX_10;
  longlong lStackX_20;
  longlong *plStack_48;
  longlong alStack_40 [2];
  undefined8 uStack_30;
  
  plVar1 = *(longlong **)(self + 0x10);
  if (plVar1 == (longlong *)0x0) {
LAB_7ffe9a41ab6e:
    uStack_30 = 0x7ffe9a41ab73;
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    iVar7 = (*pcVar2)();
    return iVar7;
  }
  uStack_30 = 0x7ffe9a41ab55;
  lVar10 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
  if (lVar10 == 0) goto LAB_7ffe9a41ab6e;
  plVar1 = *(longlong **)(self + 0x10);
  if (DAT_7ffe9cada8bc == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c9679b0);
    FUN_7ffe9996d590(&DAT_7ffe9c969590);
    DAT_7ffe9cada8bc = '\x01';
  }
  iVar7 = 0;
  plStackX_10 = (longlong *)0x0;
  lStackX_20 = 0;
  plStack_48 = (longlong *)0x0;
  if (plVar1 == (longlong *)0x0) {
LAB_7ffe99c085a7:
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    iVar7 = (*pcVar2)();
    return iVar7;
  }
  puVar8 = (undefined *)(**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0));
  if (puVar8 == (undefined *)0x0) goto LAB_7ffe99c085a7;
  iVar4 = BonusManager_GetBonusValue(puVar8,0x1d,(undefined *)0x0);
  fVar11 = (float)iVar4 + _DAT_7ffe9c049cfc;
  puVar8 = (undefined *)(**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0));
  if (puVar8 == (undefined *)0x0) goto LAB_7ffe99c085a7;
  iVar4 = BonusManager_GetBonusValue(puVar8,0x1c,(undefined *)0x0);
  lVar9 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
  if ((lVar9 == 0) || (*(longlong *)(lVar9 + 0x68) == 0)) goto LAB_7ffe99c085a7;
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x68),0x1e3,&plStackX_10,_DAT_7ffe9c935bd0);
  if (cVar3 != '\0') {
    lVar9 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
    if (lVar9 == 0) goto LAB_7ffe99c085a7;
    iVar5 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar9);
    if (plStackX_10 == (longlong *)0x0) goto LAB_7ffe99c085a7;
    iVar6 = (**(code **)(*plStackX_10 + 0x178))
                      (plStackX_10,0x12,*(undefined8 *)(*plStackX_10 + 0x180));
    iVar4 = iVar4 + (iVar6 * iVar5) / 100;
  }
  lVar9 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
  if ((lVar9 == 0) || (*(longlong *)(lVar9 + 0x68) == 0)) goto LAB_7ffe99c085a7;
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x68),0x1ec,&plStackX_10,_DAT_7ffe9c935bd0);
  if (cVar3 != '\0') {
    lVar9 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
    if (lVar9 == 0) goto LAB_7ffe99c085a7;
    iVar5 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar9);
    if (plStackX_10 == (longlong *)0x0) goto LAB_7ffe99c085a7;
    iVar6 = (**(code **)(*plStackX_10 + 0x178))
                      (plStackX_10,0x12,*(undefined8 *)(*plStackX_10 + 0x180));
    iVar4 = iVar4 + (iVar6 * iVar5) / 100;
  }
  lVar9 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
  if (lVar9 == 0) goto LAB_7ffe99c085a7;
  iVar5 = func_0x7ffe9a7c8f00(lVar9,0x19);
  iVar4 = iVar4 + iVar5;
  lVar9 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
  if (lVar9 == 0) goto LAB_7ffe99c085a7;
  iVar5 = func_0x7ffe9a7c8f00(lVar9,0x1a);
  fVar11 = fVar11 + (float)iVar5;
  lVar9 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
  if (lVar9 == 0) goto LAB_7ffe99c085a7;
  cVar3 = FUN_7ffe9abc2210(lVar9,0x38,&lStackX_20,_DAT_7ffe9c969590);
  if (cVar3 != '\0') {
    if (lStackX_20 == 0) goto LAB_7ffe99c085a7;
    cVar3 = func_0x7ffe9a79d550(lStackX_20,0);
    if (cVar3 != '\0') {
      lVar9 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
      if (lVar9 == 0) goto LAB_7ffe99c085a7;
      cVar3 = FUN_7ffe9abc2210(lVar9,0x2e,&plStack_48,_DAT_7ffe9c9679b0);
      if (cVar3 != '\0') {
        if (plStack_48 == (longlong *)0x0) goto LAB_7ffe99c085a7;
        iVar5 = (**(code **)(*plStack_48 + 0x1f8))
                          (plStack_48,0x1a,*(undefined8 *)(*plStack_48 + 0x200));
        fVar11 = (fVar11 - (float)iVar5) + (float)(iVar5 / 2);
      }
    }
  }
  iVar5 = 0;
  if (DAT_7ffe9cada8b2 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c95a358);
    DAT_7ffe9cada8b2 = '\x01';
  }
  alStack_40[0] = 0;
  if (*(longlong *)(lVar10 + 0x10) == 0) {
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    iVar7 = (*pcVar2)();
    return iVar7;
  }
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar10 + 0x10),2,alStack_40,_DAT_7ffe9c95a358);
  iVar6 = 0;
  if ((cVar3 != '\0') && (iVar6 = iVar5, alStack_40[0] != 0)) {
    lVar9 = FUN_7ffe99c08fe0(lVar10,0);
    if (lVar9 == 0) goto LAB_7ffe99c085a7;
    if (*(int *)(lVar9 + 0x38) == 0x11) {
      lVar9 = FUN_7ffe99c08fe0(lVar10,0);
      if (lVar9 == 0) goto LAB_7ffe99c085a7;
      iVar6 = (int)*(short *)(lVar9 + 0x42);
      lVar9 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
      if ((lVar9 == 0) || (*(longlong *)(lVar9 + 0x68) == 0)) goto LAB_7ffe99c085a7;
      cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x68),0x105,&plStackX_10,_DAT_7ffe9c935bd0);
      if (cVar3 != '\0') {
        if (plStackX_10 == (longlong *)0x0) goto LAB_7ffe99c085a7;
        iVar5 = (**(code **)(*plStackX_10 + 0x178))
                          (plStackX_10,0x12,*(undefined8 *)(*plStackX_10 + 0x180));
        fVar11 = fVar11 + (float)iVar5;
        if (plStackX_10 == (longlong *)0x0) goto LAB_7ffe99c085a7;
        iVar5 = (**(code **)(*plStackX_10 + 0x178))
                          (plStackX_10,0x11,*(undefined8 *)(*plStackX_10 + 0x180));
        iVar4 = iVar4 + iVar5;
      }
    }
    else {
      lVar9 = FUN_7ffe99c08fe0(lVar10,0);
      if (lVar9 == 0) goto LAB_7ffe99c085a7;
      if (*(int *)(lVar9 + 0x38) == 0x13) {
        fVar11 = fVar11 + _DAT_7ffe9c04a170;
      }
    }
  }
  if (DAT_7ffe9cada8b4 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c95a358);
    DAT_7ffe9cada8b4 = '\x01';
  }
  alStack_40[0] = 0;
  if (*(longlong *)(lVar10 + 0x10) == 0) {
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    iVar7 = (*pcVar2)();
    return iVar7;
  }
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar10 + 0x10),4,alStack_40,_DAT_7ffe9c95a358);
  if ((cVar3 != '\0') && (alStack_40[0] != 0)) {
    lVar9 = FUN_7ffe99c08e70(lVar10,0);
    if (lVar9 == 0) goto LAB_7ffe99c085a7;
    iVar6 = iVar6 + *(short *)(lVar9 + 0x42);
  }
  if (DAT_7ffe9cada8b5 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c95a358);
    DAT_7ffe9cada8b5 = '\x01';
  }
  alStack_40[0] = 0;
  if (*(longlong *)(lVar10 + 0x10) == 0) {
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    iVar7 = (*pcVar2)();
    return iVar7;
  }
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar10 + 0x10),5,alStack_40,_DAT_7ffe9c95a358);
  if ((cVar3 != '\0') && (alStack_40[0] != 0)) {
    lVar9 = FUN_7ffe99c08ee0(lVar10,0);
    if (lVar9 == 0) goto LAB_7ffe99c085a7;
    iVar6 = iVar6 + *(short *)(lVar9 + 0x42);
  }
  if (DAT_7ffe9cada8b3 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c95a358);
    DAT_7ffe9cada8b3 = '\x01';
  }
  alStack_40[0] = 0;
  if (*(longlong *)(lVar10 + 0x10) == 0) {
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    iVar7 = (*pcVar2)();
    return iVar7;
  }
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar10 + 0x10),3,alStack_40,_DAT_7ffe9c95a358);
  if ((cVar3 == '\0') || (alStack_40[0] == 0)) {
    cVar3 = '\x03';
  }
  else {
    lVar9 = FUN_7ffe99c08d90(lVar10,0);
    if (lVar9 == 0) goto LAB_7ffe99c085a7;
    cVar3 = func_0x7ffe9a56fc20(lVar9,0);
    lVar10 = FUN_7ffe99c08d90(lVar10,0);
    if (lVar10 == 0) goto LAB_7ffe99c085a7;
    iVar6 = iVar6 + *(short *)(lVar10 + 0x42);
  }
  if (cVar3 == '\0') {
    lVar10 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
    if (lVar10 == 0) goto LAB_7ffe99c085a7;
    iVar7 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar10);
    lVar10 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
    if (lVar10 == 0) goto LAB_7ffe99c085a7;
    iVar5 = FUN_7ffe99742ec0(2,_DAT_7ffe9c940d40,lVar10);
    iVar7 = iVar7 + iVar5;
  }
  else if (cVar3 == '\x01') {
    lVar10 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
    if (lVar10 == 0) goto LAB_7ffe99c085a7;
    iVar7 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar10);
    lVar10 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
    if (lVar10 == 0) goto LAB_7ffe99c085a7;
    iVar5 = FUN_7ffe99742ec0(2,_DAT_7ffe9c940d40,lVar10);
    iVar7 = (int)((float)iVar5 * _DAT_7ffe9c049c7c + (float)iVar7 * _DAT_7ffe9c049db0);
  }
  else if (cVar3 == '\x02') {
    lVar10 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
    if (lVar10 == 0) goto LAB_7ffe99c085a7;
    iVar7 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar10);
    lVar10 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
    if (lVar10 == 0) goto LAB_7ffe99c085a7;
    iVar5 = FUN_7ffe99742ec0(2,_DAT_7ffe9c940d40,lVar10);
    iVar7 = (int)((float)iVar7 * _DAT_7ffe9c049db4 + (float)iVar5 + (float)iVar5);
  }
  else {
    if (cVar3 != '\x03') goto LAB_7ffe99c0856b;
    lVar10 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
    if (lVar10 == 0) goto LAB_7ffe99c085a7;
    iVar7 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar10);
    lVar10 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
    if (lVar10 == 0) goto LAB_7ffe99c085a7;
    iVar5 = FUN_7ffe99742ec0(2,_DAT_7ffe9c940d40,lVar10);
    iVar7 = (int)((float)iVar5 / _DAT_7ffe9c049ce4 + (float)iVar7 * _DAT_7ffe9c049cc4);
  }
  iVar7 = iVar7 + iVar6;
LAB_7ffe99c0856b:
  return ((int)fVar11 * iVar7) / 100 + iVar4;
}

