
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GuildRaidManager_RaidHeldData_get_SummonLevel(undefined *self,undefined *methodInfo)

{
  return (uint)(byte)self[0x30] << 2;
}

