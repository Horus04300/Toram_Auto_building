
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte PlayerAttackBase_ChackCorrectHit
               (undefined *thisObject,undefined *status,int hit,byte isFlash,undefined *correct,
               undefined *methodInfo)

{
  longlong *plVar1;
  bool bVar2;
  code *pcVar3;
  bool bVar4;
  char cVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  longlong lVar9;
  undefined *puVar10;
  int aiStackX_10 [2];
  longlong *aplStack_38 [2];
  
  if (DAT_7ffe9caddebb == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c903268);
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    FUN_7ffe9996d590(&DAT_7ffe9c968e08);
    DAT_7ffe9caddebb = '\x01';
  }
  aplStack_38[0] = (longlong *)0x0;
  *correct = 1;
  aiStackX_10[0] = 0;
  if (((status == (undefined *)0x0) ||
      (lVar9 = (**(code **)(*(longlong *)status + 0x1f8))
                         (status,*(undefined8 *)(*(longlong *)status + 0x200)), lVar9 == 0)) ||
     (plVar1 = *(longlong **)(lVar9 + 0x18), plVar1 == (longlong *)0x0)) goto LAB_7ffe9a4ac1b1;
  (**(code **)(*plVar1 + 0x1d8))(plVar1,aiStackX_10,*(undefined8 *)(*plVar1 + 0x1e0));
  iVar7 = FUN_7ffe9bda4580(0,100,0);
  if (isFlash != 0) {
    iVar8 = aiStackX_10[0] * 2;
    aiStackX_10[0] = iVar8;
    if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    hit = func_0x7ffe9b506b70(hit,iVar8,0);
  }
  lVar9 = (**(code **)(*(longlong *)status + 0x1c8))
                    (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
  if (lVar9 == 0) goto LAB_7ffe9a4ac1b1;
  cVar5 = FUN_7ffe9a7cbb30(lVar9,0x3d3,aplStack_38,0);
  if (cVar5 != '\0') {
    lVar9 = (**(code **)(*(longlong *)status + 0x1f8))
                      (status,*(undefined8 *)(*(longlong *)status + 0x200));
    if (lVar9 == 0) goto LAB_7ffe9a4ac1b1;
    lVar9 = FUN_7ffe99c090e0(lVar9,0);
    iVar8 = aiStackX_10[0];
    if ((lVar9 != 0) && (*(int *)(lVar9 + 0x38) == 9)) {
      if (aplStack_38[0] == (longlong *)0x0) goto LAB_7ffe9a4ac1b1;
      if (((*(byte *)(*aplStack_38[0] + 0x130) < *(byte *)(_DAT_7ffe9c968e08 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*aplStack_38[0] + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7ffe9c968e08 + 0x130) * 8) != _DAT_7ffe9c968e08)) ||
         (aplStack_38[0] == (longlong *)0x0)) {
        FUN_7ffe9996c950(aplStack_38[0]);
        pcVar3 = (code *)swi(3);
        bVar6 = (*pcVar3)();
        return bVar6;
      }
      aiStackX_10[0] = func_0x7ffe9a7a51f0(aplStack_38[0],0);
      aiStackX_10[0] = aiStackX_10[0] + iVar8;
    }
  }
  puVar10 = (undefined *)
            (**(code **)(*(longlong *)status + 0x218))
                      (status,*(undefined8 *)(*(longlong *)status + 0x220));
  if (puVar10 == (undefined *)0x0) goto LAB_7ffe9a4ac1b1;
  puVar10 = GemCartBufferManager_GetGemCartBuffer(puVar10,0xf,(undefined *)0x0);
  if ((puVar10 != (undefined *)0x0) &&
     (iVar8 = GemCartBufferBase_GetValue(puVar10,(undefined *)0x2,(undefined *)0x0), iVar8 != 0)) {
    aiStackX_10[0] = 100;
  }
  if (iVar7 < hit) {
LAB_7ffe9a4ac1aa:
    *correct = 0;
  }
  else {
    bVar2 = iVar7 < aiStackX_10[0];
    if (aiStackX_10[0] <= iVar7) {
      lVar9 = (**(code **)(*(longlong *)status + 0x208))
                        (status,*(undefined8 *)(*(longlong *)status + 0x210));
      if (lVar9 == 0) goto LAB_7ffe9a4ac1b1;
      cVar5 = FUN_7ffe9a51e210(lVar9,0x87,0);
      if (cVar5 != '\0') {
        lVar9 = (**(code **)(*(longlong *)status + 0x208))
                          (status,*(undefined8 *)(*(longlong *)status + 0x210));
        if (lVar9 == 0) goto LAB_7ffe9a4ac1b1;
        cVar5 = FUN_7ffe9a51e030(lVar9,0x87,0);
        if (cVar5 != '\0') goto LAB_7ffe9a4ac1aa;
      }
    }
    if (*(int *)(thisObject + 0xd0) != 3) {
      return bVar2;
    }
    if ((*(byte *)(*(longlong *)thisObject + 0x130) < *(byte *)(_DAT_7ffe9c903268 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)thisObject + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c903268 + 0x130) * 8) != _DAT_7ffe9c903268)) {
      bVar4 = false;
    }
    else {
      bVar4 = true;
    }
    puVar10 = (undefined *)0x0;
    if (bVar4) {
      puVar10 = thisObject;
    }
    cVar5 = FUN_7ffe9a8fecd0(puVar10,0,0);
    if (cVar5 != '\0') {
      if (puVar10 == (undefined *)0x0) {
LAB_7ffe9a4ac1b1:
        FUN_7ffe9996d7a0();
        pcVar3 = (code *)swi(3);
        bVar6 = (*pcVar3)();
        return bVar6;
      }
      if (puVar10[0x154] == '\0') {
        return bVar2;
      }
    }
  }
  return 1;
}

