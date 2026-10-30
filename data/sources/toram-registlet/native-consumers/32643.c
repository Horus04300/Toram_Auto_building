
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MindimageSenjuSupportAction_ActionHit
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  undefined4 uVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  byte bVar5;
  undefined1 uVar6;
  int iVar7;
  uint uVar8;
  undefined4 uVar9;
  longlong *plVar10;
  longlong lVar11;
  undefined8 uVar12;
  longlong lVar13;
  longlong *plVar14;
  longlong *plVar15;
  undefined *thisObject_00;
  longlong *plVar16;
  undefined1 uVar17;
  undefined4 uVar18;
  longlong *plStackX_10;
  ulonglong in_stack_ffffffffffffff98;
  undefined8 in_stack_ffffffffffffffa0;
  ulonglong uVar19;
  undefined8 uVar20;
  longlong *plStack_48;
  longlong *aplStack_40 [3];
  
  uVar18 = (undefined4)((ulonglong)in_stack_ffffffffffffffa0 >> 0x20);
  if (DAT_7ffe9cadf865 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c953098);
    FUN_7ffe9996d590(&DAT_7ffe9c958a98);
    FUN_7ffe9996d590(&DAT_7ffe9c8ed850);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c91ac20);
    FUN_7ffe9996d590(&DAT_7ffe9c9279a8);
    FUN_7ffe9996d590(&DAT_7ffe9c929cd0);
    FUN_7ffe9996d590(&DAT_7ffe9c92b7a8);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c8ff608);
    FUN_7ffe9996d590(&DAT_7ffe9c903978);
    DAT_7ffe9cadf865 = '\x01';
  }
  plVar10 = (longlong *)0x0;
  plStack_48 = (longlong *)0x0;
  aplStack_40[0] = (longlong *)0x0;
  plStackX_10 = (longlong *)0x0;
  plVar16 = plVar10;
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar3 = false;
    }
    else {
      bVar3 = true;
    }
    plVar16 = (longlong *)0x0;
    if (bVar3) {
      plVar16 = (longlong *)actarAction;
    }
  }
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar4 = FUN_7ffe9bda2160(plVar16,0,0);
  if (cVar4 == '\0') {
    return;
  }
  if (thisObject[0x130] == '\0') {
    return;
  }
  plVar14 = *(longlong **)(thisObject + 0x128);
  if (plVar14 != (longlong *)0x0) {
    iVar7 = (**(code **)(*plVar14 + 0x188))(plVar14,*(undefined8 *)(*plVar14 + 400));
    plVar14 = *(longlong **)(thisObject + 0x128);
    if (plVar14 != (longlong *)0x0) {
      uVar17 = *(undefined1 *)((longlong)plVar14 + 0x14);
      if (iVar7 < 0x285) {
        if (iVar7 < 0x8f) {
          if (iVar7 == 0x2b) {
            uVar8 = *(uint *)(thisObject + 0xfc);
            lVar11 = func_0x7ffe99940040(_DAT_7ffe9c8ff608);
            FUN_7ffe9a7a63e0(lVar11,uVar17,uVar8 & 0xff,0);
            if ((((lVar11 != 0) && (*(undefined1 *)(lVar11 + 0x21) = 1, plVar16 != (longlong *)0x0))
                && (plVar10 = (longlong *)
                              (**(code **)(*plVar16 + 0x298))
                                        (plVar16,*(undefined8 *)(*plVar16 + 0x2a0)),
                   plVar10 != (longlong *)0x0)) &&
               (lVar13 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
               lVar13 != 0)) {
              FUN_7ffe9a7c1d20(lVar13,lVar11,0,0);
              return;
            }
          }
          else if (iVar7 == 0x45) {
            if (((plVar16 != (longlong *)0x0) &&
                (plVar10 = (longlong *)
                           (**(code **)(*plVar16 + 0x298))
                                     (plVar16,*(undefined8 *)(*plVar16 + 0x2a0)),
                plVar10 != (longlong *)0x0)) &&
               (thisObject_00 =
                     (undefined *)
                     (**(code **)(*plVar10 + 0x218))(plVar10,*(undefined8 *)(*plVar10 + 0x220)),
               thisObject_00 != (undefined *)0x0)) {
              bVar5 = GemCartBufferManager_ContainsBuffer(thisObject_00,0x405,(undefined *)0x0);
              lVar11 = func_0x7ffe99940040(_DAT_7ffe9c929cd0);
              FUN_7ffe9a790c50(lVar11,uVar17,bVar5,0);
              plVar10 = (longlong *)
                        (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
              if ((plVar10 != (longlong *)0x0) &&
                 (lVar13 = (**(code **)(*plVar10 + 0x1c8))
                                     (plVar10,*(undefined8 *)(*plVar10 + 0x1d0)), lVar13 != 0)) {
                uVar17 = thisObject[0x10];
                goto LAB_7ffe9a82c870;
              }
            }
          }
          else {
            if (iVar7 != 0x8e) {
              return;
            }
            uVar6 = FUN_7ffe9a4ad740(plVar16,0x10,0);
            lVar11 = func_0x7ffe99940040(_DAT_7ffe9c953098);
            FUN_7ffe9a77e4c0(lVar11,uVar17,1,uVar6,0);
            if (((plVar16 != (longlong *)0x0) &&
                (plVar10 = (longlong *)
                           (**(code **)(*plVar16 + 0x298))
                                     (plVar16,*(undefined8 *)(*plVar16 + 0x2a0)),
                plVar10 != (longlong *)0x0)) &&
               (lVar13 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
               lVar13 != 0)) {
              uVar17 = thisObject[0x10];
LAB_7ffe9a82c870:
              FUN_7ffe9a7c26c0(lVar13,lVar11,uVar17,0);
              return;
            }
          }
        }
        else if (iVar7 < 0x269) {
          if (iVar7 == 0x109) {
            if (((plVar16 != (longlong *)0x0) &&
                (plVar10 = (longlong *)
                           (**(code **)(*plVar16 + 0x298))
                                     (plVar16,*(undefined8 *)(*plVar16 + 0x2a0)),
                plVar10 != (longlong *)0x0)) &&
               (lVar11 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
               lVar11 != 0)) {
              plVar10 = (longlong *)FUN_7ffe9a7c2b40(lVar11,0x109,uVar17,0,0);
              if (plVar10 == (longlong *)0x0) {
                return;
              }
              if (*(byte *)(*plVar10 + 0x130) < *(byte *)(_DAT_7ffe9c91ac20 + 0x130)) {
                return;
              }
              if (*(longlong *)
                   (*(longlong *)(*plVar10 + 200) + -8 +
                   (ulonglong)*(byte *)(_DAT_7ffe9c91ac20 + 0x130) * 8) != _DAT_7ffe9c91ac20) {
                return;
              }
              lVar11 = (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
              plVar10[8] = lVar11;
              il2cpp_write_barrier_0();
              return;
            }
          }
          else {
            if (iVar7 != 0x268) {
              return;
            }
            lVar11 = func_0x7ffe99940040(_DAT_7ffe9c958a98);
            FUN_7ffe9a77ec30(lVar11,uVar17,0);
            iVar7 = FUN_7ffe9a4ae0a0(plVar16,0);
            if (iVar7 != 8) {
              iVar7 = FUN_7ffe9a4ade20(plVar16,0);
            }
            if (((lVar11 != 0) && (func_0x7ffe9a77ec10(lVar11,iVar7,0), plVar16 != (longlong *)0x0))
               && ((plVar10 = (longlong *)
                              (**(code **)(*plVar16 + 0x298))
                                        (plVar16,*(undefined8 *)(*plVar16 + 0x2a0)),
                   plVar10 != (longlong *)0x0 &&
                   (lVar13 = (**(code **)(*plVar10 + 0x1c8))
                                       (plVar10,*(undefined8 *)(*plVar10 + 0x1d0)), lVar13 != 0))))
            {
              uVar17 = thisObject[0x10];
              goto LAB_7ffe9a82c870;
            }
          }
        }
        else {
          if (iVar7 == 0x26e) {
            if ((*(byte *)(*plVar14 + 0x130) < *(byte *)(_DAT_7ffe9c903978 + 0x130)) ||
               (*(longlong *)
                 (*(longlong *)(*plVar14 + 200) + -8 +
                 (ulonglong)*(byte *)(_DAT_7ffe9c903978 + 0x130) * 8) != _DAT_7ffe9c903978)) {
              bVar3 = false;
            }
            else {
              bVar3 = true;
            }
            if (bVar3) {
              plVar10 = plVar14;
            }
            FUN_7ffe9a847400(plVar10,plVar16,0);
            return;
          }
          if (iVar7 != 0x284) {
            return;
          }
          if ((((plVar16 != (longlong *)0x0) &&
               (plVar10 = (longlong *)
                          (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0))
               , plVar10 != (longlong *)0x0)) &&
              (lVar11 = (**(code **)(*plVar10 + 0x1f8))(plVar10,*(undefined8 *)(*plVar10 + 0x200)),
              lVar11 != 0)) && (*(longlong *)(lVar11 + 0x18) != 0)) {
            func_0x7ffe99c1ed70(*(longlong *)(lVar11 + 0x18),0);
            plVar10 = (longlong *)
                      (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
            if (((plVar10 != (longlong *)0x0) &&
                (lVar11 = (**(code **)(*plVar10 + 0x1f8))(plVar10,*(undefined8 *)(*plVar10 + 0x200))
                , lVar11 != 0)) && (*(longlong *)(lVar11 + 0x20) != 0)) {
              func_0x7ffe99c1ed70(*(longlong *)(lVar11 + 0x20),0);
              plVar10 = (longlong *)
                        (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
              if ((plVar10 != (longlong *)0x0) &&
                 (lVar11 = (**(code **)(*plVar10 + 0x1c8))
                                     (plVar10,*(undefined8 *)(*plVar10 + 0x1d0)), lVar11 != 0)) {
                FUN_7ffe9a7c22c0(lVar11,0x284,uVar17);
                return;
              }
            }
          }
        }
      }
      else if (iVar7 < 0x3c6) {
        if (iVar7 == 0x28a) {
          if (((plVar16 != (longlong *)0x0) &&
              (plVar10 = (longlong *)
                         (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0)),
              plVar10 != (longlong *)0x0)) &&
             ((lVar11 = (**(code **)(*plVar10 + 0x1f8))(plVar10,*(undefined8 *)(*plVar10 + 0x200)),
              lVar11 != 0 && (*(longlong *)(lVar11 + 0x18) != 0)))) {
            func_0x7ffe99c1ed70(*(longlong *)(lVar11 + 0x18),0);
            plVar10 = (longlong *)
                      (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
            if (((plVar10 != (longlong *)0x0) &&
                (lVar11 = (**(code **)(*plVar10 + 0x1f8))(plVar10,*(undefined8 *)(*plVar10 + 0x200))
                , lVar11 != 0)) && (*(longlong *)(lVar11 + 0x20) != 0)) {
              func_0x7ffe99c1ed70(*(longlong *)(lVar11 + 0x20),0);
              plVar10 = (longlong *)
                        (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
              if ((plVar10 != (longlong *)0x0) &&
                 (lVar11 = (**(code **)(*plVar10 + 0x1c8))
                                     (plVar10,*(undefined8 *)(*plVar10 + 0x1d0)), lVar11 != 0)) {
                FUN_7ffe9a7c22c0(lVar11,0x28a,uVar17);
                return;
              }
            }
          }
        }
        else if (iVar7 == 0x34b) {
          if (((plVar16 != (longlong *)0x0) &&
              (plVar10 = (longlong *)
                         (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0)),
              plVar10 != (longlong *)0x0)) &&
             (lVar11 = (**(code **)(*plVar10 + 0x1f8))(plVar10,*(undefined8 *)(*plVar10 + 0x200)),
             lVar11 != 0)) {
            FUN_7ffe99c08fe0(lVar11,0);
            uVar18 = 0;
            plVar10 = (longlong *)
                      (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
            if ((plVar10 != (longlong *)0x0) &&
               (lVar11 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
               lVar11 != 0)) {
              cVar4 = FUN_7ffe9a7cbb30(lVar11,0x34b,&plStackX_10,0);
              if (cVar4 != '\0') {
                if (plStackX_10 == (longlong *)0x0) goto LAB_7ffe9a82d506;
                if (((*(byte *)(*plStackX_10 + 0x130) < *(byte *)(_DAT_7ffe9c92b7a8 + 0x130)) ||
                    (*(longlong *)
                      (*(longlong *)(*plStackX_10 + 200) + -8 +
                      (ulonglong)*(byte *)(_DAT_7ffe9c92b7a8 + 0x130) * 8) != _DAT_7ffe9c92b7a8)) ||
                   (plStackX_10 == (longlong *)0x0)) {
                  FUN_7ffe9996c950(plStackX_10);
                  pcVar2 = (code *)swi(3);
                  (*pcVar2)();
                  return;
                }
                uVar18 = (undefined4)plStackX_10[4];
              }
              plVar10 = (longlong *)
                        (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
              if ((plVar10 != (longlong *)0x0) &&
                 (lVar11 = (**(code **)(*plVar10 + 0x1c8))
                                     (plVar10,*(undefined8 *)(*plVar10 + 0x1d0)), lVar11 != 0)) {
                uVar20 = 0;
                uVar19 = (ulonglong)(byte)*(undefined4 *)(thisObject + 0x10);
                in_stack_ffffffffffffff98 = in_stack_ffffffffffffff98 & 0xffffffff00000000;
                plVar10 = (longlong *)FUN_7ffe9a7c2660(lVar11,0x34b,uVar17);
                plStackX_10 = plVar10;
                uVar12 = (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
                if (plVar10 != (longlong *)0x0) {
                  if ((*(byte *)(_DAT_7ffe9c92b7a8 + 0x130) <= *(byte *)(*plVar10 + 0x130)) &&
                     (*(longlong *)
                       (*(longlong *)(*plVar10 + 200) + -8 +
                       (ulonglong)*(byte *)(_DAT_7ffe9c92b7a8 + 0x130) * 8) == _DAT_7ffe9c92b7a8)) {
                    FUN_7ffe9a7911c0(plVar10,uVar12,uVar18,0,in_stack_ffffffffffffff98,uVar19,uVar20
                                    );
                    return;
                  }
                  FUN_7ffe9996c950(plVar10,_DAT_7ffe9c92b7a8);
                  pcVar2 = (code *)swi(3);
                  (*pcVar2)();
                  return;
                }
              }
            }
          }
        }
        else {
          if (iVar7 != 0x3c5) {
            return;
          }
          if (((plVar16 != (longlong *)0x0) &&
              (plVar10 = (longlong *)
                         (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0)),
              plVar10 != (longlong *)0x0)) &&
             (lVar13 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
             lVar13 != 0)) {
            lVar11 = *(longlong *)(thisObject + 0x138);
            uVar17 = 0;
            goto LAB_7ffe9a82c870;
          }
        }
      }
      else if (iVar7 < 0x3e0) {
        if (iVar7 == 0x3ce) {
          uVar9 = 0xffffffff;
          if ((((plVar16 != (longlong *)0x0) &&
               (plVar14 = (longlong *)
                          (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0))
               , plVar14 != (longlong *)0x0)) &&
              (lVar11 = (**(code **)(*plVar14 + 0x1c8))(plVar14,*(undefined8 *)(*plVar14 + 0x1d0)),
              lVar11 != 0)) && (*(longlong *)(lVar11 + 0x40) != 0)) {
            cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar11 + 0x40),0x3ce,&plStack_48,
                                     _DAT_7ffe9c934418);
            plVar14 = plStack_48;
            if (cVar4 == '\0') {
              plVar14 = (longlong *)
                        (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
              if ((plVar14 != (longlong *)0x0) &&
                 (lVar11 = (**(code **)(*plVar14 + 0x1c8))
                                     (plVar14,*(undefined8 *)(*plVar14 + 0x1d0)), lVar11 != 0)) {
                plVar15 = (longlong *)FUN_7ffe9a7c2b40(lVar11,0x3ce,uVar17,thisObject[0x10],0);
                if (plVar15 == (longlong *)0x0) {
                  return;
                }
                if ((*(byte *)(*plVar15 + 0x130) < *(byte *)(_DAT_7ffe9c9279a8 + 0x130)) ||
                   (*(longlong *)
                     (*(longlong *)(*plVar15 + 200) + -8 +
                     (ulonglong)*(byte *)(_DAT_7ffe9c9279a8 + 0x130) * 8) != _DAT_7ffe9c9279a8)) {
                  bVar3 = false;
                }
                else {
                  bVar3 = true;
                }
                plVar14 = plVar10;
                if (bVar3) {
                  plVar14 = plVar15;
                }
                if (plVar14 == (longlong *)0x0) {
                  return;
                }
                goto LAB_7ffe9a82ca94;
              }
            }
            else if (plStack_48 != (longlong *)0x0) {
              if (((*(byte *)(_DAT_7ffe9c9279a8 + 0x130) <= *(byte *)(*plStack_48 + 0x130)) &&
                  (*(longlong *)
                    (*(longlong *)(*plStack_48 + 200) + -8 +
                    (ulonglong)*(byte *)(_DAT_7ffe9c9279a8 + 0x130) * 8) == _DAT_7ffe9c9279a8)) &&
                 (plStack_48 != (longlong *)0x0)) {
                uVar8 = (**(code **)(*plStack_48 + 0x1f8))
                                  (plStack_48,0x32,*(undefined8 *)(*plStack_48 + 0x200));
                plVar10 = (longlong *)(ulonglong)uVar8;
                if ((int)uVar8 < 3) {
                  plVar15 = (longlong *)
                            (**(code **)(*plVar16 + 0x298))
                                      (plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
                  if ((plVar15 == (longlong *)0x0) ||
                     (lVar11 = (**(code **)(*plVar15 + 0x1c8))
                                         (plVar15,*(undefined8 *)(*plVar15 + 0x1d0)), lVar11 == 0))
                  goto LAB_7ffe9a82d506;
                  uVar9 = func_0x7ffe9a7cbf90(lVar11,plVar14,0,0);
                }
LAB_7ffe9a82ca94:
                uVar1 = *(undefined4 *)(thisObject + 0xfc);
                uVar12 = (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
                FUN_7ffe9a78f930(plVar14,uVar1,plVar10,uVar17,uVar12,CONCAT44(uVar18,uVar9),0);
                return;
              }
            }
          }
        }
        else {
          if (2 < iVar7 - 0x3ddU) {
            return;
          }
          if (((plVar16 != (longlong *)0x0) &&
              (plVar10 = (longlong *)
                         (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0)),
              plVar10 != (longlong *)0x0)) &&
             ((lVar11 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
              lVar11 != 0 && (*(longlong *)(lVar11 + 0x40) != 0)))) {
            cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar11 + 0x40),0x3ce,aplStack_40,
                                     _DAT_7ffe9c934418);
            if (cVar4 == '\0') {
              plVar10 = (longlong *)
                        (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
              if ((plVar10 != (longlong *)0x0) &&
                 (lVar11 = (**(code **)(*plVar10 + 0x1c8))
                                     (plVar10,*(undefined8 *)(*plVar10 + 0x1d0)), lVar11 != 0)) {
                plVar10 = (longlong *)
                          FUN_7ffe9a7c2b40(lVar11,0x3ce,thisObject[0x14],thisObject[0x10],0);
                if (plVar10 == (longlong *)0x0) {
                  return;
                }
                if (*(byte *)(*plVar10 + 0x130) < *(byte *)(_DAT_7ffe9c9279a8 + 0x130)) {
                  return;
                }
                if (*(longlong *)
                     (*(longlong *)(*plVar10 + 200) + -8 +
                     (ulonglong)*(byte *)(_DAT_7ffe9c9279a8 + 0x130) * 8) != _DAT_7ffe9c9279a8) {
                  return;
                }
LAB_7ffe9a82cc41:
                FUN_7ffe9a78fa90(plVar10,*(undefined4 *)(thisObject + 0xfc),0x3e0 - iVar7,
                                 thisObject[0x14],plVar16,0);
                return;
              }
            }
            else if (aplStack_40[0] != (longlong *)0x0) {
              if (((*(byte *)(_DAT_7ffe9c9279a8 + 0x130) <= *(byte *)(*aplStack_40[0] + 0x130)) &&
                  (*(longlong *)
                    (*(longlong *)(*aplStack_40[0] + 200) + -8 +
                    (ulonglong)*(byte *)(_DAT_7ffe9c9279a8 + 0x130) * 8) == _DAT_7ffe9c9279a8)) &&
                 (plVar10 = aplStack_40[0], aplStack_40[0] != (longlong *)0x0))
              goto LAB_7ffe9a82cc41;
            }
          }
        }
      }
      else if (iVar7 == 0x482) {
        if (((plVar16 != (longlong *)0x0) &&
            (plVar10 = (longlong *)
                       (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0)),
            plVar10 != (longlong *)0x0)) &&
           (lVar11 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
           lVar11 != 0)) {
          FUN_7ffe9a7c2b40(lVar11,0x482,uVar17,thisObject[0x10],0);
          return;
        }
      }
      else {
        if (iVar7 != 0x487) {
          return;
        }
        if (plVar16 != (longlong *)0x0) {
          uVar12 = (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
          lVar11 = func_0x7ffe99940040(_DAT_7ffe9c8ed850);
          FUN_7ffe9a7811f0(lVar11,uVar17,uVar12,0);
          plVar10 = (longlong *)
                    (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
          if ((plVar10 != (longlong *)0x0) &&
             (lVar13 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
             lVar13 != 0)) {
            uVar17 = 0;
            goto LAB_7ffe9a82c870;
          }
        }
      }
    }
  }
LAB_7ffe9a82d506:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

