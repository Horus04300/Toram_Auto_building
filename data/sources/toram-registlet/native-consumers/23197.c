
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void AirSlicerAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  undefined8 uVar6;
  longlong *plVar7;
  longlong lVar8;
  undefined *puVar9;
  longlong *plVar10;
  int iVar11;
  int iVar12;
  undefined4 uVar13;
  float fVar14;
  float fVar15;
  
  if (DAT_7ffe9cadec46 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadec46 = '\x01';
  }
  if (actarAction == (undefined *)0x0) {
    plVar10 = (longlong *)0x0;
  }
  else {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    plVar10 = (longlong *)0x0;
    if (bVar3) {
      plVar10 = (longlong *)actarAction;
    }
  }
  uVar13 = func_0x7ffe99a4d6a0();
  *(undefined4 *)(thisObject + 0x20) = uVar13;
  uVar13 = FUN_7ffe9a4ae0a0(plVar10,0);
  *(undefined4 *)(thisObject + 0xfc) = uVar13;
  *(undefined4 *)(thisObject + 0x30) = 3;
  if (plVar10 != (longlong *)0x0) {
    uVar6 = (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
    uVar13 = FUN_7ffe9a4aabb0(uVar6,0);
    *(undefined4 *)(thisObject + 0x78) = uVar13;
    FUN_7ffe9a4aacd0(thisObject,plVar10,0);
    plVar7 = (longlong *)(**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
    if (plVar7 != (longlong *)0x0) {
      lVar8 = (**(code **)(*plVar7 + 0x1b8))(plVar7,*(undefined8 *)(*plVar7 + 0x1c0));
      if (lVar8 != 0) {
        iVar4 = FUN_7ffe9a7fd580(lVar8,0x286,1,0);
        iVar11 = iVar4 * 2 + 0x1e;
        fVar14 = (float)iVar4 * _DAT_7ffe9c04ab84;
        iVar12 = 0x7d - (int)fVar14;
        plVar7 = (longlong *)
                 (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
        if (plVar7 != (longlong *)0x0) {
          puVar9 = (undefined *)
                   (**(code **)(*plVar7 + 0x218))(plVar7,*(undefined8 *)(*plVar7 + 0x220));
          if (puVar9 != (undefined *)0x0) {
            puVar9 = GemCartBufferManager_GetGemCartBuffer(puVar9,0xd2,(undefined *)0x0);
            if (puVar9 != (undefined *)0x0) {
              iVar5 = GemCartBufferBase_GetValue(puVar9,(undefined *)0x4,(undefined *)0x0);
              iVar12 = iVar12 + iVar5;
              iVar5 = GemCartBufferBase_GetValue(puVar9,(undefined *)0x4,(undefined *)0x0);
              iVar11 = iVar11 + iVar5;
            }
            fVar15 = (float)(iVar12 + iVar11 * 3);
            *(float *)(thisObject + 0x128) = fVar15;
            plVar7 = (longlong *)
                     (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
            if (plVar7 != (longlong *)0x0) {
              lVar8 = (**(code **)(*plVar7 + 0x188))(plVar7,*(undefined8 *)(*plVar7 + 400));
              if (lVar8 != 0) {
                iVar11 = *(int *)(lVar8 + 0x24);
                *(int *)(thisObject + 300) = (iVar4 + 10) * 5;
                *(int *)(thisObject + 0x130) = 0xf - (int)fVar14;
                *(float *)(thisObject + 0x128) =
                     (float)(int)((iVar11 / 10) * (uint)(byte)thisObject[0x14]) + fVar15;
                plVar7 = (longlong *)
                         (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
                if (plVar7 != (longlong *)0x0) {
                  lVar8 = (**(code **)(*plVar7 + 0x1b8))(plVar7,*(undefined8 *)(*plVar7 + 0x1c0));
                  if (lVar8 != 0) {
                    iVar4 = FUN_7ffe9a7fd580(lVar8,0x282,1,0);
                    *(float *)(thisObject + 0x134) = (float)(((byte)thisObject[0x14] + 5) * 100);
                    plVar10 = (longlong *)
                              (**(code **)(*plVar10 + 0x298))
                                        (plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
                    if (plVar10 != (longlong *)0x0) {
                      lVar8 = (**(code **)(*plVar10 + 0x188))
                                        (plVar10,*(undefined8 *)(*plVar10 + 400));
                      if (lVar8 != 0) {
                        iVar11 = *(int *)(lVar8 + 0x14);
                        *(uint *)(thisObject + 0x13c) =
                             ((uint)(byte)thisObject[0x14] + (uint)(byte)thisObject[0x14] * 4) * 4;
                        *(float *)(thisObject + 0x138) = (float)iVar11;
                        *(int *)(thisObject + 0x140) = ((iVar4 + 10) * 5) / 2;
                        uVar6 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
                        FUN_7ffe9a9002e0(uVar6,0xbfb5a30,0);
                        *(undefined8 *)(thisObject + 0x58) = uVar6;
                        il2cpp_write_barrier_0();
                        if ((*(longlong *)(thisObject + 0x58) != 0) &&
                           (lVar8 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50),
                           lVar8 != 0)) {
                          FUN_7ffe9ad10e00(lVar8,7,*(undefined4 *)(thisObject + 0x30),
                                           _DAT_7ffe9c949490);
                          lVar8 = *(longlong *)(thisObject + 0x58);
                          uVar6 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
                          FUN_7ffe9a9002e0(uVar6,0x9ecc5d,0);
                          if (lVar8 != 0) {
                            *(undefined8 *)(lVar8 + 0x20) = uVar6;
                            il2cpp_write_barrier_0();
                            if (((*(longlong *)(thisObject + 0x58) != 0) &&
                                (lVar8 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x20),
                                lVar8 != 0)) && (lVar8 = *(longlong *)(lVar8 + 0x50), lVar8 != 0)) {
                              lVar1 = *(longlong *)(*(longlong *)(_DAT_7ffe9c949490 + 0x20) + 0xc0);
                              FUN_7ffe9ad1fce0(lVar8,7,*(undefined4 *)(thisObject + 0x30),
                                               CONCAT71((int7)((ulonglong)lVar1 >> 8),2),
                                               *(undefined8 *)(lVar1 + 0x118));
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
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

