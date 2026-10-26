
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
MobAttackBase_GetBarrierBuf(undefined *mobAttack,undefined *status,undefined *methodInfo)

{
  code *pcVar1;
  longlong lVar2;
  undefined *puVar3;
  undefined8 uVar4;
  undefined *puStackX_8;
  
  if (DAT_7ffe9cadd7e4 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8ed488);
    FUN_7ffe9996d590(&DAT_7ffe9c8ee328);
    FUN_7ffe9996d590(&DAT_7ffe9c8ee3f8);
    FUN_7ffe9996d590(&DAT_7ffe9c8eeb48);
    DAT_7ffe9cadd7e4 = '\x01';
  }
  puStackX_8 = (undefined *)0x0;
  if (mobAttack == (undefined *)0x0) {
    return (undefined *)0x0;
  }
  lVar2 = *(longlong *)mobAttack;
  if (((*(byte *)(lVar2 + 0x130) < *(byte *)(_DAT_7ffe9c8ee3f8 + 0x130)) ||
      (*(longlong *)
        (*(longlong *)(lVar2 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8ee3f8 + 0x130) * 8) !=
       _DAT_7ffe9c8ee3f8)) &&
     ((*(byte *)(lVar2 + 0x130) < *(byte *)(_DAT_7ffe9c8ed488 + 0x130) ||
      (*(longlong *)
        (*(longlong *)(lVar2 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8ed488 + 0x130) * 8) !=
       _DAT_7ffe9c8ed488)))) {
    if ((*(byte *)(lVar2 + 0x130) < *(byte *)(_DAT_7ffe9c8ee328 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(lVar2 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8ee328 + 0x130) * 8) !=
        _DAT_7ffe9c8ee328)) {
      if (*(byte *)(lVar2 + 0x130) < *(byte *)(_DAT_7ffe9c8eeb48 + 0x130)) {
        return (undefined *)0x0;
      }
      if (*(longlong *)
           (*(longlong *)(lVar2 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8eeb48 + 0x130) * 8)
          != _DAT_7ffe9c8eeb48) {
        return (undefined *)0x0;
      }
      if ((status == (undefined *)0x0) ||
         (lVar2 = (**(code **)(*(longlong *)status + 0x1c8))
                            (status,*(undefined8 *)(*(longlong *)status + 0x1d0)), lVar2 == 0))
      goto LAB_7ffe9a375aa4;
      uVar4 = 2;
    }
    else {
      if ((status == (undefined *)0x0) ||
         (lVar2 = (**(code **)(*(longlong *)status + 0x1c8))
                            (status,*(undefined8 *)(*(longlong *)status + 0x1d0)), lVar2 == 0)) {
LAB_7ffe9a375aa4:
        FUN_7ffe9996d7a0();
        pcVar1 = (code *)swi(3);
        puVar3 = (undefined *)(*pcVar1)();
        return puVar3;
      }
      uVar4 = 3;
    }
  }
  else {
    if ((status == (undefined *)0x0) ||
       (lVar2 = (**(code **)(*(longlong *)status + 0x1c8))
                          (status,*(undefined8 *)(*(longlong *)status + 0x1d0)), lVar2 == 0))
    goto LAB_7ffe9a375aa4;
    uVar4 = 4;
  }
  FUN_7ffe9a7cbb30(lVar2,uVar4,&puStackX_8);
  return puStackX_8;
}

