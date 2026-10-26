
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float UIPlayerStatusDetailPanel_CalcGuardBreakerValue(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  longlong lVar5;
  ulonglong uVar6;
  int iVar7;
  float fVar8;
  float fVar9;
  longlong lStackX_8;
  
  if (DAT_7ffe9cadc4cc == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92c1e0);
    DAT_7ffe9cadc4cc = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x70);
  iVar7 = 0;
  lStackX_8 = 0;
  if ((plVar1 != (longlong *)0x0) &&
     (lVar5 = (**(code **)(*plVar1 + 0x208))(plVar1,*(undefined8 *)(*plVar1 + 0x210)), lVar5 != 0))
  {
    cVar3 = FUN_7ffe9ab944b0(lVar5,0x91,&lStackX_8,_DAT_7ffe9c92c1e0);
    if (cVar3 != '\0') {
      if (lStackX_8 == 0) goto LAB_7ffe9a090b99;
      iVar7 = (int)*(short *)(lStackX_8 + 0x10);
    }
    plVar1 = *(longlong **)(self + 0x70);
    fVar8 = (float)iVar7;
    if ((plVar1 != (longlong *)0x0) &&
       (lVar5 = (**(code **)(*plVar1 + 0x218))(plVar1,*(undefined8 *)(*plVar1 + 0x220)), lVar5 != 0)
       ) {
      cVar3 = FUN_7ffe9a5b20c0(lVar5,0x48,0);
      if (cVar3 == '\0') {
        return fVar8;
      }
      plVar1 = *(longlong **)(self + 0x70);
      if ((plVar1 != (longlong *)0x0) &&
         (lVar5 = (**(code **)(*plVar1 + 0x218))(plVar1,*(undefined8 *)(*plVar1 + 0x220)),
         lVar5 != 0)) {
        iVar7 = FUN_7ffe9a5b2120(lVar5,0x48,0);
        if (iVar7 < 1) {
          return fVar8;
        }
        plVar1 = *(longlong **)(self + 0x70);
        if ((plVar1 != (longlong *)0x0) &&
           (lVar5 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)),
           lVar5 != 0)) {
          uVar6 = FUN_7ffe99c09050(lVar5,0);
          fVar9 = _DAT_7ffe9c049b18;
          if ((uVar6 & 0xffffffef) != 0) {
            return fVar8;
          }
          plVar1 = *(longlong **)(self + 0x70);
          if ((plVar1 != (longlong *)0x0) &&
             (lVar5 = (**(code **)(*plVar1 + 0x1f8))(plVar1,*(undefined8 *)(*plVar1 + 0x200)),
             lVar5 != 0)) {
            iVar4 = FUN_7ffe99c08f50(lVar5,0);
            if (iVar4 == 0) {
              fVar9 = _DAT_7ffe9c049b74;
            }
            return fVar8 + (float)(int)((float)iVar7 * fVar9);
          }
        }
      }
    }
  }
LAB_7ffe9a090b99:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  fVar8 = (float)(*pcVar2)();
  return fVar8;
}

