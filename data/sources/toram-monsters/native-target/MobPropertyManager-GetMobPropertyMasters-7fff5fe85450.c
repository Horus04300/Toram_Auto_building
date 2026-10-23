
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * MobPropertyManager_GetMobPropertyMasters(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  longlong lVar4;
  longlong lVar5;
  undefined8 uVar6;
  undefined *puVar7;
  longlong lStackX_8;
  undefined8 uStack_38;
  longlong *plStack_30;
  longlong lStack_28;
  undefined8 uStack_20;
  longlong *plStack_18;
  longlong lStack_10;
  
  if (DAT_7fff625e4ed8 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62431900);
    FUN_7fff5f47d450(&DAT_7fff62431a88);
    FUN_7fff5f47d450(&DAT_7fff6244b550);
    FUN_7fff5f47d450(&DAT_7fff6244b610);
    FUN_7fff5f47d450(0x7fff6244b6d8);
    FUN_7fff5f47d450(&DAT_7fff624413c0);
    FUN_7fff5f47d450(&DAT_7fff6245cc90);
    FUN_7fff5f47d450(&DAT_7fff62462768);
    FUN_7fff5f47d450(&DAT_7fff62442498);
    FUN_7fff5f47d450(&DAT_7fff62444388);
    FUN_7fff5f47d450(&DAT_7fff62444510);
    FUN_7fff5f47d450(&DAT_7fff624442c0);
    FUN_7fff5f47d450(&DAT_7fff624758e0);
    FUN_7fff5f47d450(&DAT_7fff624030f0);
    DAT_7fff625e4ed8 = '\x01';
  }
  uStack_20 = 0;
  plStack_18 = (longlong *)0x0;
  lStack_10 = 0;
  lStackX_8 = 0;
  lVar4 = func_0x7fff5f44ff00(_DAT_7fff624758e0);
  FUN_7fff60a943d0(lVar4,_DAT_7fff624442c0);
  if ((*(longlong *)(self + 0x10) != 0) &&
     (iVar3 = func_0x7fff607e24e0(*(longlong *)(self + 0x10),_DAT_7fff62431900), 0 < iVar3)) {
    if ((*(longlong *)(self + 0x10) == 0) ||
       (lVar5 = FUN_7fff607dcb60(*(longlong *)(self + 0x10),_DAT_7fff62431a88), lVar5 == 0))
    goto LAB_7fff5fe8574e;
    FUN_7fff60a4b980(&uStack_38,lVar5,_DAT_7fff624030f0);
    uStack_20 = uStack_38;
    plStack_18 = plStack_30;
    lStack_10 = lStack_28;
    while (cVar2 = FUN_7fff60941650(&uStack_20,_DAT_7fff6244b610), cVar2 != '\0') {
      if (lStack_10 == 0) goto LAB_7fff5fe8576f;
      if (*(longlong *)(lStack_10 + 0x10) == 0) goto LAB_7fff5fe8576a;
      lStackX_8 = FUN_7fff5f252ec0(0,_DAT_7fff6245cc90);
      uStack_38 = 0;
      plStack_30 = &lStackX_8;
      while( true ) {
        if (lStackX_8 == 0) goto LAB_7fff5fe8575f;
        cVar2 = FUN_7fff5f252ec0(0,_DAT_7fff62442498);
        if (cVar2 == '\0') break;
        if (lStackX_8 == 0) goto LAB_7fff5fe8575a;
        uVar6 = FUN_7fff5f252ec0(0,_DAT_7fff62462768);
        if (lVar4 == 0) goto LAB_7fff5fe85754;
        FUN_7fff5f253100(lVar4,uVar6,_DAT_7fff62444388);
      }
      if (lStackX_8 != 0) {
        FUN_7fff5f253010(0,_DAT_7fff624413c0);
      }
    }
    func_0x7fff5f4d3920(&uStack_20,_DAT_7fff6244b550);
  }
  if (lVar4 != 0) {
    puVar7 = (undefined *)FUN_7fff60a940e0(lVar4,_DAT_7fff62444510);
    return puVar7;
  }
LAB_7fff5fe8574e:
  FUN_7fff5f47d660();
LAB_7fff5fe85754:
  FUN_7fff5f47d660();
LAB_7fff5fe8575a:
  FUN_7fff5f47d660();
LAB_7fff5fe8575f:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
LAB_7fff5fe8576a:
  FUN_7fff5f47d660();
LAB_7fff5fe8576f:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar1 = (code *)swi(3);
  puVar7 = (undefined *)(*pcVar1)();
  return puVar7;
}

