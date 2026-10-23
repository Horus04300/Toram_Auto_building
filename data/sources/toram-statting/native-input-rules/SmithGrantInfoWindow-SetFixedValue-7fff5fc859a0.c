
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithGrantInfoWindow_SetFixedValue(undefined *self,int fixedVal,undefined *methodInfo)

{
  *(int *)(self + 0xd4) = fixedVal;
  *(int *)(self + 0xd8) = fixedVal;
  return;
}

