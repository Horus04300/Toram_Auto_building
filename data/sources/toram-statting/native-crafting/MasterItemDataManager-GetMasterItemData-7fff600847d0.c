
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * MasterItemDataManager_GetMasterItemData(undefined *self,int id,undefined *methodInfo)

{
  longlong lVar1;
  longlong lVar2;
  longlong lVar3;
  code *pcVar4;
  char cVar5;
  uint uVar6;
  undefined8 uVar7;
  undefined *puVar8;
  undefined8 unaff_RDI;
  int aiStackX_10 [2];
  
  if (DAT_7fff625e5cf4 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62401500);
    FUN_7fff5f47d450(&DAT_7fff62401770);
    DAT_7fff625e5cf4 = '\x01';
  }
  if (*(longlong *)(self + 0x20) != 0) {
    cVar5 = FUN_7fff6082f170(*(longlong *)(self + 0x20),id,_DAT_7fff62401500);
    lVar3 = _DAT_7fff62401770;
    if (cVar5 == '\0') {
      return (undefined *)0x0;
    }
    lVar1 = *(longlong *)(self + 0x20);
    if (lVar1 != 0) {
      lVar2 = *(longlong *)(*(longlong *)(_DAT_7fff62401770 + 0x20) + 0xc0);
      uVar6 = FUN_7fff6082fdf0(lVar1,id,*(undefined8 *)(lVar2 + 0x110),lVar2,unaff_RDI);
      if ((int)uVar6 < 0) {
        aiStackX_10[0] = id;
        uVar7 = func_0x7fff5f47c7a0(*(undefined8 *)
                                     (*(longlong *)(*(longlong *)(lVar3 + 0x20) + 0xc0) + 0x70),
                                    aiStackX_10);
        FUN_7fff610328a0(uVar7,0);
        return (undefined *)0x0;
      }
      lVar3 = *(longlong *)(lVar1 + 0x18);
      if (lVar3 != 0) {
        if (uVar6 < *(uint *)(lVar3 + 0x18)) {
          return *(undefined **)(lVar3 + 0x30 + (longlong)(int)uVar6 * 0x18);
        }
        FUN_7fff5f47d650();
        pcVar4 = (code *)swi(3);
        puVar8 = (undefined *)(*pcVar4)();
        return puVar8;
      }
      FUN_7fff5f47d660();
      pcVar4 = (code *)swi(3);
      puVar8 = (undefined *)(*pcVar4)();
      return puVar8;
    }
  }
  FUN_7fff5f47d660();
  pcVar4 = (code *)swi(3);
  puVar8 = (undefined *)(*pcVar4)();
  return puVar8;
}

