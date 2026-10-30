
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void WindStyleAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  undefined4 uVar3;
  int iVar4;
  longlong lVar5;
  undefined8 uVar6;
  longlong *plVar7;
  undefined *puVar8;
  float fVar9;
  undefined8 uStackX_8;
  
  if (DAT_7ffe9cadf182 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadf182 = '\x01';
  }
  uStackX_8 = 0;
  plVar7 = (longlong *)0x0;
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    if (bVar2) {
      plVar7 = (longlong *)actarAction;
    }
  }
  uVar3 = FUN_7ffe9a4adfc0(plVar7,&uStackX_8,0);
  *(undefined4 *)(thisObject + 0xfc) = uVar3;
  uVar3 = FUN_7ffe9a4adf80(uStackX_8,0);
  *(undefined4 *)(thisObject + 0x20) = uVar3;
  if (plVar7 != (longlong *)0x0) {
    lVar5 = (**(code **)(*plVar7 + 0x298))(plVar7,*(undefined8 *)(*plVar7 + 0x2a0));
    if (lVar5 != 0) {
      uVar3 = FUN_7ffe9a4a1cc0(lVar5,0);
      *(undefined4 *)(thisObject + 0x30) = uVar3;
      uVar6 = (**(code **)(*plVar7 + 0x298))(plVar7,*(undefined8 *)(*plVar7 + 0x2a0));
      uVar3 = FUN_7ffe9a4aabb0(uVar6,0);
      *(undefined4 *)(thisObject + 0x78) = uVar3;
      uVar6 = (**(code **)(*plVar7 + 0x298))(plVar7,*(undefined8 *)(*plVar7 + 0x2a0));
      FUN_7ffe9a7b7ae0(thisObject,_DAT_7ffe9c049b18,uVar6,0);
      uVar3 = FUN_7ffe9a7b7a30(thisObject,500,plVar7,0);
      *(undefined4 *)(thisObject + 0x128) = uVar3;
      FUN_7ffe9a4aacd0(thisObject,plVar7,0);
      uVar3 = func_0x7ffe99a4d6a0();
      *(undefined4 *)(thisObject + 0x138) = uVar3;
      iVar4 = ((uint)(byte)thisObject[0x14] + (uint)(byte)thisObject[0x14] * 4) * 2;
      *(int *)(thisObject + 0x130) = iVar4 + 200;
      fVar9 = (float)(iVar4 + 500);
      *(float *)(thisObject + 300) = fVar9;
      uVar6 = (**(code **)(*plVar7 + 0x298))(plVar7,*(undefined8 *)(*plVar7 + 0x2a0));
      iVar4 = FUN_7ffe9a7b7d10(thisObject,uVar6,0);
      fVar9 = (float)iVar4 + fVar9;
      *(float *)(thisObject + 300) = fVar9;
      uVar6 = (**(code **)(*plVar7 + 0x298))(plVar7,*(undefined8 *)(*plVar7 + 0x2a0));
      iVar4 = FUN_7ffe9a7b7c00(thisObject,uVar6,0);
      *(float *)(thisObject + 300) = (float)(iVar4 * 0x14) + fVar9;
      plVar7 = (longlong *)(**(code **)(*plVar7 + 0x298))(plVar7,*(undefined8 *)(*plVar7 + 0x2a0));
      if (plVar7 != (longlong *)0x0) {
        puVar8 = (undefined *)
                 (**(code **)(*plVar7 + 0x218))(plVar7,*(undefined8 *)(*plVar7 + 0x220));
        if (puVar8 != (undefined *)0x0) {
          puVar8 = GemCartBufferManager_GetGemCartBuffer(puVar8,0x40e,(undefined *)0x0);
          if (puVar8 != (undefined *)0x0) {
            thisObject[0x149] = 1;
            iVar4 = GemCartBufferBase_GetValue(puVar8,(undefined *)0x2,(undefined *)0x0);
            *(int *)(thisObject + 0x14c) = iVar4;
          }
          return;
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

