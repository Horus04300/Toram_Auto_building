
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte GuildRaidBossMobBattleStatus_TryGetCollectionValue
               (undefined *self,undefined *type,undefined *constant,undefined *rate,
               undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  longlong lStackX_8;
  
  if (DAT_7fff625e4c72 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62430c10);
    DAT_7fff625e4c72 = '\x01';
  }
  *(undefined4 *)constant = 0;
  *(undefined4 *)rate = 0;
  lStackX_8 = 0;
  if (*(longlong *)(self + 0x40) != 0) {
    cVar2 = FUN_7fff606c2a90(*(longlong *)(self + 0x40),0x28,&lStackX_8,_DAT_7fff62430c10);
    bVar3 = 0;
    if (cVar2 != '\0') {
      if (lStackX_8 == 0) goto LAB_7fff5fe2790a;
      bVar3 = FUN_7fff5fe86c30(lStackX_8,(ulonglong)type & 0xffffffff,constant,rate,0);
    }
    return bVar3;
  }
LAB_7fff5fe2790a:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  bVar3 = (*pcVar1)();
  return bVar3;
}

