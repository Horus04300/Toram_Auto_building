
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GuildRaidBossMobBattleStatus___c__get_Def_b__9_0
              (undefined *self,undefined *p,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  int iVar3;
  
  if (p == (undefined *)0x0) {
    FUN_7fff5f47d660();
    pcVar1 = (code *)swi(3);
    iVar3 = (*pcVar1)();
    return iVar3;
  }
  bVar2 = MobPartsStatus_get_IsDead(p,(undefined *)0x0);
  if (bVar2 == 0) {
                    /* WARNING: Could not recover jumptable at 0x7fff5fe3b025. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    iVar3 = (**(code **)(*(longlong *)p + 0x188))(p,*(undefined8 *)(*(longlong *)p + 400));
    return iVar3;
  }
  return 0;
}

