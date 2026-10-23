
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
  undefined *puVar8;
  undefined8 uVar9;
  undefined *puStackX_18;
  undefined8 uStack_68;
  undefined8 *puStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  undefined8 *puStack_48;
  undefined8 uStack_40;
  
  iVar3 = (int)type;
  if (DAT_7fff625e55a3 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6240f508);
    FUN_7fff5f47d450(&DAT_7fff6247a738);
    FUN_7fff5f47d450(&DAT_7fff6247a808);
    FUN_7fff5f47d450(0x7fff6247a8d8);
    FUN_7fff5f47d450(&DAT_7fff6243f870);
    FUN_7fff5f47d450(&DAT_7fff6240fec0);
    FUN_7fff5f47d450(&DAT_7fff6240f5d0);
    FUN_7fff5f47d450(&DAT_7fff62410130);
    FUN_7fff5f47d450(&DAT_7fff6240f360);
    FUN_7fff5f47d450(&DAT_7fff6240fd20);
    FUN_7fff5f47d450(0x7fff6240fb80);
    FUN_7fff5f47d450(&DAT_7fff6246bec0);
    FUN_7fff5f47d450(&DAT_7fff6246bf90);
    FUN_7fff5f47d450(&DAT_7fff6245a5f8);
    FUN_7fff5f47d450(&DAT_7fff62405618);
    FUN_7fff5f47d450(&DAT_7fff62419990);
    DAT_7fff625e55a3 = '\x01';
  }
  uStack_50 = 0;
  puStack_48 = (undefined8 *)0x0;
  uStack_40 = 0;
  lVar4 = (**(code **)(*(longlong *)self + 0x1f8))(self,*(undefined8 *)(*(longlong *)self + 0x200));
  if (lVar4 == 0) goto LAB_7fff5ffae720;
  FUN_7fff5f718470(lVar4,(ulonglong)type & 0xffffffff);
  if ((((iVar3 - 1U & 0xfffffffc) == 0) && (iVar3 != 2)) || (iVar3 == 5)) {
    puVar5 = (undefined *)(**(code **)(*(longlong *)self + 0x1d8))(self);
    if (item == (undefined *)0x0) {
      if (puVar5 == (undefined *)0x0) goto LAB_7fff5ffae720;
      BonusManager_SetEquipBonus
                (puVar5,(undefined *)((ulonglong)type & 0xffffffff),(undefined *)0x0,
                 (undefined *)0x0);
      lVar4 = (**(code **)(*(longlong *)self + 0x208))
                        (self,*(undefined8 *)(*(longlong *)self + 0x210));
      if (lVar4 == 0) goto LAB_7fff5ffae720;
      puVar5 = (undefined *)0x0;
    }
    else {
      puVar6 = ItemData_get_BonusLines(item,(undefined *)0x0);
      if (puVar5 == (undefined *)0x0) goto LAB_7fff5ffae720;
      puVar5 = BonusManager_CreateBonus(puVar5,puVar6,0,(undefined *)0x0);
      puVar6 = (undefined *)
               (**(code **)(*(longlong *)self + 0x1d8))
                         (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
      if (puVar6 == (undefined *)0x0) goto LAB_7fff5ffae720;
      BonusManager_SetEquipBonus
                (puVar6,(undefined *)((ulonglong)type & 0xffffffff),puVar5,(undefined *)0x0);
      if (*(int *)(item + 0x48) != 0) {
        lVar4 = FUN_7fff60c4bc00(_DAT_7fff6245a5f8);
        if (lVar4 == 0) goto LAB_7fff5ffae720;
        puVar6 = (undefined *)FUN_7fff600847d0(lVar4,*(undefined4 *)(item + 0x48),0);
        if (puVar6 != (undefined *)0x0) {
          puVar7 = (undefined *)(**(code **)(*(longlong *)self + 0x1d8))(self);
          puVar6 = ItemDBData_get_BonusLines(puVar6,(undefined *)0x0);
          if (puVar7 == (undefined *)0x0) goto LAB_7fff5ffae720;
          puVar6 = BonusManager_CreateBonus(puVar7,puVar6,0,(undefined *)0x0);
          puVar7 = (undefined *)
                   (**(code **)(*(longlong *)self + 0x1d8))
                             (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
          if (puVar7 == (undefined *)0x0) goto LAB_7fff5ffae720;
          BonusManager_AddEquipCristaBonus
                    (puVar7,(undefined *)((ulonglong)type & 0xffffffff),puVar6,(undefined *)0x0);
          PlayerStatusBase_SetCristEquipBuff(self,puVar5,puVar6,(undefined *)0x0);
        }
      }
      if (*(int *)(item + 0x4c) != 0) {
        lVar4 = FUN_7fff60c4bc00(_DAT_7fff6245a5f8);
        if (lVar4 == 0) goto LAB_7fff5ffae720;
        puVar6 = (undefined *)FUN_7fff600847d0(lVar4,*(undefined4 *)(item + 0x4c),0);
        if (puVar6 != (undefined *)0x0) {
          puVar7 = (undefined *)(**(code **)(*(longlong *)self + 0x1d8))(self);
          puVar6 = ItemDBData_get_BonusLines(puVar6,(undefined *)0x0);
          if (puVar7 == (undefined *)0x0) goto LAB_7fff5ffae720;
          puVar6 = BonusManager_CreateBonus(puVar7,puVar6,0,(undefined *)0x0);
          puVar7 = (undefined *)
                   (**(code **)(*(longlong *)self + 0x1d8))
                             (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
          if (puVar7 == (undefined *)0x0) goto LAB_7fff5ffae720;
          BonusManager_AddEquipCristaBonus
                    (puVar7,(undefined *)((ulonglong)type & 0xffffffff),puVar6,(undefined *)0x0);
          PlayerStatusBase_SetCristEquipBuff(self,puVar5,puVar6,(undefined *)0x0);
        }
      }
      lVar4 = (**(code **)(*(longlong *)self + 0x208))
                        (self,*(undefined8 *)(*(longlong *)self + 0x210));
      if (lVar4 == 0) goto LAB_7fff5ffae720;
    }
    FUN_7fff60029150(lVar4,(ulonglong)type & 0xff,puVar5,0);
    lVar4 = (**(code **)(*(longlong *)self + 0x228))
                      (self,*(undefined8 *)(*(longlong *)self + 0x230));
    if (lVar4 != 0) {
      lVar4 = (**(code **)(*(longlong *)self + 0x228))
                        (self,*(undefined8 *)(*(longlong *)self + 0x230));
      if (lVar4 == 0) goto LAB_7fff5ffae720;
      FUN_7fff60083620(lVar4,(ulonglong)type & 0xffffffff,item,0);
    }
  }
  else if (iVar3 == 2) {
    if (item == (undefined *)0x0) {
      puVar5 = (undefined *)
               (**(code **)(*(longlong *)self + 0x1d8))
                         (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
      if (puVar5 == (undefined *)0x0) goto LAB_7fff5ffae720;
      BonusManager_SetEquipBonus(puVar5,(undefined *)0x2,(undefined *)0x0,(undefined *)0x0);
      lVar4 = (**(code **)(*(longlong *)self + 0x208))
                        (self,*(undefined8 *)(*(longlong *)self + 0x210));
      if (lVar4 == 0) goto LAB_7fff5ffae720;
      FUN_7fff60029150(lVar4,2,0,0);
    }
    else {
      iVar3 = *(int *)(item + 0x38);
      if (((iVar3 == 0x10) || (iVar3 == 0xf)) || (iVar3 == 10)) {
        if (iVar3 == 8) goto LAB_7fff5ffae0ef;
        if (iVar3 != 10) goto LAB_7fff5ffae15a;
LAB_7fff5ffae1c7:
        lVar4 = func_0x7fff5f44ff00(_DAT_7fff6246bf90);
        FUN_7fff60a943d0(lVar4,_DAT_7fff6240fd20);
        if (lVar4 == 0) goto LAB_7fff5ffae720;
        FUN_7fff5f254640(lVar4,0x41,_DAT_7fff6240fec0);
        puVar6 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff6246bec0);
        FUN_7fff60a943d0(puVar6,_DAT_7fff6240f360);
        puVar5 = _DAT_7fff62410130;
        FUN_7fff60a8daa0(&uStack_68,lVar4);
        uStack_50 = uStack_68;
        puStack_48 = puStack_60;
        uStack_40 = uStack_58;
        puStackX_18 = (undefined *)0x0;
        uStack_68 = 0;
        puStack_60 = &uStack_50;
        while (cVar2 = FUN_7fff6092ec20(&uStack_50), cVar2 != '\0') {
          puVar7 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff62419990);
          MainPlayer_OnSkillDelayStandbyOk(puVar7,0,puVar5);
          if (puVar7 == (undefined *)0x0) goto LAB_7fff5ffae714;
          *(undefined4 *)(puVar7 + 0x10) = (undefined4)uStack_40;
          puVar8 = ItemData_get_BonusLines(item,(undefined *)0x0);
          uVar9 = func_0x7fff5f44ff00(_DAT_7fff6243f870);
          FUN_7fff60a1d7e0(uVar9,puVar7,_DAT_7fff62405618);
          puVar5 = _DAT_7fff6240f508;
          lVar4 = FUN_7fff6068f870(puVar8,uVar9);
          if (lVar4 != 0) {
            if (puVar6 == (undefined *)0x0) {
              FUN_7fff5f47d660();
LAB_7fff5ffae714:
              FUN_7fff5f47d660();
              FUN_7fff5f40a410();
              pcVar1 = (code *)swi(3);
              (*pcVar1)();
              return;
            }
            puVar5 = _DAT_7fff6240f5d0;
            FUN_7fff5f253100(puVar6,lVar4);
          }
        }
        MainPlayer_OnSkillDelayStandbyOk((undefined *)&uStack_50,(short)_DAT_7fff6247a738,puVar5);
        if (puVar6 == (undefined *)0x0) goto LAB_7fff5ffae720;
        if (0 < *(int *)(puVar6 + 0x18)) {
          puVar5 = (undefined *)
                   (**(code **)(*(longlong *)self + 0x1d8))
                             (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
          if (puVar5 == (undefined *)0x0) goto LAB_7fff5ffae720;
          puStackX_18 = BonusManager_CreateBonus(puVar5,puVar6,0,(undefined *)0x0);
        }
      }
      else {
        if (iVar3 != 8) {
          puVar5 = (undefined *)(**(code **)(*(longlong *)self + 0x1d8))(self);
          puVar6 = ItemData_get_BonusLines(item,(undefined *)0x0);
          if (puVar5 == (undefined *)0x0) goto LAB_7fff5ffae720;
          puVar5 = BonusManager_CreateBonus(puVar5,puVar6,0,(undefined *)0x0);
          puVar6 = (undefined *)
                   (**(code **)(*(longlong *)self + 0x1d8))
                             (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
          if (puVar6 == (undefined *)0x0) goto LAB_7fff5ffae720;
          BonusManager_SetEquipBonus(puVar6,(undefined *)0x2,puVar5,(undefined *)0x0);
          if (*(int *)(item + 0x48) != 0) {
            lVar4 = FUN_7fff60c4bc00(_DAT_7fff6245a5f8);
            if (lVar4 == 0) goto LAB_7fff5ffae720;
            puVar6 = (undefined *)FUN_7fff600847d0(lVar4,*(undefined4 *)(item + 0x48),0);
            if (puVar6 != (undefined *)0x0) {
              puVar7 = (undefined *)(**(code **)(*(longlong *)self + 0x1d8))(self);
              puVar6 = ItemDBData_get_BonusLines(puVar6,(undefined *)0x0);
              if (puVar7 == (undefined *)0x0) goto LAB_7fff5ffae720;
              puVar6 = BonusManager_CreateBonus(puVar7,puVar6,0,(undefined *)0x0);
              puVar7 = (undefined *)
                       (**(code **)(*(longlong *)self + 0x1d8))
                                 (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
              if (puVar7 == (undefined *)0x0) goto LAB_7fff5ffae720;
              BonusManager_AddEquipCristaBonus(puVar7,(undefined *)0x2,puVar6,(undefined *)0x0);
              PlayerStatusBase_SetCristEquipBuff(self,puVar5,puVar6,(undefined *)0x0);
            }
          }
          if (*(int *)(item + 0x4c) != 0) {
            lVar4 = FUN_7fff60c4bc00(_DAT_7fff6245a5f8);
            if (lVar4 == 0) goto LAB_7fff5ffae720;
            puVar6 = (undefined *)FUN_7fff600847d0(lVar4,*(undefined4 *)(item + 0x4c),0);
            if (puVar6 != (undefined *)0x0) {
              puVar7 = (undefined *)(**(code **)(*(longlong *)self + 0x1d8))(self);
              puVar6 = ItemDBData_get_BonusLines(puVar6,(undefined *)0x0);
              if (puVar7 == (undefined *)0x0) goto LAB_7fff5ffae720;
              puVar6 = BonusManager_CreateBonus(puVar7,puVar6,0,(undefined *)0x0);
              puVar7 = (undefined *)
                       (**(code **)(*(longlong *)self + 0x1d8))
                                 (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
              if (puVar7 == (undefined *)0x0) goto LAB_7fff5ffae720;
              BonusManager_AddEquipCristaBonus(puVar7,(undefined *)0x2,puVar6,(undefined *)0x0);
              PlayerStatusBase_SetCristEquipBuff(self,puVar5,puVar6,(undefined *)0x0);
            }
          }
          lVar4 = (**(code **)(*(longlong *)self + 0x208))
                            (self,*(undefined8 *)(*(longlong *)self + 0x210));
          if (lVar4 == 0) goto LAB_7fff5ffae720;
          FUN_7fff60029150(lVar4,2,puVar5,0);
          goto LAB_7fff5ffae6d9;
        }
LAB_7fff5ffae0ef:
        lVar4 = (**(code **)(*(longlong *)self + 0x1b8))
                          (self,*(undefined8 *)(*(longlong *)self + 0x1c0));
        if (lVar4 == 0) goto LAB_7fff5ffae720;
        iVar3 = FUN_7fff60307a10(lVar4,0x56,1);
        if (0 < iVar3) {
          lVar4 = (**(code **)(*(longlong *)self + 0x1b8))
                            (self,*(undefined8 *)(*(longlong *)self + 0x1c0));
          if (lVar4 == 0) goto LAB_7fff5ffae720;
          iVar3 = FUN_7fff60307a10(lVar4,0x53,1);
          if (9 < iVar3) goto LAB_7fff5ffae1c7;
        }
LAB_7fff5ffae15a:
        puStackX_18 = (undefined *)0x0;
      }
      puVar5 = (undefined *)
               (**(code **)(*(longlong *)self + 0x1d8))
                         (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
LAB_7fff5ffae172:
      if (puVar5 == (undefined *)0x0) goto LAB_7fff5ffae720;
      BonusManager_SetEquipBonus
                (puVar5,(undefined *)((ulonglong)type & 0xffffffff),puStackX_18,(undefined *)0x0);
      lVar4 = (**(code **)(*(longlong *)self + 0x208))
                        (self,*(undefined8 *)(*(longlong *)self + 0x210));
      if (lVar4 == 0) goto LAB_7fff5ffae720;
      FUN_7fff60029150(lVar4,(ulonglong)type & 0xff,puStackX_18,0);
    }
  }
  else if ((iVar3 - 7U < 2) || (iVar3 == 9)) {
    puVar5 = (undefined *)(**(code **)(*(longlong *)self + 0x1d8))(self);
    if (item != (undefined *)0x0) {
      puVar6 = ItemData_get_BonusLines(item,(undefined *)0x0);
      if (puVar5 == (undefined *)0x0) goto LAB_7fff5ffae720;
      puStackX_18 = BonusManager_CreateBonus(puVar5,puVar6,0,(undefined *)0x0);
      puVar5 = (undefined *)
               (**(code **)(*(longlong *)self + 0x1d8))
                         (self,*(undefined8 *)(*(longlong *)self + 0x1e0));
      goto LAB_7fff5ffae172;
    }
    if (puVar5 == (undefined *)0x0) goto LAB_7fff5ffae720;
    BonusManager_SetEquipBonus
              (puVar5,(undefined *)((ulonglong)type & 0xffffffff),(undefined *)0x0,(undefined *)0x0)
    ;
    lVar4 = (**(code **)(*(longlong *)self + 0x208))
                      (self,*(undefined8 *)(*(longlong *)self + 0x210));
    if (lVar4 == 0) goto LAB_7fff5ffae720;
    FUN_7fff60029150(lVar4,(ulonglong)type & 0xff,0,0);
  }
LAB_7fff5ffae6d9:
  puVar5 = (undefined *)(**(code **)(*(longlong *)self + 0x1d8))(self);
  if (puVar5 != (undefined *)0x0) {
    BonusManager_UpdateEquipLimitBonus(puVar5,(undefined *)0x0);
    return;
  }
LAB_7fff5ffae720:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

