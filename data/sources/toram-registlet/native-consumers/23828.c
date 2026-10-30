
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void FlashStubAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  code *pcVar1;
  float fVar2;
  undefined4 uVar3;
  int iVar4;
  longlong lVar5;
  longlong *plVar6;
  undefined *puVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  float fVar10;
  undefined8 uStackX_10;
  
  if (DAT_7ffe9caded2a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9caded2a = '\x01';
  }
  uStackX_10 = 0;
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(_DAT_7ffe9c922720 + 0x130) <= *(byte *)(*(longlong *)actarAction + 0x130)) &&
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) == _DAT_7ffe9c922720)) {
      lVar5 = (**(code **)(*(longlong *)actarAction + 0x298))
                        (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
      if (lVar5 != 0) {
        uVar3 = FUN_7ffe9a4a1cc0(lVar5,0);
        *(undefined4 *)(thisObject + 0x30) = uVar3;
        uVar3 = FUN_7ffe9a4adfc0(actarAction,&uStackX_10,0);
        *(undefined4 *)(thisObject + 0xfc) = uVar3;
        uVar3 = FUN_7ffe9a4adf80(uStackX_10,0);
        *(undefined4 *)(thisObject + 0x20) = uVar3;
        *(float *)(thisObject + 0x120) =
             (float)(byte)thisObject[0x14] * _DAT_7ffe9c049ce0 + _DAT_7ffe9c049cfc;
        plVar6 = (longlong *)
                 (**(code **)(*(longlong *)actarAction + 0x298))
                           (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
        if (plVar6 != (longlong *)0x0) {
          puVar7 = (undefined *)
                   (**(code **)(*plVar6 + 0x218))(plVar6,*(undefined8 *)(*plVar6 + 0x220));
          if (puVar7 != (undefined *)0x0) {
            puVar7 = GemCartBufferManager_GetGemCartBuffer(puVar7,0x6f,(undefined *)0x0);
            if (puVar7 != (undefined *)0x0) {
              fVar10 = *(float *)(thisObject + 0x120);
              iVar4 = GemCartBufferBase_GetValue(puVar7,(undefined *)0x4,(undefined *)0x0);
              *(float *)(thisObject + 0x120) = (float)iVar4 + fVar10;
            }
            fVar10 = _DAT_7ffe9c049b4c;
            *(float *)(thisObject + 0x120) = *(float *)(thisObject + 0x120) / _DAT_7ffe9c049cfc;
            *(float *)(thisObject + 0x124) = (float)(((byte)thisObject[0x14] + 10) * 5);
            if (*(int *)(thisObject + 0xfc) == 10) {
              fVar10 = _DAT_7ffe9c049cc8;
            }
            uVar8 = (**(code **)(*(longlong *)actarAction + 0x298))
                              (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
            uVar3 = FUN_7ffe9a4aabb0(uVar8,0);
            *(undefined4 *)(thisObject + 0x78) = uVar3;
            if (thisObject[0x118] != '\0') {
              *(undefined4 *)(thisObject + 0x78) = 100;
            }
            iVar4 = func_0x7ffe9a8fec10(thisObject,0);
            fVar2 = _DAT_7ffe9c049cf4;
            if (_DAT_7ffe9c049cf4 <= (float)iVar4 * fVar10) {
              fVar2 = (float)iVar4 * fVar10;
            }
            *(int *)(thisObject + 0x78) = (int)fVar2;
            FUN_7ffe9a4aacd0(thisObject,actarAction,0);
            iVar4 = *(int *)(thisObject + 0xfc);
            uVar8 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
            uVar9 = 0x33453;
            if (iVar4 != 10) {
              uVar9 = 0x10e439;
            }
            FUN_7ffe9a9002e0(uVar8,uVar9,0);
            *(undefined8 *)(thisObject + 0x58) = uVar8;
            il2cpp_write_barrier_0();
            return;
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

