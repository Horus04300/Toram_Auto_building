
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte AbsoluteHitRate_Function(undefined *self,undefined *methodInfo)

{
  short sVar1;
  int iVar2;
  
  sVar1 = *(short *)(self + 0x10);
  iVar2 = FUN_7ffe9bda4580(0,100);
  return iVar2 < sVar1;
}

