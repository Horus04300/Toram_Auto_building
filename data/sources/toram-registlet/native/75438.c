
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GemCartBuffer_MagicalBashBuff_OnGetValue(undefined *self,undefined *id,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  int iVar3;
  longlong lVar4;
  
  if (DAT_7ffe9cadd3ce == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    DAT_7ffe9cadd3ce = '\x01';
  }
  if ((int)id != 3) {
    return 0;
  }
  plVar1 = *(longlong **)(self + 0x18);
  if (plVar1 != (longlong *)0x0) {
    lVar4 = (**(code **)(*plVar1 + 0x198))(plVar1,*(undefined8 *)(*plVar1 + 0x1a0));
    if (lVar4 != 0) {
      iVar3 = FUN_7ffe99742ec0(0x1a,_DAT_7ffe9c940d40,lVar4);
      return iVar3 / 2;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar3 = (*pcVar2)();
  return iVar3;
}

