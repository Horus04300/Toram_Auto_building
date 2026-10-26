
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PlayerBattleManager_PursuitAttack
               (undefined *self,undefined *targetActManager,undefined *action,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  undefined *mobAction;
  longlong *plVar9;
  undefined8 uVar10;
  longlong *plVar11;
  undefined8 uVar12;
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
  plVar11 = (longlong *)0x0;
  aplStack_38[0] = (longlong *)0x0;
  aplStackX_18[0] = (longlong *)0x0;
  if (action == (undefined *)0x0) goto LAB_7ffe9a469f5c;
  uVar10 = *(undefined8 *)(action + 0x80);
  if (*(int *)(_DAT_7ffe9c9108e8 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  lVar8 = *(longlong *)(*(longlong *)(_DAT_7ffe9c9108e8 + 0xb8) + 0x28);
  if (lVar8 == 0) {
    if (*(int *)(_DAT_7ffe9c9108e8 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    uVar12 = **(undefined8 **)(_DAT_7ffe9c9108e8 + 0xb8);
    lVar8 = func_0x7ffe99940040(_DAT_7ffe9c94ab28);
    FUN_7ffe9af13420(lVar8,uVar12,_DAT_7ffe9c8fccb8,0);
    *(longlong *)(*(longlong *)(_DAT_7ffe9c9108e8 + 0xb8) + 0x28) = lVar8;
    il2cpp_write_barrier_0();
  }
  cVar4 = FUN_7ffe9ab7ad20(uVar10,lVar8,_DAT_7ffe9c8fbdc8);
  if (cVar4 != '\0') {
    plVar9 = *(longlong **)(self + 0x28);
    if (plVar9 != (longlong *)0x0) {
      if ((*(byte *)(*plVar9 + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar9 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8)
          != _DAT_7ffe9c922720)) {
        bVar3 = false;
      }
      else {
        bVar3 = true;
      }
      if (bVar3) {
        plVar11 = plVar9;
      }
    }
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar4 = FUN_7ffe9bda1fa0(plVar11,0,0);
    if ((cVar4 == '\0') &&
       ((mobAction = (undefined *)func_0x7ffe9996c920(targetActManager,_DAT_7ffe9c9724e0),
        mobAction == (undefined *)0x0 ||
        (cVar4 = FUN_7ffe99742ec0(0x14,_DAT_7ffe9c9724e0,mobAction), cVar4 == '\0')))) {
      uVar5 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      cVar4 = func_0x7ffe9a496210(uVar5,0);
      if (cVar4 != '\0') {
        if (((plVar11 != (longlong *)0x0) &&
            (plVar9 = (longlong *)
                      (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0)),
            plVar9 != (longlong *)0x0)) &&
           (lVar8 = (**(code **)(*plVar9 + 0x208))(plVar9,*(undefined8 *)(*plVar9 + 0x210)),
           lVar8 != 0)) {
          cVar4 = FUN_7ffe9a51e210(lVar8,0x99,0);
          iVar6 = 0x19;
          if (cVar4 == '\0') {
            plVar9 = *(longlong **)(self + 0x88);
            if (((plVar9 == (longlong *)0x0) ||
                (plVar9 = (longlong *)
                          (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0)),
                plVar9 == (longlong *)0x0)) ||
               (lVar8 = (**(code **)(*plVar9 + 0x1c8))(plVar9,*(undefined8 *)(*plVar9 + 0x1d0)),
               lVar8 == 0)) goto LAB_7ffe9a469f5c;
            cVar4 = FUN_7ffe9a7c6d00(lVar8,0x32,0);
            if (cVar4 != '\0') {
              iVar7 = 0x19;
              plVar9 = (longlong *)
                       (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
              if (((plVar9 == (longlong *)0x0) ||
                  (lVar8 = (**(code **)(*plVar9 + 0x1b8))(plVar9,*(undefined8 *)(*plVar9 + 0x1c0)),
                  lVar8 == 0)) || (*(longlong *)(lVar8 + 0x68) == 0)) goto LAB_7ffe9a469f5c;
              cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0x1ed,aplStack_38);
              if (cVar4 != '\0') {
                if (aplStack_38[0] == (longlong *)0x0) goto LAB_7ffe9a469f5c;
                iVar7 = (**(code **)(*aplStack_38[0] + 0x178))
                                  (aplStack_38[0],0x1b,*(undefined8 *)(*aplStack_38[0] + 0x180));
                iVar7 = iVar7 + 0x19;
              }
              cVar4 = FUN_7ffe99a4d1d0(iVar7,0);
              if (cVar4 != '\0') {
                if ((*(longlong *)(self + 0x48) == 0) ||
                   (uVar10 = *(undefined8 *)(*(longlong *)(self + 0x48) + 0x18),
                   mobAction == (undefined *)0x0)) goto LAB_7ffe9a469f5c;
                uVar12 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c9724e0,mobAction);
                if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                  func_0x7ffe9996d830();
                }
                cVar4 = FUN_7ffe9bda1fa0(uVar10,uVar12,0);
                if (cVar4 != '\0') {
                  PlayerBattleManager_EquipBuffAttack(self,0x99,mobAction,(undefined *)0x0);
                }
              }
            }
          }
          else {
            plVar9 = (longlong *)
                     (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
            if ((plVar9 == (longlong *)0x0) ||
               (lVar8 = (**(code **)(*plVar9 + 0x208))(plVar9,*(undefined8 *)(*plVar9 + 0x210)),
               lVar8 == 0)) goto LAB_7ffe9a469f5c;
            FUN_7ffe9a51d1c0(lVar8,0x99,0,plVar11,mobAction,0);
          }
          plVar9 = (longlong *)
                   (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
          if ((plVar9 != (longlong *)0x0) &&
             (lVar8 = (**(code **)(*plVar9 + 0x208))(plVar9,*(undefined8 *)(*plVar9 + 0x210)),
             lVar8 != 0)) {
            cVar4 = FUN_7ffe9a51e210(lVar8,0x9a,0);
            pcVar2 = *(code **)(*plVar11 + 0x298);
            if (cVar4 == '\0') {
              plVar9 = (longlong *)(*pcVar2)();
              if ((plVar9 != (longlong *)0x0) &&
                 (lVar8 = (**(code **)(*plVar9 + 0x1c8))(plVar9,*(undefined8 *)(*plVar9 + 0x1d0)),
                 lVar8 != 0)) {
                cVar4 = FUN_7ffe9a7c6d00(lVar8,0x401,0);
                if (cVar4 == '\0') {
                  plVar9 = (longlong *)
                           (**(code **)(*plVar11 + 0x298))
                                     (plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
                  if ((plVar9 == (longlong *)0x0) ||
                     (lVar8 = (**(code **)(*plVar9 + 0x1c8))
                                        (plVar9,*(undefined8 *)(*plVar9 + 0x1d0)), lVar8 == 0))
                  goto LAB_7ffe9a469f5c;
                  cVar4 = FUN_7ffe9a7c6d00(lVar8,0x408,0);
                  if (cVar4 == '\0') {
                    plVar9 = (longlong *)
                             (**(code **)(*plVar11 + 0x298))
                                       (plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
                    if ((plVar9 == (longlong *)0x0) ||
                       (lVar8 = (**(code **)(*plVar9 + 0x1c8))
                                          (plVar9,*(undefined8 *)(*plVar9 + 0x1d0)), lVar8 == 0))
                    goto LAB_7ffe9a469f5c;
                    cVar4 = FUN_7ffe9a7c6d00(lVar8,0x3d6,0);
                    if (cVar4 == '\0') {
                      return;
                    }
                  }
                }
                plVar9 = (longlong *)
                         (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
                if (((plVar9 != (longlong *)0x0) &&
                    (lVar8 = (**(code **)(*plVar9 + 0x1b8))(plVar9,*(undefined8 *)(*plVar9 + 0x1c0))
                    , lVar8 != 0)) && (*(longlong *)(lVar8 + 0x68) != 0)) {
                  cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0x1ed,aplStackX_18);
                  if (cVar4 != '\0') {
                    if (aplStackX_18[0] == (longlong *)0x0) goto LAB_7ffe9a469f5c;
                    iVar6 = (**(code **)(*aplStackX_18[0] + 0x178))
                                      (aplStackX_18[0],0x1b,
                                       *(undefined8 *)(*aplStackX_18[0] + 0x180));
                    iVar6 = iVar6 + 0x19;
                    plVar11 = (longlong *)
                              (**(code **)(*plVar11 + 0x298))
                                        (plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
                    if ((plVar11 == (longlong *)0x0) ||
                       (lVar8 = (**(code **)(*plVar11 + 0x218))
                                          (plVar11,*(undefined8 *)(*plVar11 + 0x220)), lVar8 == 0))
                    goto LAB_7ffe9a469f5c;
                    cVar4 = FUN_7ffe9a5b20c0(lVar8,0x3f2,0);
                    if (cVar4 != '\0') {
                      if ((aplStackX_18[0] == (longlong *)0x0) || (aplStackX_18[0][2] == 0))
                      goto LAB_7ffe9a469f5c;
                      iVar6 = iVar6 + (uint)*(byte *)(aplStackX_18[0][2] + 0x18);
                    }
                  }
                  cVar4 = FUN_7ffe99a4d1d0(iVar6,0);
                  if (cVar4 == '\0') {
                    return;
                  }
                  if ((*(longlong *)(self + 0x48) != 0) &&
                     (uVar10 = *(undefined8 *)(*(longlong *)(self + 0x48) + 0x18),
                     mobAction != (undefined *)0x0)) {
                    uVar12 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c9724e0,mobAction);
                    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                      func_0x7ffe9996d830();
                    }
                    cVar4 = FUN_7ffe9bda1fa0(uVar10,uVar12,0);
                    if (cVar4 == '\0') {
                      return;
                    }
                    PlayerBattleManager_EquipBuffAttack(self,0x9a,mobAction,(undefined *)0x0);
                    return;
                  }
                }
              }
            }
            else {
              plVar9 = (longlong *)(*pcVar2)(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
              if ((plVar9 != (longlong *)0x0) &&
                 (lVar8 = (**(code **)(*plVar9 + 0x208))(plVar9,*(undefined8 *)(*plVar9 + 0x210)),
                 lVar8 != 0)) {
                FUN_7ffe9a51d1c0(lVar8,0x9a,0,plVar11,mobAction,0);
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
      iVar6 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      if (iVar6 == 0x3cd) {
        if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c963378 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*(longlong *)action + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c963378 + 0x130) * 8) != _DAT_7ffe9c963378)) {
          FUN_7ffe9996c950(action);
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
        plVar9 = (longlong *)func_0x7ffe9a7fb2b0(0xf);
        if (plVar9 != (longlong *)0x0) {
          if ((*(byte *)(_DAT_7ffe9c9635d8 + 0x130) <= *(byte *)(*plVar9 + 0x130)) &&
             (*(longlong *)
               (*(longlong *)(*plVar9 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c9635d8 + 0x130) * 8) == _DAT_7ffe9c9635d8)) {
            FUN_7ffe9a8fe290(plVar9,*(undefined8 *)(self + 0x28),action[0x14],0);
            FUN_7ffe9a490ae0(plVar9,*(undefined8 *)(action + 0x130),
                             (float)*(int *)(action + 0x104) / _DAT_7ffe9c049cfc,0);
            if (targetActManager != (undefined *)0x0) {
              uVar10 = FUN_7ffe9bd98960(targetActManager,0);
              cVar4 = FUN_7ffe9974e380(0x1c,self,uVar10,targetActManager,plVar9);
              if (cVar4 == '\0') {
                return;
              }
              plVar1 = *(longlong **)(self + 0x30);
              uVar10 = FUN_7ffe9bd98960(targetActManager,0);
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
                FUN_7ffe9a49fd00(plVar1,uVar10,plVar9,0);
                if (((plVar11 != (longlong *)0x0) &&
                    (plVar11 = (longlong *)
                               (**(code **)(*plVar11 + 0x298))
                                         (plVar11,*(undefined8 *)(*plVar11 + 0x2a0)),
                    plVar11 != (longlong *)0x0)) &&
                   (lVar8 = (**(code **)(*plVar11 + 0x1c8))
                                      (plVar11,*(undefined8 *)(*plVar11 + 0x1d0)), lVar8 != 0)) {
                  FUN_7ffe9a7c2b40(lVar8,0x3cd,action[0x14],action[0x10],0);
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

