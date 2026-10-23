
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte _ConnectWaitManufacture_d__86_MoveNext(undefined *self,undefined *methodInfo)

{
  char cVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined *self_00;
  undefined8 uVar5;
  longlong *plVar6;
  code *pcVar7;
  byte bVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  undefined *puVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  longlong lVar15;
  undefined8 uVar16;
  longlong lVar17;
  float fVar18;
  undefined4 auStackX_8 [2];
  undefined8 in_stack_ffffffffffffffb8;
  
  uVar9 = (undefined4)((ulonglong)in_stack_ffffffffffffffb8 >> 0x20);
  if (DAT_7fff625e42b5 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62403388);
    FUN_7fff5f47d450(&DAT_7fff624503e0);
    FUN_7fff5f47d450(&DAT_7fff62450258);
    FUN_7fff5f47d450(&DAT_7fff62473318);
    FUN_7fff5f47d450(&DAT_7fff62427f28);
    FUN_7fff5f47d450(&DAT_7fff6242a400);
    FUN_7fff5f47d450(&DAT_7fff6242f158);
    FUN_7fff5f47d450(&DAT_7fff624444f8);
    FUN_7fff5f47d450(&DAT_7fff62444a18);
    FUN_7fff5f47d450(&DAT_7fff624532c0);
    FUN_7fff5f47d450(&DAT_7fff62401db0);
    FUN_7fff5f47d450(&DAT_7fff62450e50);
    FUN_7fff5f47d450(&DAT_7fff624378f8);
    FUN_7fff5f47d450(&DAT_7fff623fd630);
    FUN_7fff5f47d450(&DAT_7fff62459938);
    FUN_7fff5f47d450(&DAT_7fff6245d9b0);
    FUN_7fff5f47d450(&DAT_7fff62416c98);
    FUN_7fff5f47d450(&DAT_7fff62418fa8);
    FUN_7fff5f47d450(&DAT_7fff62419078);
    FUN_7fff5f47d450(&DAT_7fff62419148);
    FUN_7fff5f47d450(&DAT_7fff6242b1b8);
    DAT_7fff625e42b5 = '\x01';
  }
  iVar2 = *(int *)(self + 0x10);
  self_00 = *(undefined **)(self + 0x20);
  if (iVar2 == 0) {
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    uVar13 = func_0x7fff5f44ff00(_DAT_7fff6242b1b8);
    func_0x7fff5f4d30f0(uVar13,0);
    *(undefined8 *)(self + 0x28) = uVar13;
    thunk_FUN_7fff5f491fd0();
    if (*(longlong *)(self + 0x28) == 0) goto LAB_7fff5fca8046;
    *(undefined8 *)(*(longlong *)(self + 0x28) + 0x10) = *(undefined8 *)(self + 0x20);
    thunk_FUN_7fff5f491fd0();
    if (self_00 == (undefined *)0x0) goto LAB_7fff5fca8046;
    FUN_7fff5fc75ae0(self_00,0);
    FUN_7fff5fc75b70(self_00,0);
    lVar15 = FUN_7fff60c4bc00(_DAT_7fff6245d9b0);
    if ((lVar15 == 0) || (*(longlong *)(lVar15 + 0x188) == 0)) goto LAB_7fff5fca8046;
    *(undefined1 *)(*(longlong *)(lVar15 + 0x188) + 0x100) = 1;
    lVar15 = FUN_7fff60c4bc00(_DAT_7fff6245d9b0);
    if (lVar15 == 0) goto LAB_7fff5fca8046;
    FUN_7fff5fda8f10(lVar15,0);
    if ((*(longlong *)(self_00 + 400) == 0) ||
       (lVar15 = FUN_7fff5ff8a9f0(*(longlong *)(self_00 + 400),0), lVar15 == 0))
    goto LAB_7fff5fca8046;
    *(undefined8 *)(self + 0x30) = *(undefined8 *)(lVar15 + 0x58);
    thunk_FUN_7fff5f491fd0();
    lVar15 = func_0x7fff5f44ff00(_DAT_7fff62427f28);
    FUN_7fff6082c480(lVar15,_DAT_7fff62450258);
    fVar18 = (float)FUN_7fff5f5e6b00(0);
    if (lVar15 == 0) goto LAB_7fff5fca8046;
    FUN_7fff6081b1c0(lVar15,6,(int)(fVar18 * _DAT_7fff61b52cfc),_DAT_7fff624503e0);
    uVar13 = *(undefined8 *)(self + 0x28);
    uVar14 = func_0x7fff5f44ff00(_DAT_7fff62403388);
    FUN_7fff6083fe30(uVar14,uVar13,_DAT_7fff62418fa8,0);
    if (*(longlong *)(self + 0x30) == 0) goto LAB_7fff5fca8046;
    uVar9 = FUN_7fff604c1bf0(*(longlong *)(self + 0x30),0x98d8e8,uVar14,
                             *(undefined8 *)(self_00 + 0x120),0,lVar15,0);
    *(undefined4 *)(self + 0x38) = uVar9;
    if (*(longlong *)(self_00 + 0x118) == 0) goto LAB_7fff5fca8046;
    FUN_7fff618a4510(*(longlong *)(self_00 + 0x118),1,0);
    self_00[0x1e0] = 1;
    puVar12 = SmithManufacture_EquipmentProductionConnect
                        (self_00,*(undefined **)(self + 0x30),*(int *)(self + 0x38),(undefined *)0x0
                        );
    FUN_7fff618a87c0(self_00,puVar12,0);
LAB_7fff5fca7ab0:
    if (self_00[0x1e0] != '\0') {
      *(undefined8 *)(self + 0x18) = 0;
      thunk_FUN_7fff5f491fd0();
      *(undefined4 *)(self + 0x10) = 1;
      return 1;
    }
    *(undefined8 *)(self + 0x40) = *(undefined8 *)(self_00 + 0x1e8);
    thunk_FUN_7fff5f491fd0();
    if (*(longlong *)(self + 0x40) == 0) {
      return 0;
    }
    if (*(longlong *)(self + 0x28) == 0) goto LAB_7fff5fca8046;
    *(undefined1 *)(*(longlong *)(self + 0x28) + 0x18) = 0;
    lVar15 = *(longlong *)(self + 0x30);
    uVar9 = *(undefined4 *)(self + 0x38);
    if (*(longlong *)(self + 0x40) == 0) goto LAB_7fff5fca8046;
    cVar1 = *(char *)(*(longlong *)(self + 0x40) + 0x40);
    uVar13 = *(undefined8 *)(self + 0x28);
    uVar14 = func_0x7fff5f44ff00(_DAT_7fff62403388);
    FUN_7fff6083fe30(uVar14,uVar13,_DAT_7fff62419078,0);
    if (lVar15 == 0) goto LAB_7fff5fca8046;
    uVar13 = *(undefined8 *)(self_00 + 0x120);
    uVar10 = FUN_7fff604c1f60(lVar15,uVar9,0x98d8ea - (uint)(cVar1 != '\0'),uVar14,uVar13,0,0,0);
    uVar9 = (undefined4)((ulonglong)uVar13 >> 0x20);
    *(undefined4 *)(self + 0x38) = uVar10;
  }
  else {
    if (iVar2 == 1) {
      *(undefined4 *)(self + 0x10) = 0xffffffff;
      if (self_00 == (undefined *)0x0) goto LAB_7fff5fca8046;
      goto LAB_7fff5fca7ab0;
    }
    if (iVar2 != 2) {
      return 0;
    }
    *(undefined4 *)(self + 0x10) = 0xffffffff;
  }
  if (*(longlong *)(self + 0x28) != 0) {
    uVar10 = 0;
    if (*(char *)(*(longlong *)(self + 0x28) + 0x18) == '\0') {
      auStackX_8[0] = 0;
      uVar13 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,auStackX_8);
      *(undefined8 *)(self + 0x18) = uVar13;
      thunk_FUN_7fff5f491fd0();
      *(undefined4 *)(self + 0x10) = 2;
      return 1;
    }
    if (((*(longlong *)(self + 0x30) != 0) &&
        (FUN_7fff604c26c0(*(longlong *)(self + 0x30),*(undefined4 *)(self + 0x38),0),
        self_00 != (undefined *)0x0)) && (*(longlong *)(self_00 + 0x118) != 0)) {
      FUN_7fff618a4510(*(longlong *)(self_00 + 0x118),0,0);
      uVar13 = func_0x7fff5f47c850(_DAT_7fff62416c98,4);
      if (*(longlong *)(self_00 + 0x1d0) != 0) {
        uVar14 = FUN_7fff60a940e0(*(longlong *)(self_00 + 0x1d0),_DAT_7fff62401db0);
        FUN_7fff61023540(uVar14,*(int *)(self_00 + 0x168) << 2,uVar13,0,CONCAT44(uVar9,4),0);
        if ((*(longlong *)(self_00 + 0xd0) != 0) &&
           (lVar15 = FUN_7fff618a1ae0(*(longlong *)(self_00 + 0xd0),0), lVar15 != 0)) {
          FUN_7fff618a4510(lVar15,1,0);
          if (*(longlong *)(self + 0x40) != 0) {
            uVar14 = *(undefined8 *)(*(longlong *)(self + 0x40) + 0x28);
            uVar5 = *(undefined8 *)(self + 0x28);
            uVar16 = func_0x7fff5f44ff00(_DAT_7fff624444f8);
            FUN_7fff60a1d7e0(uVar16,uVar5,_DAT_7fff62419148,0);
            uVar14 = FUN_7fff6069d430(uVar14,uVar16,_DAT_7fff6242f158);
            lVar15 = FUN_7fff6069cf90(uVar14,_DAT_7fff6242a400);
            if (lVar15 != 0) {
              lVar17 = FUN_7fff60a94f50(lVar15,0,_DAT_7fff624378f8);
              lVar15 = *(longlong *)(self_00 + 0xd0);
              if (lVar17 != 0) {
                uVar11 = FUN_7fff5f252ec0(0,_DAT_7fff62444a18,lVar17);
                uVar9 = *(undefined4 *)(self_00 + 0x24);
                if (lVar15 != 0) {
                  if (DAT_7fff625e42ce == '\0') {
                    FUN_7fff5f47d450(&DAT_7fff62426170);
                    DAT_7fff625e42ce = '\x01';
                  }
                  lVar17 = *(longlong *)(lVar15 + 0x30);
                  uVar14 = FUN_7fff5fc99d70(lVar15,uVar11,(byte)((uint)uVar9 >> 0x1f) ^ 1,0);
                  uVar14 = FUN_7fff60e71970(_DAT_7fff62426170,uVar14,0);
                  if (lVar17 != 0) {
                    FUN_7fff5ff0eed0(lVar17,uVar14,0);
                    if (0 < *(int *)(self_00 + 0x24)) {
                      if (((*(longlong *)(self_00 + 0x150) == 0) ||
                          (lVar15 = FUN_7fff60a94f50(*(longlong *)(self_00 + 0x150),
                                                     *(undefined4 *)(self_00 + 0x160),
                                                     _DAT_7fff623fd630), lVar15 == 0)) ||
                         ((lVar15 = FUN_7fff6083faa0(lVar15,*(undefined4 *)(self_00 + 0x164),
                                                     _DAT_7fff62473318), lVar15 == 0 ||
                          (lVar15 = FUN_7fff60a94f50(lVar15,*(undefined4 *)(self_00 + 0x168),
                                                     _DAT_7fff62450e50), lVar15 == 0))))
                      goto LAB_7fff5fca8046;
                      uVar10 = *(undefined4 *)(lVar15 + 0x18);
                    }
                    if (*(longlong *)(self + 0x40) != 0) {
                      iVar2 = *(int *)(*(longlong *)(self + 0x40) + 0x3c);
                      if ((*(longlong *)(self_00 + 400) != 0) &&
                         (lVar15 = FUN_7fff5ff8ad00(*(longlong *)(self_00 + 400),0), lVar15 != 0)) {
                        iVar3 = *(int *)(lVar15 + 0x20);
                        if ((*(longlong *)(self_00 + 400) != 0) &&
                           (lVar15 = FUN_7fff5ff8ad00(*(longlong *)(self_00 + 400),0), lVar15 != 0))
                        {
                          iVar4 = *(int *)(lVar15 + 0x20);
                          if ((((*(longlong *)(self_00 + 0x150) != 0) &&
                               (lVar15 = FUN_7fff60a94f50(*(longlong *)(self_00 + 0x150),
                                                          *(undefined4 *)(self_00 + 0x160),
                                                          _DAT_7fff623fd630), lVar15 != 0)) &&
                              (lVar15 = FUN_7fff6083faa0(lVar15,*(undefined4 *)(self_00 + 0x164),
                                                         _DAT_7fff62473318), lVar15 != 0)) &&
                             (lVar15 = FUN_7fff60a94f50(lVar15,*(undefined4 *)(self_00 + 0x168),
                                                        _DAT_7fff62450e50), lVar15 != 0)) {
                            if (iVar4 / 100 - (int)*(short *)(lVar15 + 0x16) < 0xb) {
                              bVar8 = 1;
                            }
                            else {
                              bVar8 = (byte)~(byte)((uint)*(undefined4 *)(self_00 + 0x24) >> 0x18)
                                      >> 7;
                            }
                            if (*(longlong *)(self_00 + 0xd0) != 0) {
                              FUN_7fff5fc9a640(*(longlong *)(self_00 + 0xd0),uVar10,iVar2 - iVar3,
                                               0xffffffff,bVar8,uVar13,0);
                              lVar15 = *(longlong *)(self_00 + 0xd0);
                              if ((((*(longlong *)(self_00 + 0x150) != 0) &&
                                   (lVar17 = FUN_7fff60a94f50(*(longlong *)(self_00 + 0x150),
                                                              *(undefined4 *)(self_00 + 0x160),
                                                              _DAT_7fff623fd630), lVar17 != 0)) &&
                                  ((lVar17 = FUN_7fff6083faa0(lVar17,*(undefined4 *)
                                                                      (self_00 + 0x164),
                                                              _DAT_7fff62473318), lVar17 != 0 &&
                                   ((lVar17 = FUN_7fff60a94f50(lVar17,*(undefined4 *)
                                                                       (self_00 + 0x168),
                                                               _DAT_7fff62450e50), lVar17 != 0 &&
                                    (lVar15 != 0)))))) &&
                                 (lVar15 = *(longlong *)(lVar15 + 0x28), lVar15 != 0)) {
                                func_0x7fff5fc30c60(lVar15,*(undefined4 *)(lVar17 + 0x20),0);
                                lVar15 = FUN_7fff60c4bc00(_DAT_7fff62459938);
                                if ((*(longlong *)(self + 0x40) != 0) && (lVar15 != 0)) {
                                  FUN_7fff603e3bd0(lVar15,*(undefined4 *)
                                                           (*(longlong *)(self + 0x40) + 0x3c),0);
                                  if (*(longlong *)(self_00 + 0x58) != 0) {
                                    plVar6 = *(longlong **)(self_00 + 0x28);
                                    if (plVar6 == (longlong *)0x0) goto LAB_7fff5fca8046;
                                    (**(code **)(*plVar6 + 0x188))
                                              (plVar6,*(undefined8 *)(*plVar6 + 400));
                                  }
                                  if (*(longlong *)(self_00 + 0x60) != 0) {
                                    plVar6 = *(longlong **)(self_00 + 0x28);
                                    if (plVar6 == (longlong *)0x0) goto LAB_7fff5fca8046;
                                    (**(code **)(*plVar6 + 0x188))
                                              (plVar6,*(undefined8 *)(*plVar6 + 400));
                                  }
                                  FUN_7fff5fc754e0(self_00,0);
                                  return 0;
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
            }
          }
        }
      }
    }
  }
LAB_7fff5fca8046:
  FUN_7fff5f47d660();
  pcVar7 = (code *)swi(3);
  bVar8 = (*pcVar7)();
  return bVar8;
}

