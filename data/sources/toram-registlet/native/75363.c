
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GemCartBuffer_BackwardWarningBuff_OnGetValue
              (undefined *self,undefined *id,undefined *methodInfo)

{
  if ((int)id != 1) {
    return 0;
  }
  return (int)*(short *)(self + 0x14);
}

