
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void AegisAction_ActionHit
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  undefined1 uVar1;
  code *pcVar2;
  bool bVar3;
  byte bVar4;
  uint uVar5;
  longlong lVar6;
  longlong *plVar7;
  longlong lVar8;
  undefined *thisObject_00;
  longlong *plVar9;
  
  if (DAT_7ffe9cadf70b == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c930f30);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c928be8);
    DAT_7ffe9cadf70b = '\x01';
  }
  if (actarAction == (undefined *)0x0) {
    plVar9 = (longlong *)0x0;
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
    plVar9 = (longlong *)0x0;
    if (bVar3) {
      plVar9 = (longlong *)actarAction;
    }
  }
  uVar1 = thisObject[0x14];
  lVar6 = func_0x7ffe99940040(_DAT_7ffe9c930f30);
  FUN_7ffe9a779700(lVar6,uVar1,0);
  if ((((lVar6 != 0) && (*(undefined1 *)(lVar6 + 0x20) = 1, plVar9 != (longlong *)0x0)) &&
      (plVar7 = (longlong *)(**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0)),
      plVar7 != (longlong *)0x0)) &&
     (lVar8 = (**(code **)(*plVar7 + 0x1c8))(plVar7,*(undefined8 *)(*plVar7 + 0x1d0)), lVar8 != 0))
  {
    FUN_7ffe9a7c1d20(lVar8,lVar6,0,0);
    plVar7 = (longlong *)(**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
    if ((plVar7 != (longlong *)0x0) &&
       (thisObject_00 =
             (undefined *)(**(code **)(*plVar7 + 0x218))(plVar7,*(undefined8 *)(*plVar7 + 0x220)),
       thisObject_00 != (undefined *)0x0)) {
      bVar4 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x40c,(undefined *)0x0);
      if (bVar4 == 0) {
        return;
      }
      plVar7 = (longlong *)(**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
      if (plVar7 != (longlong *)0x0) {
        lVar6 = (**(code **)(*plVar7 + 0x1b8))(plVar7,*(undefined8 *)(*plVar7 + 0x1c0));
        if (lVar6 != 0) {
          uVar5 = FUN_7ffe9a7fd580(lVar6,0x107,1,0);
          if ((int)uVar5 < 1) {
            return;
          }
          lVar6 = func_0x7ffe99940040(_DAT_7ffe9c928be8);
          FUN_7ffe9a79f0c0(lVar6,uVar5 & 0xff,0);
          if (lVar6 != 0) {
            *(undefined1 *)(lVar6 + 0x20) = 1;
            plVar9 = (longlong *)
                     (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
            if ((plVar9 != (longlong *)0x0) &&
               (lVar8 = (**(code **)(*plVar9 + 0x1c8))(plVar9,*(undefined8 *)(*plVar9 + 0x1d0)),
               lVar8 != 0)) {
              FUN_7ffe9a7c1d20(lVar8,lVar6,0,0);
              return;
            }
          }
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

