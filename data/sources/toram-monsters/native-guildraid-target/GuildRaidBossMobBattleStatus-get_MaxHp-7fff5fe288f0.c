
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GuildRaidBossMobBattleStatus_get_MaxHp(undefined *self,undefined *methodInfo)

{
  int iVar1;
  int iVar2;
  float fVar3;
  double dVar4;
  
  if (DAT_7fff625e4c64 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff624700a0);
    DAT_7fff625e4c64 = '\x01';
  }
  iVar2 = *(int *)(self + 0x50);
  iVar1 = iVar2 * 4;
  if (*(int *)(_DAT_7fff624700a0 + 0xe0) == 0) {
    func_0x7fff5f47d6f0();
  }
  fVar3 = (float)(iVar2 * iVar2) / _DAT_7fff61b52cfc;
  if (DAT_7fff625e15a2 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff624700a0);
    DAT_7fff625e15a2 = '\x01';
  }
  if (*(int *)(_DAT_7fff624700a0 + 0xe0) == 0) {
    func_0x7fff5f47d6f0();
  }
  dVar4 = System_Math_Round((double)fVar3,2,(undefined *)0x0,(undefined *)0x0);
  return (int)((dVar4 + _DAT_7fff61b53808) *
              (double)((float)(int)((float)(iVar1 * iVar1) / _DAT_7fff61b52ef0 +
                                   (float)(iVar1 + 0x51)) *
                      ((float)iVar1 / _DAT_7fff61b52ce4 + _DAT_7fff61b52e64)));
}

