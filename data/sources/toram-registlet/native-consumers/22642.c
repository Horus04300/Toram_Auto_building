
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void HardHitAction_OnInitialize(undefined *thisObject,undefined *actarAction,undefined *methodInfo)

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
  double dVar11;
  double dStackX_8;
  undefined8 uStackX_10;
  
  if (DAT_7ffe9cadeb79 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadeb79 = '\x01';
  }
  uStackX_10 = 0;
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
  uVar4 = FUN_7ffe9a4adfc0(plVar9,&uStackX_10,0);
  *(undefined4 *)(thisObject + 0xfc) = uVar4;
  uVar4 = FUN_7ffe9a4adf80(uStackX_10,0);
  *(undefined4 *)(thisObject + 0x20) = uVar4;
  fVar10 = (float)(byte)thisObject[0x14] * _DAT_7ffe9c049ce0 + _DAT_7ffe9c049cfc;
  *(float *)(thisObject + 0x120) = fVar10;
  if (*(int *)(thisObject + 0xfc) == 0xb) {
    *(float *)(thisObject + 0x120) = fVar10 + _DAT_7ffe9c049cf4;
  }
  if (((plVar9 != (longlong *)0x0) &&
      (plVar6 = (longlong *)(**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0)),
      plVar6 != (longlong *)0x0)) &&
     (puVar7 = (undefined *)(**(code **)(*plVar6 + 0x218))(plVar6,*(undefined8 *)(*plVar6 + 0x220)),
     puVar7 != (undefined *)0x0)) {
    puVar7 = GemCartBufferManager_GetGemCartBuffer(puVar7,0x65,(undefined *)0x0);
    if (puVar7 != (undefined *)0x0) {
      fVar10 = *(float *)(thisObject + 0x120);
      iVar5 = GemCartBufferBase_GetValue(puVar7,(undefined *)0x4,(undefined *)0x0);
      *(float *)(thisObject + 0x120) = (float)iVar5 + fVar10;
    }
    fVar10 = *(float *)(thisObject + 0x120) / _DAT_7ffe9c049cfc;
    bVar1 = thisObject[0x14];
    *(uint *)(thisObject + 0x124) = (bVar1 + 10) * 5;
    *(float *)(thisObject + 0x120) = fVar10;
    if (DAT_7ffe9cad9b50 == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c968830);
      DAT_7ffe9cad9b50 = '\x01';
    }
    fVar10 = (float)bVar1 * _DAT_7ffe9c04b590;
    if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    if (fVar10 < 0.0) {
      dVar11 = (double)func_0x7ffe99997688();
      if (dVar11 == _DAT_7ffe9c049b98) {
        if (((longlong)dStackX_8 & 1U) != 0) {
          dStackX_8 = dStackX_8 - _DAT_7ffe9c049b68;
        }
      }
      else {
        dStackX_8 = (double)func_0x7ffe99997768();
      }
    }
    else {
      dVar11 = (double)func_0x7ffe99997688();
      if (dVar11 == _DAT_7ffe9c049b60) {
        if (((longlong)dStackX_8 & 1U) != 0) {
          dStackX_8 = dStackX_8 + _DAT_7ffe9c049b68;
        }
      }
      else {
        dStackX_8 = (double)func_0x7ffe999978b4();
      }
    }
    *(int *)(thisObject + 0x128) = (int)dStackX_8 + 5;
    if (*(int *)(thisObject + 0xfc) == 10) {
      *(int *)(thisObject + 0x128) = (int)dStackX_8 + 0x37;
    }
    uVar8 = (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
    uVar4 = FUN_7ffe9a4aabb0(uVar8,0);
    *(undefined4 *)(thisObject + 0x78) = uVar4;
    FUN_7ffe9a4aacd0(thisObject,plVar9,0);
    return;
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

