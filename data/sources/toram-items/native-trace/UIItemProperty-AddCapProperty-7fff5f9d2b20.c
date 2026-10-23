
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
UIItemProperty_AddCapProperty
          (byte isColor,short id,short val,undefined *itemPropertyTextManager,
          undefined *systemManager,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  undefined4 uVar3;
  longlong lVar4;
  undefined8 uVar5;
  longlong *plVar6;
  undefined8 uVar7;
  longlong *plVar8;
  longlong lVar9;
  undefined *puVar10;
  int bonusType;
  undefined8 uVar11;
  float fVar12;
  float afStackX_10 [2];
  float fStack_68;
  uint uStack_64;
  float afStack_60 [2];
  undefined8 uStack_58;
  undefined8 uStack_50;
  int iStack_48;
  
  bonusType = (int)id;
  if (DAT_7fff625e328e == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62450248);
    FUN_7fff5f47d450(&DAT_7fff623fc188);
    FUN_7fff5f47d450(&DAT_7fff62404658);
    FUN_7fff5f47d450(&DAT_7fff62411770);
    FUN_7fff5f47d450(&DAT_7fff62422c48);
    FUN_7fff5f47d450(&DAT_7fff62450b30);
    FUN_7fff5f47d450(&DAT_7fff6245af88);
    FUN_7fff5f47d450(&DAT_7fff6245a460);
    FUN_7fff5f47d450(&DAT_7fff62453550);
    FUN_7fff5f47d450(&DAT_7fff624606c8);
    FUN_7fff5f47d450(&DAT_7fff623f57b0);
    FUN_7fff5f47d450(&DAT_7fff6241a898);
    FUN_7fff5f47d450(&DAT_7fff6241c668);
    FUN_7fff5f47d450(&DAT_7fff62425428);
    FUN_7fff5f47d450(&DAT_7fff62401c80);
    FUN_7fff5f47d450(&DAT_7fff623f7f60);
    FUN_7fff5f47d450(&DAT_7fff624263c8);
    DAT_7fff625e328e = '\x01';
  }
  if (id < 1) {
    return _DAT_7fff623f7f60;
  }
  if (*(int *)(_DAT_7fff62450248 + 0xe0) == 0) {
    func_0x7fff5f47d6f0();
  }
  fVar12 = BonusManager_GetBonusTime(bonusType,(undefined *)0x0);
  fVar12 = fVar12 * (float)(int)val;
  if (*(int *)(_DAT_7fff623f57b0 + 0xe0) == 0) {
    func_0x7fff5f47d6f0(_DAT_7fff623f57b0);
  }
  cVar2 = FUN_7fff606894c0(**(undefined8 **)(_DAT_7fff623f57b0 + 0xb8),id,_DAT_7fff62404658);
  uVar5 = _DAT_7fff624263c8;
  if (cVar2 != '\0') {
    lVar4 = FUN_7fff60c4bc00(_DAT_7fff6245af88);
    if ((lVar4 == 0) || (*(longlong *)(lVar4 + 0x28) == 0)) goto LAB_7fff5f9d31f0;
    uVar5 = FUN_7fff5f597050(*(longlong *)(lVar4 + 0x28),0);
  }
  uVar7 = _DAT_7fff62425428;
  if (bonusType == 0x41) {
    if (itemPropertyTextManager == (undefined *)0x0) goto LAB_7fff5f9d31f0;
    lVar4 = func_0x7fff5f47d0d0(*(undefined8 *)
                                 (*(longlong *)itemPropertyTextManager +
                                 ((ulonglong)*(ushort *)(_DAT_7fff62411770 + 0x50) + 0x14) * 0x10));
    plVar6 = (longlong *)(**(code **)(lVar4 + 8))(itemPropertyTextManager,0x41,lVar4);
    if (plVar6 == (longlong *)0x0) {
      return _DAT_7fff623f7f60;
    }
    lVar4 = (**(code **)(*plVar6 + 0x178))(plVar6,*(undefined8 *)(*plVar6 + 0x180));
    uStack_58 = _DAT_7fff623fc188;
    iStack_48 = (int)fVar12;
    uStack_50 = 0xffffffffffffffff;
    uVar7 = FUN_7fff6104ddb0(&uStack_58,0);
    if (systemManager == (undefined *)0x0) {
      FUN_7fff5f47d660();
      pcVar1 = (code *)swi(3);
      puVar10 = (undefined *)(*pcVar1)();
      return puVar10;
    }
    uVar7 = FUN_7fff5f568150(systemManager,uVar7,0);
  }
  else {
    if ((((ushort)(id - 0xa6U) < 10) || (id == 0xbc)) || (bonusType == 0x30)) {
      if (0.0 <= fVar12) {
        if (itemPropertyTextManager != (undefined *)0x0) {
          plVar6 = (longlong *)FUN_7fff5f256fc0(_DAT_7fff62411770,itemPropertyTextManager,bonusType)
          ;
          plVar8 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
          fStack_68 = fVar12;
          lVar4 = func_0x7fff5f47c7a0(_DAT_7fff62450b30,&fStack_68);
          if (plVar8 != (longlong *)0x0) {
            if ((lVar4 != 0) &&
               (lVar9 = func_0x7fff5f47c7e0(lVar4,*(undefined8 *)(*plVar8 + 0x40)), lVar9 == 0)) {
              uVar5 = func_0x7fff5f47d0b0();
              FUN_7fff5f47d620(uVar5,0);
              pcVar1 = (code *)swi(3);
              puVar10 = (undefined *)(*pcVar1)();
              return puVar10;
            }
            if ((int)plVar8[3] == 0) {
              FUN_7fff5f47d650();
              pcVar1 = (code *)swi(3);
              puVar10 = (undefined *)(*pcVar1)();
              return puVar10;
            }
            plVar8[4] = lVar4;
            thunk_FUN_7fff5f491fd0();
            if (plVar6 != (longlong *)0x0) {
              puVar10 = (undefined *)
                        (**(code **)(*plVar6 + 0x1a8))
                                  (plVar6,plVar8,*(undefined8 *)(*plVar6 + 0x1b0));
              uVar7 = uVar5;
              goto LAB_7fff5f9d3141;
            }
          }
        }
        FUN_7fff5f47d660();
        pcVar1 = (code *)swi(3);
        puVar10 = (undefined *)(*pcVar1)();
        return puVar10;
      }
      if (itemPropertyTextManager == (undefined *)0x0) goto LAB_7fff5f9d31f0;
      plVar6 = (longlong *)FUN_7fff5f256fc0(_DAT_7fff62411770,itemPropertyTextManager,-bonusType);
      if (plVar6 == (longlong *)0x0) {
        plVar6 = (longlong *)FUN_7fff5f256fc0(_DAT_7fff62411770,itemPropertyTextManager,bonusType);
        plVar8 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
        afStack_60[0] = fVar12;
        lVar4 = func_0x7fff5f47c7a0(_DAT_7fff62450b30,afStack_60);
        if (plVar8 != (longlong *)0x0) {
          if ((lVar4 != 0) &&
             (lVar9 = func_0x7fff5f47c7e0(lVar4,*(undefined8 *)(*plVar8 + 0x40)), lVar9 == 0)) {
            uVar5 = func_0x7fff5f47d0b0();
            FUN_7fff5f47d620(uVar5,0);
            pcVar1 = (code *)swi(3);
            puVar10 = (undefined *)(*pcVar1)();
            return puVar10;
          }
          if ((int)plVar8[3] == 0) {
            FUN_7fff5f47d650();
            pcVar1 = (code *)swi(3);
            puVar10 = (undefined *)(*pcVar1)();
            return puVar10;
          }
          plVar8[4] = lVar4;
          thunk_FUN_7fff5f491fd0();
          if ((plVar6 != (longlong *)0x0) &&
             (lVar4 = (**(code **)(*plVar6 + 0x1a8))(plVar6,plVar8,*(undefined8 *)(*plVar6 + 0x1b0))
             , lVar4 != 0)) {
            puVar10 = (undefined *)FUN_7fff60e78ac0(lVar4,_DAT_7fff6241a898,_DAT_7fff623f7f60,0);
            goto LAB_7fff5f9d3141;
          }
        }
        FUN_7fff5f47d660();
        pcVar1 = (code *)swi(3);
        puVar10 = (undefined *)(*pcVar1)();
        return puVar10;
      }
      plVar8 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
      uStack_64 = (uint)fVar12 ^ _DAT_7fff61b52c00;
      lVar4 = func_0x7fff5f47c7a0(_DAT_7fff62450b30,&uStack_64);
      if (plVar8 == (longlong *)0x0) {
        FUN_7fff5f47d660();
        pcVar1 = (code *)swi(3);
        puVar10 = (undefined *)(*pcVar1)();
        return puVar10;
      }
      if ((lVar4 != 0) &&
         (lVar9 = func_0x7fff5f47c7e0(lVar4,*(undefined8 *)(*plVar8 + 0x40)), lVar9 == 0)) {
        uVar5 = func_0x7fff5f47d0b0();
        FUN_7fff5f47d620(uVar5,0);
        pcVar1 = (code *)swi(3);
        puVar10 = (undefined *)(*pcVar1)();
        return puVar10;
      }
      if ((int)plVar8[3] == 0) {
        FUN_7fff5f47d650();
        pcVar1 = (code *)swi(3);
        puVar10 = (undefined *)(*pcVar1)();
        return puVar10;
      }
      plVar8[4] = lVar4;
      thunk_FUN_7fff5f491fd0();
      puVar10 = (undefined *)
                (**(code **)(*plVar6 + 0x1a8))(plVar6,plVar8,*(undefined8 *)(*plVar6 + 0x1b0));
      goto LAB_7fff5f9d3141;
    }
    if (id == 0xbd) {
      lVar4 = FUN_7fff60c4bc00(_DAT_7fff6245a460);
      if (lVar4 != 0) {
        plVar6 = (longlong *)FUN_7fff5f55ae30(lVar4,2);
        uVar3 = func_0x7fff60307220((int)val,0);
        if (plVar6 != (longlong *)0x0) {
          if ((*(byte *)(_DAT_7fff62453550 + 0x130) <= *(byte *)(*plVar6 + 0x130)) &&
             (*(longlong *)
               (*(longlong *)(*plVar6 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7fff62453550 + 0x130) * 8) == _DAT_7fff62453550)) {
            puVar10 = (undefined *)FUN_7fff5f5654f0(plVar6,uVar3,0);
            return puVar10;
          }
          FUN_7fff5f47c810(plVar6,_DAT_7fff62453550);
          pcVar1 = (code *)swi(3);
          puVar10 = (undefined *)(*pcVar1)();
          return puVar10;
        }
      }
LAB_7fff5f9d31f0:
      FUN_7fff5f47d660();
      pcVar1 = (code *)swi(3);
      puVar10 = (undefined *)(*pcVar1)();
      return puVar10;
    }
    if (itemPropertyTextManager == (undefined *)0x0) goto LAB_7fff5f9d31f0;
    plVar6 = (longlong *)FUN_7fff5f256fc0(_DAT_7fff62411770,itemPropertyTextManager,bonusType);
    if (plVar6 == (longlong *)0x0) {
      return _DAT_7fff623f7f60;
    }
    lVar4 = (**(code **)(*plVar6 + 0x178))(plVar6,*(undefined8 *)(*plVar6 + 0x180));
    uVar11 = _DAT_7fff62425428;
    if (fVar12 < 0.0) {
      if (lVar4 == 0) goto LAB_7fff5f9d31f0;
      lVar4 = FUN_7fff60e78ac0(lVar4,_DAT_7fff6241a898,_DAT_7fff623f7f60,0);
    }
    else {
      uVar11 = uVar5;
      if (fVar12 == 0.0) {
        uVar11 = _DAT_7fff6241c668;
      }
    }
    afStackX_10[0] = fVar12;
    uVar7 = func_0x7fff5f47c7a0(_DAT_7fff62450b30,afStackX_10);
    uVar5 = uVar11;
  }
  puVar10 = (undefined *)FUN_7fff60e74b00(lVar4,uVar7,0);
  uVar7 = uVar5;
LAB_7fff5f9d3141:
  if (isColor != 0) {
    puVar10 = (undefined *)FUN_7fff60e74db0(_DAT_7fff62401c80,uVar7,puVar10,0);
  }
  return puVar10;
}

