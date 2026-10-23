
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte ItemDBData_IsSubWeapon(int type,undefined *methodInfo)

{
  if (((type != 8) && (4 < type - 0xfU)) && (type != 0x17)) {
    return 0;
  }
  return 1;
}

