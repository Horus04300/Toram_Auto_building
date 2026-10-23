
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
  
  if (DAT_7ffe9cadbb14 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c948908);
    FUN_7ffe9996d590(&DAT_7ffe9c9540a0);
    FUN_7ffe9996d590(&DAT_7ffe9c91ef20);
    FUN_7ffe9996d590(&DAT_7ffe9c9590b8);
    FUN_7ffe9996d590(&DAT_7ffe9c8ee100);
    FUN_7ffe9996d590(&DAT_7ffe9c8f3b08);
    FUN_7ffe9996d590(&DAT_7ffe9c8f7318);
    FUN_7ffe9996d590(&DAT_7ffe9c920640);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1820);
    DAT_7ffe9cadbb14 = '\x01';
  }
  iVar14 = 0;
  iVar12 = 0;
  uVar13 = 0;
  puVar11 = _DAT_7ffe9c8f1820;
  puVar8 = _DAT_7ffe9c8f1820;
  do {
    iVar5 = iVar12 + -1;
    if (iVar12 < 1) {
      iVar5 = iVar12;
    }
    if (capId == (undefined *)0x0) goto LAB_7ffe99ec555b;
    if (*(uint *)(capId + 0x18) <= uVar13) goto LAB_7ffe99ec5561;
    sVar1 = *(short *)(capId + (longlong)(int)uVar13 * 2 + 0x20);
    lVar7 = (longlong)(int)uVar13 * 2 + 0x20;
    if (0 < sVar1) {
      if (*(int *)(_DAT_7ffe9c948908 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      bVar4 = BonusManager_CheckEquipLimitBonusId(sVar1,(undefined *)0x0);
      if (bVar4 == 0) {
        if (*(uint *)(capId + 0x18) <= uVar13) {
LAB_7ffe99ec5561:
          FUN_7ffe9996d790();
          pcVar3 = (code *)swi(3);
          puVar11 = (undefined *)(*pcVar3)();
          return puVar11;
        }
        sVar1 = *(short *)(capId + lVar7);
        if (capVal == (undefined *)0x0) goto LAB_7ffe99ec555b;
        if (*(uint *)(capVal + 0x18) <= uVar13) goto LAB_7ffe99ec5561;
        sVar2 = *(short *)(capVal + lVar7);
        if (*(int *)(_DAT_7ffe9c8ee100 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        puVar6 = UIItemProperty_AddCapProperty
                           (iVar12 < 1,sVar1,sVar2,itemPropertyTextManager,systemManager,
                            (undefined *)0x0);
        if (iVar12 < 1) {
          iVar14 = iVar14 + 0x10;
        }
        else if (iVar5 == 0) {
          if (puVar11 == (undefined *)0x0) goto LAB_7ffe99ec555b;
          iVar5 = 0;
          if (0 < *(int *)(puVar11 + 0x10)) {
            if (puVar6 == (undefined *)0x0) goto LAB_7ffe99ec555b;
            if (widthWord + iVar14 < *(int *)(puVar11 + 0x10) + *(int *)(puVar6 + 0x10)) {
              lVar7 = func_0x7ffe9996c990(_DAT_7ffe9c91ef20,5);
              if (lVar7 != 0) {
                if (*(int *)(lVar7 + 0x18) == 0) goto LAB_7ffe99ec5561;
                *(undefined **)(lVar7 + 0x20) = puVar8;
                il2cpp_write_barrier_0();
                if (*(uint *)(lVar7 + 0x18) < 2) goto LAB_7ffe99ec5561;
                *(undefined **)(lVar7 + 0x28) = puVar11;
                il2cpp_write_barrier_0();
                if (*(uint *)(lVar7 + 0x18) < 3) goto LAB_7ffe99ec5561;
                *(undefined8 *)(lVar7 + 0x30) = _DAT_7ffe9c8f3b08;
                il2cpp_write_barrier_0();
                if (*(uint *)(lVar7 + 0x18) < 4) goto LAB_7ffe99ec5561;
                *(undefined **)(lVar7 + 0x38) = puVar6;
                il2cpp_write_barrier_0();
                if (*(uint *)(lVar7 + 0x18) < 5) goto LAB_7ffe99ec5561;
                *(undefined8 *)(lVar7 + 0x40) = _DAT_7ffe9c920640;
                il2cpp_write_barrier_0();
                puVar8 = (undefined *)FUN_7ffe9b366f30(lVar7);
                puVar11 = _DAT_7ffe9c8f1820;
                iVar14 = 0;
                goto LAB_7ffe99ec5513;
              }
              goto LAB_7ffe99ec555b;
            }
          }
          puVar8 = (undefined *)FUN_7ffe9b366c90(puVar8,puVar11,puVar6,_DAT_7ffe9c920640,0);
          puVar11 = _DAT_7ffe9c8f1820;
          iVar14 = 0;
          goto LAB_7ffe99ec5513;
        }
        if ((puVar11 == (undefined *)0x0) || (puVar6 == (undefined *)0x0)) goto LAB_7ffe99ec555b;
        if (widthWord + iVar14 < *(int *)(puVar6 + 0x10) + *(int *)(puVar11 + 0x10)) {
          if (*(int *)(puVar11 + 0x10) < 1) {
            puVar8 = (undefined *)FUN_7ffe9b367290(puVar8,puVar6,_DAT_7ffe9c8f3b08,0);
            puVar11 = _DAT_7ffe9c8f1820;
            iVar14 = 0;
            goto LAB_7ffe99ec5513;
          }
          puVar8 = (undefined *)FUN_7ffe9b367290(puVar8,puVar11,_DAT_7ffe9c8f3b08,0);
          iVar14 = 0x10;
          puVar11 = _DAT_7ffe9c8f1820;
        }
        puVar11 = (undefined *)FUN_7ffe9b367290(puVar11,puVar6,_DAT_7ffe9c8f7318,0);
      }
      else {
        if (puVar11 == (undefined *)0x0) goto LAB_7ffe99ec555b;
        if (0 < *(int *)(puVar11 + 0x10)) {
          puVar8 = (undefined *)FUN_7ffe9b367290(puVar8,puVar11,_DAT_7ffe9c8f3b08,0);
        }
        puVar11 = (undefined *)**(undefined8 **)(_DAT_7ffe9c9590b8 + 0xb8);
        lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c9540a0);
        if ((lVar9 == 0) || (*(longlong *)(lVar9 + 0x28) == 0)) goto LAB_7ffe99ec555b;
        uVar10 = FUN_7ffe99a873c0(*(longlong *)(lVar9 + 0x28),0);
        if (*(uint *)(capId + 0x18) <= uVar13) goto LAB_7ffe99ec5561;
        sVar1 = *(short *)(capId + lVar7);
        if (capVal == (undefined *)0x0) goto LAB_7ffe99ec555b;
        if (*(uint *)(capVal + 0x18) <= uVar13) goto LAB_7ffe99ec5561;
        sVar2 = *(short *)(capVal + lVar7);
        if (*(int *)(_DAT_7ffe9c8ee100 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        puVar6 = UIItemProperty_AddCapProperty
                           (0,sVar1,sVar2,itemPropertyTextManager,systemManager,(undefined *)0x0);
        puVar8 = (undefined *)FUN_7ffe9b366c90(puVar8,uVar10,puVar6,_DAT_7ffe9c8f3b08,0);
        if (*(uint *)(capVal + 0x18) <= uVar13) goto LAB_7ffe99ec5561;
        iVar5 = (int)*(short *)(capVal + lVar7);
        iVar14 = 0;
      }
    }
LAB_7ffe99ec5513:
    iVar12 = iVar5;
    uVar13 = uVar13 + 1;
  } while ((int)uVar13 < 10);
  if (puVar11 != (undefined *)0x0) {
    if (0 < *(int *)(puVar11 + 0x10)) {
      puVar8 = (undefined *)FUN_7ffe9b367290(puVar8,puVar11,_DAT_7ffe9c8f3b08,0);
    }
    return puVar8;
  }
LAB_7ffe99ec555b:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  puVar11 = (undefined *)(*pcVar3)();
  return puVar11;
}

