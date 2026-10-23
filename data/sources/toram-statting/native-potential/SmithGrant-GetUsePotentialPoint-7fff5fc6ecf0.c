
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SmithGrant_GetUsePotentialPoint(undefined *self,undefined *methodInfo)

{
  undefined2 uVar1;
  undefined2 uVar2;
  code *pcVar3;
  short sVar4;
  int iVar5;
  longlong lVar6;
  longlong lVar7;
  longlong *property;
  longlong lVar8;
  longlong lVar9;
  undefined8 uVar10;
  uint uVar11;
  longlong lVar12;
  undefined *puStackX_20;
  undefined *apuStack_48 [2];
  
  if (DAT_7fff625e422a == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62419050,0,0);
    FUN_7fff5f47d450(&DAT_7fff62450498);
    FUN_7fff5f47d450(&DAT_7fff624061f8);
    DAT_7fff625e422a = '\x01';
  }
  apuStack_48[0] = (undefined *)0x0;
  puStackX_20 = (undefined *)0x0;
  if (*(longlong *)(self + 0x120) != 0) {
    lVar6 = FUN_7fff5fc68e10(*(longlong *)(self + 0x120),0);
    if ((*(longlong *)(self + 0x120) != 0) &&
       (lVar7 = FUN_7fff5fc68f40(*(longlong *)(self + 0x120),0), lVar6 != 0)) {
      property = (longlong *)func_0x7fff5f47c850(_DAT_7fff62419050,*(undefined4 *)(lVar6 + 0x18));
      uVar11 = 0;
      iVar5 = FUN_7fff6068aa20(property,_DAT_7fff624061f8);
      if (0 < iVar5) {
        do {
          if (*(uint *)(lVar6 + 0x18) <= uVar11) {
LAB_7fff5fc6ef41:
            FUN_7fff5f47d650();
            pcVar3 = (code *)swi(3);
            iVar5 = (*pcVar3)();
            return iVar5;
          }
          lVar12 = (longlong)(int)uVar11;
          uVar1 = *(undefined2 *)(lVar6 + 0x20 + lVar12 * 2);
          if (lVar7 == 0) goto LAB_7fff5fc6ef2b;
          if (*(uint *)(lVar7 + 0x18) <= uVar11) goto LAB_7fff5fc6ef41;
          uVar2 = *(undefined2 *)(lVar7 + 0x20 + lVar12 * 2);
          lVar8 = func_0x7fff5f44ff00(_DAT_7fff62450498);
          FUN_7fff617759d0(lVar8,uVar1,uVar2,0);
          if (property == (longlong *)0x0) goto LAB_7fff5fc6ef2b;
          if ((lVar8 != 0) &&
             (lVar9 = func_0x7fff5f47c7e0(lVar8,*(undefined8 *)(*property + 0x40)), lVar9 == 0)) {
            uVar10 = func_0x7fff5f47d0b0();
            FUN_7fff5f47d620(uVar10,0);
            pcVar3 = (code *)swi(3);
            iVar5 = (*pcVar3)();
            return iVar5;
          }
          if (*(uint *)(property + 3) <= uVar11) goto LAB_7fff5fc6ef41;
          property[lVar12 + 4] = lVar8;
          thunk_FUN_7fff5f491fd0();
          uVar11 = uVar11 + 1;
          iVar5 = FUN_7fff6068aa20(property,_DAT_7fff624061f8);
        } while ((int)uVar11 < iVar5);
      }
      SmithGrant_EnhanceGetPropertyPosition
                (self,*(undefined **)(self + 0x148),(undefined *)property,(undefined *)apuStack_48,
                 (undefined *)&puStackX_20,(undefined *)0x0);
      sVar4 = SmithGrant_CalcUsePotentialPoint
                        (self,*(undefined **)(self + 0x148),apuStack_48[0],puStackX_20,0,
                         (undefined *)0x0);
      return (int)sVar4;
    }
  }
LAB_7fff5fc6ef2b:
  FUN_7fff5f47d660();
  pcVar3 = (code *)swi(3);
  iVar5 = (*pcVar3)();
  return iVar5;
}

