
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void NormalAttackAction_calcPlayerToMobDamage
               (undefined *thisObject,undefined *playerAction,undefined *mobAction,
               undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  bool bVar3;
  float fVar4;
  longlong lVar5;
  char cVar6;
  undefined1 uVar7;
  byte bVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  int iVar13;
  int iVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  undefined *puVar17;
  longlong lVar18;
  longlong *plVar19;
  longlong *plVar20;
  longlong *plVar21;
  longlong lVar22;
  undefined8 uVar23;
  undefined8 uVar24;
  undefined8 *puVar25;
  longlong *plVar26;
  ushort uVar27;
  uint uVar28;
  float fVar29;
  float fVar30;
  float fVar31;
  float fVar32;
  undefined8 extraout_XMM0_Qb;
  float fVar33;
  undefined1 auVar34 [16];
  undefined1 auVar35 [16];
  char acStackX_10 [8];
  longlong *plStackX_18;
  undefined8 in_stack_fffffffffffffe78;
  int *resistReactionType;
  undefined1 *puVar36;
  char *pcVar37;
  undefined1 uStack_138;
  undefined1 uStack_137;
  undefined1 auStack_136 [2];
  uint uStack_134;
  undefined1 uStack_130;
  undefined1 auStack_12f [3];
  int iStack_12c;
  uint uStack_128;
  longlong *plStack_120;
  int aiStack_118 [2];
  longlong lStack_110;
  float fStack_108;
  int iStack_104;
  int aiStack_100 [4];
  longlong *plStack_f0;
  longlong *plStack_e8;
  longlong lStack_e0;
  longlong *plStack_d8;
  longlong *plStack_d0;
  longlong *plStack_c8;
  longlong lStack_c0;
  longlong lStack_b8;
  longlong lStack_b0;
  longlong lStack_a8;
  longlong *plStack_a0;
  longlong alStack_98 [12];
  
  plStackX_18 = (longlong *)mobAction;
  if (DAT_7ffe9cadde87 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92eda0);
    FUN_7ffe9996d590(&DAT_7ffe9c920098);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1e88);
    FUN_7ffe9996d590(&DAT_7ffe9c91aa80);
    FUN_7ffe9996d590(&DAT_7ffe9c923808);
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c913488);
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    FUN_7ffe9996d590(&DAT_7ffe9c96a1b0);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c923468);
    FUN_7ffe9996d590(&DAT_7ffe9c948740);
    FUN_7ffe9996d590(&DAT_7ffe9c96a188);
    FUN_7ffe9996d590(&DAT_7ffe9c96a320);
    FUN_7ffe9996d590(&DAT_7ffe9c94a078);
    FUN_7ffe9996d590(&DAT_7ffe9c94aa68);
    FUN_7ffe9996d590(&DAT_7ffe9c96f7c8);
    FUN_7ffe9996d590(&DAT_7ffe9c8fcc10);
    DAT_7ffe9cadde87 = '\x01';
  }
  plStack_d0 = (longlong *)0x0;
  plStack_c8 = (longlong *)0x0;
  plStack_e8 = (longlong *)0x0;
  lStack_e0 = 0;
  lStack_a8 = 0;
  fStack_108 = 0.0;
  iStack_104 = 0;
  aiStack_100[0] = 0;
  plStack_f0 = (longlong *)0x0;
  lStack_b0 = 0;
  plStack_a0 = (longlong *)0x0;
  alStack_98[1] = 0;
  aiStack_100[1] = 0;
  auStack_12f[0] = 0;
  puVar17 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c8fcc10);
  GemCartMasterData__ctor(puVar17,(undefined *)0x0);
  if (puVar17 == (undefined *)0x0) goto LAB_7ffe9a49c468;
  plVar26 = (longlong *)(puVar17 + 0x10);
  *plVar26 = (longlong)playerAction;
  il2cpp_write_barrier_0();
  lVar18 = func_0x7ffe99940040(_DAT_7ffe9c920098);
  FUN_7ffe9a8f6350(lVar18,mobAction,0);
  plVar19 = (longlong *)*plVar26;
  if ((plVar19 == (longlong *)0x0) ||
     (plVar19 = (longlong *)
                (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0)),
     plVar19 == (longlong *)0x0)) goto LAB_7ffe9a49c468;
  plVar20 = (longlong *)(**(code **)(*plVar19 + 0x1a8))(plVar19,*(undefined8 *)(*plVar19 + 0x1b0));
  plVar19 = (longlong *)*plVar26;
  plStack_120 = plVar20;
  if ((plVar19 == (longlong *)0x0) ||
     (plVar19 = (longlong *)
                (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0)),
     plVar19 == (longlong *)0x0)) goto LAB_7ffe9a49c468;
  plVar21 = (longlong *)(**(code **)(*plVar19 + 0x198))(plVar19,*(undefined8 *)(*plVar19 + 0x1a0));
  plVar19 = (longlong *)0x0;
  if (plVar21 != (longlong *)0x0) {
    if ((*(byte *)(*plVar21 + 0x130) < *(byte *)(_DAT_7ffe9c923468 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*plVar21 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c923468 + 0x130) * 8)
        != _DAT_7ffe9c923468)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    if (bVar3) {
      plVar19 = plVar21;
    }
  }
  plVar21 = (longlong *)*plVar26;
  if ((plVar21 == (longlong *)0x0) ||
     (plVar21 = (longlong *)
                (**(code **)(*plVar21 + 0x298))(plVar21,*(undefined8 *)(*plVar21 + 0x2a0)),
     plVar21 == (longlong *)0x0)) goto LAB_7ffe9a49c468;
  lVar22 = (**(code **)(*plVar21 + 0x1c8))(plVar21,*(undefined8 *)(*plVar21 + 0x1d0));
  plStack_d8 = (longlong *)(puVar17 + 0x18);
  *plStack_d8 = lVar22;
  il2cpp_write_barrier_0();
  if (mobAction == (undefined *)0x0) goto LAB_7ffe9a49c468;
  lStack_110 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0);
  acStackX_10[0] = '\0';
  uStack_138 = 0;
  uStack_137 = 0;
  auStack_136[0] = 0;
  uStack_130 = 0;
  uStack_128 = 0;
  aiStack_100[2] = 1;
  iStack_12c = 0;
  aiStack_118[0] = 0;
  if ((thisObject[0x104] & 2) == 0) {
    plVar21 = (longlong *)*plVar26;
    if (((plVar21 == (longlong *)0x0) ||
        (plVar21 = (longlong *)
                   (**(code **)(*plVar21 + 0x298))(plVar21,*(undefined8 *)(*plVar21 + 0x2a0)),
        plVar21 == (longlong *)0x0)) ||
       (lVar22 = (**(code **)(*plVar21 + 0x1c8))(plVar21,*(undefined8 *)(*plVar21 + 0x1d0)),
       lVar22 == 0)) goto LAB_7ffe9a49c468;
    FUN_7ffe9a7cb960(lVar22,0x2a6,1,0);
  }
  if (plVar19 == (longlong *)0x0) {
    if (plVar20 == (longlong *)0x0) goto LAB_7ffe9a49c468;
    uVar9 = FUN_7ffe99742ec0(0x1b,_DAT_7ffe9c940d40,plVar20);
  }
  else {
    uVar28 = *(uint *)(thisObject + 0x104);
    FUN_7ffe9a484e10(plVar19,0);
    PlayerSecondaryStatus_GetCrtConstant
              ((undefined *)plVar19,~(byte)(uVar28 >> 1) & 1,(undefined *)0x0);
    uVar9 = FUN_7ffe9a472c30(plVar19);
  }
  cVar6 = FUN_7ffe9a4b33f0(thisObject,uVar9,mobAction,0);
  uStack_134 = 1;
  if (cVar6 != '\0') {
    uStack_134 = 2;
  }
  if (lStack_110 == 0) goto LAB_7ffe9a49c468;
  iVar10 = FUN_7ffe99742ec0(2,_DAT_7ffe9c93ed20,lStack_110);
  fVar31 = _DAT_7ffe9c049b18;
  if ((*(longlong *)(puVar17 + 0x18) == 0) ||
     (lVar22 = *(longlong *)(*(longlong *)(puVar17 + 0x18) + 0x50), lVar22 == 0))
  goto LAB_7ffe9a49c468;
  cVar6 = FUN_7ffe9ad8e670(lVar22,0x324,&plStack_d0,_DAT_7ffe9c934418);
  fVar32 = _DAT_7ffe9c049b34;
  fVar33 = fVar31;
  if (cVar6 != '\0') {
    if (plStack_d0 == (longlong *)0x0) goto LAB_7ffe9a49c468;
    iVar11 = (**(code **)(*plStack_d0 + 0x1f8))
                       (plStack_d0,0x32,*(undefined8 *)(*plStack_d0 + 0x200));
    fVar33 = (float)iVar11 * fVar32 + fVar31;
  }
  lVar22 = FUN_7ffe99742ec0(0xb,_DAT_7ffe9c9724e0,mobAction);
  if (lVar22 == 0) goto LAB_7ffe9a49c468;
  cVar6 = FUN_7ffe9a2ac880(lVar22,10,&plStack_c8);
  if (cVar6 != '\0') {
    if (plStack_c8 == (longlong *)0x0) goto LAB_7ffe9a49c468;
    iVar11 = (**(code **)(*plStack_c8 + 0x1a8))(plStack_c8,*(undefined8 *)(*plStack_c8 + 0x1b0));
    if (0x32 < iVar11) {
      iVar11 = 0x32;
    }
    fVar33 = fVar33 - (float)iVar11 * fVar32;
  }
  lStack_c0 = 0;
  if ((*(longlong *)(puVar17 + 0x18) == 0) ||
     (lVar22 = *(longlong *)(*(longlong *)(puVar17 + 0x18) + 0x50), lVar22 == 0))
  goto LAB_7ffe9a49c468;
  cVar6 = FUN_7ffe9ad8e670(lVar22,0x8f,&lStack_c0,_DAT_7ffe9c934418);
  if (cVar6 != '\0') {
    if (*(longlong *)(puVar17 + 0x18) == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a7ca6f0(*(longlong *)(puVar17 + 0x18),0x8f,0);
  }
  lStack_b8 = 0;
  if ((*(longlong *)(puVar17 + 0x18) == 0) ||
     (lVar22 = *(longlong *)(*(longlong *)(puVar17 + 0x18) + 0x50), lVar22 == 0))
  goto LAB_7ffe9a49c468;
  cVar6 = FUN_7ffe9ad8e670(lVar22,0x26f,&lStack_b8,_DAT_7ffe9c934418);
  if (cVar6 != '\0') {
    if (*(longlong *)(puVar17 + 0x18) == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a7ca6f0(*(longlong *)(puVar17 + 0x18),0x26f,0);
  }
  plVar19 = (longlong *)*plVar26;
  if (plVar19 == (longlong *)0x0) goto LAB_7ffe9a49c468;
  uVar23 = (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0));
  uVar9 = (**(code **)(*(longlong *)thisObject + 0x298))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  lVar22 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,plStackX_18);
  if (lVar22 == 0) goto LAB_7ffe9a49c468;
  uVar7 = FUN_7ffe9a4daa60(lVar22,0x21);
  pcVar37 = acStackX_10;
  uVar24 = CONCAT71((int7)((ulonglong)in_stack_fffffffffffffe78 >> 8),uVar7);
  bVar8 = (**(code **)(*(longlong *)thisObject + 0x688))
                    (thisObject,uVar23,(int)((float)iVar10 * fVar33),uVar9,uVar24,pcVar37,
                     *(undefined8 *)(*(longlong *)thisObject + 0x690));
  uVar9 = (undefined4)((ulonglong)uVar24 >> 0x20);
  uVar15 = (undefined4)((ulonglong)pcVar37 >> 0x20);
  plVar19 = (longlong *)(puVar17 + 0x18);
  if (lStack_c0 != 0) {
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a7c26c0(*plVar19,lStack_c0,0);
  }
  if (lStack_b8 != 0) {
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a7c26c0(*plVar19,lStack_b8,0);
  }
  bVar8 = NormalAttackAction_RampageHitCheck
                    (thisObject,(undefined *)*plVar26,bVar8,(undefined *)0x0);
  alStack_98[0] = 0;
  if ((*plVar19 == 0) || (lVar22 = *(longlong *)(*plVar19 + 0x50), lVar22 == 0))
  goto LAB_7ffe9a49c468;
  cVar6 = FUN_7ffe9ad8e670(lVar22,0x27f,alStack_98,_DAT_7ffe9c934418);
  if (cVar6 != '\0') {
    bVar8 = 1;
    uStack_134 = 2;
    uVar23 = func_0x7ffe99940040(_DAT_7ffe9c92eda0);
    FUN_7ffe999e6880(uVar23,puVar17,_DAT_7ffe9c96f7c8,0);
    FUN_7ffe9a4b20c0(thisObject,uVar23,0);
  }
  plVar19 = (longlong *)*plVar26;
  if (((plVar19 == (longlong *)0x0) ||
      (plVar19 = (longlong *)
                 (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0)),
      plVar19 == (longlong *)0x0)) ||
     (lVar22 = (**(code **)(*plVar19 + 0x1e8))(plVar19,*(undefined8 *)(*plVar19 + 0x1f0)),
     lVar22 == 0)) goto LAB_7ffe9a49c468;
  cVar6 = FUN_7ffe9a4daa60(lVar22,0x21);
  if ((cVar6 != '\0') && (cVar6 = func_0x7ffe9a4ad2d0(thisObject,2), cVar6 == '\0')) {
    if (acStackX_10[0] == '\0') {
      acStackX_10[0] = '\x01';
    }
    else {
      bVar8 = 0;
      uStack_134 = 0;
    }
  }
  plVar19 = plStackX_18;
  cVar6 = FUN_7ffe99742ec0(0x14,_DAT_7ffe9c9724e0,plStackX_18);
  if (cVar6 == '\0') {
    if ((bVar8 != 0) || (uStack_134 == 2)) goto LAB_7ffe9a49aba1;
    uStack_134 = 0;
    uVar28 = 0;
LAB_7ffe9a49ac70:
    uStack_128 = 0;
    uVar12 = 0;
    if (plStack_120 == (longlong *)0x0) goto LAB_7ffe9a49c468;
  }
  else {
    uStack_134 = 0;
LAB_7ffe9a49aba1:
    uVar28 = uStack_134;
    uVar12 = (**(code **)(*(longlong *)thisObject + 0x198))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
    resistReactionType = aiStack_118;
    uVar15 = 0;
    puVar17 = PlayerAttackBase_CalcHitReaction
                        (thisObject,(undefined *)(ulonglong)uVar12,(undefined *)*plVar26,
                         (undefined *)plVar19,(undefined *)resistReactionType,(undefined *)0x0);
    uVar9 = (undefined4)((ulonglong)resistReactionType >> 0x20);
    iStack_12c = (int)puVar17;
    if ((*(int *)(thisObject + 0xfc) - 10U < 2) && ((thisObject[0x104] & 2) != 0)) {
      NormalAttackAction_calcRampageFinish
                (thisObject,(undefined *)*plVar26,(undefined *)plVar19,(undefined *)0x0);
      return;
    }
    if (iStack_12c == 1) goto LAB_7ffe9a49ac70;
    lVar22 = func_0x7ffe99940040(_DAT_7ffe9c94a078);
    FUN_7ffe9a6596c0(lVar22,0);
    plVar19 = (longlong *)(thisObject + 0x180);
    *plVar19 = lVar22;
    il2cpp_write_barrier_0();
    lVar22 = *plVar19;
    uVar9 = (**(code **)(*(longlong *)thisObject + 0x188))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
    if (lVar22 == 0) goto LAB_7ffe9a49c468;
    *(undefined4 *)(lVar22 + 0x20) = uVar9;
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a658f90(*plVar19,0,1,0);
    iVar10 = FUN_7ffe9a494ae0(thisObject,*plVar26,plStackX_18,uVar28,0);
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657a50(*plVar19,7);
    if (*plStack_d8 == 0) goto LAB_7ffe9a49c468;
    iVar11 = func_0x7ffe9a7c8f00(*plStack_d8,0x38);
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657a50(*plVar19,8);
    iVar13 = NormalAttackAction_calcRampageConstantDamage
                       (thisObject,(undefined *)*plVar26,(undefined *)0x0);
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657a50(*plVar19,8);
    iVar14 = FUN_7ffe9a7a6a60(*plVar26,plStackX_18,0);
    iVar10 = iVar13 + iVar14 / 2 + iVar11 + iVar10;
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657a50(*plVar19,8);
    if (thisObject[0x175] != '\0') {
      plVar20 = (longlong *)*plVar26;
      if (plVar20 == (longlong *)0x0) goto LAB_7ffe9a49c468;
      uVar23 = (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0));
      iVar11 = FUN_7ffe9a7d3200(uVar23,0);
      iVar10 = iVar10 + iVar11;
      if (*plVar19 == 0) goto LAB_7ffe9a49c468;
      FUN_7ffe9a657a50(*plVar19,8);
    }
    if (thisObject[0x176] != '\0') {
      plVar20 = (longlong *)*plVar26;
      if (plVar20 == (longlong *)0x0) goto LAB_7ffe9a49c468;
      uVar23 = (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0));
      iVar11 = FUN_7ffe9a792260(uVar23,0);
      iVar10 = iVar10 + iVar11;
      if (*plVar19 == 0) goto LAB_7ffe9a49c468;
      FUN_7ffe9a657a50(*plVar19,8);
    }
    fVar4 = _DAT_7ffe9c049cfc;
    fVar33 = fVar31;
    if (thisObject[0x140] != '\0') {
      iVar11 = FUN_7ffe9a4b2d40(thisObject,*plVar26,0);
      iVar10 = iVar10 + iVar11;
      iVar11 = FUN_7ffe9a4b2a70(*plVar26,0);
      fVar33 = (float)iVar11 / fVar4;
    }
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657a50(*plVar19,0xb);
    iVar11 = FUN_7ffe9a495060(thisObject,*plVar26,lStack_110,0);
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657a50(*plVar19,10);
    iVar13 = 0;
    if (-1 < iVar10 - iVar11) {
      iVar13 = iVar10 - iVar11;
    }
    if (uStack_134 == 2) {
      if ((*plVar19 == 0) || (FUN_7ffe9a658f90(*plVar19,6,1), plStack_120 == (longlong *)0x0))
      goto LAB_7ffe9a49c468;
      iVar10 = FUN_7ffe99742ec0(0x1c,_DAT_7ffe9c940d40,plStack_120);
      iVar13 = (int)((float)iVar13 * ((float)iVar10 / fVar4));
    }
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar19,0xd);
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar19,0x13);
    plVar20 = (longlong *)*plVar26;
    if (plVar20 == (longlong *)0x0) goto LAB_7ffe9a49c468;
    uVar23 = (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0));
    uVar9 = (**(code **)(*(longlong *)thisObject + 0x198))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
    uVar15 = FUN_7ffe99742ec0(9,_DAT_7ffe9c93ed20);
    fVar29 = (float)FUN_7ffe9a4a9110(thisObject,uVar23,uVar9,uVar15,auStack_136,0);
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar19,0xf);
    plVar20 = (longlong *)*plVar26;
    if (plVar20 == (longlong *)0x0) goto LAB_7ffe9a49c468;
    uVar23 = (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0));
    fVar30 = (float)FUN_7ffe9a4aad20(uVar23,plStackX_18);
    iVar10 = (int)((float)(int)((float)(int)((float)iVar13 * fVar33) * fVar29) * fVar30);
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar19,0x10);
    if (thisObject[0x130] != '\0') {
      iVar10 = (int)((float)iVar10 * *(float *)(thisObject + 300));
      if (*plVar19 == 0) goto LAB_7ffe9a49c468;
      FUN_7ffe9a657c40(*plVar19,0x11);
    }
    plVar20 = (longlong *)*plVar26;
    if (DAT_7ffe9cadde8d == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c96a1b0);
      FUN_7ffe9996d590(&DAT_7ffe9c906b90);
      DAT_7ffe9cadde8d = '\x01';
    }
    plVar21 = plVar20;
    if (plVar20 != (longlong *)0x0) {
      if ((*(byte *)(*plVar20 + 0x130) < *(byte *)(_DAT_7ffe9c96a1b0 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar20 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c96a1b0 + 0x130) * 8
           ) != _DAT_7ffe9c96a1b0)) {
        bVar3 = false;
      }
      else {
        bVar3 = true;
      }
      plVar21 = (longlong *)0x0;
      if (bVar3) {
        plVar21 = plVar20;
      }
    }
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar6 = FUN_7ffe9bda1fa0(plVar21,0);
    if (cVar6 == '\0') {
      if ((plVar21 == (longlong *)0x0) || (plVar21[0x40] == 0)) goto LAB_7ffe9a49c468;
      if (*(int *)(plVar21[0x40] + 0x94) == 1) {
        if (plVar21[0x45] == 0) goto LAB_7ffe9a49c468;
        fVar33 = (float)func_0x7ffe99dfd710(plVar21[0x45],0);
        iVar10 = (int)((fVar33 + fVar31) * (float)iVar10);
      }
      if (plVar21[0x40] == 0) goto LAB_7ffe9a49c468;
      iVar10 = (int)((float)iVar10 * *(float *)(plVar21[0x40] + 0xb0));
    }
    fVar31 = NormalAttackAction_calcRampageSkillRate
                       (thisObject,(undefined *)*plVar26,(undefined *)0x0,(undefined *)0x0);
    bVar3 = false;
    if (thisObject[0x176] != '\0') {
      plVar20 = (longlong *)*plVar26;
      if (plVar20 == (longlong *)0x0) goto LAB_7ffe9a49c468;
      uVar23 = (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0));
      cVar6 = FUN_7ffe9a7b40f0(uVar23,*(undefined4 *)(thisObject + 0x178),0);
      bVar3 = false;
      if (cVar6 != '\0') {
        bVar3 = true;
      }
    }
    if (thisObject[0x175] != '\0') {
      plVar20 = (longlong *)*plVar26;
      if (((plVar20 == (longlong *)0x0) ||
          (plVar20 = (longlong *)
                     (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0)),
          plVar20 == (longlong *)0x0)) ||
         (lVar22 = (**(code **)(*plVar20 + 0x1c8))(plVar20,*(undefined8 *)(*plVar20 + 0x1d0)),
         lVar22 == 0)) goto LAB_7ffe9a49c468;
      cVar6 = FUN_7ffe9a7cbb30(lVar22,0x26b,&plStack_e8,0);
      if (cVar6 != '\0') {
        if (plStack_e8 == (longlong *)0x0) goto LAB_7ffe9a49c468;
        if (((*(byte *)(*plStack_e8 + 0x130) < *(byte *)(_DAT_7ffe9c948740 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*plStack_e8 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c948740 + 0x130) * 8) != _DAT_7ffe9c948740)) ||
           (plStack_e8 == (longlong *)0x0)) {
          FUN_7ffe9996c950(plStack_e8);
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
        func_0x7ffe9a329d50(plStack_e8,0);
      }
    }
    if (*plStack_d8 == 0) goto LAB_7ffe9a49c468;
    iVar11 = func_0x7ffe9a7c8f00(*plStack_d8,0x3a);
    plVar20 = (longlong *)*plVar26;
    if (((plVar20 == (longlong *)0x0) ||
        (plVar20 = (longlong *)
                   (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0)),
        plVar20 == (longlong *)0x0)) ||
       (puVar17 = (undefined *)(**(code **)(*plVar20 + 0x218))(plVar20), puVar17 == (undefined *)0x0
       )) goto LAB_7ffe9a49c468;
    fVar33 = GemCartBufferManager_GetNormalAttackRate(puVar17,(undefined *)0x0);
    fVar31 = fVar33 * fVar32 + (float)iVar11 / fVar4 + fVar31;
    cVar6 = func_0x7ffe9a4ad2d0(thisObject,0x400,0);
    if (cVar6 != '\0') {
      plVar20 = (longlong *)*plVar26;
      if ((((plVar20 == (longlong *)0x0) ||
           (plVar20 = (longlong *)
                      (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0)),
           plVar20 == (longlong *)0x0)) ||
          (lVar22 = (**(code **)(*plVar20 + 0x1b8))(plVar20,*(undefined8 *)(*plVar20 + 0x1c0)),
          lVar22 == 0)) || (*(longlong *)(lVar22 + 0x68) == 0)) goto LAB_7ffe9a49c468;
      cVar6 = FUN_7ffe9ad8e670(*(longlong *)(lVar22 + 0x68),0x128,&plStack_f0,_DAT_7ffe9c935bd0);
      if (cVar6 != '\0') {
        if (plStack_f0 == (longlong *)0x0) goto LAB_7ffe9a49c468;
        iVar11 = (**(code **)(*plStack_f0 + 0x178))
                           (plStack_f0,0x1a,*(undefined8 *)(*plStack_f0 + 0x180));
        fVar31 = fVar31 + (float)iVar11 / fVar4;
      }
      plVar20 = (longlong *)*plVar26;
      if (((plVar20 == (longlong *)0x0) ||
          (plVar20 = (longlong *)
                     (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0)),
          plVar20 == (longlong *)0x0)) ||
         ((lVar22 = (**(code **)(*plVar20 + 0x1b8))(plVar20,*(undefined8 *)(*plVar20 + 0x1c0)),
          lVar22 == 0 || (*(longlong *)(lVar22 + 0x68) == 0)))) goto LAB_7ffe9a49c468;
      cVar6 = FUN_7ffe9ad8e670(*(longlong *)(lVar22 + 0x68),0x129,&plStack_f0,_DAT_7ffe9c935bd0);
      if (cVar6 != '\0') {
        if (plStack_f0 == (longlong *)0x0) goto LAB_7ffe9a49c468;
        iVar11 = (**(code **)(*plStack_f0 + 0x178))
                           (plStack_f0,0x1a,*(undefined8 *)(*plStack_f0 + 0x180));
        fVar31 = fVar31 + (float)iVar11 / fVar4;
      }
    }
    if (thisObject[0x176] != '\0') {
      plVar20 = (longlong *)*plVar26;
      if (plVar20 == (longlong *)0x0) goto LAB_7ffe9a49c468;
      uVar23 = (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0));
      fVar32 = (float)FUN_7ffe9a792330(uVar23,0);
      plVar20 = (longlong *)*plVar26;
      if (plVar20 == (longlong *)0x0) goto LAB_7ffe9a49c468;
      uVar23 = (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0));
      iVar11 = FUN_7ffe9a7b3fc0(uVar23,0);
      fVar31 = fVar31 + ((float)iVar11 + fVar32) / fVar4;
    }
    if (plStack_e8 != (longlong *)0x0) {
      if (((*(byte *)(*plStack_e8 + 0x130) < *(byte *)(_DAT_7ffe9c948740 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*plStack_e8 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7ffe9c948740 + 0x130) * 8) != _DAT_7ffe9c948740)) ||
         (plStack_e8 == (longlong *)0x0)) {
        FUN_7ffe9996c950(plStack_e8);
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      func_0x7ffe99a998f0(plStack_e8,0);
    }
    if (bVar3) {
      plVar20 = (longlong *)*plVar26;
      if (((plVar20 == (longlong *)0x0) ||
          (plVar20 = (longlong *)
                     (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0)),
          plVar20 == (longlong *)0x0)) ||
         (lVar22 = (**(code **)(*plVar20 + 0x1c8))(plVar20,*(undefined8 *)(*plVar20 + 0x1d0)),
         lVar22 == 0)) goto LAB_7ffe9a49c468;
      FUN_7ffe9a7cafa0(lVar22,0x26b,0);
    }
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar19,0x12);
    cVar6 = func_0x7ffe9a4ad2d0(thisObject,0x10);
    if (cVar6 != '\0') {
      plVar20 = (longlong *)*plVar26;
      if (((plVar20 == (longlong *)0x0) ||
          (plVar20 = (longlong *)
                     (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0)),
          plVar20 == (longlong *)0x0)) ||
         (lVar22 = (**(code **)(*plVar20 + 0x1c8))(plVar20,*(undefined8 *)(*plVar20 + 0x1d0)),
         lVar22 == 0)) goto LAB_7ffe9a49c468;
      cVar6 = FUN_7ffe9abc2210(lVar22,0x52,&lStack_e0,_DAT_7ffe9c96a188);
      if (cVar6 != '\0') {
        if (lStack_e0 == 0) goto LAB_7ffe9a49c468;
        func_0x7ffe9a7a5e70(lStack_e0,0);
      }
    }
    if (plStack_120 == (longlong *)0x0) goto LAB_7ffe9a49c468;
    uVar9 = FUN_7ffe99742ec0(0xf,_DAT_7ffe9c940d40,plStack_120);
    cVar6 = acStackX_10[0];
    plVar20 = (longlong *)*plVar26;
    if (plVar20 == (longlong *)0x0) goto LAB_7ffe9a49c468;
    uVar23 = (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0));
    fVar32 = (float)(**(code **)(*(longlong *)thisObject + 0x6a8))
                              (thisObject,3,uVar9,cVar6,uVar23,
                               *(undefined8 *)(*(longlong *)thisObject + 0x6b0));
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar19,0x15);
    if (lStack_e0 != 0) {
      func_0x7ffe9a262af0(lStack_e0,0);
    }
    iVar11 = FUN_7ffe99742ec0(0x10,_DAT_7ffe9c93ed20,lStack_110);
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar19,0x17);
    plVar20 = plStack_d8;
    if ((*plStack_d8 == 0) || (lVar22 = *(longlong *)(*plStack_d8 + 0x50), lVar22 == 0))
    goto LAB_7ffe9a49c468;
    cVar6 = FUN_7ffe9ad8e670(lVar22,0x28d,&lStack_a8,_DAT_7ffe9c934418);
    if (cVar6 != '\0') {
      lVar22 = *plVar20;
      if (lVar22 == 0) goto LAB_7ffe9a49c468;
      FUN_7ffe9a7ca6f0(lVar22,0x28d,0);
    }
    plVar21 = (longlong *)*plVar26;
    if (plVar21 == (longlong *)0x0) goto LAB_7ffe9a49c468;
    uVar23 = (**(code **)(*plVar21 + 0x298))(plVar21,*(undefined8 *)(*plVar21 + 0x2a0));
    uVar23 = FUN_7ffe9a4a7d60(thisObject,uVar23,0);
    plVar21 = plStackX_18;
    auVar34._8_4_ = (int)extraout_XMM0_Qb;
    auVar34._0_8_ = uVar23;
    auVar34._12_4_ = (int)((ulonglong)extraout_XMM0_Qb >> 0x20);
    lVar22 = *plStackX_18;
    if ((*(byte *)(_DAT_7ffe9c923808 + 0x130) <= *(byte *)(lVar22 + 0x130)) &&
       (*(longlong *)
         (*(longlong *)(lVar22 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c923808 + 0x130) * 8) ==
        _DAT_7ffe9c923808)) {
      if ((*(byte *)(lVar22 + 0x130) < *(byte *)(_DAT_7ffe9c923808 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(lVar22 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c923808 + 0x130) * 8)
          != _DAT_7ffe9c923808)) {
        FUN_7ffe9996c950(plStackX_18);
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      cVar6 = FUN_7ffe9ab798a0(plStackX_18,0x5a,&lStack_b0,_DAT_7ffe9c8f1e88);
      if (cVar6 != '\0') {
        if (lStack_b0 == 0) goto LAB_7ffe9a49c468;
        fVar33 = (float)FUN_7ffe9a37a550(lStack_b0,0);
        auVar35._4_12_ = auVar34._4_12_;
        auVar35._0_4_ = (float)uVar23 - fVar33;
        uVar23 = auVar35._0_8_;
      }
    }
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar19,0x19);
    if (lStack_a8 != 0) {
      lVar22 = *plVar20;
      if (lVar22 == 0) goto LAB_7ffe9a49c468;
      FUN_7ffe9a7c26c0(lVar22,lStack_a8,0,0);
    }
    fVar33 = (float)FUN_7ffe9a4a8c60(*plVar26,plVar21,0);
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar19,0x1a);
    plVar20 = (longlong *)*plVar26;
    if (plVar20 == (longlong *)0x0) goto LAB_7ffe9a49c468;
    uVar24 = (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0));
    fVar29 = (float)FUN_7ffe9a4a97e0(thisObject,uVar24,0);
    iVar10 = (int)((float)(int)((float)(int)((float)(int)((float)(int)((float)(int)((float)iVar10 *
                                                                                   fVar31) * fVar32)
                                                         * ((float)iVar11 / fVar4)) * (float)uVar23)
                               * fVar33) * fVar29);
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar19,0x1c);
    cVar6 = FUN_7ffe9a4ac1c0(thisObject,plVar21,&fStack_108,0);
    if (cVar6 != '\0') {
      iVar10 = (int)((float)iVar10 * fStack_108);
    }
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar19,0x1d);
    fVar31 = _DAT_7ffe9c049f04;
    if (iStack_12c == 2) {
      lVar22 = FUN_7ffe99742ec0(0xb,_DAT_7ffe9c9724e0,plVar21);
      if (lVar22 == 0) goto LAB_7ffe9a49c468;
      cVar6 = FUN_7ffe9a2ac880(lVar22,4,&plStack_a0);
      if (cVar6 != '\0') {
        if (plStack_a0 == (longlong *)0x0) goto LAB_7ffe9a49c468;
        if (((*(byte *)(*plStack_a0 + 0x130) < *(byte *)(_DAT_7ffe9c91aa80 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*plStack_a0 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c91aa80 + 0x130) * 8) != _DAT_7ffe9c91aa80)) ||
           (plStack_a0 == (longlong *)0x0)) {
          FUN_7ffe9996c950(plStack_a0);
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
        FUN_7ffe9a2ea460(plStack_a0,0);
        if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        fVar31 = (float)func_0x7ffe9b506c10();
      }
      iVar10 = (int)(((float)iVar10 * fVar31) / fVar4);
      if (*plVar19 == 0) goto LAB_7ffe9a49c468;
      FUN_7ffe9a658f90(*plVar19,0x20,1);
      if (*plVar19 == 0) goto LAB_7ffe9a49c468;
      FUN_7ffe9a658e30(*plVar19,0x21);
    }
    plVar20 = (longlong *)*plVar26;
    if (((plVar20 == (longlong *)0x0) ||
        (plVar20 = (longlong *)
                   (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0)),
        plVar20 == (longlong *)0x0)) ||
       (lVar22 = (**(code **)(*plVar20 + 0x1d8))(plVar20,*(undefined8 *)(*plVar20 + 0x1e0)),
       lVar22 == 0)) goto LAB_7ffe9a49c468;
    fVar31 = (float)FUN_7ffe9a4ebf80(lVar22,0);
    iVar10 = (int)((float)iVar10 * fVar31);
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar19,0x22);
    plVar20 = (longlong *)*plVar26;
    if (((plVar20 == (longlong *)0x0) ||
        (plVar20 = (longlong *)
                   (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0)),
        plVar20 == (longlong *)0x0)) ||
       (puVar17 = (undefined *)
                  (**(code **)(*plVar20 + 0x218))(plVar20,*(undefined8 *)(*plVar20 + 0x220)),
       puVar17 == (undefined *)0x0)) goto LAB_7ffe9a49c468;
    bVar8 = GemCartBufferManager_ContainsBuffer(puVar17,0x45,(undefined *)0x0);
    if (bVar8 != 0) {
      lVar22 = *plVar21;
      uVar27 = 0;
      if (*(ushort *)(lVar22 + 0x12e) != 0) {
        do {
          if (*(longlong *)(*(longlong *)(lVar22 + 0xb0) + (ulonglong)uVar27 * 0x10) ==
              _DAT_7ffe9c9724e0) {
            puVar25 = (undefined8 *)
                      ((longlong)
                       (*(int *)(*(longlong *)(lVar22 + 0xb0) + 8 + (ulonglong)uVar27 * 0x10) + 0x17
                       ) * 0x10 + 0x138 + lVar22);
            goto LAB_7ffe9a49bc8a;
          }
          uVar27 = uVar27 + 1;
        } while (uVar27 < *(ushort *)(lVar22 + 0x12e));
      }
      puVar25 = (undefined8 *)FUN_7ffe998ce540(plVar21,_DAT_7ffe9c9724e0,0x17);
LAB_7ffe9a49bc8a:
      (*(code *)*puVar25)(plVar21,0x10,puVar25[1]);
      iVar11 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ed20,lStack_110);
      iVar11 = (int)((float)iVar11 / fVar4);
      if (iVar11 < 1) {
        iVar11 = 1;
      }
      if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      iVar10 = func_0x7ffe9b506d80(iVar10,iVar11,0);
      if (*plVar19 == 0) goto LAB_7ffe9a49c468;
      FUN_7ffe9a6590f0(*plVar19,0x23);
    }
    cVar6 = FUN_7ffe9a4ac310(thisObject,plVar21,&iStack_104,aiStack_100,0);
    if (cVar6 != '\0') {
      if (iStack_104 != -1) {
        if (*plVar19 == 0) goto LAB_7ffe9a49c468;
        FUN_7ffe9a657a50(*plVar19,0x24);
      }
      if (aiStack_100[0] != -1) {
        if (*plVar19 == 0) goto LAB_7ffe9a49c468;
        FUN_7ffe9a657a50(*plVar19,0x25);
      }
    }
    puVar36 = &uStack_137;
    uVar23 = 0;
    iVar10 = FUN_7ffe9a4ad9c0(thisObject,iVar10,plVar21,&uStack_138,puVar36,0);
    if (iVar10 < 1) {
      iVar10 = 1;
    }
    fVar31 = (float)FUN_7ffe9a4adbc0(*plVar26,plVar21,0);
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar19,0x28);
    uVar12 = (int)((float)iVar10 * fVar31);
    if ((int)((float)iVar10 * fVar31) < 1) {
      uVar12 = 1;
    }
    if (*plVar19 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a658600(*plVar19,0);
    uVar9 = (undefined4)((ulonglong)puVar36 >> 0x20);
    uVar15 = (undefined4)((ulonglong)uVar23 >> 0x20);
    plVar19 = plStackX_18;
    uVar28 = uStack_134;
    if (*(int *)(thisObject + 0x150) == 10) {
      plVar20 = (longlong *)*plVar26;
      if (plVar20 == (longlong *)0x0) goto LAB_7ffe9a49c468;
      if ((*(byte *)(*plVar20 + 0x130) < *(byte *)(_DAT_7ffe9c96a1b0 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar20 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c96a1b0 + 0x130) * 8
           ) != _DAT_7ffe9c96a1b0)) {
        plVar19 = (longlong *)
                  (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0));
        if ((plVar19 == (longlong *)0x0) ||
           (lVar22 = (**(code **)(*plVar19 + 0x1a8))(plVar19,*(undefined8 *)(*plVar19 + 0x1b0)),
           lVar22 == 0)) goto LAB_7ffe9a49c468;
        uVar9 = FUN_7ffe99742ec0(0x27,_DAT_7ffe9c940d40);
        uVar28 = uStack_134;
        plVar19 = plStackX_18;
        uVar24 = CONCAT71((int7)((ulonglong)uVar23 >> 8),uStack_134 == 2);
        uVar23 = CONCAT71((int7)((ulonglong)puVar36 >> 8),acStackX_10[0]);
        uStack_128 = FUN_7ffe9a499c50(thisObject,uVar9,*plVar26,plStackX_18,uVar23,uVar24,
                                      iStack_12c == 2,&uStack_130,0);
        uVar9 = (undefined4)((ulonglong)uVar23 >> 0x20);
        uVar15 = (undefined4)((ulonglong)uVar24 >> 0x20);
        if (thisObject[0x130] != '\0') {
          uStack_128 = (uint)((float)(int)uStack_128 * *(float *)(thisObject + 300));
          uVar12 = uVar12 + uStack_128;
        }
      }
      else {
        uStack_128 = uVar12 >> 1;
        uVar12 = uStack_128;
      }
    }
    else if ((*(int *)(thisObject + 0xfc) == 8) && (alStack_98[0] != 0)) {
      uVar12 = uVar12 * 2;
    }
  }
  uVar16 = FUN_7ffe99742ec0(0x16,_DAT_7ffe9c940d40,plStack_120);
  uVar27 = 0;
  lVar22 = *plStack_120;
  if (*(ushort *)(lVar22 + 0x12e) != 0) {
    do {
      if (*(longlong *)(*(longlong *)(lVar22 + 0xb0) + (ulonglong)uVar27 * 0x10) ==
          _DAT_7ffe9c940d40) {
        puVar25 = (undefined8 *)
                  ((longlong)
                   (*(int *)(*(longlong *)(lVar22 + 0xb0) + 8 + (ulonglong)uVar27 * 0x10) + 0x2d) *
                   0x10 + 0x138 + lVar22);
        goto LAB_7ffe9a49bf0a;
      }
      uVar27 = uVar27 + 1;
    } while (uVar27 < *(ushort *)(lVar22 + 0x12e));
  }
  puVar25 = (undefined8 *)FUN_7ffe998ce540(plStack_120,_DAT_7ffe9c940d40,0x2d);
LAB_7ffe9a49bf0a:
  uVar16 = (*(code *)*puVar25)(plStack_120,uVar16,puVar25[1]);
  iVar10 = iStack_12c;
  cVar6 = acStackX_10[0];
  *(undefined4 *)(thisObject + 0x2c) = uVar16;
  if (uVar28 == 0) {
    if (lVar18 == 0) {
LAB_7ffe9a49c468:
      FUN_7ffe9996d7a0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    *(undefined4 *)(lVar18 + 0x40) = 0;
    cVar6 = FUN_7ffe99742ec0(0x14,_DAT_7ffe9c9724e0,plVar19);
    if (cVar6 == '\0') {
      aiStack_100[2] = 0;
    }
    else {
      iStack_12c = 3;
    }
    *(int *)(lVar18 + 0x1c) = aiStack_100[2];
    *(int *)(lVar18 + 0x34) = iStack_12c;
    uVar23 = *(undefined8 *)(lVar18 + 0x48);
    uVar24 = func_0x7ffe99940040(_DAT_7ffe9c94aa68);
    FUN_7ffe9a8fff70(uVar24,uVar23,0);
    *(undefined8 *)(lVar18 + 0x38) = uVar24;
    il2cpp_write_barrier_0();
    if (*(longlong *)(lVar18 + 0x38) == 0) goto LAB_7ffe9a49c468;
    *(undefined4 *)(*(longlong *)(lVar18 + 0x38) + 0x14) = 0;
  }
  else {
    if (((*(int *)(thisObject + 0xfc) == 10) && (*(int *)(thisObject + 0x150) == 10)) &&
       (thisObject[0x130] == '\0')) {
      uVar16 = *(undefined4 *)(thisObject + 0x124);
      uVar23 = FUN_7ffe99742ec0(6,_DAT_7ffe9c9724e0,plVar19);
      iVar10 = iStack_12c;
      uVar24 = CONCAT44(uVar9,uStack_134);
      lVar18 = FUN_7ffe9a499780(thisObject,uVar12,uStack_128,uVar16,uVar24,
                                CONCAT44(uVar15,iStack_12c),cVar6,uVar23,uStack_138,uStack_137,
                                auStack_136[0],uStack_130,0);
      uVar9 = (undefined4)((ulonglong)uVar24 >> 0x20);
      uVar28 = uStack_134;
    }
    else {
      if (lVar18 == 0) goto LAB_7ffe9a49c468;
      *(uint *)(lVar18 + 0x1c) = uVar28;
      *(char *)(lVar18 + 0x30) = acStackX_10[0];
      *(int *)(lVar18 + 0x34) = iStack_12c;
      *(undefined1 *)(lVar18 + 0x31) = uStack_138;
      *(undefined1 *)(lVar18 + 0x32) = uStack_137;
      *(bool *)(lVar18 + 0x61) = aiStack_118[0] == 2;
      *(uint *)(lVar18 + 0x18) = uVar12;
      *(bool *)(lVar18 + 0x62) = aiStack_118[0] == 1;
      *(undefined4 *)(lVar18 + 0x40) = *(undefined4 *)(thisObject + 0x124);
      *(undefined1 *)(lVar18 + 0x60) = auStack_136[0];
      FUN_7ffe9a4b37b0(thisObject,lVar18,uVar12,0);
    }
    if (iVar10 != 1) {
      cVar6 = FUN_7ffe9a495680(thisObject,*plVar26,0);
      if (cVar6 != '\0') {
        *(uint *)(thisObject + 0x104) = *(uint *)(thisObject + 0x104) | 0x800;
      }
      if ((*(uint *)(thisObject + 0x104) & 0x800) != 0) {
        uVar23 = CONCAT44(uVar9,iVar10);
        FUN_7ffe9a4981b0(thisObject,*plVar26,plVar19,acStackX_10[0],uVar23,lVar18,0);
        uVar9 = (undefined4)((ulonglong)uVar23 >> 0x20);
      }
      cVar6 = FUN_7ffe9a495830(thisObject,*plVar26,0);
      if (cVar6 != '\0') {
        *(uint *)(thisObject + 0x104) = *(uint *)(thisObject + 0x104) | 0x1000;
      }
      if ((*(uint *)(thisObject + 0x104) & 0x1000) != 0) {
        FUN_7ffe9a498b20(thisObject,*plVar26,plVar19,acStackX_10[0],CONCAT44(uVar9,iVar10),lVar18,0)
        ;
      }
      plVar20 = (longlong *)*plVar26;
      if (((plVar20 == (longlong *)0x0) ||
          (plVar20 = (longlong *)
                     (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0)),
          plVar20 == (longlong *)0x0)) ||
         (lVar22 = (**(code **)(*plVar20 + 0x1c8))(plVar20,*(undefined8 *)(*plVar20 + 0x1d0)),
         lVar22 == 0)) goto LAB_7ffe9a49c468;
      cVar6 = FUN_7ffe9abc2210(lVar22,0x3e9,alStack_98 + 1,_DAT_7ffe9c96a320);
      if (cVar6 != '\0') {
        plVar20 = (longlong *)*plVar26;
        if (plVar20 == (longlong *)0x0) goto LAB_7ffe9a49c468;
        uVar23 = (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0));
        uVar9 = FUN_7ffe9a846140(uVar23,uVar28 == 2,acStackX_10[0],0);
        cVar6 = FUN_7ffe9a4b2fb0(thisObject,5,uVar9,*plVar26,plVar19,aiStack_100 + 1,0);
        if (cVar6 != '\0') {
          if ((lVar18 == 0) || (*(longlong *)(lVar18 + 0x38) == 0)) goto LAB_7ffe9a49c462;
          FUN_7ffe9a8ffe30(*(longlong *)(lVar18 + 0x38),5);
          plVar19 = (longlong *)*plVar26;
          if (plVar19 == (longlong *)0x0) goto LAB_7ffe9a49c462;
          uVar23 = (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0));
          cVar6 = FUN_7ffe9a7b7f70(uVar23,auStack_12f,0);
          if (cVar6 != '\0') {
            FUN_7ffe9a7b80b0(*(undefined8 *)(lVar18 + 0x38),auStack_12f[0],0);
          }
        }
      }
    }
  }
  lVar5 = _DAT_7ffe9c913488;
  lVar22 = *(longlong *)(thisObject + 0x80);
  if (lVar22 != 0) {
    *(int *)(lVar22 + 0x1c) = *(int *)(lVar22 + 0x1c) + 1;
    lVar1 = *(longlong *)(lVar22 + 0x10);
    uVar28 = *(uint *)(lVar22 + 0x18);
    if (lVar1 != 0) {
      if (uVar28 < *(uint *)(lVar1 + 0x18)) {
        *(uint *)(lVar22 + 0x18) = uVar28 + 1;
        if (*(uint *)(lVar1 + 0x18) <= uVar28) {
          FUN_7ffe9996d790();
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
        *(longlong *)(lVar1 + 0x20 + (longlong)(int)uVar28 * 8) = lVar18;
        il2cpp_write_barrier_0();
      }
      else {
        FUN_7ffe9afd58b0(lVar22,lVar18,
                         *(undefined8 *)(*(longlong *)(*(longlong *)(lVar5 + 0x20) + 0xc0) + 0x70));
      }
      plVar26 = (longlong *)*plVar26;
      if (((plVar26 != (longlong *)0x0) &&
          (plVar26 = (longlong *)
                     (**(code **)(*plVar26 + 0x298))(plVar26,*(undefined8 *)(*plVar26 + 0x2a0)),
          plVar26 != (longlong *)0x0)) &&
         (lVar18 = (**(code **)(*plVar26 + 0x1c8))(plVar26,*(undefined8 *)(*plVar26 + 0x1d0)),
         lVar18 != 0)) {
        FUN_7ffe9a7cb960(lVar18,0x2a6,0,0);
        return;
      }
    }
  }
LAB_7ffe9a49c462:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

