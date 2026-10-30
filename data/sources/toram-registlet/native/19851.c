
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBufferManager_ClearBuffCoolDown(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  undefined8 uStack_60;
  undefined8 uStack_58;
  undefined8 uStack_50;
  longlong lStack_48;
  undefined8 uStack_40;
  undefined8 uStack_38;
  undefined8 uStack_30;
  undefined8 uStack_28;
  longlong lStack_20;
  undefined8 uStack_18;
  
  if (DAT_7ffe9cade79a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c965718);
    FUN_7ffe9996d590(&DAT_7ffe9c92ea20);
    FUN_7ffe9996d590(&DAT_7ffe9c92eae0);
    FUN_7ffe9996d590(0x7ffe9c92eba8);
    FUN_7ffe9996d590(0x7ffe9c9676b8);
    DAT_7ffe9cade79a = '\x01';
  }
  if (*(longlong *)(self + 0x18) != 0) {
    FUN_7ffe9accf860(&uStack_38,*(longlong *)(self + 0x18),_DAT_7ffe9c965718);
    uStack_60 = uStack_38;
    uStack_58 = uStack_30;
    uStack_50 = uStack_28;
    lStack_48 = lStack_20;
    uStack_40 = uStack_18;
    while( true ) {
      cVar2 = FUN_7ffe9ae385a0(&uStack_60,_DAT_7ffe9c92eae0);
      if (cVar2 == '\0') {
        func_0x7ffe999c3920(&uStack_60,_DAT_7ffe9c92ea20);
        return;
      }
      if (lStack_48 == 0) break;
      *(undefined4 *)(lStack_48 + 0x10) = 0;
    }
    FUN_7ffe9996d7a0();
    FUN_7ffe998fa550();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

