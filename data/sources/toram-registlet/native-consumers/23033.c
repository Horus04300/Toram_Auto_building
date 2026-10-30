
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BloodBiteAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  float fVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  longlong *plVar8;
  undefined *puVar9;
  longlong lVar10;
  undefined8 uVar11;
  longlong *plVar12;
  longlong *plStackX_8;
  undefined8 uStackX_10;
  
  if (DAT_7ffe9cadec0a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c8f9db8);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadec0a = '\x01';
  }
  plVar12 = (longlong *)0x0;
  uStackX_10 = 0;
  plStackX_8 = (longlong *)0x0;
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
    plVar12 = (longlong *)0x0;
    if (bVar3) {
      plVar12 = (longlong *)actarAction;
    }
  }
  uVar5 = FUN_7ffe9a4adfc0(plVar12,&uStackX_10,0);
  *(undefined4 *)(thisObject + 0xfc) = uVar5;
  uVar5 = FUN_7ffe9a4ade20(plVar12,0);
  *(undefined4 *)(thisObject + 0x100) = uVar5;
  uVar5 = func_0x7ffe99a4d6a0();
  *(undefined4 *)(thisObject + 0x20) = uVar5;
  *(float *)(thisObject + 0x120) = (float)(((byte)thisObject[0x14] + 10) * 10);
  if (((plVar12 != (longlong *)0x0) &&
      (plVar8 = (longlong *)
                (**(code **)(*plVar12 + 0x298))(plVar12,*(undefined8 *)(*plVar12 + 0x2a0)),
      plVar8 != (longlong *)0x0)) &&
     (puVar9 = (undefined *)(**(code **)(*plVar8 + 0x218))(plVar8,*(undefined8 *)(*plVar8 + 0x220)),
     puVar9 != (undefined *)0x0)) {
    puVar9 = GemCartBufferManager_GetGemCartBuffer(puVar9,0x3f7,(undefined *)0x0);
    if (puVar9 != (undefined *)0x0) {
      fVar1 = *(float *)(thisObject + 0x120);
      iVar6 = GemCartBufferBase_GetValue(puVar9,(undefined *)0x4,(undefined *)0x0);
      *(float *)(thisObject + 0x120) = (float)iVar6 + fVar1;
    }
    *(undefined4 *)(thisObject + 0x124) = 100;
    *(float *)(thisObject + 300) =
         (float)(((uint)(byte)thisObject[0x14] + (uint)(byte)thisObject[0x14] * 4) * 2);
    plVar8 = (longlong *)(**(code **)(*plVar12 + 0x298))(plVar12,*(undefined8 *)(*plVar12 + 0x2a0));
    if ((plVar8 != (longlong *)0x0) &&
       (lVar10 = (**(code **)(*plVar8 + 0x198))(plVar8,*(undefined8 *)(*plVar8 + 0x1a0)),
       lVar10 != 0)) {
      iVar6 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar10);
      *(int *)(thisObject + 0x130) = iVar6 * 10;
      plVar8 = (longlong *)
               (**(code **)(*plVar12 + 0x298))(plVar12,*(undefined8 *)(*plVar12 + 0x2a0));
      if ((plVar8 != (longlong *)0x0) &&
         ((lVar10 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)),
          lVar10 != 0 && (*(longlong *)(lVar10 + 0x40) != 0)))) {
        cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar10 + 0x40),0x428,&plStackX_8,_DAT_7ffe9c934418);
        if (cVar4 != '\0') {
          iVar6 = *(int *)(thisObject + 0x130);
          if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a666c6c;
          if (((*(byte *)(*plStackX_8 + 0x130) < *(byte *)(_DAT_7ffe9c8f9db8 + 0x130)) ||
              (*(longlong *)
                (*(longlong *)(*plStackX_8 + 200) + -8 +
                (ulonglong)*(byte *)(_DAT_7ffe9c8f9db8 + 0x130) * 8) != _DAT_7ffe9c8f9db8)) ||
             (plStackX_8 == (longlong *)0x0)) {
            FUN_7ffe9996c950(plStackX_8);
            pcVar2 = (code *)swi(3);
            (*pcVar2)();
            return;
          }
          iVar7 = FUN_7ffe9a78abb0(plStackX_8,0,0);
          *(int *)(thisObject + 0x130) = (int)((float)(iVar7 * iVar6) * _DAT_7ffe9c049b34);
        }
        uVar11 = (**(code **)(*plVar12 + 0x298))(plVar12,*(undefined8 *)(*plVar12 + 0x2a0));
        uVar5 = FUN_7ffe9a4aabb0(uVar11,0);
        *(undefined4 *)(thisObject + 0x78) = uVar5;
        FUN_7ffe9a4aacd0(thisObject,plVar12,0);
        return;
      }
    }
  }
LAB_7ffe9a666c6c:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

