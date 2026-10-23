
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float Toram_Common_Rooms_BossDifficultyLevelMethods_GetTumbleResistTime
                (float param,int difficulty,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  int iVar3;
  float fVar4;
  
  if (DAT_7ffe9cae7a30 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949540);
    DAT_7ffe9cae7a30 = '\x01';
  }
  if (*(int *)(_DAT_7ffe9c949540 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_7ffe9c949540 + 0xb8) + 0x28);
  if (difficulty < -1) {
    iVar3 = -1;
  }
  else {
    iVar3 = difficulty;
    if (3 < difficulty) {
      iVar3 = 3;
    }
  }
  if (lVar1 != 0) {
    if ((uint)((longlong)iVar3 + 1) < *(uint *)(lVar1 + 0x18)) {
      if (*(float *)(lVar1 + 0x20 + ((longlong)iVar3 + 1) * 4) <= param) {
        return param;
      }
      if (*(int *)(_DAT_7ffe9c949540 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      lVar1 = *(longlong *)(*(longlong *)(_DAT_7ffe9c949540 + 0xb8) + 0x28);
      if (difficulty < -1) {
        difficulty = -1;
      }
      else if (3 < difficulty) {
        difficulty = 3;
      }
      if (lVar1 == 0) goto LAB_7ffe9bc889da;
      if ((uint)((longlong)difficulty + 1) < *(uint *)(lVar1 + 0x18)) {
        return *(float *)(lVar1 + 0x20 + ((longlong)difficulty + 1) * 4);
      }
    }
    FUN_7ffe9996d790();
    pcVar2 = (code *)swi(3);
    fVar4 = (float)(*pcVar2)();
    return fVar4;
  }
LAB_7ffe9bc889da:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  fVar4 = (float)(*pcVar2)();
  return fVar4;
}

