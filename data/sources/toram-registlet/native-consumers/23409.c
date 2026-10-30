
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PhantomRaveAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  byte bVar1;
  longlong lVar2;
  code *pcVar3;
  bool bVar4;
  undefined4 uVar5;
  int iVar6;
  longlong *plVar7;
  undefined *puVar8;
  undefined8 uVar9;
  longlong *plVar10;
  float fVar11;
  undefined8 uStackX_8;
  
  if (DAT_7ffe9cadec90 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c920c90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadec90 = '\x01';
  }
  uStackX_8 = 0;
  plVar10 = (longlong *)0x0;
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar4 = false;
    }
    else {
      bVar4 = true;
    }
    if (bVar4) {
      plVar10 = (longlong *)actarAction;
    }
  }
  *(undefined4 *)(thisObject + 0x30) = 6;
  uVar5 = FUN_7ffe9a4adfc0(plVar10,&uStackX_8,0);
  *(undefined4 *)(thisObject + 0xfc) = uVar5;
  uVar5 = func_0x7ffe99a4d6a0();
  *(undefined4 *)(thisObject + 0x20) = uVar5;
  *(float *)(thisObject + 0x128) = (float)(((byte)thisObject[0x14] + 0x19) * 0x14);
  if (plVar10 != (longlong *)0x0) {
    plVar7 = (longlong *)(**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
    if (plVar7 != (longlong *)0x0) {
      puVar8 = (undefined *)(**(code **)(*plVar7 + 0x218))(plVar7,*(undefined8 *)(*plVar7 + 0x220));
      if (puVar8 != (undefined *)0x0) {
        puVar8 = GemCartBufferManager_GetGemCartBuffer(puVar8,0x131,(undefined *)0x0);
        if (puVar8 != (undefined *)0x0) {
          fVar11 = *(float *)(thisObject + 0x128);
          iVar6 = GemCartBufferBase_GetValue(puVar8,(undefined *)0x4,(undefined *)0x0);
          *(float *)(thisObject + 0x128) = (float)iVar6 + fVar11;
        }
        bVar1 = thisObject[0x14];
        fVar11 = *(float *)(thisObject + 0x128) / _DAT_7ffe9c049cfc;
        *(uint *)(thisObject + 0x134) = ((uint)bVar1 + (uint)bVar1 * 4) * 2;
        *(uint *)(thisObject + 300) = (bVar1 + 10) * 0x14;
        *(float *)(thisObject + 0x128) = fVar11;
        uVar9 = (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
        uVar5 = FUN_7ffe9a4aabb0(uVar9,0);
        *(undefined4 *)(thisObject + 0x78) = uVar5;
        *(undefined4 *)(thisObject + 0x130) = 400;
        FUN_7ffe9a4aacd0(thisObject,plVar10,0);
        uVar9 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
        FUN_7ffe9a9002e0(uVar9,0xf4241,0);
        *(undefined8 *)(thisObject + 0x58) = uVar9;
        il2cpp_write_barrier_0();
        if ((*(longlong *)(thisObject + 0x58) != 0) &&
           (lVar2 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar2 != 0)) {
          FUN_7ffe9ad10e00(lVar2,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
          uVar9 = func_0x7ffe99940040(_DAT_7ffe9c920c90);
          FUN_7ffe9a7c0770(uVar9,2,plVar10,0);
          *(undefined8 *)(thisObject + 0x140) = uVar9;
          il2cpp_write_barrier_0();
          return;
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

