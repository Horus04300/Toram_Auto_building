
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BonusManager_SetEquipBonus
               (undefined *self,undefined *type,undefined *bonus,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  undefined8 uVar4;
  longlong lVar5;
  ulonglong uVar6;
  undefined *methodInfo_00;
  undefined8 uStack_50;
  undefined8 uStack_48;
  undefined8 uStack_40;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined4 uStack_2c;
  undefined8 uStack_28;
  
  uVar6 = (ulonglong)type & 0xffffffff;
  if (DAT_7fff625e585c == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62460318);
    FUN_7fff5f47d450(&DAT_7fff6245ffe8);
    FUN_7fff5f47d450(&DAT_7fff624604b0);
    FUN_7fff5f47d450(&DAT_7fff62460648);
    FUN_7fff5f47d450(&DAT_7fff624600b8);
    FUN_7fff5f47d450(&DAT_7fff624607e0);
    FUN_7fff5f47d450(&DAT_7fff62460180);
    FUN_7fff5f47d450(&DAT_7fff62460978);
    FUN_7fff5f47d450(&DAT_7fff6247a258);
    FUN_7fff5f47d450(&DAT_7fff6247a328);
    FUN_7fff5f47d450(0x7fff6247a3f8);
    FUN_7fff5f47d450(&DAT_7fff6240edb0);
    FUN_7fff5f47d450(&DAT_7fff6240f020);
    FUN_7fff5f47d450(&DAT_7fff6240f0f0);
    FUN_7fff5f47d450(0x7fff624102d0);
    DAT_7fff625e585c = '\x01';
  }
  lVar5 = *(longlong *)(self + 0x20);
  if (bonus == (undefined *)0x0) {
    if (lVar5 == 0) goto LAB_7fff5fff76f4;
    cVar3 = FUN_7fff60869460(lVar5,uVar6,_DAT_7fff624604b0);
    if (cVar3 != '\0') {
      lVar5 = *(longlong *)(self + 0x78);
      if ((*(longlong *)(self + 0x20) == 0) ||
         (uVar4 = FUN_7fff6087c780(*(longlong *)(self + 0x20),uVar6,_DAT_7fff624607e0), lVar5 == 0))
      goto LAB_7fff5fff76f4;
      FUN_7fff60ae6370(lVar5,uVar4,_DAT_7fff6240f0f0);
      if (*(longlong *)(self + 0x20) == 0) goto LAB_7fff5fff76f4;
      FUN_7fff60891320(*(longlong *)(self + 0x20),uVar6,_DAT_7fff62460648);
    }
  }
  else {
    if (lVar5 == 0) goto LAB_7fff5fff76f4;
    cVar3 = FUN_7fff60869460(lVar5,uVar6,_DAT_7fff624604b0);
    lVar5 = *(longlong *)(self + 0x20);
    if (cVar3 == '\0') {
      if (lVar5 == 0) goto LAB_7fff5fff76f4;
      FUN_7fff6088cb20(lVar5,uVar6,bonus,_DAT_7fff62460318);
    }
    else {
      lVar1 = *(longlong *)(self + 0x78);
      if ((lVar5 == 0) || (uVar4 = FUN_7fff6087c780(lVar5,uVar6,_DAT_7fff624607e0), lVar1 == 0))
      goto LAB_7fff5fff76f4;
      FUN_7fff60ae6370(lVar1,uVar4,_DAT_7fff6240f0f0);
      if (*(longlong *)(self + 0x20) == 0) goto LAB_7fff5fff76f4;
      FUN_7fff6089f0e0(*(longlong *)(self + 0x20),uVar6,bonus,_DAT_7fff62460978);
    }
    if (*(longlong *)(bonus + 0x18) == 0) goto LAB_7fff5fff76f4;
    if (0 < *(int *)(*(longlong *)(bonus + 0x18) + 0x18)) {
      if (*(longlong *)(self + 0x78) == 0) goto LAB_7fff5fff76f4;
      FUN_7fff5f253100(*(longlong *)(self + 0x78),bonus,_DAT_7fff6240edb0);
    }
  }
  if (*(longlong *)(self + 0x28) != 0) {
    cVar3 = FUN_7fff60869460(*(longlong *)(self + 0x28),uVar6,_DAT_7fff6245ffe8);
    if (cVar3 == '\0') {
      return;
    }
    if ((*(longlong *)(self + 0x28) != 0) &&
       (lVar5 = FUN_7fff6087c780(*(longlong *)(self + 0x28),uVar6,_DAT_7fff62460180), lVar5 != 0)) {
      methodInfo_00 = _DAT_7fff6240f020;
      FUN_7fff60a8da60(&uStack_50,lVar5);
      uStack_38 = (undefined4)uStack_50;
      uStack_34 = uStack_50._4_4_;
      uStack_30 = (undefined4)uStack_48;
      uStack_2c = uStack_48._4_4_;
      uStack_28 = uStack_40;
      uStack_50 = 0;
      uStack_48 = &uStack_38;
      while (cVar3 = FUN_7fff60933290(&uStack_38,_DAT_7fff6247a328), cVar3 != '\0') {
        if (*(longlong *)(self + 0x78) == 0) goto LAB_7fff5fff76fa;
        methodInfo_00 = _DAT_7fff6240f0f0;
        FUN_7fff60ae6370(*(longlong *)(self + 0x78),uStack_28);
      }
      MainPlayer_OnSkillDelayStandbyOk
                ((undefined *)&uStack_38,(short)_DAT_7fff6247a258,methodInfo_00);
      if (*(longlong *)(self + 0x28) != 0) {
        FUN_7fff60891320(*(longlong *)(self + 0x28),uVar6,_DAT_7fff624600b8);
        return;
      }
    }
  }
LAB_7fff5fff76f4:
  FUN_7fff5f47d660();
LAB_7fff5fff76fa:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

