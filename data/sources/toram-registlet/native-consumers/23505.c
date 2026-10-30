
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void TwinBusterBladeAction_ActionStart
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  longlong lVar6;
  longlong lVar7;
  ulonglong *puVar8;
  undefined8 uVar9;
  undefined8 *puVar10;
  longlong *plVar11;
  undefined *puVar12;
  ulonglong uStack_38;
  float fStack_30;
  ulonglong uStack_28;
  float fStack_20;
  
  if (DAT_7ffe9cadecb0 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f3938);
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c95ff88);
    FUN_7ffe9996d590(&DAT_7ffe9c8f7490);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922658);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    FUN_7ffe9996d590(&DAT_7ffe9c94c0a0);
    FUN_7ffe9996d590(&DAT_7ffe9c928f70);
    FUN_7ffe9996d590(&DAT_7ffe9c934bf8);
    DAT_7ffe9cadecb0 = '\x01';
  }
  lVar6 = func_0x7ffe99940040(_DAT_7ffe9c934bf8);
  func_0x7ffe999c3920(lVar6,0);
  if (lVar6 != 0) {
    *(undefined **)(lVar6 + 0x10) = thisObject;
    il2cpp_write_barrier_0();
    FUN_7ffe9a4a6970(thisObject,actarAction,target,0);
    cVar3 = func_0x7ffe9a4aea60(thisObject,0);
    if (cVar3 != '\0') {
      return;
    }
    if ((target != (undefined *)0x0) && (lVar7 = FUN_7ffe9bd9b890(target,0), lVar7 != 0)) {
      puVar8 = (ulonglong *)FUN_7ffe9bdbf710(&uStack_28,lVar7,0);
      uStack_38 = *puVar8;
      fStack_30 = *(float *)(puVar8 + 1);
      if ((actarAction != (undefined *)0x0) && (lVar7 = FUN_7ffe9bd98a10(actarAction,0), lVar7 != 0)
         ) {
        puVar8 = (ulonglong *)FUN_7ffe9bdbf710(&uStack_28,lVar7,0);
        uStack_28 = *puVar8;
        fStack_20 = *(float *)(puVar8 + 1);
        fStack_30 = fStack_30 - fStack_20;
        uStack_38 = (ulonglong)(uint)((float)uStack_38 - (float)uStack_28);
        FUN_7ffe99a14ca0(&uStack_38,0);
        lVar7 = FUN_7ffe9bd98a10(actarAction,0);
        if (lVar7 != 0) {
          fStack_20 = fStack_30;
          uStack_28 = uStack_38;
          FUN_7ffe9bdbfb00(lVar7,&uStack_28,0);
          uVar9 = FUN_7ffe9bd9b890(target,0);
          *(undefined8 *)(thisObject + 0x160) = uVar9;
          il2cpp_write_barrier_0();
          lVar7 = FUN_7ffe9bd98a10(actarAction,0);
          if (lVar7 != 0) {
            puVar10 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_28,lVar7,0);
            uVar4 = *(undefined4 *)(puVar10 + 1);
            *(undefined8 *)(thisObject + 0x130) = *puVar10;
            *(undefined4 *)(thisObject + 0x138) = uVar4;
            lVar7 = FUN_7ffe9bd98a10(actarAction,0);
            if (lVar7 != 0) {
              puVar10 = (undefined8 *)FUN_7ffe9bdbf190(&uStack_28,lVar7,0);
              uVar4 = *(undefined4 *)(puVar10 + 1);
              *(undefined8 *)(thisObject + 0x13c) = *puVar10;
              *(undefined4 *)(thisObject + 0x144) = uVar4;
              uVar9 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
              FUN_7ffe9a9002e0(uVar9,0xbfb4e78,0);
              *(undefined8 *)(thisObject + 0x58) = uVar9;
              il2cpp_write_barrier_0();
              if ((*(longlong *)(thisObject + 0x58) != 0) &&
                 (lVar7 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar7 != 0)) {
                FUN_7ffe9ad10e00(lVar7,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
                if ((*(longlong *)(thisObject + 0x58) != 0) &&
                   (lVar7 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar7 != 0)) {
                  FUN_7ffe9ad10e00(lVar7,0x24,*(undefined4 *)(thisObject + 0x34),_DAT_7ffe9c949490);
                  lVar7 = *(longlong *)(thisObject + 0x58);
                  uVar9 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
                  FUN_7ffe9a9002e0(uVar9,0x11e37ba8,0);
                  if (lVar7 != 0) {
                    *(undefined8 *)(lVar7 + 0x20) = uVar9;
                    il2cpp_write_barrier_0();
                    if (((*(longlong *)(thisObject + 0x58) != 0) &&
                        (lVar7 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x20), lVar7 != 0)
                        ) && (lVar7 = *(longlong *)(lVar7 + 0x50), lVar7 != 0)) {
                      FUN_7ffe9ad10e00(lVar7,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490)
                      ;
                      if (((*(longlong *)(thisObject + 0x58) != 0) &&
                          (lVar7 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x20),
                          lVar7 != 0)) && (lVar7 = *(longlong *)(lVar7 + 0x50), lVar7 != 0)) {
                        FUN_7ffe9ad10e00(lVar7,0x24,*(undefined4 *)(thisObject + 0x34),
                                         _DAT_7ffe9c949490);
                        if ((*(longlong *)(thisObject + 0x58) != 0) &&
                           (lVar7 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x20),
                           lVar7 != 0)) {
                          lVar7 = *(longlong *)(lVar7 + 0x50);
                          uVar4 = func_0x7ffe9a8fec10(thisObject,0);
                          if (*(int *)(_DAT_7ffe9c94c0a0 + 0xe0) == 0) {
                            func_0x7ffe9996d830();
                          }
                          uVar4 = func_0x7ffe9a812780(uVar4,0);
                          if (lVar7 != 0) {
                            FUN_7ffe9ad10e00(lVar7,2,uVar4,_DAT_7ffe9c949490);
                            if ((*(byte *)(*(longlong *)actarAction + 0x130) <
                                 *(byte *)(_DAT_7ffe9c922658 + 0x130)) ||
                               (*(longlong *)
                                 (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
                                 (ulonglong)*(byte *)(_DAT_7ffe9c922658 + 0x130) * 8) !=
                                _DAT_7ffe9c922658)) {
                              bVar2 = false;
                            }
                            else {
                              bVar2 = true;
                            }
                            puVar12 = (undefined *)0x0;
                            if (bVar2) {
                              puVar12 = actarAction;
                            }
                            *(undefined **)(lVar6 + 0x18) = puVar12;
                            il2cpp_write_barrier_0();
                            uVar9 = *(undefined8 *)(lVar6 + 0x18);
                            if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                              func_0x7ffe9996d830();
                            }
                            cVar3 = FUN_7ffe9bda1fa0(uVar9,0,0);
                            if ((cVar3 != '\0') && (thisObject[0x118] != '\0')) {
                              if ((*(byte *)(*(longlong *)actarAction + 0x130) <
                                   *(byte *)(_DAT_7ffe9c8f7490 + 0x130)) ||
                                 (*(longlong *)
                                   (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
                                   (ulonglong)*(byte *)(_DAT_7ffe9c8f7490 + 0x130) * 8) !=
                                  _DAT_7ffe9c8f7490)) {
                                bVar2 = false;
                              }
                              else {
                                bVar2 = true;
                              }
                              puVar12 = (undefined *)0x0;
                              if (bVar2) {
                                puVar12 = actarAction;
                              }
                              *(undefined **)(lVar6 + 0x18) = puVar12;
                              il2cpp_write_barrier_0();
                            }
                            uVar9 = *(undefined8 *)(lVar6 + 0x18);
                            if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                              func_0x7ffe9996d830();
                            }
                            cVar3 = FUN_7ffe9bda2160(uVar9,0,0);
                            if (cVar3 == '\0') {
                              return;
                            }
                            plVar11 = *(longlong **)(lVar6 + 0x18);
                            if (((plVar11 != (longlong *)0x0) &&
                                (plVar11 = (longlong *)
                                           (**(code **)(*plVar11 + 0x298))
                                                     (plVar11,*(undefined8 *)(*plVar11 + 0x2a0)),
                                plVar11 != (longlong *)0x0)) &&
                               (lVar7 = (**(code **)(*plVar11 + 0x1b8))
                                                  (plVar11,*(undefined8 *)(*plVar11 + 0x1c0)),
                               lVar7 != 0)) {
                              iVar5 = FUN_7ffe9a7fd580(lVar7,0x2d,1);
                              *(int *)(lVar6 + 0x20) = iVar5;
                              if (0 < iVar5) {
                                plVar11 = *(longlong **)(lVar6 + 0x18);
                                if (((plVar11 == (longlong *)0x0) ||
                                    (plVar11 = (longlong *)
                                               (**(code **)(*plVar11 + 0x298))
                                                         (plVar11,*(undefined8 *)(*plVar11 + 0x2a0))
                                    , plVar11 == (longlong *)0x0)) ||
                                   (lVar7 = (**(code **)(*plVar11 + 0x1c8))
                                                      (plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
                                   lVar7 == 0)) goto LAB_7ffe9a687bdb;
                                cVar3 = FUN_7ffe9a7c6d00(lVar7,0x2d);
                                if (cVar3 == '\0') {
                                  uVar9 = func_0x7ffe99940040(_DAT_7ffe9c8f3938);
                                  FUN_7ffe9ac2ed50(uVar9,lVar6,_DAT_7ffe9c928f70,0);
                                  FUN_7ffe9a4b2010(thisObject,uVar9,0);
                                }
                              }
                              plVar11 = *(longlong **)(lVar6 + 0x18);
                              if (((plVar11 != (longlong *)0x0) &&
                                  (plVar11 = (longlong *)
                                             (**(code **)(*plVar11 + 0x298))
                                                       (plVar11,*(undefined8 *)(*plVar11 + 0x2a0)),
                                  plVar11 != (longlong *)0x0)) &&
                                 (puVar12 = (undefined *)
                                            (**(code **)(*plVar11 + 0x218))
                                                      (plVar11,*(undefined8 *)(*plVar11 + 0x220)),
                                 puVar12 != (undefined *)0x0)) {
                                puVar12 = GemCartBufferManager_GetGemCartBuffer
                                                    (puVar12,0x418,(undefined *)0x0);
                                if (puVar12 != (undefined *)0x0) {
                                  thisObject[0x168] = 1;
                                  iVar5 = GemCartBufferBase_GetValue
                                                    (puVar12,(undefined *)0x2,(undefined *)0x0);
                                  *(int *)(thisObject + 0x16c) = iVar5;
                                  lVar6 = FUN_7ffe9ab9c3a0(target,_DAT_7ffe9c95ff88);
                                  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                                    func_0x7ffe9996d830();
                                  }
                                  cVar3 = FUN_7ffe9bda2160(lVar6,0,0);
                                  if (cVar3 != '\0') {
                                    if ((lVar6 == 0) ||
                                       (lVar6 = FUN_7ffe9a317be0(lVar6,0), lVar6 == 0))
                                    goto LAB_7ffe9a687bdb;
                                    iVar5 = FUN_7ffe9a2ac2c0(lVar6,0);
                                    if (*(int *)(thisObject + 0x16c) < iVar5) {
                                      iVar5 = *(int *)(thisObject + 0x16c);
                                    }
                                    *(int *)(thisObject + 0x170) = iVar5;
                                  }
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
              }
            }
          }
        }
      }
    }
  }
LAB_7ffe9a687bdb:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

