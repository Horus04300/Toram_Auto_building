
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GemCartBuffer_InflexibilityEmergingBuff_OnGetValue
              (undefined *self,undefined *id,undefined *methodInfo)

{
  int iVar1;
  int iVar2;
  
  if ((int)id != 2) {
    return 0;
  }
  iVar1 = (4 - *(short *)(self + 0x14)) * 3;
  iVar2 = 3;
  if (3 < iVar1) {
    iVar2 = iVar1;
  }
  return iVar2;
}

