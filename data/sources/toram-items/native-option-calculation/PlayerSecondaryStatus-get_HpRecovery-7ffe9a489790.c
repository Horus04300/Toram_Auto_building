
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_get_HpRecovery(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined *self_00;
  longlong lVar7;
  longlong *plStackX_8;
  
  iVar6 = 0;
  plStackX_8 = (longlong *)0x0;
  if (*(longlong **)(self + 0x10) != (longlong *)0x0) {
    self_00 = (undefined *)(**(code **)(**(longlong **)(self + 0x10) + 0x1d8))();
    iVar4 = PlayerSecondaryStatus_CalcBaseMaxHp(self,(undefined *)0x0);
    iVar5 = 99999;
    if (iVar4 < 99999) {
      iVar5 = iVar4;
    }
    if (self_00 != (undefined *)0x0) {
      iVar5 = BonusManager_GetCalcBonusValue(self_00,iVar5 / 0x19 + 10,0x23,0x22,(undefined *)0x0);
      plVar1 = *(longlong **)(self + 0x10);
      if (plVar1 != (longlong *)0x0) {
        lVar7 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
        if (lVar7 != 0) {
          cVar3 = FUN_7ffe9a7cbb30(lVar7,0xe2,&plStackX_8,0);
          if (cVar3 != '\0') {
            if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a48988d;
            iVar6 = (**(code **)(*plStackX_8 + 0x1f8))
                              (plStackX_8,0xf,*(undefined8 *)(*plStackX_8 + 0x200));
          }
          return (int)(float)iVar5 + iVar6;
        }
      }
    }
  }
LAB_7ffe9a48988d:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar6 = (*pcVar2)();
  return iVar6;
}

