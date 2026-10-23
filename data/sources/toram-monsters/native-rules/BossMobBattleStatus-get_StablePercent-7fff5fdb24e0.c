
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float BossMobBattleStatus_get_StablePercent(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  float fVar3;
  
  if (*(longlong *)(self + 0x18) == 0) {
    FUN_7fff5f47d660();
    pcVar1 = (code *)swi(3);
    fVar3 = (float)(*pcVar1)();
    return fVar3;
  }
  cVar2 = FUN_7fff5ffe5620(*(longlong *)(self + 0x18),0x17);
  if (cVar2 == '\0') {
    return _DAT_7fff61b52b18;
  }
  return _DAT_7fff61b52cc8;
}

