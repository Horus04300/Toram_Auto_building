
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PhotonListener_OnEventEnterGuildRaidField
               (undefined *self,undefined *game,undefined *enterEvent,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  undefined1 uVar3;
  undefined1 uVar4;
  longlong lVar5;
  longlong *plVar6;
  undefined *self_00;
  undefined8 uVar7;
  longlong lVar8;
  longlong lVar9;
  ulonglong in_stack_ffffffffffffffc8;
  int aiStack_28 [4];
  
  if (DAT_7ffe9cae0a0c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9240a0);
    FUN_7ffe9996d590(&DAT_7ffe9c94ba38);
    FUN_7ffe9996d590(&DAT_7ffe9c91b0b8);
    FUN_7ffe9996d590(&DAT_7ffe9c9394a0);
    FUN_7ffe9996d590(&DAT_7ffe9c955480);
    FUN_7ffe9996d590(&DAT_7ffe9c9632c0);
    DAT_7ffe9cae0a0c = '\x01';
  }
  lVar5 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
  if (lVar5 != 0) {
    plVar6 = *(longlong **)(lVar5 + 0x28);
    if (plVar6 != (longlong *)0x0) {
      if ((*(byte *)(_DAT_7ffe9c9240a0 + 0x130) <= *(byte *)(*plVar6 + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(*plVar6 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c9240a0 + 0x130) * 8)
          == _DAT_7ffe9c9240a0)) goto LAB_7ffe9aaa24c4;
    }
    plVar6 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c9240a0);
    FUN_7ffe9a5d6e90(plVar6,0);
    lVar5 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
    if (lVar5 != 0) {
      *(longlong **)(lVar5 + 0x28) = plVar6;
      il2cpp_write_barrier_0();
LAB_7ffe9aaa24c4:
      if (((enterEvent != (undefined *)0x0) && (*(longlong *)(enterEvent + 0x28) != 0)) &&
         (plVar6 != (longlong *)0x0)) {
        GuildRaidRoomData_SetGuildRaidLevel
                  ((undefined *)plVar6,*(short *)(*(longlong *)(enterEvent + 0x28) + 0x20),
                   (undefined *)0x0);
        func_0x7ffe9a5d6840(plVar6,enterEvent[0x48]);
        GuildRaidRoomData_SetCurrentHpCount((undefined *)plVar6,enterEvent[0x49],(undefined *)0x0);
        plVar6[0xe] = *(longlong *)(enterEvent + 0x40);
        il2cpp_write_barrier_0();
        self_00 = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c955480);
        if (self_00 != (undefined *)0x0) {
          UITrophyButton_set_TrophyId(self_00,*(int *)(enterEvent + 0x20),(undefined *)0x0);
          lVar5 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
          if (*(longlong *)(enterEvent + 0x28) != 0) {
            cVar2 = func_0x7ffe9bc90b40(*(longlong *)(enterEvent + 0x28),0);
            if (*(longlong *)(enterEvent + 0x28) != 0) {
              uVar3 = func_0x7ffe9bc90b40(*(longlong *)(enterEvent + 0x28),0);
              if (*(longlong *)(enterEvent + 0x28) != 0) {
                uVar4 = func_0x7ffe9bc90b50(*(longlong *)(enterEvent + 0x28),0);
                uVar7 = func_0x7ffe99940040(_DAT_7ffe9c9394a0);
                FUN_7ffe9bc91cc0(uVar7,cVar2 == '\0',uVar3,uVar4,
                                 in_stack_ffffffffffffffc8 & 0xffffffffffff0000,0);
                if (*(longlong *)(enterEvent + 0x28) != 0) {
                  uVar3 = func_0x7ffe9bc90b60(*(longlong *)(enterEvent + 0x28),0);
                  if (lVar5 != 0) {
                    FUN_7ffe9a604450(lVar5,uVar7,uVar3,0);
                    lVar8 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
                    lVar5 = *(longlong *)(enterEvent + 0x30);
                    uVar7 = *(undefined8 *)(enterEvent + 0x38);
                    if (lVar5 != 0) {
                      uVar3 = *(undefined1 *)(lVar5 + 0x26);
                      uVar4 = *(undefined1 *)(lVar5 + 0x25);
                      plVar6 = (longlong *)func_0x7ffe9996c990(_DAT_7ffe9c91b0b8,1);
                      if (*(longlong *)(enterEvent + 0x28) != 0) {
                        aiStack_28[0] = (int)*(short *)(*(longlong *)(enterEvent + 0x28) + 0x20);
                        lVar5 = func_0x7ffe9996c8e0(_DAT_7ffe9c94ba38,aiStack_28);
                        if (plVar6 != (longlong *)0x0) {
                          if (lVar5 != 0) {
                            lVar9 = func_0x7ffe9996c920(lVar5,*(undefined8 *)(*plVar6 + 0x40));
                            if (lVar9 == 0) {
                              uVar7 = func_0x7ffe9996d1f0();
                              FUN_7ffe9996d760(uVar7,0);
                              pcVar1 = (code *)swi(3);
                              (*pcVar1)();
                              return;
                            }
                          }
                          if ((int)plVar6[3] == 0) {
                            FUN_7ffe9996d790();
                            pcVar1 = (code *)swi(3);
                            (*pcVar1)();
                            return;
                          }
                          plVar6[4] = lVar5;
                          il2cpp_write_barrier_0();
                          if (lVar8 != 0) {
                            FUN_7ffe9a337e40(lVar8,uVar7,uVar3,uVar4,plVar6,0);
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
      FUN_7ffe9996d7a0();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

