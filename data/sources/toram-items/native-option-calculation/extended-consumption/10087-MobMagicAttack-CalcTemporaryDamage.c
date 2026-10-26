
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobMagicAttack_CalcTemporaryDamage
              (undefined *self,undefined *mobAction,undefined *playerAction,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  longlong *plVar9;
  undefined *puVar10;
  longlong lVar11;
  float fVar12;
  longlong *aplStackX_18 [2];
  uint in_stack_ffffffffffffffac;
  uint7 in_stack_ffffffffffffffb1;
  
  if (DAT_7ffe9cadd7fc == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c8ff718);
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    DAT_7ffe9cadd7fc = '\x01';
  }
  aplStackX_18[0] = (longlong *)0x0;
  if (playerAction == (undefined *)0x0) goto LAB_7ffe9a388eba;
  lVar8 = (**(code **)(*(longlong *)playerAction + 0x298))
                    (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if (lVar8 != 0) {
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    if ((*(byte *)(*(longlong *)playerAction + 0x130) < *(byte *)(_DAT_7ffe9c8ff718 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)playerAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c8ff718 + 0x130) * 8) != _DAT_7ffe9c8ff718)) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    puVar10 = (undefined *)0x0;
    if (bVar2) {
      puVar10 = playerAction;
    }
    cVar3 = FUN_7ffe9bda2160(puVar10,0,0);
    if (cVar3 == '\0') {
      lVar8 = *(longlong *)(self + 0xa0);
      if (lVar8 != 0) {
        if ((*(byte *)(lVar8 + 0x6c) & 2) != 0) {
          return *(int *)(lVar8 + 0x14);
        }
        plVar9 = (longlong *)
                 (**(code **)(*(longlong *)playerAction + 0x298))
                           (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if ((plVar9 != (longlong *)0x0) &&
           (lVar8 = (**(code **)(*plVar9 + 0x1a8))(plVar9,*(undefined8 *)(*plVar9 + 0x1b0)),
           mobAction != (undefined *)0x0)) {
          puVar10 = (undefined *)func_0x7ffe9a2ef690(mobAction,0);
          MobAttackBase_CalcBaseAttack(self,puVar10,(undefined *)0x0);
          lVar11 = (**(code **)(*(longlong *)mobAction + 0x518))
                             (mobAction,*(undefined8 *)(*(longlong *)mobAction + 0x520));
          if (lVar11 != 0) {
            FUN_7ffe99744d60(0xd,_DAT_7ffe9c93ed20,lVar11);
            lVar11 = (**(code **)(*(longlong *)mobAction + 0x518))
                               (mobAction,*(undefined8 *)(*(longlong *)mobAction + 0x520));
            if (lVar11 != 0) {
              FUN_7ffe99742ec0(1,_DAT_7ffe9c93ed20,lVar11);
              if (lVar8 != 0) {
                FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar8);
                uVar4 = FUN_7ffe99742ec0(0x14,_DAT_7ffe9c940d40,lVar8);
                FUN_7ffe99749320(0x2b,_DAT_7ffe9c940d40,lVar8,uVar4);
                iVar5 = FUN_7ffe99749320(0x2c,_DAT_7ffe9c940d40,lVar8);
                iVar6 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c940d40);
                fVar12 = MobAttackBase_calcEquipDefPercent(self,(float)iVar6,(undefined *)0x0);
                plVar9 = *(longlong **)(self + 0xa8);
                iVar6 = 0;
                if (plVar9 != (longlong *)0x0) {
                  cVar3 = (**(code **)(*plVar9 + 0x1e8))(plVar9,*(undefined8 *)(*plVar9 + 0x1f0));
                  if (cVar3 == '\0') {
                    puVar10 = (undefined *)
                              (**(code **)(*(longlong *)playerAction + 0x298))
                                        (playerAction,
                                         *(undefined8 *)(*(longlong *)playerAction + 0x2a0));
                    if (puVar10 == (undefined *)0x0) goto LAB_7ffe9a388eba;
                    iVar6 = PlayerStatusBase_GetBonusValueWithBuf(puVar10,0x32,(undefined *)0x0);
                  }
                  iVar7 = MobAttackBase_GetActionTypeResist(self,playerAction,(undefined *)0x0);
                  iVar6 = iVar6 + iVar7;
                  plVar9 = (longlong *)
                           (**(code **)(*(longlong *)playerAction + 0x298))
                                     (playerAction,
                                      *(undefined8 *)(*(longlong *)playerAction + 0x2a0));
                  if ((plVar9 != (longlong *)0x0) &&
                     (lVar8 = (**(code **)(*plVar9 + 0x1e8))
                                        (plVar9,*(undefined8 *)(*plVar9 + 0x1f0)), lVar8 != 0)) {
                    cVar3 = FUN_7ffe9a4daa60(lVar8,10);
                    if (cVar3 != '\0') {
                      iVar6 = iVar6 + -0x32;
                    }
                    plVar9 = (longlong *)
                             (**(code **)(*(longlong *)playerAction + 0x298))
                                       (playerAction,
                                        *(undefined8 *)(*(longlong *)playerAction + 0x2a0));
                    if (((plVar9 != (longlong *)0x0) &&
                        (lVar8 = (**(code **)(*plVar9 + 0x1f8))
                                           (plVar9,*(undefined8 *)(*plVar9 + 0x200)), lVar8 != 0))
                       && (*(longlong *)(lVar8 + 0x20) != 0)) {
                      iVar7 = func_0x7ffe99c1ed70(*(longlong *)(lVar8 + 0x20),0);
                      if (iVar7 == 0x11) {
                        plVar9 = (longlong *)
                                 (**(code **)(*(longlong *)playerAction + 0x298))
                                           (playerAction,
                                            *(undefined8 *)(*(longlong *)playerAction + 0x2a0));
                        if (((plVar9 == (longlong *)0x0) ||
                            (lVar8 = (**(code **)(*plVar9 + 0x1b8))
                                               (plVar9,*(undefined8 *)(*plVar9 + 0x1c0)), lVar8 == 0
                            )) || (*(longlong *)(lVar8 + 0x68) == 0)) goto LAB_7ffe9a388eba;
                        cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0x105,aplStackX_18);
                        if (cVar3 != '\0') {
                          if (aplStackX_18[0] == (longlong *)0x0) goto LAB_7ffe9a388eba;
                          iVar7 = (**(code **)(*aplStackX_18[0] + 0x178))
                                            (aplStackX_18[0],0x19,
                                             *(undefined8 *)(*aplStackX_18[0] + 0x180));
                          iVar6 = iVar6 + iVar7;
                        }
                      }
                      iVar5 = MobAttackBase_calcResistDamage
                                        (self,(int)(fVar12 * (float)iVar5),iVar6,(undefined *)0x0);
                      puVar10 = (undefined *)
                                (**(code **)(*(longlong *)playerAction + 0x298))
                                          (playerAction,
                                           *(undefined8 *)(*(longlong *)playerAction + 0x2a0));
                      iVar6 = MobAttackBase_getElementShield
                                        (self,(undefined *)(ulonglong)*(uint *)(self + 0x30),
                                         (undefined *)0x0);
                      if (puVar10 != (undefined *)0x0) {
                        iVar6 = PlayerStatusBase_GetBonusValueWithBuf
                                          (puVar10,iVar6,(undefined *)0x0);
                        iVar5 = MobAttackBase_calcResistDamage(self,iVar5,iVar6,(undefined *)0x0);
                        lVar8 = FUN_7ffe9a317ba0(mobAction,0);
                        if (lVar8 != 0) {
                          cVar3 = FUN_7ffe9a4daa60(lVar8,0x12);
                          if (cVar3 != '\0') {
                            cVar3 = (**(code **)(*(longlong *)mobAction + 0x538))
                                              (mobAction,
                                               *(undefined8 *)(*(longlong *)mobAction + 0x540));
                            fVar12 = _DAT_7ffe9c049c7c;
                            if (cVar3 == '\0') {
                              fVar12 = _DAT_7ffe9c049b4c;
                            }
                            iVar5 = (int)((_DAT_7ffe9c049b18 - fVar12) * (float)iVar5);
                          }
                          iVar5 = MobAttackBase_CalcLastDamage
                                            (self,mobAction,playerAction,iVar5,
                                             (undefined *)
                                             ((ulonglong)in_stack_ffffffffffffffac << 0x20),
                                             (undefined *)
                                             ((ulonglong)in_stack_ffffffffffffffb1 << 8),
                                             (undefined *)0x0);
                          if (iVar5 < 1) {
                            iVar5 = 1;
                          }
                          plVar9 = (longlong *)
                                   (**(code **)(*(longlong *)playerAction + 0x298))
                                             (playerAction,
                                              *(undefined8 *)(*(longlong *)playerAction + 0x2a0));
                          if ((plVar9 != (longlong *)0x0) &&
                             (puVar10 = (undefined *)(**(code **)(*plVar9 + 0x1d8))(plVar9),
                             puVar10 != (undefined *)0x0)) {
                            fVar12 = BonusManager_GetTreasureHuntLastDmgedDownRateBonus
                                               (puVar10,(undefined *)0x0);
                            return (int)(fVar12 * (float)iVar5);
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
LAB_7ffe9a388eba:
      FUN_7ffe9996d7a0();
      pcVar1 = (code *)swi(3);
      iVar5 = (*pcVar1)();
      return iVar5;
    }
  }
  return 0;
}

