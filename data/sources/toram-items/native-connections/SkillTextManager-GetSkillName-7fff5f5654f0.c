
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * SkillTextManager_GetSkillName(undefined *self,int skillId,undefined *methodInfo)

{
  code *UNRECOVERED_JUMPTABLE;
  char cVar1;
  longlong *plVar2;
  undefined *puVar3;
  
  if (DAT_7fff625e156e == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6240cbd0);
    FUN_7fff5f47d450(&DAT_7fff6240cd70);
    FUN_7fff5f47d450(&DAT_7fff624408b0);
    DAT_7fff625e156e = '\x01';
  }
  if (*(longlong *)(self + 0x18) != 0) {
    cVar1 = FUN_7fff6082f170(*(longlong *)(self + 0x18),skillId,_DAT_7fff6240cbd0);
    if (cVar1 == '\0') {
      return _DAT_7fff624408b0;
    }
    if (*(longlong *)(self + 0x18) != 0) {
      plVar2 = (longlong *)FUN_7fff6083faa0(*(longlong *)(self + 0x18),skillId,_DAT_7fff6240cd70);
      if (plVar2 != (longlong *)0x0) {
        UNRECOVERED_JUMPTABLE = *(code **)(*plVar2 + 0x188);
                    /* WARNING: Could not recover jumptable at 0x7fff5f565588. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        puVar3 = (undefined *)
                 (*UNRECOVERED_JUMPTABLE)
                           (plVar2,*(undefined8 *)(*plVar2 + 400),UNRECOVERED_JUMPTABLE);
        return puVar3;
      }
    }
  }
  FUN_7fff5f47d660();
  UNRECOVERED_JUMPTABLE = (code *)swi(3);
  puVar3 = (undefined *)(*UNRECOVERED_JUMPTABLE)();
  return puVar3;
}

