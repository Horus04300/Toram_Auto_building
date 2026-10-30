
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte UIRegistletReinforcementPanel__CreateGemCartList_b__51_0
               (undefined *self,undefined *gem,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  longlong lVar3;
  longlong lVar4;
  undefined *puVar5;
  undefined8 uVar6;
  
  if (DAT_7ffe9cadc375 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9091d8);
    FUN_7ffe9996d590(&DAT_7ffe9c93b0e8);
    FUN_7ffe9996d590(&DAT_7ffe9c953a40);
    FUN_7ffe9996d590(&DAT_7ffe9c904af0);
    FUN_7ffe9996d590(&DAT_7ffe9c8fc1c8);
    DAT_7ffe9cadc375 = '\x01';
  }
  lVar3 = func_0x7ffe99940040(_DAT_7ffe9c8fc1c8);
  func_0x7ffe999c3920(lVar3,0);
  if (lVar3 != 0) {
    *(undefined **)(lVar3 + 0x10) = gem;
    il2cpp_write_barrier_0();
    if ((*(longlong *)(self + 0xa0) != 0) && (*(longlong *)(lVar3 + 0x10) != 0)) {
      if (*(longlong *)(*(longlong *)(self + 0xa0) + 0x18) !=
          *(longlong *)(*(longlong *)(lVar3 + 0x10) + 0x18)) {
        if (((*(longlong *)(self + 0xc0) == 0) || (lVar4 = FUN_7ffe9a480320(), lVar4 == 0)) ||
           (*(undefined **)(lVar4 + 0x18) == (undefined *)0x0)) goto LAB_7ffe9a052c12;
        puVar5 = GemCartBag_GetEquipGemCarts(*(undefined **)(lVar4 + 0x18),(undefined *)0x0);
        uVar6 = func_0x7ffe99940040(_DAT_7ffe9c93b0e8);
        FUN_7ffe9af13420(uVar6,lVar3,_DAT_7ffe9c904af0,0);
        lVar4 = FUN_7ffe9ab854c0(puVar5,uVar6,_DAT_7ffe9c9091d8);
        if (lVar4 == 0) {
          lVar4 = FUN_7ffe9b141840(_DAT_7ffe9c953a40);
          if ((*(longlong *)(lVar3 + 0x10) == 0) || (lVar4 == 0)) goto LAB_7ffe9a052c12;
          lVar4 = FUN_7ffe9a5b4af0(lVar4,*(undefined2 *)(*(longlong *)(lVar3 + 0x10) + 0x20),0);
          if (lVar4 != 0) {
            if (*(undefined **)(lVar3 + 0x10) == (undefined *)0x0) goto LAB_7ffe9a052c12;
            bVar2 = GemCartData_get_IsLock(*(undefined **)(lVar3 + 0x10),(undefined *)0x0);
            if (bVar2 == 0) {
              return 1;
            }
          }
        }
      }
      return 0;
    }
  }
LAB_7ffe9a052c12:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  bVar2 = (*pcVar1)();
  return bVar2;
}

