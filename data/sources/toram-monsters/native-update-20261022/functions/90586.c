
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int Toram_Common_Rooms_BossDifficultyLevelMethods_GetHpRate
              (int param,int difficulty,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  int iVar3;
  
  if (DAT_7ffe9cae7a2c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949540);
    DAT_7ffe9cae7a2c = '\x01';
  }
  if (*(int *)(_DAT_7ffe9c949540 + 0xe0) == 0) {
    func_0x7ffe9996d830(_DAT_7ffe9c949540);
  }
  lVar1 = **(longlong **)(_DAT_7ffe9c949540 + 0xb8);
  if (difficulty < -1) {
    difficulty = -1;
  }
  else if (3 < difficulty) {
    difficulty = 3;
  }
  if (lVar1 != 0) {
    if ((uint)((longlong)difficulty + 1) < *(uint *)(lVar1 + 0x18)) {
      return (int)((float)param * *(float *)(lVar1 + 0x20 + ((longlong)difficulty + 1) * 4));
    }
    FUN_7ffe9996d790();
    pcVar2 = (code *)swi(3);
    iVar3 = (*pcVar2)();
    return iVar3;
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar3 = (*pcVar2)();
  return iVar3;
}

