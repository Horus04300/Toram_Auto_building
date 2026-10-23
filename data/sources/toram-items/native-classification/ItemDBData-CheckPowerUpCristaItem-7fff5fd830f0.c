
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte ItemDBData_CheckPowerUpCristaItem(int type,undefined *methodInfo)

{
  if (type < 0x3d) {
    return 0;
  }
  return type < 0x42;
}

