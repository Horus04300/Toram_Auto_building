
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float PlayerAttackBase_CalcSkillMasteryLastDamageRate
                (undefined *thisObject,undefined *playerStatus,undefined *attackType,
                undefined *methodInfo)

{
  code *pcVar1;
  float fVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  longlong lVar8;
  undefined *puVar9;
  undefined4 uVar10;
  bool bVar11;
  float fVar12;
  longlong *plStackX_8;
  
  if (DAT_7ffe9caddec5 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9635d8);
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c935c98);
    DAT_7ffe9caddec5 = '\x01';
  }
  plStackX_8 = (longlong *)0x0;
  iVar7 = 0;
  iVar5 = iVar7;
  if (*(longlong *)(thisObject + 0xb8) != 0) {
    iVar5 = *(int *)(*(longlong *)(thisObject + 0xb8) + 0x1c);
  }
  iVar4 = (**(code **)(*(longlong *)thisObject + 0x188))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
  if (((((iVar4 == 0x9f) ||
        (iVar4 = (**(code **)(*(longlong *)thisObject + 0x188))
                           (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400)),
        iVar4 == 0x9d)) ||
       (iVar4 = (**(code **)(*(longlong *)thisObject + 0x188))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400)), iVar4 == 0x3f
       )) || ((iVar4 = (**(code **)(*(longlong *)thisObject + 0x188))
                                 (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400)),
              iVar4 == 0x3dc ||
              (iVar4 = (**(code **)(*(longlong *)thisObject + 0x188))
                                 (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400)),
              iVar4 == 0xf)))) ||
     (iVar4 = (**(code **)(*(longlong *)thisObject + 0x188))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400)), iVar4 == 0x13f)
     ) {
    iVar5 = (**(code **)(*(longlong *)thisObject + 0x588))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x590));
  }
  fVar12 = 0.0;
  if (((playerStatus == (undefined *)0x0) ||
      (lVar8 = (**(code **)(*(longlong *)playerStatus + 0x1b8))
                         (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x1c0)),
      lVar8 == 0)) || (*(longlong *)(lVar8 + 0x68) == 0)) goto LAB_7ffe9a4abb25;
  iVar4 = func_0x7ffe9acd8120(*(longlong *)(lVar8 + 0x68),_DAT_7ffe9c935c98);
  if (iVar4 < 1) {
    return 0.0;
  }
  cVar3 = (**(code **)(*(longlong *)thisObject + 0x5b8))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x5c0));
  fVar2 = _DAT_7ffe9c049cfc;
  if ((cVar3 != '\0') && (_DAT_7ffe9c04a330 <= *(float *)(thisObject + 0x20))) {
    lVar8 = (**(code **)(*(longlong *)playerStatus + 0x1b8))
                      (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x1c0));
    if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x68) == 0)) goto LAB_7ffe9a4abb25;
    cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0x48,&plStackX_8,_DAT_7ffe9c935bd0);
    if (cVar3 != '\0') {
      if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a4abb25;
      iVar4 = (**(code **)(*plStackX_8 + 0x178))(plStackX_8,8,*(undefined8 *)(*plStackX_8 + 0x180));
      fVar12 = (float)iVar4 / fVar2 + 0.0;
    }
  }
  iVar4 = (**(code **)(*(longlong *)thisObject + 0x198))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
  if (iVar4 == 1) {
    lVar8 = (**(code **)(*(longlong *)playerStatus + 0x1b8))
                      (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x1c0));
    if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x68) == 0)) goto LAB_7ffe9a4abb25;
    cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0x1e4,&plStackX_8,_DAT_7ffe9c935bd0);
    if (cVar3 != '\0') {
      puVar9 = (undefined *)
               (**(code **)(*(longlong *)playerStatus + 0x218))
                         (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x220));
      if (puVar9 == (undefined *)0x0) goto LAB_7ffe9a4abb25;
      puVar9 = GemCartBufferManager_GetGemCartBuffer(puVar9,0x3f0,(undefined *)0x0);
      iVar4 = iVar7;
      if (puVar9 != (undefined *)0x0) {
        iVar4 = GemCartBufferBase_GetValue(puVar9,(undefined *)0x2,(undefined *)0x0);
      }
      if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a4abb25;
      iVar6 = (**(code **)(*plStackX_8 + 0x178))(plStackX_8,0,*(undefined8 *)(*plStackX_8 + 0x180));
      cVar3 = FUN_7ffe9a8fea70(thisObject,100,iVar6 + iVar4);
      if (cVar3 != '\0') {
        if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a4abb25;
        iVar4 = (**(code **)(*plStackX_8 + 0x178))
                          (plStackX_8,8,*(undefined8 *)(*plStackX_8 + 0x180));
        fVar12 = fVar12 + (float)iVar4 / fVar2;
      }
    }
  }
  iVar4 = (**(code **)(*(longlong *)thisObject + 0x198))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
  if (iVar4 == 2) {
    lVar8 = (**(code **)(*(longlong *)playerStatus + 0x1b8))
                      (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x1c0));
    if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x68) == 0)) goto LAB_7ffe9a4abb25;
    cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0x1e5,&plStackX_8,_DAT_7ffe9c935bd0);
    if (cVar3 != '\0') {
      puVar9 = (undefined *)
               (**(code **)(*(longlong *)playerStatus + 0x218))
                         (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x220));
      if (puVar9 == (undefined *)0x0) goto LAB_7ffe9a4abb25;
      puVar9 = GemCartBufferManager_GetGemCartBuffer(puVar9,0x3f1,(undefined *)0x0);
      if (puVar9 != (undefined *)0x0) {
        iVar7 = GemCartBufferBase_GetValue(puVar9,(undefined *)0x2,(undefined *)0x0);
      }
      if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a4abb25;
      iVar4 = (**(code **)(*plStackX_8 + 0x178))(plStackX_8,0,*(undefined8 *)(*plStackX_8 + 0x180));
      cVar3 = FUN_7ffe9a8fea70(thisObject,100,iVar4 + iVar7);
      if (cVar3 != '\0') {
        if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a4abb25;
        iVar7 = (**(code **)(*plStackX_8 + 0x178))
                          (plStackX_8,8,*(undefined8 *)(*plStackX_8 + 0x180));
        fVar12 = fVar12 + (float)iVar7 / fVar2;
      }
    }
  }
  if (iVar5 == 1) {
    if (1 < *(int *)(thisObject + 0xfc) - 10U) {
      return fVar12;
    }
    lVar8 = (**(code **)(*(longlong *)playerStatus + 0x1b8))
                      (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x1c0));
    if ((lVar8 == 0) || (lVar8 = *(longlong *)(lVar8 + 0x68), lVar8 == 0)) goto LAB_7ffe9a4abb25;
    uVar10 = 0x28;
LAB_7ffe9a4ab9bd:
    cVar3 = FUN_7ffe9ad8e670(lVar8,uVar10,&plStackX_8,_DAT_7ffe9c935bd0);
    bVar11 = cVar3 == '\0';
LAB_7ffe9a4ab9c4:
    if (bVar11) {
      return fVar12;
    }
  }
  else {
    if (iVar5 == 4) {
      if ((*(int *)(thisObject + 0xfc) != 0x10) && (*(int *)(thisObject + 0x100) != 0x10)) {
        return fVar12;
      }
      lVar8 = (**(code **)(*(longlong *)playerStatus + 0x1b8))
                        (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x1c0));
      if ((lVar8 == 0) || (lVar8 = *(longlong *)(lVar8 + 0x68), lVar8 == 0)) goto LAB_7ffe9a4abb25;
      uVar10 = 0x8b;
      goto LAB_7ffe9a4ab9bd;
    }
    if (iVar5 != 0x1e) {
      return fVar12;
    }
    lVar8 = (**(code **)(*(longlong *)playerStatus + 0x1b8))
                      (playerStatus,*(undefined8 *)(*(longlong *)playerStatus + 0x1c0));
    if ((lVar8 == 0) || (*(longlong *)(lVar8 + 0x68) == 0)) goto LAB_7ffe9a4abb25;
    cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar8 + 0x68),0x3d2,&plStackX_8,_DAT_7ffe9c935bd0);
    if (cVar3 == '\0') {
      return fVar12;
    }
    iVar5 = (**(code **)(*(longlong *)thisObject + 0x188))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
    if (iVar5 != 0xf) {
      bVar11 = (int)attackType == 2;
      goto LAB_7ffe9a4ab9c4;
    }
    if ((*(byte *)(*(longlong *)thisObject + 0x130) < *(byte *)(_DAT_7ffe9c9635d8 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)thisObject + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c9635d8 + 0x130) * 8) != _DAT_7ffe9c9635d8)) {
      FUN_7ffe9996c950(thisObject);
      pcVar1 = (code *)swi(3);
      fVar12 = (float)(*pcVar1)();
      return fVar12;
    }
    if (thisObject[0x120] != '\0') {
      return fVar12;
    }
  }
  if (plStackX_8 != (longlong *)0x0) {
    iVar5 = (**(code **)(*plStackX_8 + 0x178))(plStackX_8,8,*(undefined8 *)(*plStackX_8 + 0x180));
    return fVar12 + (float)iVar5 / fVar2;
  }
LAB_7ffe9a4abb25:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  fVar12 = (float)(*pcVar1)();
  return fVar12;
}

