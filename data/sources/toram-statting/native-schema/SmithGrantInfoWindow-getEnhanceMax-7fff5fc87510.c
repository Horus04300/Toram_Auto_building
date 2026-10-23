
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SmithGrantInfoWindow_getEnhanceMax
              (undefined *self,byte isUpper,int checkType,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  longlong lVar7;
  longlong *plVar8;
  int iVar9;
  float fVar10;
  undefined1 auStack_88 [16];
  float fStack_78;
  undefined1 auStack_60 [20];
  int iStack_4c;
  int iStack_48;
  int iStack_44;
  int iStack_40;
  
  if (DAT_7fff625e4262 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6244ce08);
    FUN_7fff5f47d450(&DAT_7fff62420f50);
    FUN_7fff5f47d450(&DAT_7fff624485c8);
    FUN_7fff5f47d450(&DAT_7fff624700a0);
    FUN_7fff5f47d450(&DAT_7fff6240e4b0);
    DAT_7fff625e4262 = '\x01';
  }
  uVar6 = *(undefined8 *)(self + 0xe0);
  if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
    func_0x7fff5f47d6f0();
  }
  cVar2 = FUN_7fff618ab120(uVar6,0,0);
  if (cVar2 != '\0') {
    uVar6 = FUN_7fff5ff86680(0);
    *(undefined8 *)(self + 0xe0) = uVar6;
    thunk_FUN_7fff5f491fd0();
  }
  if (*(longlong *)(self + 0xe0) != 0) {
    lVar7 = FUN_7fff5ff8b150(*(longlong *)(self + 0xe0),0);
    if (lVar7 != 0) {
      iVar3 = FUN_7fff60307a10(lVar7,0x16d,1,0);
      iVar9 = 0;
      if (iVar3 < 0) {
        iVar3 = iVar9;
      }
      iVar4 = FUN_7fff60307a10(lVar7,0x16e,1,0);
      if (iVar4 < 0) {
        iVar4 = iVar9;
      }
      iVar5 = FUN_7fff60307a10(lVar7,0x16f,1,0);
      if (iVar5 < 0) {
        iVar5 = iVar9;
      }
      fVar10 = (float)(iVar3 * 3) + _DAT_7fff61b52ce4 + (float)(iVar4 * 3) + (float)(iVar5 * 3);
      if (*(longlong *)(self + 0xe0) != 0) {
        plVar8 = (longlong *)FUN_7fff5ff8ac30(*(longlong *)(self + 0xe0),0);
        if (plVar8 != (longlong *)0x0) {
          lVar7 = (**(code **)(*plVar8 + 0x198))(plVar8,*(undefined8 *)(*plVar8 + 0x1a0));
          if (lVar7 != 0) {
            iVar3 = FUN_7fff5f252ec0(0,_DAT_7fff624485c8,lVar7);
            if (iVar3 < 0xd2) {
              if (*(int *)(_DAT_7fff62420f50 + 0xe0) == 0) {
                func_0x7fff5f47d6f0(_DAT_7fff62420f50);
              }
              if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) != 0) {
                FUN_7fff6088c670(auStack_60,**(longlong **)(_DAT_7fff62420f50 + 0xb8),checkType,
                                 _DAT_7fff6244ce08);
                iVar9 = iStack_4c;
                if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) != 0) {
                  FUN_7fff6088c670(auStack_60,**(longlong **)(_DAT_7fff62420f50 + 0xb8),checkType,
                                   _DAT_7fff6244ce08);
                  if (*(int *)(_DAT_7fff624700a0 + 0xe0) == 0) {
                    func_0x7fff5f47d6f0();
                  }
                  iVar3 = int_minmax_1dc1140((int)((fVar10 / _DAT_7fff61b52cfc) * (float)iVar9),
                                             iVar3 / 10,(undefined *)0x0);
                  iVar3 = int_minmax_1dc1140(iVar3,iStack_4c,(undefined *)0x0);
                  goto LAB_7fff5fc87a54;
                }
              }
            }
            else {
              if (*(int *)(_DAT_7fff62420f50 + 0xe0) == 0) {
                func_0x7fff5f47d6f0(_DAT_7fff62420f50);
              }
              if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) != 0) {
                FUN_7fff6088c670(auStack_60,**(longlong **)(_DAT_7fff62420f50 + 0xb8),checkType,
                                 _DAT_7fff6244ce08);
                if (*(int *)(_DAT_7fff624700a0 + 0xe0) == 0) {
                  func_0x7fff5f47d6f0();
                }
                iVar3 = int_minmax_1dc0f30(0,iVar3 / 10 + -0x14,(undefined *)0x0);
                if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) != 0) {
                  FUN_7fff6088c670(auStack_88,**(longlong **)(_DAT_7fff62420f50 + 0xb8),checkType,
                                   _DAT_7fff6244ce08);
                  if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) != 0) {
                    FUN_7fff6088c670(auStack_60,**(longlong **)(_DAT_7fff62420f50 + 0xb8),checkType,
                                     _DAT_7fff6244ce08);
                    fVar10 = fVar10 / _DAT_7fff61b52cfc;
                    iVar3 = (int)(fStack_78 * (float)iVar3) * iStack_40;
                    if (isUpper == 0) {
                      if (*(int *)(_DAT_7fff62420f50 + 0xe0) == 0) {
                        func_0x7fff5f47d6f0(_DAT_7fff62420f50);
                      }
                      if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) == 0) goto LAB_7fff5fc87aa8;
                      FUN_7fff6088c670(auStack_60,**(longlong **)(_DAT_7fff62420f50 + 0xb8),
                                       checkType,_DAT_7fff6244ce08);
                      iVar9 = iStack_44;
                    }
                    else {
                      if (*(int *)(_DAT_7fff62420f50 + 0xe0) == 0) {
                        func_0x7fff5f47d6f0(_DAT_7fff62420f50);
                      }
                      if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) == 0) goto LAB_7fff5fc87aa8;
                      FUN_7fff6088c670(auStack_60,**(longlong **)(_DAT_7fff62420f50 + 0xb8),
                                       checkType,_DAT_7fff6244ce08);
                      iVar9 = iStack_48;
                    }
                    if (*(int *)(_DAT_7fff62420f50 + 0xe0) == 0) {
                      func_0x7fff5f47d6f0(_DAT_7fff62420f50);
                    }
                    if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) != 0) {
                      FUN_7fff6088c670(auStack_60,**(longlong **)(_DAT_7fff62420f50 + 0xb8),
                                       checkType,_DAT_7fff6244ce08);
                      iVar9 = (iVar9 - iStack_4c) * iStack_40;
                      if (*(int *)(_DAT_7fff624700a0 + 0xe0) == 0) {
                        func_0x7fff5f47d6f0();
                      }
                      iVar3 = int_minmax_1dc1140((int)((float)(iVar3 + iStack_4c) * fVar10),
                                                 iVar9 + iStack_4c,(undefined *)0x0);
                      if ((((checkType - 0x16U < 0xb) && ((checkType - 0x16U & 1) == 0)) ||
                          (checkType == 0xc)) && (iStack_4c < iVar3)) {
                        if (*(int *)(_DAT_7fff62420f50 + 0xe0) == 0) {
                          func_0x7fff5f47d6f0();
                        }
                        if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) == 0) goto LAB_7fff5fc87aa8;
                        FUN_7fff6088c670(auStack_60,**(longlong **)(_DAT_7fff62420f50 + 0xb8),
                                         checkType,_DAT_7fff6244ce08);
                        iVar3 = iStack_4c + (iVar3 - iStack_4c) / iStack_40;
                      }
LAB_7fff5fc87a54:
                      if (*(int *)(_DAT_7fff624700a0 + 0xe0) == 0) {
                        func_0x7fff5f47d6f0();
                      }
                      if (iVar3 < 2) {
                        iVar3 = 1;
                      }
                      return iVar3;
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
LAB_7fff5fc87aa8:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  iVar3 = (*pcVar1)();
  return iVar3;
}

