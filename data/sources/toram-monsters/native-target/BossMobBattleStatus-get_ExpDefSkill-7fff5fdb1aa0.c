
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BossMobBattleStatus_get_ExpDefSkill(undefined *self,undefined *methodInfo)

{
  if (*(longlong *)(self + 0x38) != 0) {
    return *(int *)(*(longlong *)(self + 0x38) + 0x1c);
  }
  return 100;
}

