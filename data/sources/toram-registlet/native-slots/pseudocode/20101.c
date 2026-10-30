
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void RegistletManager_Initialize
               (undefined *self,undefined *registletData,undefined *cartData,undefined *equips,
               undefined *methodInfo)

{
  code *pcVar1;
  
  if (registletData == (undefined *)0x0) {
    return;
  }
  self[0x10] = registletData[0x20];
  *(undefined4 *)(self + 0x14) = *(undefined4 *)(registletData + 0x24);
  if (*(undefined **)(self + 0x18) != (undefined *)0x0) {
    GemCartBag_InitializeBag(*(undefined **)(self + 0x18),cartData,(undefined *)0x0);
    if (*(undefined **)(self + 0x18) != (undefined *)0x0) {
      GemCartBag_InitializeEquip
                (*(undefined **)(self + 0x18),equips,registletData[0x21],(undefined *)0x0);
      if (*(longlong *)(self + 0x20) != 0) {
        FUN_7ffe9a5b3140(*(longlong *)(self + 0x20),cartData,equips,0);
        return;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

