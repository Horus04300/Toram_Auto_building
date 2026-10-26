
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobAttackBase_SetAbnormalEffect
               (undefined *self,undefined *skillDamageData,undefined *status,int guardPower,
               byte justGuard,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  undefined4 in_stack_ffffffffffffffd4;
  
  lVar1 = *(longlong *)(self + 0xa0);
  if (lVar1 != 0) {
    MobAttackBase_SetAbnormalEffect
              (self,skillDamageData,status,guardPower,justGuard,
               (undefined *)CONCAT44(in_stack_ffffffffffffffd4,*(undefined4 *)(lVar1 + 0x30)),
               *(int *)(lVar1 + 0x34),*(int *)(lVar1 + 0x38),(undefined *)0x0);
    return;
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

