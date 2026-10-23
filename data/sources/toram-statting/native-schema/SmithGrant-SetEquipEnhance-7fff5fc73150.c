
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithGrant_SetEquipEnhance(undefined *self,undefined *methodInfo)

{
  undefined4 uVar1;
  int iVar2;
  code *pcVar3;
  short sVar4;
  short sVar5;
  int iVar6;
  longlong lVar7;
  longlong lVar8;
  longlong *plVar9;
  longlong lVar10;
  longlong lVar11;
  undefined8 uVar12;
  uint uVar13;
  
  if (DAT_7fff625e421a == '\0') {
    FUN_7fff5f47d450(0x7fff62401320);
    FUN_7fff5f47d450(&DAT_7fff624013f0);
    FUN_7fff5f47d450(&DAT_7fff62416958);
    FUN_7fff5f47d450(&DAT_7fff62446b98);
    FUN_7fff5f47d450(0x7fff62447400);
    FUN_7fff5f47d450(&DAT_7fff62407dc0);
    FUN_7fff5f47d450(&DAT_7fff62471c30);
    DAT_7fff625e421a = '\x01';
  }
  lVar7 = *(longlong *)(self + 0x70);
  if (lVar7 != 0) {
    if (*(int *)(lVar7 + 0x18) < 1) {
      SmithGrantInfoWindow_Start(_DAT_7fff62471c30,(undefined *)0x0);
      return;
    }
    lVar8 = *(longlong *)(self + 0x128);
    if (lVar8 != 0) {
      if (*(int *)(lVar8 + 0x18) == 0) {
LAB_7fff5fc738be:
        FUN_7fff5f47d650();
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
      lVar7 = FUN_7fff60a94f50(lVar7,*(undefined4 *)(lVar8 + 0x20),_DAT_7fff624013f0);
      if (lVar7 != 0) {
        uVar1 = *(undefined4 *)(lVar7 + 0x18);
        if ((*(longlong *)(self + 0x140) != 0) &&
           (lVar7 = FUN_7fff5ff8a8a0(*(longlong *)(self + 0x140),0), lVar7 != 0)) {
          lVar8 = FUN_7fff6007b880(lVar7,uVar1,0);
          lVar7 = *(longlong *)(self + 0x120);
          plVar9 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62416958,10);
          if (lVar8 != 0) {
            sVar4 = FUN_7fff5fd06df0(lVar8,0);
            sVar5 = FUN_7fff5fd06fd0(lVar8,0);
            lVar10 = func_0x7fff5f44ff00(_DAT_7fff62407dc0);
            FUN_7fff5f5ad230(lVar10,(int)sVar4,(int)sVar5,_DAT_7fff62446b98);
            if (plVar9 != (longlong *)0x0) {
              if ((lVar10 != 0) &&
                 (lVar11 = func_0x7fff5f47c7e0(lVar10,*(undefined8 *)(*plVar9 + 0x40)), lVar11 == 0)
                 ) {
                uVar12 = func_0x7fff5f47d0b0();
                FUN_7fff5f47d620(uVar12,0);
                pcVar3 = (code *)swi(3);
                (*pcVar3)();
                return;
              }
              if ((int)plVar9[3] != 0) {
                plVar9[4] = lVar10;
                thunk_FUN_7fff5f491fd0();
                sVar4 = FUN_7fff5fd06e20(lVar8,0);
                sVar5 = FUN_7fff5fd07000(lVar8,0);
                lVar10 = func_0x7fff5f44ff00(_DAT_7fff62407dc0);
                FUN_7fff5f5ad230(lVar10,(int)sVar4,(int)sVar5,_DAT_7fff62446b98);
                if ((lVar10 != 0) &&
                   (lVar11 = func_0x7fff5f47c7e0(lVar10,*(undefined8 *)(*plVar9 + 0x40)),
                   lVar11 == 0)) {
                  uVar12 = func_0x7fff5f47d0b0();
                  FUN_7fff5f47d620(uVar12,0);
                  pcVar3 = (code *)swi(3);
                  (*pcVar3)();
                  return;
                }
                if (1 < *(uint *)(plVar9 + 3)) {
                  plVar9[5] = lVar10;
                  thunk_FUN_7fff5f491fd0();
                  sVar4 = FUN_7fff5fd06e50(lVar8,0);
                  sVar5 = FUN_7fff5fd07030(lVar8,0);
                  lVar10 = func_0x7fff5f44ff00(_DAT_7fff62407dc0);
                  FUN_7fff5f5ad230(lVar10,(int)sVar4,(int)sVar5,_DAT_7fff62446b98);
                  if ((lVar10 != 0) &&
                     (lVar11 = func_0x7fff5f47c7e0(lVar10,*(undefined8 *)(*plVar9 + 0x40)),
                     lVar11 == 0)) {
                    uVar12 = func_0x7fff5f47d0b0();
                    FUN_7fff5f47d620(uVar12,0);
                    pcVar3 = (code *)swi(3);
                    (*pcVar3)();
                    return;
                  }
                  if (2 < *(uint *)(plVar9 + 3)) {
                    plVar9[6] = lVar10;
                    thunk_FUN_7fff5f491fd0();
                    sVar4 = FUN_7fff5fd06e80(lVar8,0);
                    sVar5 = FUN_7fff5fd07060(lVar8,0);
                    lVar10 = func_0x7fff5f44ff00(_DAT_7fff62407dc0);
                    FUN_7fff5f5ad230(lVar10,(int)sVar4,(int)sVar5,_DAT_7fff62446b98);
                    if ((lVar10 != 0) &&
                       (lVar11 = func_0x7fff5f47c7e0(lVar10,*(undefined8 *)(*plVar9 + 0x40)),
                       lVar11 == 0)) {
                      uVar12 = func_0x7fff5f47d0b0();
                      FUN_7fff5f47d620(uVar12,0);
                      pcVar3 = (code *)swi(3);
                      (*pcVar3)();
                      return;
                    }
                    if (3 < *(uint *)(plVar9 + 3)) {
                      plVar9[7] = lVar10;
                      thunk_FUN_7fff5f491fd0();
                      sVar4 = FUN_7fff5fd06eb0(lVar8,0);
                      sVar5 = FUN_7fff5fd07090(lVar8,0);
                      lVar10 = func_0x7fff5f44ff00(_DAT_7fff62407dc0);
                      FUN_7fff5f5ad230(lVar10,(int)sVar4,(int)sVar5,_DAT_7fff62446b98);
                      if ((lVar10 != 0) &&
                         (lVar11 = func_0x7fff5f47c7e0(lVar10,*(undefined8 *)(*plVar9 + 0x40)),
                         lVar11 == 0)) {
                        uVar12 = func_0x7fff5f47d0b0();
                        FUN_7fff5f47d620(uVar12,0);
                        pcVar3 = (code *)swi(3);
                        (*pcVar3)();
                        return;
                      }
                      if (4 < *(uint *)(plVar9 + 3)) {
                        plVar9[8] = lVar10;
                        thunk_FUN_7fff5f491fd0();
                        sVar4 = FUN_7fff5fd06ee0(lVar8,0);
                        sVar5 = FUN_7fff5fd070c0(lVar8,0);
                        lVar10 = func_0x7fff5f44ff00(_DAT_7fff62407dc0);
                        FUN_7fff5f5ad230(lVar10,(int)sVar4,(int)sVar5,_DAT_7fff62446b98);
                        if ((lVar10 != 0) &&
                           (lVar11 = func_0x7fff5f47c7e0(lVar10,*(undefined8 *)(*plVar9 + 0x40)),
                           lVar11 == 0)) {
                          uVar12 = func_0x7fff5f47d0b0();
                          FUN_7fff5f47d620(uVar12,0);
                          pcVar3 = (code *)swi(3);
                          (*pcVar3)();
                          return;
                        }
                        if (5 < *(uint *)(plVar9 + 3)) {
                          plVar9[9] = lVar10;
                          thunk_FUN_7fff5f491fd0();
                          sVar4 = FUN_7fff5fd06f10(lVar8,0);
                          sVar5 = FUN_7fff5fd070f0(lVar8,0);
                          lVar10 = func_0x7fff5f44ff00(_DAT_7fff62407dc0);
                          FUN_7fff5f5ad230(lVar10,(int)sVar4,(int)sVar5,_DAT_7fff62446b98);
                          if ((lVar10 != 0) &&
                             (lVar11 = func_0x7fff5f47c7e0(lVar10,*(undefined8 *)(*plVar9 + 0x40)),
                             lVar11 == 0)) {
                            uVar12 = func_0x7fff5f47d0b0();
                            FUN_7fff5f47d620(uVar12,0);
                            pcVar3 = (code *)swi(3);
                            (*pcVar3)();
                            return;
                          }
                          if (6 < *(uint *)(plVar9 + 3)) {
                            plVar9[10] = lVar10;
                            thunk_FUN_7fff5f491fd0();
                            sVar4 = FUN_7fff5fd06f40(lVar8,0);
                            sVar5 = FUN_7fff5fd07120(lVar8,0);
                            lVar10 = func_0x7fff5f44ff00(_DAT_7fff62407dc0);
                            FUN_7fff5f5ad230(lVar10,(int)sVar4,(int)sVar5,_DAT_7fff62446b98);
                            if ((lVar10 != 0) &&
                               (lVar11 = func_0x7fff5f47c7e0(lVar10,*(undefined8 *)(*plVar9 + 0x40))
                               , lVar11 == 0)) {
                              uVar12 = func_0x7fff5f47d0b0();
                              FUN_7fff5f47d620(uVar12,0);
                              pcVar3 = (code *)swi(3);
                              (*pcVar3)();
                              return;
                            }
                            if (7 < *(uint *)(plVar9 + 3)) {
                              plVar9[0xb] = lVar10;
                              thunk_FUN_7fff5f491fd0();
                              sVar4 = FUN_7fff5fd06f70(lVar8,0);
                              sVar5 = FUN_7fff5fd07150(lVar8,0);
                              lVar10 = func_0x7fff5f44ff00(_DAT_7fff62407dc0);
                              FUN_7fff5f5ad230(lVar10,(int)sVar4,(int)sVar5,_DAT_7fff62446b98);
                              if ((lVar10 != 0) &&
                                 (lVar11 = func_0x7fff5f47c7e0(lVar10,*(undefined8 *)
                                                                       (*plVar9 + 0x40)),
                                 lVar11 == 0)) {
                                uVar12 = func_0x7fff5f47d0b0();
                                FUN_7fff5f47d620(uVar12,0);
                                pcVar3 = (code *)swi(3);
                                (*pcVar3)();
                                return;
                              }
                              if (8 < *(uint *)(plVar9 + 3)) {
                                plVar9[0xc] = lVar10;
                                thunk_FUN_7fff5f491fd0();
                                sVar4 = FUN_7fff5fd06dc0(lVar8,0);
                                sVar5 = FUN_7fff5fd06fa0(lVar8,0);
                                lVar8 = func_0x7fff5f44ff00(_DAT_7fff62407dc0);
                                FUN_7fff5f5ad230(lVar8,(int)sVar4,(int)sVar5,_DAT_7fff62446b98);
                                if ((lVar8 != 0) &&
                                   (lVar10 = func_0x7fff5f47c7e0(lVar8,*(undefined8 *)
                                                                        (*plVar9 + 0x40)),
                                   lVar10 == 0)) {
                                  uVar12 = func_0x7fff5f47d0b0();
                                  FUN_7fff5f47d620(uVar12,0);
                                  pcVar3 = (code *)swi(3);
                                  (*pcVar3)();
                                  return;
                                }
                                if (9 < *(uint *)(plVar9 + 3)) {
                                  plVar9[0xd] = lVar8;
                                  thunk_FUN_7fff5f491fd0();
                                  if (lVar7 != 0) {
                                    if (DAT_7fff625e4235 == '\0') {
                                      FUN_7fff5f47d450(&DAT_7fff62405de8);
                                      FUN_7fff5f47d450(0x7fff62446c58);
                                      FUN_7fff5f47d450(0x7fff62446d20);
                                      DAT_7fff625e4235 = '\x01';
                                    }
                                    iVar6 = FUN_7fff6068aa20(plVar9,_DAT_7fff62405de8);
                                    if (iVar6 < 10) {
                                      return;
                                    }
                                    uVar13 = 0;
                                    iVar6 = FUN_7fff6068aa20(plVar9,_DAT_7fff62405de8);
                                    if (iVar6 < 1) {
                                      return;
                                    }
                                    while (lVar8 = *(longlong *)(lVar7 + 0x10), lVar8 != 0) {
                                      if ((int)*(uint *)(lVar8 + 0x18) <= (int)uVar13) {
                                        return;
                                      }
                                      if (*(uint *)(lVar8 + 0x18) <= uVar13) goto LAB_7fff5fc738be;
                                      lVar8 = *(longlong *)
                                               (lVar8 + 0x20 + (longlong)(int)uVar13 * 8);
                                      if (*(uint *)(plVar9 + 3) <= uVar13) goto LAB_7fff5fc738be;
                                      lVar10 = plVar9[(longlong)(int)uVar13 + 4];
                                      if (lVar10 == 0) break;
                                      iVar6 = *(int *)(lVar10 + 0x14);
                                      iVar2 = *(int *)(lVar10 + 0x10);
                                      if (lVar8 == 0) break;
                                      *(int *)(lVar8 + 0x20) = iVar2;
                                      *(int *)(lVar8 + 0x30) = iVar6;
                                      *(bool *)(lVar8 + 0x2c) = 0 < iVar2;
                                      if (((0 < iVar2) || (*(int *)(lVar8 + 0x28) + iVar6 != 0)) &&
                                         (*(int *)(lVar8 + 0x20) == 0x41)) {
                                        *(int *)(lVar8 + 0x24) = iVar6;
                                      }
                                      uVar13 = uVar13 + 1;
                                      iVar6 = FUN_7fff6068aa20(plVar9,_DAT_7fff62405de8);
                                      if (iVar6 <= (int)uVar13) {
                                        return;
                                      }
                                    }
                                  }
                                  goto LAB_7fff5fc73818;
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
              goto LAB_7fff5fc738be;
            }
          }
        }
      }
    }
  }
LAB_7fff5fc73818:
  FUN_7fff5f47d660();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

