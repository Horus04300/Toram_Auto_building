
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MobPartsStatus_get_IsDead(undefined *self,undefined *methodInfo)

{
  return *(int *)(self + 0x30) == 0;
}

