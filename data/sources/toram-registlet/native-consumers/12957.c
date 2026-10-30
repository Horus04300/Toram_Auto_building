
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte PlayerActionManager_SkillReserveMpLess
               (undefined *thisObject,undefined *action,undefined *sendActionStart,
               undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  byte bVar4;
  undefined4 uVar5;
  int iVar6;
  longlong lVar7;
  longlong *plVar8;
  undefined *puVar9;
  undefined8 uVar10;
  longlong *thisObject_00;
  
  if (DAT_7ffe9caddc9e == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9228b0);
    FUN_7ffe9996d590(&DAT_7ffe9c952a50);
    FUN_7ffe9996d590(&DAT_7ffe9c956938);
    DAT_7ffe9caddc9e = '\x01';
  }
  *sendActionStart = 0;
  if (action == (undefined *)0x0) {
    thisObject_00 = (longlong *)0x0;
  }
  else {
    if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c9228b0 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)action + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c9228b0 + 0x130) * 8) != _DAT_7ffe9c9228b0)) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    thisObject_00 = (longlong *)0x0;
    if (bVar2) {
      thisObject_00 = (longlong *)action;
    }
  }
  cVar3 = FUN_7ffe9a8fec40(thisObject_00,0,0);
  if (cVar3 != '\0') {
    return 0;
  }
  lVar7 = (**(code **)(*(longlong *)thisObject + 0x298))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if ((action != (undefined *)0x0) &&
     (uVar5 = (**(code **)(*(longlong *)action + 0x298))
                        (action,*(undefined8 *)(*(longlong *)action + 0x2a0)), lVar7 != 0)) {
    cVar3 = FUN_7ffe9a4a1760(lVar7,uVar5);
    if (cVar3 != '\0') {
      return 0;
    }
    if (thisObject_00 != (longlong *)0x0) {
      iVar6 = (**(code **)(*thisObject_00 + 0x188))
                        (thisObject_00,*(undefined8 *)(*thisObject_00 + 400));
      if ((iVar6 == 0xe4) ||
         (iVar6 = (**(code **)(*thisObject_00 + 0x188))
                            (thisObject_00,*(undefined8 *)(*thisObject_00 + 400)), iVar6 == 0xed)) {
        plVar8 = (longlong *)
                 (**(code **)(*(longlong *)thisObject + 0x298))
                           (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
        if ((plVar8 == (longlong *)0x0) ||
           (lVar7 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0)),
           lVar7 == 0)) goto LAB_7ffe9a4514d2;
        cVar3 = FUN_7ffe9a7c6d00(lVar7,0x17);
        if ((cVar3 != '\0') && (*(int *)((longlong)thisObject_00 + 0x104) == 1)) {
          return 0;
        }
      }
      iVar6 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      if (iVar6 == 0x72) {
        plVar8 = (longlong *)
                 (**(code **)(*(longlong *)thisObject + 0x298))
                           (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
        if ((plVar8 == (longlong *)0x0) ||
           (puVar9 = (undefined *)
                     (**(code **)(*plVar8 + 0x218))(plVar8,*(undefined8 *)(*plVar8 + 0x220)),
           puVar9 == (undefined *)0x0)) goto LAB_7ffe9a4514d2;
        bVar4 = GemCartBufferManager_ContainsBuffer(puVar9,0x40f,(undefined *)0x0);
        if (bVar4 != 0) {
          return 0;
        }
      }
      if (*(longlong *)(thisObject + 0x118) != 0) {
        cVar3 = FUN_7ffe9a7efd70(*(longlong *)(thisObject + 0x118),0);
        if (cVar3 != '\0') {
          lVar7 = FUN_7ffe9a4565c0(thisObject,0);
          if (lVar7 == 0) goto LAB_7ffe9a4514d2;
          *(undefined1 *)(lVar7 + 0xb0) = 0;
        }
        puVar9 = (undefined *)
                 (**(code **)(*(longlong *)thisObject + 0x298))
                           (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
        bVar4 = PlayerAttackBase_CheckGemCartEmergencyMpRecovery
                          ((undefined *)thisObject_00,puVar9,(undefined *)0x0);
        if (bVar4 != 0) {
          *sendActionStart = 1;
        }
        uVar10 = (**(code **)(*(longlong *)thisObject + 0x298))
                           (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
        cVar3 = FUN_7ffe9a4ac630(thisObject_00,uVar10,0);
        if (cVar3 != '\0') {
          *sendActionStart = 1;
        }
        lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
        if (lVar7 != 0) {
          FUN_7ffe9a8a75a0(lVar7,0);
          lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
          if (lVar7 != 0) {
            FUN_7ffe99caacb0(lVar7,1);
            return 1;
          }
        }
      }
    }
  }
LAB_7ffe9a4514d2:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  bVar4 = (*pcVar1)();
  return bVar4;
}

