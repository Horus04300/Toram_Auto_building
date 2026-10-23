
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithGrantInfoWindow_SetDetailValue(undefined *self,int enhanceValue,undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  uint uVar3;
  undefined8 uVar4;
  longlong *plVar5;
  longlong lVar6;
  longlong lVar7;
  undefined8 uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  undefined4 auStackX_20 [2];
  undefined1 auStack_68 [8];
  undefined8 uStack_60;
  undefined8 uStack_58;
  int iStack_54;
  int iStack_48;
  undefined8 in_stack_ffffffffffffffd8;
  int in_stack_ffffffffffffffe8;
  
  if (DAT_7fff625e425b == '\0') {
    uStack_60 = 0x7fff5fc85849;
    FUN_7fff5f47d450(&DAT_7fff6244ce08);
    uStack_60 = 0x7fff5fc85855;
    FUN_7fff5f47d450(&DAT_7fff62420f50);
    DAT_7fff625e425b = '\x01';
  }
  iVar9 = *(int *)(self + 0xa4);
  if (((iVar9 - 0x16U < 0xb) && ((iVar9 - 0x16U & 1) == 0)) || (iVar9 == 0xc)) {
    if (*(int *)(_DAT_7fff62420f50 + 0xe0) == 0) {
      uStack_60 = 0x7fff5fc85894;
      func_0x7fff5f47d6f0(_DAT_7fff62420f50);
    }
    if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) == 0) {
LAB_7fff5fc85994:
      uStack_60 = 0x7fff5fc85999;
      FUN_7fff5f47d660();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    uStack_60 = 0x7fff5fc858c2;
    FUN_7fff6088c670(&stack0xffffffffffffffc8,**(longlong **)(_DAT_7fff62420f50 + 0xb8),iVar9,
                     _DAT_7fff6244ce08);
    if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) == 0) goto LAB_7fff5fc85994;
    uStack_60 = 0x7fff5fc858f9;
    FUN_7fff6088c670(&stack0xffffffffffffffc8,**(longlong **)(_DAT_7fff62420f50 + 0xb8),iVar9,
                     _DAT_7fff6244ce08);
    iVar9 = *(int *)(self + 0xd8);
    iVar10 = (int)((ulonglong)in_stack_ffffffffffffffd8 >> 0x20);
    if (iVar10 < iVar9) {
      iVar2 = (iVar9 - iVar10) / in_stack_ffffffffffffffe8 + iVar10;
LAB_7fff5fc85925:
      *(int *)(self + 0xd4) = iVar2;
    }
    else if (iVar9 < -iVar10) {
      iVar2 = (iVar9 + iVar10) / in_stack_ffffffffffffffe8 - iVar10;
      goto LAB_7fff5fc85925;
    }
    iVar9 = iVar9 + enhanceValue;
    if (iVar10 < iVar9) {
      if (enhanceValue != 0) {
        enhanceValue = ((iVar9 - iVar10) / in_stack_ffffffffffffffe8 - *(int *)(self + 0xd4)) +
                       iVar10;
      }
    }
    else if (iVar9 < -iVar10) {
      if (enhanceValue != 0) {
        enhanceValue = ((iVar9 + iVar10) / in_stack_ffffffffffffffe8 - *(int *)(self + 0xd4)) -
                       iVar10;
      }
    }
    else {
      enhanceValue = iVar9 - *(int *)(self + 0xd4);
    }
  }
  *(int *)(self + 0xa0) = enhanceValue;
  if (DAT_7fff625e4263 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6244ce08);
    FUN_7fff5f47d450(&DAT_7fff62420f50);
    FUN_7fff5f47d450(&DAT_7fff624485c8);
    FUN_7fff5f47d450(&DAT_7fff624532c0);
    FUN_7fff5f47d450(&DAT_7fff62422c48);
    FUN_7fff5f47d450(&DAT_7fff62426990);
    FUN_7fff5f47d450(&DAT_7fff624767c0);
    FUN_7fff5f47d450(&DAT_7fff6243f290);
    FUN_7fff5f47d450(&DAT_7fff624021d8);
    FUN_7fff5f47d450(&DAT_7fff623ffd48);
    FUN_7fff5f47d450(&DAT_7fff62426620);
    FUN_7fff5f47d450(&DAT_7fff624191d8);
    FUN_7fff5f47d450(&DAT_7fff62426170);
    DAT_7fff625e4263 = '\x01';
  }
  if ((*(int *)(self + 0xa4) == 0xc) || (iVar9 = 1, *(int *)(self + 0xa4) == 0x6e)) {
    iVar9 = 10;
  }
  lVar6 = *(longlong *)(self + 0x98);
  uVar4 = FUN_7fff5fc6d060((*(int *)(self + 0xd4) + *(int *)(self + 0xa0)) * iVar9,0);
  if (lVar6 == 0) goto LAB_7fff5fc872de;
  FUN_7fff5ff0eed0(lVar6,uVar4,0);
  iVar10 = *(int *)(self + 0xa4);
  if (*(int *)(_DAT_7fff62420f50 + 0xe0) == 0) {
    func_0x7fff5f47d6f0(_DAT_7fff62420f50);
  }
  if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) == 0) goto LAB_7fff5fc872de;
  FUN_7fff6088c670(auStack_68,**(longlong **)(_DAT_7fff62420f50 + 0xb8),iVar10,_DAT_7fff6244ce08);
  if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) == 0) goto LAB_7fff5fc872de;
  FUN_7fff6088c670(auStack_68,**(longlong **)(_DAT_7fff62420f50 + 0xb8),iVar10,_DAT_7fff6244ce08);
  iVar11 = 0;
  iVar2 = *(int *)(self + 0xa0);
  iVar12 = *(int *)(self + 0xd4) + iVar2;
  if (self[0xfc] == '\0') {
    if (((iVar10 - 0x16U < 0xb) && ((iVar10 - 0x16U & 1) == 0)) || (iVar10 == 0xc)) {
      if (iStack_54 < iVar12) {
        iVar10 = (iVar12 - iStack_54) * iStack_48 + iStack_54;
      }
      else {
        if (-iStack_54 <= iVar12) goto LAB_7fff5fc86e1f;
        iVar10 = (iVar12 + iStack_54) * iStack_48 - iStack_54;
      }
      lVar6 = *(longlong *)(self + 0x98);
      uVar4 = FUN_7fff5fc6d060(iVar10 * iVar9,0);
      if (lVar6 == 0) goto LAB_7fff5fc872de;
      FUN_7fff5ff0eed0(lVar6,uVar4,0);
    }
LAB_7fff5fc86e1f:
    if (iVar2 < 0) {
      if (iStack_54 < *(int *)(self + 0xd4)) {
        iVar10 = iStack_54 - *(int *)(self + 0xd4);
        iVar9 = iVar2;
        if (iVar2 <= iVar10) {
          iVar9 = iVar10;
        }
      }
      else {
        iVar9 = 0;
      }
      iVar2 = iVar2 - iVar9;
      if ((iVar12 < -iStack_54) && (iVar11 = iVar2, iVar2 <= iVar12 + iStack_54)) {
        iVar11 = iVar12 + iStack_54;
      }
      iVar10 = *(int *)(self + 0xb4);
      if (((*(longlong *)(self + 0xe0) == 0) ||
          (plVar5 = (longlong *)FUN_7fff5ff8ac30(*(longlong *)(self + 0xe0),0),
          plVar5 == (longlong *)0x0)) ||
         (lVar6 = (**(code **)(*plVar5 + 0x198))(plVar5,*(undefined8 *)(*plVar5 + 0x1a0)),
         lVar6 == 0)) {
LAB_7fff5fc872de:
        FUN_7fff5f47d660();
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      iVar12 = FUN_7fff5f252ec0(9,_DAT_7fff624485c8,lVar6);
      iVar11 = (int)(((float)iVar12 / _DAT_7fff61b52c90 + _DAT_7fff61b52b3c) *
                    ((float)((iVar9 - iVar11) + iVar2) + (float)iVar11 * _DAT_7fff61b52b4c) *
                    (float)iVar10);
    }
    else if (iVar2 != 0) {
      if (*(int *)(self + 0xd4) < -iStack_54) {
        iVar10 = -(*(int *)(self + 0xd4) + iStack_54);
        iVar9 = iVar2;
        if (iVar10 <= iVar2) {
          iVar9 = iVar10;
        }
      }
      else {
        iVar9 = 0;
      }
      iVar2 = iVar2 - iVar9;
      if ((iStack_54 < iVar12) && (iVar11 = iVar2, iVar12 - iStack_54 <= iVar2)) {
        iVar11 = iVar12 - iStack_54;
      }
      iVar11 = (int)(short)((((short)iVar2 - (short)iVar11) + (short)iVar9) *
                           *(short *)(self + 0xb4)) +
               (int)(short)((short)iVar11 * *(short *)(self + 0xb4) * 2);
    }
  }
  else {
    iVar11 = iVar2 * *(int *)(self + 0xb4);
  }
  plVar5 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,3);
  lVar6 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,&stack0x00000008);
  if (plVar5 == (longlong *)0x0) {
LAB_7fff5fc8731a:
    FUN_7fff5f47d660();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  if ((lVar6 != 0) &&
     (lVar7 = func_0x7fff5f47c7e0(lVar6,*(undefined8 *)(*plVar5 + 0x40)), lVar7 == 0)) {
    uVar4 = func_0x7fff5f47d0b0();
    FUN_7fff5f47d620(uVar4,0);
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  if ((int)plVar5[3] != 0) {
    plVar5[4] = lVar6;
    thunk_FUN_7fff5f491fd0();
    lVar6 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,&stack0x00000018);
    if ((lVar6 != 0) &&
       (lVar7 = func_0x7fff5f47c7e0(lVar6,*(undefined8 *)(*plVar5 + 0x40)), lVar7 == 0)) {
      uVar4 = func_0x7fff5f47d0b0();
      FUN_7fff5f47d620(uVar4,0);
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    if (1 < *(uint *)(plVar5 + 3)) {
      plVar5[5] = lVar6;
      thunk_FUN_7fff5f491fd0();
      auStackX_20[0] = *(undefined4 *)(self + 0xf8);
      lVar6 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,auStackX_20);
      if ((lVar6 != 0) &&
         (lVar7 = func_0x7fff5f47c7e0(lVar6,*(undefined8 *)(*plVar5 + 0x40)), lVar7 == 0)) {
        uVar4 = func_0x7fff5f47d0b0();
        FUN_7fff5f47d620(uVar4,0);
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      if (2 < *(uint *)(plVar5 + 3)) {
        plVar5[6] = lVar6;
        thunk_FUN_7fff5f491fd0();
        SmithGrant_Update(_DAT_7fff624767c0,(undefined *)plVar5);
        lVar6 = *(longlong *)(self + 0x48);
        lVar7 = func_0x7fff5f47c850(_DAT_7fff62426990,7);
        if (lVar7 == 0) goto LAB_7fff5fc8731a;
        if (*(int *)(lVar7 + 0x18) != 0) {
          *(undefined8 *)(lVar7 + 0x20) = _DAT_7fff62426170;
          thunk_FUN_7fff5f491fd0();
          uVar4 = FUN_7fff5fc6ce20((longlong)
                                   ((*(int *)(self + 200) - iVar11) - *(int *)(self + 0xb0)),
                                   _DAT_7fff6243f290,0);
          if (1 < *(uint *)(lVar7 + 0x18)) {
            *(undefined8 *)(lVar7 + 0x28) = uVar4;
            thunk_FUN_7fff5f491fd0();
            if (2 < *(uint *)(lVar7 + 0x18)) {
              *(undefined8 *)(lVar7 + 0x30) = _DAT_7fff62426620;
              thunk_FUN_7fff5f491fd0();
              uVar4 = FUN_7fff5fc6ce20((longlong)(*(int *)(self + 200) - *(int *)(self + 0xb0)),
                                       _DAT_7fff6243f290,0);
              if (3 < *(uint *)(lVar7 + 0x18)) {
                *(undefined8 *)(lVar7 + 0x38) = uVar4;
                thunk_FUN_7fff5f491fd0();
                if (4 < *(uint *)(lVar7 + 0x18)) {
                  *(undefined8 *)(lVar7 + 0x40) = _DAT_7fff624021d8;
                  thunk_FUN_7fff5f491fd0();
                  uVar4 = FUN_7fff5fc6ce20((longlong)-iVar11,_DAT_7fff6243f290,0);
                  if (5 < *(uint *)(lVar7 + 0x18)) {
                    *(undefined8 *)(lVar7 + 0x48) = uVar4;
                    thunk_FUN_7fff5f491fd0();
                    if (6 < *(uint *)(lVar7 + 0x18)) {
                      *(undefined8 *)(lVar7 + 0x50) = _DAT_7fff624191d8;
                      thunk_FUN_7fff5f491fd0();
                      uVar4 = FUN_7fff60e712f0(lVar7,0);
                      if (lVar6 != 0) {
                        FUN_7fff5ff0eed0(lVar6,uVar4,0);
                        uVar3 = SmithGrantInfoWindow_GetCurrentRequireMaterialPoint
                                          (self,(undefined *)0x0);
                        lVar6 = *(longlong *)(self + 0x58);
                        if ((*(longlong *)(self + 0xe0) != 0) &&
                           (lVar7 = FUN_7fff5ff8a970(*(longlong *)(self + 0xe0),0), lVar7 != 0)) {
                          iVar9 = FUN_7fff5ff1ac40(lVar7,*(undefined4 *)(self + 0xac),1);
                          uVar4 = FUN_7fff5fc6d000((longlong)iVar9,0);
                          if (DAT_7fff625e1394 == '\0') {
                            FUN_7fff5f47d450(&DAT_7fff624700a0);
                            DAT_7fff625e1394 = '\x01';
                          }
                          if (*(int *)(_DAT_7fff624700a0 + 0xe0) == 0) {
                            func_0x7fff5f47d6f0();
                          }
                          uVar8 = FUN_7fff5fc6cf60(6,(uVar3 ^ (int)uVar3 >> 0x1f) -
                                                     ((int)uVar3 >> 0x1f));
                          uVar4 = FUN_7fff60e71650(uVar4,_DAT_7fff623ffd48,uVar8,0);
                          if (lVar6 != 0) {
                            FUN_7fff5ff0eed0(lVar6,uVar4,0);
                            return;
                          }
                        }
                      }
                      goto LAB_7fff5fc8731a;
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
  FUN_7fff5f47d650();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

