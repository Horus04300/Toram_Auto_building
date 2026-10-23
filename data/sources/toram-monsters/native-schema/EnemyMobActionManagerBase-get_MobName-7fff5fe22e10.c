
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * EnemyMobActionManagerBase_get_MobName(undefined *self,undefined *methodInfo)

{
  undefined4 uVar1;
  code *UNRECOVERED_JUMPTABLE;
  undefined *puVar2;
  longlong *plVar3;
  longlong lVar4;
  
  if (DAT_7fff625e4c15 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff623f9608);
    FUN_7fff5f47d450(&DAT_7fff623fe068);
    FUN_7fff5f47d450(&DAT_7fff6245a460);
    FUN_7fff5f47d450(&DAT_7fff623f7f60);
    DAT_7fff625e4c15 = '\x01';
  }
  puVar2 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff6245a460);
  if (puVar2 != (undefined *)0x0) {
    plVar3 = (longlong *)LocalizeManager_Get(puVar2,(undefined *)0x7,(undefined *)0x0);
    if (self[0x151] == '\0') {
      puVar2 = *(undefined **)(self + 0x70);
    }
    else {
      if (*(undefined **)(self + 0xf8) == (undefined *)0x0) goto LAB_7fff5fe22f5f;
      puVar2 = EnemyMobActionManagerBase_get_MobStatusMaster
                         (*(undefined **)(self + 0xf8),(undefined *)0x0);
    }
    if (puVar2 != (undefined *)0x0) {
      uVar1 = *(undefined4 *)(puVar2 + 0x14);
      if (plVar3 != (longlong *)0x0) {
        if ((*(byte *)(_DAT_7fff623fe068 + 0x130) <= *(byte *)(*plVar3 + 0x130)) &&
           (*(longlong *)
             (*(longlong *)(*plVar3 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7fff623fe068 + 0x130) * 8) == _DAT_7fff623fe068)) {
          lVar4 = func_0x7fff5f47d0d0(*(undefined8 *)
                                       (*plVar3 +
                                       ((ulonglong)*(ushort *)(_DAT_7fff623f9608 + 0x50) + 0x14) *
                                       0x10));
          plVar3 = (longlong *)(**(code **)(lVar4 + 8))(plVar3,uVar1,lVar4);
          if (plVar3 != (longlong *)0x0) {
            UNRECOVERED_JUMPTABLE = *(code **)(*plVar3 + 0x178);
                    /* WARNING: Could not recover jumptable at 0x7fff5fe22f45. Too many branches */
                    /* WARNING: Treating indirect jump as call */
            puVar2 = (undefined *)
                     (*UNRECOVERED_JUMPTABLE)
                               (plVar3,*(undefined8 *)(*plVar3 + 0x180),UNRECOVERED_JUMPTABLE);
            return puVar2;
          }
          return _DAT_7fff623f7f60;
        }
        FUN_7fff5f47c810(plVar3);
        UNRECOVERED_JUMPTABLE = (code *)swi(3);
        puVar2 = (undefined *)(*UNRECOVERED_JUMPTABLE)();
        return puVar2;
      }
    }
  }
LAB_7fff5fe22f5f:
  FUN_7fff5f47d660();
  UNRECOVERED_JUMPTABLE = (code *)swi(3);
  puVar2 = (undefined *)(*UNRECOVERED_JUMPTABLE)();
  return puVar2;
}

