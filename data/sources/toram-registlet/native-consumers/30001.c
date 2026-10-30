
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void CallGolemNormalAttackAction_calcPlayerToMobDamage
               (undefined *thisObject,undefined *playerAction,undefined *mobAction,
               undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  char cVar5;
  byte bVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  undefined4 uVar13;
  longlong *plVar14;
  longlong lVar15;
  undefined *puVar16;
  longlong lVar17;
  undefined8 uVar18;
  undefined8 uVar19;
  longlong *plVar20;
  longlong lVar21;
  float fVar22;
  float fVar23;
  float fVar24;
  float fVar25;
  float fVar26;
  float fVar27;
  float fVar28;
  float fVar29;
  float fVar30;
  longlong *plStackX_8;
  char acStackX_10 [8];
  undefined1 auStackX_18 [8];
  undefined4 *resistReactionType;
  undefined1 uStack_e8;
  undefined1 auStack_e7 [3];
  int iStack_e4;
  float fStack_e0;
  int iStack_dc;
  undefined4 uStack_d8;
  longlong *plStack_d0;
  undefined4 uStack_c8;
  undefined4 uStack_c4;
  undefined4 auStack_c0 [2];
  longlong *aplStack_b8 [16];
  
  if (DAT_7ffe9cadf4b2 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c920098);
    FUN_7ffe9996d590(&DAT_7ffe9c91aa80);
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c913488);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c923468);
    FUN_7ffe9996d590(&DAT_7ffe9c94aa68);
    DAT_7ffe9cadf4b2 = '\x01';
  }
  plVar20 = (longlong *)0x0;
  aplStack_b8[0] = (longlong *)0x0;
  plStack_d0 = (longlong *)0x0;
  acStackX_10[0] = '\0';
  uStack_c8 = 0;
  fStack_e0 = 0.0;
  auStack_c0[0] = 0;
  uStack_c4 = 0;
  uVar7 = FUN_7ffe9a4adee0(thisObject,playerAction,mobAction,0);
  *(undefined4 *)(thisObject + 0x30) = uVar7;
  if ((playerAction == (undefined *)0x0) ||
     (plVar14 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
     plVar14 == (longlong *)0x0)) goto LAB_7ffe9a7aaae3;
  plVar14 = (longlong *)(**(code **)(*plVar14 + 0x198))(plVar14,*(undefined8 *)(*plVar14 + 0x1a0));
  if (plVar14 == (longlong *)0x0) {
    plStackX_8 = (longlong *)0x0;
  }
  else {
    if ((*(byte *)(*plVar14 + 0x130) < *(byte *)(_DAT_7ffe9c923468 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*plVar14 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c923468 + 0x130) * 8)
        != _DAT_7ffe9c923468)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    plStackX_8 = plVar20;
    if (bVar3) {
      plStackX_8 = plVar14;
    }
  }
  lVar17 = *(longlong *)(thisObject + 0x120);
  iStack_e4 = 0;
  auStack_e7[0] = 0;
  auStackX_18[0] = 0;
  uStack_e8 = 0;
  plVar14 = plVar20;
  if (lVar17 == 0) goto LAB_7ffe9a7aaae3;
  while (uVar10 = (uint)plVar14, (int)uVar10 < *(int *)(lVar17 + 0x18)) {
    if (*(uint *)(lVar17 + 0x18) <= uVar10) goto LAB_7ffe9a7aaaf2;
    plVar14 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if ((plVar14 == (longlong *)0x0) ||
       (lVar15 = (**(code **)(*plVar14 + 0x1c8))(plVar14,*(undefined8 *)(*plVar14 + 0x1d0)),
       lVar15 == 0)) goto LAB_7ffe9a7aaae3;
    FUN_7ffe9a7cb960(lVar15);
    plVar14 = (longlong *)(ulonglong)(uVar10 + 1);
  }
  if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a7aaae3;
  FUN_7ffe9a484e10(plStackX_8,0);
  PlayerSecondaryStatus_GetCrtConstant((undefined *)plStackX_8,1,(undefined *)0x0);
  uVar7 = FUN_7ffe9a472c30(plStackX_8);
  iVar8 = (**(code **)(*(longlong *)thisObject + 0x198))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
  if (iVar8 == 2) {
    uVar18 = (**(code **)(*(longlong *)playerAction + 0x298))
                       (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    cVar4 = FUN_7ffe9a4acb20(thisObject,uVar7,uVar18,mobAction,0);
  }
  else {
    cVar4 = FUN_7ffe9a4b33f0(thisObject,uVar7,mobAction,0);
  }
  uStack_d8 = 1;
  if ((thisObject[0x148] != '\0') && (*(int *)(thisObject + 0x140) == 2)) {
    cVar4 = '\x01';
  }
  iVar8 = (cVar4 != '\0') + 1;
  iVar9 = (**(code **)(*(longlong *)thisObject + 0x198))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
  if (iVar9 == 2) {
    plStackX_8._0_1_ = 1;
    if (mobAction == (undefined *)0x0) goto LAB_7ffe9a7aaae3;
  }
  else {
    if ((mobAction == (undefined *)0x0) ||
       (lVar17 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction), lVar17 == 0))
    goto LAB_7ffe9a7aaae3;
    iVar9 = FUN_7ffe99742ec0(2,_DAT_7ffe9c93ed20,lVar17);
    fVar29 = _DAT_7ffe9c049b18;
    plVar14 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if ((plVar14 == (longlong *)0x0) ||
       (lVar17 = (**(code **)(*plVar14 + 0x1c8))(plVar14,*(undefined8 *)(*plVar14 + 0x1d0)),
       lVar17 == 0)) goto LAB_7ffe9a7aaae3;
    cVar5 = FUN_7ffe9a7cbb30(lVar17,0x324,aplStack_b8,0);
    fVar30 = _DAT_7ffe9c049b34;
    if (cVar5 != '\0') {
      if (aplStack_b8[0] == (longlong *)0x0) goto LAB_7ffe9a7aaae3;
      iVar11 = (**(code **)(*aplStack_b8[0] + 0x1f8))
                         (aplStack_b8[0],0x32,*(undefined8 *)(*aplStack_b8[0] + 0x200));
      fVar29 = (float)iVar11 * fVar30 + fVar29;
    }
    lVar17 = FUN_7ffe99742ec0(0xb,_DAT_7ffe9c9724e0,mobAction);
    if (lVar17 == 0) goto LAB_7ffe9a7aaae3;
    cVar5 = FUN_7ffe9a2ac880(lVar17,10,&plStack_d0);
    if (cVar5 != '\0') {
      if (plStack_d0 == (longlong *)0x0) goto LAB_7ffe9a7aaae3;
      iVar11 = (**(code **)(*plStack_d0 + 0x1a8))(plStack_d0,*(undefined8 *)(*plStack_d0 + 0x1b0));
      if (0x32 < iVar11) {
        iVar11 = 0x32;
      }
      fVar29 = fVar29 - (float)iVar11 * fVar30;
    }
    plVar14 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if ((plVar14 == (longlong *)0x0) ||
       (lVar17 = (**(code **)(*plVar14 + 0x1a8))(plVar14,*(undefined8 *)(*plVar14 + 0x1b0)),
       lVar17 == 0)) goto LAB_7ffe9a7aaae3;
    iVar11 = FUN_7ffe99742ec0(0x11,_DAT_7ffe9c940d40,lVar17);
    fVar29 = (float)(((int)((float)iVar9 * fVar29) - *(int *)(thisObject + 0x134)) - iVar11) /
             _DAT_7ffe9c049b74;
    iVar9 = (**(code **)(*(longlong *)thisObject + 0x298))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    iVar9 = (iVar9 / 100 + 10) * 10 - (int)fVar29;
    if (100 < iVar9) {
      iVar9 = 100;
    }
    plVar14 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if ((plVar14 == (longlong *)0x0) ||
       (lVar17 = (**(code **)(*plVar14 + 0x1e8))(plVar14,*(undefined8 *)(*plVar14 + 0x1f0)),
       lVar17 == 0)) goto LAB_7ffe9a7aaae3;
    cVar5 = FUN_7ffe9a4daa60(lVar17,7);
    if (cVar5 != '\0') {
      fVar29 = _DAT_7ffe9c049db0;
      if (_DAT_7ffe9c049b7c < *(float *)(thisObject + 0x20) ||
          _DAT_7ffe9c049b7c == *(float *)(thisObject + 0x20)) {
        fVar29 = _DAT_7ffe9c049e50;
      }
      iVar9 = (int)((float)iVar9 * fVar29);
    }
    puVar16 = (undefined *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    lVar17 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,mobAction);
    if (lVar17 == 0) goto LAB_7ffe9a7aaae3;
    bVar6 = FUN_7ffe9a4daa60(lVar17,0x21);
    plStackX_8._0_1_ =
         PlayerAttackBase_ChackCorrectHit
                   (thisObject,puVar16,iVar9,bVar6,acStackX_10,(undefined *)0x0);
    plVar14 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if ((plVar14 == (longlong *)0x0) ||
       (lVar17 = (**(code **)(*plVar14 + 0x1e8))(plVar14,*(undefined8 *)(*plVar14 + 0x1f0)),
       lVar17 == 0)) goto LAB_7ffe9a7aaae3;
    cVar5 = FUN_7ffe9a4daa60(lVar17,0x21);
    if (cVar5 != '\0') {
      if (acStackX_10[0] == '\0') {
        acStackX_10[0] = '\x01';
      }
      else {
        plStackX_8._0_1_ = 0;
        iVar8 = 0;
      }
    }
  }
  cVar5 = FUN_7ffe99742ec0(0x14,_DAT_7ffe9c9724e0,mobAction);
  if (cVar5 != '\0') {
    plStackX_8._0_1_ = 1;
    iVar8 = 0;
  }
  uVar10 = (**(code **)(*(longlong *)thisObject + 0x198))
                     (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
  resistReactionType = &uStack_c8;
  puVar16 = PlayerAttackBase_CalcHitReaction
                      (thisObject,(undefined *)(ulonglong)uVar10,playerAction,mobAction,
                       (undefined *)resistReactionType,(undefined *)0x0);
  iVar9 = (int)puVar16;
  if ((thisObject[0x148] != '\0') && (*(int *)(thisObject + 0x140) == 0)) {
    lVar17 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
    if (lVar17 == 0) goto LAB_7ffe9a7aaae3;
    iVar11 = FUN_7ffe99742ec0(8,_DAT_7ffe9c93ed20,lVar17);
    if ((iVar11 < 100) && (iVar9 != 1)) {
      iVar9 = 0;
    }
    cVar5 = FUN_7ffe99742ec0(0x14,_DAT_7ffe9c9724e0,mobAction);
    if ((cVar5 == '\0') && (iVar9 != 1)) {
      acStackX_10[0] = '\0';
      plStackX_8._0_1_ = 1;
      if (cVar4 != '\0') {
        iVar8 = 2;
      }
    }
  }
  iStack_dc = 0;
  iVar11 = 0;
  bVar6 = 0;
  if (*(float *)(thisObject + 0x13c) <= _DAT_7ffe9c049cec) {
    iStack_dc = iVar8;
    iVar11 = iVar9;
    bVar6 = (byte)plStackX_8;
  }
  if ((bVar6 == 0) && (iStack_dc != 2)) {
    lVar17 = func_0x7ffe99940040(_DAT_7ffe9c920098);
    FUN_7ffe9a8f6350(lVar17,mobAction,0);
LAB_7ffe9a7aa03d:
    if (lVar17 == 0) goto LAB_7ffe9a7aaae3;
    *(undefined4 *)(lVar17 + 0x18) = 0;
    *(undefined4 *)(lVar17 + 0x40) = 0;
    cVar4 = FUN_7ffe99742ec0(0x14,_DAT_7ffe9c9724e0,mobAction);
    if (cVar4 == '\0') {
      uStack_d8 = 0;
    }
    else {
      iVar11 = 3;
    }
    *(undefined4 *)(lVar17 + 0x1c) = uStack_d8;
    *(int *)(lVar17 + 0x34) = iVar11;
    uVar18 = *(undefined8 *)(lVar17 + 0x48);
    uVar19 = func_0x7ffe99940040(_DAT_7ffe9c94aa68);
    FUN_7ffe9a8fff70(uVar19,uVar18,0);
    *(undefined8 *)(lVar17 + 0x38) = uVar19;
    il2cpp_write_barrier_0();
    if (*(longlong *)(lVar17 + 0x38) == 0) goto LAB_7ffe9a7aaae3;
    *(undefined4 *)(*(longlong *)(lVar17 + 0x38) + 0x14) = 0;
  }
  else {
    if (iVar11 != 1) {
      uVar7 = (**(code **)(*(longlong *)thisObject + 0x198))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
      iVar8 = (**(code **)(*(longlong *)thisObject + 0x698))
                        (thisObject,playerAction,mobAction,uVar7,
                         (ulonglong)resistReactionType & 0xffffffff00000000,cVar4,
                         *(undefined8 *)(*(longlong *)thisObject + 0x6a0));
      plVar14 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar14 == (longlong *)0x0) ||
         (lVar17 = (**(code **)(*plVar14 + 0x1c8))(plVar14,*(undefined8 *)(*plVar14 + 0x1d0)),
         lVar17 == 0)) goto LAB_7ffe9a7aaae3;
      iVar9 = func_0x7ffe9a7c8f00(lVar17,0x38);
      iVar12 = (**(code **)(*(longlong *)thisObject + 0x198))
                         (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
      if (iVar12 == 2) {
        lVar17 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
        uVar18 = (**(code **)(*(longlong *)playerAction + 0x298))
                           (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if (lVar17 == 0) goto LAB_7ffe9a7aaae3;
        uVar7 = FUN_7ffe99742f50(0x16,_DAT_7ffe9c93ed20,lVar17,uVar18);
        uVar18 = (**(code **)(*(longlong *)playerAction + 0x298))
                           (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        fVar29 = _DAT_7ffe9c049cfc;
        iVar12 = FUN_7ffe9a4aaac0(uVar18,uVar7,(float)*(int *)(thisObject + 300) / _DAT_7ffe9c049cfc
                                  ,0);
      }
      else {
        lVar17 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
        uVar18 = (**(code **)(*(longlong *)playerAction + 0x298))
                           (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if (lVar17 == 0) goto LAB_7ffe9a7aaae3;
        uVar7 = FUN_7ffe99742f50(0x15,_DAT_7ffe9c93ed20,lVar17,uVar18);
        uVar18 = (**(code **)(*(longlong *)playerAction + 0x298))
                           (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        fVar29 = _DAT_7ffe9c049cfc;
        iVar12 = FUN_7ffe9a4ab0b0(uVar18,uVar7,(float)*(int *)(thisObject + 300) / _DAT_7ffe9c049cfc
                                  ,0);
      }
      iVar12 = (iVar8 + iVar9) - iVar12;
      iVar8 = 0;
      if (-1 < iVar12) {
        iVar8 = iVar12;
      }
      if (iStack_dc == 2) {
        plVar14 = (longlong *)
                  (**(code **)(*(longlong *)playerAction + 0x298))
                            (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if ((plVar14 == (longlong *)0x0) ||
           (lVar17 = (**(code **)(*plVar14 + 0x1a8))(plVar14,*(undefined8 *)(*plVar14 + 0x1b0)),
           lVar17 == 0)) goto LAB_7ffe9a7aaae3;
        iVar9 = FUN_7ffe99742ec0(0x1c,_DAT_7ffe9c940d40,lVar17);
        iVar12 = (**(code **)(*(longlong *)thisObject + 0x198))
                           (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
        if (iVar12 == 2) {
          plVar14 = (longlong *)
                    (**(code **)(*(longlong *)playerAction + 0x298))
                              (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
          if ((plVar14 == (longlong *)0x0) ||
             (lVar17 = (**(code **)(*plVar14 + 0x1a8))(plVar14,*(undefined8 *)(*plVar14 + 0x1b0)),
             lVar17 == 0)) goto LAB_7ffe9a7aaae3;
          iVar9 = FUN_7ffe99742ec0(0x1d,_DAT_7ffe9c940d40,lVar17);
        }
        iVar8 = (int)(((float)iVar9 / fVar29) * (float)iVar8);
      }
      uVar18 = (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      uVar7 = (**(code **)(*(longlong *)thisObject + 0x198))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
      lVar17 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
      if (lVar17 == 0) goto LAB_7ffe9a7aaae3;
      uVar13 = FUN_7ffe99742ec0(9,_DAT_7ffe9c93ed20,lVar17);
      fVar22 = (float)FUN_7ffe9a4a9110(thisObject,uVar18,uVar7,uVar13,auStack_e7,0);
      uVar18 = (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      fVar23 = (float)FUN_7ffe9a4aad20(uVar18,mobAction,0);
      fVar30 = *(float *)(thisObject + 0x128);
      plVar14 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar14 == (longlong *)0x0) ||
         (lVar17 = (**(code **)(*plVar14 + 0x1c8))(plVar14,*(undefined8 *)(*plVar14 + 0x1d0)),
         lVar17 == 0)) goto LAB_7ffe9a7aaae3;
      iVar9 = func_0x7ffe9a7c8f00(lVar17,0x3a);
      plVar14 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar14 == (longlong *)0x0) ||
         (puVar16 = (undefined *)(**(code **)(*plVar14 + 0x218))(plVar14),
         puVar16 == (undefined *)0x0)) goto LAB_7ffe9a7aaae3;
      fVar24 = GemCartBufferManager_GetNormalAttackRate(puVar16,(undefined *)0x0);
      iStack_e4 = (**(code **)(*(longlong *)thisObject + 0x198))
                            (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
      plVar14 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar14 == (longlong *)0x0) ||
         (lVar17 = (**(code **)(*plVar14 + 0x1a8))(plVar14,*(undefined8 *)(*plVar14 + 0x1b0)),
         lVar17 == 0)) goto LAB_7ffe9a7aaae3;
      uVar7 = FUN_7ffe99742ec0(0xf,_DAT_7ffe9c940d40,lVar17);
      cVar4 = acStackX_10[0];
      uVar18 = (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      fVar25 = (float)(**(code **)(*(longlong *)thisObject + 0x6a8))
                                (thisObject,iStack_e4,uVar7,cVar4,uVar18,
                                 *(undefined8 *)(*(longlong *)thisObject + 0x6b0));
      lVar17 = FUN_7ffe99742ec0(8,_DAT_7ffe9c9724e0,mobAction);
      if (lVar17 == 0) goto LAB_7ffe9a7aaae3;
      iVar12 = *(int *)(lVar17 + 0x18);
      uVar18 = (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      fVar26 = (float)FUN_7ffe9a4a7d60(thisObject,uVar18,0);
      fVar27 = (float)FUN_7ffe9a4a8c60(playerAction,mobAction,0);
      uVar18 = (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      fVar28 = (float)FUN_7ffe9a4a97e0(thisObject,uVar18,0);
      iVar8 = (int)(fVar28 * (float)(int)((float)(int)(fVar26 * (float)(int)((float)(int)((float)(
                                                  int)((float)(int)((float)(int)((float)iVar8 *
                                                                                fVar22) * fVar23) *
                                                      ((fVar24 + (float)iVar9 + fVar30) / fVar29)) *
                                                  fVar25) * ((float)iVar12 / fVar29))) * fVar27));
      cVar4 = FUN_7ffe9a4ac1c0(thisObject,mobAction,&fStack_e0,0);
      fVar30 = _DAT_7ffe9c049f04;
      if (cVar4 != '\0') {
        iVar8 = (int)((float)iVar8 * fStack_e0);
      }
      if (iVar11 == 2) {
        lVar17 = FUN_7ffe99742ec0(0xb,_DAT_7ffe9c9724e0,mobAction);
        if (lVar17 == 0) goto LAB_7ffe9a7aaae3;
        cVar4 = FUN_7ffe9a2ac880(lVar17,4,&plStack_d0);
        if (cVar4 != '\0') {
          if (plStack_d0 == (longlong *)0x0) goto LAB_7ffe9a7aaae3;
          if (((*(byte *)(*plStack_d0 + 0x130) < *(byte *)(_DAT_7ffe9c91aa80 + 0x130)) ||
              (*(longlong *)
                (*(longlong *)(*plStack_d0 + 200) + -8 +
                (ulonglong)*(byte *)(_DAT_7ffe9c91aa80 + 0x130) * 8) != _DAT_7ffe9c91aa80)) ||
             (plStack_d0 == (longlong *)0x0)) {
            FUN_7ffe9996c950(plStack_d0);
            pcVar2 = (code *)swi(3);
            (*pcVar2)();
            return;
          }
          iVar9 = FUN_7ffe9a2ea460(plStack_d0,0);
          fVar30 = fVar30 - (float)iVar9;
          if (fVar30 < 0.0) {
            fVar30 = 0.0;
          }
        }
        iVar8 = (int)((fVar30 / fVar29) * (float)iVar8);
      }
      plVar14 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar14 == (longlong *)0x0) ||
         (lVar17 = (**(code **)(*plVar14 + 0x1d8))(plVar14,*(undefined8 *)(*plVar14 + 0x1e0)),
         lVar17 == 0)) goto LAB_7ffe9a7aaae3;
      fVar30 = (float)FUN_7ffe9a4ebf80(lVar17,0);
      iVar8 = (int)(fVar30 * (float)iVar8);
      plVar14 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar14 == (longlong *)0x0) ||
         (puVar16 = (undefined *)
                    (**(code **)(*plVar14 + 0x218))(plVar14,*(undefined8 *)(*plVar14 + 0x220)),
         puVar16 == (undefined *)0x0)) goto LAB_7ffe9a7aaae3;
      bVar6 = GemCartBufferManager_ContainsBuffer(puVar16,0x45,(undefined *)0x0);
      if (bVar6 != 0) {
        FUN_7ffe99749320(0x17,_DAT_7ffe9c9724e0,mobAction,0x10);
        lVar17 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
        if (lVar17 == 0) goto LAB_7ffe9a7aaae3;
        iVar9 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ed20,lVar17);
        iVar9 = (int)((float)iVar9 / fVar29);
        if (iVar9 < 1) {
          iVar9 = 1;
        }
        if (iVar9 <= iVar8) {
          iVar8 = iVar9;
        }
      }
      FUN_7ffe9a4ac310(thisObject,mobAction,auStack_c0,&uStack_c4,0);
      iVar8 = FUN_7ffe9a4ad9c0(thisObject,iVar8,mobAction,auStackX_18,&uStack_e8,0);
      if (iVar8 < 1) {
        iVar8 = 1;
      }
      fVar29 = (float)FUN_7ffe9a4adbc0(playerAction,mobAction,0);
      iStack_e4 = (int)(fVar29 * (float)iVar8);
      if (iStack_e4 < 1) {
        iStack_e4 = 1;
      }
    }
    iVar8 = iStack_dc;
    lVar17 = func_0x7ffe99940040(_DAT_7ffe9c920098);
    FUN_7ffe9a8f6350(lVar17,mobAction,0);
    if (iVar8 == 0) goto LAB_7ffe9a7aa03d;
    if (lVar17 == 0) goto LAB_7ffe9a7aaae3;
    *(int *)(lVar17 + 0x18) = iStack_e4;
    *(int *)(lVar17 + 0x34) = iVar11;
    *(undefined4 *)(lVar17 + 0x40) = 1;
    *(int *)(lVar17 + 0x1c) = iVar8;
    *(char *)(lVar17 + 0x30) = acStackX_10[0];
    *(undefined1 *)(lVar17 + 0x31) = auStackX_18[0];
    *(undefined1 *)(lVar17 + 0x32) = uStack_e8;
    *(undefined1 *)(lVar17 + 0x60) = auStack_e7[0];
    FUN_7ffe9a4b37b0(thisObject,lVar17,iStack_e4,0);
  }
  lVar15 = *(longlong *)(thisObject + 0x120);
  if (lVar15 != 0) {
    while (lVar21 = _DAT_7ffe9c913488, uVar10 = (uint)plVar20, (int)uVar10 < *(int *)(lVar15 + 0x18)
          ) {
      if (*(uint *)(lVar15 + 0x18) <= uVar10) goto LAB_7ffe9a7aaaf2;
      uVar7 = *(undefined4 *)(lVar15 + 0x20 + (longlong)(int)uVar10 * 4);
      plVar20 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if (plVar20 == (longlong *)0x0) goto LAB_7ffe9a7aaae3;
      lVar21 = (**(code **)(*plVar20 + 0x1c8))(plVar20,*(undefined8 *)(*plVar20 + 0x1d0));
      if (lVar21 == 0) goto LAB_7ffe9a7aaae3;
      FUN_7ffe9a7cb960(lVar21,uVar7,1,0);
      plVar20 = (longlong *)(ulonglong)(uVar10 + 1);
    }
    lVar15 = *(longlong *)(thisObject + 0x80);
    if (lVar15 != 0) {
      *(int *)(lVar15 + 0x1c) = *(int *)(lVar15 + 0x1c) + 1;
      lVar1 = *(longlong *)(lVar15 + 0x10);
      uVar10 = *(uint *)(lVar15 + 0x18);
      if (lVar1 != 0) {
        if (uVar10 < *(uint *)(lVar1 + 0x18)) {
          *(uint *)(lVar15 + 0x18) = uVar10 + 1;
          if (*(uint *)(lVar1 + 0x18) <= uVar10) {
LAB_7ffe9a7aaaf2:
            FUN_7ffe9996d790();
            pcVar2 = (code *)swi(3);
            (*pcVar2)();
            return;
          }
          *(longlong *)(lVar1 + 0x20 + (longlong)(int)uVar10 * 8) = lVar17;
          il2cpp_write_barrier_0();
        }
        else {
          FUN_7ffe9afd58b0(lVar15,lVar17,
                           *(undefined8 *)
                            (*(longlong *)(*(longlong *)(lVar21 + 0x20) + 0xc0) + 0x70));
        }
        return;
      }
    }
  }
LAB_7ffe9a7aaae3:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

