
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void RegistletManager__ctor(undefined *self,undefined *manager,undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  undefined *self_00;
  uint uVar5;
  
  if (DAT_7ffe9cade7c8 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c90da90);
    FUN_7ffe9996d590(&DAT_7ffe9c917f28);
    FUN_7ffe9996d590(&DAT_7ffe9c930e10);
    DAT_7ffe9cade7c8 = '\x01';
  }
  uVar4 = func_0x7ffe9996c990(_DAT_7ffe9c917f28,9);
  FUN_7ffe9b436460(uVar4,_DAT_7ffe9c930e10,0);
  *(undefined8 *)(self + 0x30) = uVar4;
  il2cpp_write_barrier_0();
  func_0x7ffe999c3920(self);
  self_00 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c90da90);
  GemCartBag__ctor(self_00,(undefined *)0x0);
  *(undefined **)(self + 0x18) = self_00;
  il2cpp_write_barrier_0();
  *(undefined **)(self + 0x20) = manager;
  if (_DAT_7ffe9caee1a8 != 0) {
    uVar5 = (uint)((ulonglong)(self + 0x20) >> 0xc);
    puVar1 = (ulonglong *)((ulonglong)((uVar5 & 0x1fffff) >> 6) * 8 + 0x7ffe9cb35fe0);
    do {
      uVar3 = *puVar1;
      LOCK();
      uVar2 = *puVar1;
      if (uVar3 == uVar2) {
        *puVar1 = uVar3 | 1L << (uVar5 & 0x3f);
      }
      UNLOCK();
    } while (uVar3 != uVar2);
  }
  return;
}

