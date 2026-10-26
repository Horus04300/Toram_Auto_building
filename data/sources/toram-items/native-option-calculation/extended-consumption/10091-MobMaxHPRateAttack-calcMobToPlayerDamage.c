
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobMaxHPRateAttack_calcMobToPlayerDamage
               (undefined *self,undefined *mobAction,undefined *playerAction,undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  byte bVar5;
  char cVar6;
  undefined1 uVar7;
  int iVar8;
  int iVar9;
  uint uVar10;
  longlong lVar11;
  undefined *damageData;
  longlong *plVar12;
  undefined *puVar13;
  longlong lVar14;
  undefined *status;
  float fVar15;
  float fVar16;
  byte abStackX_18 [8];
  undefined4 *puVar17;
  undefined4 uVar18;
  byte *pbVar19;
  int iStack_48;
  undefined4 uStack_44;
  longlong *plStack_40;
  longlong *aplStack_38 [2];
  
  if (DAT_7ffe9cadd7fe == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c920098);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c8f64d8);
    FUN_7ffe9996d590(&DAT_7ffe9c8ff718);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c913488);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c914fd0);
    FUN_7ffe9996d590(&DAT_7ffe9c969d88);
    FUN_7ffe9996d590(&DAT_7ffe9c94aa68);
    DAT_7ffe9cadd7fe = '\x01';
  }
  plStack_40 = (longlong *)0x0;
  aplStack_38[0] = (longlong *)0x0;
  cVar6 = '\0';
  uStack_44 = 0;
  if (playerAction == (undefined *)0x0) goto LAB_7ffe9a38b790;
  lVar11 = (**(code **)(*(longlong *)playerAction + 0x298))
                     (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if (lVar11 == 0) {
    return;
  }
  if ((*(byte *)(*(longlong *)playerAction + 0x130) < *(byte *)(_DAT_7ffe9c8ff718 + 0x130)) ||
     (*(longlong *)
       (*(longlong *)(*(longlong *)playerAction + 200) + -8 +
       (ulonglong)*(byte *)(_DAT_7ffe9c8ff718 + 0x130) * 8) != _DAT_7ffe9c8ff718)) {
    bVar3 = false;
  }
  else {
    bVar3 = true;
  }
  plVar12 = (longlong *)0x0;
  if (bVar3) {
    plVar12 = (longlong *)playerAction;
  }
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar4 = FUN_7ffe9bda2160(plVar12,0);
  if (cVar4 != '\0') {
    MobAttackBase_CreateFamiliaDamageData(self,(undefined *)plVar12,(undefined *)0x0);
    return;
  }
  damageData = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c920098);
  FUN_7ffe9a8f6490(damageData,playerAction,0);
  *(undefined4 *)(self + 0xc4) = 0;
  *(undefined4 *)(self + 0xd0) = 0;
  iStack_48 = -1;
  abStackX_18[0] = 0;
  self[0xd5] = 0;
  MobAttackBase_CalcHit(self,damageData,mobAction,playerAction,(undefined *)0x0);
  if (damageData == (undefined *)0x0) goto LAB_7ffe9a38b790;
  plVar12 = (longlong *)0x0;
  if (*(int *)(damageData + 0x1c) != 0) {
    plVar12 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if (plVar12 == (longlong *)0x0) goto LAB_7ffe9a38b790;
    lVar11 = (**(code **)(*plVar12 + 0x1a8))(plVar12,*(undefined8 *)(*plVar12 + 0x1b0));
    if (*(longlong *)(self + 0xa0) == 0) goto LAB_7ffe9a38b790;
    if ((*(byte *)(*(longlong *)(self + 0xa0) + 0x6c) & 2) == 0) {
      if (mobAction == (undefined *)0x0) goto LAB_7ffe9a38b790;
      puVar13 = (undefined *)FUN_7ffe99742ec0(6,_DAT_7ffe9c9724e0);
      MobAttackBase_CalcBaseAttack(self,puVar13,(undefined *)0x0);
      plVar12 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar12 == (longlong *)0x0) ||
         (lVar14 = (**(code **)(*plVar12 + 0x1c8))(plVar12,*(undefined8 *)(*plVar12 + 0x1d0)),
         lVar14 == 0)) goto LAB_7ffe9a38b790;
      cVar4 = FUN_7ffe9abc2210(lVar14,0x303,aplStack_38,_DAT_7ffe9c969d88);
      if (cVar4 != '\0') {
        if (aplStack_38[0] == (longlong *)0x0) goto LAB_7ffe9a38b790;
        (**(code **)(*aplStack_38[0] + 0x1f8))
                  (aplStack_38[0],0x14,*(undefined8 *)(*aplStack_38[0] + 0x200));
      }
      plVar12 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar12 == (longlong *)0x0) ||
         (lVar14 = (**(code **)(*plVar12 + 0x1f8))(plVar12,*(undefined8 *)(*plVar12 + 0x200)),
         lVar14 == 0)) goto LAB_7ffe9a38b790;
      puVar13 = (undefined *)FUN_7ffe99c08d90(lVar14,0);
      bVar5 = ItemDBData_CheckArmorAbility(puVar13,(undefined *)0x2,(undefined *)0x0);
      if (bVar5 != 0) {
        plVar12 = (longlong *)
                  (**(code **)(*(longlong *)playerAction + 0x298))
                            (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if (((plVar12 == (longlong *)0x0) ||
            (lVar14 = (**(code **)(*plVar12 + 0x1f8))(plVar12,*(undefined8 *)(*plVar12 + 0x200)),
            lVar14 == 0)) || (lVar14 = FUN_7ffe99c08d90(lVar14,0), lVar14 == 0))
        goto LAB_7ffe9a38b790;
        func_0x7ffe9a56fe10(lVar14,0);
      }
      if (lVar11 == 0) goto LAB_7ffe9a38b790;
      FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar11);
      iVar8 = FUN_7ffe99749320(0x2c,_DAT_7ffe9c940d40,lVar11);
      if (*(int *)(damageData + 0x1c) == 2) {
        lVar11 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,mobAction);
        if (lVar11 == 0) goto LAB_7ffe9a38b790;
        cVar4 = FUN_7ffe9a4daa60(lVar11,0x13);
        if (cVar4 == '\0') {
          if (*(longlong *)(self + 0xa0) == 0) goto LAB_7ffe9a38b790;
          iVar8 = (iVar8 * *(int *)(*(longlong *)(self + 0xa0) + 0x28)) / 100;
        }
        else {
          if ((*(byte *)(*(longlong *)mobAction + 0x130) < *(byte *)(_DAT_7ffe9c8f64d8 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(*(longlong *)mobAction + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c8f64d8 + 0x130) * 8) != _DAT_7ffe9c8f64d8)) {
            bVar3 = false;
          }
          else {
            bVar3 = true;
          }
          plVar12 = (longlong *)0x0;
          if (bVar3) {
            plVar12 = (longlong *)mobAction;
          }
          if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          cVar4 = FUN_7ffe9bda2160(plVar12,0,0);
          if (cVar4 != '\0') {
            if (plVar12 == (longlong *)0x0) goto LAB_7ffe9a38b790;
            cVar6 = (**(code **)(*plVar12 + 0x538))(plVar12,*(undefined8 *)(*plVar12 + 0x540));
          }
          if (*(longlong *)(self + 0xa0) == 0) goto LAB_7ffe9a38b790;
          iVar9 = *(int *)(*(longlong *)(self + 0xa0) + 0x28);
          if (cVar6 == '\0') {
            if (99 < iVar9) goto LAB_7ffe9a38b1ed;
          }
          else if (100 < iVar9) {
            iVar9 = (iVar9 + -100) / 2 + 100;
          }
          iVar8 = (iVar9 * iVar8) / 100;
        }
      }
      else {
        *(undefined4 *)(damageData + 0x1c) = 1;
      }
LAB_7ffe9a38b1ed:
      iVar9 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c940d40);
      fVar15 = MobAttackBase_calcEquipDefPercent(self,(float)iVar9,(undefined *)0x0);
      fVar16 = MobAttackBase_CalcStable(self,mobAction,playerAction,(undefined *)0x0);
      iVar8 = (int)(fVar16 * (float)(int)(fVar15 * (float)iVar8));
      plVar12 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if (((plVar12 == (longlong *)0x0) ||
          (lVar11 = (**(code **)(*plVar12 + 0x1c8))(plVar12,*(undefined8 *)(*plVar12 + 0x1d0)),
          lVar11 == 0)) || (*(longlong *)(lVar11 + 0x50) == 0)) goto LAB_7ffe9a38b790;
      cVar6 = FUN_7ffe9ad8e670(*(longlong *)(lVar11 + 0x50),0x283,&plStack_40,_DAT_7ffe9c934418);
      if (cVar6 != '\0') {
        if (plStack_40 == (longlong *)0x0) goto LAB_7ffe9a38b790;
        lVar11 = *plStack_40;
        bVar5 = *(byte *)(_DAT_7ffe9c914fd0 + 0x130);
        if (((*(byte *)(lVar11 + 0x130) < bVar5) ||
            (*(longlong *)(*(longlong *)(lVar11 + 200) + -8 + (ulonglong)bVar5 * 8) !=
             _DAT_7ffe9c914fd0)) || (plStack_40 == (longlong *)0x0)) goto LAB_7ffe9a38b790;
        plVar12 = (longlong *)0x0;
        if (*(longlong *)(*(longlong *)(lVar11 + 200) + -8 + (ulonglong)bVar5 * 8) ==
            _DAT_7ffe9c914fd0) {
          plVar12 = plStack_40;
        }
        func_0x7ffe9a79e3d0(plVar12,0);
      }
      pbVar19 = abStackX_18;
      puVar17 = &uStack_44;
      cVar6 = (**(code **)(*(longlong *)self + 0x598))
                        (self,playerAction,mobAction,iVar8,puVar17,pbVar19,
                         *(undefined8 *)(*(longlong *)self + 0x5a0));
      uVar18 = (undefined4)((ulonglong)puVar17 >> 0x20);
      if (cVar6 != '\0') {
        *(undefined4 *)(damageData + 0x34) = uStack_44;
        uVar18 = 0;
        iVar8 = MobAttackBase_CalcGuard
                          (self,iVar8,playerAction,(undefined *)&iStack_48,(undefined *)0x0);
      }
      iVar8 = MobAttackBase_CalcSkillComboTough(self,playerAction,iVar8,(undefined *)0x0);
      iVar8 = MobAttackBase_CalcLastDamage
                        (self,mobAction,playerAction,iVar8,
                         (undefined *)CONCAT44(uVar18,*(undefined4 *)(damageData + 0x34)),
                         (undefined *)CONCAT71((int7)((ulonglong)pbVar19 >> 8),1),(undefined *)0x0);
      fVar15 = MobAttackBase_GetDistDamageRegistRate(self,playerAction,mobAction,(undefined *)0x0);
      iVar8 = MobAttackBase_CalcMobaBonusDamageResist
                        (self,(int)(fVar15 * (float)iVar8),playerAction,(undefined *)0x0);
      iVar8 = MobAttackBase_CalcBarrier(self,iVar8,playerAction,mobAction,(undefined *)0x0);
      if (iVar8 < 1) {
        iVar8 = 1;
      }
      bVar5 = MobAttackBase_InvalidDamage(self,playerAction,(undefined *)0x0);
      if (bVar5 != 0) {
        *(undefined4 *)(damageData + 0x20) = 4;
        iVar8 = 0;
      }
      plVar12 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar12 == (longlong *)0x0) ||
         (puVar13 = (undefined *)(**(code **)(*plVar12 + 0x1d8))(plVar12),
         puVar13 == (undefined *)0x0)) goto LAB_7ffe9a38b790;
      fVar15 = BonusManager_GetTreasureHuntLastDmgedDownRateBonus(puVar13,(undefined *)0x0);
      plVar12 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar12 == (longlong *)0x0) ||
         ((lVar11 = (**(code **)(*plVar12 + 0x1c8))(plVar12,*(undefined8 *)(*plVar12 + 0x1d0)),
          lVar11 == 0 || (*(longlong *)(lVar11 + 0x50) == 0)))) goto LAB_7ffe9a38b790;
      cVar6 = FUN_7ffe9ad8e670(*(longlong *)(lVar11 + 0x50),0x385,&plStack_40);
      plVar12 = (longlong *)(ulonglong)(uint)(int)(fVar15 * (float)iVar8);
      if (cVar6 != '\0') {
        if (plStack_40 == (longlong *)0x0) goto LAB_7ffe9a38b790;
        iVar9 = func_0x7ffe9a7a2140(plStack_40,0x32);
        uVar10 = (uint)((_DAT_7ffe9c049b68 - (double)((float)iVar9 * _DAT_7ffe9c049b34)) *
                       (double)(int)(fVar15 * (float)iVar8));
        plVar12 = (longlong *)0x0;
        if (-1 < (int)uVar10) {
          plVar12 = (longlong *)(ulonglong)uVar10;
        }
      }
    }
    else {
      if (lVar11 == 0) goto LAB_7ffe9a38b790;
      iVar8 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar11);
      if (*(longlong *)(self + 0xa0) == 0) goto LAB_7ffe9a38b790;
      uVar10 = MobAttackBase_CreateFixDamage
                         (self,(int)((float)(iVar8 * *(int *)(*(longlong *)(self + 0xa0) + 0x14)) /
                                    _DAT_7ffe9c049cfc),mobAction,playerAction,damageData,
                          (undefined *)&iStack_48,abStackX_18,(undefined *)0x0);
      plVar12 = (longlong *)(ulonglong)uVar10;
    }
  }
  if (*(longlong *)(self + 0xa0) != 0) {
    if ((((*(byte *)(*(longlong *)(self + 0xa0) + 0x6c) & 1) != 0) &&
        (*(int *)(damageData + 0x1c) == 0)) && (*(int *)(damageData + 0x34) != 1)) {
      uVar10 = MobAttackBase_CalcUnavoidableAttack
                         (self,mobAction,playerAction,damageData,(undefined *)&iStack_48,abStackX_18
                          ,(undefined *)0x0);
      plVar12 = (longlong *)(ulonglong)uVar10;
    }
    uVar1 = *(undefined8 *)(damageData + 0x48);
    puVar13 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c94aa68);
    FUN_7ffe9a8fff70(puVar13,uVar1,0);
    if (puVar13 != (undefined *)0x0) {
      func_0x7ffe9a900040(puVar13,plVar12,0);
      *(undefined4 *)(puVar13 + 0x14) = *(undefined4 *)(damageData + 0x1c);
      *(undefined4 *)(puVar13 + 0x18) = *(undefined4 *)(damageData + 0x34);
      *(undefined4 *)(puVar13 + 0x1c) = *(undefined4 *)(damageData + 0x20);
      plVar12 = *(longlong **)(self + 0xa8);
      if (plVar12 != (longlong *)0x0) {
        uVar7 = (**(code **)(*plVar12 + 0x208))(plVar12,*(undefined8 *)(*plVar12 + 0x210));
        puVar13[0xa1] = uVar7;
        *(undefined4 *)(puVar13 + 0x48) = *(undefined4 *)(self + 0xc4);
        *(undefined4 *)(puVar13 + 0x4c) = *(undefined4 *)(self + 0xd0);
        *(undefined4 *)(puVar13 + 0x50) = *(undefined4 *)(self + 0xcc);
        *(undefined4 *)(puVar13 + 0x54) = 0xffffffff;
        puVar13[0x5a] = abStackX_18[0];
        *(undefined4 *)(puVar13 + 0x6c) = *(undefined4 *)(self + 0xd8);
        if ((*(int *)(damageData + 0x1c) != 0) && (*(int *)(damageData + 0x34) != 1)) {
          *(uint *)(puVar13 + 0x70) = *(uint *)(puVar13 + 0x70) | -(uint)(self[200] != '\0') & 8;
          *(uint *)(puVar13 + 0x70) =
               *(uint *)(puVar13 + 0x70) | -(uint)(self[0xd4] != '\0') & 0x800;
          status = (undefined *)
                   (**(code **)(*(longlong *)playerAction + 0x298))
                             (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
          MobAttackBase_SetAbnormalEffect
                    (self,puVar13,status,iStack_48,abStackX_18[0],(undefined *)0x0);
        }
        if (self[0xd5] != '\0') {
          *(uint *)(puVar13 + 0x70) = *(uint *)(puVar13 + 0x70) | 0x10000;
        }
        MobAttackBase_FinawGuard(self,puVar13,iStack_48,(undefined *)0x0);
        *(undefined **)(damageData + 0x38) = puVar13;
        il2cpp_write_barrier_0();
        if (*(longlong *)(self + 0x80) != 0) {
          FUN_7ffe99743100(*(longlong *)(self + 0x80),damageData,_DAT_7ffe9c913488);
          return;
        }
      }
    }
  }
LAB_7ffe9a38b790:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

