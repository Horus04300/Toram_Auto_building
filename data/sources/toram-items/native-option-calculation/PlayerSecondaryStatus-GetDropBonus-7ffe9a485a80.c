
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_GetDropBonus(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined *self_00;
  longlong lVar6;
  longlong *plStackX_8;
  
  if (DAT_7ffe9cadde29 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    DAT_7ffe9cadde29 = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x10);
  plStackX_8 = (longlong *)0x0;
  if ((plVar1 != (longlong *)0x0) &&
     (self_00 = (undefined *)(**(code **)(*plVar1 + 0x1d8))(plVar1,*(undefined8 *)(*plVar1 + 0x1e0))
     , self_00 != (undefined *)0x0)) {
    iVar4 = BonusManager_GetBonusValue(self_00,0x40,(undefined *)0x0);
    plVar1 = *(longlong **)(self + 0x10);
    if ((plVar1 != (longlong *)0x0) &&
       (lVar6 = (**(code **)(*plVar1 + 0x188))(plVar1,*(undefined8 *)(*plVar1 + 400)), lVar6 != 0))
    {
      plVar1 = *(longlong **)(self + 0x10);
      iVar4 = *(int *)(lVar6 + 0x2c) / 5 + iVar4;
      if (((plVar1 != (longlong *)0x0) &&
          (lVar6 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0)),
          lVar6 != 0)) && (*(longlong *)(lVar6 + 0x68) != 0)) {
        cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar6 + 0x68),0xc3,&plStackX_8,_DAT_7ffe9c935bd0);
        if (cVar3 != '\0') {
          if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a485c13;
          iVar5 = (**(code **)(*plStackX_8 + 0x178))
                            (plStackX_8,0x1c,*(undefined8 *)(*plStackX_8 + 0x180));
          iVar4 = iVar4 + iVar5;
        }
        if (*(int *)(self + 0x18) != 2) {
          return iVar4;
        }
        lVar6 = FUN_7ffe9a47bac0(0);
        if (lVar6 != 0) {
          if (DAT_7ffe9cadddc1 == '\0') {
            FUN_7ffe9996d590(&DAT_7ffe9c952be8);
            DAT_7ffe9cadddc1 = '\x01';
          }
          lVar6 = FUN_7ffe9b141840(_DAT_7ffe9c952be8);
          if ((lVar6 != 0) && (*(longlong *)(lVar6 + 0x40) != 0)) {
            iVar5 = func_0x7ffe9a53b4e0(*(longlong *)(lVar6 + 0x40),*(undefined4 *)(self + 0x18),0);
            return iVar4 + iVar5;
          }
        }
      }
    }
  }
LAB_7ffe9a485c13:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar4 = (*pcVar2)();
  return iVar4;
}

