
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int WaveMobBattleStatus_get_NecessaryHit(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  
  if (*(longlong *)(self + 0x10) != 0) {
    return *(int *)(*(longlong *)(self + 0x10) + 0x38);
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  iVar2 = (*pcVar1)();
  return iVar2;
}

