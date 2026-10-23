
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

short HighRaidRoomData_get_AreaLevel(undefined *self,undefined *methodInfo)

{
  if (*(longlong *)(self + 0x30) != 0) {
    return *(short *)(*(longlong *)(self + 0x30) + 0x22);
  }
  return 0;
}

