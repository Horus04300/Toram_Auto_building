
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PhotonListener_OnEventTreasureHuntTestGameEnd
               (undefined *self,undefined *game,undefined *endEvent,undefined *methodInfo)

{
  longlong *self_00;
  code *pcVar1;
  longlong lVar2;
  undefined *puVar3;
  
  if (DAT_7ffe9cae0b3b == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c955480);
    FUN_7ffe9996d590(&DAT_7ffe9c96c9c0);
    DAT_7ffe9cae0b3b = '\x01';
  }
  lVar2 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
  if (lVar2 == 0) {
LAB_7ffe9aaae22e:
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  self_00 = *(longlong **)(lVar2 + 0x28);
  if (self_00 != (longlong *)0x0) {
    if ((*(byte *)(_DAT_7ffe9c96c9c0 + 0x130) <= *(byte *)(*self_00 + 0x130)) &&
       (*(longlong *)
         (*(longlong *)(*self_00 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c96c9c0 + 0x130) * 8)
        == _DAT_7ffe9c96c9c0)) {
      puVar3 = TreasureHuntRoomData_get_TreasureHuntPanelManager
                         ((undefined *)self_00,(undefined *)0x0);
      if ((puVar3 != (undefined *)0x0) &&
         (func_0x7ffe9a4d6650(puVar3,endEvent,0), endEvent != (undefined *)0x0)) {
        FUN_7ffe9a625140(self_00,endEvent[0x20],*(undefined2 *)(endEvent + 0x22),0,0);
        puVar3 = TreasureHuntRoomData_get_TreasureHuntPanelManager
                           ((undefined *)self_00,(undefined *)0x0);
        if (puVar3 != (undefined *)0x0) {
          FUN_7ffe9a4d6540(puVar3,0);
          return;
        }
      }
      goto LAB_7ffe9aaae22e;
    }
  }
  return;
}

