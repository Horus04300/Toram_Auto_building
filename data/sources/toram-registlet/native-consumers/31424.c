
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SummonDemonicSpecialAttack_calcPlayerToMobDamage
               (undefined *thisObject,undefined *playerAction,undefined *mobAction,
               undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  byte bVar5;
  undefined1 uVar6;
  char cVar7;
  undefined4 uVar8;
  uint uVar9;
  int iVar10;
  int iVar11;
  undefined4 uVar12;
  longlong *plVar13;
  longlong lVar14;
  longlong lVar15;
  undefined *puVar16;
  undefined8 uVar17;
  undefined8 uVar18;
  longlong *plVar19;
  longlong lVar20;
  int iVar21;
  int iVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  undefined8 extraout_XMM0_Qb;
  undefined1 auVar29 [16];
  char acStackX_10 [8];
  undefined4 *resistReactionType;
  undefined1 uStack_d8;
  undefined1 uStack_d7;
  undefined1 auStack_d6 [2];
  int iStack_d4;
  int iStack_d0;
  longlong *plStack_c8;
  float fStack_c0;
  int iStack_bc;
  undefined4 uStack_b8;
  longlong *plStack_b0;
  undefined4 uStack_a8;
  undefined4 uStack_a4;
  undefined4 auStack_a0 [2];
  longlong *plStack_98;
  longlong alStack_90 [13];
  
  if (DAT_7ffe9cadf705 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c920098);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1e88);
    FUN_7ffe9996d590(&DAT_7ffe9c91aa80);
    FUN_7ffe9996d590(&DAT_7ffe9c923808);
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c913488);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c923468);
    FUN_7ffe9996d590(&DAT_7ffe9c94aa68);
    FUN_7ffe9996d590(&DAT_7ffe9c94c0a0);
    DAT_7ffe9cadf705 = '\x01';
  }
  plVar19 = (longlong *)0x0;
  plStack_98 = (longlong *)0x0;
  plStack_b0 = (longlong *)0x0;
  acStackX_10[0] = '\0';
  iVar22 = 0;
  uStack_a8 = 0;
  fStack_c0 = 0.0;
  auStack_a0[0] = 0;
  uStack_a4 = 0;
  alStack_90[0] = 0;
  if ((playerAction == (undefined *)0x0) ||
     (plVar13 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
     plVar13 == (longlong *)0x0)) goto LAB_7ffe9a816409;
  plVar13 = (longlong *)(**(code **)(*plVar13 + 0x198))(plVar13,*(undefined8 *)(*plVar13 + 0x1a0));
  if (plVar13 == (longlong *)0x0) {
    plStack_c8 = (longlong *)0x0;
  }
  else {
    if ((*(byte *)(*plVar13 + 0x130) < *(byte *)(_DAT_7ffe9c923468 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*plVar13 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c923468 + 0x130) * 8)
        != _DAT_7ffe9c923468)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    plStack_c8 = plVar19;
    if (bVar3) {
      plStack_c8 = plVar13;
    }
  }
  lVar15 = *(longlong *)(thisObject + 0x130);
  iStack_bc = 0;
  auStack_d6[0] = 0;
  uStack_d8 = 0;
  uStack_d7 = 0;
  plVar13 = plVar19;
  if (lVar15 == 0) goto LAB_7ffe9a816409;
  while (uVar9 = (uint)plVar13, (int)uVar9 < *(int *)(lVar15 + 0x18)) {
    if (*(uint *)(lVar15 + 0x18) <= uVar9) goto LAB_7ffe9a816421;
    plVar13 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if ((plVar13 == (longlong *)0x0) ||
       (lVar14 = (**(code **)(*plVar13 + 0x1c8))(plVar13,*(undefined8 *)(*plVar13 + 0x1d0)),
       lVar14 == 0)) goto LAB_7ffe9a816409;
    FUN_7ffe9a7cb960(lVar14);
    plVar13 = (longlong *)(ulonglong)(uVar9 + 1);
  }
  uStack_b8 = 1;
  if ((*(longlong *)(thisObject + 0x120) != 0) && (cVar4 = FUN_7ffe9a5224e0(), cVar4 != '\0')) {
    if ((mobAction == (undefined *)0x0) ||
       (lVar15 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction), lVar15 == 0))
    goto LAB_7ffe9a816409;
    uVar8 = FUN_7ffe99742ec0(9);
    if (*(int *)(_DAT_7ffe9c94c0a0 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    iVar21 = iVar22;
    switch(uVar8) {
    case 1:
      iVar21 = 2;
      break;
    case 2:
      iVar21 = 3;
      break;
    case 3:
      iVar21 = 4;
      break;
    case 4:
      iVar21 = 1;
      break;
    case 5:
      iVar21 = 6;
      break;
    case 6:
      iVar21 = 5;
    }
    *(int *)(thisObject + 0x30) = iVar21;
  }
  plVar13 = plStack_c8;
  if (plStack_c8 == (longlong *)0x0) goto LAB_7ffe9a816409;
  FUN_7ffe9a484e10(plStack_c8);
  PlayerSecondaryStatus_GetCrtConstant((undefined *)plVar13,0,(undefined *)0x0);
  uVar8 = FUN_7ffe9a472c30(plVar13);
  if (*(int *)(thisObject + 0x138) == 2) {
    uVar17 = (**(code **)(*(longlong *)playerAction + 0x298))
                       (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    bVar5 = FUN_7ffe9a4acfc0(thisObject,uVar17,mobAction,0);
  }
  else {
    bVar5 = FUN_7ffe9a4b33f0(thisObject,uVar8,mobAction,0);
  }
  iVar21 = bVar5 + 1;
  iStack_d4 = iVar21;
  if (*(int *)(thisObject + 0x138) == 2) {
    cVar4 = '\x01';
    if (mobAction == (undefined *)0x0) goto LAB_7ffe9a816409;
  }
  else {
    if ((mobAction == (undefined *)0x0) ||
       (lVar15 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction), lVar15 == 0))
    goto LAB_7ffe9a816409;
    iStack_d0 = FUN_7ffe99742ec0(2,_DAT_7ffe9c93ed20,lVar15);
    fVar28 = _DAT_7ffe9c049b18;
    plVar13 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if ((plVar13 == (longlong *)0x0) ||
       (lVar15 = (**(code **)(*plVar13 + 0x1c8))(plVar13,*(undefined8 *)(*plVar13 + 0x1d0)),
       lVar15 == 0)) goto LAB_7ffe9a816409;
    cVar4 = FUN_7ffe9a7cbb30(lVar15,0x324,&plStack_98,0);
    fVar23 = _DAT_7ffe9c049b34;
    if (cVar4 != '\0') {
      if (plStack_98 == (longlong *)0x0) goto LAB_7ffe9a816409;
      iVar10 = (**(code **)(*plStack_98 + 0x1f8))
                         (plStack_98,0x32,*(undefined8 *)(*plStack_98 + 0x200));
      fVar28 = (float)iVar10 * fVar23 + fVar28;
    }
    lVar15 = FUN_7ffe99742ec0(0xb,_DAT_7ffe9c9724e0,mobAction);
    if (lVar15 == 0) goto LAB_7ffe9a816409;
    cVar4 = FUN_7ffe9a2ac880(lVar15,10,&plStack_b0);
    if (cVar4 != '\0') {
      if (plStack_b0 == (longlong *)0x0) goto LAB_7ffe9a816409;
      iVar10 = (**(code **)(*plStack_b0 + 0x1a8))(plStack_b0,*(undefined8 *)(*plStack_b0 + 0x1b0));
      if (0x32 < iVar10) {
        iVar10 = 0x32;
      }
      fVar28 = fVar28 - (float)iVar10 * fVar23;
    }
    uVar17 = (**(code **)(*(longlong *)playerAction + 0x298))
                       (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    uVar8 = (**(code **)(*(longlong *)thisObject + 0x298))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    plStack_c8 = (longlong *)CONCAT44(plStack_c8._4_4_,uVar8);
    lVar15 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,mobAction);
    if (lVar15 == 0) goto LAB_7ffe9a816409;
    uVar6 = FUN_7ffe9a4daa60(lVar15,0x21);
    cVar4 = (**(code **)(*(longlong *)thisObject + 0x688))
                      (thisObject,uVar17,(int)((float)iStack_d0 * fVar28),
                       (ulonglong)plStack_c8 & 0xffffffff,uVar6,acStackX_10,
                       *(undefined8 *)(*(longlong *)thisObject + 0x690));
    plVar13 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if ((plVar13 == (longlong *)0x0) ||
       (lVar15 = (**(code **)(*plVar13 + 0x1e8))(plVar13,*(undefined8 *)(*plVar13 + 0x1f0)),
       lVar15 == 0)) goto LAB_7ffe9a816409;
    cVar7 = FUN_7ffe9a4daa60(lVar15,0x21);
    if (cVar7 != '\0') {
      if (acStackX_10[0] == '\0') {
        acStackX_10[0] = '\x01';
        iStack_d4 = iVar21;
      }
      else {
        cVar4 = '\0';
        iStack_d4 = 0;
        iVar21 = iVar22;
      }
    }
  }
  cVar7 = FUN_7ffe99742ec0(0x14,_DAT_7ffe9c9724e0,mobAction);
  if (cVar7 != '\0') {
    cVar4 = '\x01';
    iStack_d4 = 0;
    iVar21 = iVar22;
  }
  uVar9 = (**(code **)(*(longlong *)thisObject + 0x198))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
  resistReactionType = &uStack_a8;
  puVar16 = PlayerAttackBase_CalcHitReaction
                      (thisObject,(undefined *)(ulonglong)uVar9,playerAction,mobAction,
                       (undefined *)resistReactionType,(undefined *)0x0);
  iStack_d0 = (int)puVar16;
  if ((cVar4 == '\0') && (iVar21 != 2)) {
    lVar15 = func_0x7ffe99940040(_DAT_7ffe9c920098);
    FUN_7ffe9a8f6350(lVar15,mobAction,0);
LAB_7ffe9a815a15:
    if (lVar15 == 0) goto LAB_7ffe9a816409;
    *(undefined4 *)(lVar15 + 0x18) = 0;
    *(undefined4 *)(lVar15 + 0x40) = 0;
    cVar4 = FUN_7ffe99742ec0(0x14,_DAT_7ffe9c9724e0,mobAction);
    if (cVar4 == '\0') {
      uStack_b8 = 0;
      iVar22 = iStack_d0;
    }
    else {
      iVar22 = 3;
    }
    *(undefined4 *)(lVar15 + 0x1c) = uStack_b8;
    *(int *)(lVar15 + 0x34) = iVar22;
    uVar17 = *(undefined8 *)(lVar15 + 0x48);
    uVar18 = func_0x7ffe99940040(_DAT_7ffe9c94aa68);
    FUN_7ffe9a8fff70(uVar18,uVar17,0);
    *(undefined8 *)(lVar15 + 0x38) = uVar18;
    il2cpp_write_barrier_0();
    if (*(longlong *)(lVar15 + 0x38) == 0) goto LAB_7ffe9a816409;
    *(undefined4 *)(*(longlong *)(lVar15 + 0x38) + 0x14) = 0;
  }
  else {
    if (iStack_d0 != 1) {
      uVar8 = (**(code **)(*(longlong *)thisObject + 0x198))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
      iVar10 = (**(code **)(*(longlong *)thisObject + 0x698))
                         (thisObject,playerAction,mobAction,uVar8,
                          (ulonglong)resistReactionType & 0xffffffff00000000,bVar5,
                          *(undefined8 *)(*(longlong *)thisObject + 0x6a0));
      iVar22 = *(int *)(thisObject + 0x140);
      iVar11 = (**(code **)(*(longlong *)thisObject + 0x198))
                         (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
      if (iVar11 == 2) {
        lVar15 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
        uVar17 = (**(code **)(*(longlong *)playerAction + 0x298))
                           (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if (lVar15 == 0) goto LAB_7ffe9a816409;
        uVar8 = FUN_7ffe99742f50(0x16,_DAT_7ffe9c93ed20,lVar15,uVar17);
        uVar17 = (**(code **)(*(longlong *)playerAction + 0x298))
                           (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        iVar11 = FUN_7ffe9a4aaac0(uVar17,uVar8);
      }
      else {
        lVar15 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
        uVar17 = (**(code **)(*(longlong *)playerAction + 0x298))
                           (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if (lVar15 == 0) goto LAB_7ffe9a816409;
        uVar8 = FUN_7ffe99742f50(0x15,_DAT_7ffe9c93ed20,lVar15,uVar17);
        uVar17 = (**(code **)(*(longlong *)playerAction + 0x298))
                           (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        iVar11 = FUN_7ffe9a4ab0b0(uVar17,uVar8);
      }
      fVar28 = _DAT_7ffe9c049cfc;
      iVar11 = (iVar22 + iVar10) - iVar11;
      plStack_c8 = (longlong *)CONCAT44(plStack_c8._4_4_,iVar11);
      iVar22 = 0;
      if (-1 < iVar11) {
        iVar22 = iVar11;
      }
      if (iVar21 == 2) {
        pcVar2 = *(code **)(*(longlong *)playerAction + 0x298);
        if (*(int *)(thisObject + 0x138) == 2) {
          plVar13 = (longlong *)(*pcVar2)();
          if ((plVar13 == (longlong *)0x0) ||
             (lVar15 = (**(code **)(*plVar13 + 0x1a8))(plVar13,*(undefined8 *)(*plVar13 + 0x1b0)),
             lVar15 == 0)) goto LAB_7ffe9a816409;
          uVar8 = 0x1d;
        }
        else {
          plVar13 = (longlong *)
                    (*pcVar2)(playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
          if ((plVar13 == (longlong *)0x0) ||
             (lVar15 = (**(code **)(*plVar13 + 0x1a8))(plVar13,*(undefined8 *)(*plVar13 + 0x1b0)),
             lVar15 == 0)) goto LAB_7ffe9a816409;
          uVar8 = 0x1c;
        }
        iVar21 = FUN_7ffe99742ec0(uVar8,_DAT_7ffe9c940d40,lVar15);
        iVar22 = (int)(((float)iVar21 / fVar28) * (float)iVar22);
      }
      uVar17 = (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      uVar8 = (**(code **)(*(longlong *)thisObject + 0x198))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
      lVar15 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
      if (lVar15 == 0) goto LAB_7ffe9a816409;
      uVar12 = FUN_7ffe99742ec0(9,_DAT_7ffe9c93ed20,lVar15);
      fVar23 = (float)FUN_7ffe9a4a9110(thisObject,uVar17,uVar8,uVar12,auStack_d6,0);
      uVar17 = (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      fVar24 = (float)FUN_7ffe9a4aad20(uVar17,mobAction,0);
      iVar21 = *(int *)(thisObject + 0x13c);
      uVar8 = (**(code **)(*(longlong *)thisObject + 0x198))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
      plStack_c8 = (longlong *)CONCAT44(plStack_c8._4_4_,uVar8);
      plVar13 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar13 == (longlong *)0x0) ||
         (lVar15 = (**(code **)(*plVar13 + 0x1a8))(plVar13,*(undefined8 *)(*plVar13 + 0x1b0)),
         lVar15 == 0)) goto LAB_7ffe9a816409;
      uVar8 = FUN_7ffe99742ec0(0xf,_DAT_7ffe9c940d40,lVar15);
      cVar4 = acStackX_10[0];
      uVar17 = (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      fVar25 = (float)(**(code **)(*(longlong *)thisObject + 0x6a8))
                                (thisObject,(ulonglong)plStack_c8 & 0xffffffff,uVar8,cVar4,uVar17,
                                 *(undefined8 *)(*(longlong *)thisObject + 0x6b0));
      lVar15 = FUN_7ffe99742ec0(8,_DAT_7ffe9c9724e0,mobAction);
      uVar8 = (**(code **)(*(longlong *)thisObject + 0x1a8))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1b0));
      if (lVar15 == 0) goto LAB_7ffe9a816409;
      iVar10 = func_0x7ffe9a3604f0(lVar15,uVar8,0);
      uVar17 = (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      uVar17 = FUN_7ffe9a4a7d60(thisObject,uVar17,0);
      lVar15 = *(longlong *)mobAction;
      auVar29._8_4_ = (int)extraout_XMM0_Qb;
      auVar29._0_8_ = uVar17;
      auVar29._12_4_ = (int)((ulonglong)extraout_XMM0_Qb >> 0x20);
      if ((*(byte *)(_DAT_7ffe9c923808 + 0x130) <= *(byte *)(lVar15 + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(lVar15 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c923808 + 0x130) * 8)
          == _DAT_7ffe9c923808)) {
        if ((*(byte *)(lVar15 + 0x130) < *(byte *)(_DAT_7ffe9c923808 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(lVar15 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c923808 + 0x130) * 8
             ) != _DAT_7ffe9c923808)) {
          FUN_7ffe9996c950(mobAction);
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
        cVar4 = FUN_7ffe9ab798a0(mobAction,0x5a,alStack_90,_DAT_7ffe9c8f1e88);
        if (cVar4 != '\0') {
          if (alStack_90[0] == 0) goto LAB_7ffe9a816409;
          fVar26 = (float)FUN_7ffe9a37a550(alStack_90[0],0);
          auVar29._0_4_ = (float)uVar17 - fVar26;
        }
      }
      fVar26 = (float)FUN_7ffe9a4a8c60(playerAction,mobAction,0);
      uVar17 = (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      fVar27 = (float)FUN_7ffe9a4a97e0(thisObject,uVar17,0);
      iVar22 = (int)(fVar27 * (float)(int)((float)(int)((float)(int)(((float)iVar10 / fVar28) *
                                                                    (float)(int)((float)(int)((float
                                                  )(int)((float)(int)((float)iVar22 * fVar23) *
                                                        fVar24) * ((float)iVar21 / fVar28)) * fVar25
                                                  )) * auVar29._0_4_) * fVar26));
      cVar4 = FUN_7ffe9a4ac1c0(thisObject,mobAction,&fStack_c0,0);
      fVar23 = _DAT_7ffe9c049f04;
      if (cVar4 != '\0') {
        iVar22 = (int)((float)iVar22 * fStack_c0);
      }
      if (iStack_d0 == 2) {
        lVar15 = FUN_7ffe99742ec0(0xb,_DAT_7ffe9c9724e0,mobAction);
        if (lVar15 == 0) goto LAB_7ffe9a816409;
        cVar4 = FUN_7ffe9a2ac880(lVar15,4,&plStack_b0);
        if (cVar4 != '\0') {
          if (plStack_b0 == (longlong *)0x0) goto LAB_7ffe9a816409;
          if (((*(byte *)(*plStack_b0 + 0x130) < *(byte *)(_DAT_7ffe9c91aa80 + 0x130)) ||
              (*(longlong *)
                (*(longlong *)(*plStack_b0 + 200) + -8 +
                (ulonglong)*(byte *)(_DAT_7ffe9c91aa80 + 0x130) * 8) != _DAT_7ffe9c91aa80)) ||
             (plStack_b0 == (longlong *)0x0)) {
            FUN_7ffe9996c950(plStack_b0);
            pcVar2 = (code *)swi(3);
            (*pcVar2)();
            return;
          }
          iVar21 = FUN_7ffe9a2ea460(plStack_b0,0);
          fVar23 = fVar23 - (float)iVar21;
          if (fVar23 < 0.0) {
            fVar23 = 0.0;
          }
        }
        iVar22 = (int)((fVar23 / fVar28) * (float)iVar22);
      }
      plVar13 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar13 == (longlong *)0x0) ||
         (lVar15 = (**(code **)(*plVar13 + 0x1d8))(plVar13,*(undefined8 *)(*plVar13 + 0x1e0)),
         lVar15 == 0)) goto LAB_7ffe9a816409;
      fVar23 = (float)FUN_7ffe9a4ebf80(lVar15,0);
      iVar22 = (int)(fVar23 * (float)iVar22);
      plVar13 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar13 == (longlong *)0x0) ||
         (puVar16 = (undefined *)
                    (**(code **)(*plVar13 + 0x218))(plVar13,*(undefined8 *)(*plVar13 + 0x220)),
         puVar16 == (undefined *)0x0)) goto LAB_7ffe9a816409;
      bVar5 = GemCartBufferManager_ContainsBuffer(puVar16,0x45,(undefined *)0x0);
      iVar21 = iVar22;
      if (bVar5 != 0) {
        FUN_7ffe99749320(0x17,_DAT_7ffe9c9724e0,mobAction,0x10);
        lVar15 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
        if (lVar15 == 0) goto LAB_7ffe9a816409;
        iVar21 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ed20,lVar15);
        iVar21 = (int)((float)iVar21 / fVar28);
        if (iVar21 < 1) {
          iVar21 = 1;
        }
        if (iVar22 < iVar21) {
          iVar21 = iVar22;
        }
      }
      FUN_7ffe9a4ac310(thisObject,mobAction,auStack_a0,&uStack_a4,0);
      iVar22 = FUN_7ffe9a4ad9c0(thisObject,iVar21,mobAction,&uStack_d8,&uStack_d7,0);
      if (iVar22 < 1) {
        iVar22 = 1;
      }
      fVar28 = (float)FUN_7ffe9a4adbc0(playerAction,mobAction,0);
      iStack_bc = (int)(fVar28 * (float)iVar22);
      iVar21 = iStack_d4;
      if (iStack_bc < 1) {
        iStack_bc = 1;
      }
    }
    lVar15 = func_0x7ffe99940040(_DAT_7ffe9c920098);
    FUN_7ffe9a8f6350(lVar15,mobAction,0);
    if (iVar21 == 0) goto LAB_7ffe9a815a15;
    if (lVar15 == 0) goto LAB_7ffe9a816409;
    *(int *)(lVar15 + 0x18) = iStack_bc;
    *(int *)(lVar15 + 0x34) = iStack_d0;
    *(undefined4 *)(lVar15 + 0x40) = 1;
    *(int *)(lVar15 + 0x1c) = iVar21;
    *(char *)(lVar15 + 0x30) = acStackX_10[0];
    *(undefined1 *)(lVar15 + 0x31) = uStack_d8;
    *(undefined1 *)(lVar15 + 0x32) = uStack_d7;
    *(undefined1 *)(lVar15 + 0x60) = auStack_d6[0];
    FUN_7ffe9a4b37b0(thisObject,lVar15,iStack_bc,0);
  }
  lVar14 = *(longlong *)(thisObject + 0x130);
  if (lVar14 != 0) {
    while( true ) {
      lVar20 = _DAT_7ffe9c913488;
      uVar9 = (uint)plVar19;
      if ((int)*(uint *)(lVar14 + 0x18) <= (int)uVar9) break;
      if (*(uint *)(lVar14 + 0x18) <= uVar9) goto LAB_7ffe9a816421;
      uVar8 = *(undefined4 *)(lVar14 + 0x20 + (longlong)(int)uVar9 * 4);
      plVar19 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if (plVar19 == (longlong *)0x0) goto LAB_7ffe9a816409;
      lVar20 = (**(code **)(*plVar19 + 0x1c8))(plVar19,*(undefined8 *)(*plVar19 + 0x1d0));
      if (lVar20 == 0) goto LAB_7ffe9a816409;
      FUN_7ffe9a7cb960(lVar20,uVar8,1,0);
      plVar19 = (longlong *)(ulonglong)(uVar9 + 1);
    }
    lVar14 = *(longlong *)(thisObject + 0x80);
    if (lVar14 != 0) {
      *(int *)(lVar14 + 0x1c) = *(int *)(lVar14 + 0x1c) + 1;
      lVar1 = *(longlong *)(lVar14 + 0x10);
      uVar9 = *(uint *)(lVar14 + 0x18);
      if (lVar1 != 0) {
        if (uVar9 < *(uint *)(lVar1 + 0x18)) {
          *(uint *)(lVar14 + 0x18) = uVar9 + 1;
          if (*(uint *)(lVar1 + 0x18) <= uVar9) {
LAB_7ffe9a816421:
            FUN_7ffe9996d790();
            pcVar2 = (code *)swi(3);
            (*pcVar2)();
            return;
          }
          *(longlong *)(lVar1 + 0x20 + (longlong)(int)uVar9 * 8) = lVar15;
          il2cpp_write_barrier_0();
        }
        else {
          FUN_7ffe9afd58b0(lVar14,lVar15,
                           *(undefined8 *)
                            (*(longlong *)(*(longlong *)(lVar20 + 0x20) + 0xc0) + 0x70));
        }
        return;
      }
    }
  }
LAB_7ffe9a816409:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

