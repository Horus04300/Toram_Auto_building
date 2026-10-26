
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * BonusScriptManager_eventCheck(undefined *self,undefined *line,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  longlong lVar3;
  undefined *puVar4;
  
  if (DAT_7ffe9cade143 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9528b8);
    DAT_7ffe9cade143 = '\x01';
  }
  lVar3 = FUN_7ffe9b141840(_DAT_7ffe9c9528b8);
  if ((line != (undefined *)0x0) && (lVar3 != 0)) {
    cVar2 = FUN_7ffe9a526960(lVar3,line[0x14],0);
    puVar4 = (undefined *)0x0;
    if (cVar2 == '\0') {
      puVar4 = (undefined *)0x2;
    }
    return puVar4;
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  puVar4 = (undefined *)(*pcVar1)();
  return puVar4;
}

