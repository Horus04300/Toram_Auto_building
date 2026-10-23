
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int HighRaidBossBattleStatus_get_Def(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  longlong *plVar2;
  char cVar3;
  int iVar4;
  longlong lVar5;
  int iVar6;
  undefined8 uVar7;
  undefined *methodInfo_00;
  longlong lStackX_20;
  undefined8 uStack_50;
  undefined8 *puStack_48;
  longlong *plStack_40;
  undefined8 uStack_38;
  undefined8 *puStack_30;
  longlong *plStack_28;
  
  if (DAT_7fff625e4c95 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62406640);
    FUN_7fff5f47d450(&DAT_7fff6243e768);
    FUN_7fff5f47d450(&DAT_7fff6243e830);
    FUN_7fff5f47d450(0x7fff6243e8f0);
    FUN_7fff5f47d450(&DAT_7fff62400b90);
    DAT_7fff625e4c95 = '\x01';
  }
  lStackX_20 = 0;
  if (DAT_7fff625e4ca0 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff624309c0);
    DAT_7fff625e4ca0 = '\x01';
  }
  if ((*(longlong *)(self + 0x10) == 0) ||
     (lVar5 = *(longlong *)(*(longlong *)(self + 0x10) + 0xa0), lVar5 == 0)) goto LAB_7fff5fe2dfb8;
  methodInfo_00 = _DAT_7fff624309c0;
  cVar3 = FUN_7fff606c2a90(lVar5,0x20,&lStackX_20);
  if (cVar3 == '\0') {
LAB_7fff5fe2de01:
    if (*(longlong *)(self + 0x10) == 0) goto LAB_7fff5fe2dfb8;
    iVar6 = (int)((float)*(int *)(self + 0x30) *
                 ((float)*(int *)(*(longlong *)(self + 0x10) + 0x3c) / _DAT_7fff61b52cfc));
  }
  else {
    if (lStackX_20 == 0) goto LAB_7fff5fe2dfb8;
    cVar3 = FUN_7fff5fe848f0(lStackX_20,0);
    if (cVar3 == '\0') goto LAB_7fff5fe2de01;
    if (*(longlong *)(self + 0x10) == 0) goto LAB_7fff5fe2dfb8;
    iVar6 = *(int *)(*(longlong *)(self + 0x10) + 0x3c);
  }
  if ((*(longlong *)(self + 0x38) != 0) &&
     (lVar5 = FUN_7fff607dcb60(*(longlong *)(self + 0x38),_DAT_7fff62406640), lVar5 != 0)) {
    uVar7 = _DAT_7fff62400b90;
    FUN_7fff60a4b980(&uStack_50,lVar5);
    uStack_38 = uStack_50;
    puStack_30 = puStack_48;
    plStack_28 = plStack_40;
    uStack_50 = 0;
    puStack_48 = &uStack_38;
    while (cVar3 = FUN_7fff60941650(&uStack_38,_DAT_7fff6243e830), plVar2 = plStack_28,
          cVar3 != '\0') {
      if (plStack_28 == (longlong *)0x0) goto LAB_7fff5fe2dfbe;
      cVar3 = func_0x7fff5fe666a0(plStack_28,0);
      if (cVar3 == '\0') {
        lVar5 = *plVar2;
        iVar4 = (**(code **)(lVar5 + 0x188))(plVar2,*(undefined8 *)(lVar5 + 400));
        iVar6 = iVar6 + iVar4;
      }
    }
    HighRaidRoomData_LoadAsset
              ((undefined *)&uStack_38,(byte)_DAT_7fff6243e768,(short)uVar7,methodInfo_00);
    if (*(longlong *)(self + 0x20) != 0) {
      iVar4 = FUN_7fff5fdb72d0(*(longlong *)(self + 0x20),2);
      iVar6 = (int)(((float)iVar4 / _DAT_7fff61b52cfc + _DAT_7fff61b52b18) * (float)iVar6);
      if (*(longlong *)(self + 0x18) != 0) {
        cVar3 = FUN_7fff5ffe5620(*(longlong *)(self + 0x18),10);
        if (cVar3 != '\0') {
          iVar6 = (int)((float)iVar6 * _DAT_7fff61b52b4c);
        }
        return iVar6;
      }
    }
  }
LAB_7fff5fe2dfb8:
  FUN_7fff5f47d660();
LAB_7fff5fe2dfbe:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar1 = (code *)swi(3);
  iVar6 = (*pcVar1)();
  return iVar6;
}

