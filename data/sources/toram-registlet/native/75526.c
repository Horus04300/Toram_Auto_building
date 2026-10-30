
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GemCartBuffer_StartDashBuff_OnGetValue(undefined *self,undefined *id,undefined *methodInfo)

{
  uint uVar1;
  
  uVar1 = 0;
  if ((int)id == 2) {
    uVar1 = (uint)(0.0 < *(float *)(self + 0x18));
  }
  return uVar1;
}

