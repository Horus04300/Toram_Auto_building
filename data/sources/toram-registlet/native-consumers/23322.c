
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void LunaDitherStarAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  byte bVar3;
  undefined4 uVar4;
  int iVar5;
  longlong *plVar6;
  longlong lVar7;
  undefined8 uVar8;
  undefined *thisObject_00;
  longlong *plVar9;
  float fVar10;
  undefined8 uStackX_8;
  
  if (DAT_7ffe9cadec72 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadec72 = '\x01';
  }
  uStackX_8 = 0;
  plVar9 = (longlong *)0x0;
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
      plVar9 = (longlong *)actarAction;
    }
  }
  uVar4 = FUN_7ffe9a4adfc0(plVar9,&uStackX_8,0);
  *(undefined4 *)(thisObject + 0xfc) = uVar4;
  uVar4 = func_0x7ffe99a4d6a0();
  *(undefined4 *)(thisObject + 0x20) = uVar4;
  *(undefined4 *)(thisObject + 0x30) = 6;
  if (plVar9 != (longlong *)0x0) {
    plVar6 = (longlong *)(**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
    if (plVar6 != (longlong *)0x0) {
      lVar7 = (**(code **)(*plVar6 + 0x1d8))(plVar6,*(undefined8 *)(*plVar6 + 0x1e0));
      if (lVar7 != 0) {
        uVar4 = FUN_7ffe9a4eb8d0(lVar7,2);
        *(undefined4 *)(thisObject + 0x34) = uVar4;
        uVar8 = (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
        uVar4 = FUN_7ffe9a4aabb0(uVar8,0);
        *(undefined4 *)(thisObject + 0x78) = uVar4;
        plVar6 = (longlong *)(**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0))
        ;
        if (plVar6 != (longlong *)0x0) {
          thisObject_00 =
               (undefined *)(**(code **)(*plVar6 + 0x218))(plVar6,*(undefined8 *)(*plVar6 + 0x220));
          if (thisObject_00 != (undefined *)0x0) {
            bVar3 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x410,(undefined *)0x0);
            uVar4 = 400;
            if (bVar3 != 0) {
              uVar4 = 300;
            }
            *(undefined4 *)(thisObject + 0x120) = uVar4;
            FUN_7ffe9a4aacd0(thisObject,plVar9,0);
            fVar10 = (float)(((byte)thisObject[0x14] + 10) * 0x32);
            *(float *)(thisObject + 0x124) = fVar10;
            plVar9 = (longlong *)
                     (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
            if (plVar9 != (longlong *)0x0) {
              lVar7 = (**(code **)(*plVar9 + 0x1a8))(plVar9,*(undefined8 *)(*plVar9 + 0x1b0));
              if (lVar7 != 0) {
                iVar5 = FUN_7ffe99742ec0(5,_DAT_7ffe9c940d40,lVar7);
                *(undefined4 *)(thisObject + 0x128) = 400;
                *(float *)(thisObject + 0x124) = (float)iVar5 / _DAT_7ffe9c049cd8 + fVar10;
                uVar8 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
                FUN_7ffe9a9002e0(uVar8,0xbfb46a8,0);
                *(undefined8 *)(thisObject + 0x58) = uVar8;
                il2cpp_write_barrier_0();
                if ((*(longlong *)(thisObject + 0x58) != 0) &&
                   (lVar7 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar7 != 0)) {
                  FUN_7ffe9ad10e00(lVar7,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
                  *(uint *)(thisObject + 0x108) = *(uint *)(thisObject + 0x108) | 2;
                  return;
                }
              }
            }
          }
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

