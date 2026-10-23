
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte UIItemListManager_CheckUseItem(undefined *type,undefined *methodInfo)

{
  int iVar1;
  
  iVar1 = (int)type;
  return (iVar1 == 5 || (iVar1 == 0x32 || iVar1 == 0x1e)) || iVar1 < 3;
}

