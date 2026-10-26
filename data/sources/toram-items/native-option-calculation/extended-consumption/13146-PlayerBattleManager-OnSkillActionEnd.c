
/* WARNING: Removing unreachable block (ram,0x7ffe9a461a08) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a461a27) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a461a39) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a461a42) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a461a4f) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a461a53) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a461a59) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a461a7b) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a461a97) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PlayerBattleManager_OnSkillActionEnd
               (undefined *self,undefined *target,undefined *targetActManager,undefined *action,
               undefined *methodInfo)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  code *pcVar4;
  undefined4 uVar5;
  char cVar6;
  byte bVar7;
  bool bVar8;
  undefined1 uVar9;
  short sVar10;
  ushort uVar11;
  int iVar12;
  longlong lVar13;
  longlong *plVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  ulonglong uVar17;
  longlong lVar18;
  longlong lVar19;
  undefined8 *puVar20;
  float fVar21;
  undefined8 uStack_e8;
  undefined8 *puStack_e0;
  longlong lStack_d8;
  undefined8 uStack_d0;
  undefined8 *puStack_c8;
  longlong lStack_c0;
  undefined8 uStack_b8;
  undefined4 uStack_b0;
  undefined8 uStack_a8;
  undefined4 uStack_a0;
  undefined1 auStack_90 [16];
  undefined1 auStack_80 [72];
  
  if (DAT_7ffe9caddcfc == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c941198);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c91b2b0);
    FUN_7ffe9996d590(&DAT_7ffe9c91b380);
    FUN_7ffe9996d590(0x7ffe9c91b450);
    FUN_7ffe9996d590(&DAT_7ffe9c962758);
    FUN_7ffe9996d590(&DAT_7ffe9c9136f8);
    FUN_7ffe9996d590(&DAT_7ffe9c95c838);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c914fd0);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c922658);
    FUN_7ffe9996d590(&DAT_7ffe9c9228b0);
    FUN_7ffe9996d590(&DAT_7ffe9c952a50);
    FUN_7ffe9996d590(&DAT_7ffe9c956938);
    FUN_7ffe9996d590(&DAT_7ffe9c956ad0);
    FUN_7ffe9996d590(&DAT_7ffe9c94c0a0);
    DAT_7ffe9caddcfc = '\x01';
  }
  uStack_d0 = 0;
  puStack_c8 = (undefined8 *)0x0;
  lStack_c0 = 0;
  uVar17 = 0;
  lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
  if (lVar13 != 0) {
    FUN_7ffe9a29adb0(lVar13,0);
    if ((action != (undefined *)0x0) && (*(longlong *)(self + 0xd0) != 0)) {
      FUN_7ffe99aaebf0(*(longlong *)(self + 0xd0),*(undefined4 *)(action + 0x10));
      cVar6 = (**(code **)(*(longlong *)action + 0x2c8))
                        (action,*(undefined8 *)(*(longlong *)action + 0x2d0));
      if (cVar6 == '\0') {
        plVar14 = *(longlong **)(self + 0x88);
        if (((plVar14 == (longlong *)0x0) ||
            (plVar14 = (longlong *)
                       (**(code **)(*plVar14 + 0x298))(plVar14,*(undefined8 *)(*plVar14 + 0x2a0)),
            plVar14 == (longlong *)0x0)) ||
           (lVar13 = (**(code **)(*plVar14 + 0x1e8))(plVar14,*(undefined8 *)(*plVar14 + 0x1f0)),
           lVar13 == 0)) goto LAB_7ffe9a46278f;
        func_0x7ffe9a4dbd30(lVar13,0xfc);
        if ((*(longlong *)(self + 0xa8) != 0) &&
           (cVar6 = func_0x7ffe9a4ceea0(*(longlong *)(self + 0xa8),0), cVar6 != '\0')) {
          if ((*(longlong *)(self + 0xa8) == 0) ||
             (lVar13 = *(longlong *)(*(longlong *)(self + 0xa8) + 0x30), lVar13 == 0))
          goto LAB_7ffe9a46278f;
          sVar10 = FUN_7ffe9a7f21f0(lVar13,0);
          if (*(int *)(_DAT_7ffe9c94c0a0 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          bVar7 = SkillUtil_CheckSameSkill(action,(int)sVar10,(undefined *)0x0);
          if (bVar7 != 0) {
            if (*(longlong *)(self + 0xa8) == 0) goto LAB_7ffe9a46278f;
            func_0x7ffe9a4115d0(*(longlong *)(self + 0xa8),0);
          }
        }
        iVar12 = (**(code **)(*(longlong *)action + 0x188))
                           (action,*(undefined8 *)(*(longlong *)action + 400));
        if (iVar12 == 0x283) {
          plVar14 = *(longlong **)(self + 0x28);
          if (plVar14 == (longlong *)0x0) goto LAB_7ffe9a46278f;
          if (((*(byte *)(*plVar14 + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
              (*(longlong *)
                (*(longlong *)(*plVar14 + 200) + -8 +
                (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) ||
             ((plVar14 = (longlong *)
                         (**(code **)(*plVar14 + 0x298))(plVar14,*(undefined8 *)(*plVar14 + 0x2a0)),
              plVar14 == (longlong *)0x0 ||
              (((lVar13 = (**(code **)(*plVar14 + 0x1c8))(plVar14,*(undefined8 *)(*plVar14 + 0x1d0))
                , lVar13 == 0 || (*(longlong *)(lVar13 + 0x40) == 0)) ||
               (cVar6 = FUN_7ffe9ad8e670(*(longlong *)(lVar13 + 0x40),0x283), cVar6 != '\0'))))))
          goto LAB_7ffe9a46278f;
        }
        cVar6 = (**(code **)(*(longlong *)action + 0x228))(action);
        if (cVar6 == '\0') {
          *(float *)(self + 0xc0) = *(float *)(action + 0x2c) + *(float *)(self + 0xc0);
          bVar7 = PlayerBattleManager_CheckZeroActionDelay(self,(undefined *)0x0);
          if (bVar7 != 0) {
            *(undefined4 *)(self + 0xc0) = 0;
            if (*(float *)(self + 0xc4) <= 0.0) {
              bVar8 = 0.0 < *(float *)(self + 200);
            }
            else {
              bVar8 = true;
            }
            self[0x6e] = bVar8;
          }
          fVar21 = *(float *)(self + 0xc0);
          if ((0.0 < fVar21) &&
             (self[0x6e] = 1, *(float *)(self + 0xc4) <= fVar21 && fVar21 != *(float *)(self + 0xc4)
             )) {
            lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
            if ((lVar13 == 0) || (lVar13 = FUN_7ffe9a29e310(lVar13,0), lVar13 == 0))
            goto LAB_7ffe9a46278f;
            FUN_7ffe99d24d20(lVar13,1,*(undefined4 *)(self + 0xc0));
          }
          cVar6 = (**(code **)(*(longlong *)action + 0x1f8))
                            (action,*(undefined8 *)(*(longlong *)action + 0x200));
          if (cVar6 != '\0') {
            self[0x6a] = 0;
          }
          if (*(longlong *)(self + 0x48) == 0) goto LAB_7ffe9a46278f;
          cVar6 = FUN_7ffe9a9005a0(*(longlong *)(self + 0x48),0);
          if (cVar6 != '\0') {
            if (self[0xb0] != '\0') {
              uVar9 = (**(code **)(*(longlong *)action + 0x1d8))
                                (action,*(undefined8 *)(*(longlong *)action + 0x1e0));
              self[0xb0] = uVar9;
            }
            iVar12 = (**(code **)(*(longlong *)action + 0x188))
                               (action,*(undefined8 *)(*(longlong *)action + 400));
            if (iVar12 == 0x28f) {
              if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c95c838 + 0x130)) ||
                 (*(longlong *)
                   (*(longlong *)(*(longlong *)action + 200) + -8 +
                   (ulonglong)*(byte *)(_DAT_7ffe9c95c838 + 0x130) * 8) != _DAT_7ffe9c95c838)) {
                FUN_7ffe9996c950(action);
                pcVar4 = (code *)swi(3);
                (*pcVar4)();
                return;
              }
              cVar6 = func_0x7ffe9a66e8f0(action,0);
              if (cVar6 != '\0') {
                lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
                if (lVar13 == 0) goto LAB_7ffe9a46278f;
                FUN_7ffe9a8a75a0(lVar13,0);
              }
            }
            if ((*(longlong *)(self + 0xa8) != 0) &&
               (cVar6 = FUN_7ffe9a7efd70(*(longlong *)(self + 0xa8),0), cVar6 != '\0')) {
              if (*(longlong *)(self + 0xa8) == 0) goto LAB_7ffe9a46278f;
              lVar13 = *(longlong *)(*(longlong *)(self + 0xa8) + 0x28);
              uVar16 = *(undefined8 *)(self + 0x88);
              if (lVar13 == 0) goto LAB_7ffe9a46278f;
              uVar15 = func_0x7ffe9996c920(targetActManager,_DAT_7ffe9c9724e0);
              FUN_7ffe9a7f0890(lVar13,uVar15,uVar16);
              if (*(longlong *)(self + 0xa8) == 0) goto LAB_7ffe9a46278f;
              cVar6 = FUN_7ffe9a7f0020(*(longlong *)(self + 0xa8),0);
              if (cVar6 == '\0') {
                if ((*(longlong *)(self + 0xa8) == 0) ||
                   (lVar13 = *(longlong *)(*(longlong *)(self + 0xa8) + 0x28), lVar13 == 0))
                goto LAB_7ffe9a46278f;
                uVar11 = FUN_7ffe9a7f21f0(lVar13,0);
                self[0xd8] = 1;
                (**(code **)(*(longlong *)self + 0x218))
                          (self,*(undefined8 *)(*(longlong *)self + 0x220));
                uVar17 = (ulonglong)uVar11;
              }
              else {
                lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
                if (lVar13 == 0) goto LAB_7ffe9a46278f;
                FUN_7ffe9a8a75a0(lVar13,0);
                uVar17 = 0;
              }
            }
            cVar6 = func_0x7ffe9a7e1180(self,0);
            if (cVar6 == '\0') {
              iVar12 = (**(code **)(*(longlong *)action + 0x188))
                                 (action,*(undefined8 *)(*(longlong *)action + 400));
              if ((iVar12 != 0x308) || ((short)uVar17 != 0)) {
                plVar14 = *(longlong **)(self + 0x28);
                if (plVar14 == (longlong *)0x0) goto LAB_7ffe9a46278f;
                if ((*(byte *)(*plVar14 + 0x130) < *(byte *)(_DAT_7ffe9c922658 + 0x130)) ||
                   (*(longlong *)
                     (*(longlong *)(*plVar14 + 200) + -8 +
                     (ulonglong)*(byte *)(_DAT_7ffe9c922658 + 0x130) * 8) != _DAT_7ffe9c922658)) {
                  FUN_7ffe9996c950(plVar14);
                  pcVar4 = (code *)swi(3);
                  (*pcVar4)();
                  return;
                }
                FUN_7ffe9a450fb0(plVar14,uVar17,0);
              }
            }
            PlayerBattleManager_PursuitAttack(self,targetActManager,action,(undefined *)0x0);
          }
          iVar12 = (**(code **)(*(longlong *)action + 0x188))
                             (action,*(undefined8 *)(*(longlong *)action + 400));
          if (iVar12 == 0x327) {
            uVar16 = FUN_7ffe9a7fb2c0(0x10,action[0x14],*(undefined8 *)(self + 0x28),0);
            uVar15 = FUN_7ffe9bd98960(self,0);
            (**(code **)(*(longlong *)self + 0x2f8))
                      (self,uVar15,*(undefined8 *)(self + 0x28),uVar16,
                       *(undefined8 *)(*(longlong *)self + 0x300));
            uVar15 = FUN_7ffe9bd98960(self,0);
            (**(code **)(*(longlong *)self + 0x368))
                      (self,uVar15,*(undefined8 *)(self + 0x28),uVar16,
                       *(undefined8 *)(*(longlong *)self + 0x370));
            uVar15 = FUN_7ffe9bd98960(self,0);
            (**(code **)(*(longlong *)self + 0x348))
                      (self,uVar15,*(undefined8 *)(self + 0x28),uVar16,
                       *(undefined8 *)(*(longlong *)self + 0x350));
            lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
            if (lVar13 == 0) goto LAB_7ffe9a46278f;
            FUN_7ffe9a89e600(lVar13,uVar16);
          }
        }
        else {
          iVar12 = (**(code **)(*(longlong *)action + 0x188))
                             (action,*(undefined8 *)(*(longlong *)action + 400));
          if (iVar12 == 0x205) {
            fVar21 = *(float *)(action + 0x2c);
            if (DAT_7ffe9caddcfd == '\0') {
              FUN_7ffe9996d590(&DAT_7ffe9c956ad0);
              DAT_7ffe9caddcfd = '\x01';
            }
            fVar21 = fVar21 + *(float *)(self + 0xc0);
            *(float *)(self + 0xc0) = fVar21;
            if ((0.0 < fVar21) &&
               (self[0x6e] = 1,
               *(float *)(self + 0xc4) <= fVar21 && fVar21 != *(float *)(self + 0xc4))) {
              lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
              if ((lVar13 == 0) || (lVar13 = FUN_7ffe9a29e310(lVar13,0), lVar13 == 0))
              goto LAB_7ffe9a46278f;
              FUN_7ffe99d24d20(lVar13,1,*(undefined4 *)(self + 0xc0));
            }
          }
          cVar6 = func_0x7ffe9a7e1180(self,0);
          if (cVar6 == '\0') {
            if (*(longlong *)(self + 0x48) == 0) goto LAB_7ffe9a46278f;
            cVar6 = FUN_7ffe9a9005a0(*(longlong *)(self + 0x48),0);
            if (cVar6 != '\0') {
              if (self[0xb0] != '\0') {
                uVar9 = (**(code **)(*(longlong *)action + 0x1d8))
                                  (action,*(undefined8 *)(*(longlong *)action + 0x1e0));
                self[0xb0] = uVar9;
              }
              sVar10 = 0;
              if (*(longlong *)(self + 0x48) == 0) goto LAB_7ffe9a46278f;
              cVar6 = FUN_7ffe9a9005a0(*(longlong *)(self + 0x48),0);
              if (((cVar6 != '\0') && (*(longlong *)(self + 0xa8) != 0)) &&
                 (cVar6 = FUN_7ffe9a7efd70(*(longlong *)(self + 0xa8),0), cVar6 != '\0')) {
                if (*(longlong *)(self + 0x48) == 0) goto LAB_7ffe9a46278f;
                uVar16 = *(undefined8 *)(*(longlong *)(self + 0x48) + 0x18);
                if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                  func_0x7ffe9996d830();
                }
                cVar6 = FUN_7ffe9bda2160(uVar16,0,0);
                if (cVar6 != '\0') {
                  if ((*(longlong *)(self + 0x48) == 0) ||
                     (lVar13 = *(longlong *)(*(longlong *)(self + 0x48) + 0x18), lVar13 == 0))
                  goto LAB_7ffe9a46278f;
                  uVar17 = FUN_7ffe9ab9c3a0(lVar13,_DAT_7ffe9c962758);
                }
                if ((*(longlong *)(self + 0xa8) == 0) ||
                   (lVar13 = *(longlong *)(*(longlong *)(self + 0xa8) + 0x28), lVar13 == 0))
                goto LAB_7ffe9a46278f;
                FUN_7ffe9a7f0890(lVar13,uVar17,*(undefined8 *)(self + 0x88),0);
                if (*(longlong *)(self + 0xa8) == 0) goto LAB_7ffe9a46278f;
                cVar6 = FUN_7ffe9a7f0020(*(longlong *)(self + 0xa8),0);
                if (cVar6 == '\0') {
                  if ((*(longlong *)(self + 0xa8) == 0) ||
                     (lVar13 = *(longlong *)(*(longlong *)(self + 0xa8) + 0x28), lVar13 == 0))
                  goto LAB_7ffe9a46278f;
                  sVar10 = FUN_7ffe9a7f21f0(lVar13,0);
                  self[0xd8] = 1;
                  (**(code **)(*(longlong *)self + 0x218))
                            (self,*(undefined8 *)(*(longlong *)self + 0x220));
                }
                else {
                  lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
                  if (lVar13 == 0) goto LAB_7ffe9a46278f;
                  FUN_7ffe9a8a75a0(lVar13,0);
                  sVar10 = 0;
                }
              }
              if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c9228b0 + 0x130)) ||
                 (*(longlong *)
                   (*(longlong *)(*(longlong *)action + 200) + -8 +
                   (ulonglong)*(byte *)(_DAT_7ffe9c9228b0 + 0x130) * 8) != _DAT_7ffe9c9228b0))
              goto LAB_7ffe9a46278f;
              iVar12 = (**(code **)(*(longlong *)action + 0x588))
                                 (action,*(undefined8 *)(*(longlong *)action + 0x590));
              bVar8 = true;
              if ((iVar12 == 0x18) && (bVar8 = true, sVar10 == 0)) {
                bVar8 = false;
              }
              plVar14 = *(longlong **)(self + 0x88);
              if (((plVar14 == (longlong *)0x0) ||
                  (plVar14 = (longlong *)
                             (**(code **)(*plVar14 + 0x298))
                                       (plVar14,*(undefined8 *)(*plVar14 + 0x2a0)),
                  plVar14 == (longlong *)0x0)) ||
                 (lVar13 = (**(code **)(*plVar14 + 0x1c8))
                                     (plVar14,*(undefined8 *)(*plVar14 + 0x1d0)), lVar13 == 0))
              goto LAB_7ffe9a46278f;
              cVar6 = FUN_7ffe9a7c6d00(lVar13,0x36e);
              if (((cVar6 == '\0') || (sVar10 != 0)) && (bVar8)) {
                plVar14 = *(longlong **)(self + 0x28);
                if (plVar14 == (longlong *)0x0) goto LAB_7ffe9a46278f;
                if ((*(byte *)(*plVar14 + 0x130) < *(byte *)(_DAT_7ffe9c922658 + 0x130)) ||
                   (*(longlong *)
                     (*(longlong *)(*plVar14 + 200) + -8 +
                     (ulonglong)*(byte *)(_DAT_7ffe9c922658 + 0x130) * 8) != _DAT_7ffe9c922658)) {
                  FUN_7ffe9996c950(plVar14);
LAB_7ffe9a4627b0:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4627b5:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4627ba:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4627bf:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4627c4:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4627c9:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4627ce:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4627d3:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4627d8:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4627dd:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4627e2:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4627e7:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4627ec:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4627f1:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4627f6:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4627fb:
                  FUN_7ffe9996d7a0();
                  FUN_7ffe998fa550();
                  pcVar4 = (code *)swi(3);
                  (*pcVar4)();
                  return;
                }
                FUN_7ffe9a450fb0(plVar14,sVar10);
              }
            }
          }
        }
        (**(code **)(*(longlong *)self + 600))(self,*(undefined8 *)(*(longlong *)self + 0x260));
        func_0x7ffe9a8fe300(action,0);
        iVar12 = (**(code **)(*(longlong *)action + 0x188))
                           (action,*(undefined8 *)(*(longlong *)action + 400));
        if (iVar12 != 8) {
          lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
          if (lVar13 == 0) goto LAB_7ffe9a46278f;
          FUN_7ffe9a89e8a0(lVar13,*(undefined8 *)(self + 0x20),action,0);
        }
        iVar12 = (**(code **)(*(longlong *)action + 0x188))
                           (action,*(undefined8 *)(*(longlong *)action + 400));
        if (iVar12 == 0x65) {
          FUN_7ffe9a8fd7f0(action,0);
          PlayerBattleManager_AddReconnectionActionEnd(self,action,(undefined *)0x0);
          lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
          if (lVar13 == 0) goto LAB_7ffe9a46278f;
          FUN_7ffe9a89e600(lVar13,action);
        }
        iVar12 = (**(code **)(*(longlong *)action + 0x188))
                           (action,*(undefined8 *)(*(longlong *)action + 400));
        if (iVar12 == 0x2a5) {
          FUN_7ffe9a8fd7f0(action,0);
          PlayerBattleManager_AddReconnectionActionEnd(self,action,(undefined *)0x0);
          lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
          if (lVar13 == 0) goto LAB_7ffe9a46278f;
          FUN_7ffe9a89e600(lVar13,action,0);
        }
      }
      else {
        iVar12 = (**(code **)(*(longlong *)action + 0x188))
                           (action,*(undefined8 *)(*(longlong *)action + 400));
        if (iVar12 != 0x11) {
          if (*(longlong *)(action + 0x80) == 0) goto LAB_7ffe9a46278f;
          FUN_7ffe9af836a0(&uStack_e8,*(longlong *)(action + 0x80),_DAT_7ffe9c9136f8);
          uVar5 = _DAT_7ffe9c049b18;
          uStack_d0 = uStack_e8;
          puStack_c8 = puStack_e0;
          lStack_c0 = lStack_d8;
          uStack_e8 = 0;
          puStack_e0 = &uStack_d0;
          while (cVar6 = FUN_7ffe9ae28ed0(&uStack_d0,_DAT_7ffe9c91b380), lVar13 = lStack_c0,
                cVar6 != '\0') {
            cVar6 = '\x01';
            while (cVar6 != '\0') {
              lVar18 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
              if (lVar18 == 0) goto LAB_7ffe9a4627fb;
              uVar9 = FUN_7ffe9a8b14d0(lVar18,0);
              if (lVar13 == 0) goto LAB_7ffe9a4627f6;
              lVar18 = *(longlong *)(lVar13 + 0x10);
              uVar16 = FUN_7ffe9bd98960(self,0);
              if (lVar18 == 0) goto LAB_7ffe9a4627f1;
              FUN_7ffe99744ed0(0xe,lVar18,uVar16,action,*(undefined8 *)(lVar13 + 0x38),uVar9);
              if (*(longlong *)(lVar13 + 0x38) == 0) goto LAB_7ffe9a4627ec;
              if (*(char *)(*(longlong *)(lVar13 + 0x38) + 0x38) == '\0') {
                iVar12 = (**(code **)(*(longlong *)action + 0x188))
                                   (action,*(undefined8 *)(*(longlong *)action + 400));
                if (iVar12 == 10) {
                  if (*(longlong *)(lVar13 + 0x38) == 0) goto LAB_7ffe9a4627e2;
                  uVar1 = *(undefined4 *)(*(longlong *)(lVar13 + 0x38) + 0x10);
                  if (*(int *)(_DAT_7ffe9c941198 + 0xe0) == 0) {
                    func_0x7ffe9996d830();
                  }
                  FUN_7ffe9a7dd820(1,uVar1,0);
                }
                else {
                  iVar12 = (**(code **)(*(longlong *)action + 0x188))
                                     (action,*(undefined8 *)(*(longlong *)action + 400));
                  if ((iVar12 == 0xb) ||
                     (iVar12 = (**(code **)(*(longlong *)action + 0x188))
                                         (action,*(undefined8 *)(*(longlong *)action + 400)),
                     iVar12 == 0xc)) {
                    if (*(longlong *)(lVar13 + 0x38) == 0) goto LAB_7ffe9a4627c4;
                    uVar1 = *(undefined4 *)(*(longlong *)(lVar13 + 0x38) + 0x10);
                    if (*(int *)(_DAT_7ffe9c941198 + 0xe0) == 0) {
                      func_0x7ffe9996d830();
                    }
                    FUN_7ffe9a7dcb00(uVar1,action,0);
                  }
                  else {
                    uVar1 = *(undefined4 *)(lVar13 + 0x1c);
                    if (*(longlong *)(lVar13 + 0x38) == 0) goto LAB_7ffe9a4627bf;
                    uVar2 = *(undefined4 *)(*(longlong *)(lVar13 + 0x38) + 0x10);
                    plVar14 = *(longlong **)(self + 0x88);
                    if (plVar14 == (longlong *)0x0) goto LAB_7ffe9a4627ba;
                    plVar14 = (longlong *)
                              (**(code **)(*plVar14 + 0x298))
                                        (plVar14,*(undefined8 *)(*plVar14 + 0x2a0));
                    if (plVar14 == (longlong *)0x0) goto LAB_7ffe9a4627b5;
                    lVar18 = (**(code **)(*plVar14 + 0x178))
                                       (plVar14,*(undefined8 *)(*plVar14 + 0x180));
                    if (lVar18 == 0) goto LAB_7ffe9a4627b0;
                    uVar3 = *(undefined4 *)(lVar18 + 0x14);
                    if (*(int *)(_DAT_7ffe9c941198 + 0xe0) == 0) {
                      func_0x7ffe9996d830();
                    }
                    FUN_7ffe9a7dcf30(uVar1,1,uVar2,uVar3,action,0);
                  }
                }
                lVar18 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
                uVar1 = *(undefined4 *)(lVar13 + 0x1c);
                if (*(longlong *)(lVar13 + 0x38) == 0) goto LAB_7ffe9a4627dd;
                uVar2 = *(undefined4 *)(*(longlong *)(lVar13 + 0x38) + 0x10);
                lVar19 = FUN_7ffe9bd98a10(self,0);
                if (lVar19 == 0) goto LAB_7ffe9a4627d8;
                puVar20 = (undefined8 *)FUN_7ffe9bdbf710(auStack_90,lVar19,0);
                uVar16 = *puVar20;
                uVar3 = *(undefined4 *)(puVar20 + 1);
                if (*(longlong *)(lVar13 + 0x10) == 0) goto LAB_7ffe9a4627d3;
                lVar19 = FUN_7ffe9bd98a10(*(longlong *)(lVar13 + 0x10),0);
                if (lVar19 == 0) goto LAB_7ffe9a4627ce;
                puVar20 = (undefined8 *)FUN_7ffe9bdbf710(auStack_80,lVar19,0);
                if (lVar18 == 0) goto LAB_7ffe9a4627c9;
                uStack_b8 = *puVar20;
                uStack_b0 = *(undefined4 *)(puVar20 + 1);
                uStack_a8 = uVar16;
                uStack_a0 = uVar3;
                FUN_7ffe99ca8580(lVar18,uVar1,1,uVar2,&uStack_a8,&uStack_b8,uVar5,
                                 *(undefined1 *)(lVar13 + 0x30),0,0);
              }
              lVar18 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
              if (lVar18 == 0) goto LAB_7ffe9a4627e7;
              FUN_7ffe9a8a0c90(lVar18,action,uVar9);
              cVar6 = FUN_7ffe9a8f6320(lVar13);
            }
          }
          _GetDurationBonusTime_d__7_System_IDisposable_Dispose
                    ((undefined *)&uStack_d0,_DAT_7ffe9c91b2b0);
        }
        if (*(longlong *)(self + 0x48) == 0) goto LAB_7ffe9a46278f;
        cVar6 = FUN_7ffe9a9005a0(*(longlong *)(self + 0x48),0);
        if (cVar6 != '\0') {
          PlayerBattleManager_PursuitAttack(self,targetActManager,action,(undefined *)0x0);
        }
        (**(code **)(*(longlong *)self + 600))(self,*(undefined8 *)(*(longlong *)self + 0x260));
      }
      return;
    }
  }
LAB_7ffe9a46278f:
  FUN_7ffe9996d7a0();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

