
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte GuildRaidBossMobBattleStatus_TryGetCollectionValue
               (undefined *self,undefined *type,undefined *constant,undefined *rate,
               undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  undefined *puStackX_8;
  
  if (DAT_7ffe9cadd51a == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c929d78);
    DAT_7ffe9cadd51a = '\x01';
  }
  *(undefined4 *)constant = 0;
  *(undefined4 *)rate = 0;
  puStackX_8 = (undefined *)0x0;
  if (*(longlong *)(self + 0x40) != 0) {
    cVar2 = FUN_7ffe9abb86e0(*(longlong *)(self + 0x40),0x28,&puStackX_8,_DAT_7ffe9c929d78);
    bVar3 = 0;
    if (cVar2 != '\0') {
      if (puStackX_8 == (undefined *)0x0) goto LAB_7ffe9a31cc3a;
      bVar3 = MobPropertyStatusCollection_TryGetValue
                        (puStackX_8,(undefined *)((ulonglong)type & 0xffffffff),constant,rate,
                         (undefined *)0x0);
    }
    return bVar3;
  }
LAB_7ffe9a31cc3a:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  bVar3 = (*pcVar1)();
  return bVar3;
}

