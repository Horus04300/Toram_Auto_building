
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobAttackBase_calcResistDamage(undefined *self,int damage,int resistVal,undefined *methodInfo)

{
  uint uVar1;
  ulonglong uVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  double dVar6;
  float fVar7;
  
  if (resistVal < 0) {
    fVar7 = (float)-resistVal / _DAT_7ffe9c049cf4;
    if (DAT_7ffe9cad9e25 == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c968830);
      DAT_7ffe9cad9e25 = '\x01';
    }
    if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    dVar6 = (double)func_0x7ffe99997768((double)fVar7);
    iVar5 = 0;
    iVar3 = (int)dVar6;
    if (7 < iVar3) {
      uVar1 = (iVar3 - 8U >> 3) + 1;
      uVar2 = (ulonglong)uVar1;
      iVar5 = uVar1 * 8;
      do {
        if (resistVal < -0x31) {
          fVar7 = (float)(int)((float)damage * _DAT_7ffe9c049cd8);
          iVar4 = resistVal + 0x32;
          if (-0x32 < resistVal + 0x32) goto LAB_7ffe9a37779a;
          iVar4 = resistVal + 100;
          fVar7 = (float)(int)(fVar7 * _DAT_7ffe9c049cd8);
          if (-0x32 < iVar4) goto LAB_7ffe9a3777bb;
          iVar4 = resistVal + 0x96;
          fVar7 = (float)(int)(fVar7 * _DAT_7ffe9c049cd8);
          if (-0x32 < iVar4) goto LAB_7ffe9a3777dc;
          iVar4 = resistVal + 200;
          fVar7 = (float)(int)(fVar7 * _DAT_7ffe9c049cd8);
          if (-0x32 < iVar4) goto LAB_7ffe9a3777fd;
          iVar4 = resistVal + 0xfa;
          fVar7 = (float)(int)(fVar7 * _DAT_7ffe9c049cd8);
          if (-0x32 < iVar4) goto LAB_7ffe9a37781e;
          iVar4 = resistVal + 300;
          fVar7 = (float)(int)(fVar7 * _DAT_7ffe9c049cd8);
          if (-0x32 < iVar4) goto LAB_7ffe9a37783f;
          fVar7 = (float)(int)(fVar7 * _DAT_7ffe9c049cd8);
          iVar4 = resistVal + 0x15e;
          if (-0x32 < resistVal + 0x15e) goto LAB_7ffe9a377860;
          resistVal = resistVal + 400;
          fVar7 = fVar7 * _DAT_7ffe9c049cd8;
        }
        else {
          fVar7 = (float)(int)(((_DAT_7ffe9c049cfc - (float)resistVal) * (float)damage) /
                              _DAT_7ffe9c049cfc);
          iVar4 = resistVal;
LAB_7ffe9a37779a:
          fVar7 = (float)(int)(((_DAT_7ffe9c049cfc - (float)iVar4) * fVar7) / _DAT_7ffe9c049cfc);
LAB_7ffe9a3777bb:
          fVar7 = (float)(int)(((_DAT_7ffe9c049cfc - (float)iVar4) * fVar7) / _DAT_7ffe9c049cfc);
LAB_7ffe9a3777dc:
          fVar7 = (float)(int)(((_DAT_7ffe9c049cfc - (float)iVar4) * fVar7) / _DAT_7ffe9c049cfc);
LAB_7ffe9a3777fd:
          fVar7 = (float)(int)(((_DAT_7ffe9c049cfc - (float)iVar4) * fVar7) / _DAT_7ffe9c049cfc);
LAB_7ffe9a37781e:
          fVar7 = (float)(int)(((_DAT_7ffe9c049cfc - (float)iVar4) * fVar7) / _DAT_7ffe9c049cfc);
LAB_7ffe9a37783f:
          fVar7 = (float)(int)(((_DAT_7ffe9c049cfc - (float)iVar4) * fVar7) / _DAT_7ffe9c049cfc);
LAB_7ffe9a377860:
          resistVal = iVar4;
          fVar7 = ((_DAT_7ffe9c049cfc - (float)resistVal) * fVar7) / _DAT_7ffe9c049cfc;
        }
        damage = (int)fVar7;
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
    }
    if (iVar5 < iVar3) {
      uVar2 = (ulonglong)(uint)(iVar3 - iVar5);
      do {
        if (resistVal < -0x31) {
          resistVal = resistVal + 0x32;
          fVar7 = (float)damage * _DAT_7ffe9c049cd8;
        }
        else {
          fVar7 = ((_DAT_7ffe9c049cfc - (float)resistVal) * (float)damage) / _DAT_7ffe9c049cfc;
        }
        damage = (int)fVar7;
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
    }
  }
  else if (0 < resistVal) {
    fVar7 = (float)resistVal / _DAT_7ffe9c049cf4;
    if (DAT_7ffe9cad9e25 == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c968830);
      DAT_7ffe9cad9e25 = '\x01';
    }
    if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    dVar6 = (double)func_0x7ffe99997768((double)fVar7);
    iVar5 = 0;
    iVar3 = (int)dVar6;
    if (7 < iVar3) {
      uVar1 = (iVar3 - 8U >> 3) + 1;
      uVar2 = (ulonglong)uVar1;
      iVar5 = uVar1 * 8;
      do {
        if (resistVal < 0x32) {
          fVar7 = (float)(int)(((_DAT_7ffe9c049cfc - (float)resistVal) * (float)damage) /
                              _DAT_7ffe9c049cfc);
          iVar4 = resistVal;
LAB_7ffe9a3774da:
          fVar7 = (float)(int)(((_DAT_7ffe9c049cfc - (float)iVar4) * fVar7) / _DAT_7ffe9c049cfc);
LAB_7ffe9a3774fb:
          fVar7 = (float)(int)(((_DAT_7ffe9c049cfc - (float)iVar4) * fVar7) / _DAT_7ffe9c049cfc);
LAB_7ffe9a37751c:
          fVar7 = (float)(int)(((_DAT_7ffe9c049cfc - (float)iVar4) * fVar7) / _DAT_7ffe9c049cfc);
LAB_7ffe9a37753d:
          fVar7 = (float)(int)(((_DAT_7ffe9c049cfc - (float)iVar4) * fVar7) / _DAT_7ffe9c049cfc);
LAB_7ffe9a37755e:
          fVar7 = (float)(int)(((_DAT_7ffe9c049cfc - (float)iVar4) * fVar7) / _DAT_7ffe9c049cfc);
LAB_7ffe9a37757f:
          fVar7 = (float)(int)(((_DAT_7ffe9c049cfc - (float)iVar4) * fVar7) / _DAT_7ffe9c049cfc);
LAB_7ffe9a3775a0:
          resistVal = iVar4;
          fVar7 = ((_DAT_7ffe9c049cfc - (float)resistVal) * fVar7) / _DAT_7ffe9c049cfc;
        }
        else {
          fVar7 = (float)(int)((float)damage * _DAT_7ffe9c049b4c);
          iVar4 = resistVal + -0x32;
          if (resistVal + -0x32 < 0x32) goto LAB_7ffe9a3774da;
          iVar4 = resistVal + -100;
          fVar7 = (float)(int)(fVar7 * _DAT_7ffe9c049b4c);
          if (iVar4 < 0x32) goto LAB_7ffe9a3774fb;
          iVar4 = resistVal + -0x96;
          fVar7 = (float)(int)(fVar7 * _DAT_7ffe9c049b4c);
          if (iVar4 < 0x32) goto LAB_7ffe9a37751c;
          iVar4 = resistVal + -200;
          fVar7 = (float)(int)(fVar7 * _DAT_7ffe9c049b4c);
          if (iVar4 < 0x32) goto LAB_7ffe9a37753d;
          iVar4 = resistVal + -0xfa;
          fVar7 = (float)(int)(fVar7 * _DAT_7ffe9c049b4c);
          if (iVar4 < 0x32) goto LAB_7ffe9a37755e;
          iVar4 = resistVal + -300;
          fVar7 = (float)(int)(fVar7 * _DAT_7ffe9c049b4c);
          if (iVar4 < 0x32) goto LAB_7ffe9a37757f;
          fVar7 = (float)(int)(fVar7 * _DAT_7ffe9c049b4c);
          iVar4 = resistVal + -0x15e;
          if (resistVal + -0x15e < 0x32) goto LAB_7ffe9a3775a0;
          resistVal = resistVal + -400;
          fVar7 = fVar7 * _DAT_7ffe9c049b4c;
        }
        damage = (int)fVar7;
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
    }
    if (iVar5 < iVar3) {
      uVar2 = (ulonglong)(uint)(iVar3 - iVar5);
      do {
        if (resistVal < 0x32) {
          fVar7 = ((_DAT_7ffe9c049cfc - (float)resistVal) * (float)damage) / _DAT_7ffe9c049cfc;
        }
        else {
          resistVal = resistVal + -0x32;
          fVar7 = (float)damage * _DAT_7ffe9c049b4c;
        }
        damage = (int)fVar7;
        uVar2 = uVar2 - 1;
      } while (uVar2 != 0);
      return damage;
    }
  }
  return damage;
}

