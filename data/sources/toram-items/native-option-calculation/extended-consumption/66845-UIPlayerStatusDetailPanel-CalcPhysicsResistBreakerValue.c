
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float UIPlayerStatusDetailPanel_CalcPhysicsResistBreakerValue(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  longlong *plVar4;
  undefined *self_00;
  longlong lVar5;
  float fVar6;
  
  plVar4 = *(longlong **)(self + 0x60);
  if (plVar4 != (longlong *)0x0) {
    plVar4 = (longlong *)(**(code **)(*plVar4 + 0x298))(plVar4,*(undefined8 *)(*plVar4 + 0x2a0));
    if (plVar4 != (longlong *)0x0) {
      self_00 = (undefined *)(**(code **)(*plVar4 + 0x1d8))(plVar4,*(undefined8 *)(*plVar4 + 0x1e0))
      ;
      if (self_00 != (undefined *)0x0) {
        iVar2 = BonusManager_GetBonusValue(self_00,0x33,(undefined *)0x0);
        plVar4 = *(longlong **)(self + 0x70);
        if (plVar4 != (longlong *)0x0) {
          lVar5 = (**(code **)(*plVar4 + 0x1c8))(plVar4,*(undefined8 *)(*plVar4 + 0x1d0));
          if (lVar5 != 0) {
            iVar3 = func_0x7ffe9a7c8f00(lVar5,0x48);
            return (float)iVar3 + (float)iVar2;
          }
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  fVar6 = (float)(*pcVar1)();
  return fVar6;
}

