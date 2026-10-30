
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBag_InitializeBag(undefined *self,undefined *gems,undefined *methodInfo)

{
  ulonglong *puVar1;
  int iVar2;
  uint uVar3;
  ulonglong uVar4;
  longlong lVar5;
  undefined8 uVar6;
  code *pcVar7;
  longlong lVar8;
  longlong lVar9;
  undefined8 uVar10;
  ulonglong uVar11;
  uint uVar12;
  
  if (DAT_7ffe9cade7b7 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c90dc30);
    FUN_7ffe9996d590(&DAT_7ffe9c91ebd0);
    FUN_7ffe9996d590(0x7ffe9c91ee28);
    DAT_7ffe9cade7b7 = '\x01';
  }
  lVar9 = *(longlong *)(self + 0x10);
  if (lVar9 == 0) {
LAB_7ffe9a5adb9a:
    FUN_7ffe9996d7a0();
    pcVar7 = (code *)swi(3);
    (*pcVar7)();
    return;
  }
  iVar2 = *(int *)(lVar9 + 0x18);
  uVar12 = 0;
  *(int *)(lVar9 + 0x1c) = *(int *)(lVar9 + 0x1c) + 1;
  *(undefined4 *)(lVar9 + 0x18) = 0;
  if (0 < iVar2) {
    FUN_7ffe9b518970(*(undefined8 *)(lVar9 + 0x10),0,iVar2,0);
  }
  if (gems != (undefined *)0x0) {
    while( true ) {
      uVar11 = (ulonglong)uVar12;
      if ((int)*(uint *)(gems + 0x18) <= (int)uVar12) break;
      if (*(uint *)(gems + 0x18) <= uVar12) {
LAB_7ffe9a5adba0:
        FUN_7ffe9996d790(uVar11);
        pcVar7 = (code *)swi(3);
        (*pcVar7)();
        return;
      }
      lVar9 = *(longlong *)(self + 0x10);
      lVar5 = *(longlong *)(gems + (longlong)(int)uVar12 * 8 + 0x20);
      lVar8 = func_0x7ffe99940040(_DAT_7ffe9c90dc30);
      func_0x7ffe999c3920(lVar8,0);
      if (lVar5 == 0) goto LAB_7ffe9a5adb9a;
      *(undefined2 *)(lVar8 + 0x10) = *(undefined2 *)(lVar5 + 0x20);
      *(undefined8 *)(lVar8 + 0x18) = *(undefined8 *)(lVar5 + 0x28);
      *(undefined2 *)(lVar8 + 0x20) = *(undefined2 *)(lVar5 + 0x30);
      *(undefined2 *)(lVar8 + 0x22) = *(undefined2 *)(lVar5 + 0x32);
      *(undefined1 *)(lVar8 + 0x24) = *(undefined1 *)(lVar5 + 0x34);
      lVar5 = _DAT_7ffe9c91ebd0;
      if (lVar9 == 0) goto LAB_7ffe9a5adb9a;
      *(int *)(lVar9 + 0x1c) = *(int *)(lVar9 + 0x1c) + 1;
      uVar11 = *(ulonglong *)(lVar9 + 0x10);
      uVar3 = *(uint *)(lVar9 + 0x18);
      if (uVar11 == 0) goto LAB_7ffe9a5adb9a;
      if (uVar3 < *(uint *)(uVar11 + 0x18)) {
        *(uint *)(lVar9 + 0x18) = uVar3 + 1;
        if (*(uint *)(uVar11 + 0x18) <= uVar3) goto LAB_7ffe9a5adba0;
        *(longlong *)(uVar11 + (longlong)(int)uVar3 * 8 + 0x20) = lVar8;
        il2cpp_write_barrier_0();
        uVar12 = uVar12 + 1;
      }
      else {
        FUN_7ffe9afd58b0(lVar9,lVar8,
                         *(undefined8 *)(*(longlong *)(*(longlong *)(lVar5 + 0x20) + 0xc0) + 0x70));
        uVar12 = uVar12 + 1;
      }
    }
  }
  if (DAT_7ffe9cade7bf == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c912408,0);
    FUN_7ffe9996d590(&DAT_7ffe9c91c678);
    FUN_7ffe9996d590(&DAT_7ffe9c922738);
    FUN_7ffe9996d590(&DAT_7ffe9c93add8);
    FUN_7ffe9996d590(&DAT_7ffe9c944eb8);
    FUN_7ffe9996d590(&DAT_7ffe9c944f80);
    FUN_7ffe9996d590(&DAT_7ffe9c955c68);
    DAT_7ffe9cade7bf = '\x01';
  }
  uVar10 = *(undefined8 *)(self + 0x10);
  if (*(int *)(_DAT_7ffe9c955c68 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_7ffe9c955c68 + 0xb8) + 0x38);
  if (lVar9 == 0) {
    if (*(int *)(_DAT_7ffe9c955c68 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    uVar6 = **(undefined8 **)(_DAT_7ffe9c955c68 + 0xb8);
    lVar9 = func_0x7ffe99940040(_DAT_7ffe9c93add8);
    FUN_7ffe9af151b0(lVar9,uVar6,_DAT_7ffe9c944eb8,0);
    *(longlong *)(*(longlong *)(_DAT_7ffe9c955c68 + 0xb8) + 0x38) = lVar9;
    il2cpp_write_barrier_0();
  }
  uVar10 = FUN_7ffe9ab8ba10(uVar10,lVar9,_DAT_7ffe9c912408);
  if (*(int *)(_DAT_7ffe9c955c68 + 0xe0) == 0) {
    func_0x7ffe9996d830(_DAT_7ffe9c955c68);
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_7ffe9c955c68 + 0xb8) + 0x40);
  if (lVar9 == 0) {
    if (*(int *)(_DAT_7ffe9c955c68 + 0xe0) == 0) {
      func_0x7ffe9996d830(_DAT_7ffe9c955c68);
    }
    uVar6 = **(undefined8 **)(_DAT_7ffe9c955c68 + 0xb8);
    lVar9 = func_0x7ffe99940040(_DAT_7ffe9c93add8);
    FUN_7ffe9af151b0(lVar9,uVar6,_DAT_7ffe9c944f80,0);
    *(longlong *)(*(longlong *)(_DAT_7ffe9c955c68 + 0xb8) + 0x40) = lVar9;
    il2cpp_write_barrier_0();
  }
  uVar10 = FUN_7ffe9ab90540(uVar10,lVar9,_DAT_7ffe9c91c678);
  uVar10 = FUN_7ffe9ab92be0(uVar10,_DAT_7ffe9c922738);
  *(undefined8 *)(self + 0x10) = uVar10;
  if (_DAT_7ffe9caee1a8 != 0) {
    uVar12 = (uint)((ulonglong)(self + 0x10) >> 0xc);
    puVar1 = (ulonglong *)((ulonglong)((uVar12 & 0x1fffff) >> 6) * 8 + 0x7ffe9cb35fe0);
    do {
      uVar4 = *puVar1;
      LOCK();
      uVar11 = *puVar1;
      if (uVar4 == uVar11) {
        *puVar1 = uVar4 | 1L << (uVar12 & 0x3f);
      }
      UNLOCK();
    } while (uVar4 != uVar11);
  }
  return;
}

