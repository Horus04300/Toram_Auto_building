
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte UIItemListManager_CheckPowerCristaItem(undefined *type,undefined *methodInfo)

{
  if ((int)type < 0x3d) {
    return 0;
  }
  return (int)type < 0x42;
}

