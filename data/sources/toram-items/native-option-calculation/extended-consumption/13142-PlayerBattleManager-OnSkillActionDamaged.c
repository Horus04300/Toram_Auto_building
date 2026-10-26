
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PlayerBattleManager_OnSkillActionDamaged
               (undefined *self,undefined *target,undefined *targetActManager,undefined *action,
               undefined *damageData,undefined *methodInfo)

{
  undefined4 uVar1;
  undefined4 uVar2;
  code *pcVar3;
  char cVar4;
  undefined1 uVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  longlong lVar11;
  undefined8 uVar12;
  longlong *plVar13;
  longlong *plVar14;
  longlong lVar15;
  undefined8 *puVar16;
  longlong lVar17;
  bool bVar18;
  float fVar19;
  longlong *plStackX_20;
  undefined8 in_stack_ffffffffffffff18;
  undefined8 uVar20;
  undefined7 uVar21;
  undefined8 uStack_a8;
  undefined4 uStack_a0;
  longlong lStack_98;
  undefined4 uStack_90;
  undefined8 uStack_88;
  undefined4 uStack_80;
  undefined4 uStack_78;
  longlong *plStack_70;
  longlong *plStack_68;
  longlong *aplStack_60 [5];
  
  if (DAT_7ffe9caddcf8 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c941198);
    FUN_7ffe9996d590(&DAT_7ffe9c8efe80);
    FUN_7ffe9996d590(&DAT_7ffe9c8f5158);
    FUN_7ffe9996d590(&DAT_7ffe9c92bfa0);
    FUN_7ffe9996d590(&DAT_7ffe9c92c1e0);
    FUN_7ffe9996d590(&DAT_7ffe9c95d5c0);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c904080);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c9228b0);
    FUN_7ffe9996d590(&DAT_7ffe9c923530);
    FUN_7ffe9996d590(&DAT_7ffe9c952a50);
    FUN_7ffe9996d590(&DAT_7ffe9c956938);
    FUN_7ffe9996d590(&DAT_7ffe9c9632c0);
    DAT_7ffe9caddcf8 = '\x01';
  }
  plVar14 = (longlong *)0x0;
  plStack_70 = (longlong *)0x0;
  plStack_68 = (longlong *)0x0;
  aplStack_60[0] = (longlong *)0x0;
  if (action == (undefined *)0x0) goto LAB_7ffe9a461676;
  cVar4 = (**(code **)(*(longlong *)action + 0x218))
                    (action,*(undefined8 *)(*(longlong *)action + 0x220));
  if (cVar4 != '\0') {
    return;
  }
  lVar11 = FUN_7ffe9a35c7f0(0);
  if (lVar11 == 0) goto LAB_7ffe9a461676;
  if (*(char *)(lVar11 + 0x28) != '\0') {
    lVar11 = FUN_7ffe9a35c7f0(0);
    if (lVar11 == 0) goto LAB_7ffe9a461676;
    if (*(char *)(lVar11 + 0x2d) == '\0') {
      lVar11 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
      if ((target == (undefined *)0x0) || (uVar12 = func_0x7ffe9aaf83a0(target,0), lVar11 == 0))
      goto LAB_7ffe9a461676;
      cVar4 = FUN_7ffe9a337770(lVar11,uVar12,0);
      if (cVar4 == '\0') {
        return;
      }
    }
  }
  lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
  if (lVar11 == 0) goto LAB_7ffe9a461676;
  uVar5 = FUN_7ffe9a8b14d0(lVar11,0);
  plStackX_20 = (longlong *)CONCAT71(plStackX_20._1_7_,uVar5);
  iVar7 = FUN_7ffe9a8fde10(action,0);
  bVar18 = iVar7 == 0;
  if (((*(byte *)(_DAT_7ffe9c904080 + 0x130) <= *(byte *)(*(longlong *)action + 0x130)) &&
      (*(longlong *)
        (*(longlong *)(*(longlong *)action + 200) + -8 +
        (ulonglong)*(byte *)(_DAT_7ffe9c904080 + 0x130) * 8) == _DAT_7ffe9c904080)) && (bVar18)) {
    if (damageData == (undefined *)0x0) goto LAB_7ffe9a461676;
    if (damageData[0x3c] != '\0') {
      plVar13 = *(longlong **)(self + 0x88);
      if (((plVar13 == (longlong *)0x0) ||
          (plVar13 = (longlong *)
                     (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0)),
          plVar13 == (longlong *)0x0)) ||
         (lVar11 = (**(code **)(*plVar13 + 0x208))(plVar13,*(undefined8 *)(*plVar13 + 0x210)),
         lVar11 == 0)) goto LAB_7ffe9a461676;
      cVar4 = FUN_7ffe9ab944b0(lVar11,0x90,&plStack_70,_DAT_7ffe9c92bfa0);
      if (cVar4 != '\0') {
        if (plStack_70 == (longlong *)0x0) goto LAB_7ffe9a461676;
        if (*(char *)((longlong)plStack_70 + 0x12) != '\0') {
          iVar7 = (**(code **)(*plStack_70 + 0x1f8))
                            (plStack_70,*(undefined8 *)(*plStack_70 + 0x200));
          uVar10 = (undefined4)((ulonglong)in_stack_ffffffffffffff18 >> 0x20);
          plVar13 = *(longlong **)(self + 0x88);
          if (((plVar13 == (longlong *)0x0) ||
              (plVar13 = (longlong *)
                         (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0)),
              plVar13 == (longlong *)0x0)) ||
             ((lVar11 = (**(code **)(*plVar13 + 0x1f8))(plVar13,*(undefined8 *)(*plVar13 + 0x200)),
              lVar11 == 0 || (*(longlong *)(lVar11 + 0x18) == 0)))) goto LAB_7ffe9a461676;
          iVar8 = func_0x7ffe99c1ed70(*(longlong *)(lVar11 + 0x18),0);
          plVar13 = *(longlong **)(self + 0x88);
          if ((((plVar13 == (longlong *)0x0) ||
               (plVar13 = (longlong *)
                          (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0))
               , plVar13 == (longlong *)0x0)) ||
              (lVar11 = (**(code **)(*plVar13 + 0x1f8))(plVar13,*(undefined8 *)(*plVar13 + 0x200)),
              lVar11 == 0)) || (*(longlong *)(lVar11 + 0x20) == 0)) goto LAB_7ffe9a461676;
          iVar9 = func_0x7ffe99c1ed70(*(longlong *)(lVar11 + 0x20),0);
          if ((*(longlong *)(self + 0x88) == 0) ||
             (lVar11 = FUN_7ffe9bd98a10(*(longlong *)(self + 0x88),0), lVar11 == 0))
          goto LAB_7ffe9a461676;
          plVar13 = (longlong *)FUN_7ffe9bdbf710(&uStack_a8,lVar11,0);
          in_stack_ffffffffffffff18 = CONCAT44(uVar10,iVar9);
          lStack_98 = *plVar13;
          uStack_90 = (undefined4)plVar13[1];
          PlayerAttackBase_ViewPreventedHitReactionIcon
                    ((undefined *)0x1,(undefined *)&lStack_98,iVar7,iVar8,iVar9,(undefined *)0x0);
          goto LAB_7ffe9a4606f0;
        }
      }
      if ((*(longlong *)(self + 0x88) == 0) ||
         (lVar11 = FUN_7ffe9bd98a10(*(longlong *)(self + 0x88),0), lVar11 == 0))
      goto LAB_7ffe9a461676;
      plVar13 = (longlong *)FUN_7ffe9bdbf710(&uStack_a8,lVar11);
      lStack_98 = *plVar13;
      uStack_90 = (undefined4)plVar13[1];
      PlayerAttackBase_ViewPreventedHitReactionIconToGemCart
                ((undefined *)0x1,(undefined *)&lStack_98,(undefined *)0x0);
    }
LAB_7ffe9a4606f0:
    if (damageData[0x3b] != '\0') {
      plVar13 = *(longlong **)(self + 0x88);
      if (((plVar13 == (longlong *)0x0) ||
          (plVar13 = (longlong *)
                     (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0)),
          plVar13 == (longlong *)0x0)) ||
         (lVar11 = (**(code **)(*plVar13 + 0x208))(plVar13,*(undefined8 *)(*plVar13 + 0x210)),
         lVar11 == 0)) goto LAB_7ffe9a461676;
      cVar4 = FUN_7ffe9ab944b0(lVar11,0x91,&plStack_68,_DAT_7ffe9c92c1e0);
      if (cVar4 != '\0') {
        if (plStack_68 == (longlong *)0x0) goto LAB_7ffe9a461676;
        if (*(char *)((longlong)plStack_68 + 0x12) != '\0') {
          iVar7 = (**(code **)(*plStack_68 + 0x1f8))
                            (plStack_68,*(undefined8 *)(*plStack_68 + 0x200));
          uVar10 = (undefined4)((ulonglong)in_stack_ffffffffffffff18 >> 0x20);
          plVar13 = *(longlong **)(self + 0x88);
          if (((plVar13 == (longlong *)0x0) ||
              (plVar13 = (longlong *)
                         (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0)),
              plVar13 == (longlong *)0x0)) ||
             ((lVar11 = (**(code **)(*plVar13 + 0x1f8))(plVar13,*(undefined8 *)(*plVar13 + 0x200)),
              lVar11 == 0 || (*(longlong *)(lVar11 + 0x18) == 0)))) goto LAB_7ffe9a461676;
          iVar8 = func_0x7ffe99c1ed70(*(longlong *)(lVar11 + 0x18),0);
          plVar13 = *(longlong **)(self + 0x88);
          if (((plVar13 == (longlong *)0x0) ||
              (plVar13 = (longlong *)
                         (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0)),
              plVar13 == (longlong *)0x0)) ||
             ((lVar11 = (**(code **)(*plVar13 + 0x1f8))(plVar13,*(undefined8 *)(*plVar13 + 0x200)),
              lVar11 == 0 || (*(longlong *)(lVar11 + 0x20) == 0)))) goto LAB_7ffe9a461676;
          iVar9 = func_0x7ffe99c1ed70(*(longlong *)(lVar11 + 0x20),0);
          if ((*(longlong *)(self + 0x88) == 0) ||
             (lVar11 = FUN_7ffe9bd98a10(*(longlong *)(self + 0x88),0), lVar11 == 0))
          goto LAB_7ffe9a461676;
          plVar13 = (longlong *)FUN_7ffe9bdbf710(&uStack_a8,lVar11,0);
          in_stack_ffffffffffffff18 = CONCAT44(uVar10,iVar9);
          lStack_98 = *plVar13;
          uStack_90 = (undefined4)plVar13[1];
          PlayerAttackBase_ViewPreventedHitReactionIcon
                    ((undefined *)0x2,(undefined *)&lStack_98,iVar7,iVar8,iVar9,(undefined *)0x0);
          goto LAB_7ffe9a460908;
        }
      }
      if ((*(longlong *)(self + 0x88) == 0) ||
         (lVar11 = FUN_7ffe9bd98a10(*(longlong *)(self + 0x88),0), lVar11 == 0))
      goto LAB_7ffe9a461676;
      plVar13 = (longlong *)FUN_7ffe9bdbf710(&uStack_a8,lVar11);
      lStack_98 = *plVar13;
      uStack_90 = (undefined4)plVar13[1];
      PlayerAttackBase_ViewPreventedHitReactionIconToGemCart
                ((undefined *)0x2,(undefined *)&lStack_98,(undefined *)0x0);
    }
  }
LAB_7ffe9a460908:
  lVar11 = func_0x7ffe9996c920(targetActManager,_DAT_7ffe9c9724e0);
  lStack_98 = lVar11;
  if (lVar11 != 0) {
    cVar4 = FUN_7ffe99742ec0(0x14,_DAT_7ffe9c9724e0,lVar11);
    if (cVar4 == '\0') {
      cVar4 = FUN_7ffe99742ec0(0x29,_DAT_7ffe9c9724e0,lVar11);
      if (cVar4 == '\0') goto LAB_7ffe9a460e3e;
      if (damageData == (undefined *)0x0) goto LAB_7ffe9a461676;
      func_0x7ffe9a900040(damageData,0,0);
      *(undefined4 *)(damageData + 0x14) = 1;
      FUN_7ffe9a8ffe30(damageData,0,0,0);
      if (damageData[0x39] == '\0') {
        plVar14 = *(longlong **)(self + 0x88);
        uVar10 = *(undefined4 *)(damageData + 0x10);
        if ((plVar14 == (longlong *)0x0) ||
           (plVar14 = (longlong *)
                      (**(code **)(*plVar14 + 0x298))(plVar14,*(undefined8 *)(*plVar14 + 0x2a0)),
           plVar14 == (longlong *)0x0)) goto LAB_7ffe9a461676;
        lVar11 = (**(code **)(*plVar14 + 0x178))(plVar14,*(undefined8 *)(*plVar14 + 0x180));
        if (lVar11 == 0) goto LAB_7ffe9a461676;
        uVar1 = *(undefined4 *)(lVar11 + 0x14);
        if (*(int *)(_DAT_7ffe9c941198 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        FUN_7ffe9a7dcf30(0,1,uVar10,uVar1,action,0);
      }
      lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
      uVar10 = *(undefined4 *)(damageData + 0x10);
      lVar15 = FUN_7ffe9bd98a10(self,0);
      if (lVar15 == 0) goto LAB_7ffe9a461676;
      puVar16 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_a8,lVar15,0);
      uVar12 = *puVar16;
      uVar1 = *(undefined4 *)(puVar16 + 1);
      if ((target == (undefined *)0x0) || (lVar15 = FUN_7ffe9bd9b890(target,0), lVar15 == 0))
      goto LAB_7ffe9a461676;
      puVar16 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_a8,lVar15,0);
      if (lVar11 == 0) goto LAB_7ffe9a461676;
      uStack_88 = *puVar16;
      uStack_80 = *(undefined4 *)(puVar16 + 1);
      puVar16 = &uStack_a8;
      uStack_a8 = uVar12;
      uStack_a0 = uVar1;
      FUN_7ffe99ca8580(lVar11,0,1,uVar10,puVar16,&uStack_88,_DAT_7ffe9c049b18,damageData[0x20],0,0);
      if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      cVar4 = FUN_7ffe9bda20c0(targetActManager,0);
      if (cVar4 == '\0') {
        return;
      }
      if (targetActManager == (undefined *)0x0) goto LAB_7ffe9a461676;
      cVar4 = (**(code **)(*(longlong *)targetActManager + 0x1a8))
                        (targetActManager,*(undefined8 *)(*(longlong *)targetActManager + 0x1b0));
      if (cVar4 != '\0') {
        return;
      }
      lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
      if (lVar11 == 0) goto LAB_7ffe9a461676;
      uVar12 = func_0x7ffe9996c920(targetActManager,_DAT_7ffe9c9724e0);
      uVar20 = CONCAT71((int7)((ulonglong)puVar16 >> 8),plStackX_20._0_1_);
      FUN_7ffe9a8a1870(lVar11,uVar12,action,damageData,uVar20,0);
      if (!bVar18) {
        return;
      }
      iVar7 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      if (iVar7 != 0) goto LAB_7ffe9a460c20;
      lVar11 = *(longlong *)action;
      if ((*(byte *)(lVar11 + 0x130) < *(byte *)(_DAT_7ffe9c9228b0 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(lVar11 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c9228b0 + 0x130) * 8)
          != _DAT_7ffe9c9228b0)) goto LAB_7ffe9a460c20;
      if ((*(byte *)(lVar11 + 0x130) < *(byte *)(_DAT_7ffe9c904080 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(lVar11 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c904080 + 0x130) * 8)
          != _DAT_7ffe9c904080)) {
        FUN_7ffe9996c950(action);
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
      uVar21 = (undefined7)((ulonglong)uVar20 >> 8);
      lVar11 = lStack_98;
    }
    else {
      if (damageData == (undefined *)0x0) goto LAB_7ffe9a461676;
      func_0x7ffe9a900040(damageData,0,0);
      *(undefined4 *)(damageData + 0x14) = 1;
      FUN_7ffe9a8ffe30(damageData,0,0,0);
      if (damageData[0x3a] == '\0') {
        lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
        if (((target == (undefined *)0x0) || (lVar17 = FUN_7ffe9bd9b890(target,0), lVar17 == 0)) ||
           (puVar16 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_88,lVar17,0), lVar15 == 0))
        goto LAB_7ffe9a461676;
        uStack_a8 = *puVar16;
        uStack_a0 = *(undefined4 *)(puVar16 + 1);
        FUN_7ffe99ca8d70(lVar15,0,&uStack_a8,0);
      }
      if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      cVar4 = FUN_7ffe9bda20c0(targetActManager,0);
      if (cVar4 == '\0') {
        return;
      }
      if (targetActManager == (undefined *)0x0) goto LAB_7ffe9a461676;
      cVar4 = (**(code **)(*(longlong *)targetActManager + 0x1a8))
                        (targetActManager,*(undefined8 *)(*(longlong *)targetActManager + 0x1b0));
      if (cVar4 != '\0') {
        return;
      }
      lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
      if (lVar15 == 0) goto LAB_7ffe9a461676;
      uVar12 = func_0x7ffe9996c920(targetActManager,_DAT_7ffe9c9724e0);
      uVar20 = CONCAT71((int7)((ulonglong)in_stack_ffffffffffffff18 >> 8),plStackX_20._0_1_);
      FUN_7ffe9a8a1870(lVar15,uVar12,action,damageData,uVar20,0);
      if (!bVar18) {
        return;
      }
      iVar7 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      if (iVar7 != 0) goto LAB_7ffe9a460c20;
      lVar15 = *(longlong *)action;
      if ((*(byte *)(lVar15 + 0x130) < *(byte *)(_DAT_7ffe9c9228b0 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(lVar15 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c9228b0 + 0x130) * 8)
          != _DAT_7ffe9c9228b0)) goto LAB_7ffe9a460c20;
      if ((*(byte *)(lVar15 + 0x130) < *(byte *)(_DAT_7ffe9c904080 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(lVar15 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c904080 + 0x130) * 8)
          != _DAT_7ffe9c904080)) {
        FUN_7ffe9996c950(action);
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
      uVar21 = (undefined7)((ulonglong)uVar20 >> 8);
    }
    FUN_7ffe9a495a10(action,*(undefined8 *)(self + 0x88),lVar11,damageData,CONCAT71(uVar21,bVar18),0
                    );
LAB_7ffe9a460c20:
    FUN_7ffe9a822410(*(undefined8 *)(self + 0x88),action,damageData);
    PlayerBattleManager_ConsumeBuffAttack
              (self,action,(undefined *)(ulonglong)*(uint *)(damageData + 0x14),(undefined *)0x0);
    return;
  }
LAB_7ffe9a460e3e:
  FUN_7ffe9a7a27e0(*(undefined8 *)(self + 0x88),action,targetActManager,damageData,bVar18,0);
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar4 = FUN_7ffe9bda20c0(targetActManager,0);
  if (cVar4 != '\0') {
    FUN_7ffe9bd98960(self,0);
    uVar12 = FUN_7ffe9bd98960(self,0);
    if (targetActManager == (undefined *)0x0) goto LAB_7ffe9a461676;
    FUN_7ffe99744ed0(0xe,targetActManager,uVar12,action,damageData,(ulonglong)plStackX_20 & 0xff);
  }
  iVar7 = (**(code **)(*(longlong *)action + 0x188))
                    (action,*(undefined8 *)(*(longlong *)action + 400));
  if (iVar7 == 0) {
    lVar15 = *(longlong *)action;
    if ((*(byte *)(_DAT_7ffe9c9228b0 + 0x130) <= *(byte *)(lVar15 + 0x130)) &&
       (*(longlong *)
         (*(longlong *)(lVar15 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c9228b0 + 0x130) * 8) ==
        _DAT_7ffe9c9228b0)) {
      if ((*(byte *)(lVar15 + 0x130) < *(byte *)(_DAT_7ffe9c904080 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(lVar15 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c904080 + 0x130) * 8)
          != _DAT_7ffe9c904080)) {
        FUN_7ffe9996c950(action);
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
      FUN_7ffe9a495a10(action,*(undefined8 *)(self + 0x88),lVar11,damageData,bVar18,0);
    }
  }
  iVar7 = (**(code **)(*(longlong *)action + 0x188))
                    (action,*(undefined8 *)(*(longlong *)action + 400));
  if (iVar7 == 300) {
    if (damageData == (undefined *)0x0) goto LAB_7ffe9a461676;
    if (((*(int *)(damageData + 0x18) != 1) && (*(int *)(damageData + 0x14) != 0)) &&
       (damageData[0x20] == '\0')) {
      plVar13 = *(longlong **)(self + 0x88);
      if (((plVar13 == (longlong *)0x0) ||
          (plVar13 = (longlong *)
                     (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0)),
          plVar13 == (longlong *)0x0)) ||
         (lVar15 = (**(code **)(*plVar13 + 0x1c8))(plVar13,*(undefined8 *)(*plVar13 + 0x1d0)),
         lVar15 == 0)) goto LAB_7ffe9a461676;
      cVar4 = FUN_7ffe9a7cbb30(lVar15,0x125,aplStack_60,0);
      if (cVar4 != '\0') {
        if (aplStack_60[0] == (longlong *)0x0) goto LAB_7ffe9a461676;
        if (((*(byte *)(*aplStack_60[0] + 0x130) < *(byte *)(_DAT_7ffe9c8efe80 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*aplStack_60[0] + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c8efe80 + 0x130) * 8) != _DAT_7ffe9c8efe80)) ||
           (aplStack_60[0] == (longlong *)0x0)) {
          FUN_7ffe9996c950(aplStack_60[0]);
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
        func_0x7ffe9a7814e0(aplStack_60[0],_DAT_7ffe9c049ce4,0);
      }
      damageData[0x74] = 1;
    }
  }
  if ((*(byte *)(_DAT_7ffe9c8f5158 + 0x130) <= *(byte *)(*(longlong *)action + 0x130)) &&
     (*(longlong *)
       (*(longlong *)(*(longlong *)action + 200) + -8 +
       (ulonglong)*(byte *)(_DAT_7ffe9c8f5158 + 0x130) * 8) == _DAT_7ffe9c8f5158)) {
    FUN_7ffe9a6a60e0(*(undefined8 *)(self + 0x88),action,damageData,0);
  }
  FUN_7ffe9a822410(*(undefined8 *)(self + 0x88),action,damageData,0);
  plVar13 = *(longlong **)(self + 0x88);
  if (plVar13 != (longlong *)0x0) {
    uVar12 = (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
    cVar4 = FUN_7ffe9a7b74e0(uVar12,damageData,0);
    if (damageData != (undefined *)0x0) {
      if (cVar4 != '\0') {
        *(uint *)(damageData + 0x70) = *(uint *)(damageData + 0x70) | 0x20000;
        plVar13 = *(longlong **)(self + 0x88);
        if (plVar13 == (longlong *)0x0) goto LAB_7ffe9a461676;
        uVar12 = (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
        FUN_7ffe9a7b7780(uVar12,0);
      }
      if (*(int *)(damageData + 0x18) == 1) {
        *(undefined4 *)(damageData + 0x14) = 0;
      }
      else {
        if (damageData[0x38] == '\0') {
          if (damageData[0x39] == '\0') {
            plVar13 = *(longlong **)(self + 0x88);
            uVar10 = *(undefined4 *)(damageData + 0x10);
            uVar1 = *(undefined4 *)(damageData + 0x14);
            if ((plVar13 == (longlong *)0x0) ||
               (plVar13 = (longlong *)
                          (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0))
               , plVar13 == (longlong *)0x0)) goto LAB_7ffe9a461676;
            lVar11 = (**(code **)(*plVar13 + 0x178))(plVar13,*(undefined8 *)(*plVar13 + 0x180));
            if (lVar11 == 0) goto LAB_7ffe9a461676;
            uVar2 = *(undefined4 *)(lVar11 + 0x14);
            if (*(int *)(_DAT_7ffe9c941198 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            FUN_7ffe9a7dcf30(uVar1,1,uVar10,uVar2,action,0);
          }
          fVar19 = 0.0;
          iVar7 = (**(code **)(*(longlong *)action + 0x188))
                            (action,*(undefined8 *)(*(longlong *)action + 400));
          if (iVar7 == 0x271) {
            bVar6 = func_0x7ffe99fa9c90(action,0);
            fVar19 = (float)bVar6;
          }
          else {
            iVar7 = (**(code **)(*(longlong *)action + 0x188))
                              (action,*(undefined8 *)(*(longlong *)action + 400));
            if (iVar7 == 0x61) {
              uVar5 = func_0x7ffe99fa9c90(action,0);
              if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c95d5c0 + 0x130)) ||
                 (*(longlong *)
                   (*(longlong *)(*(longlong *)action + 200) + -8 +
                   (ulonglong)*(byte *)(_DAT_7ffe9c95d5c0 + 0x130) * 8) != _DAT_7ffe9c95d5c0)) {
                FUN_7ffe9996c950(action,_DAT_7ffe9c95d5c0);
                pcVar3 = (code *)swi(3);
                (*pcVar3)();
                return;
              }
              fVar19 = (float)func_0x7ffe9a6b5860(action,uVar5,0);
            }
          }
          lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
          uVar10 = *(undefined4 *)(damageData + 0x14);
          uStack_78 = *(undefined4 *)(damageData + 0x10);
          lVar15 = FUN_7ffe9bd98a10(self,0);
          if (lVar15 == 0) goto LAB_7ffe9a461676;
          puVar16 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_a8,lVar15,0);
          uVar12 = *puVar16;
          uVar1 = *(undefined4 *)(puVar16 + 1);
          if ((target == (undefined *)0x0) || (lVar15 = FUN_7ffe9bd9b890(target,0), lVar15 == 0))
          goto LAB_7ffe9a461676;
          puVar16 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_88,lVar15,0);
          if (lVar11 == 0) goto LAB_7ffe9a461676;
          uStack_a8 = *puVar16;
          uStack_a0 = *(undefined4 *)(puVar16 + 1);
          uStack_88 = uVar12;
          uStack_80 = uVar1;
          FUN_7ffe99ca8580(lVar11,uVar10,1,uStack_78,&uStack_88,&uStack_a8,_DAT_7ffe9c049b18,
                           damageData[0x20],fVar19,0);
          lVar11 = lStack_98;
        }
        if (0 < *(int *)(damageData + 0x84)) {
          if (targetActManager == (undefined *)0x0) goto LAB_7ffe9a461676;
          cVar4 = (**(code **)(*(longlong *)targetActManager + 0x1a8))
                            (targetActManager,*(undefined8 *)(*(longlong *)targetActManager + 0x1b0)
                            );
          if ((cVar4 == '\0') &&
             (((iVar7 = (**(code **)(*(longlong *)action + 0x188))
                                  (action,*(undefined8 *)(*(longlong *)action + 400)),
               iVar7 != 0x289 || (*(int *)(damageData + 0x84) != 999999999)) &&
              (*(longlong *)(self + 0xa8) != 0)))) {
            FUN_7ffe9a7eee40(*(longlong *)(self + 0xa8),action,*(undefined4 *)(damageData + 0x84),0)
            ;
          }
        }
      }
      lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
      if (lVar15 != 0) {
        uVar12 = func_0x7ffe9996c920(targetActManager,_DAT_7ffe9c9724e0);
        FUN_7ffe9a8a1870(lVar15,uVar12,action,damageData,(ulonglong)plStackX_20 & 0xff,0);
        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        cVar4 = FUN_7ffe9bda20c0(targetActManager,0);
        if (cVar4 != '\0') {
          if (targetActManager == (undefined *)0x0) goto LAB_7ffe9a461676;
          cVar4 = (**(code **)(*(longlong *)targetActManager + 0x1a8))
                            (targetActManager,*(undefined8 *)(*(longlong *)targetActManager + 0x1b0)
                            );
          if (cVar4 == '\0') {
            if (bVar18) {
              PlayerBattleManager_ConsumeBuffAttack
                        (self,action,(undefined *)(ulonglong)*(uint *)(damageData + 0x14),
                         (undefined *)0x0);
            }
            bVar6 = PlayerBattleManager_IsPersuitAction(self,action,(undefined *)0x0);
            if (bVar6 != 0) {
              return;
            }
            PlayerBattleManager_CheckMagicEgelAttackTarget
                      (self,action,targetActManager,(undefined *)0x0);
            PlayerBattleManager_StartHolyBiblePursuitAttack
                      (self,targetActManager,action,(undefined *)0x0);
            if (DAT_7ffe9caddd1c == '\0') {
              FUN_7ffe9996d590(&DAT_7ffe9c9368c8);
              DAT_7ffe9caddd1c = '\x01';
            }
            plVar13 = *(longlong **)(self + 0x88);
            plStackX_20 = (longlong *)0x0;
            if (((plVar13 == (longlong *)0x0) ||
                (plVar13 = (longlong *)
                           (**(code **)(*plVar13 + 0x298))
                                     (plVar13,*(undefined8 *)(*plVar13 + 0x2a0)),
                plVar13 == (longlong *)0x0)) ||
               (lVar15 = (**(code **)(*plVar13 + 0x1c8))(plVar13,*(undefined8 *)(*plVar13 + 0x1d0)),
               lVar15 == 0)) goto LAB_7ffe9a4616b5;
            cVar4 = FUN_7ffe9a7cbb30(lVar15,0x91,&plStackX_20);
            if (cVar4 != '\0') {
              if (plStackX_20 != (longlong *)0x0) {
                if (((*(byte *)(*plStackX_20 + 0x130) < *(byte *)(_DAT_7ffe9c9368c8 + 0x130)) ||
                    (*(longlong *)
                      (*(longlong *)(*plStackX_20 + 200) + -8 +
                      (ulonglong)*(byte *)(_DAT_7ffe9c9368c8 + 0x130) * 8) != _DAT_7ffe9c9368c8)) ||
                   (plVar14 = plStackX_20, plStackX_20 == (longlong *)0x0)) {
                  FUN_7ffe9996c950(plStackX_20);
                  pcVar3 = (code *)swi(3);
                  (*pcVar3)();
                  return;
                }
              }
              iVar7 = (**(code **)(*(longlong *)action + 0x188))
                                (action,*(undefined8 *)(*(longlong *)action + 400));
              if (iVar7 == 0) {
                if (*(longlong *)(self + 0x98) == 0) {
LAB_7ffe9a4616b5:
                  FUN_7ffe9996d7a0();
                  pcVar3 = (code *)swi(3);
                  (*pcVar3)();
                  return;
                }
                if (*(char *)(*(longlong *)(self + 0x98) + 0x80) == '\0') {
                  if (plVar14 == (longlong *)0x0) goto LAB_7ffe9a4616b5;
                  FUN_7ffe9a779e30(plVar14,lVar11,0);
                }
              }
            }
            PlayerBattleManager_StartMagicFinawPursuitAttack
                      (self,targetActManager,action,(undefined *)0x0);
            return;
          }
        }
        cVar4 = (**(code **)(*(longlong *)action + 0x248))
                          (action,*(undefined8 *)(*(longlong *)action + 0x250));
        if (cVar4 != '\0') {
          plVar13 = *(longlong **)(self + 0x30);
          if (plVar13 != (longlong *)0x0) {
            if ((*(byte *)(*plVar13 + 0x130) < *(byte *)(_DAT_7ffe9c923530 + 0x130)) ||
               (*(longlong *)
                 (*(longlong *)(*plVar13 + 200) + -8 +
                 (ulonglong)*(byte *)(_DAT_7ffe9c923530 + 0x130) * 8) != _DAT_7ffe9c923530)) {
              bVar18 = false;
            }
            else {
              bVar18 = true;
            }
            if (bVar18) {
              plVar14 = plVar13;
            }
          }
          if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          cVar4 = FUN_7ffe9bda2160(plVar14,0,0);
          if (cVar4 != '\0') {
            uVar10 = (**(code **)(*(longlong *)action + 0x188))
                               (action,*(undefined8 *)(*(longlong *)action + 400));
            if (plVar14 == (longlong *)0x0) goto LAB_7ffe9a461676;
            FUN_7ffe9a4b4c80(plVar14,uVar10,*(undefined4 *)(action + 0x10),0);
          }
        }
        return;
      }
    }
  }
LAB_7ffe9a461676:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

