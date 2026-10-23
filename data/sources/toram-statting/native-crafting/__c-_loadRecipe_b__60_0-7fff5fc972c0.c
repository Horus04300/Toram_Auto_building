
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte __c__loadRecipe_b__60_0(undefined *self,undefined *x,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  longlong lVar3;
  
  if (DAT_7fff625e42ad == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6245a5f8);
    DAT_7fff625e42ad = '\x01';
  }
  lVar3 = FUN_7fff60c4bc00(_DAT_7fff6245a5f8);
  if ((x != (undefined *)0x0) && (lVar3 != 0)) {
    lVar3 = FUN_7fff600847d0(lVar3,*(undefined4 *)(x + 0x20),0);
    if (lVar3 != 0) {
      return *(short *)(lVar3 + 0x4c) < 1;
    }
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  bVar2 = (*pcVar1)();
  return bVar2;
}

