
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
  int iVar8;
  undefined4 uVar9;
  undefined *puVar10;
  longlong *plVar11;
  longlong lVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  longlong *plVar15;
  longlong lVar16;
  longlong lVar17;
  uint uVar18;
  longlong *plVar19;
  float fVar20;
  float fVar21;
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
  
  if (DAT_7ffe9cada448 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c91de00);
    FUN_7ffe9996d590(&DAT_7ffe9c91dec8);
    FUN_7ffe9996d590(&DAT_7ffe9c91e058);
    FUN_7ffe9996d590(&DAT_7ffe9c9117d8);
    FUN_7ffe9996d590(&DAT_7ffe9c921158);
    FUN_7ffe9996d590(&DAT_7ffe9c8f8228);
    FUN_7ffe9996d590(&DAT_7ffe9c8f82f8);
    FUN_7ffe9996d590(0x7ffe9c8f83c8);
    FUN_7ffe9996d590(&DAT_7ffe9c934db0);
    FUN_7ffe9996d590(&DAT_7ffe9c934e78);
    FUN_7ffe9996d590(&DAT_7ffe9c96df68);
    FUN_7ffe9996d590(&DAT_7ffe9c8eefb8);
    FUN_7ffe9996d590(&DAT_7ffe9c90c578);
    FUN_7ffe9996d590(&DAT_7ffe9c9549a0);
    FUN_7ffe9996d590(&DAT_7ffe9c9269c8);
    FUN_7ffe9996d590(&DAT_7ffe9c92d5c0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c954a30);
    FUN_7ffe9996d590(&DAT_7ffe9c952588);
    FUN_7ffe9996d590(&DAT_7ffe9c953710);
    FUN_7ffe9996d590(&DAT_7ffe9c953578);
    FUN_7ffe9996d590(&DAT_7ffe9c954238);
    FUN_7ffe9996d590(&DAT_7ffe9c9528b8);
    FUN_7ffe9996d590(&DAT_7ffe9c960dc8);
    FUN_7ffe9996d590(&DAT_7ffe9c951540);
    FUN_7ffe9996d590(&DAT_7ffe9c951600);
    FUN_7ffe9996d590(&DAT_7ffe9c9516c8);
    FUN_7ffe9996d590(&DAT_7ffe9c954738);
    FUN_7ffe9996d590(&DAT_7ffe9c8ed8e0);
    FUN_7ffe9996d590(&DAT_7ffe9c8ed9b0);
    FUN_7ffe9996d590(&DAT_7ffe9c95e1a0);
    FUN_7ffe9996d590(&DAT_7ffe9c91f830);
    FUN_7ffe9996d590(&DAT_7ffe9c92ff50);
    DAT_7ffe9cada448 = '\x01';
  }
  if (*(longlong *)(self + 0x20) == 0) {
    puVar10 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c953578);
    fVar20 = fStack_b8;
    fVar21 = fStack_b4;
    fVar2 = fStack_b0;
    if (puVar10 == (undefined *)0x0) goto LAB_7ffe99b530b3;
    plVar11 = (longlong *)LocalizeManager_Get(puVar10,(undefined *)0x0,(undefined *)0x0);
    if (plVar11 == (longlong *)0x0) {
      *(undefined8 *)(self + 0x20) = 0;
      il2cpp_write_barrier_0();
    }
    else {
      if ((*(byte *)(*plVar11 + 0x130) < *(byte *)(_DAT_7ffe9c960dc8 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar11 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c960dc8 + 0x130) * 8
           ) != _DAT_7ffe9c960dc8)) {
        FUN_7ffe9996c950(plVar11);
LAB_7ffe99b53086:
        FUN_7ffe9996d7a0();
LAB_7ffe99b5308c:
        FUN_7ffe9996d7a0();
LAB_7ffe99b53091:
        FUN_7ffe9996d7a0();
        FUN_7ffe998fa550();
LAB_7ffe99b5309d:
        FUN_7ffe9996d7a0();
LAB_7ffe99b530a2:
        FUN_7ffe9996d7a0();
LAB_7ffe99b530a7:
        FUN_7ffe9996d7a0();
        FUN_7ffe998fa550();
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
      *(longlong **)(self + 0x20) = plVar11;
      if ((*(byte *)(*plVar11 + 0x130) < *(byte *)(_DAT_7ffe9c960dc8 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar11 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c960dc8 + 0x130) * 8
           ) != _DAT_7ffe9c960dc8)) {
        FUN_7ffe9996c950(plVar11);
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
      il2cpp_write_barrier_0();
    }
  }
  plVar11 = (longlong *)0x0;
  lVar12 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
  fVar20 = fStack_b8;
  fVar21 = fStack_b4;
  fVar2 = fStack_b0;
  if (lVar12 == 0) goto LAB_7ffe99b530b3;
  cVar7 = FUN_7ffe9a5a4650(lVar12,0);
  if (cVar7 == '\0') {
    uVar14 = *(undefined8 *)(self + 0x80);
LAB_7ffe99b521c1:
    uVar13 = func_0x7ffe99940040(_DAT_7ffe9c8ed8e0);
    FUN_7ffe99b4e080(uVar13,uVar14);
  }
  else {
    lVar12 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
    fVar20 = fStack_b8;
    fVar21 = fStack_b4;
    fVar2 = fStack_b0;
    if (lVar12 == 0) goto LAB_7ffe99b530b3;
    cVar7 = FUN_7ffe9a5a4230(lVar12,0);
    uVar14 = *(undefined8 *)(self + 0x80);
    if (cVar7 != '\0') goto LAB_7ffe99b521c1;
    uVar13 = func_0x7ffe99940040(_DAT_7ffe9c8ed9b0);
    FUN_7ffe99b54520(uVar13,uVar14);
  }
  *(undefined8 *)(self + 0x148) = uVar13;
  il2cpp_write_barrier_0();
  lVar12 = *(longlong *)(self + 0x30);
  if (DAT_7ffe9cad9ca8 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
    DAT_7ffe9cad9ca8 = '\x01';
  }
  fVar5 = _DAT_7ffe9c049da4;
  uVar4 = _DAT_7ffe9c049b40;
  uVar14 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x30);
  fVar2 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x38);
  fStack_b0 = fVar2 * _DAT_7ffe9c049da4;
  fVar20 = (float)uVar14;
  fVar21 = (float)((ulonglong)uVar14 >> 0x20);
  fStack_b4 = fVar21 * _DAT_7ffe9c049da4;
  fStack_b8 = fVar20 * _DAT_7ffe9c049da4;
  uStack_a8 = CONCAT44(fStack_b4,fStack_b8);
  fStack_a0 = fStack_b0;
  if (lVar12 != 0) {
    FUN_7ffe99a0ed20(lVar12,&fStack_b8,_DAT_7ffe9c049b40);
    if (self[0x198] != '\0') {
      return;
    }
    lVar12 = FUN_7ffe9b141840(_DAT_7ffe9c9528b8);
    fVar20 = fStack_b8;
    fVar21 = fStack_b4;
    fVar2 = fStack_b0;
    if ((lVar12 != 0) && (*(longlong *)(lVar12 + 0x78) != 0)) {
      lVar12 = FUN_7ffe9a529c10(*(longlong *)(lVar12 + 0x78),self[0x199]);
      if (lVar12 == 0) {
        return;
      }
      lVar16 = *(longlong *)(self + 0x50);
      fVar20 = fStack_b8;
      fVar21 = fStack_b4;
      fVar2 = fStack_b0;
      if ((*(undefined **)(self + 0x188) != (undefined *)0x0) &&
         (puVar10 = EnemyTextManager_GetName
                              (*(undefined **)(self + 0x188),*(int *)(lVar12 + 0x24),
                               (undefined *)0x0), fVar20 = fStack_b8, fVar21 = fStack_b4,
         fVar2 = fStack_b0, lVar16 != 0)) {
        FUN_7ffe9a404310(lVar16,puVar10,0);
        uVar1 = *(undefined2 *)(lVar12 + 0x28);
        *(undefined2 *)(self + 0x178) = uVar1;
        *(int *)(self + 400) = (int)*(short *)(lVar12 + 0x2a);
        *(undefined2 *)(self + 0x174) = uVar1;
        puVar10 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c952588);
        fVar20 = fStack_b8;
        fVar21 = fStack_b4;
        fVar2 = fStack_b0;
        if (puVar10 != (undefined *)0x0) {
          FunctionLimitManager_GetValue(puVar10,(undefined *)0xf,self + 0x194,(undefined *)0x0);
          iVar8 = *(int *)(self + 400);
          if ((*(int *)(self + 0x194) <= iVar8) || (*(short *)(self + 0x178) < iVar8)) {
            *(short *)(self + 0x174) = (short)iVar8;
          }
          FUN_7ffe99b530c0(self,0);
          uVar14 = _DAT_7ffe9c91f830;
          fVar20 = fStack_b8;
          fVar21 = fStack_b4;
          fVar2 = fStack_b0;
          if (*(longlong *)(self + 0x70) != 0) {
            FUN_7ffe999f2150(*(longlong *)(self + 0x70),1,0);
            lVar12 = *(longlong *)(self + 0x78);
            fVar20 = fStack_b8;
            fVar21 = fStack_b4;
            fVar2 = fStack_b0;
            if (*(longlong *)(self + 0x20) != 0) {
              uVar13 = FUN_7ffe99a58320(*(longlong *)(self + 0x20),_DAT_7ffe9c92ff50,0);
              uVar14 = FUN_7ffe9b3675b0(uVar14,uVar13,0);
              fVar20 = fStack_b8;
              fVar21 = fStack_b4;
              fVar2 = fStack_b0;
              if (lVar12 != 0) {
                FUN_7ffe9a404310(lVar12,uVar14,0);
                if (DAT_7ffe9cada44d == '\0') {
                  FUN_7ffe9996d590(&DAT_7ffe9c954a30);
                  DAT_7ffe9cada44d = '\x01';
                }
                lVar12 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
                fVar20 = fStack_b8;
                fVar21 = fStack_b4;
                fVar2 = fStack_b0;
                if (lVar12 != 0) {
                  cVar7 = FUN_7ffe9a5a4230(lVar12,0);
                  if (cVar7 != '\0') {
                    lVar12 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
                    fVar20 = fStack_b8;
                    fVar21 = fStack_b4;
                    fVar2 = fStack_b0;
                    if (lVar12 == 0) goto LAB_7ffe99b530b3;
                    iVar8 = FUN_7ffe9a5a4750(lVar12,0);
                    lVar12 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
                    fVar20 = fStack_b8;
                    fVar21 = fStack_b4;
                    fVar2 = fStack_b0;
                    if (lVar12 == 0) goto LAB_7ffe99b530b3;
                    if (iVar8 <= *(int *)(lVar12 + 0x70) + -1) {
                      lVar12 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
                      fVar20 = fStack_b8;
                      fVar21 = fStack_b4;
                      fVar2 = fStack_b0;
                      if (lVar12 == 0) goto LAB_7ffe99b530b3;
                      cVar7 = FUN_7ffe9a5a40f0(lVar12,0);
                      if (cVar7 == '\0') {
                        fVar20 = fStack_b8;
                        fVar21 = fStack_b4;
                        fVar2 = fStack_b0;
                        if ((*(longlong *)(self + 0x140) == 0) ||
                           (lVar12 = FUN_7ffe9a480210(*(longlong *)(self + 0x140),0),
                           fVar20 = fStack_b8, fVar21 = fStack_b4, fVar2 = fStack_b0, lVar12 == 0))
                        goto LAB_7ffe99b530b3;
                        if (4 < *(int *)(lVar12 + 0x8c)) {
                          if (DAT_7ffe9cada44e == '\0') {
                            FUN_7ffe9996d590(&DAT_7ffe9c954808);
                            DAT_7ffe9cada44e = '\x01';
                          }
                          lVar12 = func_0x7ffe99940040(_DAT_7ffe9c954808);
                          func_0x7ffe999c3920(lVar12,0);
                          *(undefined4 *)(lVar12 + 0x10) = 0;
                          *(undefined **)(lVar12 + 0x20) = self;
                          il2cpp_write_barrier_0();
                          FUN_7ffe9bd9f640(self,lVar12,0);
                        }
                      }
                    }
                  }
                  uVar14 = FUN_7ffe9bda5f80(_DAT_7ffe9c95e1a0,0);
                  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                    func_0x7ffe9996d830();
                  }
                  plVar15 = (longlong *)FUN_7ffe9bda12a0(uVar14,0);
                  fVar20 = fStack_b8;
                  fVar21 = fStack_b4;
                  fVar2 = fStack_b0;
                  if (plVar15 != (longlong *)0x0) {
                    plVar19 = plVar11;
                    if (*plVar15 == _DAT_7ffe9c90c578) {
                      plVar19 = plVar15;
                    }
                    if (plVar19 != (longlong *)0x0) {
                      lVar12 = FUN_7ffe9bd9b890(plVar19,0);
                      uVar14 = FUN_7ffe9bd98a10(self,0);
                      fVar20 = fStack_b8;
                      fVar21 = fStack_b4;
                      fVar2 = fStack_b0;
                      if (lVar12 != 0) {
                        FUN_7ffe9bdbfe50(lVar12,uVar14,0);
                        lVar12 = FUN_7ffe9bd9b890(plVar19,0);
                        if (DAT_7ffe9cad9b4e == '\0') {
                          FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
                          DAT_7ffe9cad9b4e = '\x01';
                        }
                        fVar20 = fStack_b8;
                        fVar21 = fStack_b4;
                        fVar2 = fStack_b0;
                        if (lVar12 != 0) {
                          uVar14 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0xc);
                          fStack_b8 = (float)uVar14;
                          fStack_b4 = (float)((ulonglong)uVar14 >> 0x20);
                          fStack_b0 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x14);
                          FUN_7ffe9bdbfe00(lVar12,&fStack_b8,0);
                          uVar14 = FUN_7ffe9ab9c3a0(plVar19,_DAT_7ffe9c8eefb8);
                          *(undefined8 *)(self + 0x1d0) = uVar14;
                          il2cpp_write_barrier_0();
                          uVar14 = FUN_7ffe9ab9c3a0(plVar19,_DAT_7ffe9c96df68);
                          *(undefined8 *)(self + 0x1d8) = uVar14;
                          il2cpp_write_barrier_0();
                          lVar12 = *(longlong *)(self + 0x1d8);
                          if (DAT_7ffe9cad9c13 == '\0') {
                            FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
                            DAT_7ffe9cad9c13 = '\x01';
                          }
                          uVar14 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x3c);
                          fStack_b0 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x44) *
                                      fVar5;
                          fStack_b4 = (float)((ulonglong)uVar14 >> 0x20) * fVar5;
                          fStack_b8 = (float)uVar14 * fVar5;
                          if (DAT_7ffe9cad9c13 == '\0') {
                            FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
                            DAT_7ffe9cad9c13 = '\x01';
                          }
                          uVar14 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x3c);
                          fStack_a0 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x44) *
                                      fVar5;
                          uStack_a8 = CONCAT44((float)((ulonglong)uVar14 >> 0x20) * fVar5,
                                               (float)uVar14 * fVar5);
                          fVar20 = fStack_b8;
                          fVar21 = fStack_b4;
                          fVar2 = fStack_b0;
                          if (lVar12 != 0) {
                            uStack_98 = uStack_a8;
                            uStack_90 = (undefined4 *)CONCAT44(uStack_90._4_4_,fStack_a0);
                            uStack_a8 = CONCAT44(fStack_b4,fStack_b8);
                            fStack_a0 = fStack_b0;
                            FUN_7ffe99a0ec80(lVar12,&uStack_a8,&uStack_98,uVar4,0);
                            fVar20 = fStack_b8;
                            fVar21 = fStack_b4;
                            fVar2 = fStack_b0;
                            if (*(longlong *)(self + 0x100) != 0) {
                              *(undefined4 *)(*(longlong *)(self + 0x100) + 0x98) = 0x20;
                              if ((*(longlong *)(self + 0x100) != 0) &&
                                 (lVar12 = FUN_7ffe9bd98960(*(longlong *)(self + 0x100),0),
                                 fVar20 = fStack_b8, fVar21 = fStack_b4, fVar2 = fStack_b0,
                                 lVar12 != 0)) {
                                lVar12 = FUN_7ffe9bd9b890(lVar12,0);
                                fVar20 = fStack_b8;
                                fVar21 = fStack_b4;
                                fVar2 = fStack_b0;
                                if ((*(longlong *)(self + 0x1d8) != 0) &&
                                   (uVar14 = FUN_7ffe9bd98a10(*(longlong *)(self + 0x1d8),0),
                                   fVar20 = fStack_b8, fVar21 = fStack_b4, fVar2 = fStack_b0,
                                   lVar12 != 0)) {
                                  FUN_7ffe9bdbfe50(lVar12,uVar14,0);
                                  fVar20 = fStack_b8;
                                  fVar21 = fStack_b4;
                                  fVar2 = fStack_b0;
                                  if ((*(longlong *)(self + 0x100) != 0) &&
                                     (lVar12 = FUN_7ffe9bd98960(*(longlong *)(self + 0x100),0),
                                     fVar20 = fStack_b8, fVar21 = fStack_b4, fVar2 = fStack_b0,
                                     lVar12 != 0)) {
                                    lVar12 = FUN_7ffe9bd9b890(lVar12,0);
                                    if (DAT_7ffe9cad9b4e == '\0') {
                                      FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
                                      DAT_7ffe9cad9b4e = '\x01';
                                    }
                                    fVar20 = fStack_b8;
                                    fVar21 = fStack_b4;
                                    fVar2 = fStack_b0;
                                    if (lVar12 != 0) {
                                      uStack_98 = *(ulonglong *)
                                                   (*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0xc);
                                      uStack_90 = (undefined4 *)
                                                  CONCAT44(uStack_90._4_4_,
                                                           *(undefined4 *)
                                                            (*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8)
                                                            + 0x14));
                                      FUN_7ffe9bdbfe00(lVar12,&uStack_98,0);
                                      fVar20 = fStack_b8;
                                      fVar21 = fStack_b4;
                                      fVar2 = fStack_b0;
                                      if ((*(longlong *)(self + 0x100) != 0) &&
                                         (lVar12 = FUN_7ffe9bd98960(*(longlong *)(self + 0x100),0),
                                         fVar20 = fStack_b8, fVar21 = fStack_b4, fVar2 = fStack_b0,
                                         lVar12 != 0)) {
                                        lVar12 = FUN_7ffe9bd9b890(lVar12,0);
                                        fStack_b8 = _DAT_7ffe9c049e34;
                                        fStack_b4 = _DAT_7ffe9c049e24;
                                        fStack_b0 = 0.0;
                                        fVar20 = fStack_b8;
                                        fVar21 = fStack_b4;
                                        fVar2 = fStack_b0;
                                        if (lVar12 != 0) {
                                          uStack_98 = CONCAT44(_DAT_7ffe9c049e24,_DAT_7ffe9c049e34);
                                          uStack_90 = (undefined4 *)
                                                      ((ulonglong)uStack_90 & 0xffffffff00000000);
                                          FUN_7ffe9bdbfcc0(lVar12,&uStack_98,0);
                                          fVar20 = fStack_b8;
                                          fVar21 = fStack_b4;
                                          fVar2 = fStack_b0;
                                          if (*(longlong *)(self + 0xf8) != 0) {
                                            lVar12 = FUN_7ffe9bd98a10(*(longlong *)(self + 0xf8),0);
                                            fVar20 = fStack_b8;
                                            fVar21 = fStack_b4;
                                            fVar2 = fStack_b0;
                                            if ((*(longlong *)(self + 0x1d8) != 0) &&
                                               (uVar14 = FUN_7ffe9bd98a10(*(longlong *)
                                                                           (self + 0x1d8),0),
                                               fVar20 = fStack_b8, fVar21 = fStack_b4,
                                               fVar2 = fStack_b0, lVar12 != 0)) {
                                              FUN_7ffe9bdbfe50(lVar12,uVar14,0);
                                              fVar20 = fStack_b8;
                                              fVar21 = fStack_b4;
                                              fVar2 = fStack_b0;
                                              if (*(longlong *)(self + 0xf8) != 0) {
                                                lVar12 = FUN_7ffe9bd98a10(*(longlong *)(self + 0xf8)
                                                                          ,0);
                                                if (DAT_7ffe9cad9b4e == '\0') {
                                                  FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
                                                  DAT_7ffe9cad9b4e = '\x01';
                                                }
                                                fVar20 = fStack_b8;
                                                fVar21 = fStack_b4;
                                                fVar2 = fStack_b0;
                                                if (lVar12 != 0) {
                                                  uStack_98 = *(ulonglong *)
                                                               (*(longlong *)
                                                                 (_DAT_7ffe9c8fc068 + 0xb8) + 0xc);
                                                  uStack_90 = (undefined4 *)
                                                              CONCAT44(uStack_90._4_4_,
                                                                       *(undefined4 *)
                                                                        (*(longlong *)
                                                                          (_DAT_7ffe9c8fc068 + 0xb8)
                                                                        + 0x14));
                                                  FUN_7ffe9bdbfe00(lVar12,&uStack_98,0);
                                                  fVar20 = fStack_b8;
                                                  fVar21 = fStack_b4;
                                                  fVar2 = fStack_b0;
                                                  if (*(longlong *)(self + 0xf8) != 0) {
                                                    lVar12 = FUN_7ffe9bd98a10(*(longlong *)
                                                                               (self + 0xf8),0);
                                                    fStack_b8 = _DAT_7ffe9c049e28;
                                                    fStack_b4 = 0.0;
                                                    fStack_b0 = 0.0;
                                                    fVar20 = fStack_b8;
                                                    fVar21 = fStack_b4;
                                                    fVar2 = fStack_b0;
                                                    if (lVar12 != 0) {
                                                      uStack_98 = (ulonglong)(uint)_DAT_7ffe9c049e28
                                                      ;
                                                      uStack_90 = (undefined4 *)
                                                                  ((ulonglong)uStack_90 &
                                                                  0xffffffff00000000);
                                                      FUN_7ffe9bdbfcc0(lVar12,&uStack_98,0);
                                                      fVar20 = fStack_b8;
                                                      fVar21 = fStack_b4;
                                                      fVar2 = fStack_b0;
                                                      if (*(longlong *)(self + 0x140) != 0) {
                                                        lVar12 = FUN_7ffe9a47fce0(*(longlong *)
                                                                                   (self + 0x140),0)
                                                        ;
                                                        lVar16 = func_0x7ffe9996c990(
                                                  _DAT_7ffe9c9269c8,1);
                                                  fVar20 = fStack_b8;
                                                  fVar21 = fStack_b4;
                                                  fVar2 = fStack_b0;
                                                  if (lVar16 != 0) {
                                                    if (*(int *)(lVar16 + 0x18) == 0) {
LAB_7ffe99b5306e:
                                                      FUN_7ffe9996d790();
                                                      pcVar3 = (code *)swi(3);
                                                      (*pcVar3)();
                                                      return;
                                                    }
                                                    *(undefined4 *)(lVar16 + 0x20) = 4;
                                                    if (lVar12 != 0) {
                                                      lVar12 = FUN_7ffe9a5718b0(lVar12,lVar16,0);
                                                      fVar20 = fStack_b8;
                                                      fVar21 = fStack_b4;
                                                      fVar2 = fStack_b0;
                                                      if ((*(longlong *)(self + 0x1a0) != 0) &&
                                                         (FUN_7ffe9acce330(*(longlong *)
                                                                            (self + 0x1a0),
                                                                           _DAT_7ffe9c91dec8),
                                                         fVar20 = fStack_b8, fVar21 = fStack_b4,
                                                         fVar2 = fStack_b0, lVar12 != 0)) {
                                                        FUN_7ffe9af836e0(&uStack_98,lVar12,
                                                                         _DAT_7ffe9c92d5c0);
                                                        uStack_78 = (undefined4)uStack_98;
                                                        uStack_74 = uStack_98._4_4_;
                                                        uStack_70 = (undefined4)uStack_90;
                                                        uStack_6c = uStack_90._4_4_;
                                                        uStack_68 = uStack_88;
                                                        uStack_98 = 0;
                                                        uStack_90 = &uStack_78;
                                                        while (cVar7 = FUN_7ffe9ae24860(&uStack_78,
                                                                                                                                                                                
                                                  _DAT_7ffe9c8f82f8), uVar6 = uStack_68,
                                                  cVar7 != '\0') {
                                                    uVar4 = (undefined4)uStack_68;
                                                    if (*(longlong *)(self + 0x140) == 0)
                                                    goto LAB_7ffe99b53091;
                                                    lVar12 = FUN_7ffe9a47fce0(*(longlong *)
                                                                               (self + 0x140),0);
                                                    if (lVar12 == 0) goto LAB_7ffe99b5308c;
                                                    uVar9 = FUN_7ffe9a5711d0(lVar12,uVar6 & 
                                                  0xffffffff,0);
                                                  lVar12 = *(longlong *)(self + 0x1a0);
                                                  lVar16 = func_0x7ffe99940040(_DAT_7ffe9c9549a0);
                                                  func_0x7ffe999c3920(lVar16,0);
                                                  *(undefined4 *)(lVar16 + 0x10) = uVar4;
                                                  *(undefined4 *)(lVar16 + 0x14) = uVar9;
                                                  *(undefined1 *)(lVar16 + 0x19) = 0;
                                                  *(undefined8 *)(lVar16 + 0x20) = 0;
                                                  il2cpp_write_barrier_0();
                                                  *(undefined1 *)(lVar16 + 0x18) = 0;
                                                  if (lVar12 == 0) goto LAB_7ffe99b53086;
                                                  FUN_7ffe9ad4d2a0(lVar12,uVar6 & 0xffffffff);
                                                  }
                                                  func_0x7ffe999c3920(&uStack_78,_DAT_7ffe9c8f8228);
                                                  uVar14 = *(undefined8 *)(self + 0x1a0);
                                                  if (*(int *)(_DAT_7ffe9c954738 + 0xe0) == 0) {
                                                    func_0x7ffe9996d830();
                                                  }
                                                  lVar12 = *(longlong *)
                                                            (*(longlong *)(_DAT_7ffe9c954738 + 0xb8)
                                                            + 8);
                                                  if (lVar12 == 0) {
                                                    if (*(int *)(_DAT_7ffe9c954738 + 0xe0) == 0) {
                                                      func_0x7ffe9996d830();
                                                    }
                                                    uVar13 = **(undefined8 **)
                                                               (_DAT_7ffe9c954738 + 0xb8);
                                                    lVar12 = func_0x7ffe99940040(_DAT_7ffe9c934db0);
                                                    FUN_7ffe9af13120(lVar12,uVar13,_DAT_7ffe9c951540
                                                                     ,0);
                                                    *(longlong *)
                                                     (*(longlong *)(_DAT_7ffe9c954738 + 0xb8) + 8) =
                                                         lVar12;
                                                    il2cpp_write_barrier_0();
                                                  }
                                                  uVar14 = FUN_7ffe9ab8b7d0(uVar14,lVar12,
                                                                            _DAT_7ffe9c9117d8);
                                                  if (*(int *)(_DAT_7ffe9c954738 + 0xe0) == 0) {
                                                    func_0x7ffe9996d830(_DAT_7ffe9c954738);
                                                  }
                                                  lVar12 = *(longlong *)
                                                            (*(longlong *)(_DAT_7ffe9c954738 + 0xb8)
                                                            + 0x10);
                                                  if (lVar12 == 0) {
                                                    if (*(int *)(_DAT_7ffe9c954738 + 0xe0) == 0) {
                                                      func_0x7ffe9996d830(_DAT_7ffe9c954738);
                                                    }
                                                    uVar13 = **(undefined8 **)
                                                               (_DAT_7ffe9c954738 + 0xb8);
                                                    lVar12 = func_0x7ffe99940040(_DAT_7ffe9c934db0);
                                                    FUN_7ffe9af13120(lVar12,uVar13,_DAT_7ffe9c951600
                                                                     ,0);
                                                    *(longlong *)
                                                     (*(longlong *)(_DAT_7ffe9c954738 + 0xb8) + 0x10
                                                     ) = lVar12;
                                                    il2cpp_write_barrier_0();
                                                  }
                                                  if (*(int *)(_DAT_7ffe9c954738 + 0xe0) == 0) {
                                                    func_0x7ffe9996d830(_DAT_7ffe9c954738);
                                                  }
                                                  lVar16 = *(longlong *)
                                                            (*(longlong *)(_DAT_7ffe9c954738 + 0xb8)
                                                            + 0x18);
                                                  if (lVar16 == 0) {
                                                    if (*(int *)(_DAT_7ffe9c954738 + 0xe0) == 0) {
                                                      func_0x7ffe9996d830(_DAT_7ffe9c954738);
                                                    }
                                                    uVar13 = **(undefined8 **)
                                                               (_DAT_7ffe9c954738 + 0xb8);
                                                    lVar16 = func_0x7ffe99940040(_DAT_7ffe9c934e78);
                                                    FUN_7ffe9af13360(lVar16,uVar13,_DAT_7ffe9c9516c8
                                                                     ,0);
                                                    *(longlong *)
                                                     (*(longlong *)(_DAT_7ffe9c954738 + 0xb8) + 0x18
                                                     ) = lVar16;
                                                    il2cpp_write_barrier_0();
                                                  }
                                                  uVar14 = FUN_7ffe9ab91960(uVar14,lVar12,lVar16,
                                                                            _DAT_7ffe9c921158);
                                                  fVar20 = fStack_b8;
                                                  fVar21 = fStack_b4;
                                                  fVar2 = fStack_b0;
                                                  if (self != (undefined *)0x0) {
                                                    *(undefined8 *)(self + 0x1a0) = uVar14;
                                                    il2cpp_write_barrier_0();
                                                    lVar12 = FUN_7ffe9b141840(_DAT_7ffe9c954238);
                                                    lVar16 = FUN_7ffe9b141840(_DAT_7ffe9c952588);
                                                    fVar20 = fStack_b8;
                                                    fVar21 = fStack_b4;
                                                    fVar2 = fStack_b0;
                                                    if (lVar16 != 0) {
                                                      cVar7 = FUN_7ffe9a8dd380(lVar16,3);
                                                      if (cVar7 == '\0') {
                                                        lVar16 = FUN_7ffe9b141840(_DAT_7ffe9c953710)
                                                        ;
                                                        lVar17 = func_0x7ffe9996c990(
                                                  _DAT_7ffe9c9269c8,1);
                                                  fVar20 = fStack_b8;
                                                  fVar21 = fStack_b4;
                                                  fVar2 = fStack_b0;
                                                  if (lVar17 == 0) goto LAB_7ffe99b530b3;
                                                  if (*(int *)(lVar17 + 0x18) == 0)
                                                  goto LAB_7ffe99b5306e;
                                                  *(undefined4 *)(lVar17 + 0x20) = 0x67;
                                                  if ((lVar16 == 0) ||
                                                     (lVar16 = FUN_7ffe9a579fd0(lVar16,lVar17,0),
                                                     fVar20 = fStack_b8, fVar21 = fStack_b4,
                                                     fVar2 = fStack_b0, lVar16 == 0))
                                                  goto LAB_7ffe99b530b3;
                                                  FUN_7ffe9af836e0(&uStack_98,lVar16,
                                                                   _DAT_7ffe9c92d5c0);
                                                  uStack_78 = (undefined4)uStack_98;
                                                  uStack_74 = uStack_98._4_4_;
                                                  uStack_70 = (undefined4)uStack_90;
                                                  uStack_6c = uStack_90._4_4_;
                                                  uStack_68 = uStack_88;
                                                  uStack_98 = 0;
                                                  uStack_90 = &uStack_78;
                                                  while (cVar7 = FUN_7ffe9ae24860(&uStack_78,
                                                                                  _DAT_7ffe9c8f82f8)
                                                        , uVar6 = uStack_68, cVar7 != '\0') {
                                                    if (lVar12 == 0) goto LAB_7ffe99b530a7;
                                                    if (*(longlong *)(lVar12 + 0x70) == 0)
                                                    goto LAB_7ffe99b530a2;
                                                    iVar8 = FUN_7ffe9a5962a0(*(longlong *)
                                                                              (lVar12 + 0x70),
                                                                             uStack_68 & 0xffffffff)
                                                    ;
                                                    if (0 < iVar8) {
                                                      lVar16 = *(longlong *)(self + 0x1a0);
                                                      uVar14 = func_0x7ffe99940040(_DAT_7ffe9c9549a0
                                                                                  );
                                                      FUN_7ffe99ae78b0(uVar14,uVar6 & 0xffffffff,
                                                                       iVar8,1,0);
                                                      if (lVar16 == 0) goto LAB_7ffe99b5309d;
                                                      FUN_7ffe9ad4d2a0(lVar16,uVar6 & 0xffffffff,
                                                                       uVar14,_DAT_7ffe9c91de00);
                                                    }
                                                  }
                                                  func_0x7ffe999c3920(&uStack_78,_DAT_7ffe9c8f8228);
                                                  }
                                                  fVar20 = fStack_b8;
                                                  fVar21 = fStack_b4;
                                                  fVar2 = fStack_b0;
                                                  if (*(longlong *)(self + 0xf8) != 0) {
                                                    lVar12 = FUN_7ffe9bd98960(*(longlong *)
                                                                               (self + 0xf8),0);
                                                    fVar20 = fStack_b8;
                                                    fVar21 = fStack_b4;
                                                    fVar2 = fStack_b0;
                                                    if ((*(longlong *)(self + 0x1a0) != 0) &&
                                                       (iVar8 = func_0x7ffe9acd8120(*(longlong *)
                                                                                     (self + 0x1a0),
                                                                                                                                                                        
                                                  _DAT_7ffe9c91e058), fVar20 = fStack_b8,
                                                  fVar21 = fStack_b4, fVar2 = fStack_b0, lVar12 != 0
                                                  )) {
                                                    FUN_7ffe9bd9b390(lVar12,iVar8 < 1,0);
                                                    fVar20 = fStack_b8;
                                                    fVar21 = fStack_b4;
                                                    fVar2 = fStack_b0;
                                                    if (*(longlong *)(self + 0xf0) != 0) {
                                                      FUN_7ffe9bd97d00(*(longlong *)(self + 0xf0),0,
                                                                       0);
                                                      lVar12 = *(longlong *)(self + 0x110);
                                                      while (fVar20 = fStack_b8, fVar21 = fStack_b4,
                                                            fVar2 = fStack_b0, lVar12 != 0) {
                                                        uVar18 = (uint)plVar11;
                                                        if (*(int *)(lVar12 + 0x18) <= (int)uVar18)
                                                        {
                                                          self[0x150] = 1;
                                                          return;
                                                        }
                                                        lVar12 = *(longlong *)(self + 0x110);
                                                        if (lVar12 == 0) break;
                                                        if (*(uint *)(lVar12 + 0x18) <= uVar18)
                                                        goto LAB_7ffe99b5306e;
                                                        lVar12 = *(longlong *)
                                                                  (lVar12 + 0x20 +
                                                                  (longlong)(int)uVar18 * 8);
                                                        if (lVar12 == 0) break;
                                                        FUN_7ffe999f2150(lVar12,1,0);
                                                        plVar11 = (longlong *)
                                                                  (ulonglong)(uVar18 + 1);
                                                        lVar12 = *(longlong *)(self + 0x110);
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
LAB_7ffe99b530b3:
  fStack_b0 = fVar2;
  fStack_b4 = fVar21;
  fStack_b8 = fVar20;
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

