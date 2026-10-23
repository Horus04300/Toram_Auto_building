
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
FieldScriptManager_OnBossMenuCommand(undefined *self,undefined *command,undefined *methodInfo)

{
  code *pcVar1;
  undefined *puVar2;
  
  if (DAT_7fff625e7d18 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62447578);
    DAT_7fff625e7d18 = '\x01';
  }
  puVar2 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff62447578);
  FUN_7fff5f4eb770(puVar2,0,0);
  if (puVar2 != (undefined *)0x0) {
    *(undefined **)(puVar2 + 0x20) = self;
    thunk_FUN_7fff5f491fd0();
    *(int *)(puVar2 + 0x28) = (int)command;
    return puVar2;
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  puVar2 = (undefined *)(*pcVar1)();
  return puVar2;
}

