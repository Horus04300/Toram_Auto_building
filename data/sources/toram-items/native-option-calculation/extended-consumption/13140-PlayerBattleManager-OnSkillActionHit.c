
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PlayerBattleManager_OnSkillActionHit
               (undefined *self,undefined *target,undefined *targetActManager,undefined *action,
               undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  longlong lVar5;
  undefined8 uVar6;
  longlong lVar7;
  undefined8 *puVar8;
  undefined8 uVar9;
  longlong *plVar10;
  longlong *plVar11;
  undefined4 uVar12;
  undefined1 uVar13;
  undefined8 uStack_b0;
  undefined8 *puStack_a8;
  longlong *plStack_a0;
  undefined8 uStack_98;
  undefined8 *puStack_90;
  longlong *plStack_88;
  undefined8 uStack_80;
  undefined8 *puStack_78;
  longlong *plStack_70;
  undefined8 uStack_68;
  undefined4 uStack_60;
  undefined1 auStack_48 [16];
  
  if (DAT_7ffe9caddcf6 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c941198);
    FUN_7ffe9996d590(&DAT_7ffe9c8f64d8);
    FUN_7ffe9996d590(&DAT_7ffe9c91b2b0);
    FUN_7ffe9996d590(&DAT_7ffe9c8fc188);
    FUN_7ffe9996d590(&DAT_7ffe9c91b380);
    FUN_7ffe9996d590(&DAT_7ffe9c8fc258);
    FUN_7ffe9996d590(0x7ffe9c8fc328);
    FUN_7ffe9996d590(0x7ffe9c91b450);
    FUN_7ffe9996d590(&DAT_7ffe9c9136f8);
    FUN_7ffe9996d590(&DAT_7ffe9c93a898);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c904080);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c956938);
    FUN_7ffe9996d590(&DAT_7ffe9c9632c0);
    DAT_7ffe9caddcf6 = '\x01';
  }
  uStack_80 = 0;
  puStack_78 = (undefined8 *)0x0;
  plStack_70 = (longlong *)0x0;
  uStack_98 = 0;
  puStack_90 = (undefined8 *)0x0;
  plStack_88 = (longlong *)0x0;
  lVar5 = FUN_7ffe9a35c7f0(0);
  if (lVar5 != 0) {
    if (*(char *)(lVar5 + 0x28) != '\0') {
      lVar5 = FUN_7ffe9a35c7f0(0);
      if (lVar5 == 0) goto LAB_7ffe9a463945;
      if (*(char *)(lVar5 + 0x2d) == '\0') {
        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        cVar3 = FUN_7ffe9bda1fa0(target,0);
        if (cVar3 != '\0') {
          return;
        }
        lVar5 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
        if ((target == (undefined *)0x0) || (uVar6 = func_0x7ffe9aaf83a0(target,0), lVar5 == 0))
        goto LAB_7ffe9a463945;
        cVar3 = FUN_7ffe9a337770(lVar5,uVar6);
        if (cVar3 == '\0') {
          return;
        }
      }
    }
    if (action != (undefined *)0x0) {
      cVar3 = (**(code **)(*(longlong *)action + 0x228))
                        (action,*(undefined8 *)(*(longlong *)action + 0x230));
      if (cVar3 != '\0') {
        PlayerBattleManager_OnSkillActionHitToSupport(self,action,(undefined *)0x0);
        return;
      }
      iVar4 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      if ((((iVar4 == 0x225) ||
           (iVar4 = (**(code **)(*(longlong *)action + 0x188))
                              (action,*(undefined8 *)(*(longlong *)action + 400)), iVar4 == 0x226))
          || (iVar4 = (**(code **)(*(longlong *)action + 0x188))
                                (action,*(undefined8 *)(*(longlong *)action + 400)), iVar4 == 0x227)
          ) || (iVar4 = (**(code **)(*(longlong *)action + 0x188))
                                  (action,*(undefined8 *)(*(longlong *)action + 400)),
               iVar4 == 0x228)) {
        PlayerBattleManager_TrapActionHit(self,target,action,(undefined *)0x0);
        return;
      }
      iVar4 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      if (iVar4 == 0) {
        if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c904080 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*(longlong *)action + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c904080 + 0x130) * 8) != _DAT_7ffe9c904080)) {
          FUN_7ffe9996c950(action);
LAB_7ffe9a463954:
          FUN_7ffe9996d7a0();
LAB_7ffe9a463959:
          FUN_7ffe9996d7a0();
LAB_7ffe9a46395e:
          FUN_7ffe9996d7a0();
LAB_7ffe9a463963:
          FUN_7ffe9996d7a0();
          FUN_7ffe998fa550();
LAB_7ffe9a46396f:
          FUN_7ffe9996d7a0();
LAB_7ffe9a463974:
          FUN_7ffe9996d7a0();
LAB_7ffe9a463979:
          FUN_7ffe9996d7a0();
LAB_7ffe9a46397e:
          FUN_7ffe9996d7a0();
LAB_7ffe9a463983:
          FUN_7ffe9996d7a0();
LAB_7ffe9a463988:
          FUN_7ffe9996d7a0();
          FUN_7ffe998fa550();
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        FUN_7ffe9a4975b0(action,*(undefined8 *)(self + 0x28),target,0);
      }
      cVar3 = (**(code **)(*(longlong *)action + 0x218))
                        (action,*(undefined8 *)(*(longlong *)action + 0x220));
      if (cVar3 == '\0') {
        bVar2 = false;
        uVar13 = 0;
        if (*(longlong *)(action + 0x80) != 0) {
          FUN_7ffe9af836a0(&uStack_b0,*(longlong *)(action + 0x80),_DAT_7ffe9c9136f8);
          uStack_98 = uStack_b0;
          puStack_90 = puStack_a8;
          plStack_88 = plStack_a0;
          uStack_b0 = 0;
          puStack_a8 = &uStack_98;
          while (cVar3 = FUN_7ffe9ae28ed0(&uStack_98,_DAT_7ffe9c91b380), cVar3 != '\0') {
            if (plStack_88 == (longlong *)0x0) goto LAB_7ffe9a463963;
            lVar5 = plStack_88[7];
            if (lVar5 != 0) {
              if (*(int *)((longlong)plStack_88 + 0x1c) == 0) {
                if (*(char *)(lVar5 + 0x3a) == '\0') {
                  if (*(int *)((longlong)plStack_88 + 0x34) == 1) {
                    if (*(int *)(_DAT_7ffe9c941198 + 0xe0) == 0) {
                      func_0x7ffe9996d830();
                    }
                    FUN_7ffe9a7dccb0(0,action,0);
                    lVar5 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
                    if (target == (undefined *)0x0) goto LAB_7ffe9a46395e;
                    lVar7 = FUN_7ffe9bd9b890(target,0);
                    if (lVar7 == 0) goto LAB_7ffe9a463959;
                    puVar8 = (undefined8 *)FUN_7ffe9bdbf710(auStack_48,lVar7,0);
                    if (lVar5 == 0) goto LAB_7ffe9a463954;
                    uStack_68 = *puVar8;
                    uStack_60 = *(undefined4 *)(puVar8 + 1);
                    FUN_7ffe99ca5e50(lVar5,0,&uStack_68,0);
                  }
                  else {
                    FUN_7ffe9974e9b0(0x1e,self,target,targetActManager,action,lVar5,uVar13);
                  }
                }
                iVar4 = (**(code **)(*(longlong *)action + 0x188))
                                  (action,*(undefined8 *)(*(longlong *)action + 400));
                if (iVar4 == 0x289) {
                  bVar2 = true;
                  uVar13 = 1;
                }
              }
              else {
                bVar2 = true;
                uVar13 = 1;
              }
            }
          }
          _GetDurationBonusTime_d__7_System_IDisposable_Dispose
                    ((undefined *)&uStack_98,_DAT_7ffe9c91b2b0);
          if (!bVar2) {
            return;
          }
          goto LAB_7ffe9a4635a5;
        }
      }
      else {
        lVar5 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
        if ((lVar5 != 0) && (lVar5 = FUN_7ffe9a33dc30(lVar5,0), lVar5 != 0)) {
          FUN_7ffe9af836a0(&uStack_b0,lVar5,_DAT_7ffe9c93a898);
          uStack_80 = uStack_b0;
          puStack_78 = puStack_a8;
          plStack_70 = plStack_a0;
          uStack_b0 = 0;
          puStack_a8 = &uStack_80;
LAB_7ffe9a463640:
          do {
            cVar3 = FUN_7ffe9ae28ed0(&uStack_80,_DAT_7ffe9c8fc258);
            plVar10 = plStack_70;
            if (cVar3 == '\0') goto LAB_7ffe9a46388d;
            uVar6 = *(undefined8 *)(self + 0x20);
            if (plStack_70 == (longlong *)0x0) goto LAB_7ffe9a463988;
            uVar9 = FUN_7ffe99742ec0(0x16,_DAT_7ffe9c9724e0,plStack_70);
            uVar12 = FUN_7ffe99744d60(0,_DAT_7ffe9c9724e0,plVar10);
            cVar3 = (**(code **)(*(longlong *)action + 0x4e8))
                              (action,uVar6,uVar9,uVar12,
                               *(undefined8 *)(*(longlong *)action + 0x4f0));
            if (cVar3 != '\0') {
              if ((*(byte *)(*plVar10 + 0x130) < *(byte *)(_DAT_7ffe9c8f64d8 + 0x130)) ||
                 (*(longlong *)
                   (*(longlong *)(*plVar10 + 200) + -8 +
                   (ulonglong)*(byte *)(_DAT_7ffe9c8f64d8 + 0x130) * 8) != _DAT_7ffe9c8f64d8)) {
                bVar2 = false;
              }
              else {
                bVar2 = true;
              }
              plVar11 = (longlong *)0x0;
              if (bVar2) {
                plVar11 = plVar10;
              }
              if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                func_0x7ffe9996d830();
              }
              cVar3 = FUN_7ffe9bda2160(plVar11,0,0);
              if (cVar3 != '\0') {
                if (plVar11 == (longlong *)0x0) goto LAB_7ffe9a46396f;
                cVar3 = (**(code **)(*plVar11 + 0x5d8))
                                  (plVar11,0x200000,*(undefined8 *)(*plVar11 + 0x5e0));
                if (cVar3 != '\0') {
                  uVar6 = FUN_7ffe99742ec0(6,_DAT_7ffe9c9724e0,plVar10);
                  cVar3 = FUN_7ffe9a8fd1d0(action,uVar6,0);
                  if (cVar3 == '\0') {
                    uVar6 = FUN_7ffe99742ec0(6,_DAT_7ffe9c9724e0,plVar10);
                    cVar3 = FUN_7ffe9a8fd0e0(action,uVar6,0);
                    if (cVar3 != '\0') goto LAB_7ffe9a463640;
                  }
                }
              }
              cVar3 = FUN_7ffe99742ec0(2,_DAT_7ffe9c9724e0,plVar10);
              if (cVar3 == '\0') {
                lVar5 = FUN_7ffe9a35c7f0(0);
                if (lVar5 == 0) goto LAB_7ffe9a463983;
                if (*(char *)(lVar5 + 0x28) != '\0') {
                  lVar5 = FUN_7ffe9a35c7f0(0);
                  if (lVar5 == 0) goto LAB_7ffe9a463979;
                  if (*(char *)(lVar5 + 0x2d) == '\0') {
                    lVar5 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
                    uVar6 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c9724e0,plVar10);
                    if (lVar5 == 0) goto LAB_7ffe9a463974;
                    cVar3 = FUN_7ffe9a337770(lVar5,uVar6,0);
                    if (cVar3 == '\0') goto LAB_7ffe9a463640;
                  }
                }
                if (DAT_7ffe9caddcce == '\0') {
                  FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
                  DAT_7ffe9caddcce = '\x01';
                }
                lVar5 = FUN_7ffe9a35c7f0(0);
                if (lVar5 == 0) goto LAB_7ffe9a46397e;
                if (*(char *)(lVar5 + 0x28) == '\0') {
                  FUN_7ffe99742ec0(0x27,_DAT_7ffe9c9724e0,plVar10);
                }
                uVar6 = *(undefined8 *)(self + 0x28);
                uVar9 = FUN_7ffe99742ec0(6,_DAT_7ffe9c9724e0,plVar10);
                FUN_7ffe9a8fc4b0(action,uVar6,uVar9,0);
              }
            }
          } while( true );
        }
      }
    }
  }
LAB_7ffe9a463945:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
LAB_7ffe9a46388d:
  _GetDurationBonusTime_d__7_System_IDisposable_Dispose((undefined *)&uStack_80,_DAT_7ffe9c8fc188);
  func_0x7ffe9a8fe3b0(action,0);
  plVar10 = *(longlong **)(self + 0x88);
  if ((plVar10 != (longlong *)0x0) &&
     (plVar10 = (longlong *)
                (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
     plVar10 != (longlong *)0x0)) {
    (**(code **)(*plVar10 + 0x2c8))(plVar10,*(undefined8 *)(*plVar10 + 0x2d0));
LAB_7ffe9a4635a5:
    (**(code **)(*(longlong *)action + 0x3f8))
              (action,*(undefined8 *)(self + 0x28),target,
               *(undefined8 *)(*(longlong *)action + 0x400));
    return;
  }
  goto LAB_7ffe9a463945;
}

