
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int HighRaidBossBattleStatus_get_MagicDef(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  longlong *plVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  longlong lVar6;
  int iVar7;
  undefined *puStackX_20;
  undefined8 uStack_50;
  undefined8 *puStack_48;
  longlong *plStack_40;
  undefined8 uStack_38;
  undefined8 *puStack_30;
  longlong *plStack_28;
  
  if (DAT_7ffe9cadd53e == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8ff610);
    FUN_7ffe9996d590(&DAT_7ffe9c937818);
    FUN_7ffe9996d590(&DAT_7ffe9c9378d8);
    FUN_7ffe9996d590(0x7ffe9c9379a0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f9b60);
    DAT_7ffe9cadd53e = '\x01';
  }
  puStackX_20 = (undefined *)0x0;
  if (DAT_7ffe9cadd548 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c929b20);
    DAT_7ffe9cadd548 = '\x01';
  }
  if ((*(longlong *)(self + 0x10) == 0) ||
     (lVar6 = *(longlong *)(*(longlong *)(self + 0x10) + 0xa0), lVar6 == 0)) goto LAB_7ffe9a323838;
  cVar3 = FUN_7ffe9abb86e0(lVar6,0x20,&puStackX_20,_DAT_7ffe9c929b20);
  if (cVar3 == '\0') {
LAB_7ffe9a323681:
    if (*(longlong *)(self + 0x10) == 0) goto LAB_7ffe9a323838;
    iVar7 = (int)((float)*(int *)(self + 0x30) *
                 ((float)*(int *)(*(longlong *)(self + 0x10) + 0x40) / _DAT_7ffe9c049cfc));
  }
  else {
    if (puStackX_20 == (undefined *)0x0) goto LAB_7ffe9a323838;
    bVar4 = MobPropertyHighRaidCalcExceptionFlag_FixedMagicDefFlag(puStackX_20,(undefined *)0x0);
    if (bVar4 == 0) goto LAB_7ffe9a323681;
    if (*(longlong *)(self + 0x10) == 0) goto LAB_7ffe9a323838;
    iVar7 = *(int *)(*(longlong *)(self + 0x10) + 0x40);
  }
  if ((*(longlong *)(self + 0x38) != 0) &&
     (lVar6 = FUN_7ffe9acd27a0(*(longlong *)(self + 0x38),_DAT_7ffe9c8ff610), lVar6 != 0)) {
    FUN_7ffe9af415c0(&uStack_50,lVar6,_DAT_7ffe9c8f9b60);
    uStack_38 = uStack_50;
    puStack_30 = puStack_48;
    plStack_28 = plStack_40;
    uStack_50 = 0;
    puStack_48 = &uStack_38;
    while (cVar3 = FUN_7ffe9ae37290(&uStack_38), plVar2 = plStack_28, cVar3 != '\0') {
      if (plStack_28 == (longlong *)0x0) goto LAB_7ffe9a32383e;
      bVar4 = MobPartsStatus_get_IsDead((undefined *)plStack_28,(undefined *)0x0);
      if (bVar4 == 0) {
        lVar6 = *plVar2;
        iVar5 = (**(code **)(lVar6 + 0x198))(plVar2,*(undefined8 *)(lVar6 + 0x1a0));
        iVar7 = iVar7 + iVar5;
      }
    }
    func_0x7ffe999c3920(&uStack_38,_DAT_7ffe9c937818);
    if (*(longlong *)(self + 0x20) != 0) {
      iVar5 = FUN_7ffe9a2ac490(*(longlong *)(self + 0x20),3);
      iVar7 = (int)(((float)iVar5 / _DAT_7ffe9c049cfc + _DAT_7ffe9c049b18) * (float)iVar7);
      if (*(longlong *)(self + 0x18) != 0) {
        cVar3 = FUN_7ffe9a4daa60(*(longlong *)(self + 0x18),10);
        if (cVar3 != '\0') {
          iVar7 = (int)((float)iVar7 * _DAT_7ffe9c049b4c);
        }
        return iVar7;
      }
    }
  }
LAB_7ffe9a323838:
  FUN_7ffe9996d7a0();
LAB_7ffe9a32383e:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar1 = (code *)swi(3);
  iVar7 = (*pcVar1)();
  return iVar7;
}

