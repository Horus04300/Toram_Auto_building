
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void FumaShurikenAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  float fVar1;
  byte bVar2;
  code *pcVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  longlong *plVar7;
  undefined *puVar8;
  longlong lVar9;
  undefined8 uVar10;
  
  if (DAT_7ffe9cadf149 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadf149 = '\x01';
  }
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(_DAT_7ffe9c922720 + 0x130) <= *(byte *)(*(longlong *)actarAction + 0x130)) &&
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) == _DAT_7ffe9c922720)) {
      plVar7 = (longlong *)
               (**(code **)(*(longlong *)actarAction + 0x298))
                         (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
      if (plVar7 != (longlong *)0x0) {
        puVar8 = (undefined *)
                 (**(code **)(*plVar7 + 0x218))(plVar7,*(undefined8 *)(*plVar7 + 0x220));
        if (puVar8 != (undefined *)0x0) {
          puVar8 = GemCartBufferManager_GetGemCartBuffer(puVar8,0x406,(undefined *)0x0);
          uVar4 = FUN_7ffe9a4ae0a0(actarAction,0);
          *(undefined4 *)(thisObject + 0xfc) = uVar4;
          uVar4 = func_0x7ffe99a4d6a0();
          *(undefined4 *)(thisObject + 0x20) = uVar4;
          lVar9 = (**(code **)(*(longlong *)actarAction + 0x298))
                            (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
          if (lVar9 != 0) {
            uVar4 = FUN_7ffe9a4a1cc0(lVar9,0);
            *(undefined4 *)(thisObject + 0x30) = uVar4;
            uVar10 = (**(code **)(*(longlong *)actarAction + 0x298))
                               (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
            uVar4 = FUN_7ffe9a4aabb0(uVar10,0);
            *(undefined4 *)(thisObject + 0x78) = uVar4;
            iVar5 = 500;
            if (puVar8 != (undefined *)0x0) {
              iVar5 = GemCartBufferBase_GetValue(puVar8,(undefined *)0x2,(undefined *)0x0);
              iVar5 = iVar5 + 500;
            }
            uVar4 = FUN_7ffe9a7b7a30(thisObject,iVar5,actarAction,0);
            *(undefined4 *)(thisObject + 0x128) = uVar4;
            FUN_7ffe9a4aacd0(thisObject,actarAction,0);
            bVar2 = thisObject[0x14];
            iVar5 = (bVar2 + 5) * 0x14;
            *(int *)(thisObject + 0x130) = iVar5;
            *(float *)(thisObject + 300) = (float)((uint)bVar2 * 3 + 0x14);
            *(uint *)(thisObject + 0x138) = (uint)(bVar2 == 10);
            uVar4 = func_0x7ffe99a4d6a0(iVar5,0);
            fVar1 = *(float *)(thisObject + 300);
            *(undefined4 *)(thisObject + 0x134) = uVar4;
            uVar10 = (**(code **)(*(longlong *)actarAction + 0x298))
                               (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
            iVar6 = FUN_7ffe9a7b7d10(thisObject,uVar10,0);
            iVar5 = *(int *)(thisObject + 0x138);
            *(float *)(thisObject + 300) = (float)(iVar6 / 10) + fVar1;
            uVar10 = (**(code **)(*(longlong *)actarAction + 0x298))
                               (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
            iVar6 = FUN_7ffe9a7b7c00(thisObject,uVar10,0);
            iVar5 = iVar6 / 10 + iVar5;
            *(int *)(thisObject + 0x138) = iVar5;
            if (*(int *)(thisObject + 0xfc) == 8) {
              *(int *)(thisObject + 0x138) = iVar5 + 1;
            }
            if (puVar8 != (undefined *)0x0) {
              *(int *)(thisObject + 0x138) = *(int *)(thisObject + 0x138) + 1;
            }
            return;
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

