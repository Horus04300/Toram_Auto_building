
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_get_AntiVirus(undefined *self,undefined *methodInfo)

{
  int iVar1;
  
  iVar1 = PlayerSecondaryStatus_CalcAntiVirus(self,(undefined *)0x0);
  if (100 < iVar1) {
    iVar1 = 100;
  }
  return iVar1;
}

