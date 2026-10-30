
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SonicThrustAction_ActionStart
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  code *pcVar1;
  byte bVar2;
  undefined4 uVar3;
  longlong *plVar4;
  undefined *thisObject_00;
  undefined8 uVar5;
  
  if (DAT_7ffe9cadee1c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadee1c = '\x01';
  }
  FUN_7ffe9a4a6970(thisObject,actarAction,target,0);
  *(undefined4 *)(thisObject + 0x78) = 0x32;
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(_DAT_7ffe9c922720 + 0x130) <= *(byte *)(*(longlong *)actarAction + 0x130)) &&
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) == _DAT_7ffe9c922720)) {
      plVar4 = (longlong *)
               (**(code **)(*(longlong *)actarAction + 0x298))
                         (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
      if (plVar4 != (longlong *)0x0) {
        thisObject_00 =
             (undefined *)(**(code **)(*plVar4 + 0x218))(plVar4,*(undefined8 *)(*plVar4 + 0x220));
        if (thisObject_00 != (undefined *)0x0) {
          bVar2 = GemCartBufferManager_ContainsBuffer(thisObject_00,0xd9,(undefined *)0x0);
          if (bVar2 != 0) {
            uVar5 = (**(code **)(*(longlong *)actarAction + 0x298))
                              (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
            uVar3 = FUN_7ffe9a4aabb0(uVar5,0);
            *(undefined4 *)(thisObject + 0x78) = uVar3;
          }
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

