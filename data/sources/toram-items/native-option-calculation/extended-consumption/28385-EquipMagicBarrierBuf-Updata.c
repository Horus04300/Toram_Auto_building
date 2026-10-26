
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void EquipMagicBarrierBuf_Updata(undefined *self,undefined *methodInfo)

{
  float fVar1;
  float fVar2;
  
  if (self[0x1c] == '\0') {
    fVar1 = *(float *)(self + 0x28);
    fVar2 = (float)FUN_7ffe9bda7ce0(0);
    *(float *)(self + 0x28) = fVar1 - fVar2;
    if (fVar1 - fVar2 <= 0.0) {
      self[0x1c] = 1;
    }
  }
  return;
}

