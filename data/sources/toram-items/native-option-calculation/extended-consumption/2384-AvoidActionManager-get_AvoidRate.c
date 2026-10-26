
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float AvoidActionManager_get_AvoidRate(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  longlong *plVar3;
  longlong lVar4;
  float fVar5;
  
  if (DAT_7ffe9cadf5ce == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    DAT_7ffe9cadf5ce = '\x01';
  }
  plVar3 = *(longlong **)(self + 0x28);
  if (plVar3 != (longlong *)0x0) {
    plVar3 = (longlong *)(**(code **)(*plVar3 + 0x298))(plVar3,*(undefined8 *)(*plVar3 + 0x2a0));
    if (plVar3 != (longlong *)0x0) {
      lVar4 = (**(code **)(*plVar3 + 0x198))(plVar3,*(undefined8 *)(*plVar3 + 0x1a0));
      if (lVar4 != 0) {
        iVar2 = FUN_7ffe99742ec0(0x24,_DAT_7ffe9c940d40,lVar4);
        if (iVar2 != 0) {
          return *(float *)(self + 0x54) / (float)iVar2;
        }
        return 0.0;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  fVar5 = (float)(*pcVar1)();
  return fVar5;
}

