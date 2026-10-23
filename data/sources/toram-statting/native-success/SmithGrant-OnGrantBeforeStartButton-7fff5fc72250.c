
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithGrant_OnGrantBeforeStartButton(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  longlong lVar9;
  undefined8 uVar10;
  longlong *plVar11;
  longlong lVar12;
  longlong lVar13;
  undefined8 uVar14;
  undefined *puVar15;
  int aiStackX_8 [2];
  
  if (DAT_7fff625e4224 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62436790);
    FUN_7fff5f47d450(&DAT_7fff624532c0);
    FUN_7fff5f47d450(&DAT_7fff62422c48);
    FUN_7fff5f47d450(&DAT_7fff6245a5f8);
    FUN_7fff5f47d450(&DAT_7fff62473040);
    FUN_7fff5f47d450(&DAT_7fff624731d8);
    FUN_7fff5f47d450(&DAT_7fff623f6410);
    DAT_7fff625e4224 = '\x01';
  }
  if (*(undefined **)(self + 0xb8) != (undefined *)0x0) {
    SmithGrantInfoWindow_CloseCheckWIndow(*(undefined **)(self + 0xb8),(undefined *)0x0);
    if ((*(longlong *)(self + 0xb8) != 0) &&
       (lVar9 = FUN_7fff618a1ae0(*(longlong *)(self + 0xb8),0), lVar9 != 0)) {
      FUN_7fff618a4510(lVar9,0);
      if (*(longlong *)(self + 0xd0) != 0) {
        FUN_7fff5f502150(*(longlong *)(self + 0xd0),1);
        if (*(longlong *)(self + 0xb8) != 0) {
          iVar8 = *(int *)(*(longlong *)(self + 0xb8) + 200);
          lVar9 = FUN_7fff60c4bc00(_DAT_7fff6245a5f8);
          if (((*(longlong *)(self + 0xb8) != 0) && (lVar9 != 0)) &&
             (lVar9 = FUN_7fff600847d0(lVar9), lVar9 != 0)) {
            iVar7 = (int)*(short *)(lVar9 + 0x4c);
            if (*(short *)(lVar9 + 0x4c) <= iVar8) {
              iVar7 = iVar8;
            }
            if (*(longlong *)(self + 0xb8) != 0) {
              iVar8 = *(int *)(*(longlong *)(self + 0xb8) + 200);
              iVar2 = SmithGrant_GetUsePotentialPoint(self,0,(undefined *)0x0);
              if ((*(longlong *)(self + 0x140) != 0) &&
                 (lVar9 = FUN_7fff5ff8b150(*(longlong *)(self + 0x140),0), lVar9 != 0)) {
                iVar3 = FUN_7fff60307a10(lVar9,0x16d,1,0);
                iVar4 = FUN_7fff60307a10(lVar9,0x16e,1,0);
                iVar5 = FUN_7fff60307a10(lVar9,0x16f,1,0);
                iVar6 = 0;
                if (0 < iVar3) {
                  iVar6 = iVar3;
                }
                if (0 < iVar4) {
                  iVar6 = iVar6 + 10 + iVar4;
                }
                if (0 < iVar5) {
                  iVar6 = iVar6 + 0x14 + iVar5;
                }
                iVar7 = (int)((float)(iVar6 + 100) -
                             (_DAT_7fff61b52cfc / (float)iVar7) *
                             (float)(iVar2 - iVar8) * _DAT_7fff61b538a8);
                iVar8 = 0;
                if (-1 < iVar7) {
                  iVar8 = iVar7;
                }
                if (iVar8 < 100) {
                  iVar7 = SmithGrant_GetUsePotentialPoint(self,0,(undefined *)0x0);
                  if (*(longlong *)(self + 0xb8) == 0) goto LAB_7fff5fc72746;
                  if (*(int *)(*(longlong *)(self + 0xb8) + 200) < iVar7) {
                    if (*(longlong *)(self + 0xc0) != 0) {
                      FUN_7fff5f51e650(*(longlong *)(self + 0xc0),0);
                      plVar11 = *(longlong **)(self + 0x28);
                      uVar10 = func_0x7fff5f44ff00(_DAT_7fff62436790);
                      FUN_7fff5f4f6880(uVar10,self,_DAT_7fff624731d8,0);
                      if (plVar11 != (longlong *)0x0) {
                        (**(code **)(*plVar11 + 0x1c8))
                                  (plVar11,uVar10,*(undefined8 *)(*plVar11 + 0x1d0));
                        if (iVar8 < 1) {
                          if (*(longlong *)(self + 0xd0) == 0) goto LAB_7fff5fc72746;
                          FUN_7fff5f502150(*(longlong *)(self + 0xd0),0,0);
                        }
                        lVar9 = *(longlong *)(self + 200);
                        plVar11 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
                        aiStackX_8[0] = iVar8;
                        lVar12 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,aiStackX_8);
                        if (plVar11 != (longlong *)0x0) {
                          if ((lVar12 != 0) &&
                             (lVar13 = func_0x7fff5f47c7e0(lVar12,*(undefined8 *)(*plVar11 + 0x40)),
                             lVar13 == 0)) {
                            uVar10 = func_0x7fff5f47d0b0();
                            FUN_7fff5f47d620(uVar10,0);
                            pcVar1 = (code *)swi(3);
                            (*pcVar1)();
                            return;
                          }
                          if ((int)plVar11[3] == 0) {
                            FUN_7fff5f47d650();
                            pcVar1 = (code *)swi(3);
                            (*pcVar1)();
                            return;
                          }
                          plVar11[4] = lVar12;
                          thunk_FUN_7fff5f491fd0();
                          if (lVar9 != 0) {
                            FUN_7fff5f55c500(lVar9,plVar11,0);
                            return;
                          }
                        }
                        FUN_7fff5f47d660();
                        pcVar1 = (code *)swi(3);
                        (*pcVar1)();
                        return;
                      }
                    }
                    goto LAB_7fff5fc72746;
                  }
                }
                iVar8 = SmithGrant_getEmptySlotCount(self,(undefined *)0x0);
                if (iVar8 < 1) {
                  if (*(longlong *)(self + 0xb8) == 0) goto LAB_7fff5fc72746;
                  if (0 < *(int *)(*(longlong *)(self + 0xb8) + 0xd0)) {
                    plVar11 = *(longlong **)(self + 0x28);
                    uVar10 = func_0x7fff5f44ff00(_DAT_7fff62436790);
                    FUN_7fff5f4f6880(uVar10,self,_DAT_7fff62473040,0);
                    if (plVar11 != (longlong *)0x0) {
                      (**(code **)(*plVar11 + 0x1c8))
                                (plVar11,uVar10,*(undefined8 *)(*plVar11 + 0x1d0));
                      if (*(longlong *)(self + 0x110) != 0) {
                        FUN_7fff618a4510(*(longlong *)(self + 0x110),1,0);
                        lVar9 = *(longlong *)(self + 0x118);
                        if (*(longlong *)(self + 0x30) != 0) {
                          uVar10 = FUN_7fff5f568150(*(longlong *)(self + 0x30),_DAT_7fff623f6410,0);
                          if (*(longlong *)(self + 0xb8) != 0) {
                            aiStackX_8[0] = *(int *)(*(longlong *)(self + 0xb8) + 0xd0);
                            uVar14 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,aiStackX_8);
                            uVar10 = FUN_7fff60e74b00(uVar10,uVar14,0);
                            if (lVar9 != 0) {
                              FUN_7fff5ff0eed0(lVar9,uVar10,0);
                              return;
                            }
                          }
                        }
                      }
                    }
                    FUN_7fff5f47d660();
                    pcVar1 = (code *)swi(3);
                    (*pcVar1)();
                    return;
                  }
                }
                if (self[0x158] != '\0') {
                  return;
                }
                self[0x158] = 1;
                if (*(longlong *)(self + 0x110) != 0) {
                  FUN_7fff618a4510(*(longlong *)(self + 0x110),0,0);
                  puVar15 = SmithGrant_ConnectWaitManufactureGuard(self,(undefined *)0x0);
                  FUN_7fff618a87c0(self,puVar15,0);
                  plVar11 = *(longlong **)(self + 0x28);
                  if (plVar11 != (longlong *)0x0) {
                    (**(code **)(*plVar11 + 0x1d8))(plVar11,*(undefined8 *)(*plVar11 + 0x1e0));
                    return;
                  }
                }
              }
            }
          }
        }
      }
    }
  }
LAB_7fff5fc72746:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

