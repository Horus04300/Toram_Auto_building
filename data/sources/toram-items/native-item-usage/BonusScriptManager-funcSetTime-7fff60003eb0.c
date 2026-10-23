
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * BonusScriptManager_funcSetTime(undefined *self,undefined *line,undefined *methodInfo)

{
  short sVar1;
  longlong lVar2;
  code *pcVar3;
  undefined *puVar4;
  undefined4 uVar5;
  
  if ((line != (undefined *)0x0) && (lVar2 = *(longlong *)(self + 0x20), lVar2 != 0)) {
    sVar1 = *(short *)(line + 0x14);
    uVar5 = *(undefined4 *)(line + 0x10);
    *(int *)(lVar2 + 0x48) = (int)sVar1;
    *(undefined4 *)(lVar2 + 0x30) = uVar5;
    *(undefined1 *)(lVar2 + 0x40) = 1;
    *(float *)(lVar2 + 0x4c) = (float)(int)sVar1;
    uVar5 = FUN_7fff618b0ec0(0);
    *(undefined4 *)(lVar2 + 0x34) = uVar5;
    return (undefined *)0x0;
  }
  FUN_7fff5f47d660();
  pcVar3 = (code *)swi(3);
  puVar4 = (undefined *)(*pcVar3)();
  return puVar4;
}

