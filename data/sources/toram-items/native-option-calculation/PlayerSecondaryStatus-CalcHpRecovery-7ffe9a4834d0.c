
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_CalcHpRecovery(undefined *self,byte isBattle,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  float fVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined *self_00;
  longlong lVar9;
  float fVar10;
  longlong *plStackX_8;
  longlong *plStackX_20;
  
  if (DAT_7ffe9cadde2a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9341c8);
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    DAT_7ffe9cadde2a = '\x01';
  }
  iVar8 = 0;
  iVar7 = 0;
  plStackX_20 = (longlong *)0x0;
  plStackX_8 = (longlong *)0x0;
  if (*(longlong **)(self + 0x10) != (longlong *)0x0) {
    self_00 = (undefined *)(**(code **)(**(longlong **)(self + 0x10) + 0x1d8))();
    iVar5 = PlayerSecondaryStatus_CalcBaseMaxHp(self,(undefined *)0x0);
    iVar6 = 99999;
    if (iVar5 < 99999) {
      iVar6 = iVar5;
    }
    if (self_00 != (undefined *)0x0) {
      iVar6 = BonusManager_GetCalcBonusValue(self_00,iVar6 / 0x19 + 10,0x23,0x22,(undefined *)0x0);
      plVar1 = *(longlong **)(self + 0x10);
      if (plVar1 != (longlong *)0x0) {
        lVar9 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
        if (lVar9 != 0) {
          cVar4 = FUN_7ffe9a7cbb30(lVar9,0xe2,&plStackX_20,0);
          if (cVar4 != '\0') {
            if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a483868;
            iVar7 = (**(code **)(*plStackX_20 + 0x1f8))
                              (plStackX_20,0xf,*(undefined8 *)(*plStackX_20 + 0x200));
          }
          fVar10 = _DAT_7ffe9c049b18;
          plVar1 = *(longlong **)(self + 0x10);
          if (isBattle == 0) {
            if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a483868;
            lVar9 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
            if ((lVar9 == 0) || (*(longlong *)(lVar9 + 0x68) == 0)) goto LAB_7ffe9a483868;
            cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x68),0xc4,&plStackX_8,_DAT_7ffe9c935bd0)
            ;
            fVar3 = _DAT_7ffe9c049cfc;
            if (cVar4 != '\0') {
              if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a483868;
              iVar8 = (**(code **)(*plStackX_8 + 0x178))
                                (plStackX_8,0x1b,*(undefined8 *)(*plStackX_8 + 0x180));
              fVar10 = (float)iVar8 / fVar3 + fVar10;
              if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a483868;
              iVar8 = (**(code **)(*plStackX_8 + 0x178))
                                (plStackX_8,0x1c,*(undefined8 *)(*plStackX_8 + 0x180));
            }
            plVar1 = *(longlong **)(self + 0x10);
            if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a483868;
            lVar9 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
            if (lVar9 == 0) goto LAB_7ffe9a483868;
            cVar4 = FUN_7ffe9a7cbb30(lVar9,0x301,&plStackX_20,0);
            if (cVar4 != '\0') {
              if (plStackX_20 == (longlong *)0x0) goto LAB_7ffe9a483868;
              iVar5 = (**(code **)(*plStackX_20 + 0x1f8))
                                (plStackX_20,0x10,*(undefined8 *)(*plStackX_20 + 0x200));
              fVar10 = fVar10 + (float)iVar5 / fVar3;
            }
            fVar10 = (float)iVar6 * fVar10 + (float)iVar8;
          }
          else {
            fVar10 = 0.0;
            if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a483868;
            lVar9 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
            if ((lVar9 == 0) || (*(longlong *)(lVar9 + 0x68) == 0)) goto LAB_7ffe9a483868;
            cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x68),199,&plStackX_8,_DAT_7ffe9c935bd0);
            if (cVar4 != '\0') {
              if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a483868;
              iVar8 = (**(code **)(*plStackX_8 + 0x178))
                                (plStackX_8,0x1c,*(undefined8 *)(*plStackX_8 + 0x180));
              fVar10 = (float)iVar8 / _DAT_7ffe9c049cfc + 0.0;
            }
            fVar10 = (float)iVar6 * fVar10;
          }
          plVar1 = *(longlong **)(self + 0x10);
          if (plVar1 != (longlong *)0x0) {
            lVar9 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
            if ((lVar9 != 0) && (*(longlong *)(lVar9 + 0x40) != 0)) {
              cVar4 = FUN_7ffe9ad5f0a0(*(longlong *)(lVar9 + 0x40),0x428,_DAT_7ffe9c9341c8);
              if (cVar4 == '\0') {
                iVar7 = (int)fVar10 + iVar7;
              }
              else {
                iVar7 = 0;
              }
              return iVar7;
            }
          }
        }
      }
    }
  }
LAB_7ffe9a483868:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar8 = (*pcVar2)();
  return iVar8;
}

