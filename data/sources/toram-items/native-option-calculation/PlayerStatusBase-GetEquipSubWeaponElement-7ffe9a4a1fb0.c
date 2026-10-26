
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * PlayerStatusBase_GetEquipSubWeaponElement(undefined *self,undefined *methodInfo)

{
  undefined8 uVar1;
  undefined8 uVar2;
  code *pcVar3;
  longlong lVar4;
  undefined *puVar5;
  undefined *bonusLines;
  uint uVar6;
  undefined *puVar7;
  
  if (DAT_7ffe9cadde50 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c90b598);
    FUN_7ffe9996d590(&DAT_7ffe9c9419c0);
    FUN_7ffe9996d590(&DAT_7ffe9c8feac8);
    FUN_7ffe9996d590(&DAT_7ffe9c912480);
    DAT_7ffe9cadde50 = '\x01';
  }
  lVar4 = (**(code **)(*(longlong *)self + 0x1f8))(self,*(undefined8 *)(*(longlong *)self + 0x200));
  if (lVar4 != 0) {
    lVar4 = FUN_7ffe99c08fe0(lVar4,0);
    if (lVar4 == 0) {
      return (undefined *)0x7;
    }
    puVar7 = (undefined *)0x7;
    puVar5 = (undefined *)
             (**(code **)(*(longlong *)self + 0x1d8))
                       (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
    lVar4 = (**(code **)(*(longlong *)self + 0x1f8))
                      (self,*(undefined8 *)(*(longlong *)self + 0x200));
    if (lVar4 != 0) {
      lVar4 = FUN_7ffe99c08fe0(lVar4,0);
      if (lVar4 != 0) {
        bonusLines = (undefined *)FUN_7ffe9a56fc30(lVar4,0);
        if (puVar5 != (undefined *)0x0) {
          puVar5 = BonusManager_CreateBonus(puVar5,bonusLines,0,(undefined *)0x0);
          if (puVar5 != (undefined *)0x0) {
            uVar1 = *(undefined8 *)(puVar5 + 0x20);
            if (*(int *)(_DAT_7ffe9c912480 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            lVar4 = *(longlong *)(*(longlong *)(_DAT_7ffe9c912480 + 0xb8) + 8);
            if (lVar4 == 0) {
              if (*(int *)(_DAT_7ffe9c912480 + 0xe0) == 0) {
                func_0x7ffe9996d830();
              }
              uVar2 = **(undefined8 **)(_DAT_7ffe9c912480 + 0xb8);
              lVar4 = func_0x7ffe99940040(_DAT_7ffe9c9419c0);
              FUN_7ffe9af13420(lVar4,uVar2,_DAT_7ffe9c8feac8,0);
              *(longlong *)(*(longlong *)(_DAT_7ffe9c912480 + 0xb8) + 8) = lVar4;
              il2cpp_write_barrier_0();
            }
            lVar4 = FUN_7ffe9ab854c0(uVar1,lVar4,_DAT_7ffe9c90b598);
            if (lVar4 != 0) {
              uVar6 = *(uint *)(lVar4 + 0x14);
              if (uVar6 == 0) {
                uVar6 = 7;
              }
              puVar7 = (undefined *)(ulonglong)uVar6;
            }
            return puVar7;
          }
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  puVar5 = (undefined *)(*pcVar3)();
  return puVar5;
}

