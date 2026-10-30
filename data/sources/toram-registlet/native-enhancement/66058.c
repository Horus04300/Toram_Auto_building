
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UIRegistletReinforcementPanel_OnClickSelectMaterialGem
               (undefined *self,int param,undefined *methodInfo)

{
  byte flag;
  short sVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  code *pcVar5;
  float fVar6;
  char cVar7;
  short sVar8;
  short sVar9;
  longlong lVar10;
  longlong lVar11;
  undefined *puVar12;
  undefined8 uVar13;
  undefined8 uVar14;
  longlong lVar15;
  longlong lVar16;
  ulonglong uVar17;
  longlong *plVar18;
  undefined1 uVar19;
  short sVar20;
  undefined4 uVar21;
  uint auStackX_10 [4];
  uint auStackX_20 [2];
  longlong lStack_118;
  undefined4 uStack_110;
  longlong lStack_108;
  ulonglong uStack_100;
  undefined4 uStack_f8;
  longlong lStack_e8;
  undefined4 uStack_e0;
  int iStack_d8;
  undefined8 uStack_d0;
  longlong *plStack_c8;
  undefined8 uStack_c0;
  undefined8 *puStack_b8;
  longlong lStack_b0;
  undefined *puStack_a8;
  undefined8 uStack_a0;
  undefined8 *puStack_98;
  longlong lStack_90;
  undefined *puStack_88;
  
  puStack_a8 = self;
  puStack_88 = self;
  if (DAT_7ffe9cadc36e == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c909038);
    FUN_7ffe9996d590(&DAT_7ffe9c90d060);
    FUN_7ffe9996d590(&DAT_7ffe9c927b98);
    FUN_7ffe9996d590(&DAT_7ffe9c8f27f8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f28c8);
    FUN_7ffe9996d590(0x7ffe9c8f2998);
    FUN_7ffe9996d590(&DAT_7ffe9c946a20);
    FUN_7ffe9996d590(&DAT_7ffe9c93ad18);
    FUN_7ffe9996d590(&DAT_7ffe9c90dc30);
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c954370);
    FUN_7ffe9996d590(&DAT_7ffe9c959ca0);
    FUN_7ffe9996d590(&DAT_7ffe9c93ac18);
    FUN_7ffe9996d590(&DAT_7ffe9c94ba38);
    FUN_7ffe9996d590(&DAT_7ffe9c91ebd0);
    FUN_7ffe9996d590(&DAT_7ffe9c91eef0);
    FUN_7ffe9996d590(&DAT_7ffe9c91efb8);
    FUN_7ffe9996d590(&DAT_7ffe9c91eb08);
    FUN_7ffe9996d590(0x7ffe9c91f148);
    FUN_7ffe9996d590(&DAT_7ffe9c91f210);
    FUN_7ffe9996d590(&DAT_7ffe9c9682d8);
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c954178);
    FUN_7ffe9996d590(&DAT_7ffe9c953a40);
    FUN_7ffe9996d590(&DAT_7ffe9c955c78);
    FUN_7ffe9996d590(&DAT_7ffe9c904470);
    FUN_7ffe9996d590(&DAT_7ffe9c904540);
    FUN_7ffe9996d590(&DAT_7ffe9c904610);
    FUN_7ffe9996d590(&DAT_7ffe9c9046e0);
    FUN_7ffe9996d590(&DAT_7ffe9c9047b0);
    FUN_7ffe9996d590(&DAT_7ffe9c904880);
    FUN_7ffe9996d590(&DAT_7ffe9c8fc028);
    FUN_7ffe9996d590(&DAT_7ffe9c904950);
    FUN_7ffe9996d590(&DAT_7ffe9c904a20);
    FUN_7ffe9996d590(&DAT_7ffe9c8fc0f8);
    FUN_7ffe9996d590(&DAT_7ffe9c94ce98);
    FUN_7ffe9996d590(&DAT_7ffe9c91f060);
    FUN_7ffe9996d590(&DAT_7ffe9c94c938);
    FUN_7ffe9996d590(&DAT_7ffe9c91f830);
    FUN_7ffe9996d590(&DAT_7ffe9c94cb88);
    FUN_7ffe9996d590(&DAT_7ffe9c94cdd0);
    FUN_7ffe9996d590(&DAT_7ffe9c920578);
    FUN_7ffe9996d590(&DAT_7ffe9c94ca00);
    DAT_7ffe9cadc36e = '\x01';
  }
  lStack_108 = 0;
  uStack_a0 = 0;
  puStack_98 = (undefined8 *)0x0;
  lStack_90 = 0;
  lVar10 = func_0x7ffe99940040(_DAT_7ffe9c8fc028);
  func_0x7ffe999c3920(lVar10,0);
  lStack_e8 = lVar10;
  if (lVar10 == 0) goto LAB_7ffe9a0526dc;
  *(int *)(lVar10 + 0x10) = param;
  *(undefined **)(lVar10 + 0x18) = self;
  il2cpp_write_barrier_0();
  lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c955c78);
  if ((((lVar11 == 0) || (FUN_7ffe99a314f0(lVar11,7,0), *(longlong *)(self + 0xc0) == 0)) ||
      (lVar11 = FUN_7ffe9a480320(), lVar11 == 0)) ||
     (*(undefined **)(lVar11 + 0x18) == (undefined *)0x0)) goto LAB_7ffe9a0526dc;
  puVar12 = GemCartBag_get_Bag(*(undefined **)(lVar11 + 0x18),(undefined *)0x0);
  uVar13 = func_0x7ffe99940040(_DAT_7ffe9c93ad18);
  FUN_7ffe9af13420(uVar13,lVar10,_DAT_7ffe9c904470,0);
  lVar11 = FUN_7ffe9ab854c0(puVar12,uVar13,_DAT_7ffe9c909038);
  if (lVar11 == 0) {
    return;
  }
  uVar13 = *(undefined8 *)(self + 0xd0);
  uVar14 = func_0x7ffe99940040(_DAT_7ffe9c946a20);
  FUN_7ffe9af13420(uVar14,lVar10,_DAT_7ffe9c904540,0);
  lVar11 = FUN_7ffe9ab854c0(uVar13,uVar14,_DAT_7ffe9c90d060);
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar7 = FUN_7ffe9bda1fa0(lVar11,0,0);
  if (cVar7 != '\0') {
    return;
  }
  iStack_d8 = 100;
  sVar20 = 1;
  auStackX_20[0] = CONCAT22(auStackX_20[0]._2_2_,1);
  lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c953a40);
  if ((*(longlong *)(self + 0xa0) == 0) || (lVar15 == 0)) goto LAB_7ffe9a0526dc;
  lVar15 = FUN_7ffe9a5b4af0(lVar15,*(undefined2 *)(*(longlong *)(self + 0xa0) + 0x20),0);
  if (lVar15 != 0) {
    iStack_d8 = *(int *)(lVar15 + 0x14);
    sVar20 = *(short *)(lVar15 + 0x18);
    auStackX_20[0] = CONCAT22(auStackX_20[0]._2_2_,sVar20);
  }
  plVar18 = (longlong *)(self + 0xd8);
  lVar15 = *plVar18;
  uVar13 = func_0x7ffe99940040(_DAT_7ffe9c93ad18);
  FUN_7ffe9af13420(uVar13,lVar10,_DAT_7ffe9c904610,0);
  lVar15 = FUN_7ffe9ab854c0(lVar15,uVar13,_DAT_7ffe9c909038);
  if (lVar15 == 0) {
    lVar15 = *plVar18;
    uVar21 = _DAT_7ffe9c049b40;
    if (self[0xf2] == '\0') {
      if (lVar15 == 0) goto LAB_7ffe9a0526dc;
      if (0 < *(int *)(lVar15 + 0x18)) {
        uVar13 = *(undefined8 *)(self + 0xd0);
        uVar14 = func_0x7ffe99940040(_DAT_7ffe9c946a20);
        FUN_7ffe9af13420(uVar14,lVar10,_DAT_7ffe9c9046e0,0);
        lVar15 = FUN_7ffe9ab854c0(uVar13,uVar14,_DAT_7ffe9c90d060);
        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        cVar7 = FUN_7ffe9bda2160(lVar15,0,0);
        uVar21 = _DAT_7ffe9c049b40;
        if (cVar7 != '\0') {
          if ((lVar15 == 0) || (*(longlong *)(lVar15 + 0x20) == 0)) goto LAB_7ffe9a0526dc;
          FUN_7ffe9a404310(*(longlong *)(lVar15 + 0x20),*(undefined8 *)(lVar15 + 0x50),0);
          uVar13 = FUN_7ffe9bd98960(lVar15,0);
          lVar16 = FUN_7ffe9bd98a10(lVar15,0);
          if (lVar16 == 0) goto LAB_7ffe9a0526dc;
          lVar16 = FUN_7ffe9bdbf3e0(&lStack_118,lVar16,0);
          uVar21 = _DAT_7ffe9c049b40;
          uStack_f8 = 0;
          lStack_118 = (ulonglong)*(uint *)(lVar16 + 4) << 0x20;
          uStack_110 = 0;
          FUN_7ffe9a2f5f60(uVar13,_DAT_7ffe9c049b40,&lStack_118,0);
          if (*plVar18 == 0) goto LAB_7ffe9a0526dc;
          FUN_7ffe9afdbfb0(*plVar18,*(undefined8 *)(lVar15 + 0x48),_DAT_7ffe9c91efb8);
        }
      }
    }
    else {
      if (lVar15 == 0) goto LAB_7ffe9a0526dc;
      if (*(int *)(self + 0xf4) <= *(int *)(lVar15 + 0x18)) {
        return;
      }
      if ((int)sVar20 <= *(int *)(self + 0xec)) {
        return;
      }
    }
    if (lVar11 == 0) goto LAB_7ffe9a0526dc;
    FUN_7ffe9a04b280(lVar11,0);
    uVar13 = FUN_7ffe9bd98960(lVar11,0);
    lVar15 = FUN_7ffe9bd98a10(lVar11,0);
    if (lVar15 == 0) goto LAB_7ffe9a0526dc;
    lVar15 = FUN_7ffe9bdbf3e0(&lStack_118,lVar15,0);
    uStack_f8 = 0;
    lStack_118 = CONCAT44(*(undefined4 *)(lVar15 + 4),_DAT_7ffe9c04a0a0);
    uStack_110 = 0;
    FUN_7ffe9a2f5f60(uVar13,uVar21,&lStack_118,0);
    if (*plVar18 == 0) goto LAB_7ffe9a0526dc;
    FUN_7ffe99743100(*plVar18,*(undefined8 *)(lVar11 + 0x48),_DAT_7ffe9c91ebd0);
    uVar17 = func_0x7ffe99940040(_DAT_7ffe9c9682d8);
    FUN_7ffe9af8a010(uVar17,_DAT_7ffe9c91eb08);
    uStack_100 = uVar17;
    if (*(longlong *)(self + 0xa0) == 0) goto LAB_7ffe9a0526dc;
    sVar8 = *(short *)(*(longlong *)(self + 0xa0) + 0x22);
    auStackX_10[0] = CONCAT22(auStackX_10[0]._2_2_,sVar8);
    lStack_118 = *plVar18;
    lVar11 = *(longlong *)(lVar10 + 0x20);
    if (lVar11 == 0) {
      lVar11 = func_0x7ffe99940040(_DAT_7ffe9c93ad18);
      FUN_7ffe9af13420(lVar11,lVar10,_DAT_7ffe9c9047b0,0);
      *(longlong *)(lVar10 + 0x20) = lVar11;
      il2cpp_write_barrier_0();
    }
    lVar11 = FUN_7ffe9ab93080(lStack_118,lVar11,_DAT_7ffe9c927b98);
    if (lVar11 == 0) goto LAB_7ffe9a0526dc;
    lStack_108 = FUN_7ffe99742ec0(0,_DAT_7ffe9c954370,lVar11);
    uStack_d0 = 0;
    plStack_c8 = &lStack_108;
    do {
      if (lStack_108 == 0) goto LAB_7ffe9a0526fc;
      cVar7 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ac18);
      if (cVar7 == '\0') {
        if (lStack_108 != 0) {
          FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
        }
        if (sVar20 <= sVar8) goto LAB_7ffe9a051d34;
        lStack_e8 = *(longlong *)(self + 0xd8);
        lVar11 = *(longlong *)(lVar10 + 0x28);
        if (lVar11 == 0) {
          lVar11 = func_0x7ffe99940040(_DAT_7ffe9c93ad18);
          FUN_7ffe9af13420(lVar11,lVar10,_DAT_7ffe9c904880,0);
          *(longlong *)(lVar10 + 0x28) = lVar11;
          il2cpp_write_barrier_0();
        }
        lVar10 = FUN_7ffe9ab93080(lStack_e8,lVar11,_DAT_7ffe9c927b98);
        if (lVar10 == 0) goto LAB_7ffe9a0526dc;
        lStack_108 = FUN_7ffe99742ec0(0,_DAT_7ffe9c954370,lVar10);
        uStack_d0 = 0;
        plStack_c8 = &lStack_108;
        goto LAB_7ffe9a051c00;
      }
      if (lStack_108 == 0) goto LAB_7ffe9a0526f7;
      lVar11 = FUN_7ffe99742ec0(0,_DAT_7ffe9c959ca0);
      if (lVar11 == 0) goto LAB_7ffe9a0526f2;
      sVar1 = *(short *)(lVar11 + 0x22);
      if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      sVar8 = func_0x7ffe9b506d80((int)sVar20,(int)sVar1 + (int)sVar8,0);
      lVar15 = _DAT_7ffe9c91ebd0;
      auStackX_10[0] = CONCAT22(auStackX_10[0]._2_2_,sVar8);
      if (uVar17 == 0) goto LAB_7ffe9a0526ed;
      *(int *)(uVar17 + 0x1c) = *(int *)(uVar17 + 0x1c) + 1;
      lVar16 = *(longlong *)(uVar17 + 0x10);
      uVar2 = *(uint *)(uVar17 + 0x18);
      if (lVar16 == 0) goto LAB_7ffe9a0526e8;
      if (uVar2 < *(uint *)(lVar16 + 0x18)) {
        *(uint *)(uVar17 + 0x18) = uVar2 + 1;
        if (*(uint *)(lVar16 + 0x18) <= uVar2) goto LAB_7ffe9a0526e2;
        *(longlong *)(lVar16 + (longlong)(int)uVar2 * 8 + 0x20) = lVar11;
        il2cpp_write_barrier_0();
      }
      else {
        FUN_7ffe9afd58b0(uVar17,lVar11,
                         *(undefined8 *)(*(longlong *)(*(longlong *)(lVar15 + 0x20) + 0xc0) + 0x70))
        ;
      }
    } while (sVar8 < sVar20);
    if (lStack_108 != 0) {
      FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
    }
    goto LAB_7ffe9a051d34;
  }
  if ((lVar11 == 0) || (*(longlong *)(lVar11 + 0x20) == 0)) goto LAB_7ffe9a0526dc;
  FUN_7ffe9a404310(*(longlong *)(lVar11 + 0x20),*(undefined8 *)(lVar11 + 0x50),0);
  uVar13 = FUN_7ffe9bd98960(lVar11,0);
  lVar10 = FUN_7ffe9bd98a10(lVar11,0);
  if (lVar10 == 0) goto LAB_7ffe9a0526dc;
  lVar10 = FUN_7ffe9bdbf3e0(&uStack_d0,lVar10,0);
  uStack_110 = 0;
  lStack_e8 = (ulonglong)*(uint *)(lVar10 + 4) << 0x20;
  uStack_e0 = 0;
  FUN_7ffe9a2f5f60(uVar13,_DAT_7ffe9c049b40,&lStack_e8,0);
  if (*plVar18 == 0) goto LAB_7ffe9a0526dc;
  FUN_7ffe9afdbfb0(*plVar18,lVar15,_DAT_7ffe9c91efb8);
  goto LAB_7ffe9a05204a;
  while( true ) {
    cVar7 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ac18);
    if (cVar7 == '\0') {
      if (lStack_108 != 0) {
        FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
      }
      goto LAB_7ffe9a051d34;
    }
    if (lStack_108 == 0) goto LAB_7ffe9a052717;
    uVar13 = FUN_7ffe99742ec0(0,_DAT_7ffe9c959ca0);
    lVar10 = _DAT_7ffe9c91ebd0;
    sVar8 = sVar8 + 1;
    if (uVar17 == 0) goto LAB_7ffe9a052712;
    *(int *)(uVar17 + 0x1c) = *(int *)(uVar17 + 0x1c) + 1;
    lVar11 = *(longlong *)(uVar17 + 0x10);
    uVar2 = *(uint *)(uVar17 + 0x18);
    if (lVar11 == 0) goto LAB_7ffe9a05270d;
    if (uVar2 < *(uint *)(lVar11 + 0x18)) {
      *(uint *)(uVar17 + 0x18) = uVar2 + 1;
      if (*(uint *)(lVar11 + 0x18) <= uVar2) goto LAB_7ffe9a052708;
      *(undefined8 *)(lVar11 + (longlong)(int)uVar2 * 8 + 0x20) = uVar13;
      il2cpp_write_barrier_0();
    }
    else {
      FUN_7ffe9afd58b0(uVar17,uVar13,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar10 + 0x20) + 0xc0) + 0x70));
    }
    if (sVar20 <= sVar8) break;
LAB_7ffe9a051c00:
    if (lStack_108 == 0) goto LAB_7ffe9a05271c;
  }
  if (lStack_108 != 0) {
    FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
  }
LAB_7ffe9a051d34:
  if (*(longlong *)(self + 0xd8) == 0) goto LAB_7ffe9a0526dc;
  FUN_7ffe9af836a0(&uStack_c0,*(longlong *)(self + 0xd8),_DAT_7ffe9c91eef0);
  uStack_a0 = uStack_c0;
  puStack_98 = puStack_b8;
  lStack_90 = lStack_b0;
  uStack_c0 = 0;
  puStack_b8 = &uStack_a0;
  while (cVar7 = FUN_7ffe9ae28ed0(&uStack_a0,_DAT_7ffe9c8f28c8), cVar7 != '\0') {
    lVar10 = func_0x7ffe99940040(_DAT_7ffe9c8fc0f8);
    func_0x7ffe999c3920(lVar10,0);
    if (lVar10 == 0) goto LAB_7ffe9a052737;
    *(longlong *)(lVar10 + 0x10) = lStack_90;
    il2cpp_write_barrier_0();
    uVar13 = func_0x7ffe99940040(_DAT_7ffe9c93ad18);
    FUN_7ffe9af13420(uVar13,lVar10,_DAT_7ffe9c904950);
    lVar11 = FUN_7ffe9ab854c0(uVar17,uVar13);
    if (lVar11 == 0) {
      uVar13 = *(undefined8 *)(self + 0xd0);
      uVar14 = func_0x7ffe99940040(_DAT_7ffe9c946a20);
      FUN_7ffe9af13420(uVar14,lVar10,_DAT_7ffe9c904a20);
      lVar10 = FUN_7ffe9ab854c0(uVar13,uVar14);
      if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      cVar7 = FUN_7ffe9bda2160(lVar10,0);
      if (cVar7 != '\0') {
        if (lVar10 == 0) goto LAB_7ffe9a052732;
        if (*(longlong *)(lVar10 + 0x20) == 0) goto LAB_7ffe9a05272d;
        FUN_7ffe9a404310(*(longlong *)(lVar10 + 0x20),*(undefined8 *)(lVar10 + 0x50),0);
        uVar13 = FUN_7ffe9bd98960(lVar10,0);
        lVar10 = FUN_7ffe9bd98a10(lVar10,0);
        if (lVar10 == 0) goto LAB_7ffe9a052728;
        lVar10 = FUN_7ffe9bdbf3e0(&uStack_d0,lVar10,0);
        uStack_110 = 0;
        lStack_e8 = (ulonglong)*(uint *)(lVar10 + 4) << 0x20;
        uStack_e0 = 0;
        FUN_7ffe9a2f5f60(uVar13,uVar21);
      }
    }
  }
  func_0x7ffe999c3920(&uStack_a0,_DAT_7ffe9c8f27f8);
  *(ulonglong *)(self + 0xd8) = uVar17;
  il2cpp_write_barrier_0();
LAB_7ffe9a05204a:
  if (*(longlong *)(self + 0xa0) != 0) {
    *(int *)(self + 0xec) = (int)*(short *)(*(longlong *)(self + 0xa0) + 0x22);
    lVar10 = *(longlong *)(self + 0xd8);
    if (lVar10 != 0) {
      uStack_100 = CONCAT44(uStack_100._4_4_,*(int *)(lVar10 + 0x18));
      if (*(int *)(lVar10 + 0x18) < 1) {
        lVar10 = *(longlong *)(self + 0x20);
        if (lVar10 != 0) {
          if (*(uint *)(lVar10 + 0x18) < 2) {
LAB_7ffe9a052765:
            FUN_7ffe9996d790();
            pcVar5 = (code *)swi(3);
            (*pcVar5)();
            return;
          }
          lVar10 = *(longlong *)(lVar10 + 0x28);
          if ((*(longlong *)(self + 0xb0) != 0) &&
             (uVar13 = FUN_7ffe99a58320(*(longlong *)(self + 0xb0),_DAT_7ffe9c94cb88,0), lVar10 != 0
             )) {
            FUN_7ffe9a04a990(lVar10,uVar13,0);
            if (*(longlong *)(self + 0x38) != 0) {
              FUN_7ffe9bd9b390(*(longlong *)(self + 0x38),0,0);
              return;
            }
          }
        }
      }
      else {
        *(undefined4 *)(self + 0xe8) = 0;
        uVar19 = 0;
        auStackX_10[0] = auStackX_10[0] & 0xffffff00;
        FUN_7ffe9af836a0(&uStack_c0,lVar10,_DAT_7ffe9c91eef0);
        fVar6 = _DAT_7ffe9c049ec4;
        uStack_a0 = uStack_c0;
        puStack_98 = puStack_b8;
        lStack_90 = lStack_b0;
        uStack_c0 = 0;
        puStack_b8 = &uStack_a0;
        while (cVar7 = FUN_7ffe9ae28ed0(&uStack_a0,_DAT_7ffe9c8f28c8), cVar7 != '\0') {
          if (lStack_90 == 0) goto LAB_7ffe9a05274d;
          sVar8 = *(short *)(lStack_90 + 0x20);
          if (*(longlong *)(self + 0xa0) == 0) goto LAB_7ffe9a052748;
          sVar1 = *(short *)(*(longlong *)(self + 0xa0) + 0x20);
          iVar3 = *(int *)(puStack_a8 + 0xec);
          if (sVar8 == sVar1) {
            sVar9 = *(short *)(lStack_90 + 0x22);
            if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            sVar9 = func_0x7ffe9b506d80((int)sVar20,sVar9 + iVar3);
          }
          else {
            sVar9 = (short)iVar3 + 1;
          }
          if (puStack_a8 == (undefined *)0x0) goto LAB_7ffe9a052743;
          *(int *)(puStack_a8 + 0xec) = (int)sVar9;
          if (sVar8 == sVar1) {
            *(int *)(puStack_a8 + 0xe8) = *(int *)(self + 0xe8) - (int)((float)iStack_d8 * fVar6);
          }
          else {
            *(int *)(puStack_88 + 0xe8) = (int)(float)iStack_d8 + *(int *)(self + 0xe8);
            uVar19 = 1;
            auStackX_10[0] = CONCAT31(auStackX_10[0]._1_3_,1);
          }
        }
        func_0x7ffe999c3920(&uStack_a0,_DAT_7ffe9c8f27f8);
        uVar17 = uStack_100;
        uVar2 = (uint)uStack_100;
        if ((int)(uint)uStack_100 < 2) {
          if (*(longlong *)(self + 0xd8) == 0) goto LAB_7ffe9a0526dc;
          lVar10 = FUN_7ffe9af8ab90(*(longlong *)(self + 0xd8),0,_DAT_7ffe9c91f210);
          plVar18 = *(longlong **)(self + 0xb8);
          if ((lVar10 == 0) || (sVar20 = *(short *)(lVar10 + 0x20), plVar18 == (longlong *)0x0))
          goto LAB_7ffe9a0526dc;
          lVar11 = func_0x7ffe9996d210(*(undefined8 *)
                                        (*plVar18 +
                                        ((ulonglong)*(ushort *)(_DAT_7ffe9c954178 + 0x50) + 0x14) *
                                        0x10));
          plVar18 = (longlong *)(**(code **)(lVar11 + 8))(plVar18,(int)sVar20,lVar11);
          if (plVar18 == (longlong *)0x0) goto LAB_7ffe9a0526dc;
          uVar13 = (**(code **)(*plVar18 + 0x188))(plVar18,*(undefined8 *)(*plVar18 + 400));
          lVar11 = *(longlong *)(self + 0x20);
          if (lVar11 == 0) goto LAB_7ffe9a0526dc;
          if (*(uint *)(lVar11 + 0x18) < 2) goto LAB_7ffe9a052765;
          lVar11 = *(longlong *)(lVar11 + 0x28);
          if (lVar11 == 0) goto LAB_7ffe9a0526dc;
          if (DAT_7ffe9cadc332 == '\0') {
            FUN_7ffe9996d590(&DAT_7ffe9c920578);
            DAT_7ffe9cadc332 = '\x01';
          }
          FUN_7ffe9a04ac90(lVar11,lVar10,uVar13,_DAT_7ffe9c920578,0);
        }
        else {
          if (*(longlong *)(self + 0xb0) == 0) {
            FUN_7ffe9996d7a0();
            pcVar5 = (code *)swi(3);
            (*pcVar5)();
            return;
          }
          uVar13 = FUN_7ffe99a58320(*(longlong *)(self + 0xb0),_DAT_7ffe9c94c938,0);
          auStackX_10[0] = uVar2;
          uVar14 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,auStackX_10);
          uVar13 = FUN_7ffe9b36a740(uVar13,uVar14,0);
          if ((*(int *)(self + 0xf4) <= (int)uVar2) || ((int)sVar20 <= *(int *)(self + 0xec))) {
            if (*(longlong *)(self + 0xb0) == 0) {
              FUN_7ffe9996d7a0(0,uVar13);
              pcVar5 = (code *)swi(3);
              (*pcVar5)();
              return;
            }
            uVar13 = FUN_7ffe99a58320(*(longlong *)(self + 0xb0),_DAT_7ffe9c94ca00,0);
            auStackX_20[0] = uVar2;
            uVar14 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,auStackX_20);
            uVar13 = FUN_7ffe9b36a740(uVar13,uVar14,0);
          }
          lVar10 = *(longlong *)(self + 0x20);
          if (lVar10 == 0) goto LAB_7ffe9a0526dc;
          if (*(uint *)(lVar10 + 0x18) < 2) goto LAB_7ffe9a052765;
          if (*(longlong *)(lVar10 + 0x28) == 0) goto LAB_7ffe9a0526dc;
          FUN_7ffe9a04a4e0(*(longlong *)(lVar10 + 0x28),uVar13,uVar17 & 0xffffffff,0);
        }
        if (*(longlong *)(self + 0x38) != 0) {
          FUN_7ffe9bd9b390(*(longlong *)(self + 0x38),1,0);
          if (*(longlong *)(self + 0x88) != 0) {
            FUN_7ffe9bd9b390(*(longlong *)(self + 0x88),uVar19,0);
            lVar10 = *(longlong *)(self + 0xa0);
            if (lVar10 != 0) {
              sVar20 = *(short *)(lVar10 + 0x10);
              lVar11 = *(longlong *)(lVar10 + 0x18);
              sVar8 = *(short *)(lVar10 + 0x20);
              uVar21 = *(undefined4 *)(self + 0xec);
              flag = *(byte *)(lVar10 + 0x24);
              puVar12 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c90dc30);
              GemCartData__ctor(puVar12,sVar20,lVar11,sVar8,(byte)uVar21,flag,(undefined *)0x0);
              plVar18 = *(longlong **)(self + 0xb8);
              if ((puVar12 != (undefined *)0x0) &&
                 (sVar20 = *(short *)(puVar12 + 0x20), plVar18 != (longlong *)0x0)) {
                lVar10 = func_0x7ffe9996d210(*(undefined8 *)
                                              (*plVar18 +
                                              ((ulonglong)*(ushort *)(_DAT_7ffe9c954178 + 0x50) +
                                              0x14) * 0x10));
                plVar18 = (longlong *)(**(code **)(lVar10 + 8))(plVar18,(int)sVar20,lVar10);
                if (plVar18 != (longlong *)0x0) {
                  uVar13 = (**(code **)(*plVar18 + 0x188))(plVar18,*(undefined8 *)(*plVar18 + 400));
                  FUN_7ffe9bda22c0(self,uVar13,0);
                  lVar10 = *(longlong *)(self + 0x20);
                  if (lVar10 != 0) {
                    if (*(uint *)(lVar10 + 0x18) < 3) goto LAB_7ffe9a052765;
                    lVar10 = *(longlong *)(lVar10 + 0x30);
                    uVar13 = FUN_7ffe9bda1f30(self,0);
                    if (lVar10 != 0) {
                      FUN_7ffe9a04ac90(lVar10,puVar12,uVar13,_DAT_7ffe9c91f830,0);
                      if ((*(longlong *)(self + 0xc0) != 0) &&
                         (lVar10 = FUN_7ffe9a480320(*(longlong *)(self + 0xc0),0), lVar10 != 0)) {
                        iVar3 = *(int *)(lVar10 + 0x14);
                        iVar4 = *(int *)(self + 0xe8);
                        uVar13 = _DAT_7ffe9c91f060;
                        if (iVar4 <= iVar3) {
                          uVar13 = _DAT_7ffe9c920578;
                        }
                        lVar10 = *(longlong *)(self + 0x70);
                        uVar14 = FUN_7ffe9b5043c0(self + 0xe8,0);
                        uVar13 = FUN_7ffe9b3675b0(uVar13,uVar14,0);
                        if (lVar10 != 0) {
                          FUN_7ffe9a404310(lVar10,uVar13,0);
                          if (*(longlong *)(self + 0x78) != 0) {
                            FUN_7ffe999f2150(*(longlong *)(self + 0x78),iVar4 <= iVar3,0);
                            lVar10 = *(longlong *)(self + 0x80);
                            uVar13 = _DAT_7ffe9c94ce98;
                            if (iVar4 <= iVar3) {
                              uVar13 = _DAT_7ffe9c94cdd0;
                            }
                            if ((*(longlong *)(puStack_a8 + 0xb0) != 0) &&
                               (uVar13 = FUN_7ffe99a58320(*(longlong *)(puStack_a8 + 0xb0),uVar13,0)
                               , lVar10 != 0)) {
                              FUN_7ffe9a404310(lVar10,uVar13,0);
                              return;
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
LAB_7ffe9a0526dc:
  FUN_7ffe9996d7a0();
LAB_7ffe9a0526e2:
  FUN_7ffe9996d790();
LAB_7ffe9a0526e8:
  FUN_7ffe9996d7a0();
LAB_7ffe9a0526ed:
  FUN_7ffe9996d7a0();
LAB_7ffe9a0526f2:
  FUN_7ffe9996d7a0();
LAB_7ffe9a0526f7:
  FUN_7ffe9996d7a0();
LAB_7ffe9a0526fc:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
LAB_7ffe9a052708:
  FUN_7ffe9996d790();
LAB_7ffe9a05270d:
  FUN_7ffe9996d7a0();
LAB_7ffe9a052712:
  FUN_7ffe9996d7a0();
LAB_7ffe9a052717:
  FUN_7ffe9996d7a0();
LAB_7ffe9a05271c:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
LAB_7ffe9a052728:
  FUN_7ffe9996d7a0();
LAB_7ffe9a05272d:
  FUN_7ffe9996d7a0();
LAB_7ffe9a052732:
  FUN_7ffe9996d7a0();
LAB_7ffe9a052737:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
LAB_7ffe9a052743:
  FUN_7ffe9996d7a0();
LAB_7ffe9a052748:
  FUN_7ffe9996d7a0();
LAB_7ffe9a05274d:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}

