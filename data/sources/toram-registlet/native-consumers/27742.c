
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MeteorStrikeAction_ActionPreparation
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  undefined4 uVar6;
  longlong *plVar7;
  longlong lVar8;
  longlong *plVar9;
  undefined *thisObject_00;
  
  if (DAT_7ffe9cadf34a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadf34a = '\x01';
  }
  if (actarAction == (undefined *)0x0) {
    func_0x7ffe9a4ad2e0(thisObject,0x100,0);
  }
  else {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    plVar9 = (longlong *)0x0;
    if (bVar2) {
      plVar9 = (longlong *)actarAction;
    }
    cVar3 = func_0x7ffe9a4ad2e0(thisObject,0x100,0);
    if (plVar9 != (longlong *)0x0) {
      if (cVar3 == '\0') {
        plVar7 = (longlong *)(**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0))
        ;
        if (plVar7 == (longlong *)0x0) goto LAB_7ffe9a7719e4;
        lVar8 = (**(code **)(*plVar7 + 0x1e8))(plVar7,*(undefined8 *)(*plVar7 + 0x1f0));
        if (lVar8 == 0) goto LAB_7ffe9a7719e4;
        cVar3 = FUN_7ffe9a4daa60(lVar8,0xd);
        if (cVar3 != '\0') {
          cVar3 = FUN_7ffe9a8fea70(thisObject,100);
          if (cVar3 != '\0') {
            *(uint *)(thisObject + 0x108) = *(uint *)(thisObject + 0x108) | 0x10;
          }
        }
        cVar3 = func_0x7ffe9a4aea60(thisObject,0);
        if (cVar3 == '\0') {
          iVar5 = (**(code **)(*(longlong *)thisObject + 0x188))
                            (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
          if (iVar5 != 0) {
            uVar6 = (**(code **)(*(longlong *)thisObject + 0x188))
                              (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
            cVar3 = func_0x7ffe9a4ad460(uVar6,0);
            if (cVar3 == '\0') {
              FUN_7ffe9a4a7480(thisObject,plVar9);
              SkillActionBase_AddTemporarySkillBuffer
                        (thisObject,(undefined *)plVar9,(undefined *)0x0);
            }
          }
        }
      }
      plVar9 = (longlong *)(**(code **)(*plVar9 + 0x298))(plVar9,*(undefined8 *)(*plVar9 + 0x2a0));
      if (plVar9 != (longlong *)0x0) {
        thisObject_00 =
             (undefined *)(**(code **)(*plVar9 + 0x218))(plVar9,*(undefined8 *)(*plVar9 + 0x220));
        if (thisObject_00 != (undefined *)0x0) {
          bVar4 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x3fe,(undefined *)0x0);
          thisObject[0x18c] = bVar4;
          return;
        }
      }
    }
  }
LAB_7ffe9a7719e4:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

