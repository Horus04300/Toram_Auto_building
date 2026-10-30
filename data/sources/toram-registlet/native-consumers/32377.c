
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void ImprovisationSongAction_ActionPreparation
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  undefined1 uVar1;
  longlong lVar2;
  longlong *plVar3;
  code *pcVar4;
  longlong **pplVar5;
  bool bVar6;
  char cVar7;
  int iVar8;
  undefined4 uVar9;
  uint uVar10;
  longlong lVar11;
  longlong *plVar12;
  undefined *thisObject_00;
  undefined8 uVar13;
  undefined8 *puVar14;
  ushort uVar15;
  ulonglong uVar16;
  byte bVar17;
  longlong *plStack_c0;
  undefined8 uStack_b8;
  longlong **pplStack_b0;
  longlong lStack_a8;
  undefined1 auStack_68 [64];
  
  if (DAT_7ffe9cadf806 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f3938);
    FUN_7ffe9996d590(&DAT_7ffe9c92eda0);
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c950de8);
    FUN_7ffe9996d590(&DAT_7ffe9c939b40);
    FUN_7ffe9996d590(&DAT_7ffe9c955e78);
    FUN_7ffe9996d590(&DAT_7ffe9c95b950);
    FUN_7ffe9996d590(&DAT_7ffe9c93ac18);
    FUN_7ffe9996d590(&DAT_7ffe9c948f68);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c9538a8);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    FUN_7ffe9996d590(&DAT_7ffe9c94f0d8);
    FUN_7ffe9996d590(&DAT_7ffe9c96e9e0);
    FUN_7ffe9996d590(&DAT_7ffe9c94da00);
    FUN_7ffe9996d590(&DAT_7ffe9c94dac8);
    FUN_7ffe9996d590(&DAT_7ffe9c95fe20);
    DAT_7ffe9cadf806 = '\x01';
  }
  plVar12 = (longlong *)0x0;
  plStack_c0 = (longlong *)0x0;
  lVar11 = func_0x7ffe99940040(_DAT_7ffe9c95fe20);
  func_0x7ffe999c3920(lVar11,0);
  lStack_a8 = lVar11;
  if (lVar11 != 0) {
    *(undefined **)(lVar11 + 0x10) = thisObject;
    il2cpp_write_barrier_0();
    FUN_7ffe9a4a5ca0(thisObject,actarAction,target,0);
    cVar7 = func_0x7ffe9a4aea60(thisObject,0);
    if (cVar7 != '\0') {
      return;
    }
    bVar17 = 0;
    target = (undefined *)plVar12;
    if (actarAction != (undefined *)0x0) {
      if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
           (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
        bVar6 = false;
      }
      else {
        bVar6 = true;
      }
      target = (undefined *)(longlong *)0x0;
      if (bVar6) {
        target = actarAction;
      }
    }
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar7 = FUN_7ffe9bda2160(target,0,0);
    if (cVar7 == '\0') {
LAB_7ffe9a823ace:
      uVar16 = (ulonglong)plVar12 & 0xffff;
LAB_7ffe9a823ad1:
      uVar10 = func_0x7ffe9bbab340(uVar16,0);
      *(uint *)(thisObject + 0x104) = bVar17 | uVar10;
      return;
    }
    if ((((longlong *)target != (longlong *)0x0) &&
        (plVar12 = (longlong *)
                   (**(code **)(*(longlong *)target + 0x298))
                             (target,*(undefined8 *)(*(longlong *)target + 0x2a0)),
        plVar12 != (longlong *)0x0)) &&
       (thisObject_00 =
             (undefined *)(**(code **)(*plVar12 + 0x218))(plVar12,*(undefined8 *)(*plVar12 + 0x220))
       , thisObject_00 != (undefined *)0x0)) {
      iVar8 = GemCartBufferManager_GetBufferLevel(thisObject_00,0x2e,(undefined *)0x0);
      thisObject[0x12a] = (char)iVar8;
      plVar12 = (longlong *)
                (**(code **)(*(longlong *)target + 0x298))
                          (target,*(undefined8 *)(*(longlong *)target + 0x2a0));
      if (plVar12 != (longlong *)0x0) {
        uVar13 = (**(code **)(*plVar12 + 0x1c8))(plVar12,*(undefined8 *)(*plVar12 + 0x1d0));
        *(undefined8 *)(lVar11 + 0x18) = uVar13;
        il2cpp_write_barrier_0();
        bVar6 = true;
        if (*(longlong *)(lVar11 + 0x18) != 0) {
          target = (undefined *)FUN_7ffe9a7c8af0(*(longlong *)(lVar11 + 0x18),0x18000,0);
          if (((longlong *)target != (longlong *)0x0) &&
             (iVar8 = FUN_7ffe99742ec0(0,_DAT_7ffe9c950de8,target), 0 < iVar8)) {
            lVar2 = *(longlong *)target;
            if (*(ushort *)(lVar2 + 0x12e) != 0) {
              uVar15 = 0;
              do {
                if (*(longlong *)(*(longlong *)(lVar2 + 0xb0) + (ulonglong)uVar15 * 0x10) ==
                    _DAT_7ffe9c955e78) {
                  puVar14 = (undefined8 *)
                            (lVar2 + 0x138 +
                            (longlong)
                            *(int *)(*(longlong *)(lVar2 + 0xb0) + 8 + (ulonglong)uVar15 * 0x10) *
                            0x10);
                  goto LAB_7ffe9a8235e6;
                }
                uVar15 = uVar15 + 1;
              } while (uVar15 < *(ushort *)(lVar2 + 0x12e));
            }
            puVar14 = (undefined8 *)FUN_7ffe998ce540(target,_DAT_7ffe9c955e78,0);
LAB_7ffe9a8235e6:
            plStack_c0 = (longlong *)(*(code *)*puVar14)(target,puVar14[1]);
            uStack_b8 = 0;
            pplStack_b0 = &plStack_c0;
            while (plStack_c0 != (longlong *)0x0) {
              cVar7 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ac18);
              plVar12 = plStack_c0;
              if (cVar7 == '\0') {
                FUN_7ffe99a2cac0(&pplStack_b0);
                if (bVar6) goto LAB_7ffe9a8237dc;
                goto LAB_7ffe9a8237fc;
              }
              if (plStack_c0 == (longlong *)0x0) goto LAB_7ffe9a823b1c;
              lVar2 = *plStack_c0;
              if (*(ushort *)(lVar2 + 0x12e) != 0) {
                uVar15 = 0;
                do {
                  if (*(longlong *)(*(longlong *)(lVar2 + 0xb0) + (ulonglong)uVar15 * 0x10) ==
                      _DAT_7ffe9c95b950) {
                    puVar14 = (undefined8 *)
                              (lVar2 + 0x138 +
                              (longlong)
                              *(int *)(*(longlong *)(lVar2 + 0xb0) + 8 + (ulonglong)uVar15 * 0x10) *
                              0x10);
                    goto LAB_7ffe9a823699;
                  }
                  uVar15 = uVar15 + 1;
                } while (uVar15 < *(ushort *)(lVar2 + 0x12e));
              }
              puVar14 = (undefined8 *)FUN_7ffe998ce540(plStack_c0,_DAT_7ffe9c95b950,0);
LAB_7ffe9a823699:
              target = (undefined *)(*(code *)*puVar14)(plVar12,puVar14[1]);
              if ((longlong *)target == (longlong *)0x0) goto LAB_7ffe9a823b17;
              uVar9 = (**(code **)(*(longlong *)target + 0x178))
                                (target,*(undefined8 *)(*(longlong *)target + 0x180));
              if (*(int *)(_DAT_7ffe9c94f0d8 + 0xe0) == 0) {
                func_0x7ffe9996d830();
              }
              cVar7 = FUN_7ffe9a83a4f0(uVar9,0);
              if (cVar7 == '\0') {
                iVar8 = (**(code **)(*(longlong *)target + 0x178))
                                  (target,*(undefined8 *)(*(longlong *)target + 0x180));
                if (iVar8 == 0x52) {
                  if ((*(byte *)(*(longlong *)target + 0x130) < *(byte *)(_DAT_7ffe9c96e9e0 + 0x130)
                      ) || (*(longlong *)
                             (*(longlong *)(*(longlong *)target + 200) + -8 +
                             (ulonglong)*(byte *)(_DAT_7ffe9c96e9e0 + 0x130) * 8) !=
                            _DAT_7ffe9c96e9e0)) goto LAB_7ffe9a823b0f;
                  if ((char)*(longlong *)((longlong)target + 0x48) != '\0') {
                    bVar6 = false;
                  }
                }
                else {
                  bVar6 = false;
                }
              }
            }
            goto LAB_7ffe9a823b21;
          }
LAB_7ffe9a8237dc:
          if (*(longlong *)(lVar11 + 0x18) != 0) {
            cVar7 = FUN_7ffe9a7cbba0(*(longlong *)(lVar11 + 0x18),thisObject + 0x120,0);
            if (cVar7 == '\0') {
LAB_7ffe9a8237fc:
              if ((*(longlong *)(thisObject + 0x58) != 0) &&
                 (lVar11 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar11 != 0)) {
                FUN_7ffe9ad10e00(lVar11,8,0x644b32,_DAT_7ffe9c949490);
                if ((*(longlong *)(thisObject + 0x58) != 0) &&
                   (lVar11 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar11 != 0)) {
                  FUN_7ffe9ad10e00(lVar11,9,0,_DAT_7ffe9c949490);
                  uVar16 = 0;
                  goto LAB_7ffe9a823ad1;
                }
              }
            }
            else {
              plVar12 = *(longlong **)(thisObject + 0x120);
              if (plVar12 != (longlong *)0x0) {
                uVar10 = (**(code **)(*plVar12 + 0x178))(plVar12,*(undefined8 *)(*plVar12 + 0x180));
                plVar12 = (longlong *)(ulonglong)uVar10;
                lVar2 = *(longlong *)(thisObject + 0x120);
                if (lVar2 != 0) {
                  if ((*(char *)(lVar2 + 0x13) == '\0') &&
                     (cVar7 = FUN_7ffe9a7a3040(lVar2,0), cVar7 != '\0')) {
                    if (*(longlong *)(thisObject + 0x120) == 0) goto LAB_7ffe9a823b09;
                    if (*(char *)(*(longlong *)(thisObject + 0x120) + 0x21) != '\0')
                    goto LAB_7ffe9a82390e;
                    uVar1 = thisObject[0x14];
                    uVar10 = *(uint *)(thisObject + 0x10);
                    target = (undefined *)(ulonglong)uVar10;
                    uVar13 = func_0x7ffe99940040(_DAT_7ffe9c948f68);
                    FUN_7ffe9a7932d0(uVar13,uVar1,(char)uVar10,0);
                    if (*(longlong *)(lVar11 + 0x18) == 0) goto LAB_7ffe9a823b09;
                    FUN_7ffe9a7c26c0(*(longlong *)(lVar11 + 0x18),uVar13,thisObject[0x10],0);
                    bVar17 = 0;
                  }
                  else {
LAB_7ffe9a82390e:
                    if (thisObject[0x12a] == '\0') {
                      bVar17 = 1;
                      uVar13 = func_0x7ffe99940040(_DAT_7ffe9c94b460);
                      FUN_7ffe9a9002e0(uVar13,0xc0a7949,0);
                      *(undefined8 *)(thisObject + 0x58) = uVar13;
                      il2cpp_write_barrier_0();
                      if ((*(longlong *)(thisObject + 0x58) == 0) ||
                         (lVar2 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar2 == 0
                         )) goto LAB_7ffe9a823b09;
                      FUN_7ffe9ad10e00(lVar2,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490)
                      ;
                    }
                  }
                  target = (undefined *)FUN_7ffe9b141840(_DAT_7ffe9c9538a8);
                  plVar3 = *(longlong **)(thisObject + 0x120);
                  if ((plVar3 != (longlong *)0x0) &&
                     (uVar9 = (**(code **)(*plVar3 + 0x178))
                                        (plVar3,*(undefined8 *)(*plVar3 + 0x180)),
                     (longlong *)target != (longlong *)0x0)) {
                    puVar14 = (undefined8 *)FUN_7ffe9a57bd70(auStack_68,target,uVar9,0);
                    uVar13 = puVar14[2];
                    pplVar5 = (longlong **)puVar14[3];
                    target = (undefined *)0x0;
                    if (*(longlong *)(thisObject + 0x58) != 0) {
                      target = *(undefined **)(*(longlong *)(thisObject + 0x58) + 0x50);
                      uStack_b8 = *puVar14;
                      pplStack_b0 = (longlong **)puVar14[1];
                      uVar9 = FUN_7ffe99a5f3c0(&uStack_b8,0);
                      uVar9 = func_0x7ffe99a4d200(uVar9,0);
                      if ((longlong *)target != (longlong *)0x0) {
                        FUN_7ffe9ad10e00(target,8,uVar9,_DAT_7ffe9c949490);
                        if (*(longlong *)(thisObject + 0x58) != 0) {
                          lVar2 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50);
                          uStack_b8 = uVar13;
                          pplStack_b0 = pplVar5;
                          uVar9 = FUN_7ffe99a5f3c0(&uStack_b8,0);
                          uVar9 = func_0x7ffe99a4d200(uVar9,0);
                          target = (undefined *)0x0;
                          if (lVar2 != 0) {
                            FUN_7ffe9ad10e00(lVar2,9,uVar9,_DAT_7ffe9c949490);
                            uVar13 = func_0x7ffe99940040(_DAT_7ffe9c92eda0);
                            FUN_7ffe999e6880(uVar13,lVar11,_DAT_7ffe9c94da00,0);
                            FUN_7ffe9a4b20c0(thisObject,uVar13,0);
                            uVar13 = func_0x7ffe99940040(_DAT_7ffe9c8f3938);
                            FUN_7ffe9ac2ed50(uVar13,lVar11,_DAT_7ffe9c94dac8,0);
                            FUN_7ffe9a4b2010(thisObject,uVar13,0);
                            goto LAB_7ffe9a823ace;
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
LAB_7ffe9a823b09:
  FUN_7ffe9996d7a0();
LAB_7ffe9a823b0f:
  FUN_7ffe9996c950(target);
LAB_7ffe9a823b17:
  FUN_7ffe9996d7a0();
LAB_7ffe9a823b1c:
  FUN_7ffe9996d7a0();
LAB_7ffe9a823b21:
  FUN_7ffe9996d7a0();
  FUN_7ffe998fa550();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

