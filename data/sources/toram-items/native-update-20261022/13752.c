
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PlayerStatusBase_SetEquip
               (undefined *self,undefined *type,undefined *item,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  longlong lVar4;
  undefined *puVar5;
  undefined *puVar6;
  undefined *puVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined *puStackX_18;
  undefined8 uStack_68;
  undefined8 *puStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 *puStack_48;
  undefined8 uStack_40;
  
  iVar3 = (int)type;
  if (DAT_7ffe9cadde4b == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9085a8);
    FUN_7ffe9996d590(&DAT_7ffe9c973828);
    FUN_7ffe9996d590(&DAT_7ffe9c9738f8);
    FUN_7ffe9996d590(0x7ffe9c9739c8);
    FUN_7ffe9996d590(&DAT_7ffe9c937e60);
    FUN_7ffe9996d590(&DAT_7ffe9c908e90);
    FUN_7ffe9996d590(&DAT_7ffe9c9085a0);
    FUN_7ffe9996d590(&DAT_7ffe9c909100);
    FUN_7ffe9996d590(&DAT_7ffe9c908330);
    FUN_7ffe9996d590(&DAT_7ffe9c908cf0);
    FUN_7ffe9996d590(0x7ffe9c908b50);
    FUN_7ffe9996d590(&DAT_7ffe9c9644b8);
    FUN_7ffe9996d590(&DAT_7ffe9c964580);
    FUN_7ffe9996d590(&DAT_7ffe9c953710);
    FUN_7ffe9996d590(&DAT_7ffe9c8feb98);
    FUN_7ffe9996d590(&DAT_7ffe9c912550);
    DAT_7ffe9cadde4b = '\x01';
  }
  uStack_50 = 0;
  puStack_48 = (undefined8 *)0x0;
  uStack_40 = 0;
  lVar4 = (**(code **)(*(longlong *)self + 0x1f8))(self,*(undefined8 *)(*(longlong *)self + 0x200));
  if (lVar4 == 0) goto LAB_7ffe9a4a3b60;
  FUN_7ffe99c087b0(lVar4,(ulonglong)type & 0xffffffff);
  if ((((iVar3 - 1U & 0xfffffffc) == 0) && (iVar3 != 2)) || (iVar3 == 5)) {
    puVar5 = (undefined *)
             (**(code **)(*(longlong *)self + 0x1d8))
                       (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
    if (item == (undefined *)0x0) {
      if (puVar5 == (undefined *)0x0) goto LAB_7ffe9a4a3b60;
      BonusManager_SetEquipBonus
                (puVar5,(undefined *)((ulonglong)type & 0xffffffff),(undefined *)0x0,
                 (undefined *)0x0);
      lVar4 = (**(code **)(*(longlong *)self + 0x208))
                        (self,*(undefined8 *)(*(longlong *)self + 0x210));
      if (lVar4 == 0) goto LAB_7ffe9a4a3b60;
      puVar5 = (undefined *)0x0;
    }
    else {
      puVar6 = (undefined *)FUN_7ffe9a56fc30(item,0);
      if (puVar5 == (undefined *)0x0) goto LAB_7ffe9a4a3b60;
      puVar5 = BonusManager_CreateBonus(puVar5,puVar6,0,(undefined *)0x0);
      puVar6 = (undefined *)
               (**(code **)(*(longlong *)self + 0x1d8))
                         (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
      if (puVar6 == (undefined *)0x0) goto LAB_7ffe9a4a3b60;
      BonusManager_SetEquipBonus
                (puVar6,(undefined *)((ulonglong)type & 0xffffffff),puVar5,(undefined *)0x0);
      if (*(int *)(item + 0x48) != 0) {
        lVar4 = FUN_7ffe9b141840(_DAT_7ffe9c953710);
        if (lVar4 == 0) goto LAB_7ffe9a4a3b60;
        lVar4 = FUN_7ffe9a57a320(lVar4,*(undefined4 *)(item + 0x48),0);
        if (lVar4 != 0) {
          puVar6 = (undefined *)
                   (**(code **)(*(longlong *)self + 0x1d8))
                             (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
          puVar7 = (undefined *)FUN_7ffe9a569db0(lVar4,0);
          if (puVar6 == (undefined *)0x0) goto LAB_7ffe9a4a3b60;
          puVar6 = BonusManager_CreateBonus(puVar6,puVar7,0,(undefined *)0x0);
          lVar4 = (**(code **)(*(longlong *)self + 0x1d8))
                            (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
          if (lVar4 == 0) goto LAB_7ffe9a4a3b60;
          FUN_7ffe9a4e8380(lVar4,(ulonglong)type & 0xffffffff,puVar6);
          FUN_7ffe9a4a2e30(self,puVar5,puVar6);
        }
      }
      if (*(int *)(item + 0x4c) != 0) {
        lVar4 = FUN_7ffe9b141840(_DAT_7ffe9c953710);
        if (lVar4 == 0) goto LAB_7ffe9a4a3b60;
        lVar4 = FUN_7ffe9a57a320(lVar4,*(undefined4 *)(item + 0x4c),0);
        if (lVar4 != 0) {
          puVar6 = (undefined *)
                   (**(code **)(*(longlong *)self + 0x1d8))
                             (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
          puVar7 = (undefined *)FUN_7ffe9a569db0(lVar4,0);
          if (puVar6 == (undefined *)0x0) goto LAB_7ffe9a4a3b60;
          puVar6 = BonusManager_CreateBonus(puVar6,puVar7,0,(undefined *)0x0);
          lVar4 = (**(code **)(*(longlong *)self + 0x1d8))
                            (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
          if (lVar4 == 0) goto LAB_7ffe9a4a3b60;
          FUN_7ffe9a4e8380(lVar4,(ulonglong)type & 0xffffffff,puVar6,0);
          FUN_7ffe9a4a2e30(self,puVar5,puVar6,0);
        }
      }
      lVar4 = (**(code **)(*(longlong *)self + 0x208))
                        (self,*(undefined8 *)(*(longlong *)self + 0x210));
      if (lVar4 == 0) goto LAB_7ffe9a4a3b60;
    }
    FUN_7ffe9a51e660(lVar4,(ulonglong)type & 0xff,puVar5,0);
    lVar4 = (**(code **)(*(longlong *)self + 0x228))
                      (self,*(undefined8 *)(*(longlong *)self + 0x230));
    if (lVar4 != 0) {
      lVar4 = (**(code **)(*(longlong *)self + 0x228))
                        (self,*(undefined8 *)(*(longlong *)self + 0x230));
      if (lVar4 == 0) goto LAB_7ffe9a4a3b60;
      FUN_7ffe9a579170(lVar4,(ulonglong)type & 0xffffffff,item,0);
    }
  }
  else if (iVar3 == 2) {
    if (item == (undefined *)0x0) {
      puVar5 = (undefined *)
               (**(code **)(*(longlong *)self + 0x1d8))
                         (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
      if (puVar5 == (undefined *)0x0) goto LAB_7ffe9a4a3b60;
      BonusManager_SetEquipBonus(puVar5,(undefined *)0x2,(undefined *)0x0,(undefined *)0x0);
      lVar4 = (**(code **)(*(longlong *)self + 0x208))
                        (self,*(undefined8 *)(*(longlong *)self + 0x210));
      if (lVar4 == 0) goto LAB_7ffe9a4a3b60;
      FUN_7ffe9a51e660(lVar4,2,0,0);
    }
    else {
      iVar3 = *(int *)(item + 0x38);
      if (((iVar3 == 0x10) || (iVar3 == 0xf)) || (iVar3 == 10)) {
        if (iVar3 == 8) goto LAB_7ffe9a4a352f;
        if (iVar3 != 10) goto LAB_7ffe9a4a359a;
LAB_7ffe9a4a3607:
        lVar4 = func_0x7ffe99940040(_DAT_7ffe9c964580);
        FUN_7ffe9af8a010(lVar4,_DAT_7ffe9c908cf0);
        if (lVar4 == 0) goto LAB_7ffe9a4a3b60;
        FUN_7ffe99744640(lVar4,0x41,_DAT_7ffe9c908e90);
        puVar5 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c9644b8);
        FUN_7ffe9af8a010(puVar5,_DAT_7ffe9c908330);
        FUN_7ffe9af836e0(&uStack_68,lVar4);
        uStack_50 = uStack_68;
        puStack_48 = puStack_60;
        uStack_40 = uStack_58;
        puStackX_18 = (undefined *)0x0;
        uStack_68 = 0;
        puStack_60 = &uStack_50;
        while (cVar2 = FUN_7ffe9ae24860(&uStack_50,_DAT_7ffe9c9738f8), cVar2 != '\0') {
          lVar4 = func_0x7ffe99940040(_DAT_7ffe9c912550);
          func_0x7ffe999c3920(lVar4,0);
          if (lVar4 == 0) goto LAB_7ffe9a4a3b54;
          *(undefined4 *)(lVar4 + 0x10) = (undefined4)uStack_40;
          uVar8 = FUN_7ffe9a56fc30(item,0);
          uVar9 = func_0x7ffe99940040(_DAT_7ffe9c937e60);
          FUN_7ffe9af13420(uVar9,lVar4,_DAT_7ffe9c8feb98);
          lVar4 = FUN_7ffe9ab854c0(uVar8,uVar9);
          if (lVar4 != 0) {
            if (puVar5 == (undefined *)0x0) {
              FUN_7ffe9996d7a0();
LAB_7ffe9a4a3b54:
              FUN_7ffe9996d7a0();
              FUN_7ffe998fa550();
              pcVar1 = (code *)swi(3);
              (*pcVar1)();
              return;
            }
            FUN_7ffe99743100(puVar5,lVar4);
          }
        }
        func_0x7ffe999c3920(&uStack_50,_DAT_7ffe9c973828);
        if (puVar5 == (undefined *)0x0) goto LAB_7ffe9a4a3b60;
        if (0 < *(int *)(puVar5 + 0x18)) {
          puVar6 = (undefined *)
                   (**(code **)(*(longlong *)self + 0x1d8))
                             (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
          if (puVar6 == (undefined *)0x0) goto LAB_7ffe9a4a3b60;
          puStackX_18 = BonusManager_CreateBonus(puVar6,puVar5,0,(undefined *)0x0);
        }
      }
      else {
        if (iVar3 != 8) {
          puVar5 = (undefined *)
                   (**(code **)(*(longlong *)self + 0x1d8))
                             (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
          puVar6 = (undefined *)FUN_7ffe9a56fc30(item,0);
          if (puVar5 == (undefined *)0x0) goto LAB_7ffe9a4a3b60;
          puVar5 = BonusManager_CreateBonus(puVar5,puVar6,0,(undefined *)0x0);
          puVar6 = (undefined *)
                   (**(code **)(*(longlong *)self + 0x1d8))
                             (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
          if (puVar6 == (undefined *)0x0) goto LAB_7ffe9a4a3b60;
          BonusManager_SetEquipBonus(puVar6,(undefined *)0x2,puVar5,(undefined *)0x0);
          if (*(int *)(item + 0x48) != 0) {
            lVar4 = FUN_7ffe9b141840(_DAT_7ffe9c953710);
            if (lVar4 == 0) goto LAB_7ffe9a4a3b60;
            lVar4 = FUN_7ffe9a57a320(lVar4,*(undefined4 *)(item + 0x48),0);
            if (lVar4 != 0) {
              puVar6 = (undefined *)
                       (**(code **)(*(longlong *)self + 0x1d8))
                                 (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
              puVar7 = (undefined *)FUN_7ffe9a569db0(lVar4,0);
              if (puVar6 == (undefined *)0x0) goto LAB_7ffe9a4a3b60;
              puVar6 = BonusManager_CreateBonus(puVar6,puVar7,0,(undefined *)0x0);
              lVar4 = (**(code **)(*(longlong *)self + 0x1d8))
                                (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
              if (lVar4 == 0) goto LAB_7ffe9a4a3b60;
              FUN_7ffe9a4e8380(lVar4,2,puVar6);
              FUN_7ffe9a4a2e30(self,puVar5,puVar6);
            }
          }
          if (*(int *)(item + 0x4c) != 0) {
            lVar4 = FUN_7ffe9b141840(_DAT_7ffe9c953710);
            if (lVar4 == 0) goto LAB_7ffe9a4a3b60;
            lVar4 = FUN_7ffe9a57a320(lVar4,*(undefined4 *)(item + 0x4c),0);
            if (lVar4 != 0) {
              puVar6 = (undefined *)
                       (**(code **)(*(longlong *)self + 0x1d8))
                                 (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
              puVar7 = (undefined *)FUN_7ffe9a569db0(lVar4,0);
              if (puVar6 == (undefined *)0x0) goto LAB_7ffe9a4a3b60;
              puVar6 = BonusManager_CreateBonus(puVar6,puVar7,0,(undefined *)0x0);
              lVar4 = (**(code **)(*(longlong *)self + 0x1d8))
                                (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
              if (lVar4 == 0) goto LAB_7ffe9a4a3b60;
              FUN_7ffe9a4e8380(lVar4,2,puVar6);
              FUN_7ffe9a4a2e30(self,puVar5,puVar6,0);
            }
          }
          lVar4 = (**(code **)(*(longlong *)self + 0x208))
                            (self,*(undefined8 *)(*(longlong *)self + 0x210));
          if (lVar4 == 0) goto LAB_7ffe9a4a3b60;
          FUN_7ffe9a51e660(lVar4,2,puVar5,0);
          goto LAB_7ffe9a4a3b19;
        }
LAB_7ffe9a4a352f:
        lVar4 = (**(code **)(*(longlong *)self + 0x1b8))
                          (self,*(undefined8 *)(*(longlong *)self + 0x1c0));
        if (lVar4 == 0) goto LAB_7ffe9a4a3b60;
        iVar3 = FUN_7ffe9a7fd580(lVar4,0x56,1);
        if (0 < iVar3) {
          lVar4 = (**(code **)(*(longlong *)self + 0x1b8))
                            (self,*(undefined8 *)(*(longlong *)self + 0x1c0));
          if (lVar4 == 0) goto LAB_7ffe9a4a3b60;
          iVar3 = FUN_7ffe9a7fd580(lVar4,0x53,1);
          if (9 < iVar3) goto LAB_7ffe9a4a3607;
        }
LAB_7ffe9a4a359a:
        puStackX_18 = (undefined *)0x0;
      }
      puVar5 = (undefined *)
               (**(code **)(*(longlong *)self + 0x1d8))
                         (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
LAB_7ffe9a4a35b2:
      if (puVar5 == (undefined *)0x0) goto LAB_7ffe9a4a3b60;
      BonusManager_SetEquipBonus
                (puVar5,(undefined *)((ulonglong)type & 0xffffffff),puStackX_18,(undefined *)0x0);
      lVar4 = (**(code **)(*(longlong *)self + 0x208))
                        (self,*(undefined8 *)(*(longlong *)self + 0x210));
      if (lVar4 == 0) goto LAB_7ffe9a4a3b60;
      FUN_7ffe9a51e660(lVar4,(ulonglong)type & 0xff,puStackX_18,0);
    }
  }
  else if ((iVar3 - 7U < 2) || (iVar3 == 9)) {
    puVar5 = (undefined *)
             (**(code **)(*(longlong *)self + 0x1d8))
                       (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
    if (item != (undefined *)0x0) {
      puVar6 = (undefined *)FUN_7ffe9a56fc30(item,0);
      if (puVar5 == (undefined *)0x0) goto LAB_7ffe9a4a3b60;
      puStackX_18 = BonusManager_CreateBonus(puVar5,puVar6,0,(undefined *)0x0);
      puVar5 = (undefined *)
               (**(code **)(*(longlong *)self + 0x1d8))
                         (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
      goto LAB_7ffe9a4a35b2;
    }
    if (puVar5 == (undefined *)0x0) goto LAB_7ffe9a4a3b60;
    BonusManager_SetEquipBonus
              (puVar5,(undefined *)((ulonglong)type & 0xffffffff),(undefined *)0x0,(undefined *)0x0)
    ;
    lVar4 = (**(code **)(*(longlong *)self + 0x208))
                      (self,*(undefined8 *)(*(longlong *)self + 0x210));
    if (lVar4 == 0) goto LAB_7ffe9a4a3b60;
    FUN_7ffe9a51e660(lVar4,(ulonglong)type & 0xff,0,0);
  }
LAB_7ffe9a4a3b19:
  puVar5 = (undefined *)(**(code **)(*(longlong *)self + 0x1d8))(self);
  if (puVar5 != (undefined *)0x0) {
    BonusManager_UpdateEquipLimitBonus(puVar5,(undefined *)0x0);
    return;
  }
LAB_7ffe9a4a3b60:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

