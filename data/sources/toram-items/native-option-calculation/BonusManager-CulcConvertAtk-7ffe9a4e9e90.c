
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BonusManager_CulcConvertAtk
              (undefined *self,undefined *status,undefined *plusValue,undefined *minusValue,
              undefined *methodInfo)

{
  code *pcVar1;
  float fVar2;
  undefined8 uVar3;
  char cVar4;
  int iVar5;
  longlong lVar6;
  undefined8 uVar7;
  undefined *methodInfo_00;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  undefined8 uStack_b8;
  undefined8 *puStack_b0;
  undefined8 uStack_a8;
  undefined8 uStack_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  
  if (DAT_7ffe9cade129 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9468a8);
    FUN_7ffe9996d590(&DAT_7ffe9c946a30);
    FUN_7ffe9996d590(&DAT_7ffe9c9467e8);
    FUN_7ffe9996d590(&DAT_7ffe9c906df8);
    FUN_7ffe9996d590(&DAT_7ffe9c925118);
    FUN_7ffe9996d590(&DAT_7ffe9c9251e0);
    FUN_7ffe9996d590(0x7ffe9c9252a8);
    FUN_7ffe9996d590(0x7ffe9c963960);
    FUN_7ffe9996d590(0x7ffe9c963a30);
    DAT_7ffe9cade129 = '\x01';
  }
  lVar6 = func_0x7ffe99940040(_DAT_7ffe9c906df8);
  FUN_7ffe9ad6e630(lVar6,_DAT_7ffe9c9467e8);
  if ((status != (undefined *)0x0) && (lVar6 != 0)) {
    FUN_7ffe9ad726f0(lVar6,0xa6,*(undefined4 *)(status + 0x14),_DAT_7ffe9c9468a8);
    FUN_7ffe9ad726f0(lVar6,0xa7,*(undefined4 *)(status + 0x18),_DAT_7ffe9c9468a8);
    FUN_7ffe9ad726f0(lVar6,0xa8,*(undefined4 *)(status + 0x1c),_DAT_7ffe9c9468a8);
    FUN_7ffe9ad726f0(lVar6,0xa9,*(undefined4 *)(status + 0x20),_DAT_7ffe9c9468a8);
    methodInfo_00 = _DAT_7ffe9c9468a8;
    FUN_7ffe9ad726f0(lVar6,0xaa,*(undefined4 *)(status + 0x24));
    fVar9 = 0.0;
    fVar10 = 0.0;
    fVar11 = 0.0;
    uVar7 = _DAT_7ffe9c946a30;
    FUN_7ffe9acecdb0(&uStack_b8,lVar6);
    fVar2 = _DAT_7ffe9c049c90;
    uStack_98 = uStack_b8;
    uStack_90 = puStack_b0;
    uStack_88 = uStack_a8;
    uStack_80 = uStack_a0;
    uStack_b8 = 0;
    puStack_b0 = &uStack_98;
    while( true ) {
      iVar5 = (int)uVar7;
      cVar4 = FUN_7ffe9ae3fbf0(&uStack_98,_DAT_7ffe9c9251e0);
      uVar3 = uStack_88;
      if (cVar4 == '\0') break;
      uVar7 = 0;
      iVar5 = BonusManager_getDataBonusValue(self,(int)uStack_88,(undefined *)0x0);
      fVar8 = ((float)iVar5 / fVar2) * (float)(int)((ulonglong)uVar3 >> 0x20);
      fVar11 = fVar11 + fVar8;
      if (0.0 < fVar8) {
        fVar9 = fVar9 + fVar8;
      }
      else if (fVar8 < 0.0) {
        fVar10 = fVar10 + fVar8;
      }
    }
    _GetDurationBonusTime_d__7_System_IDisposable_Dispose
              ((undefined *)&uStack_98,(int)_DAT_7ffe9c925118,iVar5,methodInfo_00);
    *(int *)plusValue = (int)fVar9;
    *(int *)minusValue = (int)fVar10;
    return (int)fVar11;
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  iVar5 = (*pcVar1)();
  return iVar5;
}

