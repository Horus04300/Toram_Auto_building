
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void NormalAttackAction_calcPlayerToMobDamage
               (undefined *self,undefined *playerAction,undefined *mobAction,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  bool bVar3;
  float fVar4;
  char cVar5;
  undefined1 uVar6;
  char cVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  longlong lVar16;
  longlong lVar17;
  longlong *plVar18;
  longlong *plVar19;
  longlong *plVar20;
  longlong lVar21;
  undefined8 uVar22;
  undefined *puVar23;
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
  lVar16 = func_0x7ffe99940040(_DAT_7ffe9c8fcc10);
  func_0x7ffe999c30f0(lVar16,0);
  if (lVar16 == 0) goto LAB_7ffe9a49c468;
  plVar26 = (longlong *)(lVar16 + 0x10);
  *plVar26 = (longlong)playerAction;
  il2cpp_write_barrier_0();
  lVar17 = func_0x7ffe99940040(_DAT_7ffe9c920098);
  FUN_7ffe9a8f6350(lVar17,mobAction,0);
  plVar18 = (longlong *)*plVar26;
  if ((plVar18 == (longlong *)0x0) ||
     (plVar18 = (longlong *)
                (**(code **)(*plVar18 + 0x298))(plVar18,*(undefined8 *)(*plVar18 + 0x2a0)),
     plVar18 == (longlong *)0x0)) goto LAB_7ffe9a49c468;
  plVar19 = (longlong *)(**(code **)(*plVar18 + 0x1a8))(plVar18,*(undefined8 *)(*plVar18 + 0x1b0));
  plVar18 = (longlong *)*plVar26;
  plStack_120 = plVar19;
  if ((plVar18 == (longlong *)0x0) ||
     (plVar18 = (longlong *)
                (**(code **)(*plVar18 + 0x298))(plVar18,*(undefined8 *)(*plVar18 + 0x2a0)),
     plVar18 == (longlong *)0x0)) goto LAB_7ffe9a49c468;
  plVar20 = (longlong *)(**(code **)(*plVar18 + 0x198))(plVar18,*(undefined8 *)(*plVar18 + 0x1a0));
  plVar18 = (longlong *)0x0;
  if (plVar20 != (longlong *)0x0) {
    if ((*(byte *)(*plVar20 + 0x130) < *(byte *)(_DAT_7ffe9c923468 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*plVar20 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c923468 + 0x130) * 8)
        != _DAT_7ffe9c923468)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    if (bVar3) {
      plVar18 = plVar20;
    }
  }
  plVar20 = (longlong *)*plVar26;
  if ((plVar20 == (longlong *)0x0) ||
     (plVar20 = (longlong *)
                (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0)),
     plVar20 == (longlong *)0x0)) goto LAB_7ffe9a49c468;
  lVar21 = (**(code **)(*plVar20 + 0x1c8))(plVar20,*(undefined8 *)(*plVar20 + 0x1d0));
  plStack_d8 = (longlong *)(lVar16 + 0x18);
  *plStack_d8 = lVar21;
  il2cpp_write_barrier_0();
  if (mobAction == (undefined *)0x0) goto LAB_7ffe9a49c468;
  lStack_110 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
  acStackX_10[0] = '\0';
  uStack_138 = 0;
  uStack_137 = 0;
  auStack_136[0] = 0;
  uStack_130 = 0;
  uStack_128 = 0;
  aiStack_100[2] = 1;
  iStack_12c = 0;
  aiStack_118[0] = 0;
  if ((self[0x104] & 2) == 0) {
    plVar20 = (longlong *)*plVar26;
    if (((plVar20 == (longlong *)0x0) ||
        (plVar20 = (longlong *)
                   (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0)),
        plVar20 == (longlong *)0x0)) ||
       (lVar21 = (**(code **)(*plVar20 + 0x1c8))(plVar20,*(undefined8 *)(*plVar20 + 0x1d0)),
       lVar21 == 0)) goto LAB_7ffe9a49c468;
    FUN_7ffe9a7cb960(lVar21,0x2a6,1,0);
  }
  if (plVar18 == (longlong *)0x0) {
    if (plVar19 == (longlong *)0x0) goto LAB_7ffe9a49c468;
    uVar8 = FUN_7ffe99742ec0(0x1b,_DAT_7ffe9c940d40,plVar19);
  }
  else {
    uVar28 = *(uint *)(self + 0x104);
    FUN_7ffe9a484e10(plVar18,0);
    FUN_7ffe9a484110(plVar18,~(byte)(uVar28 >> 1) & 1,0);
    uVar8 = FUN_7ffe9a472c30(plVar18);
  }
  cVar5 = FUN_7ffe9a4b33f0(self,uVar8,mobAction,0);
  uStack_134 = 1;
  if (cVar5 != '\0') {
    uStack_134 = 2;
  }
  if (lStack_110 == 0) goto LAB_7ffe9a49c468;
  iVar9 = FUN_7ffe99742ec0(2,_DAT_7ffe9c93ed20,lStack_110);
  fVar31 = _DAT_7ffe9c049b18;
  if ((*(longlong *)(lVar16 + 0x18) == 0) ||
     (lVar21 = *(longlong *)(*(longlong *)(lVar16 + 0x18) + 0x50), lVar21 == 0))
  goto LAB_7ffe9a49c468;
  cVar5 = FUN_7ffe9ad8e670(lVar21,0x324,&plStack_d0,_DAT_7ffe9c934418);
  fVar32 = _DAT_7ffe9c049b34;
  fVar33 = fVar31;
  if (cVar5 != '\0') {
    if (plStack_d0 == (longlong *)0x0) goto LAB_7ffe9a49c468;
    iVar10 = (**(code **)(*plStack_d0 + 0x1f8))
                       (plStack_d0,0x32,*(undefined8 *)(*plStack_d0 + 0x200));
    fVar33 = (float)iVar10 * fVar32 + fVar31;
  }
  lVar21 = FUN_7ffe99742ec0(0xb,_DAT_7ffe9c9724e0,mobAction);
  if (lVar21 == 0) goto LAB_7ffe9a49c468;
  cVar5 = FUN_7ffe9a2ac880(lVar21,10,&plStack_c8);
  if (cVar5 != '\0') {
    if (plStack_c8 == (longlong *)0x0) goto LAB_7ffe9a49c468;
    iVar10 = (**(code **)(*plStack_c8 + 0x1a8))(plStack_c8,*(undefined8 *)(*plStack_c8 + 0x1b0));
    if (0x32 < iVar10) {
      iVar10 = 0x32;
    }
    fVar33 = fVar33 - (float)iVar10 * fVar32;
  }
  lStack_c0 = 0;
  if ((*(longlong *)(lVar16 + 0x18) == 0) ||
     (lVar21 = *(longlong *)(*(longlong *)(lVar16 + 0x18) + 0x50), lVar21 == 0))
  goto LAB_7ffe9a49c468;
  cVar5 = FUN_7ffe9ad8e670(lVar21,0x8f,&lStack_c0,_DAT_7ffe9c934418);
  if (cVar5 != '\0') {
    if (*(longlong *)(lVar16 + 0x18) == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a7ca6f0(*(longlong *)(lVar16 + 0x18),0x8f,0);
  }
  lStack_b8 = 0;
  if ((*(longlong *)(lVar16 + 0x18) == 0) ||
     (lVar21 = *(longlong *)(*(longlong *)(lVar16 + 0x18) + 0x50), lVar21 == 0))
  goto LAB_7ffe9a49c468;
  cVar5 = FUN_7ffe9ad8e670(lVar21,0x26f,&lStack_b8,_DAT_7ffe9c934418);
  if (cVar5 != '\0') {
    if (*(longlong *)(lVar16 + 0x18) == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a7ca6f0(*(longlong *)(lVar16 + 0x18),0x26f,0);
  }
  plVar18 = (longlong *)*plVar26;
  if (plVar18 == (longlong *)0x0) goto LAB_7ffe9a49c468;
  uVar22 = (**(code **)(*plVar18 + 0x298))(plVar18,*(undefined8 *)(*plVar18 + 0x2a0));
  uVar8 = (**(code **)(*(longlong *)self + 0x298))(self,*(undefined8 *)(*(longlong *)self + 0x2a0));
  lVar21 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,plStackX_18);
  if (lVar21 == 0) goto LAB_7ffe9a49c468;
  uVar6 = FUN_7ffe9a4daa60(lVar21,0x21);
  pcVar37 = acStackX_10;
  uVar24 = CONCAT71((int7)((ulonglong)in_stack_fffffffffffffe78 >> 8),uVar6);
  uVar6 = (**(code **)(*(longlong *)self + 0x688))
                    (self,uVar22,(int)((float)iVar9 * fVar33),uVar8,uVar24,pcVar37,
                     *(undefined8 *)(*(longlong *)self + 0x690));
  uVar8 = (undefined4)((ulonglong)uVar24 >> 0x20);
  uVar14 = (undefined4)((ulonglong)pcVar37 >> 0x20);
  plVar18 = (longlong *)(lVar16 + 0x18);
  if (lStack_c0 != 0) {
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a7c26c0(*plVar18,lStack_c0,0,0);
  }
  if (lStack_b8 != 0) {
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a7c26c0(*plVar18,lStack_b8,0,0);
  }
  cVar5 = FUN_7ffe9a497710(self,*plVar26,uVar6,0);
  alStack_98[0] = 0;
  if ((*plVar18 == 0) || (lVar21 = *(longlong *)(*plVar18 + 0x50), lVar21 == 0))
  goto LAB_7ffe9a49c468;
  cVar7 = FUN_7ffe9ad8e670(lVar21,0x27f,alStack_98,_DAT_7ffe9c934418);
  if (cVar7 != '\0') {
    cVar5 = '\x01';
    uStack_134 = 2;
    uVar22 = func_0x7ffe99940040(_DAT_7ffe9c92eda0);
    FUN_7ffe999e6880(uVar22,lVar16,_DAT_7ffe9c96f7c8,0);
    FUN_7ffe9a4b20c0(self,uVar22,0);
  }
  plVar18 = (longlong *)*plVar26;
  if (((plVar18 == (longlong *)0x0) ||
      (plVar18 = (longlong *)
                 (**(code **)(*plVar18 + 0x298))(plVar18,*(undefined8 *)(*plVar18 + 0x2a0)),
      plVar18 == (longlong *)0x0)) ||
     (lVar16 = (**(code **)(*plVar18 + 0x1e8))(plVar18,*(undefined8 *)(*plVar18 + 0x1f0)),
     lVar16 == 0)) goto LAB_7ffe9a49c468;
  cVar7 = FUN_7ffe9a4daa60(lVar16,0x21);
  if ((cVar7 != '\0') && (cVar7 = func_0x7ffe9a4ad2d0(self,2), cVar7 == '\0')) {
    if (acStackX_10[0] == '\0') {
      acStackX_10[0] = '\x01';
    }
    else {
      cVar5 = '\0';
      uStack_134 = 0;
    }
  }
  plVar18 = plStackX_18;
  cVar7 = FUN_7ffe99742ec0(0x14,_DAT_7ffe9c9724e0,plStackX_18);
  if (cVar7 == '\0') {
    if ((cVar5 != '\0') || (uStack_134 == 2)) goto LAB_7ffe9a49aba1;
    uStack_134 = 0;
    uVar28 = 0;
LAB_7ffe9a49ac70:
    uStack_128 = 0;
    uVar11 = 0;
    if (plStack_120 == (longlong *)0x0) goto LAB_7ffe9a49c468;
  }
  else {
    uStack_134 = 0;
LAB_7ffe9a49aba1:
    uVar28 = uStack_134;
    uVar11 = (**(code **)(*(longlong *)self + 0x198))
                       (self,*(undefined8 *)(*(longlong *)self + 0x1a0));
    resistReactionType = aiStack_118;
    uVar14 = 0;
    puVar23 = PlayerAttackBase_CalcHitReaction
                        (self,(undefined *)(ulonglong)uVar11,(undefined *)*plVar26,
                         (undefined *)plVar18,(undefined *)resistReactionType,(undefined *)0x0);
    uVar8 = (undefined4)((ulonglong)resistReactionType >> 0x20);
    iStack_12c = (int)puVar23;
    if ((*(int *)(self + 0xfc) - 10U < 2) && ((self[0x104] & 2) != 0)) {
      FUN_7ffe9a49c630(self,*plVar26,plVar18,0);
      return;
    }
    if (iStack_12c == 1) goto LAB_7ffe9a49ac70;
    lVar16 = func_0x7ffe99940040(_DAT_7ffe9c94a078);
    FUN_7ffe9a6596c0(lVar16,0);
    plVar18 = (longlong *)(self + 0x180);
    *plVar18 = lVar16;
    il2cpp_write_barrier_0();
    lVar16 = *plVar18;
    uVar8 = (**(code **)(*(longlong *)self + 0x188))(self,*(undefined8 *)(*(longlong *)self + 400));
    if (lVar16 == 0) goto LAB_7ffe9a49c468;
    *(undefined4 *)(lVar16 + 0x20) = uVar8;
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a658f90(*plVar18,0,1,0);
    iVar9 = FUN_7ffe9a494ae0(self,*plVar26,plStackX_18,uVar28,0);
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657a50(*plVar18,7);
    if (*plStack_d8 == 0) goto LAB_7ffe9a49c468;
    iVar10 = func_0x7ffe9a7c8f00(*plStack_d8,0x38);
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657a50(*plVar18,8);
    iVar12 = FUN_7ffe9a49c4a0(self,*plVar26,0);
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657a50(*plVar18,8);
    iVar13 = FUN_7ffe9a7a6a60(*plVar26,plStackX_18,0);
    iVar9 = iVar12 + iVar13 / 2 + iVar10 + iVar9;
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657a50(*plVar18,8);
    if (self[0x175] != '\0') {
      plVar19 = (longlong *)*plVar26;
      if (plVar19 == (longlong *)0x0) goto LAB_7ffe9a49c468;
      uVar22 = (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0));
      iVar10 = FUN_7ffe9a7d3200(uVar22,0);
      iVar9 = iVar9 + iVar10;
      if (*plVar18 == 0) goto LAB_7ffe9a49c468;
      FUN_7ffe9a657a50(*plVar18,8);
    }
    if (self[0x176] != '\0') {
      plVar19 = (longlong *)*plVar26;
      if (plVar19 == (longlong *)0x0) goto LAB_7ffe9a49c468;
      uVar22 = (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0));
      iVar10 = FUN_7ffe9a792260(uVar22,0);
      iVar9 = iVar9 + iVar10;
      if (*plVar18 == 0) goto LAB_7ffe9a49c468;
      FUN_7ffe9a657a50(*plVar18,8);
    }
    fVar4 = _DAT_7ffe9c049cfc;
    fVar33 = fVar31;
    if (self[0x140] != '\0') {
      iVar10 = FUN_7ffe9a4b2d40(self,*plVar26,0);
      iVar9 = iVar9 + iVar10;
      iVar10 = FUN_7ffe9a4b2a70(*plVar26,0);
      fVar33 = (float)iVar10 / fVar4;
    }
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657a50(*plVar18,0xb);
    iVar10 = FUN_7ffe9a495060(self,*plVar26,lStack_110,0);
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657a50(*plVar18,10);
    iVar12 = 0;
    if (-1 < iVar9 - iVar10) {
      iVar12 = iVar9 - iVar10;
    }
    if (uStack_134 == 2) {
      if ((*plVar18 == 0) || (FUN_7ffe9a658f90(*plVar18,6,1), plStack_120 == (longlong *)0x0))
      goto LAB_7ffe9a49c468;
      iVar9 = FUN_7ffe99742ec0(0x1c,_DAT_7ffe9c940d40,plStack_120);
      iVar12 = (int)((float)iVar12 * ((float)iVar9 / fVar4));
    }
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar18,0xd);
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar18,0x13);
    plVar19 = (longlong *)*plVar26;
    if (plVar19 == (longlong *)0x0) goto LAB_7ffe9a49c468;
    uVar22 = (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0));
    uVar8 = (**(code **)(*(longlong *)self + 0x198))
                      (self,*(undefined8 *)(*(longlong *)self + 0x1a0));
    uVar14 = FUN_7ffe99742ec0(9,_DAT_7ffe9c93ed20);
    fVar29 = (float)FUN_7ffe9a4a9110(self,uVar22,uVar8,uVar14,auStack_136,0);
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar18,0xf);
    plVar19 = (longlong *)*plVar26;
    if (plVar19 == (longlong *)0x0) goto LAB_7ffe9a49c468;
    uVar22 = (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0));
    fVar30 = (float)FUN_7ffe9a4aad20(uVar22,plStackX_18,0);
    iVar9 = (int)((float)(int)((float)(int)((float)iVar12 * fVar33) * fVar29) * fVar30);
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar18,0x10);
    if (self[0x130] != '\0') {
      iVar9 = (int)((float)iVar9 * *(float *)(self + 300));
      if (*plVar18 == 0) goto LAB_7ffe9a49c468;
      FUN_7ffe9a657c40(*plVar18,0x11);
    }
    plVar19 = (longlong *)*plVar26;
    if (DAT_7ffe9cadde8d == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c96a1b0);
      FUN_7ffe9996d590(&DAT_7ffe9c906b90);
      DAT_7ffe9cadde8d = '\x01';
    }
    plVar20 = plVar19;
    if (plVar19 != (longlong *)0x0) {
      if ((*(byte *)(*plVar19 + 0x130) < *(byte *)(_DAT_7ffe9c96a1b0 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar19 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c96a1b0 + 0x130) * 8
           ) != _DAT_7ffe9c96a1b0)) {
        bVar3 = false;
      }
      else {
        bVar3 = true;
      }
      plVar20 = (longlong *)0x0;
      if (bVar3) {
        plVar20 = plVar19;
      }
    }
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar5 = FUN_7ffe9bda1fa0(plVar20,0,0);
    if (cVar5 == '\0') {
      if ((plVar20 == (longlong *)0x0) || (plVar20[0x40] == 0)) goto LAB_7ffe9a49c468;
      if (*(int *)(plVar20[0x40] + 0x94) == 1) {
        if (plVar20[0x45] == 0) goto LAB_7ffe9a49c468;
        fVar33 = (float)func_0x7ffe99dfd710(plVar20[0x45],0);
        iVar9 = (int)((fVar33 + fVar31) * (float)iVar9);
      }
      if (plVar20[0x40] == 0) goto LAB_7ffe9a49c468;
      iVar9 = (int)((float)iVar9 * *(float *)(plVar20[0x40] + 0xb0));
    }
    fVar31 = (float)FUN_7ffe9a49cc30(self,*plVar26,0,0);
    bVar3 = false;
    if (self[0x176] != '\0') {
      plVar19 = (longlong *)*plVar26;
      if (plVar19 == (longlong *)0x0) goto LAB_7ffe9a49c468;
      uVar22 = (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0));
      cVar5 = FUN_7ffe9a7b40f0(uVar22,*(undefined4 *)(self + 0x178),0);
      bVar3 = false;
      if (cVar5 != '\0') {
        bVar3 = true;
      }
    }
    if (self[0x175] != '\0') {
      plVar19 = (longlong *)*plVar26;
      if (((plVar19 == (longlong *)0x0) ||
          (plVar19 = (longlong *)
                     (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0)),
          plVar19 == (longlong *)0x0)) ||
         (lVar16 = (**(code **)(*plVar19 + 0x1c8))(plVar19,*(undefined8 *)(*plVar19 + 0x1d0)),
         lVar16 == 0)) goto LAB_7ffe9a49c468;
      cVar5 = FUN_7ffe9a7cbb30(lVar16,0x26b,&plStack_e8,0);
      if (cVar5 != '\0') {
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
    iVar10 = func_0x7ffe9a7c8f00(*plStack_d8,0x3a);
    plVar19 = (longlong *)*plVar26;
    if (((plVar19 == (longlong *)0x0) ||
        (plVar19 = (longlong *)
                   (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0)),
        plVar19 == (longlong *)0x0)) ||
       (lVar16 = (**(code **)(*plVar19 + 0x218))(plVar19,*(undefined8 *)(*plVar19 + 0x220)),
       lVar16 == 0)) goto LAB_7ffe9a49c468;
    fVar33 = (float)func_0x7ffe9a5b25f0(lVar16,0);
    fVar31 = fVar33 * fVar32 + (float)iVar10 / fVar4 + fVar31;
    cVar5 = func_0x7ffe9a4ad2d0(self,0x400,0);
    if (cVar5 != '\0') {
      plVar19 = (longlong *)*plVar26;
      if ((((plVar19 == (longlong *)0x0) ||
           (plVar19 = (longlong *)
                      (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0)),
           plVar19 == (longlong *)0x0)) ||
          (lVar16 = (**(code **)(*plVar19 + 0x1b8))(plVar19,*(undefined8 *)(*plVar19 + 0x1c0)),
          lVar16 == 0)) || (*(longlong *)(lVar16 + 0x68) == 0)) goto LAB_7ffe9a49c468;
      cVar5 = FUN_7ffe9ad8e670(*(longlong *)(lVar16 + 0x68),0x128,&plStack_f0,_DAT_7ffe9c935bd0);
      if (cVar5 != '\0') {
        if (plStack_f0 == (longlong *)0x0) goto LAB_7ffe9a49c468;
        iVar10 = (**(code **)(*plStack_f0 + 0x178))
                           (plStack_f0,0x1a,*(undefined8 *)(*plStack_f0 + 0x180));
        fVar31 = fVar31 + (float)iVar10 / fVar4;
      }
      plVar19 = (longlong *)*plVar26;
      if (((plVar19 == (longlong *)0x0) ||
          (plVar19 = (longlong *)
                     (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0)),
          plVar19 == (longlong *)0x0)) ||
         ((lVar16 = (**(code **)(*plVar19 + 0x1b8))(plVar19,*(undefined8 *)(*plVar19 + 0x1c0)),
          lVar16 == 0 || (*(longlong *)(lVar16 + 0x68) == 0)))) goto LAB_7ffe9a49c468;
      cVar5 = FUN_7ffe9ad8e670(*(longlong *)(lVar16 + 0x68),0x129,&plStack_f0,_DAT_7ffe9c935bd0);
      if (cVar5 != '\0') {
        if (plStack_f0 == (longlong *)0x0) goto LAB_7ffe9a49c468;
        iVar10 = (**(code **)(*plStack_f0 + 0x178))
                           (plStack_f0,0x1a,*(undefined8 *)(*plStack_f0 + 0x180));
        fVar31 = fVar31 + (float)iVar10 / fVar4;
      }
    }
    if (self[0x176] != '\0') {
      plVar19 = (longlong *)*plVar26;
      if (plVar19 == (longlong *)0x0) goto LAB_7ffe9a49c468;
      uVar22 = (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0));
      fVar32 = (float)FUN_7ffe9a792330(uVar22,0);
      plVar19 = (longlong *)*plVar26;
      if (plVar19 == (longlong *)0x0) goto LAB_7ffe9a49c468;
      uVar22 = (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0));
      iVar10 = FUN_7ffe9a7b3fc0(uVar22,0);
      fVar31 = fVar31 + ((float)iVar10 + fVar32) / fVar4;
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
      plVar19 = (longlong *)*plVar26;
      if (((plVar19 == (longlong *)0x0) ||
          (plVar19 = (longlong *)
                     (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0)),
          plVar19 == (longlong *)0x0)) ||
         (lVar16 = (**(code **)(*plVar19 + 0x1c8))(plVar19,*(undefined8 *)(*plVar19 + 0x1d0)),
         lVar16 == 0)) goto LAB_7ffe9a49c468;
      FUN_7ffe9a7cafa0(lVar16,0x26b,0);
    }
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar18,0x12);
    cVar5 = func_0x7ffe9a4ad2d0(self,0x10);
    if (cVar5 != '\0') {
      plVar19 = (longlong *)*plVar26;
      if (((plVar19 == (longlong *)0x0) ||
          (plVar19 = (longlong *)
                     (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0)),
          plVar19 == (longlong *)0x0)) ||
         (lVar16 = (**(code **)(*plVar19 + 0x1c8))(plVar19,*(undefined8 *)(*plVar19 + 0x1d0)),
         lVar16 == 0)) goto LAB_7ffe9a49c468;
      cVar5 = FUN_7ffe9abc2210(lVar16,0x52,&lStack_e0,_DAT_7ffe9c96a188);
      if (cVar5 != '\0') {
        if (lStack_e0 == 0) goto LAB_7ffe9a49c468;
        func_0x7ffe9a7a5e70(lStack_e0,0);
      }
    }
    if (plStack_120 == (longlong *)0x0) goto LAB_7ffe9a49c468;
    uVar8 = FUN_7ffe99742ec0(0xf,_DAT_7ffe9c940d40,plStack_120);
    cVar5 = acStackX_10[0];
    plVar19 = (longlong *)*plVar26;
    if (plVar19 == (longlong *)0x0) goto LAB_7ffe9a49c468;
    uVar22 = (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0));
    fVar32 = (float)(**(code **)(*(longlong *)self + 0x6a8))
                              (self,3,uVar8,cVar5,uVar22,*(undefined8 *)(*(longlong *)self + 0x6b0))
    ;
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar18,0x15);
    if (lStack_e0 != 0) {
      func_0x7ffe9a262af0(lStack_e0,0);
    }
    iVar10 = FUN_7ffe99742ec0(0x10,_DAT_7ffe9c93ed20,lStack_110);
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar18,0x17);
    plVar19 = plStack_d8;
    if ((*plStack_d8 == 0) || (lVar16 = *(longlong *)(*plStack_d8 + 0x50), lVar16 == 0))
    goto LAB_7ffe9a49c468;
    cVar5 = FUN_7ffe9ad8e670(lVar16,0x28d,&lStack_a8,_DAT_7ffe9c934418);
    if (cVar5 != '\0') {
      lVar16 = *plVar19;
      if (lVar16 == 0) goto LAB_7ffe9a49c468;
      FUN_7ffe9a7ca6f0(lVar16,0x28d,0);
    }
    plVar20 = (longlong *)*plVar26;
    if (plVar20 == (longlong *)0x0) goto LAB_7ffe9a49c468;
    uVar22 = (**(code **)(*plVar20 + 0x298))(plVar20,*(undefined8 *)(*plVar20 + 0x2a0));
    uVar22 = FUN_7ffe9a4a7d60(self,uVar22,0);
    plVar20 = plStackX_18;
    auVar34._8_4_ = (int)extraout_XMM0_Qb;
    auVar34._0_8_ = uVar22;
    auVar34._12_4_ = (int)((ulonglong)extraout_XMM0_Qb >> 0x20);
    lVar16 = *plStackX_18;
    if ((*(byte *)(_DAT_7ffe9c923808 + 0x130) <= *(byte *)(lVar16 + 0x130)) &&
       (*(longlong *)
         (*(longlong *)(lVar16 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c923808 + 0x130) * 8) ==
        _DAT_7ffe9c923808)) {
      if ((*(byte *)(lVar16 + 0x130) < *(byte *)(_DAT_7ffe9c923808 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(lVar16 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c923808 + 0x130) * 8)
          != _DAT_7ffe9c923808)) {
        FUN_7ffe9996c950(plStackX_18);
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      cVar5 = FUN_7ffe9ab798a0(plStackX_18,0x5a,&lStack_b0,_DAT_7ffe9c8f1e88);
      if (cVar5 != '\0') {
        if (lStack_b0 == 0) goto LAB_7ffe9a49c468;
        fVar33 = (float)FUN_7ffe9a37a550(lStack_b0,0);
        auVar35._4_12_ = auVar34._4_12_;
        auVar35._0_4_ = (float)uVar22 - fVar33;
        uVar22 = auVar35._0_8_;
      }
    }
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar18,0x19);
    if (lStack_a8 != 0) {
      lVar16 = *plVar19;
      if (lVar16 == 0) goto LAB_7ffe9a49c468;
      FUN_7ffe9a7c26c0(lVar16,lStack_a8,0,0);
    }
    fVar33 = (float)FUN_7ffe9a4a8c60(*plVar26,plVar20,0);
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar18,0x1a);
    plVar19 = (longlong *)*plVar26;
    if (plVar19 == (longlong *)0x0) goto LAB_7ffe9a49c468;
    uVar24 = (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0));
    fVar29 = (float)FUN_7ffe9a4a97e0(self,uVar24,0);
    iVar9 = (int)((float)(int)((float)(int)((float)(int)((float)(int)((float)(int)((float)iVar9 *
                                                                                  fVar31) * fVar32)
                                                        * ((float)iVar10 / fVar4)) * (float)uVar22)
                              * fVar33) * fVar29);
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar18,0x1c);
    cVar5 = FUN_7ffe9a4ac1c0(self,plVar20,&fStack_108,0);
    if (cVar5 != '\0') {
      iVar9 = (int)((float)iVar9 * fStack_108);
    }
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar18,0x1d);
    fVar31 = _DAT_7ffe9c049f04;
    if (iStack_12c == 2) {
      lVar16 = FUN_7ffe99742ec0(0xb,_DAT_7ffe9c9724e0,plVar20);
      if (lVar16 == 0) goto LAB_7ffe9a49c468;
      cVar5 = FUN_7ffe9a2ac880(lVar16,4,&plStack_a0);
      if (cVar5 != '\0') {
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
      iVar9 = (int)(((float)iVar9 * fVar31) / fVar4);
      if (*plVar18 == 0) goto LAB_7ffe9a49c468;
      FUN_7ffe9a658f90(*plVar18,0x20,1);
      if (*plVar18 == 0) goto LAB_7ffe9a49c468;
      FUN_7ffe9a658e30(*plVar18,0x21);
    }
    plVar19 = (longlong *)*plVar26;
    if (((plVar19 == (longlong *)0x0) ||
        (plVar19 = (longlong *)
                   (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0)),
        plVar19 == (longlong *)0x0)) ||
       (lVar16 = (**(code **)(*plVar19 + 0x1d8))(plVar19,*(undefined8 *)(*plVar19 + 0x1e0)),
       lVar16 == 0)) goto LAB_7ffe9a49c468;
    fVar31 = (float)FUN_7ffe9a4ebf80(lVar16,0);
    iVar9 = (int)((float)iVar9 * fVar31);
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar18,0x22);
    plVar19 = (longlong *)*plVar26;
    if (((plVar19 == (longlong *)0x0) ||
        (plVar19 = (longlong *)
                   (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0)),
        plVar19 == (longlong *)0x0)) ||
       (lVar16 = (**(code **)(*plVar19 + 0x218))(plVar19,*(undefined8 *)(*plVar19 + 0x220)),
       lVar16 == 0)) goto LAB_7ffe9a49c468;
    cVar5 = FUN_7ffe9a5b20c0(lVar16,0x45,0);
    if (cVar5 != '\0') {
      lVar16 = *plVar20;
      uVar27 = 0;
      if (*(ushort *)(lVar16 + 0x12e) != 0) {
        do {
          if (*(longlong *)(*(longlong *)(lVar16 + 0xb0) + (ulonglong)uVar27 * 0x10) ==
              _DAT_7ffe9c9724e0) {
            puVar25 = (undefined8 *)
                      ((longlong)
                       (*(int *)(*(longlong *)(lVar16 + 0xb0) + 8 + (ulonglong)uVar27 * 0x10) + 0x17
                       ) * 0x10 + 0x138 + lVar16);
            goto LAB_7ffe9a49bc8a;
          }
          uVar27 = uVar27 + 1;
        } while (uVar27 < *(ushort *)(lVar16 + 0x12e));
      }
      puVar25 = (undefined8 *)FUN_7ffe998ce540(plVar20,_DAT_7ffe9c9724e0,0x17);
LAB_7ffe9a49bc8a:
      (*(code *)*puVar25)(plVar20,0x10,puVar25[1]);
      iVar10 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ed20,lStack_110);
      iVar10 = (int)((float)iVar10 / fVar4);
      if (iVar10 < 1) {
        iVar10 = 1;
      }
      if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      iVar9 = func_0x7ffe9b506d80(iVar9,iVar10,0);
      if (*plVar18 == 0) goto LAB_7ffe9a49c468;
      FUN_7ffe9a6590f0(*plVar18,0x23);
    }
    cVar5 = FUN_7ffe9a4ac310(self,plVar20,&iStack_104,aiStack_100,0);
    if (cVar5 != '\0') {
      if (iStack_104 != -1) {
        if (*plVar18 == 0) goto LAB_7ffe9a49c468;
        FUN_7ffe9a657a50(*plVar18,0x24);
      }
      if (aiStack_100[0] != -1) {
        if (*plVar18 == 0) goto LAB_7ffe9a49c468;
        FUN_7ffe9a657a50(*plVar18,0x25);
      }
    }
    puVar36 = &uStack_137;
    uVar22 = 0;
    iVar9 = FUN_7ffe9a4ad9c0(self,iVar9,plVar20,&uStack_138,puVar36,0);
    if (iVar9 < 1) {
      iVar9 = 1;
    }
    fVar31 = (float)FUN_7ffe9a4adbc0(*plVar26,plVar20,0);
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a657c40(*plVar18,0x28);
    uVar11 = (int)((float)iVar9 * fVar31);
    if ((int)((float)iVar9 * fVar31) < 1) {
      uVar11 = 1;
    }
    if (*plVar18 == 0) goto LAB_7ffe9a49c468;
    FUN_7ffe9a658600(*plVar18,0);
    uVar8 = (undefined4)((ulonglong)puVar36 >> 0x20);
    uVar14 = (undefined4)((ulonglong)uVar22 >> 0x20);
    plVar18 = plStackX_18;
    uVar28 = uStack_134;
    if (*(int *)(self + 0x150) == 10) {
      plVar19 = (longlong *)*plVar26;
      if (plVar19 == (longlong *)0x0) goto LAB_7ffe9a49c468;
      if ((*(byte *)(*plVar19 + 0x130) < *(byte *)(_DAT_7ffe9c96a1b0 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar19 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c96a1b0 + 0x130) * 8
           ) != _DAT_7ffe9c96a1b0)) {
        plVar18 = (longlong *)
                  (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0));
        if ((plVar18 == (longlong *)0x0) ||
           (lVar16 = (**(code **)(*plVar18 + 0x1a8))(plVar18,*(undefined8 *)(*plVar18 + 0x1b0)),
           lVar16 == 0)) goto LAB_7ffe9a49c468;
        uVar8 = FUN_7ffe99742ec0(0x27,_DAT_7ffe9c940d40);
        uVar28 = uStack_134;
        plVar18 = plStackX_18;
        uVar24 = CONCAT71((int7)((ulonglong)uVar22 >> 8),uStack_134 == 2);
        uVar22 = CONCAT71((int7)((ulonglong)puVar36 >> 8),acStackX_10[0]);
        uStack_128 = FUN_7ffe9a499c50(self,uVar8,*plVar26,plStackX_18,uVar22,uVar24,iStack_12c == 2,
                                      &uStack_130,0);
        uVar8 = (undefined4)((ulonglong)uVar22 >> 0x20);
        uVar14 = (undefined4)((ulonglong)uVar24 >> 0x20);
        if (self[0x130] != '\0') {
          uStack_128 = (uint)((float)(int)uStack_128 * *(float *)(self + 300));
          uVar11 = uVar11 + uStack_128;
        }
      }
      else {
        uStack_128 = uVar11 >> 1;
        uVar11 = uStack_128;
      }
    }
    else if ((*(int *)(self + 0xfc) == 8) && (alStack_98[0] != 0)) {
      uVar11 = uVar11 * 2;
    }
  }
  uVar15 = FUN_7ffe99742ec0(0x16,_DAT_7ffe9c940d40,plStack_120);
  uVar27 = 0;
  lVar16 = *plStack_120;
  if (*(ushort *)(lVar16 + 0x12e) != 0) {
    do {
      if (*(longlong *)(*(longlong *)(lVar16 + 0xb0) + (ulonglong)uVar27 * 0x10) ==
          _DAT_7ffe9c940d40) {
        puVar25 = (undefined8 *)
                  ((longlong)
                   (*(int *)(*(longlong *)(lVar16 + 0xb0) + 8 + (ulonglong)uVar27 * 0x10) + 0x2d) *
                   0x10 + 0x138 + lVar16);
        goto LAB_7ffe9a49bf0a;
      }
      uVar27 = uVar27 + 1;
    } while (uVar27 < *(ushort *)(lVar16 + 0x12e));
  }
  puVar25 = (undefined8 *)FUN_7ffe998ce540(plStack_120,_DAT_7ffe9c940d40,0x2d);
LAB_7ffe9a49bf0a:
  uVar15 = (*(code *)*puVar25)(plStack_120,uVar15,puVar25[1]);
  iVar9 = iStack_12c;
  cVar5 = acStackX_10[0];
  *(undefined4 *)(self + 0x2c) = uVar15;
  if (uVar28 == 0) {
    if (lVar17 == 0) {
LAB_7ffe9a49c468:
      FUN_7ffe9996d7a0();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    *(undefined4 *)(lVar17 + 0x40) = 0;
    cVar5 = FUN_7ffe99742ec0(0x14,_DAT_7ffe9c9724e0,plVar18);
    if (cVar5 == '\0') {
      aiStack_100[2] = 0;
    }
    else {
      iStack_12c = 3;
    }
    *(int *)(lVar17 + 0x1c) = aiStack_100[2];
    *(int *)(lVar17 + 0x34) = iStack_12c;
    uVar22 = *(undefined8 *)(lVar17 + 0x48);
    uVar24 = func_0x7ffe99940040(_DAT_7ffe9c94aa68);
    FUN_7ffe9a8fff70(uVar24,uVar22,0);
    *(undefined8 *)(lVar17 + 0x38) = uVar24;
    il2cpp_write_barrier_0();
    if (*(longlong *)(lVar17 + 0x38) == 0) goto LAB_7ffe9a49c468;
    *(undefined4 *)(*(longlong *)(lVar17 + 0x38) + 0x14) = 0;
  }
  else {
    if (((*(int *)(self + 0xfc) == 10) && (*(int *)(self + 0x150) == 10)) && (self[0x130] == '\0'))
    {
      uVar15 = *(undefined4 *)(self + 0x124);
      uVar22 = FUN_7ffe99742ec0(6,_DAT_7ffe9c9724e0,plVar18);
      iVar9 = iStack_12c;
      uVar24 = CONCAT44(uVar8,uStack_134);
      lVar17 = FUN_7ffe9a499780(self,uVar11,uStack_128,uVar15,uVar24,CONCAT44(uVar14,iStack_12c),
                                cVar5,uVar22,uStack_138,uStack_137,auStack_136[0],uStack_130,0);
      uVar8 = (undefined4)((ulonglong)uVar24 >> 0x20);
      uVar28 = uStack_134;
    }
    else {
      if (lVar17 == 0) goto LAB_7ffe9a49c468;
      *(uint *)(lVar17 + 0x1c) = uVar28;
      *(char *)(lVar17 + 0x30) = acStackX_10[0];
      *(int *)(lVar17 + 0x34) = iStack_12c;
      *(undefined1 *)(lVar17 + 0x31) = uStack_138;
      *(undefined1 *)(lVar17 + 0x32) = uStack_137;
      *(bool *)(lVar17 + 0x61) = aiStack_118[0] == 2;
      *(uint *)(lVar17 + 0x18) = uVar11;
      *(bool *)(lVar17 + 0x62) = aiStack_118[0] == 1;
      *(undefined4 *)(lVar17 + 0x40) = *(undefined4 *)(self + 0x124);
      *(undefined1 *)(lVar17 + 0x60) = auStack_136[0];
      FUN_7ffe9a4b37b0(self,lVar17,uVar11,0);
    }
    if (iVar9 != 1) {
      cVar5 = FUN_7ffe9a495680(self,*plVar26,0);
      if (cVar5 != '\0') {
        *(uint *)(self + 0x104) = *(uint *)(self + 0x104) | 0x800;
      }
      if ((*(uint *)(self + 0x104) & 0x800) != 0) {
        uVar22 = CONCAT44(uVar8,iVar9);
        FUN_7ffe9a4981b0(self,*plVar26,plVar18,acStackX_10[0],uVar22,lVar17,0);
        uVar8 = (undefined4)((ulonglong)uVar22 >> 0x20);
      }
      cVar5 = FUN_7ffe9a495830(self,*plVar26,0);
      if (cVar5 != '\0') {
        *(uint *)(self + 0x104) = *(uint *)(self + 0x104) | 0x1000;
      }
      if ((*(uint *)(self + 0x104) & 0x1000) != 0) {
        FUN_7ffe9a498b20(self,*plVar26,plVar18,acStackX_10[0],CONCAT44(uVar8,iVar9),lVar17,0);
      }
      plVar19 = (longlong *)*plVar26;
      if (((plVar19 == (longlong *)0x0) ||
          (plVar19 = (longlong *)
                     (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0)),
          plVar19 == (longlong *)0x0)) ||
         (lVar16 = (**(code **)(*plVar19 + 0x1c8))(plVar19,*(undefined8 *)(*plVar19 + 0x1d0)),
         lVar16 == 0)) goto LAB_7ffe9a49c468;
      cVar5 = FUN_7ffe9abc2210(lVar16,0x3e9,alStack_98 + 1,_DAT_7ffe9c96a320);
      if (cVar5 != '\0') {
        plVar19 = (longlong *)*plVar26;
        if (plVar19 == (longlong *)0x0) goto LAB_7ffe9a49c468;
        uVar22 = (**(code **)(*plVar19 + 0x298))(plVar19,*(undefined8 *)(*plVar19 + 0x2a0));
        uVar8 = FUN_7ffe9a846140(uVar22,uVar28 == 2,acStackX_10[0],0);
        cVar5 = FUN_7ffe9a4b2fb0(self,5,uVar8,*plVar26,plVar18,aiStack_100 + 1,0);
        if (cVar5 != '\0') {
          if ((lVar17 == 0) || (*(longlong *)(lVar17 + 0x38) == 0)) goto LAB_7ffe9a49c462;
          FUN_7ffe9a8ffe30(*(longlong *)(lVar17 + 0x38),5);
          plVar18 = (longlong *)*plVar26;
          if (plVar18 == (longlong *)0x0) goto LAB_7ffe9a49c462;
          uVar22 = (**(code **)(*plVar18 + 0x298))(plVar18,*(undefined8 *)(*plVar18 + 0x2a0));
          cVar5 = FUN_7ffe9a7b7f70(uVar22,auStack_12f,0);
          if (cVar5 != '\0') {
            FUN_7ffe9a7b80b0(*(undefined8 *)(lVar17 + 0x38),auStack_12f[0],0);
          }
        }
      }
    }
  }
  lVar21 = _DAT_7ffe9c913488;
  lVar16 = *(longlong *)(self + 0x80);
  if (lVar16 != 0) {
    *(int *)(lVar16 + 0x1c) = *(int *)(lVar16 + 0x1c) + 1;
    lVar1 = *(longlong *)(lVar16 + 0x10);
    uVar28 = *(uint *)(lVar16 + 0x18);
    if (lVar1 != 0) {
      if (uVar28 < *(uint *)(lVar1 + 0x18)) {
        *(uint *)(lVar16 + 0x18) = uVar28 + 1;
        if (*(uint *)(lVar1 + 0x18) <= uVar28) {
          FUN_7ffe9996d790();
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
        *(longlong *)(lVar1 + 0x20 + (longlong)(int)uVar28 * 8) = lVar17;
        il2cpp_write_barrier_0();
      }
      else {
        FUN_7ffe9afd58b0(lVar16,lVar17,
                         *(undefined8 *)(*(longlong *)(*(longlong *)(lVar21 + 0x20) + 0xc0) + 0x70))
        ;
      }
      plVar26 = (longlong *)*plVar26;
      if (((plVar26 != (longlong *)0x0) &&
          (plVar26 = (longlong *)
                     (**(code **)(*plVar26 + 0x298))(plVar26,*(undefined8 *)(*plVar26 + 0x2a0)),
          plVar26 != (longlong *)0x0)) &&
         (lVar16 = (**(code **)(*plVar26 + 0x1c8))(plVar26,*(undefined8 *)(*plVar26 + 0x1d0)),
         lVar16 != 0)) {
        FUN_7ffe9a7cb960(lVar16,0x2a6,0,0);
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

