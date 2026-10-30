
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int WeaponTypeCalculatorBase_CalcMatk
              (undefined *thisObject,undefined *status,undefined *plusBaseValue,undefined *plusValue
              ,undefined *plusRateValue,undefined *minusBaseValue,undefined *minusValue,
              undefined *minusRateValue,undefined *methodInfo)

{
  code *pcVar1;
  float fVar2;
  undefined *puVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  longlong lVar9;
  longlong lVar10;
  undefined8 uVar11;
  undefined *puVar12;
  float fVar13;
  int aiStackX_10 [2];
  float afStackX_18 [2];
  int aiStackX_20 [2];
  undefined4 uVar14;
  longlong *plStack_b8;
  float fStack_b0;
  int iStack_ac;
  float fStack_a8;
  int iStack_a4;
  int iStack_a0;
  int iStack_9c;
  int iStack_98;
  int iStack_94;
  int aiStack_90 [2];
  longlong alStack_88 [9];
  
  if (DAT_7ffe9cada8c0 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    DAT_7ffe9cada8c0 = '\x01';
  }
  puVar3 = minusRateValue;
  *(undefined4 *)plusBaseValue = 0;
  *(undefined4 *)plusValue = 0;
  *(undefined4 *)plusRateValue = 0;
  *(undefined4 *)minusBaseValue = 0;
  *(undefined4 *)minusValue = 0;
  *(undefined4 *)minusRateValue = 0;
  aiStackX_20[0] = 0;
  fStack_b0 = 0.0;
  iStack_ac = 0;
  fStack_a8 = 0.0;
  iStack_a4 = 0;
  iStack_a0 = 0;
  plStack_b8 = (longlong *)0x0;
  iStack_9c = 0;
  iStack_98 = 0;
  iStack_94 = 0;
  aiStack_90[0] = 0;
  if ((status != (undefined *)0x0) &&
     (lVar9 = (**(code **)(*(longlong *)status + 0x1f8))
                        (status,*(undefined8 *)(*(longlong *)status + 0x200)), lVar9 != 0)) {
    if (DAT_7ffe9cada8b1 == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c95a358);
      DAT_7ffe9cada8b1 = '\x01';
    }
    minusRateValue = (undefined *)0x0;
    if (*(longlong *)(lVar9 + 0x10) == 0) {
      FUN_7ffe9996d7a0();
      pcVar1 = (code *)swi(3);
      iVar5 = (*pcVar1)();
      return iVar5;
    }
    cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x10),1,&minusRateValue,_DAT_7ffe9c95a358);
    puVar12 = minusRateValue;
    if (cVar4 == '\0') {
      puVar12 = (undefined *)0x0;
    }
    lVar9 = (**(code **)(*(longlong *)status + 0x1f8))
                      (status,*(undefined8 *)(*(longlong *)status + 0x200));
    if (lVar9 != 0) {
      if (DAT_7ffe9cada8b2 == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c95a358);
        DAT_7ffe9cada8b2 = '\x01';
      }
      alStack_88[0] = 0;
      if (*(longlong *)(lVar9 + 0x10) == 0) {
        FUN_7ffe9996d7a0();
        pcVar1 = (code *)swi(3);
        iVar5 = (*pcVar1)();
        return iVar5;
      }
      cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x10),2,alStack_88,_DAT_7ffe9c95a358);
      afStackX_18[0] = _DAT_7ffe9c049b18;
      lVar9 = alStack_88[0];
      if (cVar4 == '\0') {
        lVar9 = 0;
      }
      aiStackX_10[0] = 0;
      lVar10 = (**(code **)(*(longlong *)status + 0x1d8))
                         (status,*(undefined8 *)(*(longlong *)status + 0x1e0));
      if (lVar10 != 0) {
        FUN_7ffe9a4ea6d0(lVar10,0x13,0xb5,0x14,aiStackX_10,afStackX_18,aiStackX_20,&fStack_b0,
                         &iStack_ac,&fStack_a8,0);
        *(int *)plusValue = *(int *)plusValue + aiStackX_20[0];
        *(float *)plusRateValue = fStack_b0 + *(float *)plusRateValue;
        *(int *)minusValue = *(int *)minusValue + iStack_ac;
        pcVar1 = *(code **)(*(longlong *)status + 0x1d8);
        uVar11 = *(undefined8 *)(*(longlong *)status + 0x1e0);
        *(float *)puVar3 = fStack_a8 + *(float *)puVar3;
        lVar10 = (*pcVar1)(status,uVar11);
        uVar11 = (**(code **)(*(longlong *)status + 0x188))
                           (status,*(undefined8 *)(*(longlong *)status + 400));
        if (lVar10 != 0) {
          iVar5 = FUN_7ffe9a4ea180(lVar10,uVar11,&iStack_a4,&iStack_a0,0);
          *(int *)plusBaseValue = *(int *)plusBaseValue + iStack_a4;
          *(int *)minusBaseValue = *(int *)minusBaseValue + iStack_a0;
          if ((lVar9 != 0) && (*(int *)(lVar9 + 0x38) == 0x10)) {
            afStackX_18[0] = afStackX_18[0] + _DAT_7ffe9c04a168;
            *(float *)puVar3 = *(float *)puVar3 - _DAT_7ffe9c049b48;
          }
          lVar10 = (**(code **)(*(longlong *)status + 0x1b8))
                             (status,*(undefined8 *)(*(longlong *)status + 0x1c0));
          if ((lVar10 != 0) && (*(longlong *)(lVar10 + 0x68) != 0)) {
            cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar10 + 0x68),0x1e2,&plStack_b8,
                                     _DAT_7ffe9c935bd0);
            if (cVar4 != '\0') {
              lVar10 = (**(code **)(*(longlong *)status + 0x198))
                                 (status,*(undefined8 *)(*(longlong *)status + 0x1a0));
              if ((lVar10 == 0) ||
                 (iVar6 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar10),
                 plStack_b8 == (longlong *)0x0)) goto LAB_7ffe99c1ecae;
              iVar7 = (**(code **)(*plStack_b8 + 0x178))
                                (plStack_b8,5,*(undefined8 *)(*plStack_b8 + 0x180));
              iVar6 = (iVar7 * iVar6) / 100;
              aiStackX_10[0] = aiStackX_10[0] + iVar6;
              *(int *)plusValue = *(int *)plusValue + iVar6;
            }
            lVar10 = (**(code **)(*(longlong *)status + 0x1b8))
                               (status,*(undefined8 *)(*(longlong *)status + 0x1c0));
            if (lVar10 != 0) {
              iVar6 = FUN_7ffe9a7fd580(lVar10,0x363,1,0);
              fVar13 = _DAT_7ffe9c049cfc;
              if (((0 < iVar6) && (puVar12 != (undefined *)0x0)) &&
                 (cVar4 = func_0x7ffe9a80ac00(*(undefined4 *)(puVar12 + 0x38),0), cVar4 != '\0')) {
                iVar7 = func_0x7ffe9a80ac40(iVar6,0x1c);
                if (*(int *)(puVar12 + 0x38) == 0x10) {
                  iVar7 = iVar7 / 2;
                }
                lVar10 = (**(code **)(*(longlong *)status + 0x198))
                                   (status,*(undefined8 *)(*(longlong *)status + 0x1a0));
                if (lVar10 == 0) goto LAB_7ffe99c1ecae;
                iVar8 = FUN_7ffe99742ec0(0xc,_DAT_7ffe9c940d40,lVar10);
                iVar7 = (int)((float)(iVar8 * iVar7) / fVar13);
                aiStackX_10[0] = aiStackX_10[0] + iVar7;
                *(int *)plusValue = *(int *)plusValue + iVar7;
                if (*(int *)(puVar12 + 0x38) != 0x10) {
                  lVar10 = (**(code **)(*(longlong *)status + 0x198))
                                     (status,*(undefined8 *)(*(longlong *)status + 0x1a0));
                  if (lVar10 == 0) goto LAB_7ffe99c1ecae;
                  iVar7 = FUN_7ffe99742ec0(2,_DAT_7ffe9c940d40,lVar10);
                  iVar5 = iVar5 + (int)((float)(iVar7 * iVar6 * 10) / fVar13);
                }
              }
              if ((lVar9 != 0) && (*(int *)(lVar9 + 0x38) == 0xf)) {
                lVar9 = (**(code **)(*(longlong *)status + 0x1b8))
                                  (status,*(undefined8 *)(*(longlong *)status + 0x1c0));
                if ((lVar9 == 0) || (*(longlong *)(lVar9 + 0x68) == 0)) goto LAB_7ffe99c1ecae;
                cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x68),0x361,&plStack_b8,
                                         _DAT_7ffe9c935bd0);
                if (cVar4 != '\0') {
                  if (plStack_b8 == (longlong *)0x0) goto LAB_7ffe99c1ecae;
                  iVar6 = (**(code **)(*plStack_b8 + 0x178))
                                    (plStack_b8,4,*(undefined8 *)(*plStack_b8 + 0x180));
                  aiStackX_10[0] = aiStackX_10[0] + iVar6;
                  *(int *)plusValue = *(int *)plusValue + iVar6;
                }
              }
              fVar2 = afStackX_18[0];
              lVar9 = (**(code **)(*(longlong *)status + 0x1c8))
                                (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
              if (lVar9 != 0) {
                iVar7 = FUN_7ffe9a7c8f10(lVar9,0x1e,&iStack_9c,&iStack_98,0);
                iVar6 = aiStackX_10[0];
                afStackX_18[0] = (float)iVar7 / fVar13 + fVar2;
                pcVar1 = *(code **)(*(longlong *)status + 0x1c8);
                uVar11 = *(undefined8 *)(*(longlong *)status + 0x1d0);
                *(float *)plusRateValue = (float)iStack_9c / fVar13 + *(float *)plusRateValue;
                *(float *)puVar3 = (float)iStack_98 / fVar13 + *(float *)puVar3;
                lVar9 = (*pcVar1)(status,uVar11);
                if (lVar9 != 0) {
                  uVar14 = 0;
                  aiStackX_10[0] = FUN_7ffe9a7c8f10(lVar9,0x37,&iStack_94,aiStack_90,0);
                  aiStackX_10[0] = aiStackX_10[0] + iVar6;
                  *(int *)plusValue = *(int *)plusValue + iStack_94;
                  *(int *)minusValue = *(int *)minusValue + aiStack_90[0];
                  lVar9 = (**(code **)(*(longlong *)status + 0x1b8))
                                    (status,*(undefined8 *)(*(longlong *)status + 0x1c0));
                  if ((lVar9 != 0) && (*(longlong *)(lVar9 + 0x68) != 0)) {
                    cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x68),0x1eb,&plStack_b8,
                                             _DAT_7ffe9c935bd0);
                    if (cVar4 != '\0') {
                      lVar9 = (**(code **)(*(longlong *)status + 0x198))
                                        (status,*(undefined8 *)(*(longlong *)status + 0x1a0));
                      if ((lVar9 == 0) ||
                         (iVar6 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar9),
                         plStack_b8 == (longlong *)0x0)) goto LAB_7ffe99c1ecae;
                      iVar7 = (**(code **)(*plStack_b8 + 0x178))(plStack_b8,5);
                      iVar6 = (iVar7 * iVar6) / 100;
                      aiStackX_10[0] = aiStackX_10[0] + iVar6;
                      *(int *)plusValue = *(int *)plusValue + iVar6;
                    }
                    puVar12 = (undefined *)
                              (**(code **)(*(longlong *)status + 0x218))
                                        (status,*(undefined8 *)(*(longlong *)status + 0x220));
                    if (puVar12 != (undefined *)0x0) {
                      puVar12 = GemCartBufferManager_GetGemCartBuffer(puVar12,0x25,(undefined *)0x0)
                      ;
                      if (puVar12 != (undefined *)0x0) {
                        iVar6 = GemCartBufferBase_GetValue
                                          (puVar12,(undefined *)0x2,(undefined *)0x0);
                        fVar13 = (float)iVar6 / fVar13;
                        afStackX_18[0] = afStackX_18[0] + fVar13;
                        if (0.0 < fVar13) {
                          *(float *)plusRateValue = fVar13 + *(float *)plusRateValue;
                        }
                        else if (fVar13 < 0.0) {
                          *(float *)puVar3 = fVar13 + *(float *)puVar3;
                        }
                      }
                      lVar9 = (**(code **)(*(longlong *)status + 0x1c8))
                                        (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
                      if (lVar9 != 0) {
                        cVar4 = FUN_7ffe9a7c6d00(lVar9,0x3db,0);
                        if (cVar4 == '\0') {
LAB_7ffe99c1ec4b:
                          pcVar1 = *(code **)(*(longlong *)thisObject + 0x1a8);
                          iVar5 = (*pcVar1)(thisObject,status,iVar5,pcVar1,
                                            CONCAT44(uVar14,aiStackX_10[0]),
                                            *(undefined8 *)(*(longlong *)thisObject + 0x1b0));
                          return iVar5;
                        }
                        lVar9 = (**(code **)(*(longlong *)status + 0x198))
                                          (status,*(undefined8 *)(*(longlong *)status + 0x1a0));
                        if (lVar9 != 0) {
                          iVar6 = FUN_7ffe99742ec0(2,_DAT_7ffe9c940d40,lVar9);
                          lVar9 = (**(code **)(*(longlong *)status + 0x198))
                                            (status,*(undefined8 *)(*(longlong *)status + 0x1a0));
                          if (lVar9 != 0) {
                            iVar7 = FUN_7ffe99742ec0(0xc,_DAT_7ffe9c940d40,lVar9);
                            lVar9 = (**(code **)(*(longlong *)status + 0x198))
                                              (status,*(undefined8 *)(*(longlong *)status + 0x1a0));
                            if (lVar9 != 0) {
                              iVar8 = FUN_7ffe99742ec0(5,_DAT_7ffe9c940d40,lVar9);
                              if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
                                func_0x7ffe9996d830();
                              }
                              fVar13 = (float)func_0x7ffe9b506c10(((float)iVar7 / _DAT_7ffe9c049e58
                                                                  + (float)(iVar6 * 2)) -
                                                                  (float)iVar8);
                              iVar5 = iVar5 + (int)fVar13;
                              goto LAB_7ffe99c1ec4b;
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
    }
  }
LAB_7ffe99c1ecae:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  iVar5 = (*pcVar1)();
  return iVar5;
}

