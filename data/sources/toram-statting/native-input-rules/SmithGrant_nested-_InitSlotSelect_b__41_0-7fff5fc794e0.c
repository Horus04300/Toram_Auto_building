
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte SmithGrant_nested__InitSlotSelect_b__41_0(undefined *self,undefined *x,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  
  if (x == (undefined *)0x0) {
    FUN_7fff5f47d660();
    pcVar1 = (code *)swi(3);
    bVar2 = (*pcVar1)();
    return bVar2;
  }
  if ((x[0x2c] == '\0') && (*(int *)(x + 0x30) + *(int *)(x + 0x28) == 0)) {
    return 0;
  }
  return *(int *)(x + 0x20) != 0;
}

