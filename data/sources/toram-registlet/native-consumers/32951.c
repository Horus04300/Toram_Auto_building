
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ResonanceAction_ActionHit
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  undefined1 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  code *pcVar4;
  bool bVar5;
  char cVar6;
  short id;
  int iVar7;
  longlong *plVar8;
  undefined *puVar9;
  undefined8 uVar10;
  longlong *plVar11;
  longlong lVar12;
  float fVar13;
  
  if (DAT_7ffe9cadf8b5 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f9490);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c9343c8);
    DAT_7ffe9cadf8b5 = '\x01';
  }
  if (actarAction == (undefined *)0x0) {
    plVar11 = (longlong *)0x0;
  }
  else {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar5 = false;
    }
    else {
      bVar5 = true;
    }
    plVar11 = (longlong *)0x0;
    if (bVar5) {
      plVar11 = (longlong *)actarAction;
    }
  }
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar6 = FUN_7ffe9bda2160(plVar11,0,0);
  fVar13 = _DAT_7ffe9c049b18;
  if (cVar6 == '\0') {
    return;
  }
  if ((plVar11 != (longlong *)0x0) &&
     (plVar8 = (longlong *)
               (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0)),
     plVar8 != (longlong *)0x0)) {
    puVar9 = (undefined *)(**(code **)(*plVar8 + 0x218))(plVar8,*(undefined8 *)(*plVar8 + 0x220));
    if ((*(longlong *)(thisObject + 0x128) != 0) &&
       (id = FUN_7ffe9ad35780(*(longlong *)(thisObject + 0x128),*(undefined4 *)(thisObject + 0x104))
       , puVar9 != (undefined *)0x0)) {
      puVar9 = GemCartBufferManager_GetGemCartBuffer(puVar9,id,(undefined *)0x0);
      if (puVar9 != (undefined *)0x0) {
        iVar7 = GemCartBufferBase_GetValue(puVar9,(undefined *)0x2,(undefined *)0x0);
        fVar13 = (float)iVar7 / _DAT_7ffe9c049cfc;
      }
      uVar1 = thisObject[0x14];
      uVar2 = *(undefined4 *)(thisObject + 0x104);
      uVar3 = *(undefined4 *)(thisObject + 0x120);
      uVar10 = func_0x7ffe99940040(_DAT_7ffe9c9343c8);
      FUN_7ffe9a79ff90(uVar10,uVar1,uVar2,uVar3,fVar13,0);
      plVar11 = (longlong *)
                (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
      if ((plVar11 != (longlong *)0x0) &&
         (lVar12 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
         lVar12 != 0)) {
        FUN_7ffe9a7c26c0(lVar12,uVar10,thisObject[0x10],0);
        return;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

