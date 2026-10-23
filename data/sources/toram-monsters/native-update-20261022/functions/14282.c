
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
  
  if (DAT_7ffe9caddec1 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c904970);
    DAT_7ffe9caddec1 = '\x01';
  }
  fVar8 = (float)FUN_7ffe9a4ab4f0(self,playerStatus,(ulonglong)attackType & 0xffffffff,0);
  fVar9 = (float)FUN_7ffe9a4a7d60(self,playerStatus,0);
  iVar7 = *(int *)(self + 0xcc);
  iVar3 = (**(code **)(*(longlong *)self + 0x618))(self,*(undefined8 *)(*(longlong *)self + 0x620));
  iVar7 = iVar7 + iVar3;
  if (iVar7 < 10) {
    iVar7 = 10;
  }
  else {
    iVar3 = 0x96;
    if (0x96 < iVar7) goto LAB_7ffe9a4aa980;
  }
  iVar3 = iVar7;
LAB_7ffe9a4aa980:
  fVar11 = (float)iVar3 / _DAT_7ffe9c049cfc;
  if (playerStatus != (undefined *)0x0) {
    lVar5 = (**(code **)(*(longlong *)playerStatus + 0x218))
                      (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x220));
    if (lVar5 != 0) {
      plVar6 = (longlong *)FUN_7ffe9a5b23a0(lVar5,0x2c,0);
      fVar8 = fVar8 + _DAT_7ffe9c049b18;
      if (plVar6 != (longlong *)0x0) {
        uVar4 = (**(code **)(*(longlong *)self + 0x188))
                          (self,*(undefined8 *)(*(longlong *)self + 400));
        if ((*(byte *)(*plVar6 + 0x130) < *(byte *)(_DAT_7ffe9c904970 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar6 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c904970 + 0x130) * 8) != _DAT_7ffe9c904970)) {
          FUN_7ffe9996c950(plVar6,_DAT_7ffe9c904970);
          pcVar1 = (code *)swi(3);
          fVar8 = (float)(*pcVar1)();
          return fVar8;
        }
        cVar2 = FUN_7ffe9a2ef6c0(plVar6,uVar4,*(undefined8 *)(self + 0xd8),fVar11,0);
        if (cVar2 != '\0') {
          iVar7 = FUN_7ffe9a5af330(plVar6,2);
          fVar11 = fVar11 + (float)iVar7 / _DAT_7ffe9c049cfc;
        }
      }
      fVar10 = (float)FUN_7ffe9a4a8ed0(self,playerStatus,0);
      return fVar10 * (fVar8 + 0.0) * fVar9 * fVar11;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  fVar8 = (float)(*pcVar1)();
  return fVar8;
}

