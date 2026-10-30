
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ShadowWalkAttackAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  byte bVar3;
  undefined4 uVar4;
  longlong lVar5;
  longlong *plVar6;
  undefined *thisObject_00;
  
  if (DAT_7ffe9cadeb23 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadeb23 = '\x01';
  }
  if (actarAction == (undefined *)0x0) {
    plVar6 = (longlong *)0x0;
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
    plVar6 = (longlong *)0x0;
    if (bVar2) {
      plVar6 = (longlong *)actarAction;
    }
  }
  uVar4 = FUN_7ffe9a4adfc0(plVar6,thisObject + 0x138,0);
  *(undefined4 *)(thisObject + 0xfc) = uVar4;
  uVar4 = FUN_7ffe9a4adf80(*(undefined8 *)(thisObject + 0x138),0);
  *(undefined4 *)(thisObject + 0x140) = uVar4;
  uVar4 = FUN_7ffe9a4add40(plVar6,thisObject + 0x138,0);
  *(undefined4 *)(thisObject + 0xfc) = uVar4;
  *(undefined4 *)(thisObject + 0x20) = 0xbf800000;
  if (plVar6 != (longlong *)0x0) {
    lVar5 = (**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0));
    if (lVar5 != 0) {
      uVar4 = FUN_7ffe9a4a1cc0(lVar5,0);
      *(undefined4 *)(thisObject + 0x30) = uVar4;
      plVar6 = (longlong *)(**(code **)(*plVar6 + 0x298))(plVar6,*(undefined8 *)(*plVar6 + 0x2a0));
      if (plVar6 != (longlong *)0x0) {
        thisObject_00 =
             (undefined *)(**(code **)(*plVar6 + 0x218))(plVar6,*(undefined8 *)(*plVar6 + 0x220));
        if (thisObject_00 != (undefined *)0x0) {
          bVar3 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x400,(undefined *)0x0);
          thisObject[0x144] = bVar3 == 0;
          return;
        }
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

