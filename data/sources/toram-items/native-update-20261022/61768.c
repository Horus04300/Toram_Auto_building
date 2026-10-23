
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float UIItemProperty_WeaponPropertys
                (undefined *self,undefined *itemData,undefined *text,byte isPotentialZero,
                undefined *methodInfo)

{
  int iVar1;
  undefined *capVal;
  code *pcVar2;
  byte bVar3;
  char cVar4;
  short sVar5;
  undefined4 uVar6;
  longlong lVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined *puVar12;
  undefined *itemPropertyTextManager;
  longlong lVar13;
  longlong lVar14;
  undefined8 *puVar15;
  longlong *plVar16;
  uint uVar17;
  ulonglong uVar18;
  longlong lVar19;
  int iVar20;
  int iVar21;
  bool bVar22;
  uint uVar23;
  float fVar24;
  float fVar25;
  byte bStack_1a8;
  byte abStack_1a7 [3];
  int iStack_1a4;
  undefined1 auStack_1a0 [4];
  undefined2 auStack_19c [2];
  undefined8 uStack_198;
  undefined2 auStack_190 [4];
  undefined *puStack_188;
  float fStack_180;
  undefined8 uStack_178;
  float fStack_170;
  undefined8 uStack_168;
  longlong lStack_160;
  int aiStack_158 [2];
  undefined8 uStack_150;
  int aiStack_148 [4];
  undefined8 uStack_138;
  float fStack_130;
  undefined8 uStack_128;
  float fStack_120;
  undefined8 uStack_118;
  undefined4 uStack_110;
  float fStack_100;
  undefined *puStack_f8;
  float fStack_f0;
  float fStack_e0;
  undefined *puStack_d8;
  float fStack_d0;
  undefined8 uStack_c8;
  undefined8 uStack_c0;
  undefined8 uStack_b8;
  undefined8 uStack_b0;
  undefined1 auStack_a8 [16];
  undefined1 auStack_98 [96];
  
  if (DAT_7ffe9cadbb22 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9118d0);
    FUN_7ffe9996d590(&DAT_7ffe9c94c948);
    FUN_7ffe9996d590(&DAT_7ffe9c954bb0);
    FUN_7ffe9996d590(&DAT_7ffe9c94b8b0);
    FUN_7ffe9996d590(&DAT_7ffe9c917f28);
    FUN_7ffe9996d590(&DAT_7ffe9c94ba38);
    FUN_7ffe9996d590(&DAT_7ffe9c90a8e0);
    FUN_7ffe9996d590(&DAT_7ffe9c90af60);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c949440);
    FUN_7ffe9996d590(&DAT_7ffe9c953710);
    FUN_7ffe9996d590(&DAT_7ffe9c9538a8);
    FUN_7ffe9996d590(&DAT_7ffe9c96b310);
    FUN_7ffe9996d590(&DAT_7ffe9c8ede90);
    FUN_7ffe9996d590(&DAT_7ffe9c8ee100);
    FUN_7ffe9996d590(&DAT_7ffe9c8f3b08);
    FUN_7ffe9996d590(&DAT_7ffe9c933a80);
    FUN_7ffe9996d590(&DAT_7ffe9c933150);
    FUN_7ffe9996d590(&DAT_7ffe9c933b40);
    FUN_7ffe9996d590(&DAT_7ffe9c9336a8);
    FUN_7ffe9996d590(&DAT_7ffe9c932078);
    FUN_7ffe9996d590(&DAT_7ffe9c8f7318);
    FUN_7ffe9996d590(&DAT_7ffe9c920640);
    FUN_7ffe9996d590(&DAT_7ffe9c91ac58);
    FUN_7ffe9996d590(0x7ffe9c932bf0);
    FUN_7ffe9996d590(&DAT_7ffe9c933c08);
    FUN_7ffe9996d590(0x7ffe9c932b30);
    FUN_7ffe9996d590(&DAT_7ffe9c9339b8);
    FUN_7ffe9996d590(&DAT_7ffe9c932510);
    FUN_7ffe9996d590(&DAT_7ffe9c932758);
    FUN_7ffe9996d590(&DAT_7ffe9c91f830);
    FUN_7ffe9996d590(&DAT_7ffe9c9335e8);
    FUN_7ffe9996d590(&DAT_7ffe9c933088);
    FUN_7ffe9996d590(&DAT_7ffe9c932448);
    FUN_7ffe9996d590(&DAT_7ffe9c9325d0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f9660);
    FUN_7ffe9996d590(&DAT_7ffe9c932698);
    FUN_7ffe9996d590(&DAT_7ffe9c933210);
    FUN_7ffe9996d590(0x7ffe9c932200);
    FUN_7ffe9996d590(&DAT_7ffe9c934538);
    FUN_7ffe9996d590(&DAT_7ffe9c932388);
    FUN_7ffe9996d590(&DAT_7ffe9c9332d8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f3bd8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f5150);
    FUN_7ffe9996d590(&DAT_7ffe9c916b90);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1820);
    FUN_7ffe9996d590(0x7ffe9c932cb8);
    FUN_7ffe9996d590(&DAT_7ffe9c931fb0);
    FUN_7ffe9996d590(&DAT_7ffe9c920578);
    FUN_7ffe9996d590(&DAT_7ffe9c9328e0);
    FUN_7ffe9996d590(&DAT_7ffe9c932820);
    FUN_7ffe9996d590(&DAT_7ffe9c91fd18);
    FUN_7ffe9996d590(&DAT_7ffe9c932a68);
    DAT_7ffe9cadbb22 = '\x01';
  }
  uVar23 = 0;
  iVar20 = 0;
  aiStack_148[0] = 0;
  auStack_190[0] = 0;
  bVar22 = false;
  auStack_1a0[0] = 0;
  aiStack_158[0] = 0;
  if (itemData == (undefined *)0x0) goto LAB_7ffe99ec969e;
  bVar3 = UIItemListManager_CheckEquipItem
                    ((undefined *)(ulonglong)*(uint *)(itemData + 0x38),(undefined *)0x0);
  if (bVar3 == 0) {
    return 0.0;
  }
  lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c953710);
  if (lVar7 == 0) goto LAB_7ffe99ec969e;
  lStack_160 = FUN_7ffe9a57a320(lVar7,*(undefined4 *)(itemData + 0x34),0);
  abStack_1a7[0] = func_0x7ffe9a2782f0(*(undefined4 *)(itemData + 0x38),0);
  fVar25 = _DAT_7ffe9c049cfc;
  iStack_1a4 = *(int *)(itemData + 0x38);
  if (abStack_1a7[0] == 0) {
    lVar7 = FUN_7ffe99ec9e00(self,0);
    if (lVar7 == 0) {
LAB_7ffe99ec96a4:
      FUN_7ffe9996d7a0();
      pcVar2 = (code *)swi(3);
      fVar25 = (float)(*pcVar2)();
      return fVar25;
    }
    uVar8 = FUN_7ffe99a58320(lVar7,_DAT_7ffe9c932a68,0);
    lVar7 = FUN_7ffe99ec9e00(self,0);
    uStack_198._4_4_ = *(undefined4 *)(itemData + 0x38);
    uVar9 = FUN_7ffe9b5043c0((undefined2 *)((longlong)&uStack_198 + 4),0);
    uVar9 = FUN_7ffe9b3675b0(_DAT_7ffe9c934538,uVar9,0);
    if (lVar7 == 0) goto LAB_7ffe99ec96a4;
    uVar9 = FUN_7ffe99a58320(lVar7,uVar9,0);
    auStack_19c[0] = *(undefined2 *)(itemData + 0x42);
    uVar10 = func_0x7ffe9996c8e0(_DAT_7ffe9c94b8b0,auStack_19c);
    uVar8 = FUN_7ffe9b36a9f0(uVar8,uVar9,uVar10,0);
    uVar8 = FUN_7ffe9b3675b0(text,uVar8,0);
LAB_7ffe99ec7d4a:
    if (lStack_160 == 0) goto LAB_7ffe99ec969e;
  }
  else {
    if (iStack_1a4 == 0x17) {
      aiStack_148[0] =
           ((int)(((float)(byte)itemData[0x58] / _DAT_7ffe9c049dd0) * _DAT_7ffe9c049cfc) / 100) *
           100;
      uVar8 = _DAT_7ffe9c91fd18;
      if (99 < aiStack_148[0]) {
        lVar7 = FUN_7ffe9b5043c0(aiStack_148,0);
        if (lVar7 == 0) goto LAB_7ffe99ec969e;
        auStack_190[0] = FUN_7ffe9b3713a0(lVar7,*(int *)(lVar7 + 0x10) + -3,0);
        if (*(int *)(_DAT_7ffe9c954bb0 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        uVar8 = FUN_7ffe9b487ca0(auStack_190,0);
      }
      fVar24 = (float)func_0x7ffe99997964(((float)(byte)itemData[0x53] / fVar25) * _DAT_7ffe9c049ce4
                                         );
      fVar25 = _DAT_7ffe9c049cd8;
      if (fVar24 / _DAT_7ffe9c049ce4 <= _DAT_7ffe9c049cd8) {
        fVar25 = fVar24 / _DAT_7ffe9c049ce4;
      }
      uStack_150 = CONCAT44(uStack_150._4_4_,fVar25);
      uVar9 = func_0x7ffe9996c8e0(_DAT_7ffe9c949440,&uStack_150);
      uVar9 = FUN_7ffe9b36a740(_DAT_7ffe9c8f5150,uVar9,0);
      lVar7 = FUN_7ffe99ec9e00(self,0);
      if (lVar7 == 0) {
LAB_7ffe99ec96fe:
        FUN_7ffe9996d7a0();
        pcVar2 = (code *)swi(3);
        fVar25 = (float)(*pcVar2)();
        return fVar25;
      }
      uStack_178 = (undefined *)FUN_7ffe99a58320(lVar7,_DAT_7ffe9c932078,0);
      lVar7 = FUN_7ffe99ec9e00(self,0);
      uStack_198._4_4_ = *(undefined4 *)(itemData + 0x38);
      uVar10 = FUN_7ffe9b5043c0((undefined2 *)((longlong)&uStack_198 + 4),0);
      uVar10 = FUN_7ffe9b3675b0(_DAT_7ffe9c934538,uVar10,0);
      if (lVar7 == 0) goto LAB_7ffe99ec96fe;
      uVar10 = FUN_7ffe99a58320(lVar7,uVar10,0);
      uStack_168 = CONCAT62(uStack_168._2_6_,*(undefined2 *)(itemData + 0x42));
      uVar11 = func_0x7ffe9996c8e0(_DAT_7ffe9c94b8b0,&uStack_168);
      uVar8 = FUN_7ffe9b36a9f0(_DAT_7ffe9c8f9660,uVar8,uVar9,0);
      uVar8 = FUN_7ffe9b36a600(uStack_178,uVar10,uVar11,uVar8,0);
      uVar8 = FUN_7ffe9b3675b0(text,uVar8,0);
      goto LAB_7ffe99ec7d4a;
    }
    lVar7 = FUN_7ffe99ec9e00(self,0);
    if (lVar7 == 0) {
LAB_7ffe99ec96aa:
      FUN_7ffe9996d7a0();
      pcVar2 = (code *)swi(3);
      fVar25 = (float)(*pcVar2)();
      return fVar25;
    }
    uVar8 = FUN_7ffe99a58320(lVar7,_DAT_7ffe9c931fb0,0);
    lVar7 = FUN_7ffe99ec9e00(self,0);
    uStack_198._4_4_ = *(undefined4 *)(itemData + 0x38);
    uVar9 = FUN_7ffe9b5043c0((undefined2 *)((longlong)&uStack_198 + 4),0);
    uVar9 = FUN_7ffe9b3675b0(_DAT_7ffe9c934538,uVar9,0);
    if (lVar7 == 0) goto LAB_7ffe99ec96aa;
    uVar9 = FUN_7ffe99a58320(lVar7,uVar9,0);
    uStack_198._0_2_ = *(undefined2 *)(itemData + 0x42);
    uVar10 = func_0x7ffe9996c8e0(_DAT_7ffe9c94b8b0,&uStack_198);
    if (lStack_160 == 0) goto LAB_7ffe99ec96aa;
    bStack_1a8 = *(byte *)(lStack_160 + 0x40);
    uVar11 = func_0x7ffe9996c8e0(_DAT_7ffe9c94c948,&bStack_1a8);
    uVar8 = FUN_7ffe9b36a600(uVar8,uVar9,uVar10,uVar11,0);
    uVar8 = FUN_7ffe9b3675b0(text,uVar8,0);
  }
  if (*(longlong *)(itemData + 0x60) != 0) {
    bVar22 = 0 < *(int *)(*(longlong *)(itemData + 0x60) + 0x10);
  }
  if (self == (undefined *)0x0) goto LAB_7ffe99ec969e;
  uVar9 = FUN_7ffe99ec5b30(self,*(undefined4 *)(lStack_160 + 0x44),bVar22,0);
  uVar8 = FUN_7ffe9b3675b0(uVar8,uVar9);
  if ((*(longlong *)(itemData + 0x60) == 0) || (*(int *)(*(longlong *)(itemData + 0x60) + 0x10) < 1)
     ) {
    uVar9 = *(undefined8 *)(self + 0x30);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar4 = FUN_7ffe9bda2160(uVar9,0);
    if (cVar4 != '\0') {
      if (*(longlong *)(self + 0x30) == 0) goto LAB_7ffe99ec969e;
      FUN_7ffe9a404310(*(longlong *)(self + 0x30),_DAT_7ffe9c8f1820);
    }
LAB_7ffe99ec7e82:
    iVar20 = iStack_1a4;
    uVar8 = FUN_7ffe9b3675b0(uVar8,_DAT_7ffe9c8f3b08);
    if (iVar20 == 0x17) {
      uVar17 = 5;
      while (lVar7 = *(longlong *)(itemData + 0x18), lVar7 != 0) {
        puVar12 = _DAT_7ffe9c8f3b08;
        if (*(int *)(lVar7 + 0x18) <= (int)uVar17) goto LAB_7ffe99ec817b;
        if (*(uint *)(lVar7 + 0x18) <= uVar17) goto LAB_7ffe99ec96f8;
        sVar5 = *(short *)(lVar7 + 0x20 + (longlong)(int)uVar17 * 2);
        if (sVar5 != 0) {
          lVar7 = FUN_7ffe99ec9cf0(self,0);
          if (lVar7 == 0) break;
          plVar16 = (longlong *)FUN_7ffe99746fc0(_DAT_7ffe9c96b310,lVar7,(int)sVar5);
          if ((*(longlong *)(self + 0x70) == 0) ||
             (uVar9 = FUN_7ffe99a58320(*(longlong *)(self + 0x70),_DAT_7ffe9c9339b8,0),
             plVar16 == (longlong *)0x0)) break;
          uVar10 = (**(code **)(*plVar16 + 0x188))(plVar16,*(undefined8 *)(*plVar16 + 400));
          uVar9 = FUN_7ffe9b36a740(uVar9,uVar10,0);
          uVar8 = FUN_7ffe9b366c90(uVar8,_DAT_7ffe9c91f830,uVar9,_DAT_7ffe9c920640,0);
        }
        uVar17 = uVar17 + 1;
      }
      goto LAB_7ffe99ec969e;
    }
  }
  else {
    if (isPotentialZero == 0) {
      iVar20 = (int)*(short *)(itemData + 0x50);
    }
    uVar9 = *(undefined8 *)(self + 0x30);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar4 = FUN_7ffe9bda2160(uVar9,0,0);
    if (cVar4 == '\0') {
      lVar7 = FUN_7ffe99ec9e00(self,0);
      if (lVar7 == 0) {
        FUN_7ffe9996d7a0();
        pcVar2 = (code *)swi(3);
        fVar25 = (float)(*pcVar2)();
        return fVar25;
      }
      uVar9 = FUN_7ffe99a58320(lVar7,_DAT_7ffe9c9325d0,0);
      uVar10 = FUN_7ffe9b367290(_DAT_7ffe9c91ac58,*(undefined8 *)(itemData + 0x60),_DAT_7ffe9c920578
                                ,0);
      uStack_150 = CONCAT44(uStack_150._4_4_,iVar20);
      uVar11 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,&uStack_150);
      uVar9 = FUN_7ffe9b36a9f0(uVar9,uVar10,uVar11,0);
      uVar8 = FUN_7ffe9b3675b0(uVar8,uVar9);
      goto LAB_7ffe99ec7e82;
    }
    if (*(longlong *)(self + 0x28) == 0) goto LAB_7ffe99ec969e;
    FUN_7ffe9a404310(*(longlong *)(self + 0x28),uVar8,0);
    if (*(longlong *)(self + 0x28) == 0) goto LAB_7ffe99ec969e;
    uVar9 = FUN_7ffe9a403cb0(*(longlong *)(self + 0x28),0);
    if (*(int *)(_DAT_7ffe9c8ee100 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    iVar21 = FUN_7ffe99ec71b0(uVar9,0);
    uVar9 = _DAT_7ffe9c8f1820;
    if (0 < (int)(iVar21 - 1U)) {
      uVar18 = (ulonglong)(iVar21 - 1U);
      do {
        uVar9 = FUN_7ffe9b3675b0(uVar9,_DAT_7ffe9c8f3b08,0);
        uVar18 = uVar18 - 1;
      } while (uVar18 != 0);
    }
    lVar7 = *(longlong *)(self + 0x30);
    lVar13 = FUN_7ffe99ec9e00(self,0);
    if (lVar13 == 0) goto LAB_7ffe99ec969e;
    uVar10 = FUN_7ffe99a58320(lVar13,_DAT_7ffe9c932698,0);
    uVar11 = FUN_7ffe9b367290(_DAT_7ffe9c91ac58,*(undefined8 *)(itemData + 0x60),_DAT_7ffe9c920578,0
                             );
    uVar10 = FUN_7ffe9b36a740(uVar10,uVar11);
    uVar9 = FUN_7ffe9b3675b0(uVar9,uVar10);
    if (lVar7 == 0) goto LAB_7ffe99ec969e;
    FUN_7ffe9a404310(lVar7,uVar9);
    if (iStack_1a4 == 0x17) goto LAB_7ffe99ec7e82;
    lVar7 = FUN_7ffe99ec9e00(self,0);
    if (lVar7 == 0) {
      FUN_7ffe9996d7a0();
      pcVar2 = (code *)swi(3);
      fVar25 = (float)(*pcVar2)();
      return fVar25;
    }
    uVar9 = FUN_7ffe99a58320(lVar7,_DAT_7ffe9c932758,0);
    uStack_168 = CONCAT44(uStack_168._4_4_,iVar20);
    uVar10 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,&uStack_168);
    uVar9 = FUN_7ffe9b36a740(uVar9,uVar10,0);
    uVar8 = FUN_7ffe9b367290(uVar8,_DAT_7ffe9c8f3b08,uVar9,0);
    uVar8 = FUN_7ffe9b3675b0(uVar8,_DAT_7ffe9c8f3b08);
  }
  puVar12 = UIItemProperty_ItemText(self,*(int *)(itemData + 0x34),(undefined *)0x0);
LAB_7ffe99ec817b:
  uVar8 = FUN_7ffe9b3675b0(uVar8,puVar12,0);
  if (DAT_7ffe9cadbb1e == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8ee100);
    DAT_7ffe9cadbb1e = '\x01';
  }
  puVar12 = *(undefined **)(itemData + 0x10);
  iVar20 = *(int *)(self + 0x98);
  capVal = *(undefined **)(itemData + 0x18);
  itemPropertyTextManager = (undefined *)FUN_7ffe99ec99c0(self,0);
  uStack_178 = *(undefined **)(self + 0x70);
  if (*(int *)(_DAT_7ffe9c8ee100 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  puVar12 = UIItemProperty_GetItemPropertysTextData
                      (puVar12,capVal,iVar20,itemPropertyTextManager,uStack_178,(undefined *)0x0);
  uVar8 = FUN_7ffe9b3675b0(uVar8,puVar12,0);
  uStack_168 = uVar8;
  lVar7 = func_0x7ffe9996c990(_DAT_7ffe9c917f28,2);
  if (lVar7 == 0) goto LAB_7ffe99ec969e;
  if (*(int *)(lVar7 + 0x18) == 0) {
LAB_7ffe99ec96f8:
    FUN_7ffe9996d790();
    pcVar2 = (code *)swi(3);
    fVar25 = (float)(*pcVar2)();
    return fVar25;
  }
  *(undefined4 *)(lVar7 + 0x20) = *(undefined4 *)(itemData + 0x48);
  fVar25 = _DAT_7ffe9c049b88;
  if (*(uint *)(lVar7 + 0x18) < 2) goto LAB_7ffe99ec96f8;
  *(undefined4 *)(lVar7 + 0x24) = *(undefined4 *)(itemData + 0x4c);
  uVar17 = uVar23;
  do {
    if (*(longlong *)(self + 0x28) == 0) goto LAB_7ffe99ec969e;
    FUN_7ffe9a404310(*(longlong *)(self + 0x28),uVar8,0);
    if (*(longlong *)(self + 0x28) == 0) goto LAB_7ffe99ec969e;
    lVar13 = FUN_7ffe9a403cb0(*(longlong *)(self + 0x28),0);
    if (*(int *)(_DAT_7ffe9c8ee100 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    if (DAT_7ffe9cadbb1b == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c8f3b08);
      FUN_7ffe9996d590(&DAT_7ffe9c923458);
      FUN_7ffe9996d590(&DAT_7ffe9c8f1820);
      DAT_7ffe9cadbb1b = '\x01';
    }
    if (lVar13 == 0) goto LAB_7ffe99ec969e;
    lVar14 = FUN_7ffe9b36e700(lVar13,_DAT_7ffe9c8f3b08,_DAT_7ffe9c8f1820,0);
    iVar20 = *(int *)(lVar13 + 0x10);
    if (lVar14 == 0) goto LAB_7ffe99ec969e;
    iVar21 = *(int *)(lVar14 + 0x10);
    lVar13 = FUN_7ffe9b36e700(lVar14,_DAT_7ffe9c923458,_DAT_7ffe9c8f1820,0);
    if (lVar13 == 0) goto LAB_7ffe99ec969e;
    iVar1 = *(int *)(lVar13 + 0x10);
    if ((*(longlong *)(self + 0x28) == 0) ||
       (lVar13 = FUN_7ffe9bd98a10(*(longlong *)(self + 0x28),0), lVar13 == 0))
    goto LAB_7ffe99ec969e;
    puVar15 = (undefined8 *)FUN_7ffe9bdbf3e0(&uStack_118);
    puStack_188 = (undefined *)*puVar15;
    fStack_180 = *(float *)(puVar15 + 1);
    fStack_170 = fStack_180 + 0.0;
    uStack_178 = (undefined *)
                 CONCAT44((float)(((iVar21 - (iVar21 - iVar1) / 2) - iVar20) * 0x20 + -0x10) +
                          (float)((ulonglong)puStack_188 >> 0x20),SUB84(puStack_188,0) + fVar25);
    bVar3 = ItemData_get_SlotMax(itemData,(undefined *)0x0);
    if ((int)uVar17 < (int)(uint)bVar3) {
      lVar13 = *(longlong *)(self + 0x40);
      if (lVar13 == 0) goto LAB_7ffe99ec969e;
      if (*(uint *)(lVar13 + 0x18) <= uVar17) goto LAB_7ffe99ec96f8;
      lVar19 = (longlong)(int)uVar17;
      lVar14 = *(longlong *)(lVar13 + 0x20 + lVar19 * 8);
      lVar13 = lVar19 * 8 + 0x20;
      if (lVar14 == 0) goto LAB_7ffe99ec969e;
      FUN_7ffe9bd97d00(lVar14,1,0);
      if (*(uint *)(lVar7 + 0x18) <= uVar17) goto LAB_7ffe99ec96f8;
      if (*(int *)(lVar7 + 0x20 + lVar19 * 4) == 0) {
        lVar14 = *(longlong *)(self + 0x38);
        if (lVar14 == 0) goto LAB_7ffe99ec969e;
        if (*(uint *)(lVar14 + 0x18) <= uVar17) goto LAB_7ffe99ec96f8;
        if (*(longlong *)(lVar14 + lVar13) == 0) goto LAB_7ffe99ec969e;
        FUN_7ffe9bd97d00(*(longlong *)(lVar14 + lVar13),0,0);
        uVar8 = FUN_7ffe9b367290(uVar8,*(undefined8 *)(self + 0x20));
        uStack_168 = uVar8;
      }
      else {
        lVar14 = FUN_7ffe9b141840(_DAT_7ffe9c953710);
        if (*(uint *)(lVar7 + 0x18) <= uVar17) goto LAB_7ffe99ec96f8;
        if (lVar14 == 0) goto LAB_7ffe99ec969e;
        FUN_7ffe9a57a320(lVar14,*(undefined4 *)(lVar7 + 0x20 + lVar19 * 4),0);
        lVar14 = *(longlong *)(self + 0x38);
        if (lVar14 == 0) goto LAB_7ffe99ec969e;
        if (*(uint *)(lVar14 + 0x18) <= uVar17) goto LAB_7ffe99ec96f8;
        if (*(longlong *)(lVar14 + lVar13) == 0) goto LAB_7ffe99ec969e;
        FUN_7ffe9bd97d00(*(longlong *)(lVar14 + lVar13),1,0);
        lVar14 = *(longlong *)(self + 0x38);
        if (lVar14 == 0) goto LAB_7ffe99ec969e;
        if ((*(uint *)(lVar14 + 0x18) <= uVar17) ||
           (lVar14 = *(longlong *)(lVar14 + lVar13), *(uint *)(lVar7 + 0x18) <= uVar17))
        goto LAB_7ffe99ec96f8;
        uVar6 = *(undefined4 *)(lVar7 + 0x20 + lVar19 * 4);
        uStack_150 = CONCAT44(uStack_150._4_4_,uVar6);
        if (*(int *)(_DAT_7ffe9c8ede90 + 0xe0) == 0) {
          func_0x7ffe9996d830();
          uVar6 = (undefined4)uStack_150;
        }
        uVar8 = FUN_7ffe9a26c890(uVar6,0);
        if (lVar14 == 0) goto LAB_7ffe99ec969e;
        FUN_7ffe9a515470(lVar14,uVar8,0);
        uVar8 = *(undefined8 *)(self + 0x20);
        lVar14 = FUN_7ffe99ec9be0(self,0);
        if (*(uint *)(lVar7 + 0x18) <= uVar17) goto LAB_7ffe99ec96f8;
        if ((lVar14 == 0) ||
           (plVar16 = (longlong *)
                      FUN_7ffe99746fc0(_DAT_7ffe9c90af60,lVar14,
                                       *(undefined4 *)(lVar7 + 0x20 + lVar19 * 4)),
           plVar16 == (longlong *)0x0)) goto LAB_7ffe99ec969e;
        uVar9 = (**(code **)(*plVar16 + 0x188))(plVar16,*(undefined8 *)(*plVar16 + 400));
        uVar8 = FUN_7ffe9b366c90(uStack_168,uVar8,uVar9,_DAT_7ffe9c8f3b08,0);
        uStack_168 = uVar8;
      }
    }
    else {
      lVar13 = *(longlong *)(self + 0x38);
      if (lVar13 == 0) goto LAB_7ffe99ec969e;
      if (*(uint *)(lVar13 + 0x18) <= uVar17) goto LAB_7ffe99ec96f8;
      lVar14 = *(longlong *)(lVar13 + 0x20 + (longlong)(int)uVar17 * 8);
      lVar13 = (longlong)(int)uVar17 * 8 + 0x20;
      if (lVar14 == 0) goto LAB_7ffe99ec969e;
      FUN_7ffe9bd97d00(lVar14,0);
      lVar14 = *(longlong *)(self + 0x40);
      if (lVar14 == 0) goto LAB_7ffe99ec969e;
      if (*(uint *)(lVar14 + 0x18) <= uVar17) goto LAB_7ffe99ec96f8;
      if (*(longlong *)(lVar14 + lVar13) == 0) goto LAB_7ffe99ec969e;
      FUN_7ffe9bd97d00(*(longlong *)(lVar14 + lVar13),0);
    }
    lVar14 = *(longlong *)(self + 0x38);
    if (lVar14 == 0) goto LAB_7ffe99ec969e;
    if (*(uint *)(lVar14 + 0x18) <= uVar17) goto LAB_7ffe99ec96f8;
    if ((*(longlong *)(lVar14 + lVar13) == 0) ||
       (lVar14 = FUN_7ffe9bd98a10(*(longlong *)(lVar14 + lVar13),0), fVar24 = fStack_170,
       puVar12 = uStack_178, lVar14 == 0)) goto LAB_7ffe99ec969e;
    uStack_128 = uStack_178;
    fStack_120 = fStack_170;
    FUN_7ffe9bdbfcc0(lVar14,&uStack_128);
    lVar14 = *(longlong *)(self + 0x40);
    if (lVar14 == 0) goto LAB_7ffe99ec969e;
    if (*(uint *)(lVar14 + 0x18) <= uVar17) goto LAB_7ffe99ec96f8;
    if ((*(longlong *)(lVar14 + lVar13) == 0) ||
       (lVar13 = FUN_7ffe9bd98a10(*(longlong *)(lVar14 + lVar13),0), lVar13 == 0))
    goto LAB_7ffe99ec969e;
    uStack_138 = puVar12;
    fStack_130 = fVar24;
    FUN_7ffe9bdbfcc0(lVar13,&uStack_138);
    uVar17 = uVar17 + 1;
  } while ((int)uVar17 < 2);
  sVar5 = func_0x7ffe9a56fe00(itemData,0);
  if (sVar5 < 1) {
    uVar9 = *(undefined8 *)(self + 0x58);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar4 = FUN_7ffe9bda2160(uVar9,0,0);
    if (cVar4 != '\0') {
      if (*(longlong *)(self + 0x58) == 0) goto LAB_7ffe99ec969e;
      FUN_7ffe9bd97d00(*(longlong *)(self + 0x58),0,0);
    }
  }
  else {
    if (*(longlong *)(self + 0x28) == 0) goto LAB_7ffe99ec969e;
    FUN_7ffe9a404310(*(longlong *)(self + 0x28),uVar8,0);
    if (*(longlong *)(self + 0x28) == 0) goto LAB_7ffe99ec969e;
    lVar7 = FUN_7ffe9a403cb0(*(longlong *)(self + 0x28),0);
    if (*(int *)(_DAT_7ffe9c8ee100 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    if (DAT_7ffe9cadbb1b == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c8f3b08);
      FUN_7ffe9996d590(&DAT_7ffe9c923458);
      FUN_7ffe9996d590(&DAT_7ffe9c8f1820);
      DAT_7ffe9cadbb1b = '\x01';
    }
    if (lVar7 == 0) goto LAB_7ffe99ec969e;
    lVar13 = FUN_7ffe9b36e700(lVar7,_DAT_7ffe9c8f3b08,_DAT_7ffe9c8f1820,0);
    iVar20 = *(int *)(lVar7 + 0x10);
    if (lVar13 == 0) goto LAB_7ffe99ec969e;
    iVar21 = *(int *)(lVar13 + 0x10);
    lVar7 = FUN_7ffe9b36e700(lVar13,_DAT_7ffe9c923458,_DAT_7ffe9c8f1820,0);
    if (lVar7 == 0) goto LAB_7ffe99ec969e;
    iVar1 = *(int *)(lVar7 + 0x10);
    if ((*(longlong *)(self + 0x28) == 0) ||
       (lVar7 = FUN_7ffe9bd98a10(*(longlong *)(self + 0x28),0), lVar7 == 0)) goto LAB_7ffe99ec969e;
    puVar15 = (undefined8 *)FUN_7ffe9bdbf3e0(&uStack_118,lVar7);
    puStack_188 = (undefined *)*puVar15;
    fStack_180 = *(float *)(puVar15 + 1);
    fStack_170 = fStack_180 + 0.0;
    uStack_178 = (undefined *)
                 CONCAT44((float)(((iVar21 - (iVar21 - iVar1) / 2) - iVar20) * 0x20 + -0x10) +
                          (float)((ulonglong)puStack_188 >> 0x20),SUB84(puStack_188,0) + fVar25);
    uVar9 = *(undefined8 *)(self + 0x58);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar4 = FUN_7ffe9bda1fa0(uVar9,0);
    if (cVar4 != '\0') {
      (**(code **)(*(longlong *)self + 0x1d8))(self,*(undefined8 *)(*(longlong *)self + 0x1e0));
    }
    uVar9 = *(undefined8 *)(self + 0x58);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar4 = FUN_7ffe9bda2160(uVar9,0);
    if (cVar4 != '\0') {
      if (*(longlong *)(self + 0x58) == 0) goto LAB_7ffe99ec969e;
      FUN_7ffe9bd97d00(*(longlong *)(self + 0x58),1,0);
      if ((*(longlong *)(self + 0x58) == 0) ||
         (lVar7 = FUN_7ffe9bd98a10(*(longlong *)(self + 0x58),0), lVar7 == 0))
      goto LAB_7ffe99ec969e;
      fStack_180 = fStack_170;
      puStack_188 = uStack_178;
      FUN_7ffe9bdbfcc0(lVar7,&puStack_188,0);
      plVar16 = *(longlong **)(self + 0x58);
      if (*(int *)(_DAT_7ffe9c8ede90 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      puVar15 = (undefined8 *)FUN_7ffe9a26c9a0(&uStack_b8,sVar5,0);
      if (plVar16 == (longlong *)0x0) goto LAB_7ffe99ec969e;
      uStack_c8 = *puVar15;
      uStack_c0 = puVar15[1];
      (**(code **)(*plVar16 + 0x1d8))(plVar16,&uStack_c8);
    }
    if (DAT_7ffe9cadbb19 == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c94fa88);
      FUN_7ffe9996d590(&DAT_7ffe9c953578);
      DAT_7ffe9cadbb19 = '\x01';
    }
    if (*(longlong *)(self + 0x90) == 0) {
      puVar12 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c953578);
      if (puVar12 == (undefined *)0x0) goto LAB_7ffe99ec969e;
      plVar16 = (longlong *)LocalizeManager_Get(puVar12,(undefined *)0xe,(undefined *)0x0);
      if (plVar16 == (longlong *)0x0) {
        *(undefined8 *)(self + 0x90) = 0;
      }
      else {
        if ((*(byte *)(*plVar16 + 0x130) < *(byte *)(_DAT_7ffe9c94fa88 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar16 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c94fa88 + 0x130) * 8) != _DAT_7ffe9c94fa88)) {
          FUN_7ffe9996c950(plVar16);
          pcVar2 = (code *)swi(3);
          fVar25 = (float)(*pcVar2)();
          return fVar25;
        }
        *(longlong **)(self + 0x90) = plVar16;
        if ((*(byte *)(*plVar16 + 0x130) < *(byte *)(_DAT_7ffe9c94fa88 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar16 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c94fa88 + 0x130) * 8) != _DAT_7ffe9c94fa88)) {
          FUN_7ffe9996c950(plVar16);
          pcVar2 = (code *)swi(3);
          fVar25 = (float)(*pcVar2)();
          return fVar25;
        }
      }
      il2cpp_write_barrier_0();
    }
    plVar16 = *(longlong **)(self + 0x90);
    if (plVar16 == (longlong *)0x0) goto LAB_7ffe99ec969e;
    lVar7 = func_0x7ffe9996d210(*(undefined8 *)
                                 (*plVar16 +
                                 ((ulonglong)*(ushort *)(_DAT_7ffe9c90a8e0 + 0x50) + 0x14) * 0x10));
    plVar16 = (longlong *)(**(code **)(lVar7 + 8))(plVar16,(int)sVar5,lVar7);
    uVar9 = *(undefined8 *)(self + 0x20);
    if (plVar16 == (longlong *)0x0) goto LAB_7ffe99ec969e;
    uVar10 = (**(code **)(*plVar16 + 0x188))(plVar16,*(undefined8 *)(*plVar16 + 400));
    uVar8 = FUN_7ffe9b366c90(uVar8,uVar9,uVar10,_DAT_7ffe9c8f3b08,0);
  }
  uVar8 = FUN_7ffe9b3675b0(uVar8,_DAT_7ffe9c8f3b08,0);
  if (iStack_1a4 != 0x17) {
    lVar7 = FUN_7ffe99ec9e00(self,0);
    if (abStack_1a7[0] == 0) {
      if (lVar7 == 0) {
        FUN_7ffe9996d7a0();
        pcVar2 = (code *)swi(3);
        fVar25 = (float)(*pcVar2)();
        return fVar25;
      }
      uVar9 = FUN_7ffe99a58320(lVar7,_DAT_7ffe9c9328e0,0);
      puVar15 = &uStack_168;
      uStack_168 = CONCAT62(uStack_168._2_6_,*(undefined2 *)(lStack_160 + 0x3e));
    }
    else {
      if (lVar7 == 0) {
        FUN_7ffe9996d7a0();
        pcVar2 = (code *)swi(3);
        fVar25 = (float)(*pcVar2)();
        return fVar25;
      }
      uVar9 = FUN_7ffe99a58320(lVar7,_DAT_7ffe9c932820,0);
      puVar15 = &uStack_198;
      uStack_198._0_2_ = *(undefined2 *)(lStack_160 + 0x3e);
    }
    uVar10 = func_0x7ffe9996c8e0(_DAT_7ffe9c94b8b0,puVar15);
    uVar9 = FUN_7ffe9b36a740(uVar9,uVar10,0);
    uVar8 = FUN_7ffe9b3675b0(uVar8,uVar9,0);
  }
  if (*(int *)(itemData + 0x38) - 0x12U < 2) {
    lVar7 = FUN_7ffe99ec9e00(self,0);
    if (lVar7 == 0) goto LAB_7ffe99ec969e;
    uVar9 = FUN_7ffe99a58320(lVar7,_DAT_7ffe9c9335e8,0);
    lVar7 = FUN_7ffe99ec9e00(self,0);
    uVar10 = _DAT_7ffe9c933150;
joined_r0x7ffe99ec8cc1:
    if (lVar7 == 0) goto LAB_7ffe99ec969e;
    uVar10 = FUN_7ffe99a58320(lVar7,uVar10,0);
    uVar9 = FUN_7ffe9b36a740(uVar9,uVar10,0);
LAB_7ffe99ec8ce7:
    uVar8 = FUN_7ffe9b3675b0(uVar8,uVar9,0);
  }
  else {
    if (*(int *)(itemData + 0x38) == 0x16) {
      lVar7 = FUN_7ffe99ec9e00(self,0);
      if (lVar7 == 0) goto LAB_7ffe99ec969e;
      uVar9 = FUN_7ffe99a58320(lVar7,_DAT_7ffe9c9335e8,0);
      lVar7 = FUN_7ffe99ec9e00(self,0);
      uVar10 = _DAT_7ffe9c933210;
      goto joined_r0x7ffe99ec8cc1;
    }
    if (iStack_1a4 != 0x17) {
      lVar7 = FUN_7ffe99ec9e00(self,0);
      if (lVar7 == 0) {
        FUN_7ffe9996d7a0();
        pcVar2 = (code *)swi(3);
        fVar25 = (float)(*pcVar2)();
        return fVar25;
      }
      uVar9 = FUN_7ffe99a58320(lVar7,_DAT_7ffe9c9336a8,0);
      uVar10 = FUN_7ffe9a56f730(itemData,0);
      auStack_19c[0] = func_0x7ffe9a56fde0(itemData,0);
      uVar11 = func_0x7ffe9996c8e0(_DAT_7ffe9c94b8b0,auStack_19c);
      uVar9 = FUN_7ffe9b36a9f0(uVar9,uVar10,uVar11,0);
      goto LAB_7ffe99ec8ce7;
    }
  }
  if (*(int *)(itemData + 0x38) - 0x11U < 3) {
    lVar7 = FUN_7ffe99ec9e00(self,0);
    if (lVar7 == 0) goto LAB_7ffe99ec969e;
    uVar9 = FUN_7ffe99a58320(lVar7,_DAT_7ffe9c933a80,0);
    lVar7 = FUN_7ffe99ec9e00(self,0);
    if (lVar7 == 0) goto LAB_7ffe99ec969e;
    uVar10 = FUN_7ffe99a58320(lVar7,_DAT_7ffe9c9332d8,0);
LAB_7ffe99ec8e6f:
    uVar9 = FUN_7ffe9b36a740(uVar9,uVar10,0);
LAB_7ffe99ec8e7d:
    uVar8 = FUN_7ffe9b3675b0(uVar8,uVar9,0);
  }
  else if (iStack_1a4 != 0x17) {
    if ((*(int *)(itemData + 0x38) != 0x14) || ((byte)itemData[0x53] < 4)) {
      lVar7 = FUN_7ffe99ec9e00(self,0);
      if (lVar7 == 0) {
        FUN_7ffe9996d7a0();
        pcVar2 = (code *)swi(3);
        fVar25 = (float)(*pcVar2)();
        return fVar25;
      }
      uVar9 = FUN_7ffe99a58320(lVar7,_DAT_7ffe9c933a80,0);
      bStack_1a8 = ItemData_get_SlotMax(itemData,(undefined *)0x0);
      uVar10 = func_0x7ffe9996c8e0(_DAT_7ffe9c94c948,&bStack_1a8);
      goto LAB_7ffe99ec8e6f;
    }
    lVar7 = FUN_7ffe99ec9e00(self,0);
    if (lVar7 == 0) {
LAB_7ffe99ec96e0:
      FUN_7ffe9996d7a0();
      pcVar2 = (code *)swi(3);
      fVar25 = (float)(*pcVar2)();
      return fVar25;
    }
    uVar9 = FUN_7ffe99a58320(lVar7,_DAT_7ffe9c933b40,0);
    abStack_1a7[0] = ItemData_get_SlotMax(itemData,(undefined *)0x0);
    uVar10 = func_0x7ffe9996c8e0(_DAT_7ffe9c94c948,abStack_1a7);
    lVar7 = FUN_7ffe99ec9e00(self,0);
    auStack_1a0[0] = FUN_7ffe9a56f340(itemData,0);
    uVar11 = FUN_7ffe9b485060(auStack_1a0,0);
    uVar11 = FUN_7ffe9b3675b0(_DAT_7ffe9c933c08,uVar11,0);
    if (lVar7 == 0) goto LAB_7ffe99ec96e0;
    uVar11 = FUN_7ffe99a58320(lVar7,uVar11,0);
    uVar9 = FUN_7ffe9b36a9f0(uVar9,uVar10,uVar11,0);
    goto LAB_7ffe99ec8e7d;
  }
  if (*(longlong *)(self + 0x28) == 0) {
LAB_7ffe99ec969e:
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    fVar25 = (float)(*pcVar2)();
    return fVar25;
  }
  FUN_7ffe9a404310(*(longlong *)(self + 0x28),uVar8,0);
  if (*(longlong *)(self + 0x28) == 0) goto LAB_7ffe99ec96f2;
  lVar7 = FUN_7ffe9a403cb0(*(longlong *)(self + 0x28),0);
  if (*(int *)(_DAT_7ffe9c8ee100 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  if (DAT_7ffe9cadbb1b == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f3b08);
    FUN_7ffe9996d590(&DAT_7ffe9c923458);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1820);
    DAT_7ffe9cadbb1b = '\x01';
  }
  if (lVar7 == 0) goto LAB_7ffe99ec96f2;
  lVar13 = FUN_7ffe9b36e700(lVar7,_DAT_7ffe9c8f3b08,_DAT_7ffe9c8f1820,0);
  iVar20 = *(int *)(lVar7 + 0x10);
  if (lVar13 == 0) goto LAB_7ffe99ec96f2;
  iVar21 = *(int *)(lVar13 + 0x10);
  lVar7 = FUN_7ffe9b36e700(lVar13,_DAT_7ffe9c923458,_DAT_7ffe9c8f1820,0);
  if (lVar7 == 0) goto LAB_7ffe99ec96f2;
  iVar20 = (iVar20 + ((iVar21 - *(int *)(lVar7 + 0x10)) / 2 - iVar21)) * 0x20;
  iVar21 = iVar20 + 0x30;
  if (*(longlong *)(self + 0x28) == 0) goto LAB_7ffe99ec96f2;
  lVar7 = FUN_7ffe9bd98a10(*(longlong *)(self + 0x28),0);
  if (DAT_7ffe9cad9b4e == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
    DAT_7ffe9cad9b4e = '\x01';
  }
  if (lVar7 == 0) goto LAB_7ffe99ec96f2;
  puStack_188 = *(undefined **)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0xc);
  fStack_180 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x14);
  FUN_7ffe9bdbfe00(lVar7,&puStack_188);
  if (*(longlong *)(self + 0x70) == 0) goto LAB_7ffe99ec96f2;
  uVar9 = FUN_7ffe99a58320(*(longlong *)(self + 0x70),_DAT_7ffe9c932388);
  if (*(longlong *)(self + 0x70) == 0) goto LAB_7ffe99ec96f2;
  uStack_150 = FUN_7ffe99a58320(*(longlong *)(self + 0x70),_DAT_7ffe9c932448);
  if (*(longlong *)(self + 0x70) == 0) goto LAB_7ffe99ec96f2;
  uStack_178 = (undefined *)FUN_7ffe99a58320(*(longlong *)(self + 0x70),_DAT_7ffe9c932510);
  lVar7 = FUN_7ffe9b3675b0(_DAT_7ffe9c8f3b08,uVar9);
  lStack_160 = lVar7;
  lVar13 = func_0x7ffe9996c990(_DAT_7ffe9c9118d0,3);
  if (lVar13 == 0) goto LAB_7ffe99ec96f2;
  if (*(int *)(lVar13 + 0x18) == 0) {
LAB_7ffe99ec96ec:
    FUN_7ffe9996d790();
    pcVar2 = (code *)swi(3);
    fVar25 = (float)(*pcVar2)();
    return fVar25;
  }
  *(undefined *)(lVar13 + 0x20) = itemData[0x58];
  if (*(uint *)(lVar13 + 0x18) < 2) goto LAB_7ffe99ec96ec;
  *(undefined *)(lVar13 + 0x21) = itemData[0x59];
  fVar24 = _DAT_7ffe9c04a2c8;
  fVar25 = _DAT_7ffe9c049e64;
  if (*(uint *)(lVar13 + 0x18) < 3) goto LAB_7ffe99ec96ec;
  *(undefined *)(lVar13 + 0x22) = itemData[0x5a];
  do {
    if (iStack_1a4 == 0x17) {
      if (*(uint *)(lVar13 + 0x18) <= uVar23) goto LAB_7ffe99ec96ec;
      *(undefined1 *)((longlong)(int)uVar23 + 0x20 + lVar13) = 0;
    }
    if (*(uint *)(lVar13 + 0x18) <= uVar23) goto LAB_7ffe99ec96ec;
    lVar14 = *(longlong *)(self + 0x48);
    lVar19 = (longlong)(int)uVar23;
    if (*(char *)(lVar13 + 0x20 + lVar19) == '\0') {
      if (lVar14 == 0) goto LAB_7ffe99ec96f2;
      if (*(uint *)(lVar14 + 0x18) <= uVar23) goto LAB_7ffe99ec96ec;
      lVar14 = *(longlong *)(lVar14 + 0x20 + lVar19 * 8);
      if (lVar14 == 0) goto LAB_7ffe99ec96f2;
      FUN_7ffe9bd97d00(lVar14,0);
      lVar14 = *(longlong *)(self + 0x50);
      if (lVar14 == 0) goto LAB_7ffe99ec96f2;
      if (*(uint *)(lVar14 + 0x18) <= uVar23) goto LAB_7ffe99ec96ec;
      lVar14 = *(longlong *)(lVar14 + 0x20 + lVar19 * 8);
      if (lVar14 == 0) goto LAB_7ffe99ec96f2;
      FUN_7ffe9bd97d00(lVar14,0);
      puVar12 = uStack_178;
    }
    else {
      if (lVar14 == 0) goto LAB_7ffe99ec96f2;
      if (*(uint *)(lVar14 + 0x18) <= uVar23) goto LAB_7ffe99ec96ec;
      lVar7 = *(longlong *)(lVar14 + 0x20 + lVar19 * 8);
      if (lVar7 == 0) goto LAB_7ffe99ec96f2;
      FUN_7ffe9bd97d00(lVar7,1,0);
      lVar7 = *(longlong *)(self + 0x48);
      if (lVar7 == 0) goto LAB_7ffe99ec96f2;
      if (*(uint *)(lVar7 + 0x18) <= uVar23) goto LAB_7ffe99ec96ec;
      lVar7 = *(longlong *)(lVar7 + 0x20 + lVar19 * 8);
      if (lVar7 == 0) goto LAB_7ffe99ec96f2;
      lVar7 = FUN_7ffe9bd98a10(lVar7,0);
      if ((*(longlong *)(self + 0x28) == 0) ||
         (lVar14 = FUN_7ffe9bd98a10(*(longlong *)(self + 0x28),0), lVar14 == 0))
      goto LAB_7ffe99ec96f2;
      puVar15 = (undefined8 *)FUN_7ffe9bdbf3e0(auStack_a8,lVar14,0);
      fStack_100 = *(float *)(puVar15 + 1);
      fStack_130 = fStack_100 + 0.0;
      uStack_138 = (undefined *)
                   CONCAT44((float)-iVar21 + (float)((ulonglong)*puVar15 >> 0x20),
                            (float)(int)uVar23 * fVar24 + fVar25 + (float)*puVar15);
      if (lVar7 == 0) goto LAB_7ffe99ec96f2;
      puStack_f8 = uStack_138;
      fStack_f0 = fStack_130;
      FUN_7ffe9bdbfcc0(lVar7,&puStack_f8,0);
      lVar7 = *(longlong *)(self + 0x50);
      if (lVar7 == 0) goto LAB_7ffe99ec96f2;
      if (*(uint *)(lVar7 + 0x18) <= uVar23) goto LAB_7ffe99ec96ec;
      lVar7 = *(longlong *)(lVar7 + 0x20 + lVar19 * 8);
      if (lVar7 == 0) goto LAB_7ffe99ec96f2;
      FUN_7ffe9bd97d00(lVar7,1,0);
      lVar7 = *(longlong *)(self + 0x50);
      if (lVar7 == 0) goto LAB_7ffe99ec96f2;
      if (*(uint *)(lVar7 + 0x18) <= uVar23) goto LAB_7ffe99ec96ec;
      plVar16 = *(longlong **)(lVar7 + 0x20 + lVar19 * 8);
      lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c9538a8);
      if (*(uint *)(lVar13 + 0x18) <= uVar23) goto LAB_7ffe99ec96ec;
      if ((lVar7 == 0) ||
         (puVar15 = (undefined8 *)
                    FUN_7ffe9a57bc00(auStack_98,lVar7,*(undefined1 *)(lVar13 + 0x20 + lVar19),0),
         plVar16 == (longlong *)0x0)) goto LAB_7ffe99ec96f2;
      uStack_b8 = *puVar15;
      uStack_b0 = puVar15[1];
      (**(code **)(*plVar16 + 0x1d8))(plVar16,&uStack_b8);
      lVar7 = *(longlong *)(self + 0x50);
      if (lVar7 == 0) goto LAB_7ffe99ec96f2;
      if (*(uint *)(lVar7 + 0x18) <= uVar23) goto LAB_7ffe99ec96ec;
      lVar7 = *(longlong *)(lVar7 + 0x20 + lVar19 * 8);
      if (lVar7 == 0) goto LAB_7ffe99ec96f2;
      lVar14 = FUN_7ffe9bd98a10(lVar7,0);
      lVar7 = *(longlong *)(self + 0x48);
      if (lVar7 == 0) goto LAB_7ffe99ec96f2;
      if (*(uint *)(lVar7 + 0x18) <= uVar23) goto LAB_7ffe99ec96ec;
      lVar7 = *(longlong *)(lVar7 + 0x20 + lVar19 * 8);
      if ((lVar7 == 0) || (lVar7 = FUN_7ffe9bd98a10(lVar7,0), lVar7 == 0)) goto LAB_7ffe99ec96f2;
      puVar15 = (undefined8 *)FUN_7ffe9bdbf3e0(&uStack_c8,lVar7);
      fStack_e0 = *(float *)(puVar15 + 1);
      fStack_120 = fStack_e0 + 0.0;
      uStack_128 = (undefined *)
                   CONCAT44((float)((ulonglong)*puVar15 >> 0x20) + 0.0,(float)*puVar15 + fVar25);
      if (lVar14 == 0) goto LAB_7ffe99ec96f2;
      puStack_d8 = uStack_128;
      fStack_d0 = fStack_120;
      FUN_7ffe9bdbfcc0(lVar14,&puStack_d8);
      lVar7 = *(longlong *)(self + 0x50);
      if (lVar7 == 0) goto LAB_7ffe99ec96f2;
      if (*(uint *)(lVar7 + 0x18) <= uVar23) goto LAB_7ffe99ec96ec;
      lVar7 = *(longlong *)(lVar7 + 0x20 + lVar19 * 8);
      if (lVar7 == 0) goto LAB_7ffe99ec96f2;
      lVar7 = FUN_7ffe9bd98a10(lVar7,0);
      puStack_188 = (undefined *)0x3f80000040000000;
      fStack_180 = 1.0;
      if (lVar7 == 0) goto LAB_7ffe99ec96f2;
      uStack_110 = 0x3f800000;
      uStack_118 = 0x3f80000040000000;
      FUN_7ffe9bdbfe00(lVar7,&uStack_118);
      if (*(uint *)(lVar13 + 0x18) <= uVar23) goto LAB_7ffe99ec96ec;
      aiStack_158[0] = *(byte *)(lVar13 + 0x20 + lVar19) - 10;
      lVar7 = lStack_160;
      if (aiStack_158[0] < 100) {
        lVar7 = FUN_7ffe9b3675b0(lStack_160,_DAT_7ffe9c8f7318);
      }
      if (aiStack_158[0] < 10) {
        lVar7 = FUN_7ffe9b3675b0(lVar7,_DAT_7ffe9c8f7318);
      }
      puVar12 = (undefined *)FUN_7ffe9b5043c0(aiStack_158,0);
    }
    uVar9 = FUN_7ffe9b3675b0(lVar7,puVar12);
    lVar7 = FUN_7ffe9b3675b0(uVar9);
    uVar23 = uVar23 + 1;
    lStack_160 = lVar7;
  } while ((int)uVar23 < 3);
  uVar23 = *(uint *)(lVar13 + 0x18);
  if (uVar23 == 0) goto LAB_7ffe99ec96ec;
  if (*(char *)(lVar13 + 0x20) == '\0') {
    if (uVar23 < 2) goto LAB_7ffe99ec96ec;
    if (*(char *)(lVar13 + 0x21) != '\0') goto LAB_7ffe99ec9511;
    if (uVar23 < 3) goto LAB_7ffe99ec96ec;
    if (*(char *)(lVar13 + 0x22) != '\0') goto LAB_7ffe99ec9511;
  }
  else {
LAB_7ffe99ec9511:
    iVar21 = iVar20 + 0x58;
    uVar8 = FUN_7ffe9b367290(uVar8,lVar7,_DAT_7ffe9c8f3bd8,0);
  }
  uStack_198._4_4_ = *(undefined4 *)(itemData + 0x38);
  switch(uStack_198._4_4_) {
  case 9:
  case 0xb:
  case 0x11:
code_r0x7ffe99ec95c4:
    lVar7 = *(longlong *)(self + 0x70);
    uVar9 = uRam00007ffe9c932bf0;
    break;
  case 10:
    lVar7 = *(longlong *)(self + 0x70);
    uVar9 = uRam00007ffe9c932b30;
    break;
  default:
    goto LAB_7ffe99ec95f5;
  case 0xf:
  case 0x12:
code_r0x7ffe99ec95ae:
    lVar7 = *(longlong *)(self + 0x70);
    uVar9 = uRam00007ffe9c932200;
    break;
  case 0x10:
    lVar7 = *(longlong *)(self + 0x70);
    uVar9 = uRam00007ffe9c932cb8;
    break;
  case 0x14:
    bVar3 = ItemDBData_CheckArmorAbility(itemData,(undefined *)0x2,(undefined *)0x0);
    if (bVar3 != 0) goto code_r0x7ffe99ec95c4;
    bVar3 = ItemDBData_CheckArmorAbility(itemData,(undefined *)0x1,(undefined *)0x0);
    if (bVar3 != 0) goto code_r0x7ffe99ec95ae;
    goto LAB_7ffe99ec95f5;
  }
  if (lVar7 != 0) {
    uVar9 = FUN_7ffe99a58320(lVar7,uVar9,0);
    uVar8 = FUN_7ffe9b3675b0(uVar8,uVar9,0);
    iVar21 = iVar21 + 0x20;
LAB_7ffe99ec95f5:
    if (iStack_1a4 == 0x17) {
      if (*(longlong *)(self + 0x70) == 0) goto LAB_7ffe99ec96f2;
      uVar9 = FUN_7ffe99a58320(*(longlong *)(self + 0x70),_DAT_7ffe9c933088,0);
      uVar8 = FUN_7ffe9b3675b0(uVar8,uVar9,0);
      iVar21 = iVar21 + 0x20;
    }
    if (*(longlong *)(self + 0x28) != 0) {
      FUN_7ffe9a404310(*(longlong *)(self + 0x28),uVar8,0);
      return (float)iVar21;
    }
  }
LAB_7ffe99ec96f2:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  fVar25 = (float)(*pcVar2)();
  return fVar25;
}

