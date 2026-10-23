
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte UIItemListManager_CheckAvatarEquipItem(undefined *type,undefined *methodInfo)

{
  if ((int)type < 0x19) {
    return 0;
  }
  return (int)type < 0x1c;
}

