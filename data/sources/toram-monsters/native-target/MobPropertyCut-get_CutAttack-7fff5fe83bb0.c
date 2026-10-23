
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobPropertyCut_get_CutAttack(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  longlong lVar2;
  char cVar3;
  int iVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  int iVar8;
  
  if (DAT_7fff625e4ee4 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62422cf0);
    FUN_7fff5f47d450(&DAT_7fff62446cc0);
    FUN_7fff5f47d450(&DAT_7fff6246eab8);
    FUN_7fff5f47d450(&DAT_7fff623f8980);
    DAT_7fff625e4ee4 = '\x01';
  }
  uVar6 = *(undefined8 *)(self + 0x10);
  if (*(int *)(_DAT_7fff623f8980 + 0xe0) == 0) {
    func_0x7fff5f47d6f0();
  }
  lVar5 = *(longlong *)(*(longlong *)(_DAT_7fff623f8980 + 0xb8) + 8);
  if (lVar5 == 0) {
    if (*(int *)(_DAT_7fff623f8980 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    uVar7 = **(undefined8 **)(_DAT_7fff623f8980 + 0xb8);
    lVar5 = func_0x7fff5f44ff00(_DAT_7fff62446cc0);
    FUN_7fff60a1fa30(lVar5,uVar7,_DAT_7fff6246eab8,0);
    *(longlong *)(*(longlong *)(_DAT_7fff623f8980 + 0xb8) + 8) = lVar5;
    thunk_FUN_7fff5f491fd0();
  }
  lVar2 = _DAT_7fff62422cf0;
  if (*(longlong *)(_DAT_7fff62422cf0 + 0x38) == 0) {
    FUN_7fff5f3dec80(_DAT_7fff62422cf0);
  }
  lVar5 = FUN_7fff606965b0(uVar6,lVar5,*(undefined8 *)(*(longlong *)(lVar2 + 0x38) + 0x10));
  if (DAT_7fff625ebcf6 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff624329a0,0);
    FUN_7fff5f47d450(&DAT_7fff624413c0);
    FUN_7fff5f47d450(&DAT_7fff6245c238);
    FUN_7fff5f47d450(&DAT_7fff62461b78);
    FUN_7fff5f47d450(&DAT_7fff62442498);
    DAT_7fff625ebcf6 = '\x01';
  }
  if (lVar5 == 0) {
    uVar6 = func_0x7fff5f47d470(0x7fff624551d8);
    uVar6 = FUN_7fff6116bfb0(uVar6,0);
    uVar7 = func_0x7fff5f47d470(&DAT_7fff624329a0);
    FUN_7fff5f47d620(uVar6,uVar7);
LAB_7fff6116bdac:
    uVar6 = _DAT_7fff624329a0;
    uVar7 = func_0x7fff5f47d240();
    FUN_7fff5f47d620(uVar7,uVar6);
LAB_7fff6116bdc3:
    FUN_7fff5f47d660();
  }
  else {
    iVar8 = 0;
    lVar5 = FUN_7fff5f252ec0(0,_DAT_7fff6245c238,lVar5);
    while (lVar5 != 0) {
      cVar3 = FUN_7fff5f252ec0(0,_DAT_7fff62442498);
      if (cVar3 == '\0') {
        if (lVar5 != 0) {
          FUN_7fff5f253010(0,_DAT_7fff624413c0);
        }
        return iVar8;
      }
      if (lVar5 == 0) goto LAB_7fff6116bdc3;
      iVar4 = FUN_7fff5f252ec0(0,_DAT_7fff62461b78);
      if (0xffffffff < (ulonglong)((longlong)iVar8 + (longlong)iVar4 + 0x80000000))
      goto LAB_7fff6116bdac;
      iVar8 = iVar8 + iVar4;
    }
  }
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar1 = (code *)swi(3);
  iVar8 = (*pcVar1)();
  return iVar8;
}

