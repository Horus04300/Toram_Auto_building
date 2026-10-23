
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte ItemData_get_SlotMax(undefined *self,undefined *methodInfo)

{
  if (2 < *(int *)(self + 0x38) - 0x11U) {
    return self[0x44];
  }
  return 0;
}

