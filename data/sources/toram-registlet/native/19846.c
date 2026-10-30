
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBufferManager_ClearBuffer(undefined *self,undefined *methodInfo)

{
  undefined8 uVar1;
  undefined8 uVar2;
  code *pcVar3;
  char cVar4;
  longlong lVar5;
  longlong lVar6;
  longlong *plVar7;
  undefined *self_00;
  uint uVar8;
  
  if (DAT_7ffe9cade795 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c965580);
    FUN_7ffe9996d590(&DAT_7ffe9c907f28);
    FUN_7ffe9996d590(&DAT_7ffe9c9375f8);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c956ad0);
    FUN_7ffe9996d590(&DAT_7ffe9c945f90);
    FUN_7ffe9996d590(&DAT_7ffe9c956928);
    DAT_7ffe9cade795 = '\x01';
  }
  if (*(longlong *)(self + 0x18) == 0) goto LAB_7ffe9a5b20b8;
  FUN_7ffe9acce330(*(longlong *)(self + 0x18),_DAT_7ffe9c965580);
  uVar1 = *(undefined8 *)(self + 0x10);
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar4 = FUN_7ffe9bda2160(uVar1,0,0);
  if (cVar4 != '\0') {
    if (*(longlong *)(self + 0x10) == 0) goto LAB_7ffe9a5b20b8;
    lVar6 = FUN_7ffe9a47f190(*(longlong *)(self + 0x10),0);
    if (lVar6 == 0) goto LAB_7ffe9a5b20b8;
    FUN_7ffe9a4e9240(lVar6,0);
    if ((*(longlong *)(self + 0x10) == 0) ||
       (lVar6 = *(longlong *)(*(longlong *)(self + 0x10) + 0x70), lVar6 == 0))
    goto LAB_7ffe9a5b20b8;
    uVar1 = *(undefined8 *)(lVar6 + 0x10);
    if (*(int *)(_DAT_7ffe9c956928 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    lVar6 = *(longlong *)(*(longlong *)(_DAT_7ffe9c956928 + 0xb8) + 0x18);
    if (lVar6 == 0) {
      if (*(int *)(_DAT_7ffe9c956928 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      uVar2 = **(undefined8 **)(_DAT_7ffe9c956928 + 0xb8);
      lVar6 = func_0x7ffe99940040(_DAT_7ffe9c9375f8);
      FUN_7ffe9af13420(lVar6,uVar2,_DAT_7ffe9c945f90,0);
      *(longlong *)(*(longlong *)(_DAT_7ffe9c956928 + 0xb8) + 0x18) = lVar6;
      il2cpp_write_barrier_0();
    }
    lVar6 = FUN_7ffe9ab854c0(uVar1,lVar6,_DAT_7ffe9c907f28);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar4 = FUN_7ffe9bda2160(lVar6,0,0);
    if (cVar4 != '\0') {
      if (lVar6 == 0) goto LAB_7ffe9a5b20b8;
      plVar7 = (longlong *)FUN_7ffe9a4ca6d0(lVar6,0);
      if (plVar7 == (longlong *)0x0) goto LAB_7ffe9a5b20b8;
      plVar7 = (longlong *)(**(code **)(*plVar7 + 0x298))(plVar7,*(undefined8 *)(*plVar7 + 0x2a0));
      if (plVar7 == (longlong *)0x0) goto LAB_7ffe9a5b20b8;
      self_00 = (undefined *)(**(code **)(*plVar7 + 0x218))(plVar7);
      if (self_00 == (undefined *)0x0) goto LAB_7ffe9a5b20b8;
      GemCartBufferManager_ClearBuffer(self_00,(undefined *)0x0);
    }
  }
  lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
  if (lVar6 == 0) {
LAB_7ffe9a5b20b8:
    FUN_7ffe9996d7a0();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  if (DAT_7ffe9cadd16f == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906b90,0);
    FUN_7ffe9996d590(&DAT_7ffe9c955948);
    DAT_7ffe9cadd16f = '\x01';
  }
  lVar5 = FUN_7ffe9b141840(_DAT_7ffe9c955948);
  if (lVar5 != 0) {
    uVar1 = *(undefined8 *)(lVar5 + 0x50);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar4 = FUN_7ffe9bda1fa0(uVar1,0,0);
    if (cVar4 == '\0') {
      lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c955948);
      if ((lVar6 == 0) || (*(longlong *)(lVar6 + 0x50) == 0)) goto LAB_7ffe9a29ae85;
      FUN_7ffe99d1a7d0(*(longlong *)(lVar6 + 0x50),0);
    }
    else {
      lVar6 = *(longlong *)(lVar6 + 0xe8);
      uVar8 = 0;
      if (lVar6 == 0) goto LAB_7ffe9a29ae85;
      for (; (int)uVar8 < *(int *)(lVar6 + 0x18); uVar8 = uVar8 + 1) {
        if (*(uint *)(lVar6 + 0x18) <= uVar8) {
          FUN_7ffe9996d790();
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
        lVar5 = *(longlong *)(lVar6 + 0x20 + (longlong)(int)uVar8 * 8);
        if (lVar5 == 0) goto LAB_7ffe9a29ae85;
        FUN_7ffe99cde8c0(lVar5,0);
      }
    }
    return;
  }
LAB_7ffe9a29ae85:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

