
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte UIPetShopSellManager___c__DisplayClass67_0__OnSelectPet_b__0
               (undefined *self,undefined *x,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  
  if (x != (undefined *)0x0) {
    return *(int *)(x + 0x10) == *(int *)(self + 0x10);
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  bVar2 = (*pcVar1)();
  return bVar2;
}

