
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte EquipBuffManager_IsGrantStopAbnormal(undefined *self,undefined *type,undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;
  undefined *self_00;
  undefined *self_01;
  undefined8 uVar5;
  longlong lVar6;
  int iVar7;
  undefined4 uVar8;
  bool bVar9;
  
  iVar7 = (int)type;
  if (iVar7 == 1) {
    uVar8 = 0xa3;
  }
  else if (iVar7 == 2) {
    uVar8 = 0xa4;
  }
  else {
    if (iVar7 != 3) {
      return 0;
    }
    uVar8 = 0xa5;
  }
  if (DAT_7ffe9cade252 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c908cf8,uVar8,0);
    FUN_7ffe9996d590(&DAT_7ffe9c939d00);
    FUN_7ffe9996d590(&DAT_7ffe9c92e208);
    FUN_7ffe9996d590(&DAT_7ffe9c93a5c0);
    DAT_7ffe9cade252 = '\x01';
  }
  self_00 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c93a5c0);
  _GetDurationBonusTime_d__7_System_IDisposable_Dispose(self_00,(undefined *)0x0);
  if (self_00 != (undefined *)0x0) {
    bVar9 = DAT_7ffe9cade251 == '\0';
    *(undefined4 *)(self_00 + 0x10) = uVar8;
    if (bVar9) {
      FUN_7ffe9996d590(&DAT_7ffe9c8f8688);
      FUN_7ffe9996d590(&DAT_7ffe9c939d00);
      FUN_7ffe9996d590(&DAT_7ffe9c92e148);
      FUN_7ffe9996d590(&DAT_7ffe9c93a4f8);
      DAT_7ffe9cade251 = '\x01';
    }
    self_01 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c93a4f8);
    _GetDurationBonusTime_d__7_System_IDisposable_Dispose(self_01,(undefined *)0x0);
    if (self_01 != (undefined *)0x0) {
      *(undefined4 *)(self_01 + 0x10) = uVar8;
      uVar1 = *(undefined8 *)(self + 0x20);
      uVar5 = func_0x7ffe99940040(_DAT_7ffe9c939d00);
      FUN_7ffe9af13420(uVar5,self_01,_DAT_7ffe9c92e148,0);
      cVar3 = FUN_7ffe9ab7ad20(uVar1,uVar5,_DAT_7ffe9c8f8688);
      if (cVar3 == '\0') {
        bVar4 = 0;
      }
      else {
        uVar1 = *(undefined8 *)(self + 0x20);
        uVar5 = func_0x7ffe99940040(_DAT_7ffe9c939d00);
        FUN_7ffe9af13420(uVar5,self_00,_DAT_7ffe9c92e208,0);
        lVar6 = FUN_7ffe9ab854c0(uVar1,uVar5,_DAT_7ffe9c908cf8);
        if (lVar6 == 0) goto LAB_7ffe9a51e4a9;
        bVar4 = *(byte *)(lVar6 + 0x12);
      }
      return bVar4;
    }
  }
LAB_7ffe9a51e4a9:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  bVar4 = (*pcVar2)();
  return bVar4;
}

