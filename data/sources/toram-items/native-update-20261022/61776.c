
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UIItemProperty__cctor(undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  uint uVar5;
  
  if (DAT_7ffe9cadbb2a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c917e58);
    FUN_7ffe9996d590(&DAT_7ffe9c935608);
    FUN_7ffe9996d590(&DAT_7ffe9c8ee100);
    DAT_7ffe9cadbb2a = '\x01';
  }
  uVar4 = func_0x7ffe9996c990(_DAT_7ffe9c917e58,0x15);
  FUN_7ffe9b436460(uVar4,_DAT_7ffe9c935608,0);
  **(undefined8 **)(_DAT_7ffe9c8ee100 + 0xb8) = uVar4;
  if (_DAT_7ffe9caee1a8 != 0) {
    uVar5 = (uint)(*(ulonglong *)(_DAT_7ffe9c8ee100 + 0xb8) >> 0xc);
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

