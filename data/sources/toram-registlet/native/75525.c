
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte GemCartBuffer_StartDashBuff_CheckTrigger(undefined *self,undefined *methodInfo)

{
  return 0.0 < *(float *)(self + 0x18);
}

