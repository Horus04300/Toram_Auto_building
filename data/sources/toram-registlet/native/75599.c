
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBuffer_InflexibilityEmergingBuff_Damaged
               (undefined *playerAction,int damage,undefined *hitReaction,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  longlong *plVar4;
  undefined *puVar5;
  longlong lVar6;
  longlong *aplStack_18 [2];
  
  if (DAT_7ffe9cadd3da == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c968c00);
    DAT_7ffe9cadd3da = '\x01';
  }
  aplStack_18[0] = (longlong *)0x0;
  if (damage < 1) {
    return;
  }
  if ((int)hitReaction == 2) {
    return;
  }
  if ((int)hitReaction == 6) {
    return;
  }
  if (((playerAction != (undefined *)0x0) && (*(longlong *)(playerAction + 0x30) != 0)) &&
     (plVar4 = *(longlong **)(*(longlong *)(playerAction + 0x30) + 0x30), plVar4 != (longlong *)0x0)
     ) {
    plVar4 = (longlong *)(**(code **)(*plVar4 + 0x188))(plVar4,*(undefined8 *)(*plVar4 + 400));
    cVar2 = FUN_7ffe9a8fecd0(plVar4,0,0);
    if (cVar2 != '\0') {
      if (plVar4 == (longlong *)0x0) goto LAB_7ffe9a2eb938;
      iVar3 = (**(code **)(*plVar4 + 0x188))(plVar4,*(undefined8 *)(*plVar4 + 400));
      if (iVar3 == 0x267) {
        return;
      }
      iVar3 = (**(code **)(*plVar4 + 0x188))(plVar4,*(undefined8 *)(*plVar4 + 400));
      if (iVar3 == 0x26a) {
        return;
      }
      iVar3 = (**(code **)(*plVar4 + 0x188))(plVar4,*(undefined8 *)(*plVar4 + 400));
      if (iVar3 == 0x26f) {
        return;
      }
    }
    plVar4 = (longlong *)
             (**(code **)(*(longlong *)playerAction + 0x298))
                       (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if ((plVar4 != (longlong *)0x0) &&
       (puVar5 = (undefined *)
                 (**(code **)(*plVar4 + 0x218))(plVar4,*(undefined8 *)(*plVar4 + 0x220)),
       puVar5 != (undefined *)0x0)) {
      puVar5 = GemCartBufferManager_GetGemCartBuffer(puVar5,0x415,(undefined *)0x0);
      if (puVar5 == (undefined *)0x0) {
        return;
      }
      plVar4 = (longlong *)
               (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar4 != (longlong *)0x0) &&
         (lVar6 = (**(code **)(*plVar4 + 0x1c8))(plVar4,*(undefined8 *)(*plVar4 + 0x1d0)),
         lVar6 != 0)) {
        cVar2 = FUN_7ffe9abc2210(lVar6,0x273,aplStack_18,_DAT_7ffe9c968c00);
        if (cVar2 != '\0') {
          iVar3 = GemCartBufferBase_GetValue(puVar5,(undefined *)0x2,(undefined *)0x0);
          if (aplStack_18[0] == (longlong *)0x0) goto LAB_7ffe9a2eb938;
          (**(code **)(*aplStack_18[0] + 0x2d8))
                    (aplStack_18[0],iVar3,*(undefined8 *)(*aplStack_18[0] + 0x2e0));
        }
        return;
      }
    }
  }
LAB_7ffe9a2eb938:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

