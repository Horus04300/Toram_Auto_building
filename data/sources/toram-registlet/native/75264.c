
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GemCartBuffer_AirSlideCompressionBuff_OnGetValue
              (undefined *self,undefined *id,undefined *methodInfo)

{
  if ((int)id == 2) {
    return 0x32;
  }
  if ((int)id == 4) {
    return *(short *)(self + 0x14) * 5;
  }
  return 0;
}

