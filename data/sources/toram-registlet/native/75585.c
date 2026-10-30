
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBuffer_HealStockpileBuff_Update(undefined *self,undefined *methodInfo)

{
  float fVar1;
  undefined2 uVar2;
  longlong *plVar3;
  undefined8 uVar4;
  code *pcVar5;
  char cVar6;
  longlong lVar7;
  longlong *plVar8;
  float fVar9;
  longlong *plStackX_8;
  
  if (DAT_7ffe9cadd3d9 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c960fa0);
    FUN_7ffe9996d590(&DAT_7ffe9c90dea0);
    DAT_7ffe9cadd3d9 = '\x01';
  }
  plStackX_8 = (longlong *)0x0;
  GemCartBufferBase_Update(self,(undefined *)0x0);
  plVar3 = *(longlong **)(self + 0x18);
  if (plVar3 != (longlong *)0x0) {
    cVar6 = (**(code **)(*plVar3 + 0x248))(plVar3,*(undefined8 *)(*plVar3 + 0x250));
    if (cVar6 != '\0') {
      *(undefined4 *)(self + 0x20) = 0;
      return;
    }
    fVar1 = *(float *)(self + 0x20);
    fVar9 = (float)FUN_7ffe9bda7ce0(0);
    plVar3 = *(longlong **)(self + 0x18);
    *(float *)(self + 0x20) = fVar9 + fVar1;
    if ((plVar3 != (longlong *)0x0) &&
       (lVar7 = (**(code **)(*plVar3 + 0x1c8))(plVar3,*(undefined8 *)(*plVar3 + 0x1d0)), lVar7 != 0)
       ) {
      cVar6 = FUN_7ffe9a7cbb30(lVar7,0x17,&plStackX_8,0);
      if (cVar6 != '\0') {
        if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a2ea705;
        if (((*(byte *)(*plStackX_8 + 0x130) < *(byte *)(_DAT_7ffe9c960fa0 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*plStackX_8 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c960fa0 + 0x130) * 8) != _DAT_7ffe9c960fa0)) ||
           (plStackX_8 == (longlong *)0x0)) {
          FUN_7ffe9996c950(plStackX_8);
          pcVar5 = (code *)swi(3);
          (*pcVar5)();
          return;
        }
        cVar6 = (**(code **)(*plStackX_8 + 0x288))(plStackX_8,*(undefined8 *)(*plStackX_8 + 0x290));
        if (cVar6 != '\0') {
          *(undefined4 *)(self + 0x20) = 0;
        }
      }
      if (*(float *)(self + 0x20) < _DAT_7ffe9c049b74) {
        return;
      }
      *(float *)(self + 0x20) = *(float *)(self + 0x20) - _DAT_7ffe9c049b74;
      if (plStackX_8 != (longlong *)0x0) {
        if (((*(byte *)(_DAT_7ffe9c960fa0 + 0x130) <= *(byte *)(*plStackX_8 + 0x130)) &&
            (*(longlong *)
              (*(longlong *)(*plStackX_8 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c960fa0 + 0x130) * 8) == _DAT_7ffe9c960fa0)) &&
           (plStackX_8 != (longlong *)0x0)) {
          (**(code **)(*plStackX_8 + 0x2a8))(plStackX_8,*(undefined8 *)(*plStackX_8 + 0x2b0));
          return;
        }
        FUN_7ffe9996c950(plStackX_8);
        pcVar5 = (code *)swi(3);
        (*pcVar5)();
        return;
      }
      uVar2 = *(undefined2 *)(self + 0x14);
      uVar4 = *(undefined8 *)(self + 0x18);
      plVar8 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c90dea0);
      FUN_7ffe9a78d3c0(plVar8,(char)uVar2,1,uVar4,0);
      plVar3 = *(longlong **)(self + 0x18);
      plStackX_8 = plVar8;
      if ((plVar3 != (longlong *)0x0) &&
         (lVar7 = (**(code **)(*plVar3 + 0x1c8))(plVar3,*(undefined8 *)(*plVar3 + 0x1d0)),
         lVar7 != 0)) {
        FUN_7ffe9a7c26c0(lVar7,plStackX_8,0,0);
        return;
      }
    }
  }
LAB_7ffe9a2ea705:
  FUN_7ffe9996d7a0();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}

