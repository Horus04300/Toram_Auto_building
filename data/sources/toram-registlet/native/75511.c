
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GemCartBuffer_SilentRechargeBuff_OnGetValue(undefined *self,undefined *id,undefined *methodInfo)

{
  if ((int)id != 7) {
    return 0;
  }
  return *(short *)(self + 0x14) * 5;
}

