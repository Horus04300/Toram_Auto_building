
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte ItemDBData_CheckAvatarEquipItem(int type,undefined *methodInfo)

{
  if (type < 0x19) {
    return 0;
  }
  return type < 0x1c;
}

