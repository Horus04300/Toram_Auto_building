
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * MapInfo_get_MobDb(undefined *self,undefined *methodInfo)

{
  return *(undefined **)(self + 0x48);
}

