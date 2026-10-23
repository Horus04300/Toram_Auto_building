
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte ItemDBData_CheckArmorAbility(undefined *armorItem,undefined *type,undefined *methodInfo)

{
  if (armorItem != (undefined *)0x0) {
    return (armorItem[0x53] & 3) == (byte)type;
  }
  return 0;
}

