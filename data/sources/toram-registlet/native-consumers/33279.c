
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void WarCryAction_ActionPreparation
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  int iVar4;
  undefined4 uVar5;
  longlong *plVar6;
  longlong lVar7;
  undefined *thisObject_00;
  undefined8 uVar8;
  
  if (DAT_7ffe9cadf914 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c9632c0);
    DAT_7ffe9cadf914 = '\x01';
  }
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(_DAT_7ffe9c922720 + 0x130) <= *(byte *)(*(longlong *)actarAction + 0x130)) &&
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) == _DAT_7ffe9c922720)) {
      plVar6 = (longlong *)
               (**(code **)(*(longlong *)actarAction + 0x298))
                         (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
      if (plVar6 != (longlong *)0x0) {
        lVar7 = (**(code **)(*plVar6 + 0x1e8))(plVar6,*(undefined8 *)(*plVar6 + 0x1f0));
        if (lVar7 != 0) {
          cVar2 = FUN_7ffe9a4daa60(lVar7,0xd);
          if (cVar2 != '\0') {
            plVar6 = (longlong *)
                     (**(code **)(*(longlong *)actarAction + 0x298))
                               (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
            if (plVar6 == (longlong *)0x0) goto LAB_7ffe9a846b05;
            thisObject_00 =
                 (undefined *)
                 (**(code **)(*plVar6 + 0x218))(plVar6,*(undefined8 *)(*plVar6 + 0x220));
            if (thisObject_00 == (undefined *)0x0) goto LAB_7ffe9a846b05;
            bVar3 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x3f9,(undefined *)0x0);
            if (bVar3 == 0) {
              cVar2 = FUN_7ffe9a8fea70(thisObject,100,0x1e);
              if (cVar2 != '\0') {
                *(uint *)(thisObject + 0x108) = *(uint *)(thisObject + 0x108) | 0x10;
              }
            }
          }
          plVar6 = (longlong *)
                   (**(code **)(*(longlong *)actarAction + 0x298))
                             (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
          if (plVar6 != (longlong *)0x0) {
            uVar8 = (**(code **)(*plVar6 + 0x1b8))(plVar6,*(undefined8 *)(*plVar6 + 0x1c0));
            if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            cVar2 = FUN_7ffe9bda2160(uVar8,0);
            if (cVar2 == '\0') goto LAB_7ffe9a846a7f;
            plVar6 = (longlong *)
                     (**(code **)(*(longlong *)actarAction + 0x298))
                               (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
            if (plVar6 != (longlong *)0x0) {
              lVar7 = (**(code **)(*plVar6 + 0x1b8))(plVar6,*(undefined8 *)(*plVar6 + 0x1c0));
              if (lVar7 != 0) {
                iVar4 = FUN_7ffe9a7fd580(lVar7,0x208,1,0);
                if (0 < iVar4) {
                  lVar7 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
                  if (lVar7 == 0) goto LAB_7ffe9a846b05;
                  cVar2 = FUN_7ffe9a33a880(lVar7,0);
                  if (cVar2 != '\0') {
                    *(uint *)(thisObject + 0x108) = *(uint *)(thisObject + 0x108) | 0x200;
                  }
                }
LAB_7ffe9a846a7f:
                cVar2 = func_0x7ffe9a4aea60(thisObject,0);
                if (cVar2 == '\0') {
                  iVar4 = (**(code **)(*(longlong *)thisObject + 0x188))
                                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
                  if (iVar4 != 0) {
                    cVar2 = func_0x7ffe9a4ad2e0(thisObject,0x400);
                    if (cVar2 == '\0') {
                      uVar5 = (**(code **)(*(longlong *)thisObject + 0x188))
                                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
                      cVar2 = func_0x7ffe9a4ad460(uVar5,0);
                      if (cVar2 == '\0') {
                        FUN_7ffe9a4a7480(thisObject,actarAction);
                        SkillActionBase_AddTemporarySkillBuffer
                                  (thisObject,actarAction,(undefined *)0x0);
                      }
                    }
                  }
                }
                return;
              }
            }
          }
        }
      }
    }
  }
LAB_7ffe9a846b05:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

