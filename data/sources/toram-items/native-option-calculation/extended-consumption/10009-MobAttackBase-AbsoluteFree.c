
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MobAttackBase_AbsoluteFree
               (undefined *self,undefined *playerAction,undefined *type,undefined *hit,
               undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  int iVar6;
  longlong *plVar7;
  longlong lVar8;
  longlong *plVar9;
  
  if (DAT_7ffe9cadd7d6 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9481a0);
    FUN_7ffe9996d590(&DAT_7ffe9c948ea8);
    FUN_7ffe9996d590(&DAT_7ffe9c8edca8);
    FUN_7ffe9996d590(&DAT_7ffe9c9228b0);
    DAT_7ffe9cadd7d6 = '\x01';
  }
  if (*hit == '\0') {
    return 0;
  }
  if (((playerAction == (undefined *)0x0) ||
      (plVar7 = (longlong *)
                (**(code **)(*(longlong *)playerAction + 0x298))
                          (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
      plVar7 == (longlong *)0x0)) ||
     (lVar8 = (**(code **)(*plVar7 + 0x208))(plVar7,*(undefined8 *)(*plVar7 + 0x210)), lVar8 == 0))
  goto LAB_7ffe9a36e747;
  cVar3 = FUN_7ffe9a51e210(lVar8,0x88,0);
  if (cVar3 == '\0') {
    return 0;
  }
  if ((int)type == 2) {
    return 0;
  }
  if (self == (undefined *)0x0) {
LAB_7ffe9a36e488:
    if (*(longlong *)(self + 0xa0) == 0) goto LAB_7ffe9a36e747;
    iVar6 = *(int *)(*(longlong *)(self + 0xa0) + 0x2c);
  }
  else {
    lVar8 = *(longlong *)self;
    if ((*(byte *)(lVar8 + 0x130) < *(byte *)(_DAT_7ffe9c8edca8 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(lVar8 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8edca8 + 0x130) * 8) !=
        _DAT_7ffe9c8edca8)) goto LAB_7ffe9a36e488;
    if ((*(byte *)(lVar8 + 0x130) < *(byte *)(_DAT_7ffe9c8edca8 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(lVar8 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8edca8 + 0x130) * 8) !=
        _DAT_7ffe9c8edca8)) {
      FUN_7ffe9996c950(self);
      pcVar1 = (code *)swi(3);
      bVar4 = (*pcVar1)();
      return bVar4;
    }
    iVar6 = *(int *)(self + 0xf4);
  }
  if (iVar6 == 0) {
    return 0;
  }
  if ((*(longlong *)(playerAction + 0x30) != 0) &&
     (plVar7 = *(longlong **)(*(longlong *)(playerAction + 0x30) + 0x30), plVar7 != (longlong *)0x0)
     ) {
    plVar7 = (longlong *)(**(code **)(*plVar7 + 0x188))(plVar7,*(undefined8 *)(*plVar7 + 400));
    if (plVar7 == (longlong *)0x0) {
      plVar9 = (longlong *)0x0;
    }
    else {
      if ((*(byte *)(*plVar7 + 0x130) < *(byte *)(_DAT_7ffe9c9228b0 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar7 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c9228b0 + 0x130) * 8)
          != _DAT_7ffe9c9228b0)) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      plVar9 = (longlong *)0x0;
      if (bVar2) {
        plVar9 = plVar7;
      }
    }
    cVar3 = FUN_7ffe9a8fecd0(plVar9,0,0);
    if (cVar3 != '\0') {
      if (plVar9 == (longlong *)0x0) goto LAB_7ffe9a36e747;
      iVar5 = (**(code **)(*plVar9 + 0x188))(plVar9,*(undefined8 *)(*plVar9 + 400));
      if (((((iVar5 == 0x93) ||
            (iVar5 = (**(code **)(*plVar9 + 0x188))(plVar9,*(undefined8 *)(*plVar9 + 400)),
            iVar5 == 0x283)) ||
           (iVar5 = (**(code **)(*plVar9 + 0x188))(plVar9,*(undefined8 *)(*plVar9 + 400)),
           iVar5 == 0x36b)) ||
          ((iVar5 = (**(code **)(*plVar9 + 0x188))(plVar9,*(undefined8 *)(*plVar9 + 400)),
           iVar5 == 0x267 ||
           (iVar5 = (**(code **)(*plVar9 + 0x188))(plVar9,*(undefined8 *)(*plVar9 + 400)),
           iVar5 == 0x26a)))) ||
         ((iVar5 = (**(code **)(*plVar9 + 0x188))(plVar9,*(undefined8 *)(*plVar9 + 400)),
          iVar5 == 0x26f ||
          (iVar5 = (**(code **)(*plVar9 + 0x188))(plVar9,*(undefined8 *)(*plVar9 + 400)),
          iVar5 == 0x486)))) {
        return 0;
      }
      iVar5 = (**(code **)(*plVar9 + 0x188))(plVar9,*(undefined8 *)(*plVar9 + 400));
      if (iVar5 == 0x27d) {
        if ((*(byte *)(*plVar9 + 0x130) < *(byte *)(_DAT_7ffe9c9481a0 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar9 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c9481a0 + 0x130) * 8) != _DAT_7ffe9c9481a0)) {
          FUN_7ffe9996c950(plVar9);
          pcVar1 = (code *)swi(3);
          bVar4 = (*pcVar1)();
          return bVar4;
        }
        if ((int)plVar9[0x2a] == 0) {
          return 0;
        }
      }
      else {
        iVar5 = (**(code **)(*plVar9 + 0x188))(plVar9,*(undefined8 *)(*plVar9 + 400));
        if (iVar5 == 0x305) {
          if ((*(byte *)(*plVar9 + 0x130) < *(byte *)(_DAT_7ffe9c948ea8 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(*plVar9 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c948ea8 + 0x130) * 8) != _DAT_7ffe9c948ea8)) {
            FUN_7ffe9996c950(plVar9);
            pcVar1 = (code *)swi(3);
            bVar4 = (*pcVar1)();
            return bVar4;
          }
          cVar3 = func_0x7ffe9a8247f0(plVar9,0);
          if (cVar3 != '\0') {
            return 0;
          }
        }
      }
    }
    plVar7 = (longlong *)
             (**(code **)(*(longlong *)playerAction + 0x298))
                       (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if ((plVar7 != (longlong *)0x0) &&
       (lVar8 = (**(code **)(*plVar7 + 0x208))(plVar7,*(undefined8 *)(*plVar7 + 0x210)), lVar8 != 0)
       ) {
      iVar6 = FUN_7ffe9a51d0c0(lVar8,0x88,iVar6,0);
      if (0 < iVar6) {
        *hit = 0;
        return 0 < iVar6;
      }
      return 0 < iVar6;
    }
  }
LAB_7ffe9a36e747:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  bVar4 = (*pcVar1)();
  return bVar4;
}

