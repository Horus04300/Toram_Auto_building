
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte UIItemListManager_CheckWeaponItem(undefined *type,undefined *methodInfo)

{
  int iVar1;
  
  iVar1 = (int)type;
  if (iVar1 == 0x11) {
    return 0;
  }
  if (iVar1 - 7U < 0xd) {
    return 1;
  }
  return iVar1 == 0x17;
}

