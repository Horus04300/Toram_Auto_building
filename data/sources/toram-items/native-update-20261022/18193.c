
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte UIItemListManager_CheckEquipItem(undefined *type,undefined *methodInfo)

{
  if ((int)type < 7) {
    return 0;
  }
  return (int)type < 0x1c;
}

