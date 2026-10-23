
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GuildRaidBossMobBattleStatus_get_MaxHp(undefined *self,undefined *methodInfo)

{
  int iVar1;
  int iVar2;
  float fVar3;
  double dVar4;
  
  if (DAT_7ffe9cadd50c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    DAT_7ffe9cadd50c = '\x01';
  }
  iVar2 = *(int *)(self + 0x50);
  iVar1 = iVar2 * 4;
  if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  fVar3 = (float)(iVar2 * iVar2) / _DAT_7ffe9c049cfc;
  if (DAT_7ffe9cad9e26 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    DAT_7ffe9cad9e26 = '\x01';
  }
  if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  dVar4 = System_Math_Round((double)fVar3,2,0,(undefined *)0x0);
  return (int)((dVar4 + _DAT_7ffe9c04a7f8) *
              (double)((float)(int)((float)(iVar1 * iVar1) / _DAT_7ffe9c049ef0 +
                                   (float)(iVar1 + 0x51)) *
                      ((float)iVar1 / _DAT_7ffe9c049ce4 + _DAT_7ffe9c049e64)));
}

