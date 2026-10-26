
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UIPlayerStatusDetailPanel_AddAbsoluteStatus(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  longlong lVar4;
  longlong lStackX_8;
  longlong alStackX_18 [2];
  undefined4 uVar5;
  undefined8 uVar6;
  undefined8 uVar7;
  undefined4 uVar8;
  undefined8 uVar9;
  
  if (DAT_7ffe9cadc4ca == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92be18);
    FUN_7ffe9996d590(&DAT_7ffe9c92bee0);
    DAT_7ffe9cadc4ca = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x70);
  lStackX_8 = 0;
  alStackX_18[0] = 0;
  if (((plVar1 != (longlong *)0x0) &&
      (lVar4 = (**(code **)(*plVar1 + 0x208))(plVar1,*(undefined8 *)(*plVar1 + 0x210)), lVar4 != 0))
     && ((cVar3 = FUN_7ffe9ab944b0(lVar4,0x87,&lStackX_8,_DAT_7ffe9c92bee0), cVar3 == '\0' ||
         (lStackX_8 != 0)))) {
    uVar9 = 0;
    uVar5 = 0;
    uVar6 = _DAT_7ffe9c04a7f0;
    uVar7 = _DAT_7ffe9c04a830;
    uVar8 = _DAT_7ffe9c049b90;
    FUN_7ffe9a08ef60(self);
    plVar1 = *(longlong **)(self + 0x70);
    if (((plVar1 != (longlong *)0x0) &&
        (lVar4 = (**(code **)(*plVar1 + 0x208))(plVar1,*(undefined8 *)(*plVar1 + 0x210)), lVar4 != 0
        )) && ((cVar3 = FUN_7ffe9ab944b0(lVar4,0x88,alStackX_18,_DAT_7ffe9c92be18,uVar5,uVar6,uVar7,
                                         uVar8,uVar9), cVar3 == '\0' || (alStackX_18[0] != 0)))) {
      FUN_7ffe9a08ef60(self);
      FUN_7ffe9a08ee50(self,0);
      return;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

