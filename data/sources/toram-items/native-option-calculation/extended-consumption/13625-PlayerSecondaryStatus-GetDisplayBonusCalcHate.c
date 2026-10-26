
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_GetDisplayBonusCalcHate(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  float fVar3;
  char cVar4;
  int iVar5;
  undefined *puVar6;
  longlong lVar7;
  float fVar8;
  float fVar9;
  double dVar10;
  longlong *plStackX_8;
  longlong *plStackX_18;
  double dStackX_20;
  
  if (DAT_7ffe9cadde27 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8edb90);
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c954998);
    DAT_7ffe9cadde27 = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x10);
  plStackX_8 = (longlong *)0x0;
  plStackX_18 = (longlong *)0x0;
  if ((plVar1 == (longlong *)0x0) ||
     (puVar6 = (undefined *)(**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0)),
     puVar6 == (undefined *)0x0)) goto LAB_7ffe9a485a59;
  fVar8 = BonusManager_GetBonusPercentValue(puVar6,0x3e,(undefined *)0x0);
  plVar1 = *(longlong **)(self + 0x10);
  if ((plVar1 == (longlong *)0x0) ||
     ((lVar7 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0)), lVar7 == 0
      || (*(longlong *)(lVar7 + 0x68) == 0)))) goto LAB_7ffe9a485a59;
  cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x68),0x208,&plStackX_18,_DAT_7ffe9c935bd0);
  fVar3 = _DAT_7ffe9c049cfc;
  if (cVar4 != '\0') {
    plVar1 = *(longlong **)(self + 0x10);
    if ((plVar1 == (longlong *)0x0) ||
       (lVar7 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)), lVar7 == 0)
       ) goto LAB_7ffe9a485a59;
    iVar5 = FUN_7ffe99c08f50(lVar7,0);
    if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a485a59;
    if (((*(byte *)(*plStackX_18 + 0x130) < *(byte *)(_DAT_7ffe9c954998 + 0x130)) ||
        (*(longlong *)
          (*(longlong *)(*plStackX_18 + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c954998 + 0x130) * 8) != _DAT_7ffe9c954998)) ||
       (plStackX_18 == (longlong *)0x0)) {
      FUN_7ffe9996c950(plStackX_18,_DAT_7ffe9c954998,iVar5 == 0x11);
      pcVar2 = (code *)swi(3);
      iVar5 = (*pcVar2)();
      return iVar5;
    }
    iVar5 = FUN_7ffe9a7b4880(plStackX_18,5,iVar5 == 0x11,0);
    fVar8 = fVar8 + (float)iVar5 / fVar3;
  }
  plVar1 = *(longlong **)(self + 0x10);
  if ((plVar1 == (longlong *)0x0) ||
     (lVar7 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)), lVar7 == 0))
  goto LAB_7ffe9a485a59;
  cVar4 = FUN_7ffe9a7cbb30(lVar7,0x209,&plStackX_8,0);
  if (cVar4 != '\0') {
    if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a485a59;
    iVar5 = func_0x7ffe9a7a2140(plStackX_8,0x59);
    fVar8 = fVar8 + (float)iVar5 / fVar3;
  }
  plVar1 = *(longlong **)(self + 0x10);
  if (((plVar1 == (longlong *)0x0) ||
      (lVar7 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0)), lVar7 == 0))
     || (*(longlong *)(lVar7 + 0x68) == 0)) goto LAB_7ffe9a485a59;
  cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar7 + 0x68),0x4c1,&plStackX_18,_DAT_7ffe9c935bd0);
  if (cVar4 != '\0') {
    if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a485a59;
    iVar5 = (**(code **)(*plStackX_18 + 0x178))
                      (plStackX_18,0x1b,*(undefined8 *)(*plStackX_18 + 0x180));
    fVar8 = fVar8 + (float)iVar5 / fVar3;
  }
  plVar1 = *(longlong **)(self + 0x10);
  if ((plVar1 == (longlong *)0x0) ||
     (lVar7 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)), lVar7 == 0))
  goto LAB_7ffe9a485a59;
  cVar4 = FUN_7ffe9a7cbb30(lVar7,0x229,&plStackX_8,0);
  if (cVar4 != '\0') {
    if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a485a59;
    if (((*(byte *)(*plStackX_8 + 0x130) < *(byte *)(_DAT_7ffe9c8edb90 + 0x130)) ||
        (*(longlong *)
          (*(longlong *)(*plStackX_8 + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c8edb90 + 0x130) * 8) != _DAT_7ffe9c8edb90)) ||
       (plStackX_8 == (longlong *)0x0)) {
      FUN_7ffe9996c950(plStackX_8);
      pcVar2 = (code *)swi(3);
      iVar5 = (*pcVar2)();
      return iVar5;
    }
    iVar5 = FUN_7ffe9a781250(plStackX_8,*(undefined8 *)(self + 0x10),0);
    fVar8 = fVar8 + (float)iVar5 * _DAT_7ffe9c049b34;
  }
  plVar1 = *(longlong **)(self + 0x10);
  if ((plVar1 == (longlong *)0x0) ||
     (lVar7 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)), lVar7 == 0))
  goto LAB_7ffe9a485a59;
  cVar4 = FUN_7ffe9a7cbb30(lVar7,0x2a8,&plStackX_8,0);
  if (cVar4 != '\0') {
    if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a485a59;
    iVar5 = func_0x7ffe9a7a2140(plStackX_8,0x59);
    fVar8 = fVar8 + (float)iVar5 / fVar3;
  }
  if (0.0 < fVar8) {
    plVar1 = *(longlong **)(self + 0x10);
    if ((plVar1 == (longlong *)0x0) ||
       (puVar6 = (undefined *)
                 (**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0)),
       puVar6 == (undefined *)0x0)) goto LAB_7ffe9a485a59;
    iVar5 = 0x9c;
LAB_7ffe9a4858f0:
    fVar9 = BonusManager_GetBonusPercentValue(puVar6,iVar5,(undefined *)0x0);
    fVar8 = fVar8 * (_DAT_7ffe9c049b18 - fVar9);
  }
  else if (fVar8 < 0.0) {
    plVar1 = *(longlong **)(self + 0x10);
    if ((plVar1 == (longlong *)0x0) ||
       (puVar6 = (undefined *)
                 (**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0)),
       puVar6 == (undefined *)0x0)) goto LAB_7ffe9a485a59;
    iVar5 = 0x9d;
    goto LAB_7ffe9a4858f0;
  }
  plVar1 = *(longlong **)(self + 0x10);
  if ((plVar1 != (longlong *)0x0) &&
     (lVar7 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)), lVar7 != 0))
  {
    cVar4 = FUN_7ffe9a7cbb30(lVar7,0x109,&plStackX_8,0);
    if (cVar4 != '\0') {
      if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a485a59;
      iVar5 = func_0x7ffe9a7a2140(plStackX_8,0x59);
      fVar8 = fVar8 + (float)iVar5 / fVar3;
    }
    if (DAT_7ffe9cad9b50 == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c968830);
      DAT_7ffe9cad9b50 = '\x01';
    }
    fVar8 = fVar8 + _DAT_7ffe9c049b18;
    if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    if (fVar8 * fVar3 < 0.0) {
      dVar10 = (double)func_0x7ffe99997688();
      if (dVar10 == _DAT_7ffe9c049b98) {
        if (((longlong)dStackX_20 & 1U) != 0) {
          dStackX_20 = dStackX_20 - _DAT_7ffe9c049b68;
        }
      }
      else {
        dStackX_20 = (double)func_0x7ffe99997768();
      }
    }
    else {
      dVar10 = (double)func_0x7ffe99997688();
      if (dVar10 == _DAT_7ffe9c049b60) {
        if (((longlong)dStackX_20 & 1U) != 0) {
          dStackX_20 = dStackX_20 + _DAT_7ffe9c049b68;
        }
      }
      else {
        dStackX_20 = (double)func_0x7ffe999978b4();
      }
    }
    return (int)dStackX_20;
  }
LAB_7ffe9a485a59:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar5 = (*pcVar2)();
  return iVar5;
}

