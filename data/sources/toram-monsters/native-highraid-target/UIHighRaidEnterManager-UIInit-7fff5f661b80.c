
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UIHighRaidEnterManager_UIInit(undefined *self,undefined *methodInfo)

{
  undefined2 uVar1;
  float fVar2;
  code *pcVar3;
  undefined4 uVar4;
  float fVar5;
  ulonglong uVar6;
  char cVar7;
  byte bVar8;
  int iVar9;
  undefined4 uVar10;
  longlong lVar11;
  longlong *plVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  undefined *puVar15;
  longlong *plVar16;
  longlong lVar17;
  longlong lVar18;
  uint uVar19;
  longlong *plVar20;
  float fVar21;
  float fVar22;
  float fStack_b8;
  float fStack_b4;
  float fStack_b0;
  undefined8 uStack_a8;
  float fStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  ulonglong uStack_88;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  ulonglong uStack_68;
  
  if (DAT_7fff625e1bc4 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62424d80);
    FUN_7fff5f47d450(&DAT_7fff62424e48);
    FUN_7fff5f47d450(&DAT_7fff62424fd8);
    FUN_7fff5f47d450(&DAT_7fff62418738);
    FUN_7fff5f47d450(&DAT_7fff62428010);
    FUN_7fff5f47d450(&DAT_7fff623ff258);
    FUN_7fff5f47d450(&DAT_7fff623ff328);
    FUN_7fff5f47d450(0x7fff623ff3f8);
    FUN_7fff5f47d450(&DAT_7fff6243c7c0);
    FUN_7fff5f47d450(&DAT_7fff6243c880);
    FUN_7fff5f47d450(&DAT_7fff62474da8);
    FUN_7fff5f47d450(&DAT_7fff623f5f18);
    FUN_7fff5f47d450(&DAT_7fff62414030);
    FUN_7fff5f47d450(&DAT_7fff6245b880);
    FUN_7fff5f47d450(&DAT_7fff6242e438);
    FUN_7fff5f47d450(&DAT_7fff62434510);
    FUN_7fff5f47d450(&DAT_7fff6240e4b0);
    FUN_7fff5f47d450(&DAT_7fff6245b918);
    FUN_7fff5f47d450(&DAT_7fff62459498);
    FUN_7fff5f47d450(&DAT_7fff6245a5f8);
    FUN_7fff5f47d450(&DAT_7fff6245a460);
    FUN_7fff5f47d450(&DAT_7fff6245b120);
    FUN_7fff5f47d450(&DAT_7fff624597a8);
    FUN_7fff5f47d450(&DAT_7fff62468308);
    FUN_7fff5f47d450(&DAT_7fff62457c28);
    FUN_7fff5f47d450(&DAT_7fff62457ce8);
    FUN_7fff5f47d450(&DAT_7fff62457db0);
    FUN_7fff5f47d450(&DAT_7fff6245b620);
    FUN_7fff5f47d450(&DAT_7fff623f4f90);
    FUN_7fff5f47d450(&DAT_7fff623f5060);
    FUN_7fff5f47d450(&DAT_7fff62463f08);
    FUN_7fff5f47d450(&DAT_7fff62425680);
    FUN_7fff5f47d450(&DAT_7fff62436638);
    DAT_7fff625e1bc4 = '\x01';
  }
  if (*(longlong *)(self + 0x20) == 0) {
    lVar11 = FUN_7fff60c4bc00(_DAT_7fff6245a460);
    fVar21 = fStack_b8;
    fVar22 = fStack_b4;
    fVar2 = fStack_b0;
    if (lVar11 == 0) goto LAB_7fff5f662d73;
    plVar12 = (longlong *)FUN_7fff5f55ae30(lVar11,0,0);
    if (plVar12 == (longlong *)0x0) {
      *(undefined8 *)(self + 0x20) = 0;
      thunk_FUN_7fff5f491fd0();
    }
    else {
      if ((*(byte *)(*plVar12 + 0x130) < *(byte *)(_DAT_7fff62468308 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar12 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7fff62468308 + 0x130) * 8
           ) != _DAT_7fff62468308)) {
        FUN_7fff5f47c810(plVar12);
LAB_7fff5f662d46:
        FUN_7fff5f47d660();
LAB_7fff5f662d4c:
        FUN_7fff5f47d660();
LAB_7fff5f662d51:
        FUN_7fff5f47d660();
        FUN_7fff5f40a410();
LAB_7fff5f662d5d:
        FUN_7fff5f47d660();
LAB_7fff5f662d62:
        FUN_7fff5f47d660();
LAB_7fff5f662d67:
        FUN_7fff5f47d660();
        FUN_7fff5f40a410();
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
      *(longlong **)(self + 0x20) = plVar12;
      if ((*(byte *)(*plVar12 + 0x130) < *(byte *)(_DAT_7fff62468308 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar12 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7fff62468308 + 0x130) * 8
           ) != _DAT_7fff62468308)) {
        FUN_7fff5f47c810(plVar12);
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
      thunk_FUN_7fff5f491fd0();
    }
  }
  plVar12 = (longlong *)0x0;
  lVar11 = FUN_7fff60c4bc00(_DAT_7fff6245b918);
  fVar21 = fStack_b8;
  fVar22 = fStack_b4;
  fVar2 = fStack_b0;
  if (lVar11 == 0) goto LAB_7fff5f662d73;
  cVar7 = FUN_7fff600aeb00(lVar11,0);
  if (cVar7 == '\0') {
    uVar14 = *(undefined8 *)(self + 0x80);
LAB_7fff5f661e81:
    uVar13 = func_0x7fff5f44ff00(_DAT_7fff623f4f90);
    FUN_7fff5f65dd40(uVar13,uVar14,0);
  }
  else {
    lVar11 = FUN_7fff60c4bc00(_DAT_7fff6245b918);
    fVar21 = fStack_b8;
    fVar22 = fStack_b4;
    fVar2 = fStack_b0;
    if (lVar11 == 0) goto LAB_7fff5f662d73;
    cVar7 = FUN_7fff600ae6e0(lVar11,0);
    uVar14 = *(undefined8 *)(self + 0x80);
    if (cVar7 != '\0') goto LAB_7fff5f661e81;
    uVar13 = func_0x7fff5f44ff00(_DAT_7fff623f5060);
    FUN_7fff5f6641e0(uVar13,uVar14,0);
  }
  *(undefined8 *)(self + 0x148) = uVar13;
  thunk_FUN_7fff5f491fd0();
  lVar11 = *(longlong *)(self + 0x30);
  if (DAT_7fff625e1428 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62403718);
    DAT_7fff625e1428 = '\x01';
  }
  fVar5 = _DAT_7fff61b52da4;
  uVar4 = _DAT_7fff61b52b40;
  uVar14 = *(undefined8 *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0x30);
  fVar2 = *(float *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0x38);
  fStack_b0 = fVar2 * _DAT_7fff61b52da4;
  fVar21 = (float)uVar14;
  fVar22 = (float)((ulonglong)uVar14 >> 0x20);
  fStack_b4 = fVar22 * _DAT_7fff61b52da4;
  fStack_b8 = fVar21 * _DAT_7fff61b52da4;
  uStack_a8 = CONCAT44(fStack_b4,fStack_b8);
  fStack_a0 = fStack_b0;
  if (lVar11 != 0) {
    FUN_7fff5f51ed20(lVar11,&fStack_b8,_DAT_7fff61b52b40);
    if (self[0x198] != '\0') {
      return;
    }
    lVar11 = FUN_7fff60c4bc00(_DAT_7fff624597a8);
    fVar21 = fStack_b8;
    fVar22 = fStack_b4;
    fVar2 = fStack_b0;
    if ((lVar11 != 0) && (*(longlong *)(lVar11 + 0x78) != 0)) {
      lVar11 = FUN_7fff60034700(*(longlong *)(lVar11 + 0x78),self[0x199],0);
      if (lVar11 == 0) {
        return;
      }
      lVar17 = *(longlong *)(self + 0x50);
      fVar21 = fStack_b8;
      fVar22 = fStack_b4;
      fVar2 = fStack_b0;
      if ((*(longlong *)(self + 0x188) != 0) &&
         (uVar14 = FUN_7fff5f555b60(*(longlong *)(self + 0x188),*(undefined4 *)(lVar11 + 0x24),0),
         fVar21 = fStack_b8, fVar22 = fStack_b4, fVar2 = fStack_b0, lVar17 != 0)) {
        FUN_7fff5ff0eed0(lVar17,uVar14,0);
        uVar1 = *(undefined2 *)(lVar11 + 0x28);
        *(undefined2 *)(self + 0x178) = uVar1;
        *(int *)(self + 400) = (int)*(short *)(lVar11 + 0x2a);
        *(undefined2 *)(self + 0x174) = uVar1;
        puVar15 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff62459498);
        fVar21 = fStack_b8;
        fVar22 = fStack_b4;
        fVar2 = fStack_b0;
        if (puVar15 != (undefined *)0x0) {
          FunctionLimitManager_GetValue(puVar15,(undefined *)0xf,self + 0x194,(undefined *)0x0);
          iVar9 = *(int *)(self + 400);
          if ((*(int *)(self + 0x194) <= iVar9) || (*(short *)(self + 0x178) < iVar9)) {
            *(short *)(self + 0x174) = (short)iVar9;
          }
          UIHighRaidEnterManager_UpdateDifficultyLabel(self,(undefined *)0x0);
          uVar14 = _DAT_7fff62425680;
          fVar21 = fStack_b8;
          fVar22 = fStack_b4;
          fVar2 = fStack_b0;
          if (*(longlong *)(self + 0x70) != 0) {
            FUN_7fff5f502150(*(longlong *)(self + 0x70),1,0);
            lVar11 = *(longlong *)(self + 0x78);
            fVar21 = fStack_b8;
            fVar22 = fStack_b4;
            fVar2 = fStack_b0;
            if (*(longlong *)(self + 0x20) != 0) {
              uVar13 = FUN_7fff5f568150(*(longlong *)(self + 0x20),_DAT_7fff62436638,0);
              uVar14 = FUN_7fff60e71970(uVar14,uVar13,0);
              fVar21 = fStack_b8;
              fVar22 = fStack_b4;
              fVar2 = fStack_b0;
              if (lVar11 != 0) {
                FUN_7fff5ff0eed0(lVar11,uVar14,0);
                if (DAT_7fff625e1bc9 == '\0') {
                  FUN_7fff5f47d450(&DAT_7fff6245b918);
                  DAT_7fff625e1bc9 = '\x01';
                }
                lVar11 = FUN_7fff60c4bc00(_DAT_7fff6245b918);
                fVar21 = fStack_b8;
                fVar22 = fStack_b4;
                fVar2 = fStack_b0;
                if (lVar11 != 0) {
                  cVar7 = FUN_7fff600ae6e0(lVar11,0);
                  if (cVar7 != '\0') {
                    lVar11 = FUN_7fff60c4bc00(_DAT_7fff6245b918);
                    fVar21 = fStack_b8;
                    fVar22 = fStack_b4;
                    fVar2 = fStack_b0;
                    if (lVar11 == 0) goto LAB_7fff5f662d73;
                    iVar9 = FUN_7fff600aec00(lVar11,0);
                    lVar11 = FUN_7fff60c4bc00(_DAT_7fff6245b918);
                    fVar21 = fStack_b8;
                    fVar22 = fStack_b4;
                    fVar2 = fStack_b0;
                    if (lVar11 == 0) goto LAB_7fff5f662d73;
                    if (iVar9 <= *(int *)(lVar11 + 0x70) + -1) {
                      lVar11 = FUN_7fff60c4bc00(_DAT_7fff6245b918);
                      fVar21 = fStack_b8;
                      fVar22 = fStack_b4;
                      fVar2 = fStack_b0;
                      if (lVar11 == 0) goto LAB_7fff5f662d73;
                      cVar7 = FUN_7fff600ae5a0(lVar11,0);
                      if (cVar7 == '\0') {
                        fVar21 = fStack_b8;
                        fVar22 = fStack_b4;
                        fVar2 = fStack_b0;
                        if ((*(longlong *)(self + 0x140) == 0) ||
                           (lVar11 = FUN_7fff5ff8add0(*(longlong *)(self + 0x140),0),
                           fVar21 = fStack_b8, fVar22 = fStack_b4, fVar2 = fStack_b0, lVar11 == 0))
                        goto LAB_7fff5f662d73;
                        if (4 < *(int *)(lVar11 + 0x8c)) {
                          if (DAT_7fff625e1bca == '\0') {
                            FUN_7fff5f47d450(&DAT_7fff6245b6e8);
                            DAT_7fff625e1bca = '\x01';
                          }
                          lVar11 = func_0x7fff5f44ff00(_DAT_7fff6245b6e8);
                          func_0x7fff5f4d3920(lVar11,0);
                          *(undefined4 *)(lVar11 + 0x10) = 0;
                          *(undefined **)(lVar11 + 0x20) = self;
                          thunk_FUN_7fff5f491fd0();
                          FUN_7fff618a87c0(self,lVar11,0);
                        }
                      }
                    }
                  }
                  uVar14 = FUN_7fff618af100(_DAT_7fff62463f08,0);
                  if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
                    func_0x7fff5f47d6f0();
                  }
                  plVar16 = (longlong *)FUN_7fff618aa420(uVar14,0);
                  fVar21 = fStack_b8;
                  fVar22 = fStack_b4;
                  fVar2 = fStack_b0;
                  if (plVar16 != (longlong *)0x0) {
                    plVar20 = plVar12;
                    if (*plVar16 == _DAT_7fff62414030) {
                      plVar20 = plVar16;
                    }
                    if (plVar20 != (longlong *)0x0) {
                      lVar11 = FUN_7fff618a4a10(plVar20,0);
                      uVar14 = FUN_7fff618a1b90(self,0);
                      fVar21 = fStack_b8;
                      fVar22 = fStack_b4;
                      fVar2 = fStack_b0;
                      if (lVar11 != 0) {
                        FUN_7fff618c8fd0(lVar11,uVar14,0);
                        lVar11 = FUN_7fff618a4a10(plVar20,0);
                        if (DAT_7fff625e12ce == '\0') {
                          FUN_7fff5f47d450(&DAT_7fff62403718);
                          DAT_7fff625e12ce = '\x01';
                        }
                        fVar21 = fStack_b8;
                        fVar22 = fStack_b4;
                        fVar2 = fStack_b0;
                        if (lVar11 != 0) {
                          uVar14 = *(undefined8 *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0xc);
                          fStack_b8 = (float)uVar14;
                          fStack_b4 = (float)((ulonglong)uVar14 >> 0x20);
                          fStack_b0 = *(float *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0x14);
                          FUN_7fff618c8f80(lVar11,&fStack_b8,0);
                          uVar14 = FUN_7fff606a6750(plVar20,_DAT_7fff623f5f18);
                          *(undefined8 *)(self + 0x1d0) = uVar14;
                          thunk_FUN_7fff5f491fd0();
                          uVar14 = FUN_7fff606a6750(plVar20,_DAT_7fff62474da8);
                          *(undefined8 *)(self + 0x1d8) = uVar14;
                          thunk_FUN_7fff5f491fd0();
                          lVar11 = *(longlong *)(self + 0x1d8);
                          if (DAT_7fff625e1393 == '\0') {
                            FUN_7fff5f47d450(&DAT_7fff62403718);
                            DAT_7fff625e1393 = '\x01';
                          }
                          uVar14 = *(undefined8 *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0x3c);
                          fStack_b0 = *(float *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0x44) *
                                      fVar5;
                          fStack_b4 = (float)((ulonglong)uVar14 >> 0x20) * fVar5;
                          fStack_b8 = (float)uVar14 * fVar5;
                          if (DAT_7fff625e1393 == '\0') {
                            FUN_7fff5f47d450(&DAT_7fff62403718);
                            DAT_7fff625e1393 = '\x01';
                          }
                          uVar14 = *(undefined8 *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0x3c);
                          fStack_a0 = *(float *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0x44) *
                                      fVar5;
                          uStack_a8 = CONCAT44((float)((ulonglong)uVar14 >> 0x20) * fVar5,
                                               (float)uVar14 * fVar5);
                          fVar21 = fStack_b8;
                          fVar22 = fStack_b4;
                          fVar2 = fStack_b0;
                          if (lVar11 != 0) {
                            uStack_98 = uStack_a8;
                            uStack_90 = (undefined4 *)CONCAT44(uStack_90._4_4_,fStack_a0);
                            uStack_a8 = CONCAT44(fStack_b4,fStack_b8);
                            fStack_a0 = fStack_b0;
                            FUN_7fff5f51ec80(lVar11,&uStack_a8,&uStack_98,uVar4,0);
                            fVar21 = fStack_b8;
                            fVar22 = fStack_b4;
                            fVar2 = fStack_b0;
                            if (*(longlong *)(self + 0x100) != 0) {
                              *(undefined4 *)(*(longlong *)(self + 0x100) + 0x98) = 0x20;
                              if ((*(longlong *)(self + 0x100) != 0) &&
                                 (lVar11 = FUN_7fff618a1ae0(*(longlong *)(self + 0x100),0),
                                 fVar21 = fStack_b8, fVar22 = fStack_b4, fVar2 = fStack_b0,
                                 lVar11 != 0)) {
                                lVar11 = FUN_7fff618a4a10(lVar11,0);
                                fVar21 = fStack_b8;
                                fVar22 = fStack_b4;
                                fVar2 = fStack_b0;
                                if ((*(longlong *)(self + 0x1d8) != 0) &&
                                   (uVar14 = FUN_7fff618a1b90(*(longlong *)(self + 0x1d8),0),
                                   fVar21 = fStack_b8, fVar22 = fStack_b4, fVar2 = fStack_b0,
                                   lVar11 != 0)) {
                                  FUN_7fff618c8fd0(lVar11,uVar14,0);
                                  fVar21 = fStack_b8;
                                  fVar22 = fStack_b4;
                                  fVar2 = fStack_b0;
                                  if ((*(longlong *)(self + 0x100) != 0) &&
                                     (lVar11 = FUN_7fff618a1ae0(*(longlong *)(self + 0x100),0),
                                     fVar21 = fStack_b8, fVar22 = fStack_b4, fVar2 = fStack_b0,
                                     lVar11 != 0)) {
                                    lVar11 = FUN_7fff618a4a10(lVar11,0);
                                    if (DAT_7fff625e12ce == '\0') {
                                      FUN_7fff5f47d450(&DAT_7fff62403718);
                                      DAT_7fff625e12ce = '\x01';
                                    }
                                    fVar21 = fStack_b8;
                                    fVar22 = fStack_b4;
                                    fVar2 = fStack_b0;
                                    if (lVar11 != 0) {
                                      uStack_98 = *(ulonglong *)
                                                   (*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0xc);
                                      uStack_90 = (undefined4 *)
                                                  CONCAT44(uStack_90._4_4_,
                                                           *(undefined4 *)
                                                            (*(longlong *)(_DAT_7fff62403718 + 0xb8)
                                                            + 0x14));
                                      FUN_7fff618c8f80(lVar11,&uStack_98,0);
                                      fVar21 = fStack_b8;
                                      fVar22 = fStack_b4;
                                      fVar2 = fStack_b0;
                                      if ((*(longlong *)(self + 0x100) != 0) &&
                                         (lVar11 = FUN_7fff618a1ae0(*(longlong *)(self + 0x100),0),
                                         fVar21 = fStack_b8, fVar22 = fStack_b4, fVar2 = fStack_b0,
                                         lVar11 != 0)) {
                                        lVar11 = FUN_7fff618a4a10(lVar11,0);
                                        fStack_b8 = _DAT_7fff61b52e34;
                                        fStack_b4 = _DAT_7fff61b52e24;
                                        fStack_b0 = 0.0;
                                        fVar21 = fStack_b8;
                                        fVar22 = fStack_b4;
                                        fVar2 = fStack_b0;
                                        if (lVar11 != 0) {
                                          uStack_98 = CONCAT44(_DAT_7fff61b52e24,_DAT_7fff61b52e34);
                                          uStack_90 = (undefined4 *)
                                                      ((ulonglong)uStack_90 & 0xffffffff00000000);
                                          FUN_7fff618c8e40(lVar11,&uStack_98,0);
                                          fVar21 = fStack_b8;
                                          fVar22 = fStack_b4;
                                          fVar2 = fStack_b0;
                                          if (*(longlong *)(self + 0xf8) != 0) {
                                            lVar11 = FUN_7fff618a1b90(*(longlong *)(self + 0xf8),0);
                                            fVar21 = fStack_b8;
                                            fVar22 = fStack_b4;
                                            fVar2 = fStack_b0;
                                            if ((*(longlong *)(self + 0x1d8) != 0) &&
                                               (uVar14 = FUN_7fff618a1b90(*(longlong *)
                                                                           (self + 0x1d8),0),
                                               fVar21 = fStack_b8, fVar22 = fStack_b4,
                                               fVar2 = fStack_b0, lVar11 != 0)) {
                                              FUN_7fff618c8fd0(lVar11,uVar14,0);
                                              fVar21 = fStack_b8;
                                              fVar22 = fStack_b4;
                                              fVar2 = fStack_b0;
                                              if (*(longlong *)(self + 0xf8) != 0) {
                                                lVar11 = FUN_7fff618a1b90(*(longlong *)(self + 0xf8)
                                                                          ,0);
                                                if (DAT_7fff625e12ce == '\0') {
                                                  FUN_7fff5f47d450(&DAT_7fff62403718);
                                                  DAT_7fff625e12ce = '\x01';
                                                }
                                                fVar21 = fStack_b8;
                                                fVar22 = fStack_b4;
                                                fVar2 = fStack_b0;
                                                if (lVar11 != 0) {
                                                  uStack_98 = *(ulonglong *)
                                                               (*(longlong *)
                                                                 (_DAT_7fff62403718 + 0xb8) + 0xc);
                                                  uStack_90 = (undefined4 *)
                                                              CONCAT44(uStack_90._4_4_,
                                                                       *(undefined4 *)
                                                                        (*(longlong *)
                                                                          (_DAT_7fff62403718 + 0xb8)
                                                                        + 0x14));
                                                  FUN_7fff618c8f80(lVar11,&uStack_98,0);
                                                  fVar21 = fStack_b8;
                                                  fVar22 = fStack_b4;
                                                  fVar2 = fStack_b0;
                                                  if (*(longlong *)(self + 0xf8) != 0) {
                                                    lVar11 = FUN_7fff618a1b90(*(longlong *)
                                                                               (self + 0xf8),0);
                                                    fStack_b8 = _DAT_7fff61b52e28;
                                                    fStack_b4 = 0.0;
                                                    fStack_b0 = 0.0;
                                                    fVar21 = fStack_b8;
                                                    fVar22 = fStack_b4;
                                                    fVar2 = fStack_b0;
                                                    if (lVar11 != 0) {
                                                      uStack_98 = (ulonglong)(uint)_DAT_7fff61b52e28
                                                      ;
                                                      uStack_90 = (undefined4 *)
                                                                  ((ulonglong)uStack_90 &
                                                                  0xffffffff00000000);
                                                      FUN_7fff618c8e40(lVar11,&uStack_98,0);
                                                      fVar21 = fStack_b8;
                                                      fVar22 = fStack_b4;
                                                      fVar2 = fStack_b0;
                                                      if (*(longlong *)(self + 0x140) != 0) {
                                                        lVar11 = FUN_7fff5ff8a8a0(*(longlong *)
                                                                                   (self + 0x140),0)
                                                        ;
                                                        lVar17 = func_0x7fff5f47c850(
                                                  _DAT_7fff6242e438,1);
                                                  fVar21 = fStack_b8;
                                                  fVar22 = fStack_b4;
                                                  fVar2 = fStack_b0;
                                                  if (lVar17 != 0) {
                                                    if (*(int *)(lVar17 + 0x18) == 0) {
LAB_7fff5f662d2e:
                                                      FUN_7fff5f47d650();
                                                      pcVar3 = (code *)swi(3);
                                                      (*pcVar3)();
                                                      return;
                                                    }
                                                    *(undefined4 *)(lVar17 + 0x20) = 4;
                                                    if (lVar11 != 0) {
                                                      lVar11 = FUN_7fff6007bd60(lVar11,lVar17,0);
                                                      fVar21 = fStack_b8;
                                                      fVar22 = fStack_b4;
                                                      fVar2 = fStack_b0;
                                                      if ((*(longlong *)(self + 0x1a0) != 0) &&
                                                         (FUN_7fff607d86f0(*(longlong *)
                                                                            (self + 0x1a0),
                                                                           _DAT_7fff62424e48),
                                                         fVar21 = fStack_b8, fVar22 = fStack_b4,
                                                         fVar2 = fStack_b0, lVar11 != 0)) {
                                                        FUN_7fff60a8daa0(&uStack_98,lVar11,
                                                                         _DAT_7fff62434510);
                                                        uStack_78 = (undefined4)uStack_98;
                                                        uStack_74 = uStack_98._4_4_;
                                                        uStack_70 = (undefined4)uStack_90;
                                                        uStack_6c = uStack_90._4_4_;
                                                        uStack_68 = uStack_88;
                                                        uStack_98 = 0;
                                                        uStack_90 = &uStack_78;
                                                        while (cVar7 = FUN_7fff6092ec20(&uStack_78,
                                                                                                                                                                                
                                                  _DAT_7fff623ff328), uVar6 = uStack_68,
                                                  cVar7 != '\0') {
                                                    uVar4 = (undefined4)uStack_68;
                                                    if (*(longlong *)(self + 0x140) == 0)
                                                    goto LAB_7fff5f662d51;
                                                    lVar11 = FUN_7fff5ff8a8a0(*(longlong *)
                                                                               (self + 0x140),0);
                                                    if (lVar11 == 0) goto LAB_7fff5f662d4c;
                                                    uVar10 = FUN_7fff6007b680(lVar11,uVar6 & 
                                                  0xffffffff,0);
                                                  lVar11 = *(longlong *)(self + 0x1a0);
                                                  lVar17 = func_0x7fff5f44ff00(_DAT_7fff6245b880);
                                                  func_0x7fff5f4d3920(lVar17,0);
                                                  *(undefined4 *)(lVar17 + 0x10) = uVar4;
                                                  *(undefined4 *)(lVar17 + 0x14) = uVar10;
                                                  *(undefined1 *)(lVar17 + 0x19) = 0;
                                                  *(undefined8 *)(lVar17 + 0x20) = 0;
                                                  thunk_FUN_7fff5f491fd0();
                                                  *(undefined1 *)(lVar17 + 0x18) = 0;
                                                  if (lVar11 == 0) goto LAB_7fff5f662d46;
                                                  FUN_7fff60857660(lVar11,uVar6 & 0xffffffff);
                                                  }
                                                  func_0x7fff5f4d3920(&uStack_78,_DAT_7fff623ff258);
                                                  uVar14 = *(undefined8 *)(self + 0x1a0);
                                                  if (*(int *)(_DAT_7fff6245b620 + 0xe0) == 0) {
                                                    func_0x7fff5f47d6f0();
                                                  }
                                                  lVar11 = *(longlong *)
                                                            (*(longlong *)(_DAT_7fff6245b620 + 0xb8)
                                                            + 8);
                                                  if (lVar11 == 0) {
                                                    if (*(int *)(_DAT_7fff6245b620 + 0xe0) == 0) {
                                                      func_0x7fff5f47d6f0();
                                                    }
                                                    uVar13 = **(undefined8 **)
                                                               (_DAT_7fff6245b620 + 0xb8);
                                                    lVar11 = func_0x7fff5f44ff00(_DAT_7fff6243c7c0);
                                                    FUN_7fff60a1d4e0(lVar11,uVar13,_DAT_7fff62457c28
                                                                     ,0);
                                                    *(longlong *)
                                                     (*(longlong *)(_DAT_7fff6245b620 + 0xb8) + 8) =
                                                         lVar11;
                                                    thunk_FUN_7fff5f491fd0();
                                                  }
                                                  uVar14 = FUN_7fff60695b80(uVar14,lVar11,
                                                                            _DAT_7fff62418738);
                                                  if (*(int *)(_DAT_7fff6245b620 + 0xe0) == 0) {
                                                    func_0x7fff5f47d6f0(_DAT_7fff6245b620);
                                                  }
                                                  lVar11 = *(longlong *)
                                                            (*(longlong *)(_DAT_7fff6245b620 + 0xb8)
                                                            + 0x10);
                                                  if (lVar11 == 0) {
                                                    if (*(int *)(_DAT_7fff6245b620 + 0xe0) == 0) {
                                                      func_0x7fff5f47d6f0(_DAT_7fff6245b620);
                                                    }
                                                    uVar13 = **(undefined8 **)
                                                               (_DAT_7fff6245b620 + 0xb8);
                                                    lVar11 = func_0x7fff5f44ff00(_DAT_7fff6243c7c0);
                                                    FUN_7fff60a1d4e0(lVar11,uVar13,_DAT_7fff62457ce8
                                                                     ,0);
                                                    *(longlong *)
                                                     (*(longlong *)(_DAT_7fff6245b620 + 0xb8) + 0x10
                                                     ) = lVar11;
                                                    thunk_FUN_7fff5f491fd0();
                                                  }
                                                  if (*(int *)(_DAT_7fff6245b620 + 0xe0) == 0) {
                                                    func_0x7fff5f47d6f0(_DAT_7fff6245b620);
                                                  }
                                                  lVar17 = *(longlong *)
                                                            (*(longlong *)(_DAT_7fff6245b620 + 0xb8)
                                                            + 0x18);
                                                  if (lVar17 == 0) {
                                                    if (*(int *)(_DAT_7fff6245b620 + 0xe0) == 0) {
                                                      func_0x7fff5f47d6f0(_DAT_7fff6245b620);
                                                    }
                                                    uVar13 = **(undefined8 **)
                                                               (_DAT_7fff6245b620 + 0xb8);
                                                    lVar17 = func_0x7fff5f44ff00(_DAT_7fff6243c880);
                                                    FUN_7fff60a1d720(lVar17,uVar13,_DAT_7fff62457db0
                                                                     ,0);
                                                    *(longlong *)
                                                     (*(longlong *)(_DAT_7fff6245b620 + 0xb8) + 0x18
                                                     ) = lVar17;
                                                    thunk_FUN_7fff5f491fd0();
                                                  }
                                                  uVar14 = FUN_7fff6069bd10(uVar14,lVar11,lVar17,
                                                                            _DAT_7fff62428010);
                                                  fVar21 = fStack_b8;
                                                  fVar22 = fStack_b4;
                                                  fVar2 = fStack_b0;
                                                  if (self != (undefined *)0x0) {
                                                    *(undefined8 *)(self + 0x1a0) = uVar14;
                                                    thunk_FUN_7fff5f491fd0();
                                                    lVar11 = FUN_7fff60c4bc00(_DAT_7fff6245b120);
                                                    puVar15 = (undefined *)
                                                              FUN_7fff60c4bc00(_DAT_7fff62459498);
                                                    fVar21 = fStack_b8;
                                                    fVar22 = fStack_b4;
                                                    fVar2 = fStack_b0;
                                                    if (puVar15 != (undefined *)0x0) {
                                                      bVar8 = FunctionLimitManager_IsLimited
                                                                        (puVar15,(undefined *)0x3,
                                                                         (undefined *)0x0);
                                                      if (bVar8 == 0) {
                                                        lVar17 = FUN_7fff60c4bc00(_DAT_7fff6245a5f8)
                                                        ;
                                                        lVar18 = func_0x7fff5f47c850(
                                                  _DAT_7fff6242e438,1);
                                                  fVar21 = fStack_b8;
                                                  fVar22 = fStack_b4;
                                                  fVar2 = fStack_b0;
                                                  if (lVar18 == 0) goto LAB_7fff5f662d73;
                                                  if (*(int *)(lVar18 + 0x18) == 0)
                                                  goto LAB_7fff5f662d2e;
                                                  *(undefined4 *)(lVar18 + 0x20) = 0x67;
                                                  if ((lVar17 == 0) ||
                                                     (lVar17 = FUN_7fff60084480(lVar17,lVar18,0),
                                                     fVar21 = fStack_b8, fVar22 = fStack_b4,
                                                     fVar2 = fStack_b0, lVar17 == 0))
                                                  goto LAB_7fff5f662d73;
                                                  FUN_7fff60a8daa0(&uStack_98,lVar17,
                                                                   _DAT_7fff62434510);
                                                  uStack_78 = (undefined4)uStack_98;
                                                  uStack_74 = uStack_98._4_4_;
                                                  uStack_70 = (undefined4)uStack_90;
                                                  uStack_6c = uStack_90._4_4_;
                                                  uStack_68 = uStack_88;
                                                  uStack_98 = 0;
                                                  uStack_90 = &uStack_78;
                                                  while (cVar7 = FUN_7fff6092ec20(&uStack_78,
                                                                                  _DAT_7fff623ff328)
                                                        , uVar6 = uStack_68, cVar7 != '\0') {
                                                    if (lVar11 == 0) goto LAB_7fff5f662d67;
                                                    if (*(longlong *)(lVar11 + 0x70) == 0)
                                                    goto LAB_7fff5f662d62;
                                                    iVar9 = FUN_7fff600a0750(*(longlong *)
                                                                              (lVar11 + 0x70),
                                                                             uStack_68 & 0xffffffff)
                                                    ;
                                                    if (0 < iVar9) {
                                                      lVar17 = *(longlong *)(self + 0x1a0);
                                                      uVar14 = func_0x7fff5f44ff00(_DAT_7fff6245b880
                                                                                  );
                                                      FUN_7fff5f5f73a0(uVar14,uVar6 & 0xffffffff,
                                                                       iVar9,1,0);
                                                      if (lVar17 == 0) goto LAB_7fff5f662d5d;
                                                      FUN_7fff60857660(lVar17,uVar6 & 0xffffffff,
                                                                       uVar14,_DAT_7fff62424d80);
                                                    }
                                                  }
                                                  func_0x7fff5f4d3920(&uStack_78,_DAT_7fff623ff258);
                                                  }
                                                  fVar21 = fStack_b8;
                                                  fVar22 = fStack_b4;
                                                  fVar2 = fStack_b0;
                                                  if (*(longlong *)(self + 0xf8) != 0) {
                                                    lVar11 = FUN_7fff618a1ae0(*(longlong *)
                                                                               (self + 0xf8),0);
                                                    fVar21 = fStack_b8;
                                                    fVar22 = fStack_b4;
                                                    fVar2 = fStack_b0;
                                                    if ((*(longlong *)(self + 0x1a0) != 0) &&
                                                       (iVar9 = func_0x7fff607e24e0(*(longlong *)
                                                                                     (self + 0x1a0),
                                                                                                                                                                        
                                                  _DAT_7fff62424fd8), fVar21 = fStack_b8,
                                                  fVar22 = fStack_b4, fVar2 = fStack_b0, lVar11 != 0
                                                  )) {
                                                    FUN_7fff618a4510(lVar11,iVar9 < 1,0);
                                                    fVar21 = fStack_b8;
                                                    fVar22 = fStack_b4;
                                                    fVar2 = fStack_b0;
                                                    if (*(longlong *)(self + 0xf0) != 0) {
                                                      FUN_7fff618a0e80(*(longlong *)(self + 0xf0),0,
                                                                       0);
                                                      lVar11 = *(longlong *)(self + 0x110);
                                                      while (fVar21 = fStack_b8, fVar22 = fStack_b4,
                                                            fVar2 = fStack_b0, lVar11 != 0) {
                                                        uVar19 = (uint)plVar12;
                                                        if (*(int *)(lVar11 + 0x18) <= (int)uVar19)
                                                        {
                                                          self[0x150] = 1;
                                                          return;
                                                        }
                                                        lVar11 = *(longlong *)(self + 0x110);
                                                        if (lVar11 == 0) break;
                                                        if (*(uint *)(lVar11 + 0x18) <= uVar19)
                                                        goto LAB_7fff5f662d2e;
                                                        lVar11 = *(longlong *)
                                                                  (lVar11 + 0x20 +
                                                                  (longlong)(int)uVar19 * 8);
                                                        if (lVar11 == 0) break;
                                                        FUN_7fff5f502150(lVar11,1,0);
                                                        plVar12 = (longlong *)
                                                                  (ulonglong)(uVar19 + 1);
                                                        lVar11 = *(longlong *)(self + 0x110);
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
        }
      }
    }
  }
LAB_7fff5f662d73:
  fStack_b0 = fVar2;
  fStack_b4 = fVar22;
  fStack_b8 = fVar21;
  FUN_7fff5f47d660();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

