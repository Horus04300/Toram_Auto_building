
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
FieldScriptManager_OnBossMenuCommand(undefined *self,undefined *command,undefined *methodInfo)

{
  code *pcVar1;
  undefined *puVar2;
  
  if (DAT_7ffe9cae05c2 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9400c8);
    DAT_7ffe9cae05c2 = '\x01';
  }
  puVar2 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c9400c8);
  FUN_7ffe999db770(puVar2,0,0);
  if (puVar2 != (undefined *)0x0) {
    *(undefined **)(puVar2 + 0x20) = self;
    il2cpp_write_barrier_0();
    *(int *)(puVar2 + 0x28) = (int)command;
    return puVar2;
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  puVar2 = (undefined *)(*pcVar1)();
  return puVar2;
}

