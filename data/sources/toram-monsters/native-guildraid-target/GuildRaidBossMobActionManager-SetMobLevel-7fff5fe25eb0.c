
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidBossMobActionManager_SetMobLevel(undefined *self,int level,undefined *methodInfo)

{
  *(int *)(self + 400) = level;
  return;
}

