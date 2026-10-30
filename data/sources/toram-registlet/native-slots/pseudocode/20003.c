
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBag_UpdateSlotCount(undefined *self,byte value,undefined *methodInfo)

{
  self[0x20] = value;
  return;
}

