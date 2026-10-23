
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithGrantInfoWindow_UpdateDetailVal(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  uint uVar2;
  int iVar3;
  undefined8 uVar4;
  longlong *plVar5;
  longlong lVar6;
  longlong lVar7;
  undefined8 uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int aiStackX_8 [2];
  int aiStackX_18 [2];
  undefined4 auStackX_20 [2];
  undefined1 auStack_68 [20];
  int iStack_54;
  int iStack_48;
  
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
  if ((*(int *)(self + 0xa4) == 0xc) || (iVar3 = 1, *(int *)(self + 0xa4) == 0x6e)) {
    iVar3 = 10;
  }
  lVar6 = *(longlong *)(self + 0x98);
  uVar4 = FUN_7fff5fc6d060((*(int *)(self + 0xd4) + *(int *)(self + 0xa0)) * iVar3,0);
  if (lVar6 == 0) goto LAB_7fff5fc872de;
  FUN_7fff5ff0eed0(lVar6,uVar4,0);
  iVar9 = *(int *)(self + 0xa4);
  if (*(int *)(_DAT_7fff62420f50 + 0xe0) == 0) {
    func_0x7fff5f47d6f0(_DAT_7fff62420f50);
  }
  if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) == 0) goto LAB_7fff5fc872de;
  FUN_7fff6088c670(auStack_68,**(longlong **)(_DAT_7fff62420f50 + 0xb8),iVar9,_DAT_7fff6244ce08);
  if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) == 0) goto LAB_7fff5fc872de;
  FUN_7fff6088c670(auStack_68,**(longlong **)(_DAT_7fff62420f50 + 0xb8),iVar9,_DAT_7fff6244ce08);
  iVar11 = 0;
  iVar10 = *(int *)(self + 0xa0);
  iVar12 = *(int *)(self + 0xd4) + iVar10;
  if (self[0xfc] == '\0') {
    if (((iVar9 - 0x16U < 0xb) && ((iVar9 - 0x16U & 1) == 0)) || (iVar9 == 0xc)) {
      if (iStack_54 < iVar12) {
        iVar9 = (iVar12 - iStack_54) * iStack_48 + iStack_54;
      }
      else {
        if (-iStack_54 <= iVar12) goto LAB_7fff5fc86e1f;
        iVar9 = (iVar12 + iStack_54) * iStack_48 - iStack_54;
      }
      lVar6 = *(longlong *)(self + 0x98);
      uVar4 = FUN_7fff5fc6d060(iVar9 * iVar3,0);
      if (lVar6 == 0) goto LAB_7fff5fc872de;
      FUN_7fff5ff0eed0(lVar6,uVar4,0);
    }
LAB_7fff5fc86e1f:
    if (iVar10 < 0) {
      if (iStack_54 < *(int *)(self + 0xd4)) {
        iVar9 = iStack_54 - *(int *)(self + 0xd4);
        iVar3 = iVar10;
        if (iVar10 <= iVar9) {
          iVar3 = iVar9;
        }
      }
      else {
        iVar3 = 0;
      }
      iVar10 = iVar10 - iVar3;
      if ((iVar12 < -iStack_54) && (iVar11 = iVar10, iVar10 <= iVar12 + iStack_54)) {
        iVar11 = iVar12 + iStack_54;
      }
      iVar9 = *(int *)(self + 0xb4);
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
                    ((float)((iVar3 - iVar11) + iVar10) + (float)iVar11 * _DAT_7fff61b52b4c) *
                    (float)iVar9);
    }
    else if (iVar10 != 0) {
      if (*(int *)(self + 0xd4) < -iStack_54) {
        iVar9 = -(*(int *)(self + 0xd4) + iStack_54);
        iVar3 = iVar10;
        if (iVar9 <= iVar10) {
          iVar3 = iVar9;
        }
      }
      else {
        iVar3 = 0;
      }
      iVar10 = iVar10 - iVar3;
      if ((iStack_54 < iVar12) && (iVar11 = iVar10, iVar12 - iStack_54 <= iVar10)) {
        iVar11 = iVar12 - iStack_54;
      }
      iVar11 = (int)(short)((((short)iVar10 - (short)iVar11) + (short)iVar3) *
                           *(short *)(self + 0xb4)) +
               (int)(short)((short)iVar11 * *(short *)(self + 0xb4) * 2);
    }
  }
  else {
    iVar11 = iVar10 * *(int *)(self + 0xb4);
  }
  plVar5 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,3);
  aiStackX_8[0] = *(int *)(self + 200) - *(int *)(self + 0xb0);
  lVar6 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,aiStackX_8);
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
    aiStackX_18[0] = iVar11;
    lVar6 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,aiStackX_18);
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
        func_0x7fff5f4d3920(_DAT_7fff624767c0,plVar5,0);
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
                        uVar2 = FUN_7fff5fc84d80(self,0);
                        lVar6 = *(longlong *)(self + 0x58);
                        if ((*(longlong *)(self + 0xe0) != 0) &&
                           (lVar7 = FUN_7fff5ff8a970(*(longlong *)(self + 0xe0),0), lVar7 != 0)) {
                          iVar3 = FUN_7fff5ff1ac40(lVar7,*(undefined4 *)(self + 0xac),1);
                          uVar4 = FUN_7fff5fc6d000((longlong)iVar3,0);
                          if (DAT_7fff625e1394 == '\0') {
                            FUN_7fff5f47d450(&DAT_7fff624700a0);
                            DAT_7fff625e1394 = '\x01';
                          }
                          if (*(int *)(_DAT_7fff624700a0 + 0xe0) == 0) {
                            func_0x7fff5f47d6f0();
                          }
                          uVar8 = FUN_7fff5fc6cf60(6,(uVar2 ^ (int)uVar2 >> 0x1f) -
                                                     ((int)uVar2 >> 0x1f));
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

