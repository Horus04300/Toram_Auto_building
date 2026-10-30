
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBufferManager_UpdateMercenaryGemCart
               (undefined *self,undefined *mercenary,undefined *methodInfo)

{
  code *pcVar1;
  longlong *plVar2;
  char cVar3;
  short id;
  undefined4 uVar4;
  longlong lVar5;
  longlong *plVar6;
  undefined *self_00;
  undefined8 uStack_40;
  undefined8 *puStack_38;
  longlong *plStack_30;
  undefined8 uStack_28;
  undefined8 uStack_20;
  longlong *plStack_18;
  
  if (DAT_7ffe9cade798 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c965a48);
    FUN_7ffe9996d590(&DAT_7ffe9c92ec68);
    FUN_7ffe9996d590(&DAT_7ffe9c92ed30);
    FUN_7ffe9996d590(0x7ffe9c92edf0);
    FUN_7ffe9996d590(&DAT_7ffe9c91faa8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f8710);
    DAT_7ffe9cade798 = '\x01';
  }
  if (*(longlong *)(self + 0x18) != 0) {
    lVar5 = FUN_7ffe9acd27a0(*(longlong *)(self + 0x18),_DAT_7ffe9c965a48);
    if (lVar5 != 0) {
      FUN_7ffe9af415c0(&uStack_40,lVar5,_DAT_7ffe9c8f8710);
      uStack_28 = uStack_40;
      uStack_20 = puStack_38;
      plStack_18 = plStack_30;
      uStack_40 = 0;
      puStack_38 = &uStack_28;
LAB_7ffe9a5b3f50:
      cVar3 = FUN_7ffe9ae37290(&uStack_28,_DAT_7ffe9c92ed30);
      plVar2 = plStack_18;
      if (cVar3 == '\0') {
        func_0x7ffe999c3920(&uStack_28,_DAT_7ffe9c92ec68);
        return;
      }
      lVar5 = *(longlong *)(self + 0x28);
      if (plStack_18 == (longlong *)0x0) goto LAB_7ffe9a5b4097;
      uVar4 = (**(code **)(*plStack_18 + 0x178))(plStack_18,*(undefined8 *)(*plStack_18 + 0x180));
      if (lVar5 != 0) goto code_r0x7ffe9a5b3f9a;
      goto LAB_7ffe9a5b4092;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
code_r0x7ffe9a5b3f9a:
  cVar3 = FUN_7ffe9afc8940(lVar5,uVar4,_DAT_7ffe9c91faa8);
  if (cVar3 != '\0') {
    if (mercenary != (undefined *)0x0) {
      plVar6 = (longlong *)FUN_7ffe9a4ca6d0(mercenary,0);
      if (plVar6 != (longlong *)0x0) {
        plVar6 = (longlong *)(**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0))
        ;
        if (plVar6 != (longlong *)0x0) {
          self_00 = (undefined *)
                    (**(code **)(*plVar6 + 0x218))(plVar6,*(undefined8 *)(*plVar6 + 0x220));
          id = (**(code **)(*plVar2 + 0x178))(plVar2,*(undefined8 *)(*plVar2 + 0x180));
          if (self_00 != (undefined *)0x0) {
            GemCartBufferManager_UpdateEquipGemCartData
                      (self_00,id,*(short *)((longlong)plVar2 + 0x14),(undefined *)0x0);
            goto LAB_7ffe9a5b3f50;
          }
          FUN_7ffe9996d7a0();
        }
        FUN_7ffe9996d7a0();
      }
      FUN_7ffe9996d7a0();
    }
    FUN_7ffe9996d7a0();
LAB_7ffe9a5b4092:
    FUN_7ffe9996d7a0();
LAB_7ffe9a5b4097:
    FUN_7ffe9996d7a0();
    FUN_7ffe998fa550();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  goto LAB_7ffe9a5b3f50;
}

