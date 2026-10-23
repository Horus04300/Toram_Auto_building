
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * SkillTextManager_GetSkillName(undefined *self,int skillId,undefined *methodInfo)

{
  code *UNRECOVERED_JUMPTABLE;
  char cVar1;
  longlong *plVar2;
  undefined *puVar3;
  
  if (DAT_7ffe9cad9df2 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c905ba0);
    FUN_7ffe9996d590(&DAT_7ffe9c905d40);
    FUN_7ffe9996d590(&DAT_7ffe9c93a1c8);
    DAT_7ffe9cad9df2 = '\x01';
  }
  if (*(longlong *)(self + 0x18) != 0) {
    cVar1 = FUN_7ffe9ad24db0(*(longlong *)(self + 0x18),skillId,_DAT_7ffe9c905ba0);
    if (cVar1 == '\0') {
      return _DAT_7ffe9c93a1c8;
    }
    if (*(longlong *)(self + 0x18) != 0) {
      plVar2 = (longlong *)FUN_7ffe9ad356e0(*(longlong *)(self + 0x18),skillId,_DAT_7ffe9c905d40);
      if (plVar2 != (longlong *)0x0) {
        UNRECOVERED_JUMPTABLE = *(code **)(*plVar2 + 0x188);
                    /* WARNING: Could not recover jumptable at 0x7ffe99a55758. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        puVar3 = (undefined *)
                 (*UNRECOVERED_JUMPTABLE)
                           (plVar2,*(undefined8 *)(*plVar2 + 400),UNRECOVERED_JUMPTABLE);
        return puVar3;
      }
    }
  }
  FUN_7ffe9996d7a0();
  UNRECOVERED_JUMPTABLE = (code *)swi(3);
  puVar3 = (undefined *)(*UNRECOVERED_JUMPTABLE)();
  return puVar3;
}

