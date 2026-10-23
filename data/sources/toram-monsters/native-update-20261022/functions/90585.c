
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
  
  if (DAT_7ffe9cae7a2b == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949540);
    DAT_7ffe9cae7a2b = '\x01';
  }
  if (*(int *)(_DAT_7ffe9c949540 + 0xe0) == 0) {
    func_0x7ffe9996d830(_DAT_7ffe9c949540);
  }
  if (difficulty < -1) {
    difficulty = -1;
  }
  else if (3 < difficulty) {
    difficulty = 3;
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_7ffe9c949540 + 0xb8) + 0x38);
  if (lVar1 != 0) {
    lVar5 = (longlong)difficulty + 1;
    if ((uint)lVar5 < *(uint *)(lVar1 + 0x18)) {
      lVar2 = *(longlong *)(*(longlong *)(_DAT_7ffe9c949540 + 0xb8) + 0x40);
      if (lVar2 == 0) goto LAB_7ffe9bc884d2;
      if ((uint)lVar5 < *(uint *)(lVar2 + 0x18)) {
        return (int)((float)partsExp * *(float *)(lVar2 + 0x20 + lVar5 * 4) +
                    (float)exp * *(float *)(lVar1 + 0x20 + lVar5 * 4));
      }
    }
    FUN_7ffe9996d790();
    pcVar3 = (code *)swi(3);
    iVar4 = (*pcVar3)();
    return iVar4;
  }
LAB_7ffe9bc884d2:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  iVar4 = (*pcVar3)();
  return iVar4;
}

