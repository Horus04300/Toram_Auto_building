
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte GemCartBufferBase_get_IsCoolDown(undefined *self,undefined *methodInfo)

{
  return 0.0 < *(float *)(self + 0x10);
}

