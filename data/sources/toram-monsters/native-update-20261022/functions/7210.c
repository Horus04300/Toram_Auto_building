
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BossMobBattleStatus__ctor
               (undefined *self,undefined *statusMaster,undefined *abnormalManager,
               undefined *buffManager,short difficulty,undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  uint uVar5;
  
  if (DAT_7ffe9cadd1cb == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8ff130);
    FUN_7ffe9996d590(&DAT_7ffe9c912c08);
    DAT_7ffe9cadd1cb = '\x01';
  }
  uVar4 = func_0x7ffe99940040(_DAT_7ffe9c912c08);
  FUN_7ffe9ad214a0(uVar4,_DAT_7ffe9c8ff130);
  *(undefined8 *)(self + 0x30) = uVar4;
  il2cpp_write_barrier_0();
  func_0x7ffe999c3920(self,0);
  *(short *)(self + 0x28) = difficulty;
  *(undefined **)(self + 0x10) = statusMaster;
  il2cpp_write_barrier_0();
  *(undefined **)(self + 0x18) = abnormalManager;
  il2cpp_write_barrier_0();
  *(undefined **)(self + 0x20) = buffManager;
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

