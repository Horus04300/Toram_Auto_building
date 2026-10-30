
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void FlashDrawnSwordAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  float fVar1;
  longlong lVar2;
  code *pcVar3;
  bool bVar4;
  int iVar5;
  longlong *plVar6;
  undefined *puVar7;
  undefined8 uVar8;
  longlong *plVar9;
  undefined4 uVar10;
  undefined8 uStackX_8;
  
  if (DAT_7ffe9cadefb0 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadefb0 = '\x01';
  }
  uStackX_8 = 0;
  if (actarAction == (undefined *)0x0) {
    plVar9 = (longlong *)0x0;
  }
  else {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar4 = false;
    }
    else {
      bVar4 = true;
    }
    plVar9 = (longlong *)0x0;
    if (bVar4) {
      plVar9 = (longlong *)actarAction;
    }
  }
  iVar5 = FUN_7ffe9a4adfc0(plVar9,&uStackX_8,0);
  *(int *)(thisObject + 0xfc) = iVar5;
  if (iVar5 == 0xc) {
    FUN_7ffe9a4add40(plVar9,&uStackX_8,0);
  }
  uVar10 = FUN_7ffe9a4adf80(uStackX_8,0);
  lVar2 = *(longlong *)(thisObject + 0x120);
  *(undefined4 *)(thisObject + 0x20) = uVar10;
  if (lVar2 != 0) {
    if (*(int *)(lVar2 + 0x18) == 0) {
LAB_7ffe9a6e1de8:
      FUN_7ffe9996d790();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
    *(undefined4 *)(lVar2 + 0x20) = 0x42480000;
    lVar2 = *(longlong *)(thisObject + 0x120);
    if (lVar2 != 0) {
      if (*(int *)(lVar2 + 0x18) == 0) goto LAB_7ffe9a6e1de8;
      *(float *)(lVar2 + 0x20) = *(float *)(lVar2 + 0x20) / _DAT_7ffe9c049cfc;
      lVar2 = *(longlong *)(thisObject + 0x128);
      if (lVar2 != 0) {
        if (*(int *)(lVar2 + 0x18) == 0) goto LAB_7ffe9a6e1de8;
        *(undefined4 *)(lVar2 + 0x20) = 0;
        lVar2 = *(longlong *)(thisObject + 0x120);
        if (lVar2 != 0) {
          if (*(uint *)(lVar2 + 0x18) < 2) goto LAB_7ffe9a6e1de8;
          *(float *)(lVar2 + 0x24) = (float)(((byte)thisObject[0x14] + 0x14) * 5);
          if (plVar9 != (longlong *)0x0) {
            plVar6 = (longlong *)
                     (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
            if (plVar6 != (longlong *)0x0) {
              puVar7 = (undefined *)
                       (**(code **)(*plVar6 + 0x218))(plVar6,*(undefined8 *)(*plVar6 + 0x220));
              if (puVar7 != (undefined *)0x0) {
                puVar7 = GemCartBufferManager_GetGemCartBuffer(puVar7,0x71,(undefined *)0x0);
                if (puVar7 != (undefined *)0x0) {
                  lVar2 = *(longlong *)(thisObject + 0x120);
                  if (lVar2 == 0) goto LAB_7ffe9a6e1de2;
                  if (*(uint *)(lVar2 + 0x18) < 2) goto LAB_7ffe9a6e1de8;
                  fVar1 = *(float *)(lVar2 + 0x24);
                  iVar5 = GemCartBufferBase_GetValue(puVar7,(undefined *)0x4,(undefined *)0x0);
                  *(float *)(lVar2 + 0x24) = (float)iVar5 + fVar1;
                }
                lVar2 = *(longlong *)(thisObject + 0x120);
                if (lVar2 != 0) {
                  if (1 < *(uint *)(lVar2 + 0x18)) {
                    *(float *)(lVar2 + 0x24) = *(float *)(lVar2 + 0x24) / _DAT_7ffe9c049cfc;
                    lVar2 = *(longlong *)(thisObject + 0x128);
                    if (lVar2 == 0) goto LAB_7ffe9a6e1de2;
                    if (1 < *(uint *)(lVar2 + 0x18)) {
                      *(uint *)(lVar2 + 0x24) = ((byte)thisObject[0x14] + 10) * 5;
                      uVar8 = (**(code **)(*plVar9 + 0x298))
                                        (plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
                      uVar10 = FUN_7ffe9a4aabb0(uVar8,0);
                      *(undefined4 *)(thisObject + 0x78) = uVar10;
                      FUN_7ffe9a4aacd0(thisObject,plVar9,0);
                      *(uint *)(thisObject + 0x108) = *(uint *)(thisObject + 0x108) | 2;
                      return;
                    }
                  }
                  goto LAB_7ffe9a6e1de8;
                }
              }
            }
          }
        }
      }
    }
  }
LAB_7ffe9a6e1de2:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

