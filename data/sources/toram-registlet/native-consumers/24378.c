
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void AssaultAttackAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  byte bVar1;
  longlong lVar2;
  code *pcVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  longlong lVar7;
  longlong *plVar8;
  undefined *puVar9;
  undefined8 uVar10;
  float fVar11;
  
  if (DAT_7ffe9cadedfa == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadedfa = '\x01';
  }
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(_DAT_7ffe9c922720 + 0x130) <= *(byte *)(*(longlong *)actarAction + 0x130)) &&
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) == _DAT_7ffe9c922720)) {
      lVar7 = (**(code **)(*(longlong *)actarAction + 0x298))
                        (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
      if (lVar7 != 0) {
        uVar4 = FUN_7ffe9a4a1cc0(lVar7,0);
        *(undefined4 *)(thisObject + 0x30) = uVar4;
        uVar4 = FUN_7ffe9a4ade20(actarAction,0);
        *(undefined4 *)(thisObject + 0xfc) = uVar4;
        uVar4 = func_0x7ffe99a4d6a0();
        bVar1 = thisObject[0x14];
        *(undefined4 *)(thisObject + 0x20) = uVar4;
        iVar6 = ((uint)bVar1 + (uint)bVar1 * 4) * 2;
        *(int *)(thisObject + 0x128) = iVar6;
        iVar5 = (uint)bVar1 + (uint)bVar1 * 4;
        *(int *)(thisObject + 0x124) = iVar5;
        *(int *)(thisObject + 300) = iVar6;
        *(float *)(thisObject + 0x120) = (float)(iVar6 + 0x19);
        if (*(int *)(thisObject + 0xfc) == 0x11) {
          fVar11 = (float)(iVar6 + 0x19) + _DAT_7ffe9c049f04;
          *(int *)(thisObject + 0x124) = iVar5 + 0x32;
          *(int *)(thisObject + 300) = iVar6 + 0x32;
          *(float *)(thisObject + 0x120) = fVar11;
        }
        plVar8 = (longlong *)
                 (**(code **)(*(longlong *)actarAction + 0x298))
                           (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
        if (plVar8 != (longlong *)0x0) {
          puVar9 = (undefined *)
                   (**(code **)(*plVar8 + 0x218))(plVar8,*(undefined8 *)(*plVar8 + 0x220));
          if (puVar9 != (undefined *)0x0) {
            puVar9 = GemCartBufferManager_GetGemCartBuffer(puVar9,0x3ea,(undefined *)0x0);
            if (puVar9 != (undefined *)0x0) {
              fVar11 = *(float *)(thisObject + 0x120);
              iVar6 = GemCartBufferBase_GetValue(puVar9,(undefined *)0x4,(undefined *)0x0);
              *(undefined8 *)(thisObject + 0x128) = 0;
              *(float *)(thisObject + 0x120) = (float)iVar6 + fVar11;
            }
            uVar10 = (**(code **)(*(longlong *)actarAction + 0x298))
                               (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
            uVar4 = FUN_7ffe9a4aabb0(uVar10,0);
            *(undefined4 *)(thisObject + 0x78) = uVar4;
            FUN_7ffe9a4aacd0(thisObject,actarAction,0);
            uVar10 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
            FUN_7ffe9a9002e0(uVar10,0x1e462,0);
            *(undefined8 *)(thisObject + 0x58) = uVar10;
            il2cpp_write_barrier_0();
            if ((*(longlong *)(thisObject + 0x58) != 0) &&
               (lVar7 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar7 != 0)) {
              lVar2 = *(longlong *)(*(longlong *)(_DAT_7ffe9c949490 + 0x20) + 0xc0);
              FUN_7ffe9ad1fce0(lVar7,7,*(undefined4 *)(thisObject + 0x30),
                               CONCAT71((int7)((ulonglong)lVar2 >> 8),2),
                               *(undefined8 *)(lVar2 + 0x118));
              return;
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

