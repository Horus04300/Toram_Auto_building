
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte ItemDBData_CheckWeaponItem(undefined *type,undefined *methodInfo)

{
  int iVar1;
  
  iVar1 = (int)type;
  if ((iVar1 != 0x11) && (6 < iVar1)) {
    return iVar1 < 0x14;
  }
  return 0;
}

