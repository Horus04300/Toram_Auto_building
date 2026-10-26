
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MagicBarrier_Updata(undefined *self,undefined *methodInfo)

{
  float fVar1;
  float fVar2;
  
  if (self[0x12] == '\0') {
    fVar1 = *(float *)(self + 0x1c);
    fVar2 = (float)FUN_7ffe9bda7ce0(0);
    *(float *)(self + 0x1c) = fVar1 - fVar2;
    if (fVar1 - fVar2 <= 0.0) {
      self[0x12] = 1;
    }
  }
  return;
}

