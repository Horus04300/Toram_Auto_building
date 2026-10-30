
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBag__ctor(undefined *self,undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  longlong lVar5;
  uint uVar6;
  
  if (DAT_7ffe9cade7aa == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c90dc30);
    FUN_7ffe9996d590(&DAT_7ffe9c91eb08);
    FUN_7ffe9996d590(&DAT_7ffe9c91f3a0);
    FUN_7ffe9996d590(&DAT_7ffe9c9682d8);
    FUN_7ffe9996d590(&DAT_7ffe9c9683a0);
    DAT_7ffe9cade7aa = '\x01';
  }
  func_0x7ffe999c3920(self,0);
  uVar4 = func_0x7ffe99940040(_DAT_7ffe9c9682d8);
  FUN_7ffe9af8a010(uVar4,_DAT_7ffe9c91eb08);
  *(undefined8 *)(self + 0x10) = uVar4;
  il2cpp_write_barrier_0();
  uVar4 = func_0x7ffe99940040(_DAT_7ffe9c9683a0);
  FUN_7ffe9af8a010(uVar4,_DAT_7ffe9c91f3a0);
  *(undefined8 *)(self + 0x18) = uVar4;
  il2cpp_write_barrier_0();
  lVar5 = func_0x7ffe99940040(_DAT_7ffe9c90dc30);
  func_0x7ffe999c3920(lVar5,0);
  *(undefined2 *)(lVar5 + 0x10) = 0;
  *(undefined8 *)(lVar5 + 0x18) = 0;
  *(undefined4 *)(lVar5 + 0x20) = 0;
  *(undefined1 *)(lVar5 + 0x24) = 0;
  *(longlong *)(self + 0x28) = lVar5;
  if (_DAT_7ffe9caee1a8 != 0) {
    uVar6 = (uint)((ulonglong)(self + 0x28) >> 0xc);
    puVar1 = (ulonglong *)((ulonglong)((uVar6 & 0x1fffff) >> 6) * 8 + 0x7ffe9cb35fe0);
    do {
      uVar3 = *puVar1;
      LOCK();
      uVar2 = *puVar1;
      if (uVar3 == uVar2) {
        *puVar1 = uVar3 | 1L << (uVar6 & 0x3f);
      }
      UNLOCK();
    } while (uVar3 != uVar2);
  }
  return;
}

