
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GemCartBuffer_EatingTooFastBuff_OnGetValue(undefined *self,undefined *id,undefined *methodInfo)

{
  if (((int)id == 2) && (self[0x18] != '\0')) {
    return (int)*(short *)(self + 0x14);
  }
  return 0;
}

