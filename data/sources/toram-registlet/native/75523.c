
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBuffer_StartDashBuff__ctor(undefined *self,short lv,undefined *methodInfo)

{
  float fVar1;
  
  GemCartBufferBase__ctor(self,lv,(undefined *)0x0);
  fVar1 = _DAT_7ffe9c049ddc;
  *(undefined4 *)(self + 0x18) = 0;
  *(float *)(self + 0x1c) = (float)(*(short *)(self + 0x14) + 5);
  *(float *)(self + 0x20) = fVar1 - (float)(*(short *)(self + 0x14) + 5);
  return;
}

