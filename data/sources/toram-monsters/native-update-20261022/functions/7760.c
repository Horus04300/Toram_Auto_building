
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * GuildRaidBossMobBattleStatus_get_Element(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  undefined *puVar2;
  
  if (*(longlong *)(self + 0x20) != 0) {
    return (undefined *)(ulonglong)*(uint *)(*(longlong *)(self + 0x20) + 0x54);
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  puVar2 = (undefined *)(*pcVar1)();
  return puVar2;
}

