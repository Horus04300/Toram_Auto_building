
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float MobAttackBase_calcEquipDefPercent(undefined *self,float eqDef,undefined *methodInfo)

{
  float fVar1;
  
  fVar1 = _DAT_7ffe9c049cfc;
  if (eqDef <= _DAT_7ffe9c049cfc) {
    fVar1 = eqDef;
  }
  return (_DAT_7ffe9c049cfc - fVar1) / _DAT_7ffe9c049cfc;
}

