
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float MobAttackBase_CalcElementBonus
                (undefined *self,undefined *status,undefined *targetType,undefined *methodInfo)

{
  uint uVar1;
  byte bVar2;
  int iVar3;
  
  if (DAT_7ffe9cadd7de == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c94c0a0);
    DAT_7ffe9cadd7de = '\x01';
  }
  uVar1 = *(uint *)(self + 0x30);
  if (*(int *)(_DAT_7ffe9c94c0a0 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  bVar2 = SkillUtil_CheckWeakElemet
                    ((undefined *)(ulonglong)uVar1,(undefined *)((ulonglong)targetType & 0xffffffff)
                     ,(undefined *)0x0);
  iVar3 = 100;
  if (bVar2 != 0) {
    iVar3 = 0x7d;
  }
  return (float)iVar3 * _DAT_7ffe9c049b34;
}

