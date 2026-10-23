
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithGrantInfoWindow_FromOnDetail(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  longlong lVar2;
  undefined *self_00;
  
  if (DAT_7fff625e4261 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6244da18);
    DAT_7fff625e4261 = '\x01';
  }
  lVar2 = FUN_7fff618a1b90(self,0);
  if (lVar2 != 0) {
    lVar2 = FUN_7fff618c7030(lVar2,0);
    if (lVar2 != 0) {
      self_00 = (undefined *)FUN_7fff60678610(lVar2,_DAT_7fff6244da18);
      if (self_00 != (undefined *)0x0) {
        SmithGrant_OnDetailButton(self_00,*(int *)(self + 0xa0),(undefined *)0x0);
        *(undefined4 *)(self + 0xa0) = 0;
        return;
      }
    }
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

