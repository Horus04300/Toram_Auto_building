
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float UIPlayerStatusDetailPanel_CalcMagicPursuitValue(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  longlong lVar5;
  float fVar6;
  longlong alStackX_8 [4];
  
  if (DAT_7ffe9cadc4ce == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    DAT_7ffe9cadc4ce = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x70);
  alStackX_8[0] = 0;
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a090edb;
  lVar5 = (**(code **)(*plVar1 + 0x208))(plVar1,*(undefined8 *)(*plVar1 + 0x210));
  if (lVar5 == 0) goto LAB_7ffe9a090edb;
  iVar4 = FUN_7ffe9a51e120(lVar5,0x9a,0);
  plVar1 = *(longlong **)(self + 0x70);
  fVar6 = (float)iVar4;
  if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a090edb;
  lVar5 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
  if ((lVar5 == 0) || (*(longlong *)(lVar5 + 0x40) == 0)) goto LAB_7ffe9a090edb;
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar5 + 0x40),0x401,alStackX_8,_DAT_7ffe9c934418);
  if (cVar3 == '\0') {
    plVar1 = *(longlong **)(self + 0x70);
    if (plVar1 == (longlong *)0x0) goto LAB_7ffe9a090edb;
    lVar5 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
    if ((lVar5 == 0) || (*(longlong *)(lVar5 + 0x40) == 0)) goto LAB_7ffe9a090edb;
    cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar5 + 0x40),0x408,alStackX_8,_DAT_7ffe9c934418);
    if (cVar3 != '\0') goto LAB_7ffe9a090e43;
  }
  else {
LAB_7ffe9a090e43:
    if (alStackX_8[0] == 0) goto LAB_7ffe9a090edb;
    iVar4 = func_0x7ffe9a7a2140(alStackX_8[0],0x32);
    fVar6 = fVar6 + (float)iVar4;
  }
  plVar1 = *(longlong **)(self + 0x70);
  if (plVar1 != (longlong *)0x0) {
    lVar5 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
    if ((lVar5 != 0) && (*(longlong *)(lVar5 + 0x40) != 0)) {
      cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar5 + 0x40),0x3d6,alStackX_8,_DAT_7ffe9c934418);
      if (cVar3 != '\0') {
        if (alStackX_8[0] == 0) goto LAB_7ffe9a090edb;
        iVar4 = func_0x7ffe9a7a2140(alStackX_8[0],0x56);
        fVar6 = fVar6 + (float)iVar4;
      }
      return fVar6;
    }
  }
LAB_7ffe9a090edb:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  fVar6 = (float)(*pcVar2)();
  return fVar6;
}

