
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MobAttackBase_CheckActionType(undefined *self,undefined *actionTypes,undefined *methodInfo)

{
  undefined4 uVar1;
  code *pcVar2;
  byte bVar3;
  longlong lVar4;
  longlong lVar5;
  undefined8 unaff_RDI;
  
  if (DAT_7ffe9cadd7ce == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8fd968);
    DAT_7ffe9cadd7ce = '\x01';
  }
  lVar5 = _DAT_7ffe9c8fd968;
  if (actionTypes != (undefined *)0x0) {
    if (*(longlong *)(self + 0xa0) != 0) {
      uVar1 = *(undefined4 *)(*(longlong *)(self + 0xa0) + 0x3c);
      if (*(longlong *)(_DAT_7ffe9c8fd968 + 0x38) == 0) {
        FUN_7ffe998cedc0(_DAT_7ffe9c8fd968);
      }
      lVar4 = *(longlong *)(*(longlong *)(lVar5 + 0x38) + 8);
      if ((*(byte *)(lVar4 + 0x135) & 1) == 0) {
        lVar4 = FUN_7ffe998ced40(lVar4);
      }
      lVar4 = func_0x7ffe9996c920(actionTypes,lVar4);
      lVar5 = *(longlong *)(lVar5 + 0x38);
      if (lVar4 == 0) {
        bVar3 = FUN_7ffe9ab7f620(actionTypes,uVar1,0,*(undefined8 *)(lVar5 + 0x20));
      }
      else {
        lVar5 = *(longlong *)(lVar5 + 8);
        if ((*(byte *)(lVar5 + 0x135) & 1) == 0) {
          lVar5 = FUN_7ffe998ced40(lVar5);
        }
        bVar3 = FUN_7ffe99749320(4,lVar5,lVar4,uVar1,unaff_RDI);
      }
      return bVar3;
    }
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    bVar3 = (*pcVar2)();
    return bVar3;
  }
  return 0;
}

