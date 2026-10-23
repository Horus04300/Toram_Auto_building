
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int Toram_Common_Rooms_BossDifficultyLevelMethods_GetExp
              (int exp,int partsExp,int difficulty,undefined *methodInfo)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  int iVar4;
  longlong lVar5;
  
  if (DAT_7fff625ef176 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62450e80);
    DAT_7fff625ef176 = '\x01';
  }
  if (*(int *)(_DAT_7fff62450e80 + 0xe0) == 0) {
    func_0x7fff5f47d6f0(_DAT_7fff62450e80);
  }
  if (difficulty < -1) {
    difficulty = -1;
  }
  else if (3 < difficulty) {
    difficulty = 3;
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_7fff62450e80 + 0xb8) + 0x38);
  if (lVar1 != 0) {
    lVar5 = (longlong)difficulty + 1;
    if ((uint)lVar5 < *(uint *)(lVar1 + 0x18)) {
      lVar2 = *(longlong *)(*(longlong *)(_DAT_7fff62450e80 + 0xb8) + 0x40);
      if (lVar2 == 0) goto LAB_7fff61793922;
      if ((uint)lVar5 < *(uint *)(lVar2 + 0x18)) {
        return (int)((float)partsExp * *(float *)(lVar2 + 0x20 + lVar5 * 4) +
                    (float)exp * *(float *)(lVar1 + 0x20 + lVar5 * 4));
      }
    }
    FUN_7fff5f47d650();
    pcVar3 = (code *)swi(3);
    iVar4 = (*pcVar3)();
    return iVar4;
  }
LAB_7fff61793922:
  FUN_7fff5f47d660();
  pcVar3 = (code *)swi(3);
  iVar4 = (*pcVar3)();
  return iVar4;
}

