
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GemCartBuffer_PowerWaveChangeBuff_OnGetValue
              (undefined *self,undefined *id,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  int iVar3;
  longlong lVar4;
  
  if ((int)id != 3) {
    return 0;
  }
  plVar1 = *(longlong **)(self + 0x18);
  if (plVar1 != (longlong *)0x0) {
    lVar4 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0),(char)methodInfo)
    ;
    if (lVar4 != 0) {
      iVar3 = FUN_7ffe9a7fd580(lVar4,0x6b,1);
      return (iVar3 + *(short *)(self + 0x14)) / 2;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar3 = (*pcVar2)();
  return iVar3;
}

