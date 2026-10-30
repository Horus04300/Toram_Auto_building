
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GemCartBuffer_LonelyBuff_OnGetValue(undefined *self,undefined *id,undefined *methodInfo)

{
  int iVar1;
  
  iVar1 = 100;
  if ((int)id != 2) {
    iVar1 = 0;
  }
  return iVar1;
}

