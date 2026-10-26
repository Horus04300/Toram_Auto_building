
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
BonusScriptManager_funcSetAntiVirusBonus(undefined *self,undefined *line,undefined *methodInfo)

{
  code *pcVar1;
  undefined *puVar2;
  
  if ((line != (undefined *)0x0) && (*(undefined **)(self + 0x20) != (undefined *)0x0)) {
    BonusScriptData_AddBonus
              (*(undefined **)(self + 0x20),*(int *)(line + 0x10),(int)*(short *)(line + 0x14),1,
               (undefined *)0x0);
    return (undefined *)0x0;
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  puVar2 = (undefined *)(*pcVar1)();
  return puVar2;
}

