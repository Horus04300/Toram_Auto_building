
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte ItemDBData_CheckEquipItem(int type,undefined *methodInfo)

{
  if (type < 7) {
    return 0;
  }
  return type < 0x1c;
}

