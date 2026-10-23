
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GuildRaidBossMobBattleStatus_get_CutMagicAttack(undefined *self,undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  int iVar3;
  int iVar4;
  undefined8 uVar5;
  longlong lVar6;
  
  if (DAT_7fff625e4c69 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62406640);
    FUN_7fff5f47d450(&DAT_7fff62422c20);
    FUN_7fff5f47d450(&DAT_7fff62446a70);
    FUN_7fff5f47d450(&DAT_7fff6244f220);
    FUN_7fff5f47d450(&DAT_7fff62461960);
    DAT_7fff625e4c69 = '\x01';
  }
  if (*(longlong *)(self + 0x20) != 0) {
    iVar4 = *(int *)(*(longlong *)(self + 0x20) + 0x48);
    if (*(longlong *)(self + 0x18) != 0) {
      uVar5 = FUN_7fff607dcb60(*(longlong *)(self + 0x18),_DAT_7fff62406640);
      if (*(int *)(_DAT_7fff62461960 + 0xe0) == 0) {
        func_0x7fff5f47d6f0(_DAT_7fff62461960);
      }
      lVar6 = *(longlong *)(*(longlong *)(_DAT_7fff62461960 + 0xb8) + 0x28);
      if (lVar6 == 0) {
        if (*(int *)(_DAT_7fff62461960 + 0xe0) == 0) {
          func_0x7fff5f47d6f0(_DAT_7fff62461960);
        }
        uVar1 = **(undefined8 **)(_DAT_7fff62461960 + 0xb8);
        lVar6 = func_0x7fff5f44ff00(_DAT_7fff62446a70);
        FUN_7fff60a1fa30(lVar6,uVar1,_DAT_7fff6244f220,0);
        *(longlong *)(*(longlong *)(_DAT_7fff62461960 + 0xb8) + 0x28) = lVar6;
        thunk_FUN_7fff5f491fd0();
      }
      iVar3 = FUN_7fff6069a2e0(uVar5,lVar6,_DAT_7fff62422c20);
      return *(int *)(self + 0x10) / 10 + iVar4 + iVar3;
    }
  }
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  iVar4 = (*pcVar2)();
  return iVar4;
}

