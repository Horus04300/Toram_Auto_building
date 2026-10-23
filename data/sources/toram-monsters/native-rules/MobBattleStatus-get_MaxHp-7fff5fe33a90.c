
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobBattleStatus_get_MaxHp(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  
  if (*(longlong *)(self + 0x10) != 0) {
    return *(int *)(*(longlong *)(self + 0x10) + 0x30);
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  iVar2 = (*pcVar1)();
  return iVar2;
}

