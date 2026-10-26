
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GuardActionManager_get_MaxGuardPower(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  code *UNRECOVERED_JUMPTABLE;
  ushort uVar2;
  int iVar3;
  undefined8 *puVar4;
  longlong *plVar5;
  
  if (DAT_7ffe9cadfeaa == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    DAT_7ffe9cadfeaa = '\x01';
  }
  plVar5 = *(longlong **)(self + 0x28);
  if (plVar5 != (longlong *)0x0) {
    plVar5 = (longlong *)(**(code **)(*plVar5 + 0x298))(plVar5,*(undefined8 *)(*plVar5 + 0x2a0));
    if (plVar5 != (longlong *)0x0) {
      plVar5 = (longlong *)(**(code **)(*plVar5 + 0x1a8))(plVar5,*(undefined8 *)(*plVar5 + 0x1b0));
      if (plVar5 != (longlong *)0x0) {
        iVar3 = FUN_7ffe99742ec0(0x21,_DAT_7ffe9c940d40,plVar5);
        if (iVar3 != 0) {
          uVar2 = 0;
          lVar1 = *plVar5;
          if (*(ushort *)(lVar1 + 0x12e) != 0) {
            do {
              if (*(longlong *)(*(longlong *)(lVar1 + 0xb0) + (ulonglong)uVar2 * 0x10) ==
                  _DAT_7ffe9c940d40) {
                puVar4 = (undefined8 *)
                         ((longlong)
                          (*(int *)(*(longlong *)(lVar1 + 0xb0) + 8 + (ulonglong)uVar2 * 0x10) +
                          0x21) * 0x10 + 0x138 + lVar1);
                UNRECOVERED_JUMPTABLE = (code *)*puVar4;
                    /* WARNING: Could not recover jumptable at 0x7ffe99742f4b. Too many branches */
                    /* WARNING: Treating indirect jump as call */
                iVar3 = (*UNRECOVERED_JUMPTABLE)(plVar5,puVar4[1],UNRECOVERED_JUMPTABLE);
                return iVar3;
              }
              uVar2 = uVar2 + 1;
            } while (uVar2 < *(ushort *)(lVar1 + 0x12e));
          }
          puVar4 = (undefined8 *)FUN_7ffe998ce540(plVar5);
                    /* WARNING: Could not recover jumptable at 0x7ffe99742f1c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
          iVar3 = (*(code *)*puVar4)(plVar5,puVar4[1],(code *)*puVar4);
          return iVar3;
        }
      }
      return 0;
    }
  }
  FUN_7ffe9996d7a0();
  UNRECOVERED_JUMPTABLE = (code *)swi(3);
  iVar3 = (*UNRECOVERED_JUMPTABLE)();
  return iVar3;
}

