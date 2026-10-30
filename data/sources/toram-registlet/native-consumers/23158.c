
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SacrificeAction_ActionStart
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  longlong *plVar6;
  undefined *thisObject_00;
  longlong *plVar7;
  longlong lVar8;
  
  if (DAT_7ffe9cadec37 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadec37 = '\x01';
  }
  FUN_7ffe9a4a6970(thisObject,actarAction,target,0);
  if (actarAction == (undefined *)0x0) {
    plVar7 = (longlong *)0x0;
  }
  else {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    plVar7 = (longlong *)0x0;
    if (bVar2) {
      plVar7 = (longlong *)actarAction;
    }
  }
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar3 = FUN_7ffe9bda1fa0(plVar7,0,0);
  if (cVar3 != '\0') {
    return;
  }
  if (((plVar7 != (longlong *)0x0) &&
      (plVar6 = (longlong *)(**(code **)(*plVar7 + 0x298))(plVar7,*(undefined8 *)(*plVar7 + 0x2a0)),
      plVar6 != (longlong *)0x0)) &&
     (thisObject_00 =
           (undefined *)(**(code **)(*plVar6 + 0x218))(plVar6,*(undefined8 *)(*plVar6 + 0x220)),
     thisObject_00 != (undefined *)0x0)) {
    bVar4 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x191,(undefined *)0x0);
    if (bVar4 == 0) {
      return;
    }
    plVar7 = (longlong *)(**(code **)(*plVar7 + 0x298))(plVar7,*(undefined8 *)(*plVar7 + 0x2a0));
    if (plVar7 != (longlong *)0x0) {
      lVar8 = (**(code **)(*plVar7 + 0x1b8))(plVar7,*(undefined8 *)(*plVar7 + 0x1c0));
      if (lVar8 != 0) {
        iVar5 = FUN_7ffe9a7fd580(lVar8,0x2e,1);
        if (iVar5 < 1) {
          return;
        }
        cVar3 = FUN_7ffe99a4d1d0(iVar5 * 10,0);
        if (cVar3 == '\0') {
          return;
        }
        *(undefined4 *)(thisObject + 0x104) = 1;
        return;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

