
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobaOtherPlayerBattleStatus_get_ExpDefNormal(undefined *self,undefined *methodInfo)

{
  if (*(longlong *)(self + 0x38) != 0) {
    return *(int *)(*(longlong *)(self + 0x38) + 0x18);
  }
  return 100;
}

