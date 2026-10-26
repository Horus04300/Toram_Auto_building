
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UIPlayerStatusDetailPanel_AddBarrierStatus(undefined *self,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  char cVar3;
  longlong lVar4;
  longlong *plStackX_8;
  longlong alStackX_18 [2];
  undefined4 uVar5;
  undefined4 uVar6;
  undefined8 uVar7;
  undefined8 uVar8;
  undefined8 uVar9;
  undefined4 uVar10;
  undefined8 uVar11;
  undefined8 uVar12;
  
  if (DAT_7ffe9cadc4c9 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92c060);
    FUN_7ffe9996d590(&DAT_7ffe9c8f9188);
    FUN_7ffe9996d590(&DAT_7ffe9c8f9258);
    FUN_7ffe9996d590(&DAT_7ffe9c8f9328);
    DAT_7ffe9cadc4c9 = '\x01';
  }
  plVar1 = *(longlong **)(self + 0x70);
  plStackX_8 = (longlong *)0x0;
  alStackX_18[0] = 0;
  if ((plVar1 != (longlong *)0x0) &&
     (lVar4 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)), lVar4 != 0))
  {
    cVar3 = FUN_7ffe9a7cbb30(lVar4,2,&plStackX_8,0);
    if (cVar3 != '\0') {
      if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a08de09;
      if (((*(byte *)(*plStackX_8 + 0x130) < *(byte *)(_DAT_7ffe9c8f9258 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*plStackX_8 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7ffe9c8f9258 + 0x130) * 8) != _DAT_7ffe9c8f9258)) ||
         (plStackX_8 == (longlong *)0x0)) {
        FUN_7ffe9996c950(plStackX_8);
        pcVar2 = (code *)swi(3);
        (*pcVar2)();
        return;
      }
      EquipPhysicalBarrierBuf_GetBarrierValue
                ((undefined *)plStackX_8,*(undefined **)(self + 0x70),(undefined *)0x0);
    }
    uVar9 = _DAT_7ffe9c04a830;
    uVar7 = _DAT_7ffe9c04a820;
    uVar10 = _DAT_7ffe9c049b90;
    uVar11 = 0;
    uVar5 = 0;
    uVar12 = _DAT_7ffe9c04a820;
    uVar8 = _DAT_7ffe9c04a830;
    uVar6 = _DAT_7ffe9c049b90;
    FUN_7ffe9a08ef60(self,0x47);
    plVar1 = *(longlong **)(self + 0x70);
    if ((plVar1 != (longlong *)0x0) &&
       (lVar4 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)), lVar4 != 0)
       ) {
      cVar3 = FUN_7ffe9a7cbb30(lVar4,3,&plStackX_8,0,uVar5,uVar12,uVar8,uVar6,uVar11);
      if (cVar3 != '\0') {
        if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a08de09;
        if (((*(byte *)(*plStackX_8 + 0x130) < *(byte *)(_DAT_7ffe9c8f9188 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*plStackX_8 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c8f9188 + 0x130) * 8) != _DAT_7ffe9c8f9188)) ||
           (plStackX_8 == (longlong *)0x0)) {
          FUN_7ffe9996c950(plStackX_8);
          pcVar2 = (code *)swi(3);
          (*pcVar2)();
          return;
        }
        EquipMagicBarrierBuf_GetBarrierValue
                  ((undefined *)plStackX_8,*(undefined **)(self + 0x70),(undefined *)0x0);
      }
      uVar11 = 0;
      uVar5 = 0;
      uVar12 = uVar7;
      uVar8 = uVar9;
      uVar6 = uVar10;
      FUN_7ffe9a08ef60(self,0x48);
      plVar1 = *(longlong **)(self + 0x70);
      if ((plVar1 != (longlong *)0x0) &&
         (lVar4 = (**(code **)(*plVar1 + 0x1c8))(plVar1,*(undefined8 *)(*plVar1 + 0x1d0)),
         lVar4 != 0)) {
        cVar3 = FUN_7ffe9a7cbb30(lVar4,4,&plStackX_8,0,uVar5,uVar12,uVar8,uVar6,uVar11);
        if (cVar3 != '\0') {
          if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a08de09;
          if (((*(byte *)(*plStackX_8 + 0x130) < *(byte *)(_DAT_7ffe9c8f9328 + 0x130)) ||
              (*(longlong *)
                (*(longlong *)(*plStackX_8 + 200) + -8 +
                (ulonglong)*(byte *)(_DAT_7ffe9c8f9328 + 0x130) * 8) != _DAT_7ffe9c8f9328)) ||
             (plStackX_8 == (longlong *)0x0)) {
            FUN_7ffe9996c950(plStackX_8);
            pcVar2 = (code *)swi(3);
            (*pcVar2)();
            return;
          }
          EquipRateBarrierBuf_GetBarrierValue
                    ((undefined *)plStackX_8,*(undefined **)(self + 0x70),(undefined *)0x0);
        }
        uVar12 = 0;
        uVar6 = 0;
        FUN_7ffe9a08ef60(self);
        plVar1 = *(longlong **)(self + 0x70);
        if (((plVar1 != (longlong *)0x0) &&
            (lVar4 = (**(code **)(*plVar1 + 0x208))(plVar1,*(undefined8 *)(*plVar1 + 0x210)),
            lVar4 != 0)) &&
           ((cVar3 = FUN_7ffe9ab944b0(lVar4,0xa2,alStackX_18,_DAT_7ffe9c92c060,uVar6,uVar7,uVar9,
                                      uVar10,uVar12), cVar3 == '\0' || (alStackX_18[0] != 0)))) {
          FUN_7ffe9a08ef60(self);
          FUN_7ffe9a08ee50(self,0);
          return;
        }
      }
    }
  }
LAB_7ffe9a08de09:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

