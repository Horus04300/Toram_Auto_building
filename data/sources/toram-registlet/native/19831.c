
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBufferBase_Update(undefined *self,undefined *methodInfo)

{
  float fVar1;
  float fVar2;
  
  fVar2 = *(float *)(self + 0x10);
  if (0.0 < fVar2) {
    fVar1 = (float)FUN_7ffe9bda7ce0(0);
    fVar2 = fVar2 - fVar1;
    *(float *)(self + 0x10) = fVar2;
    if (fVar2 <= 0.0) {
      *(undefined4 *)(self + 0x10) = 0;
    }
  }
  return;
}

