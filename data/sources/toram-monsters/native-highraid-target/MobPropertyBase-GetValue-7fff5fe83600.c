
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * MobPropertyBase_GetValue(undefined *self,int type,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  longlong lVar3;
  longlong lVar4;
  longlong lVar5;
  longlong lVar6;
  undefined *puVar7;
  undefined8 uVar8;
  
  if (DAT_7fff625e4ee1 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff624113e8);
    FUN_7fff5f47d450(&DAT_7fff62446bf8);
    FUN_7fff5f47d450(&DAT_7fff6246e9e8);
    FUN_7fff5f47d450(&DAT_7fff623f88b0);
    DAT_7fff625e4ee1 = '\x01';
  }
  lVar3 = func_0x7fff5f44ff00(_DAT_7fff623f88b0);
  func_0x7fff5f4d3920(lVar3,0);
  if (lVar3 == 0) {
    FUN_7fff5f47d660();
    pcVar1 = (code *)swi(3);
    puVar7 = (undefined *)(*pcVar1)();
    return puVar7;
  }
  *(int *)(lVar3 + 0x10) = type;
  lVar6 = *(longlong *)(self + 0x10);
  lVar4 = func_0x7fff5f44ff00(_DAT_7fff62446bf8);
  FUN_7fff60a1d7e0(lVar4,lVar3,_DAT_7fff6246e9e8,0);
  lVar3 = _DAT_7fff624113e8;
  if (*(longlong *)(_DAT_7fff624113e8 + 0x38) == 0) {
    FUN_7fff5f47d450(&DAT_7fff624413c0);
    FUN_7fff5f47d450(&DAT_7fff62442498);
    if (*(longlong *)(lVar3 + 0x38) == 0) {
      FUN_7fff5f3dec80(lVar3);
    }
  }
  if (lVar6 == 0) {
    uVar8 = func_0x7fff5f47d470(0x7fff624551d8);
    uVar8 = FUN_7fff6116bfb0(uVar8,0);
    FUN_7fff5f47d620(uVar8,lVar3);
LAB_7fff6068fa0e:
    FUN_7fff5f47d660();
  }
  else {
    if (lVar4 == 0) {
      uVar8 = func_0x7fff5f47d470(0x7fff6243d500);
      uVar8 = FUN_7fff6116bfb0(uVar8,0);
      FUN_7fff5f47d620(uVar8,lVar3);
      pcVar1 = (code *)swi(3);
      puVar7 = (undefined *)(*pcVar1)();
      return puVar7;
    }
    lVar5 = **(longlong **)(lVar3 + 0x38);
    if ((*(byte *)(lVar5 + 0x135) & 1) == 0) {
      lVar5 = FUN_7fff5f3dec00(lVar5);
    }
    lVar6 = FUN_7fff5f252ec0(0,lVar5,lVar6);
    while (lVar6 != 0) {
      cVar2 = FUN_7fff5f252ec0(0,_DAT_7fff62442498);
      if (cVar2 == '\0') {
        if (lVar6 != 0) {
          FUN_7fff5f253010(0,_DAT_7fff624413c0);
        }
        return (undefined *)0x0;
      }
      if (lVar6 == 0) goto LAB_7fff6068fa0e;
      lVar5 = *(longlong *)(*(longlong *)(lVar3 + 0x38) + 0x18);
      if ((*(byte *)(lVar5 + 0x135) & 1) == 0) {
        lVar5 = FUN_7fff5f3dec00(lVar5);
      }
      puVar7 = (undefined *)FUN_7fff5f252ec0(0,lVar5,lVar6);
      cVar2 = (**(code **)(lVar4 + 0x18))
                        (*(undefined8 *)(lVar4 + 0x40),puVar7,*(undefined8 *)(lVar4 + 0x28));
      if (cVar2 != '\0') {
        if (lVar6 != 0) {
          FUN_7fff5f253010(0,_DAT_7fff624413c0);
        }
        return puVar7;
      }
    }
  }
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar1 = (code *)swi(3);
  puVar7 = (undefined *)(*pcVar1)();
  return puVar7;
}

