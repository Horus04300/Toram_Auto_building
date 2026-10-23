
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
UIItemProperty_GetItemPropertysTextData
          (undefined *capId,undefined *capVal,int widthWord,undefined *itemPropertyTextManager,
          undefined *systemManager,undefined *methodInfo)

{
  short sVar1;
  short sVar2;
  code *pcVar3;
  byte bVar4;
  int iVar5;
  undefined *puVar6;
  longlong lVar7;
  undefined *puVar8;
  longlong lVar9;
  undefined8 uVar10;
  undefined *puVar11;
  int iVar12;
  uint uVar13;
  int iVar14;
  
  if (DAT_7fff625e328f == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62450248);
    FUN_7fff5f47d450(&DAT_7fff6245af88);
    FUN_7fff5f47d450(&DAT_7fff62426990);
    FUN_7fff5f47d450(&DAT_7fff624606c8);
    FUN_7fff5f47d450(&DAT_7fff623f57b0);
    FUN_7fff5f47d450(&DAT_7fff623fa248);
    FUN_7fff5f47d450(&DAT_7fff623fda58);
    FUN_7fff5f47d450(&DAT_7fff62426490);
    FUN_7fff5f47d450(&DAT_7fff623f7f60);
    DAT_7fff625e328f = '\x01';
  }
  iVar14 = 0;
  iVar12 = 0;
  uVar13 = 0;
  puVar11 = _DAT_7fff623f7f60;
  puVar8 = _DAT_7fff623f7f60;
  do {
    iVar5 = iVar12 + -1;
    if (iVar12 < 1) {
      iVar5 = iVar12;
    }
    if (capId == (undefined *)0x0) goto LAB_7fff5f9d4bab;
    if (*(uint *)(capId + 0x18) <= uVar13) goto LAB_7fff5f9d4bb1;
    sVar1 = *(short *)(capId + (longlong)(int)uVar13 * 2 + 0x20);
    lVar7 = (longlong)(int)uVar13 * 2 + 0x20;
    if (0 < sVar1) {
      if (*(int *)(_DAT_7fff62450248 + 0xe0) == 0) {
        func_0x7fff5f47d6f0();
      }
      bVar4 = BonusManager_CheckEquipLimitBonusId(sVar1,(undefined *)0x0);
      if (bVar4 == 0) {
        if (*(uint *)(capId + 0x18) <= uVar13) {
LAB_7fff5f9d4bb1:
          FUN_7fff5f47d650();
          pcVar3 = (code *)swi(3);
          puVar11 = (undefined *)(*pcVar3)();
          return puVar11;
        }
        sVar1 = *(short *)(capId + lVar7);
        if (capVal == (undefined *)0x0) goto LAB_7fff5f9d4bab;
        if (*(uint *)(capVal + 0x18) <= uVar13) goto LAB_7fff5f9d4bb1;
        sVar2 = *(short *)(capVal + lVar7);
        if (*(int *)(_DAT_7fff623f57b0 + 0xe0) == 0) {
          func_0x7fff5f47d6f0();
        }
        puVar6 = UIItemProperty_AddCapProperty
                           (iVar12 < 1,sVar1,sVar2,itemPropertyTextManager,systemManager,
                            (undefined *)0x0);
        if (iVar12 < 1) {
          iVar14 = iVar14 + 0x10;
        }
        else if (iVar5 == 0) {
          if (puVar11 == (undefined *)0x0) goto LAB_7fff5f9d4bab;
          iVar5 = 0;
          if (0 < *(int *)(puVar11 + 0x10)) {
            if (puVar6 == (undefined *)0x0) goto LAB_7fff5f9d4bab;
            if (widthWord + iVar14 < *(int *)(puVar11 + 0x10) + *(int *)(puVar6 + 0x10)) {
              lVar7 = func_0x7fff5f47c850(_DAT_7fff62426990,5);
              if (lVar7 != 0) {
                if (*(int *)(lVar7 + 0x18) == 0) goto LAB_7fff5f9d4bb1;
                *(undefined **)(lVar7 + 0x20) = puVar8;
                thunk_FUN_7fff5f491fd0();
                if (*(uint *)(lVar7 + 0x18) < 2) goto LAB_7fff5f9d4bb1;
                *(undefined **)(lVar7 + 0x28) = puVar11;
                thunk_FUN_7fff5f491fd0();
                if (*(uint *)(lVar7 + 0x18) < 3) goto LAB_7fff5f9d4bb1;
                *(undefined8 *)(lVar7 + 0x30) = _DAT_7fff623fa248;
                thunk_FUN_7fff5f491fd0();
                if (*(uint *)(lVar7 + 0x18) < 4) goto LAB_7fff5f9d4bb1;
                *(undefined **)(lVar7 + 0x38) = puVar6;
                thunk_FUN_7fff5f491fd0();
                if (*(uint *)(lVar7 + 0x18) < 5) goto LAB_7fff5f9d4bb1;
                *(undefined8 *)(lVar7 + 0x40) = _DAT_7fff62426490;
                thunk_FUN_7fff5f491fd0();
                puVar8 = (undefined *)FUN_7fff60e712f0(lVar7);
                puVar11 = _DAT_7fff623f7f60;
                iVar14 = 0;
                goto LAB_7fff5f9d4b63;
              }
              goto LAB_7fff5f9d4bab;
            }
          }
          puVar8 = (undefined *)FUN_7fff60e71050(puVar8,puVar11,puVar6,_DAT_7fff62426490,0);
          puVar11 = _DAT_7fff623f7f60;
          iVar14 = 0;
          goto LAB_7fff5f9d4b63;
        }
        if ((puVar11 == (undefined *)0x0) || (puVar6 == (undefined *)0x0)) goto LAB_7fff5f9d4bab;
        if (widthWord + iVar14 < *(int *)(puVar6 + 0x10) + *(int *)(puVar11 + 0x10)) {
          if (*(int *)(puVar11 + 0x10) < 1) {
            puVar8 = (undefined *)FUN_7fff60e71650(puVar8,puVar6,_DAT_7fff623fa248,0);
            puVar11 = _DAT_7fff623f7f60;
            iVar14 = 0;
            goto LAB_7fff5f9d4b63;
          }
          puVar8 = (undefined *)FUN_7fff60e71650(puVar8,puVar11,_DAT_7fff623fa248,0);
          iVar14 = 0x10;
          puVar11 = _DAT_7fff623f7f60;
        }
        puVar11 = (undefined *)FUN_7fff60e71650(puVar11,puVar6,_DAT_7fff623fda58,0);
      }
      else {
        if (puVar11 == (undefined *)0x0) goto LAB_7fff5f9d4bab;
        if (0 < *(int *)(puVar11 + 0x10)) {
          puVar8 = (undefined *)FUN_7fff60e71650(puVar8,puVar11,_DAT_7fff623fa248,0);
        }
        puVar11 = (undefined *)**(undefined8 **)(_DAT_7fff624606c8 + 0xb8);
        lVar9 = FUN_7fff60c4bc00(_DAT_7fff6245af88);
        if ((lVar9 == 0) || (*(longlong *)(lVar9 + 0x28) == 0)) goto LAB_7fff5f9d4bab;
        uVar10 = FUN_7fff5f597090(*(longlong *)(lVar9 + 0x28),0);
        if (*(uint *)(capId + 0x18) <= uVar13) goto LAB_7fff5f9d4bb1;
        sVar1 = *(short *)(capId + lVar7);
        if (capVal == (undefined *)0x0) goto LAB_7fff5f9d4bab;
        if (*(uint *)(capVal + 0x18) <= uVar13) goto LAB_7fff5f9d4bb1;
        sVar2 = *(short *)(capVal + lVar7);
        if (*(int *)(_DAT_7fff623f57b0 + 0xe0) == 0) {
          func_0x7fff5f47d6f0();
        }
        puVar6 = UIItemProperty_AddCapProperty
                           (0,sVar1,sVar2,itemPropertyTextManager,systemManager,(undefined *)0x0);
        puVar8 = (undefined *)FUN_7fff60e71050(puVar8,uVar10,puVar6,_DAT_7fff623fa248,0);
        if (*(uint *)(capVal + 0x18) <= uVar13) goto LAB_7fff5f9d4bb1;
        iVar5 = (int)*(short *)(capVal + lVar7);
        iVar14 = 0;
      }
    }
LAB_7fff5f9d4b63:
    iVar12 = iVar5;
    uVar13 = uVar13 + 1;
  } while ((int)uVar13 < 10);
  if (puVar11 != (undefined *)0x0) {
    if (0 < *(int *)(puVar11 + 0x10)) {
      puVar8 = (undefined *)FUN_7fff60e71650(puVar8,puVar11,_DAT_7fff623fa248,0);
    }
    return puVar8;
  }
LAB_7fff5f9d4bab:
  FUN_7fff5f47d660();
  pcVar3 = (code *)swi(3);
  puVar11 = (undefined *)(*pcVar3)();
  return puVar11;
}

