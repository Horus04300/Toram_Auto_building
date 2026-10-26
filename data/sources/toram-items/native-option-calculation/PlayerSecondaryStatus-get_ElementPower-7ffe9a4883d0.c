
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerSecondaryStatus_get_ElementPower(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  longlong lVar5;
  int iVar6;
  double dVar7;
  float fVar8;
  longlong *plStackX_8;
  
  if (DAT_7ffe9cadde15 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    DAT_7ffe9cadde15 = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x10);
  plStackX_8 = (longlong *)0x0;
  if (plVar1 != (longlong *)0x0) {
    lVar5 = (**(code **)(*plVar1 + 0x188))(plVar1,*(undefined8 *)(*plVar1 + 400));
    if (lVar5 != 0) {
      fVar8 = (float)*(int *)(lVar5 + 0x18) / _DAT_7ffe9c049ce4;
      if (DAT_7ffe9cad9c12 == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c968830);
        DAT_7ffe9cad9c12 = '\x01';
      }
      if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      dVar7 = (double)func_0x7ffe999978b4((double)fVar8);
      plVar1 = *(longlong **)(self + 0x10);
      iVar6 = (int)dVar7;
      if (plVar1 != (longlong *)0x0) {
        lVar5 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
        if ((lVar5 != 0) && (*(longlong *)(lVar5 + 0x50) != 0)) {
          cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar5 + 0x50),0x40b,&plStackX_8,_DAT_7ffe9c934418);
          if (cVar3 != '\0') {
            if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a4884f9;
            iVar4 = (**(code **)(*plStackX_8 + 0x1f8))
                              (plStackX_8,0x32,*(undefined8 *)(*plStackX_8 + 0x200));
            iVar6 = iVar6 + iVar4;
          }
          return iVar6;
        }
      }
    }
  }
LAB_7ffe9a4884f9:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar6 = (*pcVar2)();
  return iVar6;
}

