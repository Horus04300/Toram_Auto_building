
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmokeDustAction_ActionHit
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  longlong *plVar5;
  undefined *puVar6;
  longlong *plVar7;
  longlong lVar8;
  float fVar9;
  
  if (DAT_7ffe9cadf293 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f7490);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadf293 = '\x01';
  }
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
  cVar3 = FUN_7ffe9bda2160(plVar7,0,0);
  fVar9 = _DAT_7ffe9c049ce4;
  if (cVar3 != '\0') {
    if (plVar7 != (longlong *)0x0) {
      lVar8 = *plVar7;
      if ((*(byte *)(_DAT_7ffe9c8f7490 + 0x130) <= *(byte *)(lVar8 + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(lVar8 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8f7490 + 0x130) * 8)
          == _DAT_7ffe9c8f7490)) {
        return;
      }
      plVar5 = (longlong *)(**(code **)(lVar8 + 0x298))(plVar7,*(undefined8 *)(lVar8 + 0x2a0));
      if ((plVar5 != (longlong *)0x0) &&
         (puVar6 = (undefined *)
                   (**(code **)(*plVar5 + 0x218))(plVar5,*(undefined8 *)(*plVar5 + 0x220)),
         puVar6 != (undefined *)0x0)) {
        puVar6 = GemCartBufferManager_GetGemCartBuffer(puVar6,0x12f,(undefined *)0x0);
        if (puVar6 != (undefined *)0x0) {
          iVar4 = GemCartBufferBase_GetValue(puVar6,(undefined *)0x2,(undefined *)0x0);
          fVar9 = (float)iVar4 + fVar9;
        }
        plVar7 = (longlong *)(**(code **)(*plVar7 + 0x298))(plVar7,*(undefined8 *)(*plVar7 + 0x2a0))
        ;
        if ((plVar7 != (longlong *)0x0) &&
           (lVar8 = (**(code **)(*plVar7 + 0x1c8))(plVar7,*(undefined8 *)(*plVar7 + 0x1d0)),
           lVar8 != 0)) {
          FUN_7ffe9a7c2660(lVar8,0x4a,thisObject[0x14],fVar9,0,thisObject[0x10],0);
          return;
        }
      }
    }
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  return;
}

