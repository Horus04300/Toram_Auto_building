
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte PlayerBattleManager_OnSkillActionStart
               (undefined *thisObject,undefined *target,undefined *targetActManager,
               undefined *action,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  char cVar4;
  undefined1 uVar5;
  byte bVar6;
  int iVar7;
  undefined4 uVar8;
  longlong *plVar9;
  longlong *plVar10;
  undefined *thisObject_00;
  longlong lVar11;
  undefined8 uVar12;
  longlong lVar13;
  undefined8 uVar14;
  longlong *plVar15;
  char cStack_88;
  char acStack_87 [7];
  longlong *plStack_80;
  undefined8 uStack_78;
  undefined4 uStack_70;
  undefined4 uStack_6c;
  undefined4 auStack_68 [2];
  longlong *plStack_60;
  longlong lStack_58;
  longlong *aplStack_50 [3];
  
  if (DAT_7ffe9caddcec == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9317a0);
    FUN_7ffe9996d590(&DAT_7ffe9c9368c8);
    FUN_7ffe9996d590(&DAT_7ffe9c938030);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c8f9db8);
    FUN_7ffe9996d590(&DAT_7ffe9c903e98);
    FUN_7ffe9996d590(&DAT_7ffe9c903f68);
    FUN_7ffe9996d590(&DAT_7ffe9c963748);
    FUN_7ffe9996d590(&DAT_7ffe9c928948);
    FUN_7ffe9996d590(&DAT_7ffe9c93e0e0);
    FUN_7ffe9996d590(&DAT_7ffe9c9481a0);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922658);
    FUN_7ffe9996d590(&DAT_7ffe9c9228b0);
    FUN_7ffe9996d590(&DAT_7ffe9c922a40);
    FUN_7ffe9996d590(&DAT_7ffe9c929de0);
    FUN_7ffe9996d590(&DAT_7ffe9c92d5b0);
    FUN_7ffe9996d590(&DAT_7ffe9c952a50);
    FUN_7ffe9996d590(&DAT_7ffe9c954a30);
    FUN_7ffe9996d590(&DAT_7ffe9c956938);
    FUN_7ffe9996d590(&DAT_7ffe9c949d68);
    FUN_7ffe9996d590(&DAT_7ffe9c94c0a0);
    FUN_7ffe9996d590(&DAT_7ffe9c9632c0);
    FUN_7ffe9996d590(&DAT_7ffe9c8fcc98);
    FUN_7ffe9996d590(&DAT_7ffe9c963f50);
    FUN_7ffe9996d590(&DAT_7ffe9c971518);
    DAT_7ffe9caddcec = '\x01';
  }
  plVar9 = (longlong *)0x0;
  cVar4 = '\0';
  auStack_68[0] = 0;
  uStack_70 = 0;
  uStack_6c = 0;
  plStack_60 = (longlong *)0x0;
  aplStack_50[0] = (longlong *)0x0;
  plStack_80 = (longlong *)0x0;
  uStack_78 = 0;
  acStack_87[0] = '\0';
  cStack_88 = '\0';
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar3 = FUN_7ffe9bda20c0(target,0);
  if (cVar3 == '\0') {
    return 0;
  }
  if (action == (undefined *)0x0) goto LAB_7ffe9a467640;
  iVar7 = (**(code **)(*(longlong *)action + 0x188))
                    (action,*(undefined8 *)(*(longlong *)action + 400));
  if (iVar7 == 0x4c2) {
    FUN_7ffe9a45b7d0(thisObject,target,action,0);
    return 0;
  }
  iVar7 = (**(code **)(*(longlong *)action + 0x188))
                    (action,*(undefined8 *)(*(longlong *)action + 400));
  if ((iVar7 == 0x4c3) && (cVar3 = FUN_7ffe9a45a170(thisObject,action,0), cVar3 != '\0')) {
    plVar9 = (longlong *)FUN_7ffe9a7fb2c0(0x4dd,action[0x14],*(undefined8 *)(thisObject + 0x28),0);
    if (plVar9 != (longlong *)0x0) {
      if ((*(byte *)(_DAT_7ffe9c92d5b0 + 0x130) <= *(byte *)(*plVar9 + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(*plVar9 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c92d5b0 + 0x130) * 8)
          == _DAT_7ffe9c92d5b0)) {
        FUN_7ffe9a730590(plVar9,*(undefined8 *)(thisObject + 0x28),0);
        FUN_7ffe9a7df370(thisObject,target,plVar9,0);
        return 0;
      }
      FUN_7ffe9996c950(plVar9);
      pcVar1 = (code *)swi(3);
      bVar6 = (*pcVar1)();
      return bVar6;
    }
    goto LAB_7ffe9a467640;
  }
  iVar7 = (**(code **)(*(longlong *)action + 0x188))
                    (action,*(undefined8 *)(*(longlong *)action + 400));
  if (iVar7 == 0x72) {
    FUN_7ffe9a45ab30(thisObject,target,targetActManager,action,0);
    return 0;
  }
  iVar7 = (**(code **)(*(longlong *)action + 0x188))
                    (action,*(undefined8 *)(*(longlong *)action + 400));
  if ((iVar7 == 0x26d) &&
     (cVar3 = FUN_7ffe9a470ea0(thisObject,target,targetActManager,action,0), cVar3 != '\0')) {
    return 0;
  }
  iVar7 = (**(code **)(*(longlong *)action + 0x188))
                    (action,*(undefined8 *)(*(longlong *)action + 400));
  if (iVar7 == 799) {
    FUN_7ffe9a46aba0(thisObject,action,0);
    return 0;
  }
  lVar11 = *(longlong *)action;
  if ((*(byte *)(_DAT_7ffe9c9228b0 + 0x130) <= *(byte *)(lVar11 + 0x130)) &&
     (*(longlong *)
       (*(longlong *)(lVar11 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c9228b0 + 0x130) * 8) ==
      _DAT_7ffe9c9228b0)) {
    if ((*(byte *)(lVar11 + 0x130) < *(byte *)(_DAT_7ffe9c9228b0 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(lVar11 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c9228b0 + 0x130) * 8) !=
        _DAT_7ffe9c9228b0)) {
      FUN_7ffe9996c950(action);
      pcVar1 = (code *)swi(3);
      bVar6 = (*pcVar1)();
      return bVar6;
    }
    (**(code **)(lVar11 + 0x678))
              (action,*(undefined8 *)(thisObject + 0x88),*(undefined8 *)(lVar11 + 0x680));
    if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c9228b0 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)action + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c9228b0 + 0x130) * 8) != _DAT_7ffe9c9228b0)) {
      FUN_7ffe9996c950(action);
      pcVar1 = (code *)swi(3);
      bVar6 = (*pcVar1)();
      return bVar6;
    }
    cVar3 = func_0x7ffe9a4ad2e0(action,0x2000,0);
    if (cVar3 != '\0') {
      plVar10 = *(longlong **)(thisObject + 0x88);
      if (((plVar10 == (longlong *)0x0) ||
          (plVar10 = (longlong *)
                     (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
          plVar10 == (longlong *)0x0)) ||
         (thisObject_00 =
               (undefined *)
               (**(code **)(*plVar10 + 0x218))(plVar10,*(undefined8 *)(*plVar10 + 0x220)),
         thisObject_00 == (undefined *)0x0)) goto LAB_7ffe9a467640;
      bVar6 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x40f,(undefined *)0x0);
      if (bVar6 != 0) {
        plVar10 = *(longlong **)(thisObject + 0x88);
        if (plVar10 == (longlong *)0x0) goto LAB_7ffe9a467640;
        lVar11 = (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
        uVar8 = (**(code **)(*(longlong *)action + 0x298))
                          (action,*(undefined8 *)(*(longlong *)action + 0x2a0));
        if (lVar11 == 0) goto LAB_7ffe9a467640;
        cVar3 = FUN_7ffe9a4a1760(lVar11,uVar8,0);
        if (cVar3 == '\0') {
          plVar10 = *(longlong **)(thisObject + 0x88);
          if (((plVar10 == (longlong *)0x0) ||
              (plVar10 = (longlong *)
                         (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
              plVar10 == (longlong *)0x0)) ||
             (lVar11 = (**(code **)(*plVar10 + 0x178))(plVar10,*(undefined8 *)(*plVar10 + 0x180)),
             lVar11 == 0)) goto LAB_7ffe9a467640;
          if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c9228b0 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(*(longlong *)action + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c9228b0 + 0x130) * 8) != _DAT_7ffe9c9228b0)) {
            FUN_7ffe9996c950(action,_DAT_7ffe9c9228b0);
            pcVar1 = (code *)swi(3);
            bVar6 = (*pcVar1)();
            return bVar6;
          }
          *(int *)(action + 200) = *(int *)(lVar11 + 0x18) / 100;
        }
      }
    }
  }
  if (*(int *)(_DAT_7ffe9c94c0a0 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar3 = FUN_7ffe9a8111e0(action,0);
  if (cVar3 != '\0') {
    iVar7 = (**(code **)(*(longlong *)action + 0x198))
                      (action,*(undefined8 *)(*(longlong *)action + 0x1a0));
    if (iVar7 == 1) {
      plVar10 = *(longlong **)(thisObject + 0x88);
      if ((plVar10 == (longlong *)0x0) ||
         (lVar11 = (**(code **)(*plVar10 + 0x2a8))(plVar10,*(undefined8 *)(*plVar10 + 0x2b0)),
         lVar11 == 0)) goto LAB_7ffe9a467640;
      cVar3 = FUN_7ffe9a4daa60(lVar11,0x13);
      if (cVar3 != '\0') {
        lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
        if (lVar11 != 0) {
          FUN_7ffe9a8a75a0(lVar11,0);
          lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
          if (lVar11 != 0) {
            FUN_7ffe99caacb0(lVar11,3);
            uVar12 = _DAT_7ffe9c963f50;
LAB_7ffe9a465968:
            func_0x7ffe999c3920(uVar12,0);
            return 0;
          }
        }
        goto LAB_7ffe9a467640;
      }
    }
    else {
      iVar7 = (**(code **)(*(longlong *)action + 0x198))
                        (action,*(undefined8 *)(*(longlong *)action + 0x1a0));
      if (iVar7 == 2) {
        plVar10 = *(longlong **)(thisObject + 0x88);
        if ((plVar10 == (longlong *)0x0) ||
           (lVar11 = (**(code **)(*plVar10 + 0x2a8))(plVar10,*(undefined8 *)(*plVar10 + 0x2b0)),
           lVar11 == 0)) goto LAB_7ffe9a467640;
        cVar3 = FUN_7ffe9a4daa60(lVar11,0x12);
        if (cVar3 != '\0') {
          lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
          if (lVar11 != 0) {
            FUN_7ffe9a8a75a0(lVar11,0);
            lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
            if (lVar11 != 0) {
              FUN_7ffe99caacb0(lVar11,2);
              uVar12 = _DAT_7ffe9c971518;
              goto LAB_7ffe9a465968;
            }
          }
          goto LAB_7ffe9a467640;
        }
      }
    }
  }
  iVar7 = (**(code **)(*(longlong *)action + 0x188))
                    (action,*(undefined8 *)(*(longlong *)action + 400));
  if (iVar7 == 0x325) {
    plVar10 = *(longlong **)(thisObject + 0x88);
    if (plVar10 == (longlong *)0x0) goto LAB_7ffe9a467640;
    uVar12 = (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
    cVar3 = (**(code **)(*(longlong *)action + 0x528))
                      (action,uVar12,auStack_68,*(undefined8 *)(*(longlong *)action + 0x530));
    if (cVar3 != '\0') {
      lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
      if (lVar11 != 0) {
        FUN_7ffe9a8a75a0(lVar11,0);
        lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
        if (lVar11 != 0) {
          FUN_7ffe99caacb0(lVar11,auStack_68[0],0);
          return 0;
        }
      }
      goto LAB_7ffe9a467640;
    }
  }
  else {
    iVar7 = (**(code **)(*(longlong *)action + 0x188))
                      (action,*(undefined8 *)(*(longlong *)action + 400));
    if (iVar7 == 0x10d) {
      plVar10 = *(longlong **)(thisObject + 0x88);
      if (plVar10 == (longlong *)0x0) goto LAB_7ffe9a467640;
      uVar12 = (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
      cVar3 = (**(code **)(*(longlong *)action + 0x528))
                        (action,uVar12,&uStack_70,*(undefined8 *)(*(longlong *)action + 0x530));
      if (cVar3 != '\0') {
        lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
        if (lVar11 != 0) {
          FUN_7ffe9a8a75a0(lVar11,0);
          lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
          if (lVar11 != 0) {
            FUN_7ffe99caacb0(lVar11,uStack_70,0);
            return 0;
          }
        }
        goto LAB_7ffe9a467640;
      }
    }
    else {
      iVar7 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      if (iVar7 == 0x3eb) {
        if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c8fcc98 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*(longlong *)action + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c8fcc98 + 0x130) * 8) != _DAT_7ffe9c8fcc98)) {
          FUN_7ffe9996c950(action);
          pcVar1 = (code *)swi(3);
          bVar6 = (*pcVar1)();
          return bVar6;
        }
        cVar3 = FUN_7ffe9a63e560(action,*(undefined8 *)(thisObject + 0x88),0);
        if (cVar3 == '\0') {
          lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
          if (lVar11 != 0) {
            FUN_7ffe9a8a75a0(lVar11,0);
            lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
            if (lVar11 != 0) {
              FUN_7ffe99caacb0(lVar11,6);
              return 0;
            }
          }
          goto LAB_7ffe9a467640;
        }
      }
    }
  }
  iVar7 = (**(code **)(*(longlong *)action + 0x188))
                    (action,*(undefined8 *)(*(longlong *)action + 400));
  if (iVar7 == 0xe4) {
    if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c929de0 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)action + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c929de0 + 0x130) * 8) != _DAT_7ffe9c929de0))
    goto LAB_7ffe9a467640;
    func_0x7ffe9a81d390(action,0);
  }
  iVar7 = (**(code **)(*(longlong *)action + 0x188))
                    (action,*(undefined8 *)(*(longlong *)action + 400));
  if (iVar7 == 0xed) {
    if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c928948 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)action + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c928948 + 0x130) * 8) != _DAT_7ffe9c928948))
    goto LAB_7ffe9a467640;
    func_0x7ffe9a81d390(action,0);
  }
  if ((*(byte *)(_DAT_7ffe9c9317a0 + 0x130) <= *(byte *)(*(longlong *)action + 0x130)) &&
     (*(longlong *)
       (*(longlong *)(*(longlong *)action + 200) + -8 +
       (ulonglong)*(byte *)(_DAT_7ffe9c9317a0 + 0x130) * 8) == _DAT_7ffe9c9317a0)) {
    FUN_7ffe9a74f9d0(action,0);
  }
  iVar7 = (**(code **)(*(longlong *)action + 0x188))
                    (action,*(undefined8 *)(*(longlong *)action + 400));
  if (iVar7 == 0x467) {
    bVar6 = FUN_7ffe9a464d30(thisObject,action,0);
    return bVar6;
  }
  iVar7 = (**(code **)(*(longlong *)action + 0x188))
                    (action,*(undefined8 *)(*(longlong *)action + 400));
  if (iVar7 == 0x308) {
    plVar10 = *(longlong **)(thisObject + 0x88);
    if (plVar10 == (longlong *)0x0) goto LAB_7ffe9a467640;
    uVar12 = (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
    cVar3 = (**(code **)(*(longlong *)action + 0x528))
                      (action,uVar12,&uStack_6c,*(undefined8 *)(*(longlong *)action + 0x530));
    if (cVar3 != '\0') {
      lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
      if (lVar11 != 0) {
        FUN_7ffe9a8a75a0(lVar11,0);
        lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
        if (lVar11 != 0) {
          FUN_7ffe99caacb0(lVar11,uStack_6c,0);
          return 0;
        }
      }
      goto LAB_7ffe9a467640;
    }
  }
  FUN_7ffe9a8fe3d0(action,targetActManager,0);
  if (DAT_7ffe9caddcc6 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    DAT_7ffe9caddcc6 = '\x01';
  }
  uVar12 = *(undefined8 *)(thisObject + 0x98);
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar3 = FUN_7ffe9bda2160(uVar12,0,0);
  if (cVar3 != '\0') {
    if (*(longlong *)(thisObject + 0x98) == 0) goto LAB_7ffe9a467640;
    if (((*(char *)(*(longlong *)(thisObject + 0x98) + 0x80) != '\0') &&
        (iVar7 = (**(code **)(*(longlong *)action + 0x188))
                           (action,*(undefined8 *)(*(longlong *)action + 400)), 0x20 < iVar7)) &&
       (iVar7 = (**(code **)(*(longlong *)action + 0x188))
                          (action,*(undefined8 *)(*(longlong *)action + 400)), iVar7 != 0x106)) {
      if (DAT_7ffe9caddcdd == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c906b90);
        DAT_7ffe9caddcdd = '\x01';
      }
      uVar12 = *(undefined8 *)(thisObject + 0x98);
      if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      cVar3 = FUN_7ffe9bda2160(uVar12,0,0);
      if (cVar3 != '\0') {
        if (*(longlong *)(thisObject + 0x98) == 0) goto LAB_7ffe9a467640;
        FUN_7ffe9a8f9ce0(*(longlong *)(thisObject + 0x98),1,0);
      }
    }
  }
  FUN_7ffe9a459970(thisObject,action,0);
  lVar11 = func_0x7ffe9996c920(targetActManager,_DAT_7ffe9c9724e0);
  if (lVar11 == 0) {
    cVar3 = (**(code **)(*(longlong *)action + 0x228))
                      (action,*(undefined8 *)(*(longlong *)action + 0x230));
    if (cVar3 == '\0') {
      return 0;
    }
    plVar9 = *(longlong **)(thisObject + 0x30);
    if (plVar9 == (longlong *)0x0) goto LAB_7ffe9a467640;
    if ((*(byte *)(*plVar9 + 0x130) < *(byte *)(_DAT_7ffe9c949d68 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*plVar9 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c949d68 + 0x130) * 8)
        != _DAT_7ffe9c949d68)) {
      FUN_7ffe9996c950(plVar9);
      pcVar1 = (code *)swi(3);
      bVar6 = (*pcVar1)();
      return bVar6;
    }
    (**(code **)(*plVar9 + 0x228))(plVar9,action,*(undefined8 *)(*plVar9 + 0x230));
    cVar3 = FUN_7ffe9a457ec0(thisObject,action,&cStack_88,0);
    if (cVar3 != '\0') {
      if (cStack_88 == '\0') {
        return 0;
      }
      lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
      if (lVar11 != 0) {
        FUN_7ffe9a8d6d90(lVar11,target,action,0);
        return 0;
      }
      goto LAB_7ffe9a467640;
    }
    if ((*(longlong *)(thisObject + 0xa8) != 0) &&
       (cVar3 = func_0x7ffe9a4ceea0(*(longlong *)(thisObject + 0xa8),0), cVar3 != '\0')) {
      if (*(longlong *)(thisObject + 0xa8) == 0) goto LAB_7ffe9a467640;
      plVar9 = *(longlong **)(thisObject + 0x88);
      lVar11 = *(longlong *)(*(longlong *)(thisObject + 0xa8) + 0x28);
      if ((plVar9 == (longlong *)0x0) ||
         (uVar12 = (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0)),
         lVar11 == 0)) goto LAB_7ffe9a467640;
      cVar3 = FUN_7ffe9a7f0480(lVar11,uVar12,0);
      if (cVar3 == '\0') {
LAB_7ffe9a46648a:
        lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
        if (lVar11 != 0) {
          FUN_7ffe9a8a75a0(lVar11,0);
          return 0;
        }
        goto LAB_7ffe9a467640;
      }
      if (*(longlong *)(thisObject + 0xa8) == 0) goto LAB_7ffe9a467640;
      FUN_7ffe9a7ee7b0(*(longlong *)(thisObject + 0xa8),*(undefined8 *)(thisObject + 0x88),0);
    }
    plVar9 = *(longlong **)(thisObject + 0x88);
    if (((plVar9 == (longlong *)0x0) ||
        (plVar9 = (longlong *)
                  (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0)),
        plVar9 == (longlong *)0x0)) ||
       (lVar11 = (**(code **)(*plVar9 + 0x1c8))(plVar9,*(undefined8 *)(*plVar9 + 0x1d0)),
       lVar11 == 0)) goto LAB_7ffe9a467640;
    cVar3 = FUN_7ffe9a7cbb30(lVar11,0x91,&plStack_80,0);
    if (cVar3 != '\0') {
      if (plStack_80 == (longlong *)0x0) goto LAB_7ffe9a467640;
      if (((*(byte *)(*plStack_80 + 0x130) < *(byte *)(_DAT_7ffe9c9368c8 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*plStack_80 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7ffe9c9368c8 + 0x130) * 8) != _DAT_7ffe9c9368c8)) ||
         (plStack_80 == (longlong *)0x0)) {
        FUN_7ffe9996c950(plStack_80);
        pcVar1 = (code *)swi(3);
        bVar6 = (*pcVar1)();
        return bVar6;
      }
      FUN_7ffe9a77a2f0(plStack_80,action,0);
    }
    iVar7 = (**(code **)(*(longlong *)action + 0x188))
                      (action,*(undefined8 *)(*(longlong *)action + 400));
    if (((iVar7 == 0x428) ||
        (iVar7 = (**(code **)(*(longlong *)action + 0x188))
                           (action,*(undefined8 *)(*(longlong *)action + 400)), iVar7 == 0x4c7)) ||
       ((((iVar7 = (**(code **)(*(longlong *)action + 0x188))
                             (action,*(undefined8 *)(*(longlong *)action + 400)), iVar7 == 0x4c8 ||
          ((((iVar7 = (**(code **)(*(longlong *)action + 0x188))
                                (action,*(undefined8 *)(*(longlong *)action + 400)), iVar7 == 0x93
             || (iVar7 = (**(code **)(*(longlong *)action + 0x188))
                                   (action,*(undefined8 *)(*(longlong *)action + 400)),
                iVar7 == 0x325)) ||
            (iVar7 = (**(code **)(*(longlong *)action + 0x188))
                               (action,*(undefined8 *)(*(longlong *)action + 400)), iVar7 == 0x36c))
           || ((iVar7 = (**(code **)(*(longlong *)action + 0x188))
                                  (action,*(undefined8 *)(*(longlong *)action + 400)),
               iVar7 == 0x36b ||
               (iVar7 = (**(code **)(*(longlong *)action + 0x188))
                                  (action,*(undefined8 *)(*(longlong *)action + 400)), iVar7 == 0x65
               )))))) ||
         (iVar7 = (**(code **)(*(longlong *)action + 0x188))
                            (action,*(undefined8 *)(*(longlong *)action + 400)), iVar7 == 0x6e)) ||
        ((iVar7 = (**(code **)(*(longlong *)action + 0x188))
                            (action,*(undefined8 *)(*(longlong *)action + 400)), iVar7 == 0x74 ||
         (cVar3 = (**(code **)(*(longlong *)action + 0x238))
                            (action,*(undefined8 *)(*(longlong *)action + 0x240)), cVar3 != '\0'))))
       )) {
      if (*(longlong *)(thisObject + 0xd0) == 0) goto LAB_7ffe9a46767f;
      uVar8 = FUN_7ffe99aaea90(*(longlong *)(thisObject + 0xd0),0);
      func_0x7ffe9a8fe3c0(action,uVar8,0);
    }
    FUN_7ffe99744e90(0x27,action,*(undefined8 *)(thisObject + 0x28),target);
    lVar11 = func_0x7ffe997430a0(action,_DAT_7ffe9c903e98);
    if (lVar11 == 0) {
      FUN_7ffe99744e90(0x28,action,*(undefined8 *)(thisObject + 0x28),target);
      (**(code **)(*(longlong *)action + 0x548))
                (action,*(undefined8 *)(*(longlong *)action + 0x550));
      plVar9 = *(longlong **)(thisObject + 0x88);
      if (((plVar9 == (longlong *)0x0) ||
          (plVar9 = (longlong *)
                    (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0)),
          plVar9 == (longlong *)0x0)) ||
         (lVar11 = (**(code **)(*plVar9 + 0x1c8))(plVar9,*(undefined8 *)(*plVar9 + 0x1d0)),
         lVar11 == 0)) goto LAB_7ffe9a46767f;
      cVar4 = FUN_7ffe9a7c4f20(lVar11,0);
      if ((cVar4 != '\0') &&
         (cVar4 = (**(code **)(*(longlong *)action + 0x328))
                            (action,*(undefined8 *)(*(longlong *)action + 0x330)), cVar4 == '\0')) {
        plVar9 = *(longlong **)(thisObject + 0x88);
        if ((plVar9 == (longlong *)0x0) ||
           ((plVar9 = (longlong *)
                      (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0)),
            plVar9 == (longlong *)0x0 ||
            (lVar11 = (**(code **)(*plVar9 + 0x1c8))(plVar9,*(undefined8 *)(*plVar9 + 0x1d0)),
            lVar11 == 0)))) goto LAB_7ffe9a46767f;
        func_0x7ffe9a7cba00(lVar11,0);
      }
      if (*(longlong *)(thisObject + 0xa0) == 0) goto LAB_7ffe9a46767f;
      FUN_7ffe9a7d9360(*(longlong *)(thisObject + 0xa0),action,0);
      lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
      if (lVar11 == 0) goto LAB_7ffe9a46767f;
      FUN_7ffe9a8d6d90(lVar11,target,action,0);
      plVar9 = *(longlong **)(thisObject + 0x88);
      if (((plVar9 == (longlong *)0x0) ||
          (plVar9 = (longlong *)
                    (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0)),
          plVar9 == (longlong *)0x0)) ||
         (lVar11 = (**(code **)(*plVar9 + 0x1c8))(plVar9,*(undefined8 *)(*plVar9 + 0x1d0)),
         lVar11 == 0)) goto LAB_7ffe9a46767f;
      cVar4 = FUN_7ffe9a7cbb30(lVar11,0x2c6,&plStack_80,0);
      plVar9 = plStack_80;
      if (cVar4 != '\0') {
        lVar11 = FUN_7ffe99744bb0(plStack_80,_DAT_7ffe9c938030);
        if (lVar11 == 0) goto LAB_7ffe9a46767f;
        uVar12 = FUN_7ffe99744bb0(plVar9,_DAT_7ffe9c938030);
        FUN_7ffe9a77abf0(uVar12,action,0);
      }
      cVar4 = func_0x7ffe99744540(0x3c,thisObject,action);
      if (cVar4 != '\0') {
        iVar7 = (**(code **)(*(longlong *)action + 0x188))
                          (action,*(undefined8 *)(*(longlong *)action + 400));
        if (((iVar7 == 0x428) ||
            (iVar7 = (**(code **)(*(longlong *)action + 0x188))
                               (action,*(undefined8 *)(*(longlong *)action + 400)), iVar7 == 0x4c7))
           || (iVar7 = func_0x7ffe99742fe0(5,action), iVar7 == 0x4c8)) {
          if (*(longlong *)(thisObject + 0xd0) == 0) goto LAB_7ffe9a46767f;
          FUN_7ffe99aaebf0(*(longlong *)(thisObject + 0xd0),*(undefined4 *)(action + 0x10),0);
        }
        iVar7 = func_0x7ffe99742fe0(5,action);
        lVar11 = _DAT_7ffe9c922658;
        if (iVar7 != 0x205) {
          return 0;
        }
        uVar12 = *(undefined8 *)(thisObject + 0x28);
        lVar13 = func_0x7ffe997430a0(uVar12,_DAT_7ffe9c922658);
        if (lVar13 != 0) {
          uVar12 = func_0x7ffe997430a0(uVar12,lVar11);
          lVar11 = func_0x7ffe99742fe0(0x16,uVar12);
          if ((lVar11 != 0) && (lVar11 = func_0x7ffe99742fe0(9,lVar11), lVar11 != 0)) {
            FUN_7ffe9a7cafa0(lVar11,0x205,0);
            return 0;
          }
        }
        goto LAB_7ffe9a46767f;
      }
      cVar4 = FUN_7ffe9a43cc80(thisObject,action,0);
      if (cVar4 == '\0') {
        return 0;
      }
      if (thisObject[0xb0] != '\0') {
        uVar5 = func_0x7ffe99742fe0(10,action);
        thisObject[0xb0] = uVar5;
      }
      goto LAB_7ffe9a466475;
    }
    if (target == (undefined *)0x0) goto LAB_7ffe9a46767f;
    lVar11 = FUN_7ffe9ab9c3a0(target,_DAT_7ffe9c963748);
    lStack_58 = 0;
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar3 = FUN_7ffe9bda2160(lVar11,0,0);
    if (cVar3 != '\0') {
      if (lVar11 == 0) goto LAB_7ffe9a46767f;
      cVar4 = *(char *)(lVar11 + 0xf0);
    }
    cVar4 = cVar4 != '\0';
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar3 = FUN_7ffe9bda2160(lVar11,0,0);
    if (cVar3 != '\0') {
      lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
      if (lVar13 == 0) goto LAB_7ffe9a46767f;
      cVar3 = FUN_7ffe9a5a4650(lVar13,0);
      if (cVar3 != '\0') {
        lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
        if (lVar11 == 0) goto LAB_7ffe9a46767f;
        uStack_78 = *(undefined8 *)(lVar11 + 0x48);
        uVar5 = func_0x7ffe9bb9e860(&uStack_78,0);
        uStack_78 = *(undefined8 *)(lVar11 + 0x48);
        uVar8 = func_0x7ffe9a331500(&uStack_78,0);
        if (lVar13 == 0) goto LAB_7ffe9a46767f;
        lVar13 = FUN_7ffe9a59be30(lVar13,uVar5,uVar8,0);
        if (lVar13 != 0) {
          uVar12 = *(undefined8 *)(lVar13 + 0x20);
          if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          cVar3 = FUN_7ffe9bda2160(uVar12,0,0);
          if (cVar3 != '\0') {
            if (*(longlong *)(lVar13 + 0x20) == 0) goto LAB_7ffe9a46767f;
            cVar4 = FUN_7ffe99b1ccd0(*(longlong *)(lVar13 + 0x20),0);
            if (cVar4 == '\0') {
              cVar4 = (float)*(byte *)(lVar13 + 0x30) <= 0.0;
            }
            else {
              cVar4 = true;
            }
          }
        }
      }
    }
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar3 = FUN_7ffe9bda1fa0(lVar11,0,0);
    if (cVar3 == '\0') {
LAB_7ffe9a466781:
      if (lVar11 == 0) goto LAB_7ffe9a46767f;
      uStack_78 = *(undefined8 *)(lVar11 + 0x48);
      cVar3 = func_0x7ffe9bb9e860(&uStack_78,0);
      if ((cVar3 == '\0') && (cVar3 = FUN_7ffe9a3bccd0(lVar11,0), cVar3 != '\0')) {
        return 0;
      }
    }
    else {
      lVar13 = FUN_7ffe9a47bac0(0);
      if ((lVar13 == 0) || (*(longlong *)(lVar13 + 0x70) == 0)) goto LAB_7ffe9a46767f;
      cVar3 = FUN_7ffe99a23410(*(longlong *)(lVar13 + 0x70),target,&lStack_58,0);
      if (cVar3 == '\0') goto LAB_7ffe9a466781;
      if (lStack_58 == 0) goto LAB_7ffe9a46767f;
      cVar4 = *(char *)(lStack_58 + 0xb4);
    }
    if (cVar4 == '\0') {
      return 0;
    }
    FUN_7ffe99744e90(0x28,action,*(undefined8 *)(thisObject + 0x28),target);
    if ((*(longlong *)(thisObject + 0x78) == 0) ||
       (lVar11 = FUN_7ffe99742ec0(10,_DAT_7ffe9c93e0e0), lVar11 == 0)) goto LAB_7ffe9a46767f;
    cVar4 = FUN_7ffe9a51e320(lVar11,0x8f,0);
    if (cVar4 != '\0') {
      if ((*(longlong *)(thisObject + 0x78) == 0) ||
         (lVar11 = FUN_7ffe99742ec0(10,_DAT_7ffe9c93e0e0), lVar11 == 0)) goto LAB_7ffe9a46767f;
      iVar7 = FUN_7ffe9a51e120(lVar11,0x8f,0);
      plVar9 = *(longlong **)(thisObject + 0x88);
      if ((plVar9 == (longlong *)0x0) ||
         (((plVar9 = (longlong *)
                     (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0)),
           plVar9 == (longlong *)0x0 ||
           (lVar11 = (**(code **)(*plVar9 + 0x1c8))(plVar9,*(undefined8 *)(*plVar9 + 0x1d0)),
           lVar11 == 0)) || (*(longlong *)(lVar11 + 0x40) == 0)))) goto LAB_7ffe9a46767f;
      cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar11 + 0x40),9,&plStack_80,_DAT_7ffe9c934418);
      if (cVar4 == '\0') {
        plVar10 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c903f68);
        FUN_7ffe9a78c2e0(plVar10,0,0,0);
        plVar9 = *(longlong **)(thisObject + 0x88);
        plStack_80 = plVar10;
        if (((plVar9 == (longlong *)0x0) ||
            (plVar9 = (longlong *)
                      (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0)),
            plVar9 == (longlong *)0x0)) ||
           (lVar11 = (**(code **)(*plVar9 + 0x1c8))(plVar9,*(undefined8 *)(*plVar9 + 0x1d0)),
           lVar11 == 0)) goto LAB_7ffe9a46767f;
        FUN_7ffe9a7c26c0(lVar11,plStack_80,0,0);
      }
      plVar9 = plStack_80;
      lVar11 = FUN_7ffe99744bb0(plStack_80,_DAT_7ffe9c903f68);
      if (lVar11 == 0) goto LAB_7ffe9a46767f;
      uVar12 = FUN_7ffe99744bb0(plVar9,_DAT_7ffe9c903f68);
      func_0x7ffe9a78c2c0(uVar12,(float)iVar7,0);
    }
    plVar9 = *(longlong **)(thisObject + 0x88);
    if (((plVar9 != (longlong *)0x0) &&
        (plVar9 = (longlong *)
                  (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0)),
        plVar9 != (longlong *)0x0)) &&
       (lVar11 = (**(code **)(*plVar9 + 0x1c8))(plVar9,*(undefined8 *)(*plVar9 + 0x1d0)),
       lVar11 != 0)) {
      cVar4 = FUN_7ffe9a7c4f20(lVar11,0);
      if (cVar4 != '\0') {
        plVar9 = *(longlong **)(thisObject + 0x88);
        if (((plVar9 == (longlong *)0x0) ||
            (plVar9 = (longlong *)
                      (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0)),
            plVar9 == (longlong *)0x0)) ||
           (lVar11 = (**(code **)(*plVar9 + 0x1c8))(plVar9,*(undefined8 *)(*plVar9 + 0x1d0)),
           lVar11 == 0)) goto LAB_7ffe9a46767f;
        func_0x7ffe9a7cba00(lVar11,0);
      }
      if (*(longlong *)(thisObject + 0xa0) != 0) {
        FUN_7ffe9a7d9360(*(longlong *)(thisObject + 0xa0),action,0);
        lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
        if (lVar11 != 0) {
          FUN_7ffe9a8d6d90(lVar11,target,action,0);
          plVar9 = *(longlong **)(thisObject + 0x88);
          if (((plVar9 != (longlong *)0x0) &&
              (plVar9 = (longlong *)
                        (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0)),
              plVar9 != (longlong *)0x0)) &&
             (lVar11 = (**(code **)(*plVar9 + 0x1c8))(plVar9,*(undefined8 *)(*plVar9 + 0x1d0)),
             lVar11 != 0)) {
            cVar4 = FUN_7ffe9a7cbb30(lVar11,0x2c6,&plStack_80,0);
            plVar9 = plStack_80;
            if (cVar4 != '\0') {
              lVar11 = FUN_7ffe99744bb0(plStack_80,_DAT_7ffe9c938030);
              if (lVar11 == 0) goto LAB_7ffe9a46767f;
              uVar12 = FUN_7ffe99744bb0(plVar9,_DAT_7ffe9c938030);
              FUN_7ffe9a77abf0(uVar12,action,0);
            }
            cVar4 = func_0x7ffe99744540(0x3c,thisObject,action);
            if (cVar4 != '\0') {
              return 0;
            }
            if (thisObject[0xb0] != '\0') {
              uVar5 = (**(code **)(*(longlong *)action + 0x1d8))
                                (action,*(undefined8 *)(*(longlong *)action + 0x1e0));
              thisObject[0xb0] = uVar5;
            }
            return 1;
          }
        }
      }
    }
LAB_7ffe9a46767f:
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    bVar6 = (*pcVar1)();
    return bVar6;
  }
  lVar13 = FUN_7ffe9a35c7f0(0);
  if (lVar13 == 0) goto LAB_7ffe9a467640;
  if (*(char *)(lVar13 + 0x28) != '\0') {
    lVar13 = FUN_7ffe9a35c7f0(0);
    if (lVar13 == 0) goto LAB_7ffe9a467640;
    if (*(char *)(lVar13 + 0x2d) == '\0') {
      lVar13 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
      uVar12 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c9724e0,lVar11);
      if (lVar13 == 0) goto LAB_7ffe9a467640;
      cVar4 = FUN_7ffe9a337770(lVar13,uVar12,0);
      if (cVar4 == '\0') {
        return 0;
      }
    }
  }
  iVar7 = (**(code **)(*(longlong *)action + 0x188))
                    (action,*(undefined8 *)(*(longlong *)action + 400));
  if (((iVar7 != 0x12) &&
      (iVar7 = (**(code **)(*(longlong *)action + 0x188))
                         (action,*(undefined8 *)(*(longlong *)action + 400)), iVar7 != 0x2df)) &&
     ((iVar7 = (**(code **)(*(longlong *)action + 0x188))
                         (action,*(undefined8 *)(*(longlong *)action + 400)), iVar7 != 0x2a1 &&
      ((iVar7 = (**(code **)(*(longlong *)action + 0x188))
                          (action,*(undefined8 *)(*(longlong *)action + 400)), iVar7 != 0x2a2 &&
       (iVar7 = (**(code **)(*(longlong *)action + 0x188))
                          (action,*(undefined8 *)(*(longlong *)action + 400)), iVar7 != 0x2a3))))))
  {
    plVar10 = *(longlong **)(thisObject + 0x30);
    if (plVar10 == (longlong *)0x0) goto LAB_7ffe9a467640;
    if ((*(byte *)(*plVar10 + 0x130) < *(byte *)(_DAT_7ffe9c949d68 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*plVar10 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c949d68 + 0x130) * 8)
        != _DAT_7ffe9c949d68)) {
      FUN_7ffe9996c950(plVar10);
      pcVar1 = (code *)swi(3);
      bVar6 = (*pcVar1)();
      return bVar6;
    }
    (**(code **)(*plVar10 + 0x228))(plVar10,action,*(undefined8 *)(*plVar10 + 0x230));
  }
  cVar4 = FUN_7ffe99742ec0(2,_DAT_7ffe9c9724e0,lVar11);
  if (cVar4 != '\0') {
    return 0;
  }
  *(undefined4 *)(thisObject + 0xb4) = 0;
  *(undefined8 *)(thisObject + 0xb8) = 0;
  thisObject[0xb1] = 0;
  il2cpp_write_barrier_0();
  if (DAT_7ffe9caddcce == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    DAT_7ffe9caddcce = '\x01';
  }
  lVar13 = FUN_7ffe9a35c7f0(0);
  if (lVar13 == 0) goto LAB_7ffe9a467640;
  if (*(char *)(lVar13 + 0x28) == '\0') {
    FUN_7ffe99742ec0(0x27,_DAT_7ffe9c9724e0,lVar11);
  }
  cVar4 = FUN_7ffe9a457ec0(thisObject,action,acStack_87,0);
  if (cVar4 != '\0') {
    if (acStack_87[0] == '\0') {
      return 0;
    }
    lVar11 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
    if (lVar11 != 0) {
      FUN_7ffe9a8a1f90(lVar11,0,action,0);
      return 0;
    }
    goto LAB_7ffe9a467640;
  }
  uVar8 = (**(code **)(*(longlong *)action + 0x188))
                    (action,*(undefined8 *)(*(longlong *)action + 400));
  if (*(int *)(_DAT_7ffe9c94c0a0 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar4 = func_0x7ffe9a8112f0(uVar8,0);
  if (((cVar4 == '\0') && (*(longlong *)(thisObject + 0xa8) != 0)) &&
     (cVar4 = func_0x7ffe9a4ceea0(*(longlong *)(thisObject + 0xa8),0), cVar4 != '\0')) {
    if (*(longlong *)(thisObject + 0xa8) == 0) goto LAB_7ffe9a467640;
    plVar10 = *(longlong **)(thisObject + 0x88);
    lVar13 = *(longlong *)(*(longlong *)(thisObject + 0xa8) + 0x28);
    if ((plVar10 == (longlong *)0x0) ||
       (uVar12 = (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
       lVar13 == 0)) goto LAB_7ffe9a467640;
    cVar4 = FUN_7ffe9a7f0480(lVar13,uVar12,0);
    if (cVar4 == '\0') goto LAB_7ffe9a46648a;
    if (*(longlong *)(thisObject + 0xa8) == 0) goto LAB_7ffe9a467640;
    plVar10 = *(longlong **)(thisObject + 0x88);
    lVar13 = *(longlong *)(*(longlong *)(thisObject + 0xa8) + 0x28);
    if ((plVar10 == (longlong *)0x0) ||
       (uVar12 = (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
       lVar13 == 0)) goto LAB_7ffe9a467640;
    FUN_7ffe9a7f0100(lVar13,uVar12,0);
    if (*(longlong *)(thisObject + 0xa8) == 0) goto LAB_7ffe9a467640;
    FUN_7ffe9a7ee7b0(*(longlong *)(thisObject + 0xa8),*(undefined8 *)(thisObject + 0x88),0);
  }
  if (*(longlong *)(thisObject + 0xd0) == 0) goto LAB_7ffe9a467640;
  uVar8 = FUN_7ffe99aaea90(*(longlong *)(thisObject + 0xd0),0);
  func_0x7ffe9a8fe3c0(action,uVar8,0);
  plVar10 = *(longlong **)(thisObject + 0x88);
  if (((plVar10 == (longlong *)0x0) ||
      (plVar10 = (longlong *)
                 (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
      plVar10 == (longlong *)0x0)) ||
     (lVar13 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
     lVar13 == 0)) goto LAB_7ffe9a467640;
  cVar4 = FUN_7ffe9a7cbb30(lVar13,0x91,&plStack_60,0);
  if (cVar4 != '\0') {
    if (plStack_60 == (longlong *)0x0) goto LAB_7ffe9a467640;
    if (((*(byte *)(*plStack_60 + 0x130) < *(byte *)(_DAT_7ffe9c9368c8 + 0x130)) ||
        (*(longlong *)
          (*(longlong *)(*plStack_60 + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c9368c8 + 0x130) * 8) != _DAT_7ffe9c9368c8)) ||
       (plStack_60 == (longlong *)0x0)) {
      FUN_7ffe9996c950(plStack_60);
      pcVar1 = (code *)swi(3);
      bVar6 = (*pcVar1)();
      return bVar6;
    }
    FUN_7ffe9a77a2f0(plStack_60,action,0);
  }
  uVar12 = *(undefined8 *)(thisObject + 0x28);
  uVar14 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c9724e0,lVar11);
  (**(code **)(*(longlong *)action + 0x3a8))
            (action,uVar12,uVar14,*(undefined8 *)(*(longlong *)action + 0x3b0));
  lVar13 = *(longlong *)action;
  if ((*(byte *)(lVar13 + 0x130) < *(byte *)(_DAT_7ffe9c9481a0 + 0x130)) ||
     (*(longlong *)
       (*(longlong *)(lVar13 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c9481a0 + 0x130) * 8) !=
      _DAT_7ffe9c9481a0)) {
LAB_7ffe9a46700c:
    cVar4 = (**(code **)(lVar13 + 0x218))(action,*(undefined8 *)(lVar13 + 0x220));
    if (cVar4 == '\0') {
      uVar12 = *(undefined8 *)(thisObject + 0x28);
      uVar14 = FUN_7ffe99742ec0(6,_DAT_7ffe9c9724e0,lVar11);
      FUN_7ffe9a8fc4b0(action,uVar12,uVar14,0);
    }
  }
  else {
    if ((*(byte *)(lVar13 + 0x130) < *(byte *)(_DAT_7ffe9c9481a0 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(lVar13 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c9481a0 + 0x130) * 8) !=
        _DAT_7ffe9c9481a0)) {
      FUN_7ffe9996c950(action,_DAT_7ffe9c9481a0);
      pcVar1 = (code *)swi(3);
      bVar6 = (*pcVar1)();
      return bVar6;
    }
    if ((*(int *)(action + 0x150) != 0) && (*(int *)(action + 0x150) != 5)) goto LAB_7ffe9a46700c;
  }
  uVar12 = *(undefined8 *)(thisObject + 0x28);
  uVar14 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c9724e0,lVar11);
  (**(code **)(*(longlong *)action + 0x3b8))
            (action,uVar12,uVar14,*(undefined8 *)(*(longlong *)action + 0x3c0));
  (**(code **)(*(longlong *)action + 0x548))(action,*(undefined8 *)(*(longlong *)action + 0x550));
  plVar10 = *(longlong **)(thisObject + 0x88);
  if (((plVar10 != (longlong *)0x0) &&
      (plVar10 = (longlong *)
                 (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
      plVar10 != (longlong *)0x0)) &&
     (lVar13 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
     lVar13 != 0)) {
    cVar4 = FUN_7ffe9a7c4f20(lVar13,0);
    if (((((cVar4 != '\0') &&
          (iVar7 = (**(code **)(*(longlong *)action + 0x188))
                             (action,*(undefined8 *)(*(longlong *)action + 400)), iVar7 != 0x308))
         && ((iVar7 = (**(code **)(*(longlong *)action + 0x188))
                                (action,*(undefined8 *)(*(longlong *)action + 400)), iVar7 != 0x31d
             && ((iVar7 = (**(code **)(*(longlong *)action + 0x188))
                                    (action,*(undefined8 *)(*(longlong *)action + 400)),
                 iVar7 != 0x2df &&
                 (iVar7 = (**(code **)(*(longlong *)action + 0x188))
                                    (action,*(undefined8 *)(*(longlong *)action + 400)),
                 iVar7 != 0x12)))))) &&
        (iVar7 = (**(code **)(*(longlong *)action + 0x188))
                           (action,*(undefined8 *)(*(longlong *)action + 400)), iVar7 != 0x2dc)) &&
       (cVar4 = (**(code **)(*(longlong *)action + 0x328))
                          (action,*(undefined8 *)(*(longlong *)action + 0x330)), cVar4 == '\0')) {
      plVar10 = *(longlong **)(thisObject + 0x88);
      if (((plVar10 == (longlong *)0x0) ||
          (plVar10 = (longlong *)
                     (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
          plVar10 == (longlong *)0x0)) ||
         (lVar13 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
         lVar13 == 0)) goto LAB_7ffe9a467640;
      func_0x7ffe9a7cba00(lVar13,0);
    }
    if (*(longlong *)(thisObject + 0xa0) != 0) {
      FUN_7ffe9a7d9360(*(longlong *)(thisObject + 0xa0),action,0);
      lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
      if (lVar13 != 0) {
        FUN_7ffe9a8a1f90(lVar13,lVar11,action,0);
        plVar10 = *(longlong **)(thisObject + 0x88);
        if (((plVar10 != (longlong *)0x0) &&
            (plVar10 = (longlong *)
                       (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
            plVar10 != (longlong *)0x0)) &&
           (lVar13 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
           lVar13 != 0)) {
          cVar4 = FUN_7ffe9a7cbb30(lVar13,0x2c6,&plStack_60,0);
          if (cVar4 != '\0') {
            if (plStack_60 == (longlong *)0x0) goto LAB_7ffe9a467640;
            if (((*(byte *)(*plStack_60 + 0x130) < *(byte *)(_DAT_7ffe9c938030 + 0x130)) ||
                (*(longlong *)
                  (*(longlong *)(*plStack_60 + 200) + -8 +
                  (ulonglong)*(byte *)(_DAT_7ffe9c938030 + 0x130) * 8) != _DAT_7ffe9c938030)) ||
               (plStack_60 == (longlong *)0x0)) {
              FUN_7ffe9996c950(plStack_60);
              pcVar1 = (code *)swi(3);
              bVar6 = (*pcVar1)();
              return bVar6;
            }
            FUN_7ffe9a77abf0(plStack_60,action,0);
          }
          cVar4 = (**(code **)(*(longlong *)thisObject + 0x4f8))
                            (thisObject,action,*(undefined8 *)(*(longlong *)thisObject + 0x500));
          if ((cVar4 == '\0') && (cVar4 = FUN_7ffe9a43cc80(thisObject,action,0), cVar4 != '\0')) {
            iVar7 = (**(code **)(*(longlong *)action + 0x188))
                              (action,*(undefined8 *)(*(longlong *)action + 400));
            if (iVar7 == 0x28b) {
              plVar10 = *(longlong **)(thisObject + 0x28);
              plVar15 = plVar9;
              if (plVar10 != (longlong *)0x0) {
                if ((*(byte *)(*plVar10 + 0x130) < *(byte *)(_DAT_7ffe9c922658 + 0x130)) ||
                   (*(longlong *)
                     (*(longlong *)(*plVar10 + 200) + -8 +
                     (ulonglong)*(byte *)(_DAT_7ffe9c922658 + 0x130) * 8) != _DAT_7ffe9c922658)) {
                  bVar2 = false;
                }
                else {
                  bVar2 = true;
                }
                if (bVar2) {
                  plVar15 = plVar10;
                }
              }
              if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                func_0x7ffe9996d830();
              }
              cVar4 = FUN_7ffe9bda2160(plVar15,0,0);
              if (cVar4 != '\0') {
                if (plVar15 == (longlong *)0x0) goto LAB_7ffe9a467640;
                plVar10 = (longlong *)plVar15[6];
                if (plVar10 != (longlong *)0x0) {
                  if ((*(byte *)(*plVar10 + 0x130) < *(byte *)(_DAT_7ffe9c922a40 + 0x130)) ||
                     (*(longlong *)
                       (*(longlong *)(*plVar10 + 200) + -8 +
                       (ulonglong)*(byte *)(_DAT_7ffe9c922a40 + 0x130) * 8) != _DAT_7ffe9c922a40)) {
                    bVar2 = false;
                  }
                  else {
                    bVar2 = true;
                  }
                  if (bVar2) {
                    plVar9 = plVar10;
                  }
                }
                if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                  func_0x7ffe9996d830();
                }
                cVar4 = FUN_7ffe9bda2160(plVar9,0,0);
                if (cVar4 != '\0') {
                  uVar12 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c9724e0,lVar11);
                  if (plVar9 == (longlong *)0x0) goto LAB_7ffe9a467640;
                  FUN_7ffe9a468740(plVar9,plVar15,uVar12,0);
                }
              }
            }
            if (thisObject[0xb0] != '\0') {
              uVar5 = (**(code **)(*(longlong *)action + 0x1d8))
                                (action,*(undefined8 *)(*(longlong *)action + 0x1e0));
              thisObject[0xb0] = uVar5;
            }
            plVar9 = *(longlong **)(thisObject + 0x88);
            if ((((plVar9 != (longlong *)0x0) &&
                 (plVar9 = (longlong *)
                           (**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0)),
                 plVar9 != (longlong *)0x0)) &&
                (lVar11 = (**(code **)(*plVar9 + 0x1c8))(plVar9,*(undefined8 *)(*plVar9 + 0x1d0)),
                lVar11 != 0)) && (*(longlong *)(lVar11 + 0x50) != 0)) {
              cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar11 + 0x50),0x428,aplStack_50,
                                       _DAT_7ffe9c934418);
              if (cVar4 != '\0') {
                if (aplStack_50[0] == (longlong *)0x0) goto LAB_7ffe9a467640;
                if (((*(byte *)(*aplStack_50[0] + 0x130) < *(byte *)(_DAT_7ffe9c8f9db8 + 0x130)) ||
                    (*(longlong *)
                      (*(longlong *)(*aplStack_50[0] + 200) + -8 +
                      (ulonglong)*(byte *)(_DAT_7ffe9c8f9db8 + 0x130) * 8) != _DAT_7ffe9c8f9db8)) ||
                   (aplStack_50[0] == (longlong *)0x0)) {
                  FUN_7ffe9996c950(aplStack_50[0]);
                  pcVar1 = (code *)swi(3);
                  bVar6 = (*pcVar1)();
                  return bVar6;
                }
                FUN_7ffe9a78ad10(aplStack_50[0],targetActManager,0);
              }
LAB_7ffe9a466475:
              FUN_7ffe9a4702e0(thisObject,action,0);
              return 1;
            }
          }
          else if (*(longlong *)(thisObject + 0xd0) != 0) {
            FUN_7ffe99aaebf0(*(longlong *)(thisObject + 0xd0),*(undefined4 *)(action + 0x10),0);
            return 0;
          }
        }
      }
    }
  }
LAB_7ffe9a467640:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  bVar6 = (*pcVar1)();
  return bVar6;
}

