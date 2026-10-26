
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * BonusScriptManager_funcSetBonus(undefined *self,undefined *line,undefined *methodInfo)

{
  code *pcVar1;
  undefined *puVar2;
  uint val;
  
  puVar2 = *(undefined **)(self + 0x20);
  if (line != (undefined *)0x0) {
    val = (uint)*(short *)(line + 0x14);
    methodInfo = (undefined *)(ulonglong)val;
    if (val == 0) {
      if (puVar2 == (undefined *)0x0) goto LAB_7ffe9a4f8a92;
      val = *(uint *)(puVar2 + 0x6c);
    }
    else if (puVar2 == (undefined *)0x0) goto LAB_7ffe9a4f8a92;
    BonusScriptData_AddBonus(puVar2,*(int *)(line + 0x10),val,0,(undefined *)0x0);
    return (undefined *)0x0;
  }
LAB_7ffe9a4f8a92:
  FUN_7ffe9996d7a0(puVar2,line,methodInfo);
  pcVar1 = (code *)swi(3);
  puVar2 = (undefined *)(*pcVar1)();
  return puVar2;
}

