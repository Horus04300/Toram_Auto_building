
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void FieldScriptManager_OnOpenGuildRaidSymbolCommand
               (undefined *self,undefined *command,undefined *methodInfo)

{
  code *pcVar1;
  longlong *plVar2;
  
  if (DAT_7ffe9cae05d5 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c956ad0);
    DAT_7ffe9cae05d5 = '\x01';
  }
  FUN_7ffe9aa10230(self,3);
  FUN_7ffe9aa19880(self,(ulonglong)command & 0xffffffff,0);
  plVar2 = (longlong *)FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
  if (plVar2 != (longlong *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x7ffe9aa20784. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar2 + 0x278))(plVar2,0xbf,*(undefined8 *)(*plVar2 + 0x280));
    return;
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

