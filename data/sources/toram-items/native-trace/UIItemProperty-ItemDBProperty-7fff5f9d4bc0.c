
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UIItemProperty_ItemDBProperty(undefined *self,int itemId,undefined *methodInfo)

{
  short sVar1;
  short sVar2;
  ushort uVar3;
  longlong lVar4;
  longlong lVar5;
  longlong *plVar6;
  bool isColor;
  code *pcVar7;
  byte bVar8;
  char cVar9;
  int iVar10;
  undefined *puVar11;
  undefined *puVar12;
  longlong lVar13;
  longlong lVar14;
  longlong lVar15;
  undefined8 uVar16;
  uint uVar17;
  uint uVar18;
  int iVar19;
  int iVar20;
  uint uVar21;
  int iVar22;
  longlong lStackX_20;
  
  if (DAT_7fff625e329a == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62450248);
    FUN_7fff5f47d450(&DAT_7fff6245af88);
    FUN_7fff5f47d450(&DAT_7fff6245a5f8);
    FUN_7fff5f47d450(&DAT_7fff62426990);
    FUN_7fff5f47d450(&DAT_7fff624606c8);
    FUN_7fff5f47d450(&DAT_7fff623f57b0);
    FUN_7fff5f47d450(&DAT_7fff623fa248);
    FUN_7fff5f47d450(&DAT_7fff623fda58);
    FUN_7fff5f47d450(&DAT_7fff62426490);
    FUN_7fff5f47d450(&DAT_7fff623f7f60);
    DAT_7fff625e329a = '\x01';
  }
  puVar11 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff6245a5f8);
  if (puVar11 != (undefined *)0x0) {
    puVar11 = MasterItemDataManager_GetMasterItemData(puVar11,itemId,(undefined *)0x0);
    lStackX_20 = _DAT_7fff623f7f60;
    if (puVar11 != (undefined *)0x0) {
      lVar4 = *(longlong *)(puVar11 + 0x18);
      iVar20 = 0;
      lVar5 = *(longlong *)(puVar11 + 0x10);
      uVar21 = 0;
      iVar22 = 0;
      lVar14 = _DAT_7fff623f7f60;
      do {
        isColor = iVar20 < 1;
        iVar19 = iVar20 + -1;
        if (iVar20 < 1) {
          iVar19 = iVar20;
        }
        iVar20 = iVar19;
        if (lVar5 == 0) goto LAB_7fff5f9d5166;
        if (*(uint *)(lVar5 + 0x18) <= uVar21) goto LAB_7fff5f9d516c;
        lVar13 = (longlong)(int)uVar21 * 2 + 0x20;
        sVar1 = *(short *)(lVar13 + lVar5);
        if (*(int *)(_DAT_7fff62450248 + 0xe0) == 0) {
          func_0x7fff5f47d6f0();
        }
        bVar8 = BonusManager_CheckEquipLimitBonusId(sVar1,(undefined *)0x0);
        if (bVar8 == 0) {
          if (*(uint *)(lVar5 + 0x18) <= uVar21) {
LAB_7fff5f9d516c:
            FUN_7fff5f47d650();
            pcVar7 = (code *)swi(3);
            (*pcVar7)();
            return;
          }
          sVar1 = *(short *)(lVar13 + lVar5);
          if (lVar4 == 0) goto LAB_7fff5f9d5166;
          if (*(uint *)(lVar4 + 0x18) <= uVar21) goto LAB_7fff5f9d516c;
          sVar2 = *(short *)(lVar13 + lVar4);
          puVar12 = UIItemProperty_get_itemPropertyTextManager(self,(undefined *)0x0);
          puVar11 = *(undefined **)(self + 0x70);
          if (*(int *)(_DAT_7fff623f57b0 + 0xe0) == 0) {
            func_0x7fff5f47d6f0();
          }
          puVar11 = UIItemProperty_AddCapProperty
                              (isColor,sVar1,sVar2,puVar12,puVar11,(undefined *)0x0);
          iVar19 = 0;
          if (puVar11 == (undefined *)0x0) goto LAB_7fff5f9d5166;
          lVar13 = FUN_7fff60e7ad00(puVar11);
          uVar18 = 0;
          while( true ) {
            if (lVar13 == 0) goto LAB_7fff5f9d5166;
            if ((int)*(uint *)(lVar13 + 0x18) <= (int)uVar18) break;
            if (*(uint *)(lVar13 + 0x18) <= uVar18) goto LAB_7fff5f9d516c;
            uVar3 = *(ushort *)(lVar13 + 0x20 + (longlong)(int)uVar18 * 2);
            uVar17 = uVar3 - 0x25;
            if ((((ushort)uVar17 < 0x39) &&
                ((0x17ffffff01ff941U >> ((ulonglong)uVar17 & 0x3f) & 1) != 0)) ||
               (iVar10 = 2, (ushort)(uVar3 - 0x61) < 0x1a)) {
              iVar10 = 1;
            }
            uVar18 = uVar18 + 1;
            iVar19 = iVar19 + iVar10;
          }
          iVar19 = iVar19 + -0x10;
          if (iVar20 == 0) {
            if ((iVar22 < 1) || (iVar19 + iVar22 <= *(int *)(self + 0x98))) {
              lStackX_20 = FUN_7fff60e71050(lStackX_20,lVar14,puVar11,_DAT_7fff62426490,0);
            }
            else {
              lVar13 = func_0x7fff5f47c850(_DAT_7fff62426990,5);
              if (lVar13 == 0) goto LAB_7fff5f9d5166;
              if (*(int *)(lVar13 + 0x18) == 0) goto LAB_7fff5f9d516c;
              *(longlong *)(lVar13 + 0x20) = lStackX_20;
              thunk_FUN_7fff5f491fd0();
              if (*(uint *)(lVar13 + 0x18) < 2) goto LAB_7fff5f9d516c;
              *(longlong *)(lVar13 + 0x28) = lVar14;
              thunk_FUN_7fff5f491fd0();
              if (*(uint *)(lVar13 + 0x18) < 3) goto LAB_7fff5f9d516c;
              *(undefined8 *)(lVar13 + 0x30) = _DAT_7fff623fa248;
              thunk_FUN_7fff5f491fd0();
              if (*(uint *)(lVar13 + 0x18) < 4) goto LAB_7fff5f9d516c;
              *(undefined **)(lVar13 + 0x38) = puVar11;
              thunk_FUN_7fff5f491fd0();
              if (*(uint *)(lVar13 + 0x18) < 5) goto LAB_7fff5f9d516c;
              *(undefined8 *)(lVar13 + 0x40) = _DAT_7fff62426490;
              thunk_FUN_7fff5f491fd0();
              lStackX_20 = FUN_7fff60e712f0(lVar13);
            }
            iVar20 = 0;
            lVar14 = _DAT_7fff623f7f60;
          }
          else {
            if (*(int *)(self + 0x98) < iVar19 + iVar22) {
              lStackX_20 = FUN_7fff60e71650(lStackX_20,lVar14,_DAT_7fff623fa248,0);
              iVar22 = 0;
              lVar14 = _DAT_7fff623f7f60;
            }
            iVar22 = iVar22 + iVar19;
            lVar14 = FUN_7fff60e71650(lVar14,puVar11,_DAT_7fff623fda58,0);
          }
        }
        else {
          if (lVar14 == 0) goto LAB_7fff5f9d5166;
          if (0 < *(int *)(lVar14 + 0x10)) {
            lStackX_20 = FUN_7fff60e71650(lStackX_20,lVar14,_DAT_7fff623fa248,0);
          }
          lVar14 = **(longlong **)(_DAT_7fff624606c8 + 0xb8);
          lVar15 = FUN_7fff60c4bc00(_DAT_7fff6245af88);
          if ((lVar15 == 0) || (*(longlong *)(lVar15 + 0x28) == 0)) goto LAB_7fff5f9d5166;
          uVar16 = FUN_7fff5f597090();
          if (*(uint *)(lVar5 + 0x18) <= uVar21) goto LAB_7fff5f9d516c;
          sVar1 = *(short *)(lVar13 + lVar5);
          if (lVar4 == 0) goto LAB_7fff5f9d5166;
          if (*(uint *)(lVar4 + 0x18) <= uVar21) goto LAB_7fff5f9d516c;
          sVar2 = *(short *)(lVar13 + lVar4);
          puVar12 = UIItemProperty_get_itemPropertyTextManager(self,(undefined *)0x0);
          puVar11 = *(undefined **)(self + 0x70);
          if (*(int *)(_DAT_7fff623f57b0 + 0xe0) == 0) {
            func_0x7fff5f47d6f0();
          }
          puVar11 = UIItemProperty_AddCapProperty(0,sVar1,sVar2,puVar12,puVar11,(undefined *)0x0);
          lStackX_20 = FUN_7fff60e71050(lStackX_20,uVar16,puVar11,_DAT_7fff623fa248,0);
          if (*(uint *)(lVar4 + 0x18) <= uVar21) goto LAB_7fff5f9d516c;
          iVar20 = (int)*(short *)(lVar13 + lVar4);
        }
        uVar21 = uVar21 + 1;
      } while ((int)uVar21 < 10);
      if (0 < iVar22) {
        lStackX_20 = FUN_7fff60e71650(lStackX_20,lVar14,_DAT_7fff623fa248,0);
      }
      plVar6 = *(longlong **)(self + 0x28);
      if (plVar6 != (longlong *)0x0) {
        if (DAT_7fff625e5260 == '\0') {
          FUN_7fff5f47d450(&DAT_7fff6240e4b0,lStackX_20,0);
          FUN_7fff5f47d450(&DAT_7fff623f7f60);
          DAT_7fff625e5260 = '\x01';
        }
        cVar9 = func_0x7fff60e76090(lStackX_20,0);
        if (cVar9 == '\0') {
          cVar9 = FUN_7fff60e7b970(plVar6[0x23],lStackX_20,0);
          if (cVar9 != '\0') {
            plVar6[0x23] = lStackX_20;
            thunk_FUN_7fff5f491fd0();
            *(undefined1 *)(plVar6 + 0xb) = 1;
            *(undefined1 *)((longlong)plVar6 + 0x161) = 1;
            lVar4 = plVar6[0x22];
            if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
              func_0x7fff5f47d6f0();
            }
            cVar9 = FUN_7fff618ab2e0(lVar4,0,0);
            if (cVar9 != '\0') {
              if (plVar6[0x22] == 0) {
                FUN_7fff5f47d660();
                pcVar7 = (code *)swi(3);
                (*pcVar7)();
                return;
              }
              FUN_7fff5ff06840(plVar6[0x22],lStackX_20,0);
            }
            if (*(int *)((longlong)plVar6 + 0x14c) == 0) {
                    /* WARNING: Could not recover jumptable at 0x7fff5ff0efc3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
              (**(code **)(*plVar6 + 0x2b8))(plVar6,*(undefined8 *)(*plVar6 + 0x2c0));
              return;
            }
          }
        }
        else {
          cVar9 = func_0x7fff60e76090(plVar6[0x23],0);
          if (cVar9 == '\0') {
            plVar6[0x23] = _DAT_7fff623f7f60;
            thunk_FUN_7fff5f491fd0();
          }
          *(undefined1 *)(plVar6 + 0xb) = 1;
          *(undefined1 *)((longlong)plVar6 + 0x161) = 1;
        }
        return;
      }
    }
  }
LAB_7fff5f9d5166:
  FUN_7fff5f47d660();
  pcVar7 = (code *)swi(3);
  (*pcVar7)();
  return;
}

