
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_CalcBaseSecondaryStatus
              (undefined *self,int baseStatus,int rateType,int constType,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  int iVar3;
  undefined *self_00;
  float afStackX_8 [2];
  int aiStack_18 [4];
  
  plVar1 = *(longlong **)(self + 0x10);
  afStackX_8[0] = _DAT_7ffe9c049b18;
  aiStack_18[0] = 0;
  if (plVar1 != (longlong *)0x0) {
    self_00 = (undefined *)(**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0));
    if (self_00 != (undefined *)0x0) {
      BonusManager_GetBonusConstant_Rate
                (self_00,constType,rateType,(undefined *)aiStack_18,(undefined *)afStackX_8,
                 (undefined *)0x0);
      if (*(int *)(self + 0x18) == 3) {
        afStackX_8[0] = afStackX_8[0] + (float)*(int *)(self + 0x1c) / _DAT_7ffe9c049cfc;
      }
      return (int)((float)baseStatus * afStackX_8[0] + (float)aiStack_18[0]);
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar3 = (*pcVar2)();
  return iVar3;
}

