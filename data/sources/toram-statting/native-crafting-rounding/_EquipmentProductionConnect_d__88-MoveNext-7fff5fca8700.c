
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte _EquipmentProductionConnect_d__88_MoveNext(undefined *self,undefined *methodInfo)

{
  uint uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined *self_00;
  longlong *plVar4;
  code *pcVar5;
  char cVar6;
  byte bVar7;
  int iVar8;
  longlong lVar9;
  undefined *puVar10;
  undefined *message;
  undefined *buttonCallback;
  undefined8 uVar11;
  longlong lVar12;
  undefined8 *puVar13;
  undefined8 uVar14;
  short asStackX_8 [4];
  undefined8 in_stack_ffffffffffffff88;
  undefined *control;
  undefined4 uVar15;
  undefined8 uStack_58;
  undefined4 uStack_50;
  undefined1 auStack_48 [32];
  
  uVar15 = (undefined4)((ulonglong)in_stack_ffffffffffffff88 >> 0x20);
  if (DAT_7fff625e42b6 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62436790);
    FUN_7fff5f47d450(&DAT_7fff62473318);
    FUN_7fff5f47d450(&DAT_7fff6242b7f8);
    FUN_7fff5f47d450(&DAT_7fff62450e50);
    FUN_7fff5f47d450(&DAT_7fff623fd630);
    FUN_7fff5f47d450(&DAT_7fff62459938);
    FUN_7fff5f47d450(&DAT_7fff6245bc40);
    FUN_7fff5f47d450(&DAT_7fff62458e78);
    FUN_7fff5f47d450(&DAT_7fff6245d9b0);
    FUN_7fff5f47d450(&DAT_7fff62473aa0);
    FUN_7fff5f47d450(&DAT_7fff62406568);
    FUN_7fff5f47d450(&DAT_7fff623fdfc8);
    DAT_7fff625e42b6 = '\x01';
  }
  iVar8 = *(int *)(self + 0x10);
  self_00 = *(undefined **)(self + 0x20);
  asStackX_8[0] = 0;
  if (iVar8 == 0) {
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (self_00 == (undefined *)0x0) goto LAB_7fff5fca8ea1;
    if (*(int *)(self_00 + 0x24) < 0) {
      lVar9 = FUN_7fff60c4bc00(_DAT_7fff62459938);
      if ((((*(longlong *)(self_00 + 0x150) == 0) ||
           (lVar12 = FUN_7fff60a94f50(*(longlong *)(self_00 + 0x150),
                                      *(undefined4 *)(self_00 + 0x160),_DAT_7fff623fd630),
           lVar12 == 0)) ||
          (lVar12 = FUN_7fff6083faa0(lVar12,*(undefined4 *)(self_00 + 0x164),_DAT_7fff62473318),
          lVar12 == 0)) ||
         (lVar12 = FUN_7fff60a94f50(lVar12,*(undefined4 *)(self_00 + 0x168),_DAT_7fff62450e50),
         lVar12 == 0)) goto LAB_7fff5fca8ea1;
      uVar15 = *(undefined4 *)(lVar12 + 0x10);
      uVar11 = func_0x7fff5f44ff00(_DAT_7fff6242b7f8);
      FUN_7fff5fc80480(uVar11,self_00,uVar15,0);
    }
    else {
      lVar9 = FUN_7fff60c4bc00(_DAT_7fff62459938);
      uVar2 = *(undefined4 *)(self_00 + 0x24);
      if ((*(longlong *)(self_00 + 400) == 0) ||
         (lVar12 = FUN_7fff5ff8b500(*(longlong *)(self_00 + 400),0), lVar12 == 0))
      goto LAB_7fff5fca8ea1;
      puVar13 = (undefined8 *)FUN_7fff618c8890(auStack_48,lVar12,0);
      uStack_58 = *puVar13;
      uStack_50 = *(undefined4 *)(puVar13 + 1);
      uVar14 = FUN_7fff5f58c830(&uStack_58,0);
      if (((*(longlong *)(self_00 + 0x150) == 0) ||
          ((lVar12 = FUN_7fff60a94f50(*(longlong *)(self_00 + 0x150),
                                      *(undefined4 *)(self_00 + 0x160),_DAT_7fff623fd630),
           lVar12 == 0 ||
           (lVar12 = FUN_7fff6083faa0(lVar12,*(undefined4 *)(self_00 + 0x164),_DAT_7fff62473318),
           lVar12 == 0)))) ||
         (lVar12 = FUN_7fff60a94f50(lVar12,*(undefined4 *)(self_00 + 0x168),_DAT_7fff62450e50),
         lVar12 == 0)) goto LAB_7fff5fca8ea1;
      uVar3 = *(undefined4 *)(lVar12 + 0x10);
      uVar11 = func_0x7fff5f44ff00(_DAT_7fff6242b7f8);
      FUN_7fff5fc80410(uVar11,self_00,uVar2,uVar14,CONCAT44(uVar15,uVar3),0);
    }
    if (lVar9 != 0) {
      FUN_7fff603cf040(lVar9,uVar11,0);
      uVar15 = *(undefined4 *)(self_00 + 0x48);
      uVar11 = func_0x7fff5f44ff00(_DAT_7fff62406568);
      FUN_7fff618b74f0(uVar11,uVar15,0);
      *(undefined8 *)(self + 0x18) = uVar11;
      thunk_FUN_7fff5f491fd0();
      *(undefined4 *)(self + 0x10) = 1;
      return 1;
    }
    goto LAB_7fff5fca8ea1;
  }
  if ((iVar8 == 1) || (iVar8 == 2)) {
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    lVar9 = FUN_7fff60c4bc00(_DAT_7fff6245bc40);
    if (lVar9 == 0) goto LAB_7fff5fca8ea1;
    cVar6 = FUN_7fff605f04d0(lVar9,0x97,6,0);
    if (cVar6 != '\0') {
      *(undefined8 *)(self + 0x18) = 0;
      thunk_FUN_7fff5f491fd0();
      *(undefined4 *)(self + 0x10) = 2;
      return 1;
    }
    lVar9 = FUN_7fff60c4bc00(_DAT_7fff6245bc40);
    if (lVar9 == 0) goto LAB_7fff5fca8ea1;
    cVar6 = FUN_7fff605f2300(lVar9,0x97,6,asStackX_8,0);
    if (cVar6 == '\0') {
      if (self_00 != (undefined *)0x0) {
        self_00[0x1e0] = 0;
        return 0;
      }
      goto LAB_7fff5fca8ea1;
    }
    *(int *)(self + 0x34) = (int)asStackX_8[0];
    lVar9 = FUN_7fff60c4bc00(_DAT_7fff62458e78);
    if (lVar9 == 0) goto LAB_7fff5fca8ea1;
    iVar8 = FUN_7fff6037cb10(lVar9,0);
    if ((iVar8 == 5) && (*(int *)(self + 0x34) == 0x189)) {
      if ((self_00 == (undefined *)0x0) ||
         ((*(longlong *)(self_00 + 400) == 0 ||
          (lVar9 = FUN_7fff5ff8a490(*(longlong *)(self_00 + 400),0), lVar9 == 0))))
      goto LAB_7fff5fca8ea1;
      FUN_7fff6004e810(lVar9,0);
      goto LAB_7fff5fca89f0;
    }
  }
  else {
    if (iVar8 != 3) {
      if (iVar8 != 4) {
        return 0;
      }
      *(undefined4 *)(self + 0x10) = 0xffffffff;
      if (((*(longlong *)(self + 0x28) != 0) &&
          (FUN_7fff604c26c0(*(longlong *)(self + 0x28),*(undefined4 *)(self + 0x30),0),
          self_00 != (undefined *)0x0)) && (*(longlong *)(self_00 + 0x118) != 0)) {
        FUN_7fff618a4510(*(longlong *)(self_00 + 0x118),0,0);
        if (*(longlong *)(self_00 + 0x58) != 0) {
          plVar4 = *(longlong **)(self_00 + 0x28);
          if (plVar4 == (longlong *)0x0) goto LAB_7fff5fca8ea1;
          (**(code **)(*plVar4 + 0x188))(plVar4,*(undefined8 *)(*plVar4 + 400));
        }
        if (*(longlong *)(self_00 + 0x60) != 0) {
          plVar4 = *(longlong **)(self_00 + 0x28);
          if (plVar4 == (longlong *)0x0) goto LAB_7fff5fca8ea1;
          (**(code **)(*plVar4 + 0x188))(plVar4,*(undefined8 *)(*plVar4 + 400));
        }
        FUN_7fff5fc754e0(self_00,0);
        self_00[0x1e0] = 0;
        return 0;
      }
      goto LAB_7fff5fca8ea1;
    }
    *(undefined4 *)(self + 0x10) = 0xffffffff;
LAB_7fff5fca89f0:
    lVar9 = FUN_7fff60c4bc00(_DAT_7fff6245bc40);
    if (lVar9 == 0) goto LAB_7fff5fca8ea1;
    cVar6 = FUN_7fff605f04d0(lVar9,0x4c,0x70);
    if (cVar6 != '\0') {
      *(undefined8 *)(self + 0x18) = 0;
      thunk_FUN_7fff5f491fd0();
      *(undefined4 *)(self + 0x10) = 3;
      return 1;
    }
    if (self_00 == (undefined *)0x0) goto LAB_7fff5fca8ea1;
    if (-1 < *(int *)(self_00 + 0x24)) {
      puVar10 = SmithManufacture_EquipmentProductionConnect
                          (self_00,*(undefined **)(self + 0x28),*(int *)(self + 0x30),
                           (undefined *)0x0);
      FUN_7fff618a87c0(self_00,puVar10,0);
      return 0;
    }
  }
  lVar9 = FUN_7fff60c4bc00(_DAT_7fff6245d9b0);
  if ((lVar9 == 0) || (lVar9 = FUN_7fff5fda8f10(lVar9,0), lVar9 == 0)) goto LAB_7fff5fca8ea1;
  FUN_7fff5f7f5bb0(lVar9,0,0);
  if (*(int *)(self + 0x34) == 0x73) {
    lVar9 = FUN_7fff60c4bc00(_DAT_7fff62458e78);
    if (lVar9 == 0) goto LAB_7fff5fca8ea1;
    iVar8 = FUN_7fff6037cb10(lVar9,0);
    if (iVar8 != 5) goto LAB_7fff5fca8b71;
    if ((self_00 == (undefined *)0x0) || (*(longlong *)(self_00 + 0x30) == 0))
    goto LAB_7fff5fca8ea1;
    message = (undefined *)FUN_7fff5f568150(*(longlong *)(self_00 + 0x30),_DAT_7fff623fdfc8,0);
    uVar1 = *(uint *)(self + 0x34);
    lVar9 = FUN_7fff618a1b90(self_00,0);
    if (lVar9 == 0) goto LAB_7fff5fca8ea1;
    puVar10 = (undefined *)FUN_7fff618c7030(lVar9,0);
    plVar4 = *(longlong **)(self_00 + 0x28);
    buttonCallback = (undefined *)func_0x7fff5f44ff00(_DAT_7fff62436790);
    if (plVar4 == (longlong *)0x0) goto LAB_7fff5fca8ea1;
    FUN_7fff5f4f6880(buttonCallback,plVar4,*(undefined8 *)(*plVar4 + 0x1a0),0);
    control = *(undefined **)(self_00 + 0x28);
  }
  else {
LAB_7fff5fca8b71:
    uVar1 = *(uint *)(self + 0x34);
    if (((self_00 == (undefined *)0x0) || (lVar9 = FUN_7fff618a1b90(self_00,0), lVar9 == 0)) ||
       (lVar9 = FUN_7fff618c7030(lVar9,0), lVar9 == 0)) goto LAB_7fff5fca8ea1;
    puVar10 = (undefined *)FUN_7fff618c7030(lVar9,0);
    plVar4 = *(longlong **)(self_00 + 0x28);
    buttonCallback = (undefined *)func_0x7fff5f44ff00(_DAT_7fff62436790);
    if (plVar4 == (longlong *)0x0) goto LAB_7fff5fca8ea1;
    FUN_7fff5f4f6880(buttonCallback,plVar4,*(undefined8 *)(*plVar4 + 400),0);
    control = *(undefined **)(self_00 + 0x28);
    message = (undefined *)0x0;
  }
  puVar10 = ShopUtil_CreateOperationFailurePopWindow
                      ((undefined *)(ulonglong)uVar1,puVar10,(undefined *)0x0,buttonCallback,control
                       ,message,(undefined *)0x0);
  *(undefined **)(self_00 + 0x1d8) = puVar10;
  thunk_FUN_7fff5f491fd0();
  plVar4 = *(longlong **)(self_00 + 0x28);
  uVar11 = func_0x7fff5f44ff00(_DAT_7fff62436790);
  FUN_7fff5f4f6880(uVar11,self_00,_DAT_7fff62473aa0,0);
  if (plVar4 != (longlong *)0x0) {
    (**(code **)(*plVar4 + 0x1c8))(plVar4,uVar11,*(undefined8 *)(*plVar4 + 0x1d0));
    uVar11 = func_0x7fff5f44ff00(_DAT_7fff62406568);
    FUN_7fff618b74f0(uVar11,_DAT_7fff61b52b40,0);
    *(undefined8 *)(self + 0x18) = uVar11;
    thunk_FUN_7fff5f491fd0();
    *(undefined4 *)(self + 0x10) = 4;
    return 1;
  }
LAB_7fff5fca8ea1:
  FUN_7fff5f47d660();
  pcVar5 = (code *)swi(3);
  bVar7 = (*pcVar5)();
  return bVar7;
}

