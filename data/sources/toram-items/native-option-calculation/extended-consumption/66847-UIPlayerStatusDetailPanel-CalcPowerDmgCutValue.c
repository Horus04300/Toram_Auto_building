
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int UIPlayerStatusDetailPanel_CalcPowerDmgCutValue(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  undefined *self_00;
  longlong lVar6;
  longlong *plStackX_8;
  
  if (DAT_7ffe9cadc4c5 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    DAT_7ffe9cadc4c5 = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x60);
  plStackX_8 = (longlong *)0x0;
  if (plVar1 != (longlong *)0x0) {
    self_00 = (undefined *)(**(code **)(*plVar1 + 0x298))(plVar1,*(undefined8 *)(*plVar1 + 0x2a0));
    if (self_00 != (undefined *)0x0) {
      iVar4 = PlayerStatusBase_GetBonusValueWithBuf(self_00,0x31,(undefined *)0x0);
      plVar1 = *(longlong **)(self + 0x70);
      if (plVar1 != (longlong *)0x0) {
        lVar6 = (**(code **)(*plVar1 + 0x1b8))(plVar1,*(undefined8 *)(*plVar1 + 0x1c0));
        if ((lVar6 != 0) && (*(longlong *)(lVar6 + 0x68) != 0)) {
          cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar6 + 0x68),0x103,&plStackX_8,_DAT_7ffe9c935bd0);
          if (cVar3 != '\0') {
            if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a091333;
            iVar5 = (**(code **)(*plStackX_8 + 0x178))
                              (plStackX_8,0x19,*(undefined8 *)(*plStackX_8 + 0x180));
            iVar4 = iVar4 + iVar5;
          }
          return iVar4;
        }
      }
    }
  }
LAB_7ffe9a091333:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar4 = (*pcVar2)();
  return iVar4;
}

