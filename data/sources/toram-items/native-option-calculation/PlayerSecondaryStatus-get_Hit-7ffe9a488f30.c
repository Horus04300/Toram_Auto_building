
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_get_Hit(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  float fVar3;
  float fVar4;
  char cVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  longlong lVar9;
  undefined *self_00;
  float afStackX_8 [4];
  int aiStackX_18 [2];
  longlong *plStackX_20;
  
  if (DAT_7ffe9cadde10 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    DAT_7ffe9cadde10 = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x10);
  afStackX_8[0] = _DAT_7ffe9c049b18;
  aiStackX_18[0] = 0;
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a489789;
  lVar9 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
  if (lVar9 == 0) goto LAB_7ffe9a489789;
  iVar6 = FUN_7ffe99c09050(lVar9,0);
  plVar1 = *(longlong **)(self + 0x10);
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a489789;
  lVar9 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
  if (lVar9 == 0) goto LAB_7ffe9a489789;
  iVar7 = FUN_7ffe99c08f50(lVar9,0);
  plVar1 = *(longlong **)(self + 0x10);
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a489789;
  self_00 = (undefined *)(**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0));
  if (self_00 == (undefined *)0x0) goto LAB_7ffe9a489789;
  BonusManager_GetBonusConstant_AvatarConstan_Rate
            (self_00,0x16,0xb6,0x17,(undefined *)aiStackX_18,(undefined *)afStackX_8,
             (undefined *)0x0);
  iVar8 = aiStackX_18[0];
  plVar1 = *(longlong **)(self + 0x10);
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a489789;
  lVar9 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
  if (lVar9 == 0) goto LAB_7ffe9a489789;
  aiStackX_18[0] = func_0x7ffe9a7c8f00(lVar9,0x2a);
  fVar4 = afStackX_8[0];
  plVar1 = *(longlong **)(self + 0x10);
  aiStackX_18[0] = aiStackX_18[0] + iVar8;
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a489789;
  lVar9 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
  if (lVar9 == 0) goto LAB_7ffe9a489789;
  iVar8 = func_0x7ffe9a7c8f00(lVar9,0xb);
  fVar3 = _DAT_7ffe9c049cfc;
  plVar1 = *(longlong **)(self + 0x10);
  plStackX_20 = (longlong *)0x0;
  afStackX_8[0] = (float)iVar8 / _DAT_7ffe9c049cfc + fVar4;
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a489789;
  lVar9 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
  if (lVar9 == 0) goto LAB_7ffe9a489789;
  lVar9 = FUN_7ffe99c090e0(lVar9,0);
  if (lVar9 != 0) {
    plVar1 = *(longlong **)(self + 0x10);
    if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a489789;
    lVar9 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
    if (lVar9 == 0) goto LAB_7ffe9a489789;
    lVar9 = FUN_7ffe99c08fe0(lVar9,0);
    if (lVar9 != 0) {
      plVar1 = *(longlong **)(self + 0x10);
      if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a489789;
      lVar9 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
      if (lVar9 == 0) goto LAB_7ffe9a489789;
      lVar9 = FUN_7ffe99c090e0(lVar9,0);
      if (lVar9 == 0) goto LAB_7ffe9a489789;
      if (*(int *)(lVar9 + 0x38) == 10) {
        plVar1 = *(longlong **)(self + 0x10);
        if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a489789;
        lVar9 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
        if (lVar9 == 0) goto LAB_7ffe9a489789;
        lVar9 = FUN_7ffe99c08fe0(lVar9,0);
        if (lVar9 == 0) goto LAB_7ffe9a489789;
        if (*(int *)(lVar9 + 0x38) == 10) {
          plVar1 = *(longlong **)(self + 0x10);
          if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a489789;
          lVar9 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
          if ((lVar9 == 0) || (*(longlong *)(lVar9 + 0x68) == 0)) goto LAB_7ffe9a489789;
          cVar5 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x68),0x281,&plStackX_20,_DAT_7ffe9c935bd0)
          ;
          fVar4 = afStackX_8[0];
          if (cVar5 != '\0') {
            if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a489789;
            iVar8 = (**(code **)(*plStackX_20 + 0x178))
                              (plStackX_20,0x15,*(undefined8 *)(*plStackX_20 + 0x180));
            afStackX_8[0] = (float)iVar8 / fVar3 + fVar4;
          }
          plVar1 = *(longlong **)(self + 0x10);
          if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a489789;
          lVar9 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
          if ((lVar9 == 0) || (*(longlong *)(lVar9 + 0x68) == 0)) goto LAB_7ffe9a489789;
          cVar5 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x68),0x285,&plStackX_20,_DAT_7ffe9c935bd0)
          ;
          fVar4 = afStackX_8[0];
          if (cVar5 != '\0') {
            if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a489789;
            iVar8 = (**(code **)(*plStackX_20 + 0x178))
                              (plStackX_20,0x15,*(undefined8 *)(*plStackX_20 + 0x180));
            afStackX_8[0] = (float)iVar8 / fVar3 + fVar4;
          }
        }
      }
    }
  }
  plVar1 = *(longlong **)(self + 0x10);
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a489789;
  lVar9 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
  if ((lVar9 == 0) || (*(longlong *)(lVar9 + 0x68) == 0)) goto LAB_7ffe9a489789;
  cVar5 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x68),0x1e9,&plStackX_20,_DAT_7ffe9c935bd0);
  iVar8 = aiStackX_18[0];
  if (cVar5 != '\0') {
    if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a489789;
    aiStackX_18[0] =
         (**(code **)(*plStackX_20 + 0x178))(plStackX_20,0x14,*(undefined8 *)(*plStackX_20 + 0x180))
    ;
    aiStackX_18[0] = aiStackX_18[0] + iVar8;
  }
  plVar1 = *(longlong **)(self + 0x10);
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a489789;
  lVar9 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
  if ((lVar9 == 0) || (*(longlong *)(lVar9 + 0x68) == 0)) goto LAB_7ffe9a489789;
  cVar5 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x68),0x264,&plStackX_20,_DAT_7ffe9c935bd0);
  iVar8 = aiStackX_18[0];
  if (cVar5 != '\0') {
    if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a489789;
    aiStackX_18[0] =
         (**(code **)(*plStackX_20 + 0x178))(plStackX_20,0x14,*(undefined8 *)(*plStackX_20 + 0x180))
    ;
    aiStackX_18[0] = aiStackX_18[0] + iVar8;
  }
  plVar1 = *(longlong **)(self + 0x10);
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a489789;
  lVar9 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
  if ((lVar9 == 0) || (*(longlong *)(lVar9 + 0x68) == 0)) goto LAB_7ffe9a489789;
  cVar5 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x68),0x88,&plStackX_20,_DAT_7ffe9c935bd0);
  if ((cVar5 != '\0') && (((iVar6 == 0x10 || (iVar7 == 0x10)) || (iVar6 == 0)))) {
    if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a489789;
    iVar6 = (**(code **)(*plStackX_20 + 0x178))
                      (plStackX_20,0x15,*(undefined8 *)(*plStackX_20 + 0x180));
    plVar1 = *(longlong **)(self + 0x10);
    if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a489789;
    lVar9 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
    if ((lVar9 == 0) || (*(longlong *)(lVar9 + 0x18) == 0)) goto LAB_7ffe9a489789;
    iVar7 = func_0x7ffe99c1ed70(*(longlong *)(lVar9 + 0x18),0);
    if (iVar7 == 0x10) {
      iVar6 = iVar6 * 2;
    }
    afStackX_8[0] = afStackX_8[0] + (float)iVar6 / fVar3;
  }
  plVar1 = *(longlong **)(self + 0x10);
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a489789;
  lVar9 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
  if (lVar9 == 0) goto LAB_7ffe9a489789;
  lVar9 = FUN_7ffe99c08fe0(lVar9,0);
  if (lVar9 == 0) {
    plVar1 = *(longlong **)(self + 0x10);
    if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a489789;
    lVar9 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
    if (lVar9 == 0) goto LAB_7ffe9a489789;
    lVar9 = FUN_7ffe99c090e0(lVar9,0);
    if (lVar9 == 0) goto LAB_7ffe9a489570;
LAB_7ffe9a489669:
    plVar1 = *(longlong **)(self + 0x10);
    if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a489789;
    lVar9 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
    if ((lVar9 == 0) || (*(longlong *)(lVar9 + 0x68) == 0)) goto LAB_7ffe9a489789;
    cVar5 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x68),0x265,&plStackX_20,_DAT_7ffe9c935bd0);
    fVar4 = afStackX_8[0];
    if (cVar5 != '\0') {
      if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a489789;
      iVar6 = (**(code **)(*plStackX_20 + 0x178))
                        (plStackX_20,0x15,*(undefined8 *)(*plStackX_20 + 0x180));
      afStackX_8[0] = (float)iVar6 / fVar3 + fVar4;
    }
  }
  else {
LAB_7ffe9a489570:
    plVar1 = *(longlong **)(self + 0x10);
    if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a489789;
    lVar9 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
    if (lVar9 == 0) goto LAB_7ffe9a489789;
    lVar9 = FUN_7ffe99c090e0(lVar9,0);
    if (lVar9 != 0) {
      plVar1 = *(longlong **)(self + 0x10);
      if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a489789;
      lVar9 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200));
      if ((lVar9 == 0) || (*(longlong *)(lVar9 + 0x20) == 0)) goto LAB_7ffe9a489789;
      iVar6 = func_0x7ffe99c1ed70(*(longlong *)(lVar9 + 0x20),0);
      if (iVar6 == 0x17) {
        plVar1 = *(longlong **)(self + 0x10);
        if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a489789;
        lVar9 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
        if ((lVar9 == 0) || (*(longlong *)(lVar9 + 0x68) == 0)) goto LAB_7ffe9a489789;
        cVar5 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x68),0x4c1,&plStackX_20,_DAT_7ffe9c935bd0);
        if (cVar5 != '\0') {
          if ((plStackX_20 == (longlong *)0x0) || (plStackX_20[2] == 0)) goto LAB_7ffe9a489789;
          if (*(char *)(plStackX_20[2] + 0x18) == '\n') goto LAB_7ffe9a489669;
        }
      }
    }
  }
  plVar1 = *(longlong **)(self + 0x10);
  if (plVar1 != (longlong *)0x0) {
    lVar9 = (**(code **)(*plVar1 + 0x188))(plVar1,*(undefined8 *)(*plVar1 + 400));
    if (lVar9 != 0) {
      plVar1 = *(longlong **)(self + 0x10);
      iVar6 = *(int *)(lVar9 + 0x10);
      if (plVar1 != (longlong *)0x0) {
        lVar9 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
        if (lVar9 != 0) {
          iVar7 = FUN_7ffe99742ec0(5,_DAT_7ffe9c940d40,lVar9);
          return (int)((float)(iVar7 + iVar6) * afStackX_8[0]) + aiStackX_18[0];
        }
      }
    }
  }
LAB_7ffe9a489789:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar6 = (*pcVar2)();
  return iVar6;
}

