
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte ItemDBData_CheckWeaponItem(int type,undefined *methodInfo)

{
  if ((type != 0x11) && (6 < type)) {
    return type < 0x14;
  }
  return 0;
}

