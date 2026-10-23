
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte EnemyMobActionManagerBase_get_IsDead(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  
  lVar1 = *(longlong *)(self + 0x78);
  if ((lVar1 != 0) && (*(char *)(lVar1 + 0x3d) != '\0')) {
    return *(int *)(lVar1 + 0x10) < 1;
  }
  return 0;
}

