
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * MasterRegistletManager_GetGemCartMaster(undefined *self,short id,undefined *methodInfo)

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
  short asStackX_10 [4];
  
  if (DAT_7ffe9cade7c3 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c965d78);
    FUN_7ffe9996d590(&DAT_7ffe9c965e48);
    DAT_7ffe9cade7c3 = '\x01';
  }
  if (*(longlong *)(self + 0x20) != 0) {
    cVar5 = FUN_7ffe9ad11000(*(longlong *)(self + 0x20),id,_DAT_7ffe9c965d78);
    lVar3 = _DAT_7ffe9c965e48;
    if (cVar5 == '\0') {
      return (undefined *)0x0;
    }
    lVar1 = *(longlong *)(self + 0x20);
    if (lVar1 != 0) {
      lVar2 = *(longlong *)(*(longlong *)(_DAT_7ffe9c965e48 + 0x20) + 0xc0);
      uVar6 = FUN_7ffe9ad11880(lVar1,id,*(undefined8 *)(lVar2 + 0x110),lVar2,unaff_RDI);
      if ((int)uVar6 < 0) {
        asStackX_10[0] = id;
        uVar7 = func_0x7ffe9996c8e0(*(undefined8 *)
                                     (*(longlong *)(*(longlong *)(lVar3 + 0x20) + 0xc0) + 0x70),
                                    asStackX_10);
        FUN_7ffe9b5284e0(uVar7,0);
        return (undefined *)0x0;
      }
      lVar3 = *(longlong *)(lVar1 + 0x18);
      if (lVar3 != 0) {
        if (uVar6 < *(uint *)(lVar3 + 0x18)) {
          return *(undefined **)(lVar3 + 0x30 + (longlong)(int)uVar6 * 0x18);
        }
        FUN_7ffe9996d790();
        pcVar4 = (code *)swi(3);
        puVar8 = (undefined *)(*pcVar4)();
        return puVar8;
      }
      FUN_7ffe9996d7a0();
      pcVar4 = (code *)swi(3);
      puVar8 = (undefined *)(*pcVar4)();
      return puVar8;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar4 = (code *)swi(3);
  puVar8 = (undefined *)(*pcVar4)();
  return puVar8;
}

