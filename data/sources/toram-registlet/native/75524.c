
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBuffer_StartDashBuff_Update(undefined *self,undefined *methodInfo)

{
  float fVar1;
  float fVar2;
  
  GemCartBufferBase_Update(self,(undefined *)0x0);
  fVar2 = *(float *)(self + 0x18);
  if (0.0 < fVar2) {
    fVar1 = (float)FUN_7ffe9bda7ce0(0);
    fVar2 = fVar2 - fVar1;
    *(float *)(self + 0x18) = fVar2;
    if (fVar2 < 0.0) {
      *(undefined4 *)(self + 0x18) = 0;
    }
  }
  fVar2 = *(float *)(self + 0x20);
  if (0.0 < fVar2) {
    fVar1 = (float)FUN_7ffe9bda7ce0(0);
    fVar2 = fVar2 - fVar1;
    *(float *)(self + 0x20) = fVar2;
    if (fVar2 <= 0.0) {
      *(undefined4 *)(self + 0x20) = 0;
    }
  }
  return;
}

