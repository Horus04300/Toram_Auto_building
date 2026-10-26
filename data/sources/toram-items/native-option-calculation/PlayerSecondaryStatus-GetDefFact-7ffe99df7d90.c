
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_GetDefFact(undefined *self,int mdef,undefined *methodInfo)

{
  int iVar1;
  
  if (mdef < 0xfb) {
    iVar1 = (int)((float)mdef * _DAT_7ffe9c04a470);
    if (0x3c < (int)((float)mdef * _DAT_7ffe9c04a470)) {
      iVar1 = 0x3c;
    }
    return iVar1;
  }
  if (0x4e2 < mdef) {
    iVar1 = 0x1e - (int)((float)(mdef + -0x4e2) * _DAT_7ffe9c04a480);
    if (0x3c < iVar1) {
      iVar1 = 0x3c;
    }
    return iVar1;
  }
  iVar1 = 0x14 - (int)((float)(mdef + -0xfa) * _DAT_7ffe9c049fd0);
  if (0x3c < iVar1) {
    iVar1 = 0x3c;
  }
  return iVar1;
}

