
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
  undefined *puVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
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
  bool creater;
  uint uVar22;
  float fVar23;
  float fVar24;
  byte bStack_1a8;
  byte bStack_1a7;
  int iStack_1a4;
  byte abStack_1a0 [4];
  short asStack_19c [2];
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
  
  if (DAT_7fff625e329d == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62419460);
    FUN_7fff5f47d450(&DAT_7fff62454290);
    FUN_7fff5f47d450(&DAT_7fff6245c4e0);
    FUN_7fff5f47d450(&DAT_7fff62453138);
    FUN_7fff5f47d450(&DAT_7fff6241fab8);
    FUN_7fff5f47d450(&DAT_7fff624532c0);
    FUN_7fff5f47d450(&DAT_7fff62411840);
    FUN_7fff5f47d450(&DAT_7fff62411ec0);
    FUN_7fff5f47d450(&DAT_7fff6240e4b0);
    FUN_7fff5f47d450(&DAT_7fff62450b30);
    FUN_7fff5f47d450(&DAT_7fff6245a5f8);
    FUN_7fff5f47d450(&DAT_7fff6245a790);
    FUN_7fff5f47d450(&DAT_7fff62472120);
    FUN_7fff5f47d450(&DAT_7fff623f5540);
    FUN_7fff5f47d450(&DAT_7fff623f57b0);
    FUN_7fff5f47d450(&DAT_7fff623fa248);
    FUN_7fff5f47d450(&DAT_7fff6243a168);
    FUN_7fff5f47d450(&DAT_7fff62439838);
    FUN_7fff5f47d450(&DAT_7fff6243a228);
    FUN_7fff5f47d450(&DAT_7fff62439d90);
    FUN_7fff5f47d450(&DAT_7fff62438760);
    FUN_7fff5f47d450(&DAT_7fff623fda58);
    FUN_7fff5f47d450(&DAT_7fff62426490);
    FUN_7fff5f47d450(&DAT_7fff62420aa8);
    FUN_7fff5f47d450(0x7fff624392d8);
    FUN_7fff5f47d450(&DAT_7fff6243a2f0);
    FUN_7fff5f47d450(0x7fff62439218);
    FUN_7fff5f47d450(&DAT_7fff6243a0a0);
    FUN_7fff5f47d450(&DAT_7fff62438bf8);
    FUN_7fff5f47d450(&DAT_7fff62438e40);
    FUN_7fff5f47d450(&DAT_7fff62425680);
    FUN_7fff5f47d450(&DAT_7fff62439cd0);
    FUN_7fff5f47d450(&DAT_7fff62439770);
    FUN_7fff5f47d450(&DAT_7fff62438b30);
    FUN_7fff5f47d450(&DAT_7fff62438cb8);
    FUN_7fff5f47d450(&DAT_7fff623ff4b0);
    FUN_7fff5f47d450(&DAT_7fff62438d80);
    FUN_7fff5f47d450(&DAT_7fff624398f8);
    FUN_7fff5f47d450(0x7fff624388e8);
    FUN_7fff5f47d450(&DAT_7fff6243ac20);
    FUN_7fff5f47d450(&DAT_7fff62438a70);
    FUN_7fff5f47d450(&DAT_7fff624399c0);
    FUN_7fff5f47d450(&DAT_7fff623fa318);
    FUN_7fff5f47d450(&DAT_7fff623fafa0);
    FUN_7fff5f47d450(&DAT_7fff6241d2d0);
    FUN_7fff5f47d450(&DAT_7fff623f7f60);
    FUN_7fff5f47d450(0x7fff624393a0);
    FUN_7fff5f47d450(&DAT_7fff62438698);
    FUN_7fff5f47d450(&DAT_7fff624263c8);
    FUN_7fff5f47d450(&DAT_7fff62438fc8);
    FUN_7fff5f47d450(&DAT_7fff62438f08);
    FUN_7fff5f47d450(&DAT_7fff62426400);
    FUN_7fff5f47d450(&DAT_7fff62439150);
    DAT_7fff625e329d = '\x01';
  }
  uVar22 = 0;
  iVar20 = 0;
  aiStack_148[0] = 0;
  auStack_190[0] = 0;
  creater = false;
  abStack_1a0[0] = 0;
  aiStack_158[0] = 0;
  if (itemData == (undefined *)0x0) goto LAB_7fff5f9d8cee;
  bVar3 = ItemDBData_CheckEquipItem(*(int *)(itemData + 0x38),(undefined *)0x0);
  if (bVar3 == 0) {
    return 0.0;
  }
  lVar7 = FUN_7fff60c4bc00(_DAT_7fff6245a5f8);
  if (lVar7 == 0) goto LAB_7fff5f9d8cee;
  lStack_160 = FUN_7fff600847d0(lVar7,*(undefined4 *)(itemData + 0x34),0);
  bStack_1a7 = func_0x7fff5fd83130(*(undefined4 *)(itemData + 0x38));
  fVar24 = _DAT_7fff61b52cfc;
  iStack_1a4 = *(int *)(itemData + 0x38);
  if (bStack_1a7 == 0) {
    puVar8 = UIItemProperty_get_systemTextManager(self,(undefined *)0x0);
    if (puVar8 == (undefined *)0x0) {
LAB_7fff5f9d8cf4:
      FUN_7fff5f47d660();
      pcVar2 = (code *)swi(3);
      fVar24 = (float)(*pcVar2)();
      return fVar24;
    }
    uVar9 = FUN_7fff5f568150(puVar8,_DAT_7fff62439150,0);
    puVar8 = UIItemProperty_get_systemTextManager(self,(undefined *)0x0);
    uStack_198._4_4_ = *(undefined4 *)(itemData + 0x38);
    uVar10 = FUN_7fff6100e780((undefined2 *)((longlong)&uStack_198 + 4),0);
    uVar10 = FUN_7fff60e71970(_DAT_7fff6243ac20,uVar10,0);
    if (puVar8 == (undefined *)0x0) goto LAB_7fff5f9d8cf4;
    uVar10 = FUN_7fff5f568150(puVar8,uVar10,0);
    asStack_19c[0] = *(short *)(itemData + 0x42);
    uVar11 = func_0x7fff5f47c7a0(_DAT_7fff62453138,asStack_19c);
    uVar9 = FUN_7fff60e74db0(uVar9,uVar10,uVar11);
    uVar9 = FUN_7fff60e71970(text,uVar9,0);
LAB_7fff5f9d739a:
    if (lStack_160 == 0) goto LAB_7fff5f9d8cee;
  }
  else {
    if (iStack_1a4 == 0x17) {
      aiStack_148[0] =
           ((int)(((float)(byte)itemData[0x58] / _DAT_7fff61b52dd0) * _DAT_7fff61b52cfc) / 100) *
           100;
      uVar9 = _DAT_7fff62426400;
      if (99 < aiStack_148[0]) {
        lVar7 = FUN_7fff6100e780(aiStack_148,0);
        if (lVar7 == 0) goto LAB_7fff5f9d8cee;
        auStack_190[0] = FUN_7fff60e7b760(lVar7,*(int *)(lVar7 + 0x10) + -3,0);
        if (*(int *)(_DAT_7fff6245c4e0 + 0xe0) == 0) {
          func_0x7fff5f47d6f0();
        }
        uVar9 = FUN_7fff60f92060(auStack_190,0);
      }
      fVar23 = (float)func_0x7fff5f4a7824(((float)(byte)itemData[0x53] / fVar24) * _DAT_7fff61b52ce4
                                         );
      fVar24 = _DAT_7fff61b52cd8;
      if (fVar23 / _DAT_7fff61b52ce4 <= _DAT_7fff61b52cd8) {
        fVar24 = fVar23 / _DAT_7fff61b52ce4;
      }
      uStack_150 = CONCAT44(uStack_150._4_4_,fVar24);
      uVar10 = func_0x7fff5f47c7a0(_DAT_7fff62450b30,&uStack_150);
      uVar10 = FUN_7fff60e74b00(_DAT_7fff623fafa0,uVar10,0);
      puVar8 = UIItemProperty_get_systemTextManager(self,(undefined *)0x0);
      if (puVar8 == (undefined *)0x0) {
LAB_7fff5f9d8d4e:
        FUN_7fff5f47d660();
        pcVar2 = (code *)swi(3);
        fVar24 = (float)(*pcVar2)();
        return fVar24;
      }
      uStack_178 = (undefined *)FUN_7fff5f568150(puVar8,_DAT_7fff62438760,0);
      puVar8 = UIItemProperty_get_systemTextManager(self,(undefined *)0x0);
      uStack_198._4_4_ = *(undefined4 *)(itemData + 0x38);
      uVar11 = FUN_7fff6100e780((undefined2 *)((longlong)&uStack_198 + 4),0);
      uVar11 = FUN_7fff60e71970(_DAT_7fff6243ac20,uVar11,0);
      if (puVar8 == (undefined *)0x0) goto LAB_7fff5f9d8d4e;
      uVar11 = FUN_7fff5f568150(puVar8,uVar11,0);
      uStack_168 = CONCAT62(uStack_168._2_6_,*(undefined2 *)(itemData + 0x42));
      uVar12 = func_0x7fff5f47c7a0(_DAT_7fff62453138,&uStack_168);
      uVar9 = FUN_7fff60e74db0(_DAT_7fff623ff4b0,uVar9,uVar10,0);
      uVar9 = FUN_7fff60e749c0(uStack_178,uVar11,uVar12,uVar9,0);
      uVar9 = FUN_7fff60e71970(text,uVar9,0);
      goto LAB_7fff5f9d739a;
    }
    puVar8 = UIItemProperty_get_systemTextManager(self,(undefined *)0x0);
    if (puVar8 == (undefined *)0x0) {
LAB_7fff5f9d8cfa:
      FUN_7fff5f47d660();
      pcVar2 = (code *)swi(3);
      fVar24 = (float)(*pcVar2)();
      return fVar24;
    }
    uVar9 = FUN_7fff5f568150(puVar8,_DAT_7fff62438698,0);
    puVar8 = UIItemProperty_get_systemTextManager(self,(undefined *)0x0);
    uStack_198._4_4_ = *(undefined4 *)(itemData + 0x38);
    uVar10 = FUN_7fff6100e780((undefined2 *)((longlong)&uStack_198 + 4),0);
    uVar10 = FUN_7fff60e71970(_DAT_7fff6243ac20,uVar10,0);
    if (puVar8 == (undefined *)0x0) goto LAB_7fff5f9d8cfa;
    uVar10 = FUN_7fff5f568150(puVar8,uVar10,0);
    uStack_198._0_2_ = *(undefined2 *)(itemData + 0x42);
    uVar11 = func_0x7fff5f47c7a0(_DAT_7fff62453138,&uStack_198);
    if (lStack_160 == 0) goto LAB_7fff5f9d8cfa;
    bStack_1a8 = *(byte *)(lStack_160 + 0x40);
    uVar12 = func_0x7fff5f47c7a0(_DAT_7fff62454290,&bStack_1a8);
    uVar9 = FUN_7fff60e749c0(uVar9,uVar10,uVar11,uVar12,0);
    uVar9 = FUN_7fff60e71970(text,uVar9,0);
  }
  if (*(longlong *)(itemData + 0x60) != 0) {
    creater = 0 < *(int *)(*(longlong *)(itemData + 0x60) + 0x10);
  }
  if (self == (undefined *)0x0) goto LAB_7fff5f9d8cee;
  UIItemProperty_ItemLockPropertys(self,*(int *)(lStack_160 + 0x44),creater,(undefined *)0x0);
  uVar9 = FUN_7fff60e71970(uVar9);
  if ((*(longlong *)(itemData + 0x60) == 0) || (*(int *)(*(longlong *)(itemData + 0x60) + 0x10) < 1)
     ) {
    uVar10 = *(undefined8 *)(self + 0x30);
    if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    cVar4 = FUN_7fff618ab2e0(uVar10,0);
    if (cVar4 != '\0') {
      if (*(longlong *)(self + 0x30) == 0) goto LAB_7fff5f9d8cee;
      FUN_7fff5ff0eed0(*(longlong *)(self + 0x30),_DAT_7fff623f7f60);
    }
LAB_7fff5f9d74d2:
    iVar20 = iStack_1a4;
    uVar9 = FUN_7fff60e71970(uVar9);
    if (iVar20 == 0x17) {
      uVar17 = 5;
      while (lVar7 = *(longlong *)(itemData + 0x18), lVar7 != 0) {
        puVar8 = _DAT_7fff623fa248;
        if (*(int *)(lVar7 + 0x18) <= (int)uVar17) goto LAB_7fff5f9d77cb;
        if (*(uint *)(lVar7 + 0x18) <= uVar17) goto LAB_7fff5f9d8d48;
        sVar5 = *(short *)(lVar7 + 0x20 + (longlong)(int)uVar17 * 2);
        if (sVar5 != 0) {
          puVar8 = UIItemProperty_get_skillTextManager(self,(undefined *)0x0);
          if (puVar8 == (undefined *)0x0) break;
          plVar16 = (longlong *)FUN_7fff5f256fc0(_DAT_7fff62472120,puVar8,(int)sVar5);
          if ((*(longlong *)(self + 0x70) == 0) ||
             (uVar10 = FUN_7fff5f568150(*(longlong *)(self + 0x70),_DAT_7fff6243a0a0,0),
             plVar16 == (longlong *)0x0)) break;
          uVar11 = (**(code **)(*plVar16 + 0x188))(plVar16,*(undefined8 *)(*plVar16 + 400));
          uVar10 = FUN_7fff60e74b00(uVar10,uVar11,0);
          uVar9 = FUN_7fff60e71050(uVar9,_DAT_7fff62425680,uVar10,_DAT_7fff62426490,0);
        }
        uVar17 = uVar17 + 1;
      }
      goto LAB_7fff5f9d8cee;
    }
  }
  else {
    if (isPotentialZero == 0) {
      iVar20 = (int)*(short *)(itemData + 0x50);
    }
    uVar10 = *(undefined8 *)(self + 0x30);
    if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    cVar4 = FUN_7fff618ab2e0(uVar10,0,0);
    if (cVar4 == '\0') {
      puVar8 = UIItemProperty_get_systemTextManager(self,(undefined *)0x0);
      if (puVar8 == (undefined *)0x0) {
        FUN_7fff5f47d660();
        pcVar2 = (code *)swi(3);
        fVar24 = (float)(*pcVar2)();
        return fVar24;
      }
      uVar10 = FUN_7fff5f568150(puVar8,_DAT_7fff62438cb8,0);
      uVar11 = FUN_7fff60e71650(_DAT_7fff62420aa8,*(undefined8 *)(itemData + 0x60),_DAT_7fff624263c8
                                ,0);
      uStack_150 = CONCAT44(uStack_150._4_4_,iVar20);
      uVar12 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,&uStack_150);
      uVar10 = FUN_7fff60e74db0(uVar10,uVar11,uVar12,0);
      uVar9 = FUN_7fff60e71970(uVar9,uVar10);
      goto LAB_7fff5f9d74d2;
    }
    if ((*(longlong *)(self + 0x28) == 0) ||
       (FUN_7fff5ff0eed0(*(longlong *)(self + 0x28),uVar9,0), *(longlong *)(self + 0x28) == 0))
    goto LAB_7fff5f9d8cee;
    puVar8 = (undefined *)FUN_7fff5ff0e870();
    if (*(int *)(_DAT_7fff623f57b0 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    iVar21 = UIItemProperty_RowCount(puVar8,(undefined *)0x0);
    uVar10 = _DAT_7fff623f7f60;
    if (0 < (int)(iVar21 - 1U)) {
      uVar18 = (ulonglong)(iVar21 - 1U);
      do {
        uVar10 = FUN_7fff60e71970(uVar10,_DAT_7fff623fa248,0);
        uVar18 = uVar18 - 1;
      } while (uVar18 != 0);
    }
    lVar7 = *(longlong *)(self + 0x30);
    puVar8 = UIItemProperty_get_systemTextManager(self,(undefined *)0x0);
    if (puVar8 == (undefined *)0x0) goto LAB_7fff5f9d8cee;
    uVar11 = FUN_7fff5f568150(puVar8,_DAT_7fff62438d80,0);
    uVar12 = FUN_7fff60e71650(_DAT_7fff62420aa8,*(undefined8 *)(itemData + 0x60),_DAT_7fff624263c8,0
                             );
    uVar11 = FUN_7fff60e74b00(uVar11,uVar12);
    FUN_7fff60e71970(uVar10,uVar11);
    if (lVar7 == 0) goto LAB_7fff5f9d8cee;
    FUN_7fff5ff0eed0(lVar7);
    if (iStack_1a4 == 0x17) goto LAB_7fff5f9d74d2;
    puVar8 = UIItemProperty_get_systemTextManager(self,(undefined *)0x0);
    if (puVar8 == (undefined *)0x0) {
      FUN_7fff5f47d660();
      pcVar2 = (code *)swi(3);
      fVar24 = (float)(*pcVar2)();
      return fVar24;
    }
    uVar10 = FUN_7fff5f568150(puVar8,_DAT_7fff62438e40,0);
    uStack_168 = CONCAT44(uStack_168._4_4_,iVar20);
    uVar11 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,&uStack_168);
    uVar10 = FUN_7fff60e74b00(uVar10,uVar11,0);
    uVar9 = FUN_7fff60e71650(uVar9,_DAT_7fff623fa248,uVar10,0);
    uVar9 = FUN_7fff60e71970(uVar9,_DAT_7fff623fa248);
  }
  puVar8 = UIItemProperty_ItemText(self,*(int *)(itemData + 0x34),(undefined *)0x0);
LAB_7fff5f9d77cb:
  uVar9 = FUN_7fff60e71970(uVar9,puVar8,0);
  if (DAT_7fff625e3299 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff623f57b0);
    DAT_7fff625e3299 = '\x01';
  }
  puVar8 = *(undefined **)(itemData + 0x10);
  iVar20 = *(int *)(self + 0x98);
  capVal = *(undefined **)(itemData + 0x18);
  itemPropertyTextManager = UIItemProperty_get_itemPropertyTextManager(self,(undefined *)0x0);
  uStack_178 = *(undefined **)(self + 0x70);
  if (*(int *)(_DAT_7fff623f57b0 + 0xe0) == 0) {
    func_0x7fff5f47d6f0();
  }
  puVar8 = UIItemProperty_GetItemPropertysTextData
                     (puVar8,capVal,iVar20,itemPropertyTextManager,uStack_178,(undefined *)0x0);
  uVar9 = FUN_7fff60e71970(uVar9,puVar8,0);
  uStack_168 = uVar9;
  lVar7 = func_0x7fff5f47c850(_DAT_7fff6241fab8,2);
  if (lVar7 == 0) goto LAB_7fff5f9d8cee;
  if (*(int *)(lVar7 + 0x18) == 0) {
LAB_7fff5f9d8d48:
    FUN_7fff5f47d650();
    pcVar2 = (code *)swi(3);
    fVar24 = (float)(*pcVar2)();
    return fVar24;
  }
  *(undefined4 *)(lVar7 + 0x20) = *(undefined4 *)(itemData + 0x48);
  fVar24 = _DAT_7fff61b52b88;
  if (*(uint *)(lVar7 + 0x18) < 2) goto LAB_7fff5f9d8d48;
  *(undefined4 *)(lVar7 + 0x24) = *(undefined4 *)(itemData + 0x4c);
  uVar17 = uVar22;
  do {
    if (*(longlong *)(self + 0x28) == 0) goto LAB_7fff5f9d8cee;
    FUN_7fff5ff0eed0(*(longlong *)(self + 0x28),uVar9,0);
    if (*(longlong *)(self + 0x28) == 0) goto LAB_7fff5f9d8cee;
    lVar13 = FUN_7fff5ff0e870(*(longlong *)(self + 0x28),0);
    if (*(int *)(_DAT_7fff623f57b0 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    if (DAT_7fff625e3296 == '\0') {
      FUN_7fff5f47d450(&DAT_7fff623fa248);
      FUN_7fff5f47d450(&DAT_7fff624292a8);
      FUN_7fff5f47d450(&DAT_7fff623f7f60);
      DAT_7fff625e3296 = '\x01';
    }
    if (lVar13 == 0) goto LAB_7fff5f9d8cee;
    lVar14 = FUN_7fff60e78ac0(lVar13,_DAT_7fff623fa248,_DAT_7fff623f7f60,0);
    iVar20 = *(int *)(lVar13 + 0x10);
    if (lVar14 == 0) goto LAB_7fff5f9d8cee;
    iVar21 = *(int *)(lVar14 + 0x10);
    lVar13 = FUN_7fff60e78ac0(lVar14,_DAT_7fff624292a8,_DAT_7fff623f7f60,0);
    if (lVar13 == 0) goto LAB_7fff5f9d8cee;
    iVar1 = *(int *)(lVar13 + 0x10);
    if ((*(longlong *)(self + 0x28) == 0) ||
       (lVar13 = FUN_7fff618a1b90(*(longlong *)(self + 0x28),0), lVar13 == 0))
    goto LAB_7fff5f9d8cee;
    puVar15 = (undefined8 *)FUN_7fff618c8560(&uStack_118);
    puStack_188 = (undefined *)*puVar15;
    fStack_180 = *(float *)(puVar15 + 1);
    fStack_170 = fStack_180 + 0.0;
    uStack_178 = (undefined *)
                 CONCAT44((float)(((iVar21 - (iVar21 - iVar1) / 2) - iVar20) * 0x20 + -0x10) +
                          (float)((ulonglong)puStack_188 >> 0x20),SUB84(puStack_188,0) + fVar24);
    bVar3 = ItemData_get_SlotMax(itemData,(undefined *)0x0);
    if ((int)uVar17 < (int)(uint)bVar3) {
      lVar13 = *(longlong *)(self + 0x40);
      if (lVar13 == 0) goto LAB_7fff5f9d8cee;
      if (*(uint *)(lVar13 + 0x18) <= uVar17) goto LAB_7fff5f9d8d48;
      lVar19 = (longlong)(int)uVar17;
      lVar14 = *(longlong *)(lVar13 + 0x20 + lVar19 * 8);
      lVar13 = lVar19 * 8 + 0x20;
      if (lVar14 == 0) goto LAB_7fff5f9d8cee;
      FUN_7fff618a0e80(lVar14,1,0);
      if (*(uint *)(lVar7 + 0x18) <= uVar17) goto LAB_7fff5f9d8d48;
      if (*(int *)(lVar7 + 0x20 + lVar19 * 4) == 0) {
        lVar14 = *(longlong *)(self + 0x38);
        if (lVar14 == 0) goto LAB_7fff5f9d8cee;
        if (*(uint *)(lVar14 + 0x18) <= uVar17) goto LAB_7fff5f9d8d48;
        if (*(longlong *)(lVar14 + lVar13) == 0) goto LAB_7fff5f9d8cee;
        FUN_7fff618a0e80(*(longlong *)(lVar14 + lVar13),0,0);
        uVar9 = FUN_7fff60e71650(uVar9,*(undefined8 *)(self + 0x20));
        uStack_168 = uVar9;
      }
      else {
        lVar14 = FUN_7fff60c4bc00(_DAT_7fff6245a5f8);
        if (*(uint *)(lVar7 + 0x18) <= uVar17) goto LAB_7fff5f9d8d48;
        if (lVar14 == 0) goto LAB_7fff5f9d8cee;
        FUN_7fff600847d0(lVar14,*(undefined4 *)(lVar7 + 0x20 + lVar19 * 4),0);
        lVar14 = *(longlong *)(self + 0x38);
        if (lVar14 == 0) goto LAB_7fff5f9d8cee;
        if (*(uint *)(lVar14 + 0x18) <= uVar17) goto LAB_7fff5f9d8d48;
        if (*(longlong *)(lVar14 + lVar13) == 0) goto LAB_7fff5f9d8cee;
        FUN_7fff618a0e80(*(longlong *)(lVar14 + lVar13),1,0);
        lVar14 = *(longlong *)(self + 0x38);
        if (lVar14 == 0) goto LAB_7fff5f9d8cee;
        if ((*(uint *)(lVar14 + 0x18) <= uVar17) ||
           (lVar14 = *(longlong *)(lVar14 + lVar13), *(uint *)(lVar7 + 0x18) <= uVar17))
        goto LAB_7fff5f9d8d48;
        uVar6 = *(undefined4 *)(lVar7 + 0x20 + lVar19 * 4);
        uStack_150 = CONCAT44(uStack_150._4_4_,uVar6);
        if (*(int *)(_DAT_7fff623f5540 + 0xe0) == 0) {
          func_0x7fff5f47d6f0();
          uVar6 = (undefined4)uStack_150;
        }
        uVar9 = FUN_7fff5fd776d0(uVar6,0);
        if (lVar14 == 0) goto LAB_7fff5f9d8cee;
        FUN_7fff60020030(lVar14,uVar9,0);
        uVar9 = *(undefined8 *)(self + 0x20);
        puVar8 = UIItemProperty_get_itemTextManager(self,(undefined *)0x0);
        if (*(uint *)(lVar7 + 0x18) <= uVar17) goto LAB_7fff5f9d8d48;
        if ((puVar8 == (undefined *)0x0) ||
           (plVar16 = (longlong *)
                      FUN_7fff5f256fc0(_DAT_7fff62411ec0,puVar8,
                                       *(undefined4 *)(lVar7 + 0x20 + lVar19 * 4)),
           plVar16 == (longlong *)0x0)) goto LAB_7fff5f9d8cee;
        uVar10 = (**(code **)(*plVar16 + 0x188))(plVar16,*(undefined8 *)(*plVar16 + 400));
        uVar9 = FUN_7fff60e71050(uStack_168,uVar9,uVar10,_DAT_7fff623fa248,0);
        uStack_168 = uVar9;
      }
    }
    else {
      lVar13 = *(longlong *)(self + 0x38);
      if (lVar13 == 0) goto LAB_7fff5f9d8cee;
      if (*(uint *)(lVar13 + 0x18) <= uVar17) goto LAB_7fff5f9d8d48;
      lVar14 = *(longlong *)(lVar13 + 0x20 + (longlong)(int)uVar17 * 8);
      lVar13 = (longlong)(int)uVar17 * 8 + 0x20;
      if (lVar14 == 0) goto LAB_7fff5f9d8cee;
      FUN_7fff618a0e80(lVar14,0);
      lVar14 = *(longlong *)(self + 0x40);
      if (lVar14 == 0) goto LAB_7fff5f9d8cee;
      if (*(uint *)(lVar14 + 0x18) <= uVar17) goto LAB_7fff5f9d8d48;
      if (*(longlong *)(lVar14 + lVar13) == 0) goto LAB_7fff5f9d8cee;
      FUN_7fff618a0e80(*(longlong *)(lVar14 + lVar13),0);
    }
    lVar14 = *(longlong *)(self + 0x38);
    if (lVar14 == 0) goto LAB_7fff5f9d8cee;
    if (*(uint *)(lVar14 + 0x18) <= uVar17) goto LAB_7fff5f9d8d48;
    if ((*(longlong *)(lVar14 + lVar13) == 0) ||
       (lVar14 = FUN_7fff618a1b90(*(longlong *)(lVar14 + lVar13),0), fVar23 = fStack_170,
       puVar8 = uStack_178, lVar14 == 0)) goto LAB_7fff5f9d8cee;
    uStack_128 = uStack_178;
    fStack_120 = fStack_170;
    FUN_7fff618c8e40(lVar14,&uStack_128);
    lVar14 = *(longlong *)(self + 0x40);
    if (lVar14 == 0) goto LAB_7fff5f9d8cee;
    if (*(uint *)(lVar14 + 0x18) <= uVar17) goto LAB_7fff5f9d8d48;
    if ((*(longlong *)(lVar14 + lVar13) == 0) ||
       (lVar13 = FUN_7fff618a1b90(*(longlong *)(lVar14 + lVar13),0), lVar13 == 0))
    goto LAB_7fff5f9d8cee;
    uStack_138 = puVar8;
    fStack_130 = fVar23;
    FUN_7fff618c8e40(lVar13);
    uVar17 = uVar17 + 1;
  } while ((int)uVar17 < 2);
  sVar5 = ItemData_get_RandamProperty(itemData,(undefined *)0x0);
  if (sVar5 < 1) {
    uVar10 = *(undefined8 *)(self + 0x58);
    if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    cVar4 = FUN_7fff618ab2e0(uVar10,0,0);
    if (cVar4 != '\0') {
      if (*(longlong *)(self + 0x58) == 0) goto LAB_7fff5f9d8cee;
      FUN_7fff618a0e80(*(longlong *)(self + 0x58),0,0);
    }
  }
  else {
    if (*(longlong *)(self + 0x28) == 0) goto LAB_7fff5f9d8cee;
    FUN_7fff5ff0eed0(*(longlong *)(self + 0x28),uVar9,0);
    if (*(longlong *)(self + 0x28) == 0) goto LAB_7fff5f9d8cee;
    lVar7 = FUN_7fff5ff0e870(*(longlong *)(self + 0x28),0);
    if (*(int *)(_DAT_7fff623f57b0 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    if (DAT_7fff625e3296 == '\0') {
      FUN_7fff5f47d450(&DAT_7fff623fa248);
      FUN_7fff5f47d450(&DAT_7fff624292a8);
      FUN_7fff5f47d450(&DAT_7fff623f7f60);
      DAT_7fff625e3296 = '\x01';
    }
    if (lVar7 == 0) goto LAB_7fff5f9d8cee;
    lVar13 = FUN_7fff60e78ac0(lVar7,_DAT_7fff623fa248,_DAT_7fff623f7f60,0);
    iVar20 = *(int *)(lVar7 + 0x10);
    if (lVar13 == 0) goto LAB_7fff5f9d8cee;
    iVar21 = *(int *)(lVar13 + 0x10);
    lVar7 = FUN_7fff60e78ac0(lVar13,_DAT_7fff624292a8,_DAT_7fff623f7f60,0);
    if (lVar7 == 0) goto LAB_7fff5f9d8cee;
    iVar1 = *(int *)(lVar7 + 0x10);
    if ((*(longlong *)(self + 0x28) == 0) ||
       (lVar7 = FUN_7fff618a1b90(*(longlong *)(self + 0x28),0), lVar7 == 0)) goto LAB_7fff5f9d8cee;
    puVar15 = (undefined8 *)FUN_7fff618c8560(&uStack_118,lVar7,0);
    puStack_188 = (undefined *)*puVar15;
    fStack_180 = *(float *)(puVar15 + 1);
    fStack_170 = fStack_180 + 0.0;
    uStack_178 = (undefined *)
                 CONCAT44((float)(((iVar21 - (iVar21 - iVar1) / 2) - iVar20) * 0x20 + -0x10) +
                          (float)((ulonglong)puStack_188 >> 0x20),SUB84(puStack_188,0) + fVar24);
    uVar10 = *(undefined8 *)(self + 0x58);
    if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    cVar4 = FUN_7fff618ab120(uVar10,0,0);
    if (cVar4 != '\0') {
      (**(code **)(*(longlong *)self + 0x1d8))(self,*(undefined8 *)(*(longlong *)self + 0x1e0));
    }
    uVar10 = *(undefined8 *)(self + 0x58);
    if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    cVar4 = FUN_7fff618ab2e0(uVar10,0,0);
    if (cVar4 != '\0') {
      if (*(longlong *)(self + 0x58) == 0) goto LAB_7fff5f9d8cee;
      FUN_7fff618a0e80(*(longlong *)(self + 0x58),1,0);
      if ((*(longlong *)(self + 0x58) == 0) ||
         (lVar7 = FUN_7fff618a1b90(*(longlong *)(self + 0x58),0), lVar7 == 0))
      goto LAB_7fff5f9d8cee;
      fStack_180 = fStack_170;
      puStack_188 = uStack_178;
      FUN_7fff618c8e40(lVar7,&puStack_188,0);
      plVar16 = *(longlong **)(self + 0x58);
      if (*(int *)(_DAT_7fff623f5540 + 0xe0) == 0) {
        func_0x7fff5f47d6f0();
      }
      puVar15 = (undefined8 *)FUN_7fff5fd777e0(&uStack_b8,sVar5,0);
      if (plVar16 == (longlong *)0x0) goto LAB_7fff5f9d8cee;
      uStack_c8 = *puVar15;
      uStack_c0 = puVar15[1];
      (**(code **)(*plVar16 + 0x1d8))(plVar16,&uStack_c8,*(undefined8 *)(*plVar16 + 0x1e0));
    }
    if (DAT_7fff625e3294 == '\0') {
      FUN_7fff5f47d450(&DAT_7fff62457310);
      FUN_7fff5f47d450(&DAT_7fff6245a460);
      DAT_7fff625e3294 = '\x01';
    }
    if (*(longlong *)(self + 0x90) == 0) {
      lVar7 = FUN_7fff60c4bc00(_DAT_7fff6245a460);
      if (lVar7 == 0) goto LAB_7fff5f9d8cee;
      plVar16 = (longlong *)FUN_7fff5f55ae30(lVar7,0xe);
      if (plVar16 == (longlong *)0x0) {
        *(undefined8 *)(self + 0x90) = 0;
      }
      else {
        if ((*(byte *)(*plVar16 + 0x130) < *(byte *)(_DAT_7fff62457310 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar16 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7fff62457310 + 0x130) * 8) != _DAT_7fff62457310)) {
          FUN_7fff5f47c810(plVar16);
          pcVar2 = (code *)swi(3);
          fVar24 = (float)(*pcVar2)();
          return fVar24;
        }
        *(longlong **)(self + 0x90) = plVar16;
        if ((*(byte *)(*plVar16 + 0x130) < *(byte *)(_DAT_7fff62457310 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar16 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7fff62457310 + 0x130) * 8) != _DAT_7fff62457310)) {
          FUN_7fff5f47c810(plVar16);
          pcVar2 = (code *)swi(3);
          fVar24 = (float)(*pcVar2)();
          return fVar24;
        }
      }
      thunk_FUN_7fff5f491fd0();
    }
    plVar16 = *(longlong **)(self + 0x90);
    if (plVar16 == (longlong *)0x0) goto LAB_7fff5f9d8cee;
    lVar7 = func_0x7fff5f47d0d0(*(undefined8 *)
                                 (*plVar16 +
                                 ((ulonglong)*(ushort *)(_DAT_7fff62411840 + 0x50) + 0x14) * 0x10));
    plVar16 = (longlong *)(**(code **)(lVar7 + 8))(plVar16,(int)sVar5,lVar7);
    uVar10 = *(undefined8 *)(self + 0x20);
    if (plVar16 == (longlong *)0x0) goto LAB_7fff5f9d8cee;
    uVar11 = (**(code **)(*plVar16 + 0x188))(plVar16,*(undefined8 *)(*plVar16 + 400));
    uVar9 = FUN_7fff60e71050(uVar9,uVar10,uVar11,_DAT_7fff623fa248,0);
  }
  uVar9 = FUN_7fff60e71970(uVar9,_DAT_7fff623fa248,0);
  if (iStack_1a4 != 0x17) {
    puVar8 = UIItemProperty_get_systemTextManager(self,(undefined *)0x0);
    if (bStack_1a7 == 0) {
      if (puVar8 == (undefined *)0x0) {
        FUN_7fff5f47d660();
        pcVar2 = (code *)swi(3);
        fVar24 = (float)(*pcVar2)();
        return fVar24;
      }
      uVar10 = FUN_7fff5f568150(puVar8,_DAT_7fff62438fc8,0);
      puVar15 = &uStack_168;
      uStack_168 = CONCAT62(uStack_168._2_6_,*(undefined2 *)(lStack_160 + 0x3e));
    }
    else {
      if (puVar8 == (undefined *)0x0) {
        FUN_7fff5f47d660();
        pcVar2 = (code *)swi(3);
        fVar24 = (float)(*pcVar2)();
        return fVar24;
      }
      uVar10 = FUN_7fff5f568150(puVar8,_DAT_7fff62438f08,0);
      puVar15 = &uStack_198;
      uStack_198._0_2_ = *(undefined2 *)(lStack_160 + 0x3e);
    }
    uVar11 = func_0x7fff5f47c7a0(_DAT_7fff62453138,puVar15);
    uVar10 = FUN_7fff60e74b00(uVar10,uVar11,0);
    uVar9 = FUN_7fff60e71970(uVar9,uVar10,0);
  }
  if (*(int *)(itemData + 0x38) - 0x12U < 2) {
    puVar8 = UIItemProperty_get_systemTextManager(self,(undefined *)0x0);
    if (puVar8 == (undefined *)0x0) goto LAB_7fff5f9d8cee;
    uVar10 = FUN_7fff5f568150(puVar8,_DAT_7fff62439cd0,0);
    puVar8 = UIItemProperty_get_systemTextManager(self,(undefined *)0x0);
    uVar11 = _DAT_7fff62439838;
joined_r0x7fff5f9d8311:
    if (puVar8 == (undefined *)0x0) goto LAB_7fff5f9d8cee;
    uVar11 = FUN_7fff5f568150(puVar8,uVar11,0);
    uVar10 = FUN_7fff60e74b00(uVar10,uVar11,0);
LAB_7fff5f9d8337:
    uVar9 = FUN_7fff60e71970(uVar9,uVar10,0);
  }
  else {
    if (*(int *)(itemData + 0x38) == 0x16) {
      puVar8 = UIItemProperty_get_systemTextManager(self,(undefined *)0x0);
      if (puVar8 == (undefined *)0x0) goto LAB_7fff5f9d8cee;
      uVar10 = FUN_7fff5f568150(puVar8,_DAT_7fff62439cd0,0);
      puVar8 = UIItemProperty_get_systemTextManager(self,(undefined *)0x0);
      uVar11 = _DAT_7fff624398f8;
      goto joined_r0x7fff5f9d8311;
    }
    if (iStack_1a4 != 0x17) {
      puVar8 = UIItemProperty_get_systemTextManager(self,(undefined *)0x0);
      if (puVar8 == (undefined *)0x0) {
        FUN_7fff5f47d660();
        pcVar2 = (code *)swi(3);
        fVar24 = (float)(*pcVar2)();
        return fVar24;
      }
      uVar10 = FUN_7fff5f568150(puVar8,_DAT_7fff62439d90,0);
      puVar8 = ItemData_RefineToString(itemData,(undefined *)0x0);
      asStack_19c[0] = ItemData_get_OreBonus(itemData,(undefined *)0x0);
      uVar11 = func_0x7fff5f47c7a0(_DAT_7fff62453138,asStack_19c);
      uVar10 = FUN_7fff60e74db0(uVar10,puVar8,uVar11,0);
      goto LAB_7fff5f9d8337;
    }
  }
  if (*(int *)(itemData + 0x38) - 0x11U < 3) {
    puVar8 = UIItemProperty_get_systemTextManager(self,(undefined *)0x0);
    if (puVar8 == (undefined *)0x0) goto LAB_7fff5f9d8cee;
    uVar10 = FUN_7fff5f568150(puVar8,_DAT_7fff6243a168,0);
    puVar8 = UIItemProperty_get_systemTextManager(self,(undefined *)0x0);
    if (puVar8 == (undefined *)0x0) goto LAB_7fff5f9d8cee;
    uVar11 = FUN_7fff5f568150(puVar8,_DAT_7fff624399c0,0);
LAB_7fff5f9d84bf:
    uVar10 = FUN_7fff60e74b00(uVar10,uVar11,0);
LAB_7fff5f9d84cd:
    uVar9 = FUN_7fff60e71970(uVar9,uVar10,0);
  }
  else if (iStack_1a4 != 0x17) {
    if ((*(int *)(itemData + 0x38) != 0x14) || ((byte)itemData[0x53] < 4)) {
      puVar8 = UIItemProperty_get_systemTextManager(self,(undefined *)0x0);
      if (puVar8 == (undefined *)0x0) {
        FUN_7fff5f47d660();
        pcVar2 = (code *)swi(3);
        fVar24 = (float)(*pcVar2)();
        return fVar24;
      }
      uVar10 = FUN_7fff5f568150(puVar8,_DAT_7fff6243a168,0);
      bStack_1a8 = ItemData_get_SlotMax(itemData,(undefined *)0x0);
      uVar11 = func_0x7fff5f47c7a0(_DAT_7fff62454290,&bStack_1a8);
      goto LAB_7fff5f9d84bf;
    }
    puVar8 = UIItemProperty_get_systemTextManager(self,(undefined *)0x0);
    if (puVar8 == (undefined *)0x0) {
LAB_7fff5f9d8d30:
      FUN_7fff5f47d660();
      pcVar2 = (code *)swi(3);
      fVar24 = (float)(*pcVar2)();
      return fVar24;
    }
    uVar10 = FUN_7fff5f568150(puVar8,_DAT_7fff6243a228,0);
    bStack_1a7 = ItemData_get_SlotMax(itemData,(undefined *)0x0);
    uVar11 = func_0x7fff5f47c7a0(_DAT_7fff62454290);
    puVar8 = UIItemProperty_get_systemTextManager(self,(undefined *)0x0);
    abStack_1a0[0] = ItemData_GetCustomize(itemData,(undefined *)0x0);
    uVar12 = FUN_7fff60f8f420(abStack_1a0,0);
    uVar12 = FUN_7fff60e71970(_DAT_7fff6243a2f0,uVar12,0);
    if (puVar8 == (undefined *)0x0) goto LAB_7fff5f9d8d30;
    uVar12 = FUN_7fff5f568150(puVar8,uVar12,0);
    uVar10 = FUN_7fff60e74db0(uVar10,uVar11,uVar12,0);
    goto LAB_7fff5f9d84cd;
  }
  if (*(longlong *)(self + 0x28) == 0) {
LAB_7fff5f9d8cee:
    FUN_7fff5f47d660();
    pcVar2 = (code *)swi(3);
    fVar24 = (float)(*pcVar2)();
    return fVar24;
  }
  FUN_7fff5ff0eed0(*(longlong *)(self + 0x28),uVar9,0);
  if (*(longlong *)(self + 0x28) == 0) goto LAB_7fff5f9d8d42;
  lVar7 = FUN_7fff5ff0e870(*(longlong *)(self + 0x28),0);
  if (*(int *)(_DAT_7fff623f57b0 + 0xe0) == 0) {
    func_0x7fff5f47d6f0();
  }
  if (DAT_7fff625e3296 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff623fa248);
    FUN_7fff5f47d450(&DAT_7fff624292a8);
    FUN_7fff5f47d450(&DAT_7fff623f7f60);
    DAT_7fff625e3296 = '\x01';
  }
  if (lVar7 == 0) goto LAB_7fff5f9d8d42;
  lVar13 = FUN_7fff60e78ac0(lVar7,_DAT_7fff623fa248,_DAT_7fff623f7f60,0);
  iVar20 = *(int *)(lVar7 + 0x10);
  if (lVar13 == 0) goto LAB_7fff5f9d8d42;
  iVar21 = *(int *)(lVar13 + 0x10);
  lVar7 = FUN_7fff60e78ac0(lVar13,_DAT_7fff624292a8,_DAT_7fff623f7f60,0);
  if (lVar7 == 0) goto LAB_7fff5f9d8d42;
  iVar20 = (iVar20 + ((iVar21 - *(int *)(lVar7 + 0x10)) / 2 - iVar21)) * 0x20;
  iVar21 = iVar20 + 0x30;
  if (*(longlong *)(self + 0x28) == 0) goto LAB_7fff5f9d8d42;
  lVar7 = FUN_7fff618a1b90(*(longlong *)(self + 0x28),0);
  if (DAT_7fff625e12ce == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62403718);
    DAT_7fff625e12ce = '\x01';
  }
  if (lVar7 == 0) goto LAB_7fff5f9d8d42;
  puStack_188 = *(undefined **)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0xc);
  fStack_180 = *(float *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0x14);
  FUN_7fff618c8f80(lVar7,&puStack_188);
  if (*(longlong *)(self + 0x70) == 0) goto LAB_7fff5f9d8d42;
  uVar10 = FUN_7fff5f568150(*(longlong *)(self + 0x70),_DAT_7fff62438a70);
  if (*(longlong *)(self + 0x70) == 0) goto LAB_7fff5f9d8d42;
  uStack_150 = FUN_7fff5f568150(*(longlong *)(self + 0x70),_DAT_7fff62438b30);
  if (*(longlong *)(self + 0x70) == 0) goto LAB_7fff5f9d8d42;
  uStack_178 = (undefined *)FUN_7fff5f568150(*(longlong *)(self + 0x70),_DAT_7fff62438bf8);
  lVar7 = FUN_7fff60e71970(_DAT_7fff623fa248,uVar10);
  lStack_160 = lVar7;
  lVar13 = func_0x7fff5f47c850(_DAT_7fff62419460,3);
  if (lVar13 == 0) goto LAB_7fff5f9d8d42;
  if (*(int *)(lVar13 + 0x18) == 0) {
LAB_7fff5f9d8d3c:
    FUN_7fff5f47d650();
    pcVar2 = (code *)swi(3);
    fVar24 = (float)(*pcVar2)();
    return fVar24;
  }
  *(undefined *)(lVar13 + 0x20) = itemData[0x58];
  if (*(uint *)(lVar13 + 0x18) < 2) goto LAB_7fff5f9d8d3c;
  *(undefined *)(lVar13 + 0x21) = itemData[0x59];
  fVar23 = _DAT_7fff61b532c8;
  fVar24 = _DAT_7fff61b52e64;
  if (*(uint *)(lVar13 + 0x18) < 3) goto LAB_7fff5f9d8d3c;
  *(undefined *)(lVar13 + 0x22) = itemData[0x5a];
  do {
    if (iStack_1a4 == 0x17) {
      if (*(uint *)(lVar13 + 0x18) <= uVar22) goto LAB_7fff5f9d8d3c;
      *(undefined1 *)((longlong)(int)uVar22 + 0x20 + lVar13) = 0;
    }
    if (*(uint *)(lVar13 + 0x18) <= uVar22) goto LAB_7fff5f9d8d3c;
    lVar14 = *(longlong *)(self + 0x48);
    lVar19 = (longlong)(int)uVar22;
    if (*(char *)(lVar13 + 0x20 + lVar19) == '\0') {
      if (lVar14 == 0) goto LAB_7fff5f9d8d42;
      if (*(uint *)(lVar14 + 0x18) <= uVar22) goto LAB_7fff5f9d8d3c;
      lVar14 = *(longlong *)(lVar14 + 0x20 + lVar19 * 8);
      if (lVar14 == 0) goto LAB_7fff5f9d8d42;
      FUN_7fff618a0e80(lVar14,0);
      lVar14 = *(longlong *)(self + 0x50);
      if (lVar14 == 0) goto LAB_7fff5f9d8d42;
      if (*(uint *)(lVar14 + 0x18) <= uVar22) goto LAB_7fff5f9d8d3c;
      lVar14 = *(longlong *)(lVar14 + 0x20 + lVar19 * 8);
      if (lVar14 == 0) goto LAB_7fff5f9d8d42;
      FUN_7fff618a0e80(lVar14,0);
      puVar8 = uStack_178;
    }
    else {
      if (lVar14 == 0) goto LAB_7fff5f9d8d42;
      if (*(uint *)(lVar14 + 0x18) <= uVar22) goto LAB_7fff5f9d8d3c;
      lVar7 = *(longlong *)(lVar14 + 0x20 + lVar19 * 8);
      if (lVar7 == 0) goto LAB_7fff5f9d8d42;
      FUN_7fff618a0e80(lVar7,1,0);
      lVar7 = *(longlong *)(self + 0x48);
      if (lVar7 == 0) goto LAB_7fff5f9d8d42;
      if (*(uint *)(lVar7 + 0x18) <= uVar22) goto LAB_7fff5f9d8d3c;
      lVar7 = *(longlong *)(lVar7 + 0x20 + lVar19 * 8);
      if (lVar7 == 0) goto LAB_7fff5f9d8d42;
      lVar7 = FUN_7fff618a1b90(lVar7,0);
      if ((*(longlong *)(self + 0x28) == 0) ||
         (lVar14 = FUN_7fff618a1b90(*(longlong *)(self + 0x28),0), lVar14 == 0))
      goto LAB_7fff5f9d8d42;
      puVar15 = (undefined8 *)FUN_7fff618c8560(auStack_a8,lVar14,0);
      fStack_100 = *(float *)(puVar15 + 1);
      fStack_130 = fStack_100 + 0.0;
      uStack_138 = (undefined *)
                   CONCAT44((float)-iVar21 + (float)((ulonglong)*puVar15 >> 0x20),
                            (float)(int)uVar22 * fVar23 + fVar24 + (float)*puVar15);
      if (lVar7 == 0) goto LAB_7fff5f9d8d42;
      puStack_f8 = uStack_138;
      fStack_f0 = fStack_130;
      FUN_7fff618c8e40(lVar7,&puStack_f8,0);
      lVar7 = *(longlong *)(self + 0x50);
      if (lVar7 == 0) goto LAB_7fff5f9d8d42;
      if (*(uint *)(lVar7 + 0x18) <= uVar22) goto LAB_7fff5f9d8d3c;
      lVar7 = *(longlong *)(lVar7 + 0x20 + lVar19 * 8);
      if (lVar7 == 0) goto LAB_7fff5f9d8d42;
      FUN_7fff618a0e80(lVar7,1,0);
      lVar7 = *(longlong *)(self + 0x50);
      if (lVar7 == 0) goto LAB_7fff5f9d8d42;
      if (*(uint *)(lVar7 + 0x18) <= uVar22) goto LAB_7fff5f9d8d3c;
      plVar16 = *(longlong **)(lVar7 + 0x20 + lVar19 * 8);
      lVar7 = FUN_7fff60c4bc00(_DAT_7fff6245a790);
      if (*(uint *)(lVar13 + 0x18) <= uVar22) goto LAB_7fff5f9d8d3c;
      if ((lVar7 == 0) ||
         (puVar15 = (undefined8 *)
                    FUN_7fff600860b0(auStack_98,lVar7,*(undefined1 *)(lVar13 + 0x20 + lVar19),0),
         plVar16 == (longlong *)0x0)) goto LAB_7fff5f9d8d42;
      uStack_b8 = *puVar15;
      uStack_b0 = puVar15[1];
      (**(code **)(*plVar16 + 0x1d8))(plVar16,&uStack_b8);
      lVar7 = *(longlong *)(self + 0x50);
      if (lVar7 == 0) goto LAB_7fff5f9d8d42;
      if (*(uint *)(lVar7 + 0x18) <= uVar22) goto LAB_7fff5f9d8d3c;
      lVar7 = *(longlong *)(lVar7 + 0x20 + lVar19 * 8);
      if (lVar7 == 0) goto LAB_7fff5f9d8d42;
      lVar14 = FUN_7fff618a1b90(lVar7,0);
      lVar7 = *(longlong *)(self + 0x48);
      if (lVar7 == 0) goto LAB_7fff5f9d8d42;
      if (*(uint *)(lVar7 + 0x18) <= uVar22) goto LAB_7fff5f9d8d3c;
      lVar7 = *(longlong *)(lVar7 + 0x20 + lVar19 * 8);
      if ((lVar7 == 0) || (lVar7 = FUN_7fff618a1b90(lVar7,0), lVar7 == 0)) goto LAB_7fff5f9d8d42;
      puVar15 = (undefined8 *)FUN_7fff618c8560(&uStack_c8,lVar7);
      fStack_e0 = *(float *)(puVar15 + 1);
      fStack_120 = fStack_e0 + 0.0;
      uStack_128 = (undefined *)
                   CONCAT44((float)((ulonglong)*puVar15 >> 0x20) + 0.0,(float)*puVar15 + fVar24);
      if (lVar14 == 0) goto LAB_7fff5f9d8d42;
      puStack_d8 = uStack_128;
      fStack_d0 = fStack_120;
      FUN_7fff618c8e40(lVar14,&puStack_d8);
      lVar7 = *(longlong *)(self + 0x50);
      if (lVar7 == 0) goto LAB_7fff5f9d8d42;
      if (*(uint *)(lVar7 + 0x18) <= uVar22) goto LAB_7fff5f9d8d3c;
      lVar7 = *(longlong *)(lVar7 + 0x20 + lVar19 * 8);
      if (lVar7 == 0) goto LAB_7fff5f9d8d42;
      lVar7 = FUN_7fff618a1b90(lVar7,0);
      puStack_188 = (undefined *)0x3f80000040000000;
      fStack_180 = 1.0;
      if (lVar7 == 0) goto LAB_7fff5f9d8d42;
      uStack_110 = 0x3f800000;
      uStack_118 = 0x3f80000040000000;
      FUN_7fff618c8f80(lVar7,&uStack_118);
      if (*(uint *)(lVar13 + 0x18) <= uVar22) goto LAB_7fff5f9d8d3c;
      aiStack_158[0] = *(byte *)(lVar13 + 0x20 + lVar19) - 10;
      lVar7 = lStack_160;
      if (aiStack_158[0] < 100) {
        lVar7 = FUN_7fff60e71970(lStack_160,_DAT_7fff623fda58);
      }
      if (aiStack_158[0] < 10) {
        lVar7 = FUN_7fff60e71970(lVar7,_DAT_7fff623fda58);
      }
      puVar8 = (undefined *)FUN_7fff6100e780(aiStack_158,0);
    }
    uVar10 = FUN_7fff60e71970(lVar7,puVar8);
    lVar7 = FUN_7fff60e71970(uVar10);
    uVar22 = uVar22 + 1;
    lStack_160 = lVar7;
  } while ((int)uVar22 < 3);
  uVar22 = *(uint *)(lVar13 + 0x18);
  if (uVar22 == 0) goto LAB_7fff5f9d8d3c;
  if (*(char *)(lVar13 + 0x20) == '\0') {
    if (uVar22 < 2) goto LAB_7fff5f9d8d3c;
    if (*(char *)(lVar13 + 0x21) != '\0') goto LAB_7fff5f9d8b61;
    if (uVar22 < 3) goto LAB_7fff5f9d8d3c;
    if (*(char *)(lVar13 + 0x22) != '\0') goto LAB_7fff5f9d8b61;
  }
  else {
LAB_7fff5f9d8b61:
    iVar21 = iVar20 + 0x58;
    uVar9 = FUN_7fff60e71650(uVar9,lVar7,_DAT_7fff623fa318,0);
  }
  uStack_198._4_4_ = *(undefined4 *)(itemData + 0x38);
  switch(uStack_198._4_4_) {
  case 9:
  case 0xb:
  case 0x11:
code_r0x7fff5f9d8c14:
    lVar7 = *(longlong *)(self + 0x70);
    uVar10 = uRam00007fff624392d8;
    break;
  case 10:
    lVar7 = *(longlong *)(self + 0x70);
    uVar10 = uRam00007fff62439218;
    break;
  default:
    goto LAB_7fff5f9d8c45;
  case 0xf:
  case 0x12:
code_r0x7fff5f9d8bfe:
    lVar7 = *(longlong *)(self + 0x70);
    uVar10 = uRam00007fff624388e8;
    break;
  case 0x10:
    lVar7 = *(longlong *)(self + 0x70);
    uVar10 = uRam00007fff624393a0;
    break;
  case 0x14:
    bVar3 = ItemDBData_CheckArmorAbility(itemData,2,(undefined *)0x0);
    if (bVar3 != 0) goto code_r0x7fff5f9d8c14;
    bVar3 = ItemDBData_CheckArmorAbility(itemData,1,(undefined *)0x0);
    if (bVar3 != 0) goto code_r0x7fff5f9d8bfe;
    goto LAB_7fff5f9d8c45;
  }
  if (lVar7 != 0) {
    uVar10 = FUN_7fff5f568150(lVar7,uVar10,0);
    uVar9 = FUN_7fff60e71970(uVar9,uVar10,0);
    iVar21 = iVar21 + 0x20;
LAB_7fff5f9d8c45:
    if (iStack_1a4 == 0x17) {
      if (*(longlong *)(self + 0x70) == 0) goto LAB_7fff5f9d8d42;
      uVar10 = FUN_7fff5f568150(*(longlong *)(self + 0x70),_DAT_7fff62439770,0);
      uVar9 = FUN_7fff60e71970(uVar9,uVar10,0);
      iVar21 = iVar21 + 0x20;
    }
    if (*(longlong *)(self + 0x28) != 0) {
      FUN_7fff5ff0eed0(*(longlong *)(self + 0x28),uVar9,0);
      return (float)iVar21;
    }
  }
LAB_7fff5f9d8d42:
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  fVar24 = (float)(*pcVar2)();
  return fVar24;
}

