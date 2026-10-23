
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BonusManager_UpdateEquipLimitBonus(undefined *self,undefined *methodInfo)

{
  undefined *self_00;
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  longlong lVar4;
  undefined8 uVar5;
  undefined8 uStack_40;
  undefined8 *puStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  undefined8 uStack_18;
  
  if (DAT_7ffe9cade106 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f5b58);
    FUN_7ffe9996d590(&DAT_7ffe9c973348);
    FUN_7ffe9996d590(&DAT_7ffe9c973418);
    FUN_7ffe9996d590(0x7ffe9c9734e8);
    FUN_7ffe9996d590(&DAT_7ffe9c94b3a8);
    FUN_7ffe9996d590(&DAT_7ffe9c907ff0);
    FUN_7ffe9996d590(&DAT_7ffe9c919768);
    FUN_7ffe9996d590(&DAT_7ffe9c924f40);
    DAT_7ffe9cade106 = '\x01';
  }
  if (*(longlong *)(self + 0x78) == 0) {
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  FUN_7ffe9af836a0(&uStack_40);
  uStack_28 = uStack_40;
  uStack_20 = puStack_38;
  uStack_18 = uStack_30;
  uStack_40 = 0;
  puStack_38 = &uStack_28;
LAB_7ffe9a4ed164:
  cVar3 = FUN_7ffe9ae28ed0(&uStack_28,_DAT_7ffe9c973418);
  if (cVar3 == '\0') {
    func_0x7ffe999c3920(&uStack_28,_DAT_7ffe9c973348);
    return;
  }
  lVar4 = func_0x7ffe99940040(_DAT_7ffe9c924f40);
  func_0x7ffe999c30f0(lVar4,0);
  if (lVar4 == 0) goto LAB_7ffe9a4ed2a6;
  *(undefined **)(lVar4 + 0x18) = self;
  il2cpp_write_barrier_0();
  *(undefined8 *)(lVar4 + 0x10) = uStack_18;
  il2cpp_write_barrier_0();
  self_00 = *(undefined **)(lVar4 + 0x10);
  if (self_00 != (undefined *)0x0) goto code_r0x7ffe9a4ed1cd;
  goto LAB_7ffe9a4ed2a1;
code_r0x7ffe9a4ed1cd:
  if (self_00[0x41] != '\0') {
    if (*(undefined **)(self + 0x18) != (undefined *)0x0) {
      BonusScriptManager_Run
                (*(undefined **)(self + 0x18),*(undefined **)(self_00 + 0x10),0,(undefined *)0x0);
      BonusData_UpdateBonusList(self_00,(undefined *)0x0);
      if (*(longlong *)(lVar4 + 0x10) != 0) {
        lVar1 = *(longlong *)(*(longlong *)(lVar4 + 0x10) + 0x20);
        uVar5 = func_0x7ffe99940040(_DAT_7ffe9c8f5b58);
        FUN_7ffe9a2f3fb0(uVar5,lVar4,_DAT_7ffe9c919768);
        if (lVar1 != 0) {
          FUN_7ffe9af83580(lVar1,uVar5);
          goto LAB_7ffe9a4ed164;
        }
        FUN_7ffe9996d7a0();
      }
      FUN_7ffe9996d7a0();
    }
    FUN_7ffe9996d7a0();
LAB_7ffe9a4ed2a1:
    FUN_7ffe9996d7a0();
LAB_7ffe9a4ed2a6:
    FUN_7ffe9996d7a0();
    FUN_7ffe998fa550();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  goto LAB_7ffe9a4ed164;
}

