
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBufferManager_RemoveGemCartBuffer(undefined *self,short id,undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  char cVar3;
  longlong lVar4;
  longlong lVar5;
  undefined8 uVar6;
  longlong *plVar7;
  undefined *self_00;
  
  while( true ) {
    if (DAT_7ffe9cade794 == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c965650);
      FUN_7ffe9996d590(&DAT_7ffe9c9657e8);
      FUN_7ffe9996d590(&DAT_7ffe9c8f88f8);
      FUN_7ffe9996d590(&DAT_7ffe9c907f28);
      FUN_7ffe9996d590(&DAT_7ffe9c93b270);
      FUN_7ffe9996d590(&DAT_7ffe9c9375f8);
      FUN_7ffe9996d590(&DAT_7ffe9c906b90);
      FUN_7ffe9996d590(&DAT_7ffe9c946118);
      FUN_7ffe9996d590(&DAT_7ffe9c9461e0);
      FUN_7ffe9996d590(&DAT_7ffe9c946428);
      FUN_7ffe9996d590(&DAT_7ffe9c9464f0);
      FUN_7ffe9996d590(&DAT_7ffe9c9569f0);
      FUN_7ffe9996d590(&DAT_7ffe9c956928);
      DAT_7ffe9cade794 = '\x01';
    }
    lVar4 = func_0x7ffe99940040(_DAT_7ffe9c9569f0);
    func_0x7ffe999c3920(lVar4,0);
    if (lVar4 == 0) break;
    *(short *)(lVar4 + 0x10) = id;
    if (*(longlong *)(self + 0x18) == 0) break;
    cVar3 = FUN_7ffe9ad11000(*(longlong *)(self + 0x18),id,_DAT_7ffe9c965650);
    if (cVar3 == '\0') {
      return;
    }
    if (*(longlong *)(self + 0x18) == 0) break;
    FUN_7ffe9ad161b0(*(longlong *)(self + 0x18),*(undefined2 *)(lVar4 + 0x10),_DAT_7ffe9c9657e8);
    uVar1 = *(undefined8 *)(self + 0x10);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar3 = FUN_7ffe9bda2160(uVar1,0,0);
    if (cVar3 == '\0') {
      return;
    }
    if ((*(longlong *)(self + 0x10) == 0) ||
       (lVar5 = FUN_7ffe9a47f190(*(longlong *)(self + 0x10),0), lVar5 == 0)) break;
    FUN_7ffe9a4ec280(lVar5,*(undefined2 *)(lVar4 + 0x10),0);
    uVar1 = *(undefined8 *)(self + 0x20);
    uVar6 = func_0x7ffe99940040(_DAT_7ffe9c93b270);
    FUN_7ffe9af155b0(uVar6,lVar4,_DAT_7ffe9c946428,0);
    cVar3 = FUN_7ffe9ab7a900(uVar1,uVar6,_DAT_7ffe9c8f88f8);
    if (cVar3 != '\0') {
      if ((*(longlong *)(self + 0x10) == 0) ||
         (lVar5 = *(longlong *)(*(longlong *)(self + 0x10) + 0x70), lVar5 == 0)) break;
      uVar1 = *(undefined8 *)(lVar5 + 0x10);
      if (*(int *)(_DAT_7ffe9c956928 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      lVar5 = *(longlong *)(*(longlong *)(_DAT_7ffe9c956928 + 0xb8) + 8);
      if (lVar5 == 0) {
        if (*(int *)(_DAT_7ffe9c956928 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        uVar6 = **(undefined8 **)(_DAT_7ffe9c956928 + 0xb8);
        lVar5 = func_0x7ffe99940040(_DAT_7ffe9c9375f8);
        FUN_7ffe9af13420(lVar5,uVar6,_DAT_7ffe9c946118);
        *(longlong *)(*(longlong *)(_DAT_7ffe9c956928 + 0xb8) + 8) = lVar5;
        il2cpp_write_barrier_0();
      }
      lVar5 = FUN_7ffe9ab854c0(uVar1,lVar5,_DAT_7ffe9c907f28);
      if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      cVar3 = FUN_7ffe9bda2160(lVar5,0,0);
      if (cVar3 != '\0') {
        if ((((lVar5 == 0) ||
             (plVar7 = (longlong *)FUN_7ffe9a4ca6d0(lVar5,0), plVar7 == (longlong *)0x0)) ||
            (plVar7 = (longlong *)
                      (**(code **)(*plVar7 + 0x298))(plVar7,*(undefined8 *)(*plVar7 + 0x2a0)),
            plVar7 == (longlong *)0x0)) ||
           (self_00 = (undefined *)
                      (**(code **)(*plVar7 + 0x218))(plVar7,*(undefined8 *)(*plVar7 + 0x220)),
           self_00 == (undefined *)0x0)) break;
        GemCartBufferManager_RemoveGemCartBuffer(self_00,*(short *)(lVar4 + 0x10),(undefined *)0x0);
      }
    }
    uVar1 = *(undefined8 *)(self + 0x28);
    uVar6 = func_0x7ffe99940040(_DAT_7ffe9c93b270);
    FUN_7ffe9af155b0(uVar6,lVar4,_DAT_7ffe9c9464f0,0);
    cVar3 = FUN_7ffe9ab7a900(uVar1,uVar6,_DAT_7ffe9c8f88f8);
    if (cVar3 == '\0') {
      return;
    }
    if ((*(longlong *)(self + 0x10) == 0) ||
       (lVar5 = *(longlong *)(*(longlong *)(self + 0x10) + 0x70), lVar5 == 0)) break;
    uVar1 = *(undefined8 *)(lVar5 + 0x10);
    if (*(int *)(_DAT_7ffe9c956928 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    lVar5 = *(longlong *)(*(longlong *)(_DAT_7ffe9c956928 + 0xb8) + 0x10);
    if (lVar5 == 0) {
      if (*(int *)(_DAT_7ffe9c956928 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      uVar6 = **(undefined8 **)(_DAT_7ffe9c956928 + 0xb8);
      lVar5 = func_0x7ffe99940040(_DAT_7ffe9c9375f8);
      FUN_7ffe9af13420(lVar5,uVar6,_DAT_7ffe9c9461e0);
      *(longlong *)(*(longlong *)(_DAT_7ffe9c956928 + 0xb8) + 0x10) = lVar5;
      il2cpp_write_barrier_0();
    }
    lVar5 = FUN_7ffe9ab854c0(uVar1,lVar5,_DAT_7ffe9c907f28);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar3 = FUN_7ffe9bda2160(lVar5,0,0);
    if (cVar3 == '\0') {
      return;
    }
    if (((lVar5 == 0) || (plVar7 = (longlong *)FUN_7ffe9a4ca6d0(lVar5,0), plVar7 == (longlong *)0x0)
        ) || ((plVar7 = (longlong *)
                        (**(code **)(*plVar7 + 0x298))(plVar7,*(undefined8 *)(*plVar7 + 0x2a0)),
              plVar7 == (longlong *)0x0 ||
              (self = (undefined *)(**(code **)(*plVar7 + 0x218))(plVar7), self == (undefined *)0x0)
              ))) break;
    id = *(short *)(lVar4 + 0x10);
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

