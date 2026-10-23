
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float PlayerAttackBase_CalcLastDamageRate
                (undefined *self,undefined *playerStatus,undefined *attackType,undefined *methodInfo
                )

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  undefined4 uVar4;
  longlong lVar5;
  longlong *plVar6;
  int iVar7;
  float fVar8;
  float fVar9;
  float fVar10;
  float fVar11;
  
  if (DAT_7fff625e5619 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6240c290);
    DAT_7fff625e5619 = '\x01';
  }
  fVar8 = (float)FUN_7fff5ffb60b0(self,playerStatus,(ulonglong)attackType & 0xffffffff,0);
  fVar9 = (float)FUN_7fff5ffb2920(self,playerStatus,0);
  iVar7 = *(int *)(self + 0xcc);
  iVar3 = (**(code **)(*(longlong *)self + 0x618))(self,*(undefined8 *)(*(longlong *)self + 0x620));
  iVar7 = iVar7 + iVar3;
  if (iVar7 < 10) {
    iVar7 = 10;
  }
  else {
    iVar3 = 0x96;
    if (0x96 < iVar7) goto LAB_7fff5ffb5540;
  }
  iVar3 = iVar7;
LAB_7fff5ffb5540:
  fVar11 = (float)iVar3 / _DAT_7fff61b52cfc;
  if (playerStatus != (undefined *)0x0) {
    lVar5 = (**(code **)(*(longlong *)playerStatus + 0x218))
                      (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x220));
    if (lVar5 != 0) {
      plVar6 = (longlong *)FUN_7fff600bc830(lVar5,0x2c,0);
      fVar8 = fVar8 + _DAT_7fff61b52b18;
      if (plVar6 != (longlong *)0x0) {
        uVar4 = (**(code **)(*(longlong *)self + 0x188))
                          (self,*(undefined8 *)(*(longlong *)self + 400));
        if ((*(byte *)(*plVar6 + 0x130) < *(byte *)(_DAT_7fff6240c290 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar6 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7fff6240c290 + 0x130) * 8) != _DAT_7fff6240c290)) {
          FUN_7fff5f47c810(plVar6,_DAT_7fff6240c290);
          pcVar1 = (code *)swi(3);
          fVar8 = (float)(*pcVar1)();
          return fVar8;
        }
        cVar2 = FUN_7fff5fdfa4c0(plVar6,uVar4,*(undefined8 *)(self + 0xd8),fVar11,0);
        if (cVar2 != '\0') {
          iVar7 = FUN_7fff600b97e0(plVar6,2);
          fVar11 = fVar11 + (float)iVar7 / _DAT_7fff61b52cfc;
        }
      }
      fVar10 = (float)FUN_7fff5ffb3a90(self,playerStatus,0);
      return fVar10 * (fVar8 + 0.0) * fVar9 * fVar11;
    }
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  fVar8 = (float)(*pcVar1)();
  return fVar8;
}

