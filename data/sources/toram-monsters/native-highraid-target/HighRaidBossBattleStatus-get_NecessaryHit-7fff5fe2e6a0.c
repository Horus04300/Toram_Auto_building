
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int HighRaidBossBattleStatus_get_NecessaryHit(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  longlong *plVar2;
  char cVar3;
  int iVar4;
  longlong lVar5;
  int iVar6;
  undefined8 uVar7;
  undefined *methodInfo_00;
  longlong lStackX_18;
  undefined8 uStack_40;
  undefined8 *puStack_38;
  longlong *plStack_30;
  undefined8 uStack_28;
  undefined8 *puStack_20;
  longlong *plStack_18;
  
  if (DAT_7fff625e4c94 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62406640);
    FUN_7fff5f47d450(&DAT_7fff6243e768);
    FUN_7fff5f47d450(&DAT_7fff6243e830);
    FUN_7fff5f47d450(0x7fff6243e8f0);
    FUN_7fff5f47d450(&DAT_7fff62400b90);
    DAT_7fff625e4c94 = '\x01';
  }
  lStackX_18 = 0;
  if (DAT_7fff625e4ca0 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff624309c0);
    DAT_7fff625e4ca0 = '\x01';
  }
  if ((*(longlong *)(self + 0x10) != 0) &&
     (lVar5 = *(longlong *)(*(longlong *)(self + 0x10) + 0xa0), lVar5 != 0)) {
    methodInfo_00 = _DAT_7fff624309c0;
    cVar3 = FUN_7fff606c2a90(lVar5,0x20,&lStackX_18);
    if (cVar3 == '\0') {
LAB_7fff5fe2e78e:
      if (*(longlong *)(self + 0x10) != 0) {
        iVar6 = (int)((float)*(int *)(self + 0x30) * _DAT_7fff61b52cd8 *
                     ((float)*(int *)(*(longlong *)(self + 0x10) + 0x38) / _DAT_7fff61b52cfc));
LAB_7fff5fe2e7c3:
        if ((*(longlong *)(self + 0x38) != 0) &&
           (lVar5 = FUN_7fff607dcb60(*(longlong *)(self + 0x38),_DAT_7fff62406640), lVar5 != 0)) {
          uVar7 = _DAT_7fff62400b90;
          FUN_7fff60a4b980(&uStack_40,lVar5);
          uStack_28 = uStack_40;
          puStack_20 = puStack_38;
          plStack_18 = plStack_30;
          uStack_40 = 0;
          puStack_38 = &uStack_28;
          while( true ) {
            cVar3 = FUN_7fff60941650(&uStack_28,_DAT_7fff6243e830);
            plVar2 = plStack_18;
            if (cVar3 == '\0') {
              HighRaidRoomData_LoadAsset
                        ((undefined *)&uStack_28,(byte)_DAT_7fff6243e768,(short)uVar7,methodInfo_00)
              ;
              return iVar6;
            }
            if (plStack_18 == (longlong *)0x0) break;
            cVar3 = func_0x7fff5fe666a0(plStack_18,0);
            if (cVar3 == '\0') {
              lVar5 = *plVar2;
              iVar4 = (**(code **)(lVar5 + 0x178))(plVar2,*(undefined8 *)(lVar5 + 0x180));
              iVar6 = iVar6 + iVar4;
            }
          }
          goto LAB_7fff5fe2e8d4;
        }
      }
    }
    else if (lStackX_18 != 0) {
      cVar3 = FUN_7fff5fe84a40(lStackX_18,0);
      if (cVar3 == '\0') goto LAB_7fff5fe2e78e;
      if (*(longlong *)(self + 0x10) == 0) goto LAB_7fff5fe2e8ce;
      iVar6 = *(int *)(*(longlong *)(self + 0x10) + 0x38);
      goto LAB_7fff5fe2e7c3;
    }
  }
LAB_7fff5fe2e8ce:
  FUN_7fff5f47d660();
LAB_7fff5fe2e8d4:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar1 = (code *)swi(3);
  iVar6 = (*pcVar1)();
  return iVar6;
}

