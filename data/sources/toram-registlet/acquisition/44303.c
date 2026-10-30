
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PhotonListener_OnEventTreasureHuntMoveMob
               (undefined *self,undefined *game,undefined *moveEvent,undefined *methodInfo)

{
  longlong lVar1;
  longlong lVar2;
  code *pcVar3;
  ulonglong uVar4;
  uint uVar5;
  
  if (DAT_7ffe9cae0b38 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9632c0);
    DAT_7ffe9cae0b38 = '\x01';
  }
  if (moveEvent != (undefined *)0x0) {
    if (*(longlong *)(moveEvent + 0x20) == 0) {
      return;
    }
    uVar4 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
    if (uVar4 != 0) {
      lVar2 = *(longlong *)(moveEvent + 0x20);
      lVar1 = *(longlong *)(uVar4 + 0x48);
      if ((lVar1 != 0) && (uVar4 = 0, lVar2 != 0)) {
        while( true ) {
          uVar5 = (uint)uVar4;
          if ((int)*(uint *)(lVar2 + 0x18) <= (int)uVar5) {
            return;
          }
          if (*(uint *)(lVar2 + 0x18) <= uVar5) break;
          FUN_7ffe9a3531a0(lVar1,*(undefined8 *)(lVar2 + 0x20 + (longlong)(int)uVar5 * 8),0,0);
          uVar4 = (ulonglong)(uVar5 + 1);
        }
        FUN_7ffe9996d790();
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
      FUN_7ffe9996d7a0(uVar4,lVar2,0);
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

