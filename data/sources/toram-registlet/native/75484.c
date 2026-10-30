
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GemCartBuffer_PetOfTankerBuff_OnGetValue(undefined *self,undefined *id,undefined *methodInfo)

{
  if ((int)id == 0) {
    return 0x1e;
  }
  if ((int)id == 1) {
    return *(short *)(self + 0x14) * 3;
  }
  return 0;
}

