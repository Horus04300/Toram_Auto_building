
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
ShopUtil_GetManufactureItemPropertyText
          (undefined *itemData,undefined *systemTextManager,undefined *itemTextManager,
          undefined *itemPropertyTextManager,undefined *methodInfo)

{
  undefined4 uVar1;
  code *pcVar2;
  longlong lVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong lVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  undefined *puVar12;
  bool bVar13;
  undefined1 auStackX_8 [8];
  undefined2 auStack_38 [2];
  undefined2 auStack_34 [2];
  undefined2 auStack_30 [2];
  undefined2 auStack_2c [2];
  
  if (DAT_7fff625e41ed == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62454290);
    FUN_7fff5f47d450(&DAT_7fff62453138);
    FUN_7fff5f47d450(&DAT_7fff62411ec0);
    FUN_7fff5f47d450(&DAT_7fff6245a5f8);
    FUN_7fff5f47d450(&DAT_7fff623fa248);
    FUN_7fff5f47d450(&DAT_7fff624385d8);
    FUN_7fff5f47d450(&DAT_7fff624389a8);
    FUN_7fff5f47d450(&DAT_7fff6243ac20);
    FUN_7fff5f47d450(&DAT_7fff62439090);
    FUN_7fff5f47d450(&DAT_7fff623fa318);
    FUN_7fff5f47d450(&DAT_7fff623f7f60);
    FUN_7fff5f47d450(&DAT_7fff62438fc8);
    FUN_7fff5f47d450(&DAT_7fff62438f08);
    DAT_7fff625e41ed = '\x01';
  }
  lVar3 = FUN_7fff60c4bc00(_DAT_7fff6245a5f8);
  if ((itemData != (undefined *)0x0) && (lVar3 != 0)) {
    lVar3 = FUN_7fff600847d0(lVar3,*(undefined4 *)(itemData + 0x28),0);
    uVar1 = *(undefined4 *)(itemData + 0x28);
    if (itemTextManager == (undefined *)0x0) goto LAB_7fff5fc6c4d4;
    lVar4 = func_0x7fff5f47d0d0(*(undefined8 *)
                                 (*(longlong *)itemTextManager +
                                 ((ulonglong)*(ushort *)(_DAT_7fff62411ec0 + 0x50) + 0x14) * 0x10));
    plVar5 = (longlong *)(**(code **)(lVar4 + 8))(itemTextManager,uVar1,lVar4);
    if (plVar5 == (longlong *)0x0) goto LAB_7fff5fc6c4d4;
    lVar4 = (**(code **)(*plVar5 + 0x198))(plVar5,*(undefined8 *)(*plVar5 + 0x1a0));
    uVar1 = *(undefined4 *)(itemData + 0x28);
    if (DAT_7fff625e41f0 == '\0') {
      FUN_7fff5f47d450(&DAT_7fff6245a5f8);
      DAT_7fff625e41f0 = '\x01';
    }
    lVar6 = FUN_7fff60c4bc00(_DAT_7fff6245a5f8);
    if ((lVar6 == 0) ||
       (lVar6 = FUN_7fff600847d0(lVar6,uVar1,0), uVar10 = _DAT_7fff623f7f60, lVar6 == 0))
    goto LAB_7fff5fc6c4d4;
    if ((ushort)(*(short *)(lVar6 + 0x30) - 7U) < 0xd) {
      bVar13 = *(short *)(lVar6 + 0x30) != 0x11;
      if (bVar13) {
        if (systemTextManager == (undefined *)0x0) {
LAB_7fff5fc6c4ce:
          FUN_7fff5f47d660();
          pcVar2 = (code *)swi(3);
          puVar12 = (undefined *)(*pcVar2)();
          return puVar12;
        }
        uVar7 = FUN_7fff5f568150(systemTextManager,_DAT_7fff624385d8,0);
        auStack_38[0] = *(undefined2 *)(itemData + 0x30);
        uVar8 = FUN_7fff6100d7f0(auStack_38,0);
        uVar8 = FUN_7fff60e71970(_DAT_7fff6243ac20,uVar8,0);
        uVar8 = FUN_7fff5f568150(systemTextManager,uVar8,0);
        auStack_30[0] = *(undefined2 *)(itemData + 0x3e);
        uVar9 = func_0x7fff5f47c7a0(_DAT_7fff62453138,auStack_30);
        if (lVar3 == 0) goto LAB_7fff5fc6c4ce;
        auStackX_8[0] = *(undefined1 *)(lVar3 + 0x40);
        uVar11 = func_0x7fff5f47c7a0(_DAT_7fff62454290,auStackX_8);
        uVar7 = FUN_7fff60e749c0(uVar7,uVar8,uVar9,uVar11,0);
        uVar10 = FUN_7fff60e71970(uVar10,uVar7,0);
        goto LAB_7fff5fc6c3ee;
      }
    }
    else {
      bVar13 = false;
    }
    if (systemTextManager == (undefined *)0x0) {
      FUN_7fff5f47d660();
      pcVar2 = (code *)swi(3);
      puVar12 = (undefined *)(*pcVar2)();
      return puVar12;
    }
    uVar7 = FUN_7fff5f568150(systemTextManager,_DAT_7fff62439090,0);
    auStack_38[0] = *(undefined2 *)(itemData + 0x30);
    uVar8 = FUN_7fff6100d7f0(auStack_38,0);
    uVar8 = FUN_7fff60e71970(_DAT_7fff6243ac20,uVar8,0);
    uVar8 = FUN_7fff5f568150(systemTextManager,uVar8,0);
    auStack_34[0] = *(undefined2 *)(itemData + 0x3e);
    uVar9 = func_0x7fff5f47c7a0(_DAT_7fff62453138,auStack_34);
    uVar7 = FUN_7fff60e74db0(uVar7,uVar8,uVar9,0);
    uVar10 = FUN_7fff60e71970(uVar10,uVar7,0);
    if (lVar3 != 0) {
LAB_7fff5fc6c3ee:
      if ((*(byte *)(lVar3 + 0x44) & 1) != 0) {
        uVar7 = FUN_7fff5f568150(systemTextManager,_DAT_7fff624389a8,0);
        uVar10 = FUN_7fff60e71970(uVar10,uVar7,0);
        uVar10 = FUN_7fff60e71970(uVar10,_DAT_7fff623fa248,0);
      }
      if ((lVar4 != 0) && (0 < *(int *)(lVar4 + 0x10))) {
        uVar10 = FUN_7fff60e71650(uVar10,lVar4,_DAT_7fff623fa318,0);
      }
      uVar7 = _DAT_7fff62438fc8;
      if (bVar13) {
        uVar7 = _DAT_7fff62438f08;
      }
      uVar7 = FUN_7fff5f568150(systemTextManager,uVar7,0);
      auStack_2c[0] = *(undefined2 *)(lVar3 + 0x3e);
      uVar8 = func_0x7fff5f47c7a0(_DAT_7fff62453138,auStack_2c);
      uVar7 = FUN_7fff60e74b00(uVar7,uVar8,0);
      puVar12 = (undefined *)FUN_7fff60e71970(uVar10,uVar7,0);
      return puVar12;
    }
  }
LAB_7fff5fc6c4d4:
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  puVar12 = (undefined *)(*pcVar2)();
  return puVar12;
}

