
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void DamageReflectionAction_calcPlayerToMobDamage
               (undefined *self,undefined *playerAction,undefined *mobAction,undefined *methodInfo)

{
  uint uVar1;
  longlong lVar2;
  code *pcVar3;
  longlong lVar4;
  byte bVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined *damageData;
  longlong *plVar10;
  longlong lVar11;
  undefined *puVar12;
  undefined *puVar13;
  float fVar14;
  undefined auStackX_10 [8];
  undefined auStackX_18 [16];
  float afStack_58 [2];
  longlong *aplStack_50 [3];
  
  if (DAT_7ffe9cadde6c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c920098);
    FUN_7ffe9996d590(&DAT_7ffe9c8f64d8);
    FUN_7ffe9996d590(&DAT_7ffe9c91aa80);
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    FUN_7ffe9996d590(&DAT_7ffe9c913488);
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    DAT_7ffe9cadde6c = '\x01';
  }
  afStack_58[0] = 0.0;
  aplStack_50[0] = (longlong *)0x0;
  damageData = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c920098);
  FUN_7ffe9a8f6350(damageData,mobAction,0);
  if (playerAction != (undefined *)0x0) {
    plVar10 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if (plVar10 != (longlong *)0x0) {
      (**(code **)(*plVar10 + 0x1a8))(plVar10,*(undefined8 *)(*plVar10 + 0x1b0));
      if (mobAction != (undefined *)0x0) {
        lVar11 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
        if (lVar11 != 0) {
          iVar7 = FUN_7ffe99742ec0(7,_DAT_7ffe9c93ed20);
          puVar12 = PlayerAttackBase_checkMobReaction(self,iVar7,0,(undefined *)0x0);
          plVar10 = (longlong *)
                    (**(code **)(*(longlong *)playerAction + 0x298))
                              (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
          if (plVar10 != (longlong *)0x0) {
            lVar11 = (**(code **)(*plVar10 + 0x208))(plVar10,*(undefined8 *)(*plVar10 + 0x210));
            if (lVar11 != 0) {
              iVar7 = FUN_7ffe9a51d0c0(lVar11,0x9b,0,0);
              lVar11 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
              if (lVar11 != 0) {
                iVar8 = FUN_7ffe99742ec0(5,_DAT_7ffe9c93ed20,lVar11);
                lVar11 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
                if (lVar11 != 0) {
                  iVar9 = FUN_7ffe99742ec0(6,_DAT_7ffe9c93ed20,lVar11);
                  lVar11 = *(longlong *)mobAction;
                  if ((*(byte *)(_DAT_7ffe9c8f64d8 + 0x130) <= *(byte *)(lVar11 + 0x130)) &&
                     (*(longlong *)
                       (*(longlong *)(lVar11 + 200) + -8 +
                       (ulonglong)*(byte *)(_DAT_7ffe9c8f64d8 + 0x130) * 8) == _DAT_7ffe9c8f64d8)) {
                    if ((*(byte *)(lVar11 + 0x130) < *(byte *)(_DAT_7ffe9c8f64d8 + 0x130)) ||
                       (*(longlong *)
                         (*(longlong *)(lVar11 + 200) + -8 +
                         (ulonglong)*(byte *)(_DAT_7ffe9c8f64d8 + 0x130) * 8) != _DAT_7ffe9c8f64d8))
                    {
                      FUN_7ffe9996c950(mobAction,_DAT_7ffe9c8f64d8);
                      pcVar3 = (code *)swi(3);
                      (*pcVar3)();
                      return;
                    }
                    puVar13 = EnemyMobActionManagerBase_get_MobStatusMaster
                                        (mobAction,(undefined *)0x0);
                    if (puVar13 == (undefined *)0x0) goto LAB_7ffe9a49152d;
                    iVar8 = *(int *)(puVar13 + 0x44);
                    if ((*(byte *)(*(longlong *)mobAction + 0x130) <
                         *(byte *)(_DAT_7ffe9c8f64d8 + 0x130)) ||
                       (*(longlong *)
                         (*(longlong *)(*(longlong *)mobAction + 200) + -8 +
                         (ulonglong)*(byte *)(_DAT_7ffe9c8f64d8 + 0x130) * 8) != _DAT_7ffe9c8f64d8))
                    {
                      FUN_7ffe9996c950(mobAction);
                      pcVar3 = (code *)swi(3);
                      (*pcVar3)();
                      return;
                    }
                    puVar13 = EnemyMobActionManagerBase_get_MobStatusMaster
                                        (mobAction,(undefined *)0x0);
                    if (puVar13 == (undefined *)0x0) goto LAB_7ffe9a49152d;
                    iVar9 = *(int *)(puVar13 + 0x48);
                  }
                  iVar7 = (int)((float)((100 - (iVar9 + iVar8) / 2) * iVar7) * _DAT_7ffe9c049b34);
                  bVar5 = PlayerAttackBase_CheckAbnormalDamageIncrease
                                    (self,mobAction,(undefined *)afStack_58,(undefined *)0x0);
                  fVar14 = _DAT_7ffe9c049f04;
                  if (bVar5 != 0) {
                    iVar7 = (int)((float)iVar7 * afStack_58[0]);
                  }
                  if (99999 < iVar7) {
                    iVar7 = 99999;
                  }
                  if ((int)puVar12 == 2) {
                    lVar11 = FUN_7ffe99742ec0(0xb,_DAT_7ffe9c9724e0,mobAction);
                    if (lVar11 == 0) goto LAB_7ffe9a49152d;
                    cVar6 = FUN_7ffe9a2ac880(lVar11,4,aplStack_50,0);
                    if (cVar6 != '\0') {
                      if (aplStack_50[0] == (longlong *)0x0) goto LAB_7ffe9a49152d;
                      if (((*(byte *)(*aplStack_50[0] + 0x130) <
                            *(byte *)(_DAT_7ffe9c91aa80 + 0x130)) ||
                          (*(longlong *)
                            (*(longlong *)(*aplStack_50[0] + 200) + -8 +
                            (ulonglong)*(byte *)(_DAT_7ffe9c91aa80 + 0x130) * 8) !=
                           _DAT_7ffe9c91aa80)) || (aplStack_50[0] == (longlong *)0x0)) {
                        FUN_7ffe9996c950(aplStack_50[0]);
                        pcVar3 = (code *)swi(3);
                        (*pcVar3)();
                        return;
                      }
                      FUN_7ffe9a2ea460(aplStack_50[0],0);
                      if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
                        func_0x7ffe9996d830();
                      }
                      fVar14 = (float)func_0x7ffe9b506c10();
                    }
                    iVar7 = (int)(((float)iVar7 * fVar14) / _DAT_7ffe9c049cfc);
                  }
                  iVar7 = PlayerAttackBase_CalcPlayerDamageUpLimit
                                    (self,iVar7,playerAction,mobAction,(undefined *)0x0);
                  auStackX_10[0] = 0;
                  auStackX_18[0] = 0;
                  iVar8 = PlayerAttackBase_GetLimitDamage
                                    (self,iVar7,mobAction,auStackX_10,auStackX_18,(undefined *)0x0);
                  iVar7 = 1;
                  if (1 < iVar8) {
                    iVar7 = iVar8;
                  }
                  fVar14 = PlayerAttackBase_GetSpecificWeaponLastDamageRate
                                     (playerAction,mobAction,(undefined *)0x0);
                  iVar8 = 1;
                  if (1 < (int)(fVar14 * (float)iVar7)) {
                    iVar8 = (int)(fVar14 * (float)iVar7);
                  }
                  if (damageData != (undefined *)0x0) {
                    *(int *)(damageData + 0x18) = iVar8;
                    *(undefined4 *)(damageData + 0x40) = *(undefined4 *)(self + 0x120);
                    *(undefined4 *)(damageData + 0x1c) = 1;
                    *(int *)(damageData + 0x34) = (int)puVar12;
                    damageData[0x31] = auStackX_10[0];
                    damageData[0x32] = auStackX_18[0];
                    PlayerAttackBase_createMultiHitDamage(self,damageData,iVar8,(undefined *)0x0);
                    lVar4 = _DAT_7ffe9c913488;
                    lVar11 = *(longlong *)(self + 0x80);
                    if (lVar11 != 0) {
                      *(int *)(lVar11 + 0x1c) = *(int *)(lVar11 + 0x1c) + 1;
                      lVar2 = *(longlong *)(lVar11 + 0x10);
                      uVar1 = *(uint *)(lVar11 + 0x18);
                      if (lVar2 != 0) {
                        if (uVar1 < *(uint *)(lVar2 + 0x18)) {
                          *(uint *)(lVar11 + 0x18) = uVar1 + 1;
                          if (*(uint *)(lVar2 + 0x18) <= uVar1) {
                            FUN_7ffe9996d790();
                            pcVar3 = (code *)swi(3);
                            (*pcVar3)();
                            return;
                          }
                          *(undefined **)(lVar2 + 0x20 + (longlong)(int)uVar1 * 8) = damageData;
                          il2cpp_write_barrier_0();
                        }
                        else {
                          FUN_7ffe9afd58b0(lVar11,damageData,
                                           *(undefined8 *)
                                            (*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) +
                                            0x70));
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
LAB_7ffe9a49152d:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

