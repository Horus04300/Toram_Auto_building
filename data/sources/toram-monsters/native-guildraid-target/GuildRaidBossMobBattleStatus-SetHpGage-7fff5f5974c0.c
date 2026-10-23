
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidBossMobBattleStatus_SetHpGage(undefined *self,int gage,undefined *methodInfo)

{
  *(int *)(self + 0x50) = gage;
  return;
}

