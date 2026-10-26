
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int EquipRateBarrierBuf_Calc
              (undefined *self,int value,undefined *playerAct,undefined *mobAct,
              undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  longlong *plVar5;
  longlong lVar6;
  int iVar7;
  
  if (DAT_7ffe9cadf3c3 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c941198);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c8f7490);
    FUN_7ffe9996d590(&DAT_7ffe9c922658);
    DAT_7ffe9cadf3c3 = '\x01';
  }
  if (self[0x1c] == '\0') {
    return value;
  }
  self[0x1c] = 0;
  if (((playerAct != (undefined *)0x0) &&
      (plVar5 = (longlong *)
                (**(code **)(*(longlong *)playerAct + 0x298))
                          (playerAct,*(undefined8 *)(*(longlong *)playerAct + 0x2a0)),
      plVar5 != (longlong *)0x0)) &&
     (lVar6 = (**(code **)(*plVar5 + 0x208))(plVar5,*(undefined8 *)(*plVar5 + 0x210)), lVar6 != 0))
  {
    iVar3 = FUN_7ffe9a51d0c0(lVar6,0xa2,(int)*(float *)(self + 0x2c),0);
    *(float *)(self + 0x28) = (float)iVar3;
    iVar3 = *(int *)(self + 0x20);
    iVar2 = 1;
    if (0 < value) {
      iVar2 = value;
    }
    plVar5 = (longlong *)
             (**(code **)(*(longlong *)playerAct + 0x298))
                       (playerAct,*(undefined8 *)(*(longlong *)playerAct + 0x2a0));
    if ((plVar5 != (longlong *)0x0) &&
       (lVar6 = (**(code **)(*plVar5 + 0x198))(plVar5,*(undefined8 *)(*plVar5 + 0x1a0)), lVar6 != 0)
       ) {
      iVar4 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar6);
      iVar7 = (int)((float)iVar4 * ((float)iVar3 / _DAT_7ffe9c049cfc));
      iVar4 = iVar2 - iVar7;
      iVar3 = iVar4;
      if (iVar4 < 1) {
        iVar3 = 1;
      }
      lVar6 = *(longlong *)playerAct;
      iVar2 = iVar2 + -1;
      if (0 < iVar4) {
        iVar2 = iVar7;
      }
      if ((*(byte *)(lVar6 + 0x130) < *(byte *)(_DAT_7ffe9c922658 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(lVar6 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c922658 + 0x130) * 8)
          != _DAT_7ffe9c922658)) {
        if (*(byte *)(lVar6 + 0x130) < *(byte *)(_DAT_7ffe9c8f7490 + 0x130)) {
          return iVar3;
        }
        if (*(longlong *)
             (*(longlong *)(lVar6 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8f7490 + 0x130) * 8)
            != _DAT_7ffe9c8f7490) {
          return iVar3;
        }
      }
      if (*(int *)(_DAT_7ffe9c941198 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      FUN_7ffe9a7dce30(iVar2,0);
      return iVar3;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  iVar3 = (*pcVar1)();
  return iVar3;
}

