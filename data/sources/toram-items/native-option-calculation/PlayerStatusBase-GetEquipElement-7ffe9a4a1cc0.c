
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * PlayerStatusBase_GetEquipElement(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  undefined *puVar2;
  longlong lVar3;
  undefined *puVar4;
  undefined *puVar5;
  
  puVar2 = (undefined *)
           (**(code **)(*(longlong *)self + 0x1d8))(self,*(undefined8 *)(*(longlong *)self + 0x1e0))
  ;
  if (puVar2 != (undefined *)0x0) {
    puVar2 = BonusManager_GetEquipElement(puVar2,(undefined *)0x1,(undefined *)0x0);
    puVar5 = (undefined *)((ulonglong)puVar2 & 0xffffffff);
    lVar3 = (**(code **)(*(longlong *)self + 0x1f8))
                      (self,*(undefined8 *)(*(longlong *)self + 0x200));
    if (lVar3 != 0) {
      lVar3 = FUN_7ffe99c090e0(lVar3,0);
      if ((lVar3 != 0) && ((*(int *)(lVar3 + 0x38) == 0xc || (*(int *)(lVar3 + 0x38) == 0xd)))) {
        lVar3 = (**(code **)(*(longlong *)self + 0x1f8))
                          (self,*(undefined8 *)(*(longlong *)self + 0x200));
        if (lVar3 == 0) goto LAB_7ffe9a4a1dab;
        lVar3 = FUN_7ffe99c08fe0(lVar3,0);
        if ((lVar3 != 0) && (*(int *)(lVar3 + 0x38) == 0x13)) {
          puVar4 = (undefined *)
                   (**(code **)(*(longlong *)self + 0x1d8))
                             (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
          if (puVar4 == (undefined *)0x0) goto LAB_7ffe9a4a1dab;
          puVar4 = BonusManager_GetEquipElement(puVar4,(undefined *)0x2,(undefined *)0x0);
          if ((int)puVar4 != 0) {
            return puVar4;
          }
        }
      }
      if ((int)puVar2 == 0) {
        puVar5 = (undefined *)0x7;
      }
      return puVar5;
    }
  }
LAB_7ffe9a4a1dab:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  puVar2 = (undefined *)(*pcVar1)();
  return puVar2;
}

