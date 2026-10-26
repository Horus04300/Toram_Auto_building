
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int RateBarrier_Calc(undefined *self,int value,undefined *playerAct,undefined *mobAct,
                    undefined *methodInfo)

{
  short sVar1;
  code *pcVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  longlong *plVar6;
  longlong lVar7;
  int iVar8;
  
  if (DAT_7ffe9cade246 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c941198);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c8f7490);
    FUN_7ffe9996d590(&DAT_7ffe9c922658);
    DAT_7ffe9cade246 = '\x01';
  }
  if (self[0x12] == '\0') {
    return value;
  }
  self[0x12] = 0;
  if (((playerAct != (undefined *)0x0) &&
      (plVar6 = (longlong *)
                (**(code **)(*(longlong *)playerAct + 0x298))
                          (playerAct,*(undefined8 *)(*(longlong *)playerAct + 0x2a0)),
      plVar6 != (longlong *)0x0)) &&
     (lVar7 = (**(code **)(*plVar6 + 0x208))(plVar6,*(undefined8 *)(*plVar6 + 0x210)), lVar7 != 0))
  {
    iVar3 = FUN_7ffe9a51d0c0(lVar7,0xa2,(int)*(float *)(self + 0x18),0);
    *(float *)(self + 0x1c) = (float)iVar3;
    sVar1 = *(short *)(self + 0x10);
    iVar3 = 1;
    if (0 < value) {
      iVar3 = value;
    }
    plVar6 = (longlong *)
             (**(code **)(*(longlong *)playerAct + 0x298))
                       (playerAct,*(undefined8 *)(*(longlong *)playerAct + 0x2a0));
    if ((plVar6 != (longlong *)0x0) &&
       (lVar7 = (**(code **)(*plVar6 + 0x198))(plVar6,*(undefined8 *)(*plVar6 + 0x1a0)), lVar7 != 0)
       ) {
      iVar4 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar7);
      iVar8 = (int)((float)iVar4 * ((float)(int)sVar1 / _DAT_7ffe9c049cfc));
      iVar5 = iVar3 - iVar8;
      iVar4 = iVar5;
      if (iVar5 < 1) {
        iVar4 = 1;
      }
      lVar7 = *(longlong *)playerAct;
      iVar3 = iVar3 + -1;
      if (0 < iVar5) {
        iVar3 = iVar8;
      }
      if ((*(byte *)(lVar7 + 0x130) < *(byte *)(_DAT_7ffe9c922658 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(lVar7 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c922658 + 0x130) * 8)
          != _DAT_7ffe9c922658)) {
        if (*(byte *)(lVar7 + 0x130) < *(byte *)(_DAT_7ffe9c8f7490 + 0x130)) {
          return iVar4;
        }
        if (*(longlong *)
             (*(longlong *)(lVar7 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8f7490 + 0x130) * 8)
            != _DAT_7ffe9c8f7490) {
          return iVar4;
        }
      }
      if (*(int *)(_DAT_7ffe9c941198 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      FUN_7ffe9a7dce30(iVar3,0);
      return iVar4;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar3 = (*pcVar2)();
  return iVar3;
}

