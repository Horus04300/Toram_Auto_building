
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
  
  if (DAT_7fff625e6141 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62458e78);
    DAT_7fff625e6141 = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x28);
  if (plVar1 == (longlong *)0x0) {
    return ret;
  }
  cVar3 = (**(code **)(*plVar1 + 0x178))(plVar1,*(undefined8 *)(*plVar1 + 0x180));
  lVar6 = FUN_7fff60c4bc00(_DAT_7fff62458e78);
  if (lVar6 != 0) {
    cVar4 = FUN_7fff6037cb10(lVar6,0);
    if (cVar3 != cVar4) {
      return ret;
    }
    plVar1 = *(longlong **)(self + 0x28);
    if (plVar1 != (longlong *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x7fff6010c339. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      sVar5 = (**(code **)(*plVar1 + 0x1a8))(plVar1,*(undefined8 *)(*plVar1 + 0x1b0));
      return sVar5;
    }
  }
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  sVar5 = (*pcVar2)();
  return sVar5;
}

