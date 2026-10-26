
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int AvoidActionManager_get_MaxAvoidCount(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  longlong *plVar3;
  longlong lVar4;
  
  if (DAT_7ffe9cadf5cf == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    DAT_7ffe9cadf5cf = '\x01';
  }
  plVar3 = *(longlong **)(self + 0x28);
  if (plVar3 != (longlong *)0x0) {
    plVar3 = (longlong *)(**(code **)(*plVar3 + 0x298))(plVar3,*(undefined8 *)(*plVar3 + 0x2a0));
    if (plVar3 != (longlong *)0x0) {
      lVar4 = (**(code **)(*plVar3 + 0x198))(plVar3,*(undefined8 *)(*plVar3 + 0x1a0));
      if (lVar4 != 0) {
        iVar2 = FUN_7ffe99742ec0(0x24,_DAT_7ffe9c940d40,lVar4);
        return iVar2 / 1000;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  iVar2 = (*pcVar1)();
  return iVar2;
}

