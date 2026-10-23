
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
  undefined8 uVar7;
  longlong lVar8;
  longlong lVar9;
  ulonglong in_stack_ffffffffffffffc8;
  int aiStack_28 [4];
  
  if (DAT_7fff625e8162 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6242ba48);
    FUN_7fff5f47d450(&DAT_7fff624532c0);
    FUN_7fff5f47d450(&DAT_7fff62422c48);
    FUN_7fff5f47d450(&DAT_7fff62440c60);
    FUN_7fff5f47d450(&DAT_7fff6245c360);
    FUN_7fff5f47d450(&DAT_7fff6246a1a8);
    DAT_7fff625e8162 = '\x01';
  }
  lVar5 = FUN_7fff60c4bc00(_DAT_7fff6245c360);
  if (lVar5 != 0) {
    plVar6 = *(longlong **)(lVar5 + 0x28);
    if (plVar6 != (longlong *)0x0) {
      if ((*(byte *)(_DAT_7fff6242ba48 + 0x130) <= *(byte *)(*plVar6 + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(*plVar6 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7fff6242ba48 + 0x130) * 8)
          == _DAT_7fff6242ba48)) goto LAB_7fff605ac8b4;
    }
    plVar6 = (longlong *)func_0x7fff5f44ff00(_DAT_7fff6242ba48);
    FUN_7fff600e1320(plVar6,0);
    lVar5 = FUN_7fff60c4bc00(_DAT_7fff6245c360);
    if (lVar5 != 0) {
      *(longlong **)(lVar5 + 0x28) = plVar6;
      thunk_FUN_7fff5f491fd0();
LAB_7fff605ac8b4:
      if (((enterEvent != (undefined *)0x0) && (*(longlong *)(enterEvent + 0x28) != 0)) &&
         (plVar6 != (longlong *)0x0)) {
        GuildRaidRoomData_SetGuildRaidLevel
                  ((undefined *)plVar6,*(short *)(*(longlong *)(enterEvent + 0x28) + 0x20),
                   (undefined *)0x0);
        func_0x7fff600e0cd0(plVar6,enterEvent[0x48],0);
        func_0x7fff600e0ca0(plVar6,enterEvent[0x49],0);
        plVar6[0xe] = *(longlong *)(enterEvent + 0x40);
        thunk_FUN_7fff5f491fd0();
        lVar5 = FUN_7fff60c4bc00(_DAT_7fff6245c360);
        if (lVar5 != 0) {
          func_0x7fff5f5974c0(lVar5,*(undefined4 *)(enterEvent + 0x20),0);
          lVar5 = FUN_7fff60c4bc00(_DAT_7fff6245c360);
          if (*(longlong *)(enterEvent + 0x28) != 0) {
            cVar2 = func_0x7fff6179bf10(*(longlong *)(enterEvent + 0x28),0);
            if (*(longlong *)(enterEvent + 0x28) != 0) {
              uVar3 = func_0x7fff6179bf10(*(longlong *)(enterEvent + 0x28),0);
              if (*(longlong *)(enterEvent + 0x28) != 0) {
                uVar4 = func_0x7fff6179bf20(*(longlong *)(enterEvent + 0x28),0);
                uVar7 = func_0x7fff5f44ff00(_DAT_7fff62440c60);
                FUN_7fff6179d090(uVar7,cVar2 == '\0',uVar3,uVar4,
                                 in_stack_ffffffffffffffc8 & 0xffffffffffff0000,0);
                if (*(longlong *)(enterEvent + 0x28) != 0) {
                  uVar3 = func_0x7fff6179bf30(*(longlong *)(enterEvent + 0x28),0);
                  if (lVar5 != 0) {
                    FUN_7fff6010e8e0(lVar5,uVar7,uVar3,0);
                    lVar8 = FUN_7fff60c66630(_DAT_7fff6246a1a8);
                    lVar5 = *(longlong *)(enterEvent + 0x30);
                    uVar7 = *(undefined8 *)(enterEvent + 0x38);
                    if (lVar5 != 0) {
                      uVar3 = *(undefined1 *)(lVar5 + 0x26);
                      uVar4 = *(undefined1 *)(lVar5 + 0x25);
                      plVar6 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
                      if (*(longlong *)(enterEvent + 0x28) != 0) {
                        aiStack_28[0] = (int)*(short *)(*(longlong *)(enterEvent + 0x28) + 0x20);
                        lVar5 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,aiStack_28);
                        if (plVar6 != (longlong *)0x0) {
                          if (lVar5 != 0) {
                            lVar9 = func_0x7fff5f47c7e0(lVar5,*(undefined8 *)(*plVar6 + 0x40));
                            if (lVar9 == 0) {
                              uVar7 = func_0x7fff5f47d0b0();
                              FUN_7fff5f47d620(uVar7,0);
                              pcVar1 = (code *)swi(3);
                              (*pcVar1)();
                              return;
                            }
                          }
                          if ((int)plVar6[3] == 0) {
                            FUN_7fff5f47d650();
                            pcVar1 = (code *)swi(3);
                            (*pcVar1)();
                            return;
                          }
                          plVar6[4] = lVar5;
                          thunk_FUN_7fff5f491fd0();
                          if (lVar8 != 0) {
                            FUN_7fff5fe42b10(lVar8,uVar7,uVar3,uVar4,plVar6,0);
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
      FUN_7fff5f47d660();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

