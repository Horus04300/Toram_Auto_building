
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBufferBase_set_Lv(undefined *self,short value,undefined *methodInfo)

{
  *(short *)(self + 0x14) = value;
  return;
}

