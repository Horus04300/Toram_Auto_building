
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidRoomData_ReceiveRaidEnd(undefined *self,int subdueRewardNum,undefined *methodInfo)

{
  *(int *)(self + 0x8c) = subdueRewardNum;
  return;
}

