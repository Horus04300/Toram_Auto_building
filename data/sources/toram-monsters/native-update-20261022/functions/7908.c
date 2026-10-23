
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int HighRaidBossBattleStatus_get_NecessaryHit(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  longlong *plVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  longlong lVar6;
  int iVar7;
  undefined *puStackX_18;
  undefined8 uStack_40;
  undefined8 *puStack_38;
  longlong *plStack_30;
  undefined8 uStack_28;
  undefined8 *puStack_20;
  longlong *plStack_18;
  
  if (DAT_7ffe9cadd53c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8ff610);
    FUN_7ffe9996d590(&DAT_7ffe9c937818);
    FUN_7ffe9996d590(&DAT_7ffe9c9378d8);
    FUN_7ffe9996d590(0x7ffe9c9379a0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f9b60);
    DAT_7ffe9cadd53c = '\x01';
  }
  puStackX_18 = (undefined *)0x0;
  if (DAT_7ffe9cadd548 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c929b20);
    DAT_7ffe9cadd548 = '\x01';
  }
  if ((*(longlong *)(self + 0x10) != 0) &&
     (lVar6 = *(longlong *)(*(longlong *)(self + 0x10) + 0xa0), lVar6 != 0)) {
    cVar3 = FUN_7ffe9abb86e0(lVar6,0x20,&puStackX_18,_DAT_7ffe9c929b20);
    if (cVar3 == '\0') {
LAB_7ffe9a323abe:
      if (*(longlong *)(self + 0x10) != 0) {
        iVar7 = (int)((float)*(int *)(self + 0x30) * _DAT_7ffe9c049cd8 *
                     ((float)*(int *)(*(longlong *)(self + 0x10) + 0x38) / _DAT_7ffe9c049cfc));
LAB_7ffe9a323af3:
        if ((*(longlong *)(self + 0x38) != 0) &&
           (lVar6 = FUN_7ffe9acd27a0(*(longlong *)(self + 0x38),_DAT_7ffe9c8ff610), lVar6 != 0)) {
          FUN_7ffe9af415c0(&uStack_40,lVar6,_DAT_7ffe9c8f9b60);
          uStack_28 = uStack_40;
          puStack_20 = puStack_38;
          plStack_18 = plStack_30;
          uStack_40 = 0;
          puStack_38 = &uStack_28;
          while( true ) {
            cVar3 = FUN_7ffe9ae37290(&uStack_28);
            plVar2 = plStack_18;
            if (cVar3 == '\0') {
              func_0x7ffe999c3920(&uStack_28,_DAT_7ffe9c937818);
              return iVar7;
            }
            if (plStack_18 == (longlong *)0x0) break;
            bVar4 = MobPartsStatus_get_IsDead((undefined *)plStack_18,(undefined *)0x0);
            if (bVar4 == 0) {
              lVar6 = *plVar2;
              iVar5 = (**(code **)(lVar6 + 0x178))(plVar2,*(undefined8 *)(lVar6 + 0x180));
              iVar7 = iVar7 + iVar5;
            }
          }
          goto LAB_7ffe9a323c04;
        }
      }
    }
    else if (puStackX_18 != (undefined *)0x0) {
      bVar4 = MobPropertyHighRaidCalcExceptionFlag_FixedNecessaryHitFlag
                        (puStackX_18,(undefined *)0x0);
      if (bVar4 == 0) goto LAB_7ffe9a323abe;
      if (*(longlong *)(self + 0x10) == 0) goto LAB_7ffe9a323bfe;
      iVar7 = *(int *)(*(longlong *)(self + 0x10) + 0x38);
      goto LAB_7ffe9a323af3;
    }
  }
LAB_7ffe9a323bfe:
  FUN_7ffe9996d7a0();
LAB_7ffe9a323c04:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar1 = (code *)swi(3);
  iVar7 = (*pcVar1)();
  return iVar7;
}

