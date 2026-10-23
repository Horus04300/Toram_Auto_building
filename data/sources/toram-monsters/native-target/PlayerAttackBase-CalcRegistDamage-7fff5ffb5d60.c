
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int PlayerAttackBase_CalcRegistDamage
              (undefined *self,undefined *type,undefined *playerStatus,undefined *mobStatus,
              float addRegistvalue,undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  longlong lVar4;
  float fVar5;
  float fVar6;
  float fVar7;
  float fVar8;
  
  if (DAT_7fff625e562c == '\0') {
    FUN_7fff5f47d450(&DAT_7fff624465a0);
    DAT_7fff625e562c = '\x01';
  }
  fVar5 = _DAT_7fff61b52cfc;
  iVar2 = (int)type;
  if ((iVar2 != 0) && (iVar2 != 1)) {
    if (iVar2 == 2) {
      if (mobStatus != (undefined *)0x0) {
        iVar2 = FUN_7fff5f252f50(0x16,_DAT_7fff624465a0,mobStatus,playerStatus);
        fVar5 = (float)*(int *)(self + 0xe8) / _DAT_7fff61b52cfc;
        iVar3 = (**(code **)(*(longlong *)self + 0x188))
                          (self,*(undefined8 *)(*(longlong *)self + 400));
        if ((iVar3 == 0x71) && (1 < iVar2)) {
          iVar2 = (int)((float)iVar2 * _DAT_7fff61b52b4c);
        }
        fVar7 = 0.0;
        if ((float)iVar2 < 0.0) {
LAB_7fff5ffb5f2e:
          if (_DAT_7fff61b52b18 <= fVar7) {
            fVar7 = _DAT_7fff61b52b18;
          }
          return (int)((_DAT_7fff61b52b18 - fVar7) * (float)iVar2);
        }
        if ((playerStatus != (undefined *)0x0) &&
           (lVar4 = (**(code **)(*(longlong *)playerStatus + 0x1d8))
                              (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x1e0)),
           lVar4 != 0)) {
          fVar7 = (float)FUN_7fff5fff5de0(lVar4,0x34);
          lVar4 = (**(code **)(*(longlong *)playerStatus + 0x1c8))
                            (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x1d0));
          if (lVar4 != 0) {
            iVar3 = FUN_7fff602d3230(lVar4,0x49);
            fVar7 = (float)iVar3 * _DAT_7fff61b52b34 + fVar7 + addRegistvalue + fVar5 + 0.0;
            goto LAB_7fff5ffb5f2e;
          }
        }
      }
      goto LAB_7fff5ffb60a4;
    }
    if (iVar2 != 3) {
      return 0;
    }
  }
  fVar7 = (float)*(int *)(self + 0xe4) / _DAT_7fff61b52cfc;
  fVar8 = (float)*(int *)(self + 0xe8) / _DAT_7fff61b52cfc;
  if (mobStatus != (undefined *)0x0) {
    iVar2 = FUN_7fff5f252f50(0x15,_DAT_7fff624465a0,mobStatus,playerStatus);
    fVar6 = 0.0;
    if ((float)iVar2 < 0.0) {
LAB_7fff5ffb6040:
      if (_DAT_7fff61b52b18 <= fVar6) {
        fVar6 = _DAT_7fff61b52b18;
      }
      iVar2 = (int)((_DAT_7fff61b52b18 - fVar6) * (float)iVar2);
      iVar3 = (**(code **)(*(longlong *)self + 0x188))
                        (self,*(undefined8 *)(*(longlong *)self + 400));
      if (iVar3 == 0x59) {
        iVar2 = (int)(((float)(int)((0xe - (uint)(byte)self[0x14]) * 5) / fVar5) * (float)iVar2);
      }
      return iVar2;
    }
    if ((playerStatus != (undefined *)0x0) &&
       (lVar4 = (**(code **)(*(longlong *)playerStatus + 0x1d8))
                          (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x1e0)),
       lVar4 != 0)) {
      fVar6 = (float)FUN_7fff5fff5de0(lVar4,0x33);
      lVar4 = (**(code **)(*(longlong *)playerStatus + 0x1c8))
                        (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x1d0));
      if (lVar4 != 0) {
        iVar3 = FUN_7fff602d3230(lVar4,0x48);
        fVar6 = (float)iVar3 * _DAT_7fff61b52b34 + fVar6 + fVar7 + addRegistvalue + fVar8 + 0.0;
        goto LAB_7fff5ffb6040;
      }
    }
  }
LAB_7fff5ffb60a4:
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  iVar2 = (*pcVar1)();
  return iVar2;
}

