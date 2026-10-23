
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * BossMobBattleStatus_get_Property(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  undefined *puVar2;
  
  if (*(longlong *)(self + 0x10) != 0) {
    return *(undefined **)(*(longlong *)(self + 0x10) + 0xa0);
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  puVar2 = (undefined *)(*pcVar1)();
  return puVar2;
}

