
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GemCartBuffer_ManaCrystalAccelerationBuff_OnGetValue
              (undefined *self,undefined *id,undefined *methodInfo)

{
  if ((int)id != 2) {
    return 0;
  }
  return (10 - *(short *)(self + 0x14)) * 10;
}

