
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobBattleStatus__ctor
               (undefined *self,undefined *statusMaster,undefined *abnormalManager,
               undefined *buffManager,undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  uint uVar4;
  
  func_0x7fff5f4d3920(self,0);
  *(undefined **)(self + 0x10) = statusMaster;
  thunk_FUN_7fff5f491fd0();
  *(undefined **)(self + 0x18) = abnormalManager;
  thunk_FUN_7fff5f491fd0();
  *(undefined **)(self + 0x20) = buffManager;
  if (_DAT_7fff625f58f8 != 0) {
    uVar4 = (uint)((ulonglong)(self + 0x20) >> 0xc);
    puVar1 = (ulonglong *)((ulonglong)((uVar4 & 0x1fffff) >> 6) * 8 + 0x7fff6263d720);
    do {
      uVar3 = *puVar1;
      LOCK();
      uVar2 = *puVar1;
      if (uVar3 == uVar2) {
        *puVar1 = uVar3 | 1L << (uVar4 & 0x3f);
      }
      UNLOCK();
    } while (uVar3 != uVar2);
  }
  return;
}

