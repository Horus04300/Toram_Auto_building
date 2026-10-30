
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ParabolaCannonAction_ActionStart
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  ulonglong uVar1;
  undefined4 uVar2;
  code *pcVar3;
  bool bVar4;
  char cVar5;
  byte bVar6;
  longlong lVar7;
  ulonglong *puVar8;
  undefined8 uVar9;
  longlong lVar10;
  undefined8 *puVar11;
  longlong lVar12;
  float *pfVar13;
  longlong *plVar14;
  undefined *puVar15;
  undefined8 uVar16;
  float fVar17;
  undefined4 uVar18;
  float fVar19;
  undefined8 uStack_68;
  float fStack_60;
  ulonglong uStack_58;
  float fStack_50;
  ulonglong uStack_48;
  float fStack_40;
  
  if (DAT_7ffe9cadf26c == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c962758);
    FUN_7ffe9996d590(&DAT_7ffe9c90c578);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    FUN_7ffe9996d590(&DAT_7ffe9c94c0a0);
    FUN_7ffe9996d590(&DAT_7ffe9c920298);
    DAT_7ffe9cadf26c = '\x01';
  }
  uStack_58 = 0;
  fStack_50 = 0.0;
  FUN_7ffe9a4a6970(thisObject,actarAction,target,0);
  cVar5 = func_0x7ffe9a4aea60(thisObject,0);
  if (cVar5 != '\0') {
    return;
  }
  if (actarAction == (undefined *)0x0) {
    *(undefined8 *)(thisObject + 0x160) = 0;
  }
  else {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar4 = false;
    }
    else {
      bVar4 = true;
    }
    puVar15 = (undefined *)0x0;
    if (bVar4) {
      puVar15 = actarAction;
    }
    *(undefined **)(thisObject + 0x160) = puVar15;
  }
  il2cpp_write_barrier_0();
  if ((target != (undefined *)0x0) && (lVar7 = FUN_7ffe9bd9b890(target,0), lVar7 != 0)) {
    puVar8 = (ulonglong *)FUN_7ffe9bdbf710(&uStack_48,lVar7,0);
    uStack_68 = *puVar8;
    fStack_60 = *(float *)(puVar8 + 1);
    if ((actarAction != (undefined *)0x0) && (lVar7 = FUN_7ffe9bd98a10(actarAction,0), lVar7 != 0))
    {
      puVar8 = (ulonglong *)FUN_7ffe9bdbf710(&uStack_48,lVar7,0);
      uStack_48 = *puVar8;
      fStack_40 = *(float *)(puVar8 + 1);
      fStack_60 = fStack_60 - fStack_40;
      uStack_68 = (ulonglong)(uint)((float)uStack_68 - (float)uStack_48);
      FUN_7ffe99a14ca0(&uStack_68,0);
      lVar7 = FUN_7ffe9bd98a10(actarAction,0);
      if (lVar7 != 0) {
        fStack_40 = fStack_60;
        uStack_48 = uStack_68;
        FUN_7ffe9bdbfb00(lVar7,&uStack_48,0);
        uVar18 = 0;
        lVar7 = FUN_7ffe9ab9c3a0(target,_DAT_7ffe9c962758);
        if (lVar7 != 0) {
          uVar18 = FUN_7ffe99744d60(0,_DAT_7ffe9c9724e0,lVar7);
        }
        if (*(int *)(thisObject + 0xfc) - 0xcU < 2) {
          uVar16 = 0x11e86578;
        }
        else {
          uVar16 = 0x11e86579;
          thisObject[0x148] = 0;
        }
        uVar9 = func_0x7ffe99940040(_DAT_7ffe9c90c578);
        FUN_7ffe9bd9b5b0(uVar9,_DAT_7ffe9c920298,0);
        FUN_7ffe9a8fed70(thisObject,uVar9,0);
        if (*(longlong *)(thisObject + 0x18) != 0) {
          lVar7 = FUN_7ffe9bd9b890(*(longlong *)(thisObject + 0x18),0);
          lVar10 = FUN_7ffe9bd9b890(target,0);
          if ((lVar10 != 0) &&
             (puVar8 = (ulonglong *)FUN_7ffe9bdbf710(&uStack_68,lVar10,0), lVar7 != 0)) {
            uStack_48 = *puVar8;
            fStack_40 = *(float *)(puVar8 + 1);
            FUN_7ffe9bdbff60(lVar7,&uStack_48,0);
            if ((*(longlong *)(thisObject + 0x18) != 0) &&
               (lVar7 = FUN_7ffe9bd9b890(*(longlong *)(thisObject + 0x18),0), lVar7 != 0)) {
              puVar8 = (ulonglong *)FUN_7ffe9bdbf710(&uStack_48,lVar7,0);
              uStack_68 = *puVar8;
              fStack_60 = *(float *)(puVar8 + 1);
              if (DAT_7ffe9cad9cac == '\0') {
                FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
                DAT_7ffe9cad9cac = '\x01';
              }
              uVar9 = *(undefined8 *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x18);
              fStack_60 = fStack_60 +
                          *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x20) *
                          _DAT_7ffe9c049ce0;
              uStack_48 = CONCAT44(uStack_68._4_4_ +
                                   (float)((ulonglong)uVar9 >> 0x20) * _DAT_7ffe9c049ce0,
                                   (float)uStack_68 + (float)uVar9 * _DAT_7ffe9c049ce0);
              fStack_40 = fStack_60;
              cVar5 = FUN_7ffe9a876d10(&uStack_48,_DAT_7ffe9c049ce4,&uStack_58,0);
              if (cVar5 != '\0') {
                if ((*(longlong *)(thisObject + 0x18) == 0) ||
                   (lVar7 = FUN_7ffe9bd9b890(*(longlong *)(thisObject + 0x18),0), lVar7 == 0))
                goto LAB_7ffe9a757b48;
                fStack_40 = fStack_50;
                uStack_48 = uStack_58;
                FUN_7ffe9bdbff60(lVar7,&uStack_48,0);
              }
              if ((*(longlong *)(thisObject + 0x18) != 0) &&
                 (lVar7 = FUN_7ffe9bd9b890(*(longlong *)(thisObject + 0x18),0), lVar7 != 0)) {
                puVar11 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_48,lVar7,0);
                uVar2 = *(undefined4 *)(puVar11 + 1);
                *(undefined8 *)(thisObject + 0x154) = *puVar11;
                *(undefined4 *)(thisObject + 0x15c) = uVar2;
                lVar7 = FUN_7ffe9bd98a10(actarAction,0);
                if (lVar7 != 0) {
                  puVar8 = (ulonglong *)FUN_7ffe9bdbf710(&uStack_48,lVar7,0);
                  uVar1 = *puVar8;
                  fVar17 = *(float *)(puVar8 + 1);
                  lVar7 = FUN_7ffe9bd9b890(target,0);
                  if (lVar7 != 0) {
                    puVar8 = (ulonglong *)FUN_7ffe9bdbf710(&uStack_68,lVar7,0);
                    uStack_48 = *puVar8;
                    fStack_40 = *(float *)(puVar8 + 1);
                    uStack_68 = uVar1;
                    fStack_60 = fVar17;
                    fVar17 = (float)FUN_7ffe9a4a8d80(thisObject,&uStack_68,&uStack_48,uVar18,0);
                    if (fVar17 <= _DAT_7ffe9c049b74) {
                      fVar19 = 0.0;
                    }
                    else {
                      fVar19 = _DAT_7ffe9c049b18;
                      if (fVar17 < _DAT_7ffe9c049ce8) {
                        fVar19 = (fVar17 - _DAT_7ffe9c049b74) / _DAT_7ffe9c049fc4;
                      }
                    }
                    lVar7 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
                    FUN_7ffe9a9002e0(lVar7,uVar16,0);
                    if (lVar7 != 0) {
                      lVar10 = *(longlong *)(lVar7 + 0x50);
                      if ((*(longlong *)(thisObject + 0x18) != 0) &&
                         (lVar12 = FUN_7ffe9bd9b890(*(longlong *)(thisObject + 0x18),0), lVar12 != 0
                         )) {
                        pfVar13 = (float *)FUN_7ffe9bdbf710(&uStack_48,lVar12,0);
                        fVar17 = _DAT_7ffe9c049cfc;
                        if (lVar10 != 0) {
                          FUN_7ffe9ad10e00(lVar10,0x1e,(int)(*pfVar13 * _DAT_7ffe9c049cfc),
                                           _DAT_7ffe9c949490);
                          lVar10 = *(longlong *)(lVar7 + 0x50);
                          if ((*(longlong *)(thisObject + 0x18) != 0) &&
                             (lVar12 = FUN_7ffe9bd9b890(*(longlong *)(thisObject + 0x18),0),
                             lVar12 != 0)) {
                            lVar12 = FUN_7ffe9bdbf710(&uStack_48,lVar12,0);
                            if (lVar10 != 0) {
                              FUN_7ffe9ad10e00(lVar10,0x1f,(int)(*(float *)(lVar12 + 4) * fVar17),
                                               _DAT_7ffe9c949490);
                              lVar10 = *(longlong *)(lVar7 + 0x50);
                              if ((*(longlong *)(thisObject + 0x18) != 0) &&
                                 (lVar12 = FUN_7ffe9bd9b890(*(longlong *)(thisObject + 0x18),0),
                                 lVar12 != 0)) {
                                lVar12 = FUN_7ffe9bdbf710(&uStack_48,lVar12,0);
                                if (lVar10 != 0) {
                                  FUN_7ffe9ad10e00(lVar10,0x20,
                                                   (int)(*(float *)(lVar12 + 8) * fVar17),
                                                   _DAT_7ffe9c949490);
                                  if (*(longlong *)(lVar7 + 0x50) != 0) {
                                    FUN_7ffe9ad10e00(*(longlong *)(lVar7 + 0x50),0x1b,
                                                     (int)((_DAT_7ffe9c049dbc - fVar19) * fVar17),
                                                     _DAT_7ffe9c949490);
                                    if (*(longlong *)(lVar7 + 0x50) != 0) {
                                      FUN_7ffe9ad10e00(*(longlong *)(lVar7 + 0x50),6,100,
                                                       _DAT_7ffe9c949490);
                                      lVar10 = *(longlong *)(lVar7 + 0x50);
                                      if (*(int *)(_DAT_7ffe9c94c0a0 + 0xe0) == 0) {
                                        func_0x7ffe9996d830();
                                      }
                                      uVar18 = func_0x7ffe9a812780((int)(_DAT_7ffe9c049d98 -
                                                                        fVar19 * fVar17),0);
                                      if (lVar10 != 0) {
                                        FUN_7ffe9ad10e00(lVar10,2,uVar18,_DAT_7ffe9c949490);
                                        if (*(longlong *)(thisObject + 0x58) != 0) {
                                          *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x20) =
                                               lVar7;
                                          il2cpp_write_barrier_0();
                                          if ((*(byte *)(*(longlong *)actarAction + 0x130) <
                                               *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
                                             (*(longlong *)
                                               (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
                                               (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8)
                                              != _DAT_7ffe9c922720)) {
                                            bVar4 = false;
                                          }
                                          else {
                                            bVar4 = true;
                                          }
                                          plVar14 = (longlong *)0x0;
                                          if (bVar4) {
                                            plVar14 = (longlong *)actarAction;
                                          }
                                          if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                                            func_0x7ffe9996d830();
                                          }
                                          cVar5 = FUN_7ffe9bda2160(plVar14,0,0);
                                          if (cVar5 != '\0') {
                                            if (((plVar14 == (longlong *)0x0) ||
                                                (plVar14 = (longlong *)
                                                           (**(code **)(*plVar14 + 0x298))
                                                                     (plVar14,*(undefined8 *)
                                                                               (*plVar14 + 0x2a0)),
                                                plVar14 == (longlong *)0x0)) ||
                                               (puVar15 = (undefined *)
                                                          (**(code **)(*plVar14 + 0x218))
                                                                    (plVar14,*(undefined8 *)
                                                                              (*plVar14 + 0x220)),
                                               puVar15 == (undefined *)0x0)) goto LAB_7ffe9a757b48;
                                            bVar6 = GemCartBufferManager_ContainsBuffer
                                                              (puVar15,0x419,(undefined *)0x0);
                                            if (bVar6 != 0) {
                                              thisObject[0x168] = 1;
                                            }
                                          }
                                          return;
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
LAB_7ffe9a757b48:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

