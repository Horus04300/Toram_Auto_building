
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int ItemManager_GetSelectItemEquipType(undefined *self,int itemType,undefined *methodInfo)

{
  switch(itemType) {
  case 7:
  case 8:
  case 9:
  case 10:
  case 0xb:
  case 0xc:
  case 0xd:
  case 0xe:
  case 0xf:
  case 0x10:
    return 1;
  case 0x11:
  case 0x12:
  case 0x13:
  case 0x17:
    return 2;
  case 0x14:
    return 3;
  case 0x15:
    return 4;
  case 0x16:
    return 5;
  default:
    return 0;
  }
}

