
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
  
  if (DAT_7ffe9cadded4 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    DAT_7ffe9cadded4 = '\x01';
  }
  fVar5 = _DAT_7ffe9c049cfc;
  iVar2 = (int)type;
  if ((iVar2 != 0) && (iVar2 != 1)) {
    if (iVar2 == 2) {
      if (mobStatus != (undefined *)0x0) {
        iVar2 = FUN_7ffe99742f50(0x16,_DAT_7ffe9c93ed20,mobStatus,playerStatus);
        fVar5 = (float)*(int *)(self + 0xe8) / _DAT_7ffe9c049cfc;
        iVar3 = (**(code **)(*(longlong *)self + 0x188))
                          (self,*(undefined8 *)(*(longlong *)self + 400));
        if ((iVar3 == 0x71) && (1 < iVar2)) {
          iVar2 = (int)((float)iVar2 * _DAT_7ffe9c049b4c);
        }
        fVar7 = 0.0;
        if ((float)iVar2 < 0.0) {
LAB_7ffe9a4ab36e:
          if (_DAT_7ffe9c049b18 <= fVar7) {
            fVar7 = _DAT_7ffe9c049b18;
          }
          return (int)((_DAT_7ffe9c049b18 - fVar7) * (float)iVar2);
        }
        if ((playerStatus != (undefined *)0x0) &&
           (lVar4 = (**(code **)(*(longlong *)playerStatus + 0x1d8))
                              (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x1e0)),
           lVar4 != 0)) {
          fVar7 = (float)FUN_7ffe9a4eb220(lVar4,0x34);
          lVar4 = (**(code **)(*(longlong *)playerStatus + 0x1c8))
                            (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x1d0));
          if (lVar4 != 0) {
            iVar3 = FUN_7ffe9a7c8da0(lVar4,0x49);
            fVar7 = (float)iVar3 * _DAT_7ffe9c049b34 + fVar7 + addRegistvalue + fVar5 + 0.0;
            goto LAB_7ffe9a4ab36e;
          }
        }
      }
      goto LAB_7ffe9a4ab4e4;
    }
    if (iVar2 != 3) {
      return 0;
    }
  }
  fVar7 = (float)*(int *)(self + 0xe4) / _DAT_7ffe9c049cfc;
  fVar8 = (float)*(int *)(self + 0xe8) / _DAT_7ffe9c049cfc;
  if (mobStatus != (undefined *)0x0) {
    iVar2 = FUN_7ffe99742f50(0x15,_DAT_7ffe9c93ed20,mobStatus,playerStatus);
    fVar6 = 0.0;
    if ((float)iVar2 < 0.0) {
LAB_7ffe9a4ab480:
      if (_DAT_7ffe9c049b18 <= fVar6) {
        fVar6 = _DAT_7ffe9c049b18;
      }
      iVar2 = (int)((_DAT_7ffe9c049b18 - fVar6) * (float)iVar2);
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
      fVar6 = (float)FUN_7ffe9a4eb220(lVar4,0x33);
      lVar4 = (**(code **)(*(longlong *)playerStatus + 0x1c8))
                        (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x1d0));
      if (lVar4 != 0) {
        iVar3 = FUN_7ffe9a7c8da0(lVar4,0x48);
        fVar6 = (float)iVar3 * _DAT_7ffe9c049b34 + fVar6 + fVar7 + addRegistvalue + fVar8 + 0.0;
        goto LAB_7ffe9a4ab480;
      }
    }
  }
LAB_7ffe9a4ab4e4:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  iVar2 = (*pcVar1)();
  return iVar2;
}

