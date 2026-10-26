
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobCurrentHPRateAttack_calcMobToPlayerDamage
               (undefined *self,undefined *mobAction,undefined *playerAction,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  byte bVar4;
  char cVar5;
  undefined1 uVar6;
  int iVar7;
  uint uVar8;
  longlong lVar9;
  undefined *puVar10;
  longlong *plVar11;
  undefined *puVar12;
  undefined8 uVar13;
  undefined8 *puVar14;
  undefined8 uVar15;
  ushort uVar16;
  undefined *puVar17;
  int iVar18;
  float fVar19;
  float fVar20;
  byte abStackX_18 [8];
  undefined4 *puVar21;
  undefined4 uVar22;
  byte *pbVar23;
  int iStack_58;
  undefined4 uStack_54;
  longlong *plStack_50;
  longlong *plStack_48;
  longlong lStack_40;
  longlong *plStack_38;
  longlong lStack_30;
  
  if (DAT_7ffe9cadd7e9 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c920098);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c8f64d8);
    FUN_7ffe9996d590(&DAT_7ffe9c8ff718);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c913488);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c914fd0);
    FUN_7ffe9996d590(&DAT_7ffe9c969a58);
    FUN_7ffe9996d590(&DAT_7ffe9c969d88);
    FUN_7ffe9996d590(&DAT_7ffe9c94aa68);
    DAT_7ffe9cadd7e9 = '\x01';
  }
  puVar12 = (undefined *)0x0;
  plStack_50 = (longlong *)0x0;
  lStack_30 = 0;
  plStack_38 = (longlong *)0x0;
  plStack_48 = (longlong *)0x0;
  uStack_54 = 0;
  if (playerAction == (undefined *)0x0) goto LAB_7ffe9a385700;
  lVar9 = (**(code **)(*(longlong *)playerAction + 0x298))
                    (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if (lVar9 == 0) {
    return;
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
  puVar10 = puVar12;
  if (bVar2) {
    puVar10 = playerAction;
  }
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar3 = FUN_7ffe9bda2160(puVar10,0);
  if (cVar3 != '\0') {
    MobAttackBase_CreateFamiliaDamageData(self,puVar10,(undefined *)0x0);
    return;
  }
  puVar10 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c920098);
  FUN_7ffe9a8f6490(puVar10,playerAction,0);
  puVar17 = (undefined *)0x0;
  *(undefined4 *)(self + 0xc4) = 0;
  abStackX_18[0] = 0;
  self[0xd5] = 0;
  *(undefined4 *)(self + 0xd0) = 0;
  iStack_58 = -1;
  MobAttackBase_CalcHit(self,puVar10,mobAction,playerAction,(undefined *)0x0);
  if (puVar10 == (undefined *)0x0) goto LAB_7ffe9a385700;
  if (*(int *)(puVar10 + 0x1c) != 0) {
    plVar11 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if ((plVar11 == (longlong *)0x0) ||
       (lVar9 = (**(code **)(*plVar11 + 0x178))(plVar11,*(undefined8 *)(*plVar11 + 0x180)),
       lVar9 == 0)) goto LAB_7ffe9a385700;
    iVar18 = *(int *)(lVar9 + 0x14);
    plVar11 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if ((plVar11 == (longlong *)0x0) ||
       (lVar9 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
       lVar9 == 0)) goto LAB_7ffe9a385700;
    cVar3 = FUN_7ffe9abc2210(lVar9,0x34e,&plStack_50,_DAT_7ffe9c969a58);
    if (cVar3 != '\0') {
      if (plStack_50 == (longlong *)0x0) goto LAB_7ffe9a385700;
      iVar7 = (**(code **)(*plStack_50 + 0x1f8))
                        (plStack_50,0x32,*(undefined8 *)(*plStack_50 + 0x200));
      iVar18 = iVar18 + iVar7;
    }
    lVar9 = *(longlong *)(self + 0xa0);
    if (lVar9 == 0) goto LAB_7ffe9a385700;
    if ((*(byte *)(lVar9 + 0x6c) & 2) == 0) {
      plVar11 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if (plVar11 == (longlong *)0x0) goto LAB_7ffe9a385700;
      lStack_40 = (**(code **)(*plVar11 + 0x1a8))(plVar11,*(undefined8 *)(*plVar11 + 0x1b0));
      if (iVar18 == 1) {
        puVar12 = puVar17;
        if (*(int *)(puVar10 + 0x34) != 1) {
          *(undefined4 *)(puVar10 + 0x1c) = 0;
        }
      }
      else if (*(int *)(puVar10 + 0x34) != 1) {
        if ((*(longlong *)(self + 0xa0) == 0) || (mobAction == (undefined *)0x0))
        goto LAB_7ffe9a385700;
        puVar12 = (undefined *)FUN_7ffe99742ec0(6,_DAT_7ffe9c9724e0);
        MobAttackBase_CalcBaseAttack(self,puVar12,(undefined *)0x0);
        plVar11 = (longlong *)
                  (**(code **)(*(longlong *)playerAction + 0x298))
                            (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if ((plVar11 == (longlong *)0x0) ||
           (lVar9 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
           lVar9 == 0)) goto LAB_7ffe9a385700;
        cVar3 = FUN_7ffe9abc2210(lVar9,0x303,&plStack_48,_DAT_7ffe9c969d88);
        if (cVar3 != '\0') {
          if (plStack_48 == (longlong *)0x0) goto LAB_7ffe9a385700;
          (**(code **)(*plStack_48 + 0x1f8))(plStack_48,0x14,*(undefined8 *)(*plStack_48 + 0x200));
        }
        plVar11 = (longlong *)
                  (**(code **)(*(longlong *)playerAction + 0x298))
                            (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if ((plVar11 == (longlong *)0x0) ||
           (lVar9 = (**(code **)(*plVar11 + 0x1f8))(plVar11,*(undefined8 *)(*plVar11 + 0x200)),
           lVar9 == 0)) goto LAB_7ffe9a385700;
        puVar12 = (undefined *)FUN_7ffe99c08d90(lVar9,0);
        bVar4 = ItemDBData_CheckArmorAbility(puVar12,(undefined *)0x2,(undefined *)0x0);
        if (bVar4 != 0) {
          plVar11 = (longlong *)
                    (**(code **)(*(longlong *)playerAction + 0x298))
                              (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
          if (((plVar11 == (longlong *)0x0) ||
              (lVar9 = (**(code **)(*plVar11 + 0x1f8))(plVar11,*(undefined8 *)(*plVar11 + 0x200)),
              lVar9 == 0)) || (lVar9 = FUN_7ffe99c08d90(lVar9,0), lVar9 == 0))
          goto LAB_7ffe9a385700;
          func_0x7ffe9a56fe10(lVar9,0);
        }
        if (lStack_40 == 0) goto LAB_7ffe9a385700;
        iVar18 = FUN_7ffe99749320(0x2c,_DAT_7ffe9c940d40,lStack_40);
        if (*(int *)(puVar10 + 0x1c) == 2) {
          lVar9 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,mobAction);
          if (lVar9 == 0) goto LAB_7ffe9a385700;
          cVar3 = FUN_7ffe9a4daa60(lVar9,0x13);
          if (cVar3 == '\0') {
            if (*(longlong *)(self + 0xa0) == 0) goto LAB_7ffe9a385700;
            iVar18 = (int)((ulonglong)
                           ((longlong)(iVar18 * *(int *)(*(longlong *)(self + 0xa0) + 0x28)) *
                           0x51eb851f) >> 0x20);
          }
          else {
            cVar3 = '\0';
            if ((*(byte *)(*(longlong *)mobAction + 0x130) < *(byte *)(_DAT_7ffe9c8f64d8 + 0x130))
               || (*(longlong *)
                    (*(longlong *)(*(longlong *)mobAction + 200) + -8 +
                    (ulonglong)*(byte *)(_DAT_7ffe9c8f64d8 + 0x130) * 8) != _DAT_7ffe9c8f64d8)) {
              bVar2 = false;
            }
            else {
              bVar2 = true;
            }
            plVar11 = (longlong *)0x0;
            if (bVar2) {
              plVar11 = (longlong *)mobAction;
            }
            if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            cVar5 = FUN_7ffe9bda2160(plVar11,0,0);
            if (cVar5 != '\0') {
              if (plVar11 == (longlong *)0x0) goto LAB_7ffe9a385700;
              cVar3 = (**(code **)(*plVar11 + 0x538))(plVar11,*(undefined8 *)(*plVar11 + 0x540));
            }
            if (*(longlong *)(self + 0xa0) == 0) goto LAB_7ffe9a385700;
            iVar7 = *(int *)(*(longlong *)(self + 0xa0) + 0x28);
            if (cVar3 == '\0') {
              if (99 < iVar7) goto LAB_7ffe9a3850fb;
            }
            else if (100 < iVar7) {
              iVar7 = (iVar7 + -100) / 2 + 100;
            }
            iVar18 = (int)((ulonglong)((longlong)(iVar7 * iVar18) * 0x51eb851f) >> 0x20);
          }
          iVar18 = (iVar18 >> 5) - (iVar18 >> 0x1f);
        }
        else {
          *(undefined4 *)(puVar10 + 0x1c) = 1;
        }
LAB_7ffe9a3850fb:
        iVar7 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c940d40);
        fVar19 = MobAttackBase_calcEquipDefPercent(self,(float)iVar7,(undefined *)0x0);
        fVar20 = MobAttackBase_CalcStable(self,mobAction,playerAction,(undefined *)0x0);
        iVar18 = (int)(fVar20 * (float)(int)(fVar19 * (float)iVar18));
        plVar11 = (longlong *)
                  (**(code **)(*(longlong *)playerAction + 0x298))
                            (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if (((plVar11 == (longlong *)0x0) ||
            (lVar9 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
            lVar9 == 0)) || (*(longlong *)(lVar9 + 0x50) == 0)) goto LAB_7ffe9a385700;
        cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x50),0x283,&plStack_38,_DAT_7ffe9c934418);
        if (cVar3 != '\0') {
          if (plStack_38 == (longlong *)0x0) goto LAB_7ffe9a385700;
          bVar4 = *(byte *)(_DAT_7ffe9c914fd0 + 0x130);
          if (((*(byte *)(*plStack_38 + 0x130) < bVar4) ||
              (lVar9 = *(longlong *)(*plStack_38 + 200),
              *(longlong *)(lVar9 + -8 + (ulonglong)bVar4 * 8) != _DAT_7ffe9c914fd0)) ||
             (plStack_38 == (longlong *)0x0)) goto LAB_7ffe9a385700;
          plVar11 = (longlong *)0x0;
          if (*(longlong *)(lVar9 + -8 + (ulonglong)bVar4 * 8) == _DAT_7ffe9c914fd0) {
            plVar11 = plStack_38;
          }
          func_0x7ffe9a79e3d0(plVar11,0);
        }
        pbVar23 = abStackX_18;
        puVar21 = &uStack_54;
        cVar3 = (**(code **)(*(longlong *)self + 0x598))
                          (self,playerAction,mobAction,iVar18,puVar21,pbVar23,
                           *(undefined8 *)(*(longlong *)self + 0x5a0));
        uVar22 = (undefined4)((ulonglong)puVar21 >> 0x20);
        if (cVar3 != '\0') {
          *(undefined4 *)(puVar10 + 0x34) = uStack_54;
          uVar22 = 0;
          iVar18 = MobAttackBase_CalcGuard
                             (self,iVar18,playerAction,(undefined *)&iStack_58,(undefined *)0x0);
        }
        iVar18 = MobAttackBase_CalcSkillComboTough(self,playerAction,iVar18,(undefined *)0x0);
        iVar18 = MobAttackBase_CalcLastDamage
                           (self,mobAction,playerAction,iVar18,
                            (undefined *)CONCAT44(uVar22,*(undefined4 *)(puVar10 + 0x34)),
                            (undefined *)CONCAT71((int7)((ulonglong)pbVar23 >> 8),1),
                            (undefined *)0x0);
        fVar19 = MobAttackBase_GetDistDamageRegistRate(self,playerAction,mobAction,(undefined *)0x0)
        ;
        iVar18 = MobAttackBase_CalcMobaBonusDamageResist
                           (self,(int)(fVar19 * (float)iVar18),playerAction,(undefined *)0x0);
        uVar8 = MobAttackBase_CalcBarrier(self,iVar18,playerAction,mobAction,(undefined *)0x0);
        puVar12 = (undefined *)(ulonglong)uVar8;
        if ((int)uVar8 < 1) {
          puVar12 = (undefined *)0x1;
        }
      }
      if ((*(int *)(puVar10 + 0x1c) - 1U < 2) &&
         (bVar4 = MobAttackBase_InvalidDamage(self,playerAction,(undefined *)0x0), bVar4 != 0)) {
        *(undefined4 *)(puVar10 + 0x20) = 4;
        puVar12 = (undefined *)0x0;
      }
      plVar11 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if (((plVar11 == (longlong *)0x0) ||
          (lVar9 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
          lVar9 == 0)) || (*(longlong *)(lVar9 + 0x50) == 0)) goto LAB_7ffe9a385700;
      cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x50),0x385,&lStack_30,_DAT_7ffe9c934418);
      if (cVar3 != '\0') {
        if (lStack_30 == 0) goto LAB_7ffe9a385700;
        iVar18 = func_0x7ffe9a7a2140(lStack_30,0x32);
        uVar8 = (uint)((_DAT_7ffe9c049b68 - (double)((float)iVar18 * _DAT_7ffe9c049b34)) *
                      (double)(int)puVar12);
        puVar12 = (undefined *)0x0;
        if (-1 < (int)uVar8) {
          puVar12 = (undefined *)(ulonglong)uVar8;
        }
      }
    }
    else if (iVar18 == 1) {
      puVar12 = puVar17;
      if (*(int *)(puVar10 + 0x34) != 1) {
        *(undefined4 *)(puVar10 + 0x1c) = 0;
      }
    }
    else {
      uVar8 = MobAttackBase_CreateFixDamage
                        (self,(int)((float)(iVar18 * *(int *)(lVar9 + 0x14)) / _DAT_7ffe9c049cfc),
                         mobAction,playerAction,puVar10,(undefined *)&iStack_58,abStackX_18,
                         (undefined *)0x0);
      puVar12 = (undefined *)(ulonglong)uVar8;
    }
  }
  if (*(longlong *)(self + 0xa0) != 0) {
    if ((((*(byte *)(*(longlong *)(self + 0xa0) + 0x6c) & 1) != 0) &&
        (*(int *)(puVar10 + 0x1c) == 0)) && (*(int *)(puVar10 + 0x34) != 1)) {
      uVar8 = MobAttackBase_CalcUnavoidableAttack
                        (self,mobAction,playerAction,puVar10,(undefined *)&iStack_58,abStackX_18,
                         (undefined *)0x0);
      puVar12 = (undefined *)(ulonglong)uVar8;
    }
    if ((*(longlong *)(puVar10 + 0x10) != 0) &&
       (uVar13 = FUN_7ffe9bd98960(*(longlong *)(puVar10 + 0x10),0), mobAction != (undefined *)0x0))
    {
      lVar9 = *(longlong *)mobAction;
      uVar16 = 0;
      if (*(ushort *)(lVar9 + 0x12e) != 0) {
        do {
          if (*(longlong *)(*(longlong *)(lVar9 + 0xb0) + (ulonglong)uVar16 * 0x10) ==
              _DAT_7ffe9c9724e0) {
            puVar14 = (undefined8 *)
                      ((longlong)
                       (*(int *)(*(longlong *)(lVar9 + 0xb0) + 8 + (ulonglong)uVar16 * 0x10) + 0xd)
                       * 0x10 + 0x138 + lVar9);
            goto LAB_7ffe9a385519;
          }
          uVar16 = uVar16 + 1;
        } while (uVar16 < *(ushort *)(lVar9 + 0x12e));
      }
      puVar14 = (undefined8 *)FUN_7ffe998ce540(mobAction,_DAT_7ffe9c9724e0,0xd);
LAB_7ffe9a385519:
      uVar15 = (*(code *)*puVar14)(mobAction,puVar14[1]);
      if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      FUN_7ffe9bda1fa0(uVar13,uVar15,0);
      uVar13 = *(undefined8 *)(puVar10 + 0x48);
      puVar17 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c94aa68);
      FUN_7ffe9a8fff70(puVar17,uVar13,0);
      if (puVar17 != (undefined *)0x0) {
        func_0x7ffe9a900040(puVar17,puVar12,0);
        *(undefined4 *)(puVar17 + 0x14) = *(undefined4 *)(puVar10 + 0x1c);
        *(undefined4 *)(puVar17 + 0x18) = *(undefined4 *)(puVar10 + 0x34);
        *(undefined4 *)(puVar17 + 0x1c) = *(undefined4 *)(puVar10 + 0x20);
        plVar11 = *(longlong **)(self + 0xa8);
        if (plVar11 != (longlong *)0x0) {
          uVar6 = (**(code **)(*plVar11 + 0x208))(plVar11,*(undefined8 *)(*plVar11 + 0x210));
          puVar17[0xa1] = uVar6;
          *(undefined4 *)(puVar17 + 0x48) = *(undefined4 *)(self + 0xc4);
          *(undefined4 *)(puVar17 + 0x4c) = *(undefined4 *)(self + 0xd0);
          *(undefined4 *)(puVar17 + 0x50) = *(undefined4 *)(self + 0xcc);
          *(undefined4 *)(puVar17 + 0x6c) = *(undefined4 *)(self + 0xd8);
          *(undefined4 *)(puVar17 + 0x54) = 0xffffffff;
          puVar17[0x5a] = abStackX_18[0];
          if ((*(int *)(puVar10 + 0x1c) != 0) && (*(int *)(puVar10 + 0x34) != 1)) {
            *(uint *)(puVar17 + 0x70) = *(uint *)(puVar17 + 0x70) | -(uint)(self[200] != '\0') & 8;
            *(uint *)(puVar17 + 0x70) =
                 *(uint *)(puVar17 + 0x70) | -(uint)(self[0xd4] != '\0') & 0x800;
            puVar12 = (undefined *)
                      (**(code **)(*(longlong *)playerAction + 0x298))
                                (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
            MobAttackBase_SetAbnormalEffect
                      (self,puVar17,puVar12,iStack_58,abStackX_18[0],(undefined *)0x0);
          }
          if (self[0xd5] != '\0') {
            *(uint *)(puVar17 + 0x70) = *(uint *)(puVar17 + 0x70) | 0x10000;
          }
          MobAttackBase_FinawGuard(self,puVar17,iStack_58,(undefined *)0x0);
          *(undefined **)(puVar10 + 0x38) = puVar17;
          il2cpp_write_barrier_0();
          if (*(longlong *)(self + 0x80) != 0) {
            FUN_7ffe99743100(*(longlong *)(self + 0x80),puVar10,_DAT_7ffe9c913488);
            return;
          }
        }
      }
    }
  }
LAB_7ffe9a385700:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

