
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobAttackBase_GetMobPatternAbnormalPercent(undefined *self,undefined *methodInfo)

{
  if (*(longlong *)(self + 0xa8) != 0) {
    return *(int *)(*(longlong *)(self + 0xa8) + 0x5c);
  }
  return -1;
}

