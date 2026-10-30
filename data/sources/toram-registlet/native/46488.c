
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void RegistletTextManager_Clear(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  
  if (DAT_7ffe9cad9de2 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c903980);
    DAT_7ffe9cad9de2 = '\x01';
  }
  if (*(longlong *)(self + 0x18) != 0) {
    FUN_7ffe9acce330(*(longlong *)(self + 0x18),_DAT_7ffe9c903980);
    self[0x10] = 0;
    return;
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

