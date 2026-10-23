
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerAttackBase_CalcPowerResistDamage
              (undefined *status,int targetDef,float addResist,undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  longlong lVar3;
  float fVar4;
  
  fVar4 = 0.0;
  if ((float)targetDef < 0.0) {
LAB_7fff5ffb5d26:
    if (_DAT_7fff61b52b18 <= fVar4) {
      fVar4 = _DAT_7fff61b52b18;
    }
    return (int)((_DAT_7fff61b52b18 - fVar4) * (float)targetDef);
  }
  if (status != (undefined *)0x0) {
    lVar3 = (**(code **)(*(longlong *)status + 0x1d8))
                      (status,*(undefined8 *)(*(longlong *)status + 0x1e0));
    if (lVar3 != 0) {
      fVar4 = (float)FUN_7fff5fff5de0(lVar3,0x33);
      lVar3 = (**(code **)(*(longlong *)status + 0x1c8))
                        (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
      if (lVar3 != 0) {
        iVar2 = FUN_7fff602d3230(lVar3,0x48);
        fVar4 = (float)iVar2 * _DAT_7fff61b52b34 + fVar4 + addResist + 0.0;
        goto LAB_7fff5ffb5d26;
      }
    }
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  iVar2 = (*pcVar1)();
  return iVar2;
}

