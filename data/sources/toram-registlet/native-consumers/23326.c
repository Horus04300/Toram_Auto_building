
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void LunaDitherStarAction_ActionStart
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  byte bVar4;
  longlong *plVar5;
  undefined *thisObject_00;
  longlong lVar6;
  undefined8 uVar7;
  longlong lVar8;
  ulonglong *puVar9;
  undefined8 *puVar10;
  float fVar11;
  float fVar12;
  float fVar13;
  float fVar14;
  undefined8 uStack_78;
  float fStack_70;
  undefined8 uStack_68;
  float fStack_60;
  
  if (DAT_7ffe9cadec75 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c943090);
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c8fbcf8);
    FUN_7ffe9996d590(&DAT_7ffe9c94aa60);
    FUN_7ffe9996d590(&DAT_7ffe9c962758);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c957428);
    FUN_7ffe9996d590(&DAT_7ffe9c96a700);
    DAT_7ffe9cadec75 = '\x01';
  }
  FUN_7ffe9a4a6970(thisObject,actarAction,target,0);
  cVar3 = func_0x7ffe9a4aea60(thisObject,0);
  if (cVar3 == '\0') {
    if (actarAction == (undefined *)0x0) {
      plVar5 = (longlong *)0x0;
    }
    else {
      if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
           (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      plVar5 = (longlong *)0x0;
      if (bVar2) {
        plVar5 = (longlong *)actarAction;
      }
    }
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar3 = FUN_7ffe9bda2160(plVar5,0,0);
    if (cVar3 != '\0') {
      if (((plVar5 != (longlong *)0x0) &&
          (plVar5 = (longlong *)
                    (**(code **)(*plVar5 + 0x298))(plVar5,*(undefined8 *)(*plVar5 + 0x2a0)),
          plVar5 != (longlong *)0x0)) &&
         (thisObject_00 =
               (undefined *)(**(code **)(*plVar5 + 0x218))(plVar5,*(undefined8 *)(*plVar5 + 0x220)),
         thisObject_00 != (undefined *)0x0)) {
        plVar5 = (longlong *)
                 GemCartBufferManager_GetGemCartBuffer(thisObject_00,0x417,(undefined *)0x0);
        if ((plVar5 != (longlong *)0x0) && (lVar8 = *(longlong *)(thisObject + 0x50), lVar8 != 0)) {
          if (*(int *)(_DAT_7ffe9c96a700 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          lVar6 = *(longlong *)(*(longlong *)(_DAT_7ffe9c96a700 + 0xb8) + 8);
          if (lVar6 == 0) {
            if (*(int *)(_DAT_7ffe9c96a700 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            uVar7 = **(undefined8 **)(_DAT_7ffe9c96a700 + 0xb8);
            lVar6 = func_0x7ffe99940040(_DAT_7ffe9c94aa60);
            FUN_7ffe9af13420(lVar6,uVar7,_DAT_7ffe9c957428,0);
            *(longlong *)(*(longlong *)(_DAT_7ffe9c96a700 + 0xb8) + 8) = lVar6;
            il2cpp_write_barrier_0();
          }
          cVar3 = FUN_7ffe9ab7ad20(lVar8,lVar6,_DAT_7ffe9c8fbcf8);
          if ((cVar3 != '\0') &&
             (bVar4 = GemCartBufferBase_get_IsCoolDown((undefined *)plVar5,(undefined *)0x0),
             bVar4 == 0)) {
            (**(code **)(*plVar5 + 0x1b8))(plVar5,*(undefined8 *)(*plVar5 + 0x1c0));
            thisObject[0x16c] = 1;
          }
        }
        if (target != (undefined *)0x0) {
          uVar7 = FUN_7ffe9bd9b890(target,0);
          *(undefined8 *)(thisObject + 0x130) = uVar7;
          il2cpp_write_barrier_0();
          if (actarAction != (undefined *)0x0) {
            lVar8 = FUN_7ffe9ab6e260(actarAction,_DAT_7ffe9c943090);
            if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            cVar3 = FUN_7ffe9bda2160(lVar8,0,0);
            if (cVar3 != '\0') {
              if (lVar8 == 0) goto LAB_7ffe9a66e8df;
              FUN_7ffe99b1e730(lVar8,target,0);
              FUN_7ffe99b1e600(lVar8,0);
            }
            fVar13 = 0.0;
            lVar8 = FUN_7ffe9ab9c3a0(target,_DAT_7ffe9c962758);
            if (lVar8 != 0) {
              fVar13 = (float)FUN_7ffe99744d60(0,_DAT_7ffe9c9724e0,lVar8);
            }
            lVar8 = FUN_7ffe9bd9b890(target,0);
            if (lVar8 != 0) {
              puVar9 = (ulonglong *)FUN_7ffe9bdbf710(&uStack_68,lVar8,0);
              uStack_78 = *puVar9;
              fStack_70 = *(float *)(puVar9 + 1);
              lVar8 = FUN_7ffe9bd98a10(actarAction,0);
              if (lVar8 != 0) {
                puVar10 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_68,lVar8,0);
                fStack_70 = fStack_70 - *(float *)(puVar10 + 1);
                uStack_68 = CONCAT44(uStack_78._4_4_ - (float)((ulonglong)*puVar10 >> 0x20),
                                     (float)uStack_78 - (float)*puVar10);
                fStack_60 = fStack_70;
                fVar11 = (float)FUN_7ffe999e62d0(&uStack_68,0);
                fVar12 = 0.0;
                if (0.0 <= fVar11 - fVar13) {
                  fVar12 = fVar11 - fVar13;
                }
                *(float *)(thisObject + 0x168) = fVar12;
                lVar8 = FUN_7ffe9bd9b890(target,0);
                if (lVar8 != 0) {
                  puVar9 = (ulonglong *)FUN_7ffe9bdbf710(&uStack_68,lVar8,0);
                  uStack_78 = *puVar9;
                  fStack_70 = *(float *)(puVar9 + 1);
                  lVar8 = FUN_7ffe9bd98a10(actarAction,0);
                  if (lVar8 != 0) {
                    puVar10 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_68,lVar8,0);
                    fStack_60 = *(float *)(puVar10 + 1);
                    fStack_70 = fStack_70 - fStack_60;
                    uStack_78 = (ulonglong)(uint)((float)uStack_78 - (float)*puVar10);
                    fVar11 = (float)FUN_7ffe999e62d0(&uStack_78,0);
                    FUN_7ffe99a14ca0(&uStack_78,0);
                    fVar12 = _DAT_7ffe9c049cfc;
                    fVar11 = fVar11 - fVar13;
                    fVar14 = fVar11 * uStack_78._4_4_;
                    fVar13 = fStack_70 * fVar11;
                    if ((*(longlong *)(thisObject + 0x58) != 0) &&
                       (lVar8 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar8 != 0))
                    {
                      FUN_7ffe9ad10e00(lVar8,0x1e,
                                       (int)((float)uStack_78 * fVar11 * _DAT_7ffe9c049cfc),
                                       _DAT_7ffe9c949490);
                      if ((*(longlong *)(thisObject + 0x58) != 0) &&
                         (lVar8 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar8 != 0
                         )) {
                        FUN_7ffe9ad10e00(lVar8,0x1f,(int)(fVar14 * fVar12),_DAT_7ffe9c949490);
                        if ((*(longlong *)(thisObject + 0x58) != 0) &&
                           (lVar8 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50),
                           lVar8 != 0)) {
                          FUN_7ffe9ad10e00(lVar8,0x20,(int)(fVar13 * fVar12),_DAT_7ffe9c949490);
                          if ((*(longlong *)(thisObject + 0x58) != 0) &&
                             (lVar8 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50),
                             lVar8 != 0)) {
                            FUN_7ffe9ad10e00(lVar8,0x1b,10,_DAT_7ffe9c949490);
                            if ((*(longlong *)(thisObject + 0x58) != 0) &&
                               (lVar8 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50),
                               lVar8 != 0)) {
                              FUN_7ffe9ad10e00(lVar8,0x22,1,_DAT_7ffe9c949490);
                              if ((*(longlong *)(thisObject + 0x58) != 0) &&
                                 (lVar8 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50),
                                 lVar8 != 0)) {
                                FUN_7ffe9ad10e00(lVar8,0x33,1,_DAT_7ffe9c949490);
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
LAB_7ffe9a66e8df:
      FUN_7ffe9996d7a0();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
  }
  return;
}

