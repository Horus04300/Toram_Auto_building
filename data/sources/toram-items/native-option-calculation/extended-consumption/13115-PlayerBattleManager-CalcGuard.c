
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerBattleManager_CalcGuard
              (undefined *self,int damage,undefined *guardPower,undefined *methodInfo)

{
  undefined8 uVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  
  if (DAT_7ffe9caddcdf == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    DAT_7ffe9caddcdf = '\x01';
  }
  uVar1 = *(undefined8 *)(self + 0x98);
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar3 = FUN_7ffe9bda2160(uVar1,0,0);
  if (cVar3 == '\0') {
    iVar4 = func_0x7ffe9a7df9b0(self,damage,guardPower,0);
  }
  else {
    if (*(undefined **)(self + 0x98) == (undefined *)0x0) {
      FUN_7ffe9996d7a0();
      pcVar2 = (code *)swi(3);
      iVar4 = (*pcVar2)();
      return iVar4;
    }
    iVar4 = GuardActionManager_CalcGuard
                      (*(undefined **)(self + 0x98),damage,guardPower,(undefined *)0x0);
  }
  return iVar4;
}

