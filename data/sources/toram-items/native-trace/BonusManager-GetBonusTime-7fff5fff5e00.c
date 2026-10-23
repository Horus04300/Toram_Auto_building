
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
  
  if (DAT_7fff625e584e == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62450248);
    FUN_7fff5f47d450(&DAT_7fff6244dd58);
    FUN_7fff5f47d450(&DAT_7fff6244da48);
    DAT_7fff625e584e = '\x01';
  }
  afStackX_18[0] = 1.0;
  if (*(int *)(_DAT_7fff62450248 + 0xe0) == 0) {
    func_0x7fff5f47d6f0(_DAT_7fff62450248);
  }
  lVar1 = *(longlong *)(*(longlong *)(_DAT_7fff62450248 + 0xb8) + 8);
  if (lVar1 != 0) {
    cVar3 = FUN_7fff608868e0(lVar1,bonusType,afStackX_18,_DAT_7fff6244dd58);
    if (cVar3 != '\0') {
      return afStackX_18[0];
    }
    aiStackX_8[0] = 1;
    if (*(int *)(_DAT_7fff62450248 + 0xe0) == 0) {
      func_0x7fff5f47d6f0(_DAT_7fff62450248);
    }
    if (**(longlong **)(_DAT_7fff62450248 + 0xb8) != 0) {
      cVar3 = FUN_7fff608868e0(**(longlong **)(_DAT_7fff62450248 + 0xb8),bonusType,aiStackX_8,
                               _DAT_7fff6244da48);
      if (cVar3 != '\0') {
        return (float)aiStackX_8[0];
      }
      return _DAT_7fff61b52b18;
    }
  }
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  fVar4 = (float)(*pcVar2)();
  return fVar4;
}

