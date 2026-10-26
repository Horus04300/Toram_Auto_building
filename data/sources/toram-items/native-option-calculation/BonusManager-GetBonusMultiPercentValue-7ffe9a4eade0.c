
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float BonusManager_GetBonusMultiPercentValue(undefined *self,int type,undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  float fVar3;
  undefined *self_00;
  char cVar4;
  undefined *self_01;
  longlong lVar5;
  int skillIndividualFlag;
  undefined *in_R9;
  float fVar6;
  float fVar7;
  longlong lStackX_20;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined *puStack_80;
  undefined4 uStack_78;
  undefined4 uStack_74;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined *puStack_68;
  
  if (DAT_7ffe9cade128 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c948908);
    FUN_7ffe9996d590(&DAT_7ffe9c946970);
    FUN_7ffe9996d590(&DAT_7ffe9c929308);
    FUN_7ffe9996d590(&DAT_7ffe9c973348);
    FUN_7ffe9996d590(&DAT_7ffe9c973418);
    FUN_7ffe9996d590(0x7ffe9c9734e8);
    FUN_7ffe9996d590(&DAT_7ffe9c9419c0);
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c955b48);
    FUN_7ffe9996d590(&DAT_7ffe9c95b620);
    FUN_7ffe9996d590(&DAT_7ffe9c93ac18);
    FUN_7ffe9996d590(&DAT_7ffe9c909030);
    FUN_7ffe9996d590(&DAT_7ffe9c907ff0);
    FUN_7ffe9996d590(&DAT_7ffe9c919838);
    FUN_7ffe9996d590(&DAT_7ffe9c925008);
    DAT_7ffe9cade128 = '\x01';
  }
  lStackX_20 = 0;
  self_01 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c925008);
  PlayerStatusBase__ctor(self_01,(undefined *)0x0);
  if (self_01 != (undefined *)0x0) {
    *(int *)(self_01 + 0x10) = type;
    fVar6 = _DAT_7ffe9c049b18;
    if (*(int *)(_DAT_7ffe9c948908 + 0xe0) == 0) {
      func_0x7ffe9996d830(_DAT_7ffe9c948908);
    }
    if (**(longlong **)(_DAT_7ffe9c948908 + 0xb8) != 0) {
      cVar4 = FUN_7ffe9ad5efe0(**(longlong **)(_DAT_7ffe9c948908 + 0xb8),
                               *(undefined4 *)(self_01 + 0x10),_DAT_7ffe9c946970);
      fVar7 = fVar6;
      if (cVar4 == '\0') {
        if (*(longlong *)(self + 0x78) == 0) goto LAB_7ffe9a4eb1e9;
        lVar5 = _DAT_7ffe9c907ff0;
        FUN_7ffe9af836a0(&uStack_90);
        fVar3 = _DAT_7ffe9c049cfc;
        uStack_78 = (undefined4)uStack_90;
        uStack_74 = uStack_90._4_4_;
        uStack_70 = (undefined4)uStack_88;
        uStack_6c = uStack_88._4_4_;
        puStack_68 = puStack_80;
        while( true ) {
          skillIndividualFlag = (int)lVar5;
          cVar4 = FUN_7ffe9ae28ed0(&uStack_78,_DAT_7ffe9c973418);
          self_00 = puStack_68;
          if (cVar4 == '\0') break;
          if (puStack_68 == (undefined *)0x0) goto LAB_7ffe9a4eb214;
          if (*(longlong *)(puStack_68 + 0x18) == 0) goto LAB_7ffe9a4eb20f;
          lVar5 = _DAT_7ffe9c909030;
          cVar4 = FUN_7ffe9afc8940(*(longlong *)(puStack_68 + 0x18),*(undefined4 *)(self_01 + 0x10))
          ;
          if (cVar4 != '\0') {
            if (self_00[0x40] != '\0') {
              if (*(undefined **)(self + 0x18) == (undefined *)0x0) goto LAB_7ffe9a4eb1ef;
              in_R9 = (undefined *)0x0;
              BonusScriptManager_Run
                        (*(undefined **)(self + 0x18),*(undefined **)(self_00 + 0x10),0,
                         (undefined *)0x0);
              BonusData_UpdateBonusList(self_00,(undefined *)0x0);
            }
            uVar1 = *(undefined8 *)(self_00 + 0x20);
            lVar5 = *(longlong *)(self_01 + 0x18);
            if (lVar5 == 0) {
              lVar5 = func_0x7ffe99940040(_DAT_7ffe9c9419c0);
              in_R9 = (undefined *)0x0;
              FUN_7ffe9af13420(lVar5,self_01,_DAT_7ffe9c919838);
              *(longlong *)(self_01 + 0x18) = lVar5;
              il2cpp_write_barrier_0();
            }
            lVar5 = FUN_7ffe9ab93080(uVar1,lVar5,_DAT_7ffe9c929308);
            if (lVar5 == 0) goto LAB_7ffe9a4eb20a;
            lStackX_20 = FUN_7ffe99742ec0(0,_DAT_7ffe9c955b48,lVar5);
            uStack_90 = 0;
            uStack_88 = &lStackX_20;
            while( true ) {
              if (lStackX_20 == 0) goto LAB_7ffe9a4eb1ff;
              cVar4 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ac18);
              if (cVar4 == '\0') break;
              if (lStackX_20 == 0) goto LAB_7ffe9a4eb1fa;
              lVar5 = FUN_7ffe99742ec0(0,_DAT_7ffe9c95b620);
              if (lVar5 == 0) goto LAB_7ffe9a4eb1f5;
              fVar7 = fVar7 * (fVar6 - (float)*(int *)(lVar5 + 0x14) / fVar3);
            }
            lVar5 = lStackX_20;
            if (lStackX_20 != 0) {
              FUN_7ffe99743010(0,_DAT_7ffe9c939b40);
            }
          }
        }
        _GetDurationBonusTime_d__7_System_IDisposable_Dispose
                  ((undefined *)&uStack_78,(int)_DAT_7ffe9c973348,skillIndividualFlag,in_R9);
      }
      return fVar7;
    }
  }
LAB_7ffe9a4eb1e9:
  FUN_7ffe9996d7a0();
LAB_7ffe9a4eb1ef:
  FUN_7ffe9996d7a0();
LAB_7ffe9a4eb1f5:
  FUN_7ffe9996d7a0();
LAB_7ffe9a4eb1fa:
  FUN_7ffe9996d7a0();
LAB_7ffe9a4eb1ff:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
LAB_7ffe9a4eb20a:
  FUN_7ffe9996d7a0();
LAB_7ffe9a4eb20f:
  FUN_7ffe9996d7a0();
LAB_7ffe9a4eb214:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar2 = (code *)swi(3);
  fVar6 = (float)(*pcVar2)();
  return fVar6;
}

