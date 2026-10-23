
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

short RoomManager_GetAreaLevel(undefined *self,short ret,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  char cVar4;
  short sVar5;
  longlong lVar6;
  
  if (DAT_7ffe9cade9ea == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c951f28);
    DAT_7ffe9cade9ea = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x28);
  if (plVar1 == (longlong *)0x0) {
    return ret;
  }
  cVar3 = (**(code **)(*plVar1 + 0x178))(plVar1,*(undefined8 *)(*plVar1 + 0x180));
  lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c951f28);
  if (lVar6 != 0) {
    cVar4 = FUN_7ffe9a872680(lVar6,0);
    if (cVar3 != cVar4) {
      return ret;
    }
    plVar1 = *(longlong **)(self + 0x28);
    if (plVar1 != (longlong *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x7ffe9a601ea9. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      sVar5 = (**(code **)(*plVar1 + 0x1a8))(plVar1,*(undefined8 *)(*plVar1 + 0x1b0));
      return sVar5;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  sVar5 = (*pcVar2)();
  return sVar5;
}

