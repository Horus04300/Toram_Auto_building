
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

short Toram_Common_Rooms_BossDifficultyLevelMethods_GetLevel
                (short lv,int difficulty,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  short sVar3;
  
  if (DAT_7fff625ef175 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62450e80);
    DAT_7fff625ef175 = '\x01';
  }
  if (*(int *)(_DAT_7fff62450e80 + 0xe0) == 0) {
    func_0x7fff5f47d6f0(_DAT_7fff62450e80);
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_7fff62450e80 + 0xb8) + 0x18);
  if (difficulty < -1) {
    difficulty = -1;
  }
  else if (3 < difficulty) {
    difficulty = 3;
  }
  if (lVar1 != 0) {
    if ((uint)((longlong)difficulty + 1) < *(uint *)(lVar1 + 0x18)) {
      sVar3 = lv + *(short *)(lVar1 + 0x20 + ((longlong)difficulty + 1) * 4);
      if (sVar3 < 1) {
        sVar3 = 1;
      }
      return sVar3;
    }
    FUN_7fff5f47d650();
    pcVar2 = (code *)swi(3);
    sVar3 = (*pcVar2)();
    return sVar3;
  }
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  sVar3 = (*pcVar2)();
  return sVar3;
}

