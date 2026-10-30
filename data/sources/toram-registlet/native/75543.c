
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GemCartBuffer_AssassinStubEnhanceBuff_OnGetValue
              (undefined *self,undefined *id,undefined *methodInfo)

{
  if ((int)id == 2) {
    return *(short *)(self + 0x14) * 10;
  }
  if ((int)id != 4) {
    return 0;
  }
  return (int)*(short *)(self + 0x14);
}

