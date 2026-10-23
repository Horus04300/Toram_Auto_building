
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void FieldScriptManager_OnOpenGuildRaidSymbolCommand
               (undefined *self,undefined *command,undefined *methodInfo)

{
  code *pcVar1;
  longlong *plVar2;
  
  if (DAT_7fff625e7d2b == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6245d9b0);
    DAT_7fff625e7d2b = '\x01';
  }
  FUN_7fff6051a620(self,3);
  FUN_7fff60523c70(self,(ulonglong)command & 0xffffffff,0);
  plVar2 = (longlong *)FUN_7fff60c4bc00(_DAT_7fff6245d9b0);
  if (plVar2 != (longlong *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x7fff6052ab74. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (**(code **)(*plVar2 + 0x278))(plVar2,0xbf,*(undefined8 *)(*plVar2 + 0x280));
    return;
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

