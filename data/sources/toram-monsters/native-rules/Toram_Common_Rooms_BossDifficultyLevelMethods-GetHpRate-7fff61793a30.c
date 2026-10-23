
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int Toram_Common_Rooms_BossDifficultyLevelMethods_GetHpRate
              (int param,int difficulty,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  int iVar3;
  
  if (DAT_7fff625ef177 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62450e80);
    DAT_7fff625ef177 = '\x01';
  }
  if (*(int *)(_DAT_7fff62450e80 + 0xe0) == 0) {
    func_0x7fff5f47d6f0(_DAT_7fff62450e80);
  }
  lVar1 = **(longlong **)(_DAT_7fff62450e80 + 0xb8);
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
    FUN_7fff5f47d650();
    pcVar2 = (code *)swi(3);
    iVar3 = (*pcVar2)();
    return iVar3;
  }
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  iVar3 = (*pcVar2)();
  return iVar3;
}

