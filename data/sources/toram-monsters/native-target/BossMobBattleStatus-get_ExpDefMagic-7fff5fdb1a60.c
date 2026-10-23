
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BossMobBattleStatus_get_ExpDefMagic(undefined *self,undefined *methodInfo)

{
  if (*(longlong *)(self + 0x38) != 0) {
    return *(int *)(*(longlong *)(self + 0x38) + 0x20);
  }
  return 100;
}

