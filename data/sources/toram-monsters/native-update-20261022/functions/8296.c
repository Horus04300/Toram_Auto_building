
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int WaveMobBattleStatus_get_ExpDefMagic(undefined *self,undefined *methodInfo)

{
  if (*(longlong *)(self + 0x28) != 0) {
    return *(int *)(*(longlong *)(self + 0x28) + 0x20);
  }
  return 100;
}

