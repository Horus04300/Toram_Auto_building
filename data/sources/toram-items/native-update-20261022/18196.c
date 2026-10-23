
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte UIItemListManager_CheckCristaItem(undefined *type,undefined *methodInfo)

{
  int iVar1;
  
  iVar1 = (int)type;
  if (iVar1 - 0x1fU < 6) {
    return 1;
  }
  if (iVar1 < 0x3d) {
    return 0;
  }
  return iVar1 < 0x42;
}

