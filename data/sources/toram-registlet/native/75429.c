
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBuffer_LastResistanceBuff__ctor(undefined *self,short lv,undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  uint uVar5;
  
  GemCartBufferBase__ctor(self,lv,(undefined *)0x0);
  uVar4 = FUN_7ffe9a47bac0(0);
  *(undefined8 *)(self + 0x18) = uVar4;
  if (_DAT_7ffe9caee1a8 != 0) {
    uVar5 = (uint)((ulonglong)(self + 0x18) >> 0xc);
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

