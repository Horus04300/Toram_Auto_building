
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a68cb) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a68dd) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a68eb) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a692e) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a681a) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a6830) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a6842) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a6925) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a6761) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a6777) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a6789) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a6937) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a6669) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a65e0) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a6614) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a6634) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a6641) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a665b) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a6692) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a66b1) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a66d1) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a66de) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a66f8) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a6706) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a6731) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a6747) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a674a) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a6792) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a67be) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a67de) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a67eb) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a6805) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a684b) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a6858) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a6877) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a6897) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a68a0) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a68ba) */
/* WARNING: Removing unreachable block (ram,0x7ffe9a8a68f0) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GameManager_ReceivePlayerAttackStart
               (undefined *thisObject,undefined *archetypeType,int archetypeId,undefined *response,
               undefined *methodInfo)

{
  short sVar1;
  float fVar2;
  float fVar3;
  undefined8 uVar4;
  code *pcVar5;
  bool bVar6;
  char cVar7;
  undefined4 uVar8;
  int iVar9;
  longlong *plVar10;
  undefined *puVar11;
  undefined8 uVar12;
  longlong lVar13;
  longlong lVar14;
  undefined8 *puVar15;
  longlong *plVar16;
  longlong *plVar17;
  undefined8 uStack_58;
  undefined8 uStack_48;
  undefined8 uStack_38;
  float fStack_30;
  
  if (DAT_7ffe9cadfc47 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c907f28);
    FUN_7ffe9996d590(&DAT_7ffe9c9375f8);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c9228b0);
    FUN_7ffe9996d590(&DAT_7ffe9c956938);
    FUN_7ffe9996d590(&DAT_7ffe9c955028);
    FUN_7ffe9996d590(&DAT_7ffe9c93f9c0);
    FUN_7ffe9996d590(&DAT_7ffe9c94aab0);
    DAT_7ffe9cadfc47 = '\x01';
  }
  puVar11 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c94aab0);
  GemCartMasterData__ctor(puVar11,(undefined *)0x0);
  fVar2 = fStack_30;
  if (puVar11 == (undefined *)0x0) goto LAB_7ffe9a8ce02b;
  plVar10 = (longlong *)0x0;
  *(int *)(puVar11 + 0x10) = archetypeId;
  lVar13 = *(longlong *)(thisObject + 0x70);
  plVar17 = (longlong *)0x0;
  if ((int)archetypeType == 0) {
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar7 = FUN_7ffe9bda2160(lVar13,0);
    fVar2 = fStack_30;
    if (cVar7 == '\0') {
      if (response == (undefined *)0x0) goto LAB_7ffe9a8ce02b;
    }
    else {
      if (*(longlong *)(thisObject + 0x70) == 0) goto LAB_7ffe9a8ce02b;
      plVar17 = (longlong *)FUN_7ffe9a47fe30(*(longlong *)(thisObject + 0x70),0);
      fVar2 = fStack_30;
      if (((*(longlong *)(thisObject + 0x70) == 0) ||
          (puVar11 = (undefined *)FUN_7ffe9a47f780(*(longlong *)(thisObject + 0x70),0),
          fVar2 = fStack_30, puVar11 == (undefined *)0x0)) ||
         (plVar16 = (longlong *)GemCartBufferManager_GetGemCartBuffer(puVar11,0x23,(undefined *)0x0)
         , fVar2 = fStack_30, response == (undefined *)0x0)) goto LAB_7ffe9a8ce02b;
      if (plVar16 != (longlong *)0x0) {
        if ((*(byte *)(*plVar16 + 0x130) < *(byte *)(_DAT_7ffe9c955028 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar16 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c955028 + 0x130) * 8) != _DAT_7ffe9c955028)) {
          FUN_7ffe9996c950(plVar16);
          pcVar5 = (code *)swi(3);
          (*pcVar5)();
          return;
        }
        GemCartBuffer_StartDashBuff_Synchronization
                  ((undefined *)plVar16,*(short *)(response + 0x40),(undefined *)0x0);
      }
      if (*(int *)(response + 0x44) != 0) {
        lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
        uVar8 = *(undefined4 *)(response + 0x44);
        fVar2 = fStack_30;
        if ((*(longlong *)(thisObject + 0x70) == 0) ||
           (lVar14 = FUN_7ffe9a480940(*(longlong *)(thisObject + 0x70),0), fVar2 = fStack_30,
           lVar14 == 0)) goto LAB_7ffe9a8ce02b;
        puVar15 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_38,lVar14,0);
        uVar4 = *puVar15;
        fStack_30 = *(float *)(puVar15 + 1);
        if (DAT_7ffe9cad9cac == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
          DAT_7ffe9cad9cac = '\x01';
        }
        uStack_58._0_4_ = (float)uVar4;
        uStack_58._4_4_ = (float)((ulonglong)uVar4 >> 0x20);
        uStack_38 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x18);
        fVar2 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x20);
        fStack_30 = fStack_30 + fVar2;
        uStack_48 = CONCAT44(uStack_58._4_4_ + (float)((ulonglong)uStack_38 >> 0x20),
                             (float)uStack_58 + (float)uStack_38);
        if (lVar13 == 0) goto LAB_7ffe9a8ce02b;
        uStack_38 = uStack_48;
        FUN_7ffe99caa840(lVar13,uVar8,&uStack_38,0);
      }
      if (*(short *)(response + 0x48) != 0) {
        lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
        sVar1 = *(short *)(response + 0x48);
        fVar2 = fStack_30;
        if ((*(longlong *)(thisObject + 0x70) == 0) ||
           (lVar14 = FUN_7ffe9a480940(*(longlong *)(thisObject + 0x70),0), fVar2 = fStack_30,
           lVar14 == 0)) goto LAB_7ffe9a8ce02b;
        puVar15 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_38,lVar14,0);
        uVar4 = *puVar15;
        fVar3 = *(float *)(puVar15 + 1);
        if (DAT_7ffe9cad9cac == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
          DAT_7ffe9cad9cac = '\x01';
        }
        uStack_48._0_4_ = (float)uVar4;
        uStack_48._4_4_ = (float)((ulonglong)uVar4 >> 0x20);
        uStack_38 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x18);
        fVar2 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x20);
        fStack_30 = fVar3 + fVar2;
        uStack_58 = CONCAT44(uStack_48._4_4_ + (float)((ulonglong)uStack_38 >> 0x20),
                             (float)uStack_48 + (float)uStack_38);
        if (lVar13 == 0) goto LAB_7ffe9a8ce02b;
        uStack_38 = uStack_58;
        FUN_7ffe99caa960(lVar13,(int)sVar1,&uStack_38,0);
      }
    }
    if ((*(longlong *)(response + 0x50) != 0) &&
       (cVar7 = FUN_7ffe9bc60070(*(longlong *)(response + 0x50),0x38,0), cVar7 != '\0')) {
      lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
      fVar2 = fStack_30;
      if ((*(longlong *)(response + 0x50) == 0) ||
         ((uVar8 = FUN_7ffe9bc601e0(*(longlong *)(response + 0x50),0x38,0), fVar2 = fStack_30,
          plVar17 == (longlong *)0x0 ||
          (lVar14 = FUN_7ffe9bd98a10(plVar17,0), fVar2 = fStack_30, lVar14 == 0))))
      goto LAB_7ffe9a8ce02b;
      puVar15 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_38,lVar14,0);
      uVar4 = *puVar15;
      fVar3 = *(float *)(puVar15 + 1);
      if (DAT_7ffe9cad9cac == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
        DAT_7ffe9cad9cac = '\x01';
      }
      uStack_48._0_4_ = (float)uVar4;
      uStack_48._4_4_ = (float)((ulonglong)uVar4 >> 0x20);
      uStack_38 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x18);
      fVar2 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x20);
      fStack_30 = fVar3 + fVar2;
      uStack_58 = CONCAT44(uStack_48._4_4_ + (float)((ulonglong)uStack_38 >> 0x20),
                           (float)uStack_48 + (float)uStack_38);
      if (lVar13 == 0) goto LAB_7ffe9a8ce02b;
      uStack_38 = uStack_58;
      FUN_7ffe99caa840(lVar13,uVar8,&uStack_38,0);
    }
  }
  else {
    if ((lVar13 == 0) || (*(longlong *)(lVar13 + 0x70) == 0)) goto LAB_7ffe9a8ce02b;
    uVar4 = *(undefined8 *)(*(longlong *)(lVar13 + 0x70) + 0x10);
    uVar12 = func_0x7ffe99940040(_DAT_7ffe9c9375f8);
    FUN_7ffe9af13420(uVar12,puVar11,_DAT_7ffe9c93f9c0,0);
    lVar13 = FUN_7ffe9ab854c0(uVar4,uVar12,_DAT_7ffe9c907f28);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar7 = FUN_7ffe9bda20c0(lVar13,0);
    plVar17 = plVar10;
    if (cVar7 != '\0') {
      fVar2 = fStack_30;
      if (lVar13 == 0) goto LAB_7ffe9a8ce02b;
      plVar17 = (longlong *)FUN_7ffe9a4ca6d0(lVar13,0);
    }
  }
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar7 = FUN_7ffe9bda2160(plVar17,0,0);
  if (cVar7 != '\0') {
    fVar2 = fStack_30;
    if (((plVar17 == (longlong *)0x0) || (plVar17[6] == 0)) ||
       (plVar16 = *(longlong **)(plVar17[6] + 0x30), plVar16 == (longlong *)0x0))
    goto LAB_7ffe9a8ce02b;
    plVar16 = (longlong *)(**(code **)(*plVar16 + 0x188))(plVar16,*(undefined8 *)(*plVar16 + 400));
    if (plVar16 != (longlong *)0x0) {
      if ((*(byte *)(*plVar16 + 0x130) < *(byte *)(_DAT_7ffe9c9228b0 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar16 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c9228b0 + 0x130) * 8
           ) != _DAT_7ffe9c9228b0)) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      if (bVar6) {
        plVar10 = plVar16;
      }
    }
    cVar7 = FUN_7ffe9a8fecd0(plVar10,0,0);
    if (cVar7 != '\0') {
      fVar2 = fStack_30;
      if ((plVar10 == (longlong *)0x0) ||
         (iVar9 = (**(code **)(*plVar10 + 0x188))(plVar10,*(undefined8 *)(*plVar10 + 400)),
         fVar2 = fStack_30, response == (undefined *)0x0)) goto LAB_7ffe9a8ce02b;
      if (iVar9 == *(short *)(response + 0x28)) {
        (**(code **)(*plVar10 + 0x638))
                  (plVar10,*(undefined4 *)(response + 0x30),*(undefined4 *)(response + 0x2c),
                   *(undefined8 *)(*plVar10 + 0x640));
      }
      goto FUN_7ffe9a8a64e0;
    }
  }
  fVar2 = fStack_30;
  if (response != (undefined *)0x0) {
FUN_7ffe9a8a64e0:
    uVar8 = *(undefined4 *)(response + 0x30);
    if (DAT_7ffe9cadfc4c == '\0') {
      FUN_7ffe9996d590(&DAT_7ffe9c95a4e0,uVar8,plVar17,0);
      FUN_7ffe9996d590(&DAT_7ffe9c960fa0);
      FUN_7ffe9996d590(&DAT_7ffe9c934418);
      FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
      FUN_7ffe9996d590(&DAT_7ffe9c961750);
      DAT_7ffe9cadfc4c = '\x01';
    }
    if (((char)uVar8 < '\0') &&
       ((((plVar17 == (longlong *)0x0 ||
          (plVar10 = (longlong *)
                     (**(code **)(*plVar17 + 0x298))(plVar17,*(undefined8 *)(*plVar17 + 0x2a0)),
          plVar10 == (longlong *)0x0)) ||
         (lVar13 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
         lVar13 == 0)) ||
        ((*(longlong *)(lVar13 + 0x40) == 0 ||
         (cVar7 = FUN_7ffe9ad8e670(*(longlong *)(lVar13 + 0x40),0x441,&stack0xffffffffffffffd8,
                                   _DAT_7ffe9c934418), cVar7 != '\0')))))) {
      FUN_7ffe9996d7a0();
      pcVar5 = (code *)swi(3);
      (*pcVar5)();
      return;
    }
    return;
  }
LAB_7ffe9a8ce02b:
  fStack_30 = fVar2;
  FUN_7ffe9996d7a0();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}

