
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GuildRaidBossMobBattleStatus___c__get_NecessaryHit_b__7_0
              (undefined *self,undefined *p,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  int iVar3;
  
  if (p == (undefined *)0x0) {
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    iVar3 = (*pcVar1)();
    return iVar3;
  }
  bVar2 = MobPartsStatus_get_IsDead(p,(undefined *)0x0);
  if (bVar2 == 0) {
                    /* WARNING: Could not recover jumptable at 0x7ffe9a330475. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar3 = (**(code **)(*(longlong *)p + 0x178))(p,*(undefined8 *)(*(longlong *)p + 0x180));
    return iVar3;
  }
  return 0;
}

