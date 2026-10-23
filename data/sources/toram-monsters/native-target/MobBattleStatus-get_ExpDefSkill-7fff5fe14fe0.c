
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobBattleStatus_get_ExpDefSkill(undefined *self,undefined *methodInfo)

{
  if (*(longlong *)(self + 0x28) != 0) {
    return *(int *)(*(longlong *)(self + 0x28) + 0x1c);
  }
  return 100;
}

