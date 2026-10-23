
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float Toram_Common_Rooms_BossDifficultyLevelMethods_GetTumbleResistTime
                (float param,int difficulty,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  int iVar3;
  float fVar4;
  
  if (DAT_7fff625ef17b == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62450e80);
    DAT_7fff625ef17b = '\x01';
  }
  if (*(int *)(_DAT_7fff62450e80 + 0xe0) == 0) {
    func_0x7fff5f47d6f0();
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_7fff62450e80 + 0xb8) + 0x28);
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
      if (*(int *)(_DAT_7fff62450e80 + 0xe0) == 0) {
        func_0x7fff5f47d6f0();
      }
      lVar1 = *(longlong *)(*(longlong *)(_DAT_7fff62450e80 + 0xb8) + 0x28);
      if (difficulty < -1) {
        difficulty = -1;
      }
      else if (3 < difficulty) {
        difficulty = 3;
      }
      if (lVar1 == 0) goto LAB_7fff61793e2a;
      if ((uint)((longlong)difficulty + 1) < *(uint *)(lVar1 + 0x18)) {
        return *(float *)(lVar1 + 0x20 + ((longlong)difficulty + 1) * 4);
      }
    }
    FUN_7fff5f47d650();
    pcVar2 = (code *)swi(3);
    fVar4 = (float)(*pcVar2)();
    return fVar4;
  }
LAB_7fff61793e2a:
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  fVar4 = (float)(*pcVar2)();
  return fVar4;
}

