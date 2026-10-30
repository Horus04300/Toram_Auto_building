
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void TwinSlashAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  byte bVar1;
  code *pcVar2;
  bool bVar3;
  undefined4 uVar4;
  int iVar5;
  longlong *plVar6;
  undefined *puVar7;
  undefined8 uVar8;
  longlong *plVar9;
  float fVar10;
  undefined8 uStackX_8;
  
  if (DAT_7ffe9cadecb7 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadecb7 = '\x01';
  }
  uStackX_8 = 0;
  plVar9 = (longlong *)0x0;
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    if (bVar3) {
      plVar9 = (longlong *)actarAction;
    }
  }
  uVar4 = FUN_7ffe9a4adfc0(plVar9,&uStackX_8,0);
  *(undefined4 *)(thisObject + 0xfc) = uVar4;
  uVar4 = FUN_7ffe9a4adf80(uStackX_8,0);
  bVar1 = thisObject[0x14];
  *(undefined4 *)(thisObject + 0x20) = uVar4;
  *(uint *)(thisObject + 0x124) = (bVar1 + 10) * 10;
  fVar10 = (float)bVar1 * _DAT_7ffe9c049ce4 + _DAT_7ffe9c049d98;
  *(float *)(thisObject + 0x128) = (float)((bVar1 + 10) * 5);
  *(float *)(thisObject + 0x120) = fVar10 / _DAT_7ffe9c049cfc;
  if (plVar9 != (longlong *)0x0) {
    plVar6 = (longlong *)(**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
    if (plVar6 != (longlong *)0x0) {
      puVar7 = (undefined *)(**(code **)(*plVar6 + 0x218))(plVar6,*(undefined8 *)(*plVar6 + 0x220));
      if (puVar7 != (undefined *)0x0) {
        puVar7 = GemCartBufferManager_GetGemCartBuffer(puVar7,0x6d,(undefined *)0x0);
        if (puVar7 != (undefined *)0x0) {
          fVar10 = *(float *)(thisObject + 0x128);
          iVar5 = GemCartBufferBase_GetValue(puVar7,(undefined *)0x2,(undefined *)0x0);
          *(float *)(thisObject + 0x128) = (float)iVar5 + fVar10;
        }
        *(float *)(thisObject + 0x128) = *(float *)(thisObject + 0x128) / _DAT_7ffe9c049cfc;
        uVar8 = (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
        uVar4 = FUN_7ffe9a4aabb0(uVar8,0);
        *(undefined4 *)(thisObject + 0x78) = uVar4;
        FUN_7ffe9a4aacd0(thisObject,plVar9,0);
        return;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

