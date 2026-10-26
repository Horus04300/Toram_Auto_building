
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BonusManager_GetBonusConstant_AvatarConstan_Rate
               (undefined *self,int constantType,int constantToAvatarType,int rateType,
               undefined *constant,undefined *rate,undefined *plusValue,undefined *plusRateValue,
               undefined *minusValue,undefined *minusRateValue,undefined *methodInfo)

{
  int iVar1;
  int iVar2;
  code *pcVar3;
  float fVar4;
  undefined *puVar5;
  int iVar6;
  int iVar7;
  undefined *self_00;
  longlong lVar8;
  int iVar9;
  float fVar10;
  
  puVar5 = constant;
  if (DAT_7ffe9cade125 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c948908);
    FUN_7ffe9996d590(&DAT_7ffe9c946bb8);
    FUN_7ffe9996d590(0x7ffe9c908190);
    FUN_7ffe9996d590(0x7ffe9c94b780);
    FUN_7ffe9996d590(&DAT_7ffe9c94b840);
    FUN_7ffe9996d590();
    DAT_7ffe9cade125 = '\x01';
  }
  *(undefined4 *)constant = 0;
  *(undefined4 *)rate = 0x3f800000;
  *(undefined4 *)plusValue = 0;
  *(undefined4 *)plusRateValue = 0;
  *(undefined4 *)minusValue = 0;
  *(undefined4 *)minusRateValue = 0;
  fVar4 = _DAT_7ffe9c049b34;
  lVar8 = *(longlong *)(self + 0x78);
  constant._0_4_ = 0;
  while (lVar8 != 0) {
    if (*(int *)(lVar8 + 0x18) <= (int)constant) {
      return;
    }
    if ((lVar8 == 0) ||
       (self_00 = (undefined *)FUN_7ffe9af8ab90(lVar8,(int)constant), self_00 == (undefined *)0x0))
    break;
    if (self_00[0x40] != '\0') {
      if (*(undefined **)(self + 0x18) == (undefined *)0x0) break;
      BonusScriptManager_Run
                (*(undefined **)(self + 0x18),*(undefined **)(self_00 + 0x10),0,(undefined *)0x0);
      BonusData_UpdateBonusList(self_00,(undefined *)0x0);
    }
    iVar9 = 0;
LAB_7ffe9a4ea830:
    lVar8 = *(longlong *)(self_00 + 0x20);
    if (lVar8 == 0) break;
    if (iVar9 < *(int *)(lVar8 + 0x18)) {
      lVar8 = FUN_7ffe9af8ab90(lVar8,iVar9,_DAT_7ffe9c94b840);
      if (lVar8 == 0) break;
      iVar1 = *(int *)(lVar8 + 0x10);
      if (iVar1 == constantType) {
        iVar1 = *(int *)(lVar8 + 0x14);
        *(int *)puVar5 = *(int *)puVar5 + iVar1;
        if (0 < iVar1) {
          *(int *)plusValue = *(int *)plusValue + iVar1;
          iVar9 = iVar9 + 1;
          goto LAB_7ffe9a4ea830;
        }
        if (iVar1 < 0) {
          *(int *)minusValue = *(int *)minusValue + iVar1;
          iVar9 = iVar9 + 1;
          goto LAB_7ffe9a4ea830;
        }
      }
      else {
        if (iVar1 == rateType) {
          fVar10 = (float)*(int *)(lVar8 + 0x14) * fVar4;
          *(float *)rate = fVar10 + *(float *)rate;
          if (0.0 < fVar10) {
            iVar9 = iVar9 + 1;
            *(float *)plusRateValue = fVar10 + *(float *)plusRateValue;
          }
          else {
            if (0.0 <= fVar10) goto LAB_7ffe9a4ea922;
            iVar9 = iVar9 + 1;
            *(float *)minusRateValue = fVar10 + *(float *)minusRateValue;
          }
          goto LAB_7ffe9a4ea830;
        }
        if (iVar1 == constantToAvatarType) {
          iVar1 = *(int *)(lVar8 + 0x14);
          if (*(int *)(_DAT_7ffe9c948908 + 0xe0) == 0) {
            func_0x7ffe9996d830(_DAT_7ffe9c948908);
          }
          if (**(longlong **)(_DAT_7ffe9c948908 + 0xb8) == 0) break;
          iVar6 = FUN_7ffe9ad82430(**(longlong **)(_DAT_7ffe9c948908 + 0xb8),constantToAvatarType,
                                   _DAT_7ffe9c946bb8);
          iVar2 = *(int *)(lVar8 + 0x14);
          iVar6 = iVar6 * iVar1;
          iVar1 = *(int *)puVar5;
          if (**(longlong **)(_DAT_7ffe9c948908 + 0xb8) == 0) break;
          iVar7 = FUN_7ffe9ad82430(**(longlong **)(_DAT_7ffe9c948908 + 0xb8),constantToAvatarType,
                                   _DAT_7ffe9c946bb8);
          *(int *)puVar5 = iVar7 * iVar2 + iVar1;
          if (iVar6 < 1) {
            if (iVar6 < 0) {
              *(int *)minusValue = *(int *)minusValue + iVar6;
            }
            goto LAB_7ffe9a4ea922;
          }
          *(int *)plusValue = *(int *)plusValue + iVar6;
          iVar9 = iVar9 + 1;
          goto LAB_7ffe9a4ea830;
        }
      }
LAB_7ffe9a4ea922:
      iVar9 = iVar9 + 1;
      goto LAB_7ffe9a4ea830;
    }
    constant._0_4_ = (int)constant + 1;
    lVar8 = *(longlong *)(self + 0x78);
  }
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

