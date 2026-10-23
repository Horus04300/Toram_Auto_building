
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void EnemyMobActionManagerBase_Damaged
               (undefined *self,undefined *actor,undefined *action,undefined *damageData,byte id,
               undefined *methodInfo)

{
  undefined1 uVar1;
  byte bVar2;
  code *pcVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  longlong *plVar10;
  longlong lVar11;
  undefined8 *puVar12;
  longlong *plVar13;
  longlong lVar14;
  undefined8 uVar15;
  undefined *puVar16;
  bool bVar17;
  float fVar18;
  undefined8 in_stack_ffffffffffffff38;
  longlong *plStack_a8;
  longlong lStack_a0;
  longlong lStack_98;
  longlong lStack_90;
  longlong lStack_88;
  undefined8 uStack_80;
  float fStack_78;
  undefined8 uStack_68;
  float fStack_60;
  
  uVar8 = (undefined4)((ulonglong)in_stack_ffffffffffffff38 >> 0x20);
  if (DAT_7ffe9cadd4e1 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c931550);
    FUN_7ffe9996d590(&DAT_7ffe9c941198);
    FUN_7ffe9996d590(&DAT_7ffe9c947460);
    FUN_7ffe9996d590(&DAT_7ffe9c952e38);
    FUN_7ffe9996d590(&DAT_7ffe9c9120f0);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1b50);
    FUN_7ffe9996d590(&DAT_7ffe9c8f1f58);
    FUN_7ffe9996d590(&DAT_7ffe9c8f2028);
    FUN_7ffe9996d590(&DAT_7ffe9c903268);
    FUN_7ffe9996d590(&DAT_7ffe9c909998);
    FUN_7ffe9996d590(&DAT_7ffe9c963da8);
    FUN_7ffe9996d590(&DAT_7ffe9c92be80);
    FUN_7ffe9996d590(&DAT_7ffe9c93a908);
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    FUN_7ffe9996d590(&DAT_7ffe9c95e9a8);
    FUN_7ffe9996d590(&DAT_7ffe9c96e728);
    FUN_7ffe9996d590(&DAT_7ffe9c8feb30);
    FUN_7ffe9996d590(&DAT_7ffe9c900bb0);
    FUN_7ffe9996d590(&DAT_7ffe9c904080);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c9228b0);
    FUN_7ffe9996d590(&DAT_7ffe9c94c0a0);
    FUN_7ffe9996d590(&DAT_7ffe9c94c3b0);
    DAT_7ffe9cadd4e1 = '\x01';
  }
  lStack_98 = 0;
  lStack_90 = 0;
  lStack_88 = 0;
  lStack_a0 = 0;
  plStack_a8 = (longlong *)0x0;
  cVar4 = (**(code **)(*(longlong *)self + 0x1a8))(self,*(undefined8 *)(*(longlong *)self + 0x1b0));
  if (cVar4 != '\0') {
    return;
  }
  if (self[0x41] == '\0') {
    return;
  }
  if (self[0x149] != '\0') {
    uVar15 = *(undefined8 *)(self + 0x30);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar4 = FUN_7ffe9bda1fa0(uVar15,0,0);
    if (cVar4 != '\0') {
      (**(code **)(*(longlong *)self + 0x608))
                (self,actor,0,*(undefined8 *)(*(longlong *)self + 0x610));
    }
  }
  if (damageData == (undefined *)0x0) {
    return;
  }
  cVar4 = (**(code **)(*(longlong *)self + 0x188))(self,*(undefined8 *)(*(longlong *)self + 400));
  if (*(int *)(damageData + 0x18) == 1) {
    if (damageData[0x3a] == '\0') {
      if (*(longlong *)(self + 0x60) == 0) goto LAB_7ffe9a31027c;
      FUN_7ffe99eed250(*(longlong *)(self + 0x60),actor,0);
      if (*(int *)(_DAT_7ffe9c941198 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      FUN_7ffe9a7dccb0(0,action,0);
    }
  }
  else if (*(int *)(damageData + 0x18) == 2) {
    if (*(longlong *)(self + 0x60) == 0) goto LAB_7ffe9a31027c;
    FUN_7ffe99eee0b0(*(longlong *)(self + 0x60),actor,0);
    if ((*(int *)(damageData + 0x8c) == 4) || (*(int *)(damageData + 0x8c) - 0xbU < 2)) {
      *(undefined4 *)(damageData + 0x94) = 0;
    }
  }
  cVar5 = FUN_7ffe9a30c960(self,damageData,0);
  if (cVar5 == '\0') {
    return;
  }
  if (*(int *)(damageData + 0x14) != 0) {
    if (actor == (undefined *)0x0) goto LAB_7ffe9a31027c;
    plVar10 = (longlong *)FUN_7ffe9ab9c3a0(actor,_DAT_7ffe9c963da8);
    if ((damageData[0x22] != '\0') || (damageData[0x21] != '\0')) {
      uVar15 = *(undefined8 *)(self + 200);
      if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      cVar5 = FUN_7ffe9bda2160(uVar15,0,0);
      if (cVar5 != '\0') {
        cVar5 = FUN_7ffe9ab798a0(self,0x21,&lStack_98,_DAT_7ffe9c8f1f58);
        if ((cVar5 == '\0') || (damageData[0x22] == '\0')) {
          cVar5 = FUN_7ffe9ab798a0(self,0x22,&lStack_90,_DAT_7ffe9c8f2028);
          if ((cVar5 == '\0') || (damageData[0x21] == '\0')) {
            cVar5 = FUN_7ffe9ab798a0(self,5,&lStack_88,_DAT_7ffe9c8f1b50);
            if (cVar5 == '\0') goto LAB_7ffe9a30ee59;
            if (lStack_88 == 0) goto LAB_7ffe9a31027c;
            fVar18 = (float)FUN_7ffe9a379290(lStack_88,0);
          }
          else {
            if (lStack_90 == 0) goto LAB_7ffe9a31027c;
            fVar18 = (float)FUN_7ffe9a379290(lStack_90,0);
          }
        }
        else {
          if (lStack_98 == 0) goto LAB_7ffe9a31027c;
          fVar18 = (float)FUN_7ffe9a379290(lStack_98,0);
        }
        if (fVar18 != 0.0) {
          lVar14 = *(longlong *)(self + 200);
          lVar11 = func_0x7ffe9996c990(_DAT_7ffe9c9120f0,3);
          puVar12 = (undefined8 *)func_0x7ffe99a4d950(&uStack_68,0x7fffffff,0);
          if (lVar11 == 0) goto LAB_7ffe9a31027c;
          if (*(int *)(lVar11 + 0x18) == 0) {
LAB_7ffe9a310263:
            FUN_7ffe9996d790();
            pcVar3 = (code *)swi(3);
            (*pcVar3)();
            return;
          }
          uVar15 = puVar12[1];
          *(undefined8 *)(lVar11 + 0x20) = *puVar12;
          *(undefined8 *)(lVar11 + 0x28) = uVar15;
          puVar12 = (undefined8 *)func_0x7ffe99a4d950(&uStack_68,0x7fffffff,0);
          if (*(uint *)(lVar11 + 0x18) < 2) goto LAB_7ffe9a310263;
          uVar15 = puVar12[1];
          *(undefined8 *)(lVar11 + 0x30) = *puVar12;
          *(undefined8 *)(lVar11 + 0x38) = uVar15;
          puVar12 = (undefined8 *)func_0x7ffe99a4d950(&uStack_68,0x7fffffff,0);
          if (*(uint *)(lVar11 + 0x18) < 3) goto LAB_7ffe9a310263;
          uVar15 = puVar12[1];
          *(undefined8 *)(lVar11 + 0x40) = *puVar12;
          *(undefined8 *)(lVar11 + 0x48) = uVar15;
          if (lVar14 == 0) goto LAB_7ffe9a31027c;
          FUN_7ffe9a325690(lVar14,0xbbb,0,actor,CONCAT44(uVar8,fVar18),lVar11,0);
        }
      }
    }
LAB_7ffe9a30ee59:
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar5 = FUN_7ffe9bda2160(plVar10,0,0);
    if (cVar5 == '\0') {
      if (action == (undefined *)0x0) goto LAB_7ffe9a31027c;
    }
    else {
      if ((((plVar10 == (longlong *)0x0) ||
           (plVar13 = (longlong *)
                      (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
           plVar13 == (longlong *)0x0)) ||
          (lVar14 = (**(code **)(*plVar13 + 0x1b8))(plVar13,*(undefined8 *)(*plVar13 + 0x1c0)),
          lVar14 == 0)) || (*(longlong *)(lVar14 + 0x68) == 0)) goto LAB_7ffe9a31027c;
      cVar5 = FUN_7ffe9ad8e670(*(longlong *)(lVar14 + 0x68),0x447,&lStack_a0,_DAT_7ffe9c935bd0);
      if (cVar5 != '\0') {
        if ((lStack_a0 == 0) || (*(longlong *)(lStack_a0 + 0x10) == 0)) goto LAB_7ffe9a31027c;
        if (*(char *)(*(longlong *)(lStack_a0 + 0x10) + 0x18) != '\0') {
          plVar13 = (longlong *)
                    (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
          if ((plVar13 == (longlong *)0x0) ||
             (lVar14 = (**(code **)(*plVar13 + 0x1c8))(plVar13,*(undefined8 *)(*plVar13 + 0x1d0)),
             lVar14 == 0)) goto LAB_7ffe9a31027c;
          cVar5 = FUN_7ffe9a7c6d00(lVar14,0x443,0);
          if ((cVar5 != '\0') && (*(int *)(damageData + 0x14) == 2)) {
            plVar13 = (longlong *)
                      (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
            if (((plVar13 == (longlong *)0x0) ||
                (lVar14 = (**(code **)(*plVar13 + 0x1c8))(plVar13,*(undefined8 *)(*plVar13 + 0x1d0))
                , lVar14 == 0)) || (*(longlong *)(lVar14 + 0x50) == 0)) goto LAB_7ffe9a31027c;
            cVar5 = FUN_7ffe9ad8e670(*(longlong *)(lVar14 + 0x50),0x447,&plStack_a8,
                                     _DAT_7ffe9c934418);
            if (cVar5 == '\0') {
              if ((lStack_a0 == 0) || (*(longlong *)(lStack_a0 + 0x10) == 0)) goto LAB_7ffe9a31027c;
              uVar1 = *(undefined1 *)(*(longlong *)(lStack_a0 + 0x10) + 0x18);
              plVar13 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c909998);
              FUN_7ffe9a78d280(plVar13,uVar1,0);
              plStack_a8 = plVar13;
              plVar13 = (longlong *)
                        (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
              if ((plVar13 == (longlong *)0x0) ||
                 (lVar14 = (**(code **)(*plVar13 + 0x1c8))
                                     (plVar13,*(undefined8 *)(*plVar13 + 0x1d0)), lVar14 == 0))
              goto LAB_7ffe9a31027c;
              FUN_7ffe9a7c26c0(lVar14,plStack_a8,0,0);
            }
            if (plStack_a8 == (longlong *)0x0) goto LAB_7ffe9a31027c;
            if (((*(byte *)(*plStack_a8 + 0x130) < *(byte *)(_DAT_7ffe9c909998 + 0x130)) ||
                (*(longlong *)
                  (*(longlong *)(*plStack_a8 + 200) + -8 +
                  (ulonglong)*(byte *)(_DAT_7ffe9c909998 + 0x130) * 8) != _DAT_7ffe9c909998)) ||
               (plStack_a8 == (longlong *)0x0)) {
              FUN_7ffe9996c950(plStack_a8);
              pcVar3 = (code *)swi(3);
              (*pcVar3)();
              return;
            }
            (**(code **)(*plStack_a8 + 0x2a8))(plStack_a8,*(undefined8 *)(*plStack_a8 + 0x2b0));
          }
        }
      }
      if (action == (undefined *)0x0) goto LAB_7ffe9a31027c;
      iVar7 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      if (iVar7 == 0x4c5) {
        lVar14 = *(longlong *)action;
        if ((*(byte *)(_DAT_7ffe9c903268 + 0x130) <= *(byte *)(lVar14 + 0x130)) &&
           (*(longlong *)
             (*(longlong *)(lVar14 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c903268 + 0x130) * 8
             ) == _DAT_7ffe9c903268)) {
          if ((*(byte *)(lVar14 + 0x130) < *(byte *)(_DAT_7ffe9c903268 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(lVar14 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c903268 + 0x130) * 8) != _DAT_7ffe9c903268)) {
            FUN_7ffe9996c950(action);
            pcVar3 = (code *)swi(3);
            (*pcVar3)();
            return;
          }
          cVar5 = func_0x7ffe9a728580(action,self,0);
          if (cVar5 != '\0') {
            lVar14 = (**(code **)(*plVar10 + 0x2a8))(plVar10,*(undefined8 *)(*plVar10 + 0x2b0));
            if (lVar14 == 0) goto LAB_7ffe9a31027c;
            func_0x7ffe9a4dbd30(lVar14,8);
            if (*(longlong *)(self + 0x80) == 0) goto LAB_7ffe9a31027c;
            func_0x7ffe9a4dbd30(*(longlong *)(self + 0x80),8);
          }
        }
      }
      plVar13 = (longlong *)
                (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
      if ((plVar13 == (longlong *)0x0) ||
         (lVar14 = (**(code **)(*plVar13 + 0x1c8))(plVar13,*(undefined8 *)(*plVar13 + 0x1d0)),
         lVar14 == 0)) goto LAB_7ffe9a31027c;
      cVar5 = FUN_7ffe9a7cbb30(lVar14,0x34c,&plStack_a8,0);
      plVar13 = plStack_a8;
      if ((cVar5 != '\0') &&
         ((*(int *)(damageData + 0x18) != 1 && (0 < *(int *)(damageData + 0x84))))) {
        if (plStack_a8 == (longlong *)0x0) {
          FUN_7ffe9bd98960(self,0);
          goto LAB_7ffe9a31027c;
        }
        if (((*(byte *)(*plStack_a8 + 0x130) < *(byte *)(_DAT_7ffe9c900bb0 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*plStack_a8 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c900bb0 + 0x130) * 8) != _DAT_7ffe9c900bb0)) ||
           (plStack_a8 == (longlong *)0x0)) {
          FUN_7ffe9996c950(plStack_a8);
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
        uVar15 = FUN_7ffe9bd98960(self,0);
        cVar5 = FUN_7ffe9a79c0c0(plVar13,uVar15,*(undefined4 *)(action + 0x10),0);
        if (cVar5 != '\0') {
          FUN_7ffe9a79c880(plVar13,*(undefined4 *)(action + 0x10),0);
          *(uint *)(damageData + 0x70) = *(uint *)(damageData + 0x70) | 0x10;
        }
      }
      plVar13 = (longlong *)
                (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
      if (((plVar13 == (longlong *)0x0) ||
          (lVar14 = (**(code **)(*plVar13 + 0x1b8))(plVar13,*(undefined8 *)(*plVar13 + 0x1c0)),
          lVar14 == 0)) || (*(longlong *)(lVar14 + 0x68) == 0)) goto LAB_7ffe9a31027c;
      cVar5 = FUN_7ffe9ad8e670(*(longlong *)(lVar14 + 0x68),0x3d3,&lStack_a0,_DAT_7ffe9c935bd0);
      if (cVar5 != '\0') {
        if ((lStack_a0 == 0) || (*(longlong *)(lStack_a0 + 0x10) == 0)) goto LAB_7ffe9a31027c;
        if (*(char *)(*(longlong *)(lStack_a0 + 0x10) + 0x18) != '\0') {
          if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c9228b0 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(*(longlong *)action + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c9228b0 + 0x130) * 8) != _DAT_7ffe9c9228b0)) {
            bVar17 = false;
          }
          else {
            bVar17 = true;
          }
          plVar13 = (longlong *)0x0;
          if (bVar17) {
            plVar13 = (longlong *)action;
          }
          cVar5 = FUN_7ffe9a8fecd0(plVar13,0,0);
          if (cVar5 != '\0') {
            if (plVar13 == (longlong *)0x0) goto LAB_7ffe9a31027c;
            iVar7 = (**(code **)(*plVar13 + 0x588))(plVar13,*(undefined8 *)(*plVar13 + 0x590));
            if ((iVar7 == 0x1e) &&
               (iVar7 = (**(code **)(*plVar13 + 0x188))(plVar13,*(undefined8 *)(*plVar13 + 400)),
               iVar7 != 0xf)) {
              plVar13 = (longlong *)
                        (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
              if ((plVar13 == (longlong *)0x0) ||
                 (lVar14 = (**(code **)(*plVar13 + 0x1f8))
                                     (plVar13,*(undefined8 *)(*plVar13 + 0x200)), lVar14 == 0))
              goto LAB_7ffe9a31027c;
              lVar14 = FUN_7ffe99c090e0(lVar14,0);
              if ((lVar14 != 0) && (*(int *)(lVar14 + 0x38) == 9)) {
                iVar7 = (**(code **)(*(longlong *)action + 0x188))
                                  (action,*(undefined8 *)(*(longlong *)action + 400));
                if (iVar7 == 0x3dc) {
                  if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c947460 + 0x130)
                      ) || (*(longlong *)
                             (*(longlong *)(*(longlong *)action + 200) + -8 +
                             (ulonglong)*(byte *)(_DAT_7ffe9c947460 + 0x130) * 8) !=
                            _DAT_7ffe9c947460)) {
                    FUN_7ffe9996c950(action);
                    pcVar3 = (code *)swi(3);
                    (*pcVar3)();
                    return;
                  }
                  bVar17 = action[0x128] == '\0';
                }
                else {
                  iVar7 = FUN_7ffe9a8fde10(action,0);
                  bVar17 = iVar7 == 0;
                }
                if ((bVar17) && (*(int *)(damageData + 0x14) != 0)) {
                  if ((lStack_a0 == 0) || (*(longlong *)(lStack_a0 + 0x10) == 0))
                  goto LAB_7ffe9a31027c;
                  FUN_7ffe9a7a4fb0(plVar10,*(undefined1 *)(*(longlong *)(lStack_a0 + 0x10) + 0x18),0
                                  );
                }
              }
            }
          }
        }
      }
      plVar13 = (longlong *)
                (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
      if (((plVar13 == (longlong *)0x0) ||
          (lVar14 = (**(code **)(*plVar13 + 0x1b8))(plVar13,*(undefined8 *)(*plVar13 + 0x1c0)),
          lVar14 == 0)) || (*(longlong *)(lVar14 + 0x68) == 0)) goto LAB_7ffe9a31027c;
      cVar5 = FUN_7ffe9ad8e670(*(longlong *)(lVar14 + 0x68),0x68,&lStack_a0,_DAT_7ffe9c935bd0);
      if (cVar5 != '\0') {
        if ((lStack_a0 == 0) || (*(longlong *)(lStack_a0 + 0x10) == 0)) goto LAB_7ffe9a31027c;
        if ((*(char *)(*(longlong *)(lStack_a0 + 0x10) + 0x18) != '\0') &&
           (0 < *(int *)(damageData + 0x84))) {
          plVar13 = (longlong *)
                    (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
          if ((plVar13 == (longlong *)0x0) ||
             (lVar14 = (**(code **)(*plVar13 + 0x1f8))(plVar13,*(undefined8 *)(*plVar13 + 0x200)),
             lVar14 == 0)) goto LAB_7ffe9a31027c;
          lVar14 = FUN_7ffe99c090e0(lVar14,0);
          if ((lVar14 != 0) &&
             (((*(int *)(lVar14 + 0x38) - 0xeU < 2 &&
               (lVar14 = func_0x7ffe9996c920(action,_DAT_7ffe9c93a908), lVar14 != 0)) &&
              (cVar5 = FUN_7ffe99742ec0(2,_DAT_7ffe9c93a908,lVar14), cVar5 != '\0')))) {
            if (((*(byte *)(_DAT_7ffe9c9228b0 + 0x130) <= *(byte *)(*(longlong *)action + 0x130)) &&
                (*(longlong *)
                  (*(longlong *)(*(longlong *)action + 200) + -8 +
                  (ulonglong)*(byte *)(_DAT_7ffe9c9228b0 + 0x130) * 8) == _DAT_7ffe9c9228b0)) &&
               (cVar5 = func_0x7ffe9a4ad2e0(action,0x400,0), cVar5 == '\0')) {
              plVar13 = (longlong *)
                        (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
              if ((plVar13 == (longlong *)0x0) ||
                 (lVar14 = (**(code **)(*plVar13 + 0x1c8))
                                     (plVar13,*(undefined8 *)(*plVar13 + 0x1d0)), lVar14 == 0))
              goto LAB_7ffe9a31027c;
              cVar5 = FUN_7ffe9a7cbb30(lVar14,0x7f,&plStack_a8);
              if (cVar5 == '\0') {
                if ((lStack_a0 == 0) || (*(longlong *)(lStack_a0 + 0x10) == 0))
                goto LAB_7ffe9a31027c;
                uVar1 = *(undefined1 *)(*(longlong *)(lStack_a0 + 0x10) + 0x18);
                uVar15 = (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
                plVar13 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c952e38);
                FUN_7ffe9a77e430(plVar13,uVar1,uVar15,0);
                plStack_a8 = plVar13;
                plVar13 = (longlong *)
                          (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0))
                ;
                if ((plVar13 == (longlong *)0x0) ||
                   (lVar14 = (**(code **)(*plVar13 + 0x1c8))
                                       (plVar13,*(undefined8 *)(*plVar13 + 0x1d0)), lVar14 == 0))
                goto LAB_7ffe9a31027c;
                FUN_7ffe9a7c26c0(lVar14,plStack_a8,0,0);
              }
              if (plStack_a8 == (longlong *)0x0) goto LAB_7ffe9a31027c;
              bVar2 = *(byte *)(_DAT_7ffe9c952e38 + 0x130);
              if (((*(byte *)(*plStack_a8 + 0x130) < bVar2) ||
                  (lVar14 = *(longlong *)(*plStack_a8 + 200),
                  *(longlong *)(lVar14 + -8 + (ulonglong)bVar2 * 8) != _DAT_7ffe9c952e38)) ||
                 (plStack_a8 == (longlong *)0x0)) goto LAB_7ffe9a31027c;
              plVar13 = (longlong *)0x0;
              if (*(longlong *)(lVar14 + -8 + (ulonglong)bVar2 * 8) == _DAT_7ffe9c952e38) {
                plVar13 = plStack_a8;
              }
              (**(code **)(*plVar13 + 0x2a8))(plVar13,*(undefined8 *)(*plVar13 + 0x2b0));
            }
          }
        }
      }
      plVar13 = (longlong *)
                (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
      if ((plVar13 == (longlong *)0x0) ||
         (lVar14 = (**(code **)(*plVar13 + 0x1c8))(plVar13,*(undefined8 *)(*plVar13 + 0x1d0)),
         lVar14 == 0)) goto LAB_7ffe9a31027c;
      cVar5 = FUN_7ffe9a7cbb30(lVar14,0x22e,&plStack_a8,0);
      if (cVar5 != '\0') {
        if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c9228b0 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*(longlong *)action + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c9228b0 + 0x130) * 8) != _DAT_7ffe9c9228b0)) {
          bVar17 = false;
        }
        else {
          bVar17 = true;
        }
        puVar16 = (undefined *)0x0;
        if (bVar17) {
          puVar16 = action;
        }
        cVar5 = FUN_7ffe9a8fecd0(puVar16,0,0);
        if ((cVar5 != '\0') &&
           ((*(longlong *)(damageData + 0x28) == 0 ||
            (*(longlong *)(damageData + 0x78) !=
             *(longlong *)(*(longlong *)(damageData + 0x28) + 0x78))))) {
          iVar7 = (**(code **)(*(longlong *)action + 0x188))
                            (action,*(undefined8 *)(*(longlong *)action + 400));
          if (iVar7 < 0x21) {
            iVar7 = (**(code **)(*(longlong *)action + 0x188))
                              (action,*(undefined8 *)(*(longlong *)action + 400));
            if (iVar7 == 0) {
              if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c904080 + 0x130)) ||
                 (*(longlong *)
                   (*(longlong *)(*(longlong *)action + 200) + -8 +
                   (ulonglong)*(byte *)(_DAT_7ffe9c904080 + 0x130) * 8) != _DAT_7ffe9c904080)) {
                FUN_7ffe9996c950(action);
                pcVar3 = (code *)swi(3);
                (*pcVar3)();
                return;
              }
              if ((action[0x104] & 2) != 0) goto LAB_7ffe9a30f8e0;
            }
          }
          else {
LAB_7ffe9a30f8e0:
            if (plStack_a8 == (longlong *)0x0) goto LAB_7ffe9a31027c;
            if (((*(byte *)(*plStack_a8 + 0x130) < *(byte *)(_DAT_7ffe9c8feb30 + 0x130)) ||
                (*(longlong *)
                  (*(longlong *)(*plStack_a8 + 200) + -8 +
                  (ulonglong)*(byte *)(_DAT_7ffe9c8feb30 + 0x130) * 8) != _DAT_7ffe9c8feb30)) ||
               (plStack_a8 == (longlong *)0x0)) {
              FUN_7ffe9996c950(plStack_a8);
              pcVar3 = (code *)swi(3);
              (*pcVar3)();
              return;
            }
            cVar5 = func_0x7ffe99ad7b20(plStack_a8,2);
            plVar13 = plStack_a8;
            if (cVar5 != '\0') {
              if (plStack_a8 == (longlong *)0x0) goto LAB_7ffe9a31027c;
              if (((*(byte *)(*plStack_a8 + 0x130) < *(byte *)(_DAT_7ffe9c8feb30 + 0x130)) ||
                  (*(longlong *)
                    (*(longlong *)(*plStack_a8 + 200) + -8 +
                    (ulonglong)*(byte *)(_DAT_7ffe9c8feb30 + 0x130) * 8) != _DAT_7ffe9c8feb30)) ||
                 (plStack_a8 == (longlong *)0x0)) {
                FUN_7ffe9996c950(plStack_a8);
                pcVar3 = (code *)swi(3);
                (*pcVar3)();
                return;
              }
              if (0.0 < *(float *)((longlong)plStack_a8 + 0x14)) {
                uVar15 = (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0));
                if (plVar13 == (longlong *)0x0) goto LAB_7ffe9a31027c;
                if ((*(byte *)(*plVar13 + 0x130) < *(byte *)(_DAT_7ffe9c8feb30 + 0x130)) ||
                   (*(longlong *)
                     (*(longlong *)(*plVar13 + 200) + -8 +
                     (ulonglong)*(byte *)(_DAT_7ffe9c8feb30 + 0x130) * 8) != _DAT_7ffe9c8feb30)) {
                  FUN_7ffe9996c950(plVar13);
                  pcVar3 = (code *)swi(3);
                  (*pcVar3)();
                  return;
                }
                iVar7 = FUN_7ffe9a79b890(plVar13,puVar16,uVar15,0);
                if (0 < iVar7) {
                  lVar14 = FUN_7ffe9a47bac0(0);
                  if ((lVar14 == 0) || (lVar14 = FUN_7ffe9a47f400(lVar14,0), lVar14 == 0))
                  goto LAB_7ffe9a31027c;
                  FUN_7ffe9a6fbaa0(lVar14,0xc9,iVar7,0);
                }
                *(uint *)(damageData + 0x70) = *(uint *)(damageData + 0x70) | 0x2000;
              }
            }
          }
        }
      }
      FUN_7ffe9a7abe00(plVar10,action,damageData,0);
      FUN_7ffe9a64ea60(plVar10,action,damageData,0);
    }
    FUN_7ffe9a8fceb0(action,plVar10,self,damageData,0);
    uVar8 = FUN_7ffe9a310d00(self,*(undefined4 *)(damageData + 0x84),plVar10,0);
    iVar7 = FUN_7ffe9a8fc280(action,self,uVar8,0);
    iVar9 = (**(code **)(*(longlong *)action + 0x188))
                      (action,*(undefined8 *)(*(longlong *)action + 400));
    if ((iVar9 == 0x3ec) && ((damageData[0x74] & 1) != 0)) {
      lVar14 = *(longlong *)(self + 0x78);
      if (lVar14 == 0) goto LAB_7ffe9a31027c;
      if (iVar7 < *(int *)(lVar14 + 0x14)) goto LAB_7ffe9a30fae0;
      iVar7 = *(int *)(lVar14 + 0x14) + -1;
    }
    else {
LAB_7ffe9a30fae0:
      lVar14 = *(longlong *)(self + 0x78);
      if (lVar14 == 0) goto LAB_7ffe9a31027c;
    }
    func_0x7ffe9a3606e0(lVar14,*(int *)(lVar14 + 0x14) - iVar7,0);
    if (*(longlong *)(self + 0x80) == 0) goto LAB_7ffe9a31027c;
    FUN_7ffe9a4dacc0(*(longlong *)(self + 0x80),0);
    (**(code **)(*(longlong *)self + 0x678))(self,*(undefined8 *)(*(longlong *)self + 0x680));
    if (*(int *)(damageData + 0x8c) != 0) {
      if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      cVar5 = FUN_7ffe9bda2160(plVar10,0,0);
      if (cVar5 != '\0') {
        if ((plVar10 == (longlong *)0x0) ||
           (plVar10 = (longlong *)
                      (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
           plVar10 == (longlong *)0x0)) goto LAB_7ffe9a31027c;
        lVar14 = (**(code **)(*plVar10 + 0x208))(plVar10,*(undefined8 *)(*plVar10 + 0x210));
        if ((lVar14 != 0) &&
           (cVar5 = func_0x7ffe9a51e2e0(lVar14,*(undefined4 *)(damageData + 0x8c),0), cVar5 != '\0')
           ) {
          *(undefined4 *)(damageData + 0x8c) = 0;
        }
      }
      cVar5 = FUN_7ffe9a30cc50(self,*(undefined4 *)(damageData + 0x8c),0);
      if (cVar5 != '\0') {
        *(undefined4 *)(damageData + 0x8c) = 0;
      }
      FUN_7ffe9a30d800(self,actor,action,damageData,1,0);
    }
  }
  if (*(int *)(damageData + 0x14) != 0) {
    FUN_7ffe9a313c40(self,actor,action,damageData,0);
    FUN_7ffe9a314310(self,actor,action,0);
    cVar5 = '\0';
    if (action == (undefined *)0x0) goto LAB_7ffe9a31027c;
    cVar6 = FUN_7ffe9a8fd0e0(action,self,0);
    if (cVar6 == '\0') {
      cVar5 = FUN_7ffe9a8fd2d0(action,self,0);
      if (cVar5 == '\0') {
        FUN_7ffe9a8fbd90(action,self,0);
      }
      FUN_7ffe9a8fdf40(action,self,0);
      cVar5 = '\x01';
    }
    iVar7 = (**(code **)(*(longlong *)action + 0x188))
                      (action,*(undefined8 *)(*(longlong *)action + 400));
    if (iVar7 == 0x4c3) {
LAB_7ffe9a30fe12:
      uVar8 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      if (*(int *)(_DAT_7ffe9c94c0a0 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      cVar5 = func_0x7ffe9a812a40(uVar8,0);
      if ((cVar5 != '\0') &&
         (cVar5 = (**(code **)(*(longlong *)action + 0x308))
                            (action,*(undefined8 *)(*(longlong *)action + 0x310)), cVar5 != '\0')) {
        iVar7 = (**(code **)(*(longlong *)action + 0x188))
                          (action,*(undefined8 *)(*(longlong *)action + 400));
        if (iVar7 != 0) {
          iVar7 = (**(code **)(*(longlong *)action + 0x1a8))
                            (action,*(undefined8 *)(*(longlong *)action + 0x1b0));
          if (iVar7 == 1) {
            lVar14 = *(longlong *)(self + 0x70);
            if ((lVar14 == 0) || (*(undefined **)(self + 0x78) == (undefined *)0x0))
            goto LAB_7ffe9a31027c;
            MobStatus_CalcExpDef
                      (*(undefined **)(self + 0x78),(undefined *)0x1,(uint)*(byte *)(lVar14 + 0x34),
                       (uint)*(byte *)(lVar14 + 0x35),(uint)*(byte *)(lVar14 + 0x36),
                       (undefined *)0x0);
          }
          iVar7 = (**(code **)(*(longlong *)action + 0x1a8))
                            (action,*(undefined8 *)(*(longlong *)action + 0x1b0));
          if (iVar7 == 2) {
            lVar14 = *(longlong *)(self + 0x70);
            if ((lVar14 == 0) || (*(undefined **)(self + 0x78) == (undefined *)0x0))
            goto LAB_7ffe9a31027c;
            MobStatus_CalcExpDef
                      (*(undefined **)(self + 0x78),(undefined *)0x2,(uint)*(byte *)(lVar14 + 0x34),
                       (uint)*(byte *)(lVar14 + 0x35),(uint)*(byte *)(lVar14 + 0x36),
                       (undefined *)0x0);
          }
          iVar7 = (**(code **)(*(longlong *)action + 0x1a8))
                            (action,*(undefined8 *)(*(longlong *)action + 0x1b0));
          if (iVar7 != 3) goto LAB_7ffe9a30ff8c;
        }
        lVar14 = *(longlong *)(self + 0x70);
        if ((lVar14 == 0) || (*(undefined **)(self + 0x78) == (undefined *)0x0))
        goto LAB_7ffe9a31027c;
        MobStatus_CalcExpDef
                  (*(undefined **)(self + 0x78),(undefined *)0x0,(uint)*(byte *)(lVar14 + 0x34),
                   (uint)*(byte *)(lVar14 + 0x35),(uint)*(byte *)(lVar14 + 0x36),(undefined *)0x0);
      }
    }
    else {
      iVar7 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      if (iVar7 == 0x9f) {
        if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c96e728 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*(longlong *)action + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c96e728 + 0x130) * 8) != _DAT_7ffe9c96e728)) {
          FUN_7ffe9996c950(action);
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
        cVar5 = FUN_7ffe9a6d77a0(action,self,0);
        goto LAB_7ffe9a30fe0a;
      }
      iVar7 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      if (iVar7 == 0x292) goto LAB_7ffe9a30fe12;
      iVar7 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      if (iVar7 == 0x75) {
        if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c95e9a8 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*(longlong *)action + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c95e9a8 + 0x130) * 8) != _DAT_7ffe9c95e9a8)) {
          FUN_7ffe9996c950(action);
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
        cVar5 = func_0x7ffe9a6cd6b0(action,0);
        goto LAB_7ffe9a30fe0a;
      }
      iVar7 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      if (iVar7 == 0x22a) goto LAB_7ffe9a30fe12;
      lVar14 = *(longlong *)action;
      if ((*(byte *)(lVar14 + 0x130) < *(byte *)(_DAT_7ffe9c94c3b0 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(lVar14 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c94c3b0 + 0x130) * 8)
          != _DAT_7ffe9c94c3b0)) {
        iVar7 = (**(code **)(lVar14 + 0x188))(action,*(undefined8 *)(lVar14 + 400));
        if ((iVar7 != 0x12d) || ((damageData[0x74] & 2) != 0)) goto LAB_7ffe9a30fe0a;
      }
      else {
        cVar5 = func_0x7ffe9a774a60(action,0);
LAB_7ffe9a30fe0a:
        if (cVar5 != '\0') goto LAB_7ffe9a30fe12;
      }
    }
LAB_7ffe9a30ff8c:
    iVar7 = (**(code **)(*(longlong *)action + 0x188))
                      (action,*(undefined8 *)(*(longlong *)action + 400));
    if (iVar7 == 0x292) {
      if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c931550 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*(longlong *)action + 200) + -8 +
           (ulonglong)*(byte *)(_DAT_7ffe9c931550 + 0x130) * 8) != _DAT_7ffe9c931550)) {
        FUN_7ffe9996c950(action);
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
      func_0x7ffe9a65ff90(action,0);
    }
    iVar7 = (**(code **)(*(longlong *)action + 0x188))
                      (action,*(undefined8 *)(*(longlong *)action + 400));
    if (iVar7 == 0x22a) {
      if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c92be80 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*(longlong *)action + 200) + -8 +
           (ulonglong)*(byte *)(_DAT_7ffe9c92be80 + 0x130) * 8) != _DAT_7ffe9c92be80)) {
        FUN_7ffe9996c950(action);
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
      func_0x7ffe9a68f7c0(action,0);
    }
  }
  cVar5 = (**(code **)(*(longlong *)self + 0x188))(self,*(undefined8 *)(*(longlong *)self + 400));
  if ((cVar5 == '\0') || (cVar4 != '\0')) {
    if (0 < *(int *)(damageData + 0x84)) {
      if (*(longlong *)(self + 0x20) != 0) {
        puVar12 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_68,*(longlong *)(self + 0x20),0);
        uStack_80 = *puVar12;
        fStack_78 = *(float *)(puVar12 + 1);
        if ((actor != (undefined *)0x0) && (lVar14 = FUN_7ffe9bd9b890(actor,0), lVar14 != 0)) {
          puVar12 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_68,lVar14,0);
          fStack_78 = fStack_78 - *(float *)(puVar12 + 1);
          lVar14 = *(longlong *)(self + 0x48);
          iVar7 = *(int *)(damageData + 0x84);
          uStack_68 = CONCAT44(uStack_80._4_4_ - (float)((ulonglong)*puVar12 >> 0x20),
                               (float)uStack_80 - (float)*puVar12);
          fStack_60 = fStack_78;
          lVar11 = (**(code **)(*(longlong *)self + 0x518))
                             (self,*(undefined8 *)(*(longlong *)self + 0x520));
          if (lVar11 != 0) {
            iVar9 = FUN_7ffe99742ec0(0,_DAT_7ffe9c93ed20,lVar11);
            puVar12 = (undefined8 *)FUN_7ffe999fca00(&uStack_80,&uStack_68,0);
            if (lVar14 != 0) {
              uStack_68 = *puVar12;
              fStack_60 = *(float *)(puVar12 + 1);
              uVar15 = FUN_7ffe9a9f43c0(lVar14,_DAT_7ffe9c049b18,(float)iVar7 / (float)iVar9,
                                        &uStack_68,0);
              FUN_7ffe9bd9f640(self,uVar15,0);
              return;
            }
          }
        }
      }
LAB_7ffe9a31027c:
      FUN_7ffe9996d7a0();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
  }
  else {
    uVar15 = *(undefined8 *)(self + 0x58);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar4 = FUN_7ffe9bda20c0(uVar15,0);
    if (cVar4 != '\0') {
      plVar10 = *(longlong **)(self + 0x58);
      if (plVar10 == (longlong *)0x0) goto LAB_7ffe9a31027c;
      (**(code **)(*plVar10 + 0x1d8))(plVar10,*(undefined8 *)(*plVar10 + 0x1e0));
    }
    uVar15 = *(undefined8 *)(self + 0x68);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar4 = FUN_7ffe9bda20c0(uVar15,0);
    if (cVar4 != '\0') {
      if (*(longlong *)(self + 0x68) == 0) goto LAB_7ffe9a31027c;
      FUN_7ffe99eea280(*(longlong *)(self + 0x68),0);
    }
    FUN_7ffe9a30c060(self,id,0);
  }
  return;
}

