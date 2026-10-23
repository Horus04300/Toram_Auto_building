
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
UIItemProperty_AddCapProperty
          (byte isColor,short id,short val,undefined *itemPropertyTextManager,
          undefined *systemManager,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  longlong lVar3;
  undefined8 uVar4;
  longlong *plVar5;
  undefined8 uVar6;
  longlong *plVar7;
  longlong lVar8;
  undefined *puVar9;
  int iVar10;
  undefined8 uVar11;
  float fVar12;
  float afStackX_10 [2];
  float fStack_68;
  uint uStack_64;
  float afStack_60 [2];
  undefined8 uStack_58;
  undefined8 uStack_50;
  int iStack_48;
  
  iVar10 = (int)id;
  if (DAT_7ffe9cadbb13 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c948908);
    FUN_7ffe9996d590(&DAT_7ffe9c8f46c8);
    FUN_7ffe9996d590(&DAT_7ffe9c8fd6f8);
    FUN_7ffe9996d590(&DAT_7ffe9c90a810);
    FUN_7ffe9996d590(&DAT_7ffe9c91b0b8);
    FUN_7ffe9996d590(&DAT_7ffe9c949440);
    FUN_7ffe9996d590(&DAT_7ffe9c9540a0);
    FUN_7ffe9996d590(&DAT_7ffe9c953578);
    FUN_7ffe9996d590(&DAT_7ffe9c94be50);
    FUN_7ffe9996d590(&DAT_7ffe9c9590b8);
    FUN_7ffe9996d590(&DAT_7ffe9c8ee100);
    FUN_7ffe9996d590(&DAT_7ffe9c914158);
    FUN_7ffe9996d590(&DAT_7ffe9c916818);
    FUN_7ffe9996d590(&DAT_7ffe9c91f5d8);
    FUN_7ffe9996d590(&DAT_7ffe9c8fbe30);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1820);
    FUN_7ffe9996d590(&DAT_7ffe9c920578);
    DAT_7ffe9cadbb13 = '\x01';
  }
  if (id < 1) {
    return _DAT_7ffe9c8f1820;
  }
  if (*(int *)(_DAT_7ffe9c948908 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  fVar12 = BonusManager_GetBonusTime(iVar10,(undefined *)0x0);
  fVar12 = fVar12 * (float)(int)val;
  if (*(int *)(_DAT_7ffe9c8ee100 + 0xe0) == 0) {
    func_0x7ffe9996d830(_DAT_7ffe9c8ee100);
  }
  cVar2 = FUN_7ffe9ab7f110(**(undefined8 **)(_DAT_7ffe9c8ee100 + 0xb8),id);
  uVar4 = _DAT_7ffe9c920578;
  if (cVar2 != '\0') {
    lVar3 = FUN_7ffe9b141840(_DAT_7ffe9c9540a0);
    if ((lVar3 == 0) || (*(longlong *)(lVar3 + 0x28) == 0)) goto LAB_7ffe99ec3ba0;
    uVar4 = FUN_7ffe99a87380(*(longlong *)(lVar3 + 0x28),0);
  }
  uVar6 = _DAT_7ffe9c91f5d8;
  if (iVar10 == 0x41) {
    if (itemPropertyTextManager == (undefined *)0x0) goto LAB_7ffe99ec3ba0;
    lVar3 = func_0x7ffe9996d210(*(undefined8 *)
                                 (*(longlong *)itemPropertyTextManager +
                                 ((ulonglong)*(ushort *)(_DAT_7ffe9c90a810 + 0x50) + 0x14) * 0x10));
    plVar5 = (longlong *)(**(code **)(lVar3 + 8))(itemPropertyTextManager,0x41,lVar3);
    if (plVar5 == (longlong *)0x0) {
      return _DAT_7ffe9c8f1820;
    }
    lVar3 = (**(code **)(*plVar5 + 0x178))(plVar5,*(undefined8 *)(*plVar5 + 0x180));
    uStack_58 = _DAT_7ffe9c8f46c8;
    iStack_48 = (int)fVar12;
    uStack_50 = 0xffffffffffffffff;
    uVar6 = FUN_7ffe9b5439f0(&uStack_58,0);
    if (systemManager == (undefined *)0x0) {
      FUN_7ffe9996d7a0();
      pcVar1 = (code *)swi(3);
      puVar9 = (undefined *)(*pcVar1)();
      return puVar9;
    }
    uVar6 = FUN_7ffe99a58320(systemManager,uVar6,0);
  }
  else {
    if ((((ushort)(id - 0xa6U) < 10) || (id == 0xbc)) || (iVar10 == 0x30)) {
      if (0.0 <= fVar12) {
        if (itemPropertyTextManager != (undefined *)0x0) {
          plVar5 = (longlong *)FUN_7ffe99746fc0(_DAT_7ffe9c90a810,itemPropertyTextManager,iVar10);
          plVar7 = (longlong *)func_0x7ffe9996c990(_DAT_7ffe9c91b0b8,1);
          fStack_68 = fVar12;
          lVar3 = func_0x7ffe9996c8e0(_DAT_7ffe9c949440,&fStack_68);
          if (plVar7 != (longlong *)0x0) {
            if ((lVar3 != 0) &&
               (lVar8 = func_0x7ffe9996c920(lVar3,*(undefined8 *)(*plVar7 + 0x40)), lVar8 == 0)) {
              uVar4 = func_0x7ffe9996d1f0();
              FUN_7ffe9996d760(uVar4,0);
              pcVar1 = (code *)swi(3);
              puVar9 = (undefined *)(*pcVar1)();
              return puVar9;
            }
            if ((int)plVar7[3] == 0) {
              FUN_7ffe9996d790();
              pcVar1 = (code *)swi(3);
              puVar9 = (undefined *)(*pcVar1)();
              return puVar9;
            }
            plVar7[4] = lVar3;
            il2cpp_write_barrier_0();
            if (plVar5 != (longlong *)0x0) {
              puVar9 = (undefined *)
                       (**(code **)(*plVar5 + 0x1a8))
                                 (plVar5,plVar7,*(undefined8 *)(*plVar5 + 0x1b0));
              uVar6 = uVar4;
              goto LAB_7ffe99ec3af1;
            }
          }
        }
        FUN_7ffe9996d7a0();
        pcVar1 = (code *)swi(3);
        puVar9 = (undefined *)(*pcVar1)();
        return puVar9;
      }
      if (itemPropertyTextManager == (undefined *)0x0) goto LAB_7ffe99ec3ba0;
      plVar5 = (longlong *)FUN_7ffe99746fc0(_DAT_7ffe9c90a810,itemPropertyTextManager,-iVar10);
      if (plVar5 == (longlong *)0x0) {
        plVar5 = (longlong *)FUN_7ffe99746fc0(_DAT_7ffe9c90a810,itemPropertyTextManager,iVar10);
        plVar7 = (longlong *)func_0x7ffe9996c990(_DAT_7ffe9c91b0b8,1);
        afStack_60[0] = fVar12;
        lVar3 = func_0x7ffe9996c8e0(_DAT_7ffe9c949440,afStack_60);
        if (plVar7 != (longlong *)0x0) {
          if ((lVar3 != 0) &&
             (lVar8 = func_0x7ffe9996c920(lVar3,*(undefined8 *)(*plVar7 + 0x40)), lVar8 == 0)) {
            uVar4 = func_0x7ffe9996d1f0();
            FUN_7ffe9996d760(uVar4,0);
            pcVar1 = (code *)swi(3);
            puVar9 = (undefined *)(*pcVar1)();
            return puVar9;
          }
          if ((int)plVar7[3] == 0) {
            FUN_7ffe9996d790();
            pcVar1 = (code *)swi(3);
            puVar9 = (undefined *)(*pcVar1)();
            return puVar9;
          }
          plVar7[4] = lVar3;
          il2cpp_write_barrier_0();
          if ((plVar5 != (longlong *)0x0) &&
             (lVar3 = (**(code **)(*plVar5 + 0x1a8))(plVar5,plVar7,*(undefined8 *)(*plVar5 + 0x1b0))
             , lVar3 != 0)) {
            puVar9 = (undefined *)FUN_7ffe9b36e700(lVar3,_DAT_7ffe9c914158,_DAT_7ffe9c8f1820,0);
            goto LAB_7ffe99ec3af1;
          }
        }
        FUN_7ffe9996d7a0();
        pcVar1 = (code *)swi(3);
        puVar9 = (undefined *)(*pcVar1)();
        return puVar9;
      }
      plVar7 = (longlong *)func_0x7ffe9996c990(_DAT_7ffe9c91b0b8,1);
      uStack_64 = (uint)fVar12 ^ _DAT_7ffe9c049c00;
      lVar3 = func_0x7ffe9996c8e0(_DAT_7ffe9c949440,&uStack_64);
      if (plVar7 == (longlong *)0x0) {
        FUN_7ffe9996d7a0();
        pcVar1 = (code *)swi(3);
        puVar9 = (undefined *)(*pcVar1)();
        return puVar9;
      }
      if ((lVar3 != 0) &&
         (lVar8 = func_0x7ffe9996c920(lVar3,*(undefined8 *)(*plVar7 + 0x40)), lVar8 == 0)) {
        uVar4 = func_0x7ffe9996d1f0();
        FUN_7ffe9996d760(uVar4,0);
        pcVar1 = (code *)swi(3);
        puVar9 = (undefined *)(*pcVar1)();
        return puVar9;
      }
      if ((int)plVar7[3] == 0) {
        FUN_7ffe9996d790();
        pcVar1 = (code *)swi(3);
        puVar9 = (undefined *)(*pcVar1)();
        return puVar9;
      }
      plVar7[4] = lVar3;
      il2cpp_write_barrier_0();
      puVar9 = (undefined *)
               (**(code **)(*plVar5 + 0x1a8))(plVar5,plVar7,*(undefined8 *)(*plVar5 + 0x1b0));
      goto LAB_7ffe99ec3af1;
    }
    if (id == 0xbd) {
      puVar9 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c953578);
      if (puVar9 != (undefined *)0x0) {
        plVar5 = (longlong *)LocalizeManager_Get(puVar9,(undefined *)0x2,(undefined *)0x0);
        iVar10 = SkillManager_GetAvatarSkillId((int)val,(undefined *)0x0);
        if (plVar5 != (longlong *)0x0) {
          if ((*(byte *)(_DAT_7ffe9c94be50 + 0x130) <= *(byte *)(*plVar5 + 0x130)) &&
             (*(longlong *)
               (*(longlong *)(*plVar5 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c94be50 + 0x130) * 8) == _DAT_7ffe9c94be50)) {
            puVar9 = SkillTextManager_GetSkillName((undefined *)plVar5,iVar10,(undefined *)0x0);
            return puVar9;
          }
          FUN_7ffe9996c950(plVar5,_DAT_7ffe9c94be50);
          pcVar1 = (code *)swi(3);
          puVar9 = (undefined *)(*pcVar1)();
          return puVar9;
        }
      }
LAB_7ffe99ec3ba0:
      FUN_7ffe9996d7a0();
      pcVar1 = (code *)swi(3);
      puVar9 = (undefined *)(*pcVar1)();
      return puVar9;
    }
    if (itemPropertyTextManager == (undefined *)0x0) goto LAB_7ffe99ec3ba0;
    plVar5 = (longlong *)FUN_7ffe99746fc0(_DAT_7ffe9c90a810,itemPropertyTextManager,iVar10);
    if (plVar5 == (longlong *)0x0) {
      return _DAT_7ffe9c8f1820;
    }
    lVar3 = (**(code **)(*plVar5 + 0x178))(plVar5,*(undefined8 *)(*plVar5 + 0x180));
    uVar11 = _DAT_7ffe9c91f5d8;
    if (fVar12 < 0.0) {
      if (lVar3 == 0) goto LAB_7ffe99ec3ba0;
      lVar3 = FUN_7ffe9b36e700(lVar3,_DAT_7ffe9c914158,_DAT_7ffe9c8f1820,0);
    }
    else {
      uVar11 = uVar4;
      if (fVar12 == 0.0) {
        uVar11 = _DAT_7ffe9c916818;
      }
    }
    afStackX_10[0] = fVar12;
    uVar6 = func_0x7ffe9996c8e0(_DAT_7ffe9c949440,afStackX_10);
    uVar4 = uVar11;
  }
  puVar9 = (undefined *)FUN_7ffe9b36a740(lVar3,uVar6,0);
  uVar6 = uVar4;
LAB_7ffe99ec3af1:
  if (isColor != 0) {
    puVar9 = (undefined *)FUN_7ffe9b36a9f0(_DAT_7ffe9c8fbe30,uVar6,puVar9,0);
  }
  return puVar9;
}

