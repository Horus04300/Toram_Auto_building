
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GuildRaidBossMobBattleStatus_get_Def(undefined *self,undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  undefined8 uVar5;
  longlong lVar6;
  int iVar7;
  float afStackX_8 [4];
  int aiStackX_18 [2];
  longlong lStackX_20;
  longlong *aplStack_38 [2];
  
  if (DAT_7fff625e4c66 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62406640);
    FUN_7fff5f47d450(&DAT_7fff62422c20);
    FUN_7fff5f47d450(&DAT_7fff62446a70);
    FUN_7fff5f47d450(&DAT_7fff6244f2e0);
    FUN_7fff5f47d450(&DAT_7fff62461960);
    DAT_7fff625e4c66 = '\x01';
  }
  aplStack_38[0] = (longlong *)0x0;
  if (*(longlong *)(self + 0x20) != 0) {
    iVar7 = (int)((float)(*(int *)(*(longlong *)(self + 0x20) + 0x3c) * *(int *)(self + 0x10)) *
                 _DAT_7fff61b52b34);
    if (DAT_7fff625e4c72 == '\0') {
      FUN_7fff5f47d450(&DAT_7fff62430c10);
      DAT_7fff625e4c72 = '\x01';
    }
    afStackX_8[0] = 0.0;
    lStackX_20 = 0;
    aiStackX_18[0] = 0;
    if (*(longlong *)(self + 0x40) == 0) {
LAB_7fff5fe28397:
      FUN_7fff5f47d660();
      pcVar2 = (code *)swi(3);
      iVar7 = (*pcVar2)();
      return iVar7;
    }
    cVar3 = FUN_7fff606c2a90(*(longlong *)(self + 0x40),0x28,&lStackX_20,_DAT_7fff62430c10);
    if (cVar3 != '\0') {
      if (lStackX_20 == 0) goto LAB_7fff5fe28397;
      cVar3 = FUN_7fff5fe86c30(lStackX_20,1,aiStackX_18,afStackX_8,0);
      if (cVar3 != '\0') {
        iVar7 = (int)((afStackX_8[0] + _DAT_7fff61b52b18) * (float)iVar7 + (float)aiStackX_18[0]);
      }
    }
    if (*(longlong *)(self + 0x18) != 0) {
      uVar5 = FUN_7fff607dcb60(*(longlong *)(self + 0x18),_DAT_7fff62406640);
      if (*(int *)(_DAT_7fff62461960 + 0xe0) == 0) {
        func_0x7fff5f47d6f0(_DAT_7fff62461960);
      }
      lVar6 = *(longlong *)(*(longlong *)(_DAT_7fff62461960 + 0xb8) + 0x10);
      if (lVar6 == 0) {
        if (*(int *)(_DAT_7fff62461960 + 0xe0) == 0) {
          func_0x7fff5f47d6f0(_DAT_7fff62461960);
        }
        uVar1 = **(undefined8 **)(_DAT_7fff62461960 + 0xb8);
        lVar6 = func_0x7fff5f44ff00(_DAT_7fff62446a70);
        FUN_7fff60a1fa30(lVar6,uVar1,_DAT_7fff6244f2e0,0);
        *(longlong *)(*(longlong *)(_DAT_7fff62461960 + 0xb8) + 0x10) = lVar6;
        thunk_FUN_7fff5f491fd0();
      }
      iVar4 = FUN_7fff6069a2e0(uVar5,lVar6,_DAT_7fff62422c20);
      iVar7 = iVar7 + iVar4;
      if (*(longlong *)(self + 0x30) != 0) {
        cVar3 = FUN_7fff5fdb76c0(*(longlong *)(self + 0x30),2,aplStack_38);
        if (cVar3 != '\0') {
          if (aplStack_38[0] == (longlong *)0x0) goto LAB_7fff5fe28391;
          iVar4 = (**(code **)(*aplStack_38[0] + 0x1a8))
                            (aplStack_38[0],*(undefined8 *)(*aplStack_38[0] + 0x1b0));
          iVar7 = (int)(((float)(iVar4 + 100) / _DAT_7fff61b52cfc) * (float)iVar7);
        }
        if (*(longlong *)(self + 0x28) != 0) {
          cVar3 = FUN_7fff5ffe5620(*(longlong *)(self + 0x28),10);
          if (cVar3 != '\0') {
            iVar7 = (int)((float)iVar7 * _DAT_7fff61b52b4c);
          }
          if (*(longlong *)(self + 0x28) != 0) {
            cVar3 = FUN_7fff5ffe5620(*(longlong *)(self + 0x28),0x16);
            if (cVar3 != '\0') {
              iVar7 = (int)((float)iVar7 * _DAT_7fff61b52b4c);
            }
            return iVar7;
          }
        }
      }
    }
  }
LAB_7fff5fe28391:
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  iVar7 = (*pcVar2)();
  return iVar7;
}

