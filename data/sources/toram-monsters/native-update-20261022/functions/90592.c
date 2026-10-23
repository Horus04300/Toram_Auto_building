
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void Toram_Common_Rooms_BossDifficultyLevelMethods__cctor(undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  uint uVar5;
  
  if (DAT_7ffe9cae7a32 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949540);
    FUN_7ffe9996d590(&DAT_7ffe9c917f28);
    FUN_7ffe9996d590(&DAT_7ffe9c91da08);
    FUN_7ffe9996d590(&DAT_7ffe9c954f48);
    FUN_7ffe9996d590(&DAT_7ffe9c9555a0);
    FUN_7ffe9996d590(&DAT_7ffe9c955738);
    FUN_7ffe9996d590(&DAT_7ffe9c955a68);
    FUN_7ffe9996d590(&DAT_7ffe9c955c00);
    FUN_7ffe9996d590(&DAT_7ffe9c9560c8);
    FUN_7ffe9996d590(&DAT_7ffe9c956590);
    FUN_7ffe9996d590(&DAT_7ffe9c9568c0);
    FUN_7ffe9996d590(&DAT_7ffe9c9570b8);
    DAT_7ffe9cae7a32 = '\x01';
  }
  uVar4 = func_0x7ffe9996c990(_DAT_7ffe9c91da08,5);
  FUN_7ffe9b436460(uVar4,_DAT_7ffe9c955a68,0);
  **(undefined8 **)(_DAT_7ffe9c949540 + 0xb8) = uVar4;
  il2cpp_write_barrier_0();
  uVar4 = func_0x7ffe9996c990(_DAT_7ffe9c91da08,5);
  FUN_7ffe9b436460(uVar4,_DAT_7ffe9c9568c0,0);
  *(undefined8 *)(*(longlong *)(_DAT_7ffe9c949540 + 0xb8) + 8) = uVar4;
  il2cpp_write_barrier_0();
  uVar4 = func_0x7ffe9996c990(_DAT_7ffe9c91da08,5);
  FUN_7ffe9b436460(uVar4,_DAT_7ffe9c9570b8,0);
  *(undefined8 *)(*(longlong *)(_DAT_7ffe9c949540 + 0xb8) + 0x10) = uVar4;
  il2cpp_write_barrier_0();
  uVar4 = func_0x7ffe9996c990(_DAT_7ffe9c917f28,5);
  FUN_7ffe9b436460(uVar4,_DAT_7ffe9c9560c8,0);
  *(undefined8 *)(*(longlong *)(_DAT_7ffe9c949540 + 0xb8) + 0x18) = uVar4;
  il2cpp_write_barrier_0();
  uVar4 = func_0x7ffe9996c990(_DAT_7ffe9c91da08,5);
  FUN_7ffe9b436460(uVar4,_DAT_7ffe9c955738,0);
  *(undefined8 *)(*(longlong *)(_DAT_7ffe9c949540 + 0xb8) + 0x20) = uVar4;
  il2cpp_write_barrier_0();
  uVar4 = func_0x7ffe9996c990(_DAT_7ffe9c91da08,5);
  FUN_7ffe9b436460(uVar4,_DAT_7ffe9c955c00,0);
  *(undefined8 *)(*(longlong *)(_DAT_7ffe9c949540 + 0xb8) + 0x28) = uVar4;
  il2cpp_write_barrier_0();
  uVar4 = func_0x7ffe9996c990(_DAT_7ffe9c91da08,5);
  FUN_7ffe9b436460(uVar4,_DAT_7ffe9c954f48,0);
  *(undefined8 *)(*(longlong *)(_DAT_7ffe9c949540 + 0xb8) + 0x30) = uVar4;
  il2cpp_write_barrier_0();
  uVar4 = func_0x7ffe9996c990(_DAT_7ffe9c91da08,5);
  FUN_7ffe9b436460(uVar4,_DAT_7ffe9c955a68,0);
  *(undefined8 *)(*(longlong *)(_DAT_7ffe9c949540 + 0xb8) + 0x38) = uVar4;
  il2cpp_write_barrier_0();
  uVar4 = func_0x7ffe9996c990(_DAT_7ffe9c91da08,5);
  FUN_7ffe9b436460(uVar4,_DAT_7ffe9c956590,0);
  *(undefined8 *)(*(longlong *)(_DAT_7ffe9c949540 + 0xb8) + 0x40) = uVar4;
  il2cpp_write_barrier_0();
  uVar4 = func_0x7ffe9996c990(_DAT_7ffe9c917f28,5);
  FUN_7ffe9b436460(uVar4,_DAT_7ffe9c9555a0,0);
  *(undefined8 *)(*(longlong *)(_DAT_7ffe9c949540 + 0xb8) + 0x48) = uVar4;
  if (_DAT_7ffe9caee1a8 != 0) {
    uVar5 = (uint)(*(longlong *)(_DAT_7ffe9c949540 + 0xb8) + 0x48U >> 0xc);
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

