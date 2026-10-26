
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_get_Def(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined *puVar9;
  longlong lVar10;
  longlong lVar11;
  longlong *aplStackX_10 [2];
  longlong lStackX_20;
  longlong *plStack_48;
  longlong lStack_40;
  
  plVar1 = *(longlong **)(self + 0x10);
  if (plVar1 == (longlong *)0x0) {
LAB_7ffe9a419aae:
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    iVar8 = (*pcVar2)();
    return iVar8;
  }
  lVar11 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
  if (lVar11 == 0) goto LAB_7ffe9a419aae;
  plVar1 = *(longlong **)(self + 0x10);
  if (DAT_7ffe9cada8bb == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c9679b0);
    FUN_7ffe9996d590(&DAT_7ffe9c969590);
    DAT_7ffe9cada8bb = '\x01';
  }
  iVar8 = 0;
  aplStackX_10[0] = (longlong *)0x0;
  lStackX_20 = 0;
  plStack_48 = (longlong *)0x0;
  if (plVar1 == (longlong *)0x0) {
LAB_7ffe99c074f3:
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    iVar8 = (*pcVar2)();
    return iVar8;
  }
  puVar9 = (undefined *)(**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0));
  if (puVar9 == (undefined *)0x0) goto LAB_7ffe99c074f3;
  iVar4 = BonusManager_GetBonusValue(puVar9,0x1b,(undefined *)0x0);
  puVar9 = (undefined *)(**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0));
  if (puVar9 == (undefined *)0x0) goto LAB_7ffe99c074f3;
  iVar5 = BonusManager_GetBonusValue(puVar9,0x1a,(undefined *)0x0);
  lVar10 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
  if ((lVar10 == 0) || (*(longlong *)(lVar10 + 0x68) == 0)) goto LAB_7ffe99c074f3;
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar10 + 0x68),0x1e3,aplStackX_10,_DAT_7ffe9c935bd0);
  if (cVar3 != '\0') {
    lVar10 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
    if (lVar10 == 0) goto LAB_7ffe99c074f3;
    iVar6 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar10);
    if (aplStackX_10[0] == (longlong *)0x0) goto LAB_7ffe99c074f3;
    iVar7 = (**(code **)(*aplStackX_10[0] + 0x178))
                      (aplStackX_10[0],0x10,*(undefined8 *)(*aplStackX_10[0] + 0x180));
    iVar5 = iVar5 + (iVar7 * iVar6) / 100;
  }
  lVar10 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
  if ((lVar10 == 0) || (*(longlong *)(lVar10 + 0x68) == 0)) goto LAB_7ffe99c074f3;
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar10 + 0x68),0x1ec,aplStackX_10,_DAT_7ffe9c935bd0);
  if (cVar3 != '\0') {
    lVar10 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
    if (lVar10 == 0) goto LAB_7ffe99c074f3;
    iVar6 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar10);
    if (aplStackX_10[0] == (longlong *)0x0) goto LAB_7ffe99c074f3;
    iVar7 = (**(code **)(*aplStackX_10[0] + 0x178))
                      (aplStackX_10[0],0x10,*(undefined8 *)(*aplStackX_10[0] + 0x180));
    iVar5 = iVar5 + (iVar7 * iVar6) / 100;
  }
  lVar10 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
  if (lVar10 == 0) goto LAB_7ffe99c074f3;
  iVar6 = func_0x7ffe9a7c8f00(lVar10,0x17);
  iVar5 = iVar5 + iVar6;
  lVar10 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
  if (lVar10 == 0) goto LAB_7ffe99c074f3;
  iVar6 = func_0x7ffe9a7c8f00(lVar10,0x18);
  iVar6 = iVar4 + 100 + iVar6;
  lVar10 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
  if (lVar10 == 0) goto LAB_7ffe99c074f3;
  cVar3 = FUN_7ffe9abc2210(lVar10,0x38,&lStackX_20,_DAT_7ffe9c969590);
  if (cVar3 != '\0') {
    if (lStackX_20 == 0) goto LAB_7ffe99c074f3;
    cVar3 = func_0x7ffe9a79d550(lStackX_20,0);
    if (cVar3 != '\0') {
      lVar10 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
      if (lVar10 == 0) goto LAB_7ffe99c074f3;
      cVar3 = FUN_7ffe9abc2210(lVar10,0x2e,&plStack_48,_DAT_7ffe9c9679b0);
      if (cVar3 != '\0') {
        if (plStack_48 == (longlong *)0x0) goto LAB_7ffe99c074f3;
        iVar4 = (**(code **)(*plStack_48 + 0x1f8))
                          (plStack_48,0x18,*(undefined8 *)(*plStack_48 + 0x200));
        iVar6 = iVar6 + (iVar4 / 2 - iVar4);
      }
    }
  }
  iVar4 = 0;
  if (DAT_7ffe9cada8b2 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c95a358);
    DAT_7ffe9cada8b2 = '\x01';
  }
  lStack_40 = 0;
  if (*(longlong *)(lVar11 + 0x10) == 0) {
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    iVar8 = (*pcVar2)();
    return iVar8;
  }
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar11 + 0x10),2,&lStack_40,_DAT_7ffe9c95a358);
  iVar7 = 0;
  if ((cVar3 != '\0') && (iVar7 = iVar4, lStack_40 != 0)) {
    lVar10 = FUN_7ffe99c08fe0(lVar11,0);
    if (lVar10 == 0) goto LAB_7ffe99c074f3;
    if (*(int *)(lVar10 + 0x38) == 0x11) {
      lVar10 = FUN_7ffe99c08fe0(lVar11,0);
      if (lVar10 == 0) goto LAB_7ffe99c074f3;
      iVar7 = (int)*(short *)(lVar10 + 0x42);
      lVar10 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
      if ((lVar10 == 0) || (*(longlong *)(lVar10 + 0x68) == 0)) goto LAB_7ffe99c074f3;
      cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar10 + 0x68),0x103,aplStackX_10,_DAT_7ffe9c935bd0);
      if (cVar3 != '\0') {
        if (aplStackX_10[0] == (longlong *)0x0) goto LAB_7ffe99c074f3;
        iVar4 = (**(code **)(*aplStackX_10[0] + 0x178))
                          (aplStackX_10[0],0x10,*(undefined8 *)(*aplStackX_10[0] + 0x180));
        iVar6 = iVar6 + iVar4;
        if (aplStackX_10[0] == (longlong *)0x0) goto LAB_7ffe99c074f3;
        iVar4 = (**(code **)(*aplStackX_10[0] + 0x178))
                          (aplStackX_10[0],0xf,*(undefined8 *)(*aplStackX_10[0] + 0x180));
        iVar5 = iVar5 + iVar4;
      }
    }
    else {
      lVar10 = FUN_7ffe99c08fe0(lVar11,0);
      if (lVar10 == 0) goto LAB_7ffe99c074f3;
      if (*(int *)(lVar10 + 0x38) == 0x13) {
        iVar6 = iVar6 + -0x19;
      }
    }
  }
  if (DAT_7ffe9cada8b4 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c95a358);
    DAT_7ffe9cada8b4 = '\x01';
  }
  lStack_40 = 0;
  if (*(longlong *)(lVar11 + 0x10) == 0) {
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    iVar8 = (*pcVar2)();
    return iVar8;
  }
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar11 + 0x10),4,&lStack_40,_DAT_7ffe9c95a358);
  if ((cVar3 != '\0') && (lStack_40 != 0)) {
    lVar10 = FUN_7ffe99c08e70(lVar11,0);
    if (lVar10 == 0) goto LAB_7ffe99c074f3;
    iVar7 = iVar7 + *(short *)(lVar10 + 0x42);
  }
  if (DAT_7ffe9cada8b5 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c95a358);
    DAT_7ffe9cada8b5 = '\x01';
  }
  lStack_40 = 0;
  if (*(longlong *)(lVar11 + 0x10) == 0) {
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    iVar8 = (*pcVar2)();
    return iVar8;
  }
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar11 + 0x10),5,&lStack_40,_DAT_7ffe9c95a358);
  if ((cVar3 != '\0') && (lStack_40 != 0)) {
    lVar10 = FUN_7ffe99c08ee0(lVar11,0);
    if (lVar10 == 0) goto LAB_7ffe99c074f3;
    iVar7 = iVar7 + *(short *)(lVar10 + 0x42);
  }
  if (DAT_7ffe9cada8b3 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c95a358);
    DAT_7ffe9cada8b3 = '\x01';
  }
  lStack_40 = 0;
  if (*(longlong *)(lVar11 + 0x10) == 0) {
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    iVar8 = (*pcVar2)();
    return iVar8;
  }
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar11 + 0x10),3,&lStack_40,_DAT_7ffe9c95a358);
  if ((cVar3 == '\0') || (lStack_40 == 0)) {
    cVar3 = '\x03';
  }
  else {
    lVar10 = FUN_7ffe99c08d90(lVar11,0);
    if (lVar10 == 0) goto LAB_7ffe99c074f3;
    cVar3 = func_0x7ffe9a56fc20(lVar10,0);
    lVar11 = FUN_7ffe99c08d90(lVar11,0);
    if (lVar11 == 0) goto LAB_7ffe99c074f3;
    iVar7 = iVar7 + *(short *)(lVar11 + 0x42);
  }
  if (cVar3 == '\0') {
    lVar11 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
    if (lVar11 == 0) goto LAB_7ffe99c074f3;
    iVar8 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar11);
    lVar11 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
    if (lVar11 == 0) goto LAB_7ffe99c074f3;
    iVar4 = FUN_7ffe99742ec0(3,_DAT_7ffe9c940d40,lVar11);
    iVar8 = iVar8 + iVar4;
  }
  else {
    if (cVar3 == '\x01') {
      lVar11 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
      if (lVar11 != 0) {
        iVar8 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar11);
        lVar11 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
        if (lVar11 != 0) {
          iVar4 = FUN_7ffe99742ec0(3,_DAT_7ffe9c940d40,lVar11);
          iVar8 = (int)((float)iVar4 * _DAT_7ffe9c049c7c +
                        (float)(int)(float)iVar8 * _DAT_7ffe9c049db0 + (float)iVar7);
          goto LAB_7ffe99c074bd;
        }
      }
      goto LAB_7ffe99c074f3;
    }
    if (cVar3 == '\x02') {
      lVar11 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
      if (lVar11 == 0) goto LAB_7ffe99c074f3;
      iVar8 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar11);
      lVar11 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
      if (lVar11 == 0) goto LAB_7ffe99c074f3;
      iVar4 = FUN_7ffe99742ec0(3,_DAT_7ffe9c940d40,lVar11);
      iVar8 = (int)((float)iVar8 * _DAT_7ffe9c049db4 + (float)iVar4 + (float)iVar4);
    }
    else {
      if (cVar3 != '\x03') goto LAB_7ffe99c074bd;
      lVar11 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
      if (lVar11 == 0) goto LAB_7ffe99c074f3;
      iVar8 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar11);
      lVar11 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
      if (lVar11 == 0) goto LAB_7ffe99c074f3;
      iVar4 = FUN_7ffe99742ec0(3,_DAT_7ffe9c940d40,lVar11);
      iVar8 = (int)((float)iVar4 / _DAT_7ffe9c049ce4 + (float)iVar8 * _DAT_7ffe9c049cc4);
    }
  }
  iVar8 = iVar8 + iVar7;
LAB_7ffe99c074bd:
  return (iVar8 * iVar6) / 100 + iVar5;
}

