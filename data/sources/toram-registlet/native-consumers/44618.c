
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ReceiveSupportResult_OnEventPlayerSupport
               (short skillId,byte skillLv,byte targetArchetypeType,int targetArchetypeId,
               undefined *supportData,undefined *methodInfo)

{
  short sVar1;
  undefined4 uVar2;
  code *pcVar3;
  undefined *puVar4;
  float fVar5;
  char cVar6;
  undefined1 uVar7;
  byte bVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  longlong lVar14;
  longlong lVar15;
  longlong *plVar16;
  longlong lVar17;
  longlong *plVar18;
  undefined *puVar19;
  undefined8 *puVar20;
  undefined8 uVar21;
  undefined8 uVar22;
  undefined8 uVar23;
  int iVar24;
  bool bVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  undefined8 in_stack_fffffffffffffe18;
  ulonglong uVar30;
  ulonglong in_stack_fffffffffffffe20;
  ulonglong in_stack_fffffffffffffe28;
  undefined8 uStack_1b8;
  float fStack_1b0;
  undefined8 uStack_1a8;
  float fStack_1a0;
  undefined8 uStack_198;
  float fStack_190;
  undefined8 uStack_188;
  float fStack_180;
  undefined1 auStack_178 [4];
  uint uStack_174;
  undefined8 uStack_170;
  int aiStack_168 [2];
  longlong *plStack_160;
  longlong lStack_158;
  longlong lStack_150;
  longlong *plStack_148;
  undefined8 uStack_140;
  int iStack_138;
  longlong lStack_130;
  longlong lStack_128;
  longlong *plStack_120;
  longlong lStack_118;
  longlong lStack_110;
  longlong lStack_108;
  longlong *plStack_100;
  longlong *plStack_f8;
  longlong *plStack_f0;
  longlong *plStack_e8;
  longlong *plStack_e0;
  longlong *plStack_d8;
  undefined8 uStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  undefined4 uStack_a0;
  
  puVar4 = supportData;
  iVar24 = (int)skillId;
  if (DAT_7ffe9cae0caf == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92dfe0);
    FUN_7ffe9996d590(0x7ffe9c954a58);
    FUN_7ffe9996d590(&DAT_7ffe9c930f30);
    FUN_7ffe9996d590(&DAT_7ffe9c941198);
    FUN_7ffe9996d590(&DAT_7ffe9c94ac30);
    FUN_7ffe9996d590(&DAT_7ffe9c9585d0);
    FUN_7ffe9996d590(&DAT_7ffe9c9341c8);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c8f5638);
    FUN_7ffe9996d590(&DAT_7ffe9c8f68e8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f82e8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f9db8);
    FUN_7ffe9996d590(&DAT_7ffe9c900a98);
    FUN_7ffe9996d590(&DAT_7ffe9c8f3660);
    FUN_7ffe9996d590(&DAT_7ffe9c91ac20);
    FUN_7ffe9996d590(&DAT_7ffe9c949c60);
    FUN_7ffe9996d590(&DAT_7ffe9c94ba38);
    FUN_7ffe9996d590(&DAT_7ffe9c952db0);
    FUN_7ffe9996d590(&DAT_7ffe9c95fc00);
    FUN_7ffe9996d590(&DAT_7ffe9c964c70);
    FUN_7ffe9996d590(&DAT_7ffe9c8f7560);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c921aa0);
    FUN_7ffe9996d590(&DAT_7ffe9c922a40);
    FUN_7ffe9996d590(&DAT_7ffe9c928be8);
    FUN_7ffe9996d590(&DAT_7ffe9c93ce00);
    FUN_7ffe9996d590(&DAT_7ffe9c9467e0);
    FUN_7ffe9996d590(&DAT_7ffe9c9477f0);
    FUN_7ffe9996d590(&DAT_7ffe9c952a50);
    FUN_7ffe9996d590(&DAT_7ffe9c956938);
    FUN_7ffe9996d590(&DAT_7ffe9c956ad0);
    FUN_7ffe9996d590(&DAT_7ffe9c968c00);
    FUN_7ffe9996d590(&DAT_7ffe9c968cd0);
    FUN_7ffe9996d590(&DAT_7ffe9c969330);
    FUN_7ffe9996d590(&DAT_7ffe9c94c0a0);
    FUN_7ffe9996d590(&DAT_7ffe9c94f0d8);
    FUN_7ffe9996d590(&DAT_7ffe9c9500f0);
    FUN_7ffe9996d590(&DAT_7ffe9c95dac8);
    FUN_7ffe9996d590(&DAT_7ffe9c9636c0);
    FUN_7ffe9996d590(&DAT_7ffe9c96ec48);
    FUN_7ffe9996d590(&DAT_7ffe9c8ff608);
    FUN_7ffe9996d590(&DAT_7ffe9c928e30);
    FUN_7ffe9996d590(&DAT_7ffe9c959458);
    DAT_7ffe9cae0caf = '\x01';
  }
  plVar18 = (longlong *)0x0;
  plStack_f8 = (longlong *)0x0;
  plStack_100 = (longlong *)0x0;
  uStack_c8 = 0;
  uStack_c0 = 0;
  uStack_a8 = 0;
  uStack_b8 = 0;
  uStack_b0 = 0;
  uStack_a0 = 0;
  plStack_148 = (longlong *)0x0;
  lStack_108 = 0;
  lStack_150 = 0;
  lStack_130 = 0;
  lStack_110 = 0;
  uStack_170 = 0;
  lStack_158 = 0;
  lStack_118 = 0;
  plStack_120 = (longlong *)0x0;
  plStack_d8 = (longlong *)0x0;
  plStack_e8 = (longlong *)0x0;
  plStack_160 = (longlong *)0x0;
  aiStack_168[0] = 0;
  supportData._0_1_ = 0;
  auStack_178[0] = 0;
  plStack_e0 = (longlong *)0x0;
  lStack_128 = 0;
  uStack_140 = 0;
  plStack_f0 = (longlong *)0x0;
  uStack_d0 = 0;
  lVar14 = FUN_7ffe9a47bac0(0);
  lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
  fVar29 = fStack_1b0;
  if ((puVar4 == (undefined *)0x0) || (lVar15 == 0)) goto LAB_7ffe9aae5a30;
  FUN_7ffe9a8da6c0(lVar15,*(undefined8 *)(puVar4 + 0x20),0);
  uVar13 = (undefined4)((ulonglong)in_stack_fffffffffffffe18 >> 0x20);
  lVar15 = *(longlong *)(puVar4 + 0x40);
  plVar16 = plVar18;
  if (lVar15 != 0) {
    while( true ) {
      uVar13 = (undefined4)((ulonglong)in_stack_fffffffffffffe18 >> 0x20);
      uVar11 = (uint)plVar16;
      if (*(int *)(lVar15 + 0x18) <= (int)uVar11) break;
      if (*(uint *)(lVar15 + 0x18) <= uVar11) {
        FUN_7ffe9996d790();
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
      fVar29 = fStack_1b0;
      if (((lVar14 == 0) ||
          (plVar16 = (longlong *)FUN_7ffe9a480070(lVar14,0), fVar29 = fStack_1b0,
          plVar16 == (longlong *)0x0)) ||
         (lVar17 = (**(code **)(*plVar16 + 0x1e8))(plVar16,*(undefined8 *)(*plVar16 + 0x1f0)),
         fVar29 = fStack_1b0, lVar17 == 0)) goto LAB_7ffe9aae5a30;
      func_0x7ffe9a4dbd30(lVar17);
      plVar16 = (longlong *)(ulonglong)(uVar11 + 1);
    }
  }
  uVar2 = _DAT_7ffe9c049b18;
  uVar12 = (undefined4)(in_stack_fffffffffffffe20 >> 0x20);
  if (skillId == 0xe7) {
    if (*(longlong *)(puVar4 + 0x40) == 0) {
      uVar23 = FUN_7ffe9a79f970(skillLv,0,0);
      fVar29 = fStack_1b0;
      if ((lVar14 == 0) || (lVar15 = FUN_7ffe9a4803f0(lVar14,0), fVar29 = fStack_1b0, lVar15 == 0))
      goto LAB_7ffe9aae5a30;
      FUN_7ffe9a7c26c0(lVar15,uVar23,0,0);
    }
    if (0 < *(short *)(puVar4 + 0x2c)) {
      fVar29 = fStack_1b0;
      if ((lVar14 == 0) || (lVar15 = FUN_7ffe9a47f400(lVar14,0), fVar29 = fStack_1b0, lVar15 == 0))
      goto LAB_7ffe9aae5a30;
      FUN_7ffe9a6fbaa0(lVar15,0xcc,(int)*(short *)(puVar4 + 0x2c),0);
    }
  }
  else {
    fVar29 = fStack_1b0;
    if (skillId == 0x109) {
      if (((lVar14 == 0) || (lVar15 = FUN_7ffe9a4803f0(lVar14,0), fVar29 = fStack_1b0, lVar15 == 0))
         || (*(longlong *)(lVar15 + 0x40) == 0)) goto LAB_7ffe9aae5a30;
      cVar6 = FUN_7ffe9ad5f0a0(*(longlong *)(lVar15 + 0x40),0x109,_DAT_7ffe9c9341c8);
      uVar12 = (undefined4)(in_stack_fffffffffffffe20 >> 0x20);
      if (cVar6 == '\0') {
        if (0.0 < *(float *)(puVar4 + 0x30)) {
          plVar16 = (longlong *)FUN_7ffe9a480070(lVar14,0);
          fVar29 = fStack_1b0;
          if ((plVar16 == (longlong *)0x0) ||
             (lVar15 = (**(code **)(*plVar16 + 0x1c8))(plVar16,*(undefined8 *)(*plVar16 + 0x1d0)),
             fVar29 = fStack_1b0, lVar15 == 0)) goto LAB_7ffe9aae5a30;
          in_stack_fffffffffffffe28 = 0;
          in_stack_fffffffffffffe20 = CONCAT44(uVar12,targetArchetypeId);
          uVar23 = CONCAT44(uVar13,*(undefined4 *)(puVar4 + 0x34));
          FUN_7ffe9a7c22c0(lVar15,0x109,skillLv,*(undefined4 *)(puVar4 + 0x30),uVar23,
                           in_stack_fffffffffffffe20,0);
          uVar13 = (undefined4)((ulonglong)uVar23 >> 0x20);
        }
        lVar15 = FUN_7ffe9a4803f0(lVar14,0);
        fVar29 = fStack_1b0;
        if ((lVar15 == 0) || (*(longlong *)(lVar15 + 0x50) == 0)) goto LAB_7ffe9aae5a30;
        cVar6 = FUN_7ffe9ad8e670(*(longlong *)(lVar15 + 0x50),0x109,&plStack_f8,_DAT_7ffe9c934418);
        if ((cVar6 != '\0') && (plStack_f8 != (longlong *)0x0)) {
          if (((*(byte *)(_DAT_7ffe9c91ac20 + 0x130) <= *(byte *)(*plStack_f8 + 0x130)) &&
              (*(longlong *)
                (*(longlong *)(*plStack_f8 + 200) + -8 +
                (ulonglong)*(byte *)(_DAT_7ffe9c91ac20 + 0x130) * 8) == _DAT_7ffe9c91ac20)) &&
             (plStack_f8 != (longlong *)0x0)) {
            *(undefined4 *)((longlong)plStack_f8 + 0x3c) = *(undefined4 *)(puVar4 + 0x34);
          }
        }
      }
    }
    else if (skillId == 0x3e2) {
      if (((lVar14 == 0) ||
          (plVar16 = (longlong *)FUN_7ffe9a480070(lVar14,0), fVar29 = fStack_1b0,
          plVar16 == (longlong *)0x0)) ||
         (lVar15 = (**(code **)(*plVar16 + 0x1c8))(plVar16,*(undefined8 *)(*plVar16 + 0x1d0)),
         fVar29 = fStack_1b0, lVar15 == 0)) goto LAB_7ffe9aae5a30;
      in_stack_fffffffffffffe28 = 0;
      in_stack_fffffffffffffe20 = CONCAT44(uVar12,targetArchetypeId);
      uVar23 = CONCAT44(uVar13,*(undefined4 *)(puVar4 + 0x34));
      FUN_7ffe9a7c22c0(lVar15,0x3e2,skillLv,*(undefined4 *)(puVar4 + 0x30),uVar23,
                       in_stack_fffffffffffffe20,0);
      uVar13 = (undefined4)((ulonglong)uVar23 >> 0x20);
      lVar15 = FUN_7ffe9a47ef30(lVar14,0);
      fVar29 = fStack_1b0;
      if (lVar15 == 0) goto LAB_7ffe9aae5a30;
      func_0x7ffe9a4dbd30(lVar15,0xb);
    }
    else if (skillId == 0x48a) {
      uVar12 = *(undefined4 *)(puVar4 + 0x28);
      lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
      fVar29 = fStack_1b0;
      if ((lVar14 == 0) || (lVar17 = FUN_7ffe9a480940(lVar14,0), fVar29 = fStack_1b0, lVar17 == 0))
      goto LAB_7ffe9aae5a30;
      puVar20 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_1b8,lVar17,0);
      uStack_1a8 = *puVar20;
      fStack_1a0 = *(float *)(puVar20 + 1);
      if (DAT_7ffe9cad9cac == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
        DAT_7ffe9cad9cac = '\x01';
      }
      uStack_1b8 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x18);
      fVar29 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x20);
      fStack_1b0 = fStack_1a0 + fVar29;
      uStack_198 = CONCAT44(uStack_1a8._4_4_ + (float)((ulonglong)uStack_1b8 >> 0x20),
                            (float)uStack_1a8 + (float)uStack_1b8);
      fStack_190 = fStack_1b0;
      if (lVar15 == 0) goto LAB_7ffe9aae5a30;
      uStack_1b8 = uStack_198;
      FUN_7ffe99caa840(lVar15,uVar12,&uStack_1b8,0);
      lVar15 = FUN_7ffe9a4803f0(lVar14,0);
      fVar29 = fStack_1b0;
      if ((lVar15 == 0) || (*(longlong *)(lVar15 + 0x40) == 0)) goto LAB_7ffe9aae5a30;
      cVar6 = FUN_7ffe9ad8e670(*(longlong *)(lVar15 + 0x40),0x482,&plStack_100,_DAT_7ffe9c934418);
      if (cVar6 != '\0') {
        fVar29 = fStack_1b0;
        if (plStack_100 == (longlong *)0x0) goto LAB_7ffe9aae5a30;
        if (((*(byte *)(*plStack_100 + 0x130) < *(byte *)(_DAT_7ffe9c94ac30 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*plStack_100 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c94ac30 + 0x130) * 8) != _DAT_7ffe9c94ac30)) ||
           (plStack_100 == (longlong *)0x0)) {
          FUN_7ffe9996c950(plStack_100);
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
        func_0x7ffe9a77d680(plStack_100,uVar12,0);
      }
    }
    else {
      if (*(int *)(_DAT_7ffe9c94c0a0 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      cVar6 = FUN_7ffe9a811270(iVar24,0);
      fVar29 = fStack_1b0;
      if (cVar6 == '\0') {
        if ((skillId == 0x402) || (skillId == 0x40d)) {
          if (*(int *)(puVar4 + 0x34) == -1) {
            return;
          }
          lVar15 = FUN_7ffe9b15c270(_DAT_7ffe9c9636c0);
          fVar29 = fStack_1b0;
          if (lVar15 == 0) goto LAB_7ffe9aae5a30;
          lVar15 = FUN_7ffe9a3d0470(lVar15,0,targetArchetypeId,0);
          if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          cVar6 = FUN_7ffe9bda2160(lVar15,0,0);
          if (cVar6 != '\0') {
            fVar29 = fStack_1b0;
            if ((lVar15 == 0) ||
               (lVar15 = FUN_7ffe9bd98a10(lVar15,0), fVar29 = fStack_1b0, lVar15 == 0))
            goto LAB_7ffe9aae5a30;
            puVar20 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_1b8,lVar15,0);
            uStack_198 = *puVar20;
            fStack_190 = *(float *)(puVar20 + 1);
            lVar15 = FUN_7ffe9b15c270(_DAT_7ffe9c9636c0);
            fVar29 = fStack_1b0;
            if (lVar15 == 0) goto LAB_7ffe9aae5a30;
            lVar15 = FUN_7ffe9a3d0470(lVar15,8,targetArchetypeId,0);
            fVar27 = (float)(int)*(short *)(puVar4 + 0x36) * _DAT_7ffe9c049b40;
            fVar28 = (float)(int)*(short *)(puVar4 + 0x34) * _DAT_7ffe9c049b40;
            if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            cVar6 = FUN_7ffe9bda2160(lVar15,0,0);
            fVar26 = uStack_198._4_4_;
            fVar29 = uStack_198._4_4_;
            if (cVar6 != '\0') {
              fVar29 = fStack_1b0;
              if ((lVar15 == 0) ||
                 (lVar15 = FUN_7ffe9bd98a10(lVar15,0), fVar29 = fStack_1b0, lVar15 == 0))
              goto LAB_7ffe9aae5a30;
              lVar15 = FUN_7ffe9bdbf710(&uStack_1b8,lVar15,0);
              fVar29 = *(float *)(lVar15 + 4);
            }
            if (DAT_7ffe9cad9cac == '\0') {
              FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
              DAT_7ffe9cad9cac = '\x01';
            }
            uStack_188 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x18);
            fStack_180 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x20);
            fStack_1a0 = fStack_180 * _DAT_7ffe9c049ce4 + fVar28;
            uStack_1a8 = CONCAT44((float)((ulonglong)uStack_188 >> 0x20) * _DAT_7ffe9c049ce4 +
                                  fVar29,(float)uStack_188 * _DAT_7ffe9c049ce4 + fVar27);
            if (DAT_7ffe9cad9eaf == '\0') {
              FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
              DAT_7ffe9cad9eaf = '\x01';
            }
            uVar23 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x24);
            uVar12 = *(undefined4 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x2c);
            bVar8 = FUN_7ffe9bd9bec0(_DAT_7ffe9c959458,0);
            if (*(int *)(_DAT_7ffe9c921aa0 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            fStack_1b0 = fStack_1a0;
            uVar21 = CONCAT44(uVar13,1 << (bVar8 & 0x1f));
            uStack_1b8 = uStack_1a8;
            uStack_188 = uVar23;
            fStack_180 = (float)uVar12;
            cVar6 = FUN_7ffe9bdf0360(&uStack_1b8,&uStack_188,&uStack_c8,_DAT_7ffe9c049c90,uVar21,0);
            if (cVar6 == '\0') {
              return;
            }
            puVar20 = (undefined8 *)func_0x7ffe9bd78a30(&uStack_1b8,&uStack_c8,0);
            uVar23 = *puVar20;
            fVar27 = *(float *)(puVar20 + 1);
            uStack_1a8 = uVar23;
            fStack_1a0 = fVar27;
            if (DAT_7ffe9cad9ca9 == '\0') {
              FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
              DAT_7ffe9cad9ca9 = '\x01';
            }
            fVar5 = fStack_1a0;
            fVar28 = (float)uStack_1a8;
            fStack_1b0 = fStack_1a0 - fStack_190;
            uVar22 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x48);
            fVar29 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x50);
            uStack_1b8 = CONCAT44(uStack_1a8._4_4_ - fVar26,(float)uStack_1a8 - (float)uStack_198);
            fStack_180 = fStack_1b0;
            puVar20 = (undefined8 *)FUN_7ffe999fca00(&uStack_188,&uStack_1b8,0);
            uStack_1b8 = *puVar20;
            fStack_1b0 = *(float *)(puVar20 + 1);
            uStack_188 = uVar22;
            fStack_180 = fVar29;
            fVar26 = (float)FUN_7ffe99a4ef70(&uStack_188,&uStack_1b8,0);
            fVar26 = fVar26 + _DAT_7ffe9c049b1c;
            fVar29 = fStack_1b0;
            if ((lVar14 == 0) ||
               (lVar15 = FUN_7ffe9a480940(lVar14,0), fVar29 = fStack_1b0, lVar15 == 0))
            goto LAB_7ffe9aae5a30;
            puVar20 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_1b8,lVar15,0);
            uStack_1b8 = *puVar20;
            fStack_1b0 = *(float *)(puVar20 + 1);
            fVar28 = fVar28 - (float)uStack_1b8;
            bVar25 = fVar28 * fVar28 + 0.0 + (fVar5 - fStack_1b0) * (fVar5 - fStack_1b0) <=
                     _DAT_7ffe9c049d14;
            lVar15 = FUN_7ffe9a4803f0(lVar14,0);
            fVar29 = fStack_1b0;
            if ((lVar15 == 0) || (*(longlong *)(lVar15 + 0x50) == 0)) goto LAB_7ffe9aae5a30;
            cVar6 = FUN_7ffe9ad8e670(*(longlong *)(lVar15 + 0x50),0x402,&plStack_148,
                                     _DAT_7ffe9c934418);
            if (cVar6 == '\0') {
              plVar16 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c964c70);
              FUN_7ffe9a79b250(plVar16,skillLv,0);
              fVar29 = fStack_1b0;
              plStack_148 = plVar16;
              if (plVar16 == (longlong *)0x0) goto LAB_7ffe9aae5a30;
              lVar15 = *plVar16;
              if ((*(byte *)(lVar15 + 0x130) < *(byte *)(_DAT_7ffe9c964c70 + 0x130)) ||
                 (*(longlong *)
                   (*(longlong *)(lVar15 + 200) + -8 +
                   (ulonglong)*(byte *)(_DAT_7ffe9c964c70 + 0x130) * 8) != _DAT_7ffe9c964c70)) {
                FUN_7ffe9996c950(plVar16);
                pcVar3 = (code *)swi(3);
                (*pcVar3)();
                return;
              }
              if ((*(byte *)(lVar15 + 0x130) < *(byte *)(_DAT_7ffe9c964c70 + 0x130)) ||
                 (*(longlong *)
                   (*(longlong *)(lVar15 + 200) + -8 +
                   (ulonglong)*(byte *)(_DAT_7ffe9c964c70 + 0x130) * 8) != _DAT_7ffe9c964c70)) {
                uStack_1b8 = uVar23;
                fStack_1b0 = fVar27;
                FUN_7ffe9996c950(plVar16);
                pcVar3 = (code *)swi(3);
                (*pcVar3)();
                return;
              }
              in_stack_fffffffffffffe20 = 0;
              uVar21 = CONCAT71((int7)((ulonglong)uVar21 >> 8),bVar25);
              uStack_1b8 = uVar23;
              fStack_1b0 = fVar27;
              FUN_7ffe9a79a0c0(plVar16,targetArchetypeId,&uStack_1b8,fVar26,uVar21,0);
              uVar13 = (undefined4)((ulonglong)uVar21 >> 0x20);
              lVar15 = FUN_7ffe9a4803f0(lVar14,0);
              fVar29 = fStack_1b0;
              if (lVar15 == 0) goto LAB_7ffe9aae5a30;
              FUN_7ffe9a7c1d20(lVar15,plStack_148,0,0);
            }
            else {
              fVar29 = fStack_1b0;
              if (plStack_148 == (longlong *)0x0) goto LAB_7ffe9aae5a30;
              lVar15 = *plStack_148;
              if (((*(byte *)(lVar15 + 0x130) < *(byte *)(_DAT_7ffe9c964c70 + 0x130)) ||
                  (*(longlong *)
                    (*(longlong *)(lVar15 + 200) + -8 +
                    (ulonglong)*(byte *)(_DAT_7ffe9c964c70 + 0x130) * 8) != _DAT_7ffe9c964c70)) ||
                 (plStack_148 == (longlong *)0x0)) {
                FUN_7ffe9996c950(plStack_148);
                pcVar3 = (code *)swi(3);
                (*pcVar3)();
                return;
              }
              if (((*(byte *)(lVar15 + 0x130) < *(byte *)(_DAT_7ffe9c964c70 + 0x130)) ||
                  (*(longlong *)
                    (*(longlong *)(lVar15 + 200) + -8 +
                    (ulonglong)*(byte *)(_DAT_7ffe9c964c70 + 0x130) * 8) != _DAT_7ffe9c964c70)) ||
                 (plStack_148 == (longlong *)0x0)) {
                uStack_1b8 = uVar23;
                fStack_1b0 = fVar27;
                FUN_7ffe9996c950(plStack_148);
                pcVar3 = (code *)swi(3);
                (*pcVar3)();
                return;
              }
              in_stack_fffffffffffffe20 = 0;
              uVar21 = CONCAT71((int7)((ulonglong)uVar21 >> 8),bVar25);
              uStack_1b8 = uVar23;
              fStack_1b0 = fVar27;
              FUN_7ffe9a799f90(plStack_148,targetArchetypeId,&uStack_1b8,fVar26,uVar21,0);
              uVar13 = (undefined4)((ulonglong)uVar21 >> 0x20);
            }
          }
        }
        else if (skillId == 900) {
          if (0 < *(int *)(puVar4 + 0x34)) {
            uVar23 = func_0x7ffe99940040(_DAT_7ffe9c952db0);
            FUN_7ffe9a793770(uVar23,skillLv,0,0);
            fVar29 = fStack_1b0;
            if ((lVar14 == 0) ||
               (lVar15 = FUN_7ffe9a4803f0(lVar14,0), fVar29 = fStack_1b0, lVar15 == 0))
            goto LAB_7ffe9aae5a30;
            FUN_7ffe9a7c1d20(lVar15,uVar23,0,0);
          }
          if (0 < *(short *)(puVar4 + 0x2c)) {
            lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
            sVar1 = *(short *)(puVar4 + 0x2c);
            fVar29 = fStack_1b0;
            if ((lVar14 == 0) ||
               (lVar17 = FUN_7ffe9a480940(lVar14,0), fVar29 = fStack_1b0, lVar17 == 0))
            goto LAB_7ffe9aae5a30;
            puVar20 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_1b8,lVar17,0);
            uStack_1a8 = *puVar20;
            fStack_1a0 = *(float *)(puVar20 + 1);
            if (DAT_7ffe9cad9cac == '\0') {
              FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
              DAT_7ffe9cad9cac = '\x01';
            }
            uStack_188 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x18);
            fStack_180 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x20);
            fStack_190 = fStack_1a0 + fStack_180;
            uStack_198 = CONCAT44(uStack_1a8._4_4_ + (float)((ulonglong)uStack_188 >> 0x20),
                                  (float)uStack_1a8 + (float)uStack_188);
            fVar29 = fStack_1b0;
            if (lVar15 == 0) goto LAB_7ffe9aae5a30;
            uStack_188 = uStack_198;
            fStack_180 = fStack_190;
            FUN_7ffe99caa960(lVar15,(int)sVar1,&uStack_188,0);
          }
        }
        else if (skillId != 0x9e) {
          if (skillId == 0x273) {
            if (((lVar14 == 0) ||
                (plVar16 = (longlong *)FUN_7ffe9a480070(lVar14,0), fVar29 = fStack_1b0,
                plVar16 == (longlong *)0x0)) ||
               (puVar19 = (undefined *)
                          (**(code **)(*plVar16 + 0x218))(plVar16,*(undefined8 *)(*plVar16 + 0x220))
               , fVar29 = fStack_1b0, puVar19 == (undefined *)0x0)) goto LAB_7ffe9aae5a30;
            bVar8 = GemCartBufferManager_ContainsBuffer(puVar19,0x415,(undefined *)0x0);
            lVar15 = FUN_7ffe9a4803f0(lVar14,0);
            fVar29 = fStack_1b0;
            if (lVar15 == 0) goto LAB_7ffe9aae5a30;
            cVar6 = FUN_7ffe9abc2210(lVar15,0x273,&lStack_108,_DAT_7ffe9c968c00);
            if (cVar6 == '\0') {
              uVar23 = func_0x7ffe99940040(_DAT_7ffe9c949c60);
              FUN_7ffe9a7936f0(uVar23,skillLv,bVar8,0);
              lVar15 = FUN_7ffe9a4803f0(lVar14,0);
              fVar29 = fStack_1b0;
              if (lVar15 == 0) goto LAB_7ffe9aae5a30;
              FUN_7ffe9a7c26c0(lVar15,uVar23,0,0);
            }
            else {
              fVar29 = fStack_1b0;
              if (lStack_108 == 0) goto LAB_7ffe9aae5a30;
              func_0x7ffe9a7933b0(lStack_108,bVar8,0);
            }
          }
          else if (iVar24 == 0x76) {
            if ((puVar4[0x50] & 1) != 0) {
              if (((lVar14 == 0) ||
                  (plVar16 = (longlong *)FUN_7ffe9a480070(lVar14,0), fVar29 = fStack_1b0,
                  plVar16 == (longlong *)0x0)) ||
                 (lVar15 = (**(code **)(*plVar16 + 0x1c8))
                                     (plVar16,*(undefined8 *)(*plVar16 + 0x1d0)),
                 fVar29 = fStack_1b0, lVar15 == 0)) goto LAB_7ffe9aae5a30;
              cVar6 = FUN_7ffe9abc2210(lVar15,0x76,&lStack_150,_DAT_7ffe9c968cd0);
              if (cVar6 == '\0') {
                lVar15 = (**(code **)(*plVar16 + 0x1b8))(plVar16,*(undefined8 *)(*plVar16 + 0x1c0));
                fVar29 = fStack_1b0;
                if (lVar15 == 0) goto LAB_7ffe9aae5a30;
                uVar11 = FUN_7ffe9a7fd580(lVar15,0x76,1);
                if (0 < (int)uVar11) {
                  uVar12 = FUN_7ffe9a4a1cc0(plVar16,0);
                  uVar23 = FUN_7ffe9a47f400(lVar14,0);
                  lStack_150 = FUN_7ffe9a794590(uVar11 & 0xff,uVar12,uVar23,0);
                  lVar15 = (**(code **)(*plVar16 + 0x1c8))
                                     (plVar16,*(undefined8 *)(*plVar16 + 0x1d0));
                  fVar29 = fStack_1b0;
                  if (lVar15 == 0) goto LAB_7ffe9aae5a30;
                  FUN_7ffe9a7c26c0(lVar15,lStack_150,0,0);
                }
              }
              if (lStack_150 != 0) {
                FUN_7ffe9a793f30(lStack_150,0);
              }
            }
            if ((puVar4[0x50] & 2) != 0) {
              fVar29 = fStack_1b0;
              if (((lVar14 == 0) ||
                  (plVar16 = (longlong *)FUN_7ffe9a480070(lVar14,0), fVar29 = fStack_1b0,
                  plVar16 == (longlong *)0x0)) ||
                 (lVar15 = (**(code **)(*plVar16 + 0x1c8))
                                     (plVar16,*(undefined8 *)(*plVar16 + 0x1d0)),
                 fVar29 = fStack_1b0, lVar15 == 0)) goto LAB_7ffe9aae5a30;
              cVar6 = FUN_7ffe9abc2210(lVar15,0x76,&lStack_130,_DAT_7ffe9c968cd0);
              if (cVar6 != '\0') {
                fVar29 = fStack_1b0;
                if (lStack_130 == 0) goto LAB_7ffe9aae5a30;
                FUN_7ffe9a794920(lStack_130,0);
              }
              if ((lStack_130 != 0) && (*(char *)(lStack_130 + 0x13) != '\0')) {
                lVar15 = (**(code **)(*plVar16 + 0x1c8))(plVar16,*(undefined8 *)(*plVar16 + 0x1d0));
                fVar29 = fStack_1b0;
                if (lVar15 == 0) goto LAB_7ffe9aae5a30;
                FUN_7ffe9a7cafa0(lVar15,0x76);
              }
            }
            if ((puVar4[0x50] & 4) != 0) {
              fVar29 = fStack_1b0;
              if (((lVar14 == 0) ||
                  (plVar16 = (longlong *)FUN_7ffe9a480070(lVar14,0), fVar29 = fStack_1b0,
                  plVar16 == (longlong *)0x0)) ||
                 (lVar15 = (**(code **)(*plVar16 + 0x1c8))
                                     (plVar16,*(undefined8 *)(*plVar16 + 0x1d0)),
                 fVar29 = fStack_1b0, lVar15 == 0)) goto LAB_7ffe9aae5a30;
              cVar6 = FUN_7ffe9abc2210(lVar15,0x76,&lStack_110,_DAT_7ffe9c968cd0);
              if (cVar6 != '\0') {
                fVar29 = fStack_1b0;
                if (lStack_110 == 0) goto LAB_7ffe9aae5a30;
                FUN_7ffe9a794620(lStack_110,0);
              }
            }
          }
          else if (iVar24 == 0x72) {
            uVar12 = *(undefined4 *)(puVar4 + 0x34);
            if (*(int *)(_DAT_7ffe9c941198 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            FUN_7ffe9a7dd2f0(uVar12,0);
            lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
            fVar29 = fStack_1b0;
            if ((lVar14 == 0) ||
               (lVar17 = FUN_7ffe9a480940(lVar14,0), fVar29 = fStack_1b0, lVar17 == 0))
            goto LAB_7ffe9aae5a30;
            puVar20 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_1b8,lVar17,0);
            uStack_198 = *puVar20;
            fStack_190 = *(float *)(puVar20 + 1);
            if (DAT_7ffe9cad9cac == '\0') {
              FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
              DAT_7ffe9cad9cac = '\x01';
            }
            uStack_188 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x18);
            fStack_180 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x20);
            fStack_1a0 = fStack_190 + fStack_180;
            uStack_1a8 = CONCAT44(uStack_198._4_4_ + (float)((ulonglong)uStack_188 >> 0x20),
                                  (float)uStack_198 + (float)uStack_188);
            fVar29 = fStack_1b0;
            if (lVar15 == 0) goto LAB_7ffe9aae5a30;
            in_stack_fffffffffffffe20 = 0;
            uStack_188 = uStack_1a8;
            uVar23 = CONCAT44(uVar13,uVar2);
            fStack_180 = fStack_1a0;
            FUN_7ffe99ca74a0(lVar15,1,uVar12,&uStack_188,uVar23,0);
            uVar13 = (undefined4)((ulonglong)uVar23 >> 0x20);
          }
          else if (skillId == 0x2c5) {
            uVar12 = *(undefined4 *)(puVar4 + 0x50);
            lVar15 = func_0x7ffe99940040(_DAT_7ffe9c8f68e8);
            FUN_7ffe9a788860(lVar15,skillLv,uVar12,0);
            fVar29 = fStack_1b0;
            if (lVar14 == 0) goto LAB_7ffe9aae5a30;
            uStack_170 = *(undefined8 *)(lVar14 + 0x50);
            uVar7 = func_0x7ffe9bb9e750(&uStack_170,targetArchetypeType,targetArchetypeId,0);
            fVar29 = fStack_1b0;
            if (lVar15 == 0) goto LAB_7ffe9aae5a30;
            *(undefined1 *)(lVar15 + 0x48) = uVar7;
            plVar16 = (longlong *)FUN_7ffe9a480070(lVar14,0);
            fVar29 = fStack_1b0;
            if ((plVar16 == (longlong *)0x0) ||
               (lVar17 = (**(code **)(*plVar16 + 0x1c8))(plVar16,*(undefined8 *)(*plVar16 + 0x1d0)),
               fVar29 = fStack_1b0, lVar17 == 0)) goto LAB_7ffe9aae5a30;
            FUN_7ffe9a7c1d20(lVar17,lVar15,targetArchetypeId,0);
          }
          else if (skillId == 0x107) {
            lVar15 = func_0x7ffe99940040(_DAT_7ffe9c928be8);
            FUN_7ffe9a79f0c0(lVar15,skillLv,0);
            fVar29 = fStack_1b0;
            if ((((lVar15 == 0) || (*(undefined1 *)(lVar15 + 0x20) = 0, lVar14 == 0)) ||
                (plVar16 = (longlong *)FUN_7ffe9a480070(lVar14,0), fVar29 = fStack_1b0,
                plVar16 == (longlong *)0x0)) ||
               (lVar17 = (**(code **)(*plVar16 + 0x1c8))(plVar16,*(undefined8 *)(*plVar16 + 0x1d0)),
               fVar29 = fStack_1b0, lVar17 == 0)) goto LAB_7ffe9aae5a30;
            FUN_7ffe9a7c1d20(lVar17,lVar15,targetArchetypeId,0);
            uVar11 = *(uint *)(puVar4 + 0x38);
            if (0 < (int)uVar11) {
              lVar15 = func_0x7ffe99940040(_DAT_7ffe9c930f30);
              FUN_7ffe9a779700(lVar15,uVar11 & 0xff,0);
LAB_7ffe9aae30d7:
              fVar29 = fStack_1b0;
              if (lVar15 == 0) goto LAB_7ffe9aae5a30;
              *(undefined1 *)(lVar15 + 0x20) = 0;
              plVar16 = (longlong *)FUN_7ffe9a480070(lVar14,0);
              fVar29 = fStack_1b0;
              if ((plVar16 == (longlong *)0x0) ||
                 (lVar17 = (**(code **)(*plVar16 + 0x1c8))
                                     (plVar16,*(undefined8 *)(*plVar16 + 0x1d0)),
                 fVar29 = fStack_1b0, lVar17 == 0)) goto LAB_7ffe9aae5a30;
              FUN_7ffe9a7c1d20(lVar17,lVar15,targetArchetypeId,0);
            }
          }
          else if (skillId == 0x108) {
            lVar15 = func_0x7ffe99940040(_DAT_7ffe9c930f30);
            FUN_7ffe9a779700(lVar15,skillLv,0);
            fVar29 = fStack_1b0;
            if ((((lVar15 == 0) || (*(undefined1 *)(lVar15 + 0x20) = 0, lVar14 == 0)) ||
                (plVar16 = (longlong *)FUN_7ffe9a480070(lVar14,0), fVar29 = fStack_1b0,
                plVar16 == (longlong *)0x0)) ||
               (lVar17 = (**(code **)(*plVar16 + 0x1c8))(plVar16,*(undefined8 *)(*plVar16 + 0x1d0)),
               fVar29 = fStack_1b0, lVar17 == 0)) goto LAB_7ffe9aae5a30;
            FUN_7ffe9a7c1d20(lVar17,lVar15,targetArchetypeId,0);
            uVar11 = *(uint *)(puVar4 + 0x38);
            if (0 < (int)uVar11) {
              lVar15 = func_0x7ffe99940040(_DAT_7ffe9c928be8);
              FUN_7ffe9a79f0c0(lVar15,uVar11 & 0xff,0);
              goto LAB_7ffe9aae30d7;
            }
          }
          else if (skillId == 0x34d) {
            if (lVar14 == 0) goto LAB_7ffe9aae5a30;
            uVar23 = FUN_7ffe9a480070(lVar14,0);
            FUN_7ffe9a7a7140(uVar23,puVar4,0);
          }
          else if (skillId == 0x34e) {
            if (lVar14 == 0) goto LAB_7ffe9aae5a30;
            uVar23 = FUN_7ffe9a480070(lVar14,0);
            if (*(int *)(_DAT_7ffe9c93ce00 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            FUN_7ffe9a7b8bc0(puVar4,uVar23,0);
          }
          else if (skillId == 0x20f) {
            if (lVar14 == 0) goto LAB_7ffe9aae5a30;
            uVar23 = FUN_7ffe9a47fe30(lVar14,0);
            uVar13 = 0;
            FUN_7ffe9a827760(uVar23,puVar4,skillLv,targetArchetypeId,0);
          }
          else if (skillId == 0x4e3) {
            if ((puVar4[0x50] & 1) != 0) {
              if (((lVar14 == 0) ||
                  (plVar16 = (longlong *)FUN_7ffe9a480070(lVar14,0), fVar29 = fStack_1b0,
                  plVar16 == (longlong *)0x0)) ||
                 (lVar15 = (**(code **)(*plVar16 + 0x1b8))
                                     (plVar16,*(undefined8 *)(*plVar16 + 0x1c0)),
                 fVar29 = fStack_1b0, lVar15 == 0)) goto LAB_7ffe9aae5a30;
              uVar11 = FUN_7ffe9a7fd580(lVar15,0x4e3,1,0);
              uStack_174 = uVar11;
              lVar15 = (**(code **)(*plVar16 + 0x1c8))(plVar16,*(undefined8 *)(*plVar16 + 0x1d0));
              fVar29 = fStack_1b0;
              if (lVar15 == 0) goto LAB_7ffe9aae5a30;
              cVar6 = FUN_7ffe9abc2210(lVar15,0x4e3,&lStack_158,_DAT_7ffe9c969330);
              if ((cVar6 == '\0') && ((char)uVar11 != '\0')) {
                uVar12 = *(undefined4 *)(puVar4 + 0x34);
                lVar15 = func_0x7ffe99940040(_DAT_7ffe9c95fc00);
                uVar11 = uStack_174;
                FUN_7ffe9a7993a0(lVar15,uStack_174 & 0xff,uVar12,0);
                lStack_158 = lVar15;
                lVar15 = (**(code **)(*plVar16 + 0x1c8))(plVar16,*(undefined8 *)(*plVar16 + 0x1d0));
                fVar29 = fStack_1b0;
                if (lVar15 == 0) goto LAB_7ffe9aae5a30;
                FUN_7ffe9a7c26c0(lVar15,lStack_158,0,0);
              }
              if (lStack_158 != 0) {
                func_0x7ffe9a799270(lStack_158,uVar11 & 0xff,0);
              }
            }
            if ((puVar4[0x50] & 2) != 0) {
              fVar29 = fStack_1b0;
              if (((lVar14 == 0) ||
                  (plVar16 = (longlong *)FUN_7ffe9a480070(lVar14,0), fVar29 = fStack_1b0,
                  plVar16 == (longlong *)0x0)) ||
                 (lVar15 = (**(code **)(*plVar16 + 0x1c8))
                                     (plVar16,*(undefined8 *)(*plVar16 + 0x1d0)),
                 fVar29 = fStack_1b0, lVar15 == 0)) goto LAB_7ffe9aae5a30;
              cVar6 = FUN_7ffe9abc2210(lVar15,0x4e3,&lStack_118,_DAT_7ffe9c969330);
              if (cVar6 != '\0') {
                fVar29 = fStack_1b0;
                if (lStack_118 == 0) goto LAB_7ffe9aae5a30;
                func_0x7ffe9a7992b0(lStack_118,0);
              }
            }
          }
          else if (skillId == 0x275) {
            FUN_7ffe9a822e30(puVar4,0);
          }
          else if (skillId == 0x2d0) {
            if (((lVar14 == 0) ||
                (plVar16 = (longlong *)FUN_7ffe9a480070(lVar14,0), fVar29 = fStack_1b0,
                plVar16 == (longlong *)0x0)) ||
               (lVar15 = (**(code **)(*plVar16 + 0x1c8))(plVar16,*(undefined8 *)(*plVar16 + 0x1d0)),
               fVar29 = fStack_1b0, lVar15 == 0)) goto LAB_7ffe9aae5a30;
            uVar13 = 0;
            FUN_7ffe9a7c2b40(lVar15,0x2d0,skillLv,0,0);
          }
          else {
            if (*(int *)(_DAT_7ffe9c94f0d8 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            cVar6 = FUN_7ffe9a83a450(iVar24,0);
            uVar12 = (undefined4)(in_stack_fffffffffffffe20 >> 0x20);
            if (cVar6 == '\0') {
              if (iVar24 == 0x2b) {
                uVar11 = *(uint *)(puVar4 + 0x34);
                lVar15 = func_0x7ffe99940040(_DAT_7ffe9c8ff608);
                FUN_7ffe9a7a63e0(lVar15,skillLv,uVar11 & 0xff,0);
                fVar29 = fStack_1b0;
                if (lVar14 == 0) goto LAB_7ffe9aae5a30;
                uStack_170 = *(undefined8 *)(lVar14 + 0x50);
                uVar7 = func_0x7ffe9bb9e750(&uStack_170,targetArchetypeType,targetArchetypeId,0);
                fVar29 = fStack_1b0;
                if (lVar15 == 0) goto LAB_7ffe9aae5a30;
                *(undefined1 *)(lVar15 + 0x21) = uVar7;
                plVar16 = (longlong *)FUN_7ffe9a480070(lVar14,0);
                fVar29 = fStack_1b0;
                if ((plVar16 == (longlong *)0x0) ||
                   (lVar17 = (**(code **)(*plVar16 + 0x1c8))
                                       (plVar16,*(undefined8 *)(*plVar16 + 0x1d0)),
                   fVar29 = fStack_1b0, lVar17 == 0)) goto LAB_7ffe9aae5a30;
                FUN_7ffe9a7c1d20(lVar17,lVar15,0,0);
              }
              else if (0.0 < *(float *)(puVar4 + 0x30)) {
                fVar29 = fStack_1b0;
                if (((lVar14 == 0) ||
                    (lVar15 = FUN_7ffe9a4803f0(lVar14,0), fVar29 = fStack_1b0, lVar15 == 0)) ||
                   (*(longlong *)(lVar15 + 0x40) == 0)) goto LAB_7ffe9aae5a30;
                cVar6 = FUN_7ffe9ad8e670(*(longlong *)(lVar15 + 0x40),iVar24,&plStack_120,
                                         _DAT_7ffe9c934418);
                if ((cVar6 != '\0') && (plStack_120 != (longlong *)0x0)) {
                  if ((*(byte *)(_DAT_7ffe9c9585d0 + 0x130) <= *(byte *)(*plStack_120 + 0x130)) &&
                     ((*(longlong *)
                        (*(longlong *)(*plStack_120 + 200) + -8 +
                        (ulonglong)*(byte *)(_DAT_7ffe9c9585d0 + 0x130) * 8) == _DAT_7ffe9c9585d0 &&
                      (plStack_120 != (longlong *)0x0)))) {
                    return;
                  }
                }
                plVar16 = (longlong *)FUN_7ffe9a480070(lVar14,0);
                fVar29 = fStack_1b0;
                if ((plVar16 == (longlong *)0x0) ||
                   (lVar15 = (**(code **)(*plVar16 + 0x1c8))
                                       (plVar16,*(undefined8 *)(*plVar16 + 0x1d0)),
                   fVar29 = fStack_1b0, lVar15 == 0)) goto LAB_7ffe9aae5a30;
                in_stack_fffffffffffffe28 = 0;
                in_stack_fffffffffffffe20 = CONCAT44(uVar12,targetArchetypeId);
                uVar23 = CONCAT44(uVar13,*(undefined4 *)(puVar4 + 0x34));
                FUN_7ffe9a7c22c0(lVar15,iVar24,skillLv,*(undefined4 *)(puVar4 + 0x30),uVar23,
                                 in_stack_fffffffffffffe20,0);
                uVar13 = (undefined4)((ulonglong)uVar23 >> 0x20);
              }
            }
            else if (0.0 <= *(float *)(puVar4 + 0x30)) {
              if (*(int *)(_DAT_7ffe9c94f0d8 + 0xe0) == 0) {
                func_0x7ffe9996d830();
              }
              in_stack_fffffffffffffe20 = 0;
              puVar19 = puVar4;
              FUN_7ffe9a83a560(skillId,skillLv,targetArchetypeType,targetArchetypeId,puVar4,0);
              uVar13 = (undefined4)((ulonglong)puVar19 >> 0x20);
            }
          }
        }
      }
      else {
        if (*(int *)(puVar4 + 0x34) == -1) {
          return;
        }
        if ((lVar14 == 0) || (lVar15 = FUN_7ffe9a4803f0(lVar14,0), fVar29 = fStack_1b0, lVar15 == 0)
           ) goto LAB_7ffe9aae5a30;
        in_stack_fffffffffffffe20 = 0;
        uVar23 = CONCAT44(uVar13,*(undefined4 *)(puVar4 + 0x30));
        FUN_7ffe9a7c2360(lVar15,iVar24,skillLv,*(undefined4 *)(puVar4 + 0x34),uVar23,0);
        uVar13 = (undefined4)((ulonglong)uVar23 >> 0x20);
      }
    }
  }
  uVar12 = (undefined4)(in_stack_fffffffffffffe20 >> 0x20);
  fVar29 = fStack_1b0;
  iStack_138 = iVar24;
  if (iVar24 < 0x342) {
    if (iVar24 < 0x28d) {
      if (iVar24 < 0x8f) {
        if (iVar24 == 0x10) goto LAB_7ffe9aae5845;
        if (iVar24 == 0x8e) {
LAB_7ffe9aae591c:
          if (0 < *(short *)(puVar4 + 0x2c)) {
            lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
            sVar1 = *(short *)(puVar4 + 0x2c);
            fVar29 = fStack_1b0;
            if ((lVar14 == 0) ||
               (lVar17 = FUN_7ffe9a480940(lVar14,0), fVar29 = fStack_1b0, lVar17 == 0))
            goto LAB_7ffe9aae5a30;
            puVar20 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_1b8,lVar17,0);
            uStack_1a8 = *puVar20;
            fStack_1a0 = *(float *)(puVar20 + 1);
            if (DAT_7ffe9cad9cac == '\0') {
              FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
              DAT_7ffe9cad9cac = '\x01';
            }
            uStack_1b8 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x18);
            fVar29 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x20);
            fVar27 = (float)uStack_1b8 + (float)uStack_1a8;
            fVar28 = (float)((ulonglong)uStack_1b8 >> 0x20) + uStack_1a8._4_4_;
            fStack_1b0 = fVar29 + fStack_1a0;
            uStack_198 = CONCAT44(fVar28,fVar27);
            fStack_190 = fStack_1b0;
            if (lVar15 == 0) goto LAB_7ffe9aae5a30;
            goto LAB_7ffe9aae4860;
          }
        }
      }
      else if (iVar24 == 0x9e) {
        uVar13 = 0;
        func_0x7ffe9a7b7160(*(undefined4 *)(puVar4 + 0x50),aiStack_168,&supportData,auStack_178,0);
        uVar7 = supportData._0_1_;
        fVar29 = fStack_1b0;
        if (aiStack_168[0] == 0x8e) {
          if (((lVar14 == 0) ||
              (plVar18 = (longlong *)FUN_7ffe9a480070(lVar14,0), fVar29 = fStack_1b0,
              plVar18 == (longlong *)0x0)) ||
             (lVar15 = (**(code **)(*plVar18 + 0x1c8))(plVar18,*(undefined8 *)(*plVar18 + 0x1d0)),
             fVar29 = fStack_1b0, lVar15 == 0)) goto LAB_7ffe9aae5a8d;
          FUN_7ffe9a7c22c0(lVar15,aiStack_168[0],supportData._0_1_,*(undefined4 *)(puVar4 + 0x30),
                           CONCAT44(uVar13,*(undefined4 *)(puVar4 + 0x34)),
                           CONCAT44(uVar12,targetArchetypeId),0);
          if (*(short *)(puVar4 + 0x2c) < 1) goto LAB_7ffe9aae4f3c;
          lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
          sVar1 = *(short *)(puVar4 + 0x2c);
          lVar17 = FUN_7ffe9a480940(lVar14,0);
          fVar29 = fStack_1b0;
          if (lVar17 == 0) goto LAB_7ffe9aae5a8d;
          puVar20 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_1b8,lVar17,0);
          uStack_1a8 = *puVar20;
          fStack_1a0 = *(float *)(puVar20 + 1);
          if (DAT_7ffe9cad9cac == '\0') {
            FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
            DAT_7ffe9cad9cac = '\x01';
          }
          uVar23 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x18);
          fVar29 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x20);
          fVar27 = (float)uStack_1a8 + (float)uVar23;
          fVar28 = (float)((ulonglong)uVar23 >> 0x20) + uStack_1a8._4_4_;
          fStack_1b0 = fVar29 + fStack_1a0;
          uStack_198 = CONCAT44(fVar28,fVar27);
          fStack_190 = fStack_1b0;
          goto joined_r0x7ffe9aae5773;
        }
        if (aiStack_168[0] == 0x109) {
          if (((lVar14 != 0) &&
              (lVar15 = FUN_7ffe9a4803f0(lVar14,0), fVar29 = fStack_1b0, lVar15 != 0)) &&
             (*(longlong *)(lVar15 + 0x40) != 0)) {
            cVar6 = FUN_7ffe9ad5f0a0(*(longlong *)(lVar15 + 0x40),0x109,_DAT_7ffe9c9341c8);
            if (cVar6 != '\0') goto LAB_7ffe9aae4f3c;
            if (0.0 < *(float *)(puVar4 + 0x30)) {
              plVar18 = (longlong *)FUN_7ffe9a480070(lVar14,0);
              fVar29 = fStack_1b0;
              if ((plVar18 == (longlong *)0x0) ||
                 (lVar15 = (**(code **)(*plVar18 + 0x1c8))
                                     (plVar18,*(undefined8 *)(*plVar18 + 0x1d0)),
                 fVar29 = fStack_1b0, lVar15 == 0)) goto LAB_7ffe9aae5a8d;
              FUN_7ffe9a7c22c0(lVar15,0x109,supportData._0_1_,*(undefined4 *)(puVar4 + 0x30),
                               CONCAT44(uVar13,*(undefined4 *)(puVar4 + 0x34)),
                               CONCAT44(uVar12,targetArchetypeId),0);
            }
            lVar15 = FUN_7ffe9a4803f0(lVar14,0);
            fVar29 = fStack_1b0;
            if ((lVar15 != 0) && (*(longlong *)(lVar15 + 0x50) != 0)) {
              cVar6 = FUN_7ffe9ad8e670(*(longlong *)(lVar15 + 0x50),0x109,&plStack_e0,
                                       _DAT_7ffe9c934418);
              if ((cVar6 != '\0') && (plStack_e0 != (longlong *)0x0)) {
                if (((*(byte *)(_DAT_7ffe9c91ac20 + 0x130) <= *(byte *)(*plStack_e0 + 0x130)) &&
                    (*(longlong *)
                      (*(longlong *)(*plStack_e0 + 200) + -8 +
                      (ulonglong)*(byte *)(_DAT_7ffe9c91ac20 + 0x130) * 8) == _DAT_7ffe9c91ac20)) &&
                   (plStack_e0 != (longlong *)0x0)) {
                  *(undefined4 *)((longlong)plStack_e0 + 0x3c) = *(undefined4 *)(puVar4 + 0x34);
                }
              }
              goto LAB_7ffe9aae4f3c;
            }
          }
          goto LAB_7ffe9aae5a8d;
        }
        if (aiStack_168[0] == 0x2b) {
          uVar11 = *(uint *)(puVar4 + 0x34);
          lVar15 = func_0x7ffe99940040(_DAT_7ffe9c8ff608);
          FUN_7ffe9a7a63e0(lVar15,uVar7,uVar11 & 0xff,0);
          fVar29 = fStack_1b0;
          if (lVar14 != 0) {
            uStack_170 = *(undefined8 *)(lVar14 + 0x50);
            uVar7 = func_0x7ffe9bb9e750(&uStack_170,targetArchetypeType,targetArchetypeId,0);
            fVar29 = fStack_1b0;
            if (lVar15 != 0) {
              *(undefined1 *)(lVar15 + 0x21) = uVar7;
              plVar18 = (longlong *)FUN_7ffe9a480070(lVar14,0);
              fVar29 = fStack_1b0;
              if ((plVar18 != (longlong *)0x0) &&
                 (lVar17 = (**(code **)(*plVar18 + 0x1c8))
                                     (plVar18,*(undefined8 *)(*plVar18 + 0x1d0)),
                 fVar29 = fStack_1b0, lVar17 != 0)) {
                FUN_7ffe9a7c1d20(lVar17,lVar15,0,0);
                goto LAB_7ffe9aae4f3c;
              }
            }
          }
          goto LAB_7ffe9aae5a8d;
        }
      }
      else {
        if (iVar24 == 0x207) {
          if (((lVar14 != 0) &&
              (lVar15 = FUN_7ffe9a4803f0(lVar14,0), fVar29 = fStack_1b0, lVar15 != 0)) &&
             (*(longlong *)(lVar15 + 0x50) != 0)) {
            cVar6 = FUN_7ffe9ad8e670(*(longlong *)(lVar15 + 0x50),0x207,&plStack_d8,
                                     _DAT_7ffe9c934418);
            if (cVar6 != '\0') {
              fVar29 = fStack_1b0;
              if (plStack_d8 == (longlong *)0x0) goto LAB_7ffe9aae5a30;
              if (((*(byte *)(*plStack_d8 + 0x130) < *(byte *)(_DAT_7ffe9c900a98 + 0x130)) ||
                  (*(longlong *)
                    (*(longlong *)(*plStack_d8 + 200) + -8 +
                    (ulonglong)*(byte *)(_DAT_7ffe9c900a98 + 0x130) * 8) != _DAT_7ffe9c900a98)) ||
                 (plStack_d8 == (longlong *)0x0)) {
                FUN_7ffe9996c950(plStack_d8);
                pcVar3 = (code *)swi(3);
                (*pcVar3)();
                return;
              }
              func_0x7ffe999c3290(plStack_d8,*(undefined4 *)(puVar4 + 0x34),0);
            }
            goto LAB_7ffe9aae4f3c;
          }
          goto LAB_7ffe9aae5a30;
        }
        bVar25 = iVar24 == 0x28c;
LAB_7ffe9aae4f27:
        if (bVar25) goto LAB_7ffe9aae5845;
      }
    }
    else if (iVar24 < 0x2a8) {
      if (iVar24 == 0x2a5) {
        if (0 < *(int *)(puVar4 + 0x28)) {
          if ((lVar14 != 0) &&
             (lVar15 = FUN_7ffe9a47f400(lVar14,0), fVar29 = fStack_1b0, lVar15 != 0)) {
            FUN_7ffe9a6fbaa0(lVar15,0xc9,*(undefined4 *)(puVar4 + 0x28),0);
            goto LAB_7ffe9aae4f3c;
          }
          goto LAB_7ffe9aae5a8d;
        }
      }
      else if (iVar24 == 0x2a7) {
        if ((lVar14 == 0) || (lVar15 = FUN_7ffe9a4803f0(lVar14,0), fVar29 = fStack_1b0, lVar15 == 0)
           ) goto LAB_7ffe9aae5a8d;
        FUN_7ffe9a7c2b40(lVar15,0x2a7,skillLv,0,0);
        if (*(int *)(puVar4 + 0x28) < 1) goto LAB_7ffe9aae4f3c;
        lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
        uVar13 = *(undefined4 *)(puVar4 + 0x28);
        lVar17 = FUN_7ffe9a480940(lVar14,0);
        fVar29 = fStack_1b0;
        if (lVar17 == 0) goto LAB_7ffe9aae5a8d;
        puVar20 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_1b8,lVar17,0);
        uStack_1a8 = *puVar20;
        fStack_1a0 = *(float *)(puVar20 + 1);
        if (DAT_7ffe9cad9cac == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
          DAT_7ffe9cad9cac = '\x01';
        }
        uStack_1b8 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x18);
        fVar29 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x20);
        fStack_190 = fStack_1a0 + fVar29;
        uStack_198 = CONCAT44(uStack_1a8._4_4_ + (float)((ulonglong)uStack_1b8 >> 0x20),
                              (float)uStack_1a8 + (float)uStack_1b8);
        if (lVar15 == 0) goto LAB_7ffe9aae5a8d;
        goto LAB_7ffe9aae444a;
      }
    }
    else {
      if (iVar24 != 0x2c4) {
        if (iVar24 == 0x323) goto LAB_7ffe9aae591c;
        bVar25 = iVar24 == 0x341;
        goto LAB_7ffe9aae4f27;
      }
LAB_7ffe9aae5845:
      if (0 < *(int *)(puVar4 + 0x28)) {
        lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
        uVar13 = *(undefined4 *)(puVar4 + 0x28);
        fVar29 = fStack_1b0;
        if ((lVar14 == 0) || (lVar17 = FUN_7ffe9a480940(lVar14,0), fVar29 = fStack_1b0, lVar17 == 0)
           ) goto LAB_7ffe9aae5a30;
        puVar20 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_1b8,lVar17,0);
        uStack_1a8 = *puVar20;
        fStack_1a0 = *(float *)(puVar20 + 1);
        if (DAT_7ffe9cad9cac == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
          DAT_7ffe9cad9cac = '\x01';
        }
        uStack_1b8 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x18);
        fStack_1b0 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x20);
        fStack_190 = fStack_1b0 + fStack_1a0;
        uStack_198 = CONCAT44((float)((ulonglong)uStack_1b8 >> 0x20) + uStack_1a8._4_4_,
                              (float)uStack_1b8 + (float)uStack_1a8);
LAB_7ffe9aae443b:
        fVar29 = fStack_1b0;
        if (lVar15 == 0) goto LAB_7ffe9aae5a30;
LAB_7ffe9aae444a:
        uStack_1b8 = uStack_198;
        fStack_1b0 = fStack_190;
        FUN_7ffe99caa840(lVar15,uVar13,&uStack_1b8,0);
        goto LAB_7ffe9aae4f3c;
      }
    }
  }
  else if (iVar24 < 0x3b0) {
    if (iVar24 < 0x368) {
      if (iVar24 == 0x347) goto LAB_7ffe9aae5845;
      if (iVar24 != 0x367) goto LAB_7ffe9aae4f2d;
      if ((lVar14 == 0) || (lVar15 = FUN_7ffe9a480590(lVar14,0), fVar29 = fStack_1b0, lVar15 == 0))
      goto LAB_7ffe9aae5a30;
      iVar10 = FUN_7ffe9a7fd580(lVar15,0x367,1,0);
      if (iVar10 < 1) goto LAB_7ffe9aae4f3c;
      plVar18 = (longlong *)FUN_7ffe9a480070(lVar14,0);
      fVar29 = fStack_1b0;
      if (((plVar18 == (longlong *)0x0) ||
          (lVar15 = (**(code **)(*plVar18 + 0x1c8))(plVar18,*(undefined8 *)(*plVar18 + 0x1d0)),
          fVar29 = fStack_1b0, lVar15 == 0)) || (*(longlong *)(lVar15 + 0x40) == 0))
      goto LAB_7ffe9aae5a30;
      cVar6 = FUN_7ffe9ad5f0a0(*(longlong *)(lVar15 + 0x40),0x367,_DAT_7ffe9c9341c8);
      if (cVar6 != '\0') goto LAB_7ffe9aae4f3c;
      lVar15 = FUN_7ffe9a7f64f0(*(undefined4 *)(puVar4 + 0x34),0);
      cVar6 = FUN_7ffe9a8fec40(lVar15,0,0);
      if (cVar6 != '\0') goto LAB_7ffe9aae4f3c;
      uVar23 = FUN_7ffe9a47fe30(lVar14,0);
      fVar29 = fStack_1b0;
      if (lVar15 == 0) goto LAB_7ffe9aae5a30;
      FUN_7ffe9a8fe290(lVar15,uVar23,skillLv,0);
      lVar17 = FUN_7ffe9a47fe30(lVar14,0);
      fVar29 = fStack_1b0;
      if (lVar17 == 0) goto LAB_7ffe9aae5a30;
      plVar18 = *(longlong **)(lVar17 + 0x30);
      lVar17 = FUN_7ffe9a47fe30(lVar14,0);
      fVar29 = fStack_1b0;
      if (lVar17 == 0) goto LAB_7ffe9aae5a30;
      if (*(longlong **)(lVar17 + 0x30) == (longlong *)0x0) {
LAB_7ffe9aae5204:
        lVar17 = FUN_7ffe9a47fe30(lVar14,0);
        uVar23 = _DAT_7ffe9c8f7560;
        fVar29 = fStack_1b0;
        if (lVar17 == 0) goto LAB_7ffe9aae5a30;
        lVar17 = func_0x7ffe997430a0(*(undefined8 *)(lVar17 + 0x30),_DAT_7ffe9c8f7560);
        if (lVar17 == 0) goto LAB_7ffe9aae4f3c;
        lVar17 = FUN_7ffe99744bb0(plVar18,uVar23);
        fVar29 = fStack_1b0;
        if (lVar17 == 0) goto LAB_7ffe9aae5a30;
        uVar23 = FUN_7ffe99744bb0(plVar18,_DAT_7ffe9c8f7560);
        cVar6 = FUN_7ffe9a43ec50(uVar23,lVar15,0);
      }
      else {
        lVar17 = **(longlong **)(lVar17 + 0x30);
        if ((*(byte *)(lVar17 + 0x130) < *(byte *)(_DAT_7ffe9c922a40 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(lVar17 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c922a40 + 0x130) * 8
             ) != _DAT_7ffe9c922a40)) goto LAB_7ffe9aae5204;
        if (plVar18 == (longlong *)0x0) goto LAB_7ffe9aae5a30;
        if ((*(byte *)(*plVar18 + 0x130) < *(byte *)(_DAT_7ffe9c922a40 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar18 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c922a40 + 0x130) * 8) != _DAT_7ffe9c922a40)) {
          FUN_7ffe9996c950(plVar18,_DAT_7ffe9c922a40);
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
        uVar23 = FUN_7ffe99744bb0(plVar18,_DAT_7ffe9c922a40);
        cVar6 = FUN_7ffe9a46dd40(uVar23,lVar15,0);
      }
      if (cVar6 != '\0') {
        plVar18 = (longlong *)FUN_7ffe9a480070(lVar14,0);
        fVar29 = fStack_1b0;
        if (plVar18 != (longlong *)0x0) {
          lVar15 = (**(code **)(*plVar18 + 0x1c8))(plVar18,*(undefined8 *)(*plVar18 + 0x1d0));
          uVar13 = *(undefined4 *)(puVar4 + 0x30);
          uVar23 = func_0x7ffe99940040(_DAT_7ffe9c8f5638);
          FUN_7ffe9a779620(uVar23,skillLv,uVar13,0);
          fVar29 = fStack_1b0;
          if (lVar15 != 0) {
            FUN_7ffe9a7c26c0(lVar15,uVar23,0,0);
            goto LAB_7ffe9aae4f3c;
          }
        }
LAB_7ffe9aae5a30:
        fStack_1b0 = fVar29;
        FUN_7ffe9996d7a0();
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
      goto LAB_7ffe9aae4f3c;
    }
    if (iVar24 != 0x36d) {
      bVar25 = (iVar24 - 0x3abU & 0xfffffffb) == 0;
      goto LAB_7ffe9aae4f27;
    }
    if (0 < *(short *)(puVar4 + 0x2c)) {
      lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
      sVar1 = *(short *)(puVar4 + 0x2c);
      fVar29 = fStack_1b0;
      if ((lVar14 == 0) || (lVar17 = FUN_7ffe9a480940(lVar14,0), fVar29 = fStack_1b0, lVar17 == 0))
      goto LAB_7ffe9aae5a8d;
      puVar20 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_1b8,lVar17,0);
      uStack_1a8 = *puVar20;
      fStack_1a0 = *(float *)(puVar20 + 1);
      if (DAT_7ffe9cad9cac == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
        DAT_7ffe9cad9cac = '\x01';
      }
      uVar23 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x18);
      fVar29 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x20);
      fVar27 = (float)uStack_1a8 + (float)uVar23;
      fVar28 = uStack_1a8._4_4_ + (float)((ulonglong)uVar23 >> 0x20);
      fStack_1b0 = fStack_1a0 + fVar29;
      uStack_198 = CONCAT44(fVar28,fVar27);
      fStack_190 = fStack_1b0;
joined_r0x7ffe9aae5773:
      uStack_1b8 = uVar23;
      if (lVar15 == 0) goto LAB_7ffe9aae5a8d;
LAB_7ffe9aae4860:
      uStack_1b8 = CONCAT44(fVar28,fVar27);
      FUN_7ffe99caa960(lVar15,(int)sVar1,&uStack_1b8,0);
      goto LAB_7ffe9aae4f3c;
    }
  }
  else if (iVar24 < 0x410) {
    if (iVar24 == 1000) {
      if (((lVar14 != 0) && (lVar15 = FUN_7ffe9a4803f0(lVar14,0), fVar29 = fStack_1b0, lVar15 != 0))
         && (*(longlong *)(lVar15 + 0x50) != 0)) {
        cVar6 = FUN_7ffe9ad8e670(*(longlong *)(lVar15 + 0x50),1000,&plStack_e8,_DAT_7ffe9c934418);
        if (cVar6 != '\0') {
          fVar29 = fStack_1b0;
          if (plStack_e8 == (longlong *)0x0) goto LAB_7ffe9aae5a30;
          if (((*(byte *)(*plStack_e8 + 0x130) < *(byte *)(_DAT_7ffe9c9467e0 + 0x130)) ||
              (*(longlong *)
                (*(longlong *)(*plStack_e8 + 200) + -8 +
                (ulonglong)*(byte *)(_DAT_7ffe9c9467e0 + 0x130) * 8) != _DAT_7ffe9c9467e0)) ||
             (plStack_e8 == (longlong *)0x0)) {
            FUN_7ffe9996c950(plStack_e8);
            pcVar3 = (code *)swi(3);
            (*pcVar3)();
            return;
          }
          func_0x7ffe9a7a1a00(plStack_e8,*(undefined4 *)(puVar4 + 0x34),0);
        }
        goto LAB_7ffe9aae4f3c;
      }
      goto LAB_7ffe9aae5a30;
    }
    if ((iVar24 == 0x40f) && (*(short *)(puVar4 + 0x2c) == 0)) {
      if ((lVar14 == 0) || (lVar15 = FUN_7ffe9a4803f0(lVar14,0), fVar29 = fStack_1b0, lVar15 == 0))
      goto LAB_7ffe9aae5a8d;
      cVar6 = FUN_7ffe9a7cbb30(lVar15,0x40f,&lStack_128,0);
      if (cVar6 != '\0') {
        fVar29 = fStack_1b0;
        if (lStack_128 == 0) goto LAB_7ffe9aae5a8d;
        uStack_174 = func_0x7ffe9a7a2140(lStack_128,0x14);
        if (0 < (int)uStack_174) {
          lVar15 = FUN_7ffe9a4803f0(lVar14,0);
          fVar29 = fStack_1b0;
          if ((lVar15 == 0) ||
             (FUN_7ffe9a7cbb30(lVar15,0x41f,&uStack_140,0), fVar29 = fStack_1b0, lStack_128 == 0))
          goto LAB_7ffe9aae5a8d;
          uVar7 = *(undefined1 *)(lStack_128 + 0x10);
          uVar21 = FUN_7ffe9a480070(lVar14,0);
          uVar23 = uStack_140;
          uVar22 = func_0x7ffe99940040(_DAT_7ffe9c9477f0);
          FUN_7ffe9a7a1e30(uVar22,uVar7,uStack_174,uVar21,uVar23,0);
          uStack_140 = uVar22;
          lVar15 = FUN_7ffe9a4803f0(lVar14,0);
          fVar29 = fStack_1b0;
          if (lVar15 == 0) goto LAB_7ffe9aae5a8d;
          FUN_7ffe9a7c26c0(lVar15,uStack_140,0,0);
          iVar24 = iStack_138;
        }
      }
      lVar15 = FUN_7ffe9a4803f0(lVar14,0);
      fVar29 = fStack_1b0;
      if (lVar15 != 0) {
        FUN_7ffe9a7cafa0(lVar15,0x40f,0);
        lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
        fVar29 = fStack_1b0;
        if (lVar15 != 0) {
          lVar15 = FUN_7ffe9a29dd60(lVar15,0);
          lVar17 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
          fVar29 = fStack_1b0;
          if (((lVar17 != 0) &&
              (lVar17 = FUN_7ffe9a29dd60(lVar17,0), fVar29 = fStack_1b0, lVar17 != 0)) &&
             (lVar15 != 0)) {
            FUN_7ffe9a4cea50(lVar15,*(undefined4 *)(lVar17 + 0x40),_DAT_7ffe9c049b70,
                             _DAT_7ffe9c049b4c,0,0);
            lVar15 = FUN_7ffe9a4808f0(lVar14,0);
            fVar29 = fStack_1b0;
            if (lVar15 != 0) {
              lVar15 = FUN_7ffe9ab9bd00(lVar15,_DAT_7ffe9c8f3660);
              if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                func_0x7ffe9996d830();
              }
              cVar6 = FUN_7ffe9bda2160(lVar15,0,0);
              if (cVar6 != '\0') {
                fVar29 = fStack_1b0;
                if ((lVar15 == 0) ||
                   (lVar15 = FUN_7ffe9bd90360(lVar15,0), fVar29 = fStack_1b0, lVar15 == 0))
                goto LAB_7ffe9aae5a8d;
                while( true ) {
                  uVar11 = (uint)plVar18;
                  if ((int)*(uint *)(lVar15 + 0x18) <= (int)uVar11) break;
                  if (*(uint *)(lVar15 + 0x18) <= uVar11) {
                    FUN_7ffe9996d790();
                    pcVar3 = (code *)swi(3);
                    (*pcVar3)();
                    return;
                  }
                  lVar17 = *(longlong *)(lVar15 + 0x20 + (longlong)(int)uVar11 * 8);
                  fVar29 = fStack_1b0;
                  if (lVar17 == 0) goto LAB_7ffe9aae5a8d;
                  FUN_7ffe9bd86290(lVar17,_DAT_7ffe9c928e30,uVar2);
                  plVar18 = (longlong *)(ulonglong)(uVar11 + 1);
                }
              }
              lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
              uVar23 = FUN_7ffe9a4808f0(lVar14,0);
              fVar29 = fStack_1b0;
              if (lVar15 != 0) {
                FUN_7ffe9a8d5ed0(lVar15,uVar23,0x40f,0,2,0,0);
                goto LAB_7ffe9aae4f3c;
              }
            }
          }
        }
      }
      goto LAB_7ffe9aae5a8d;
    }
  }
  else {
    if (iVar24 == 0x428) {
      if (lVar14 == 0) goto LAB_7ffe9aae5a30;
      iVar9 = FUN_7ffe9a47fef0(lVar14,0);
      iVar10 = *(int *)(puVar4 + 0x34);
      if (targetArchetypeId == iVar9) {
        if (-1 < iVar10) {
          lVar15 = FUN_7ffe9a4803f0(lVar14,0);
          fVar29 = fStack_1b0;
          if ((lVar15 == 0) || (*(longlong *)(lVar15 + 0x40) == 0)) goto LAB_7ffe9aae5a30;
          cVar6 = FUN_7ffe9ad8e670(*(longlong *)(lVar15 + 0x40),0x427,&plStack_160,_DAT_7ffe9c934418
                                  );
          if (cVar6 == '\0') {
            lVar15 = FUN_7ffe9a480590(lVar14,0);
            fVar29 = fStack_1b0;
            if (lVar15 == 0) goto LAB_7ffe9aae5a30;
            uVar7 = FUN_7ffe9a7fd580(lVar15,0x427,1,0);
            plVar18 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c9500f0);
            FUN_7ffe9a7a3f20(plVar18,uVar7,0);
            plStack_160 = plVar18;
            lVar15 = FUN_7ffe9a4803f0(lVar14,0);
            fVar29 = fStack_1b0;
            if (lVar15 == 0) goto LAB_7ffe9aae5a30;
            FUN_7ffe9a7c26c0(lVar15,plStack_160,0,0);
          }
          while (fVar29 = fStack_1b0, plStack_160 != (longlong *)0x0) {
            iVar10 = func_0x7ffe9a7a2140(plStack_160,0x14);
            if (*(int *)(puVar4 + 0x34) <= iVar10) goto LAB_7ffe9aae4f3c;
            fVar29 = fStack_1b0;
            if (plStack_160 == (longlong *)0x0) break;
            if (((*(byte *)(*plStack_160 + 0x130) < *(byte *)(_DAT_7ffe9c9500f0 + 0x130)) ||
                (*(longlong *)
                  (*(longlong *)(*plStack_160 + 200) + -8 +
                  (ulonglong)*(byte *)(_DAT_7ffe9c9500f0 + 0x130) * 8) != _DAT_7ffe9c9500f0)) ||
               (plStack_160 == (longlong *)0x0)) {
              FUN_7ffe9996c950(plStack_160);
              pcVar3 = (code *)swi(3);
              (*pcVar3)();
              return;
            }
            (**(code **)(*plStack_160 + 0x2a8))(plStack_160,*(undefined8 *)(*plStack_160 + 0x2b0));
          }
          goto LAB_7ffe9aae5a30;
        }
      }
      else {
        uVar23 = func_0x7ffe99940040(_DAT_7ffe9c8f9db8);
        FUN_7ffe9a78b0d0(uVar23,skillLv,iVar10,0);
        lVar15 = FUN_7ffe9a4803f0(lVar14,0);
        fVar29 = fStack_1b0;
        if (lVar15 == 0) goto LAB_7ffe9aae5a30;
        FUN_7ffe9a7c1d20(lVar15,uVar23,0,0);
      }
      goto LAB_7ffe9aae4f3c;
    }
    if (iVar24 == 0x445) {
      if (*(int *)(puVar4 + 0x28) != 0) {
        if (*(int *)(puVar4 + 0x28) < 1) {
          lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
          iVar10 = *(int *)(puVar4 + 0x28);
          fVar29 = fStack_1b0;
          if ((lVar14 != 0) &&
             (lVar17 = FUN_7ffe9a480940(lVar14,0), fVar29 = fStack_1b0, lVar17 != 0)) {
            puVar20 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_1b8,lVar17,0);
            uStack_1a8 = *puVar20;
            fStack_1a0 = *(float *)(puVar20 + 1);
            if (DAT_7ffe9cad9cac == '\0') {
              FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
              DAT_7ffe9cad9cac = '\x01';
            }
            uStack_1b8 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x18);
            fVar29 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x20);
            fStack_1b0 = fStack_1a0 + fVar29;
            uStack_198 = CONCAT44(uStack_1a8._4_4_ + (float)((ulonglong)uStack_1b8 >> 0x20),
                                  (float)uStack_1a8 + (float)uStack_1b8);
            fStack_190 = fStack_1b0;
            if (lVar15 != 0) {
              uStack_1b8 = uStack_198;
              FUN_7ffe99caa180(lVar15,1,-iVar10,&uStack_1b8,CONCAT44(uVar13,uVar2),0);
              goto LAB_7ffe9aae4f3c;
            }
          }
          goto LAB_7ffe9aae5a30;
        }
        lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
        uVar13 = *(undefined4 *)(puVar4 + 0x28);
        fVar29 = fStack_1b0;
        if ((lVar14 == 0) || (lVar17 = FUN_7ffe9a480940(lVar14,0), fVar29 = fStack_1b0, lVar17 == 0)
           ) goto LAB_7ffe9aae5a30;
        puVar20 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_1b8,lVar17,0);
        uStack_1a8 = *puVar20;
        fStack_1a0 = *(float *)(puVar20 + 1);
        if (DAT_7ffe9cad9cac == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
          DAT_7ffe9cad9cac = '\x01';
        }
        uStack_1b8 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x18);
        fStack_1b0 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x20);
        fStack_190 = fStack_1a0 + fStack_1b0;
        uStack_198 = CONCAT44(uStack_1a8._4_4_ + (float)((ulonglong)uStack_1b8 >> 0x20),
                              (float)uStack_1a8 + (float)uStack_1b8);
        goto LAB_7ffe9aae443b;
      }
    }
    else {
      switch(iVar24) {
      case 0x466:
        if (0 < *(int *)(puVar4 + 0x28)) {
          lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
          uVar2 = *(undefined4 *)(puVar4 + 0x28);
          fVar29 = fStack_1b0;
          if ((lVar14 == 0) ||
             (lVar17 = FUN_7ffe9a480940(lVar14,0), fVar29 = fStack_1b0, lVar17 == 0))
          goto LAB_7ffe9aae5a8d;
          puVar20 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_1b8,lVar17,0);
          uVar23 = *puVar20;
          fStack_1b0 = *(float *)(puVar20 + 1);
          puVar20 = (undefined8 *)FUN_7ffe99a14dc0(&uStack_188,0);
          fStack_180 = *(float *)(puVar20 + 1);
          fStack_1a0 = fStack_1b0 + fStack_180;
          uStack_1a8 = CONCAT44((float)((ulonglong)uVar23 >> 0x20) +
                                (float)((ulonglong)*puVar20 >> 0x20),(float)uVar23 + (float)*puVar20
                               );
          uStack_1b8 = uVar23;
          fVar29 = fStack_1b0;
          if (lVar15 == 0) goto LAB_7ffe9aae5a8d;
          uStack_1b8 = uStack_1a8;
          fStack_1b0 = fStack_1a0;
          FUN_7ffe99caa840(lVar15,uVar2,&uStack_1b8,0);
        }
        uVar23 = uRam00007ffe9c954a58;
        if (0 < *(int *)(puVar4 + 0x34)) {
          if (*(int *)(_DAT_7ffe9c96ec48 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          uVar23 = FUN_7ffe9b52cc00(uVar23,0);
          uStack_174 = *(uint *)(puVar4 + 0x34);
          uVar21 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,&uStack_174);
          if (*(int *)(_DAT_7ffe9c8f82e8 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          cVar6 = FUN_7ffe9b5412f0(uVar23,uVar21,0);
          if (cVar6 != '\0') {
            uVar2 = *(undefined4 *)(puVar4 + 0x34);
            if (*(int *)(_DAT_7ffe9c92dfe0 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            uVar23 = FUN_7ffe9a4db1f0(uVar2,0);
            uVar12 = FUN_7ffe9a4daf00(uVar2,(int)uVar23,0);
            fVar29 = fStack_1b0;
            if (lVar14 == 0) goto LAB_7ffe9aae5a8d;
            plVar18 = (longlong *)FUN_7ffe9a47fe30(lVar14,0);
            uVar21 = FUN_7ffe9a4808f0(lVar14,0);
            fVar29 = fStack_1b0;
            if (plVar18 == (longlong *)0x0) goto LAB_7ffe9aae5a8d;
            cVar6 = (**(code **)(*plVar18 + 0x228))
                              (plVar18,uVar21,uVar2,uVar23,CONCAT44(uVar13,uVar12),
                               in_stack_fffffffffffffe20 & 0xffffffff00000000,
                               in_stack_fffffffffffffe28 & 0xffffffffffffff00,0,
                               *(undefined8 *)(*plVar18 + 0x230));
            if (cVar6 != '\0') {
              plVar18 = (longlong *)FUN_7ffe9a47fe30(lVar14,0);
              fVar29 = fStack_1b0;
              if (plVar18 != (longlong *)0x0) {
                (**(code **)(*plVar18 + 0x358))
                          (plVar18,uVar2,uVar23,0,*(undefined8 *)(*plVar18 + 0x360));
                plVar18 = (longlong *)FUN_7ffe9a47fe30(lVar14,0);
                fVar29 = fStack_1b0;
                if (plVar18 != (longlong *)0x0) {
                  (**(code **)(*plVar18 + 0x348))
                            (plVar18,uVar2,uVar23,0,*(undefined8 *)(*plVar18 + 0x350));
                  goto LAB_7ffe9aae4f3c;
                }
              }
              goto LAB_7ffe9aae5a8d;
            }
            goto LAB_7ffe9aae4f3c;
          }
        }
        break;
      case 0x468:
        if ((lVar14 != 0) && (lVar15 = FUN_7ffe9a47f400(lVar14,0), fVar29 = fStack_1b0, lVar15 != 0)
           ) {
          FUN_7ffe9a6fbd70(lVar15,(*(int *)(puVar4 + 0x34) < 1) - 1,
                           (*(int *)(puVar4 + 0x38) < 1) - 1,0);
          lVar15 = FUN_7ffe9a47fe30(lVar14,0);
          fVar29 = fStack_1b0;
          if (lVar15 != 0) {
            lVar15 = func_0x7ffe997430a0(*(undefined8 *)(lVar15 + 0x30),_DAT_7ffe9c922a40);
            if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            cVar6 = FUN_7ffe9bda2160(lVar15,0,0);
            if (cVar6 != '\0') {
              fVar29 = fStack_1b0;
              if (lVar15 == 0) goto LAB_7ffe9aae5a8d;
              FUN_7ffe9a45c7a0(lVar15,0);
            }
            goto LAB_7ffe9aae4f3c;
          }
        }
        goto LAB_7ffe9aae5a8d;
      case 0x46a:
        if (0 < *(short *)(puVar4 + 0x2c)) {
          lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
          sVar1 = *(short *)(puVar4 + 0x2c);
          fVar29 = fStack_1b0;
          if ((lVar14 == 0) ||
             (lVar17 = FUN_7ffe9a480940(lVar14,0), fVar29 = fStack_1b0, lVar17 == 0))
          goto LAB_7ffe9aae5a8d;
          puVar20 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_1b8,lVar17,0);
          uVar23 = *puVar20;
          fStack_1b0 = *(float *)(puVar20 + 1);
          puVar20 = (undefined8 *)FUN_7ffe99a14dc0(&uStack_188,0);
          fStack_180 = *(float *)(puVar20 + 1);
          fVar27 = (float)uVar23 + (float)*puVar20;
          fVar28 = (float)((ulonglong)uVar23 >> 0x20) + (float)((ulonglong)*puVar20 >> 0x20);
          fStack_1a0 = fStack_1b0 + fStack_180;
          uStack_1a8 = CONCAT44(fVar28,fVar27);
          fVar29 = fStack_1b0;
          fStack_1b0 = fStack_1a0;
          goto joined_r0x7ffe9aae5773;
        }
        break;
      case 0x46b:
        if (*(int *)(puVar4 + 0x50) == 8) {
          if (lVar14 != 0) {
            lVar15 = *(longlong *)(lVar14 + 0x70);
            uVar13 = FUN_7ffe9a47fef0(lVar14,0);
            fVar29 = fStack_1b0;
            if (lVar15 != 0) {
              uVar30 = 0;
              cVar6 = FUN_7ffe99a231d0(lVar15,0xf,uVar13,&plStack_f0,0);
              if (cVar6 == '\0') goto LAB_7ffe9aae4f3c;
              lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
              fVar29 = fStack_1b0;
              if ((lVar15 != 0) &&
                 (FUN_7ffe9a8d8390(lVar15,0x46b,0,0xf,uVar30 & 0xffffffffffffff00,0),
                 fVar29 = fStack_1b0, plStack_f0 != (longlong *)0x0)) {
                bVar8 = *(byte *)(_DAT_7ffe9c95dac8 + 0x130);
                if ((bVar8 <= *(byte *)(*plStack_f0 + 0x130)) &&
                   ((lVar15 = *(longlong *)(*plStack_f0 + 200),
                    *(longlong *)(lVar15 + -8 + (ulonglong)bVar8 * 8) == _DAT_7ffe9c95dac8 &&
                    (plStack_f0 != (longlong *)0x0)))) {
                  if (*(longlong *)(lVar15 + -8 + (ulonglong)bVar8 * 8) == _DAT_7ffe9c95dac8) {
                    plVar18 = plStack_f0;
                  }
                  FUN_7ffe9a4f2e30(plVar18,0,0);
                  lVar15 = FUN_7ffe9a480070(lVar14,0);
                  fVar29 = fStack_1b0;
                  if ((lVar15 != 0) &&
                     (lVar15 = func_0x7ffe99742fe0(9,lVar15), fVar29 = fStack_1b0, lVar15 != 0)) {
                    FUN_7ffe9a7cbb30(lVar15,0x46b,&uStack_d0,0);
                    if (0 < *(int *)(puVar4 + 0x28)) {
                      lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
                      uVar13 = *(undefined4 *)(puVar4 + 0x28);
                      lVar17 = FUN_7ffe9a480940(lVar14,0);
                      fVar29 = fStack_1b0;
                      if (lVar17 == 0) goto LAB_7ffe9aae5a8d;
                      puVar20 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_1b8,lVar17,0);
                      uVar23 = *puVar20;
                      fStack_1b0 = *(float *)(puVar20 + 1);
                      puVar20 = (undefined8 *)FUN_7ffe99a14dc0(&uStack_188,0);
                      fStack_180 = *(float *)(puVar20 + 1);
                      fStack_1a0 = fStack_1b0 + fStack_180;
                      uStack_1a8 = CONCAT44((float)((ulonglong)uVar23 >> 0x20) +
                                            (float)((ulonglong)*puVar20 >> 0x20),
                                            (float)uVar23 + (float)*puVar20);
                      uStack_1b8 = uVar23;
                      fVar29 = fStack_1b0;
                      if (lVar15 == 0) goto LAB_7ffe9aae5a8d;
                      uStack_1b8 = uStack_1a8;
                      fStack_1b0 = fStack_1a0;
                      FUN_7ffe99caa840(lVar15,uVar13,&uStack_1b8,0);
                    }
                    lVar15 = FUN_7ffe9a480070(lVar14,0);
                    fVar29 = fStack_1b0;
                    if ((lVar15 != 0) &&
                       (lVar15 = func_0x7ffe99742fe0(0xb,lVar15), fVar29 = fStack_1b0, lVar15 != 0))
                    {
                      FUN_7ffe9a4d99d0(lVar15,uVar2,0,0);
                      goto LAB_7ffe9aae4f3c;
                    }
                  }
                }
              }
            }
          }
          goto LAB_7ffe9aae5a8d;
        }
        if (*(int *)(_DAT_7ffe9c941198 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        FUN_7ffe9a7de630(0);
      }
    }
  }
LAB_7ffe9aae4f2d:
  fVar29 = fStack_1b0;
  if (lVar14 == 0) {
LAB_7ffe9aae5a8d:
    fStack_1b0 = fVar29;
    FUN_7ffe9996d7a0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
LAB_7ffe9aae4f3c:
  uStack_170 = *(undefined8 *)(lVar14 + 0x50);
  cVar6 = func_0x7ffe9bb9e750(&uStack_170,targetArchetypeType,targetArchetypeId,0);
  if (cVar6 == '\0') {
    uVar23 = FUN_7ffe9a480070(lVar14,0);
    if (*(int *)(_DAT_7ffe9c93ce00 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    FUN_7ffe9a7b8f30(iVar24,puVar4,uVar23,0);
  }
  else {
    uVar23 = FUN_7ffe9a480070(lVar14,0);
    if (*(int *)(_DAT_7ffe9c93ce00 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    FUN_7ffe9a7b8d30(iVar24,puVar4,uVar23,0);
  }
  return;
}

