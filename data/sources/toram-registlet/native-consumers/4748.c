
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void FamiliaActionManager_UpdateHighFamilia(undefined *thisObject,undefined *methodInfo)

{
  uint uVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  byte bVar5;
  undefined2 uVar6;
  int iVar7;
  uint uVar8;
  undefined4 uVar9;
  uint uVar10;
  undefined8 uVar11;
  longlong lVar12;
  longlong *plVar13;
  longlong lVar14;
  longlong lVar15;
  undefined8 *puVar16;
  undefined *puVar17;
  ushort uVar18;
  longlong *plVar19;
  float fVar20;
  float fVar21;
  undefined1 uStackX_a;
  longlong *plStackX_18;
  longlong lStackX_20;
  float fStack_70;
  undefined8 uStack_58;
  longlong **pplStack_50;
  
  if (DAT_7ffe9cada915 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c964000);
    FUN_7ffe9996d590(&DAT_7ffe9c9640c8);
    FUN_7ffe9996d590(&DAT_7ffe9c964260);
    FUN_7ffe9996d590(&DAT_7ffe9c963f30);
    FUN_7ffe9996d590(&DAT_7ffe9c9643f8);
    FUN_7ffe9996d590(&DAT_7ffe9c90cdd0);
    FUN_7ffe9996d590(&DAT_7ffe9c8fe9a8);
    FUN_7ffe9996d590(&DAT_7ffe9c903fc8);
    FUN_7ffe9996d590(&DAT_7ffe9c92a480);
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c955db0);
    FUN_7ffe9996d590(&DAT_7ffe9c95b888);
    FUN_7ffe9996d590(&DAT_7ffe9c93ac18);
    FUN_7ffe9996d590(&DAT_7ffe9c93c620);
    FUN_7ffe9996d590(0x7ffe9c967388);
    FUN_7ffe9996d590(0x7ffe9c967450);
    FUN_7ffe9996d590(&DAT_7ffe9c8f7560);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c9228b0);
    FUN_7ffe9996d590(&DAT_7ffe9c922a40);
    FUN_7ffe9996d590(&DAT_7ffe9c949d68);
    DAT_7ffe9cada915 = '\x01';
  }
  plVar19 = (longlong *)0x0;
  plStackX_18 = (longlong *)0x0;
  if (thisObject[0x1b8] == '\0') {
    return;
  }
  if ((*(longlong *)(thisObject + 0x188) != 0) &&
     (plVar13 = *(longlong **)(*(longlong *)(thisObject + 0x188) + 0x30), plVar13 != (longlong *)0x0
     )) {
    uVar11 = (**(code **)(*plVar13 + 0x188))(plVar13,*(undefined8 *)(*plVar13 + 400));
    cVar4 = FUN_7ffe9a8fecd0(uVar11,0,0);
    if (cVar4 != '\0') {
      return;
    }
    fVar21 = *(float *)(thisObject + 0x1b4);
    if (0.0 < fVar21) {
      fVar20 = (float)FUN_7ffe9bda7ce0(0);
      fVar21 = fVar21 - fVar20;
      *(float *)(thisObject + 0x1b4) = fVar21;
      if (fVar21 <= 0.0) {
        *(undefined4 *)(thisObject + 0x1b4) = 0;
      }
    }
    if ((*(longlong *)(thisObject + 0x170) != 0) &&
       (lVar12 = FUN_7ffe9a47fe30(*(longlong *)(thisObject + 0x170),0), lVar12 != 0)) {
      cVar4 = FUN_7ffe9a478bc0(lVar12,0);
      if (cVar4 == '\0') {
        return;
      }
      if (*(longlong *)(thisObject + 0x28) != 0) {
        cVar4 = func_0x7ffe99b21850(*(longlong *)(thisObject + 0x28),0);
        if (cVar4 != '\0') {
          return;
        }
        if (0.0 < *(float *)(thisObject + 0x1b4)) {
          return;
        }
        if ((((*(longlong *)(thisObject + 0x170) != 0) &&
             (lVar12 = FUN_7ffe9a47fe30(*(longlong *)(thisObject + 0x170),0), lVar12 != 0)) &&
            (*(longlong *)(lVar12 + 0x30) != 0)) &&
           (plVar13 = *(longlong **)(*(longlong *)(lVar12 + 0x30) + 0x30),
           plVar13 != (longlong *)0x0)) {
          plVar13 = (longlong *)
                    (**(code **)(*plVar13 + 0x188))(plVar13,*(undefined8 *)(*plVar13 + 400));
          cVar4 = FUN_7ffe9a8fecd0(plVar13,0,0);
          if (cVar4 != '\0') {
            if (plVar13 == (longlong *)0x0) goto LAB_7ffe99c0cb65;
            iVar7 = (**(code **)(*plVar13 + 0x188))(plVar13,*(undefined8 *)(*plVar13 + 400));
            if ((0x400 < iVar7) &&
               (iVar7 = (**(code **)(*plVar13 + 0x188))(plVar13,*(undefined8 *)(*plVar13 + 400)),
               iVar7 < 0x421)) {
              return;
            }
          }
          lVar14 = func_0x7ffe99940040(_DAT_7ffe9c90cdd0);
          FUN_7ffe9ad0cd00(lVar14,_DAT_7ffe9c963f30);
          lVar12 = *(longlong *)(thisObject + 0x168);
          plVar13 = plVar19;
          lStackX_20 = lVar14;
          if (lVar12 != 0) {
            while (uVar10 = (uint)plVar13, (int)uVar10 < *(int *)(lVar12 + 0x18)) {
              if (*(uint *)(lVar12 + 0x18) <= uVar10) {
                FUN_7ffe9996d790();
                goto LAB_7ffe99c0cb71;
              }
              uVar1 = *(uint *)(lVar12 + 0x20 + (longlong)(int)uVar10 * 4);
              if ((*(longlong *)(thisObject + 0x170) == 0) ||
                 (lVar15 = FUN_7ffe9a480590(*(longlong *)(thisObject + 0x170),0), lVar15 == 0))
              goto LAB_7ffe99c0cb65;
              uVar8 = FUN_7ffe9a7fd580(lVar15,uVar1,1);
              if (0 < (int)uVar8) {
                if (lVar14 == 0) goto LAB_7ffe99c0cb65;
                FUN_7ffe9acfd3d0(lVar14,uVar1 & 0xffff,uVar8 & 0xff);
              }
              plVar13 = (longlong *)(ulonglong)(uVar10 + 1);
            }
            if (lVar14 != 0) {
              iVar7 = func_0x7ffe9acd8120(lVar14,_DAT_7ffe9c9643f8);
              lVar12 = *(longlong *)(thisObject + 0x170);
              if (iVar7 < 1) {
                if ((lVar12 != 0) && (lVar12 = FUN_7ffe9a480590(lVar12,0), lVar12 != 0)) {
                  uVar9 = FUN_7ffe9a7fd580(lVar12,0x408,1,0);
                  if (*(int *)(_DAT_7ffe9c92a480 + 0xe0) == 0) {
                    func_0x7ffe9996d830();
                  }
                  uVar9 = func_0x7ffe9a8203c0(uVar9,0);
                  *(undefined4 *)(thisObject + 0x1b4) = uVar9;
                  if ((*(longlong *)(thisObject + 0x170) != 0) &&
                     (puVar17 = (undefined *)FUN_7ffe9a47f780(*(longlong *)(thisObject + 0x170),0),
                     puVar17 != (undefined *)0x0)) {
                    bVar5 = GemCartBufferManager_ContainsBuffer(puVar17,0x3ff,(undefined *)0x0);
                    if (bVar5 != 0) {
                      *(float *)(thisObject + 0x1b4) =
                           *(float *)(thisObject + 0x1b4) - _DAT_7ffe9c049b18;
                    }
                    fVar21 = 0.0;
                    if (0.0 <= *(float *)(thisObject + 0x1b4)) {
                      fVar21 = *(float *)(thisObject + 0x1b4);
                    }
                    *(float *)(thisObject + 0x1b4) = fVar21;
                    return;
                  }
                }
              }
              else if ((((lVar12 != 0) && (lVar12 = FUN_7ffe9a47fe30(lVar12,0), lVar12 != 0)) &&
                       (*(longlong *)(lVar12 + 0x30) != 0)) &&
                      (plVar13 = *(longlong **)(*(longlong *)(lVar12 + 0x30) + 0x30),
                      plVar13 != (longlong *)0x0)) {
                if ((*(byte *)(*plVar13 + 0x130) < *(byte *)(_DAT_7ffe9c949d68 + 0x130)) ||
                   (*(longlong *)
                     (*(longlong *)(*plVar13 + 200) + -8 +
                     (ulonglong)*(byte *)(_DAT_7ffe9c949d68 + 0x130) * 8) != _DAT_7ffe9c949d68)) {
                  FUN_7ffe9996c950(plVar13);
                  pcVar2 = (code *)swi(3);
                  (*pcVar2)();
                  return;
                }
                lVar12 = FUN_7ffe9a4b8510(plVar13,0);
                if (lVar12 != 0) {
                  plStackX_18 = (longlong *)FUN_7ffe99742ec0(0,_DAT_7ffe9c955db0,lVar12);
                  uStack_58 = 0;
                  pplStack_50 = &plStackX_18;
                  while (plStackX_18 != (longlong *)0x0) {
                    cVar4 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ac18);
                    plVar13 = plStackX_18;
                    if (cVar4 == '\0') {
                      if (plStackX_18 != (longlong *)0x0) {
                        FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
                      }
                      iVar7 = FUN_7ffe9ab80670(lVar14,_DAT_7ffe9c8fe9a8);
                      if (iVar7 < 1) {
                        *(float *)(thisObject + 0x1b4) =
                             *(float *)(thisObject + 0x1b4) + _DAT_7ffe9c049b4c;
                        return;
                      }
                      uVar9 = FUN_7ffe9bda4580(0,iVar7,0);
                      uVar10 = FUN_7ffe9ab821b0(lVar14,uVar9,_DAT_7ffe9c903fc8);
                      if (*(longlong *)(thisObject + 0x170) != 0) {
                        uVar11 = FUN_7ffe9a47fe30(*(longlong *)(thisObject + 0x170),0);
                        uStackX_a = (undefined1)(uVar10 >> 0x10);
                        plVar13 = (longlong *)FUN_7ffe9a7fb2c0(uVar10 & 0xffff,uStackX_a,uVar11,0);
                        if (plVar13 != (longlong *)0x0) {
                          if ((*(byte *)(*plVar13 + 0x130) < *(byte *)(_DAT_7ffe9c9228b0 + 0x130))
                             || (*(longlong *)
                                  (*(longlong *)(*plVar13 + 200) + -8 +
                                  (ulonglong)*(byte *)(_DAT_7ffe9c9228b0 + 0x130) * 8) !=
                                 _DAT_7ffe9c9228b0)) {
                            bVar3 = false;
                          }
                          else {
                            bVar3 = true;
                          }
                          if (bVar3) {
                            plVar19 = plVar13;
                          }
                        }
                        cVar4 = FUN_7ffe9a8fec40(plVar19,0,0);
                        if (cVar4 != '\0') {
                          return;
                        }
                        if ((*(longlong *)(thisObject + 0x170) != 0) &&
                           (lVar12 = FUN_7ffe9a480590(*(longlong *)(thisObject + 0x170),0),
                           lVar12 != 0)) {
                          uVar9 = FUN_7ffe9a7fd580(lVar12,0x408,1,0);
                          if (*(int *)(_DAT_7ffe9c92a480 + 0xe0) == 0) {
                            func_0x7ffe9996d830();
                          }
                          uVar9 = func_0x7ffe9a8203c0(uVar9,0);
                          *(undefined4 *)(thisObject + 0x1b4) = uVar9;
                          if ((*(longlong *)(thisObject + 0x170) != 0) &&
                             (puVar17 = (undefined *)
                                        FUN_7ffe9a47f780(*(longlong *)(thisObject + 0x170),0),
                             puVar17 != (undefined *)0x0)) {
                            bVar5 = GemCartBufferManager_ContainsBuffer
                                              (puVar17,0x3ff,(undefined *)0x0);
                            if (bVar5 != 0) {
                              *(float *)(thisObject + 0x1b4) =
                                   *(float *)(thisObject + 0x1b4) - _DAT_7ffe9c049b18;
                            }
                            fVar21 = *(float *)(thisObject + 0x1b4);
                            if (fVar21 < 0.0) {
                              fVar21 = 0.0;
                            }
                            *(float *)(thisObject + 0x1b4) = fVar21;
                            if ((((*(longlong *)(thisObject + 0x170) != 0) &&
                                 (lVar12 = FUN_7ffe9a47fe30(*(longlong *)(thisObject + 0x170),0),
                                 lVar12 != 0)) &&
                                (plVar13 = *(longlong **)(lVar12 + 0x30), plVar13 != (longlong *)0x0
                                )) && (lVar12 = plVar13[9], lVar12 != 0)) {
                              lVar14 = *(longlong *)(lVar12 + 0x18);
                              fVar21 = *(float *)(lVar12 + 0x28);
                              if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                                func_0x7ffe9996d830();
                              }
                              cVar4 = FUN_7ffe9bda1fa0(lVar14,0,0);
                              if (cVar4 != '\0') {
                                return;
                              }
                              if ((lVar14 != 0) &&
                                 (lVar12 = FUN_7ffe9bd9b890(lVar14,0), lVar12 != 0)) {
                                puVar16 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_58,lVar12,0);
                                uVar11 = *puVar16;
                                fVar20 = *(float *)(puVar16 + 1);
                                if ((*(longlong *)(thisObject + 0x170) != 0) &&
                                   (lVar12 = FUN_7ffe9a480940(*(longlong *)(thisObject + 0x170),0),
                                   lVar12 != 0)) {
                                  puVar16 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_58,lVar12,0);
                                  pplStack_50 = (longlong **)
                                                CONCAT44(pplStack_50._4_4_,*(float *)(puVar16 + 1));
                                  fStack_70 = (float)uVar11;
                                  fStack_70 = fStack_70 - (float)*puVar16;
                                  fVar20 = fVar20 - *(float *)(puVar16 + 1);
                                  if (plVar19 != (longlong *)0x0) {
                                    fVar21 = fVar21 + *(float *)(plVar19 + 4);
                                    if (fVar21 * fVar21 <
                                        fStack_70 * fStack_70 + 0.0 + fVar20 * fVar20) {
                                      return;
                                    }
                                    lVar12 = *plVar13;
                                    if ((*(byte *)(_DAT_7ffe9c922a40 + 0x130) <=
                                         *(byte *)(lVar12 + 0x130)) &&
                                       (*(longlong *)
                                         (*(longlong *)(lVar12 + 200) + -8 +
                                         (ulonglong)*(byte *)(_DAT_7ffe9c922a40 + 0x130) * 8) ==
                                        _DAT_7ffe9c922a40)) {
                                      if ((*(byte *)(_DAT_7ffe9c922a40 + 0x130) <=
                                           *(byte *)(lVar12 + 0x130)) &&
                                         (*(longlong *)
                                           (*(longlong *)(lVar12 + 200) + -8 +
                                           (ulonglong)*(byte *)(_DAT_7ffe9c922a40 + 0x130) * 8) ==
                                          _DAT_7ffe9c922a40)) {
                                        FUN_7ffe9a46e590(plVar13,plVar19,0);
                                        return;
                                      }
                                      FUN_7ffe9996c950(plVar13);
                                      pcVar2 = (code *)swi(3);
                                      (*pcVar2)();
                                      return;
                                    }
                                    if (*(byte *)(lVar12 + 0x130) <
                                        *(byte *)(_DAT_7ffe9c8f7560 + 0x130)) {
                                      return;
                                    }
                                    if (*(longlong *)
                                         (*(longlong *)(lVar12 + 200) + -8 +
                                         (ulonglong)*(byte *)(_DAT_7ffe9c8f7560 + 0x130) * 8) !=
                                        _DAT_7ffe9c8f7560) {
                                      return;
                                    }
                                    if ((*(byte *)(_DAT_7ffe9c8f7560 + 0x130) <=
                                         *(byte *)(lVar12 + 0x130)) &&
                                       (*(longlong *)
                                         (*(longlong *)(lVar12 + 200) + -8 +
                                         (ulonglong)*(byte *)(_DAT_7ffe9c8f7560 + 0x130) * 8) ==
                                        _DAT_7ffe9c8f7560)) {
                                      FUN_7ffe9a43f490(plVar13,plVar19,0);
                                      return;
                                    }
                                    FUN_7ffe9996c950(plVar13);
                                    pcVar2 = (code *)swi(3);
                                    (*pcVar2)();
                                    return;
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                      goto LAB_7ffe99c0cb65;
                    }
                    if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe99c0cb77;
                    lVar12 = *plStackX_18;
                    uVar18 = 0;
                    if (*(ushort *)(lVar12 + 0x12e) != 0) {
                      do {
                        if (*(longlong *)(*(longlong *)(lVar12 + 0xb0) + (ulonglong)uVar18 * 0x10)
                            == _DAT_7ffe9c95b888) {
                          puVar16 = (undefined8 *)
                                    (lVar12 + 0x138 +
                                    (longlong)
                                    *(int *)(*(longlong *)(lVar12 + 0xb0) + 8 +
                                            (ulonglong)uVar18 * 0x10) * 0x10);
                          goto LAB_7ffe99c0c5f9;
                        }
                        uVar18 = uVar18 + 1;
                      } while (uVar18 < *(ushort *)(lVar12 + 0x12e));
                    }
                    puVar16 = (undefined8 *)FUN_7ffe998ce540(plStackX_18,_DAT_7ffe9c95b888,0);
LAB_7ffe99c0c5f9:
                    plVar13 = (longlong *)(*(code *)*puVar16)(plVar13,puVar16[1]);
                    if (plVar13 == (longlong *)0x0) goto LAB_7ffe99c0cb71;
                    uVar6 = (**(code **)(*plVar13 + 0x188))(plVar13,*(undefined8 *)(*plVar13 + 400))
                    ;
                    cVar4 = FUN_7ffe9acfd500(lVar14,uVar6,_DAT_7ffe9c9640c8);
                    if (((cVar4 != '\0') &&
                        (lVar12 = func_0x7ffe9996c920(plVar13,_DAT_7ffe9c93c620), lVar12 != 0)) &&
                       (cVar4 = FUN_7ffe99742ec0(1,_DAT_7ffe9c93c620,lVar12), cVar4 != '\0')) {
                      uVar6 = (**(code **)(*plVar13 + 0x188))
                                        (plVar13,*(undefined8 *)(*plVar13 + 400));
                      FUN_7ffe9ad028c0(lVar14,uVar6,_DAT_7ffe9c964260);
                    }
                  }
                  goto LAB_7ffe99c0cb7c;
                }
              }
            }
          }
        }
      }
    }
  }
LAB_7ffe99c0cb65:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
LAB_7ffe99c0cb71:
  FUN_7ffe9996d7a0();
LAB_7ffe99c0cb77:
  FUN_7ffe9996d7a0();
LAB_7ffe99c0cb7c:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

