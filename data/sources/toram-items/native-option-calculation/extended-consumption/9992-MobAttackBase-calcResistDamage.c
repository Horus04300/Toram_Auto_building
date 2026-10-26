
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobAttackBase_calcResistDamage(undefined *self,int damage,float resistVal,undefined *methodInfo)

{
  float fVar1;
  uint uVar2;
  ulonglong uVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  float fVar7;
  
  fVar1 = _DAT_7ffe9c049cf4;
  if (resistVal < 0.0) {
    fVar7 = (float)((uint)resistVal ^ _DAT_7ffe9c049c00) / _DAT_7ffe9c049cf4;
    if (DAT_7ffe9cad9e25 == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c968830);
      DAT_7ffe9cad9e25 = '\x01';
    }
    if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    dVar6 = (double)func_0x7ffe99997768((double)fVar7);
    iVar5 = 0;
    iVar4 = (int)dVar6;
    if (7 < iVar4) {
      uVar2 = (iVar4 - 8U >> 3) + 1;
      uVar3 = (ulonglong)uVar2;
      iVar5 = uVar2 * 8;
      do {
        if (_DAT_7ffe9c049e0c < resistVal) {
          fVar7 = ((_DAT_7ffe9c049cfc - resistVal) * (float)damage) / _DAT_7ffe9c049cfc;
        }
        else {
          resistVal = resistVal + fVar1;
          fVar7 = (float)damage * _DAT_7ffe9c049cd8;
        }
        if (_DAT_7ffe9c049e0c < resistVal) {
          fVar7 = ((_DAT_7ffe9c049cfc - resistVal) * (float)(int)fVar7) / _DAT_7ffe9c049cfc;
        }
        else {
          resistVal = resistVal + fVar1;
          fVar7 = (float)(int)fVar7 * _DAT_7ffe9c049cd8;
        }
        if (_DAT_7ffe9c049e0c < resistVal) {
          fVar7 = ((_DAT_7ffe9c049cfc - resistVal) * (float)(int)fVar7) / _DAT_7ffe9c049cfc;
        }
        else {
          resistVal = resistVal + fVar1;
          fVar7 = (float)(int)fVar7 * _DAT_7ffe9c049cd8;
        }
        if (_DAT_7ffe9c049e0c < resistVal) {
          fVar7 = ((_DAT_7ffe9c049cfc - resistVal) * (float)(int)fVar7) / _DAT_7ffe9c049cfc;
        }
        else {
          resistVal = resistVal + fVar1;
          fVar7 = (float)(int)fVar7 * _DAT_7ffe9c049cd8;
        }
        if (_DAT_7ffe9c049e0c < resistVal) {
          fVar7 = ((_DAT_7ffe9c049cfc - resistVal) * (float)(int)fVar7) / _DAT_7ffe9c049cfc;
        }
        else {
          resistVal = resistVal + fVar1;
          fVar7 = (float)(int)fVar7 * _DAT_7ffe9c049cd8;
        }
        if (_DAT_7ffe9c049e0c < resistVal) {
          fVar7 = ((_DAT_7ffe9c049cfc - resistVal) * (float)(int)fVar7) / _DAT_7ffe9c049cfc;
        }
        else {
          resistVal = resistVal + fVar1;
          fVar7 = (float)(int)fVar7 * _DAT_7ffe9c049cd8;
        }
        if (_DAT_7ffe9c049e0c < resistVal) {
          fVar7 = ((_DAT_7ffe9c049cfc - resistVal) * (float)(int)fVar7) / _DAT_7ffe9c049cfc;
        }
        else {
          resistVal = resistVal + fVar1;
          fVar7 = (float)(int)fVar7 * _DAT_7ffe9c049cd8;
        }
        if (_DAT_7ffe9c049e0c < resistVal) {
          fVar7 = ((_DAT_7ffe9c049cfc - resistVal) * (float)(int)fVar7) / _DAT_7ffe9c049cfc;
        }
        else {
          resistVal = resistVal + fVar1;
          fVar7 = (float)(int)fVar7 * _DAT_7ffe9c049cd8;
        }
        damage = (int)fVar7;
        uVar3 = uVar3 - 1;
      } while (uVar3 != 0);
    }
    if (iVar5 < iVar4) {
      uVar3 = (ulonglong)(uint)(iVar4 - iVar5);
      do {
        if (_DAT_7ffe9c049e0c < resistVal) {
          fVar7 = ((_DAT_7ffe9c049cfc - resistVal) * (float)damage) / _DAT_7ffe9c049cfc;
        }
        else {
          resistVal = resistVal + fVar1;
          fVar7 = (float)damage * _DAT_7ffe9c049cd8;
        }
        damage = (int)fVar7;
        uVar3 = uVar3 - 1;
      } while (uVar3 != 0);
    }
  }
  else if (0.0 < resistVal) {
    fVar7 = resistVal / _DAT_7ffe9c049cf4;
    if (DAT_7ffe9cad9e25 == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c968830);
      DAT_7ffe9cad9e25 = '\x01';
    }
    if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    dVar6 = (double)func_0x7ffe99997768((double)fVar7);
    iVar5 = 0;
    iVar4 = (int)dVar6;
    if (7 < iVar4) {
      uVar2 = (iVar4 - 8U >> 3) + 1;
      uVar3 = (ulonglong)uVar2;
      iVar5 = uVar2 * 8;
      do {
        if (resistVal < fVar1) {
          fVar7 = ((_DAT_7ffe9c049cfc - resistVal) * (float)damage) / _DAT_7ffe9c049cfc;
        }
        else {
          resistVal = resistVal + _DAT_7ffe9c049e0c;
          fVar7 = (float)damage * _DAT_7ffe9c049b4c;
        }
        if (resistVal < fVar1) {
          fVar7 = ((_DAT_7ffe9c049cfc - resistVal) * (float)(int)fVar7) / _DAT_7ffe9c049cfc;
        }
        else {
          resistVal = resistVal + _DAT_7ffe9c049e0c;
          fVar7 = (float)(int)fVar7 * _DAT_7ffe9c049b4c;
        }
        if (resistVal < fVar1) {
          fVar7 = ((_DAT_7ffe9c049cfc - resistVal) * (float)(int)fVar7) / _DAT_7ffe9c049cfc;
        }
        else {
          resistVal = resistVal + _DAT_7ffe9c049e0c;
          fVar7 = (float)(int)fVar7 * _DAT_7ffe9c049b4c;
        }
        if (resistVal < fVar1) {
          fVar7 = ((_DAT_7ffe9c049cfc - resistVal) * (float)(int)fVar7) / _DAT_7ffe9c049cfc;
        }
        else {
          resistVal = resistVal + _DAT_7ffe9c049e0c;
          fVar7 = (float)(int)fVar7 * _DAT_7ffe9c049b4c;
        }
        if (resistVal < fVar1) {
          fVar7 = ((_DAT_7ffe9c049cfc - resistVal) * (float)(int)fVar7) / _DAT_7ffe9c049cfc;
        }
        else {
          resistVal = resistVal + _DAT_7ffe9c049e0c;
          fVar7 = (float)(int)fVar7 * _DAT_7ffe9c049b4c;
        }
        if (resistVal < fVar1) {
          fVar7 = ((_DAT_7ffe9c049cfc - resistVal) * (float)(int)fVar7) / _DAT_7ffe9c049cfc;
        }
        else {
          resistVal = resistVal + _DAT_7ffe9c049e0c;
          fVar7 = (float)(int)fVar7 * _DAT_7ffe9c049b4c;
        }
        if (resistVal < fVar1) {
          fVar7 = ((_DAT_7ffe9c049cfc - resistVal) * (float)(int)fVar7) / _DAT_7ffe9c049cfc;
        }
        else {
          resistVal = resistVal + _DAT_7ffe9c049e0c;
          fVar7 = (float)(int)fVar7 * _DAT_7ffe9c049b4c;
        }
        if (resistVal < fVar1) {
          fVar7 = ((_DAT_7ffe9c049cfc - resistVal) * (float)(int)fVar7) / _DAT_7ffe9c049cfc;
        }
        else {
          resistVal = resistVal + _DAT_7ffe9c049e0c;
          fVar7 = (float)(int)fVar7 * _DAT_7ffe9c049b4c;
        }
        damage = (int)fVar7;
        uVar3 = uVar3 - 1;
      } while (uVar3 != 0);
    }
    if (iVar5 < iVar4) {
      uVar3 = (ulonglong)(uint)(iVar4 - iVar5);
      do {
        if (resistVal < fVar1) {
          fVar7 = ((_DAT_7ffe9c049cfc - resistVal) * (float)damage) / _DAT_7ffe9c049cfc;
        }
        else {
          resistVal = resistVal + _DAT_7ffe9c049e0c;
          fVar7 = (float)damage * _DAT_7ffe9c049b4c;
        }
        damage = (int)fVar7;
        uVar3 = uVar3 - 1;
      } while (uVar3 != 0);
    }
  }
  return damage;
}

