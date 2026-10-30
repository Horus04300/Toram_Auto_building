
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MagicFallAction_ActionStart
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  short sVar1;
  longlong lVar2;
  code *pcVar3;
  undefined8 uVar4;
  bool bVar5;
  float fVar6;
  char cVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  undefined8 uVar11;
  longlong lVar12;
  undefined8 *puVar13;
  longlong lVar14;
  longlong *plVar15;
  undefined *puVar16;
  longlong *plVar17;
  longlong *plVar18;
  longlong *plVar19;
  float fVar20;
  undefined4 uVar21;
  float fVar22;
  float fVar23;
  undefined4 auStackX_8 [2];
  undefined8 uStackX_10;
  undefined *puStackX_18;
  undefined8 uStack_f8;
  float fStack_f0;
  undefined8 uStack_e8;
  undefined4 uStack_e0;
  undefined8 uStack_d8;
  undefined4 uStack_d0;
  float fStack_c0;
  undefined8 uStack_b8;
  float fStack_b0;
  undefined1 auStack_a8 [16];
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined1 auStack_88 [80];
  
  puStackX_18 = target;
  if (DAT_7ffe9cadee8c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c96d390);
    FUN_7ffe9996d590(&DAT_7ffe9c904ea0);
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c949618);
    FUN_7ffe9996d590(&DAT_7ffe9c949aa8);
    FUN_7ffe9996d590(&DAT_7ffe9c962758);
    FUN_7ffe9996d590(&DAT_7ffe9c90c578);
    FUN_7ffe9996d590(&DAT_7ffe9c909440);
    FUN_7ffe9996d590(&DAT_7ffe9c8f00c0);
    FUN_7ffe9996d590(&DAT_7ffe9c95e280);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c92d1d8);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    FUN_7ffe9996d590(&DAT_7ffe9c947960);
    DAT_7ffe9cadee8c = '\x01';
  }
  plVar19 = (longlong *)0x0;
  auStackX_8[0] = 0;
  FUN_7ffe9a4a6970(thisObject,actarAction,target,0);
  *(undefined **)(thisObject + 0x1b0) = actarAction;
  il2cpp_write_barrier_0();
  cVar7 = func_0x7ffe9a4ad2e0(thisObject,0x2000,0);
  if (cVar7 != '\0') {
    FUN_7ffe9a6beec0(thisObject,actarAction,0);
  }
  cVar7 = func_0x7ffe9a4aea60(thisObject,0);
  if (cVar7 != '\0') {
    return;
  }
  if (*(int *)(_DAT_7ffe9c96d390 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  uStackX_10 = FUN_7ffe9b4fbf50(0);
  iVar8 = FUN_7ffe9b4fc1e0(&uStackX_10,0);
  iVar8 = (iVar8 / 10) * 10;
  *(int *)(thisObject + 0x104) = iVar8;
  uVar11 = func_0x7ffe99940040(_DAT_7ffe9c92d1d8);
  FUN_7ffe9b5223b0(uVar11,iVar8 / 10,0);
  *(undefined8 *)(thisObject + 0x178) = uVar11;
  il2cpp_write_barrier_0();
  *(undefined **)(thisObject + 0x150) = target;
  il2cpp_write_barrier_0();
  if ((target != (undefined *)0x0) && (lVar12 = FUN_7ffe9bd9b890(target,0), lVar12 != 0)) {
    puVar13 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_b8,lVar12,0);
    uVar21 = *(undefined4 *)(puVar13 + 1);
    *(undefined8 *)(thisObject + 0x160) = *puVar13;
    *(undefined4 *)(thisObject + 0x168) = uVar21;
    uVar11 = func_0x7ffe99940040(_DAT_7ffe9c90c578);
    FUN_7ffe9bd9b5b0(uVar11,_DAT_7ffe9c947960,0);
    FUN_7ffe9a8fed70(thisObject,uVar11,0);
    if (*(longlong *)(thisObject + 0x18) != 0) {
      lVar12 = FUN_7ffe9bd9b890(*(longlong *)(thisObject + 0x18),0);
      lVar14 = FUN_7ffe9bd9b890(target,0);
      if ((lVar14 != 0) &&
         (puVar13 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_b8,lVar14,0), lVar12 != 0)) {
        uStack_f8 = *puVar13;
        fStack_f0 = *(float *)(puVar13 + 1);
        FUN_7ffe9bdbff60(lVar12,&uStack_f8,0);
        *(undefined4 *)(thisObject + 0x180) = 0x3f800000;
        if (*(int *)(thisObject + 0xfc) == 0xf) {
          *(undefined4 *)(thisObject + 0x180) = 0x40000000;
        }
        plVar15 = plVar19;
        if (actarAction != (undefined *)0x0) {
          if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130))
             || (*(longlong *)
                  (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
                  (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
            bVar5 = false;
          }
          else {
            bVar5 = true;
          }
          if (bVar5) {
            plVar15 = (longlong *)actarAction;
          }
        }
        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        cVar7 = FUN_7ffe9bda2160(plVar15,0,0);
        if (plVar15 != (longlong *)0x0) {
          if (cVar7 != '\0') {
            uVar11 = (**(code **)(*plVar15 + 0x298))(plVar15,*(undefined8 *)(*plVar15 + 0x2a0));
            cVar7 = FUN_7ffe9a80d0a0(uVar11,auStackX_8,0);
            if (cVar7 != '\0') {
              *(undefined4 *)(thisObject + 0x30) = auStackX_8[0];
              if ((*(longlong *)(thisObject + 0x58) == 0) ||
                 (lVar12 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar12 == 0))
              goto LAB_7ffe9a6be770;
              cVar7 = FUN_7ffe9ad10f10(lVar12,7,_DAT_7ffe9c949618);
              if (cVar7 != '\0') {
                if ((*(longlong *)(thisObject + 0x58) == 0) ||
                   (lVar12 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar12 == 0))
                goto LAB_7ffe9a6be770;
                FUN_7ffe9ad24b00(lVar12,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949aa8);
              }
            }
          }
          plVar15 = (longlong *)
                    (**(code **)(*plVar15 + 0x298))(plVar15,*(undefined8 *)(*plVar15 + 0x2a0));
          if ((plVar15 != (longlong *)0x0) &&
             (puVar16 = (undefined *)
                        (**(code **)(*plVar15 + 0x218))(plVar15,*(undefined8 *)(*plVar15 + 0x220)),
             puVar16 != (undefined *)0x0)) {
            puVar16 = GemCartBufferManager_GetGemCartBuffer(puVar16,0x412,(undefined *)0x0);
            fVar6 = _DAT_7ffe9c049ce4;
            fVar23 = _DAT_7ffe9c049b4c;
            if (puVar16 != (undefined *)0x0) {
              iVar8 = GemCartBufferBase_GetValue(puVar16,(undefined *)0x2,(undefined *)0x0);
              uVar9 = iVar8 * -10 + 0x4b;
              plVar15 = plVar19;
              if (-1 < (int)uVar9) {
                plVar15 = (longlong *)(ulonglong)uVar9;
              }
              *(float *)(thisObject + 0x48) = *(float *)(thisObject + 0x48) / fVar6;
              *(float *)(thisObject + 0x180) = *(float *)(thisObject + 0x180) * fVar23;
              plVar18 = plVar19;
              while( true ) {
                if (*(int *)(_DAT_7ffe9c95e280 + 0xe0) == 0) {
                  func_0x7ffe9996d830(_DAT_7ffe9c95e280);
                }
                uVar9 = (uint)plVar18;
                if (*(int *)(*(longlong *)(_DAT_7ffe9c95e280 + 0xb8) + 4) <= (int)uVar9) {
                  sVar1 = *(short *)(puVar16 + 0x14);
                  *(short *)(thisObject + 0x1ba) = sVar1;
                  iVar10 = 1;
                  iVar8 = (int)sVar1;
                  if (*(int *)(thisObject + 0x104) < 0) {
                    iVar8 = -(int)sVar1;
                  }
                  *(int *)(thisObject + 0x104) = iVar8 + *(int *)(thisObject + 0x104);
                  plVar18 = plVar19;
                  goto LAB_7ffe9a6be320;
                }
                lVar12 = *(longlong *)(thisObject + 0x138);
                if (lVar12 == 0) goto LAB_7ffe9a6be770;
                lVar14 = (longlong)(int)uVar9;
                if (*(uint *)(lVar12 + 0x18) <= uVar9) break;
                *(int *)(lVar12 + 0x20 + lVar14 * 4) = *(int *)(lVar12 + 0x20 + lVar14 * 4) / 10;
                lVar12 = *(longlong *)(thisObject + 0x140);
                if (lVar12 == 0) goto LAB_7ffe9a6be770;
                if (*(uint *)(lVar12 + 0x18) <= uVar9) break;
                *(int *)(lVar12 + 0x20 + lVar14 * 4) = *(int *)(lVar12 + 0x20 + lVar14 * 4) / 10;
                plVar18 = (longlong *)(ulonglong)(uVar9 + 1);
              }
LAB_7ffe9a6be76a:
              FUN_7ffe9996d790();
              pcVar3 = (code *)swi(3);
              (*pcVar3)();
              return;
            }
            lVar12 = *(longlong *)(thisObject + 0x58);
            uVar11 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
            FUN_7ffe9a9002e0(uVar11,0x11e855d3,0);
            if (lVar12 != 0) {
              *(undefined8 *)(lVar12 + 0x20) = uVar11;
              il2cpp_write_barrier_0();
              if (*(longlong *)(thisObject + 0x58) != 0) {
                lVar12 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x20);
                uVar11 = FUN_7ffe9a6bec00(thisObject,0);
                if (lVar12 != 0) {
                  *(undefined8 *)(lVar12 + 0x20) = uVar11;
                  il2cpp_write_barrier_0();
LAB_7ffe9a6be423:
                  lVar12 = FUN_7ffe9ab9c3a0(target,_DAT_7ffe9c962758);
                  fVar22 = _DAT_7ffe9c049e80;
                  fVar20 = _DAT_7ffe9c049b34;
                  if (lVar12 != 0) {
                    fVar20 = (float)FUN_7ffe99744d60(0,_DAT_7ffe9c9724e0,lVar12);
                    fVar22 = _DAT_7ffe9c049b74;
                    if (_DAT_7ffe9c049b74 <= fVar20) {
                      fVar22 = fVar20;
                    }
                    *(float *)(thisObject + 0x148) = fVar22;
                    if (0 < *(short *)(thisObject + 0x1ba)) {
                      *(float *)(thisObject + 0x148) = fVar22 * fVar23;
                    }
                    *(int *)(thisObject + 0x28) = (int)(*(float *)(thisObject + 0x148) * fVar6);
                    uVar21 = func_0x7ffe99a4d6a0(*(float *)(thisObject + 0x148),0);
                    *(undefined4 *)(thisObject + 0x148) = uVar21;
                    fVar22 = _DAT_7ffe9c049e80;
                    fVar20 = _DAT_7ffe9c049b34;
                  }
LAB_7ffe9a6be4b0:
                  if (*(int *)(_DAT_7ffe9c95e280 + 0xe0) == 0) {
                    func_0x7ffe9996d830(_DAT_7ffe9c95e280);
                  }
                  iVar8 = (int)plVar19;
                  if (**(int **)(_DAT_7ffe9c95e280 + 0xb8) <= iVar8) {
                    return;
                  }
                  plVar19 = *(longlong **)(thisObject + 0x178);
                  if (plVar19 == (longlong *)0x0) goto LAB_7ffe9a6be770;
                  iVar10 = (**(code **)(*plVar19 + 0x1a8))
                                     (plVar19,1 - (int)(*(float *)(thisObject + 0x148) * fVar22),
                                      *(undefined8 *)(*plVar19 + 0x1b0));
                  plVar19 = *(longlong **)(thisObject + 0x178);
                  fVar23 = (float)iVar10 * fVar20;
                  if (plVar19 == (longlong *)0x0) goto LAB_7ffe9a6be770;
                  iVar10 = (**(code **)(*plVar19 + 0x1a8))
                                     (plVar19,36000,*(undefined8 *)(*plVar19 + 0x1b0));
                  if (DAT_7ffe9cad9cac == '\0') {
                    FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
                    DAT_7ffe9cad9cac = '\x01';
                  }
                  uStack_e8 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x18);
                  uStack_e0 = *(undefined4 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x20);
                  puVar13 = (undefined8 *)
                            FUN_7ffe9bda2ff0(auStack_88,(float)iVar10 * fVar20,&uStack_e8,0);
                  uVar11 = *puVar13;
                  uVar4 = puVar13[1];
                  if (DAT_7ffe9cad9ca9 == '\0') {
                    FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
                    DAT_7ffe9cad9ca9 = '\x01';
                  }
                  uStack_d8 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x48);
                  uStack_d0 = *(undefined4 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x50);
                  uStack_98 = uVar11;
                  uStack_90 = uVar4;
                  puVar13 = (undefined8 *)FUN_7ffe9bda42f0(auStack_a8,&uStack_98,&uStack_d8,0);
                  lVar14 = _DAT_7ffe9c8f00c0;
                  fStack_c0 = *(float *)(puVar13 + 1);
                  fStack_f0 = fStack_c0 * fVar23;
                  uStack_f8 = CONCAT44((float)((ulonglong)*puVar13 >> 0x20) * fVar23,
                                       (float)*puVar13 * fVar23);
                  lVar12 = *(longlong *)(thisObject + 0x170);
                  if (lVar12 == 0) goto LAB_7ffe9a6be770;
                  *(int *)(lVar12 + 0x1c) = *(int *)(lVar12 + 0x1c) + 1;
                  lVar2 = *(longlong *)(lVar12 + 0x10);
                  uVar9 = *(uint *)(lVar12 + 0x18);
                  if (lVar2 == 0) goto LAB_7ffe9a6be770;
                  if (uVar9 < *(uint *)(lVar2 + 0x18)) {
                    *(uint *)(lVar12 + 0x18) = uVar9 + 1;
                    if (*(uint *)(lVar2 + 0x18) <= uVar9) goto LAB_7ffe9a6be76a;
                    *(undefined8 *)(lVar2 + 0x20 + (longlong)(int)uVar9 * 0xc) = uStack_f8;
                    *(float *)(lVar2 + 0x28 + (longlong)(int)uVar9 * 0xc) = fStack_f0;
                  }
                  else {
                    uStack_b8 = uStack_f8;
                    fStack_b0 = fStack_f0;
                    FUN_7ffe9afd57e0(lVar12,&uStack_b8,
                                     *(undefined8 *)
                                      (*(longlong *)(*(longlong *)(lVar14 + 0x20) + 0xc0) + 0x70));
                  }
                  lVar14 = _DAT_7ffe9c909440;
                  lVar12 = *(longlong *)(thisObject + 0x198);
                  if (lVar12 == 0) goto LAB_7ffe9a6be770;
                  *(int *)(lVar12 + 0x1c) = *(int *)(lVar12 + 0x1c) + 1;
                  lVar2 = *(longlong *)(lVar12 + 0x10);
                  uVar9 = *(uint *)(lVar12 + 0x18);
                  if (lVar2 == 0) goto LAB_7ffe9a6be770;
                  if (uVar9 < *(uint *)(lVar2 + 0x18)) {
                    *(uint *)(lVar12 + 0x18) = uVar9 + 1;
                    if (*(uint *)(lVar2 + 0x18) <= uVar9) goto LAB_7ffe9a6be76a;
                    *(undefined1 *)((longlong)(int)uVar9 + 0x20 + lVar2) = 0;
                    plVar19 = (longlong *)(ulonglong)(iVar8 + 1);
                  }
                  else {
                    FUN_7ffe9afaba30(lVar12,0,*(undefined8 *)
                                               (*(longlong *)(*(longlong *)(lVar14 + 0x20) + 0xc0) +
                                               0x70));
                    plVar19 = (longlong *)(ulonglong)(iVar8 + 1);
                  }
                  goto LAB_7ffe9a6be4b0;
                }
              }
            }
          }
        }
      }
    }
  }
LAB_7ffe9a6be770:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
LAB_7ffe9a6be320:
  if (*(int *)(_DAT_7ffe9c95e280 + 0xe0) == 0) {
    func_0x7ffe9996d830(_DAT_7ffe9c95e280);
  }
  target = puStackX_18;
  if (**(int **)(_DAT_7ffe9c95e280 + 0xb8) < iVar10) goto LAB_7ffe9a6be423;
  plVar17 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c94b460);
  FUN_7ffe9a9002e0(plVar17,iVar10 + 0x11e855c4,0);
  if ((plVar17 == (longlong *)0x0) || (plVar17[10] == 0)) goto LAB_7ffe9a6be770;
  FUN_7ffe9ad10e00(plVar17[10],0xd,plVar15,_DAT_7ffe9c949490);
  lVar12 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
  FUN_7ffe9a9002e0(lVar12,0x11e85204,0);
  plVar17[4] = lVar12;
  il2cpp_write_barrier_0();
  if (*(longlong *)(thisObject + 400) == 0) goto LAB_7ffe9a6be770;
  FUN_7ffe9ad4d2a0(*(longlong *)(thisObject + 400),iVar10,lVar12,_DAT_7ffe9c904ea0);
  if (plVar18 == (longlong *)0x0) {
    if (*(longlong *)(thisObject + 0x58) == 0) goto LAB_7ffe9a6be770;
    plVar18 = (longlong *)(*(longlong *)(thisObject + 0x58) + 0x20);
  }
  else {
    plVar18 = plVar18 + 3;
  }
  *plVar18 = (longlong)plVar17;
  il2cpp_write_barrier_0();
  iVar10 = iVar10 + 1;
  plVar18 = plVar17;
  goto LAB_7ffe9a6be320;
}

