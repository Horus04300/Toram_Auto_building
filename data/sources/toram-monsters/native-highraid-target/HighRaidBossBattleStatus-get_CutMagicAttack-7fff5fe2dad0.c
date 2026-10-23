
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int HighRaidBossBattleStatus_get_CutMagicAttack(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  longlong lVar4;
  int iVar5;
  undefined8 uVar6;
  undefined *in_R9;
  longlong lStackX_20;
  undefined8 uStack_50;
  undefined8 *puStack_48;
  longlong lStack_40;
  undefined8 uStack_38;
  undefined8 *puStack_30;
  longlong lStack_28;
  
  if (DAT_7fff625e4c98 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62406640);
    FUN_7fff5f47d450(&DAT_7fff6243e768);
    FUN_7fff5f47d450(&DAT_7fff6243e830);
    FUN_7fff5f47d450(0x7fff6243e8f0);
    FUN_7fff5f47d450(&DAT_7fff62400b90);
    DAT_7fff625e4c98 = '\x01';
  }
  lStackX_20 = 0;
  iVar5 = 0;
  if ((*(longlong *)(self + 0x38) != 0) &&
     (lVar4 = FUN_7fff607dcb60(*(longlong *)(self + 0x38),_DAT_7fff62406640), lVar4 != 0)) {
    uVar6 = _DAT_7fff62400b90;
    FUN_7fff60a4b980(&uStack_50,lVar4);
    uStack_38 = uStack_50;
    puStack_30 = puStack_48;
    lStack_28 = lStack_40;
    uStack_50 = 0;
    puStack_48 = &uStack_38;
    while (cVar2 = FUN_7fff60941650(&uStack_38,_DAT_7fff6243e830), lVar4 = lStack_28, cVar2 != '\0')
    {
      if (lStack_28 == 0) goto LAB_7fff5fe2dd02;
      if ((*(longlong *)(lStack_28 + 0x20) != 0) &&
         (cVar2 = func_0x7fff5fe666a0(lStack_28,0), cVar2 == '\0')) {
        if (*(longlong *)(lVar4 + 0x20) == 0) goto LAB_7fff5fe2dcfc;
        iVar3 = FUN_7fff5fe83cd0(*(longlong *)(lVar4 + 0x20),0);
        iVar5 = iVar5 + iVar3;
      }
    }
    HighRaidRoomData_LoadAsset((undefined *)&uStack_38,(byte)_DAT_7fff6243e768,(short)uVar6,in_R9);
    if (DAT_7fff625e4ca0 == '\0') {
      FUN_7fff5f47d450(&DAT_7fff624309c0);
      DAT_7fff625e4ca0 = '\x01';
    }
    if ((*(longlong *)(self + 0x10) == 0) ||
       (lVar4 = *(longlong *)(*(longlong *)(self + 0x10) + 0xa0), lVar4 == 0))
    goto LAB_7fff5fe2dcf6;
    cVar2 = FUN_7fff606c2a90(lVar4,0x20,&lStackX_20,_DAT_7fff624309c0);
    if (cVar2 != '\0') {
      if (lStackX_20 == 0) goto LAB_7fff5fe2dcf6;
      cVar2 = FUN_7fff5fe84880(lStackX_20,0);
      if (cVar2 != '\0') {
        if (*(longlong *)(self + 0x10) == 0) goto LAB_7fff5fe2dcf6;
        iVar3 = *(int *)(*(longlong *)(self + 0x10) + 0x48);
        goto LAB_7fff5fe2dcbe;
      }
    }
    if (*(longlong *)(self + 0x10) != 0) {
      iVar3 = *(int *)(*(longlong *)(self + 0x10) + 0x48) -
              (int)((float)*(int *)(self + 0x30) * _DAT_7fff61b53a88);
LAB_7fff5fe2dcbe:
      return iVar3 + iVar5;
    }
  }
LAB_7fff5fe2dcf6:
  FUN_7fff5f47d660();
LAB_7fff5fe2dcfc:
  FUN_7fff5f47d660();
LAB_7fff5fe2dd02:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar1 = (code *)swi(3);
  iVar5 = (*pcVar1)();
  return iVar5;
}

