
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PhotonListener_OnEventTreasureHuntGameEnd
               (undefined *self,undefined *game,undefined *endEvent,undefined *methodInfo)

{
  longlong *self_00;
  longlong lVar1;
  code *pcVar2;
  longlong lVar3;
  undefined *puVar4;
  uint uVar5;
  
  if (DAT_7ffe9cae0b3a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c955480);
    FUN_7ffe9996d590(&DAT_7ffe9c96c9c0);
    DAT_7ffe9cae0b3a = '\x01';
  }
  lVar3 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
  if (lVar3 == 0) {
LAB_7ffe9aaade73:
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
  self_00 = *(longlong **)(lVar3 + 0x28);
  if (self_00 != (longlong *)0x0) {
    if ((*(byte *)(_DAT_7ffe9c96c9c0 + 0x130) <= *(byte *)(*self_00 + 0x130)) &&
       (*(longlong *)
         (*(longlong *)(*self_00 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c96c9c0 + 0x130) * 8)
        == _DAT_7ffe9c96c9c0)) {
      puVar4 = TreasureHuntRoomData_get_TreasureHuntPanelManager
                         ((undefined *)self_00,(undefined *)0x0);
      if ((puVar4 != (undefined *)0x0) &&
         (func_0x7ffe9a4d6640(puVar4,endEvent,0), endEvent != (undefined *)0x0)) {
        uVar5 = 0;
        FUN_7ffe9a625140(self_00,endEvent[0x20],*(undefined2 *)(endEvent + 0x22),endEvent[0x40],0);
        lVar3 = *(longlong *)(endEvent + 0x38);
        if (lVar3 != 0) {
          for (; (int)uVar5 < *(int *)(lVar3 + 0x18); uVar5 = uVar5 + 1) {
            if (*(uint *)(lVar3 + 0x18) <= uVar5) {
              FUN_7ffe9996d790();
              pcVar2 = (code *)swi(3);
              (*pcVar2)();
              return;
            }
            lVar1 = *(longlong *)(lVar3 + 0x20 + (longlong)(int)uVar5 * 8);
            if ((lVar1 == 0) || (*(longlong *)(self + 0x20) == 0)) goto LAB_7ffe9aaade73;
            FUN_7ffe9a8d4e70(*(longlong *)(self + 0x20),*(undefined8 *)(lVar1 + 0x28),0);
          }
        }
        puVar4 = TreasureHuntRoomData_get_TreasureHuntPanelManager
                           ((undefined *)self_00,(undefined *)0x0);
        if (puVar4 != (undefined *)0x0) {
          FUN_7ffe9a4d6540(puVar4,0);
          return;
        }
      }
      goto LAB_7ffe9aaade73;
    }
  }
  return;
}

