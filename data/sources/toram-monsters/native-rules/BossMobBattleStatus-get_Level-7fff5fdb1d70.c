
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BossMobBattleStatus_get_Level(undefined *self,undefined *methodInfo)

{
  undefined4 uVar1;
  code *pcVar2;
  short sVar3;
  int iVar4;
  
  if (DAT_7fff625e492c == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62450e80);
    DAT_7fff625e492c = '\x01';
  }
  if (*(longlong *)(self + 0x10) != 0) {
    sVar3 = *(short *)(self + 0x28);
    uVar1 = *(undefined4 *)(*(longlong *)(self + 0x10) + 0x28);
    if (*(int *)(_DAT_7fff62450e80 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    sVar3 = Toram_Common_Rooms_BossDifficultyLevelMethods_GetLevel
                      ((short)uVar1,(int)sVar3,(undefined *)0x0);
    return (int)sVar3;
  }
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  iVar4 = (*pcVar2)();
  return iVar4;
}

