
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * UIEquipCristaPanel_GetPowerUpCristaList(undefined *self,undefined *methodInfo)

{
  int iVar1;
  undefined8 uVar2;
  code *pcVar3;
  longlong lVar4;
  char cVar5;
  int iVar6;
  undefined *puVar7;
  undefined *puVar8;
  longlong lVar9;
  longlong lVar10;
  longlong lVar11;
  undefined8 uVar12;
  longlong lVar13;
  bool bVar14;
  undefined8 uStack_90;
  undefined8 uStack_88;
  longlong lStack_80;
  undefined *puStack_78;
  undefined *puStack_70;
  longlong lStack_68;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  undefined4 uStack_58;
  undefined4 uStack_54;
  longlong lStack_50;
  
  if (DAT_7ffe9cadb47c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c923968);
    FUN_7ffe9996d590(&DAT_7ffe9c923a30);
    FUN_7ffe9996d590(&DAT_7ffe9c9238a0);
    FUN_7ffe9996d590(&DAT_7ffe9c923af8);
    FUN_7ffe9996d590(&DAT_7ffe9c918ff0);
    FUN_7ffe9996d590(&DAT_7ffe9c909ac8);
    FUN_7ffe9996d590(&DAT_7ffe9c911a48);
    FUN_7ffe9996d590(&DAT_7ffe9c9165d0);
    FUN_7ffe9996d590(&DAT_7ffe9c91e278);
    FUN_7ffe9996d590(&DAT_7ffe9c8f8e58);
    FUN_7ffe9996d590(&DAT_7ffe9c8f8f28);
    FUN_7ffe9996d590(0x7ffe9c8f8ff8);
    FUN_7ffe9996d590(&DAT_7ffe9c935310);
    FUN_7ffe9996d590(&DAT_7ffe9c93c8a8);
    FUN_7ffe9996d590(&DAT_7ffe9c935248);
    FUN_7ffe9996d590(&DAT_7ffe9c92f680);
    FUN_7ffe9996d590(&DAT_7ffe9c92f5c0);
    FUN_7ffe9996d590(&DAT_7ffe9c92fb18);
    FUN_7ffe9996d590(&DAT_7ffe9c92f438);
    FUN_7ffe9996d590(&DAT_7ffe9c96b698);
    FUN_7ffe9996d590(&DAT_7ffe9c93e008);
    FUN_7ffe9996d590(&DAT_7ffe9c93e0c8);
    FUN_7ffe9996d590(&DAT_7ffe9c93edd0);
    FUN_7ffe9996d590(&DAT_7ffe9c945db0);
    FUN_7ffe9996d590(&DAT_7ffe9c93ee90);
    FUN_7ffe9996d590(&DAT_7ffe9c945e70);
    FUN_7ffe9996d590(&DAT_7ffe9c9459d8);
    DAT_7ffe9cadb47c = '\x01';
  }
  puVar7 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c96b698);
  FUN_7ffe9af8a010(puVar7);
  puStack_70 = puVar7;
  puVar8 = UIEquipCristaPanel_GetAllPowerUpCristaList(self,(undefined *)0x0);
  puStack_78 = puVar8;
  if ((*(longlong *)(self + 0x158) != 0) &&
     (lVar9 = FUN_7ffe9a480070(*(longlong *)(self + 0x158),0), lVar9 != 0)) {
    lVar9 = FUN_7ffe9a4a21b0(lVar9,*(undefined4 *)(self + 0x170),0);
    lVar10 = func_0x7ffe99940040(_DAT_7ffe9c918ff0);
    FUN_7ffe9ada4840(lVar10,_DAT_7ffe9c9238a0);
    lStack_68 = lVar10;
    if (puVar8 != (undefined *)0x0) {
      FUN_7ffe9af836a0(&uStack_90,puVar8);
      uStack_60 = (undefined4)uStack_90;
      uStack_5c = uStack_90._4_4_;
      uStack_58 = (undefined4)uStack_88;
      uStack_54 = uStack_88._4_4_;
      lStack_50 = lStack_80;
      uStack_90 = 0;
      uStack_88 = &uStack_60;
LAB_7ffe99dd3218:
      cVar5 = FUN_7ffe9ae28ed0(&uStack_60,_DAT_7ffe9c8f8f28);
      lVar4 = lStack_50;
      if (cVar5 != '\0') {
        lVar11 = func_0x7ffe99940040(_DAT_7ffe9c945db0);
        func_0x7ffe999c3920(lVar11,0);
        if (lVar4 != 0) {
          iVar6 = *(int *)(lVar4 + 0x34);
          if (lVar11 != 0) {
            *(int *)(lVar11 + 0x10) = iVar6;
            if (lVar9 != 0) goto code_r0x7ffe99dd326d;
            goto LAB_7ffe99dd32e5;
          }
          goto LAB_7ffe99dd3692;
        }
        goto LAB_7ffe99dd3697;
      }
      func_0x7ffe999c3920(&uStack_60,_DAT_7ffe9c8f8e58);
      if (lVar10 != 0) {
        iVar6 = func_0x7ffe9acd8120(lVar10,_DAT_7ffe9c923af8);
        if (0 < iVar6) {
          if (*(int *)(_DAT_7ffe9c9459d8 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          lVar9 = *(longlong *)(*(longlong *)(_DAT_7ffe9c9459d8 + 0xb8) + 0x20);
          if (lVar9 == 0) {
            if (*(int *)(_DAT_7ffe9c9459d8 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            uVar12 = **(undefined8 **)(_DAT_7ffe9c9459d8 + 0xb8);
            lVar9 = func_0x7ffe99940040(_DAT_7ffe9c935248);
            FUN_7ffe9af13120(lVar9,uVar12,_DAT_7ffe9c93e008,0);
            *(longlong *)(*(longlong *)(_DAT_7ffe9c9459d8 + 0xb8) + 0x20) = lVar9;
            il2cpp_write_barrier_0();
          }
          uVar12 = FUN_7ffe9ab8b7d0(lVar10,lVar9,_DAT_7ffe9c911a48);
          if (*(int *)(_DAT_7ffe9c9459d8 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          lVar9 = *(longlong *)(*(longlong *)(_DAT_7ffe9c9459d8 + 0xb8) + 0x28);
          if (lVar9 == 0) {
            if (*(int *)(_DAT_7ffe9c9459d8 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            uVar2 = **(undefined8 **)(_DAT_7ffe9c9459d8 + 0xb8);
            lVar9 = func_0x7ffe99940040(_DAT_7ffe9c935310);
            FUN_7ffe9af13360(lVar9,uVar2,_DAT_7ffe9c93e0c8,0);
            *(longlong *)(*(longlong *)(_DAT_7ffe9c9459d8 + 0xb8) + 0x28) = lVar9;
            il2cpp_write_barrier_0();
          }
          uVar12 = FUN_7ffe9ab8c200(uVar12,lVar9,_DAT_7ffe9c9165d0);
          uVar12 = FUN_7ffe9ab90b60(uVar12,_DAT_7ffe9c91e278);
          if (puVar7 == (undefined *)0x0) goto LAB_7ffe99dd3663;
          func_0x7ffe9afd5600(puVar7,uVar12,_DAT_7ffe9c92f680);
          FUN_7ffe9acce330(lVar10,_DAT_7ffe9c923a30);
        }
        return puVar7;
      }
    }
  }
LAB_7ffe99dd3663:
  FUN_7ffe9996d7a0();
LAB_7ffe99dd3669:
  FUN_7ffe9996d790();
LAB_7ffe99dd366f:
  FUN_7ffe9996d7a0();
LAB_7ffe99dd3674:
  FUN_7ffe9996d7a0();
LAB_7ffe99dd3679:
  FUN_7ffe9996d7a0();
LAB_7ffe99dd367e:
  FUN_7ffe9996d7a0();
LAB_7ffe99dd3683:
  FUN_7ffe9996d7a0();
LAB_7ffe99dd3688:
  FUN_7ffe9996d7a0();
LAB_7ffe99dd368d:
  FUN_7ffe9996d7a0();
LAB_7ffe99dd3692:
  FUN_7ffe9996d7a0();
LAB_7ffe99dd3697:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar3 = (code *)swi(3);
  puVar7 = (undefined *)(*pcVar3)();
  return puVar7;
code_r0x7ffe99dd326d:
  if ((iVar6 != *(int *)(lVar9 + 0x48)) && (iVar6 != *(int *)(lVar9 + 0x4c))) {
    iVar6 = *(int *)(lVar9 + 0x4c);
    if (self[0x17c] != '\x01') {
      iVar6 = *(int *)(lVar9 + 0x48);
    }
    puVar8 = UIEquipCristaPanel_GetPowerUpCristaOrderList(self,iVar6,(undefined *)0x0);
    uVar12 = func_0x7ffe99940040(_DAT_7ffe9c93c8a8);
    FUN_7ffe9af13420(uVar12,lVar11,_DAT_7ffe9c93edd0);
    lVar11 = FUN_7ffe9ab854c0(puVar8,uVar12);
    if (lVar11 == 0) {
LAB_7ffe99dd32e5:
      if (self[0x17c] != '\0') {
        lVar11 = func_0x7ffe99940040(_DAT_7ffe9c945e70);
        func_0x7ffe999c3920(lVar11,0);
        if (lVar9 == 0) goto LAB_7ffe99dd368d;
        lVar13 = FUN_7ffe9a56fe40(lVar9,0);
        if (lVar13 == 0) goto LAB_7ffe99dd3688;
        if (*(uint *)(lVar13 + 0x18) <= (uint)((ulonglong)(byte)self[0x17c] - 1))
        goto LAB_7ffe99dd3669;
        iVar6 = *(int *)(lVar13 + 0x20 + ((ulonglong)(byte)self[0x17c] - 1) * 4);
        if (*(longlong *)(lVar4 + 0x28) == 0) goto LAB_7ffe99dd3683;
        iVar1 = *(int *)(*(longlong *)(lVar4 + 0x28) + 0x48);
        if (lVar11 == 0) goto LAB_7ffe99dd367e;
        *(int *)(lVar11 + 0x10) = iVar1;
        if (iVar1 == iVar6) {
          if (puVar7 == (undefined *)0x0) goto LAB_7ffe99dd3679;
          FUN_7ffe99743100(puVar7,lVar4);
        }
        else {
          while (bVar14 = *(int *)(lVar11 + 0x10) == iVar6, !bVar14) {
            lVar13 = *(longlong *)(lVar11 + 0x18);
            if (lVar13 == 0) {
              lVar13 = func_0x7ffe99940040(_DAT_7ffe9c93c8a8);
              FUN_7ffe9af13420(lVar13,lVar11,_DAT_7ffe9c93ee90);
              *(longlong *)(lVar11 + 0x18) = lVar13;
              il2cpp_write_barrier_0();
            }
            lVar13 = FUN_7ffe9ab854c0(puStack_78,lVar13);
            if (lVar13 == 0) {
              bVar14 = *(int *)(lVar11 + 0x10) == iVar6;
              break;
            }
            if (*(longlong *)(lVar13 + 0x28) == 0) goto LAB_7ffe99dd366f;
            *(undefined4 *)(lVar11 + 0x10) = *(undefined4 *)(*(longlong *)(lVar13 + 0x28) + 0x48);
          }
          if (bVar14) {
            if (lVar10 == 0) goto LAB_7ffe99dd3674;
            FUN_7ffe9ada6d20(lVar10,lVar4);
          }
        }
      }
    }
  }
  goto LAB_7ffe99dd3218;
}

