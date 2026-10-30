
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void WeirdnessOfGodAction_ActionStart
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
  longlong lVar7;
  longlong *plVar8;
  byte abStackX_10 [8];
  
  if (DAT_7ffe9cadf917 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c922658);
    DAT_7ffe9cadf917 = '\x01';
  }
  abStackX_10[0] = 0;
  FUN_7ffe9a4a6970(thisObject,actarAction,target,0);
  if (actarAction == (undefined *)0x0) {
    plVar8 = (longlong *)0x0;
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
    plVar8 = (longlong *)0x0;
    if (bVar2) {
      plVar8 = (longlong *)actarAction;
    }
  }
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar3 = FUN_7ffe9bda1fa0(plVar8,0,0);
  if (cVar3 != '\0') {
    return;
  }
  if (((plVar8 != (longlong *)0x0) &&
      (plVar6 = (longlong *)(**(code **)(*plVar8 + 0x298))(plVar8,*(undefined8 *)(*plVar8 + 0x2a0)),
      plVar6 != (longlong *)0x0)) &&
     (thisObject_00 =
           (undefined *)(**(code **)(*plVar6 + 0x218))(plVar6,*(undefined8 *)(*plVar6 + 0x220)),
     thisObject_00 != (undefined *)0x0)) {
    bVar4 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x191,(undefined *)0x0);
    if (bVar4 == 0) {
LAB_7ffe9a847352:
      lVar7 = *plVar8;
      if ((*(byte *)(_DAT_7ffe9c922658 + 0x130) <= *(byte *)(lVar7 + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(lVar7 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c922658 + 0x130) * 8)
          == _DAT_7ffe9c922658)) {
        if ((*(byte *)(lVar7 + 0x130) < *(byte *)(_DAT_7ffe9c922658 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(lVar7 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c922658 + 0x130) * 8)
            != _DAT_7ffe9c922658)) {
          FUN_7ffe9996c950(plVar8);
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        cVar3 = FUN_7ffe9a454450(plVar8,abStackX_10,0);
        if (cVar3 == '\0') {
          *(undefined4 *)(thisObject + 0x124) = 0;
        }
        else {
          *(uint *)(thisObject + 0x124) = (uint)abStackX_10[0];
        }
      }
      *(uint *)(thisObject + 0x104) = (uint)CONCAT11(thisObject[0x121],thisObject[0x124]);
      return;
    }
    plVar6 = (longlong *)(**(code **)(*plVar8 + 0x298))(plVar8,*(undefined8 *)(*plVar8 + 0x2a0));
    if (plVar6 != (longlong *)0x0) {
      lVar7 = (**(code **)(*plVar6 + 0x1b8))(plVar6,*(undefined8 *)(*plVar6 + 0x1c0));
      if (lVar7 != 0) {
        iVar5 = FUN_7ffe9a7fd580(lVar7,0x2e,1);
        if ((0 < iVar5) && (cVar3 = FUN_7ffe99a4d1d0(iVar5 * 10,0), cVar3 != '\0')) {
          thisObject[0x121] = thisObject[0x121] | 1;
        }
        goto LAB_7ffe9a847352;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

