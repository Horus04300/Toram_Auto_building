
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float UIPlayerStatusDetailPanel_CalcAvoidBreakerValue(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  longlong lVar5;
  int iVar6;
  float fVar7;
  float fVar8;
  longlong lStackX_8;
  
  if (DAT_7ffe9cadc4cb == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92bfa0);
    DAT_7ffe9cadc4cb = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x70);
  iVar6 = 0;
  lStackX_8 = 0;
  if ((plVar1 != (longlong *)0x0) &&
     (lVar5 = (**(code **)(*plVar1 + 0x208))(plVar1,*(undefined8 *)(*plVar1 + 0x210)), lVar5 != 0))
  {
    cVar3 = FUN_7ffe9ab944b0(lVar5,0x90,&lStackX_8,_DAT_7ffe9c92bfa0);
    if (cVar3 != '\0') {
      if (lStackX_8 == 0) goto LAB_7ffe9a0907a8;
      iVar6 = (int)*(short *)(lStackX_8 + 0x10);
    }
    plVar1 = *(longlong **)(self + 0x70);
    fVar7 = (float)iVar6;
    if ((plVar1 != (longlong *)0x0) &&
       (lVar5 = (**(code **)(*plVar1 + 0x218))(plVar1,*(undefined8 *)(*plVar1 + 0x220)), lVar5 != 0)
       ) {
      cVar3 = FUN_7ffe9a5b20c0(lVar5,0x46,0);
      if (cVar3 == '\0') {
        return fVar7;
      }
      plVar1 = *(longlong **)(self + 0x70);
      if ((plVar1 != (longlong *)0x0) &&
         (lVar5 = (**(code **)(*plVar1 + 0x218))(plVar1,*(undefined8 *)(*plVar1 + 0x220)),
         lVar5 != 0)) {
        iVar6 = FUN_7ffe9a5b2120(lVar5,0x46,0);
        if (iVar6 < 1) {
          return fVar7;
        }
        plVar1 = *(longlong **)(self + 0x70);
        if ((plVar1 != (longlong *)0x0) &&
           (lVar5 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)),
           lVar5 != 0)) {
          iVar4 = FUN_7ffe99c09050(lVar5,0);
          fVar8 = _DAT_7ffe9c049b18;
          if (iVar4 != 10) {
            return fVar7;
          }
          plVar1 = *(longlong **)(self + 0x70);
          if ((plVar1 != (longlong *)0x0) &&
             (lVar5 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)),
             lVar5 != 0)) {
            iVar4 = FUN_7ffe99c08f50(lVar5,0);
            if (iVar4 == 0x11) {
              fVar8 = _DAT_7ffe9c049b74;
            }
            return fVar7 + (float)(int)((float)iVar6 * fVar8);
          }
        }
      }
    }
  }
LAB_7ffe9a0907a8:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  fVar7 = (float)(*pcVar2)();
  return fVar7;
}

