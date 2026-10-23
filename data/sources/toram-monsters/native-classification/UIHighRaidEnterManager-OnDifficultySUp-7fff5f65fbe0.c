
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UIHighRaidEnterManager_OnDifficultySUp(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  longlong *plVar2;
  code *pcVar3;
  char cVar4;
  undefined8 uVar5;
  bool bVar6;
  bool bVar7;
  bool bVar8;
  undefined2 auStackX_8 [4];
  
  *(short *)(self + 0x174) = *(short *)(self + 0x174) + 10;
  if (*(int *)(self + 0x194) < (int)*(short *)(self + 0x174)) {
    *(undefined2 *)(self + 0x174) = *(undefined2 *)(self + 0x194);
  }
  if (DAT_7fff625e1bc5 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62453138,0);
    FUN_7fff5f47d450(&DAT_7fff62425cc0);
    DAT_7fff625e1bc5 = '\x01';
  }
  lVar1 = *(longlong *)(self + 0x60);
  auStackX_8[0] = *(undefined2 *)(self + 0x174);
  uVar5 = func_0x7fff5f47c7a0(_DAT_7fff62453138,auStackX_8);
  uVar5 = FUN_7fff60e74b00(_DAT_7fff62425cc0,uVar5,0);
  if (lVar1 != 0) {
    FUN_7fff5ff0eed0(lVar1,uVar5,0);
    plVar2 = *(longlong **)(self + 0x148);
    if (plVar2 != (longlong *)0x0) {
      cVar4 = (**(code **)(*plVar2 + 0x198))(plVar2,*(undefined8 *)(*plVar2 + 0x1a0));
      lVar1 = *(longlong *)(self + 0x58);
      if (lVar1 != 0) {
        if (*(int *)(lVar1 + 0x18) == 0) {
          FUN_7fff5f47d650();
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
        bVar8 = false;
        bVar7 = false;
        bVar6 = bVar7;
        if (cVar4 != '\0') {
          bVar6 = *(int *)(self + 400) < (int)*(short *)(self + 0x174);
        }
        if (*(longlong *)(lVar1 + 0x20) != 0) {
          FUN_7fff618a4510(*(longlong *)(lVar1 + 0x20),bVar6,0);
          lVar1 = *(longlong *)(self + 0x58);
          if (lVar1 != 0) {
            if (*(uint *)(lVar1 + 0x18) < 2) {
LAB_7fff5f662f5e:
              FUN_7fff5f47d650();
              pcVar3 = (code *)swi(3);
              (*pcVar3)();
              return;
            }
            bVar6 = bVar7;
            if (cVar4 != '\0') {
              bVar6 = *(int *)(self + 400) < (int)*(short *)(self + 0x174);
            }
            if (*(longlong *)(lVar1 + 0x28) != 0) {
              FUN_7fff618a4510(*(longlong *)(lVar1 + 0x28),bVar6,0);
              lVar1 = *(longlong *)(self + 0x58);
              if (lVar1 != 0) {
                if (*(uint *)(lVar1 + 0x18) < 3) goto LAB_7fff5f662f5e;
                if (cVar4 != '\0') {
                  bVar7 = (int)*(short *)(self + 0x174) < *(int *)(self + 0x194);
                }
                if (*(longlong *)(lVar1 + 0x30) != 0) {
                  FUN_7fff618a4510(*(longlong *)(lVar1 + 0x30),bVar7,0);
                  lVar1 = *(longlong *)(self + 0x58);
                  if (lVar1 != 0) {
                    if (*(uint *)(lVar1 + 0x18) < 4) goto LAB_7fff5f662f5e;
                    if (cVar4 != '\0') {
                      bVar8 = (int)*(short *)(self + 0x174) < *(int *)(self + 0x194);
                    }
                    lVar1 = *(longlong *)(lVar1 + 0x38);
                    if (lVar1 != 0) {
                      if (_DAT_7fff625f0ed8 == (code *)0x0) {
                        _DAT_7fff625f0ed8 = (code *)FUN_7fff5f47d6c0(&UNK_7fff61c3c658,bVar8,0);
                      }
                    /* WARNING: Could not recover jumptable at 0x7fff618a454f. Too many branches */
                    /* WARNING: Treating indirect jump as call */
                      (*_DAT_7fff625f0ed8)(lVar1,bVar8);
                      return;
                    }
                  }
                }
              }
            }
          }
        }
        FUN_7fff5f47d660();
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
    }
  }
  FUN_7fff5f47d660();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

