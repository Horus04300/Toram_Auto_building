
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SkullShakerAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  byte bVar1;
  int iVar2;
  code *pcVar3;
  bool bVar4;
  undefined4 uVar5;
  longlong lVar6;
  longlong *plVar7;
  undefined8 uVar8;
  longlong *plVar9;
  undefined *puVar10;
  undefined8 uStackX_8;
  
  if (DAT_7ffe9cadf0f6 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadf0f6 = '\x01';
  }
  uStackX_8 = 0;
  plVar9 = (longlong *)0x0;
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
      plVar9 = (longlong *)actarAction;
    }
  }
  uVar5 = FUN_7ffe9a4adfc0(plVar9,&uStackX_8,0);
  *(undefined4 *)(thisObject + 0xfc) = uVar5;
  uVar5 = FUN_7ffe9a4adf80(uStackX_8,0);
  *(undefined4 *)(thisObject + 0x20) = uVar5;
  if (plVar9 != (longlong *)0x0) {
    lVar6 = (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
    if (lVar6 != 0) {
      uVar5 = FUN_7ffe9a4a1cc0(lVar6,0);
      *(undefined4 *)(thisObject + 0x30) = uVar5;
      *(undefined4 *)(thisObject + 0x124) = 0x2ee;
      *(undefined4 *)(thisObject + 0x128) = 200;
      if (*(int *)(thisObject + 0xfc) == 0xe) {
        *(undefined4 *)(thisObject + 0x124) = 1000;
      }
      bVar1 = thisObject[0x14];
      plVar7 = (longlong *)(**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
      if (plVar7 != (longlong *)0x0) {
        lVar6 = (**(code **)(*plVar7 + 0x188))(plVar7,*(undefined8 *)(*plVar7 + 400));
        if (lVar6 != 0) {
          iVar2 = *(int *)(lVar6 + 0x14);
          if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          uVar5 = func_0x7ffe9b506d80(iVar2 / 5 + (uint)bVar1 + (uint)bVar1 * 4,100);
          *(undefined4 *)(thisObject + 300) = uVar5;
          thisObject[0x120] = 0;
          FUN_7ffe9a4aacd0(thisObject,plVar9,0);
          uVar8 = (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
          uVar5 = FUN_7ffe9a4aabb0(uVar8,0);
          *(undefined4 *)(thisObject + 0x78) = uVar5;
          uVar8 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
          FUN_7ffe9a9002e0(uVar8,0xbf537e0,0);
          *(undefined8 *)(thisObject + 0x58) = uVar8;
          il2cpp_write_barrier_0();
          if ((*(longlong *)(thisObject + 0x58) != 0) &&
             (lVar6 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar6 != 0)) {
            FUN_7ffe9ad10e00(lVar6,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
            plVar9 = (longlong *)
                     (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
            if (plVar9 != (longlong *)0x0) {
              puVar10 = (undefined *)
                        (**(code **)(*plVar9 + 0x218))(plVar9,*(undefined8 *)(*plVar9 + 0x220));
              if (puVar10 != (undefined *)0x0) {
                puVar10 = GemCartBufferManager_GetGemCartBuffer(puVar10,0x41d,(undefined *)0x0);
                *(undefined **)(thisObject + 0x140) = puVar10;
                il2cpp_write_barrier_0();
                return;
              }
            }
          }
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

