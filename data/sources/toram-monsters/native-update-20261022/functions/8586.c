
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MobMaster_ReadMaster
               (undefined *self,int fieldId,undefined *mobDbAsset,undefined *popMobList,
               undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  longlong *plVar8;
  longlong lVar9;
  longlong lVar10;
  undefined8 uVar11;
  longlong *plVar12;
  undefined *self_00;
  undefined8 *puVar13;
  undefined8 uVar14;
  ushort uVar15;
  int iVar16;
  uint uVar17;
  int aiStackX_10 [2];
  byte bStack_e8;
  longlong *plStack_e0;
  int iStack_d8;
  int iStack_d4;
  int iStack_d0;
  int iStack_cc;
  undefined8 uStack_c8;
  longlong **pplStack_c0;
  longlong *plStack_b8;
  longlong *plStack_b0;
  undefined8 uStack_a8;
  longlong **pplStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  longlong lStack_88;
  undefined *puStack_80;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 uStack_3c;
  longlong lStack_38;
  
  aiStackX_10[0] = fieldId;
  if (DAT_7ffe9cadd605 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c943bb8);
    FUN_7ffe9996d590(&DAT_7ffe9c8ff880);
    FUN_7ffe9996d590(&DAT_7ffe9c972940);
    FUN_7ffe9996d590(&DAT_7ffe9c972a10);
    FUN_7ffe9996d590(&DAT_7ffe9c8ff950);
    FUN_7ffe9996d590(&DAT_7ffe9c8ffaf0);
    FUN_7ffe9996d590(&DAT_7ffe9c8ffbc0);
    FUN_7ffe9996d590(&DAT_7ffe9c8ff060);
    FUN_7ffe9996d590(&DAT_7ffe9c8ffc90);
    FUN_7ffe9996d590(&DAT_7ffe9c8fd7c8);
    FUN_7ffe9996d590(&DAT_7ffe9c90a3b8);
    FUN_7ffe9996d590(&DAT_7ffe9c928a70);
    FUN_7ffe9996d590(&DAT_7ffe9c9375c8);
    FUN_7ffe9996d590(&DAT_7ffe9c937690);
    FUN_7ffe9996d590(0x7ffe9c937750);
    FUN_7ffe9996d590(&DAT_7ffe9c93efa8);
    FUN_7ffe9996d590(&DAT_7ffe9c93f380);
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c955350);
    FUN_7ffe9996d590(&DAT_7ffe9c95ae28);
    FUN_7ffe9996d590(&DAT_7ffe9c93ac18);
    FUN_7ffe9996d590(&DAT_7ffe9c917f28);
    FUN_7ffe9996d590(&DAT_7ffe9c94ba38);
    FUN_7ffe9996d590(&DAT_7ffe9c93c1d8);
    FUN_7ffe9996d590(0x7ffe9c93c2a0);
    FUN_7ffe9996d590(&DAT_7ffe9c969f48);
    FUN_7ffe9996d590(&DAT_7ffe9c8edfe8);
    FUN_7ffe9996d590(&DAT_7ffe9c91a6f8);
    FUN_7ffe9996d590(&DAT_7ffe9c8efec8);
    FUN_7ffe9996d590(&DAT_7ffe9c91b0b8);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c962b60);
    FUN_7ffe9996d590(&DAT_7ffe9c962dc0);
    FUN_7ffe9996d590(&DAT_7ffe9c8ee148);
    FUN_7ffe9996d590(&DAT_7ffe9c8eded8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f9a90);
    FUN_7ffe9996d590(&DAT_7ffe9c8f9d00);
    FUN_7ffe9996d590(&DAT_7ffe9c947bf8);
    FUN_7ffe9996d590(&DAT_7ffe9c947b30);
    FUN_7ffe9996d590(&DAT_7ffe9c947a70);
    FUN_7ffe9996d590(&DAT_7ffe9c9479a8);
    DAT_7ffe9cadd605 = '\x01';
  }
  iVar7 = 0;
  plStack_b8 = (longlong *)0x0;
  plStack_e0 = (longlong *)0x0;
  plStack_b0 = (longlong *)0x0;
  uStack_98 = (longlong *)0x0;
  uStack_90 = 0;
  lStack_88 = 0;
  plVar8 = (longlong *)func_0x7ffe9996c990(_DAT_7ffe9c91b0b8,1);
  iStack_d8 = fieldId;
  lVar9 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,&iStack_d8);
  if (plVar8 == (longlong *)0x0) goto LAB_7ffe9a33f15c;
  if ((lVar9 != 0) &&
     (lVar10 = func_0x7ffe9996c920(lVar9,*(undefined8 *)(*plVar8 + 0x40)), lVar10 == 0)) {
    uVar11 = func_0x7ffe9996d1f0();
    FUN_7ffe9996d760(uVar11,0);
    pcVar1 = (code *)swi(3);
    bVar4 = (*pcVar1)();
    return bVar4;
  }
  if ((int)plVar8[3] == 0) {
    FUN_7ffe9996d790();
LAB_7ffe9a33f178:
    FUN_7ffe9996d7a0();
LAB_7ffe9a33f17e:
    uVar11 = func_0x7ffe9996d1f0();
    FUN_7ffe9996d760(uVar11,0);
LAB_7ffe9a33f18d:
    FUN_7ffe9996d790();
LAB_7ffe9a33f192:
    uVar11 = func_0x7ffe9996d1f0();
    FUN_7ffe9996d760(uVar11,0);
LAB_7ffe9a33f1a1:
    FUN_7ffe9996d790();
LAB_7ffe9a33f1a6:
    uVar11 = func_0x7ffe9996d1f0();
    FUN_7ffe9996d760(uVar11,0);
LAB_7ffe9a33f1b5:
    FUN_7ffe9996d790();
LAB_7ffe9a33f1ba:
    uVar11 = func_0x7ffe9996d1f0();
    FUN_7ffe9996d760(uVar11,0);
LAB_7ffe9a33f1c9:
    FUN_7ffe9996d790();
LAB_7ffe9a33f1ce:
    FUN_7ffe9996d7a0();
LAB_7ffe9a33f1d3:
    FUN_7ffe9996d7a0();
LAB_7ffe9a33f1d8:
    FUN_7ffe9996d7a0();
LAB_7ffe9a33f1dd:
    FUN_7ffe9996d7a0();
LAB_7ffe9a33f1e2:
    uVar11 = func_0x7ffe9996d1f0();
    FUN_7ffe9996d760(uVar11,0);
LAB_7ffe9a33f1f1:
    FUN_7ffe9996d790();
LAB_7ffe9a33f1f6:
    FUN_7ffe9996d790();
LAB_7ffe9a33f1fb:
    FUN_7ffe9996d7a0();
LAB_7ffe9a33f200:
    FUN_7ffe9996d7a0();
LAB_7ffe9a33f205:
    FUN_7ffe9996d7a0();
LAB_7ffe9a33f20a:
    FUN_7ffe9996d7a0();
LAB_7ffe9a33f20f:
    FUN_7ffe9996d7a0();
LAB_7ffe9a33f214:
    FUN_7ffe9996d7a0();
LAB_7ffe9a33f219:
    FUN_7ffe9996d7a0();
LAB_7ffe9a33f21e:
    FUN_7ffe9996d7a0();
LAB_7ffe9a33f223:
    FUN_7ffe9996d7a0();
LAB_7ffe9a33f228:
    FUN_7ffe9996d7a0();
LAB_7ffe9a33f22d:
    FUN_7ffe9996d7a0();
LAB_7ffe9a33f232:
    FUN_7ffe9996d7a0();
LAB_7ffe9a33f237:
    FUN_7ffe9996d7a0();
    FUN_7ffe998fa550();
LAB_7ffe9a33f242:
    FUN_7ffe9996d7a0();
    FUN_7ffe998fa550();
  }
  else {
    plVar8[4] = lVar9;
    il2cpp_write_barrier_0();
    func_0x7ffe999c3920(_DAT_7ffe9c9479a8,plVar8,0);
    bStack_e8 = 1;
    if (*(longlong *)(self + 0x20) == 0) {
LAB_7ffe9a33f15c:
      FUN_7ffe9996d7a0();
      pcVar1 = (code *)swi(3);
      bVar4 = (*pcVar1)();
      return bVar4;
    }
    FUN_7ffe9acce330(*(longlong *)(self + 0x20),_DAT_7ffe9c8ff950);
    if (*(longlong *)(self + 0x28) == 0) goto LAB_7ffe9a33f15c;
    FUN_7ffe9acce330(*(longlong *)(self + 0x28),_DAT_7ffe9c972a10);
    lVar9 = *(longlong *)(self + 0x40);
    if (lVar9 == 0) goto LAB_7ffe9a33f15c;
    *(int *)(lVar9 + 0x1c) = *(int *)(lVar9 + 0x1c) + 1;
    iVar5 = *(int *)(lVar9 + 0x18);
    *(undefined4 *)(lVar9 + 0x18) = 0;
    if (0 < iVar5) {
      FUN_7ffe9b518970(*(undefined8 *)(lVar9 + 0x10),0);
    }
    self[0x38] = 0;
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar3 = FUN_7ffe9bda2160(mobDbAsset,0,0);
    if (cVar3 == '\0') {
LAB_7ffe9a33eceb:
      if ((*(longlong *)(self + 0x20) == 0) ||
         (lVar9 = FUN_7ffe9acd27a0(*(longlong *)(self + 0x20),_DAT_7ffe9c8ffc90), lVar9 == 0)) {
LAB_7ffe9a33f2a2:
        FUN_7ffe9996d7a0();
        pcVar1 = (code *)swi(3);
        bVar4 = (*pcVar1)();
        return bVar4;
      }
      iVar7 = FUN_7ffe9af43f50(lVar9,_DAT_7ffe9c8f9d00);
      if (iVar7 < 1) {
        return bStack_e8;
      }
      if (*(longlong *)(self + 0x20) == 0) goto LAB_7ffe9a33f2a2;
      uVar11 = FUN_7ffe9acd27a0(*(longlong *)(self + 0x20),_DAT_7ffe9c8ffc90);
      if (*(int *)(_DAT_7ffe9c8eded8 + 0xe0) == 0) {
        func_0x7ffe9996d830(_DAT_7ffe9c8eded8);
      }
      lVar9 = *(longlong *)(*(longlong *)(_DAT_7ffe9c8eded8 + 0xb8) + 8);
      if (lVar9 == 0) {
        if (*(int *)(_DAT_7ffe9c8eded8 + 0xe0) == 0) {
          func_0x7ffe9996d830(_DAT_7ffe9c8eded8);
        }
        uVar14 = **(undefined8 **)(_DAT_7ffe9c8eded8 + 0xb8);
        lVar9 = func_0x7ffe99940040(_DAT_7ffe9c93f380);
        FUN_7ffe9af13420(lVar9,uVar14,_DAT_7ffe9c962b60,0);
        *(longlong *)(*(longlong *)(_DAT_7ffe9c8eded8 + 0xb8) + 8) = lVar9;
        il2cpp_write_barrier_0();
      }
      lVar9 = FUN_7ffe9ab93080(uVar11,lVar9,_DAT_7ffe9c928a70);
      if (lVar9 == 0) goto LAB_7ffe9a33f2a2;
      plStack_b0 = (longlong *)FUN_7ffe99742ec0(0,_DAT_7ffe9c955350,lVar9);
      uStack_c8 = 0;
      pplStack_c0 = &plStack_b0;
      while (plStack_b0 != (longlong *)0x0) {
        cVar3 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ac18);
        if (cVar3 == '\0') {
          if (*pplStack_c0 == (longlong *)0x0) {
            return bStack_e8;
          }
          FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
          return bStack_e8;
        }
        lVar9 = func_0x7ffe99940040(_DAT_7ffe9c8ee148);
        func_0x7ffe999c3920(lVar9,0);
        plVar8 = plStack_b0;
        if (plStack_b0 == (longlong *)0x0) goto LAB_7ffe9a33f291;
        lVar10 = *plStack_b0;
        uVar15 = 0;
        if (*(ushort *)(lVar10 + 0x12e) != 0) {
          do {
            if (*(longlong *)(*(longlong *)(lVar10 + 0xb0) + (ulonglong)uVar15 * 0x10) ==
                _DAT_7ffe9c95ae28) {
              puVar13 = (undefined8 *)
                        (lVar10 + 0x138 +
                        (longlong)
                        *(int *)(*(longlong *)(lVar10 + 0xb0) + 8 + (ulonglong)uVar15 * 0x10) * 0x10
                        );
              goto LAB_7ffe9a33eeb9;
            }
            uVar15 = uVar15 + 1;
          } while (uVar15 < *(ushort *)(lVar10 + 0x12e));
        }
        puVar13 = (undefined8 *)FUN_7ffe998ce540(plStack_b0,_DAT_7ffe9c95ae28,0);
LAB_7ffe9a33eeb9:
        lVar10 = (*(code *)*puVar13)(plVar8,puVar13[1]);
        if (lVar9 == 0) goto LAB_7ffe9a33f28c;
        plVar8 = (longlong *)(lVar9 + 0x10);
        *plVar8 = lVar10;
        il2cpp_write_barrier_0();
        uVar11 = *(undefined8 *)(self + 0x40);
        uVar14 = func_0x7ffe99940040(_DAT_7ffe9c93efa8);
        FUN_7ffe9af13420(uVar14,lVar9,_DAT_7ffe9c962dc0,0);
        lVar9 = FUN_7ffe9ab854c0(uVar11,uVar14,_DAT_7ffe9c90a3b8);
        if (lVar9 == 0) {
          lVar9 = func_0x7ffe99940040(_DAT_7ffe9c8edfe8);
          FUN_7ffe9a330a00(lVar9,0);
          if (lVar9 == 0) goto LAB_7ffe9a33f25d;
          FUN_7ffe9a3305f0(lVar9,*plVar8,0);
          if (*(longlong *)(self + 0x40) == 0) goto LAB_7ffe9a33f258;
          FUN_7ffe99743100(*(longlong *)(self + 0x40),lVar9,_DAT_7ffe9c93c1d8);
          if (*plVar8 == 0) goto LAB_7ffe9a33f253;
          *(longlong *)(*plVar8 + 0xa8) = lVar9;
          il2cpp_write_barrier_0();
        }
        if (*plVar8 == 0) goto LAB_7ffe9a33f287;
        lVar10 = *(longlong *)(*plVar8 + 0x98);
        if (lVar10 == 0) goto LAB_7ffe9a33f282;
        lVar10 = FUN_7ffe9acd27a0(lVar10,_DAT_7ffe9c8ff060);
        if (lVar10 == 0) goto LAB_7ffe9a33f27d;
        FUN_7ffe9af415c0(&uStack_48,lVar10,_DAT_7ffe9c8f9a90);
        uStack_98 = (longlong *)CONCAT44(uStack_44,uStack_48);
        uStack_90 = CONCAT44(uStack_3c,uStack_40);
        lStack_88 = lStack_38;
        uStack_a8 = 0;
        pplStack_a0 = (longlong **)&uStack_98;
        while (cVar3 = FUN_7ffe9ae37290(&uStack_98,_DAT_7ffe9c937690), lVar10 = lStack_88,
              cVar3 != '\0') {
          if (*(longlong *)(self + 0x20) == 0) goto LAB_7ffe9a33f272;
          uVar11 = FUN_7ffe9acd26f0(*(longlong *)(self + 0x20),_DAT_7ffe9c8ffbc0);
          if (lVar10 == 0) goto LAB_7ffe9a33f26d;
          cVar3 = FUN_7ffe9ab7fc00(uVar11,*(undefined4 *)(lVar10 + 0x18),_DAT_7ffe9c8fd7c8);
          if (cVar3 != '\0') {
            if (*(longlong *)(self + 0x20) == 0) goto LAB_7ffe9a33f268;
            uVar11 = FUN_7ffe9ad356e0(*(longlong *)(self + 0x20),*(undefined4 *)(lVar10 + 0x18),
                                      _DAT_7ffe9c8ffaf0);
            if (lVar9 == 0) goto LAB_7ffe9a33f263;
            FUN_7ffe9a3305f0(lVar9,uVar11,0);
          }
        }
        func_0x7ffe999c3920(&uStack_98,_DAT_7ffe9c9375c8);
      }
      goto LAB_7ffe9a33f296;
    }
    if (mobDbAsset != (undefined *)0x0) {
      uVar11 = FUN_7ffe9bda7ca0(mobDbAsset,0);
      plVar8 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c969f48);
      FUN_7ffe9b4c0ad0(plVar8,uVar11,0);
      uStack_c8 = 0;
      pplStack_c0 = &plStack_b8;
      plStack_b8 = plVar8;
      plVar12 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c943bb8);
      FUN_7ffe9b4cd430(plVar12,plVar8,0);
      uStack_a8 = 0;
      pplStack_a0 = &plStack_e0;
      plStack_e0 = plVar12;
      if (plVar12 == (longlong *)0x0) goto LAB_7ffe9a33f237;
      iVar5 = (**(code **)(*plVar12 + 0x228))(plVar12,*(undefined8 *)(*plVar12 + 0x230));
      iStack_d0 = iVar5;
      if (iVar5 < 1) {
        if (plStack_e0 == (longlong *)0x0) goto LAB_7ffe9a33f178;
        iVar5 = (**(code **)(*plStack_e0 + 0x228))(plStack_e0,*(undefined8 *)(*plStack_e0 + 0x230));
      }
      plVar8 = (longlong *)func_0x7ffe9996c990(_DAT_7ffe9c91b0b8,2);
      iStack_d8 = iVar5;
      lVar9 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,&iStack_d8);
      if (plVar8 == (longlong *)0x0) goto LAB_7ffe9a33f232;
      if ((lVar9 != 0) &&
         (lVar10 = func_0x7ffe9996c920(lVar9,*(undefined8 *)(*plVar8 + 0x40)), lVar10 == 0))
      goto LAB_7ffe9a33f17e;
      if ((int)plVar8[3] == 0) goto LAB_7ffe9a33f18d;
      plVar8[4] = lVar9;
      il2cpp_write_barrier_0();
      iStack_d4 = iStack_d0;
      lVar9 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,&iStack_d4);
      if ((lVar9 != 0) &&
         (lVar10 = func_0x7ffe9996c920(lVar9,*(undefined8 *)(*plVar8 + 0x40)), lVar10 == 0))
      goto LAB_7ffe9a33f192;
      if (*(uint *)(plVar8 + 3) < 2) goto LAB_7ffe9a33f1a1;
      plVar8[5] = lVar9;
      il2cpp_write_barrier_0();
      func_0x7ffe999c3920(_DAT_7ffe9c947b30,plVar8,0);
      if (iVar5 == aiStackX_10[0]) {
        if (plStack_e0 != (longlong *)0x0) {
          iVar5 = (**(code **)(*plStack_e0 + 0x228))
                            (plStack_e0,*(undefined8 *)(*plStack_e0 + 0x230));
          iStack_cc = iVar5;
          plVar8 = (longlong *)func_0x7ffe9996c990(_DAT_7ffe9c91b0b8,1);
          iStack_d4 = iVar5;
          lVar9 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,&iStack_d4);
          if (plVar8 != (longlong *)0x0) {
            if ((lVar9 != 0) &&
               (lVar10 = func_0x7ffe9996c920(lVar9,*(undefined8 *)(*plVar8 + 0x40)), lVar10 == 0))
            goto LAB_7ffe9a33f1a6;
            if ((int)plVar8[3] == 0) goto LAB_7ffe9a33f1b5;
            plVar8[4] = lVar9;
            il2cpp_write_barrier_0();
            func_0x7ffe999c3920(_DAT_7ffe9c947a70,plVar8,0);
            while (iVar2 = iStack_d0, iVar16 = 0, iStack_d8 = iVar7, iVar7 < iVar5) {
              puStack_80 = MobStatusMaster_CreateStatusMaster
                                     (aiStackX_10[0],iStack_d0,(undefined *)plStack_e0,
                                      (undefined *)0x0);
              if (puStack_80 == (undefined *)0x0) goto LAB_7ffe9a33f1dd;
              if (*(longlong *)(self + 0x20) == 0) goto LAB_7ffe9a33f1d8;
              FUN_7ffe9ad4d2a0(*(longlong *)(self + 0x20),*(undefined4 *)(puStack_80 + 0x10));
              if (iVar2 < -1) {
                if (plStack_e0 == (longlong *)0x0) goto LAB_7ffe9a33f1d3;
                iVar7 = (**(code **)(*plStack_e0 + 0x228))
                                  (plStack_e0,*(undefined8 *)(*plStack_e0 + 0x230));
                iStack_d4 = iVar7;
                if (0 < iVar7) {
                  plVar8 = (longlong *)func_0x7ffe9996c990(_DAT_7ffe9c91a6f8,iVar7);
                  for (uVar17 = 0; plVar12 = plStack_e0, (int)uVar17 < iVar7; uVar17 = uVar17 + 1) {
                    self_00 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c8efec8);
                    MobPropertyMaster__ctor(self_00,(undefined *)plVar12,(undefined *)0x0);
                    if (plVar8 == (longlong *)0x0) goto LAB_7ffe9a33f1ce;
                    if ((self_00 != (undefined *)0x0) &&
                       (lVar9 = func_0x7ffe9996c920(self_00,*(undefined8 *)(*plVar8 + 0x40)),
                       lVar9 == 0)) goto LAB_7ffe9a33f1ba;
                    if (*(uint *)(plVar8 + 3) <= uVar17) goto LAB_7ffe9a33f1c9;
                    plVar8[(longlong)(int)uVar17 + 4] = (longlong)self_00;
                    il2cpp_write_barrier_0();
                    iVar7 = iStack_d4;
                  }
                  MobStatusMaster_SetMobPropertyMaster
                            (puStack_80,(undefined *)plVar8,(undefined *)0x0);
                  iVar5 = iStack_cc;
                }
              }
              iVar7 = iStack_d8 + 1;
            }
            if (iStack_d0 < 0) {
              if (plStack_e0 == (longlong *)0x0) goto LAB_7ffe9a33f21e;
              iVar7 = (**(code **)(*plStack_e0 + 0x228))
                                (plStack_e0,*(undefined8 *)(*plStack_e0 + 0x230));
              iStack_cc = iVar7;
              plVar8 = (longlong *)func_0x7ffe9996c990(_DAT_7ffe9c91b0b8,1);
              aiStackX_10[0] = iVar7;
              lVar9 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,aiStackX_10);
              if (plVar8 == (longlong *)0x0) goto LAB_7ffe9a33f219;
              if ((lVar9 != 0) &&
                 (lVar10 = func_0x7ffe9996c920(lVar9,*(undefined8 *)(*plVar8 + 0x40)), lVar10 == 0))
              goto LAB_7ffe9a33f1e2;
              if ((int)plVar8[3] == 0) goto LAB_7ffe9a33f1f1;
              plVar8[4] = lVar9;
              il2cpp_write_barrier_0();
              func_0x7ffe999c3920(_DAT_7ffe9c947bf8,plVar8,0);
              for (; iVar16 < iVar7; iVar16 = iVar16 + 1) {
                if (plStack_e0 == (longlong *)0x0) goto LAB_7ffe9a33f214;
                aiStackX_10[0] =
                     (**(code **)(*plStack_e0 + 0x228))
                               (plStack_e0,*(undefined8 *)(*plStack_e0 + 0x230));
                if (plStack_e0 == (longlong *)0x0) goto LAB_7ffe9a33f20f;
                iVar7 = (**(code **)(*plStack_e0 + 0x228))
                                  (plStack_e0,*(undefined8 *)(*plStack_e0 + 0x230));
                lVar9 = func_0x7ffe9996c990(_DAT_7ffe9c917f28,iVar7);
                for (uVar17 = 0; (int)uVar17 < iVar7; uVar17 = uVar17 + 1) {
                  if (plStack_e0 == (longlong *)0x0) goto LAB_7ffe9a33f205;
                  uVar6 = (**(code **)(*plStack_e0 + 0x228))
                                    (plStack_e0,*(undefined8 *)(*plStack_e0 + 0x230));
                  if (lVar9 == 0) goto LAB_7ffe9a33f200;
                  if (*(uint *)(lVar9 + 0x18) <= uVar17) goto LAB_7ffe9a33f1f6;
                  *(undefined4 *)(lVar9 + 0x20 + (longlong)(int)uVar17 * 4) = uVar6;
                  if (plStack_e0 == (longlong *)0x0) goto LAB_7ffe9a33f1fb;
                  (**(code **)(*plStack_e0 + 0x228))
                            (plStack_e0,*(undefined8 *)(*plStack_e0 + 0x230));
                }
                if (*(longlong *)(self + 0x28) == 0) goto LAB_7ffe9a33f20a;
                FUN_7ffe9ad4d2a0(*(longlong *)(self + 0x28),aiStackX_10[0],lVar9,_DAT_7ffe9c972940);
                iVar7 = iStack_cc;
              }
            }
            goto LAB_7ffe9a33ebd9;
          }
          goto LAB_7ffe9a33f228;
        }
        goto LAB_7ffe9a33f22d;
      }
      bStack_e8 = 0;
LAB_7ffe9a33ebd9:
      if (plStack_e0 == (longlong *)0x0) goto LAB_7ffe9a33f223;
      (**(code **)(*plStack_e0 + 0x198))(plStack_e0,*(undefined8 *)(*plStack_e0 + 0x1a0));
      if (plStack_e0 != (longlong *)0x0) {
        FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
      }
      if (plStack_b8 != (longlong *)0x0) {
        (**(code **)(*plStack_b8 + 600))(plStack_b8,*(undefined8 *)(*plStack_b8 + 0x260));
        if (plStack_b8 != (longlong *)0x0) {
          FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
        }
        goto LAB_7ffe9a33eceb;
      }
      goto LAB_7ffe9a33f242;
    }
  }
  FUN_7ffe9996d7a0();
LAB_7ffe9a33f253:
  FUN_7ffe9996d7a0();
LAB_7ffe9a33f258:
  FUN_7ffe9996d7a0();
LAB_7ffe9a33f25d:
  FUN_7ffe9996d7a0();
LAB_7ffe9a33f263:
  FUN_7ffe9996d7a0();
LAB_7ffe9a33f268:
  FUN_7ffe9996d7a0();
LAB_7ffe9a33f26d:
  FUN_7ffe9996d7a0();
LAB_7ffe9a33f272:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
LAB_7ffe9a33f27d:
  FUN_7ffe9996d7a0();
LAB_7ffe9a33f282:
  FUN_7ffe9996d7a0();
LAB_7ffe9a33f287:
  FUN_7ffe9996d7a0();
LAB_7ffe9a33f28c:
  FUN_7ffe9996d7a0();
LAB_7ffe9a33f291:
  FUN_7ffe9996d7a0();
LAB_7ffe9a33f296:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar1 = (code *)swi(3);
  bVar4 = (*pcVar1)();
  return bVar4;
}

