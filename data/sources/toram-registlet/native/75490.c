
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GemCartBuffer_PractitionerBuff_OnGetValue(undefined *self,undefined *id,undefined *methodInfo)

{
  if ((int)id != 6) {
    return 0;
  }
  return 0xf - *(short *)(self + 0x14);
}

