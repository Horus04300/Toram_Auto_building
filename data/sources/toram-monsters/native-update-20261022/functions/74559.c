
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void Assets_Script_PC_System_UIPCReportBanElement_Initialize
               (undefined *self,undefined *userName,undefined *banId,undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  uint uVar4;
  
  *(undefined **)(self + 0xc0) = userName;
  il2cpp_write_barrier_0();
  *(undefined **)(self + 200) = banId;
  if (_DAT_7ffe9caee1a8 != 0) {
    uVar4 = (uint)((ulonglong)(self + 200) >> 0xc);
    puVar1 = (ulonglong *)((ulonglong)((uVar4 & 0x1fffff) >> 6) * 8 + 0x7ffe9cb35fe0);
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

