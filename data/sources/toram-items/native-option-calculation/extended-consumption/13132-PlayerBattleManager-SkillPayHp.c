
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte PlayerBattleManager_SkillPayHp(undefined *self,undefined *action,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  byte bVar3;
  
  if (action == (undefined *)0x0) {
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    bVar3 = (*pcVar1)();
    return bVar3;
  }
  cVar2 = (**(code **)(*(longlong *)action + 0x2d8))
                    (action,*(undefined8 *)(*(longlong *)action + 0x2e0));
  if (cVar2 != '\0') {
    cVar2 = (**(code **)(*(longlong *)action + 0x508))
                      (action,*(undefined8 *)(self + 0x28),
                       *(undefined8 *)(*(longlong *)action + 0x510));
    if (cVar2 == '\0') {
      (**(code **)(*(longlong *)action + 0x518))
                (action,*(undefined8 *)(self + 0x28),*(undefined8 *)(*(longlong *)action + 0x520));
      return 0;
    }
  }
  return 1;
}

