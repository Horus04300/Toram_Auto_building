
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PlayerBattleManager_StartMagicFinawPursuitAttack
               (undefined *thisObject,undefined *targetActionManager,undefined *action,
               undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  uint uVar4;
  longlong *plVar5;
  undefined *puVar6;
  undefined8 uVar7;
  longlong *plVar8;
  
  if (DAT_7ffe9caddd20 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92bc40);
    FUN_7ffe9996d590(&DAT_7ffe9c95e4e0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c923530);
    DAT_7ffe9caddd20 = '\x01';
  }
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar3 = FUN_7ffe9bda1fa0(targetActionManager,0,0);
  if (cVar3 == '\0') {
    if (targetActionManager == (undefined *)0x0) goto LAB_7ffe9a46f787;
    cVar3 = FUN_7ffe99b1ccd0(targetActionManager,0);
    if ((cVar3 == '\0') && (action != (undefined *)0x0)) {
      if ((*(byte *)(_DAT_7ffe9c92bc40 + 0x130) <= *(byte *)(*(longlong *)action + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(*(longlong *)action + 200) + -8 +
           (ulonglong)*(byte *)(_DAT_7ffe9c92bc40 + 0x130) * 8) == _DAT_7ffe9c92bc40)) {
        plVar5 = *(longlong **)(thisObject + 0x88);
        if (((plVar5 == (longlong *)0x0) ||
            (plVar5 = (longlong *)
                      (**(code **)(*plVar5 + 0x298))(plVar5,*(undefined8 *)(*plVar5 + 0x2a0)),
            plVar5 == (longlong *)0x0)) ||
           (puVar6 = (undefined *)
                     (**(code **)(*plVar5 + 0x218))(plVar5,*(undefined8 *)(*plVar5 + 0x220)),
           puVar6 == (undefined *)0x0)) goto LAB_7ffe9a46f787;
        puVar6 = GemCartBufferManager_GetGemCartBuffer(puVar6,0x3ed,(undefined *)0x0);
        if ((puVar6 != (undefined *)0x0) && (cVar3 = FUN_7ffe99a4d1d0(1), cVar3 != '\0')) {
          plVar5 = (longlong *)FUN_7ffe9a7f64f0(0x15);
          if (plVar5 == (longlong *)0x0) {
            plVar8 = (longlong *)0x0;
          }
          else {
            if ((*(byte *)(*plVar5 + 0x130) < *(byte *)(_DAT_7ffe9c95e4e0 + 0x130)) ||
               (*(longlong *)
                 (*(longlong *)(*plVar5 + 200) + -8 +
                 (ulonglong)*(byte *)(_DAT_7ffe9c95e4e0 + 0x130) * 8) != _DAT_7ffe9c95e4e0)) {
              bVar2 = false;
            }
            else {
              bVar2 = true;
            }
            plVar8 = (longlong *)0x0;
            if (bVar2) {
              plVar8 = plVar5;
            }
          }
          cVar3 = FUN_7ffe9a8fec40(plVar8,0);
          if (cVar3 == '\0') {
            uVar4 = GemCartBufferBase_GetValue(puVar6,(undefined *)0x2,(undefined *)0x0);
            if (plVar8 == (longlong *)0x0) {
LAB_7ffe9a46f787:
              FUN_7ffe9996d7a0();
              pcVar1 = (code *)swi(3);
              (*pcVar1)();
              return;
            }
            FUN_7ffe9a8fe290(plVar8,*(undefined8 *)(thisObject + 0x28),uVar4 & 0xff,0);
            uVar7 = FUN_7ffe9bd98960(targetActionManager,0);
            cVar3 = FUN_7ffe9974e380(0x1c,thisObject,uVar7,targetActionManager,plVar8);
            if (cVar3 != '\0') {
              plVar5 = *(longlong **)(thisObject + 0x30);
              uVar7 = FUN_7ffe9bd98960(targetActionManager,0);
              if (plVar5 == (longlong *)0x0) goto LAB_7ffe9a46f787;
              if ((*(byte *)(*plVar5 + 0x130) < *(byte *)(_DAT_7ffe9c923530 + 0x130)) ||
                 (*(longlong *)
                   (*(longlong *)(*plVar5 + 200) + -8 +
                   (ulonglong)*(byte *)(_DAT_7ffe9c923530 + 0x130) * 8) != _DAT_7ffe9c923530)) {
                FUN_7ffe9996c950(plVar5,_DAT_7ffe9c923530);
                pcVar1 = (code *)swi(3);
                (*pcVar1)();
                return;
              }
              FUN_7ffe9a49fd00(plVar5,uVar7,plVar8,0);
            }
          }
        }
      }
    }
  }
  return;
}

