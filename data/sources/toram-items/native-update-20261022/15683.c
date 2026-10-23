
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float BonusManager_GetBonusTime(int bonusType,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  float fVar4;
  int aiStackX_8 [4];
  float afStackX_18 [4];
  
  if (DAT_7ffe9cade0f6 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c948908);
    FUN_7ffe9996d590(&DAT_7ffe9c946e08);
    FUN_7ffe9996d590(&DAT_7ffe9c946af8);
    DAT_7ffe9cade0f6 = '\x01';
  }
  afStackX_18[0] = 1.0;
  if (*(int *)(_DAT_7ffe9c948908 + 0xe0) == 0) {
    func_0x7ffe9996d830(_DAT_7ffe9c948908);
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_7ffe9c948908 + 0xb8) + 8);
  if (lVar1 != 0) {
    cVar3 = FUN_7ffe9ad7c520(lVar1,bonusType,afStackX_18,_DAT_7ffe9c946e08);
    if (cVar3 != '\0') {
      return afStackX_18[0];
    }
    aiStackX_8[0] = 1;
    if (*(int *)(_DAT_7ffe9c948908 + 0xe0) == 0) {
      func_0x7ffe9996d830(_DAT_7ffe9c948908);
    }
    if (**(longlong **)(_DAT_7ffe9c948908 + 0xb8) != 0) {
      cVar3 = FUN_7ffe9ad7c520(**(longlong **)(_DAT_7ffe9c948908 + 0xb8),bonusType,aiStackX_8,
                               _DAT_7ffe9c946af8);
      if (cVar3 != '\0') {
        return (float)aiStackX_8[0];
      }
      return _DAT_7ffe9c049b18;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  fVar4 = (float)(*pcVar2)();
  return fVar4;
}

