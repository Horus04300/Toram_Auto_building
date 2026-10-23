
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * LocalizeManager_Get(undefined *self,undefined *type,undefined *methodInfo)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  longlong lVar4;
  char cVar5;
  uint uVar6;
  undefined8 uVar7;
  undefined *puVar8;
  undefined8 unaff_RDI;
  
  if (DAT_7fff625e151c == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62462c88);
    FUN_7fff5f47d450(&DAT_7fff62462e20);
    FUN_7fff5f47d450(&DAT_7fff62462fb8);
    FUN_7fff5f47d450(0x7fff62447458);
    DAT_7fff625e151c = '\x01';
  }
  if (*(longlong *)(self + 0x20) != 0) {
    cVar5 = FUN_7fff60869460(*(longlong *)(self + 0x20),(ulonglong)type & 0xffffffff,
                             _DAT_7fff62462e20);
    if (cVar5 == '\0') {
      lVar1 = *(longlong *)(self + 0x20);
      uVar7 = FUN_7fff5f559c70(self,(ulonglong)type & 0xffffffff,0);
      if (lVar1 == 0) goto LAB_7fff5f55aeef;
      FUN_7fff6088cb20(lVar1,(ulonglong)type & 0xffffffff,uVar7,_DAT_7fff62462c88);
    }
    lVar4 = _DAT_7fff62462fb8;
    lVar1 = *(longlong *)(self + 0x20);
    if (lVar1 != 0) {
      lVar2 = *(longlong *)(*(longlong *)(_DAT_7fff62462fb8 + 0x20) + 0xc0);
      uVar6 = FUN_7fff6086aa60(lVar1,(ulonglong)type & 0xffffffff,*(undefined8 *)(lVar2 + 0x110),
                               lVar2,unaff_RDI);
      if ((int)uVar6 < 0) {
        uVar7 = func_0x7fff5f47c7a0(*(undefined8 *)
                                     (*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70),
                                    &stack0x00000010);
        FUN_7fff610328a0(uVar7,0);
        return (undefined *)0x0;
      }
      lVar1 = *(longlong *)(lVar1 + 0x18);
      if (lVar1 != 0) {
        if (uVar6 < *(uint *)(lVar1 + 0x18)) {
          return *(undefined **)(lVar1 + 0x30 + (longlong)(int)uVar6 * 0x18);
        }
        FUN_7fff5f47d650();
        pcVar3 = (code *)swi(3);
        puVar8 = (undefined *)(*pcVar3)();
        return puVar8;
      }
      FUN_7fff5f47d660();
      pcVar3 = (code *)swi(3);
      puVar8 = (undefined *)(*pcVar3)();
      return puVar8;
    }
  }
LAB_7fff5f55aeef:
  FUN_7fff5f47d660();
  pcVar3 = (code *)swi(3);
  puVar8 = (undefined *)(*pcVar3)();
  return puVar8;
}

