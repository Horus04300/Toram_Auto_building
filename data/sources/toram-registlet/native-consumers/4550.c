
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int WeaponTypeCalculatorBase_CalcAtk
              (undefined *thisObject,undefined *status,undefined *plusBaseValue,undefined *plusValue
              ,undefined *plusRateValue,undefined *minusBaseValue,undefined *minusValue,
              undefined *minusRateValue,undefined *methodInfo)

{
  code *pcVar1;
  undefined *puVar2;
  undefined *puVar3;
  char cVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  undefined8 uVar9;
  undefined *puVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float afStackX_10 [2];
  int aiStackX_18 [2];
  int aiStackX_20 [2];
  longlong *plStack_a8;
  float fStack_a0;
  int iStack_9c;
  float fStack_98;
  int iStack_94;
  int iStack_90;
  int iStack_8c;
  int iStack_88;
  int iStack_84;
  int aiStack_80 [16];
  
  if (DAT_7ffe9cada8bf == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    DAT_7ffe9cada8bf = '\x01';
  }
  puVar3 = minusRateValue;
  puVar2 = minusValue;
  puVar10 = minusBaseValue;
  afStackX_10[0] = _DAT_7ffe9c049b18;
  *(undefined4 *)plusBaseValue = 0;
  *(undefined4 *)plusValue = 0;
  *(undefined4 *)plusRateValue = 0;
  *(undefined4 *)minusBaseValue = 0;
  *(undefined4 *)minusValue = 0;
  *(undefined4 *)minusRateValue = 0;
  plStack_a8 = (longlong *)0x0;
  aiStackX_20[0] = 0;
  fStack_a0 = 0.0;
  iStack_9c = 0;
  fStack_98 = 0.0;
  iStack_94 = 0;
  iStack_90 = 0;
  aiStackX_18[0] = 0;
  if ((status != (undefined *)0x0) &&
     (lVar8 = (**(code **)(*(longlong *)status + 0x1d8))
                        (status,*(undefined8 *)(*(longlong *)status + 0x1e0)), lVar8 != 0)) {
    FUN_7ffe9a4ea6d0(lVar8,0x11,0xb4,0x12,aiStackX_18,afStackX_10,aiStackX_20,&fStack_a0,&iStack_9c,
                     &fStack_98,0);
    *(int *)plusValue = *(int *)plusValue + aiStackX_20[0];
    *(float *)plusRateValue = fStack_a0 + *(float *)plusRateValue;
    *(int *)puVar2 = *(int *)puVar2 + iStack_9c;
    pcVar1 = *(code **)(*(longlong *)status + 0x1d8);
    uVar9 = *(undefined8 *)(*(longlong *)status + 0x1e0);
    *(float *)puVar3 = fStack_98 + *(float *)puVar3;
    lVar8 = (*pcVar1)(status,uVar9);
    uVar9 = (**(code **)(*(longlong *)status + 0x188))
                      (status,*(undefined8 *)(*(longlong *)status + 400));
    if (lVar8 != 0) {
      uVar5 = FUN_7ffe9a4e9e90(lVar8,uVar9,&iStack_94,&iStack_90,0);
      iVar6 = aiStackX_18[0];
      *(int *)plusBaseValue = *(int *)plusBaseValue + iStack_94;
      *(int *)puVar10 = *(int *)puVar10 + iStack_90;
      iStack_8c = 0;
      iStack_88 = 0;
      lVar8 = (**(code **)(*(longlong *)status + 0x1c8))
                        (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
      if (lVar8 != 0) {
        aiStackX_18[0] = func_0x7ffe9a7c90a0(lVar8,0x36,&iStack_8c,&iStack_88,0);
        fVar13 = afStackX_10[0];
        aiStackX_18[0] = aiStackX_18[0] + iVar6;
        *(int *)plusValue = *(int *)plusValue + iStack_8c;
        *(int *)puVar2 = *(int *)puVar2 + iStack_88;
        iStack_84 = 0;
        aiStack_80[0] = 0;
        lVar8 = (**(code **)(*(longlong *)status + 0x1c8))
                          (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
        if (lVar8 != 0) {
          iVar6 = func_0x7ffe9a7c90a0(lVar8,0x1d,&iStack_84,aiStack_80,0);
          fVar11 = _DAT_7ffe9c049cfc;
          fVar12 = (float)aiStack_80[0] / _DAT_7ffe9c049cfc;
          afStackX_10[0] = (float)iVar6 / _DAT_7ffe9c049cfc + fVar13;
          pcVar1 = *(code **)(*(longlong *)status + 0x1f8);
          uVar9 = *(undefined8 *)(*(longlong *)status + 0x200);
          *(float *)plusRateValue = (float)iStack_84 / _DAT_7ffe9c049cfc + *(float *)plusRateValue;
          *(float *)puVar3 = fVar12 + *(float *)puVar3;
          lVar8 = (*pcVar1)(status,uVar9);
          if (lVar8 != 0) {
            if (DAT_7ffe9cada8b2 == '\0') {
              FUN_7ffe9996d590(&DAT_7ffe9c95a358);
              DAT_7ffe9cada8b2 = '\x01';
            }
            minusBaseValue = (undefined *)0x0;
            if (*(longlong *)(lVar8 + 0x10) == 0) {
              FUN_7ffe9996d7a0();
              pcVar1 = (code *)swi(3);
              iVar6 = (*pcVar1)();
              return iVar6;
            }
            cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x10),2,&minusBaseValue,_DAT_7ffe9c95a358
                                    );
            if (((cVar4 != '\0') && (minusBaseValue != (undefined *)0x0)) &&
               (*(int *)(minusBaseValue + 0x38) == 0xf)) {
              afStackX_10[0] = afStackX_10[0] + _DAT_7ffe9c04a168;
              pcVar1 = *(code **)(*(longlong *)status + 0x1b8);
              uVar9 = *(undefined8 *)(*(longlong *)status + 0x1c0);
              *(float *)puVar3 = *(float *)puVar3 - _DAT_7ffe9c049b48;
              lVar8 = (*pcVar1)(status,uVar9);
              if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x68) == 0)) goto LAB_7ffe99c1db18;
              cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0x361,&plStack_a8,
                                       _DAT_7ffe9c935bd0);
              if (cVar4 != '\0') {
                if (plStack_a8 == (longlong *)0x0) goto LAB_7ffe99c1db18;
                iVar6 = (**(code **)(*plStack_a8 + 0x178))
                                  (plStack_a8,3,*(undefined8 *)(*plStack_a8 + 0x180));
                if ((*(longlong *)(thisObject + 0x10) != 0) &&
                   (*(int *)(*(longlong *)(thisObject + 0x10) + 0x38) == 10)) {
                  iVar6 = iVar6 + 5;
                }
                fVar13 = (float)iVar6 / fVar11;
                afStackX_10[0] = afStackX_10[0] + fVar13;
                *(float *)puVar3 = fVar13 + *(float *)puVar3;
              }
            }
            lVar8 = (**(code **)(*(longlong *)status + 0x1b8))
                              (status,*(undefined8 *)(*(longlong *)status + 0x1c0));
            if ((lVar8 != 0) && (*(longlong *)(lVar8 + 0x68) != 0)) {
              cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0x1e1,&plStack_a8,
                                       _DAT_7ffe9c935bd0);
              if (cVar4 != '\0') {
                lVar8 = (**(code **)(*(longlong *)status + 0x198))
                                  (status,*(undefined8 *)(*(longlong *)status + 0x1a0));
                if ((lVar8 == 0) ||
                   (iVar6 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar8),
                   plStack_a8 == (longlong *)0x0)) goto LAB_7ffe99c1db18;
                iVar7 = (**(code **)(*plStack_a8 + 0x178))
                                  (plStack_a8,3,*(undefined8 *)(*plStack_a8 + 0x180));
                iVar6 = (iVar7 * iVar6) / 100;
                aiStackX_18[0] = aiStackX_18[0] + iVar6;
                *(int *)plusValue = *(int *)plusValue + iVar6;
              }
              lVar8 = (**(code **)(*(longlong *)status + 0x1b8))
                                (status,*(undefined8 *)(*(longlong *)status + 0x1c0));
              if ((lVar8 != 0) && (*(longlong *)(lVar8 + 0x68) != 0)) {
                cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0x1ea,&plStack_a8,
                                         _DAT_7ffe9c935bd0);
                if (cVar4 != '\0') {
                  lVar8 = (**(code **)(*(longlong *)status + 0x198))
                                    (status,*(undefined8 *)(*(longlong *)status + 0x1a0));
                  if ((lVar8 == 0) ||
                     (iVar6 = FUN_7ffe99742ec0(0,_DAT_7ffe9c940d40,lVar8),
                     plStack_a8 == (longlong *)0x0)) goto LAB_7ffe99c1db18;
                  iVar7 = (**(code **)(*plStack_a8 + 0x178))(plStack_a8,3);
                  iVar6 = (iVar7 * iVar6) / 100;
                  aiStackX_18[0] = aiStackX_18[0] + iVar6;
                  *(int *)plusValue = *(int *)plusValue + iVar6;
                }
                puVar10 = (undefined *)
                          (**(code **)(*(longlong *)status + 0x218))
                                    (status,*(undefined8 *)(*(longlong *)status + 0x220));
                if (puVar10 != (undefined *)0x0) {
                  puVar10 = GemCartBufferManager_GetGemCartBuffer(puVar10,0x25,(undefined *)0x0);
                  if (puVar10 != (undefined *)0x0) {
                    iVar6 = GemCartBufferBase_GetValue(puVar10,(undefined *)0x2,(undefined *)0x0);
                    fVar11 = (float)iVar6 / fVar11;
                    afStackX_10[0] = afStackX_10[0] + fVar11;
                    if (0.0 < fVar11) {
                      *(float *)plusRateValue = fVar11 + *(float *)plusRateValue;
                    }
                    else if (fVar11 < 0.0) {
                      *(float *)puVar3 = fVar11 + *(float *)puVar3;
                    }
                  }
                  iVar6 = (**(code **)(*(longlong *)thisObject + 0x198))
                                    (thisObject,status,uVar5,afStackX_10[0],aiStackX_18[0],
                                     *(undefined8 *)(*(longlong *)thisObject + 0x1a0));
                  return iVar6;
                }
              }
            }
          }
        }
      }
    }
  }
LAB_7ffe99c1db18:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  iVar6 = (*pcVar1)();
  return iVar6;
}

