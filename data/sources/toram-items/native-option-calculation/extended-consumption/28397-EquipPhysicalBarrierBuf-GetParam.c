
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int EquipMagicBarrierBuf_GetParam(undefined *self,int id,undefined *methodInfo)

{
  if (id != 0x32) {
    return 0;
  }
  return *(int *)(self + 0x20);
}

