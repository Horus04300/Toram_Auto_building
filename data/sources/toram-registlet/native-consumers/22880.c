
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void FloatingKickAction_ActionPreparation
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  float fVar1;
  code *pcVar2;
  bool bVar3;
  float fVar4;
  char cVar5;
  byte bVar6;
  undefined4 uVar7;
  int iVar8;
  undefined8 uVar9;
  longlong lVar10;
  ulonglong *puVar11;
  longlong lVar12;
  undefined8 *puVar13;
  longlong *plVar14;
  undefined *thisObject_00;
  longlong *plVar15;
  uint uVar16;
  float fVar17;
  float fStackX_10;
  float fStackX_14;
  longlong lStackX_18;
  ulonglong uStack_88;
  float fStack_80;
  undefined8 uStack_78;
  float fStack_70;
  ulonglong uStack_68;
  float fStack_60;
  
  if (DAT_7ffe9cadebd6 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f3938);
    FUN_7ffe9996d590(&DAT_7ffe9c943090);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c9499a8);
    FUN_7ffe9996d590(&DAT_7ffe9c962758);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c9530b0);
    DAT_7ffe9cadebd6 = '\x01';
  }
  lStackX_18 = 0;
  FUN_7ffe9a4a5ca0(thisObject,actarAction,target,0);
  cVar5 = func_0x7ffe9a4aea60(thisObject,0);
  if (cVar5 != '\0') {
    return;
  }
  *(undefined **)(thisObject + 0x138) = target;
  il2cpp_write_barrier_0();
  if (actarAction != (undefined *)0x0) {
    uVar9 = FUN_7ffe9ab6e260(actarAction,_DAT_7ffe9c943090);
    *(undefined8 *)(thisObject + 0x130) = uVar9;
    il2cpp_write_barrier_0();
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar5 = FUN_7ffe9bda2160(target,0,0);
    if (cVar5 != '\0') {
      lVar12 = *(longlong *)(thisObject + 0x130);
      if (((target == (undefined *)0x0) || (lVar10 = FUN_7ffe9bd9b890(target,0), lVar10 == 0)) ||
         (puVar11 = (ulonglong *)FUN_7ffe9bdbf710(&uStack_68,lVar10,0), lVar12 == 0))
      goto LAB_7ffe9a6494cc;
      uStack_88 = *puVar11;
      fStack_80 = *(float *)(puVar11 + 1);
      FUN_7ffe99b1df80(lVar12,&uStack_88,0);
    }
    lVar12 = FUN_7ffe9b141840(_DAT_7ffe9c9530b0);
    if (lVar12 != 0) {
      cVar5 = FUN_7ffe99ab28b0(lVar12,0);
      fVar1 = _DAT_7ffe9c049ce4;
      fVar4 = _DAT_7ffe9c049b1c;
      uVar16 = 1;
      if (cVar5 == '\0') {
        *(undefined4 *)(thisObject + 300) = 0;
      }
      else {
        uVar9 = FUN_7ffe99ab2b10(lVar12,0);
        lVar12 = FUN_7ffe9bd7a830(0);
        if ((lVar12 == 0) || (lVar12 = FUN_7ffe9bd98a10(lVar12,0), lVar12 == 0))
        goto LAB_7ffe9a6494cc;
        puVar11 = (ulonglong *)FUN_7ffe9bdbf760(&uStack_68,lVar12,0);
        uStack_88 = *puVar11;
        fStack_80 = *(float *)(puVar11 + 1);
        lVar12 = FUN_7ffe9bd7a830(0);
        if ((lVar12 == 0) || (lVar12 = FUN_7ffe9bd98a10(lVar12,0), lVar12 == 0))
        goto LAB_7ffe9a6494cc;
        puVar13 = (undefined8 *)FUN_7ffe9bdbf190(&uStack_68,lVar12,0);
        fStackX_14 = (float)((ulonglong)uVar9 >> 0x20);
        fStackX_10 = (float)uVar9;
        uStack_78 = *puVar13;
        fStack_70 = *(float *)(puVar13 + 1);
        fStack_60 = fStackX_14 * fStack_70 + fStackX_10 * fStack_80;
        *(ulonglong *)(thisObject + 0x140) =
             (ulonglong)(uint)(fStackX_14 * (float)uStack_78 + fStackX_10 * (float)uStack_88);
        *(float *)(thisObject + 0x148) = fStack_60;
        FUN_7ffe99a14ca0(thisObject + 0x140,0);
        if ((target == (undefined *)0x0) || (lVar12 = FUN_7ffe9bd9b890(target,0), lVar12 == 0))
        goto LAB_7ffe9a6494cc;
        puVar11 = (ulonglong *)FUN_7ffe9bdbf710(&uStack_68,lVar12,0);
        uStack_88 = *puVar11;
        fStack_80 = *(float *)(puVar11 + 1);
        lVar12 = FUN_7ffe9bd98a10(actarAction,0);
        if (lVar12 == 0) goto LAB_7ffe9a6494cc;
        puVar13 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_68,lVar12,0);
        uStack_78 = *puVar13;
        fStack_70 = *(float *)(puVar13 + 1);
        fStack_80 = fStack_80 - fStack_70;
        uStack_88 = (ulonglong)(uint)((float)uStack_88 - (float)uStack_78);
        FUN_7ffe99a14ca0(&uStack_88,0);
        uStack_78 = *(undefined8 *)(thisObject + 0x140);
        fStack_70 = *(float *)(thisObject + 0x148);
        uStack_68 = uStack_88;
        fStack_60 = fStack_80;
        fVar17 = (float)FUN_7ffe99a4ef70(&uStack_68,&uStack_78,0);
        if ((fVar17 < _DAT_7ffe9c049ddc) || (fVar4 < fVar17)) {
          if ((_DAT_7ffe9c049f38 < fVar17) || (fVar17 < _DAT_7ffe9c049c94)) {
            *(undefined4 *)(thisObject + 300) = 0;
          }
          else {
            *(undefined4 *)(thisObject + 300) = 1;
          }
        }
        else {
          *(undefined4 *)(thisObject + 300) = 2;
        }
        if (fVar17 < 0.0) {
          fVar17 = fVar17 + _DAT_7ffe9c049c8c;
        }
        *(int *)(thisObject + 0x104) = (int)(fVar17 * fVar1) << 0x10;
        uVar9 = func_0x7ffe99940040(_DAT_7ffe9c8f3938);
        FUN_7ffe9ac2ed50(uVar9,thisObject,_DAT_7ffe9c9499a8,0);
        FUN_7ffe9a4b2010(thisObject,uVar9,0);
      }
      lVar12 = FUN_7ffe9bd98a10(actarAction,0);
      if (lVar12 != 0) {
        lVar12 = FUN_7ffe9bdbf0a0(&uStack_68,lVar12,0);
        fVar17 = *(float *)(lVar12 + 4);
        if (fVar4 < fVar17) {
          fVar17 = fVar17 + _DAT_7ffe9c049c98;
        }
        *(uint *)(thisObject + 0x104) =
             *(uint *)(thisObject + 0x104) | *(int *)(thisObject + 300) << 0xc;
        *(float *)(thisObject + 0x24) = (float)(int)(short)(int)(fVar17 * fVar1);
        if (target != (undefined *)0x0) {
          lVar12 = FUN_7ffe9ab9c3a0(target,_DAT_7ffe9c962758);
          fVar4 = _DAT_7ffe9c049b18;
          if (lVar12 != 0) {
            fVar17 = (float)FUN_7ffe99744d60(0,_DAT_7ffe9c9724e0,lVar12);
            uVar16 = (uint)((fVar17 + fVar4) * fVar1);
            if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130))
               || (*(longlong *)
                    (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
                    (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
              bVar3 = false;
            }
            else {
              bVar3 = true;
            }
            plVar15 = (longlong *)0x0;
            if (bVar3) {
              plVar15 = (longlong *)actarAction;
            }
            uVar7 = FUN_7ffe9a4adee0(thisObject,plVar15,lVar12,0);
            *(undefined4 *)(thisObject + 0x30) = uVar7;
          }
          *(uint *)(thisObject + 0x104) = *(uint *)(thisObject + 0x104) | uVar16;
          FUN_7ffe9a64a1b0(thisObject,uVar16,0);
          if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130))
             || (*(longlong *)
                  (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
                  (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
            bVar3 = false;
          }
          else {
            bVar3 = true;
          }
          plVar15 = (longlong *)0x0;
          if (bVar3) {
            plVar15 = (longlong *)actarAction;
          }
          if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          cVar5 = FUN_7ffe9bda2160(plVar15,0,0);
          if (cVar5 == '\0') {
            return;
          }
          if ((((plVar15 != (longlong *)0x0) &&
               (plVar14 = (longlong *)
                          (**(code **)(*plVar15 + 0x298))(plVar15,*(undefined8 *)(*plVar15 + 0x2a0))
               , plVar14 != (longlong *)0x0)) &&
              (lVar12 = (**(code **)(*plVar14 + 0x1c8))(plVar14,*(undefined8 *)(*plVar14 + 0x1d0)),
              lVar12 != 0)) && (*(longlong *)(lVar12 + 0x40) != 0)) {
            cVar5 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x40),0x486,&lStackX_18,
                                     _DAT_7ffe9c934418);
            if (cVar5 != '\0') {
              fVar1 = *(float *)(thisObject + 0x120);
              if (lStackX_18 == 0) goto LAB_7ffe9a6494cc;
              iVar8 = func_0x7ffe9a7a2140(lStackX_18,0x32);
              *(float *)(thisObject + 0x120) = (float)iVar8 + fVar1;
            }
            if (*(int *)(thisObject + 300) - 1U < 2) {
              plVar14 = (longlong *)
                        (**(code **)(*plVar15 + 0x298))(plVar15,*(undefined8 *)(*plVar15 + 0x2a0));
              if ((plVar14 == (longlong *)0x0) ||
                 (thisObject_00 =
                       (undefined *)
                       (**(code **)(*plVar14 + 0x218))(plVar14,*(undefined8 *)(*plVar14 + 0x220)),
                 thisObject_00 == (undefined *)0x0)) goto LAB_7ffe9a6494cc;
              bVar6 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x404,(undefined *)0x0);
              if (bVar6 != 0) {
                (**(code **)(*plVar15 + 0x228))
                          (plVar15,0,0x1b,fVar4,0,0,0,1,*(undefined8 *)(*plVar15 + 0x230));
              }
            }
            return;
          }
        }
      }
    }
  }
LAB_7ffe9a6494cc:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

