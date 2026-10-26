
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte PlayerAttackBase_CheckHit
               (undefined *self,undefined *status,int needHit,int mp,byte isFlash,undefined *correct
               ,undefined *methodInfo)

{
  longlong *plVar1;
  code *pcVar2;
  bool bVar3;
  float fVar4;
  byte bVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  longlong lVar11;
  undefined *puVar12;
  longlong *aplStack_38 [2];
  
  if (DAT_7ffe9caddeba == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    DAT_7ffe9caddeba = '\x01';
  }
  if ((status == (undefined *)0x0) ||
     (lVar11 = (**(code **)(*(longlong *)status + 0x1a8))
                         (status,*(undefined8 *)(*(longlong *)status + 0x1b0)), lVar11 == 0)) {
LAB_7ffe9a4aca96:
    FUN_7ffe9996d7a0();
    pcVar2 = (code *)swi(3);
    bVar5 = (*pcVar2)();
    return bVar5;
  }
  iVar10 = FUN_7ffe99742ec0(0x11,_DAT_7ffe9c940d40,lVar11);
  iVar10 = (mp / 100 + 10) * 10 - (int)((float)(needHit - iVar10) / _DAT_7ffe9c049b74);
  if (100 < iVar10) {
    iVar10 = 100;
  }
  lVar11 = (**(code **)(*(longlong *)status + 0x1e8))
                     (status,*(undefined8 *)(*(longlong *)status + 0x1f0));
  if (lVar11 == 0) goto LAB_7ffe9a4aca96;
  cVar6 = FUN_7ffe9a4daa60(lVar11,7);
  if (cVar6 != '\0') {
    fVar4 = _DAT_7ffe9c049db0;
    if (_DAT_7ffe9c049b7c < *(float *)(self + 0x20) || _DAT_7ffe9c049b7c == *(float *)(self + 0x20))
    {
      fVar4 = _DAT_7ffe9c049e50;
    }
    iVar10 = (int)((float)iVar10 * fVar4);
  }
  if (DAT_7ffe9caddebb == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c903268);
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    FUN_7ffe9996d590(&DAT_7ffe9c968e08);
    DAT_7ffe9caddebb = '\x01';
  }
  aplStack_38[0] = (longlong *)0x0;
  *correct = 1;
  if (((status == (undefined *)0x0) ||
      (lVar11 = (**(code **)(*(longlong *)status + 0x1f8))
                          (status,*(undefined8 *)(*(longlong *)status + 0x200)), lVar11 == 0)) ||
     (plVar1 = *(longlong **)(lVar11 + 0x18), plVar1 == (longlong *)0x0)) goto LAB_7ffe9a4ac1b1;
  (**(code **)(*plVar1 + 0x1d8))(plVar1,&stack0x00000010,*(undefined8 *)(*plVar1 + 0x1e0));
  iVar7 = FUN_7ffe9bda4580(0,100,0);
  if (isFlash != 0) {
    if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    iVar10 = func_0x7ffe9b506b70(iVar10,0,0);
  }
  iVar8 = 0;
  lVar11 = (**(code **)(*(longlong *)status + 0x1c8))
                     (status,*(undefined8 *)(*(longlong *)status + 0x1d0));
  if (lVar11 == 0) goto LAB_7ffe9a4ac1b1;
  cVar6 = FUN_7ffe9a7cbb30(lVar11,0x3d3,aplStack_38,0);
  if (cVar6 != '\0') {
    lVar11 = (**(code **)(*(longlong *)status + 0x1f8))
                       (status,*(undefined8 *)(*(longlong *)status + 0x200));
    if (lVar11 == 0) goto LAB_7ffe9a4ac1b1;
    lVar11 = FUN_7ffe99c090e0(lVar11,0);
    if ((lVar11 != 0) && (*(int *)(lVar11 + 0x38) == 9)) {
      if (aplStack_38[0] == (longlong *)0x0) goto LAB_7ffe9a4ac1b1;
      if (((*(byte *)(*aplStack_38[0] + 0x130) < *(byte *)(_DAT_7ffe9c968e08 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*aplStack_38[0] + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7ffe9c968e08 + 0x130) * 8) != _DAT_7ffe9c968e08)) ||
         (aplStack_38[0] == (longlong *)0x0)) {
        FUN_7ffe9996c950(aplStack_38[0]);
        pcVar2 = (code *)swi(3);
        bVar5 = (*pcVar2)();
        return bVar5;
      }
      iVar8 = func_0x7ffe9a7a51f0(aplStack_38[0],0);
    }
  }
  lVar11 = (**(code **)(*(longlong *)status + 0x218))
                     (status,*(undefined8 *)(*(longlong *)status + 0x220));
  if (lVar11 == 0) goto LAB_7ffe9a4ac1b1;
  lVar11 = FUN_7ffe9a5b23a0(lVar11,0xf,0);
  if ((lVar11 != 0) && (iVar9 = FUN_7ffe9a5af330(lVar11,2), iVar9 != 0)) {
    iVar8 = 100;
  }
  if (iVar7 < iVar10) {
LAB_7ffe9a4ac1aa:
    *correct = 0;
  }
  else {
    if (iVar8 <= iVar7) {
      lVar11 = (**(code **)(*(longlong *)status + 0x208))
                         (status,*(undefined8 *)(*(longlong *)status + 0x210));
      if (lVar11 == 0) goto LAB_7ffe9a4ac1b1;
      cVar6 = FUN_7ffe9a51e210(lVar11,0x87,0);
      if (cVar6 != '\0') {
        lVar11 = (**(code **)(*(longlong *)status + 0x208))
                           (status,*(undefined8 *)(*(longlong *)status + 0x210));
        if (lVar11 == 0) goto LAB_7ffe9a4ac1b1;
        cVar6 = FUN_7ffe9a51e030(lVar11,0x87,0);
        if (cVar6 != '\0') goto LAB_7ffe9a4ac1aa;
      }
    }
    if (*(int *)(self + 0xd0) != 3) {
      return iVar7 < iVar8;
    }
    if ((*(byte *)(*(longlong *)self + 0x130) < *(byte *)(_DAT_7ffe9c903268 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)self + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c903268 + 0x130) * 8) != _DAT_7ffe9c903268)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    puVar12 = (undefined *)0x0;
    if (bVar3) {
      puVar12 = self;
    }
    cVar6 = FUN_7ffe9a8fecd0(puVar12,0,0);
    if (cVar6 != '\0') {
      if (puVar12 == (undefined *)0x0) {
LAB_7ffe9a4ac1b1:
        FUN_7ffe9996d7a0();
        pcVar2 = (code *)swi(3);
        bVar5 = (*pcVar2)();
        return bVar5;
      }
      if (puVar12[0x154] == '\0') {
        return iVar7 < iVar8;
      }
    }
  }
  return 1;
}

