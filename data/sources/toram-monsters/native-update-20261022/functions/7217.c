
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BossMobBattleStatus_get_Level(undefined *self,undefined *methodInfo)

{
  undefined4 uVar1;
  code *pcVar2;
  short sVar3;
  int iVar4;
  
  if (DAT_7ffe9cadd1d1 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949540);
    DAT_7ffe9cadd1d1 = '\x01';
  }
  if (*(longlong *)(self + 0x10) != 0) {
    sVar3 = *(short *)(self + 0x28);
    uVar1 = *(undefined4 *)(*(longlong *)(self + 0x10) + 0x28);
    if (*(int *)(_DAT_7ffe9c949540 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    sVar3 = Toram_Common_Rooms_BossDifficultyLevelMethods_GetLevel
                      ((short)uVar1,(int)sVar3,(undefined *)0x0);
    return (int)sVar3;
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar4 = (*pcVar2)();
  return iVar4;
}

