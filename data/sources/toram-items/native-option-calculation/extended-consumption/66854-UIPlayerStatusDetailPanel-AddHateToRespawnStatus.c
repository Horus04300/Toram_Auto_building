
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UIPlayerStatusDetailPanel_AddHateToRespawnStatus(undefined *self,undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong lVar6;
  code *pcVar7;
  uint uVar8;
  undefined4 uVar9;
  float fVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  undefined *puVar16;
  longlong lVar17;
  uint uVar18;
  undefined8 *puVar19;
  uint uVar20;
  uint uVar21;
  
  if (*(undefined **)(self + 0x78) != (undefined *)0x0) {
    PlayerSecondaryStatus_GetDisplayBonusCalcHate(*(undefined **)(self + 0x78),(undefined *)0x0);
    uVar12 = _DAT_7ffe9c04a830;
    uVar11 = _DAT_7ffe9c04a820;
    fVar10 = _DAT_7ffe9c049cfc;
    uVar9 = _DAT_7ffe9c049b90;
    FUN_7ffe9a08ef60(self);
    UIPlayerStatusDetailPanel_CalcExpValue(self,(undefined *)0x0);
    FUN_7ffe9a08ef60(self,0x26);
    plVar5 = *(longlong **)(self + 0x70);
    if ((plVar5 != (longlong *)0x0) &&
       (puVar16 = (undefined *)
                  (**(code **)(*plVar5 + 0x1d8))(plVar5,*(undefined8 *)(*plVar5 + 0x1e0)),
       puVar16 != (undefined *)0x0)) {
      iVar13 = BonusManager_GetBonusValue(puVar16,0x3f,(undefined *)0x0);
      plVar5 = *(longlong **)(self + 0x70);
      if ((plVar5 != (longlong *)0x0) &&
         (puVar16 = (undefined *)
                    (**(code **)(*plVar5 + 0x1d8))(plVar5,*(undefined8 *)(*plVar5 + 0x1e0)),
         puVar16 != (undefined *)0x0)) {
        iVar14 = BonusManager_GetBonusValue(puVar16,0xb0,(undefined *)0x0);
        plVar5 = *(longlong **)(self + 0x70);
        if ((plVar5 != (longlong *)0x0) &&
           (puVar16 = (undefined *)
                      (**(code **)(*plVar5 + 0x1d8))(plVar5,*(undefined8 *)(*plVar5 + 0x1e0)),
           puVar16 != (undefined *)0x0)) {
          iVar15 = BonusManager_GetGuildFacilityExpBonus(puVar16,0xb0,(undefined *)0x0);
          FUN_7ffe9a08ef60(self,0x27,(float)iVar13 + fVar10 + (float)iVar14 + (float)iVar15,1,fVar10
                           ,uVar11,uVar12,uVar9,0);
          if (DAT_7ffe9cadc4c8 == '\0') {
            FUN_7ffe9996d590(&DAT_7ffe9c9528b8);
            DAT_7ffe9cadc4c8 = '\x01';
          }
          if (*(undefined **)(self + 0x78) != (undefined *)0x0) {
            PlayerSecondaryStatus_GetDropBonus(*(undefined **)(self + 0x78),(undefined *)0x0);
            lVar17 = *(longlong *)(self + 0xa8);
            if (lVar17 != 0) {
              if ((*(uint *)(lVar17 + 0x18) < 3) || (*(uint *)(lVar17 + 0x18) < 4)) {
                FUN_7ffe9996d790();
                pcVar7 = (code *)swi(3);
                (*pcVar7)();
                return;
              }
              lVar17 = FUN_7ffe9b141840(_DAT_7ffe9c9528b8);
              if (lVar17 != 0) {
                FUN_7ffe9a527050(lVar17,0);
                FUN_7ffe9a08ef60(self);
                if (*(undefined **)(self + 0x78) != (undefined *)0x0) {
                  PlayerSecondaryStatus_GetbAvoid(*(undefined **)(self + 0x78),(undefined *)0x0);
                  FUN_7ffe9a08ef60(self);
                  if ((*(longlong *)(self + 0x58) != 0) &&
                     (puVar16 = (undefined *)FUN_7ffe9a47f0d0(), puVar16 != (undefined *)0x0)) {
                    AvoidActionManager_get_MaxAvoidCount(puVar16,(undefined *)0x0);
                    FUN_7ffe9a08ef60(self);
                    if (*(undefined **)(self + 0x78) != (undefined *)0x0) {
                      PlayerSecondaryStatus_GetbGuardSpeed
                                (*(undefined **)(self + 0x78),(undefined *)0x0);
                      FUN_7ffe9a08ef60(self);
                      if (*(undefined **)(self + 0x78) != (undefined *)0x0) {
                        PlayerSecondaryStatus_GetbGuardPower
                                  (*(undefined **)(self + 0x78),(undefined *)0x0);
                        FUN_7ffe9a08ef60(self);
                        if (*(undefined **)(self + 0x78) != (undefined *)0x0) {
                          PlayerSecondaryStatus_GetRespawnRate
                                    (*(undefined **)(self + 0x78),(undefined *)0x0);
                          FUN_7ffe9a08ef60(self);
                          if (DAT_7ffe9cadc4cf == '\0') {
                            FUN_7ffe9996d590(&DAT_7ffe9c8f6c78);
                            FUN_7ffe9996d590(&DAT_7ffe9c91fe10);
                            DAT_7ffe9cadc4cf = '\x01';
                          }
                          lVar17 = *(longlong *)(self + 0x88);
                          puVar16 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c8f6c78);
                          AvoidBreaker_Reset(puVar16,(undefined *)0x0);
                          *(undefined4 *)(puVar16 + 0x10) = 0;
                          *(undefined8 *)(puVar16 + 0x20) = 0xbff0000000000000;
                          *(undefined8 *)(puVar16 + 0x28) = 0xbff0000000000000;
                          *(undefined4 *)(puVar16 + 0x14) = 0xbf800000;
                          *(undefined4 *)(puVar16 + 0x18) = 0xbf800000;
                          *(undefined4 *)(puVar16 + 0x1c) = 0xbf800000;
                          *(undefined4 *)(puVar16 + 0x30) = 5;
                          lVar6 = _DAT_7ffe9c91fe10;
                          if (lVar17 != 0) {
                            *(int *)(lVar17 + 0x1c) = *(int *)(lVar17 + 0x1c) + 1;
                            lVar4 = *(longlong *)(lVar17 + 0x10);
                            uVar21 = *(uint *)(lVar17 + 0x18);
                            if (lVar4 != 0) {
                              if (uVar21 < *(uint *)(lVar4 + 0x18)) {
                                *(uint *)(lVar17 + 0x18) = uVar21 + 1;
                                if (*(uint *)(lVar4 + 0x18) <= uVar21) {
                                  FUN_7ffe9996d790();
                                  pcVar7 = (code *)swi(3);
                                  (*pcVar7)();
                                  return;
                                }
                                puVar19 = (undefined8 *)(lVar4 + (longlong)(int)uVar21 * 8 + 0x20);
                                *puVar19 = puVar16;
il2cpp_write_barrier_0:
                                if (_DAT_7ffe9caee1a8 != 0) {
                                  uVar21 = (uint)((ulonglong)puVar19 >> 0xc);
                                  puVar1 = (ulonglong *)
                                           ((ulonglong)((uVar21 & 0x1fffff) >> 6) * 8 +
                                           0x7ffe9cb35fe0);
                                  do {
                                    uVar3 = *puVar1;
                                    LOCK();
                                    uVar2 = *puVar1;
                                    if (uVar3 == uVar2) {
                                      *puVar1 = uVar3 | 1L << (uVar21 & 0x3f);
                                    }
                                    UNLOCK();
                                  } while (uVar3 != uVar2);
                                }
                                return;
                              }
                              uVar21 = *(uint *)(lVar17 + 0x18);
                              lVar4 = *(longlong *)(lVar17 + 0x10);
                              uVar20 = uVar21 + 1;
                              if (lVar4 != 0) {
                                if (*(int *)(lVar4 + 0x18) < (int)uVar20) {
                                  if (*(longlong *)(lVar4 + 0x18) == 0) {
                                    uVar18 = 4;
                                  }
                                  else {
                                    uVar18 = *(int *)(lVar4 + 0x18) * 2;
                                    if (0x7fefffff < uVar18) {
                                      uVar18 = 0x7fefffff;
                                    }
                                  }
                                  uVar8 = uVar20;
                                  if ((int)uVar20 <= (int)uVar18) {
                                    uVar8 = uVar18;
                                  }
                                  FUN_7ffe997b8720(lVar17,uVar8,
                                                   *(undefined8 *)
                                                    (*(longlong *)
                                                      (*(longlong *)
                                                        (*(longlong *)
                                                          (*(longlong *)
                                                            (*(longlong *)
                                                              (*(longlong *)
                                                                (*(longlong *)
                                                                  (*(longlong *)(lVar6 + 0x20) +
                                                                  0xc0) + 0x70) + 0x20) + 0xc0) +
                                                          0x78) + 0x20) + 0xc0) + 0xf0));
                                }
                                lVar6 = *(longlong *)(lVar17 + 0x10);
                                *(uint *)(lVar17 + 0x18) = uVar20;
                                if (lVar6 != 0) {
                                  if (*(uint *)(lVar6 + 0x18) <= uVar21) {
                                    FUN_7ffe9996d790();
                                    pcVar7 = (code *)swi(3);
                                    (*pcVar7)();
                                    return;
                                  }
                                  puVar19 = (undefined8 *)(lVar6 + 0x20 + (longlong)(int)uVar21 * 8)
                                  ;
                                  *puVar19 = puVar16;
                                  goto il2cpp_write_barrier_0;
                                }
                              }
                              FUN_7ffe9996d7a0();
                              pcVar7 = (code *)swi(3);
                              (*pcVar7)();
                              return;
                            }
                          }
                          FUN_7ffe9996d7a0();
                          pcVar7 = (code *)swi(3);
                          (*pcVar7)();
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
  FUN_7ffe9996d7a0();
  pcVar7 = (code *)swi(3);
  (*pcVar7)();
  return;
}

