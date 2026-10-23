
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

short SmithGrant_CalcUsePotentialPoint
                (undefined *self,undefined *customItem,undefined *changeProperties,
                undefined *newProperties,int exclusionType,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  float fVar3;
  float fVar4;
  float fVar5;
  char cVar6;
  short sVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  longlong lVar11;
  longlong lVar12;
  undefined *puVar13;
  undefined8 uVar14;
  longlong *plVar15;
  undefined *puVar16;
  uint uVar17;
  longlong lVar18;
  undefined4 uVar19;
  int iVar20;
  int iVar21;
  int iVar22;
  uint uVar23;
  short sVar24;
  uint uVar25;
  int iVar26;
  int iVar27;
  bool bVar28;
  float fVar29;
  undefined8 uStack_c0;
  undefined8 *puStack_b8;
  undefined8 uStack_b0;
  undefined8 uStack_a8;
  int iStack_a0;
  int iStack_9c;
  undefined8 uStack_98;
  undefined8 *puStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  
  puVar16 = changeProperties;
  if (DAT_7fff625e422c == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62400c10,customItem,changeProperties,newProperties,changeProperties,
                     changeProperties);
    FUN_7fff5f47d450(&DAT_7fff62400730);
    FUN_7fff5f47d450(&DAT_7fff62462c40);
    FUN_7fff5f47d450(&DAT_7fff6244ce08);
    FUN_7fff5f47d450(&DAT_7fff62400f50);
    FUN_7fff5f47d450(&DAT_7fff624011c0);
    FUN_7fff5f47d450(&DAT_7fff624198f8);
    FUN_7fff5f47d450(&DAT_7fff62406e28);
    FUN_7fff5f47d450(&DAT_7fff6242ef00);
    FUN_7fff5f47d450(&DAT_7fff6243cc28);
    FUN_7fff5f47d450(&DAT_7fff6243ccf0);
    FUN_7fff5f47d450(0x7fff6243cdb0);
    FUN_7fff5f47d450(&DAT_7fff62443ed8);
    FUN_7fff5f47d450(&DAT_7fff62420f50);
    FUN_7fff5f47d450(&DAT_7fff624485c8);
    FUN_7fff5f47d450(0x7fff62470f08);
    FUN_7fff5f47d450(&DAT_7fff62433fb8);
    FUN_7fff5f47d450(&DAT_7fff62434388);
    FUN_7fff5f47d450(&DAT_7fff62433d68);
    FUN_7fff5f47d450(&DAT_7fff62472be0);
    FUN_7fff5f47d450(&DAT_7fff6245a5f8);
    FUN_7fff5f47d450(&DAT_7fff62416d90);
    FUN_7fff5f47d450(&DAT_7fff6242a2e0);
    DAT_7fff625e422c = '\x01';
  }
  uStack_98 = 0;
  puStack_90 = (undefined8 *)0x0;
  uStack_88 = 0;
  uStack_80 = 0;
  lVar11 = func_0x7fff5f44ff00(_DAT_7fff624198f8);
  FUN_7fff6082b860(lVar11,_DAT_7fff62400730);
  lVar12 = func_0x7fff5f44ff00(_DAT_7fff62472be0);
  FUN_7fff60a943d0();
  uVar25 = 0;
  if (newProperties != (undefined *)0x0) {
    for (; fVar29 = _DAT_7fff61b52b18, (int)uVar25 < (int)*(uint *)(newProperties + 0x18);
        uVar25 = uVar25 + 1) {
      if (*(uint *)(newProperties + 0x18) <= uVar25) goto LAB_7fff5fc6e496;
      lVar1 = *(longlong *)(newProperties + (longlong)(int)uVar25 * 8 + 0x20);
      puVar13 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff6242a2e0);
      SmithGrant_Update(puVar13,(undefined *)0x0);
      if (lVar1 == 0) goto LAB_7fff5fc6e48a;
      if ((*(int *)(lVar1 + 0x10) != 0) && (*(int *)(lVar1 + 0x10) != exclusionType)) {
        if (puVar13 == (undefined *)0x0) goto LAB_7fff5fc6e48a;
        *(undefined4 *)(puVar13 + 0x10) = 0;
        if (*(int *)(lVar1 + 0x10) == 0x41) {
          if (*(int *)(_DAT_7fff62420f50 + 0xe0) == 0) {
            func_0x7fff5f47d6f0(_DAT_7fff62420f50);
          }
          lVar18 = *(longlong *)(*(longlong *)(_DAT_7fff62420f50 + 0xb8) + 8);
          if (lVar18 == 0) goto LAB_7fff5fc6e48a;
          iVar8 = (int)*(short *)(lVar1 + 0x14);
          uVar14 = _DAT_7fff62462c40;
        }
        else {
          if (*(int *)(_DAT_7fff62420f50 + 0xe0) == 0) {
            func_0x7fff5f47d6f0(_DAT_7fff62420f50);
          }
          lVar18 = **(longlong **)(_DAT_7fff62420f50 + 0xb8);
          if (lVar18 == 0) goto LAB_7fff5fc6e48a;
          iVar8 = *(int *)(lVar1 + 0x10);
          uVar14 = _DAT_7fff6244ce08;
        }
        FUN_7fff6088c670(&uStack_c0,lVar18,iVar8,uVar14);
        *(int *)(puVar13 + 0x10) = (int)((ulonglong)puStack_b8 >> 0x20);
        if (lVar12 == 0) goto LAB_7fff5fc6e48a;
        cVar6 = FUN_7fff60ad29f0(lVar12,*(undefined4 *)(puVar13 + 0x10),_DAT_7fff62434388);
        if (cVar6 != '\0') {
          uVar14 = func_0x7fff5f44ff00(_DAT_7fff62443ed8);
          FUN_7fff60a1f970(uVar14,puVar13,_DAT_7fff62416d90,0);
          uVar14 = FUN_7fff6069d430(lVar12,uVar14,_DAT_7fff6242ef00);
          iVar8 = FUN_7fff6068aa20(uVar14,_DAT_7fff62406e28);
          if (0 < iVar8) {
            if (iVar8 == 1) {
              if (lVar11 == 0) goto LAB_7fff5fc6e48a;
              FUN_7fff6083fcb0(lVar11,*(undefined4 *)(puVar13 + 0x10),1,_DAT_7fff624011c0);
              uVar19 = *(undefined4 *)(puVar13 + 0x10);
            }
            else {
              uVar19 = *(undefined4 *)(puVar13 + 0x10);
              if (lVar11 == 0) goto LAB_7fff5fc6e48a;
            }
            iVar8 = FUN_7fff6083fbe0(lVar11,uVar19,_DAT_7fff62400f50);
            FUN_7fff6083fcb0(lVar11,uVar19,iVar8 + 1,_DAT_7fff624011c0);
          }
        }
        FUN_7fff5f254640(lVar12,*(undefined4 *)(puVar13 + 0x10),_DAT_7fff62433fb8);
      }
    }
    if (lVar11 != 0) {
      FUN_7fff607f7170(&uStack_c0,lVar11,_DAT_7fff62400c10);
      fVar3 = _DAT_7fff61b52b3c;
      uStack_98 = uStack_c0;
      puStack_90 = puStack_b8;
      uStack_88 = uStack_b0;
      uStack_80 = uStack_a8;
      uVar25 = 0;
      iVar8 = 0;
      uStack_c0 = 0;
      puStack_b8 = &uStack_98;
      while (cVar6 = FUN_7fff60949fb0(&uStack_98,_DAT_7fff6243ccf0), cVar6 != '\0') {
        iVar9 = (int)((ulonglong)uStack_88 >> 0x20);
        fVar29 = fVar29 + (float)(iVar9 * iVar9) * fVar3;
      }
      SmithGrant_Update((undefined *)&uStack_98,_DAT_7fff6243cc28);
      fVar5 = _DAT_7fff61b52c90;
      fVar4 = _DAT_7fff61b52b4c;
      sVar24 = 0;
      sVar7 = 0;
      uVar23 = uVar25;
      puVar13 = puVar16;
      if (changeProperties != (undefined *)0x0) {
LAB_7fff5fc6e000:
        if (*(int *)(puVar16 + 0x18) <= (int)uVar23) {
          return (short)(int)((float)(int)sVar24 * fVar29);
        }
        if (*(uint *)(changeProperties + 0x18) <= uVar23) goto LAB_7fff5fc6e496;
        lVar11 = *(longlong *)(changeProperties + (longlong)(int)uVar23 * 8 + 0x20);
        if ((((lVar11 == 0) || (iVar9 = *(int *)(lVar11 + 0x10), iVar9 == 0)) ||
            (*(short *)(lVar11 + 0x14) == 0)) || (iVar9 == exclusionType)) goto LAB_7fff5fc6e431;
        puVar16 = puVar13;
        if (iVar9 == 0x41) {
          if (*(int *)(_DAT_7fff62420f50 + 0xe0) == 0) {
            func_0x7fff5f47d6f0(_DAT_7fff62420f50);
            puVar16 = puVar13;
          }
          lVar12 = *(longlong *)(*(longlong *)(_DAT_7fff62420f50 + 0xb8) + 8);
          if (lVar12 == 0) goto LAB_7fff5fc6e48a;
          FUN_7fff6088c670(&uStack_c0,lVar12,(int)*(short *)(lVar11 + 0x14),_DAT_7fff62462c40);
          lVar12 = *(longlong *)(*(longlong *)(_DAT_7fff62420f50 + 0xb8) + 8);
          if (lVar12 == 0) goto LAB_7fff5fc6e48a;
          iVar20 = (int)*(short *)(lVar11 + 0x14);
          uVar14 = _DAT_7fff62462c40;
          iVar27 = (int)uStack_c0;
        }
        else {
          if (*(int *)(_DAT_7fff62420f50 + 0xe0) == 0) {
            func_0x7fff5f47d6f0(_DAT_7fff62420f50);
            puVar16 = puVar13;
          }
          if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) == 0) goto LAB_7fff5fc6e48a;
          FUN_7fff6088c670(&uStack_c0,**(longlong **)(_DAT_7fff62420f50 + 0xb8),
                           *(undefined4 *)(lVar11 + 0x10),_DAT_7fff6244ce08);
          lVar12 = **(longlong **)(_DAT_7fff62420f50 + 0xb8);
          if (lVar12 == 0) goto LAB_7fff5fc6e48a;
          iVar20 = *(int *)(lVar11 + 0x10);
          uVar14 = _DAT_7fff6244ce08;
          iVar27 = (int)uStack_c0;
        }
        FUN_7fff6088c670(&uStack_c0,lVar12,iVar20,uVar14);
        iVar20 = iStack_9c;
        if (customItem == (undefined *)0x0) goto LAB_7fff5fc6e48a;
        cVar6 = func_0x7fff5fd83130(*(undefined4 *)(customItem + 0x38),0);
        if (cVar6 == '\0') {
          bVar28 = iVar20 == 1;
        }
        else {
          bVar28 = iVar20 == 2;
        }
        if (bVar28) {
          iVar27 = iVar27 * 2;
        }
        iVar20 = (int)*(short *)(lVar11 + 0x14);
        if (iVar9 == 0x41) {
          lVar12 = FUN_7fff60c4bc00(_DAT_7fff6245a5f8);
          if (lVar12 != 0) {
            lVar12 = FUN_7fff600847d0(lVar12,*(undefined4 *)(customItem + 0x34),0);
            if (lVar12 != 0) {
              lVar1 = *(longlong *)(lVar12 + 0x10);
              uVar17 = uVar25;
              do {
                if (lVar1 == 0) goto LAB_7fff5fc6e48a;
                if ((int)*(uint *)(lVar1 + 0x18) <= (int)uVar17) break;
                if (*(uint *)(lVar1 + 0x18) <= uVar17) goto LAB_7fff5fc6e496;
                if (*(short *)(lVar1 + 0x20 + (longlong)(int)uVar17 * 2) == 0x41) {
                  lVar18 = *(longlong *)(lVar12 + 0x18);
                  if (lVar18 == 0) goto LAB_7fff5fc6e48a;
                  if (*(uint *)(lVar18 + 0x18) <= uVar17) goto LAB_7fff5fc6e496;
                  if (*(short *)(lVar18 + 0x20 + (longlong)(int)uVar17 * 2) ==
                      *(short *)(lVar11 + 0x14)) goto LAB_7fff5fc6e407;
                }
                uVar17 = uVar17 + 1;
              } while( true );
            }
            goto LAB_7fff5fc6e41f;
          }
          goto LAB_7fff5fc6e48a;
        }
        if (*(int *)(_DAT_7fff62420f50 + 0xe0) == 0) {
          func_0x7fff5f47d6f0(_DAT_7fff62420f50);
        }
        if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) == 0) goto LAB_7fff5fc6e48a;
        FUN_7fff6088c670(&uStack_c0,**(longlong **)(_DAT_7fff62420f50 + 0xb8),
                         *(undefined4 *)(lVar11 + 0x10),_DAT_7fff6244ce08);
        iVar9 = iStack_a0;
        lVar12 = *(longlong *)(customItem + 0x10);
        uVar17 = uVar25;
        while( true ) {
          if (lVar12 == 0) goto LAB_7fff5fc6e48a;
          iVar22 = 0;
          if ((int)*(uint *)(lVar12 + 0x18) <= (int)uVar17) goto LAB_7fff5fc6e217;
          if (*(uint *)(lVar12 + 0x18) <= uVar17) goto LAB_7fff5fc6e496;
          if (*(short *)(lVar12 + 0x20 + (longlong)(int)uVar17 * 2) == *(short *)(lVar11 + 0x10))
          break;
          uVar17 = uVar17 + 1;
        }
        lVar11 = *(longlong *)(customItem + 0x18);
        if (lVar11 == 0) goto LAB_7fff5fc6e48a;
        if (*(uint *)(lVar11 + 0x18) <= uVar17) {
LAB_7fff5fc6e496:
          FUN_7fff5f47d650();
          pcVar2 = (code *)swi(3);
          sVar7 = (*pcVar2)();
          return sVar7;
        }
        iVar22 = (int)*(short *)(lVar11 + 0x20 + (longlong)(int)uVar17 * 2);
LAB_7fff5fc6e217:
        iVar21 = iVar22 + iVar20;
        iVar10 = (int)((ulonglong)uStack_b0 >> 0x20);
        if (iVar20 < 0) {
          iVar26 = iVar8;
          if ((iVar10 < iVar22) && (iVar26 = iVar20, iVar20 <= iVar10 - iVar22)) {
            iVar26 = iVar10 - iVar22;
          }
          iVar20 = iVar20 - iVar26;
          iVar26 = iVar26 / iStack_a0;
          iVar22 = iVar8;
          if ((iVar21 < -iVar10) && (iVar22 = iVar20, iVar20 <= iVar21 + iVar10)) {
            iVar22 = iVar21 + iVar10;
          }
          if (((*(longlong *)(self + 0x140) != 0) &&
              (plVar15 = (longlong *)FUN_7fff5ff8ac30(*(longlong *)(self + 0x140),0),
              plVar15 != (longlong *)0x0)) &&
             (lVar11 = (**(code **)(*plVar15 + 0x198))(plVar15,*(undefined8 *)(*plVar15 + 0x1a0)),
             lVar11 != 0)) {
            iVar10 = FUN_7fff5f252ec0(9,_DAT_7fff624485c8,lVar11);
            sVar24 = sVar7 + (short)(int)(((float)iVar10 / fVar5 + fVar3) *
                                         ((float)(iVar22 / iVar9) * fVar4 +
                                         (float)((iVar26 - iVar22) + iVar20)) * (float)iVar27);
            puVar13 = puVar16;
            sVar7 = sVar24;
            goto LAB_7fff5fc6e431;
          }
          goto LAB_7fff5fc6e48a;
        }
        iVar9 = 0;
        if ((iVar22 < -iVar10) && (iVar9 = iVar20, -(iVar10 + iVar22) <= iVar20)) {
          iVar9 = -(iVar10 + iVar22);
        }
        iVar20 = iVar20 - iVar9;
        iVar22 = iVar8;
        if ((iVar10 < iVar21) && (iVar22 = iVar20, iVar21 - iVar10 <= iVar20)) {
          iVar22 = iVar21 - iVar10;
        }
        sVar24 = sVar24 + (((short)(iVar22 / iStack_a0) * 2 - (short)iVar22) + (short)iVar20 +
                          (short)(iVar9 / iStack_a0)) * (short)iVar27;
        puVar13 = puVar16;
        sVar7 = sVar24;
        goto LAB_7fff5fc6e431;
      }
    }
  }
LAB_7fff5fc6e48a:
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  sVar7 = (*pcVar2)();
  return sVar7;
LAB_7fff5fc6e407:
  iVar27 = (int)(short)iVar27 / 10;
LAB_7fff5fc6e41f:
  sVar24 = sVar24 + (short)iVar27;
  puVar13 = puVar16;
  sVar7 = sVar24;
LAB_7fff5fc6e431:
  uVar23 = uVar23 + 1;
  goto LAB_7fff5fc6e000;
}

