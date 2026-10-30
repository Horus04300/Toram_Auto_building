
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void HealAction_OnInitialize(undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  float fVar3;
  byte bVar4;
  char cVar5;
  undefined1 uVar6;
  int iVar7;
  int iVar8;
  undefined8 uVar9;
  longlong *plVar10;
  longlong lVar11;
  undefined *puVar12;
  longlong lVar13;
  longlong *plVar14;
  undefined4 uVar15;
  undefined8 uStackX_8;
  longlong *plStackX_10;
  
  if (DAT_7ffe9cadf7c8 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c961838);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c946798);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c954a30);
    FUN_7ffe9996d590(&DAT_7ffe9c9562d8);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    FUN_7ffe9996d590(&DAT_7ffe9c94c0a0);
    DAT_7ffe9cadf7c8 = '\x01';
  }
  plStackX_10 = (longlong *)0x0;
  uStackX_8 = 0;
  if (actarAction == (undefined *)0x0) {
    uVar15 = func_0x7ffe99a4d6a0();
    *(undefined4 *)(thisObject + 0x20) = uVar15;
  }
  else {
    bVar4 = *(byte *)(_DAT_7ffe9c922720 + 0x130);
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < bVar4) ||
       (*(longlong *)(*(longlong *)(*(longlong *)actarAction + 200) + -8 + (ulonglong)bVar4 * 8) !=
        _DAT_7ffe9c922720)) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    plVar14 = (longlong *)0x0;
    if (bVar2) {
      plVar14 = (longlong *)actarAction;
    }
    uVar15 = func_0x7ffe99a4d6a0((ulonglong)bVar4,0);
    *(undefined4 *)(thisObject + 0x20) = uVar15;
    if (plVar14 != (longlong *)0x0) {
      uVar9 = (**(code **)(*plVar14 + 0x298))(plVar14,*(undefined8 *)(*plVar14 + 0x2a0));
      uVar15 = FUN_7ffe9a4aabb0(uVar9,0);
      *(undefined4 *)(thisObject + 0x78) = uVar15;
      plVar10 = (longlong *)
                (**(code **)(*plVar14 + 0x298))(plVar14,*(undefined8 *)(*plVar14 + 0x2a0));
      if (plVar10 != (longlong *)0x0) {
        (**(code **)(*plVar10 + 0x1a8))(plVar10,*(undefined8 *)(*plVar10 + 0x1b0));
        if (*(int *)(_DAT_7ffe9c94c0a0 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        fVar3 = _DAT_7ffe9c049b18;
        uVar15 = FUN_7ffe9a811090();
        bVar4 = thisObject[0x14];
        *(undefined4 *)(thisObject + 0x24) = uVar15;
        *(uint *)(thisObject + 0x120) = (uint)bVar4 * 300;
        plVar10 = (longlong *)
                  (**(code **)(*plVar14 + 0x298))(plVar14,*(undefined8 *)(*plVar14 + 0x2a0));
        if (plVar10 != (longlong *)0x0) {
          lVar11 = (**(code **)(*plVar10 + 0x198))(plVar10,*(undefined8 *)(*plVar10 + 0x1a0));
          if (lVar11 != 0) {
            iVar7 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar11);
            *(uint *)(thisObject + 0x120) =
                 (int)(((byte)thisObject[0x14] + 10) * iVar7) / 100 + (uint)bVar4 * 300;
            plVar10 = (longlong *)
                      (**(code **)(*plVar14 + 0x298))(plVar14,*(undefined8 *)(*plVar14 + 0x2a0));
            if (plVar10 != (longlong *)0x0) {
              puVar12 = (undefined *)
                        (**(code **)(*plVar10 + 0x218))(plVar10,*(undefined8 *)(*plVar10 + 0x220));
              if (puVar12 != (undefined *)0x0) {
                bVar4 = GemCartBufferManager_ContainsBuffer(puVar12,0x402,(undefined *)0x0);
                if (bVar4 != 0) {
                  iVar7 = *(int *)(thisObject + 0x120) / 2;
                  plVar10 = (longlong *)
                            (**(code **)(*plVar14 + 0x298))
                                      (plVar14,*(undefined8 *)(*plVar14 + 0x2a0));
                  if (plVar10 == (longlong *)0x0) goto LAB_7ffe9a81da55;
                  puVar12 = (undefined *)
                            (**(code **)(*plVar10 + 0x218))
                                      (plVar10,*(undefined8 *)(*plVar10 + 0x220));
                  if (puVar12 == (undefined *)0x0) goto LAB_7ffe9a81da55;
                  iVar8 = GemCartBufferManager_GetBufferLevel(puVar12,0x47,(undefined *)0x0);
                  if (0 < iVar8) {
                    iVar7 = (int)((fVar3 - (float)(iVar8 * 10) * _DAT_7ffe9c049b34) * (float)iVar7);
                  }
                  *(int *)(thisObject + 0x120) = *(int *)(thisObject + 0x120) - iVar7;
                }
                uVar9 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
                FUN_7ffe9a9002e0(uVar9,0x1d0d8,0);
                *(undefined8 *)(thisObject + 0x58) = uVar9;
                il2cpp_write_barrier_0();
                lVar11 = *(longlong *)(thisObject + 0x58);
                uVar9 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
                FUN_7ffe9a9002e0(uVar9,0x9ebcb8,0);
                if (lVar11 != 0) {
                  *(undefined8 *)(lVar11 + 0x20) = uVar9;
                  il2cpp_write_barrier_0();
                  plVar10 = (longlong *)
                            (**(code **)(*plVar14 + 0x298))
                                      (plVar14,*(undefined8 *)(*plVar14 + 0x2a0));
                  if (plVar10 != (longlong *)0x0) {
                    puVar12 = (undefined *)
                              (**(code **)(*plVar10 + 0x218))
                                        (plVar10,*(undefined8 *)(*plVar10 + 0x220));
                    if (puVar12 != (undefined *)0x0) {
                      bVar4 = GemCartBufferManager_ContainsBuffer(puVar12,0x3ef,(undefined *)0x0);
                      uVar15 = 300;
                      if (bVar4 != 0) {
                        uVar15 = 200;
                      }
                      *(undefined4 *)(thisObject + 0x124) = uVar15;
                      plVar10 = (longlong *)
                                (**(code **)(*plVar14 + 0x298))
                                          (plVar14,*(undefined8 *)(*plVar14 + 0x2a0));
                      if (plVar10 != (longlong *)0x0) {
                        lVar11 = (**(code **)(*plVar10 + 0x1c8))
                                           (plVar10,*(undefined8 *)(*plVar10 + 0x1d0));
                        if (lVar11 != 0) {
                          cVar5 = FUN_7ffe9a7cbb30(lVar11,0x17,&plStackX_10);
                          if (cVar5 == '\0') goto LAB_7ffe9a81da13;
                          if (plStackX_10 != (longlong *)0x0) {
                            iVar7 = (**(code **)(*plStackX_10 + 0x1f8))
                                              (plStackX_10,0x14,
                                               *(undefined8 *)(*plStackX_10 + 0x200));
                            lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c9562d8);
                            if (lVar11 != 0) {
                              lVar11 = *(longlong *)(lVar11 + 0x28);
                              lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c9562d8);
                              if (lVar13 != 0) {
                                iVar8 = *(int *)(lVar13 + 0x50);
                                if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                                  func_0x7ffe9996d830();
                                }
                                cVar5 = FUN_7ffe9bda2160(lVar11,0,0);
                                if ((cVar5 != '\0') &&
                                   ((((iVar8 - 3U & 0xfffffffc) == 0 && (iVar8 != 5)) ||
                                    (iVar8 == 7)))) {
                                  if (lVar11 == 0) goto LAB_7ffe9a81da55;
                                  lVar11 = FUN_7ffe9ab9c3a0(lVar11,_DAT_7ffe9c961838);
                                  if (lVar11 != 0) {
                                    lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
                                    uStackX_8 = FUN_7ffe99742ec0(1,_DAT_7ffe9c946798,lVar11);
                                    uVar15 = func_0x7ffe9a331500(&uStackX_8,0);
                                    uStackX_8 = FUN_7ffe99742ec0(1,_DAT_7ffe9c946798,lVar11);
                                    uVar6 = func_0x7ffe9bb9e860(&uStackX_8,0);
                                    if (lVar13 == 0) goto LAB_7ffe9a81da55;
                                    cVar5 = FUN_7ffe9a59b980(lVar13,uVar15,uVar6,0);
                                    if ((cVar5 != '\0') &&
                                       (*(int *)(thisObject + 0x124) / 100 <= iVar7)) {
                                      *(undefined4 *)(thisObject + 0x24) = 0;
                                      *(undefined4 *)(thisObject + 0x104) = 1;
                                    }
                                  }
                                }
LAB_7ffe9a81da13:
                                FUN_7ffe9a4aacd0(thisObject,plVar14,0);
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
LAB_7ffe9a81da55:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

