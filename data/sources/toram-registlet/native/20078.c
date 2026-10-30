
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartMasterData_set_Id(undefined *self,short value,undefined *methodInfo)

{
  *(short *)(self + 0x10) = value;
  return;
}

