
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GuildRaidBossMobBattleStatus_get_NecessaryHit(undefined *self,undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  undefined8 uVar5;
  longlong lVar6;
  int iVar7;
  float afStackX_8 [2];
  int aiStackX_18 [2];
  longlong lStackX_20;
  
  if (DAT_7fff625e4c65 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62406640);
    FUN_7fff5f47d450(&DAT_7fff62422c20);
    FUN_7fff5f47d450(&DAT_7fff62446a70);
    FUN_7fff5f47d450(&DAT_7fff6244f5f0);
    FUN_7fff5f47d450(&DAT_7fff62461960);
    DAT_7fff625e4c65 = '\x01';
  }
  if (*(longlong *)(self + 0x20) != 0) {
    iVar7 = (int)((float)*(int *)(self + 0x10) * _DAT_7fff61b52cd8 *
                  (float)*(int *)(*(longlong *)(self + 0x20) + 0x38) * _DAT_7fff61b52b34);
    if (DAT_7fff625e4c72 == '\0') {
      FUN_7fff5f47d450(&DAT_7fff62430c10);
      DAT_7fff625e4c72 = '\x01';
    }
    lStackX_20 = 0;
    afStackX_8[0] = 0.0;
    aiStackX_18[0] = 0;
    if (*(longlong *)(self + 0x40) == 0) {
LAB_7fff5fe28dfb:
      FUN_7fff5f47d660();
      pcVar2 = (code *)swi(3);
      iVar7 = (*pcVar2)();
      return iVar7;
    }
    cVar3 = FUN_7fff606c2a90(*(longlong *)(self + 0x40),0x28,&lStackX_20,_DAT_7fff62430c10);
    if (cVar3 != '\0') {
      if (lStackX_20 == 0) goto LAB_7fff5fe28dfb;
      cVar3 = FUN_7fff5fe86c30(lStackX_20,7,aiStackX_18,afStackX_8,0);
      if (cVar3 != '\0') {
        iVar7 = (int)((afStackX_8[0] + _DAT_7fff61b52b18) * (float)iVar7 + (float)aiStackX_18[0]);
      }
    }
    if (*(longlong *)(self + 0x18) != 0) {
      uVar5 = FUN_7fff607dcb60(*(longlong *)(self + 0x18),_DAT_7fff62406640);
      if (*(int *)(_DAT_7fff62461960 + 0xe0) == 0) {
        func_0x7fff5f47d6f0(_DAT_7fff62461960);
      }
      lVar6 = *(longlong *)(*(longlong *)(_DAT_7fff62461960 + 0xb8) + 8);
      if (lVar6 == 0) {
        if (*(int *)(_DAT_7fff62461960 + 0xe0) == 0) {
          func_0x7fff5f47d6f0(_DAT_7fff62461960);
        }
        uVar1 = **(undefined8 **)(_DAT_7fff62461960 + 0xb8);
        lVar6 = func_0x7fff5f44ff00(_DAT_7fff62446a70);
        FUN_7fff60a1fa30(lVar6,uVar1,_DAT_7fff6244f5f0,0);
        *(longlong *)(*(longlong *)(_DAT_7fff62461960 + 0xb8) + 8) = lVar6;
        thunk_FUN_7fff5f491fd0();
      }
      iVar4 = FUN_7fff6069a2e0(uVar5,lVar6,_DAT_7fff62422c20);
      return iVar4 + iVar7;
    }
  }
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  iVar7 = (*pcVar2)();
  return iVar7;
}

