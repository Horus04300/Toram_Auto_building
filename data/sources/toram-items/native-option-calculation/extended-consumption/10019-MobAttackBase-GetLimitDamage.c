
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobAttackBase_GetLimitDamage
              (undefined *self,int baseDamage,undefined *mobAction,undefined *isMinDamage,
              undefined *isMaxDamage,undefined *methodInfo)

{
  byte bVar1;
  int aiStackX_10 [2];
  int aiStackX_18 [2];
  
  *isMinDamage = 0;
  aiStackX_10[0] = 0;
  *isMaxDamage = 0;
  aiStackX_18[0] = 0;
  bVar1 = MobAttackBase_CheckDamageLimit
                    (self,mobAction,(undefined *)aiStackX_10,(undefined *)aiStackX_18,
                     (undefined *)0x0);
  if (bVar1 != 0) {
    if ((aiStackX_10[0] != -1) && (baseDamage < aiStackX_10[0])) {
      *isMinDamage = 1;
      baseDamage = aiStackX_10[0];
    }
    if ((aiStackX_18[0] != -1) && (aiStackX_18[0] < baseDamage)) {
      *isMinDamage = 0;
      *isMaxDamage = 1;
      return aiStackX_18[0];
    }
  }
  return baseDamage;
}

