
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PlayerBattleManager_OnSkillActionSupport
               (undefined *self,undefined *target,undefined *targetActManager,undefined *action,
               undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  undefined2 uVar3;
  int iVar4;
  undefined4 uVar5;
  longlong lVar6;
  longlong lVar7;
  undefined8 uVar8;
  longlong lVar9;
  undefined8 uVar10;
  longlong lStack_e8;
  longlong *plStack_e0;
  longlong lStack_d8;
  longlong lStack_d0;
  longlong lStack_c8;
  undefined8 uStack_c0;
  longlong lStack_b8;
  longlong *plStack_b0;
  longlong lStack_a8;
  longlong lStack_a0;
  longlong *plStack_98;
  longlong lStack_90;
  longlong lStack_88;
  longlong *plStack_80;
  longlong lStack_78;
  
  if (DAT_7ffe9caddcfb == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8fb7f8);
    FUN_7ffe9996d590(&DAT_7ffe9c943310);
    FUN_7ffe9996d590(&DAT_7ffe9c8f2588);
    FUN_7ffe9996d590(&DAT_7ffe9c972718);
    FUN_7ffe9996d590(&DAT_7ffe9c9234f8);
    FUN_7ffe9996d590(&DAT_7ffe9c9727e8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f2658);
    FUN_7ffe9996d590(&DAT_7ffe9c9235c0);
    FUN_7ffe9996d590(0x7ffe9c8f2728);
    FUN_7ffe9996d590(0x7ffe9c9728b8);
    FUN_7ffe9996d590(0x7ffe9c923688);
    FUN_7ffe9996d590(&DAT_7ffe9c963818);
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c93a908);
    FUN_7ffe9996d590(&DAT_7ffe9c955818);
    FUN_7ffe9996d590(&DAT_7ffe9c95b2f0);
    FUN_7ffe9996d590(&DAT_7ffe9c93ac18);
    FUN_7ffe9996d590(&DAT_7ffe9c93fc68);
    FUN_7ffe9996d590(&DAT_7ffe9c91df50);
    FUN_7ffe9996d590(&DAT_7ffe9c91e270);
    FUN_7ffe9996d590(&DAT_7ffe9c91e4c8);
    FUN_7ffe9996d590(&DAT_7ffe9c905820);
    FUN_7ffe9996d590(&DAT_7ffe9c91ddc0);
    FUN_7ffe9996d590(0x7ffe9c91e7e8);
    FUN_7ffe9996d590(&DAT_7ffe9c968140);
    FUN_7ffe9996d590(&DAT_7ffe9c96e998);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c9228b0);
    FUN_7ffe9996d590(&DAT_7ffe9c952a50);
    FUN_7ffe9996d590(&DAT_7ffe9c954a30);
    FUN_7ffe9996d590(&DAT_7ffe9c94f0d8);
    FUN_7ffe9996d590(&DAT_7ffe9c903908);
    FUN_7ffe9996d590(&DAT_7ffe9c9636c0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f6aa0);
    DAT_7ffe9caddcfb = '\x01';
  }
  lStack_b8 = 0;
  plStack_b0 = (longlong *)0x0;
  lStack_a8 = 0;
  lStack_a0 = 0;
  plStack_98 = (longlong *)0x0;
  lStack_90 = 0;
  uStack_c0 = 0;
  lStack_d0 = 0;
  lStack_88 = 0;
  plStack_80 = (longlong *)0x0;
  lStack_78 = 0;
  if (action == (undefined *)0x0) goto LAB_7ffe9a46868b;
  cVar2 = (**(code **)(*(longlong *)action + 0x228))
                    (action,*(undefined8 *)(*(longlong *)action + 0x230));
  if (cVar2 == '\0') {
    return;
  }
  (**(code **)(*(longlong *)action + 0x3f8))
            (action,*(undefined8 *)(self + 0x28),target,*(undefined8 *)(*(longlong *)action + 0x400)
            );
  cVar2 = (**(code **)(*(longlong *)action + 0x218))
                    (action,*(undefined8 *)(*(longlong *)action + 0x220));
  if (cVar2 == '\0') {
    iVar4 = (**(code **)(*(longlong *)action + 0x188))
                      (action,*(undefined8 *)(*(longlong *)action + 400));
    if (iVar4 == 0x401) {
      return;
    }
    iVar4 = (**(code **)(*(longlong *)action + 0x188))
                      (action,*(undefined8 *)(*(longlong *)action + 400));
    if (iVar4 == 0x408) {
      return;
    }
    iVar4 = (**(code **)(*(longlong *)action + 0x188))
                      (action,*(undefined8 *)(*(longlong *)action + 400));
    if (iVar4 == 0x9e) {
      if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c96e998 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*(longlong *)action + 200) + -8 +
           (ulonglong)*(byte *)(_DAT_7ffe9c96e998 + 0x130) * 8) != _DAT_7ffe9c96e998)) {
        FUN_7ffe9996c950(action);
LAB_7ffe9a4686a3:
        FUN_7ffe9996d7a0();
LAB_7ffe9a4686a8:
        FUN_7ffe9996d7a0();
LAB_7ffe9a4686ad:
        FUN_7ffe9996d7a0();
LAB_7ffe9a4686b2:
        FUN_7ffe9996d7a0();
        FUN_7ffe998fa550();
LAB_7ffe9a4686be:
        FUN_7ffe9996d7a0();
LAB_7ffe9a4686c3:
        FUN_7ffe9996d7a0();
LAB_7ffe9a4686c8:
        FUN_7ffe9996d7a0();
LAB_7ffe9a4686cd:
        FUN_7ffe9996d7a0();
LAB_7ffe9a4686d2:
        FUN_7ffe9996d7a0();
LAB_7ffe9a4686d7:
        FUN_7ffe9996d7a0();
        FUN_7ffe998fa550();
LAB_7ffe9a4686e3:
        FUN_7ffe9996d7a0();
LAB_7ffe9a4686e8:
        FUN_7ffe9996d7a0();
LAB_7ffe9a4686ed:
        FUN_7ffe9996d7a0();
LAB_7ffe9a4686f2:
        FUN_7ffe9996d7a0();
LAB_7ffe9a4686f7:
        FUN_7ffe9996d7a0();
        FUN_7ffe998fa550();
LAB_7ffe9a468703:
        FUN_7ffe9996d7a0();
LAB_7ffe9a468708:
        FUN_7ffe9996d7a0();
LAB_7ffe9a46870d:
        FUN_7ffe9996d7a0();
LAB_7ffe9a468712:
        FUN_7ffe9996d7a0();
LAB_7ffe9a468717:
        FUN_7ffe9996d7a0();
        FUN_7ffe998fa550();
LAB_7ffe9a468723:
        FUN_7ffe9996d7a0();
LAB_7ffe9a468728:
        FUN_7ffe9996d7a0();
LAB_7ffe9a46872d:
        FUN_7ffe9996d7a0();
        FUN_7ffe998fa550();
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      if (action[0x130] == '\0') {
        return;
      }
    }
    else {
      iVar4 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      if (iVar4 != 0x65) {
        lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
        if (lVar6 != 0) {
          FUN_7ffe9a89e9d0(lVar6,target,action,0);
          lVar6 = func_0x7ffe9996c920(action,_DAT_7ffe9c93a908);
          if (lVar6 != 0) {
            return;
          }
          if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c9228b0 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(*(longlong *)action + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c9228b0 + 0x130) * 8) != _DAT_7ffe9c9228b0)) {
            FUN_7ffe9996c950(action);
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
          cVar2 = (**(code **)(*(longlong *)action + 0x578))
                            (action,*(undefined8 *)(*(longlong *)action + 0x580));
          if (cVar2 != '\0') {
            return;
          }
          FUN_7ffe9a8fd7f0(action,0);
          lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
          if (lVar6 != 0) {
            FUN_7ffe9a89e600(lVar6,action);
            PlayerBattleManager_AddReconnectionActionEnd(self,action,(undefined *)0x0);
            return;
          }
        }
        goto LAB_7ffe9a46868b;
      }
    }
    lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
    if (lVar6 == 0) {
LAB_7ffe9a46868b:
      FUN_7ffe9996d7a0();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    FUN_7ffe9a89e9d0(lVar6,target,action,0);
  }
  else {
    lVar6 = func_0x7ffe99940040(_DAT_7ffe9c968140);
    FUN_7ffe9af8a010(lVar6,_DAT_7ffe9c91ddc0);
    lStack_c8 = lVar6;
    iVar4 = (**(code **)(*(longlong *)action + 0x188))
                      (action,*(undefined8 *)(*(longlong *)action + 400));
    if (iVar4 == 0x2c7) {
      lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
      if (((lVar7 == 0) || (*(longlong *)(lVar7 + 0x28) == 0)) ||
         (lVar7 = FUN_7ffe9a4e3710(*(longlong *)(lVar7 + 0x28),0), lVar7 == 0))
      goto LAB_7ffe9a46868b;
      FUN_7ffe9af836a0(&lStack_e8,lVar7,_DAT_7ffe9c905820);
      lStack_b8 = lStack_e8;
      plStack_b0 = plStack_e0;
      lStack_a8 = lStack_d8;
      lStack_e8 = 0;
      plStack_e0 = &lStack_b8;
      while (cVar2 = FUN_7ffe9ae28ed0(&lStack_b8,_DAT_7ffe9c9727e8), lVar7 = lStack_a8,
            cVar2 != '\0') {
        if (lStack_a8 == 0) goto LAB_7ffe9a4686b2;
        if (*(char *)(lStack_a8 + 0x30) == '\0') {
          if (lVar6 == 0) goto LAB_7ffe9a4686ad;
          if (0xe < *(int *)(lVar6 + 0x18)) {
            _GetDurationBonusTime_d__7_System_IDisposable_Dispose
                      ((undefined *)&lStack_b8,_DAT_7ffe9c972718);
            goto LAB_7ffe9a467d43;
          }
          uVar8 = *(undefined8 *)(lStack_a8 + 0x10);
          if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          cVar2 = FUN_7ffe9bda1fa0(uVar8,0,0);
          if (cVar2 == '\0') {
            uVar8 = FUN_7ffe9a4e32b0(lVar7,0);
            if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            cVar2 = FUN_7ffe9bda1fa0(uVar8,0,0);
            if (cVar2 == '\0') {
              lVar9 = FUN_7ffe9a4e32b0(lVar7,0);
              if (lVar9 == 0) goto LAB_7ffe9a4686a8;
              cVar2 = FUN_7ffe99b1ccd0(lVar9,0);
              if (cVar2 != '\0') {
                uVar8 = *(undefined8 *)(self + 0x20);
                if (*(longlong *)(lVar7 + 0x10) == 0) goto LAB_7ffe9a4686a3;
                uVar10 = FUN_7ffe9bd9b890(*(longlong *)(lVar7 + 0x10),0);
                cVar2 = (**(code **)(*(longlong *)action + 0x4e8))
                                  (action,uVar8,uVar10,0,
                                   *(undefined8 *)(*(longlong *)action + 0x4f0));
                if (cVar2 != '\0') {
                  FUN_7ffe99743100(lVar6,*(undefined8 *)(lVar7 + 0x10));
                }
              }
            }
          }
        }
      }
      _GetDurationBonusTime_d__7_System_IDisposable_Dispose
                ((undefined *)&lStack_b8,_DAT_7ffe9c972718);
LAB_7ffe9a467d43:
      lVar7 = FUN_7ffe9b15c270(_DAT_7ffe9c9636c0);
      if (((lVar7 == 0) || (*(longlong *)(lVar7 + 0x30) == 0)) ||
         (lVar7 = FUN_7ffe9acd27a0(*(longlong *)(lVar7 + 0x30),_DAT_7ffe9c943310), lVar7 == 0))
      goto LAB_7ffe9a46868b;
      FUN_7ffe9af415c0(&lStack_e8,lVar7,_DAT_7ffe9c8f6aa0);
      lStack_a0 = lStack_e8;
      plStack_98 = plStack_e0;
      lStack_90 = lStack_d8;
      lStack_e8 = 0;
      plStack_e0 = &lStack_a0;
LAB_7ffe9a467dc0:
      cVar2 = FUN_7ffe9ae37290(&lStack_a0,_DAT_7ffe9c9235c0);
      lVar7 = lStack_90;
      if (cVar2 != '\0') {
        if (lVar6 == 0) goto LAB_7ffe9a4686d7;
        if (0xe < *(int *)(lVar6 + 0x18)) {
          _GetDurationBonusTime_d__7_System_IDisposable_Dispose
                    ((undefined *)&lStack_a0,_DAT_7ffe9c9234f8);
          goto LAB_7ffe9a4684b8;
        }
        if (lStack_90 == 0) goto LAB_7ffe9a4686d2;
        uVar8 = FUN_7ffe9bd98960(lStack_90,0);
        cVar2 = FUN_7ffe9afd70c0(lVar6,uVar8,_DAT_7ffe9c91e270);
        if (cVar2 == '\0') {
          uVar8 = FUN_7ffe9bd98960(lVar7,0);
          if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          cVar2 = FUN_7ffe9bda1fa0(uVar8,0,0);
          if (cVar2 == '\0') {
            if (*(char *)(lVar7 + 0xf0) == '\0') {
              lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
              if (lVar9 == 0) goto LAB_7ffe9a4686c8;
              cVar2 = FUN_7ffe9a5a4650(lVar9,0);
              if (cVar2 != '\0') {
                lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
                uStack_c0 = *(undefined8 *)(lVar7 + 0x48);
                uVar5 = func_0x7ffe9a331500(&uStack_c0,0);
                if (lVar9 == 0) goto LAB_7ffe9a4686c3;
                lVar9 = FUN_7ffe9a59bdd0(lVar9,uVar5,0);
                if (lVar9 != 0) {
                  uVar8 = *(undefined8 *)(lVar9 + 0x20);
                  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                    func_0x7ffe9996d830();
                  }
                  cVar2 = FUN_7ffe9bda2160(uVar8,0,0);
                  if (cVar2 != '\0') {
                    if (*(longlong *)(lVar9 + 0x20) == 0) goto LAB_7ffe9a4686be;
                    cVar2 = FUN_7ffe99b1ccd0(*(longlong *)(lVar9 + 0x20),0);
                    if ((cVar2 == '\0') && (0.0 < (float)*(byte *)(lVar9 + 0x30)))
                    goto LAB_7ffe9a467dc0;
                  }
                }
              }
            }
            uVar8 = FUN_7ffe9a4ca6d0(lVar7,0);
            lVar9 = func_0x7ffe9996c920(uVar8,_DAT_7ffe9c93fc68);
            if ((lVar9 == 0) || (cVar2 = FUN_7ffe99742ec0(9,_DAT_7ffe9c93fc68,lVar9), cVar2 == '\0')
               ) {
              uVar8 = *(undefined8 *)(self + 0x20);
              lVar9 = FUN_7ffe9bd98960(lVar7,0);
              if (lVar9 == 0) goto LAB_7ffe9a4686cd;
              uVar10 = FUN_7ffe9bd9b890(lVar9,0);
              cVar2 = (**(code **)(*(longlong *)action + 0x4e8))
                                (action,uVar8,uVar10,0,*(undefined8 *)(*(longlong *)action + 0x4f0))
              ;
              if (cVar2 != '\0') {
                uVar8 = FUN_7ffe9bd98960(lVar7,0);
                FUN_7ffe99743100(lVar6,uVar8,_DAT_7ffe9c91df50);
              }
            }
          }
        }
        goto LAB_7ffe9a467dc0;
      }
      _GetDurationBonusTime_d__7_System_IDisposable_Dispose
                ((undefined *)&lStack_a0,_DAT_7ffe9c9234f8);
    }
    else {
      iVar4 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      if (iVar4 != 0x74) {
        iVar4 = (**(code **)(*(longlong *)action + 0x188))
                          (action,*(undefined8 *)(*(longlong *)action + 400));
        if (iVar4 == 0x461) {
          return;
        }
        uVar5 = (**(code **)(*(longlong *)action + 0x188))
                          (action,*(undefined8 *)(*(longlong *)action + 400));
        if (*(int *)(_DAT_7ffe9c94f0d8 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        cVar2 = FUN_7ffe9a83a450(uVar5,0);
        if (cVar2 != '\0') {
          lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
          if ((lVar7 == 0) || (lVar7 = FUN_7ffe9a5a46f0(lVar7,0), lVar7 == 0))
          goto LAB_7ffe9a46868b;
          lStack_d0 = FUN_7ffe99742ec0(0,_DAT_7ffe9c955818,lVar7);
          lStack_e8 = 0;
          plStack_e0 = &lStack_d0;
          while (lStack_d0 != 0) {
            cVar2 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ac18);
            if (cVar2 == '\0') {
              if (lStack_d0 != 0) {
                FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
              }
              lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
              uVar3 = (**(code **)(*(longlong *)action + 0x188))
                                (action,*(undefined8 *)(*(longlong *)action + 400));
              if (lVar7 != 0) {
                FUN_7ffe9a89e0f0(lVar7,lVar6,uVar3,action[0x10],1,0);
                iVar4 = (**(code **)(*(longlong *)action + 0x188))
                                  (action,*(undefined8 *)(*(longlong *)action + 400));
                if (iVar4 != 0x303) {
                  return;
                }
                FUN_7ffe9a83a910(*(undefined8 *)(self + 0x88),0);
                return;
              }
              goto LAB_7ffe9a46868b;
            }
            if (lStack_d0 == 0) goto LAB_7ffe9a468712;
            lVar7 = FUN_7ffe99742ec0(0,_DAT_7ffe9c95b2f0);
            if (lVar7 == 0) goto LAB_7ffe9a46870d;
            if (*(int *)(lVar7 + 0x48) == 1) {
              uVar8 = *(undefined8 *)(lVar7 + 0x50);
              if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                func_0x7ffe9996d830();
              }
              cVar2 = FUN_7ffe9bda1fa0(uVar8,0,0);
              if ((cVar2 == '\0') && (cVar2 = FUN_7ffe9a5b8c90(lVar7,0), cVar2 == '\0')) {
                if (lVar6 == 0) goto LAB_7ffe9a468708;
                if (*(int *)(lVar6 + 0x18) < 3) {
                  uVar8 = *(undefined8 *)(self + 0x20);
                  if (*(longlong *)(lVar7 + 0x50) == 0) goto LAB_7ffe9a468703;
                  uVar10 = FUN_7ffe9bd9b890(*(longlong *)(lVar7 + 0x50),0);
                  cVar2 = (**(code **)(*(longlong *)action + 0x4e8))
                                    (action,uVar8,uVar10,0,
                                     *(undefined8 *)(*(longlong *)action + 0x4f0));
                  if (cVar2 != '\0') {
                    FUN_7ffe99743100(lVar6,*(undefined8 *)(lVar7 + 0x50),_DAT_7ffe9c91df50);
                  }
                }
              }
            }
          }
          goto LAB_7ffe9a468717;
        }
        lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
        if ((lVar7 == 0) || (lVar7 = FUN_7ffe9a5a46f0(lVar7,0), lVar7 == 0)) goto LAB_7ffe9a46868b;
        lStack_d0 = FUN_7ffe99742ec0(0,_DAT_7ffe9c955818,lVar7);
        lStack_e8 = 0;
        plStack_e0 = &lStack_d0;
        while (lStack_d0 != 0) {
          cVar2 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ac18);
          if (cVar2 == '\0') {
            if (lStack_d0 != 0) {
              FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
            }
            goto LAB_7ffe9a4684b8;
          }
          if (lStack_d0 == 0) goto LAB_7ffe9a4686f2;
          lVar7 = FUN_7ffe99742ec0(0,_DAT_7ffe9c95b2f0);
          if (lVar7 == 0) goto LAB_7ffe9a4686ed;
          if (*(int *)(lVar7 + 0x48) == 1) {
            uVar8 = *(undefined8 *)(lVar7 + 0x50);
            if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            cVar2 = FUN_7ffe9bda1fa0(uVar8,0,0);
            if ((cVar2 == '\0') && (cVar2 = FUN_7ffe9a5b8c90(lVar7,0), cVar2 == '\0')) {
              if (lVar6 == 0) goto LAB_7ffe9a4686e8;
              if (*(int *)(lVar6 + 0x18) < 3) {
                uVar8 = *(undefined8 *)(self + 0x20);
                if (*(longlong *)(lVar7 + 0x50) == 0) goto LAB_7ffe9a4686e3;
                uVar10 = FUN_7ffe9bd9b890(*(longlong *)(lVar7 + 0x50),0);
                cVar2 = (**(code **)(*(longlong *)action + 0x4e8))
                                  (action,uVar8,uVar10,0,
                                   *(undefined8 *)(*(longlong *)action + 0x4f0));
                if (cVar2 != '\0') {
                  FUN_7ffe99743100(lVar6,*(undefined8 *)(lVar7 + 0x50),_DAT_7ffe9c91df50);
                }
              }
            }
          }
        }
        goto LAB_7ffe9a4686f7;
      }
      lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
      if (lVar7 == 0) goto LAB_7ffe9a46868b;
      FUN_7ffe9a89e9d0(lVar7,target,action,0);
    }
LAB_7ffe9a4684b8:
    iVar4 = (**(code **)(*(longlong *)action + 0x188))
                      (action,*(undefined8 *)(*(longlong *)action + 400));
    if (iVar4 == 0x2a5) {
      if (lVar6 == 0) goto LAB_7ffe9a46868b;
      FUN_7ffe9af836a0(&lStack_e8,lVar6,_DAT_7ffe9c91e4c8);
      lStack_88 = lStack_e8;
      plStack_80 = plStack_e0;
      lStack_78 = lStack_d8;
      lStack_e8 = 0;
      plStack_e0 = &lStack_88;
      while (cVar2 = FUN_7ffe9ae28ed0(&lStack_88,_DAT_7ffe9c8f2658), lVar7 = lStack_78,
            cVar2 != '\0') {
        if (lStack_78 == 0) goto LAB_7ffe9a46872d;
        lVar9 = FUN_7ffe9ab9c3a0(lStack_78,_DAT_7ffe9c963818);
        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        cVar2 = FUN_7ffe9bda2160(lVar9,0,0);
        if (cVar2 != '\0') {
          if (lVar9 == 0) goto LAB_7ffe9a468728;
          lVar9 = *(longlong *)(lVar9 + 0x58);
          uVar8 = func_0x7ffe99940040(_DAT_7ffe9c8fb7f8);
          FUN_7ffe9ad35a70(uVar8,lVar9,_DAT_7ffe9c903908,0);
          if (lVar9 == 0) goto LAB_7ffe9a468723;
          FUN_7ffe9a9b7770(lVar9,0x9ebcb8,uVar8,lVar7,0,0,0);
        }
      }
      _GetDurationBonusTime_d__7_System_IDisposable_Dispose
                ((undefined *)&lStack_88,_DAT_7ffe9c8f2588);
    }
    lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
    uVar3 = (**(code **)(*(longlong *)action + 0x188))
                      (action,*(undefined8 *)(*(longlong *)action + 400));
    if (lVar7 == 0) goto LAB_7ffe9a46868b;
    FUN_7ffe9a89e0f0(lVar7,lVar6,uVar3,action[0x10],1,0);
  }
  return;
}

