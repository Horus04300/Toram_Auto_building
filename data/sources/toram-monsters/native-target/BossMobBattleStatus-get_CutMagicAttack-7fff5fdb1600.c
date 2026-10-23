
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BossMobBattleStatus_get_CutMagicAttack(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  undefined *puVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  longlong lVar6;
  int iVar7;
  undefined8 uStack_50;
  undefined8 *puStack_48;
  undefined *puStack_40;
  undefined8 uStack_38;
  undefined8 *puStack_30;
  undefined *puStack_28;
  
  if (DAT_7fff625e4931 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62406640);
    FUN_7fff5f47d450(&DAT_7fff6243e768);
    FUN_7fff5f47d450(&DAT_7fff6243e830);
    FUN_7fff5f47d450(0x7fff6243e8f0);
    FUN_7fff5f47d450(&DAT_7fff62400b90);
    DAT_7fff625e4931 = '\x01';
  }
  iVar7 = 0;
  if ((*(longlong *)(self + 0x30) != 0) &&
     (lVar6 = FUN_7fff607dcb60(*(longlong *)(self + 0x30),_DAT_7fff62406640), lVar6 != 0)) {
    FUN_7fff60a4b980(&uStack_50,lVar6,_DAT_7fff62400b90);
    uStack_38 = uStack_50;
    puStack_30 = puStack_48;
    puStack_28 = puStack_40;
    uStack_50 = 0;
    puStack_48 = &uStack_38;
    while (cVar3 = FUN_7fff60941650(&uStack_38), puVar2 = puStack_28, cVar3 != '\0') {
      if (puStack_28 == (undefined *)0x0) goto LAB_7fff5fdb1796;
      if ((*(longlong *)(puStack_28 + 0x20) != 0) &&
         (bVar4 = MobPartsStatus_get_IsDead(puStack_28,(undefined *)0x0), bVar4 == 0)) {
        if (*(undefined **)(puVar2 + 0x20) == (undefined *)0x0) goto LAB_7fff5fdb1790;
        iVar5 = MobPropertyCut_get_CutMagicAttack(*(undefined **)(puVar2 + 0x20),(undefined *)0x0);
        iVar7 = iVar7 + iVar5;
      }
    }
    func_0x7fff5f4d3920(&uStack_38,_DAT_7fff6243e768);
    if (*(longlong *)(self + 0x10) != 0) {
      return *(int *)(*(longlong *)(self + 0x10) + 0x48) + iVar7;
    }
  }
  FUN_7fff5f47d660();
LAB_7fff5fdb1790:
  FUN_7fff5f47d660();
LAB_7fff5fdb1796:
  FUN_7fff5f47d660();
  FUN_7fff5f40a410();
  pcVar1 = (code *)swi(3);
  iVar7 = (*pcVar1)();
  return iVar7;
}

