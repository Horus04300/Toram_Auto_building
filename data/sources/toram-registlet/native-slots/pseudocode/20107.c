
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void RegistletManager_ExtensionSlot
               (undefined *self,int updateGemPowder,byte slot,undefined *methodInfo)

{
  code *pcVar1;
  
  *(int *)(self + 0x14) = updateGemPowder;
  if (*(longlong *)(self + 0x18) != 0) {
    *(byte *)(*(longlong *)(self + 0x18) + 0x20) = slot;
    return;
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

