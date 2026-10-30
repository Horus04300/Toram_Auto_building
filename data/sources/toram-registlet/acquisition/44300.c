
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PhotonListener_OnEventTreasureHuntEnterGame
               (undefined *self,undefined *game,undefined *enterEvent,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  longlong lVar5;
  longlong *self_00;
  undefined8 uVar6;
  longlong lVar7;
  undefined8 uVar8;
  undefined *puVar9;
  ulonglong in_stack_ffffffffffffffc8;
  
  if (DAT_7ffe9cae0b35 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c90ad30);
    FUN_7ffe9996d590(&DAT_7ffe9c9394a0);
    FUN_7ffe9996d590(&DAT_7ffe9c956608);
    FUN_7ffe9996d590(&DAT_7ffe9c955480);
    FUN_7ffe9996d590(&DAT_7ffe9c9632c0);
    FUN_7ffe9996d590(&DAT_7ffe9c96c9c0);
    DAT_7ffe9cae0b35 = '\x01';
  }
  lVar5 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
  if (lVar5 == 0) goto LAB_7ffe9aaadd21;
  self_00 = *(longlong **)(lVar5 + 0x28);
  if (self_00 == (longlong *)0x0) {
LAB_7ffe9aaadb29:
    self_00 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c96c9c0);
    FUN_7ffe9a628390(self_00,0);
    lVar5 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
    if (lVar5 == 0) goto LAB_7ffe9aaadd21;
    *(longlong **)(lVar5 + 0x28) = self_00;
    il2cpp_write_barrier_0();
  }
  else if ((*(byte *)(*self_00 + 0x130) < *(byte *)(_DAT_7ffe9c96c9c0 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*self_00 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7ffe9c96c9c0 + 0x130) * 8) != _DAT_7ffe9c96c9c0))
  goto LAB_7ffe9aaadb29;
  if (enterEvent != (undefined *)0x0) {
    if (enterEvent[0x4c] != '\0') {
      return;
    }
    if (self_00 != (longlong *)0x0) {
      TreasureHuntRoomData_SettingLoginRoomData
                ((undefined *)self_00,*(undefined **)(enterEvent + 0x30),(undefined *)0x0);
      lVar5 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
      if (*(longlong *)(enterEvent + 0x20) != 0) {
        cVar2 = func_0x7ffe9bc90b40(*(longlong *)(enterEvent + 0x20),0);
        if (*(longlong *)(enterEvent + 0x20) != 0) {
          uVar3 = func_0x7ffe9bc90b40(*(longlong *)(enterEvent + 0x20),0);
          if (*(longlong *)(enterEvent + 0x20) != 0) {
            uVar4 = func_0x7ffe9bc90b50(*(longlong *)(enterEvent + 0x20),0);
            uVar6 = func_0x7ffe99940040(_DAT_7ffe9c9394a0);
            FUN_7ffe9bc91cc0(uVar6,cVar2 == '\0',uVar3,uVar4,
                             in_stack_ffffffffffffffc8 & 0xffffffffffff0000,0);
            if ((*(longlong *)(enterEvent + 0x20) != 0) &&
               (uVar3 = func_0x7ffe9bc90b60(*(longlong *)(enterEvent + 0x20),0), lVar5 != 0)) {
              FUN_7ffe9a604450(lVar5,uVar6,uVar3,0);
              lVar7 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
              lVar5 = *(longlong *)(enterEvent + 0x28);
              uVar6 = *(undefined8 *)(enterEvent + 0x38);
              if (lVar5 != 0) {
                uVar3 = *(undefined1 *)(lVar5 + 0x26);
                uVar4 = *(undefined1 *)(lVar5 + 0x25);
                uVar8 = FUN_7ffe997442c0(_DAT_7ffe9c90ad30);
                if (lVar7 != 0) {
                  FUN_7ffe9a337e40(lVar7,uVar6,uVar3,uVar4,uVar8,0);
                  puVar9 = TreasureHuntRoomData_get_TreasureHuntPanelManager
                                     ((undefined *)self_00,(undefined *)0x0);
                  if (puVar9 != (undefined *)0x0) {
                    FUN_7ffe9a4d61d0(puVar9,*(undefined4 *)(enterEvent + 0x48),0);
                    lVar5 = FUN_7ffe9b141840(_DAT_7ffe9c956608);
                    if (lVar5 != 0) {
                      FUN_7ffe9a85b9d0(lVar5,0);
                      lVar5 = FUN_7ffe9b141840(_DAT_7ffe9c956608);
                      if (lVar5 != 0) {
                        FUN_7ffe9a85a8f0(lVar5,*(undefined8 *)(enterEvent + 0x40),0);
                        return;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
LAB_7ffe9aaadd21:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

