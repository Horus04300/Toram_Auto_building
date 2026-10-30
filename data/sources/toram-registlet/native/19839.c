
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBufferManager__ctor(undefined *self,undefined *actor,undefined *methodInfo)

{
  uint uVar1;
  longlong lVar2;
  code *pcVar3;
  char cVar4;
  undefined8 uVar5;
  longlong lVar6;
  longlong lVar7;
  
  if (DAT_7ffe9cade78e == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c943f20);
    FUN_7ffe9996d590(&DAT_7ffe9c9653e8);
    FUN_7ffe9996d590(&DAT_7ffe9c90d110);
    FUN_7ffe9996d590(&DAT_7ffe9c91f9e0);
    FUN_7ffe9996d590(&DAT_7ffe9c91f918);
    FUN_7ffe9996d590(&DAT_7ffe9c968470);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    DAT_7ffe9cade78e = '\x01';
  }
  uVar5 = func_0x7ffe99940040(_DAT_7ffe9c90d110);
  FUN_7ffe9ad0cd00(uVar5,_DAT_7ffe9c9653e8);
  *(undefined8 *)(self + 0x18) = uVar5;
  il2cpp_write_barrier_0();
  lVar6 = func_0x7ffe99940040(_DAT_7ffe9c968470);
  FUN_7ffe9af8a010(lVar6,_DAT_7ffe9c91f918);
  lVar7 = _DAT_7ffe9c91f9e0;
  if (lVar6 != 0) {
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar2 = *(longlong *)(lVar6 + 0x10);
    uVar1 = *(uint *)(lVar6 + 0x18);
    if (lVar2 == 0) goto LAB_7ffe9a5b46a0;
    if (uVar1 < *(uint *)(lVar2 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar1 + 1;
      if (*(uint *)(lVar2 + 0x18) <= uVar1) goto LAB_7ffe9a5b46a6;
      *(undefined4 *)(lVar2 + 0x20 + (longlong)(int)uVar1 * 4) = 0x1b;
    }
    else {
      FUN_7ffe9afc6d40(lVar6,0x1b,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar7 + 0x20) + 0xc0) + 0x70));
    }
    lVar2 = _DAT_7ffe9c91f9e0;
    *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
    lVar7 = *(longlong *)(lVar6 + 0x10);
    uVar1 = *(uint *)(lVar6 + 0x18);
    if (lVar7 == 0) goto LAB_7ffe9a5b46a0;
    if (uVar1 < *(uint *)(lVar7 + 0x18)) {
      *(uint *)(lVar6 + 0x18) = uVar1 + 1;
      if (*(uint *)(lVar7 + 0x18) <= uVar1) goto LAB_7ffe9a5b46a6;
      *(undefined4 *)(lVar7 + 0x20 + (longlong)(int)uVar1 * 4) = 0x1c;
    }
    else {
      FUN_7ffe9afc6d40(lVar6,0x1c,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar2 + 0x20) + 0xc0) + 0x70));
    }
    *(longlong *)(self + 0x20) = lVar6;
    il2cpp_write_barrier_0();
    lVar6 = func_0x7ffe99940040(_DAT_7ffe9c968470);
    FUN_7ffe9af8a010(lVar6,_DAT_7ffe9c91f918);
    lVar7 = _DAT_7ffe9c91f9e0;
    if (lVar6 != 0) {
      *(int *)(lVar6 + 0x1c) = *(int *)(lVar6 + 0x1c) + 1;
      lVar2 = *(longlong *)(lVar6 + 0x10);
      uVar1 = *(uint *)(lVar6 + 0x18);
      if (lVar2 != 0) {
        if (uVar1 < *(uint *)(lVar2 + 0x18)) {
          *(uint *)(lVar6 + 0x18) = uVar1 + 1;
          if (*(uint *)(lVar2 + 0x18) <= uVar1) {
LAB_7ffe9a5b46a6:
            FUN_7ffe9996d790();
            pcVar3 = (code *)swi(3);
            (*pcVar3)();
            return;
          }
          *(undefined4 *)(lVar2 + 0x20 + (longlong)(int)uVar1 * 4) = 0x49;
        }
        else {
          FUN_7ffe9afc6d40(lVar6,0x49,
                           *(undefined8 *)(*(longlong *)(*(longlong *)(lVar7 + 0x20) + 0xc0) + 0x70)
                          );
        }
        *(longlong *)(self + 0x28) = lVar6;
        il2cpp_write_barrier_0();
        func_0x7ffe999c3920(self,0);
        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        cVar4 = FUN_7ffe9bda2160(actor,0,0);
        if (cVar4 != '\0') {
          if (actor == (undefined *)0x0) goto LAB_7ffe9a5b46a0;
          lVar7 = FUN_7ffe9ab6e260(actor,_DAT_7ffe9c943f20);
          if (lVar7 != 0) {
            uVar5 = FUN_7ffe9a47bac0(0);
            *(undefined8 *)(self + 0x10) = uVar5;
            il2cpp_write_barrier_0();
          }
        }
        return;
      }
    }
  }
LAB_7ffe9a5b46a0:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

