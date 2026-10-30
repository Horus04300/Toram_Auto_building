
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBufferManager_ChangeEquipGemCartData
               (undefined *self,undefined *equips,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  char cVar5;
  longlong lVar6;
  uint uVar7;
  longlong lStackX_10;
  
  if (DAT_7ffe9cade799 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9658b0);
    FUN_7ffe9996d590(&DAT_7ffe9c9448f8);
    DAT_7ffe9cade799 = '\x01';
  }
  uVar7 = 0;
  lStackX_10 = 0;
  if (equips == (undefined *)0x0) {
LAB_7ffe9a5b1d1c:
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  do {
    if ((int)*(uint *)(equips + 0x18) <= (int)uVar7) {
      return;
    }
    if (*(uint *)(equips + 0x18) <= uVar7) {
      FUN_7ffe9996d790();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    lVar1 = *(longlong *)(equips + (longlong)(int)uVar7 * 8 + 0x20);
    if ((lVar1 == 0) || (lVar6 = *(longlong *)(lVar1 + 0x10), lVar6 == 0)) goto LAB_7ffe9a5b1d1c;
    GemCartBufferManager_UpdateEquipGemCartData
              (self,*(short *)(lVar6 + 0x20),*(short *)(lVar6 + 0x22),(undefined *)0x0);
    if ((*(longlong *)(lVar1 + 0x10) == 0) || (*(longlong *)(self + 0x18) == 0))
    goto LAB_7ffe9a5b1d1c;
    cVar5 = FUN_7ffe9ad1e480(*(longlong *)(self + 0x18),
                             *(undefined2 *)(*(longlong *)(lVar1 + 0x10) + 0x20),&lStackX_10);
    if ((cVar5 != '\0') &&
       (lVar6 = func_0x7ffe9996c920(lStackX_10,_DAT_7ffe9c9448f8), lVar1 = lStackX_10,
       uVar3 = _DAT_7ffe9c9448f8, lVar6 != 0)) {
      if (lStackX_10 == 0) goto LAB_7ffe9a5b1d1c;
      lVar6 = func_0x7ffe9996c920(lStackX_10,_DAT_7ffe9c9448f8);
      uVar4 = _DAT_7ffe9c9448f8;
      if (lVar6 == 0) {
        FUN_7ffe9996c950(lVar1,uVar3);
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      lVar6 = func_0x7ffe9996c920(lVar1,_DAT_7ffe9c9448f8);
      if (lVar6 == 0) {
        FUN_7ffe9996c950(lVar1,uVar4);
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      FUN_7ffe99742cf0(0,_DAT_7ffe9c9448f8,lVar6);
    }
    uVar7 = uVar7 + 1;
  } while( true );
}

