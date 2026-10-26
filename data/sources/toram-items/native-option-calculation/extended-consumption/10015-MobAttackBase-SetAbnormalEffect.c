
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobAttackBase_SetAbnormalEffect
               (undefined *self,undefined *skillDamageData,undefined *status,int guardPower,
               byte justGuard,undefined *baseAbnormalType,int baseAbnormalPercent,
               int abnormalEffectTime,undefined *methodInfo)

{
  int iVar1;
  code *pcVar2;
  bool bVar3;
  bool bVar4;
  char cVar5;
  byte bVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  longlong lVar12;
  undefined *armorItem;
  undefined *puVar13;
  uint uVar14;
  int iVar15;
  int iVar16;
  float fVar17;
  int iStackX_18;
  longlong *plStack_80;
  longlong *plStack_78;
  longlong *plStack_70;
  longlong *aplStack_68 [6];
  
  puVar13 = baseAbnormalType;
  if (DAT_7ffe9cadd7da == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92dfe0);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c9548c8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f77d0);
    DAT_7ffe9cadd7da = '\x01';
  }
  iVar11 = (int)baseAbnormalType;
  iVar15 = 0;
  plStack_80 = (longlong *)0x0;
  plStack_78 = (longlong *)0x0;
  plStack_70 = (longlong *)0x0;
  aplStack_68[0] = (longlong *)0x0;
  if (((status == (undefined *)0x0) ||
      (lVar12 = (**(code **)(*(longlong *)status + 0x1c8))
                          (status,*(undefined8 *)(*(longlong *)status + 0x1d0)), lVar12 == 0)) ||
     (*(longlong *)(lVar12 + 0x40) == 0)) goto LAB_7ffe9a37722c;
  cVar5 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x40),0x325,&plStack_80,_DAT_7ffe9c934418);
  if (cVar5 != '\0') {
    if (plStack_80 == (longlong *)0x0) goto LAB_7ffe9a37722c;
    uVar7 = (**(code **)(*plStack_80 + 0x1f8))(plStack_80,0x26,*(undefined8 *)(*plStack_80 + 0x200))
    ;
    cVar5 = FUN_7ffe9a8fea70(self,100,uVar7,0);
    if (cVar5 == '\0') goto LAB_7ffe9a37692a;
LAB_7ffe9a3769ce:
    if (skillDamageData == (undefined *)0x0) goto LAB_7ffe9a37722c;
    goto LAB_7ffe9a377029;
  }
LAB_7ffe9a37692a:
  lVar12 = (**(code **)(*(longlong *)status + 0x1c8))
                     (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
  if ((lVar12 == 0) || (*(longlong *)(lVar12 + 0x40) == 0)) goto LAB_7ffe9a37722c;
  cVar5 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x40),0x327,&plStack_80,_DAT_7ffe9c934418);
  if (cVar5 != '\0') {
    if ((int)baseAbnormalType == 1) {
      if (plStack_80 == (longlong *)0x0) goto LAB_7ffe9a37722c;
      uVar14 = ((uint)*(byte *)(plStack_80 + 2) + (uint)*(byte *)(plStack_80 + 2) * 4) * 4;
      if (100 < uVar14) {
        uVar14 = 100;
      }
    }
    else {
      if ((int)baseAbnormalType != 2) goto LAB_7ffe9a3769dc;
      if (plStack_80 == (longlong *)0x0) goto LAB_7ffe9a37722c;
      iVar8 = 0;
      if (-1 < (int)(*(byte *)(plStack_80 + 2) - 5)) {
        iVar8 = *(byte *)(plStack_80 + 2) - 5;
      }
      uVar14 = iVar8 * 0xf;
    }
    cVar5 = FUN_7ffe9a8fea70(self,100,uVar14,0);
    if (cVar5 != '\0') goto LAB_7ffe9a3769ce;
  }
LAB_7ffe9a3769dc:
  lVar12 = (**(code **)(*(longlong *)status + 0x1c8))
                     (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
  if (lVar12 == 0) goto LAB_7ffe9a37722c;
  cVar5 = FUN_7ffe9a7c6d00(lVar12,0x37);
  if (((cVar5 != '\0') && (justGuard != 0)) &&
     (((int)baseAbnormalType - 1U < 3 || ((int)baseAbnormalType == 4)))) goto LAB_7ffe9a3769ce;
  lVar12 = (**(code **)(*(longlong *)status + 0x1c8))
                     (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
  if (lVar12 == 0) goto LAB_7ffe9a37722c;
  cVar5 = FUN_7ffe9a7c6d00(lVar12,0x96,0);
  if ((cVar5 != '\0') && (((int)baseAbnormalType - 0xbU < 2 || ((int)baseAbnormalType == 0x1c))))
  goto LAB_7ffe9a3769ce;
  baseAbnormalType._0_4_ = 0;
  if ((*(byte *)(_DAT_7ffe9c8f77d0 + 0x130) <= *(byte *)(*(longlong *)status + 0x130)) &&
     (*(longlong *)
       (*(longlong *)(*(longlong *)status + 200) + -8 +
       (ulonglong)*(byte *)(_DAT_7ffe9c8f77d0 + 0x130) * 8) == _DAT_7ffe9c8f77d0)) {
    if (*(longlong *)(status + 0x90) == 0) goto LAB_7ffe9a37722c;
    cVar5 = FUN_7ffe9a58d6a0(*(longlong *)(status + 0x90),3,&plStack_78,&plStack_70,0);
    if (cVar5 != '\0') {
      bVar3 = false;
      if (plStack_78 != (longlong *)0x0) {
        iVar8 = (**(code **)(*plStack_78 + 0x198))(plStack_78,*(undefined8 *)(*plStack_78 + 0x1a0));
        if (iVar8 != iVar11) {
          if (plStack_78 == (longlong *)0x0) goto LAB_7ffe9a37722c;
          iVar8 = (**(code **)(*plStack_78 + 0x198))
                            (plStack_78,*(undefined8 *)(*plStack_78 + 0x1a0));
          if ((iVar8 != 1) || (iVar11 != 0)) goto LAB_7ffe9a376b1a;
        }
        bVar3 = true;
      }
LAB_7ffe9a376b1a:
      if (plStack_70 == (longlong *)0x0) {
LAB_7ffe9a376b6b:
        if (!bVar3) goto LAB_7ffe9a376b74;
      }
      else {
        iVar8 = (**(code **)(*plStack_70 + 0x198))(plStack_70,*(undefined8 *)(*plStack_70 + 0x1a0));
        if (iVar8 != iVar11) {
          if (plStack_70 == (longlong *)0x0) goto LAB_7ffe9a37722c;
          iVar8 = (**(code **)(*plStack_70 + 0x198))
                            (plStack_70,*(undefined8 *)(*plStack_70 + 0x1a0));
          if ((iVar8 != 1) || (iVar11 != 0)) goto LAB_7ffe9a376b6b;
        }
      }
      goto LAB_7ffe9a3769ce;
    }
LAB_7ffe9a376b74:
    if (*(longlong *)(status + 0x98) == 0) goto LAB_7ffe9a37722c;
    baseAbnormalType._0_4_ =
         FUN_7ffe9a589ec0(*(longlong *)(status + 0x98),(ulonglong)puVar13 & 0xffffffff,0);
  }
  if (iVar11 == 0) {
    if (skillDamageData == (undefined *)0x0) goto LAB_7ffe9a37722c;
    *(undefined4 *)(skillDamageData + 0x8c) = 0xffffffff;
    *(float *)(skillDamageData + 0x94) = (float)abnormalEffectTime;
    uVar7 = *(undefined4 *)(skillDamageData + 0x8c);
    if (*(int *)(_DAT_7ffe9c92dfe0 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    uVar7 = FUN_7ffe9a4daf00(uVar7);
    *(undefined4 *)(skillDamageData + 0x98) = uVar7;
  }
  else {
    lVar12 = (**(code **)(*(longlong *)status + 0x1a8))
                       (status,*(undefined8 *)(*(longlong *)status + 0x1b0));
    if (lVar12 == 0) goto LAB_7ffe9a37722c;
    iVar8 = FUN_7ffe99742ec0(0x1f,_DAT_7ffe9c940d40,lVar12);
    lVar12 = (**(code **)(*(longlong *)status + 0x1c8))
                       (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
    if (lVar12 == 0) goto LAB_7ffe9a37722c;
    cVar5 = FUN_7ffe9a7cbb30(lVar12,0x209,&plStack_80,0);
    if (cVar5 != '\0') {
      if (plStack_80 == (longlong *)0x0) goto LAB_7ffe9a37722c;
      if (((*(byte *)(*plStack_80 + 0x130) < *(byte *)(_DAT_7ffe9c9548c8 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*plStack_80 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7ffe9c9548c8 + 0x130) * 8) != _DAT_7ffe9c9548c8)) ||
         (plStack_80 == (longlong *)0x0)) {
        FUN_7ffe9996c950(plStack_80);
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      iVar9 = FUN_7ffe9a796080(plStack_80,(ulonglong)puVar13 & 0xffffffff,status,0);
      iVar8 = iVar8 + iVar9;
    }
    if (skillDamageData == (undefined *)0x0) goto LAB_7ffe9a37722c;
    if ((*(int *)(skillDamageData + 0x18) - 2U & 0xfffffffb) == 0) {
      iVar9 = 10000;
      if (guardPower < 0x2711) {
        iVar9 = guardPower;
      }
      iVar16 = iVar9 / 2;
      if (*(int *)(skillDamageData + 0x18) != 6) {
        iVar16 = iVar9;
      }
      lVar12 = (**(code **)(*(longlong *)status + 0x1b8))
                         (status,*(undefined8 *)(*(longlong *)status + 0x1c0));
      if ((lVar12 == 0) || (*(longlong *)(lVar12 + 0x68) == 0)) goto LAB_7ffe9a37722c;
      cVar5 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x68),0xa5,aplStack_68,_DAT_7ffe9c935bd0);
      if (cVar5 != '\0') {
        if ((aplStack_68[0] == (longlong *)0x0) || (aplStack_68[0][2] == 0)) goto LAB_7ffe9a37722c;
        if (*(char *)(aplStack_68[0][2] + 0x18) != '\0') {
          iVar9 = (**(code **)(*aplStack_68[0] + 0x178))
                            (aplStack_68[0],0,*(undefined8 *)(*aplStack_68[0] + 0x180));
          lVar12 = (**(code **)(*(longlong *)status + 0x198))
                             (status,*(undefined8 *)(*(longlong *)status + 0x1a0));
          if (lVar12 == 0) goto LAB_7ffe9a37722c;
          iVar10 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar12);
          lVar12 = (**(code **)(*(longlong *)status + 0x178))
                             (status,*(undefined8 *)(*(longlong *)status + 0x180));
          if (lVar12 == 0) goto LAB_7ffe9a37722c;
          iVar1 = *(int *)(lVar12 + 0x10);
          lVar12 = (**(code **)(*(longlong *)status + 0x178))
                             (status,*(undefined8 *)(*(longlong *)status + 0x180));
          if (lVar12 == 0) goto LAB_7ffe9a37722c;
          if ((iVar1 + *(int *)(lVar12 + 0x20) <= (int)((float)(iVar10 * iVar9) * _DAT_7ffe9c049b34)
              ) && (iVar16 = iVar16 * 2, 10000 < iVar16)) {
            iVar16 = 10000;
          }
        }
      }
      if (iVar16 / 100 <= iVar8) goto LAB_7ffe9a376e51;
      bVar3 = true;
      iVar8 = iVar16 / 100;
    }
    else {
LAB_7ffe9a376e51:
      bVar3 = false;
    }
    iVar9 = iVar15;
    bVar4 = false;
    if (iVar11 != 0x26) {
      iVar9 = iVar8;
      bVar4 = bVar3;
    }
    iStackX_18 = baseAbnormalPercent;
    lVar12 = *(longlong *)(self + 0xa8);
    if ((lVar12 != 0) && (-1 < *(int *)(lVar12 + 0x5c))) {
      iStackX_18 = *(int *)(lVar12 + 0x5c);
    }
    iVar8 = iVar15;
    if (-1 < iStackX_18 + -100) {
      iVar8 = iStackX_18 + -100;
    }
    iVar8 = ((iStackX_18 - iVar8) * (100 - iVar9)) / 100 + iVar8;
    lVar12 = (**(code **)(*(longlong *)status + 0x1f8))
                       (status,*(undefined8 *)(*(longlong *)status + 0x200));
    if (lVar12 == 0) goto LAB_7ffe9a37722c;
    armorItem = (undefined *)FUN_7ffe99c08d90(lVar12,0);
    bVar6 = ItemDBData_CheckArmorAbility(armorItem,(undefined *)0x2,(undefined *)0x0);
    iVar9 = 0;
    if (bVar6 != 0) {
      if (iVar11 == 1) {
        if ((baseAbnormalPercent < 200) && (iVar16 = iVar8 + -100, iVar8 = iVar9, -1 < iVar16)) {
          iVar8 = iVar16;
        }
      }
      else if (iVar11 == 4) {
        fVar17 = _DAT_7ffe9c049b18;
        if (_DAT_7ffe9c049b18 <= (float)abnormalEffectTime * _DAT_7ffe9c049b4c) {
          fVar17 = (float)abnormalEffectTime * _DAT_7ffe9c049b4c;
        }
        abnormalEffectTime = (int)fVar17;
      }
    }
    if (-1 < iVar8 - (int)baseAbnormalType) {
      iVar15 = iVar8 - (int)baseAbnormalType;
    }
    cVar5 = FUN_7ffe9a8fea70(self,100,iVar15,0);
    if (cVar5 == '\0') {
      if (bVar4) {
        *(int *)(skillDamageData + 0x90) = iVar11;
        if (*(int *)(_DAT_7ffe9c92dfe0 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        uVar7 = FUN_7ffe9a4daf00((ulonglong)puVar13 & 0xffffffff);
        *(undefined4 *)(skillDamageData + 0x98) = uVar7;
      }
    }
    else {
      lVar12 = (**(code **)(*(longlong *)status + 0x1c8))
                         (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
      if ((lVar12 == 0) || (*(longlong *)(lVar12 + 0x50) == 0)) goto LAB_7ffe9a37722c;
      cVar5 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x50),0xe9,&plStack_80,_DAT_7ffe9c934418);
      if (cVar5 != '\0') {
        if (plStack_80 == (longlong *)0x0) goto LAB_7ffe9a37722c;
        iVar9 = (**(code **)(*plStack_80 + 0x1f8))
                          (plStack_80,0x25,*(undefined8 *)(*plStack_80 + 0x200));
      }
      iVar15 = 0;
      if (-1 < iVar9) {
        iVar15 = iVar9;
      }
      if (100 < iVar15) {
        iVar15 = 100;
      }
      cVar5 = FUN_7ffe9a8fea70(self,100,100 - iVar15,0);
      if (cVar5 != '\0') {
        fVar17 = (float)abnormalEffectTime;
        if (iVar11 == 4) {
          fVar17 = fVar17 / _DAT_7ffe9c049ce4;
        }
        *(float *)(skillDamageData + 0x94) = fVar17;
        *(int *)(skillDamageData + 0x8c) = iVar11;
        if (*(int *)(_DAT_7ffe9c92dfe0 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        uVar7 = FUN_7ffe9a4daf00((ulonglong)puVar13 & 0xffffffff);
        *(undefined4 *)(skillDamageData + 0x98) = uVar7;
        lVar12 = (**(code **)(*(longlong *)status + 0x1f8))
                           (status,*(undefined8 *)(*(longlong *)status + 0x200));
        if (lVar12 == 0) goto LAB_7ffe9a37722c;
        puVar13 = (undefined *)FUN_7ffe99c08d90(lVar12,0);
        bVar6 = ItemDBData_CheckArmorAbility(puVar13,(undefined *)0x2,(undefined *)0x0);
        if (((bVar6 != 0) && (iVar11 == 3)) && (1 < abnormalEffectTime)) {
          iVar11 = 1;
          if (0 < abnormalEffectTime + -1) {
            iVar11 = abnormalEffectTime + -1;
          }
          *(float *)(skillDamageData + 0x94) = (float)iVar11;
          if (*(int *)(_DAT_7ffe9c92dfe0 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          uVar7 = FUN_7ffe9a4daf00(3);
          *(undefined4 *)(skillDamageData + 0x98) = uVar7;
        }
        if (100 < iStackX_18) {
          *(uint *)(skillDamageData + 0x70) = *(uint *)(skillDamageData + 0x70) | 1;
        }
      }
    }
  }
  if ((*(int *)(skillDamageData + 0x8c) != 1) && (*(int *)(skillDamageData + 0x8c) != -1)) {
    return;
  }
  lVar12 = (**(code **)(*(longlong *)status + 0x1c8))
                     (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
  if ((lVar12 != 0) && (*(longlong *)(lVar12 + 0x50) != 0)) {
    cVar5 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x50),0x346,&plStack_80,_DAT_7ffe9c934418);
    if (cVar5 == '\0') {
      return;
    }
    if (plStack_80 != (longlong *)0x0) {
      uVar7 = (**(code **)(*plStack_80 + 0x1f8))
                        (plStack_80,0x25,*(undefined8 *)(*plStack_80 + 0x200));
      cVar5 = FUN_7ffe9a8fea70(self,100,uVar7,0);
      if (cVar5 == '\0') {
        return;
      }
LAB_7ffe9a377029:
      FUN_7ffe9a8ffe30(skillDamageData,0,0,0);
      return;
    }
  }
LAB_7ffe9a37722c:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

