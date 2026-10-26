
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int EquipRateBarrierBuf_GetBarrierValue(undefined *self,undefined *status,undefined *methodInfo)

{
  return *(int *)(self + 0x20);
}

