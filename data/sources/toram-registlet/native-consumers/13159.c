
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PlayerBattleManager_PursuitAttack
               (undefined *thisObject,undefined *targetActManager,undefined *action,
               undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  byte bVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  longlong lVar9;
  longlong *plVar10;
  undefined8 uVar11;
  longlong *plVar12;
  longlong lVar13;
  undefined8 uVar14;
  undefined *thisObject_00;
  longlong *aplStackX_18 [2];
  longlong *aplStack_38 [2];
  
  if (DAT_7ffe9caddd08 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c963378);
    FUN_7ffe9996d590(&DAT_7ffe9c9635d8);
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c8fbdc8);
    FUN_7ffe9996d590(&DAT_7ffe9c94ab28);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c923530);
    FUN_7ffe9996d590(&DAT_7ffe9c8fccb8);
    FUN_7ffe9996d590(&DAT_7ffe9c9108e8);
    DAT_7ffe9caddd08 = '\x01';
  }
  plVar12 = (longlong *)0x0;
  aplStack_38[0] = (longlong *)0x0;
  aplStackX_18[0] = (longlong *)0x0;
  if (action == (undefined *)0x0) goto LAB_7ffe9a469f5c;
  uVar11 = *(undefined8 *)(action + 0x80);
  if (*(int *)(_DAT_7ffe9c9108e8 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  lVar9 = *(longlong *)(*(longlong *)(_DAT_7ffe9c9108e8 + 0xb8) + 0x28);
  if (lVar9 == 0) {
    if (*(int *)(_DAT_7ffe9c9108e8 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    uVar14 = **(undefined8 **)(_DAT_7ffe9c9108e8 + 0xb8);
    lVar9 = func_0x7ffe99940040(_DAT_7ffe9c94ab28);
    FUN_7ffe9af13420(lVar9,uVar14,_DAT_7ffe9c8fccb8,0);
    *(longlong *)(*(longlong *)(_DAT_7ffe9c9108e8 + 0xb8) + 0x28) = lVar9;
    il2cpp_write_barrier_0();
  }
  cVar4 = FUN_7ffe9ab7ad20(uVar11,lVar9,_DAT_7ffe9c8fbdc8);
  if (cVar4 != '\0') {
    plVar10 = *(longlong **)(thisObject + 0x28);
    if (plVar10 != (longlong *)0x0) {
      if ((*(byte *)(*plVar10 + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar10 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8
           ) != _DAT_7ffe9c922720)) {
        bVar3 = false;
      }
      else {
        bVar3 = true;
      }
      if (bVar3) {
        plVar12 = plVar10;
      }
    }
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar4 = FUN_7ffe9bda1fa0(plVar12,0,0);
    if ((cVar4 == '\0') &&
       ((lVar9 = func_0x7ffe9996c920(targetActManager,_DAT_7ffe9c9724e0), lVar9 == 0 ||
        (cVar4 = FUN_7ffe99742ec0(0x14,_DAT_7ffe9c9724e0,lVar9), cVar4 == '\0')))) {
      uVar6 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      cVar4 = func_0x7ffe9a496210(uVar6,0);
      if (cVar4 != '\0') {
        if (((plVar12 != (longlong *)0x0) &&
            (plVar10 = (longlong *)
                       (**(code **)(*plVar12 + 0x298))(plVar12,*(undefined8 *)(*plVar12 + 0x2a0)),
            plVar10 != (longlong *)0x0)) &&
           (lVar13 = (**(code **)(*plVar10 + 0x208))(plVar10,*(undefined8 *)(*plVar10 + 0x210)),
           lVar13 != 0)) {
          cVar4 = FUN_7ffe9a51e210(lVar13,0x99,0);
          iVar7 = 0x19;
          if (cVar4 == '\0') {
            plVar10 = *(longlong **)(thisObject + 0x88);
            if (((plVar10 == (longlong *)0x0) ||
                (plVar10 = (longlong *)
                           (**(code **)(*plVar10 + 0x298))
                                     (plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
                plVar10 == (longlong *)0x0)) ||
               (lVar13 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
               lVar13 == 0)) goto LAB_7ffe9a469f5c;
            cVar4 = FUN_7ffe9a7c6d00(lVar13,0x32,0);
            if (cVar4 != '\0') {
              iVar8 = 0x19;
              plVar10 = (longlong *)
                        (**(code **)(*plVar12 + 0x298))(plVar12,*(undefined8 *)(*plVar12 + 0x2a0));
              if (((plVar10 == (longlong *)0x0) ||
                  (lVar13 = (**(code **)(*plVar10 + 0x1b8))
                                      (plVar10,*(undefined8 *)(*plVar10 + 0x1c0)), lVar13 == 0)) ||
                 (*(longlong *)(lVar13 + 0x68) == 0)) goto LAB_7ffe9a469f5c;
              cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar13 + 0x68),0x1ed,aplStack_38,
                                       _DAT_7ffe9c935bd0);
              if (cVar4 != '\0') {
                if (aplStack_38[0] == (longlong *)0x0) goto LAB_7ffe9a469f5c;
                iVar8 = (**(code **)(*aplStack_38[0] + 0x178))
                                  (aplStack_38[0],0x1b,*(undefined8 *)(*aplStack_38[0] + 0x180));
                iVar8 = iVar8 + 0x19;
              }
              cVar4 = FUN_7ffe99a4d1d0(iVar8,0);
              if (cVar4 != '\0') {
                if ((*(longlong *)(thisObject + 0x48) == 0) ||
                   (uVar11 = *(undefined8 *)(*(longlong *)(thisObject + 0x48) + 0x18), lVar9 == 0))
                goto LAB_7ffe9a469f5c;
                uVar14 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c9724e0,lVar9);
                if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                  func_0x7ffe9996d830();
                }
                cVar4 = FUN_7ffe9bda1fa0(uVar11,uVar14,0);
                if (cVar4 != '\0') {
                  FUN_7ffe9a45bf30(thisObject,0x99,lVar9,0);
                }
              }
            }
          }
          else {
            plVar10 = (longlong *)
                      (**(code **)(*plVar12 + 0x298))(plVar12,*(undefined8 *)(*plVar12 + 0x2a0));
            if ((plVar10 == (longlong *)0x0) ||
               (lVar13 = (**(code **)(*plVar10 + 0x208))(plVar10,*(undefined8 *)(*plVar10 + 0x210)),
               lVar13 == 0)) goto LAB_7ffe9a469f5c;
            FUN_7ffe9a51d1c0(lVar13,0x99,0,plVar12,lVar9,0);
          }
          plVar10 = (longlong *)
                    (**(code **)(*plVar12 + 0x298))(plVar12,*(undefined8 *)(*plVar12 + 0x2a0));
          if ((plVar10 != (longlong *)0x0) &&
             (lVar13 = (**(code **)(*plVar10 + 0x208))(plVar10,*(undefined8 *)(*plVar10 + 0x210)),
             lVar13 != 0)) {
            cVar4 = FUN_7ffe9a51e210(lVar13,0x9a,0);
            pcVar2 = *(code **)(*plVar12 + 0x298);
            if (cVar4 == '\0') {
              plVar10 = (longlong *)(*pcVar2)();
              if ((plVar10 != (longlong *)0x0) &&
                 (lVar13 = (**(code **)(*plVar10 + 0x1c8))
                                     (plVar10,*(undefined8 *)(*plVar10 + 0x1d0)), lVar13 != 0)) {
                cVar4 = FUN_7ffe9a7c6d00(lVar13,0x401,0);
                if (cVar4 == '\0') {
                  plVar10 = (longlong *)
                            (**(code **)(*plVar12 + 0x298))
                                      (plVar12,*(undefined8 *)(*plVar12 + 0x2a0));
                  if ((plVar10 == (longlong *)0x0) ||
                     (lVar13 = (**(code **)(*plVar10 + 0x1c8))
                                         (plVar10,*(undefined8 *)(*plVar10 + 0x1d0)), lVar13 == 0))
                  goto LAB_7ffe9a469f5c;
                  cVar4 = FUN_7ffe9a7c6d00(lVar13,0x408,0);
                  if (cVar4 == '\0') {
                    plVar10 = (longlong *)
                              (**(code **)(*plVar12 + 0x298))
                                        (plVar12,*(undefined8 *)(*plVar12 + 0x2a0));
                    if ((plVar10 == (longlong *)0x0) ||
                       (lVar13 = (**(code **)(*plVar10 + 0x1c8))
                                           (plVar10,*(undefined8 *)(*plVar10 + 0x1d0)), lVar13 == 0)
                       ) goto LAB_7ffe9a469f5c;
                    cVar4 = FUN_7ffe9a7c6d00(lVar13,0x3d6,0);
                    if (cVar4 == '\0') {
                      return;
                    }
                  }
                }
                plVar10 = (longlong *)
                          (**(code **)(*plVar12 + 0x298))(plVar12,*(undefined8 *)(*plVar12 + 0x2a0))
                ;
                if (((plVar10 != (longlong *)0x0) &&
                    (lVar13 = (**(code **)(*plVar10 + 0x1b8))
                                        (plVar10,*(undefined8 *)(*plVar10 + 0x1c0)), lVar13 != 0))
                   && (*(longlong *)(lVar13 + 0x68) != 0)) {
                  cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar13 + 0x68),0x1ed,aplStackX_18,
                                           _DAT_7ffe9c935bd0);
                  if (cVar4 != '\0') {
                    if (aplStackX_18[0] == (longlong *)0x0) goto LAB_7ffe9a469f5c;
                    iVar7 = (**(code **)(*aplStackX_18[0] + 0x178))
                                      (aplStackX_18[0],0x1b,
                                       *(undefined8 *)(*aplStackX_18[0] + 0x180));
                    iVar7 = iVar7 + 0x19;
                    plVar12 = (longlong *)
                              (**(code **)(*plVar12 + 0x298))
                                        (plVar12,*(undefined8 *)(*plVar12 + 0x2a0));
                    if ((plVar12 == (longlong *)0x0) ||
                       (thisObject_00 =
                             (undefined *)
                             (**(code **)(*plVar12 + 0x218))
                                       (plVar12,*(undefined8 *)(*plVar12 + 0x220)),
                       thisObject_00 == (undefined *)0x0)) goto LAB_7ffe9a469f5c;
                    bVar5 = GemCartBufferManager_ContainsBuffer
                                      (thisObject_00,0x3f2,(undefined *)0x0);
                    if (bVar5 != 0) {
                      if ((aplStackX_18[0] == (longlong *)0x0) || (aplStackX_18[0][2] == 0))
                      goto LAB_7ffe9a469f5c;
                      iVar7 = iVar7 + (uint)*(byte *)(aplStackX_18[0][2] + 0x18);
                    }
                  }
                  cVar4 = FUN_7ffe99a4d1d0(iVar7,0);
                  if (cVar4 == '\0') {
                    return;
                  }
                  if ((*(longlong *)(thisObject + 0x48) != 0) &&
                     (uVar11 = *(undefined8 *)(*(longlong *)(thisObject + 0x48) + 0x18), lVar9 != 0)
                     ) {
                    uVar14 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c9724e0,lVar9);
                    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                      func_0x7ffe9996d830();
                    }
                    cVar4 = FUN_7ffe9bda1fa0(uVar11,uVar14,0);
                    if (cVar4 == '\0') {
                      return;
                    }
                    FUN_7ffe9a45bf30(thisObject,0x9a,lVar9,0);
                    return;
                  }
                }
              }
            }
            else {
              plVar10 = (longlong *)(*pcVar2)(plVar12,*(undefined8 *)(*plVar12 + 0x2a0));
              if ((plVar10 != (longlong *)0x0) &&
                 (lVar13 = (**(code **)(*plVar10 + 0x208))
                                     (plVar10,*(undefined8 *)(*plVar10 + 0x210)), lVar13 != 0)) {
                FUN_7ffe9a51d1c0(lVar13,0x9a,0,plVar12,lVar9,0);
                return;
              }
            }
          }
        }
LAB_7ffe9a469f5c:
        FUN_7ffe9996d7a0();
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      iVar7 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      if (iVar7 == 0x3cd) {
        if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c963378 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*(longlong *)action + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c963378 + 0x130) * 8) != _DAT_7ffe9c963378)) {
          FUN_7ffe9996c950(action);
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
        plVar10 = (longlong *)func_0x7ffe9a7fb2b0(0xf);
        if (plVar10 != (longlong *)0x0) {
          if ((*(byte *)(_DAT_7ffe9c9635d8 + 0x130) <= *(byte *)(*plVar10 + 0x130)) &&
             (*(longlong *)
               (*(longlong *)(*plVar10 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c9635d8 + 0x130) * 8) == _DAT_7ffe9c9635d8)) {
            FUN_7ffe9a8fe290(plVar10,*(undefined8 *)(thisObject + 0x28),action[0x14],0);
            FUN_7ffe9a490ae0(plVar10,*(undefined8 *)(action + 0x130),
                             (float)*(int *)(action + 0x104) / _DAT_7ffe9c049cfc,0);
            if (targetActManager != (undefined *)0x0) {
              uVar11 = FUN_7ffe9bd98960(targetActManager,0);
              cVar4 = FUN_7ffe9974e380(0x1c,thisObject,uVar11,targetActManager,plVar10);
              if (cVar4 == '\0') {
                return;
              }
              plVar1 = *(longlong **)(thisObject + 0x30);
              uVar11 = FUN_7ffe9bd98960(targetActManager,0);
              if (plVar1 != (longlong *)0x0) {
                if ((*(byte *)(*plVar1 + 0x130) < *(byte *)(_DAT_7ffe9c923530 + 0x130)) ||
                   (*(longlong *)
                     (*(longlong *)(*plVar1 + 200) + -8 +
                     (ulonglong)*(byte *)(_DAT_7ffe9c923530 + 0x130) * 8) != _DAT_7ffe9c923530)) {
                  FUN_7ffe9996c950(plVar1,_DAT_7ffe9c923530);
                  pcVar2 = (code *)swi(3);
                  (*pcVar2)();
                  return;
                }
                FUN_7ffe9a49fd00(plVar1,uVar11,plVar10,0);
                if (((plVar12 != (longlong *)0x0) &&
                    (plVar12 = (longlong *)
                               (**(code **)(*plVar12 + 0x298))
                                         (plVar12,*(undefined8 *)(*plVar12 + 0x2a0)),
                    plVar12 != (longlong *)0x0)) &&
                   (lVar9 = (**(code **)(*plVar12 + 0x1c8))
                                      (plVar12,*(undefined8 *)(*plVar12 + 0x1d0)), lVar9 != 0)) {
                  FUN_7ffe9a7c2b40(lVar9,0x3cd,action[0x14],action[0x10],0);
                  return;
                }
              }
            }
          }
        }
        goto LAB_7ffe9a469f5c;
      }
    }
  }
  return;
}

