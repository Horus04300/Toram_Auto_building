
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int AbsoluteFreeRate_Calc(undefined *self,int value,undefined *methodInfo)

{
  char cVar1;
  
  if (value != 0) {
    cVar1 = FUN_7ffe99a4d1d0((int)*(short *)(self + 0x10),0);
    if (cVar1 != '\0') {
      return 1;
    }
  }
  return 0;
}

