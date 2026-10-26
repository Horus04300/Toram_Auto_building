
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MagicPursuitAction_ActionPreparation
               (undefined *self,undefined *actarAction,undefined *target,undefined *methodInfo)

{
  PlayerAttackBase_ActionPreparation(self,actarAction,target,(undefined *)0x0);
  *(uint *)(self + 0x108) = *(uint *)(self + 0x108) & 0xffffffef;
  return;
}

