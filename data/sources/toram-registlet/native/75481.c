
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GemCartBuffer_PetOfAttackerBuff_OnGetValue(undefined *self,undefined *id,undefined *methodInfo)

{
  int iVar1;
  
  if ((int)id == 5) {
    return *(short *)(self + 0x14) * 3;
  }
  iVar1 = 0x1e;
  if ((int)id != 6) {
    iVar1 = 0;
  }
  return iVar1;
}

