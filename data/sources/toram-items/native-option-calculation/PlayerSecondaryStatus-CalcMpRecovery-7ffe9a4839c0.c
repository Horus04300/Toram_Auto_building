
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_CalcMpRecovery(undefined *self,byte isBattle,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  undefined *self_00;
  longlong lVar8;
  float fVar9;
  longlong *plStackX_8;
  longlong *plStackX_20;
  
  if (DAT_7ffe9cadde2b == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    DAT_7ffe9cadde2b = '\x01';
  }
  iVar6 = 0;
  plStackX_8 = (longlong *)0x0;
  plStackX_20 = (longlong *)0x0;
  if (*(longlong **)(self + 0x10) != (longlong *)0x0) {
    self_00 = (undefined *)(**(code **)(**(longlong **)(self + 0x10) + 0x1d8))();
    iVar4 = PlayerSecondaryStatus_CalcBaseMaxMp(self,(undefined *)0x0);
    iVar5 = iVar6;
    if ((-1 < iVar4) && (iVar5 = iVar4, 2000 < iVar4)) {
      iVar5 = 2000;
    }
    if (self_00 != (undefined *)0x0) {
      iVar5 = BonusManager_GetCalcBonusValue(self_00,iVar5 / 100 + 1,0x25,0x24,(undefined *)0x0);
      plVar1 = *(longlong **)(self + 0x10);
      if ((plVar1 != (longlong *)0x0) &&
         (lVar8 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)),
         lVar8 != 0)) {
        cVar3 = FUN_7ffe9a7cbb30(lVar8,0xe3,&plStackX_8,0);
        iVar4 = iVar6;
        if (cVar3 != '\0') {
          if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a483d6f;
          iVar4 = (**(code **)(*plStackX_8 + 0x1f8))
                            (plStackX_8,0x11,*(undefined8 *)(*plStackX_8 + 0x200));
        }
        fVar9 = _DAT_7ffe9c049b18;
        plVar1 = *(longlong **)(self + 0x10);
        if (isBattle != 0) {
          fVar9 = 0.0;
          if (((plVar1 == (longlong *)0x0) ||
              (lVar8 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0)),
              lVar8 == 0)) || (*(longlong *)(lVar8 + 0x68) == 0)) goto LAB_7ffe9a483d6f;
          cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0xc9,&plStackX_20,_DAT_7ffe9c935bd0);
          if (cVar3 != '\0') {
            if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a483d6f;
            iVar6 = (**(code **)(*plStackX_20 + 0x178))
                              (plStackX_20,0x1c,*(undefined8 *)(*plStackX_20 + 0x180));
            fVar9 = (float)iVar6 / _DAT_7ffe9c049cfc + 0.0;
          }
          fVar9 = (float)iVar5 * fVar9;
LAB_7ffe9a483d50:
          return (int)fVar9 + iVar4;
        }
        if (((plVar1 == (longlong *)0x0) ||
            (lVar8 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0)),
            lVar8 == 0)) || (*(longlong *)(lVar8 + 0x68) == 0)) goto LAB_7ffe9a483d6f;
        cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0xc5,&plStackX_20,_DAT_7ffe9c935bd0);
        if (cVar3 != '\0') {
          if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a483d6f;
          iVar6 = (**(code **)(*plStackX_20 + 0x178))
                            (plStackX_20,0x1b,*(undefined8 *)(*plStackX_20 + 0x180));
          fVar9 = (float)iVar6 / _DAT_7ffe9c049cfc + fVar9;
          if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a483d6f;
          iVar6 = (**(code **)(*plStackX_20 + 0x178))
                            (plStackX_20,0x1c,*(undefined8 *)(*plStackX_20 + 0x180));
        }
        plVar1 = *(longlong **)(self + 0x10);
        if ((plVar1 != (longlong *)0x0) &&
           (lVar8 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)),
           lVar8 != 0)) {
          cVar3 = FUN_7ffe9a7cbb30(lVar8,0xe8,&plStackX_8,0);
          if (cVar3 != '\0') {
            if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a483d6f;
            iVar7 = (**(code **)(*plStackX_8 + 0x1f8))
                              (plStackX_8,0x11,*(undefined8 *)(*plStackX_8 + 0x200));
            fVar9 = fVar9 + (float)iVar7 / _DAT_7ffe9c049cfc;
          }
          plVar1 = *(longlong **)(self + 0x10);
          if ((plVar1 != (longlong *)0x0) &&
             (lVar8 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)),
             lVar8 != 0)) {
            cVar3 = FUN_7ffe9a7cbb30(lVar8,0x301,&plStackX_8,0);
            if (cVar3 != '\0') {
              if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a483d6f;
              iVar7 = (**(code **)(*plStackX_8 + 0x1f8))
                                (plStackX_8,0x12,*(undefined8 *)(*plStackX_8 + 0x200));
              fVar9 = fVar9 + (float)iVar7 / _DAT_7ffe9c049cfc;
            }
            fVar9 = (float)iVar5 * fVar9 + (float)iVar6;
            goto LAB_7ffe9a483d50;
          }
        }
      }
    }
  }
LAB_7ffe9a483d6f:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar6 = (*pcVar2)();
  return iVar6;
}

