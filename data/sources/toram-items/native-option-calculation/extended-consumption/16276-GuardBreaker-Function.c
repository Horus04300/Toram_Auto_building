
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte AvoidBreaker_Function(undefined *self,undefined *methodInfo)

{
  int iVar1;
  
  if (self[0x12] != '\0') {
    iVar1 = FUN_7ffe9bda4580(0,100);
    return iVar1 < *(short *)(self + 0x10);
  }
  return 0;
}

