
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithManufacture_SetRequiredMaterial(undefined *self,int index,undefined *methodInfo)

{
  undefined4 *puVar1;
  int materialId;
  uint uVar2;
  int iVar3;
  code *pcVar4;
  undefined4 uVar5;
  bool bVar6;
  longlong lVar7;
  char cVar8;
  undefined4 uVar9;
  int iVar10;
  longlong lVar11;
  longlong *plVar12;
  longlong lVar13;
  undefined8 uVar14;
  undefined *puVar15;
  undefined8 uVar16;
  longlong *plVar17;
  longlong lVar18;
  longlong lVar19;
  longlong lVar20;
  undefined *puVar21;
  int iVar22;
  undefined1 auStackX_8 [8];
  int iStackX_10;
  undefined2 auStackX_20 [4];
  int iStack_88;
  int iStack_84;
  int iStack_80;
  ulonglong auStack_78 [2];
  longlong lStack_68;
  undefined4 uStack_60;
  undefined4 uStack_5c;
  longlong alStack_58 [2];
  undefined1 auStack_48 [16];
  
  iStackX_10 = index;
  if (DAT_7fff625e4293 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62442b48);
    FUN_7fff5f47d450(&DAT_7fff6244b3d0);
    FUN_7fff5f47d450(&DAT_7fff6244b618);
    FUN_7fff5f47d450(&DAT_7fff6244fc80);
    FUN_7fff5f47d450(&DAT_7fff62473318);
    FUN_7fff5f47d450(&DAT_7fff624027e8);
    FUN_7fff5f47d450(&DAT_7fff6246d2c8);
    FUN_7fff5f47d450(&DAT_7fff624532c0);
    FUN_7fff5f47d450(&DAT_7fff62411ec0);
    FUN_7fff5f47d450(&DAT_7fff6243e9f8);
    FUN_7fff5f47d450(0x7fff6243eac0);
    FUN_7fff5f47d450(0x7fff6243ec48);
    FUN_7fff5f47d450(0x7fff62421078);
    FUN_7fff5f47d450(&DAT_7fff62450e50);
    FUN_7fff5f47d450(&DAT_7fff623fd630);
    FUN_7fff5f47d450(&DAT_7fff62401e80);
    FUN_7fff5f47d450(&DAT_7fff62422c48);
    FUN_7fff5f47d450(&DAT_7fff6245a5f8);
    FUN_7fff5f47d450(&DAT_7fff62473c38);
    FUN_7fff5f47d450(&DAT_7fff62473d00);
    FUN_7fff5f47d450(&DAT_7fff624606c8);
    FUN_7fff5f47d450(&DAT_7fff62409dd8);
    FUN_7fff5f47d450(0x7fff624781e0);
    FUN_7fff5f47d450(0x7fff624782b0);
    FUN_7fff5f47d450(0x7fff62478380);
    FUN_7fff5f47d450(&DAT_7fff62465e58);
    FUN_7fff5f47d450(&DAT_7fff623fda58);
    FUN_7fff5f47d450(&DAT_7fff62420200);
    FUN_7fff5f47d450(&DAT_7fff623f7d40);
    FUN_7fff5f47d450(&DAT_7fff6241c188);
    FUN_7fff5f47d450(&DAT_7fff62402a00);
    FUN_7fff5f47d450(&DAT_7fff623ffd48);
    FUN_7fff5f47d450(&DAT_7fff62411b58);
    FUN_7fff5f47d450(&DAT_7fff62415de0);
    FUN_7fff5f47d450(&DAT_7fff623f6820);
    FUN_7fff5f47d450(&DAT_7fff6243fa30);
    FUN_7fff5f47d450(&DAT_7fff624191d8);
    FUN_7fff5f47d450(&DAT_7fff623f7f60);
    FUN_7fff5f47d450(&DAT_7fff62419458);
    FUN_7fff5f47d450(&DAT_7fff62465d88);
    FUN_7fff5f47d450(&DAT_7fff623f8bd8);
    FUN_7fff5f47d450(&DAT_7fff62455f58);
    FUN_7fff5f47d450(&DAT_7fff624209d8);
    DAT_7fff625e4293 = '\x01';
  }
  lVar11 = *(longlong *)(self + 0x1b0);
  auStackX_8[0] = 0;
  iStack_88 = 0;
  auStackX_20[0] = 0;
  if (lVar11 == 0) goto LAB_7fff5fc955b2;
  *(int *)(lVar11 + 0x1c) = *(int *)(lVar11 + 0x1c) + 1;
  *(undefined4 *)(lVar11 + 0x18) = 0;
  iVar10 = 0;
LAB_7fff5fc94100:
  if (*(longlong *)(self + 0x1d0) == 0) goto LAB_7fff5fc955b2;
  iVar22 = iVar10 + iStackX_10 * 4;
  lVar11 = FUN_7fff60a94f50(*(longlong *)(self + 0x1d0),iVar22,_DAT_7fff62401e80);
  if (lVar11 == 0) goto LAB_7fff5fc955b2;
  materialId = *(int *)(lVar11 + 0x10);
  if ((*(longlong *)(self + 0x1d0) == 0) ||
     (lVar11 = FUN_7fff60a94f50(*(longlong *)(self + 0x1d0),iVar22,_DAT_7fff62401e80), lVar11 == 0))
  goto LAB_7fff5fc955b2;
  if (*(char *)(lVar11 + 0x18) == '\0') {
    if (materialId < 0) {
LAB_7fff5fc9489c:
      if (*(longlong *)(self + 0xa0) == 0) goto LAB_7fff5fc955b2;
      lVar11 = FUN_7fff618a4a10(*(longlong *)(self + 0xa0),0);
      iStack_88 = iVar10 + 1;
      uVar14 = FUN_7fff6100e780(&iStack_88,0);
      uVar14 = FUN_7fff60e71970(_DAT_7fff62420200,uVar14,0);
      if (((lVar11 == 0) || (lVar11 = FUN_7fff618c6ee0(lVar11,uVar14,0), lVar11 == 0)) ||
         (lVar11 = FUN_7fff60678610(lVar11,_DAT_7fff6244b3d0), lVar11 == 0)) goto LAB_7fff5fc955b2;
      FUN_7fff5fc309f0(lVar11,0,0);
      FUN_7fff5f6d4090(lVar11,_DAT_7fff623fda58,0);
      if (*(longlong *)(self + 0xa0) == 0) goto LAB_7fff5fc955b2;
      lVar11 = FUN_7fff618a4a10(*(longlong *)(self + 0xa0),0);
      iStack_88 = iVar10 + 1;
      uVar14 = FUN_7fff6100e780(&iStack_88,0);
      uVar14 = FUN_7fff60e71650(_DAT_7fff62420200,uVar14,_DAT_7fff62455f58);
      if (((lVar11 == 0) || (lVar11 = FUN_7fff618c6ee0(lVar11,uVar14,0), lVar11 == 0)) ||
         (lVar11 = FUN_7fff60678610(lVar11,_DAT_7fff6244fc80), lVar11 == 0)) goto LAB_7fff5fc955b2;
      FUN_7fff5ff0eed0(lVar11,_DAT_7fff623fda58,0);
      goto LAB_7fff5fc949c2;
    }
    if ((*(longlong *)(self + 0x38) == 0) ||
       (plVar12 = (longlong *)
                  FUN_7fff5f256fc0(_DAT_7fff62411ec0,*(longlong *)(self + 0x38),materialId),
       plVar12 == (longlong *)0x0)) goto LAB_7fff5fc955b2;
    auStack_78[0] = (**(code **)(*plVar12 + 0x188))(plVar12,*(undefined8 *)(*plVar12 + 400));
    lVar11 = *(longlong *)(self + 0x1b0);
    bVar6 = true;
    lVar13 = FUN_7fff60091590(0);
    if ((lVar13 == 0) ||
       (plVar12 = (longlong *)FUN_7fff60091140(alStack_58,lVar13,materialId,0),
       lVar13 = _DAT_7fff6243e9f8, lVar11 == 0)) goto LAB_7fff5fc955b2;
    lVar20 = *plVar12;
    uVar9 = *(undefined4 *)((longlong)plVar12 + 4);
    lVar19 = *plVar12;
    lVar7 = plVar12[1];
    uVar5 = *(undefined4 *)((longlong)plVar12 + 0xc);
    *(int *)(lVar11 + 0x1c) = *(int *)(lVar11 + 0x1c) + 1;
    lVar18 = *(longlong *)(lVar11 + 0x10);
    uVar2 = *(uint *)(lVar11 + 0x18);
    if (lVar18 == 0) goto LAB_7fff5fc955b2;
    if (uVar2 < *(uint *)(lVar18 + 0x18)) {
      *(uint *)(lVar11 + 0x18) = uVar2 + 1;
      if (uVar2 < *(uint *)(lVar18 + 0x18)) {
        puVar1 = (undefined4 *)(lVar18 + ((longlong)(int)uVar2 + 2) * 0x10);
        *puVar1 = (int)lVar20;
        puVar1[1] = uVar9;
        puVar1[2] = (int)lVar7;
        puVar1[3] = uVar5;
        goto LAB_7fff5fc94402;
      }
      goto LAB_7fff5fc95644;
    }
    lStack_68 = lVar19;
    uStack_60 = (int)lVar7;
    uStack_5c = uVar5;
    FUN_7fff60aa6a80(lVar11,&lStack_68,
                     *(undefined8 *)(*(longlong *)(*(longlong *)(lVar13 + 0x20) + 0xc0) + 0x70));
  }
  else {
    if (*(longlong *)(self + 0x30) == 0) goto LAB_7fff5fc955b2;
    plVar12 = (longlong *)FUN_7fff5f2550e0(_DAT_7fff62409dd8);
    plVar17 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,2);
    puVar15 = ShopUtil_GetLocalizedMaterialName
                        (materialId,*(undefined **)(self + 0x30),(undefined *)0x0);
    if (plVar17 == (longlong *)0x0) goto LAB_7fff5fc955b2;
    if ((puVar15 != (undefined *)0x0) &&
       (lVar11 = func_0x7fff5f47c7e0(puVar15,*(undefined8 *)(*plVar17 + 0x40)), lVar11 == 0)) {
      uVar14 = func_0x7fff5f47d0b0();
      FUN_7fff5f47d620(uVar14,0);
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
    if ((int)plVar17[3] == 0) goto LAB_7fff5fc95644;
    plVar17[4] = (longlong)puVar15;
    thunk_FUN_7fff5f491fd0();
    if ((*(longlong *)(self + 0x1d0) == 0) ||
       (lVar11 = FUN_7fff60a94f50(*(longlong *)(self + 0x1d0),iVar22,_DAT_7fff62401e80), lVar11 == 0
       )) goto LAB_7fff5fc955b2;
    auStackX_8[0] = *(undefined1 *)(lVar11 + 0x18);
    lVar11 = FUN_7fff60f8f420(auStackX_8,0);
    if ((lVar11 != 0) &&
       (lVar13 = func_0x7fff5f47c7e0(lVar11,*(undefined8 *)(*plVar17 + 0x40)), lVar13 == 0)) {
      uVar14 = func_0x7fff5f47d0b0();
      FUN_7fff5f47d620(uVar14,0);
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
    if (*(uint *)(plVar17 + 3) < 2) goto LAB_7fff5fc95644;
    plVar17[5] = lVar11;
    thunk_FUN_7fff5f491fd0();
    if (plVar12 == (longlong *)0x0) goto LAB_7fff5fc955b2;
    auStack_78[0] =
         (**(code **)(*plVar12 + 0x1a8))(plVar12,plVar17,*(undefined8 *)(*plVar12 + 0x1b0));
    lVar11 = *(longlong *)(self + 0x1b0);
    lVar13 = FUN_7fff60091590(0);
    if ((lVar13 == 0) ||
       (plVar12 = (longlong *)FUN_7fff60091140(auStack_48,lVar13,materialId,0),
       lVar13 = _DAT_7fff6243e9f8, lVar11 == 0)) goto LAB_7fff5fc955b2;
    lVar20 = *plVar12;
    uVar9 = *(undefined4 *)((longlong)plVar12 + 4);
    lVar19 = *plVar12;
    lVar7 = plVar12[1];
    uVar5 = *(undefined4 *)((longlong)plVar12 + 0xc);
    *(int *)(lVar11 + 0x1c) = *(int *)(lVar11 + 0x1c) + 1;
    lVar18 = *(longlong *)(lVar11 + 0x10);
    uVar2 = *(uint *)(lVar11 + 0x18);
    if (lVar18 == 0) goto LAB_7fff5fc955b2;
    if (uVar2 < *(uint *)(lVar18 + 0x18)) {
      *(uint *)(lVar11 + 0x18) = uVar2 + 1;
      if (*(uint *)(lVar18 + 0x18) <= uVar2) goto LAB_7fff5fc95644;
      puVar1 = (undefined4 *)(lVar18 + ((longlong)(int)uVar2 + 2) * 0x10);
      *puVar1 = (int)lVar20;
      puVar1[1] = uVar9;
      puVar1[2] = (int)lVar7;
      puVar1[3] = uVar5;
    }
    else {
      lStack_68 = lVar19;
      uStack_60 = (int)lVar7;
      uStack_5c = uVar5;
      FUN_7fff60aa6a80(lVar11,&lStack_68,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar13 + 0x20) + 0xc0) + 0x70));
    }
    bVar6 = false;
    if (materialId < 0) goto LAB_7fff5fc9489c;
  }
LAB_7fff5fc94402:
  if ((*(longlong *)(self + 0x1d0) == 0) ||
     (lVar11 = FUN_7fff60a94f50(*(longlong *)(self + 0x1d0),iVar22,_DAT_7fff62401e80), lVar11 == 0))
  goto LAB_7fff5fc955b2;
  iVar3 = *(int *)(lVar11 + 0x14);
  lVar11 = *(longlong *)(self + 0xa0);
  iStack_84 = iVar3;
  if (bVar6) {
    if (lVar11 == 0) goto LAB_7fff5fc955b2;
    lVar11 = FUN_7fff618a4a10(lVar11,0);
    iStack_88 = iVar10 + 1;
    uVar14 = FUN_7fff6100e780(&iStack_88,0);
    uVar14 = FUN_7fff60e71970(_DAT_7fff62420200,uVar14,0);
    if (((lVar11 == 0) || (lVar11 = FUN_7fff618c6ee0(lVar11,uVar14,0), lVar11 == 0)) ||
       (lVar11 = FUN_7fff60678610(lVar11,_DAT_7fff6244b3d0), lVar11 == 0)) goto LAB_7fff5fc955b2;
    FUN_7fff5fc309f0(lVar11,1,0);
    func_0x7fff5fc30c60(lVar11,materialId,0);
  }
  else {
    if (lVar11 == 0) goto LAB_7fff5fc955b2;
    lVar11 = FUN_7fff618a4a10(lVar11,0);
    iStack_88 = iVar10 + 1;
    uVar14 = FUN_7fff6100e780(&iStack_88,0);
    uVar14 = FUN_7fff60e71970(_DAT_7fff62420200,uVar14,0);
    if (((lVar11 == 0) || (lVar11 = FUN_7fff618c6ee0(lVar11,uVar14,0), lVar11 == 0)) ||
       (lVar11 = FUN_7fff60678610(lVar11,_DAT_7fff6244b3d0), lVar11 == 0)) goto LAB_7fff5fc955b2;
    FUN_7fff5fc309f0(lVar11,1,0);
    puVar15 = ShopUtil_GetMaterialIconName(materialId,(undefined *)0x0);
    FUN_7fff5fc30f60(lVar11,puVar15,0);
    FUN_7fff5f6d4090(lVar11,auStack_78[0],0);
  }
  if (0 < iVar3) {
    if (*(longlong *)(self + 400) == 0) goto LAB_7fff5fc955b2;
    lVar11 = FUN_7fff5ff8a8a0(*(longlong *)(self + 400),0);
    if (((*(longlong *)(self + 0x1d0) == 0) ||
        (lVar13 = FUN_7fff60a94f50(*(longlong *)(self + 0x1d0),iVar22,_DAT_7fff62401e80),
        lVar13 == 0)) || (lVar11 == 0)) goto LAB_7fff5fc955b2;
    lVar13 = FUN_7fff6007b7b0(lVar11,*(undefined4 *)(lVar13 + 0x10),0);
    lVar11 = *(longlong *)(self + 400);
    if (lVar13 == 0) {
      if (lVar11 == 0) goto LAB_7fff5fc955b2;
      lVar11 = FUN_7fff5ff8a970(lVar11,0);
      if (((*(longlong *)(self + 0x1d0) == 0) ||
          (lVar13 = FUN_7fff60a94f50(*(longlong *)(self + 0x1d0),iVar22,_DAT_7fff62401e80),
          lVar13 == 0)) || (lVar11 == 0)) goto LAB_7fff5fc955b2;
      iVar22 = FUN_7fff5ff1ac40(lVar11,materialId,*(undefined1 *)(lVar13 + 0x18),0);
    }
    else {
      if (lVar11 == 0) goto LAB_7fff5fc955b2;
      lVar11 = FUN_7fff5ff8a8a0(lVar11,0);
      if (((*(longlong *)(self + 0x1d0) == 0) ||
          (lVar13 = FUN_7fff60a94f50(*(longlong *)(self + 0x1d0),iVar22,_DAT_7fff62401e80),
          lVar13 == 0)) || (lVar11 == 0)) goto LAB_7fff5fc955b2;
      iVar22 = FUN_7fff6007b680(lVar11,*(undefined4 *)(lVar13 + 0x10),0);
    }
    uVar14 = _DAT_7fff624209d8;
    if (iVar3 <= iVar22) {
      uVar14 = _DAT_7fff6241c188;
    }
    if (*(longlong *)(self + 0x30) == 0) goto LAB_7fff5fc955b2;
    plVar12 = (longlong *)
              FUN_7fff5f2550e0(_DAT_7fff62409dd8,*(longlong *)(self + 0x30),_DAT_7fff6243fa30);
    if (bVar6) {
      if (*(longlong *)(self + 0x30) == 0) goto LAB_7fff5fc955b2;
      plVar12 = (longlong *)
                FUN_7fff5f2550e0(_DAT_7fff62409dd8,*(longlong *)(self + 0x30),_DAT_7fff62402a00);
    }
    if (*(longlong *)(self + 0xa0) == 0) goto LAB_7fff5fc955b2;
    lVar11 = FUN_7fff618a4a10(*(longlong *)(self + 0xa0),0);
    iStack_88 = iVar10 + 1;
    uVar16 = FUN_7fff6100e780(&iStack_88,0);
    uVar16 = FUN_7fff60e71650(_DAT_7fff62420200,uVar16,_DAT_7fff62455f58,0);
    if ((lVar11 == 0) || (lVar11 = FUN_7fff618c6ee0(lVar11,uVar16,0), lVar11 == 0))
    goto LAB_7fff5fc955b2;
    lVar11 = FUN_7fff60678610(lVar11,_DAT_7fff6244fc80);
    plVar17 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48);
    puVar15 = ShopUtil_IntToCommaString((longlong)iVar22,(undefined *)0x0);
    if (plVar17 == (longlong *)0x0) goto LAB_7fff5fc955b2;
    if ((puVar15 != (undefined *)0x0) &&
       (lVar13 = func_0x7fff5f47c7e0(puVar15,*(undefined8 *)(*plVar17 + 0x40)), lVar13 == 0)) {
      uVar14 = func_0x7fff5f47d0b0();
      FUN_7fff5f47d620(uVar14,0);
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
    if ((int)plVar17[3] == 0) goto LAB_7fff5fc95644;
    plVar17[4] = (longlong)puVar15;
    thunk_FUN_7fff5f491fd0();
    if (plVar12 == (longlong *)0x0) goto LAB_7fff5fc955b2;
    auStack_78[0] =
         (**(code **)(*plVar12 + 0x1a8))(plVar12,plVar17,*(undefined8 *)(*plVar12 + 0x1b0));
    plVar17 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48);
    puVar15 = ShopUtil_IntToCommaString((longlong)iStack_84,(undefined *)0x0);
    if (plVar17 == (longlong *)0x0) goto LAB_7fff5fc955b2;
    if ((puVar15 != (undefined *)0x0) &&
       (lVar13 = func_0x7fff5f47c7e0(puVar15,*(undefined8 *)(*plVar17 + 0x40)), lVar13 == 0)) {
      uVar14 = func_0x7fff5f47d0b0();
      FUN_7fff5f47d620(uVar14,0);
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
    if ((int)plVar17[3] == 0) goto LAB_7fff5fc95644;
    plVar17[4] = (longlong)puVar15;
    thunk_FUN_7fff5f491fd0();
    uVar16 = (**(code **)(*plVar12 + 0x1a8))(plVar12,plVar17,*(undefined8 *)(*plVar12 + 0x1b0));
    uVar14 = FUN_7fff60e71050(auStack_78[0],_DAT_7fff623ffd48,uVar14,uVar16,0);
    if (lVar11 == 0) goto LAB_7fff5fc955b2;
    FUN_7fff5ff0eed0(lVar11,uVar14,0);
  }
LAB_7fff5fc949c2:
  iVar10 = iVar10 + 1;
  if (3 < iVar10) goto LAB_7fff5fc949d0;
  goto LAB_7fff5fc94100;
LAB_7fff5fc949d0:
  if ((*(longlong *)(self + 0x1b0) == 0) || (*(longlong *)(self + 0x130) == 0))
  goto LAB_7fff5fc955b2;
  FUN_7fff618a4510(*(longlong *)(self + 0x130),0 < *(int *)(*(longlong *)(self + 0x1b0) + 0x18),0);
  iStack_80 = 0;
  if ((*(longlong *)(self + 400) == 0) ||
     ((plVar12 = (longlong *)FUN_7fff5ff8ac30(*(longlong *)(self + 400),0),
      plVar12 == (longlong *)0x0 ||
      (lVar11 = (**(code **)(*plVar12 + 0x178))(plVar12,*(undefined8 *)(*plVar12 + 0x180)),
      lVar11 == 0)))) goto LAB_7fff5fc955b2;
  iVar10 = *(int *)(lVar11 + 0x38);
  iStack_84 = iVar10;
  if (*(longlong *)(self + 0xa0) == 0) goto LAB_7fff5fc955b2;
  lVar11 = FUN_7fff618a4a10(*(longlong *)(self + 0xa0),0);
  iStack_88 = 5;
  uVar14 = FUN_7fff6100e780(&iStack_88,0);
  uVar14 = FUN_7fff60e71970(_DAT_7fff62420200,uVar14,0);
  if ((lVar11 == 0) || (lVar11 = FUN_7fff618c6ee0(lVar11,uVar14,0), lVar11 == 0))
  goto LAB_7fff5fc955b2;
  lVar11 = FUN_7fff60678610(lVar11,_DAT_7fff6244b3d0);
  if (*(longlong *)(self + 0xa0) == 0) goto LAB_7fff5fc955b2;
  lVar13 = FUN_7fff618a4a10(*(longlong *)(self + 0xa0),0);
  iStack_88 = 5;
  uVar14 = FUN_7fff6100e780(&iStack_88,0);
  uVar14 = FUN_7fff60e71650(_DAT_7fff62420200,uVar14,_DAT_7fff62455f58,0);
  if ((lVar13 == 0) || (lVar13 = FUN_7fff618c6ee0(lVar13,uVar14,0), lVar13 == 0))
  goto LAB_7fff5fc955b2;
  lVar13 = FUN_7fff60678610(lVar13,_DAT_7fff6244fc80);
  uVar14 = _DAT_7fff624209d8;
  if (-1 < iVar10) {
    uVar14 = _DAT_7fff6241c188;
  }
  if ((((*(longlong *)(self + 0xa0) == 0) ||
       (lVar18 = FUN_7fff618a4a10(*(longlong *)(self + 0xa0),0), lVar18 == 0)) ||
      (lVar18 = FUN_7fff618c6ee0(lVar18,_DAT_7fff62465e58,0), lVar18 == 0)) ||
     (lVar19 = FUN_7fff618c6ee0(lVar18,_DAT_7fff62419458,0), lVar19 == 0)) goto LAB_7fff5fc955b2;
  alStack_58[0] = FUN_7fff60678610(lVar19,_DAT_7fff6244fc80);
  lVar19 = FUN_7fff618c6ee0(lVar18,_DAT_7fff62465d88,0);
  if (lVar19 == 0) goto LAB_7fff5fc955b2;
  lStack_68 = FUN_7fff60678610(lVar19,_DAT_7fff6244b618);
  if (((*(longlong *)(self + 0x150) == 0) ||
      (lVar19 = FUN_7fff60a94f50(*(longlong *)(self + 0x150),*(undefined4 *)(self + 0x160),
                                 _DAT_7fff623fd630), lVar19 == 0)) ||
     ((lVar19 = FUN_7fff6083faa0(lVar19,*(undefined4 *)(self + 0x164),_DAT_7fff62473318),
      lVar19 == 0 || (lVar19 = FUN_7fff60a94f50(lVar19,iStackX_10,_DAT_7fff62450e50), lVar11 == 0)))
     ) goto LAB_7fff5fc955b2;
  if (*(int *)(self + 0x24) < 1) {
    lVar11 = FUN_7fff618a1ae0(lVar11);
    if (lVar11 == 0) goto LAB_7fff5fc955b2;
    FUN_7fff618a4510(lVar11,0,0);
    lVar11 = FUN_7fff618a1ae0(lVar18,0);
    if (((lVar11 == 0) || (FUN_7fff618a4510(lVar11,1,0), lVar13 == 0)) ||
       (lVar11 = FUN_7fff618a1ae0(lVar13,0), lVar11 == 0)) goto LAB_7fff5fc955b2;
    FUN_7fff618a4510(lVar11,0,0);
    if ((*(longlong *)(self + 400) == 0) ||
       (lVar11 = FUN_7fff5ff8ad00(*(longlong *)(self + 400),0), lVar11 == 0)) goto LAB_7fff5fc955b2;
    uVar9 = *(undefined4 *)(lVar11 + 0x20);
    if (*(longlong *)(self + 400) == 0) goto LAB_7fff5fc955b2;
    lVar11 = FUN_7fff5ff8ad00(*(longlong *)(self + 400),0);
    if ((*(longlong *)(self + 400) == 0) ||
       (uVar14 = FUN_7fff5ff8b150(*(longlong *)(self + 400),0), lVar11 == 0)) goto LAB_7fff5fc955b2;
    cVar8 = FUN_7fff5ffaf620(lVar11,uVar14,0);
    if (cVar8 != '\0') {
      if (*(longlong *)(self + 400) == 0) goto LAB_7fff5fc955b2;
      lVar11 = FUN_7fff5ff8ad00(*(longlong *)(self + 400),0);
      if ((*(longlong *)(self + 400) == 0) ||
         (uVar14 = FUN_7fff5ff8b150(*(longlong *)(self + 400),0), lVar11 == 0))
      goto LAB_7fff5fc955b2;
      uVar9 = FUN_7fff5ffaf4f0(lVar11,uVar14,0);
    }
    if ((*(longlong *)(self + 0x148) == 0) ||
       (iVar10 = FUN_7fff5fc97d00(*(longlong *)(self + 0x148),uVar9,0), lVar19 == 0))
    goto LAB_7fff5fc955b2;
    uVar14 = _DAT_7fff624209d8;
    if (*(short *)(lVar19 + 0x1c) <= iVar10) {
      uVar14 = _DAT_7fff6241c188;
    }
    uVar16 = FUN_7fff6100d7f0(lVar19 + 0x16,0);
    if (alStack_58[0] == 0) {
LAB_7fff5fc9561e:
      FUN_7fff5f47d660();
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
    FUN_7fff5ff0eed0(alStack_58[0],uVar16,0);
    plVar12 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,2);
    if (iVar10 < 0) {
      iVar10 = 0;
    }
    auStack_78[0] = CONCAT44(auStack_78[0]._4_4_,iVar10);
    lVar11 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,auStack_78);
    if (plVar12 == (longlong *)0x0) goto LAB_7fff5fc9561e;
    if ((lVar11 != 0) &&
       (lVar13 = func_0x7fff5f47c7e0(lVar11,*(undefined8 *)(*plVar12 + 0x40)), lVar13 == 0)) {
      uVar14 = func_0x7fff5f47d0b0();
      FUN_7fff5f47d620(uVar14,0);
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
    if ((int)plVar12[3] == 0) {
LAB_7fff5fc95618:
      FUN_7fff5f47d650();
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
    plVar12[4] = lVar11;
    thunk_FUN_7fff5f491fd0();
    iStack_88 = 0;
    if (*(ushort *)(lVar19 + 0x1c) < 0x8000) {
      iStack_88 = (int)(short)*(ushort *)(lVar19 + 0x1c);
    }
    uVar16 = FUN_7fff6100e780(&iStack_88,0);
    lVar11 = FUN_7fff60e71970(uVar14,uVar16,0);
    if ((lVar11 != 0) &&
       (lVar13 = func_0x7fff5f47c7e0(lVar11,*(undefined8 *)(*plVar12 + 0x40)), lVar13 == 0)) {
      uVar14 = func_0x7fff5f47d0b0();
      FUN_7fff5f47d620(uVar14,0);
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
    if (*(uint *)(plVar12 + 3) < 2) goto LAB_7fff5fc95618;
    plVar12[5] = lVar11;
    thunk_FUN_7fff5f491fd0();
    if (lStack_68 == 0) goto LAB_7fff5fc9561e;
    FUN_7fff5f55c500(lStack_68,plVar12,0);
    iVar10 = iStack_84;
    iVar22 = iStack_80;
  }
  else {
    lVar20 = FUN_7fff618a1ae0(lVar11);
    if (lVar20 == 0) goto LAB_7fff5fc955b2;
    FUN_7fff618a4510(lVar20,1,0);
    lVar18 = FUN_7fff618a1ae0(lVar18,0);
    if (((lVar18 == 0) || (FUN_7fff618a4510(lVar18,0,0), lVar13 == 0)) ||
       ((lVar18 = FUN_7fff618a1ae0(lVar13,0), lVar18 == 0 ||
        (FUN_7fff618a4510(lVar18,1,0), uVar16 = _DAT_7fff623f8bd8, lVar19 == 0))))
    goto LAB_7fff5fc955b2;
    plVar12 = *(longlong **)(self + 0x30);
    iStack_80 = *(int *)(lVar19 + 0x18);
    if (plVar12 == (longlong *)0x0) goto LAB_7fff5fc955b2;
    lVar18 = func_0x7fff5f47d0d0(*(undefined8 *)
                                  (*plVar12 +
                                  ((ulonglong)*(ushort *)(_DAT_7fff62409dd8 + 0x50) + 0x14) * 0x10))
    ;
    plVar12 = (longlong *)(**(code **)(lVar18 + 8))(plVar12,uVar16,lVar18);
    plVar17 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
    if (plVar17 == (longlong *)0x0) goto LAB_7fff5fc955b2;
    if ((_DAT_7fff623f7f60 != 0) &&
       (lVar18 = func_0x7fff5f47c7e0(_DAT_7fff623f7f60,*(undefined8 *)(*plVar17 + 0x40)),
       lVar18 == 0)) {
      uVar14 = func_0x7fff5f47d0b0();
      FUN_7fff5f47d620(uVar14,0);
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
    if ((int)plVar17[3] == 0) goto LAB_7fff5fc95644;
    plVar17[4] = _DAT_7fff623f7f60;
    thunk_FUN_7fff5f491fd0();
    if (plVar12 == (longlong *)0x0) goto LAB_7fff5fc955b2;
    uVar16 = (**(code **)(*plVar12 + 0x1a8))(plVar12,plVar17,*(undefined8 *)(*plVar12 + 0x1b0));
    FUN_7fff5f6d4090(lVar11,uVar16,0);
    FUN_7fff5fc309f0(lVar11,1,0);
    FUN_7fff5fc30f60(lVar11,_DAT_7fff62411b58,0);
    iVar10 = iStack_84;
    puVar15 = ShopUtil_IntToSpinaString((longlong)iStack_84,(undefined *)0x0);
    iVar22 = iStack_80;
    puVar21 = ShopUtil_IntToSpinaString((longlong)iStack_80,(undefined *)0x0);
    uVar14 = FUN_7fff60e71050(puVar15,_DAT_7fff623ffd48,uVar14,puVar21,0);
    FUN_7fff5ff0eed0(lVar13,uVar14,0);
  }
  lVar11 = *(longlong *)(self + 0x110);
  if (*(char *)(lVar19 + 0x27) == '\0') {
    if ((lVar11 == 0) || (lVar11 = FUN_7fff618a1ae0(lVar11,0), lVar11 == 0)) goto LAB_7fff5fc955b2;
    FUN_7fff618a4510(lVar11,1,0);
    if ((*(longlong *)(self + 0xb8) == 0) ||
       (lVar11 = FUN_7fff618a1ae0(*(longlong *)(self + 0xb8),0), lVar11 == 0))
    goto LAB_7fff5fc955b2;
    FUN_7fff618a4510(lVar11,0,0);
  }
  else {
    if ((lVar11 == 0) || (lVar11 = FUN_7fff618a1ae0(lVar11,0), lVar11 == 0)) goto LAB_7fff5fc955b2;
    FUN_7fff618a4510(lVar11,0,0);
    if ((*(longlong *)(self + 0xb8) == 0) ||
       (lVar11 = FUN_7fff618a1ae0(*(longlong *)(self + 0xb8),0), lVar11 == 0))
    goto LAB_7fff5fc955b2;
    FUN_7fff618a4510(lVar11,1,0);
    lVar11 = *(longlong *)(self + 0xb8);
    cVar8 = (**(code **)(*(longlong *)self + 0x248))
                      (self,*(undefined8 *)(self + 0x1d0),iStackX_10 * 4,4,lVar19,
                       *(undefined8 *)(*(longlong *)self + 0x250));
    if (lVar11 == 0) goto LAB_7fff5fc955b2;
    FUN_7fff5f502150(lVar11,cVar8 != '\0' && iVar22 <= iVar10,0);
  }
  if (*(longlong *)(self + 0xb8) == 0) goto LAB_7fff5fc955b2;
  cVar8 = FUN_7fff5f5020c0(*(longlong *)(self + 0xb8),0);
  lVar11 = *(longlong *)(self + 0x138);
  if (cVar8 == '\0') {
    if (lVar11 == 0) goto LAB_7fff5fc955b2;
    if (*(int *)(lVar11 + 0x18) == 0) goto LAB_7fff5fc95644;
    if (*(longlong *)(lVar11 + 0x20) == 0) goto LAB_7fff5fc955b2;
    FUN_7fff618a4510(*(longlong *)(lVar11 + 0x20),0,0);
    lVar11 = *(longlong *)(self + 0x138);
    if (lVar11 == 0) goto LAB_7fff5fc955b2;
    if (*(uint *)(lVar11 + 0x18) < 2) goto LAB_7fff5fc95644;
    if (*(longlong *)(lVar11 + 0x28) == 0) goto LAB_7fff5fc955b2;
    FUN_7fff618a4510(*(longlong *)(lVar11 + 0x28),0,0);
  }
  else {
    if (lVar11 == 0) goto LAB_7fff5fc955b2;
    if (*(int *)(lVar11 + 0x18) == 0) goto LAB_7fff5fc95644;
    if (*(longlong *)(lVar11 + 0x20) == 0) goto LAB_7fff5fc955b2;
    cVar8 = FUN_7fff618a4950(*(longlong *)(lVar11 + 0x20),0);
    if (cVar8 == '\0') {
      lVar11 = *(longlong *)(self + 0x138);
      if (lVar11 == 0) goto LAB_7fff5fc955b2;
      if (*(int *)(lVar11 + 0x18) == 0) goto LAB_7fff5fc95644;
      if (*(longlong *)(lVar11 + 0x20) == 0) goto LAB_7fff5fc955b2;
      FUN_7fff618a4510(*(longlong *)(lVar11 + 0x20),1,0);
      lVar11 = *(longlong *)(self + 0x138);
      if (lVar11 == 0) goto LAB_7fff5fc955b2;
      if (*(uint *)(lVar11 + 0x18) < 2) goto LAB_7fff5fc95644;
      if (*(longlong *)(lVar11 + 0x28) == 0) goto LAB_7fff5fc955b2;
      FUN_7fff618a4510(*(longlong *)(lVar11 + 0x28),1,0);
      lVar11 = *(longlong *)(self + 0x138);
      if (lVar11 == 0) goto LAB_7fff5fc955b2;
      if (*(int *)(lVar11 + 0x18) == 0) goto LAB_7fff5fc95644;
      if (((*(longlong *)(lVar11 + 0x20) == 0) ||
          (lVar11 = FUN_7fff606a6750(*(longlong *)(lVar11 + 0x20),_DAT_7fff6246d2c8), lVar11 == 0))
         || (lVar11 = *(longlong *)(lVar11 + 0x48), lVar11 == 0)) goto LAB_7fff5fc955b2;
      if (*(int *)(lVar11 + 0x18) < 1) {
        uVar14 = func_0x7fff5f44ff00(_DAT_7fff62442b48);
        FUN_7fff5f4f6880(uVar14,self,_DAT_7fff62473c38,0);
        if (*(int *)(_DAT_7fff624027e8 + 0xe0) == 0) {
          func_0x7fff5f47d6f0();
        }
        FUN_7fff5f50fd80(lVar11,uVar14,0);
      }
      lVar11 = *(longlong *)(self + 0x138);
      if (lVar11 == 0) goto LAB_7fff5fc955b2;
      if (*(uint *)(lVar11 + 0x18) < 2) goto LAB_7fff5fc95644;
      if (((*(longlong *)(lVar11 + 0x28) == 0) ||
          (lVar11 = FUN_7fff606a6750(*(longlong *)(lVar11 + 0x28),_DAT_7fff6246d2c8), lVar11 == 0))
         || (lVar11 = *(longlong *)(lVar11 + 0x48), lVar11 == 0)) goto LAB_7fff5fc955b2;
      if (*(int *)(lVar11 + 0x18) < 1) {
        uVar14 = func_0x7fff5f44ff00(_DAT_7fff62442b48);
        FUN_7fff5f4f6880(uVar14,self,_DAT_7fff62473d00,0);
        if (*(int *)(_DAT_7fff624027e8 + 0xe0) == 0) {
          func_0x7fff5f47d6f0();
        }
        FUN_7fff5f50fd80(lVar11,uVar14,0);
      }
    }
  }
  uVar9 = *(undefined4 *)(lVar19 + 0x20);
  lVar11 = FUN_7fff60c4bc00(_DAT_7fff6245a5f8);
  if (lVar11 != 0) {
    puVar15 = (undefined *)FUN_7fff600847d0(lVar11,uVar9,0);
    lVar11 = *(longlong *)(self + 0x100);
    if (*(int *)(self + 0x24) < 0) {
      puVar21 = ShopUtil_GetManufactureItemText
                          (puVar15,*(undefined **)(self + 0x30),*(undefined **)(self + 0x38),
                           *(undefined **)(self + 0x140),(undefined *)0x0);
    }
    else {
      puVar21 = ShopUtil_GetItemPropertyText
                          (puVar15,*(undefined **)(self + 0x30),*(undefined **)(self + 0x38),
                           *(undefined **)(self + 0x140),(undefined *)0x0);
    }
    if (lVar11 != 0) {
      FUN_7fff5ff0eed0(lVar11,puVar21,0);
      if (-1 < *(int *)(self + 0x24)) {
        return;
      }
      if (puVar15 != (undefined *)0x0) {
        auStackX_20[0] = *(undefined2 *)(puVar15 + 0x4c);
        uVar14 = FUN_7fff6100d7f0(auStackX_20,0);
        lVar13 = FUN_7fff60e71650(_DAT_7fff62415de0,uVar14,_DAT_7fff624191d8,0);
        uVar14 = _DAT_7fff623f6820;
        lVar11 = *(longlong *)(self + 0x100);
        if (lVar11 != 0) {
          plVar12 = *(longlong **)(self + 0x30);
          uVar16 = *(undefined8 *)(lVar11 + 0x118);
          if (plVar12 != (longlong *)0x0) {
            lVar18 = func_0x7fff5f47d0d0(*(undefined8 *)
                                          (*plVar12 +
                                          ((ulonglong)*(ushort *)(_DAT_7fff62409dd8 + 0x50) + 0x14)
                                          * 0x10));
            plVar12 = (longlong *)(**(code **)(lVar18 + 8))(plVar12,uVar14,lVar18);
            plVar17 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
            if (plVar17 != (longlong *)0x0) {
              if ((lVar13 != 0) &&
                 (lVar18 = func_0x7fff5f47c7e0(lVar13,*(undefined8 *)(*plVar17 + 0x40)), lVar18 == 0
                 )) {
                uVar14 = func_0x7fff5f47d0b0();
                FUN_7fff5f47d620(uVar14,0);
                pcVar4 = (code *)swi(3);
                (*pcVar4)();
                return;
              }
              if ((int)plVar17[3] == 0) {
LAB_7fff5fc95644:
                FUN_7fff5f47d650();
                pcVar4 = (code *)swi(3);
                (*pcVar4)();
                return;
              }
              plVar17[4] = lVar13;
              thunk_FUN_7fff5f491fd0();
              if (plVar12 != (longlong *)0x0) {
                uVar14 = (**(code **)(*plVar12 + 0x1a8))
                                   (plVar12,plVar17,*(undefined8 *)(*plVar12 + 0x1b0));
                uVar14 = FUN_7fff60e71970(uVar16,uVar14,0);
                FUN_7fff5ff0eed0(lVar11,uVar14,0);
                return;
              }
            }
          }
        }
      }
    }
  }
LAB_7fff5fc955b2:
  FUN_7fff5f47d660();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

