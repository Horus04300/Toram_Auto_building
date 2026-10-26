
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float UIPlayerStatusDetailPanel_CalcShortRangeValue(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  int iVar3;
  int iVar4;
  undefined *self_00;
  longlong lVar5;
  float fVar6;
  
  plVar1 = *(longlong **)(self + 0x70);
  if (plVar1 != (longlong *)0x0) {
    self_00 = (undefined *)(**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0));
    if (self_00 != (undefined *)0x0) {
      iVar3 = BonusManager_GetBonusValue(self_00,0x6b,(undefined *)0x0);
      plVar1 = *(longlong **)(self + 0x70);
      if (plVar1 != (longlong *)0x0) {
        lVar5 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
        if (lVar5 != 0) {
          iVar4 = func_0x7ffe9a7c8f00(lVar5,0x42);
          return (float)iVar4 + (float)iVar3 + _DAT_7ffe9c049cfc;
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  fVar6 = (float)(*pcVar2)();
  return fVar6;
}

