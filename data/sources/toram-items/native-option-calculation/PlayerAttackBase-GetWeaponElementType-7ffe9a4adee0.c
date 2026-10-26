
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
PlayerAttackBase_GetWeaponElementType
          (undefined *self,undefined *playerAction,undefined *mobAction,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  undefined *puVar3;
  longlong lVar4;
  undefined *puVar5;
  undefined *puVar6;
  longlong *plVar7;
  
  if (DAT_7ffe9caddec4 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    DAT_7ffe9caddec4 = '\x01';
  }
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar2 = FUN_7ffe9bda2160(playerAction,0);
  if (cVar2 == '\0') {
    return (undefined *)(ulonglong)*(uint *)(self + 0x30);
  }
  if ((playerAction == (undefined *)0x0) ||
     (plVar7 = (longlong *)
               (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
     plVar7 == (longlong *)0x0)) {
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    puVar3 = (undefined *)(*pcVar1)();
    return puVar3;
  }
  puVar3 = (undefined *)(**(code **)(*plVar7 + 0x1d8))(plVar7,*(undefined8 *)(*plVar7 + 0x1e0));
  if (puVar3 != (undefined *)0x0) {
    puVar3 = BonusManager_GetEquipElement(puVar3,(undefined *)0x1,(undefined *)0x0);
    puVar6 = (undefined *)((ulonglong)puVar3 & 0xffffffff);
    lVar4 = (**(code **)(*plVar7 + 0x1f8))(plVar7,*(undefined8 *)(*plVar7 + 0x200));
    if (lVar4 != 0) {
      lVar4 = FUN_7ffe99c090e0(lVar4,0);
      if ((lVar4 != 0) && ((*(int *)(lVar4 + 0x38) == 0xc || (*(int *)(lVar4 + 0x38) == 0xd)))) {
        lVar4 = (**(code **)(*plVar7 + 0x1f8))(plVar7,*(undefined8 *)(*plVar7 + 0x200));
        if (lVar4 == 0) goto LAB_7ffe9a4a1dab;
        lVar4 = FUN_7ffe99c08fe0(lVar4,0);
        if ((lVar4 != 0) && (*(int *)(lVar4 + 0x38) == 0x13)) {
          puVar5 = (undefined *)
                   (**(code **)(*plVar7 + 0x1d8))(plVar7,*(undefined8 *)(*plVar7 + 0x1e0));
          if (puVar5 == (undefined *)0x0) goto LAB_7ffe9a4a1dab;
          puVar5 = BonusManager_GetEquipElement(puVar5,(undefined *)0x2,(undefined *)0x0);
          if ((int)puVar5 != 0) {
            return puVar5;
          }
        }
      }
      if ((int)puVar3 == 0) {
        puVar6 = (undefined *)0x7;
      }
      return puVar6;
    }
  }
LAB_7ffe9a4a1dab:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  puVar3 = (undefined *)(*pcVar1)();
  return puVar3;
}

