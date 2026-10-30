
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ShellBreakAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  byte bVar1;
  code *pcVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  longlong lVar7;
  longlong *plVar8;
  undefined *puVar9;
  undefined8 uVar10;
  float fVar11;
  double dVar12;
  undefined8 uStackX_10;
  longlong lStackX_20;
  
  if (DAT_7ffe9cadef68 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadef68 = '\x01';
  }
  uStackX_10 = 0;
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
        *(undefined4 *)(thisObject + 0xfc) = 0;
        cVar3 = FUN_7ffe9a4ad860(actarAction,0x10,&uStackX_10);
        if (cVar3 != '\0') {
          *(undefined4 *)(thisObject + 0xfc) = 0x10;
        }
        uVar4 = FUN_7ffe9a4adf80(uStackX_10,0);
        bVar1 = thisObject[0x14];
        *(undefined4 *)(thisObject + 0x20) = uVar4;
        fVar11 = (float)((bVar1 + 0x14) * 5);
        iVar5 = (bVar1 + 5) * 10;
        *(int *)(thisObject + 0x128) = iVar5;
        *(float *)(thisObject + 0x124) = fVar11;
        if (*(int *)(thisObject + 0xfc) == 0x10) {
          fVar11 = fVar11 + _DAT_7ffe9c049cf4;
          *(int *)(thisObject + 0x128) = iVar5 + 0x96;
          *(float *)(thisObject + 0x124) = fVar11;
        }
        fVar11 = (float)bVar1 * _DAT_7ffe9c049b4c;
        if (DAT_7ffe9cad9c12 == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c968830);
          DAT_7ffe9cad9c12 = '\x01';
        }
        if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        dVar12 = (double)func_0x7ffe999978b4((double)((float)bVar1 + fVar11));
        *(int *)(thisObject + 300) = (int)dVar12 + 10;
        plVar8 = (longlong *)
                 (**(code **)(*(longlong *)actarAction + 0x298))
                           (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
        if (plVar8 != (longlong *)0x0) {
          lVar7 = (**(code **)(*plVar8 + 0x1f8))(plVar8,*(undefined8 *)(*plVar8 + 0x200));
          if ((lVar7 != 0) && (*(longlong *)(lVar7 + 0x18) != 0)) {
            iVar5 = func_0x7ffe99c1ed70(*(longlong *)(lVar7 + 0x18),0);
            if (iVar5 == 0x10) {
              *(int *)(thisObject + 300) = *(int *)(thisObject + 300) + 0x19;
            }
            plVar8 = (longlong *)
                     (**(code **)(*(longlong *)actarAction + 0x298))
                               (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
            if (plVar8 != (longlong *)0x0) {
              puVar9 = (undefined *)
                       (**(code **)(*plVar8 + 0x218))(plVar8,*(undefined8 *)(*plVar8 + 0x220));
              if (puVar9 != (undefined *)0x0) {
                puVar9 = GemCartBufferManager_GetGemCartBuffer(puVar9,0xd0,(undefined *)0x0);
                if (puVar9 != (undefined *)0x0) {
                  iVar5 = *(int *)(thisObject + 300);
                  iVar6 = GemCartBufferBase_GetValue(puVar9,(undefined *)0x2,(undefined *)0x0);
                  *(int *)(thisObject + 300) = iVar6 + iVar5;
                }
                lStackX_20 = 0;
                plVar8 = (longlong *)
                         (**(code **)(*(longlong *)actarAction + 0x298))
                                   (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
                if (plVar8 != (longlong *)0x0) {
                  lVar7 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0));
                  if (lVar7 != 0) {
                    cVar3 = FUN_7ffe9a7cbb30(lVar7,0x487,&lStackX_20,0);
                    if (cVar3 != '\0') {
                      iVar5 = *(int *)(thisObject + 300);
                      if (lStackX_20 == 0) goto LAB_7ffe9a6ee990;
                      iVar6 = func_0x7ffe9a7a2140(lStackX_20,0x32);
                      *(int *)(thisObject + 300) = iVar6 + iVar5;
                    }
                    *(uint *)(thisObject + 0x130) =
                         (uint)(byte)thisObject[0x14] + (uint)(byte)thisObject[0x14] * 4;
                    uVar10 = (**(code **)(*(longlong *)actarAction + 0x298))
                                       (actarAction,
                                        *(undefined8 *)(*(longlong *)actarAction + 0x2a0));
                    uVar4 = FUN_7ffe9a4aabb0(uVar10,0);
                    *(undefined4 *)(thisObject + 0x78) = uVar4;
                    FUN_7ffe9a4aacd0(thisObject,actarAction,0);
                    uVar10 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
                    FUN_7ffe9a9002e0(uVar10,0xc505a,0);
                    *(undefined8 *)(thisObject + 0x58) = uVar10;
                    il2cpp_write_barrier_0();
                    if ((*(longlong *)(thisObject + 0x58) != 0) &&
                       (lVar7 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar7 != 0))
                    {
                      FUN_7ffe9ad10e00(lVar7,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490)
                      ;
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
  }
LAB_7ffe9a6ee990:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

