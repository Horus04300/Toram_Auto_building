
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int HighRaidBossBattleStatus_get_CutMagicAttack(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  undefined *puVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  longlong lVar6;
  int iVar7;
  undefined *puStackX_20;
  undefined8 uStack_50;
  undefined8 *puStack_48;
  undefined *puStack_40;
  undefined8 uStack_38;
  undefined8 *puStack_30;
  undefined *puStack_28;
  
  if (DAT_7ffe9cadd540 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8ff610);
    FUN_7ffe9996d590(&DAT_7ffe9c937818);
    FUN_7ffe9996d590(&DAT_7ffe9c9378d8);
    FUN_7ffe9996d590(0x7ffe9c9379a0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f9b60);
    DAT_7ffe9cadd540 = '\x01';
  }
  puStackX_20 = (undefined *)0x0;
  iVar7 = 0;
  if ((*(longlong *)(self + 0x38) != 0) &&
     (lVar6 = FUN_7ffe9acd27a0(*(longlong *)(self + 0x38),_DAT_7ffe9c8ff610), lVar6 != 0)) {
    FUN_7ffe9af415c0(&uStack_50,lVar6,_DAT_7ffe9c8f9b60);
    uStack_38 = uStack_50;
    puStack_30 = puStack_48;
    puStack_28 = puStack_40;
    uStack_50 = 0;
    puStack_48 = &uStack_38;
    while (cVar3 = FUN_7ffe9ae37290(&uStack_38), puVar2 = puStack_28, cVar3 != '\0') {
      if (puStack_28 == (undefined *)0x0) goto LAB_7ffe9a323032;
      if ((*(longlong *)(puStack_28 + 0x20) != 0) &&
         (bVar4 = MobPartsStatus_get_IsDead(puStack_28,(undefined *)0x0), bVar4 == 0)) {
        if (*(undefined **)(puVar2 + 0x20) == (undefined *)0x0) goto LAB_7ffe9a32302c;
        iVar5 = MobPropertyCut_get_CutMagicAttack(*(undefined **)(puVar2 + 0x20),(undefined *)0x0);
        iVar7 = iVar7 + iVar5;
      }
    }
    func_0x7ffe999c3920(&uStack_38,_DAT_7ffe9c937818);
    if (DAT_7ffe9cadd548 == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c929b20);
      DAT_7ffe9cadd548 = '\x01';
    }
    if ((*(longlong *)(self + 0x10) == 0) ||
       (lVar6 = *(longlong *)(*(longlong *)(self + 0x10) + 0xa0), lVar6 == 0))
    goto LAB_7ffe9a323026;
    cVar3 = FUN_7ffe9abb86e0(lVar6,0x20,&puStackX_20,_DAT_7ffe9c929b20);
    if (cVar3 != '\0') {
      if (puStackX_20 == (undefined *)0x0) goto LAB_7ffe9a323026;
      bVar4 = MobPropertyHighRaidCalcExceptionFlag_FixedCutMagicAttackFlag
                        (puStackX_20,(undefined *)0x0);
      if (bVar4 != 0) {
        if (*(longlong *)(self + 0x10) == 0) goto LAB_7ffe9a323026;
        iVar5 = *(int *)(*(longlong *)(self + 0x10) + 0x48);
        goto LAB_7ffe9a322fee;
      }
    }
    if (*(longlong *)(self + 0x10) != 0) {
      iVar5 = *(int *)(*(longlong *)(self + 0x10) + 0x48) -
              (int)((float)*(int *)(self + 0x30) * _DAT_7ffe9c04aa78);
LAB_7ffe9a322fee:
      return iVar5 + iVar7;
    }
  }
LAB_7ffe9a323026:
  FUN_7ffe9996d7a0();
LAB_7ffe9a32302c:
  FUN_7ffe9996d7a0();
LAB_7ffe9a323032:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar1 = (code *)swi(3);
  iVar7 = (*pcVar1)();
  return iVar7;
}

