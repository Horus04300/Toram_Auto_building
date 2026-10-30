
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void HuntingOneNormalAttackAction_calcPlayerToMobDamage
               (undefined *thisObject,undefined *playerAction,undefined *mobAction,
               undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  bool bVar3;
  longlong *thisObject_00;
  byte bVar4;
  char cVar5;
  undefined1 uVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  int iVar11;
  int iVar12;
  undefined4 uVar13;
  longlong *plVar14;
  longlong lVar15;
  longlong lVar16;
  undefined8 uVar17;
  undefined *puVar18;
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
  char acStackX_10 [8];
  undefined4 *resistReactionType;
  char cStack_c8;
  undefined1 uStack_c7;
  undefined1 uStack_c6;
  undefined1 uStack_c5;
  int iStack_c4;
  int iStack_c0;
  longlong *plStack_b8;
  float fStack_b0;
  int iStack_ac;
  longlong *plStack_a8;
  undefined4 uStack_a0;
  undefined4 uStack_9c;
  undefined4 auStack_98 [2];
  longlong lStack_90;
  longlong *plStack_88;
  longlong *plStack_80;
  longlong lStack_78;
  longlong alStack_70 [9];
  
  if (DAT_7ffe9cadf4c9 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c920098);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1e88);
    FUN_7ffe9996d590(&DAT_7ffe9c91aa80);
    FUN_7ffe9996d590(&DAT_7ffe9c923808);
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c913488);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c923468);
    FUN_7ffe9996d590(&DAT_7ffe9c9689a0);
    FUN_7ffe9996d590(&DAT_7ffe9c96a188);
    FUN_7ffe9996d590(&DAT_7ffe9c94aa68);
    DAT_7ffe9cadf4c9 = '\x01';
  }
  plVar20 = (longlong *)0x0;
  plStack_80 = (longlong *)0x0;
  plStack_a8 = (longlong *)0x0;
  acStackX_10[0] = '\0';
  uStack_a0 = 0;
  lStack_78 = 0;
  lStack_90 = 0;
  plStack_88 = (longlong *)0x0;
  fStack_b0 = 0.0;
  auStack_98[0] = 0;
  uStack_9c = 0;
  alStack_70[0] = 0;
  if ((playerAction == (undefined *)0x0) ||
     (plVar14 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
     plVar14 == (longlong *)0x0)) goto LAB_7ffe9a7b3944;
  plVar14 = (longlong *)(**(code **)(*plVar14 + 0x198))(plVar14,*(undefined8 *)(*plVar14 + 0x1a0));
  if (plVar14 == (longlong *)0x0) {
    plStack_b8 = (longlong *)0x0;
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
    plStack_b8 = plVar20;
    if (bVar3) {
      plStack_b8 = plVar14;
    }
  }
  lVar16 = *(longlong *)(thisObject + 0x120);
  iStack_ac = 0;
  uStack_c5 = 0;
  uStack_c7 = 0;
  uStack_c6 = 0;
  plVar14 = plVar20;
  if (lVar16 == 0) goto LAB_7ffe9a7b3944;
  while (thisObject_00 = plStack_b8, uVar10 = (uint)plVar14, (int)uVar10 < *(int *)(lVar16 + 0x18))
  {
    if (*(uint *)(lVar16 + 0x18) <= uVar10) goto LAB_7ffe9a7b395c;
    plVar14 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if ((plVar14 == (longlong *)0x0) ||
       (lVar15 = (**(code **)(*plVar14 + 0x1c8))(plVar14,*(undefined8 *)(*plVar14 + 0x1d0)),
       lVar15 == 0)) goto LAB_7ffe9a7b3944;
    FUN_7ffe9a7cb960(lVar15);
    plVar14 = (longlong *)(ulonglong)(uVar10 + 1);
  }
  if (plStack_b8 == (longlong *)0x0) goto LAB_7ffe9a7b3944;
  FUN_7ffe9a484e10(plStack_b8,0);
  PlayerSecondaryStatus_GetCrtConstant((undefined *)thisObject_00,1,(undefined *)0x0);
  uVar7 = FUN_7ffe9a472c30(thisObject_00);
  bVar4 = FUN_7ffe9a4b33f0(thisObject,uVar7,mobAction,0);
  if ((mobAction == (undefined *)0x0) ||
     (lVar16 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,mobAction), lVar16 == 0))
  goto LAB_7ffe9a7b3944;
  cVar5 = FUN_7ffe9a4d9f40(lVar16,0xf);
  if (cVar5 != '\0') {
    plVar14 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if ((plVar14 == (longlong *)0x0) ||
       (lVar16 = (**(code **)(*plVar14 + 0x1b8))(plVar14,*(undefined8 *)(*plVar14 + 0x1c0)),
       lVar16 == 0)) goto LAB_7ffe9a7b3944;
    iVar8 = FUN_7ffe9a7fd580(lVar16,0x4d,1,0);
    if (9 < iVar8) {
      bVar4 = 1;
    }
  }
  iVar8 = bVar4 + 1;
  iStack_c0 = iVar8;
  lVar16 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
  if (lVar16 == 0) goto LAB_7ffe9a7b3944;
  iStack_c4 = FUN_7ffe99742ec0(2,_DAT_7ffe9c93ed20,lVar16);
  fVar22 = _DAT_7ffe9c049b18;
  plVar14 = (longlong *)
            (**(code **)(*(longlong *)playerAction + 0x298))
                      (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if ((plVar14 == (longlong *)0x0) ||
     (lVar16 = (**(code **)(*plVar14 + 0x1c8))(plVar14,*(undefined8 *)(*plVar14 + 0x1d0)),
     lVar16 == 0)) goto LAB_7ffe9a7b3944;
  cVar5 = FUN_7ffe9a7cbb30(lVar16,0x324,&plStack_80,0);
  fVar25 = _DAT_7ffe9c049b34;
  if (cVar5 != '\0') {
    if (plStack_80 == (longlong *)0x0) goto LAB_7ffe9a7b3944;
    iVar9 = (**(code **)(*plStack_80 + 0x1f8))(plStack_80,0x32,*(undefined8 *)(*plStack_80 + 0x200))
    ;
    fVar22 = (float)iVar9 * fVar25 + fVar22;
  }
  lVar16 = FUN_7ffe99742ec0(0xb,_DAT_7ffe9c9724e0,mobAction);
  if (lVar16 == 0) goto LAB_7ffe9a7b3944;
  cVar5 = FUN_7ffe9a2ac880(lVar16,10,&plStack_a8);
  if (cVar5 != '\0') {
    if (plStack_a8 == (longlong *)0x0) goto LAB_7ffe9a7b3944;
    iVar9 = (**(code **)(*plStack_a8 + 0x1a8))(plStack_a8,*(undefined8 *)(*plStack_a8 + 0x1b0));
    if (0x32 < iVar9) {
      iVar9 = 0x32;
    }
    fVar22 = fVar22 - (float)iVar9 * fVar25;
  }
  uVar17 = (**(code **)(*(longlong *)playerAction + 0x298))
                     (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  uVar7 = (**(code **)(*(longlong *)thisObject + 0x298))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  plStack_b8 = (longlong *)CONCAT44(plStack_b8._4_4_,uVar7);
  lVar16 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,mobAction);
  if (lVar16 == 0) goto LAB_7ffe9a7b3944;
  uVar6 = FUN_7ffe9a4daa60(lVar16,0x21);
  cStack_c8 = (**(code **)(*(longlong *)thisObject + 0x688))
                        (thisObject,uVar17,(int)((float)iStack_c4 * fVar22),
                         (ulonglong)plStack_b8 & 0xffffffff,uVar6,acStackX_10,
                         *(undefined8 *)(*(longlong *)thisObject + 0x690));
  plVar14 = (longlong *)
            (**(code **)(*(longlong *)playerAction + 0x298))
                      (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if ((plVar14 == (longlong *)0x0) ||
     (lVar16 = (**(code **)(*plVar14 + 0x1e8))(plVar14,*(undefined8 *)(*plVar14 + 0x1f0)),
     lVar16 == 0)) goto LAB_7ffe9a7b3944;
  cVar5 = FUN_7ffe9a4daa60(lVar16,0x21);
  if (cVar5 != '\0') {
    if (acStackX_10[0] == '\0') {
      acStackX_10[0] = '\x01';
      iStack_c0 = iVar8;
    }
    else {
      iStack_c0 = 0;
      cStack_c8 = '\0';
      iVar8 = 0;
    }
  }
  cVar5 = FUN_7ffe99742ec0(0x14,_DAT_7ffe9c9724e0,mobAction);
  if (cVar5 != '\0') {
    cStack_c8 = '\x01';
    iStack_c0 = 0;
    iVar8 = 0;
  }
  uVar10 = (**(code **)(*(longlong *)thisObject + 0x198))
                     (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
  resistReactionType = &uStack_a0;
  puVar18 = PlayerAttackBase_CalcHitReaction
                      (thisObject,(undefined *)(ulonglong)uVar10,playerAction,mobAction,
                       (undefined *)resistReactionType,(undefined *)0x0);
  iVar9 = (int)puVar18;
  iStack_c4 = iVar9;
  lVar16 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,mobAction);
  if (lVar16 == 0) goto LAB_7ffe9a7b3944;
  cVar5 = FUN_7ffe9a4d9f40(lVar16,6);
  if (cVar5 != '\0') {
    plVar14 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if (plVar14 == (longlong *)0x0) goto LAB_7ffe9a7b3944;
    lVar16 = (**(code **)(*plVar14 + 0x1b8))(plVar14,*(undefined8 *)(*plVar14 + 0x1c0));
    if (lVar16 == 0) goto LAB_7ffe9a7b3944;
    iVar11 = FUN_7ffe9a7fd580(lVar16,0x47,1);
    if (9 < iVar11) {
      lVar16 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
      if (lVar16 == 0) goto LAB_7ffe9a7b3944;
      iVar11 = FUN_7ffe99742ec0(7,_DAT_7ffe9c93ed20,lVar16);
      if ((iVar11 < 100) && (iStack_c4 = iVar9, iVar9 == 2)) {
        iVar9 = 0;
        iStack_c4 = 0;
      }
    }
  }
  lVar16 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,mobAction);
  if (lVar16 == 0) goto LAB_7ffe9a7b3944;
  cVar5 = FUN_7ffe9a4d9f40(lVar16,7);
  if (cVar5 != '\0') {
    plVar14 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if (plVar14 == (longlong *)0x0) goto LAB_7ffe9a7b3944;
    lVar16 = (**(code **)(*plVar14 + 0x1b8))(plVar14,*(undefined8 *)(*plVar14 + 0x1c0));
    if (lVar16 == 0) goto LAB_7ffe9a7b3944;
    iVar11 = FUN_7ffe9a7fd580(lVar16,0x4a,1);
    if (9 < iVar11) {
      lVar16 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
      if (lVar16 == 0) goto LAB_7ffe9a7b3944;
      iVar11 = FUN_7ffe99742ec0(8,_DAT_7ffe9c93ed20,lVar16);
      if ((iVar11 < 100) && (iStack_c4 = iVar9, iVar9 == 1)) {
        iVar9 = 0;
        iStack_c4 = 0;
      }
    }
  }
  lVar16 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,mobAction);
  if (lVar16 == 0) goto LAB_7ffe9a7b3944;
  cVar5 = FUN_7ffe9a4d9f40(lVar16,0xb);
  if (cVar5 != '\0') {
    plVar14 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if (plVar14 == (longlong *)0x0) goto LAB_7ffe9a7b3944;
    lVar16 = (**(code **)(*plVar14 + 0x1b8))(plVar14,*(undefined8 *)(*plVar14 + 0x1c0));
    if (lVar16 == 0) goto LAB_7ffe9a7b3944;
    iVar11 = FUN_7ffe9a7fd580(lVar16,0x43,1);
    if ((9 < iVar11) && (iVar9 != 1)) {
      acStackX_10[0] = '\0';
      cStack_c8 = '\x01';
      iStack_c0 = iVar8;
      if (bVar4 != 0) {
        iVar8 = 2;
        iStack_c0 = 2;
      }
    }
  }
  if (*(float *)(thisObject + 0x130) <= _DAT_7ffe9c049cec) {
    if ((cStack_c8 == '\0') && (iVar8 != 2)) goto LAB_7ffe9a7b2d91;
    if (iVar9 != 1) {
      uVar7 = (**(code **)(*(longlong *)thisObject + 0x198))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
      uVar7 = (**(code **)(*(longlong *)thisObject + 0x698))
                        (thisObject,playerAction,mobAction,uVar7,
                         (ulonglong)resistReactionType & 0xffffffff00000000,bVar4,
                         *(undefined8 *)(*(longlong *)thisObject + 0x6a0));
      iVar9 = *(int *)(thisObject + 300);
      plStack_b8 = (longlong *)CONCAT44(plStack_b8._4_4_,uVar7);
      plVar14 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar14 == (longlong *)0x0) ||
         (lVar16 = (**(code **)(*plVar14 + 0x1c8))(plVar14,*(undefined8 *)(*plVar14 + 0x1d0)),
         lVar16 == 0)) goto LAB_7ffe9a7b3944;
      iVar11 = func_0x7ffe9a7c8f00(lVar16,0x38);
      lVar16 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
      uVar17 = (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if (lVar16 == 0) goto LAB_7ffe9a7b3944;
      uVar7 = FUN_7ffe99742f50(0x15,_DAT_7ffe9c93ed20,lVar16,uVar17);
      uVar17 = (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      iVar12 = FUN_7ffe9a4ab0b0(uVar17,uVar7);
      fVar22 = _DAT_7ffe9c049cfc;
      iVar12 = ((int)plStack_b8 + iVar9 + iVar11) - iVar12;
      iVar9 = 0;
      if (-1 < iVar12) {
        iVar9 = iVar12;
      }
      if (iVar8 == 2) {
        plVar14 = (longlong *)
                  (**(code **)(*(longlong *)playerAction + 0x298))
                            (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if ((plVar14 == (longlong *)0x0) ||
           (lVar16 = (**(code **)(*plVar14 + 0x1a8))(plVar14,*(undefined8 *)(*plVar14 + 0x1b0)),
           lVar16 == 0)) goto LAB_7ffe9a7b3944;
        iVar8 = FUN_7ffe99742ec0(0x1c,_DAT_7ffe9c940d40,lVar16);
        iVar9 = (int)(((float)iVar8 / fVar22) * (float)iVar9);
      }
      uVar17 = (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      uVar7 = (**(code **)(*(longlong *)thisObject + 0x198))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
      lVar16 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
      if (lVar16 == 0) goto LAB_7ffe9a7b3944;
      uVar13 = FUN_7ffe99742ec0(9,_DAT_7ffe9c93ed20,lVar16);
      fVar23 = (float)FUN_7ffe9a4a9110(thisObject,uVar17,uVar7,uVar13,&uStack_c5,0);
      uVar17 = (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      fVar24 = (float)FUN_7ffe9a4aad20(uVar17,mobAction,0);
      fVar25 = *(float *)(thisObject + 0x128);
      plStack_b8 = (longlong *)
                   CONCAT44(plStack_b8._4_4_,(int)(fVar24 * (float)(int)((float)iVar9 * fVar23)));
      plVar14 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar14 == (longlong *)0x0) ||
         (lVar16 = (**(code **)(*plVar14 + 0x1c8))(plVar14,*(undefined8 *)(*plVar14 + 0x1d0)),
         lVar16 == 0)) goto LAB_7ffe9a7b3944;
      iVar8 = func_0x7ffe9a7c8f00(lVar16,0x3a);
      plVar14 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar14 == (longlong *)0x0) ||
         (puVar18 = (undefined *)(**(code **)(*plVar14 + 0x218))(plVar14),
         puVar18 == (undefined *)0x0)) goto LAB_7ffe9a7b3944;
      fVar23 = GemCartBufferManager_GetNormalAttackRate(puVar18,(undefined *)0x0);
      fVar23 = fVar23 + (float)iVar8 + fVar25;
      plVar14 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar14 == (longlong *)0x0) ||
         (lVar16 = (**(code **)(*plVar14 + 0x1c8))(plVar14,*(undefined8 *)(*plVar14 + 0x1d0)),
         lVar16 == 0)) goto LAB_7ffe9a7b3944;
      cVar5 = FUN_7ffe9abc2210(lVar16,0x57,&lStack_90,_DAT_7ffe9c9689a0);
      if (cVar5 != '\0') {
        if (lStack_90 == 0) goto LAB_7ffe9a7b3944;
        iVar8 = func_0x7ffe9a7a2140(lStack_90,0x14);
        bVar4 = thisObject[0x14];
        plVar14 = (longlong *)
                  (**(code **)(*(longlong *)playerAction + 0x298))
                            (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if ((plVar14 == (longlong *)0x0) ||
           (lVar16 = (**(code **)(*plVar14 + 0x198))(plVar14,*(undefined8 *)(*plVar14 + 0x1a0)),
           lVar16 == 0)) goto LAB_7ffe9a7b3944;
        iVar9 = FUN_7ffe99742ec0(5,_DAT_7ffe9c940d40,lVar16);
        fVar23 = fVar23 + (float)(int)(iVar9 / (int)((0xc - (uint)(byte)thisObject[0x14]) * 5) +
                                      (uint)bVar4 * iVar8 * 10);
        if (lStack_90 == 0) goto LAB_7ffe9a7b3944;
        FUN_7ffe9a7915b0(lStack_90,0);
      }
      uVar7 = (**(code **)(*(longlong *)thisObject + 0x198))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
      plVar14 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar14 == (longlong *)0x0) ||
         (lVar16 = (**(code **)(*plVar14 + 0x1a8))(plVar14,*(undefined8 *)(*plVar14 + 0x1b0)),
         lVar16 == 0)) goto LAB_7ffe9a7b3944;
      uVar13 = FUN_7ffe99742ec0(0xf,_DAT_7ffe9c940d40,lVar16);
      cVar5 = acStackX_10[0];
      uVar17 = (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      fVar25 = (float)(**(code **)(*(longlong *)thisObject + 0x6a8))
                                (thisObject,uVar7,uVar13,cVar5,uVar17,
                                 *(undefined8 *)(*(longlong *)thisObject + 0x6b0));
      lVar16 = FUN_7ffe99742ec0(8,_DAT_7ffe9c9724e0,mobAction);
      if (lVar16 == 0) goto LAB_7ffe9a7b3944;
      iVar8 = func_0x7ffe9a3604f0(lVar16,1,0);
      uVar6 = 0;
      fVar24 = (float)(int)plStack_b8;
      plVar14 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar14 == (longlong *)0x0) ||
         (lVar16 = (**(code **)(*plVar14 + 0x1c8))(plVar14,*(undefined8 *)(*plVar14 + 0x1d0)),
         lVar16 == 0)) goto LAB_7ffe9a7b3944;
      cVar5 = FUN_7ffe9abc2210(lVar16,0x52,&plStack_88,_DAT_7ffe9c96a188);
      if (cVar5 != '\0') {
        if (plStack_88 == (longlong *)0x0) goto LAB_7ffe9a7b3944;
        uVar6 = *(undefined1 *)((longlong)plStack_88 + 0x1c);
        (**(code **)(*plStack_88 + 0x278))(plStack_88,1,*(undefined8 *)(*plStack_88 + 0x280));
      }
      uVar17 = (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      fVar26 = (float)FUN_7ffe9a4a7d60(thisObject,uVar17,0);
      lVar16 = *(longlong *)mobAction;
      if ((*(byte *)(_DAT_7ffe9c923808 + 0x130) <= *(byte *)(lVar16 + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(lVar16 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c923808 + 0x130) * 8)
          == _DAT_7ffe9c923808)) {
        if ((*(byte *)(lVar16 + 0x130) < *(byte *)(_DAT_7ffe9c923808 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(lVar16 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c923808 + 0x130) * 8
             ) != _DAT_7ffe9c923808)) {
          FUN_7ffe9996c950(mobAction);
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
        cVar5 = FUN_7ffe9ab798a0(mobAction,0x5a,alStack_70,_DAT_7ffe9c8f1e88);
        if (cVar5 != '\0') {
          if (alStack_70[0] == 0) goto LAB_7ffe9a7b3944;
          fVar27 = (float)FUN_7ffe9a37a550(alStack_70[0],0);
          fVar26 = fVar26 - fVar27;
        }
      }
      if (plStack_88 != (longlong *)0x0) {
        (**(code **)(*plStack_88 + 0x278))(plStack_88,uVar6,*(undefined8 *)(*plStack_88 + 0x280));
      }
      fVar27 = (float)FUN_7ffe9a4a8c60(playerAction,mobAction,0);
      uVar17 = (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      fVar28 = (float)FUN_7ffe9a4a97e0(thisObject,uVar17,0);
      iVar8 = (int)(fVar28 * (float)(int)((float)(int)((float)(int)(((float)iVar8 / fVar22) *
                                                                   (float)(int)((float)(int)((fVar23
                                                                                             / 
                                                  fVar22) * fVar24) * fVar25)) * fVar26) * fVar27));
      cVar5 = FUN_7ffe9a4ac1c0(thisObject,mobAction,&fStack_b0,0);
      fVar25 = _DAT_7ffe9c049f04;
      if (cVar5 != '\0') {
        iVar8 = (int)((float)iVar8 * fStack_b0);
      }
      if (iStack_c4 == 2) {
        lVar16 = FUN_7ffe99742ec0(0xb,_DAT_7ffe9c9724e0,mobAction);
        if (lVar16 == 0) goto LAB_7ffe9a7b3944;
        cVar5 = FUN_7ffe9a2ac880(lVar16,4,&plStack_a8);
        if (cVar5 != '\0') {
          if (plStack_a8 == (longlong *)0x0) goto LAB_7ffe9a7b3944;
          if (((*(byte *)(*plStack_a8 + 0x130) < *(byte *)(_DAT_7ffe9c91aa80 + 0x130)) ||
              (*(longlong *)
                (*(longlong *)(*plStack_a8 + 200) + -8 +
                (ulonglong)*(byte *)(_DAT_7ffe9c91aa80 + 0x130) * 8) != _DAT_7ffe9c91aa80)) ||
             (plStack_a8 == (longlong *)0x0)) {
            FUN_7ffe9996c950(plStack_a8);
            pcVar2 = (code *)swi(3);
            (*pcVar2)();
            return;
          }
          iVar9 = FUN_7ffe9a2ea460(plStack_a8,0);
          fVar25 = fVar25 - (float)iVar9;
          if (fVar25 < 0.0) {
            fVar25 = 0.0;
          }
        }
        iVar8 = (int)((fVar25 / fVar22) * (float)iVar8);
      }
      plVar14 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar14 == (longlong *)0x0) ||
         (lVar16 = (**(code **)(*plVar14 + 0x1d8))(plVar14,*(undefined8 *)(*plVar14 + 0x1e0)),
         lVar16 == 0)) goto LAB_7ffe9a7b3944;
      fVar25 = (float)FUN_7ffe9a4ebf80(lVar16,0);
      iVar8 = (int)(fVar25 * (float)iVar8);
      plVar14 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar14 == (longlong *)0x0) ||
         (puVar18 = (undefined *)
                    (**(code **)(*plVar14 + 0x218))(plVar14,*(undefined8 *)(*plVar14 + 0x220)),
         puVar18 == (undefined *)0x0)) goto LAB_7ffe9a7b3944;
      bVar4 = GemCartBufferManager_ContainsBuffer(puVar18,0x45,(undefined *)0x0);
      iVar9 = iVar8;
      if (bVar4 != 0) {
        FUN_7ffe99749320(0x17,_DAT_7ffe9c9724e0,mobAction,0x10);
        lVar16 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
        if (lVar16 == 0) goto LAB_7ffe9a7b3944;
        iVar9 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ed20,lVar16);
        iVar9 = (int)((float)iVar9 / fVar22);
        if (iVar9 < 1) {
          iVar9 = 1;
        }
        if (iVar8 < iVar9) {
          iVar9 = iVar8;
        }
      }
      FUN_7ffe9a4ac310(thisObject,mobAction,auStack_98,&uStack_9c,0);
      iVar8 = FUN_7ffe9a4ad9c0(thisObject,iVar9,mobAction,&uStack_c7,&uStack_c6,0);
      if (iVar8 < 1) {
        iVar8 = 1;
      }
      fVar22 = (float)FUN_7ffe9a4adbc0(playerAction,mobAction,0);
      iStack_ac = (int)(fVar22 * (float)iVar8);
      iVar9 = iStack_c4;
      if (iStack_ac < 1) {
        iStack_ac = 1;
      }
    }
    lVar16 = func_0x7ffe99940040(_DAT_7ffe9c920098);
    FUN_7ffe9a8f6350(lVar16,mobAction,0);
    if (iStack_c0 == 0) goto LAB_7ffe9a7b2db1;
    if (lVar16 == 0) goto LAB_7ffe9a7b3944;
    *(undefined4 *)(lVar16 + 0x40) = 1;
    *(int *)(lVar16 + 0x18) = iStack_ac;
    *(int *)(lVar16 + 0x1c) = iStack_c0;
    *(int *)(lVar16 + 0x34) = iVar9;
    *(char *)(lVar16 + 0x30) = acStackX_10[0];
    *(undefined1 *)(lVar16 + 0x31) = uStack_c7;
    *(undefined1 *)(lVar16 + 0x32) = uStack_c6;
    *(undefined1 *)(lVar16 + 0x60) = uStack_c5;
    FUN_7ffe9a4b37b0(thisObject,lVar16,iStack_ac,0);
  }
  else {
    plVar14 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if ((plVar14 == (longlong *)0x0) ||
       (lVar16 = (**(code **)(*plVar14 + 0x1c8))(plVar14,*(undefined8 *)(*plVar14 + 0x1d0)),
       lVar16 == 0)) goto LAB_7ffe9a7b3944;
    cVar5 = FUN_7ffe9abc2210(lVar16,0x57,&lStack_78,_DAT_7ffe9c9689a0);
    iVar9 = 0;
    if (cVar5 != '\0') {
      if (lStack_78 == 0) goto LAB_7ffe9a7b3944;
      FUN_7ffe9a7915b0(lStack_78,0);
      iVar9 = 0;
    }
LAB_7ffe9a7b2d91:
    lVar16 = func_0x7ffe99940040(_DAT_7ffe9c920098);
    FUN_7ffe9a8f6350(lVar16,mobAction,0);
LAB_7ffe9a7b2db1:
    if (lVar16 == 0) goto LAB_7ffe9a7b3944;
    *(undefined4 *)(lVar16 + 0x18) = 0;
    *(undefined4 *)(lVar16 + 0x40) = 0;
    cVar5 = FUN_7ffe99742ec0(0x14,_DAT_7ffe9c9724e0,mobAction);
    if (cVar5 != '\0') {
      iVar9 = 3;
    }
    *(uint *)(lVar16 + 0x1c) = (uint)(cVar5 != '\0');
    *(int *)(lVar16 + 0x34) = iVar9;
    uVar17 = *(undefined8 *)(lVar16 + 0x48);
    uVar19 = func_0x7ffe99940040(_DAT_7ffe9c94aa68);
    FUN_7ffe9a8fff70(uVar19,uVar17,0);
    *(undefined8 *)(lVar16 + 0x38) = uVar19;
    il2cpp_write_barrier_0();
    if (*(longlong *)(lVar16 + 0x38) == 0) goto LAB_7ffe9a7b3944;
    *(undefined4 *)(*(longlong *)(lVar16 + 0x38) + 0x14) = 0;
  }
  lVar15 = *(longlong *)(thisObject + 0x120);
  if (lVar15 != 0) {
    while( true ) {
      lVar21 = _DAT_7ffe9c913488;
      uVar10 = (uint)plVar20;
      if ((int)*(uint *)(lVar15 + 0x18) <= (int)uVar10) break;
      if (*(uint *)(lVar15 + 0x18) <= uVar10) goto LAB_7ffe9a7b395c;
      uVar7 = *(undefined4 *)(lVar15 + 0x20 + (longlong)(int)uVar10 * 4);
      plVar20 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if (plVar20 == (longlong *)0x0) goto LAB_7ffe9a7b3944;
      lVar21 = (**(code **)(*plVar20 + 0x1c8))(plVar20,*(undefined8 *)(*plVar20 + 0x1d0));
      if (lVar21 == 0) goto LAB_7ffe9a7b3944;
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
LAB_7ffe9a7b395c:
            FUN_7ffe9996d790();
            pcVar2 = (code *)swi(3);
            (*pcVar2)();
            return;
          }
          *(longlong *)(lVar1 + 0x20 + (longlong)(int)uVar10 * 8) = lVar16;
          il2cpp_write_barrier_0();
        }
        else {
          FUN_7ffe9afd58b0(lVar15,lVar16,
                           *(undefined8 *)
                            (*(longlong *)(*(longlong *)(lVar21 + 0x20) + 0xc0) + 0x70));
        }
        return;
      }
    }
  }
LAB_7ffe9a7b3944:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

