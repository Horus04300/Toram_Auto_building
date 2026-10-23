
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
  undefined4 uVar10;
  longlong *plVar11;
  longlong lVar12;
  undefined8 *puVar13;
  longlong *plVar14;
  longlong lVar15;
  undefined8 uVar16;
  undefined *puVar17;
  bool bVar18;
  float fVar19;
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
  if (DAT_7fff625e4c39 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62438f60);
    FUN_7fff5f47d450(&DAT_7fff62448ae0);
    FUN_7fff5f47d450(&DAT_7fff6244eda8);
    FUN_7fff5f47d450(&DAT_7fff6245a778);
    FUN_7fff5f47d450(&DAT_7fff62419c80);
    FUN_7fff5f47d450(&DAT_7fff6243b368);
    FUN_7fff5f47d450(&DAT_7fff6243cb28);
    FUN_7fff5f47d450(&DAT_7fff623f8aa8);
    FUN_7fff5f47d450(&DAT_7fff623f8eb8);
    FUN_7fff5f47d450(&DAT_7fff623f8f88);
    FUN_7fff5f47d450(&DAT_7fff6240ad28);
    FUN_7fff5f47d450(&DAT_7fff62411458);
    FUN_7fff5f47d450(&DAT_7fff6246abc0);
    FUN_7fff5f47d450(&DAT_7fff624336f8);
    FUN_7fff5f47d450(&DAT_7fff62442188);
    FUN_7fff5f47d450(&DAT_7fff624465a0);
    FUN_7fff5f47d450(&DAT_7fff62466220);
    FUN_7fff5f47d450(&DAT_7fff62475ff0);
    FUN_7fff5f47d450(&DAT_7fff62406520);
    FUN_7fff5f47d450(&DAT_7fff624085a0);
    FUN_7fff5f47d450(&DAT_7fff6240b9a0);
    FUN_7fff5f47d450(&DAT_7fff6240e4b0);
    FUN_7fff5f47d450(&DAT_7fff6242a0c8);
    FUN_7fff5f47d450(&DAT_7fff62453798);
    FUN_7fff5f47d450(&DAT_7fff62453aa8);
    DAT_7fff625e4c39 = '\x01';
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
    uVar16 = *(undefined8 *)(self + 0x30);
    if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    cVar4 = FUN_7fff618ab120(uVar16,0,0);
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
      if (*(longlong *)(self + 0x60) == 0) goto LAB_7fff5fe1b08c;
      FUN_7fff5f9fc8a0(*(longlong *)(self + 0x60),actor,0);
      if (*(int *)(_DAT_7fff62448ae0 + 0xe0) == 0) {
        func_0x7fff5f47d6f0();
      }
      FUN_7fff602e7140(0,action,0);
    }
  }
  else if (*(int *)(damageData + 0x18) == 2) {
    if (*(longlong *)(self + 0x60) == 0) goto LAB_7fff5fe1b08c;
    FUN_7fff5f9fd700(*(longlong *)(self + 0x60),actor,0);
    if ((*(int *)(damageData + 0x8c) == 4) || (*(int *)(damageData + 0x8c) - 0xbU < 2)) {
      *(undefined4 *)(damageData + 0x94) = 0;
    }
  }
  cVar5 = FUN_7fff5fe17770(self,damageData,0);
  if (cVar5 == '\0') {
    return;
  }
  if (*(int *)(damageData + 0x14) != 0) {
    if (actor == (undefined *)0x0) goto LAB_7fff5fe1b08c;
    plVar11 = (longlong *)FUN_7fff606a6750(actor,_DAT_7fff6246abc0);
    if ((damageData[0x22] != '\0') || (damageData[0x21] != '\0')) {
      uVar16 = *(undefined8 *)(self + 200);
      if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
        func_0x7fff5f47d6f0();
      }
      cVar5 = FUN_7fff618ab2e0(uVar16,0,0);
      if (cVar5 != '\0') {
        cVar5 = FUN_7fff60683c50(self,0x21,&lStack_98,_DAT_7fff623f8eb8);
        if ((cVar5 == '\0') || (damageData[0x22] == '\0')) {
          cVar5 = FUN_7fff60683c50(self,0x22,&lStack_90,_DAT_7fff623f8f88);
          if ((cVar5 == '\0') || (damageData[0x21] == '\0')) {
            cVar5 = FUN_7fff60683c50(self,5,&lStack_88,_DAT_7fff623f8aa8);
            if (cVar5 == '\0') goto LAB_7fff5fe19c69;
            if (lStack_88 == 0) goto LAB_7fff5fe1b08c;
            fVar19 = (float)FUN_7fff5fe83e40(lStack_88,0);
          }
          else {
            if (lStack_90 == 0) goto LAB_7fff5fe1b08c;
            fVar19 = (float)FUN_7fff5fe83e40(lStack_90,0);
          }
        }
        else {
          if (lStack_98 == 0) goto LAB_7fff5fe1b08c;
          fVar19 = (float)FUN_7fff5fe83e40(lStack_98,0);
        }
        if (fVar19 != 0.0) {
          lVar15 = *(longlong *)(self + 200);
          lVar12 = func_0x7fff5f47c850(_DAT_7fff62419c80,3);
          puVar13 = (undefined8 *)func_0x7fff5f55d780(&uStack_68,0x7fffffff,0);
          if (lVar12 == 0) goto LAB_7fff5fe1b08c;
          if (*(int *)(lVar12 + 0x18) == 0) {
LAB_7fff5fe1b073:
            FUN_7fff5f47d650();
            pcVar3 = (code *)swi(3);
            (*pcVar3)();
            return;
          }
          uVar16 = puVar13[1];
          *(undefined8 *)(lVar12 + 0x20) = *puVar13;
          *(undefined8 *)(lVar12 + 0x28) = uVar16;
          puVar13 = (undefined8 *)func_0x7fff5f55d780(&uStack_68,0x7fffffff,0);
          if (*(uint *)(lVar12 + 0x18) < 2) goto LAB_7fff5fe1b073;
          uVar16 = puVar13[1];
          *(undefined8 *)(lVar12 + 0x30) = *puVar13;
          *(undefined8 *)(lVar12 + 0x38) = uVar16;
          puVar13 = (undefined8 *)func_0x7fff5f55d780(&uStack_68,0x7fffffff,0);
          if (*(uint *)(lVar12 + 0x18) < 3) goto LAB_7fff5fe1b073;
          uVar16 = puVar13[1];
          *(undefined8 *)(lVar12 + 0x40) = *puVar13;
          *(undefined8 *)(lVar12 + 0x48) = uVar16;
          if (lVar15 == 0) goto LAB_7fff5fe1b08c;
          FUN_7fff5fe30360(lVar15,0xbbb,0,actor,CONCAT44(uVar8,fVar19),lVar12,0);
        }
      }
    }
LAB_7fff5fe19c69:
    if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    cVar5 = FUN_7fff618ab2e0(plVar11,0,0);
    if (cVar5 == '\0') {
      if (action == (undefined *)0x0) goto LAB_7fff5fe1b08c;
    }
    else {
      if ((((plVar11 == (longlong *)0x0) ||
           (plVar14 = (longlong *)
                      (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0)),
           plVar14 == (longlong *)0x0)) ||
          (lVar15 = (**(code **)(*plVar14 + 0x1b8))(plVar14,*(undefined8 *)(*plVar14 + 0x1c0)),
          lVar15 == 0)) || (*(longlong *)(lVar15 + 0x68) == 0)) goto LAB_7fff5fe1b08c;
      cVar5 = FUN_7fff60898a30(*(longlong *)(lVar15 + 0x68),0x447,&lStack_a0,_DAT_7fff6243cb28);
      if (cVar5 != '\0') {
        if ((lStack_a0 == 0) || (*(longlong *)(lStack_a0 + 0x10) == 0)) goto LAB_7fff5fe1b08c;
        if (*(char *)(*(longlong *)(lStack_a0 + 0x10) + 0x18) != '\0') {
          plVar14 = (longlong *)
                    (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
          if ((plVar14 == (longlong *)0x0) ||
             (lVar15 = (**(code **)(*plVar14 + 0x1c8))(plVar14,*(undefined8 *)(*plVar14 + 0x1d0)),
             lVar15 == 0)) goto LAB_7fff5fe1b08c;
          cVar5 = FUN_7fff602d1190(lVar15,0x443,0);
          if ((cVar5 != '\0') && (*(int *)(damageData + 0x14) == 2)) {
            plVar14 = (longlong *)
                      (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
            if (((plVar14 == (longlong *)0x0) ||
                (lVar15 = (**(code **)(*plVar14 + 0x1c8))(plVar14,*(undefined8 *)(*plVar14 + 0x1d0))
                , lVar15 == 0)) || (*(longlong *)(lVar15 + 0x50) == 0)) goto LAB_7fff5fe1b08c;
            cVar5 = FUN_7fff60898a30(*(longlong *)(lVar15 + 0x50),0x447,&plStack_a8,
                                     _DAT_7fff6243b368);
            if (cVar5 == '\0') {
              if ((lStack_a0 == 0) || (*(longlong *)(lStack_a0 + 0x10) == 0)) goto LAB_7fff5fe1b08c;
              uVar1 = *(undefined1 *)(*(longlong *)(lStack_a0 + 0x10) + 0x18);
              plVar14 = (longlong *)func_0x7fff5f44ff00(_DAT_7fff62411458);
              FUN_7fff60297710(plVar14,uVar1,0);
              plStack_a8 = plVar14;
              plVar14 = (longlong *)
                        (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
              if ((plVar14 == (longlong *)0x0) ||
                 (lVar15 = (**(code **)(*plVar14 + 0x1c8))
                                     (plVar14,*(undefined8 *)(*plVar14 + 0x1d0)), lVar15 == 0))
              goto LAB_7fff5fe1b08c;
              FUN_7fff602ccb50(lVar15,plStack_a8,0,0);
            }
            if (plStack_a8 == (longlong *)0x0) goto LAB_7fff5fe1b08c;
            if (((*(byte *)(*plStack_a8 + 0x130) < *(byte *)(_DAT_7fff62411458 + 0x130)) ||
                (*(longlong *)
                  (*(longlong *)(*plStack_a8 + 200) + -8 +
                  (ulonglong)*(byte *)(_DAT_7fff62411458 + 0x130) * 8) != _DAT_7fff62411458)) ||
               (plStack_a8 == (longlong *)0x0)) {
              FUN_7fff5f47c810(plStack_a8);
              pcVar3 = (code *)swi(3);
              (*pcVar3)();
              return;
            }
            (**(code **)(*plStack_a8 + 0x2a8))(plStack_a8,*(undefined8 *)(*plStack_a8 + 0x2b0));
          }
        }
      }
      if (action == (undefined *)0x0) goto LAB_7fff5fe1b08c;
      iVar7 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      if (iVar7 == 0x4c5) {
        lVar15 = *(longlong *)action;
        if ((*(byte *)(_DAT_7fff6240ad28 + 0x130) <= *(byte *)(lVar15 + 0x130)) &&
           (*(longlong *)
             (*(longlong *)(lVar15 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7fff6240ad28 + 0x130) * 8
             ) == _DAT_7fff6240ad28)) {
          if ((*(byte *)(lVar15 + 0x130) < *(byte *)(_DAT_7fff6240ad28 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(lVar15 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7fff6240ad28 + 0x130) * 8) != _DAT_7fff6240ad28)) {
            FUN_7fff5f47c810(action);
            pcVar3 = (code *)swi(3);
            (*pcVar3)();
            return;
          }
          cVar5 = func_0x7fff60232a10(action,self,0);
          if (cVar5 != '\0') {
            lVar15 = (**(code **)(*plVar11 + 0x2a8))(plVar11,*(undefined8 *)(*plVar11 + 0x2b0));
            if (lVar15 == 0) goto LAB_7fff5fe1b08c;
            func_0x7fff5ffe68f0(lVar15,8);
            if (*(longlong *)(self + 0x80) == 0) goto LAB_7fff5fe1b08c;
            func_0x7fff5ffe68f0(*(longlong *)(self + 0x80),8);
          }
        }
      }
      plVar14 = (longlong *)
                (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
      if ((plVar14 == (longlong *)0x0) ||
         (lVar15 = (**(code **)(*plVar14 + 0x1c8))(plVar14,*(undefined8 *)(*plVar14 + 0x1d0)),
         lVar15 == 0)) goto LAB_7fff5fe1b08c;
      cVar5 = FUN_7fff602d5fc0(lVar15,0x34c,&plStack_a8,0);
      plVar14 = plStack_a8;
      if ((cVar5 != '\0') &&
         ((*(int *)(damageData + 0x18) != 1 && (0 < *(int *)(damageData + 0x84))))) {
        if (plStack_a8 == (longlong *)0x0) {
          FUN_7fff618a1ae0(self,0);
          goto LAB_7fff5fe1b08c;
        }
        if (((*(byte *)(*plStack_a8 + 0x130) < *(byte *)(_DAT_7fff624085a0 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*plStack_a8 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7fff624085a0 + 0x130) * 8) != _DAT_7fff624085a0)) ||
           (plStack_a8 == (longlong *)0x0)) {
          FUN_7fff5f47c810(plStack_a8);
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
        uVar16 = FUN_7fff618a1ae0(self,0);
        cVar5 = FUN_7fff602a6550(plVar14,uVar16,*(undefined4 *)(action + 0x10),0);
        if (cVar5 != '\0') {
          FUN_7fff602a6d10(plVar14,*(undefined4 *)(action + 0x10),0);
          *(uint *)(damageData + 0x70) = *(uint *)(damageData + 0x70) | 0x10;
        }
      }
      plVar14 = (longlong *)
                (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
      if (((plVar14 == (longlong *)0x0) ||
          (lVar15 = (**(code **)(*plVar14 + 0x1b8))(plVar14,*(undefined8 *)(*plVar14 + 0x1c0)),
          lVar15 == 0)) || (*(longlong *)(lVar15 + 0x68) == 0)) goto LAB_7fff5fe1b08c;
      cVar5 = FUN_7fff60898a30(*(longlong *)(lVar15 + 0x68),0x3d3,&lStack_a0,_DAT_7fff6243cb28);
      if (cVar5 != '\0') {
        if ((lStack_a0 == 0) || (*(longlong *)(lStack_a0 + 0x10) == 0)) goto LAB_7fff5fe1b08c;
        if (*(char *)(*(longlong *)(lStack_a0 + 0x10) + 0x18) != '\0') {
          if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7fff6242a0c8 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(*(longlong *)action + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7fff6242a0c8 + 0x130) * 8) != _DAT_7fff6242a0c8)) {
            bVar18 = false;
          }
          else {
            bVar18 = true;
          }
          plVar14 = (longlong *)0x0;
          if (bVar18) {
            plVar14 = (longlong *)action;
          }
          cVar5 = FUN_7fff60409110(plVar14,0,0);
          if (cVar5 != '\0') {
            if (plVar14 == (longlong *)0x0) goto LAB_7fff5fe1b08c;
            iVar7 = (**(code **)(*plVar14 + 0x588))(plVar14,*(undefined8 *)(*plVar14 + 0x590));
            if ((iVar7 == 0x1e) &&
               (iVar7 = (**(code **)(*plVar14 + 0x188))(plVar14,*(undefined8 *)(*plVar14 + 400)),
               iVar7 != 0xf)) {
              plVar14 = (longlong *)
                        (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
              if ((plVar14 == (longlong *)0x0) ||
                 (lVar15 = (**(code **)(*plVar14 + 0x1f8))
                                     (plVar14,*(undefined8 *)(*plVar14 + 0x200)), lVar15 == 0))
              goto LAB_7fff5fe1b08c;
              lVar15 = FUN_7fff5f718da0(lVar15,0);
              if ((lVar15 != 0) && (*(int *)(lVar15 + 0x38) == 9)) {
                iVar7 = (**(code **)(*(longlong *)action + 0x188))
                                  (action,*(undefined8 *)(*(longlong *)action + 400));
                if (iVar7 == 0x3dc) {
                  if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7fff6244eda8 + 0x130)
                      ) || (*(longlong *)
                             (*(longlong *)(*(longlong *)action + 200) + -8 +
                             (ulonglong)*(byte *)(_DAT_7fff6244eda8 + 0x130) * 8) !=
                            _DAT_7fff6244eda8)) {
                    FUN_7fff5f47c810(action);
                    pcVar3 = (code *)swi(3);
                    (*pcVar3)();
                    return;
                  }
                  bVar18 = action[0x128] == '\0';
                }
                else {
                  iVar7 = FUN_7fff60408250(action,0);
                  bVar18 = iVar7 == 0;
                }
                if ((bVar18) && (*(int *)(damageData + 0x14) != 0)) {
                  if ((lStack_a0 == 0) || (*(longlong *)(lStack_a0 + 0x10) == 0))
                  goto LAB_7fff5fe1b08c;
                  FUN_7fff602af440(plVar11,*(undefined1 *)(*(longlong *)(lStack_a0 + 0x10) + 0x18),0
                                  );
                }
              }
            }
          }
        }
      }
      plVar14 = (longlong *)
                (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
      if (((plVar14 == (longlong *)0x0) ||
          (lVar15 = (**(code **)(*plVar14 + 0x1b8))(plVar14,*(undefined8 *)(*plVar14 + 0x1c0)),
          lVar15 == 0)) || (*(longlong *)(lVar15 + 0x68) == 0)) goto LAB_7fff5fe1b08c;
      cVar5 = FUN_7fff60898a30(*(longlong *)(lVar15 + 0x68),0x68,&lStack_a0,_DAT_7fff6243cb28);
      if (cVar5 != '\0') {
        if ((lStack_a0 == 0) || (*(longlong *)(lStack_a0 + 0x10) == 0)) goto LAB_7fff5fe1b08c;
        if ((*(char *)(*(longlong *)(lStack_a0 + 0x10) + 0x18) != '\0') &&
           (0 < *(int *)(damageData + 0x84))) {
          plVar14 = (longlong *)
                    (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
          if ((plVar14 == (longlong *)0x0) ||
             (lVar15 = (**(code **)(*plVar14 + 0x1f8))(plVar14,*(undefined8 *)(*plVar14 + 0x200)),
             lVar15 == 0)) goto LAB_7fff5fe1b08c;
          lVar15 = FUN_7fff5f718da0(lVar15,0);
          if ((lVar15 != 0) &&
             (((*(int *)(lVar15 + 0x38) - 0xeU < 2 &&
               (lVar15 = func_0x7fff5f47c7e0(action,_DAT_7fff62442188), lVar15 != 0)) &&
              (cVar5 = FUN_7fff5f252ec0(2,_DAT_7fff62442188,lVar15), cVar5 != '\0')))) {
            if (((*(byte *)(_DAT_7fff6242a0c8 + 0x130) <= *(byte *)(*(longlong *)action + 0x130)) &&
                (*(longlong *)
                  (*(longlong *)(*(longlong *)action + 200) + -8 +
                  (ulonglong)*(byte *)(_DAT_7fff6242a0c8 + 0x130) * 8) == _DAT_7fff6242a0c8)) &&
               (cVar5 = func_0x7fff5ffb7ea0(action,0x400,0), cVar5 == '\0')) {
              plVar14 = (longlong *)
                        (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
              if ((plVar14 == (longlong *)0x0) ||
                 (lVar15 = (**(code **)(*plVar14 + 0x1c8))
                                     (plVar14,*(undefined8 *)(*plVar14 + 0x1d0)), lVar15 == 0))
              goto LAB_7fff5fe1b08c;
              cVar5 = FUN_7fff602d5fc0(lVar15,0x7f,&plStack_a8);
              if (cVar5 == '\0') {
                if ((lStack_a0 == 0) || (*(longlong *)(lStack_a0 + 0x10) == 0))
                goto LAB_7fff5fe1b08c;
                uVar1 = *(undefined1 *)(*(longlong *)(lStack_a0 + 0x10) + 0x18);
                uVar16 = (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
                plVar14 = (longlong *)func_0x7fff5f44ff00(_DAT_7fff6245a778);
                FUN_7fff602888c0(plVar14,uVar1,uVar16,0);
                plStack_a8 = plVar14;
                plVar14 = (longlong *)
                          (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0))
                ;
                if ((plVar14 == (longlong *)0x0) ||
                   (lVar15 = (**(code **)(*plVar14 + 0x1c8))
                                       (plVar14,*(undefined8 *)(*plVar14 + 0x1d0)), lVar15 == 0))
                goto LAB_7fff5fe1b08c;
                FUN_7fff602ccb50(lVar15,plStack_a8,0,0);
              }
              if (plStack_a8 == (longlong *)0x0) goto LAB_7fff5fe1b08c;
              bVar2 = *(byte *)(_DAT_7fff6245a778 + 0x130);
              if (((*(byte *)(*plStack_a8 + 0x130) < bVar2) ||
                  (lVar15 = *(longlong *)(*plStack_a8 + 200),
                  *(longlong *)(lVar15 + -8 + (ulonglong)bVar2 * 8) != _DAT_7fff6245a778)) ||
                 (plStack_a8 == (longlong *)0x0)) goto LAB_7fff5fe1b08c;
              plVar14 = (longlong *)0x0;
              if (*(longlong *)(lVar15 + -8 + (ulonglong)bVar2 * 8) == _DAT_7fff6245a778) {
                plVar14 = plStack_a8;
              }
              (**(code **)(*plVar14 + 0x2a8))(plVar14,*(undefined8 *)(*plVar14 + 0x2b0));
            }
          }
        }
      }
      plVar14 = (longlong *)
                (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
      if ((plVar14 == (longlong *)0x0) ||
         (lVar15 = (**(code **)(*plVar14 + 0x1c8))(plVar14,*(undefined8 *)(*plVar14 + 0x1d0)),
         lVar15 == 0)) goto LAB_7fff5fe1b08c;
      cVar5 = FUN_7fff602d5fc0(lVar15,0x22e,&plStack_a8,0);
      if (cVar5 != '\0') {
        if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7fff6242a0c8 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*(longlong *)action + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7fff6242a0c8 + 0x130) * 8) != _DAT_7fff6242a0c8)) {
          bVar18 = false;
        }
        else {
          bVar18 = true;
        }
        puVar17 = (undefined *)0x0;
        if (bVar18) {
          puVar17 = action;
        }
        cVar5 = FUN_7fff60409110(puVar17,0,0);
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
              if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7fff6240b9a0 + 0x130)) ||
                 (*(longlong *)
                   (*(longlong *)(*(longlong *)action + 200) + -8 +
                   (ulonglong)*(byte *)(_DAT_7fff6240b9a0 + 0x130) * 8) != _DAT_7fff6240b9a0)) {
                FUN_7fff5f47c810(action);
                pcVar3 = (code *)swi(3);
                (*pcVar3)();
                return;
              }
              if ((action[0x104] & 2) != 0) goto LAB_7fff5fe1a6f0;
            }
          }
          else {
LAB_7fff5fe1a6f0:
            if (plStack_a8 == (longlong *)0x0) goto LAB_7fff5fe1b08c;
            if (((*(byte *)(*plStack_a8 + 0x130) < *(byte *)(_DAT_7fff62406520 + 0x130)) ||
                (*(longlong *)
                  (*(longlong *)(*plStack_a8 + 200) + -8 +
                  (ulonglong)*(byte *)(_DAT_7fff62406520 + 0x130) * 8) != _DAT_7fff62406520)) ||
               (plStack_a8 == (longlong *)0x0)) {
              FUN_7fff5f47c810(plStack_a8);
              pcVar3 = (code *)swi(3);
              (*pcVar3)();
              return;
            }
            cVar5 = func_0x7fff5f5e77f0(plStack_a8,2);
            plVar14 = plStack_a8;
            if (cVar5 != '\0') {
              if (plStack_a8 == (longlong *)0x0) goto LAB_7fff5fe1b08c;
              if (((*(byte *)(*plStack_a8 + 0x130) < *(byte *)(_DAT_7fff62406520 + 0x130)) ||
                  (*(longlong *)
                    (*(longlong *)(*plStack_a8 + 200) + -8 +
                    (ulonglong)*(byte *)(_DAT_7fff62406520 + 0x130) * 8) != _DAT_7fff62406520)) ||
                 (plStack_a8 == (longlong *)0x0)) {
                FUN_7fff5f47c810(plStack_a8);
                pcVar3 = (code *)swi(3);
                (*pcVar3)();
                return;
              }
              if (0.0 < *(float *)((longlong)plStack_a8 + 0x14)) {
                uVar16 = (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0));
                if (plVar14 == (longlong *)0x0) goto LAB_7fff5fe1b08c;
                if ((*(byte *)(*plVar14 + 0x130) < *(byte *)(_DAT_7fff62406520 + 0x130)) ||
                   (*(longlong *)
                     (*(longlong *)(*plVar14 + 200) + -8 +
                     (ulonglong)*(byte *)(_DAT_7fff62406520 + 0x130) * 8) != _DAT_7fff62406520)) {
                  FUN_7fff5f47c810(plVar14);
                  pcVar3 = (code *)swi(3);
                  (*pcVar3)();
                  return;
                }
                iVar7 = FUN_7fff602a5d20(plVar14,puVar17,uVar16,0);
                if (0 < iVar7) {
                  lVar15 = FUN_7fff5ff86680(0);
                  if ((lVar15 == 0) || (lVar15 = FUN_7fff5ff89fc0(lVar15,0), lVar15 == 0))
                  goto LAB_7fff5fe1b08c;
                  FUN_7fff60205f30(lVar15,0xc9,iVar7,0);
                }
                *(uint *)(damageData + 0x70) = *(uint *)(damageData + 0x70) | 0x2000;
              }
            }
          }
        }
      }
      FUN_7fff602b6290(plVar11,action,damageData,0);
      FUN_7fff60158ef0(plVar11,action,damageData,0);
    }
    FUN_7fff604072f0(action,plVar11,self,damageData,0);
    uVar8 = FUN_7fff5fe1bb10(self,*(undefined4 *)(damageData + 0x84),plVar11,0);
    iVar7 = FUN_7fff604066c0(action,self,uVar8,0);
    iVar9 = (**(code **)(*(longlong *)action + 0x188))
                      (action,*(undefined8 *)(*(longlong *)action + 400));
    if ((iVar9 == 0x3ec) && ((damageData[0x74] & 1) != 0)) {
      lVar15 = *(longlong *)(self + 0x78);
      if (lVar15 == 0) goto LAB_7fff5fe1b08c;
      if (iVar7 < *(int *)(lVar15 + 0x14)) goto LAB_7fff5fe1a8f0;
      iVar7 = *(int *)(lVar15 + 0x14) + -1;
    }
    else {
LAB_7fff5fe1a8f0:
      lVar15 = *(longlong *)(self + 0x78);
      if (lVar15 == 0) goto LAB_7fff5fe1b08c;
    }
    func_0x7fff5fe6b320(lVar15,*(int *)(lVar15 + 0x14) - iVar7,0);
    if (*(longlong *)(self + 0x80) == 0) goto LAB_7fff5fe1b08c;
    FUN_7fff5ffe5880(*(longlong *)(self + 0x80),0);
    (**(code **)(*(longlong *)self + 0x678))(self,*(undefined8 *)(*(longlong *)self + 0x680));
    if (*(int *)(damageData + 0x8c) != 0) {
      if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
        func_0x7fff5f47d6f0();
      }
      cVar5 = FUN_7fff618ab2e0(plVar11,0,0);
      if (cVar5 != '\0') {
        if ((plVar11 == (longlong *)0x0) ||
           (plVar11 = (longlong *)
                      (**(code **)(*plVar11 + 0x298))(plVar11,*(undefined8 *)(*plVar11 + 0x2a0)),
           plVar11 == (longlong *)0x0)) goto LAB_7fff5fe1b08c;
        lVar15 = (**(code **)(*plVar11 + 0x208))(plVar11,*(undefined8 *)(*plVar11 + 0x210));
        if ((lVar15 != 0) &&
           (cVar5 = func_0x7fff60028dd0(lVar15,*(undefined4 *)(damageData + 0x8c),0), cVar5 != '\0')
           ) {
          *(undefined4 *)(damageData + 0x8c) = 0;
        }
      }
      cVar5 = FUN_7fff5fe17a60(self,*(undefined4 *)(damageData + 0x8c),0);
      if (cVar5 != '\0') {
        *(undefined4 *)(damageData + 0x8c) = 0;
      }
      FUN_7fff5fe18610(self,actor,action,damageData,1,0);
    }
  }
  if (*(int *)(damageData + 0x14) != 0) {
    uVar8 = 0;
    FUN_7fff5fe1ea50(self,actor,action,damageData,0);
    FUN_7fff5fe1f120(self,actor,action,0);
    cVar5 = '\0';
    if (action == (undefined *)0x0) goto LAB_7fff5fe1b08c;
    cVar6 = FUN_7fff60407520(action,self,0);
    if (cVar6 == '\0') {
      cVar5 = FUN_7fff60407710(action,self,0);
      if (cVar5 == '\0') {
        FUN_7fff604061d0(action,self,0);
      }
      FUN_7fff60408380(action,self,0);
      cVar5 = '\x01';
    }
    iVar7 = (**(code **)(*(longlong *)action + 0x188))
                      (action,*(undefined8 *)(*(longlong *)action + 400));
    if (iVar7 == 0x4c3) {
LAB_7fff5fe1ac22:
      uVar10 = (**(code **)(*(longlong *)action + 0x188))
                         (action,*(undefined8 *)(*(longlong *)action + 400));
      if (*(int *)(_DAT_7fff62453798 + 0xe0) == 0) {
        func_0x7fff5f47d6f0();
      }
      cVar5 = func_0x7fff6031ced0(uVar10,0);
      if ((cVar5 != '\0') &&
         (cVar5 = (**(code **)(*(longlong *)action + 0x308))
                            (action,*(undefined8 *)(*(longlong *)action + 0x310)), cVar5 != '\0')) {
        iVar7 = (**(code **)(*(longlong *)action + 0x188))
                          (action,*(undefined8 *)(*(longlong *)action + 400));
        if (iVar7 != 0) {
          iVar7 = (**(code **)(*(longlong *)action + 0x1a8))
                            (action,*(undefined8 *)(*(longlong *)action + 0x1b0));
          if (iVar7 == 1) {
            lVar15 = *(longlong *)(self + 0x70);
            if ((lVar15 == 0) || (*(longlong *)(self + 0x78) == 0)) goto LAB_7fff5fe1b08c;
            uVar16 = CONCAT44(uVar8,(uint)*(byte *)(lVar15 + 0x36));
            func_0x7fff5fe6b090(*(longlong *)(self + 0x78),1,*(undefined1 *)(lVar15 + 0x34),
                                *(undefined1 *)(lVar15 + 0x35),uVar16,0);
            uVar8 = (undefined4)((ulonglong)uVar16 >> 0x20);
          }
          iVar7 = (**(code **)(*(longlong *)action + 0x1a8))
                            (action,*(undefined8 *)(*(longlong *)action + 0x1b0));
          if (iVar7 == 2) {
            lVar15 = *(longlong *)(self + 0x70);
            if ((lVar15 == 0) || (*(longlong *)(self + 0x78) == 0)) goto LAB_7fff5fe1b08c;
            uVar16 = CONCAT44(uVar8,(uint)*(byte *)(lVar15 + 0x36));
            func_0x7fff5fe6b090(*(longlong *)(self + 0x78),2,*(undefined1 *)(lVar15 + 0x34),
                                *(undefined1 *)(lVar15 + 0x35),uVar16,0);
            uVar8 = (undefined4)((ulonglong)uVar16 >> 0x20);
          }
          iVar7 = (**(code **)(*(longlong *)action + 0x1a8))
                            (action,*(undefined8 *)(*(longlong *)action + 0x1b0));
          if (iVar7 != 3) goto LAB_7fff5fe1ad9c;
        }
        lVar15 = *(longlong *)(self + 0x70);
        if ((lVar15 == 0) || (*(longlong *)(self + 0x78) == 0)) goto LAB_7fff5fe1b08c;
        func_0x7fff5fe6b090(*(longlong *)(self + 0x78),0,*(undefined1 *)(lVar15 + 0x34),
                            *(undefined1 *)(lVar15 + 0x35),
                            CONCAT44(uVar8,(uint)*(byte *)(lVar15 + 0x36)),0);
      }
    }
    else {
      iVar7 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      if (iVar7 == 0x9f) {
        if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7fff62475ff0 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*(longlong *)action + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7fff62475ff0 + 0x130) * 8) != _DAT_7fff62475ff0)) {
          FUN_7fff5f47c810(action);
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
        cVar5 = FUN_7fff601e1c30(action,self,0);
        goto LAB_7fff5fe1ac1a;
      }
      iVar7 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      if (iVar7 == 0x292) goto LAB_7fff5fe1ac22;
      iVar7 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      if (iVar7 == 0x75) {
        if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7fff62466220 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*(longlong *)action + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7fff62466220 + 0x130) * 8) != _DAT_7fff62466220)) {
          FUN_7fff5f47c810(action);
          pcVar3 = (code *)swi(3);
          (*pcVar3)();
          return;
        }
        cVar5 = func_0x7fff601d7b40(action,0);
        goto LAB_7fff5fe1ac1a;
      }
      iVar7 = (**(code **)(*(longlong *)action + 0x188))
                        (action,*(undefined8 *)(*(longlong *)action + 400));
      if (iVar7 == 0x22a) goto LAB_7fff5fe1ac22;
      lVar15 = *(longlong *)action;
      if ((*(byte *)(lVar15 + 0x130) < *(byte *)(_DAT_7fff62453aa8 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(lVar15 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7fff62453aa8 + 0x130) * 8)
          != _DAT_7fff62453aa8)) {
        iVar7 = (**(code **)(lVar15 + 0x188))(action,*(undefined8 *)(lVar15 + 400));
        if ((iVar7 != 0x12d) || ((damageData[0x74] & 2) != 0)) goto LAB_7fff5fe1ac1a;
      }
      else {
        cVar5 = func_0x7fff6027eef0(action,0);
LAB_7fff5fe1ac1a:
        if (cVar5 != '\0') goto LAB_7fff5fe1ac22;
      }
    }
LAB_7fff5fe1ad9c:
    iVar7 = (**(code **)(*(longlong *)action + 0x188))
                      (action,*(undefined8 *)(*(longlong *)action + 400));
    if (iVar7 == 0x292) {
      if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7fff62438f60 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*(longlong *)action + 200) + -8 +
           (ulonglong)*(byte *)(_DAT_7fff62438f60 + 0x130) * 8) != _DAT_7fff62438f60)) {
        FUN_7fff5f47c810(action);
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
      func_0x7fff6016a420(action,0);
    }
    iVar7 = (**(code **)(*(longlong *)action + 0x188))
                      (action,*(undefined8 *)(*(longlong *)action + 400));
    if (iVar7 == 0x22a) {
      if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7fff624336f8 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*(longlong *)action + 200) + -8 +
           (ulonglong)*(byte *)(_DAT_7fff624336f8 + 0x130) * 8) != _DAT_7fff624336f8)) {
        FUN_7fff5f47c810(action);
        pcVar3 = (code *)swi(3);
        (*pcVar3)();
        return;
      }
      func_0x7fff60199c50(action,0);
    }
  }
  cVar5 = (**(code **)(*(longlong *)self + 0x188))(self,*(undefined8 *)(*(longlong *)self + 400));
  if ((cVar5 == '\0') || (cVar4 != '\0')) {
    if (0 < *(int *)(damageData + 0x84)) {
      if (*(longlong *)(self + 0x20) != 0) {
        puVar13 = (undefined8 *)FUN_7fff618c8890(&uStack_68,*(longlong *)(self + 0x20),0);
        uStack_80 = *puVar13;
        fStack_78 = *(float *)(puVar13 + 1);
        if ((actor != (undefined *)0x0) && (lVar15 = FUN_7fff618a4a10(actor,0), lVar15 != 0)) {
          puVar13 = (undefined8 *)FUN_7fff618c8890(&uStack_68,lVar15,0);
          fStack_78 = fStack_78 - *(float *)(puVar13 + 1);
          lVar15 = *(longlong *)(self + 0x48);
          iVar7 = *(int *)(damageData + 0x84);
          uStack_68 = CONCAT44(uStack_80._4_4_ - (float)((ulonglong)*puVar13 >> 0x20),
                               (float)uStack_80 - (float)*puVar13);
          fStack_60 = fStack_78;
          lVar12 = (**(code **)(*(longlong *)self + 0x518))
                             (self,*(undefined8 *)(*(longlong *)self + 0x520));
          if (lVar12 != 0) {
            iVar9 = FUN_7fff5f252ec0(0,_DAT_7fff624465a0,lVar12);
            puVar13 = (undefined8 *)FUN_7fff5f50ca00(&uStack_80,&uStack_68,0);
            if (lVar15 != 0) {
              uStack_68 = *puVar13;
              fStack_60 = *(float *)(puVar13 + 1);
              uVar16 = FUN_7fff604fe7b0(lVar15,_DAT_7fff61b52b18,(float)iVar7 / (float)iVar9,
                                        &uStack_68,0);
              FUN_7fff618a87c0(self,uVar16,0);
              return;
            }
          }
        }
      }
LAB_7fff5fe1b08c:
      FUN_7fff5f47d660();
      pcVar3 = (code *)swi(3);
      (*pcVar3)();
      return;
    }
  }
  else {
    uVar16 = *(undefined8 *)(self + 0x58);
    if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    cVar4 = FUN_7fff618ab240(uVar16,0);
    if (cVar4 != '\0') {
      plVar11 = *(longlong **)(self + 0x58);
      if (plVar11 == (longlong *)0x0) goto LAB_7fff5fe1b08c;
      (**(code **)(*plVar11 + 0x1d8))(plVar11,*(undefined8 *)(*plVar11 + 0x1e0));
    }
    uVar16 = *(undefined8 *)(self + 0x68);
    if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    cVar4 = FUN_7fff618ab240(uVar16,0);
    if (cVar4 != '\0') {
      if (*(longlong *)(self + 0x68) == 0) goto LAB_7fff5fe1b08c;
      FUN_7fff5f9f98d0(*(longlong *)(self + 0x68),0);
    }
    FUN_7fff5fe16e70(self,id,0);
  }
  return;
}

