
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

float GemCartBufferManager_GetRecieveDamageRate
                (undefined *self,undefined *status,undefined *damageTrans,undefined *mobAttack,
                undefined *methodInfo)

{
  undefined8 uVar1;
  float fVar2;
  code *pcVar3;
  char cVar4;
  int iVar5;
  longlong *plVar6;
  longlong lVar7;
  undefined8 *puVar8;
  float fVar9;
  float fVar10;
  uint uVar11;
  longlong *plStackX_8;
  float fStack_88;
  float fStack_84;
  undefined8 uStack_78;
  float fStack_70;
  undefined8 uStack_68;
  float fStack_60;
  undefined1 auStack_58 [8];
  float fStack_50;
  
  if (DAT_7ffe9cade79c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9658b0);
    FUN_7ffe9996d590(&DAT_7ffe9c94aec0);
    FUN_7ffe9996d590(&DAT_7ffe9c94af80);
    FUN_7ffe9996d590(&DAT_7ffe9c96a4e0);
    FUN_7ffe9996d590(&DAT_7ffe9c8edca8);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c920330);
    FUN_7ffe9996d590(&DAT_7ffe9c923468);
    DAT_7ffe9cade79c = '\x01';
  }
  fVar9 = GemCartBufferManager_GetBufferValue(self,(undefined *)0x0,(undefined *)0x0);
  fVar10 = GemCartBufferManager_GetBufferValue(self,(undefined *)0x1,(undefined *)0x0);
  fVar10 = (fVar9 + 0.0) - fVar10;
  plStackX_8 = (longlong *)0x0;
  if (*(longlong *)(self + 0x18) == 0) goto LAB_7ffe9a5b2d4f;
  cVar4 = FUN_7ffe9ad1e480(*(longlong *)(self + 0x18),0x1c,&plStackX_8,_DAT_7ffe9c9658b0);
  if (cVar4 != '\0') {
    if (status == (undefined *)0x0) goto LAB_7ffe9a5b2d4f;
    plVar6 = (longlong *)
             (**(code **)(*(longlong *)status + 0x198))
                       (status,*(undefined8 *)(*(longlong *)status + 0x1a0));
    if (plVar6 != (longlong *)0x0) {
      if ((*(byte *)(_DAT_7ffe9c923468 + 0x130) <= *(byte *)(*plVar6 + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(*plVar6 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c923468 + 0x130) * 8)
          == _DAT_7ffe9c923468)) {
        if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a5b2d4f;
        iVar5 = GemCartBufferBase_GetValue
                          ((undefined *)plStackX_8,(undefined *)0x1,(undefined *)0x0);
        fVar10 = fVar10 + (float)iVar5;
        goto LAB_7ffe9a5b27d3;
      }
    }
    plVar6 = (longlong *)
             (**(code **)(*(longlong *)status + 0x198))
                       (status,*(undefined8 *)(*(longlong *)status + 0x1a0));
    if (plVar6 != (longlong *)0x0) {
      if ((*(byte *)(_DAT_7ffe9c920330 + 0x130) <= *(byte *)(*plVar6 + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(*plVar6 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c920330 + 0x130) * 8)
          == _DAT_7ffe9c920330)) {
        if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a5b2d4f;
        iVar5 = GemCartBufferBase_GetValue
                          ((undefined *)plStackX_8,(undefined *)0x0,(undefined *)0x0);
        fVar10 = fVar10 - (float)iVar5;
      }
    }
  }
LAB_7ffe9a5b27d3:
  if (*(longlong *)(self + 0x18) == 0) goto LAB_7ffe9a5b2d4f;
  cVar4 = FUN_7ffe9ad1e480(*(longlong *)(self + 0x18),0x27,&plStackX_8,_DAT_7ffe9c9658b0);
  plVar6 = plStackX_8;
  if (cVar4 != '\0') {
    if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a5b2d4f;
    iVar5 = (**(code **)(*plStackX_8 + 0x1d8))(plStackX_8,1,*(undefined8 *)(*plStackX_8 + 0x1e0));
    if ((iVar5 == 0) || (0.0 < *(float *)(plVar6 + 2))) {
LAB_7ffe9a5b285a:
      iVar5 = 0;
    }
    else {
      cVar4 = (**(code **)(*plVar6 + 0x1c8))(plVar6,*(undefined8 *)(*plVar6 + 0x1d0));
      if (cVar4 == '\0') goto LAB_7ffe9a5b285a;
    }
    fVar9 = (float)iVar5;
    fVar10 = fVar10 + fVar9;
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar4 = FUN_7ffe9bda2160(damageTrans,0,0);
    if (cVar4 != '\0') {
      lVar7 = FUN_7ffe9bd7a830(0);
      if (lVar7 == 0) goto LAB_7ffe9a5b2d4f;
      lVar7 = FUN_7ffe9bd98a10(lVar7,0);
      if (lVar7 == 0) goto LAB_7ffe9a5b2d4f;
      puVar8 = (undefined8 *)FUN_7ffe9bdbf190(auStack_58,lVar7,0);
      uStack_78 = *puVar8;
      fStack_70 = *(float *)(puVar8 + 1);
      if (damageTrans == (undefined *)0x0) goto LAB_7ffe9a5b2d4f;
      puVar8 = (undefined8 *)FUN_7ffe9bdbf710(auStack_58,damageTrans,0);
      uVar1 = *puVar8;
      fVar2 = *(float *)(puVar8 + 1);
      if (*(longlong *)(self + 0x10) == 0) goto LAB_7ffe9a5b2d4f;
      lVar7 = FUN_7ffe9a480940(*(longlong *)(self + 0x10),0);
      if (lVar7 == 0) goto LAB_7ffe9a5b2d4f;
      puVar8 = (undefined8 *)FUN_7ffe9bdbf710(auStack_58,lVar7,0);
      fStack_84 = (float)((ulonglong)uVar1 >> 0x20);
      fStack_88 = (float)uVar1;
      fStack_60 = fVar2 - *(float *)(puVar8 + 1);
      fStack_70 = fStack_70 * _DAT_7ffe9c049b90;
      uStack_68 = CONCAT44(fStack_84 - (float)((ulonglong)*puVar8 >> 0x20),
                           fStack_88 - (float)*puVar8);
      uStack_78 = CONCAT44(uStack_78._4_4_ * _DAT_7ffe9c049b90,(float)uStack_78 * _DAT_7ffe9c049b90)
      ;
      fStack_50 = fStack_70;
      uVar11 = FUN_7ffe99a4ef70(&uStack_78,&uStack_68,0);
      if (((float)(uVar11 & _DAT_7ffe9c049bf0) < _DAT_7ffe9c049d70) &&
         (fVar10 = fVar10 - fVar9, (float)(uVar11 & _DAT_7ffe9c049bf0) < _DAT_7ffe9c049dd8)) {
        fVar10 = fVar10 - fVar9;
      }
    }
  }
  if (*(longlong *)(self + 0x18) == 0) goto LAB_7ffe9a5b2d4f;
  FUN_7ffe9ad1e480(*(longlong *)(self + 0x18),0x2e,&plStackX_8,_DAT_7ffe9c9658b0);
  if (*(longlong *)(self + 0x18) == 0) goto LAB_7ffe9a5b2d4f;
  cVar4 = FUN_7ffe9ad1e480(*(longlong *)(self + 0x18),0x49,&plStackX_8,_DAT_7ffe9c9658b0);
  if (cVar4 != '\0') {
    if (status == (undefined *)0x0) goto LAB_7ffe9a5b2d4f;
    plVar6 = (longlong *)
             (**(code **)(*(longlong *)status + 0x1a8))
                       (status,*(undefined8 *)(*(longlong *)status + 0x1b0));
    if (plVar6 != (longlong *)0x0) {
      if ((*(byte *)(_DAT_7ffe9c96a4e0 + 0x130) <= *(byte *)(*plVar6 + 0x130)) &&
         (*(longlong *)
           (*(longlong *)(*plVar6 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c96a4e0 + 0x130) * 8)
          == _DAT_7ffe9c96a4e0)) {
        plVar6 = (longlong *)
                 (**(code **)(*(longlong *)status + 0x1a8))
                           (status,*(undefined8 *)(*(longlong *)status + 0x1b0));
        if (plVar6 == (longlong *)0x0) goto LAB_7ffe9a5b2d4f;
        if ((*(byte *)(*plVar6 + 0x130) < *(byte *)(_DAT_7ffe9c96a4e0 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar6 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c96a4e0 + 0x130) * 8) != _DAT_7ffe9c96a4e0)) {
          FUN_7ffe9996c950(plVar6,_DAT_7ffe9c96a4e0);
          pcVar3 = (code *)swi(3);
          fVar9 = (float)(*pcVar3)();
          return fVar9;
        }
        if ((int)plVar6[2] == 2) {
          if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a5b2d4f;
          iVar5 = GemCartBufferBase_GetValue
                            ((undefined *)plStackX_8,(undefined *)0x2,(undefined *)0x0);
          fVar10 = fVar10 - (float)iVar5;
        }
      }
    }
  }
  if (*(longlong *)(self + 0x18) == 0) goto LAB_7ffe9a5b2d4f;
  cVar4 = FUN_7ffe9ad1e480(*(longlong *)(self + 0x18),0x4a,&plStackX_8,_DAT_7ffe9c9658b0);
  fVar9 = _DAT_7ffe9c049ce4;
  if (cVar4 == '\0') goto LAB_7ffe9a5b2bd4;
  if (mobAttack == (undefined *)0x0) goto LAB_7ffe9a5b2d4f;
  if ((*(byte *)(*(longlong *)mobAttack + 0x130) < *(byte *)(_DAT_7ffe9c8edca8 + 0x130)) ||
     (*(longlong *)
       (*(longlong *)(*(longlong *)mobAttack + 200) + -8 +
       (ulonglong)*(byte *)(_DAT_7ffe9c8edca8 + 0x130) * 8) != _DAT_7ffe9c8edca8)) {
    plVar6 = *(longlong **)(mobAttack + 0xa8);
    if (plVar6 != (longlong *)0x0) {
      cVar4 = (**(code **)(*plVar6 + 0x228))(plVar6,*(undefined8 *)(*plVar6 + 0x230));
      if (cVar4 != '\0') {
        cVar4 = FUN_7ffe9a327690(*(undefined8 *)(mobAttack + 0xa0),0);
        if (cVar4 != '\0') {
          if (plStackX_8 == (longlong *)0x0) goto LAB_7ffe9a5b2d4f;
          iVar5 = GemCartBufferBase_GetValue
                            ((undefined *)plStackX_8,(undefined *)0x2,(undefined *)0x0);
          fVar10 = fVar10 - (float)iVar5;
          goto LAB_7ffe9a5b2bd4;
        }
      }
      cVar4 = FUN_7ffe9a327640(*(undefined8 *)(mobAttack + 0xa0),0);
      if (cVar4 != '\0') goto LAB_7ffe9a5b2bd0;
    }
  }
  else {
LAB_7ffe9a5b2bd0:
    fVar10 = fVar10 + fVar9;
  }
LAB_7ffe9a5b2bd4:
  if (*(longlong *)(self + 0x18) == 0) goto LAB_7ffe9a5b2d4f;
  cVar4 = FUN_7ffe9ad1e480(*(longlong *)(self + 0x18),0x4b,&plStackX_8,_DAT_7ffe9c9658b0);
  if (cVar4 == '\0') goto LAB_7ffe9a5b2d1b;
  if (mobAttack == (undefined *)0x0) goto LAB_7ffe9a5b2d4f;
  if ((*(byte *)(*(longlong *)mobAttack + 0x130) < *(byte *)(_DAT_7ffe9c8edca8 + 0x130)) ||
     (*(longlong *)
       (*(longlong *)(*(longlong *)mobAttack + 200) + -8 +
       (ulonglong)*(byte *)(_DAT_7ffe9c8edca8 + 0x130) * 8) != _DAT_7ffe9c8edca8)) {
    plVar6 = *(longlong **)(mobAttack + 0xa8);
    if (plVar6 == (longlong *)0x0) goto LAB_7ffe9a5b2d1b;
    cVar4 = (**(code **)(*plVar6 + 0x228))(plVar6,*(undefined8 *)(*plVar6 + 0x230));
    if (cVar4 != '\0') {
      cVar4 = FUN_7ffe9a327510(*(undefined8 *)(mobAttack + 0xa0),0);
      if (cVar4 != '\0') {
        plVar6 = *(longlong **)(mobAttack + 0xa8);
        if (plVar6 != (longlong *)0x0) {
          if ((*(byte *)(*plVar6 + 0x130) < *(byte *)(_DAT_7ffe9c94aec0 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(*plVar6 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c94aec0 + 0x130) * 8) != _DAT_7ffe9c94aec0)) {
            if ((*(byte *)(*plVar6 + 0x130) < *(byte *)(_DAT_7ffe9c94af80 + 0x130)) ||
               (*(longlong *)
                 (*(longlong *)(*plVar6 + 200) + -8 +
                 (ulonglong)*(byte *)(_DAT_7ffe9c94af80 + 0x130) * 8) != _DAT_7ffe9c94af80))
            goto LAB_7ffe9a5b2ce3;
          }
          if (plVar6[2] == 0) goto LAB_7ffe9a5b2d4f;
          iVar5 = FUN_7ffe9a328210(plVar6[2],0);
          if (iVar5 != 0) goto LAB_7ffe9a5b2d1b;
        }
LAB_7ffe9a5b2ce3:
        if (plStackX_8 == (longlong *)0x0) {
LAB_7ffe9a5b2d4f:
          FUN_7ffe9996d7a0();
          pcVar3 = (code *)swi(3);
          fVar9 = (float)(*pcVar3)();
          return fVar9;
        }
        iVar5 = GemCartBufferBase_GetValue
                          ((undefined *)plStackX_8,(undefined *)0x2,(undefined *)0x0);
        fVar10 = fVar10 - (float)iVar5;
        goto LAB_7ffe9a5b2d1b;
      }
    }
    cVar4 = FUN_7ffe9a327640(*(undefined8 *)(mobAttack + 0xa0),0);
    if (cVar4 == '\0') goto LAB_7ffe9a5b2d1b;
  }
  fVar10 = fVar10 + fVar9;
LAB_7ffe9a5b2d1b:
  return fVar10 / _DAT_7ffe9c049cfc;
}

