
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobaPlayerBattleManager_OnSkillActionEnd
               (undefined *thisObject,undefined *target,undefined *targetActManager,
               undefined *action,undefined *methodInfo)

{
  float fVar1;
  float fVar2;
  byte bVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  code *pcVar7;
  bool bVar8;
  undefined4 uVar9;
  char cVar10;
  undefined1 uVar11;
  short sVar12;
  ushort uVar13;
  int iVar14;
  longlong lVar15;
  longlong *plVar16;
  longlong *plVar17;
  undefined *puVar18;
  undefined8 uVar19;
  undefined8 uVar20;
  longlong *plVar21;
  longlong lVar22;
  longlong lVar23;
  undefined8 *puVar24;
  longlong *plStack_e0;
  undefined8 uStack_d8;
  undefined8 *puStack_d0;
  longlong lStack_c8;
  undefined8 uStack_c0;
  undefined8 *puStack_b8;
  longlong lStack_b0;
  undefined8 uStack_a8;
  undefined4 uStack_a0;
  undefined8 uStack_98;
  undefined4 uStack_90;
  undefined1 auStack_80 [16];
  undefined1 auStack_70 [72];
  
  if (DAT_7ffe9caddc3f == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c941198);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c91b2b0);
    FUN_7ffe9996d590(&DAT_7ffe9c91b380);
    FUN_7ffe9996d590(0x7ffe9c91b450);
    FUN_7ffe9996d590(&DAT_7ffe9c962758);
    FUN_7ffe9996d590(&DAT_7ffe9c9136f8);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f7490);
    FUN_7ffe9996d590(&DAT_7ffe9c8f7ff0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c914fd0);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c9228b0);
    FUN_7ffe9996d590(&DAT_7ffe9c952a50);
    FUN_7ffe9996d590(&DAT_7ffe9c955480);
    FUN_7ffe9996d590(&DAT_7ffe9c956938);
    FUN_7ffe9996d590(&DAT_7ffe9c956ad0);
    FUN_7ffe9996d590(&DAT_7ffe9c94c0a0);
    DAT_7ffe9caddc3f = '\x01';
  }
  uStack_c0 = 0;
  puStack_b8 = (undefined8 *)0x0;
  lStack_b0 = 0;
  plVar21 = (longlong *)0x0;
  plStack_e0 = (longlong *)0x0;
  lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
  if (lVar15 != 0) {
    FUN_7ffe9a29adb0(lVar15,0);
    if ((action != (undefined *)0x0) && (*(longlong *)(thisObject + 200) != 0)) {
      FUN_7ffe99aaebf0(*(longlong *)(thisObject + 200),*(undefined4 *)(action + 0x10));
      cVar10 = (**(code **)(*(longlong *)action + 0x2c8))
                         (action,*(undefined8 *)(*(longlong *)action + 0x2d0));
      if (cVar10 == '\0') {
        plVar16 = *(longlong **)(thisObject + 0x80);
        if (((plVar16 == (longlong *)0x0) ||
            (plVar16 = (longlong *)
                       (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0)),
            plVar16 == (longlong *)0x0)) ||
           (lVar15 = (**(code **)(*plVar16 + 0x1e8))(plVar16,*(undefined8 *)(*plVar16 + 0x1f0)),
           lVar15 == 0)) goto LAB_7ffe9a436072;
        func_0x7ffe9a4dbd30(lVar15,0xfc);
        if ((*(longlong *)(thisObject + 0x88) != 0) &&
           (cVar10 = func_0x7ffe9a4ceea0(*(longlong *)(thisObject + 0x88),0), cVar10 != '\0')) {
          if ((*(longlong *)(thisObject + 0x88) == 0) ||
             (lVar15 = *(longlong *)(*(longlong *)(thisObject + 0x88) + 0x30), lVar15 == 0))
          goto LAB_7ffe9a436072;
          sVar12 = FUN_7ffe9a7f21f0(lVar15,0);
          if (*(int *)(_DAT_7ffe9c94c0a0 + 0xe0) == 0) {
            func_0x7ffe9996d830();
          }
          cVar10 = FUN_7ffe9a811510(action,(int)sVar12);
          if (cVar10 != '\0') {
            if (*(longlong *)(thisObject + 0x88) == 0) goto LAB_7ffe9a436072;
            func_0x7ffe9a4115d0(*(longlong *)(thisObject + 0x88),0);
          }
        }
        iVar14 = (**(code **)(*(longlong *)action + 0x188))
                           (action,*(undefined8 *)(*(longlong *)action + 400));
        if (iVar14 == 0x283) {
          plVar16 = *(longlong **)(thisObject + 0x28);
          if (plVar16 == (longlong *)0x0) goto LAB_7ffe9a436072;
          if (((*(byte *)(*plVar16 + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
              (*(longlong *)
                (*(longlong *)(*plVar16 + 200) + -8 +
                (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) ||
             ((plVar17 = (longlong *)
                         (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0)),
              plVar17 == (longlong *)0x0 ||
              ((lVar15 = (**(code **)(*plVar17 + 0x1c8))(plVar17,*(undefined8 *)(*plVar17 + 0x1d0)),
               lVar15 == 0 || (*(longlong *)(lVar15 + 0x40) == 0)))))) goto LAB_7ffe9a436072;
          cVar10 = FUN_7ffe9ad8e670(*(longlong *)(lVar15 + 0x40),0x283,&plStack_e0,_DAT_7ffe9c934418
                                   );
          if (cVar10 != '\0') {
            if (plStack_e0 == (longlong *)0x0) goto LAB_7ffe9a436072;
            bVar3 = *(byte *)(_DAT_7ffe9c914fd0 + 0x130);
            if (((*(byte *)(*plStack_e0 + 0x130) < bVar3) ||
                (lVar15 = *(longlong *)(*plStack_e0 + 200),
                *(longlong *)(lVar15 + -8 + (ulonglong)bVar3 * 8) != _DAT_7ffe9c914fd0)) ||
               (plStack_e0 == (longlong *)0x0)) goto LAB_7ffe9a436072;
            plVar17 = plVar21;
            if (*(longlong *)(lVar15 + -8 + (ulonglong)bVar3 * 8) == _DAT_7ffe9c914fd0) {
              plVar17 = plStack_e0;
            }
            if (*(char *)((longlong)plVar17 + 0x24) == '\0') {
              plVar16 = (longlong *)
                        (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0));
              if ((plVar16 == (longlong *)0x0) ||
                 (lVar15 = (**(code **)(*plVar16 + 0x1c8))
                                     (plVar16,*(undefined8 *)(*plVar16 + 0x1d0)), lVar15 == 0))
              goto LAB_7ffe9a436072;
              FUN_7ffe9a7cafa0(lVar15,0x283);
            }
          }
        }
        cVar10 = (**(code **)(*(longlong *)action + 0x228))
                           (action,*(undefined8 *)(*(longlong *)action + 0x230));
        if (cVar10 == '\0') {
          *(float *)(thisObject + 0xd0) = *(float *)(action + 0x2c) + *(float *)(thisObject + 0xd0);
          plVar16 = *(longlong **)(thisObject + 0x80);
          if (((plVar16 == (longlong *)0x0) ||
              (plVar16 = (longlong *)
                         (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0)),
              plVar16 == (longlong *)0x0)) ||
             (lVar15 = (**(code **)(*plVar16 + 0x1c8))(plVar16,*(undefined8 *)(*plVar16 + 0x1d0)),
             lVar15 == 0)) goto LAB_7ffe9a436072;
          cVar10 = FUN_7ffe9a7c6d00(lVar15,0x26c);
          if (cVar10 != '\0') {
            plVar16 = *(longlong **)(thisObject + 0x80);
            if ((plVar16 == (longlong *)0x0) ||
               (lVar15 = (**(code **)(*plVar16 + 0x2a8))(plVar16,*(undefined8 *)(*plVar16 + 0x2b0)),
               lVar15 == 0)) goto LAB_7ffe9a436072;
            cVar10 = FUN_7ffe9a4daa60(lVar15,6);
            if (cVar10 == '\0') {
              *(undefined4 *)(thisObject + 0xd0) = 0;
              thisObject[0x6e] = 0;
            }
          }
          plVar16 = *(longlong **)(thisObject + 0x80);
          if (((plVar16 == (longlong *)0x0) ||
              (plVar16 = (longlong *)
                         (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0)),
              plVar16 == (longlong *)0x0)) ||
             (lVar15 = (**(code **)(*plVar16 + 0x1c8))(plVar16,*(undefined8 *)(*plVar16 + 0x1d0)),
             lVar15 == 0)) goto LAB_7ffe9a436072;
          cVar10 = FUN_7ffe9a7c6d00(lVar15,299);
          if (cVar10 != '\0') {
            *(undefined4 *)(thisObject + 0xd0) = 0;
            thisObject[0x6e] = 0;
          }
          plVar16 = *(longlong **)(thisObject + 0x80);
          if (((plVar16 == (longlong *)0x0) ||
              (plVar16 = (longlong *)
                         (**(code **)(*plVar16 + 0x298))(plVar16,*(undefined8 *)(*plVar16 + 0x2a0)),
              plVar16 == (longlong *)0x0)) ||
             (puVar18 = (undefined *)
                        (**(code **)(*plVar16 + 0x218))(plVar16,*(undefined8 *)(*plVar16 + 0x220)),
             puVar18 == (undefined *)0x0)) goto LAB_7ffe9a436072;
          puVar18 = GemCartBufferManager_GetGemCartBuffer(puVar18,0x23,(undefined *)0x0);
          if ((puVar18 != (undefined *)0x0) &&
             (iVar14 = GemCartBufferBase_GetValue(puVar18,(undefined *)0x2,(undefined *)0x0),
             iVar14 != 0)) {
            *(undefined4 *)(thisObject + 0xd0) = 0;
            thisObject[0x6e] = 0;
          }
          if (0.0 < *(float *)(thisObject + 0xd0)) {
            thisObject[0x6e] = 1;
            lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
            if ((lVar15 == 0) || (lVar15 = FUN_7ffe9a29e310(lVar15,0), lVar15 == 0))
            goto LAB_7ffe9a436072;
            FUN_7ffe99d24d20(lVar15,1,*(undefined4 *)(thisObject + 0xd0));
          }
          cVar10 = (**(code **)(*(longlong *)action + 0x1f8))
                             (action,*(undefined8 *)(*(longlong *)action + 0x200));
          if (cVar10 != '\0') {
            thisObject[0x6a] = 0;
          }
          if (*(longlong *)(thisObject + 0x48) == 0) goto LAB_7ffe9a436072;
          cVar10 = FUN_7ffe9a9005a0(*(longlong *)(thisObject + 0x48),0);
          if (cVar10 != '\0') {
            if (thisObject[0xb8] != '\0') {
              uVar11 = (**(code **)(*(longlong *)action + 0x1d8))
                                 (action,*(undefined8 *)(*(longlong *)action + 0x1e0));
              thisObject[0xb8] = uVar11;
            }
            if ((*(longlong *)(thisObject + 0x88) != 0) &&
               (cVar10 = FUN_7ffe9a7efd70(*(longlong *)(thisObject + 0x88),0), cVar10 != '\0')) {
              if (*(longlong *)(thisObject + 0x88) == 0) goto LAB_7ffe9a436072;
              lVar15 = *(longlong *)(*(longlong *)(thisObject + 0x88) + 0x28);
              uVar20 = *(undefined8 *)(thisObject + 0x80);
              if (lVar15 == 0) goto LAB_7ffe9a436072;
              uVar19 = func_0x7ffe9996c920(targetActManager,_DAT_7ffe9c9724e0);
              FUN_7ffe9a7f0890(lVar15,uVar19,uVar20,0);
              if (*(longlong *)(thisObject + 0x88) == 0) goto LAB_7ffe9a436072;
              cVar10 = FUN_7ffe9a7f0020(*(longlong *)(thisObject + 0x88),0);
              if (cVar10 == '\0') {
                if ((*(longlong *)(thisObject + 0x88) == 0) ||
                   (lVar15 = *(longlong *)(*(longlong *)(thisObject + 0x88) + 0x28), lVar15 == 0))
                goto LAB_7ffe9a436072;
                uVar13 = FUN_7ffe9a7f21f0(lVar15,0);
                thisObject[0xd4] = 1;
                (**(code **)(*(longlong *)thisObject + 0x218))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x220));
                plVar21 = (longlong *)(ulonglong)uVar13;
              }
              else {
                lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
                if (lVar15 == 0) goto LAB_7ffe9a436072;
                FUN_7ffe9a8a75a0(lVar15,0);
                plVar21 = (longlong *)0x0;
              }
            }
            cVar10 = func_0x7ffe9a7e1180(thisObject,0);
            if (cVar10 == '\0') {
              if (*(longlong *)(thisObject + 0x80) == 0) goto LAB_7ffe9a436072;
              FUN_7ffe9a429820(*(longlong *)(thisObject + 0x80),plVar21,0);
            }
          }
          iVar14 = (**(code **)(*(longlong *)action + 0x188))
                             (action,*(undefined8 *)(*(longlong *)action + 400));
          if (iVar14 == 0x327) {
            uVar20 = FUN_7ffe9a7fb2c0(0x10,action[0x14],*(undefined8 *)(thisObject + 0x28),0);
            uVar19 = FUN_7ffe9bd98960(thisObject,0);
            (**(code **)(*(longlong *)thisObject + 0x2f8))
                      (thisObject,uVar19,*(undefined8 *)(thisObject + 0x28),uVar20,
                       *(undefined8 *)(*(longlong *)thisObject + 0x300));
            uVar19 = FUN_7ffe9bd98960(thisObject,0);
            (**(code **)(*(longlong *)thisObject + 0x368))
                      (thisObject,uVar19,*(undefined8 *)(thisObject + 0x28),uVar20,
                       *(undefined8 *)(*(longlong *)thisObject + 0x370));
            uVar19 = FUN_7ffe9bd98960(thisObject,0);
            (**(code **)(*(longlong *)thisObject + 0x348))
                      (thisObject,uVar19,*(undefined8 *)(thisObject + 0x28),uVar20,
                       *(undefined8 *)(*(longlong *)thisObject + 0x350));
            lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
            if (lVar15 == 0) goto LAB_7ffe9a436072;
            FUN_7ffe9a89e600(lVar15,uVar20,0);
          }
        }
        else {
          iVar14 = (**(code **)(*(longlong *)action + 0x188))
                             (action,*(undefined8 *)(*(longlong *)action + 400));
          if (iVar14 == 0x205) {
            fVar1 = *(float *)(action + 0x2c);
            if (DAT_7ffe9caddc40 == '\0') {
              FUN_7ffe9996d590(&DAT_7ffe9c956ad0);
              DAT_7ffe9caddc40 = '\x01';
            }
            fVar2 = *(float *)(thisObject + 0xd0);
            *(float *)(thisObject + 0xd0) = fVar1 + fVar2;
            if (0.0 < fVar1 + fVar2) {
              thisObject[0x6e] = 1;
              lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
              if ((lVar15 == 0) || (lVar15 = FUN_7ffe9a29e310(lVar15,0), lVar15 == 0))
              goto LAB_7ffe9a436072;
              FUN_7ffe99d24d20(lVar15,1,*(undefined4 *)(thisObject + 0xd0));
            }
          }
          cVar10 = func_0x7ffe9a7e1180(thisObject,0);
          if (cVar10 == '\0') {
            if (*(longlong *)(thisObject + 0x48) == 0) goto LAB_7ffe9a436072;
            cVar10 = FUN_7ffe9a9005a0(*(longlong *)(thisObject + 0x48),0);
            if (cVar10 != '\0') {
              if (thisObject[0xb8] != '\0') {
                uVar11 = (**(code **)(*(longlong *)action + 0x1d8))
                                   (action,*(undefined8 *)(*(longlong *)action + 0x1e0));
                thisObject[0xb8] = uVar11;
              }
              sVar12 = 0;
              if (*(longlong *)(thisObject + 0x48) == 0) goto LAB_7ffe9a436072;
              cVar10 = FUN_7ffe9a9005a0(*(longlong *)(thisObject + 0x48),0);
              if (((cVar10 != '\0') && (*(longlong *)(thisObject + 0x88) != 0)) &&
                 (cVar10 = FUN_7ffe9a7efd70(*(longlong *)(thisObject + 0x88),0), cVar10 != '\0')) {
                if (*(longlong *)(thisObject + 0x48) == 0) goto LAB_7ffe9a436072;
                uVar20 = *(undefined8 *)(*(longlong *)(thisObject + 0x48) + 0x18);
                if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                  func_0x7ffe9996d830();
                }
                cVar10 = FUN_7ffe9bda2160(uVar20,0,0);
                if (cVar10 != '\0') {
                  if ((*(longlong *)(thisObject + 0x48) == 0) ||
                     (lVar15 = *(longlong *)(*(longlong *)(thisObject + 0x48) + 0x18), lVar15 == 0))
                  goto LAB_7ffe9a436072;
                  plVar21 = (longlong *)FUN_7ffe9ab9c3a0(lVar15,_DAT_7ffe9c962758);
                }
                if ((*(longlong *)(thisObject + 0x88) == 0) ||
                   (lVar15 = *(longlong *)(*(longlong *)(thisObject + 0x88) + 0x28), lVar15 == 0))
                goto LAB_7ffe9a436072;
                FUN_7ffe9a7f0890(lVar15,plVar21,*(undefined8 *)(thisObject + 0x80),0);
                if (*(longlong *)(thisObject + 0x88) == 0) goto LAB_7ffe9a436072;
                cVar10 = FUN_7ffe9a7f0020(*(longlong *)(thisObject + 0x88),0);
                if (cVar10 == '\0') {
                  if ((*(longlong *)(thisObject + 0x88) == 0) ||
                     (lVar15 = *(longlong *)(*(longlong *)(thisObject + 0x88) + 0x28), lVar15 == 0))
                  goto LAB_7ffe9a436072;
                  sVar12 = FUN_7ffe9a7f21f0(lVar15,0);
                  thisObject[0xd4] = 1;
                  (**(code **)(*(longlong *)thisObject + 0x218))
                            (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x220));
                }
                else {
                  lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
                  if (lVar15 == 0) goto LAB_7ffe9a436072;
                  FUN_7ffe9a8a75a0(lVar15,0);
                  sVar12 = 0;
                }
              }
              if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c9228b0 + 0x130)) ||
                 (*(longlong *)
                   (*(longlong *)(*(longlong *)action + 200) + -8 +
                   (ulonglong)*(byte *)(_DAT_7ffe9c9228b0 + 0x130) * 8) != _DAT_7ffe9c9228b0))
              goto LAB_7ffe9a436072;
              iVar14 = (**(code **)(*(longlong *)action + 0x588))
                                 (action,*(undefined8 *)(*(longlong *)action + 0x590));
              bVar8 = true;
              if ((iVar14 == 0x18) && (bVar8 = true, sVar12 == 0)) {
                bVar8 = false;
              }
              plVar21 = *(longlong **)(thisObject + 0x80);
              if (((plVar21 == (longlong *)0x0) ||
                  (plVar21 = (longlong *)
                             (**(code **)(*plVar21 + 0x298))
                                       (plVar21,*(undefined8 *)(*plVar21 + 0x2a0)),
                  plVar21 == (longlong *)0x0)) ||
                 (lVar15 = (**(code **)(*plVar21 + 0x1c8))
                                     (plVar21,*(undefined8 *)(*plVar21 + 0x1d0)), lVar15 == 0))
              goto LAB_7ffe9a436072;
              cVar10 = FUN_7ffe9a7c6d00(lVar15,0x36e,0);
              if (((cVar10 == '\0') || (sVar12 != 0)) && (bVar8)) {
                plVar21 = *(longlong **)(thisObject + 0x28);
                if (plVar21 == (longlong *)0x0) goto LAB_7ffe9a436072;
                if ((*(byte *)(*plVar21 + 0x130) < *(byte *)(_DAT_7ffe9c8f7490 + 0x130)) ||
                   (*(longlong *)
                     (*(longlong *)(*plVar21 + 200) + -8 +
                     (ulonglong)*(byte *)(_DAT_7ffe9c8f7490 + 0x130) * 8) != _DAT_7ffe9c8f7490)) {
                  FUN_7ffe9996c950(plVar21);
LAB_7ffe9a436081:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a436086:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a43608b:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a436090:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a436095:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a43609a:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a43609f:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4360a4:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4360a9:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4360ae:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4360b3:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4360b8:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4360bd:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4360c2:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4360c7:
                  FUN_7ffe9996d7a0();
LAB_7ffe9a4360cc:
                  FUN_7ffe9996d7a0();
                  FUN_7ffe998fa550();
                  pcVar7 = (code *)swi(3);
                  (*pcVar7)();
                  return;
                }
                FUN_7ffe9a429820(plVar21,sVar12,0);
              }
            }
          }
        }
        (**(code **)(*(longlong *)thisObject + 600))
                  (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x260));
        func_0x7ffe9a8fe300(action,0);
        iVar14 = (**(code **)(*(longlong *)action + 0x188))
                           (action,*(undefined8 *)(*(longlong *)action + 400));
        if (iVar14 != 8) {
          lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
          if (lVar15 == 0) goto LAB_7ffe9a436072;
          FUN_7ffe9a89e8a0(lVar15,*(undefined8 *)(thisObject + 0x20),action,0);
        }
        iVar14 = (**(code **)(*(longlong *)action + 0x188))
                           (action,*(undefined8 *)(*(longlong *)action + 400));
        if (iVar14 == 0x65) {
          FUN_7ffe9a8fd7f0(action,0,0);
          FUN_7ffe9a42ea20(thisObject,action,0);
          lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
          if (lVar15 == 0) goto LAB_7ffe9a436072;
          FUN_7ffe9a89e600(lVar15,action,0);
        }
        if (*(int *)(thisObject + 0xd8) == 2) {
          lVar15 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
          if (lVar15 == 0) goto LAB_7ffe9a436072;
          plVar21 = *(longlong **)(lVar15 + 0x28);
          if (plVar21 != (longlong *)0x0) {
            if ((*(byte *)(_DAT_7ffe9c8f7ff0 + 0x130) <= *(byte *)(*plVar21 + 0x130)) &&
               (*(longlong *)
                 (*(longlong *)(*plVar21 + 200) + -8 +
                 (ulonglong)*(byte *)(_DAT_7ffe9c8f7ff0 + 0x130) * 8) == _DAT_7ffe9c8f7ff0)) {
              FUN_7ffe9a5f1d50(plVar21,0);
            }
          }
        }
      }
      else {
        iVar14 = (**(code **)(*(longlong *)action + 0x188))
                           (action,*(undefined8 *)(*(longlong *)action + 400));
        if (iVar14 != 0x11) {
          if (*(longlong *)(action + 0x80) == 0) goto LAB_7ffe9a436072;
          FUN_7ffe9af836a0(&uStack_d8,*(longlong *)(action + 0x80),_DAT_7ffe9c9136f8);
          uVar9 = _DAT_7ffe9c049b18;
          uStack_c0 = uStack_d8;
          puStack_b8 = puStack_d0;
          lStack_b0 = lStack_c8;
          uStack_d8 = 0;
          puStack_d0 = &uStack_c0;
          while (cVar10 = FUN_7ffe9ae28ed0(&uStack_c0,_DAT_7ffe9c91b380), lVar15 = lStack_b0,
                cVar10 != '\0') {
            cVar10 = '\x01';
            while (cVar10 != '\0') {
              lVar22 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
              if (lVar22 == 0) goto LAB_7ffe9a4360cc;
              uVar11 = FUN_7ffe9a8b14d0(lVar22,0);
              if (lVar15 == 0) goto LAB_7ffe9a4360c7;
              lVar22 = *(longlong *)(lVar15 + 0x10);
              uVar20 = FUN_7ffe9bd98960(thisObject,0);
              if (lVar22 == 0) goto LAB_7ffe9a4360c2;
              FUN_7ffe99744ed0(0xe,lVar22,uVar20,action,*(undefined8 *)(lVar15 + 0x38),uVar11);
              if (*(longlong *)(lVar15 + 0x38) == 0) goto LAB_7ffe9a4360bd;
              if (*(char *)(*(longlong *)(lVar15 + 0x38) + 0x38) == '\0') {
                iVar14 = (**(code **)(*(longlong *)action + 0x188))
                                   (action,*(undefined8 *)(*(longlong *)action + 400));
                if (iVar14 == 10) {
                  if (*(longlong *)(lVar15 + 0x38) == 0) goto LAB_7ffe9a4360b3;
                  uVar4 = *(undefined4 *)(*(longlong *)(lVar15 + 0x38) + 0x10);
                  if (*(int *)(_DAT_7ffe9c941198 + 0xe0) == 0) {
                    func_0x7ffe9996d830();
                  }
                  FUN_7ffe9a7dd820(1,uVar4,0);
                }
                else {
                  iVar14 = (**(code **)(*(longlong *)action + 0x188))
                                     (action,*(undefined8 *)(*(longlong *)action + 400));
                  if ((iVar14 == 0xb) ||
                     (iVar14 = (**(code **)(*(longlong *)action + 0x188))
                                         (action,*(undefined8 *)(*(longlong *)action + 400)),
                     iVar14 == 0xc)) {
                    if (*(longlong *)(lVar15 + 0x38) == 0) goto LAB_7ffe9a436095;
                    uVar4 = *(undefined4 *)(*(longlong *)(lVar15 + 0x38) + 0x10);
                    if (*(int *)(_DAT_7ffe9c941198 + 0xe0) == 0) {
                      func_0x7ffe9996d830();
                    }
                    FUN_7ffe9a7dcb00(uVar4,action,0);
                  }
                  else {
                    uVar4 = *(undefined4 *)(lVar15 + 0x1c);
                    if (*(longlong *)(lVar15 + 0x38) == 0) goto LAB_7ffe9a436090;
                    uVar5 = *(undefined4 *)(*(longlong *)(lVar15 + 0x38) + 0x10);
                    plVar21 = *(longlong **)(thisObject + 0x80);
                    if (plVar21 == (longlong *)0x0) goto LAB_7ffe9a43608b;
                    plVar21 = (longlong *)
                              (**(code **)(*plVar21 + 0x298))
                                        (plVar21,*(undefined8 *)(*plVar21 + 0x2a0));
                    if (plVar21 == (longlong *)0x0) goto LAB_7ffe9a436086;
                    lVar22 = (**(code **)(*plVar21 + 0x178))
                                       (plVar21,*(undefined8 *)(*plVar21 + 0x180));
                    if (lVar22 == 0) goto LAB_7ffe9a436081;
                    uVar6 = *(undefined4 *)(lVar22 + 0x14);
                    if (*(int *)(_DAT_7ffe9c941198 + 0xe0) == 0) {
                      func_0x7ffe9996d830();
                    }
                    FUN_7ffe9a7dcf30(uVar4,1,uVar5,uVar6,action,0);
                  }
                }
                lVar22 = FUN_7ffe9b141840(_DAT_7ffe9c956938);
                uVar4 = *(undefined4 *)(lVar15 + 0x1c);
                if (*(longlong *)(lVar15 + 0x38) == 0) goto LAB_7ffe9a4360ae;
                uVar5 = *(undefined4 *)(*(longlong *)(lVar15 + 0x38) + 0x10);
                lVar23 = FUN_7ffe9bd98a10(thisObject,0);
                if (lVar23 == 0) goto LAB_7ffe9a4360a9;
                puVar24 = (undefined8 *)FUN_7ffe9bdbf710(auStack_80,lVar23,0);
                uVar20 = *puVar24;
                uVar6 = *(undefined4 *)(puVar24 + 1);
                if (*(longlong *)(lVar15 + 0x10) == 0) goto LAB_7ffe9a4360a4;
                lVar23 = FUN_7ffe9bd98a10(*(longlong *)(lVar15 + 0x10),0);
                if (lVar23 == 0) goto LAB_7ffe9a43609f;
                puVar24 = (undefined8 *)FUN_7ffe9bdbf710(auStack_70,lVar23,0);
                if (lVar22 == 0) goto LAB_7ffe9a43609a;
                uStack_a8 = *puVar24;
                uStack_a0 = *(undefined4 *)(puVar24 + 1);
                uStack_98 = uVar20;
                uStack_90 = uVar6;
                FUN_7ffe99ca8580(lVar22,uVar4,1,uVar5,&uStack_98,&uStack_a8,uVar9,
                                 *(undefined1 *)(lVar15 + 0x30),0,0);
              }
              lVar22 = FUN_7ffe9b141840(_DAT_7ffe9c952a50);
              if (lVar22 == 0) goto LAB_7ffe9a4360b8;
              FUN_7ffe9a8a0c90(lVar22,action,uVar11,0);
              cVar10 = FUN_7ffe9a8f6320(lVar15);
            }
          }
          func_0x7ffe999c3920(&uStack_c0,_DAT_7ffe9c91b2b0);
        }
        (**(code **)(*(longlong *)thisObject + 600))
                  (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x260));
      }
      return;
    }
  }
LAB_7ffe9a436072:
  FUN_7ffe9996d7a0();
  pcVar7 = (code *)swi(3);
  (*pcVar7)();
  return;
}

