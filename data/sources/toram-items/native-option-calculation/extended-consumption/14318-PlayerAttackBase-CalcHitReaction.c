
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
PlayerAttackBase_CalcHitReaction
          (undefined *self,undefined *attackType,undefined *playerAction,undefined *mobAction,
          undefined *resistReactionType,undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  longlong lVar10;
  longlong *plVar11;
  ulonglong uVar12;
  undefined *puVar13;
  undefined8 uVar14;
  longlong *plVar15;
  undefined8 *puVar16;
  undefined4 uVar17;
  float fVar18;
  undefined4 uVar19;
  undefined4 uVar20;
  float fVar21;
  int iStack_a8;
  int iStack_a4;
  int iStack_a0;
  int iStack_9c;
  undefined8 uStack_98;
  undefined4 uStack_90;
  undefined4 auStack_88 [2];
  longlong *plStack_80;
  longlong *plStack_78;
  undefined *puStack_70;
  undefined1 auStack_68 [48];
  
  if (DAT_7ffe9cadded6 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8ff610);
    FUN_7ffe9996d590(&DAT_7ffe9c8f2438);
    FUN_7ffe9996d590(&DAT_7ffe9c91bcc0);
    FUN_7ffe9996d590(&DAT_7ffe9c92bfa0);
    FUN_7ffe9996d590(&DAT_7ffe9c92c1e0);
    FUN_7ffe9996d590(&DAT_7ffe9c93f070);
    FUN_7ffe9996d590(&DAT_7ffe9c9238d0);
    FUN_7ffe9996d590(&DAT_7ffe9c923f10);
    FUN_7ffe9996d590(&DAT_7ffe9c936530);
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c904080);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c8fba08);
    FUN_7ffe9996d590(&DAT_7ffe9c8fbad8);
    FUN_7ffe9996d590(&DAT_7ffe9c910268);
    DAT_7ffe9cadded6 = '\x01';
  }
  *(undefined4 *)resistReactionType = 0;
  auStack_88[0] = 0;
  puStack_70 = (undefined *)0x0;
  iStack_9c = 0;
  if ((mobAction != (undefined *)0x0) &&
     (lVar10 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction), lVar10 != 0)) {
    iStack_a8 = FUN_7ffe99742ec0(8,_DAT_7ffe9c93ed20,lVar10);
    lVar10 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
    if (lVar10 != 0) {
      iVar6 = FUN_7ffe99742ec0(7,_DAT_7ffe9c93ed20,lVar10);
      plStack_78 = (longlong *)0x0;
      if (((playerAction != (undefined *)0x0) &&
          (plVar11 = (longlong *)
                     (**(code **)(*(longlong *)playerAction + 0x298))
                               (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
          plVar11 != (longlong *)0x0)) &&
         (lVar10 = (**(code **)(*plVar11 + 0x208))(plVar11,*(undefined8 *)(*plVar11 + 0x210)),
         lVar10 != 0)) {
        cVar4 = FUN_7ffe9ab944b0(lVar10,0x90,&plStack_78,_DAT_7ffe9c92bfa0);
        iStack_a4 = 0;
        if (cVar4 != '\0') {
          if (plStack_78 == (longlong *)0x0) goto LAB_7ffe9a4aa8b6;
          iStack_a4 = 0;
          if (*(char *)((longlong)plStack_78 + 0x12) != '\0') {
            iStack_a4 = (int)(short)plStack_78[2];
          }
        }
        plVar11 = (longlong *)
                  (**(code **)(*(longlong *)playerAction + 0x298))
                            (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if ((plVar11 != (longlong *)0x0) &&
           (lVar10 = (**(code **)(*plVar11 + 0x218))(plVar11,*(undefined8 *)(*plVar11 + 0x220)),
           lVar10 != 0)) {
          cVar4 = FUN_7ffe9a5b20c0(lVar10,0x46,0);
          fVar21 = _DAT_7ffe9c049b18;
          if (cVar4 != '\0') {
            plVar11 = (longlong *)
                      (**(code **)(*(longlong *)playerAction + 0x298))
                                (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
            if ((plVar11 == (longlong *)0x0) ||
               (lVar10 = (**(code **)(*plVar11 + 0x218))(plVar11,*(undefined8 *)(*plVar11 + 0x220)),
               lVar10 == 0)) goto LAB_7ffe9a4aa8b6;
            iVar7 = FUN_7ffe9a5b2120(lVar10,0x46,0);
            if (0 < iVar7) {
              plVar11 = (longlong *)
                        (**(code **)(*(longlong *)playerAction + 0x298))
                                  (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
              if ((plVar11 == (longlong *)0x0) ||
                 (lVar10 = (**(code **)(*plVar11 + 0x1f8))
                                     (plVar11,*(undefined8 *)(*plVar11 + 0x200)), lVar10 == 0))
              goto LAB_7ffe9a4aa8b6;
              iVar8 = FUN_7ffe99c09050(lVar10,0);
              if (iVar8 == 10) {
                plVar11 = (longlong *)
                          (**(code **)(*(longlong *)playerAction + 0x298))
                                    (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)
                                    );
                if ((plVar11 == (longlong *)0x0) ||
                   (lVar10 = (**(code **)(*plVar11 + 0x1f8))
                                       (plVar11,*(undefined8 *)(*plVar11 + 0x200)), lVar10 == 0))
                goto LAB_7ffe9a4aa8b6;
                iVar8 = FUN_7ffe99c08f50(lVar10,0);
                fVar18 = fVar21;
                if (iVar8 == 0x11) {
                  fVar18 = _DAT_7ffe9c049b74;
                }
                iStack_a4 = iStack_a4 + (int)((float)iVar7 * fVar18);
              }
            }
          }
          if (100 < iStack_a4) {
            iStack_a4 = 100;
          }
          plStack_80 = (longlong *)0x0;
          plVar11 = (longlong *)
                    (**(code **)(*(longlong *)playerAction + 0x298))
                              (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
          if ((plVar11 != (longlong *)0x0) &&
             (lVar10 = (**(code **)(*plVar11 + 0x208))(plVar11,*(undefined8 *)(*plVar11 + 0x210)),
             lVar10 != 0)) {
            cVar4 = FUN_7ffe9ab944b0(lVar10,0x91,&plStack_80,_DAT_7ffe9c92c1e0);
            iVar7 = 0;
            if (cVar4 != '\0') {
              if (plStack_80 == (longlong *)0x0) goto LAB_7ffe9a4aa8b6;
              iVar7 = 0;
              if (*(char *)((longlong)plStack_80 + 0x12) != '\0') {
                iVar7 = (int)(short)plStack_80[2];
              }
            }
            plVar11 = (longlong *)
                      (**(code **)(*(longlong *)playerAction + 0x298))
                                (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
            if ((plVar11 != (longlong *)0x0) &&
               (lVar10 = (**(code **)(*plVar11 + 0x218))(plVar11,*(undefined8 *)(*plVar11 + 0x220)),
               lVar10 != 0)) {
              cVar4 = FUN_7ffe9a5b20c0(lVar10,0x48,0);
              if (cVar4 != '\0') {
                plVar11 = (longlong *)
                          (**(code **)(*(longlong *)playerAction + 0x298))
                                    (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)
                                    );
                if ((plVar11 == (longlong *)0x0) ||
                   (lVar10 = (**(code **)(*plVar11 + 0x218))
                                       (plVar11,*(undefined8 *)(*plVar11 + 0x220)), lVar10 == 0))
                goto LAB_7ffe9a4aa8b6;
                iVar8 = FUN_7ffe9a5b2120(lVar10,0x48,0);
                if (0 < iVar8) {
                  plVar11 = (longlong *)
                            (**(code **)(*(longlong *)playerAction + 0x298))
                                      (playerAction,
                                       *(undefined8 *)(*(longlong *)playerAction + 0x2a0));
                  if ((plVar11 == (longlong *)0x0) ||
                     (lVar10 = (**(code **)(*plVar11 + 0x1f8))
                                         (plVar11,*(undefined8 *)(*plVar11 + 0x200)), lVar10 == 0))
                  goto LAB_7ffe9a4aa8b6;
                  uVar12 = FUN_7ffe99c09050(lVar10,0);
                  if ((uVar12 & 0xffffffef) == 0) {
                    plVar11 = (longlong *)
                              (**(code **)(*(longlong *)playerAction + 0x298))
                                        (playerAction,
                                         *(undefined8 *)(*(longlong *)playerAction + 0x2a0));
                    if ((plVar11 == (longlong *)0x0) ||
                       (lVar10 = (**(code **)(*plVar11 + 0x1f8))
                                           (plVar11,*(undefined8 *)(*plVar11 + 0x200)), lVar10 == 0)
                       ) goto LAB_7ffe9a4aa8b6;
                    iVar9 = FUN_7ffe99c08f50(lVar10,0);
                    if (iVar9 == 0) {
                      fVar21 = _DAT_7ffe9c049b74;
                    }
                    iVar7 = iVar7 + (int)((float)iVar8 * fVar21);
                  }
                }
              }
              if (100 < iVar7) {
                iVar7 = 100;
              }
              if ((*(byte *)(*(longlong *)mobAction + 0x130) < *(byte *)(_DAT_7ffe9c923f10 + 0x130))
                 || (*(longlong *)
                      (*(longlong *)(*(longlong *)mobAction + 200) + -8 +
                      (ulonglong)*(byte *)(_DAT_7ffe9c923f10 + 0x130) * 8) != _DAT_7ffe9c923f10)) {
                bVar3 = false;
              }
              else {
                bVar3 = true;
              }
              plVar11 = (longlong *)0x0;
              if (bVar3) {
                plVar11 = (longlong *)mobAction;
              }
              if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                func_0x7ffe9996d830();
              }
              cVar4 = FUN_7ffe9bda2160(plVar11,0,0);
              iStack_a0 = iVar7;
              if (cVar4 != '\0') {
                if ((plVar11 == (longlong *)0x0) ||
                   (puVar13 = EnemyMobActionManagerBase_get_MobStatusMaster
                                        ((undefined *)plVar11,(undefined *)0x0),
                   puVar13 == (undefined *)0x0)) goto LAB_7ffe9a4aa8b6;
                iStack_a8 = *(int *)(puVar13 + 0x50);
                puVar13 = EnemyMobActionManagerBase_get_MobStatusMaster
                                    ((undefined *)plVar11,(undefined *)0x0);
                if (puVar13 == (undefined *)0x0) goto LAB_7ffe9a4aa8b6;
                iVar8 = *(int *)(puVar13 + 0x4c);
                cVar4 = FUN_7ffe9ab798a0(plVar11,0x28,&puStack_70,_DAT_7ffe9c8f2438);
                if (cVar4 != '\0') {
                  if (puStack_70 == (undefined *)0x0) goto LAB_7ffe9a4aa8b6;
                  bVar5 = MobPropertyStatusCollection_TryGetValue
                                    (puStack_70,(undefined *)0x6,(undefined *)&iStack_9c,
                                     (undefined *)auStack_88,(undefined *)0x0);
                  iVar6 = iStack_9c;
                  if (bVar5 != 0) {
                    if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
                      func_0x7ffe9996d830();
                    }
                    iVar9 = func_0x7ffe9b506b70(0,iStack_a4 - iVar6,0);
                    iVar6 = func_0x7ffe9b506b70(0,iVar6 - iStack_a4,0);
                    iStack_a8 = iStack_a8 + iVar6;
                    iStack_a4 = iVar9;
                  }
                  if (puStack_70 == (undefined *)0x0) goto LAB_7ffe9a4aa8b6;
                  bVar5 = MobPropertyStatusCollection_TryGetValue
                                    (puStack_70,(undefined *)0x5,(undefined *)&iStack_9c,
                                     (undefined *)auStack_88,(undefined *)0x0);
                  iVar6 = iStack_9c;
                  if (bVar5 != 0) {
                    if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
                      func_0x7ffe9996d830();
                    }
                    iStack_a0 = func_0x7ffe9b506b70(0,iVar7 - iVar6,0);
                    iVar6 = func_0x7ffe9b506b70(0,iVar6 - iVar7,0);
                    iVar8 = iVar8 + iVar6;
                  }
                }
                uVar14 = (**(code **)(*plVar11 + 0x518))(plVar11,*(undefined8 *)(*plVar11 + 0x520));
                lVar10 = func_0x7ffe9996c920(uVar14,_DAT_7ffe9c936530);
                if (lVar10 != 0) {
                  plVar15 = (longlong *)
                            (**(code **)(*plVar11 + 0x518))
                                      (plVar11,*(undefined8 *)(*plVar11 + 0x520));
                  if (plVar15 == (longlong *)0x0) goto LAB_7ffe9a4aa8b6;
                  if ((*(byte *)(*plVar15 + 0x130) < *(byte *)(_DAT_7ffe9c9238d0 + 0x130)) ||
                     (*(longlong *)
                       (*(longlong *)(*plVar15 + 200) + -8 +
                       (ulonglong)*(byte *)(_DAT_7ffe9c9238d0 + 0x130) * 8) != _DAT_7ffe9c9238d0)) {
                    FUN_7ffe9996c950(plVar15,_DAT_7ffe9c9238d0);
                    pcVar2 = (code *)swi(3);
                    puVar13 = (undefined *)(*pcVar2)();
                    return puVar13;
                  }
                  if (plVar15[3] == 0) goto LAB_7ffe9a4aa8b6;
                  uVar14 = FUN_7ffe9acd27a0(plVar15[3],_DAT_7ffe9c8ff610);
                  if (*(int *)(_DAT_7ffe9c910268 + 0xe0) == 0) {
                    func_0x7ffe9996d830(_DAT_7ffe9c910268);
                  }
                  lVar10 = *(longlong *)(*(longlong *)(_DAT_7ffe9c910268 + 0xb8) + 0x38);
                  if (lVar10 == 0) {
                    if (*(int *)(_DAT_7ffe9c910268 + 0xe0) == 0) {
                      func_0x7ffe9996d830(_DAT_7ffe9c910268);
                    }
                    uVar1 = **(undefined8 **)(_DAT_7ffe9c910268 + 0xb8);
                    lVar10 = func_0x7ffe99940040(_DAT_7ffe9c93f070);
                    FUN_7ffe9af15670(lVar10,uVar1,_DAT_7ffe9c8fba08,0);
                    *(longlong *)(*(longlong *)(_DAT_7ffe9c910268 + 0xb8) + 0x38) = lVar10;
                    il2cpp_write_barrier_0();
                  }
                  iVar6 = FUN_7ffe9ab8ff30(uVar14,lVar10,_DAT_7ffe9c91bcc0);
                  iStack_a8 = iStack_a8 + iVar6;
                  plVar15 = (longlong *)
                            (**(code **)(*plVar11 + 0x518))
                                      (plVar11,*(undefined8 *)(*plVar11 + 0x520));
                  if (plVar15 == (longlong *)0x0) goto LAB_7ffe9a4aa8b6;
                  if ((*(byte *)(*plVar15 + 0x130) < *(byte *)(_DAT_7ffe9c9238d0 + 0x130)) ||
                     (*(longlong *)
                       (*(longlong *)(*plVar15 + 200) + -8 +
                       (ulonglong)*(byte *)(_DAT_7ffe9c9238d0 + 0x130) * 8) != _DAT_7ffe9c9238d0)) {
                    FUN_7ffe9996c950(plVar15,_DAT_7ffe9c9238d0);
                    pcVar2 = (code *)swi(3);
                    puVar13 = (undefined *)(*pcVar2)();
                    return puVar13;
                  }
                  if (plVar15[3] == 0) goto LAB_7ffe9a4aa8b6;
                  uVar14 = FUN_7ffe9acd27a0(plVar15[3],_DAT_7ffe9c8ff610);
                  if (*(int *)(_DAT_7ffe9c910268 + 0xe0) == 0) {
                    func_0x7ffe9996d830(_DAT_7ffe9c910268);
                  }
                  lVar10 = *(longlong *)(*(longlong *)(_DAT_7ffe9c910268 + 0xb8) + 0x40);
                  if (lVar10 == 0) {
                    if (*(int *)(_DAT_7ffe9c910268 + 0xe0) == 0) {
                      func_0x7ffe9996d830(_DAT_7ffe9c910268);
                    }
                    uVar1 = **(undefined8 **)(_DAT_7ffe9c910268 + 0xb8);
                    lVar10 = func_0x7ffe99940040(_DAT_7ffe9c93f070);
                    FUN_7ffe9af15670(lVar10,uVar1,_DAT_7ffe9c8fbad8,0);
                    *(longlong *)(*(longlong *)(_DAT_7ffe9c910268 + 0xb8) + 0x40) = lVar10;
                    il2cpp_write_barrier_0();
                  }
                  iVar6 = FUN_7ffe9ab8ff30(uVar14,lVar10,_DAT_7ffe9c91bcc0);
                  iVar8 = iVar8 + iVar6;
                }
                lVar10 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,mobAction);
                if (lVar10 == 0) goto LAB_7ffe9a4aa8b6;
                cVar4 = FUN_7ffe9a4daa60(lVar10,0xe);
                iVar6 = iVar8;
                if (cVar4 != '\0') {
                  cVar4 = (**(code **)(*plVar11 + 0x538))(plVar11);
                  if (cVar4 == '\0') {
                    puVar13 = EnemyMobActionManagerBase_get_MobStatusMaster
                                        ((undefined *)plVar11,(undefined *)0x0);
                    if (puVar13 == (undefined *)0x0) goto LAB_7ffe9a4aa8b6;
                    if (*(int *)(puVar13 + 0x50) < 100) {
                      iVar7 = iStack_a8 + -100;
                      iStack_a8 = 0;
                      if (-1 < iVar7) {
                        iStack_a8 = iVar7;
                      }
                    }
                    puVar13 = EnemyMobActionManagerBase_get_MobStatusMaster
                                        ((undefined *)plVar11,(undefined *)0x0);
                    if (puVar13 == (undefined *)0x0) goto LAB_7ffe9a4aa8b6;
                    if ((*(int *)(puVar13 + 0x4c) < 100) && (iVar6 = 0, -1 < iVar8 + -100)) {
                      iVar6 = iVar8 + -100;
                    }
                  }
                  else {
                    puVar13 = EnemyMobActionManagerBase_get_MobStatusMaster
                                        ((undefined *)plVar11,(undefined *)0x0);
                    fVar21 = _DAT_7ffe9c049b4c;
                    if (puVar13 == (undefined *)0x0) goto LAB_7ffe9a4aa8b6;
                    if (*(int *)(puVar13 + 0x50) < 100) {
                      iStack_a8 = (int)((float)iStack_a8 * _DAT_7ffe9c049b4c);
                    }
                    puVar13 = EnemyMobActionManagerBase_get_MobStatusMaster
                                        ((undefined *)plVar11,(undefined *)0x0);
                    if (puVar13 == (undefined *)0x0) goto LAB_7ffe9a4aa8b6;
                    if (*(int *)(puVar13 + 0x4c) < 100) {
                      iVar6 = (int)((float)iVar8 * fVar21);
                    }
                  }
                }
              }
              iVar7 = 0;
              if ((int)attackType != 2) {
                iVar7 = iStack_a8;
              }
              cVar4 = FUN_7ffe9a8fea70(self,100,iVar7);
              if (cVar4 == '\0') {
                cVar4 = FUN_7ffe9a8fea70(self,100,iVar6,0);
                if (cVar4 == '\0') {
                  return (undefined *)0x0;
                }
                if (99 < iVar6) {
                  return (undefined *)0x2;
                }
                if ((plStack_80 != (longlong *)0x0) &&
                   (*(char *)((longlong)plStack_80 + 0x12) != '\0')) {
                  cVar4 = FUN_7ffe9a8fea70(self,100,iStack_a0,0);
                  if (cVar4 == '\0') {
                    return (undefined *)0x2;
                  }
                  *(undefined4 *)resistReactionType = 2;
                  if (self != (undefined *)0x0) {
                    if ((*(byte *)(_DAT_7ffe9c904080 + 0x130) <=
                         *(byte *)(*(longlong *)self + 0x130)) &&
                       (*(longlong *)
                         (*(longlong *)(*(longlong *)self + 200) + -8 +
                         (ulonglong)*(byte *)(_DAT_7ffe9c904080 + 0x130) * 8) == _DAT_7ffe9c904080))
                    {
                      return (undefined *)0x0;
                    }
                  }
                  if (plStack_80 != (longlong *)0x0) {
                    iVar6 = (**(code **)(*plStack_80 + 0x1f8))
                                      (plStack_80,*(undefined8 *)(*plStack_80 + 0x200));
                    plVar11 = (longlong *)
                              (**(code **)(*(longlong *)playerAction + 0x298))
                                        (playerAction,
                                         *(undefined8 *)(*(longlong *)playerAction + 0x2a0));
                    if (((plVar11 != (longlong *)0x0) &&
                        (lVar10 = (**(code **)(*plVar11 + 0x1f8))
                                            (plVar11,*(undefined8 *)(*plVar11 + 0x200)), lVar10 != 0
                        )) && (*(longlong *)(lVar10 + 0x18) != 0)) {
                      iVar7 = func_0x7ffe99c1ed70(*(longlong *)(lVar10 + 0x18),0);
                      plVar11 = (longlong *)
                                (**(code **)(*(longlong *)playerAction + 0x298))
                                          (playerAction,
                                           *(undefined8 *)(*(longlong *)playerAction + 0x2a0));
                      if (((plVar11 != (longlong *)0x0) &&
                          (lVar10 = (**(code **)(*plVar11 + 0x1f8))
                                              (plVar11,*(undefined8 *)(*plVar11 + 0x200)),
                          lVar10 != 0)) && (*(longlong *)(lVar10 + 0x20) != 0)) {
                        iVar8 = func_0x7ffe99c1ed70(*(longlong *)(lVar10 + 0x20),0);
                        lVar10 = FUN_7ffe9bd98a10(playerAction,0);
                        if (lVar10 != 0) {
                          puVar16 = (undefined8 *)FUN_7ffe9bdbf710(auStack_68,lVar10,0);
                          uStack_98 = *puVar16;
                          uStack_90 = *(undefined4 *)(puVar16 + 1);
                          PlayerAttackBase_ViewPreventedHitReactionIcon
                                    ((undefined *)0x2,(undefined *)&uStack_98,iVar6,iVar7,iVar8,
                                     (undefined *)0x0);
                          return (undefined *)0x0;
                        }
                      }
                    }
                  }
                  goto LAB_7ffe9a4aa8b6;
                }
                cVar4 = FUN_7ffe9a8fea70(self,100,iStack_a0,0);
                if (cVar4 == '\0') {
                  return (undefined *)0x2;
                }
                *(undefined4 *)resistReactionType = 2;
                if (self != (undefined *)0x0) {
                  if ((*(byte *)(_DAT_7ffe9c904080 + 0x130) <= *(byte *)(*(longlong *)self + 0x130))
                     && (*(longlong *)
                          (*(longlong *)(*(longlong *)self + 200) + -8 +
                          (ulonglong)*(byte *)(_DAT_7ffe9c904080 + 0x130) * 8) == _DAT_7ffe9c904080)
                     ) {
                    return (undefined *)0x0;
                  }
                }
                lVar10 = FUN_7ffe9bd98a10(playerAction,0);
                if (lVar10 == 0) goto LAB_7ffe9a4aa8b6;
                puVar16 = (undefined8 *)FUN_7ffe9bdbf710(auStack_68,lVar10,0);
                uVar19 = (undefined4)*puVar16;
                uVar20 = (undefined4)((ulonglong)*puVar16 >> 0x20);
                uVar17 = *(undefined4 *)(puVar16 + 1);
                uVar14 = _DAT_7ffe9c9689b0;
                if (DAT_7ffe9cadded8 == '\0') {
                  FUN_7ffe9996d590(&DAT_7ffe9c956938);
                  FUN_7ffe9996d590(&DAT_7ffe9c9689b0);
                  FUN_7ffe9996d590(&DAT_7ffe9c949528);
                  DAT_7ffe9cadded8 = '\x01';
                  uVar14 = _DAT_7ffe9c9689b0;
                }
              }
              else {
                if (99 < iVar7) {
                  return (undefined *)0x1;
                }
                if ((plStack_78 != (longlong *)0x0) &&
                   (*(char *)((longlong)plStack_78 + 0x12) != '\0')) {
                  cVar4 = FUN_7ffe9a8fea70(self,100,iStack_a4,0);
                  if (cVar4 == '\0') {
                    return (undefined *)0x1;
                  }
                  *(undefined4 *)resistReactionType = 1;
                  if (self != (undefined *)0x0) {
                    if ((*(byte *)(_DAT_7ffe9c904080 + 0x130) <=
                         *(byte *)(*(longlong *)self + 0x130)) &&
                       (*(longlong *)
                         (*(longlong *)(*(longlong *)self + 200) + -8 +
                         (ulonglong)*(byte *)(_DAT_7ffe9c904080 + 0x130) * 8) == _DAT_7ffe9c904080))
                    {
                      return (undefined *)0x0;
                    }
                  }
                  if (plStack_78 != (longlong *)0x0) {
                    iVar6 = (**(code **)(*plStack_78 + 0x1f8))
                                      (plStack_78,*(undefined8 *)(*plStack_78 + 0x200));
                    plVar11 = (longlong *)
                              (**(code **)(*(longlong *)playerAction + 0x298))
                                        (playerAction,
                                         *(undefined8 *)(*(longlong *)playerAction + 0x2a0));
                    if (((plVar11 != (longlong *)0x0) &&
                        (lVar10 = (**(code **)(*plVar11 + 0x1f8))
                                            (plVar11,*(undefined8 *)(*plVar11 + 0x200)), lVar10 != 0
                        )) && (*(longlong *)(lVar10 + 0x18) != 0)) {
                      iVar7 = func_0x7ffe99c1ed70(*(longlong *)(lVar10 + 0x18),0);
                      plVar11 = (longlong *)
                                (**(code **)(*(longlong *)playerAction + 0x298))
                                          (playerAction,
                                           *(undefined8 *)(*(longlong *)playerAction + 0x2a0));
                      if (((plVar11 != (longlong *)0x0) &&
                          (lVar10 = (**(code **)(*plVar11 + 0x1f8))
                                              (plVar11,*(undefined8 *)(*plVar11 + 0x200)),
                          lVar10 != 0)) && (*(longlong *)(lVar10 + 0x20) != 0)) {
                        iVar8 = func_0x7ffe99c1ed70(*(longlong *)(lVar10 + 0x20),0);
                        lVar10 = FUN_7ffe9bd98a10(playerAction,0);
                        if (lVar10 != 0) {
                          puVar16 = (undefined8 *)FUN_7ffe9bdbf710(auStack_68,lVar10,0);
                          uStack_98 = *puVar16;
                          uStack_90 = *(undefined4 *)(puVar16 + 1);
                          PlayerAttackBase_ViewPreventedHitReactionIcon
                                    ((undefined *)0x1,(undefined *)&uStack_98,iVar6,iVar7,iVar8,
                                     (undefined *)0x0);
                          return (undefined *)0x0;
                        }
                      }
                    }
                  }
                  goto LAB_7ffe9a4aa8b6;
                }
                cVar4 = FUN_7ffe9a8fea70(self,100,iStack_a4);
                if (cVar4 == '\0') {
                  return (undefined *)0x1;
                }
                *(undefined4 *)resistReactionType = 1;
                if (self != (undefined *)0x0) {
                  if ((*(byte *)(_DAT_7ffe9c904080 + 0x130) <= *(byte *)(*(longlong *)self + 0x130))
                     && (*(longlong *)
                          (*(longlong *)(*(longlong *)self + 200) + -8 +
                          (ulonglong)*(byte *)(_DAT_7ffe9c904080 + 0x130) * 8) == _DAT_7ffe9c904080)
                     ) {
                    return (undefined *)0x0;
                  }
                }
                lVar10 = FUN_7ffe9bd98a10(playerAction,0);
                if (lVar10 == 0) goto LAB_7ffe9a4aa8b6;
                puVar16 = (undefined8 *)FUN_7ffe9bdbf710(auStack_68,lVar10,0);
                uVar19 = (undefined4)*puVar16;
                uVar20 = (undefined4)((ulonglong)*puVar16 >> 0x20);
                uVar17 = *(undefined4 *)(puVar16 + 1);
                uVar14 = _DAT_7ffe9c949528;
                if (DAT_7ffe9cadded8 == '\0') {
                  FUN_7ffe9996d590(&DAT_7ffe9c956938);
                  FUN_7ffe9996d590(&DAT_7ffe9c9689b0);
                  FUN_7ffe9996d590(&DAT_7ffe9c949528);
                  DAT_7ffe9cadded8 = '\x01';
                  uVar14 = _DAT_7ffe9c949528;
                }
              }
              lVar10 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
              if (lVar10 != 0) {
                uStack_98 = CONCAT44(uVar20,uVar19);
                uStack_90 = uVar17;
                FUN_7ffe99ca7fc0(lVar10,&uStack_98,uVar14,0);
                return (undefined *)0x0;
              }
            }
          }
        }
      }
    }
  }
LAB_7ffe9a4aa8b6:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  puVar13 = (undefined *)(*pcVar2)();
  return puVar13;
}

