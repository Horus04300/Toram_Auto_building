
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * PlayerDataManager_get_PlayerStatus(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  longlong lVar2;
  code *UNRECOVERED_JUMPTABLE;
  undefined8 *puVar3;
  undefined *puVar4;
  ushort uVar5;
  
  if (DAT_7fff625e5508 == '\0') {
    FUN_7fff5f47d450();
    DAT_7fff625e5508 = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x60);
  if (plVar1 == (longlong *)0x0) {
    return (undefined *)0x0;
  }
  lVar2 = *plVar1;
  uVar5 = 0;
  if (*(ushort *)(lVar2 + 0x12e) != 0) {
    do {
      if (*(longlong *)(*(longlong *)(lVar2 + 0xb0) + (ulonglong)uVar5 * 0x10) == _DAT_7fff62445960)
      {
        puVar3 = (undefined8 *)
                 ((longlong)
                  (*(int *)(*(longlong *)(lVar2 + 0xb0) + 8 + (ulonglong)uVar5 * 0x10) + 2) * 0x10 +
                  0x138 + lVar2);
        UNRECOVERED_JUMPTABLE = (code *)*puVar3;
                    /* WARNING: Could not recover jumptable at 0x7fff5ff8acf3. Too many branches */
                    /* WARNING: Treating indirect jump as call */
        puVar4 = (undefined *)(*UNRECOVERED_JUMPTABLE)(plVar1,puVar3[1],UNRECOVERED_JUMPTABLE);
        return puVar4;
      }
      uVar5 = uVar5 + 1;
    } while (uVar5 < *(ushort *)(lVar2 + 0x12e));
  }
  puVar3 = (undefined8 *)FUN_7fff5f3de400(plVar1,_DAT_7fff62445960,2);
                    /* WARNING: Could not recover jumptable at 0x7fff5ff8acc5. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  puVar4 = (undefined *)(*(code *)*puVar3)(plVar1,puVar3[1],(code *)*puVar3);
  return puVar4;
}

