
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void CutOffTheDisasterAction_DamageCut
               (undefined *playerAction,undefined *skillAction,undefined *damageData,
               undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  undefined *puVar5;
  longlong lVar6;
  longlong *plVar7;
  float fVar8;
  
  if (DAT_7ffe9cadefa8 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c972b60);
    DAT_7ffe9cadefa8 = '\x01';
  }
  if (skillAction == (undefined *)0x0) {
    plVar7 = (longlong *)0x0;
  }
  else {
    if ((*(byte *)(*(longlong *)skillAction + 0x130) < *(byte *)(_DAT_7ffe9c972b60 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)skillAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c972b60 + 0x130) * 8) != _DAT_7ffe9c972b60)) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    plVar7 = (longlong *)0x0;
    if (bVar2) {
      plVar7 = (longlong *)skillAction;
    }
  }
  cVar3 = FUN_7ffe9a8fecd0(plVar7,0,0);
  if (cVar3 != '\0') {
    if (plVar7 == (longlong *)0x0) goto LAB_7ffe9a6e04b8;
    iVar4 = (**(code **)(*plVar7 + 0x198))(plVar7,*(undefined8 *)(*plVar7 + 0x1a0));
    if (iVar4 == 2) {
      iVar4 = 0x2d;
      if (((playerAction == (undefined *)0x0) ||
          (plVar7 = (longlong *)
                    (**(code **)(*(longlong *)playerAction + 0x298))
                              (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
          plVar7 == (longlong *)0x0)) ||
         (puVar5 = (undefined *)
                   (**(code **)(*plVar7 + 0x218))(plVar7,*(undefined8 *)(*plVar7 + 0x220)),
         puVar5 == (undefined *)0x0)) goto LAB_7ffe9a6e04b8;
      puVar5 = GemCartBufferManager_GetGemCartBuffer(puVar5,0xd7,(undefined *)0x0);
      if (puVar5 != (undefined *)0x0) {
        iVar4 = GemCartBufferBase_GetValue(puVar5,(undefined *)0x2,(undefined *)0x0);
        iVar4 = iVar4 + 0x2d;
      }
      if (damageData == (undefined *)0x0) goto LAB_7ffe9a6e04b8;
      func_0x7ffe9a900040(damageData,
                          (int)((_DAT_7ffe9c049b18 - (float)iVar4 * _DAT_7ffe9c049b34) *
                               (float)*(int *)(damageData + 0x84)),0);
    }
    else if ((damageData == (undefined *)0x0) ||
            (func_0x7ffe9a900040(damageData,
                                 (int)((float)*(int *)(damageData + 0x84) * _DAT_7ffe9c04a474),0),
            playerAction == (undefined *)0x0)) goto LAB_7ffe9a6e04b8;
    lVar6 = (**(code **)(*(longlong *)playerAction + 0x298))
                      (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if (lVar6 == 0) {
LAB_7ffe9a6e04b8:
      FUN_7ffe9996d7a0();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    fVar8 = (float)FUN_7ffe9a4a22c0(lVar6,0);
    if (_DAT_7ffe9c049b88 <= fVar8) {
      plVar7 = (longlong *)
               (**(code **)(*(longlong *)playerAction + 0x298))
                         (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar7 == (longlong *)0x0) ||
         (lVar6 = (**(code **)(*plVar7 + 0x178))(plVar7,*(undefined8 *)(*plVar7 + 0x180)),
         lVar6 == 0)) goto LAB_7ffe9a6e04b8;
      if (*(int *)(lVar6 + 0x14) <= *(int *)(damageData + 0x84)) {
        plVar7 = (longlong *)
                 (**(code **)(*(longlong *)playerAction + 0x298))
                           (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if ((plVar7 == (longlong *)0x0) ||
           (lVar6 = (**(code **)(*plVar7 + 0x178))(plVar7,*(undefined8 *)(*plVar7 + 0x180)),
           lVar6 == 0)) goto LAB_7ffe9a6e04b8;
        func_0x7ffe9a900040(damageData,*(int *)(lVar6 + 0x14) + -1,0);
      }
    }
    FUN_7ffe9a8ffe30(damageData,0,0,0);
  }
  return;
}

