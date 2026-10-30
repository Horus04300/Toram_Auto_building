
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void DragoonSwordAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  code *pcVar1;
  undefined4 uVar2;
  int iVar3;
  longlong lVar4;
  longlong *plVar5;
  undefined *puVar6;
  undefined8 uVar7;
  float fVar8;
  undefined8 uStackX_10;
  
  if (DAT_7ffe9cadec62 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadec62 = '\x01';
  }
  uStackX_10 = 0;
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(_DAT_7ffe9c922720 + 0x130) <= *(byte *)(*(longlong *)actarAction + 0x130)) &&
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) == _DAT_7ffe9c922720)) {
      lVar4 = (**(code **)(*(longlong *)actarAction + 0x298))
                        (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
      if (lVar4 != 0) {
        uVar2 = FUN_7ffe9a4a1cc0(lVar4,0);
        *(undefined4 *)(thisObject + 0x30) = uVar2;
        uVar2 = FUN_7ffe9a4adfc0(actarAction,&uStackX_10,0);
        *(undefined4 *)(thisObject + 0xfc) = uVar2;
        uVar2 = FUN_7ffe9a4adf80(uStackX_10,0);
        *(undefined4 *)(thisObject + 0x20) = uVar2;
        uVar2 = func_0x7ffe99a4d6a0();
        *(undefined4 *)(thisObject + 300) = uVar2;
        *(float *)(thisObject + 0x120) =
             (float)(((uint)(byte)thisObject[0x14] + (uint)(byte)thisObject[0x14] * 4) * 4) +
             _DAT_7ffe9c049d00;
        plVar5 = (longlong *)
                 (**(code **)(*(longlong *)actarAction + 0x298))
                           (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
        if (plVar5 != (longlong *)0x0) {
          puVar6 = (undefined *)
                   (**(code **)(*plVar5 + 0x218))(plVar5,*(undefined8 *)(*plVar5 + 0x220));
          if (puVar6 != (undefined *)0x0) {
            puVar6 = GemCartBufferManager_GetGemCartBuffer(puVar6,0xd3,(undefined *)0x0);
            if (puVar6 != (undefined *)0x0) {
              fVar8 = *(float *)(thisObject + 0x120);
              thisObject[0x150] = 1;
              iVar3 = GemCartBufferBase_GetValue(puVar6,(undefined *)0x4,(undefined *)0x0);
              *(float *)(thisObject + 0x120) = (float)iVar3 + fVar8;
            }
            fVar8 = *(float *)(thisObject + 0x120) / _DAT_7ffe9c049cfc;
            *(uint *)(thisObject + 0x124) = ((byte)thisObject[0x14] + 5) * 0x14;
            *(float *)(thisObject + 0x120) = fVar8;
            uVar2 = func_0x7ffe99a4d6a0();
            *(undefined4 *)(thisObject + 0x128) = uVar2;
            uVar7 = (**(code **)(*(longlong *)actarAction + 0x298))
                              (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
            uVar2 = FUN_7ffe9a4aabb0(uVar7,0);
            *(undefined4 *)(thisObject + 0x78) = uVar2;
            FUN_7ffe9a4aacd0(thisObject,actarAction,0);
            uVar7 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
            FUN_7ffe9a9002e0(uVar7,0xf7121,0);
            *(undefined8 *)(thisObject + 0x58) = uVar7;
            il2cpp_write_barrier_0();
            if ((*(longlong *)(thisObject + 0x58) != 0) &&
               (lVar4 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar4 != 0)) {
              FUN_7ffe9ad10e00(lVar4,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
              *(uint *)(thisObject + 0x108) = *(uint *)(thisObject + 0x108) | 2;
              return;
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

