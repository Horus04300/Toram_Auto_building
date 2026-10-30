
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void HideAttackAction_ActionHit
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  undefined1 uVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  byte bVar5;
  longlong *plVar6;
  undefined *thisObject_00;
  undefined8 uVar7;
  longlong *plVar8;
  longlong lVar9;
  
  if (DAT_7ffe9cadf7dc == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c929cd0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadf7dc = '\x01';
  }
  if (actarAction == (undefined *)0x0) {
    plVar8 = (longlong *)0x0;
  }
  else {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    plVar8 = (longlong *)0x0;
    if (bVar3) {
      plVar8 = (longlong *)actarAction;
    }
  }
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar4 = FUN_7ffe9bda2160(plVar8,0,0);
  if (cVar4 == '\0') {
    return;
  }
  if (((plVar8 != (longlong *)0x0) &&
      (plVar6 = (longlong *)(**(code **)(*plVar8 + 0x298))(plVar8,*(undefined8 *)(*plVar8 + 0x2a0)),
      plVar6 != (longlong *)0x0)) &&
     (thisObject_00 =
           (undefined *)(**(code **)(*plVar6 + 0x218))(plVar6,*(undefined8 *)(*plVar6 + 0x220)),
     thisObject_00 != (undefined *)0x0)) {
    bVar5 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x405,(undefined *)0x0);
    uVar1 = thisObject[0x14];
    uVar7 = func_0x7ffe99940040(_DAT_7ffe9c929cd0);
    FUN_7ffe9a790c50(uVar7,uVar1,bVar5,0);
    plVar8 = (longlong *)(**(code **)(*plVar8 + 0x298))(plVar8,*(undefined8 *)(*plVar8 + 0x2a0));
    if ((plVar8 != (longlong *)0x0) &&
       (lVar9 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)), lVar9 != 0)
       ) {
      FUN_7ffe9a7c26c0(lVar9,uVar7,thisObject[0x10],0);
      return;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

