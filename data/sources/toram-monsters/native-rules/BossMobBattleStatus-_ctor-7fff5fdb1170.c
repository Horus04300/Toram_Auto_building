
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
  
  if (DAT_7fff625e4926 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62406160);
    FUN_7fff5f47d450(&DAT_7fff6241a798);
    DAT_7fff625e4926 = '\x01';
  }
  uVar4 = func_0x7fff5f44ff00(_DAT_7fff6241a798);
  FUN_7fff6082b860(uVar4,_DAT_7fff62406160);
  *(undefined8 *)(self + 0x30) = uVar4;
  thunk_FUN_7fff5f491fd0();
  func_0x7fff5f4d3920(self,0);
  *(short *)(self + 0x28) = difficulty;
  *(undefined **)(self + 0x10) = statusMaster;
  thunk_FUN_7fff5f491fd0();
  *(undefined **)(self + 0x18) = abnormalManager;
  thunk_FUN_7fff5f491fd0();
  *(undefined **)(self + 0x20) = buffManager;
  if (_DAT_7fff625f58f8 != 0) {
    uVar5 = (uint)((ulonglong)(self + 0x20) >> 0xc);
    puVar1 = (ulonglong *)((ulonglong)((uVar5 & 0x1fffff) >> 6) * 8 + 0x7fff6263d720);
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

