
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidRoomData_SetCurrentHpCount(undefined *self,byte hpCount,undefined *methodInfo)

{
  uint uVar1;
  
  *(ushort *)(self + 0xb4) = (ushort)hpCount;
  uVar1 = (uint)hpCount << 2;
  if (uVar1 < 0x28) {
    uVar1 = 0x28;
  }
  *(uint *)(self + 0xac) = uVar1;
  return;
}

