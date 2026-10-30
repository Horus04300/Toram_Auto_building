
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PhotonListener_OnEventTreasureHuntUpdateBonusEvent
               (undefined *self,undefined *game,undefined *bonusEvent,undefined *methodInfo)

{
  undefined8 uVar1;
  longlong lVar2;
  code *pcVar3;
  longlong lVar4;
  uint uVar5;
  
  if (bonusEvent != (undefined *)0x0) {
    game = *(undefined **)(bonusEvent + 0x30);
    if (game == (undefined *)0x0) {
      return;
    }
    lVar2 = *(longlong *)(self + 0x20);
    self = (undefined *)0x0;
    if (lVar2 != 0) {
      if (game != (undefined *)0x0) {
        for (uVar5 = 0; (int)uVar5 < (int)*(uint *)(game + 0x18); uVar5 = uVar5 + 1) {
          if (*(uint *)(game + 0x18) <= uVar5) {
            FUN_7ffe9996d790();
            pcVar3 = (code *)swi(3);
            (*pcVar3)();
            return;
          }
          lVar4 = *(longlong *)(lVar2 + 0x70);
          uVar1 = *(undefined8 *)(game + (longlong)(int)uVar5 * 8 + 0x20);
          if ((lVar4 == 0) || (lVar4 = FUN_7ffe9a47f190(lVar4,0), lVar4 == 0)) {
            FUN_7ffe9996d7a0();
            pcVar3 = (code *)swi(3);
            (*pcVar3)();
            return;
          }
          FUN_7ffe9a4e8aa0(lVar4,uVar1,0);
        }
      }
      return;
    }
  }
  FUN_7ffe9996d7a0(self,game);
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

