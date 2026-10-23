
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte __c__DisplayClass72_0__GetPowerUpCristaOrderList_b__0
               (undefined *self,undefined *x,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  
  if ((x != (undefined *)0x0) && (*(longlong *)(x + 0x28) != 0)) {
    return *(int *)(*(longlong *)(x + 0x28) + 0x48) == *(int *)(self + 0x10);
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  bVar2 = (*pcVar1)();
  return bVar2;
}

