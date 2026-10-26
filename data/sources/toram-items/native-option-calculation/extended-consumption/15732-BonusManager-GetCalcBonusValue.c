
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BonusManager_GetCalcBonusValue
              (undefined *self,int baseVal,int rateType,int constType,undefined *methodInfo)

{
  code *pcVar1;
  undefined *self_00;
  char cVar2;
  int iVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  undefined8 uStack_c0;
  undefined8 *puStack_b8;
  undefined *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  longlong lStack_98;
  undefined8 uStack_90;
  undefined8 *puStack_88;
  undefined *puStack_80;
  undefined8 uStack_68;
  undefined8 uStack_60;
  longlong lStack_58;
  
  if (DAT_7ffe9cade121 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c902308);
    FUN_7ffe9996d590(&DAT_7ffe9c973348);
    FUN_7ffe9996d590(&DAT_7ffe9c973418);
    FUN_7ffe9996d590(&DAT_7ffe9c9023d8);
    FUN_7ffe9996d590(0x7ffe9c9024a8);
    FUN_7ffe9996d590(0x7ffe9c9734e8);
    FUN_7ffe9996d590(&DAT_7ffe9c909030);
    FUN_7ffe9996d590(&DAT_7ffe9c94b470);
    FUN_7ffe9996d590(&DAT_7ffe9c907ff0);
    DAT_7ffe9cade121 = '\x01';
  }
  fVar5 = _DAT_7ffe9c049cfc;
  uStack_a8 = 0;
  uStack_a0 = 0;
  lStack_98 = 0;
  fVar6 = 0.0;
  if (*(longlong *)(self + 0x78) == 0) {
    FUN_7ffe9996d7a0();
LAB_7ffe9a4eb79d:
    FUN_7ffe9996d7a0();
LAB_7ffe9a4eb7a3:
    FUN_7ffe9996d7a0();
LAB_7ffe9a4eb7a9:
    FUN_7ffe9996d7a0();
    FUN_7ffe998fa550();
LAB_7ffe9a4eb7b4:
    FUN_7ffe9996d7a0();
LAB_7ffe9a4eb7b9:
    FUN_7ffe9996d7a0();
LAB_7ffe9a4eb7be:
    FUN_7ffe9996d7a0();
    FUN_7ffe998fa550();
    pcVar1 = (code *)swi(3);
    iVar3 = (*pcVar1)();
    return iVar3;
  }
  FUN_7ffe9af836a0(&uStack_c0,*(longlong *)(self + 0x78),_DAT_7ffe9c907ff0);
  uStack_90 = uStack_c0;
  puStack_88 = puStack_b8;
  puStack_80 = puStack_b0;
LAB_7ffe9a4eb580:
  cVar2 = FUN_7ffe9ae28ed0(&uStack_90,_DAT_7ffe9c973418);
  self_00 = puStack_80;
  if (cVar2 == '\0') {
    _GetDurationBonusTime_d__7_System_IDisposable_Dispose((undefined *)&uStack_90,_DAT_7ffe9c973348)
    ;
    return (int)((fVar5 / _DAT_7ffe9c049cfc) * (float)baseVal + fVar6);
  }
  if (puStack_80 != (undefined *)0x0) {
    if (*(longlong *)(puStack_80 + 0x18) != 0) {
      cVar2 = FUN_7ffe9afc8940(*(longlong *)(puStack_80 + 0x18),rateType);
      if (cVar2 != '\0') goto LAB_7ffe9a4eb5e6;
      if (*(longlong *)(self_00 + 0x18) != 0) goto code_r0x7ffe9a4eb5d4;
      goto LAB_7ffe9a4eb79d;
    }
    goto LAB_7ffe9a4eb7b9;
  }
  goto LAB_7ffe9a4eb7be;
code_r0x7ffe9a4eb5d4:
  cVar2 = FUN_7ffe9afc8940(*(longlong *)(self_00 + 0x18),constType);
  if (cVar2 != '\0') {
LAB_7ffe9a4eb5e6:
    if (self_00[0x40] != '\0') {
      if (*(undefined **)(self + 0x18) == (undefined *)0x0) goto LAB_7ffe9a4eb7a3;
      BonusScriptManager_Run
                (*(undefined **)(self + 0x18),*(undefined **)(self_00 + 0x10),0,(undefined *)0x0);
      BonusData_UpdateBonusList(self_00,(undefined *)0x0);
    }
    if (*(longlong *)(self_00 + 0x20) == 0) goto LAB_7ffe9a4eb7b4;
    FUN_7ffe9af836a0(&uStack_68,*(longlong *)(self_00 + 0x20),_DAT_7ffe9c94b470);
    uStack_a8 = uStack_68;
    uStack_a0 = uStack_60;
    lStack_98 = lStack_58;
    uStack_c0 = 0;
    puStack_b8 = &uStack_a8;
    while (cVar2 = FUN_7ffe9ae28ed0(&uStack_a8,_DAT_7ffe9c9023d8), cVar2 != '\0') {
      if (lStack_98 == 0) goto LAB_7ffe9a4eb7a9;
      iVar3 = 0;
      iVar4 = iVar3;
      if (*(int *)(lStack_98 + 0x10) == constType) {
        iVar4 = *(int *)(lStack_98 + 0x14);
      }
      fVar6 = fVar6 + (float)iVar4;
      if (*(int *)(lStack_98 + 0x10) == rateType) {
        iVar3 = *(int *)(lStack_98 + 0x14);
      }
      fVar5 = fVar5 + (float)iVar3;
    }
    _GetDurationBonusTime_d__7_System_IDisposable_Dispose((undefined *)&uStack_a8,_DAT_7ffe9c902308)
    ;
  }
  goto LAB_7ffe9a4eb580;
}

