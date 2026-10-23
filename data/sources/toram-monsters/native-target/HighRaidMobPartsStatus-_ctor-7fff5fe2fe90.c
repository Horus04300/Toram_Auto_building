
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void HighRaidMobPartsStatus__ctor
               (undefined *self,undefined *statusMaster,int hp,short difficulty,int level,
               undefined *methodInfo)

{
  MobPartsStatus__ctor(self,statusMaster,hp,difficulty,(undefined *)0x0);
  *(int *)(self + 0x38) = level;
  return;
}

