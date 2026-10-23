
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BonusManager_GetCalcBonusValue
              (undefined *self,int baseVal,int rateType,int constType,undefined *methodInfo)

{
  code *pcVar1;
  longlong lVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  undefined8 uVar9;
  undefined8 uStack_c0;
  undefined8 *puStack_b8;
  longlong lStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  longlong lStack_98;
  undefined8 uStack_90;
  undefined8 *puStack_88;
  longlong lStack_80;
  undefined8 uStack_68;
  undefined8 uStack_60;
  longlong lStack_58;
  
  if (DAT_7fff625e5879 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62409338);
    FUN_7fff5f47d450(&DAT_7fff6247a258);
    FUN_7fff5f47d450(&DAT_7fff6247a328);
    FUN_7fff5f47d450(&DAT_7fff62409408);
    FUN_7fff5f47d450(0x7fff624094d8);
    FUN_7fff5f47d450(0x7fff6247a3f8);
    FUN_7fff5f47d450(&DAT_7fff62410060);
    FUN_7fff5f47d450(&DAT_7fff624523c0);
    FUN_7fff5f47d450(&DAT_7fff6240f020);
    DAT_7fff625e5879 = '\x01';
  }
  fVar6 = _DAT_7fff61b52cfc;
  uStack_a8 = 0;
  uStack_a0 = 0;
  lStack_98 = 0;
  fVar7 = 0.0;
  fVar8 = 0.0;
  if (*(longlong *)(self + 0x78) == 0) {
    FUN_7fff5f47d660();
LAB_7fff5fff635d:
    FUN_7fff5f47d660();
LAB_7fff5fff6363:
    FUN_7fff5f47d660();
LAB_7fff5fff6369:
    FUN_7fff5f47d660();
    FUN_7fff5f40a410();
LAB_7fff5fff6374:
    FUN_7fff5f47d660();
LAB_7fff5fff6379:
    FUN_7fff5f47d660();
LAB_7fff5fff637e:
    FUN_7fff5f47d660();
    FUN_7fff5f40a410();
    pcVar1 = (code *)swi(3);
    iVar4 = (*pcVar1)();
    return iVar4;
  }
  FUN_7fff60a8da60(&uStack_c0,*(longlong *)(self + 0x78),_DAT_7fff6240f020);
  uStack_90 = uStack_c0;
  puStack_88 = puStack_b8;
  lStack_80 = lStack_b0;
  uVar9 = 0;
LAB_7fff5fff6140:
  cVar3 = FUN_7fff60933290(&uStack_90,_DAT_7fff6247a328);
  lVar2 = lStack_80;
  if (cVar3 == '\0') {
    func_0x7fff5f4d3920(&uStack_90,_DAT_7fff6247a258);
    return (int)((fVar6 / _DAT_7fff61b52cfc) * (float)baseVal + fVar7);
  }
  if (lStack_80 != 0) {
    if (*(longlong *)(lStack_80 + 0x18) != 0) {
      cVar3 = FUN_7fff60ad2d00(*(longlong *)(lStack_80 + 0x18),rateType,_DAT_7fff62410060);
      if (cVar3 != '\0') goto LAB_7fff5fff61a6;
      if (*(longlong *)(lVar2 + 0x18) != 0) goto code_r0x7fff5fff6194;
      goto LAB_7fff5fff635d;
    }
    goto LAB_7fff5fff6379;
  }
  goto LAB_7fff5fff637e;
code_r0x7fff5fff6194:
  cVar3 = FUN_7fff60ad2d00(*(longlong *)(lVar2 + 0x18),constType,_DAT_7fff62410060);
  if (cVar3 != '\0') {
LAB_7fff5fff61a6:
    if (*(char *)(lVar2 + 0x40) != '\0') {
      if (*(longlong *)(self + 0x18) == 0) goto LAB_7fff5fff6363;
      FUN_7fff600016f0(*(longlong *)(self + 0x18),*(undefined8 *)(lVar2 + 0x10),0,0,fVar8,uVar9);
      FUN_7fff5fff04d0(lVar2,0);
    }
    if (*(longlong *)(lVar2 + 0x20) == 0) goto LAB_7fff5fff6374;
    FUN_7fff60a8da60(&uStack_68,*(longlong *)(lVar2 + 0x20),_DAT_7fff624523c0);
    uStack_a8 = uStack_68;
    uStack_a0 = uStack_60;
    lStack_98 = lStack_58;
    uStack_c0 = 0;
    puStack_b8 = &uStack_a8;
    while (cVar3 = FUN_7fff60933290(&uStack_a8,_DAT_7fff62409408), cVar3 != '\0') {
      if (lStack_98 == 0) goto LAB_7fff5fff6369;
      iVar4 = 0;
      iVar5 = iVar4;
      if (*(int *)(lStack_98 + 0x10) == constType) {
        iVar5 = *(int *)(lStack_98 + 0x14);
      }
      fVar7 = fVar7 + (float)iVar5;
      if (*(int *)(lStack_98 + 0x10) == rateType) {
        iVar4 = *(int *)(lStack_98 + 0x14);
      }
      fVar6 = fVar6 + (float)iVar4;
      fVar8 = fVar7;
    }
    func_0x7fff5f4d3920(&uStack_a8,_DAT_7fff62409338);
  }
  goto LAB_7fff5fff6140;
}

