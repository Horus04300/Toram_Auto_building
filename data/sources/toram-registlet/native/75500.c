
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBuffer_SavingTechniqueBuff__ctor(undefined *self,short lv,undefined *methodInfo)

{
  GemCartBufferBase__ctor(self,lv,(undefined *)0x0);
  *(float *)(self + 0x18) = (float)(0x28 - lv);
  return;
}

