
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartMasterData_set_LevelCap(undefined *self,short value,undefined *methodInfo)

{
  *(short *)(self + 0x18) = value;
  return;
}

