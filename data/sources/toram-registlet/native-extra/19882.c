
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MaximuyzerSwitchingBuff_ConverterMaximuyzerSwitching
              (int skillId,undefined *playerStatus,undefined *comboManager,
              undefined *skillActionManager,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  short sVar3;
  int iVar4;
  longlong lVar5;
  longlong *plVar6;
  longlong *plStackX_10;
  
  if (DAT_7ffe9cade7a6 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c95ef40);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    DAT_7ffe9cade7a6 = '\x01';
  }
  plStackX_10 = (longlong *)0x0;
  if ((playerStatus != (undefined *)0x0) &&
     (lVar5 = (**(code **)(*(longlong *)playerStatus + 0x218))
                        (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x220)),
     lVar5 != 0)) {
    if (DAT_7ffe9cade790 == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c965650);
      DAT_7ffe9cade790 = '\x01';
    }
    if (*(longlong *)(lVar5 + 0x18) != 0) {
      cVar2 = FUN_7ffe9ad11000(*(longlong *)(lVar5 + 0x18),0x194,_DAT_7ffe9c965650);
      if (cVar2 == '\0') {
        return skillId;
      }
      if (comboManager != (undefined *)0x0) {
        cVar2 = FUN_7ffe9a7ee490(comboManager,0x6e);
        if (cVar2 != '\0') {
          return skillId;
        }
        cVar2 = FUN_7ffe9a7efd70(comboManager,0);
        if (((cVar2 != '\0') && (*(longlong *)(comboManager + 0x28) != 0)) &&
           (sVar3 = FUN_7ffe9a7f21f0(*(longlong *)(comboManager + 0x28),0), sVar3 == 0x6e)) {
          return skillId;
        }
        lVar5 = (**(code **)(*(longlong *)playerStatus + 0x1c8))
                          (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x1d0));
        if (lVar5 != 0) {
          cVar2 = FUN_7ffe9a7c6d00(lVar5,0x65);
          if (cVar2 != '\0') {
            return skillId;
          }
          lVar5 = (**(code **)(*(longlong *)playerStatus + 0x1c8))
                            (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x1d0));
          if (lVar5 != 0) {
            cVar2 = FUN_7ffe9a7cbb30(lVar5,0x74,&plStackX_10);
            if (cVar2 != '\0') {
              if (plStackX_10 == (longlong *)0x0) goto LAB_7ffe9a5b5354;
              if (((*(byte *)(*plStackX_10 + 0x130) < *(byte *)(_DAT_7ffe9c95ef40 + 0x130)) ||
                  (*(longlong *)
                    (*(longlong *)(*plStackX_10 + 200) + -8 +
                    (ulonglong)*(byte *)(_DAT_7ffe9c95ef40 + 0x130) * 8) != _DAT_7ffe9c95ef40)) ||
                 (plStackX_10 == (longlong *)0x0)) {
                FUN_7ffe9996c950(plStackX_10);
                pcVar1 = (code *)swi(3);
                iVar4 = (*pcVar1)();
                return iVar4;
              }
              if (*(char *)((longlong)plStackX_10 + 0x61) != '\0') {
                return skillId;
              }
            }
            lVar5 = (**(code **)(*(longlong *)playerStatus + 0x1b8))
                              (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x1c0));
            if (lVar5 != 0) {
              iVar4 = FUN_7ffe9a7fd580(lVar5,0x65,1);
              if (iVar4 < 1) {
                return skillId;
              }
              if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                func_0x7ffe9996d830();
              }
              cVar2 = FUN_7ffe9bda2160(skillActionManager,0,0);
              if (cVar2 != '\0') {
                if (skillActionManager == (undefined *)0x0) goto LAB_7ffe9a5b5354;
                plVar6 = (longlong *)
                         (**(code **)(*(longlong *)skillActionManager + 0x188))
                                   (skillActionManager,
                                    *(undefined8 *)(*(longlong *)skillActionManager + 400));
                cVar2 = FUN_7ffe9a8fecd0(plVar6,0,0);
                if (cVar2 != '\0') {
                  if (plVar6 == (longlong *)0x0) goto LAB_7ffe9a5b5354;
                  iVar4 = (**(code **)(*plVar6 + 0x188))(plVar6,*(undefined8 *)(*plVar6 + 400));
                  if (iVar4 == 0x6e) {
                    return skillId;
                  }
                  if ((skillId == 0x6e) &&
                     (iVar4 = (**(code **)(*plVar6 + 0x188))(plVar6,*(undefined8 *)(*plVar6 + 400)),
                     iVar4 == 0x65)) {
                    return 0x6e;
                  }
                }
              }
              return 0x65;
            }
          }
        }
      }
    }
  }
LAB_7ffe9a5b5354:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  iVar4 = (*pcVar1)();
  return iVar4;
}

