
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobMagicAttack_calcMobToPlayerDamage
               (undefined *self,undefined *mobAction,undefined *playerAction,undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  char cVar5;
  byte bVar6;
  undefined1 uVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  uint uVar12;
  longlong lVar13;
  undefined *puVar14;
  longlong *plVar15;
  undefined *puVar16;
  longlong lVar17;
  undefined *skillDamageData;
  float fVar18;
  float fVar19;
  byte abStackX_18 [8];
  undefined4 *puVar20;
  byte *pbVar21;
  int iStack_68;
  undefined4 uStack_64;
  longlong *plStack_60;
  longlong *plStack_58;
  longlong lStack_50;
  longlong lStack_48;
  
  if (DAT_7ffe9cadd7fa == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c920098);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f64d8);
    FUN_7ffe9996d590(&DAT_7ffe9c8ff718);
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c913488);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c914fd0);
    FUN_7ffe9996d590(&DAT_7ffe9c968010);
    FUN_7ffe9996d590(&DAT_7ffe9c94aa68);
    DAT_7ffe9cadd7fa = '\x01';
  }
  puVar16 = (undefined *)0x0;
  plStack_58 = (longlong *)0x0;
  plStack_60 = (longlong *)0x0;
  lStack_50 = 0;
  uStack_64 = 0;
  if (playerAction == (undefined *)0x0) goto LAB_7ffe9a38a3fb;
  lVar13 = (**(code **)(*(longlong *)playerAction + 0x298))
                     (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if (lVar13 == 0) {
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
  puVar14 = puVar16;
  if (bVar3) {
    puVar14 = playerAction;
  }
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar4 = FUN_7ffe9bda2160(puVar14,0);
  if (cVar4 != '\0') {
    MobAttackBase_CreateFamiliaDamageData(self,puVar14,(undefined *)0x0);
    return;
  }
  puVar14 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c920098);
  FUN_7ffe9a8f6490(puVar14,playerAction,0);
  *(undefined4 *)(self + 0xc4) = 0;
  abStackX_18[0] = 0;
  self[0xd5] = 0;
  *(undefined4 *)(self + 0xd0) = 0;
  iStack_68 = -1;
  MobAttackBase_CalcHit(self,puVar14,mobAction,playerAction,(undefined *)0x0);
  if (puVar14 == (undefined *)0x0) goto LAB_7ffe9a38a3fb;
  if (*(int *)(puVar14 + 0x1c) != 0) {
    lVar13 = *(longlong *)(self + 0xa0);
    if (lVar13 == 0) goto LAB_7ffe9a38a3fb;
    if ((*(byte *)(lVar13 + 0x6c) & 2) == 0) {
      plVar15 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar15 == (longlong *)0x0) ||
         (lVar13 = (**(code **)(*plVar15 + 0x1a8))(plVar15,*(undefined8 *)(*plVar15 + 0x1b0)),
         lStack_48 = lVar13, mobAction == (undefined *)0x0)) goto LAB_7ffe9a38a3fb;
      puVar16 = (undefined *)FUN_7ffe99742ec0(6,_DAT_7ffe9c9724e0);
      MobAttackBase_CalcBaseAttack(self,puVar16,(undefined *)0x0);
      lVar17 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
      if (lVar17 == 0) goto LAB_7ffe9a38a3fb;
      FUN_7ffe99744d60(0xd,_DAT_7ffe9c93ed20,lVar17);
      lVar17 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
      if ((lVar17 == 0) || (FUN_7ffe99742ec0(1,_DAT_7ffe9c93ed20,lVar17), lVar13 == 0))
      goto LAB_7ffe9a38a3fb;
      FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar13);
      uVar8 = FUN_7ffe99742ec0(0x14,_DAT_7ffe9c940d40,lVar13);
      FUN_7ffe99749320(0x2b,_DAT_7ffe9c940d40,lVar13,uVar8);
      iVar9 = FUN_7ffe99749320(0x2c,_DAT_7ffe9c940d40,lVar13);
      if (*(int *)(puVar14 + 0x1c) == 2) {
        lVar13 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,mobAction);
        if (lVar13 == 0) goto LAB_7ffe9a38a3fb;
        cVar4 = FUN_7ffe9a4daa60(lVar13,0x13);
        if (cVar4 == '\0') {
          if (*(longlong *)(self + 0xa0) == 0) goto LAB_7ffe9a38a3fb;
          iVar9 = (int)((ulonglong)
                        ((longlong)(iVar9 * *(int *)(*(longlong *)(self + 0xa0) + 0x28)) *
                        0x51eb851f) >> 0x20);
        }
        else {
          cVar4 = '\0';
          if ((*(byte *)(*(longlong *)mobAction + 0x130) < *(byte *)(_DAT_7ffe9c8f64d8 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(*(longlong *)mobAction + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c8f64d8 + 0x130) * 8) != _DAT_7ffe9c8f64d8)) {
            bVar3 = false;
          }
          else {
            bVar3 = true;
          }
          plVar15 = (longlong *)0x0;
          if (bVar3) {
            plVar15 = (longlong *)mobAction;
          }
          if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          cVar5 = FUN_7ffe9bda2160(plVar15,0,0);
          if (cVar5 != '\0') {
            if (plVar15 == (longlong *)0x0) goto LAB_7ffe9a38a3fb;
            cVar4 = (**(code **)(*plVar15 + 0x538))(plVar15,*(undefined8 *)(*plVar15 + 0x540));
          }
          if (*(longlong *)(self + 0xa0) == 0) goto LAB_7ffe9a38a3fb;
          iVar10 = *(int *)(*(longlong *)(self + 0xa0) + 0x28);
          if (cVar4 == '\0') {
            if (99 < iVar10) goto LAB_7ffe9a389c6c;
          }
          else if (100 < iVar10) {
            iVar10 = (iVar10 + -100) / 2 + 100;
          }
          iVar9 = (int)((ulonglong)((longlong)(iVar10 * iVar9) * 0x51eb851f) >> 0x20);
        }
        iVar9 = (iVar9 >> 5) - (iVar9 >> 0x1f);
      }
      else {
        *(undefined4 *)(puVar14 + 0x1c) = 1;
      }
LAB_7ffe9a389c6c:
      iVar10 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c940d40);
      fVar18 = MobAttackBase_calcEquipDefPercent(self,(float)iVar10,(undefined *)0x0);
      fVar19 = MobAttackBase_CalcStable(self,mobAction,playerAction,(undefined *)0x0);
      plVar15 = *(longlong **)(self + 0xa8);
      if (plVar15 == (longlong *)0x0) goto LAB_7ffe9a38a3fb;
      cVar4 = (**(code **)(*plVar15 + 0x1e8))(plVar15,*(undefined8 *)(*plVar15 + 0x1f0));
      iVar10 = 0;
      if (cVar4 == '\0') {
        puVar16 = (undefined *)
                  (**(code **)(*(longlong *)playerAction + 0x298))
                            (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if (puVar16 == (undefined *)0x0) goto LAB_7ffe9a38a3fb;
        iVar10 = PlayerStatusBase_GetBonusValueWithBuf(puVar16,0x32,(undefined *)0x0);
      }
      iVar11 = MobAttackBase_GetActionTypeResist(self,playerAction,(undefined *)0x0);
      iVar10 = iVar10 + iVar11;
      plVar15 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar15 == (longlong *)0x0) ||
         (lVar13 = (**(code **)(*plVar15 + 0x1e8))(plVar15,*(undefined8 *)(*plVar15 + 0x1f0)),
         lVar13 == 0)) goto LAB_7ffe9a38a3fb;
      cVar4 = FUN_7ffe9a4daa60(lVar13,10);
      if (cVar4 != '\0') {
        iVar10 = iVar10 + -0x32;
      }
      plVar15 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if (((plVar15 == (longlong *)0x0) ||
          (lVar13 = (**(code **)(*plVar15 + 0x1f8))(plVar15,*(undefined8 *)(*plVar15 + 0x200)),
          lVar13 == 0)) || (*(longlong *)(lVar13 + 0x20) == 0)) goto LAB_7ffe9a38a3fb;
      iVar11 = func_0x7ffe99c1ed70(*(longlong *)(lVar13 + 0x20),0);
      if (iVar11 == 0x11) {
        plVar15 = (longlong *)
                  (**(code **)(*(longlong *)playerAction + 0x298))
                            (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if (((plVar15 == (longlong *)0x0) ||
            (lVar13 = (**(code **)(*plVar15 + 0x1b8))(plVar15,*(undefined8 *)(*plVar15 + 0x1c0)),
            lVar13 == 0)) || (*(longlong *)(lVar13 + 0x68) == 0)) goto LAB_7ffe9a38a3fb;
        cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar13 + 0x68),0x105,&plStack_60);
        if (cVar4 != '\0') {
          if (plStack_60 == (longlong *)0x0) goto LAB_7ffe9a38a3fb;
          iVar11 = (**(code **)(*plStack_60 + 0x178))
                             (plStack_60,0x19,*(undefined8 *)(*plStack_60 + 0x180));
          iVar10 = iVar10 + iVar11;
        }
      }
      iVar9 = MobAttackBase_calcResistDamage
                        (self,(int)(fVar19 * (float)(int)(fVar18 * (float)iVar9)),iVar10,
                         (undefined *)0x0);
      puVar16 = (undefined *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      iVar10 = MobAttackBase_getElementShield
                         (self,(undefined *)(ulonglong)*(uint *)(self + 0x30),(undefined *)0x0);
      if (puVar16 == (undefined *)0x0) goto LAB_7ffe9a38a3fb;
      iVar10 = PlayerStatusBase_GetBonusValueWithBuf(puVar16,iVar10,(undefined *)0x0);
      iVar9 = MobAttackBase_calcResistDamage(self,iVar9,iVar10,(undefined *)0x0);
      plVar15 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if (((plVar15 == (longlong *)0x0) ||
          (lVar13 = (**(code **)(*plVar15 + 0x1c8))(plVar15,*(undefined8 *)(*plVar15 + 0x1d0)),
          lVar13 == 0)) || (*(longlong *)(lVar13 + 0x50) == 0)) goto LAB_7ffe9a38a3fb;
      cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar13 + 0x50),0x283,&plStack_58,_DAT_7ffe9c934418);
      if (cVar4 != '\0') {
        if (plStack_58 == (longlong *)0x0) goto LAB_7ffe9a38a3fb;
        bVar6 = *(byte *)(_DAT_7ffe9c914fd0 + 0x130);
        if (((*(byte *)(*plStack_58 + 0x130) < bVar6) ||
            (lVar13 = *(longlong *)(*plStack_58 + 200),
            *(longlong *)(lVar13 + -8 + (ulonglong)bVar6 * 8) != _DAT_7ffe9c914fd0)) ||
           (plStack_58 == (longlong *)0x0)) goto LAB_7ffe9a38a3fb;
        plVar15 = (longlong *)0x0;
        if (*(longlong *)(lVar13 + -8 + (ulonglong)bVar6 * 8) == _DAT_7ffe9c914fd0) {
          plVar15 = plStack_58;
        }
        func_0x7ffe9a79e3d0(plVar15,0);
      }
      plVar15 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar15 == (longlong *)0x0) ||
         (lVar13 = (**(code **)(*plVar15 + 0x1c8))(plVar15,*(undefined8 *)(*plVar15 + 0x1d0)),
         lVar13 == 0)) goto LAB_7ffe9a38a3fb;
      cVar4 = FUN_7ffe9abc2210(lVar13,0x36b,&lStack_50,_DAT_7ffe9c968010);
      if (cVar4 != '\0') {
        if (lStack_50 == 0) goto LAB_7ffe9a38a3fb;
        FUN_7ffe9a781820(lStack_50,self,0);
      }
      pbVar21 = abStackX_18;
      puVar20 = &uStack_64;
      cVar4 = (**(code **)(*(longlong *)self + 0x598))
                        (self,playerAction,mobAction,iVar9,puVar20,pbVar21,
                         *(undefined8 *)(*(longlong *)self + 0x5a0));
      uVar8 = (undefined4)((ulonglong)puVar20 >> 0x20);
      if (cVar4 != '\0') {
        *(undefined4 *)(puVar14 + 0x34) = uStack_64;
        uVar8 = 0;
        iVar9 = MobAttackBase_CalcGuard
                          (self,iVar9,playerAction,(undefined *)&iStack_68,(undefined *)0x0);
      }
      lVar13 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,mobAction);
      if (lVar13 == 0) goto LAB_7ffe9a38a3fb;
      cVar4 = FUN_7ffe9a4daa60(lVar13,0x12);
      if (cVar4 != '\0') {
        cVar4 = FUN_7ffe99742ec0(0x11,_DAT_7ffe9c9724e0,mobAction);
        fVar18 = _DAT_7ffe9c049c7c;
        if (cVar4 == '\0') {
          fVar18 = _DAT_7ffe9c049b4c;
        }
        iVar9 = (int)((_DAT_7ffe9c049b18 - fVar18) * (float)iVar9);
      }
      iVar9 = MobAttackBase_CalcSkillComboTough(self,playerAction,iVar9,(undefined *)0x0);
      iVar9 = MobAttackBase_CalcLastDamage
                        (self,mobAction,playerAction,iVar9,
                         (undefined *)CONCAT44(uVar8,*(undefined4 *)(puVar14 + 0x34)),
                         (undefined *)CONCAT71((int7)((ulonglong)pbVar21 >> 8),1),(undefined *)0x0);
      fVar18 = MobAttackBase_GetDistDamageRegistRate(self,playerAction,mobAction,(undefined *)0x0);
      iVar9 = MobAttackBase_CalcMobaBonusDamageResist
                        (self,(int)(fVar18 * (float)iVar9),playerAction,(undefined *)0x0);
      iVar9 = MobAttackBase_CalcBarrier(self,iVar9,playerAction,mobAction,(undefined *)0x0);
      if (iVar9 < 1) {
        iVar9 = 1;
      }
      bVar6 = MobAttackBase_InvalidDamage(self,playerAction,(undefined *)0x0);
      if (bVar6 != 0) {
        *(undefined4 *)(puVar14 + 0x20) = 4;
        iVar9 = 0;
      }
      plVar15 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
      if ((plVar15 == (longlong *)0x0) ||
         (puVar16 = (undefined *)(**(code **)(*plVar15 + 0x1d8))(plVar15),
         puVar16 == (undefined *)0x0)) goto LAB_7ffe9a38a3fb;
      fVar18 = BonusManager_GetTreasureHuntLastDmgedDownRateBonus(puVar16,(undefined *)0x0);
      puVar16 = (undefined *)(ulonglong)(uint)(int)(fVar18 * (float)iVar9);
    }
    else {
      uVar12 = MobAttackBase_CreateFixDamage
                         (self,*(int *)(lVar13 + 0x14),mobAction,playerAction,puVar14,
                          (undefined *)&iStack_68,abStackX_18,(undefined *)0x0);
      puVar16 = (undefined *)(ulonglong)uVar12;
    }
  }
  if (*(longlong *)(self + 0xa0) != 0) {
    if ((((*(byte *)(*(longlong *)(self + 0xa0) + 0x6c) & 1) != 0) &&
        (*(int *)(puVar14 + 0x1c) == 0)) && (*(int *)(puVar14 + 0x34) != 1)) {
      uVar12 = MobAttackBase_CalcUnavoidableAttack
                         (self,mobAction,playerAction,puVar14,(undefined *)&iStack_68,abStackX_18,
                          (undefined *)0x0);
      puVar16 = (undefined *)(ulonglong)uVar12;
    }
    uVar1 = *(undefined8 *)(puVar14 + 0x48);
    skillDamageData = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c94aa68);
    FUN_7ffe9a8fff70(skillDamageData,uVar1,0);
    if (skillDamageData != (undefined *)0x0) {
      func_0x7ffe9a900040(skillDamageData,puVar16,0);
      *(undefined4 *)(skillDamageData + 0x14) = *(undefined4 *)(puVar14 + 0x1c);
      *(undefined4 *)(skillDamageData + 0x18) = *(undefined4 *)(puVar14 + 0x34);
      *(undefined4 *)(skillDamageData + 0x1c) = *(undefined4 *)(puVar14 + 0x20);
      plVar15 = *(longlong **)(self + 0xa8);
      if (plVar15 != (longlong *)0x0) {
        uVar7 = (**(code **)(*plVar15 + 0x208))(plVar15,*(undefined8 *)(*plVar15 + 0x210));
        skillDamageData[0xa1] = uVar7;
        *(undefined4 *)(skillDamageData + 0x48) = *(undefined4 *)(self + 0xc4);
        *(undefined4 *)(skillDamageData + 0x4c) = *(undefined4 *)(self + 0xd0);
        *(undefined4 *)(skillDamageData + 0x50) = *(undefined4 *)(self + 0xcc);
        *(undefined4 *)(skillDamageData + 0x54) = 0xffffffff;
        skillDamageData[0x5a] = abStackX_18[0];
        *(undefined4 *)(skillDamageData + 0x6c) = *(undefined4 *)(self + 0xd8);
        if ((*(int *)(puVar14 + 0x1c) != 0) && (*(int *)(puVar14 + 0x34) != 1)) {
          *(uint *)(skillDamageData + 0x70) =
               *(uint *)(skillDamageData + 0x70) | -(uint)(self[200] != '\0') & 8;
          *(uint *)(skillDamageData + 0x70) =
               *(uint *)(skillDamageData + 0x70) | -(uint)(self[0xd4] != '\0') & 0x800;
          puVar16 = (undefined *)
                    (**(code **)(*(longlong *)playerAction + 0x298))
                              (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
          MobAttackBase_SetAbnormalEffect
                    (self,skillDamageData,puVar16,iStack_68,abStackX_18[0],(undefined *)0x0);
        }
        if (self[0xd5] != '\0') {
          *(uint *)(skillDamageData + 0x70) = *(uint *)(skillDamageData + 0x70) | 0x10000;
        }
        MobAttackBase_FinawGuard(self,skillDamageData,iStack_68,(undefined *)0x0);
        *(undefined **)(puVar14 + 0x38) = skillDamageData;
        il2cpp_write_barrier_0();
        if (*(longlong *)(self + 0x80) != 0) {
          FUN_7ffe99743100(*(longlong *)(self + 0x80),puVar14,_DAT_7ffe9c913488);
          return;
        }
      }
    }
  }
LAB_7ffe9a38a3fb:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

