
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BusterLanceAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  byte bVar1;
  code *pcVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  longlong *plVar7;
  longlong lVar8;
  longlong *plVar9;
  undefined *puVar10;
  undefined4 uVar11;
  
  if (DAT_7ffe9cadece1 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadece1 = '\x01';
  }
  if (actarAction == (undefined *)0x0) {
    uVar11 = func_0x7ffe99a4d6a0();
    *(undefined4 *)(thisObject + 0x20) = uVar11;
  }
  else {
    bVar1 = *(byte *)(_DAT_7ffe9c922720 + 0x130);
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < bVar1) ||
       (*(longlong *)(*(longlong *)(*(longlong *)actarAction + 200) + -8 + (ulonglong)bVar1 * 8) !=
        _DAT_7ffe9c922720)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    plVar9 = (longlong *)0x0;
    if (bVar3) {
      plVar9 = (longlong *)actarAction;
    }
    uVar11 = func_0x7ffe99a4d6a0((ulonglong)bVar1,0);
    *(undefined4 *)(thisObject + 0x20) = uVar11;
    if (plVar9 != (longlong *)0x0) {
      uVar6 = (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
      uVar11 = FUN_7ffe9a4aabb0(uVar6,0);
      *(undefined4 *)(thisObject + 0x78) = uVar11;
      FUN_7ffe9a4aacd0(thisObject,plVar9,0);
      *(undefined4 *)(thisObject + 0x120) = 0x43fa0000;
      *(undefined4 *)(thisObject + 0x124) = 100;
      *(float *)(thisObject + 0x128) = (float)(int)((0x14 - (uint)(byte)thisObject[0x14]) * 5);
      plVar7 = (longlong *)(**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
      if (plVar7 != (longlong *)0x0) {
        lVar8 = (**(code **)(*plVar7 + 0x1a8))(plVar7,*(undefined8 *)(*plVar7 + 0x1b0));
        if (lVar8 != 0) {
          iVar4 = FUN_7ffe99742ec0(1,_DAT_7ffe9c940d40,lVar8);
          plVar7 = (longlong *)
                   (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
          if (plVar7 != (longlong *)0x0) {
            lVar8 = (**(code **)(*plVar7 + 0x1a8))(plVar7,*(undefined8 *)(*plVar7 + 0x1b0));
            if (lVar8 != 0) {
              iVar5 = FUN_7ffe99742ec0(4,_DAT_7ffe9c940d40,lVar8);
              *(float *)(thisObject + 0x120) =
                   (float)((iVar5 + iVar4) / 2) + *(float *)(thisObject + 0x120);
              plVar9 = (longlong *)
                       (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
              if (plVar9 != (longlong *)0x0) {
                puVar10 = (undefined *)
                          (**(code **)(*plVar9 + 0x218))(plVar9,*(undefined8 *)(*plVar9 + 0x220));
                if (puVar10 != (undefined *)0x0) {
                  puVar10 = GemCartBufferManager_GetGemCartBuffer(puVar10,0x414,(undefined *)0x0);
                  if (puVar10 != (undefined *)0x0) {
                    *(int *)(thisObject + 300) = *(int *)(thisObject + 300) + 3;
                    thisObject[0x138] = 1;
                    uVar11 = func_0x7ffe99a4d6a0();
                    *(undefined4 *)(thisObject + 0x20) = uVar11;
                    iVar4 = GemCartBufferBase_GetValue(puVar10,(undefined *)0x4,(undefined *)0x0);
                    *(int *)(thisObject + 0x13c) = iVar4;
                  }
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
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

