
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerAttackBase_CalcMagicResistDamage
              (undefined *status,int targetMdef,float addResist,undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  longlong lVar3;
  float fVar4;
  
  fVar4 = 0.0;
  if ((float)targetMdef < 0.0) {
LAB_7ffe9a4aab76:
    if (_DAT_7ffe9c049b18 <= fVar4) {
      fVar4 = _DAT_7ffe9c049b18;
    }
    return (int)((_DAT_7ffe9c049b18 - fVar4) * (float)targetMdef);
  }
  if (status != (undefined *)0x0) {
    lVar3 = (**(code **)(*(longlong *)status + 0x1d8))
                      (status,*(undefined8 *)(*(longlong *)status + 0x1e0));
    if (lVar3 != 0) {
      fVar4 = (float)FUN_7ffe9a4eb220(lVar3,0x34);
      lVar3 = (**(code **)(*(longlong *)status + 0x1c8))
                        (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
      if (lVar3 != 0) {
        iVar2 = FUN_7ffe9a7c8da0(lVar3,0x49);
        fVar4 = (float)iVar2 * _DAT_7ffe9c049b34 + fVar4 + addResist + 0.0;
        goto LAB_7ffe9a4aab76;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  iVar2 = (*pcVar1)();
  return iVar2;
}

