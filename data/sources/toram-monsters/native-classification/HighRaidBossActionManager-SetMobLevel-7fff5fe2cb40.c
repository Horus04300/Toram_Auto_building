
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void HighRaidBossActionManager_SetMobLevel(undefined *self,int level,undefined *methodInfo)

{
  *(int *)(self + 0x160) = level;
  return;
}

