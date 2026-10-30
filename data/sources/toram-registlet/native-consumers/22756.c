
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SpiralAirAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  undefined4 uVar3;
  int iVar4;
  longlong *plVar5;
  undefined *puVar6;
  undefined8 uVar7;
  longlong *plVar8;
  float fVar9;
  undefined8 uStackX_8;
  
  if (DAT_7ffe9cadeba7 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadeba7 = '\x01';
  }
  uStackX_8 = 0;
  plVar8 = (longlong *)0x0;
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
      plVar8 = (longlong *)actarAction;
    }
  }
  uVar3 = FUN_7ffe9a4adfc0(plVar8,&uStackX_8,0);
  *(undefined4 *)(thisObject + 0xfc) = uVar3;
  uVar3 = FUN_7ffe9a4adf80(uStackX_8,0);
  *(undefined4 *)(thisObject + 0x20) = uVar3;
  fVar9 = (float)(((uint)(byte)thisObject[0x14] + (uint)(byte)thisObject[0x14] * 2) * 2 + 0x14);
  *(float *)(thisObject + 0x120) = fVar9;
  if (*(int *)(thisObject + 0xfc) == 0xb) {
    *(float *)(thisObject + 0x120) = fVar9 + _DAT_7ffe9c049ce0;
  }
  if (plVar8 != (longlong *)0x0) {
    plVar5 = (longlong *)(**(code **)(*plVar8 + 0x298))(plVar8,*(undefined8 *)(*plVar8 + 0x2a0));
    if (plVar5 != (longlong *)0x0) {
      puVar6 = (undefined *)(**(code **)(*plVar5 + 0x218))(plVar5,*(undefined8 *)(*plVar5 + 0x220));
      if (puVar6 != (undefined *)0x0) {
        puVar6 = GemCartBufferManager_GetGemCartBuffer(puVar6,0xca,(undefined *)0x0);
        if (puVar6 != (undefined *)0x0) {
          fVar9 = *(float *)(thisObject + 0x120);
          iVar4 = GemCartBufferBase_GetValue(puVar6,(undefined *)0x4,(undefined *)0x0);
          *(float *)(thisObject + 0x120) = (float)iVar4 + fVar9;
        }
        fVar9 = *(float *)(thisObject + 0x120) / _DAT_7ffe9c049cfc;
        *(undefined4 *)(thisObject + 0x124) = 0x1e;
        *(undefined4 *)(thisObject + 0x128) = 10;
        *(undefined4 *)(thisObject + 0x28) = 10;
        *(float *)(thisObject + 0x120) = fVar9;
        uVar7 = (**(code **)(*plVar8 + 0x298))(plVar8,*(undefined8 *)(*plVar8 + 0x2a0));
        uVar3 = FUN_7ffe9a4aabb0(uVar7,0);
        *(undefined4 *)(thisObject + 0x78) = uVar3;
        FUN_7ffe9a4aacd0(thisObject,plVar8,0);
        return;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

