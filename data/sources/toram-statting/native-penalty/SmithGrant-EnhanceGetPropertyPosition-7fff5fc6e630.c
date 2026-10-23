
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithGrant_EnhanceGetPropertyPosition
               (undefined *self,undefined *item,undefined *property,undefined *changeProperties,
               undefined *newProperties,undefined *methodInfo)

{
  uint uVar1;
  short sVar2;
  short sVar3;
  undefined2 uVar4;
  undefined2 uVar5;
  longlong lVar6;
  longlong lVar7;
  longlong *plVar8;
  code *pcVar9;
  undefined4 uVar10;
  int iVar11;
  undefined8 uVar12;
  longlong *plVar13;
  longlong lVar14;
  longlong lVar15;
  longlong lVar16;
  uint uVar17;
  uint uStackX_10;
  
  if (DAT_7fff625e422b == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62419050);
    FUN_7fff5f47d450(&DAT_7fff62450498);
    FUN_7fff5f47d450(&DAT_7fff624061f8);
    FUN_7fff5f47d450(&DAT_7fff62406d58);
    DAT_7fff625e422b = '\x01';
  }
  if (item != (undefined *)0x0) {
    lVar6 = *(longlong *)(item + 0x10);
    lVar7 = *(longlong *)(item + 0x18);
    uVar12 = func_0x7fff5f47c850(_DAT_7fff62419050,10);
    *(undefined8 *)changeProperties = uVar12;
    thunk_FUN_7fff5f491fd0();
    uVar12 = func_0x7fff5f47c850(_DAT_7fff62419050,10);
    *(undefined8 *)newProperties = uVar12;
    thunk_FUN_7fff5f491fd0();
    uVar10 = FUN_7fff6068aa20(property,_DAT_7fff624061f8);
    plVar13 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62419050,uVar10);
    uVar17 = 0;
    iVar11 = FUN_7fff6068aa20(property,_DAT_7fff624061f8);
    if (0 < iVar11) {
      do {
        if (property == (undefined *)0x0) goto LAB_7fff5fc6ec78;
        if (*(uint *)(property + 0x18) <= uVar17) goto LAB_7fff5fc6ecde;
        uVar12 = *(undefined8 *)(property + (longlong)(int)uVar17 * 8 + 0x20);
        lVar14 = func_0x7fff5f44ff00(_DAT_7fff62450498);
        FUN_7fff61775990(lVar14,uVar12,0);
        if (plVar13 == (longlong *)0x0) goto LAB_7fff5fc6ec78;
        if ((lVar14 != 0) &&
           (lVar15 = func_0x7fff5f47c7e0(lVar14,*(undefined8 *)(*plVar13 + 0x40)), lVar15 == 0)) {
          uVar12 = func_0x7fff5f47d0b0();
          FUN_7fff5f47d620(uVar12,0);
          pcVar9 = (code *)swi(3);
          (*pcVar9)();
          return;
        }
        if (*(uint *)(plVar13 + 3) <= uVar17) goto LAB_7fff5fc6ecde;
        plVar13[(longlong)(int)uVar17 + 4] = lVar14;
        thunk_FUN_7fff5f491fd0();
        uVar17 = uVar17 + 1;
        iVar11 = FUN_7fff6068aa20(property,_DAT_7fff624061f8);
      } while ((int)uVar17 < iVar11);
    }
    uVar17 = 0;
    iVar11 = FUN_7fff6068aa20(lVar6,_DAT_7fff62406d58);
    if (0 < iVar11) {
      do {
        if (lVar6 == 0) goto LAB_7fff5fc6ec78;
        if (*(uint *)(lVar6 + 0x18) <= uVar17) goto LAB_7fff5fc6ecde;
        if (plVar13 == (longlong *)0x0) goto LAB_7fff5fc6ec78;
        if (*(uint *)(plVar13 + 3) <= uVar17) goto LAB_7fff5fc6ecde;
        lVar15 = (longlong)(int)uVar17;
        lVar14 = plVar13[lVar15 + 4];
        if (lVar14 == 0) goto LAB_7fff5fc6ec78;
        if ((int)*(short *)(lVar6 + 0x20 + lVar15 * 2) == *(int *)(lVar14 + 0x10)) {
          uVar10 = *(undefined4 *)(lVar14 + 0x10);
          plVar8 = *(longlong **)changeProperties;
          sVar2 = *(short *)(lVar14 + 0x14);
          if (lVar7 == 0) goto LAB_7fff5fc6ec78;
          if (*(uint *)(lVar7 + 0x18) <= uVar17) goto LAB_7fff5fc6ecde;
          sVar3 = *(short *)(lVar7 + 0x20 + lVar15 * 2);
          lVar14 = func_0x7fff5f44ff00(_DAT_7fff62450498);
          FUN_7fff605f3160(lVar14,uVar10,sVar2 - sVar3,0);
          if (plVar8 == (longlong *)0x0) goto LAB_7fff5fc6ec78;
          if ((lVar14 != 0) &&
             (lVar16 = func_0x7fff5f47c7e0(lVar14,*(undefined8 *)(*plVar8 + 0x40)), lVar16 == 0)) {
            uVar12 = func_0x7fff5f47d0b0();
            FUN_7fff5f47d620(uVar12,0);
            pcVar9 = (code *)swi(3);
            (*pcVar9)();
            return;
          }
          if (*(uint *)(plVar8 + 3) <= uVar17) goto LAB_7fff5fc6ecde;
          plVar8[lVar15 + 4] = lVar14;
          thunk_FUN_7fff5f491fd0();
          lVar14 = func_0x7fff5f44ff00(_DAT_7fff62450498);
          FUN_7fff617759d0(lVar14,0,0);
          if ((lVar14 != 0) &&
             (lVar16 = func_0x7fff5f47c7e0(lVar14,*(undefined8 *)(*plVar13 + 0x40)), lVar16 == 0)) {
            uVar12 = func_0x7fff5f47d0b0();
            FUN_7fff5f47d620(uVar12,0);
            pcVar9 = (code *)swi(3);
            (*pcVar9)();
            return;
          }
          if (*(uint *)(plVar13 + 3) <= uVar17) goto LAB_7fff5fc6ecde;
          plVar13[lVar15 + 4] = lVar14;
          thunk_FUN_7fff5f491fd0();
        }
        uVar17 = uVar17 + 1;
        iVar11 = FUN_7fff6068aa20(lVar6,_DAT_7fff62406d58);
      } while ((int)uVar17 < iVar11);
    }
    uStackX_10 = 0;
    iVar11 = FUN_7fff6068aa20(plVar13,_DAT_7fff624061f8);
    if (0 < iVar11) {
      do {
        uVar17 = 0;
        iVar11 = FUN_7fff6068aa20(lVar6,_DAT_7fff62406d58);
        if (0 < iVar11) {
          do {
            if (lVar6 == 0) goto LAB_7fff5fc6ec78;
            if (*(uint *)(lVar6 + 0x18) <= uVar17) goto LAB_7fff5fc6ecde;
            lVar14 = (longlong)(int)uVar17;
            if (*(short *)(lVar6 + 0x20 + lVar14 * 2) == 0) {
              plVar8 = *(longlong **)changeProperties;
              if (plVar8 == (longlong *)0x0) goto LAB_7fff5fc6ec78;
              if (*(uint *)(plVar8 + 3) <= uVar17) goto LAB_7fff5fc6ecde;
              if (plVar8[lVar14 + 4] == 0) {
                if (plVar13 == (longlong *)0x0) goto LAB_7fff5fc6ec78;
                if (*(uint *)(plVar13 + 3) <= uStackX_10) goto LAB_7fff5fc6ecde;
                lVar15 = plVar13[(longlong)(int)uStackX_10 + 4];
                if (lVar15 == 0) goto LAB_7fff5fc6ec78;
                if (*(int *)(lVar15 + 0x10) != 0) {
                  uVar10 = *(undefined4 *)(lVar15 + 0x10);
                  uVar4 = *(undefined2 *)(lVar15 + 0x14);
                  lVar15 = func_0x7fff5f44ff00(_DAT_7fff62450498);
                  FUN_7fff605f3160(lVar15,uVar10,uVar4,0);
                  if ((lVar15 != 0) &&
                     (lVar16 = func_0x7fff5f47c7e0(lVar15,*(undefined8 *)(*plVar8 + 0x40)),
                     lVar16 == 0)) {
                    uVar12 = func_0x7fff5f47d0b0();
                    FUN_7fff5f47d620(uVar12,0);
                    pcVar9 = (code *)swi(3);
                    (*pcVar9)();
                    return;
                  }
                  if (*(uint *)(plVar8 + 3) <= uVar17) goto LAB_7fff5fc6ecde;
                  plVar8[lVar14 + 4] = lVar15;
                  thunk_FUN_7fff5f491fd0();
                  if (*(uint *)(plVar13 + 3) <= uStackX_10) goto LAB_7fff5fc6ecde;
                  lVar14 = plVar13[(longlong)(int)uStackX_10 + 4];
                  if (lVar14 == 0) goto LAB_7fff5fc6ec78;
                  *(undefined4 *)(lVar14 + 0x10) = 0;
                }
              }
            }
            uVar17 = uVar17 + 1;
            iVar11 = FUN_7fff6068aa20(lVar6,_DAT_7fff62406d58);
          } while ((int)uVar17 < iVar11);
        }
        uStackX_10 = uStackX_10 + 1;
        iVar11 = FUN_7fff6068aa20(plVar13,_DAT_7fff624061f8);
      } while ((int)uStackX_10 < iVar11);
    }
    uVar17 = 0;
    iVar11 = FUN_7fff6068aa20(lVar6,_DAT_7fff62406d58);
    if (0 < iVar11) {
      do {
        lVar14 = *(longlong *)changeProperties;
        if (lVar14 == 0) goto LAB_7fff5fc6ec78;
        if (*(uint *)(lVar14 + 0x18) <= uVar17) {
LAB_7fff5fc6ecde:
          FUN_7fff5f47d650();
          pcVar9 = (code *)swi(3);
          (*pcVar9)();
          return;
        }
        lVar15 = (longlong)(int)uVar17;
        plVar13 = *(longlong **)newProperties;
        if (*(longlong *)(lVar14 + 0x20 + lVar15 * 8) == 0) {
          if (lVar6 == 0) goto LAB_7fff5fc6ec78;
          if (*(uint *)(lVar6 + 0x18) <= uVar17) goto LAB_7fff5fc6ecde;
          uVar4 = *(undefined2 *)(lVar6 + 0x20 + lVar15 * 2);
          if (lVar7 == 0) goto LAB_7fff5fc6ec78;
          if (*(uint *)(lVar7 + 0x18) <= uVar17) goto LAB_7fff5fc6ecde;
          uVar5 = *(undefined2 *)(lVar7 + 0x20 + lVar15 * 2);
          lVar14 = func_0x7fff5f44ff00(_DAT_7fff62450498);
          FUN_7fff617759d0(lVar14,uVar4,uVar5,0);
          if (plVar13 == (longlong *)0x0) goto LAB_7fff5fc6ec78;
          if ((lVar14 != 0) &&
             (lVar16 = func_0x7fff5f47c7e0(lVar14,*(undefined8 *)(*plVar13 + 0x40)), lVar16 == 0)) {
            uVar12 = func_0x7fff5f47d0b0();
            FUN_7fff5f47d620(uVar12,0);
            pcVar9 = (code *)swi(3);
            (*pcVar9)();
            return;
          }
          uVar1 = *(uint *)(plVar13 + 3);
        }
        else {
          if (property == (undefined *)0x0) goto LAB_7fff5fc6ec78;
          if (*(uint *)(property + 0x18) <= uVar17) goto LAB_7fff5fc6ecde;
          uVar12 = *(undefined8 *)(property + lVar15 * 8 + 0x20);
          lVar14 = func_0x7fff5f44ff00(_DAT_7fff62450498);
          FUN_7fff61775990(lVar14,uVar12,0);
          if (plVar13 == (longlong *)0x0) goto LAB_7fff5fc6ec78;
          if ((lVar14 != 0) &&
             (lVar16 = func_0x7fff5f47c7e0(lVar14,*(undefined8 *)(*plVar13 + 0x40)), lVar16 == 0)) {
            uVar12 = func_0x7fff5f47d0b0();
            FUN_7fff5f47d620(uVar12,0);
            pcVar9 = (code *)swi(3);
            (*pcVar9)();
            return;
          }
          uVar1 = *(uint *)(plVar13 + 3);
        }
        if (uVar1 <= uVar17) goto LAB_7fff5fc6ecde;
        plVar13[lVar15 + 4] = lVar14;
        thunk_FUN_7fff5f491fd0();
        uVar17 = uVar17 + 1;
        iVar11 = FUN_7fff6068aa20(lVar6,_DAT_7fff62406d58);
      } while ((int)uVar17 < iVar11);
    }
    return;
  }
LAB_7fff5fc6ec78:
  FUN_7fff5f47d660();
  pcVar9 = (code *)swi(3);
  (*pcVar9)();
  return;
}

