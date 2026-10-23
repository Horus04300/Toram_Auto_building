
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * EnemyMobActionManagerBase_get_MobName(undefined *self,undefined *methodInfo)

{
  undefined4 uVar1;
  code *UNRECOVERED_JUMPTABLE;
  undefined *puVar2;
  longlong *plVar3;
  longlong lVar4;
  
  if (DAT_7ffe9cadd4bd == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f26a8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f65a8);
    FUN_7ffe9996d590(&DAT_7ffe9c953578);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1820);
    DAT_7ffe9cadd4bd = '\x01';
  }
  puVar2 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c953578);
  if (puVar2 != (undefined *)0x0) {
    plVar3 = (longlong *)LocalizeManager_Get(puVar2,(undefined *)0x7,(undefined *)0x0);
    if (self[0x151] == '\0') {
      puVar2 = *(undefined **)(self + 0x70);
    }
    else {
      if (*(undefined **)(self + 0xf8) == (undefined *)0x0) goto LAB_7ffe9a3181ef;
      puVar2 = EnemyMobActionManagerBase_get_MobStatusMaster
                         (*(undefined **)(self + 0xf8),(undefined *)0x0);
    }
    if (puVar2 != (undefined *)0x0) {
      uVar1 = *(undefined4 *)(puVar2 + 0x14);
      if (plVar3 != (longlong *)0x0) {
        if ((*(byte *)(_DAT_7ffe9c8f65a8 + 0x130) <= *(byte *)(*plVar3 + 0x130)) &&
           (*(longlong *)
             (*(longlong *)(*plVar3 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c8f65a8 + 0x130) * 8) == _DAT_7ffe9c8f65a8)) {
          lVar4 = func_0x7ffe9996d210(*(undefined8 *)
                                       (*plVar3 +
                                       ((ulonglong)*(ushort *)(_DAT_7ffe9c8f26a8 + 0x50) + 0x14) *
                                       0x10));
          plVar3 = (longlong *)(**(code **)(lVar4 + 8))(plVar3,uVar1,lVar4);
          if (plVar3 != (longlong *)0x0) {
            UNRECOVERED_JUMPTABLE = *(code **)(*plVar3 + 0x178);
                    /* WARNING: Could not recover jumptable at 0x7ffe9a3181d5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
            puVar2 = (undefined *)
                     (*UNRECOVERED_JUMPTABLE)
                               (plVar3,*(undefined8 *)(*plVar3 + 0x180),UNRECOVERED_JUMPTABLE);
            return puVar2;
          }
          return _DAT_7ffe9c8f1820;
        }
        FUN_7ffe9996c950(plVar3);
        UNRECOVERED_JUMPTABLE = (code *)swi(3);
        puVar2 = (undefined *)(*UNRECOVERED_JUMPTABLE)();
        return puVar2;
      }
    }
  }
LAB_7ffe9a3181ef:
  FUN_7ffe9996d7a0();
  UNRECOVERED_JUMPTABLE = (code *)swi(3);
  puVar2 = (undefined *)(*UNRECOVERED_JUMPTABLE)();
  return puVar2;
}

