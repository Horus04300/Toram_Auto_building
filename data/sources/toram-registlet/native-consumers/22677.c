
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MoonSlashAction_ActionStart
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  float fVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  int iVar5;
  int iVar6;
  undefined8 uVar7;
  longlong *plVar8;
  longlong lVar9;
  undefined *puVar10;
  longlong lVar11;
  undefined8 *puVar12;
  longlong *plVar13;
  longlong *plStackX_8;
  float fStack_48;
  float fStack_44;
  undefined8 uStack_28;
  float fStack_20;
  
  if (DAT_7ffe9cadeb88 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c956938);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    DAT_7ffe9cadeb88 = '\x01';
  }
  plStackX_8 = (longlong *)0x0;
  FUN_7ffe9a4a6970(thisObject,actarAction,target,0);
  uVar7 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
  FUN_7ffe9a9002e0(uVar7,0xbf09078,0);
  *(undefined8 *)(thisObject + 0x58) = uVar7;
  il2cpp_write_barrier_0();
  fVar1 = fStack_20;
  if ((*(longlong *)(thisObject + 0x58) != 0) &&
     (lVar9 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar9 != 0)) {
    FUN_7ffe9ad10e00(lVar9,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
    lVar9 = *(longlong *)(thisObject + 0x58);
    uVar7 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
    FUN_7ffe9a9002e0(uVar7,0x11e36c08,0);
    fVar1 = fStack_20;
    if (lVar9 != 0) {
      *(undefined8 *)(lVar9 + 0x20) = uVar7;
      il2cpp_write_barrier_0();
      fVar1 = fStack_20;
      if (((*(longlong *)(thisObject + 0x58) != 0) &&
          (lVar9 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x20), lVar9 != 0)) &&
         (lVar9 = *(longlong *)(lVar9 + 0x50), lVar9 != 0)) {
        FUN_7ffe9ad10e00(lVar9,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
        fVar1 = fStack_20;
        if ((*(longlong *)(thisObject + 0x58) != 0) &&
           (lVar9 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x20), lVar9 != 0)) {
          lVar9 = *(longlong *)(lVar9 + 0x50);
          iVar5 = func_0x7ffe9a8fec10(thisObject,0);
          fVar1 = fStack_20;
          if (lVar9 != 0) {
            FUN_7ffe9ad10e00(lVar9,2,10000 / (longlong)iVar5 & 0xffffffff,_DAT_7ffe9c949490);
            cVar4 = func_0x7ffe9a4aea60(thisObject,0);
            if (cVar4 == '\0') {
              plVar13 = (longlong *)0x0;
              if (actarAction != (undefined *)0x0) {
                if ((*(byte *)(*(longlong *)actarAction + 0x130) <
                     *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
                   (*(longlong *)
                     (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
                     (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
                  bVar3 = false;
                }
                else {
                  bVar3 = true;
                }
                if (bVar3) {
                  plVar13 = (longlong *)actarAction;
                }
              }
              if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                func_0x7ffe9996d830();
              }
              cVar4 = FUN_7ffe9bda2160(plVar13,0,0);
              if (cVar4 != '\0') {
                fVar1 = fStack_20;
                if ((((plVar13 != (longlong *)0x0) &&
                     (plVar8 = (longlong *)
                               (**(code **)(*plVar13 + 0x298))
                                         (plVar13,*(undefined8 *)(*plVar13 + 0x2a0)),
                     fVar1 = fStack_20, plVar8 != (longlong *)0x0)) &&
                    (lVar9 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0))
                    , fVar1 = fStack_20, lVar9 != 0)) && (*(longlong *)(lVar9 + 0x40) != 0)) {
                  cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x40),0x31,&plStackX_8,
                                           _DAT_7ffe9c934418);
                  if (cVar4 == '\0') {
                    return;
                  }
                  plVar8 = (longlong *)
                           (**(code **)(*plVar13 + 0x298))
                                     (plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
                  fVar1 = fStack_20;
                  if (plVar8 != (longlong *)0x0) {
                    lVar9 = (**(code **)(*plVar8 + 0x218))(plVar8,*(undefined8 *)(*plVar8 + 0x220));
                    if (lVar9 == 0) {
                      return;
                    }
                    plVar8 = (longlong *)
                             (**(code **)(*plVar13 + 0x298))
                                       (plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
                    fVar1 = fStack_20;
                    if ((plVar8 != (longlong *)0x0) &&
                       (puVar10 = (undefined *)
                                  (**(code **)(*plVar8 + 0x218))
                                            (plVar8,*(undefined8 *)(*plVar8 + 0x220)),
                       fVar1 = fStack_20, puVar10 != (undefined *)0x0)) {
                      puVar10 = GemCartBufferManager_GetGemCartBuffer
                                          (puVar10,0x41a,(undefined *)0x0);
                      if (puVar10 == (undefined *)0x0) {
                        return;
                      }
                      iVar5 = GemCartBufferBase_GetValue(puVar10,(undefined *)0x2,(undefined *)0x0);
                      fVar1 = fStack_20;
                      if (plStackX_8 != (longlong *)0x0) {
                        iVar6 = (**(code **)(*plStackX_8 + 0x1f8))
                                          (plStackX_8,0x14,*(undefined8 *)(*plStackX_8 + 0x200));
                        lVar9 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
                        fVar1 = fStack_20;
                        if ((actarAction != (undefined *)0x0) &&
                           (lVar11 = FUN_7ffe9bd98a10(actarAction,0), fVar1 = fStack_20, lVar11 != 0
                           )) {
                          puVar12 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_28,lVar11,0);
                          uVar7 = *puVar12;
                          fStack_20 = *(float *)(puVar12 + 1);
                          if (DAT_7ffe9cad9cac == '\0') {
                            FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
                            DAT_7ffe9cad9cac = '\x01';
                          }
                          fStack_48 = (float)uVar7;
                          fStack_44 = (float)((ulonglong)uVar7 >> 0x20);
                          uStack_28 = *(undefined8 *)
                                       (*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x18);
                          fVar1 = *(float *)(*(longlong *)(_DAT_7ffe9c8fc068 + 0xb8) + 0x20);
                          fStack_20 = fStack_20 + fVar1;
                          if (lVar9 != 0) {
                            uStack_28 = CONCAT44(fStack_44 + (float)((ulonglong)uStack_28 >> 0x20),
                                                 fStack_48 + (float)uStack_28);
                            FUN_7ffe99caa960(lVar9,iVar6 * iVar5,&uStack_28,0);
                            plVar13 = (longlong *)
                                      (**(code **)(*plVar13 + 0x298))
                                                (plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
                            fVar1 = fStack_20;
                            if ((plVar13 != (longlong *)0x0) &&
                               (lVar9 = (**(code **)(*plVar13 + 0x1c8))
                                                  (plVar13,*(undefined8 *)(*plVar13 + 0x1d0)),
                               fVar1 = fStack_20, lVar9 != 0)) {
                              FUN_7ffe9a7cafa0(lVar9,0x31);
                              return;
                            }
                          }
                        }
                      }
                    }
                  }
                }
                goto LAB_7ffe9a65288e;
              }
            }
            return;
          }
        }
      }
    }
  }
LAB_7ffe9a65288e:
  fStack_20 = fVar1;
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

