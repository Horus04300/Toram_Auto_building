
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float BonusManager_GetBonusPercentValue(undefined *self,int type,undefined *methodInfo)

{
  int iVar1;
  
  iVar1 = BonusManager_getDataBonusValue(self,type,(undefined *)0x0);
  return (float)iVar1 / _DAT_7ffe9c049cfc;
}

