
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobAttackBase_FinawGuard
               (undefined *self,undefined *damageData,int guardPower,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  
  if (damageData == (undefined *)0x0) {
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  if ((*(int *)(damageData + 0x18) == 6) && (*(int *)(damageData + 0x8c) == -1)) {
    iVar3 = guardPower / 100;
    if (100 < iVar3) {
      iVar3 = 100;
    }
    cVar2 = FUN_7ffe99a4d1d0((int)((float)iVar3 * _DAT_7ffe9c049b4c));
    if (cVar2 != '\0') {
      if (DAT_7ffe9cadfefa == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c92dfe0,0,0,0);
        DAT_7ffe9cadfefa = '\x01';
      }
      *(undefined4 *)(damageData + 0x8c) = 0;
      if (*(int *)(_DAT_7ffe9c92dfe0 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      uVar4 = FUN_7ffe9a4db1f0(0,0);
      *(undefined4 *)(damageData + 0x94) = uVar4;
      uVar4 = FUN_7ffe9a4db080(0,0);
      *(undefined4 *)(damageData + 0x98) = uVar4;
      *(undefined4 *)(damageData + 0x9c) = 0;
      damageData[0xa1] = 0;
      *(uint *)(damageData + 0x70) = *(uint *)(damageData + 0x70) ^ 1;
      return;
    }
  }
  return;
}

