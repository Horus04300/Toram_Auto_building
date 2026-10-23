
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidRoomData_SetGuildRaidLevel(undefined *self,short level,undefined *methodInfo)

{
  *(short *)(self + 0xb0) = level;
  return;
}

