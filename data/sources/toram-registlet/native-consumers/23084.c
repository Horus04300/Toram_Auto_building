
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void DemonCroweAction_ActionPreparation
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  undefined4 uVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  longlong lVar9;
  undefined8 *puVar10;
  undefined8 uVar11;
  longlong *plVar12;
  undefined *thisObject_00;
  undefined8 uVar13;
  longlong *plVar14;
  float fVar15;
  longlong *plStack_38;
  undefined1 auStack_30 [24];
  
  if (DAT_7ffe9cadec1c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c902d18);
    FUN_7ffe9996d590(&DAT_7ffe9c8f9db8);
    FUN_7ffe9996d590(&DAT_7ffe9c93e740);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c9632c0);
    FUN_7ffe9996d590(&DAT_7ffe9c9282a8);
    FUN_7ffe9996d590(&DAT_7ffe9c932dd8);
    DAT_7ffe9cadec1c = '\x01';
  }
  plVar14 = (longlong *)0x0;
  plStack_38 = (longlong *)0x0;
  lVar8 = func_0x7ffe99940040(_DAT_7ffe9c932dd8);
  func_0x7ffe999c3920(lVar8,0);
  if (lVar8 == 0) goto LAB_7ffe9a66907d;
  *(undefined **)(lVar8 + 0x10) = thisObject;
  il2cpp_write_barrier_0();
  *(undefined **)(lVar8 + 0x18) = actarAction;
  il2cpp_write_barrier_0();
  FUN_7ffe9a4a5ca0(thisObject,*(undefined8 *)(lVar8 + 0x18),target,0);
  cVar4 = func_0x7ffe9a4aea60(thisObject,0);
  if (cVar4 != '\0') {
    return;
  }
  if ((*(longlong *)(lVar8 + 0x18) == 0) ||
     (lVar9 = FUN_7ffe9bd98a10(*(longlong *)(lVar8 + 0x18),0), lVar9 == 0)) goto LAB_7ffe9a66907d;
  puVar10 = (undefined8 *)FUN_7ffe9bdbf710(auStack_30,lVar9,0);
  uVar1 = *(undefined4 *)(puVar10 + 1);
  *(undefined8 *)(thisObject + 300) = *puVar10;
  *(undefined4 *)(thisObject + 0x134) = uVar1;
  if (target == (undefined *)0x0) goto LAB_7ffe9a66907d;
  uVar11 = FUN_7ffe9bd9b890(target,0);
  *(undefined8 *)(thisObject + 0x140) = uVar11;
  il2cpp_write_barrier_0();
  plVar12 = *(longlong **)(lVar8 + 0x18);
  if (plVar12 != (longlong *)0x0) {
    if ((*(byte *)(*plVar12 + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*plVar12 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8)
        != _DAT_7ffe9c922720)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    plVar14 = (longlong *)0x0;
    if (bVar3) {
      plVar14 = plVar12;
    }
  }
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar4 = FUN_7ffe9bda2160(plVar14,0,0);
  if (cVar4 == '\0') {
    return;
  }
  if (((plVar14 == (longlong *)0x0) ||
      (plVar12 = (longlong *)
                 (**(code **)(*plVar14 + 0x298))(plVar14,*(undefined8 *)(*plVar14 + 0x2a0)),
      plVar12 == (longlong *)0x0)) ||
     (thisObject_00 =
           (undefined *)(**(code **)(*plVar12 + 0x218))(plVar12,*(undefined8 *)(*plVar12 + 0x220)),
     thisObject_00 == (undefined *)0x0)) goto LAB_7ffe9a66907d;
  bVar5 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x3f8,(undefined *)0x0);
  thisObject[0x138] = bVar5;
  if (bVar5 == 0) {
    lVar9 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
    if (lVar9 == 0) goto LAB_7ffe9a66907d;
    uVar11 = FUN_7ffe9a33dc30(lVar9,0);
    uVar13 = func_0x7ffe99940040(_DAT_7ffe9c93e740);
    FUN_7ffe9af13420(uVar13,lVar8,_DAT_7ffe9c9282a8,0);
    iVar6 = FUN_7ffe9ab81180(uVar11,uVar13,_DAT_7ffe9c902d18);
    *(int *)(thisObject + 0x104) = iVar6;
    if (iVar6 < 0xb) {
      if (iVar6 < 1) goto LAB_7ffe9a668f12;
    }
    else {
      iVar6 = 10;
    }
  }
  else {
    fVar15 = 0.0;
    if (0.0 <= *(float *)(thisObject + 0x120) - _DAT_7ffe9c049cfc) {
      fVar15 = *(float *)(thisObject + 0x120) - _DAT_7ffe9c049cfc;
    }
    *(float *)(thisObject + 0x120) = fVar15;
LAB_7ffe9a668f12:
    iVar6 = 1;
  }
  *(int *)(thisObject + 0x104) = iVar6;
  lVar8 = (**(code **)(*plVar14 + 0x298))(plVar14,*(undefined8 *)(*plVar14 + 0x2a0));
  if (lVar8 != 0) {
    fVar15 = (float)FUN_7ffe9a4a22c0(lVar8,0);
    iVar6 = (int)fVar15;
    plVar14 = (longlong *)(**(code **)(*plVar14 + 0x298))(plVar14,*(undefined8 *)(*plVar14 + 0x2a0))
    ;
    if (((plVar14 != (longlong *)0x0) &&
        (lVar8 = (**(code **)(*plVar14 + 0x1c8))(plVar14,*(undefined8 *)(*plVar14 + 0x1d0)),
        lVar8 != 0)) && (*(longlong *)(lVar8 + 0x40) != 0)) {
      cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x40),0x428,&plStack_38,_DAT_7ffe9c934418);
      if (cVar4 != '\0') {
        if (plStack_38 == (longlong *)0x0) goto LAB_7ffe9a66907d;
        if (((*(byte *)(*plStack_38 + 0x130) < *(byte *)(_DAT_7ffe9c8f9db8 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*plStack_38 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c8f9db8 + 0x130) * 8) != _DAT_7ffe9c8f9db8)) ||
           (plStack_38 == (longlong *)0x0)) {
          FUN_7ffe9996c950(plStack_38);
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
        iVar7 = FUN_7ffe9a78abb0(plStack_38,3);
        iVar6 = iVar6 - iVar7;
      }
      iVar7 = 100 - iVar6;
      if (0x5a < 100 - iVar6) {
        iVar7 = 0x5a;
      }
      iVar6 = (iVar7 / 10) * 10;
      fVar15 = (float)iVar6 / _DAT_7ffe9c049fc4;
      *(int *)(thisObject + 0x128) = iVar6 / (int)(0xb - (uint)(byte)thisObject[0x14]);
      *(float *)(thisObject + 0x120) = fVar15 * *(float *)(thisObject + 0x120);
      return;
    }
  }
LAB_7ffe9a66907d:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

