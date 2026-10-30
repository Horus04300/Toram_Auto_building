
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void DiveImpactAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  byte bVar1;
  byte bVar2;
  code *pcVar3;
  undefined4 uVar4;
  int iVar5;
  longlong lVar6;
  longlong *plVar7;
  undefined8 uVar8;
  undefined *puVar9;
  float fVar10;
  undefined8 uStackX_10;
  
  if (DAT_7ffe9caded02 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9caded02 = '\x01';
  }
  uStackX_10 = 0;
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(_DAT_7ffe9c922720 + 0x130) <= *(byte *)(*(longlong *)actarAction + 0x130)) &&
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) == _DAT_7ffe9c922720)) {
      lVar6 = (**(code **)(*(longlong *)actarAction + 0x298))
                        (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
      if (lVar6 != 0) {
        uVar4 = FUN_7ffe9a4a1cc0(lVar6,0);
        *(undefined4 *)(thisObject + 0x30) = uVar4;
        uVar4 = FUN_7ffe9a4adfc0(actarAction,&uStackX_10,0);
        *(undefined4 *)(thisObject + 0xfc) = uVar4;
        uVar4 = FUN_7ffe9a4adf80(uStackX_10,0);
        bVar1 = thisObject[0x14];
        *(undefined4 *)(thisObject + 0x20) = uVar4;
        plVar7 = (longlong *)
                 (**(code **)(*(longlong *)actarAction + 0x298))
                           (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
        if (plVar7 != (longlong *)0x0) {
          lVar6 = (**(code **)(*plVar7 + 0x198))(plVar7,*(undefined8 *)(*plVar7 + 0x1a0));
          if (lVar6 != 0) {
            iVar5 = FUN_7ffe99742ec0(1,_DAT_7ffe9c940d40,lVar6);
            fVar10 = _DAT_7ffe9c049cfc;
            bVar2 = thisObject[0x14];
            *(float *)(thisObject + 0x120) =
                 ((float)iVar5 / _DAT_7ffe9c049dc4 + (float)((bVar1 + 10) * 0x14)) /
                 _DAT_7ffe9c049cfc;
            plVar7 = (longlong *)
                     (**(code **)(*(longlong *)actarAction + 0x298))
                               (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
            if (plVar7 != (longlong *)0x0) {
              lVar6 = (**(code **)(*plVar7 + 0x198))(plVar7,*(undefined8 *)(*plVar7 + 0x1a0));
              if (lVar6 != 0) {
                iVar5 = FUN_7ffe99742ec0(2,_DAT_7ffe9c940d40,lVar6);
                bVar1 = thisObject[0x14];
                *(float *)(thisObject + 0x124) = (float)(int)(iVar5 + (bVar2 + 5) * 0x28) / fVar10;
                *(float *)(thisObject + 0x128) = (float)((bVar1 + 10) * 0x14);
                if (DAT_7ffe9cad9c12 == '\0') {
                  FUN_7ffe9996d590(&DAT_7ffe9c968830);
                  DAT_7ffe9cad9c12 = '\x01';
                }
                fVar10 = (float)bVar1 * _DAT_7ffe9c049c7c + _DAT_7ffe9c049dc4;
                if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
                  func_0x7ffe9996d830();
                }
                func_0x7ffe999978b4((double)fVar10);
                uVar4 = func_0x7ffe99a4d6a0();
                bVar1 = thisObject[0x14];
                *(undefined4 *)(thisObject + 0x134) = uVar4;
                if (DAT_7ffe9cad9c12 == '\0') {
                  FUN_7ffe9996d590(&DAT_7ffe9c968830);
                  DAT_7ffe9cad9c12 = '\x01';
                }
                fVar10 = (float)bVar1 * _DAT_7ffe9c049c7c + _DAT_7ffe9c04b590;
                if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
                  func_0x7ffe9996d830();
                }
                func_0x7ffe999978b4((double)fVar10);
                uVar4 = func_0x7ffe99a4d6a0();
                *(undefined4 *)(thisObject + 0x138) = uVar4;
                *(uint *)(thisObject + 0x148) =
                     ((uint)(byte)thisObject[0x14] + (uint)(byte)thisObject[0x14] * 4) * 2;
                uVar8 = (**(code **)(*(longlong *)actarAction + 0x298))
                                  (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
                uVar4 = FUN_7ffe9a4aabb0(uVar8,0);
                *(undefined4 *)(thisObject + 0x78) = uVar4;
                FUN_7ffe9a4aacd0(thisObject,actarAction,0);
                thisObject[0x130] = 1;
                plVar7 = (longlong *)
                         (**(code **)(*(longlong *)actarAction + 0x298))
                                   (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
                if (plVar7 != (longlong *)0x0) {
                  puVar9 = (undefined *)
                           (**(code **)(*plVar7 + 0x218))(plVar7,*(undefined8 *)(*plVar7 + 0x220));
                  if (puVar9 != (undefined *)0x0) {
                    puVar9 = GemCartBufferManager_GetGemCartBuffer(puVar9,0x132,(undefined *)0x0);
                    *(undefined **)(thisObject + 0x160) = puVar9;
                    il2cpp_write_barrier_0();
                    thisObject[0x17c] = *(longlong *)(thisObject + 0x160) != 0;
                    *(uint *)(thisObject + 0x104) = (uint)(*(longlong *)(thisObject + 0x160) != 0);
                    return;
                  }
                }
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

