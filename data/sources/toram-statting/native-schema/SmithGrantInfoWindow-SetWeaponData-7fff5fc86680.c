
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithGrantInfoWindow_SetWeaponData
               (undefined *self,int itemId,undefined *name,int potential,int grantnum,
               byte buttonEnabled,undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  longlong *plVar3;
  longlong lVar4;
  longlong lVar5;
  longlong lVar6;
  undefined8 uVar7;
  byte bVar8;
  int aiStackX_8 [2];
  
  if (DAT_7fff625e4257 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6244b618);
    FUN_7fff5f47d450(&DAT_7fff624532c0);
    FUN_7fff5f47d450(&DAT_7fff62422c48);
    DAT_7fff625e4257 = '\x01';
  }
  if (*(longlong *)(self + 0x28) != 0) {
    FUN_7fff5ff0eed0(*(longlong *)(self + 0x28),name,0);
    lVar6 = *(longlong *)(self + 0x30);
    *(int *)(self + 200) = potential;
    *(int *)(self + 0xcc) = itemId;
    plVar3 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
    lVar4 = FUN_7fff5fc6d000((longlong)potential,0);
    if (plVar3 != (longlong *)0x0) {
      if (lVar4 != 0) {
        lVar5 = func_0x7fff5f47c7e0(lVar4,*(undefined8 *)(*plVar3 + 0x40));
        if (lVar5 == 0) {
          uVar7 = func_0x7fff5f47d0b0();
          FUN_7fff5f47d620(uVar7,0);
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
      }
      if ((int)plVar3[3] == 0) {
        FUN_7fff5f47d650();
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      plVar3[4] = lVar4;
      thunk_FUN_7fff5f491fd0();
      if (lVar6 != 0) {
        FUN_7fff5f55c500(lVar6,plVar3,0);
        iVar2 = 0;
        if (0 < potential) {
          iVar2 = grantnum;
        }
        if (*(longlong *)(self + 0x40) != 0) {
          bVar8 = 0;
          if (0 < iVar2) {
            bVar8 = buttonEnabled;
          }
          FUN_7fff618a4510(*(longlong *)(self + 0x40),bVar8,0);
          if (*(longlong *)(self + 0x38) != 0) {
            lVar6 = FUN_7fff60678610(*(longlong *)(self + 0x38),_DAT_7fff6244b618);
            plVar3 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
            aiStackX_8[0] = iVar2;
            lVar4 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,aiStackX_8);
            if (plVar3 != (longlong *)0x0) {
              if (lVar4 != 0) {
                lVar5 = func_0x7fff5f47c7e0(lVar4,*(undefined8 *)(*plVar3 + 0x40));
                if (lVar5 == 0) {
                  uVar7 = func_0x7fff5f47d0b0();
                  FUN_7fff5f47d620(uVar7,0);
                  pcVar1 = (code *)swi(3);
                  (*pcVar1)();
                  return;
                }
              }
              if ((int)plVar3[3] == 0) {
                FUN_7fff5f47d650();
                pcVar1 = (code *)swi(3);
                (*pcVar1)();
                return;
              }
              plVar3[4] = lVar4;
              thunk_FUN_7fff5f491fd0();
              if (lVar6 != 0) {
                FUN_7fff5f55c500(lVar6,plVar3,0);
                return;
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
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

