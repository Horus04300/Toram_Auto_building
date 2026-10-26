
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float UIPlayerStatusDetailPanel_CalcPetExpValue(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined *puVar6;
  float fVar7;
  
  plVar1 = *(longlong **)(self + 0x70);
  if (plVar1 != (longlong *)0x0) {
    puVar6 = (undefined *)(**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0));
    if (puVar6 != (undefined *)0x0) {
      iVar3 = BonusManager_GetBonusValue(puVar6,0x3f,(undefined *)0x0);
      plVar1 = *(longlong **)(self + 0x70);
      if (plVar1 != (longlong *)0x0) {
        puVar6 = (undefined *)
                 (**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0));
        if (puVar6 != (undefined *)0x0) {
          iVar4 = BonusManager_GetBonusValue(puVar6,0xb0,(undefined *)0x0);
          plVar1 = *(longlong **)(self + 0x70);
          if (plVar1 != (longlong *)0x0) {
            puVar6 = (undefined *)
                     (**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0));
            if (puVar6 != (undefined *)0x0) {
              iVar5 = BonusManager_GetGuildFacilityExpBonus(puVar6,0xb0,(undefined *)0x0);
              return (float)iVar5 + (float)iVar3 + _DAT_7ffe9c049cfc + (float)iVar4;
            }
          }
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  fVar7 = (float)(*pcVar2)();
  return fVar7;
}

