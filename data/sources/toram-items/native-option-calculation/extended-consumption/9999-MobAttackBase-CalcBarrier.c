
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobAttackBase_CalcBarrier
              (undefined *self,int damage,undefined *playerAction,undefined *mobAction,
              undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  longlong *plVar4;
  longlong lVar5;
  longlong *plStackX_8;
  
  if (DAT_7ffe9cadd7cf == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f94c8);
    FUN_7ffe9996d590(&DAT_7ffe9c8ed488);
    FUN_7ffe9996d590(&DAT_7ffe9c8ee328);
    FUN_7ffe9996d590(&DAT_7ffe9c8ee3f8);
    FUN_7ffe9996d590(&DAT_7ffe9c8eeb48);
    DAT_7ffe9cadd7cf = '\x01';
  }
  plStackX_8 = (longlong *)0x0;
  if (self == (undefined *)0x0) {
    return damage;
  }
  lVar5 = *(longlong *)self;
  if ((*(byte *)(lVar5 + 0x130) < *(byte *)(_DAT_7ffe9c8eeb48 + 0x130)) ||
     (*(longlong *)
       (*(longlong *)(lVar5 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8eeb48 + 0x130) * 8) !=
      _DAT_7ffe9c8eeb48)) {
    if ((*(byte *)(lVar5 + 0x130) < *(byte *)(_DAT_7ffe9c8ee328 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(lVar5 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8ee328 + 0x130) * 8) !=
        _DAT_7ffe9c8ee328)) {
      if ((*(byte *)(lVar5 + 0x130) < *(byte *)(_DAT_7ffe9c8ee3f8 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(lVar5 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8ee3f8 + 0x130) * 8)
          != _DAT_7ffe9c8ee3f8)) {
        if (*(byte *)(lVar5 + 0x130) < *(byte *)(_DAT_7ffe9c8ed488 + 0x130)) {
          return damage;
        }
        if (*(longlong *)
             (*(longlong *)(lVar5 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8ed488 + 0x130) * 8)
            != _DAT_7ffe9c8ed488) {
          return damage;
        }
      }
      if (((playerAction != (undefined *)0x0) &&
          (plVar4 = (longlong *)
                    (**(code **)(*(longlong *)playerAction + 0x298))
                              (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
          plVar4 != (longlong *)0x0)) &&
         (lVar5 = (**(code **)(*plVar4 + 0x1c8))(plVar4,*(undefined8 *)(*plVar4 + 0x1d0)),
         lVar5 != 0)) {
        cVar2 = FUN_7ffe9a7cbb30(lVar5,4,&plStackX_8);
        if (cVar2 == '\0') {
          return damage;
        }
        if (plStackX_8 != (longlong *)0x0) {
          if (((*(byte *)(_DAT_7ffe9c8f94c8 + 0x130) <= *(byte *)(*plStackX_8 + 0x130)) &&
              (*(longlong *)
                (*(longlong *)(*plStackX_8 + 200) + -8 +
                (ulonglong)*(byte *)(_DAT_7ffe9c8f94c8 + 0x130) * 8) == _DAT_7ffe9c8f94c8)) &&
             (plStackX_8 != (longlong *)0x0)) {
            iVar3 = FUN_7ffe9974e1c0(0x17,plStackX_8,damage,playerAction,mobAction);
            return iVar3;
          }
          FUN_7ffe9996c950(plStackX_8);
          pcVar1 = (code *)swi(3);
          iVar3 = (*pcVar1)();
          return iVar3;
        }
      }
    }
    else if (((playerAction != (undefined *)0x0) &&
             (plVar4 = (longlong *)
                       (**(code **)(*(longlong *)playerAction + 0x298))
                                 (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
             plVar4 != (longlong *)0x0)) &&
            (lVar5 = (**(code **)(*plVar4 + 0x1c8))(plVar4,*(undefined8 *)(*plVar4 + 0x1d0)),
            lVar5 != 0)) {
      cVar2 = FUN_7ffe9a7cbb30(lVar5,3,&plStackX_8);
      if (cVar2 == '\0') {
        return damage;
      }
      if (plStackX_8 != (longlong *)0x0) {
        if (((*(byte *)(*plStackX_8 + 0x130) < *(byte *)(_DAT_7ffe9c8f94c8 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*plStackX_8 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c8f94c8 + 0x130) * 8) != _DAT_7ffe9c8f94c8)) ||
           (plStackX_8 == (longlong *)0x0)) {
          FUN_7ffe9996c950(plStackX_8);
          pcVar1 = (code *)swi(3);
          iVar3 = (*pcVar1)();
          return iVar3;
        }
        goto LAB_7ffe9a36e99e;
      }
    }
  }
  else if (((playerAction != (undefined *)0x0) &&
           (plVar4 = (longlong *)
                     (**(code **)(*(longlong *)playerAction + 0x298))
                               (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
           plVar4 != (longlong *)0x0)) &&
          (lVar5 = (**(code **)(*plVar4 + 0x1c8))(plVar4,*(undefined8 *)(*plVar4 + 0x1d0)),
          lVar5 != 0)) {
    cVar2 = FUN_7ffe9a7cbb30(lVar5,2,&plStackX_8,0);
    if (cVar2 == '\0') {
      return damage;
    }
    if (plStackX_8 != (longlong *)0x0) {
      if (((*(byte *)(*plStackX_8 + 0x130) < *(byte *)(_DAT_7ffe9c8f94c8 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*plStackX_8 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7ffe9c8f94c8 + 0x130) * 8) != _DAT_7ffe9c8f94c8)) ||
         (plStackX_8 == (longlong *)0x0)) {
        FUN_7ffe9996c950(plStackX_8);
        pcVar1 = (code *)swi(3);
        iVar3 = (*pcVar1)();
        return iVar3;
      }
LAB_7ffe9a36e99e:
      iVar3 = (**(code **)(*plStackX_8 + 0x2a8))
                        (plStackX_8,damage,playerAction,mobAction,
                         *(undefined8 *)(*plStackX_8 + 0x2b0));
      return iVar3;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  iVar3 = (*pcVar1)();
  return iVar3;
}

