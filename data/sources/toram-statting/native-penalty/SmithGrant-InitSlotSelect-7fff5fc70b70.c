
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithGrant_InitSlotSelect(undefined *self,undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  uint uVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  longlong lVar11;
  undefined8 uVar12;
  longlong *plVar13;
  longlong *plVar14;
  longlong lVar15;
  undefined1 uVar16;
  longlong lVar17;
  int iVar18;
  uint uVar19;
  longlong lVar20;
  uint uVar21;
  longlong lVar22;
  float fVar23;
  uint unaff_XMM6_Da;
  int iStackX_18;
  undefined8 uStack_d8;
  undefined8 uStack_c8;
  undefined4 uStack_c0;
  undefined8 uStack_b8;
  undefined4 uStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined4 uStack_98;
  int iStack_94;
  int iStack_88;
  undefined8 uStack_70;
  uint uStack_48;
  undefined1 *puStack_40;
  
  if (DAT_7fff625e421c == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62450860);
    FUN_7fff5f47d450(&DAT_7fff6244ce08);
    FUN_7fff5f47d450(&DAT_7fff623fc188);
    FUN_7fff5f47d450(&DAT_7fff62409048);
    FUN_7fff5f47d450(&DAT_7fff62432448);
    FUN_7fff5f47d450(&DAT_7fff624539e0);
    FUN_7fff5f47d450(&DAT_7fff6246bee0);
    FUN_7fff5f47d450(&DAT_7fff62420f50);
    FUN_7fff5f47d450(&DAT_7fff624485c8);
    FUN_7fff5f47d450(&DAT_7fff62424ed0);
    FUN_7fff5f47d450(0x7fff62425128);
    FUN_7fff5f47d450(&DAT_7fff62422c48);
    FUN_7fff5f47d450(&DAT_7fff62443180);
    FUN_7fff5f47d450(&DAT_7fff6240e4b0);
    FUN_7fff5f47d450(&DAT_7fff6245cb58);
    FUN_7fff5f47d450(&DAT_7fff624543d8);
    FUN_7fff5f47d450(&DAT_7fff62409dd8);
    FUN_7fff5f47d450(&DAT_7fff62416570);
    FUN_7fff5f47d450(&DAT_7fff6242a088);
    FUN_7fff5f47d450(&DAT_7fff623f6340);
    FUN_7fff5f47d450(&DAT_7fff623fda58);
    FUN_7fff5f47d450(&DAT_7fff623f61a0);
    FUN_7fff5f47d450(&DAT_7fff6246d1d0);
    DAT_7fff625e421c = '\x01';
  }
  if (*(longlong *)(self + 0x78) != 0) {
    uStack_48 = unaff_XMM6_Da;
    func_0x7fff5fdcfc90();
    lVar11 = *(longlong *)(self + 0x138);
    if (lVar11 != 0) {
      iVar7 = *(int *)(lVar11 + 0x18);
      *(int *)(lVar11 + 0x1c) = *(int *)(lVar11 + 0x1c) + 1;
      *(undefined4 *)(lVar11 + 0x18) = 0;
      if (0 < iVar7) {
        FUN_7fff61022d30(*(undefined8 *)(lVar11 + 0x10),0,iVar7,0);
      }
      if (*(longlong *)(self + 0x90) != 0) {
        lVar11 = FUN_7fff618a1ae0();
        if (lVar11 != 0) {
          FUN_7fff618a4510(lVar11,0,0);
          iVar7 = SmithGrant_getUsableSlotCount(self,(undefined *)0x0);
          if (*(longlong *)(self + 0x120) != 0) {
            uVar12 = *(undefined8 *)(*(longlong *)(self + 0x120) + 0x10);
            if (*(int *)(_DAT_7fff6242a088 + 0xe0) == 0) {
              func_0x7fff5f47d6f0();
            }
            lVar11 = *(longlong *)(*(longlong *)(_DAT_7fff6242a088 + 0xb8) + 0x10);
            if (lVar11 == 0) {
              if (*(int *)(_DAT_7fff6242a088 + 0xe0) == 0) {
                func_0x7fff5f47d6f0();
              }
              uVar1 = **(undefined8 **)(_DAT_7fff6242a088 + 0xb8);
              lVar11 = func_0x7fff5f44ff00(_DAT_7fff624539e0);
              FUN_7fff60a1d7e0(lVar11,uVar1,_DAT_7fff62416570,0);
              *(longlong *)(*(longlong *)(_DAT_7fff6242a088 + 0xb8) + 0x10) = lVar11;
              thunk_FUN_7fff5f491fd0();
            }
            uVar12 = FUN_7fff6069d430(uVar12,lVar11,_DAT_7fff62432448);
            iStackX_18 = FUN_7fff6068aa20(uVar12,_DAT_7fff62409048);
            uVar5 = _DAT_7fff61b52c00;
            fVar23 = _DAT_7fff61b52b4c;
            iStackX_18 = iVar7 - iStackX_18;
            uVar19 = 0;
            while( true ) {
              uVar21 = 0;
              if (*(int *)(_DAT_7fff624543d8 + 0xe0) == 0) {
                func_0x7fff5f47d6f0();
              }
              if (**(int **)(_DAT_7fff624543d8 + 0xb8) <= (int)uVar19) break;
              uVar16 = 1;
              if (*(longlong *)(self + 0x88) == 0) goto LAB_7fff5fc7199e;
              FUN_7fff5ff0eed0(*(longlong *)(self + 0x88),_DAT_7fff6246d1d0,0);
              lVar11 = *(longlong *)(self + 0x120);
              if (((lVar11 == 0) || (lVar15 = *(longlong *)(lVar11 + 0x10), lVar15 == 0)) ||
                 ((int)*(uint *)(lVar15 + 0x18) <= (int)uVar19)) goto LAB_7fff5fc7199e;
              if (*(uint *)(lVar15 + 0x18) <= uVar19) goto LAB_7fff5fc719cc;
              lVar20 = (longlong)(int)uVar19;
              lVar15 = *(longlong *)(lVar15 + 0x20 + lVar20 * 8);
              if (lVar15 == 0) goto LAB_7fff5fc7199e;
              iVar18 = *(int *)(lVar15 + 0x30) + *(int *)(lVar15 + 0x28);
              if (((*(char *)(lVar15 + 0x2c) != '\0') ||
                  (*(int *)(lVar15 + 0x30) + *(int *)(lVar15 + 0x28) != 0)) &&
                 (0 < *(int *)(lVar15 + 0x20))) {
                lVar15 = *(longlong *)(*(longlong *)(lVar11 + 0x10) + 0x20 + lVar20 * 8);
                if ((*(char *)(lVar15 + 0x2c) == '\0') &&
                   (*(int *)(lVar15 + 0x30) + *(int *)(lVar15 + 0x28) == 0)) {
LAB_7fff5fc70f78:
                  lVar22 = *(longlong *)(self + 0x88);
                  lVar17 = *(longlong *)(self + 0x30);
LAB_7fff5fc70fa0:
                  lVar11 = *(longlong *)(lVar11 + 0x10);
                  if ((lVar11 == 0) || ((int)*(uint *)(lVar11 + 0x18) <= (int)uVar19))
                  goto LAB_7fff5fc719ba;
                  if (*(uint *)(lVar11 + 0x18) <= uVar19) {
LAB_7fff5fc719b4:
                    FUN_7fff5f47d650();
                    pcVar2 = (code *)swi(3);
                    (*pcVar2)();
                    return;
                  }
                  lVar11 = *(longlong *)(lVar11 + 0x20 + lVar20 * 8);
                  if (lVar11 == 0) {
LAB_7fff5fc719ba:
                    FUN_7fff5f47d660();
                    pcVar2 = (code *)swi(3);
                    (*pcVar2)();
                    return;
                  }
                  if ((*(char *)(lVar11 + 0x2c) == '\0') &&
                     (*(int *)(lVar11 + 0x30) + *(int *)(lVar11 + 0x28) == 0)) {
                    uStack_98 = 0;
                  }
                  else {
                    uStack_98 = *(undefined4 *)(lVar11 + 0x20);
                  }
                  uStack_a8 = _DAT_7fff62450860;
                  uStack_a0 = 0xffffffffffffffff;
                  uVar12 = FUN_7fff6104ddb0(&uStack_a8,0);
                  uVar12 = FUN_7fff60e71970(_DAT_7fff623f61a0,uVar12,0);
                  if (lVar17 == 0) goto LAB_7fff5fc719ba;
                  plVar13 = (longlong *)FUN_7fff5f2550e0(_DAT_7fff62409dd8,lVar17,uVar12);
                  plVar14 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
                  lVar11 = FUN_7fff5fc6d060(iVar18,0);
                  if (plVar14 == (longlong *)0x0) goto LAB_7fff5fc719ba;
                  if (lVar11 != 0) {
                    lVar15 = func_0x7fff5f47c7e0(lVar11,*(undefined8 *)(*plVar14 + 0x40));
                    if (lVar15 == 0) {
                      uVar12 = func_0x7fff5f47d0b0();
                      FUN_7fff5f47d620(uVar12,0);
                      pcVar2 = (code *)swi(3);
                      (*pcVar2)();
                      return;
                    }
                  }
                  if ((int)plVar14[3] == 0) goto LAB_7fff5fc719b4;
                  plVar14[4] = lVar11;
                  thunk_FUN_7fff5f491fd0();
                  if (plVar13 == (longlong *)0x0) goto LAB_7fff5fc719ba;
                  uVar12 = (**(code **)(*plVar13 + 0x1a8))
                                     (plVar13,plVar14,*(undefined8 *)(*plVar13 + 0x1b0));
                  if (lVar22 == 0) goto LAB_7fff5fc719ba;
                  FUN_7fff5ff0eed0(lVar22,uVar12,0);
                  if (((*(longlong *)(self + 0x120) == 0) ||
                      (lVar11 = *(longlong *)(*(longlong *)(self + 0x120) + 0x10), lVar11 == 0)) ||
                     ((int)*(uint *)(lVar11 + 0x18) <= (int)uVar19)) goto LAB_7fff5fc719ba;
                  if (*(uint *)(lVar11 + 0x18) <= uVar19) goto LAB_7fff5fc719b4;
                  lVar11 = *(longlong *)(lVar11 + 0x20 + lVar20 * 8);
                  if (lVar11 == 0) goto LAB_7fff5fc719ba;
                  iVar18 = *(int *)(lVar11 + 0x30);
                  if ((*(char *)(lVar11 + 0x2c) == '\0') && (iVar18 + *(int *)(lVar11 + 0x28) == 0))
                  {
                    uVar10 = 0;
                  }
                  else {
                    uVar10 = *(undefined4 *)(lVar11 + 0x20);
                  }
                  if (*(longlong *)(self + 0xb8) == 0) goto LAB_7fff5fc719ba;
                  cVar6 = func_0x7fff5fc84bf0(*(longlong *)(self + 0xb8),uVar10,0);
                  if (cVar6 != '\0') {
                    if (*(int *)(_DAT_7fff62420f50 + 0xe0) == 0) {
                      func_0x7fff5f47d6f0(_DAT_7fff62420f50);
                    }
                    if (((*(longlong *)(self + 0x120) == 0) ||
                        (lVar11 = *(longlong *)(*(longlong *)(self + 0x120) + 0x10), lVar11 == 0))
                       || ((int)*(uint *)(lVar11 + 0x18) <= (int)uVar19)) goto LAB_7fff5fc7199e;
                    if (*(uint *)(lVar11 + 0x18) <= uVar19) goto LAB_7fff5fc719cc;
                    lVar11 = *(longlong *)(lVar11 + 0x20 + lVar20 * 8);
                    if (lVar11 == 0) goto LAB_7fff5fc7199e;
                    if ((*(char *)(lVar11 + 0x2c) != '\0') ||
                       (uVar10 = 0, *(int *)(lVar11 + 0x30) + *(int *)(lVar11 + 0x28) != 0)) {
                      uVar10 = *(undefined4 *)(lVar11 + 0x20);
                    }
                    if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) == 0) goto LAB_7fff5fc7199e;
                    FUN_7fff6088c670(&uStack_a8,**(longlong **)(_DAT_7fff62420f50 + 0xb8),uVar10,
                                     _DAT_7fff6244ce08);
                    iVar8 = iStack_94;
                    if (((*(longlong *)(self + 0x120) == 0) ||
                        (lVar11 = *(longlong *)(*(longlong *)(self + 0x120) + 0x10), lVar11 == 0))
                       || ((int)*(uint *)(lVar11 + 0x18) <= (int)uVar19)) goto LAB_7fff5fc7199e;
                    if (*(uint *)(lVar11 + 0x18) <= uVar19) goto LAB_7fff5fc719cc;
                    lVar11 = *(longlong *)(lVar11 + 0x20 + lVar20 * 8);
                    if (lVar11 == 0) goto LAB_7fff5fc7199e;
                    if ((*(char *)(lVar11 + 0x2c) != '\0') ||
                       (uVar10 = 0, *(int *)(lVar11 + 0x30) + *(int *)(lVar11 + 0x28) != 0)) {
                      uVar10 = *(undefined4 *)(lVar11 + 0x20);
                    }
                    if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) == 0) goto LAB_7fff5fc7199e;
                    FUN_7fff6088c670(&uStack_a8,**(longlong **)(_DAT_7fff62420f50 + 0xb8),uVar10);
                    if (iVar8 < iVar18) {
                      iVar18 = iVar8 + (iVar18 - iVar8) / iStack_88;
                    }
                    else if (iVar18 < -iVar8) {
                      iVar18 = (iVar8 + iVar18) / iStack_88 - iVar8;
                    }
                  }
                  if (((*(longlong *)(self + 0x120) == 0) ||
                      (lVar11 = *(longlong *)(*(longlong *)(self + 0x120) + 0x10), lVar11 == 0)) ||
                     ((int)*(uint *)(lVar11 + 0x18) <= (int)uVar19)) goto LAB_7fff5fc7199e;
                  if (*(uint *)(lVar11 + 0x18) <= uVar19) goto LAB_7fff5fc719cc;
                  lVar11 = *(longlong *)(lVar11 + 0x20 + lVar20 * 8);
                  if (lVar11 == 0) goto LAB_7fff5fc7199e;
                  if ((*(char *)(lVar11 + 0x2c) != '\0') ||
                     (iVar8 = 0, *(int *)(lVar11 + 0x30) + *(int *)(lVar11 + 0x28) != 0)) {
                    iVar8 = *(int *)(lVar11 + 0x20);
                  }
                  if (*(undefined **)(self + 0xb8) == (undefined *)0x0) goto LAB_7fff5fc7199e;
                  iVar8 = SmithGrantInfoWindow_getEnhanceMax
                                    (*(undefined **)(self + 0xb8),1,iVar8,(undefined *)0x0);
                  if (((*(longlong *)(self + 0x120) == 0) ||
                      (lVar11 = *(longlong *)(*(longlong *)(self + 0x120) + 0x10), lVar11 == 0)) ||
                     ((int)*(uint *)(lVar11 + 0x18) <= (int)uVar19)) goto LAB_7fff5fc7199e;
                  if (*(uint *)(lVar11 + 0x18) <= uVar19) goto LAB_7fff5fc719cc;
                  lVar11 = *(longlong *)(lVar11 + 0x20 + lVar20 * 8);
                  if (lVar11 == 0) goto LAB_7fff5fc7199e;
                  if ((*(char *)(lVar11 + 0x2c) != '\0') ||
                     (iVar9 = 0, *(int *)(lVar11 + 0x30) + *(int *)(lVar11 + 0x28) != 0)) {
                    iVar9 = *(int *)(lVar11 + 0x20);
                  }
                  if (*(undefined **)(self + 0xb8) == (undefined *)0x0) goto LAB_7fff5fc7199e;
                  iVar9 = SmithGrantInfoWindow_getEnhanceMax
                                    (*(undefined **)(self + 0xb8),0,iVar9,(undefined *)0x0);
                  if ((iVar18 <= iVar8) && (-iVar9 <= iVar18)) goto LAB_7fff5fc71423;
                  uVar16 = 0;
                }
                else {
                  if (*(int *)(lVar15 + 0x20) == 0xc) {
LAB_7fff5fc70f5c:
                    iVar18 = iVar18 * 10;
                  }
                  else {
                    lVar15 = *(longlong *)(*(longlong *)(lVar11 + 0x10) + 0x20 + lVar20 * 8);
                    if ((*(char *)(lVar15 + 0x2c) == '\0') &&
                       (*(int *)(lVar15 + 0x30) + *(int *)(lVar15 + 0x28) == 0))
                    goto LAB_7fff5fc70f78;
                    if (*(int *)(lVar15 + 0x20) == 0x6e) goto LAB_7fff5fc70f5c;
                  }
                  lVar15 = *(longlong *)(*(longlong *)(lVar11 + 0x10) + 0x20 + lVar20 * 8);
                  if ((*(char *)(lVar15 + 0x2c) == '\0') &&
                     (*(int *)(lVar15 + 0x30) + *(int *)(lVar15 + 0x28) == 0))
                  goto LAB_7fff5fc70f78;
                  lVar22 = *(longlong *)(self + 0x88);
                  lVar17 = *(longlong *)(self + 0x30);
                  if (*(int *)(lVar15 + 0x20) != 0x41) goto LAB_7fff5fc70fa0;
                  lVar11 = *(longlong *)(lVar11 + 0x10);
                  if ((lVar11 == 0) || ((int)*(uint *)(lVar11 + 0x18) <= (int)uVar19)) {
LAB_7fff5fc719c6:
                    FUN_7fff5f47d660();
                    pcVar2 = (code *)swi(3);
                    (*pcVar2)();
                    return;
                  }
                  if (*(uint *)(lVar11 + 0x18) <= uVar19) {
                    FUN_7fff5f47d650();
                    pcVar2 = (code *)swi(3);
                    (*pcVar2)();
                    return;
                  }
                  lVar11 = *(longlong *)(lVar11 + 0x20 + lVar20 * 8);
                  if (lVar11 == 0) goto LAB_7fff5fc719c6;
                  uStack_98 = *(undefined4 *)(lVar11 + 0x24);
                  uStack_a8 = _DAT_7fff623fc188;
                  uStack_a0 = 0xffffffffffffffff;
                  uVar12 = FUN_7fff6104ddb0(&uStack_a8,0);
                  uVar12 = FUN_7fff60e71970(_DAT_7fff623f6340,uVar12,0);
                  if (lVar17 == 0) goto LAB_7fff5fc719c6;
                  plVar13 = (longlong *)FUN_7fff5f2550e0(_DAT_7fff62409dd8,lVar17,uVar12);
                  if (plVar13 == (longlong *)0x0) goto LAB_7fff5fc719c6;
                  uVar12 = (**(code **)(*plVar13 + 0x178))
                                     (plVar13,*(undefined8 *)(*plVar13 + 0x180));
                  if (lVar22 == 0) goto LAB_7fff5fc719c6;
                  FUN_7fff5ff0eed0(lVar22,uVar12,0);
LAB_7fff5fc71423:
                  uVar16 = 1;
                }
                lVar11 = *(longlong *)(self + 0x120);
                if (((lVar11 == 0) || (lVar15 = *(longlong *)(lVar11 + 0x10), lVar15 == 0)) ||
                   ((int)*(uint *)(lVar15 + 0x18) <= (int)uVar19)) goto LAB_7fff5fc7199e;
                if (*(uint *)(lVar15 + 0x18) <= uVar19) goto LAB_7fff5fc719cc;
                lVar15 = *(longlong *)(lVar15 + 0x20 + lVar20 * 8);
                if (lVar15 == 0) goto LAB_7fff5fc7199e;
                if ((((*(char *)(lVar15 + 0x2c) != '\0') ||
                     (*(int *)(lVar15 + 0x30) + *(int *)(lVar15 + 0x28) != 0)) &&
                    (0x78 < *(int *)(lVar15 + 0x20))) &&
                   (((lVar11 = *(longlong *)(*(longlong *)(lVar11 + 0x10) + 0x20 + lVar20 * 8),
                     *(char *)(lVar11 + 0x2c) == '\0' &&
                     (*(int *)(lVar11 + 0x30) + *(int *)(lVar11 + 0x28) == 0)) ||
                    (*(uint *)(lVar11 + 0x20) < 0x81)))) {
                  if (*(longlong *)(self + 0x140) == 0) goto LAB_7fff5fc7199e;
                  plVar13 = (longlong *)FUN_7fff5ff8ac30(*(longlong *)(self + 0x140),0);
                  if (plVar13 == (longlong *)0x0) goto LAB_7fff5fc7199e;
                  lVar11 = (**(code **)(*plVar13 + 0x198))
                                     (plVar13,*(undefined8 *)(*plVar13 + 0x1a0));
                  if (lVar11 == 0) goto LAB_7fff5fc7199e;
                  iVar18 = FUN_7fff5f252ec0(0,_DAT_7fff624485c8,lVar11);
                  if (iVar18 < 0xd2) {
                    uVar16 = 0;
                  }
                }
              }
              uVar12 = *(undefined8 *)(self + 0x80);
              if (DAT_7fff625e12c7 == '\0') {
                FUN_7fff5f47d450(&DAT_7fff62403718);
                DAT_7fff625e12c7 = '\x01';
              }
              uVar1 = **(undefined8 **)(_DAT_7fff62403718 + 0xb8);
              uVar10 = *(undefined4 *)(*(undefined8 **)(_DAT_7fff62403718 + 0xb8) + 1);
              if (DAT_7fff625e12cf == '\0') {
                FUN_7fff5f47d450(&DAT_7fff624318b0);
                DAT_7fff625e12cf = '\x01';
              }
              uVar3 = **(undefined8 **)(_DAT_7fff624318b0 + 0xb8);
              uVar4 = (*(undefined8 **)(_DAT_7fff624318b0 + 0xb8))[1];
              if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
                func_0x7fff5f47d6f0();
              }
              uStack_c8 = uVar1;
              uStack_c0 = uVar10;
              uStack_a8 = uVar3;
              uStack_a0 = uVar4;
              lVar11 = FUN_7fff606c5700(uVar12,&uStack_c8,&uStack_a8);
              uStack_d8 = CONCAT44((float)((uint)*(float *)(self + 0xa0) ^ uVar5) *
                                   (float)(int)uVar19 - *(float *)(self + 0xa0) * fVar23,0x42c80000)
              ;
              if (lVar11 == 0) goto LAB_7fff5fc7199e;
              lVar15 = FUN_7fff618a4a10(lVar11,0);
              if (lVar15 == 0) goto LAB_7fff5fc7199e;
              uStack_b0 = 0;
              uStack_b8 = uStack_d8;
              FUN_7fff618c8e40(lVar15,&uStack_b8,0);
              lVar15 = FUN_7fff606a6750(lVar11,_DAT_7fff6246bee0);
              if (lVar15 == 0) goto LAB_7fff5fc7199e;
              *(undefined **)(lVar15 + 0x38) = self;
              *(uint *)(lVar15 + 0x28) = uVar19;
              thunk_FUN_7fff5f491fd0();
              *(undefined4 *)(lVar15 + 0x2c) = 1;
              FUN_7fff5fc84350(lVar15,uVar16,0);
              if (*(longlong *)(self + 0x88) == 0) goto LAB_7fff5fc7199e;
              cVar6 = func_0x7fff60e73b10(*(undefined8 *)(*(longlong *)(self + 0x88) + 0x118),
                                          _DAT_7fff6246d1d0,0);
              if (cVar6 != '\0') {
                if ((int)uVar19 < iVar7) {
                  if (0 < iStackX_18) {
                    FUN_7fff5fc844a0(lVar15,0);
                    FUN_7fff5fc84350(lVar15,1,0);
                    iStackX_18 = iStackX_18 + -1;
                    goto LAB_7fff5fc716bf;
                  }
                }
                FUN_7fff5fc84540(lVar15,0);
                FUN_7fff5fc84350(lVar15,0,0);
              }
LAB_7fff5fc716bf:
              lVar22 = *(longlong *)(self + 0x120);
              if (((lVar22 == 0) || (lVar17 = *(longlong *)(lVar22 + 0x10), lVar17 == 0)) ||
                 ((int)*(uint *)(lVar17 + 0x18) <= (int)uVar19)) goto LAB_7fff5fc7199e;
              if (*(uint *)(lVar17 + 0x18) <= uVar19) goto LAB_7fff5fc719cc;
              lVar17 = *(longlong *)(lVar17 + 0x20 + lVar20 * 8);
              if (lVar17 == 0) goto LAB_7fff5fc7199e;
              if (((*(char *)(lVar17 + 0x2c) != '\0') ||
                  (*(int *)(lVar17 + 0x30) + *(int *)(lVar17 + 0x28) != 0)) &&
                 ((*(int *)(lVar17 + 0x20) == 0x41 &&
                  (*(char *)(*(longlong *)(*(longlong *)(lVar22 + 0x10) + 0x20 + lVar20 * 8) + 0x2c)
                   != '\0')))) {
                FUN_7fff5fc84350(lVar15,0,0);
              }
              if (*(longlong *)(self + 0x78) == 0) goto LAB_7fff5fc7199e;
              FUN_7fff5fdcf5e0(*(longlong *)(self + 0x78),lVar11,0);
              if (*(longlong *)(self + 0x138) == 0) goto LAB_7fff5fc7199e;
              FUN_7fff5f253100(*(longlong *)(self + 0x138),lVar11);
              uVar19 = uVar19 + 1;
            }
            lVar11 = *(longlong *)(self + 0x78);
            if (DAT_7fff625e12ce == '\0') {
              FUN_7fff5f47d450(&DAT_7fff62403718);
              DAT_7fff625e12ce = '\x01';
            }
            uVar12 = *(undefined8 *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0xc);
            uVar10 = *(undefined4 *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0x14);
            if (DAT_7fff625e142c == '\0') {
              FUN_7fff5f47d450(&DAT_7fff62403718);
              DAT_7fff625e142c = '\x01';
            }
            uVar1 = *(undefined8 *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0x18);
            if (*(int *)(_DAT_7fff624543d8 + 0xe0) == 0) {
              func_0x7fff5f47d6f0();
            }
            fVar23 = (float)**(int **)(_DAT_7fff624543d8 + 0xb8) * *(float *)(self + 0xa0);
            uStack_d8._4_4_ = (float)((ulonglong)uVar1 >> 0x20);
            uStack_d8._0_4_ = (float)uVar1;
            if (lVar11 != 0) {
              uStack_b8 = uVar12;
              uStack_b0 = uVar10;
              FUN_7fff5fdd0230(lVar11,&uStack_b8,
                               CONCAT44(fVar23 * uStack_d8._4_4_,fVar23 * (float)uStack_d8),0);
              if (*(longlong *)(self + 0x78) != 0) {
                FUN_7fff5fdcfec0(*(longlong *)(self + 0x78),_DAT_7fff623fda58,0);
                uVar16 = 0;
                if ((*(longlong *)(self + 0x120) != 0) &&
                   (lVar11 = *(longlong *)(*(longlong *)(self + 0x120) + 0x10), lVar11 != 0)) {
                  goto LAB_7fff5fc71888;
                }
              }
            }
          }
        }
      }
    }
  }
LAB_7fff5fc7199e:
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
LAB_7fff5fc71888:
  if ((int)*(uint *)(lVar11 + 0x18) <= (int)uVar21) goto LAB_7fff5fc718ba;
  if (*(uint *)(lVar11 + 0x18) <= uVar21) {
LAB_7fff5fc719cc:
    FUN_7fff5f47d650();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  lVar15 = *(longlong *)(lVar11 + 0x20 + (longlong)(int)uVar21 * 8);
  if (lVar15 == 0) goto LAB_7fff5fc7199e;
  if (*(int *)(lVar15 + 0x28) != 0) {
    uVar16 = 1;
  }
  uVar21 = uVar21 + 1;
  goto LAB_7fff5fc71888;
LAB_7fff5fc718ba:
  if (*(longlong *)(self + 0xe0) != 0) {
    FUN_7fff618a4510(*(longlong *)(self + 0xe0),uVar16,0);
    lVar11 = *(longlong *)(self + 0xb8);
    if (*(longlong *)(self + 0x120) != 0) {
      uVar12 = FUN_7fff5fc69070(*(longlong *)(self + 0x120),0);
      uVar10 = FUN_7fff5fc6ed00(self,0,0);
      if (lVar11 != 0) {
        FUN_7fff5fc85c90(lVar11,uVar12,uVar10,0);
        lVar11 = FUN_7fff60c4bc00(_DAT_7fff6245cb58);
        if (lVar11 != 0) {
          puStack_40 = &stack0xffffffffffffffe8;
          uStack_48 = uStack_48 & 0xffffff00;
          uStack_70 = 0x7fff5f54153b;
          FUN_7fff5f5412c0(lVar11,4,0,_DAT_7fff61b52cfc);
          return;
        }
      }
    }
  }
  goto LAB_7fff5fc7199e;
}

