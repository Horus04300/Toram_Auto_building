
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobAttackBase_GetBarrierType(undefined *mobAttack,undefined *methodInfo)

{
  longlong lVar1;
  
  if (DAT_7ffe9cadd7e3 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8ed488);
    FUN_7ffe9996d590(&DAT_7ffe9c8ee328);
    FUN_7ffe9996d590(&DAT_7ffe9c8ee3f8);
    FUN_7ffe9996d590(&DAT_7ffe9c8eeb48);
    DAT_7ffe9cadd7e3 = '\x01';
  }
  if (mobAttack == (undefined *)0x0) {
    return 0;
  }
  lVar1 = *(longlong *)mobAttack;
  if (((*(byte *)(_DAT_7ffe9c8ee3f8 + 0x130) <= *(byte *)(lVar1 + 0x130)) &&
      (*(longlong *)
        (*(longlong *)(lVar1 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8ee3f8 + 0x130) * 8) ==
       _DAT_7ffe9c8ee3f8)) ||
     ((*(byte *)(_DAT_7ffe9c8ed488 + 0x130) <= *(byte *)(lVar1 + 0x130) &&
      (*(longlong *)
        (*(longlong *)(lVar1 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8ed488 + 0x130) * 8) ==
       _DAT_7ffe9c8ed488)))) {
    return 0xa1;
  }
  if ((*(byte *)(_DAT_7ffe9c8ee328 + 0x130) <= *(byte *)(lVar1 + 0x130)) &&
     (*(longlong *)
       (*(longlong *)(lVar1 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8ee328 + 0x130) * 8) ==
      _DAT_7ffe9c8ee328)) {
    return 0xa0;
  }
  if (*(byte *)(lVar1 + 0x130) < *(byte *)(_DAT_7ffe9c8eeb48 + 0x130)) {
    return 0;
  }
  if (*(longlong *)
       (*(longlong *)(lVar1 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8eeb48 + 0x130) * 8) !=
      _DAT_7ffe9c8eeb48) {
    return 0;
  }
  return 0x9f;
}

