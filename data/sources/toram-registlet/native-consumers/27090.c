
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ParalysisShotAction_ActionHit
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  longlong *plVar4;
  undefined *puVar5;
  longlong *plVar6;
  longlong lVar7;
  
  if (DAT_7ffe9cadf278 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f7490);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadf278 = '\x01';
  }
  if (actarAction == (undefined *)0x0) {
    plVar6 = (longlong *)0x0;
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
    plVar6 = (longlong *)0x0;
    if (bVar2) {
      plVar6 = (longlong *)actarAction;
    }
  }
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar3 = FUN_7ffe9bda2160(plVar6,0,0);
  if (cVar3 == '\0') {
    return;
  }
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(_DAT_7ffe9c8f7490 + 0x130) <= *(byte *)(*(longlong *)actarAction + 0x130)) &&
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c8f7490 + 0x130) * 8) == _DAT_7ffe9c8f7490)) {
      return;
    }
  }
  if (((plVar6 != (longlong *)0x0) &&
      (plVar4 = (longlong *)(**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0)),
      plVar4 != (longlong *)0x0)) &&
     (puVar5 = (undefined *)(**(code **)(*plVar4 + 0x218))(plVar4,*(undefined8 *)(*plVar4 + 0x220)),
     puVar5 != (undefined *)0x0)) {
    puVar5 = GemCartBufferManager_GetGemCartBuffer(puVar5,0xcc,(undefined *)0x0);
    if (puVar5 != (undefined *)0x0) {
      GemCartBufferBase_GetValue(puVar5,(undefined *)0x2,(undefined *)0x0);
    }
    plVar6 = (longlong *)(**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0));
    if ((plVar6 != (longlong *)0x0) &&
       (lVar7 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0)), lVar7 != 0)
       ) {
      FUN_7ffe9a7c2660(lVar7,0x47,thisObject[0x14]);
      return;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

