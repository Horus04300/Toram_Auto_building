
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float UIPlayerStatusDetailPanel_CalcPhysicalPursuitValue(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  longlong lVar5;
  float fVar6;
  longlong *aplStackX_8 [4];
  
  plVar1 = *(longlong **)(self + 0x70);
  aplStackX_8[0] = (longlong *)0x0;
  if (plVar1 != (longlong *)0x0) {
    lVar5 = (**(code **)(*plVar1 + 0x208))(plVar1,*(undefined8 *)(*plVar1 + 0x210));
    if (lVar5 != 0) {
      iVar4 = FUN_7ffe9a51e120(lVar5,0x99,0);
      plVar1 = *(longlong **)(self + 0x70);
      fVar6 = (float)iVar4;
      if (plVar1 != (longlong *)0x0) {
        lVar5 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0));
        if (lVar5 != 0) {
          cVar3 = FUN_7ffe9a7cbb30(lVar5,0x32,aplStackX_8);
          if (cVar3 != '\0') {
            if (aplStackX_8[0] == (longlong *)0x0) goto LAB_7ffe9a09117b;
            iVar4 = (**(code **)(*aplStackX_8[0] + 0x1f8))
                              (aplStackX_8[0],0x55,*(undefined8 *)(*aplStackX_8[0] + 0x200));
            fVar6 = fVar6 + (float)iVar4;
          }
          return fVar6;
        }
      }
    }
  }
LAB_7ffe9a09117b:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  fVar6 = (float)(*pcVar2)();
  return fVar6;
}

