
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerAttackBase_calcBaseDamage
              (int atk,int lv,int targetLv,int cut,float mobPropCut,undefined *methodInfo)

{
  return (int)((float)((atk - targetLv) + lv) * ((float)(100 - cut) / _DAT_7fff61b52cfc) *
              mobPropCut);
}

