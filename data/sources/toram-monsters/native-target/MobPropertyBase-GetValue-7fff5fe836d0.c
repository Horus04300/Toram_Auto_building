
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * MobPropertyBase_GetValue(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  longlong lVar4;
  longlong lVar5;
  longlong lVar6;
  undefined *puVar7;
  undefined8 uVar8;
  
  if (DAT_7fff625e4ee0 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6240d7c8);
    DAT_7fff625e4ee0 = '\x01';
  }
  lVar6 = _DAT_7fff6240d7c8;
  lVar5 = *(longlong *)(self + 0x10);
  if (*(longlong *)(_DAT_7fff6240d7c8 + 0x38) == 0) {
    FUN_7fff5f47d450(&DAT_7fff624413c0);
    FUN_7fff5f47d450(&DAT_7fff62442498);
    if (*(longlong *)(lVar6 + 0x38) == 0) {
      FUN_7fff5f3dec80(lVar6);
    }
  }
  if (lVar5 == 0) {
    uVar8 = func_0x7fff5f47d470(0x7fff624551d8);
    uVar8 = FUN_7fff6116bfb0(uVar8,0);
    FUN_7fff5f47d620(uVar8,lVar6);
  }
  else {
    lVar4 = *(longlong *)(*(longlong *)(lVar6 + 0x38) + 8);
    if ((*(byte *)(lVar4 + 0x135) & 1) == 0) {
      lVar4 = FUN_7fff5f3dec00(lVar4);
    }
    lVar4 = func_0x7fff5f47c7e0(lVar5,lVar4);
    if (lVar4 != 0) {
      lVar5 = (*(longlong **)(lVar6 + 0x38))[2];
      if ((*(byte *)(lVar5 + 0x135) & 1) == 0) {
        lVar5 = FUN_7fff5f3dec00(lVar5);
      }
      iVar3 = FUN_7fff5f252ec0(0,lVar5,lVar4);
      if (iVar3 < 1) {
        return (undefined *)0x0;
      }
      lVar5 = *(longlong *)(*(longlong *)(lVar6 + 0x38) + 8);
      if ((*(byte *)(lVar5 + 0x135) & 1) == 0) {
        lVar5 = FUN_7fff5f3dec00(lVar5);
      }
      puVar7 = (undefined *)FUN_7fff5f259320(0,lVar5,lVar4,0);
      return puVar7;
    }
    lVar4 = **(longlong **)(lVar6 + 0x38);
    if ((*(byte *)(lVar4 + 0x135) & 1) == 0) {
      lVar4 = FUN_7fff5f3dec00(lVar4);
    }
    lVar5 = FUN_7fff5f252ec0(0,lVar4,lVar5);
    if (lVar5 == 0) goto LAB_7fff6068f859;
    cVar2 = FUN_7fff5f252ec0(0,_DAT_7fff62442498);
    if (cVar2 == '\0') {
      if (lVar5 == 0) {
        return (undefined *)0x0;
      }
      FUN_7fff5f253010(0,_DAT_7fff624413c0);
      return (undefined *)0x0;
    }
    if (lVar5 != 0) {
      lVar6 = *(longlong *)(*(longlong *)(lVar6 + 0x38) + 0x38);
      if ((*(byte *)(lVar6 + 0x135) & 1) == 0) {
        lVar6 = FUN_7fff5f3dec00(lVar6);
      }
      puVar7 = (undefined *)FUN_7fff5f252ec0(0,lVar6,lVar5);
      if (lVar5 != 0) {
        FUN_7fff5f253010(0,_DAT_7fff624413c0);
      }
      return puVar7;
    }
  }
  FUN_7fff5f47d660();
LAB_7fff6068f859:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar1 = (code *)swi(3);
  puVar7 = (undefined *)(*pcVar1)();
  return puVar7;
}

