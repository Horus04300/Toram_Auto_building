
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte _LoadMapInfo_d__94_MoveNext(undefined *self,undefined *methodInfo)

{
  int iVar1;
  code *pcVar2;
  bool bVar3;
  char cVar4;
  byte bVar5;
  longlong *plVar6;
  undefined8 uVar7;
  longlong *plVar8;
  longlong lVar9;
  undefined *self_00;
  longlong *plVar10;
  undefined8 uVar11;
  longlong *plVar12;
  undefined *puVar13;
  longlong lVar14;
  undefined8 uVar15;
  undefined8 uVar16;
  int aiStackX_8 [2];
  undefined4 auStackX_18 [2];
  ulonglong in_stack_ffffffffffffffb8;
  
  if (DAT_7fff625e71d6 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff623fb4c8);
    FUN_7fff5f47d450(&DAT_7fff62436790);
    FUN_7fff5f47d450(&DAT_7fff6243b8b8);
    FUN_7fff5f47d450(0x7fff6244df18);
    FUN_7fff5f47d450(&DAT_7fff62454290);
    FUN_7fff5f47d450(&DAT_7fff62468fe0);
    FUN_7fff5f47d450(&DAT_7fff62414030);
    FUN_7fff5f47d450(&DAT_7fff624532c0);
    FUN_7fff5f47d450(&DAT_7fff62422c48);
    FUN_7fff5f47d450(&DAT_7fff6240e4b0);
    FUN_7fff5f47d450(&DAT_7fff6245d4e8);
    FUN_7fff5f47d450(&DAT_7fff6245dce0);
    FUN_7fff5f47d450(0x7fff6245c360);
    FUN_7fff5f47d450(&DAT_7fff6245bdd8);
    FUN_7fff5f47d450(&DAT_7fff6245a460);
    FUN_7fff5f47d450(&DAT_7fff62468308);
    FUN_7fff5f47d450(&DAT_7fff6246a948);
    FUN_7fff5f47d450(&DAT_7fff62437e68);
    FUN_7fff5f47d450(&DAT_7fff62444f38);
    FUN_7fff5f47d450(&DAT_7fff62437f28);
    FUN_7fff5f47d450(&DAT_7fff62445000);
    FUN_7fff5f47d450(&DAT_7fff62437ff0);
    FUN_7fff5f47d450(&DAT_7fff624450c0);
    FUN_7fff5f47d450(&DAT_7fff62406568);
    FUN_7fff5f47d450(0x7fff624635b8);
    FUN_7fff5f47d450(0x7fff6246b2c0);
    FUN_7fff5f47d450(0x7fff62444220);
    FUN_7fff5f47d450(0x7fff62458498);
    FUN_7fff5f47d450(0x7fff62458560);
    FUN_7fff5f47d450(0x7fff624587a8);
    FUN_7fff5f47d450(0x7fff623f7a90);
    FUN_7fff5f47d450(0x7fff62471fd8);
    FUN_7fff5f47d450(0x7fff6244ee10);
    FUN_7fff5f47d450(&DAT_7fff6245d0c8);
    FUN_7fff5f47d450(0x7fff62458620);
    FUN_7fff5f47d450(&DAT_7fff624583d8);
    FUN_7fff5f47d450(0x7fff624580c8);
    FUN_7fff5f47d450(&DAT_7fff6244b098);
    FUN_7fff5f47d450(0x7fff62458000);
    FUN_7fff5f47d450(0x7fff62400410);
    FUN_7fff5f47d450(0x7fff624586e8);
    FUN_7fff5f47d450(0x7fff62437f38);
    FUN_7fff5f47d450(0x7fff62458310);
    FUN_7fff5f47d450(&DAT_7fff6244b2e0);
    FUN_7fff5f47d450(0x7fff6246b388);
    FUN_7fff5f47d450(0x7fff62458250);
    FUN_7fff5f47d450(&DAT_7fff62458870);
    FUN_7fff5f47d450(0x7fff6246a0a8);
    FUN_7fff5f47d450(0x7fff62458188);
    FUN_7fff5f47d450(&DAT_7fff62453f28);
    FUN_7fff5f47d450(0x7fff62467fc8);
    FUN_7fff5f47d450(0x7fff6246a178);
    FUN_7fff5f47d450(&DAT_7fff623f7f60);
    FUN_7fff5f47d450(&DAT_7fff62453e68);
    FUN_7fff5f47d450(0x7fff6241a8e0);
    FUN_7fff5f47d450(0x7fff623f7b60);
    FUN_7fff5f47d450(&DAT_7fff62458930);
    FUN_7fff5f47d450(&DAT_7fff6241f290);
    DAT_7fff625e71d6 = '\x01';
  }
  iVar1 = *(int *)(self + 0x10);
  plVar12 = (longlong *)0x0;
  lVar9 = *(longlong *)(self + 0x30);
  if (iVar1 != 0) {
    if (iVar1 == 1) {
      *(undefined4 *)(self + 0x10) = 0xffffffff;
      if (*(longlong *)(self + 0x38) == 0) goto LAB_7fff6037f4eb;
      if (*(char *)(*(longlong *)(self + 0x38) + 0x10) == '\0') {
        plVar10 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
        lVar9 = *(longlong *)(self + 0x60);
        if (plVar10 == (longlong *)0x0) goto LAB_7fff6037f4eb;
        if ((lVar9 != 0) &&
           (lVar14 = func_0x7fff5f47c7e0(lVar9,*(undefined8 *)(*plVar10 + 0x40)), lVar14 == 0)) {
          uVar16 = func_0x7fff5f47d0b0();
          FUN_7fff5f47d620(uVar16,0);
          pcVar2 = (code *)swi(3);
          bVar5 = (*pcVar2)();
          return bVar5;
        }
        if ((int)plVar10[3] == 0) {
          FUN_7fff5f47d650();
          pcVar2 = (code *)swi(3);
          bVar5 = (*pcVar2)();
          return bVar5;
        }
        plVar10[4] = lVar9;
        thunk_FUN_7fff5f491fd0();
        _loadFieldData_d__125_System_IDisposable_Dispose(_DAT_7fff62453e68,(undefined *)plVar10);
        if (*(int *)(self + 0x70) < 5) {
          plVar12 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
          aiStackX_8[0] = *(int *)(self + 0x70) + 1;
          lVar9 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,aiStackX_8);
          if (plVar12 == (longlong *)0x0) {
            FUN_7fff5f47d660();
            pcVar2 = (code *)swi(3);
            bVar5 = (*pcVar2)();
            return bVar5;
          }
          if ((lVar9 != 0) &&
             (lVar14 = func_0x7fff5f47c7e0(lVar9,*(undefined8 *)(*plVar12 + 0x40)), lVar14 == 0)) {
            uVar16 = func_0x7fff5f47d0b0();
            FUN_7fff5f47d620(uVar16,0);
            pcVar2 = (code *)swi(3);
            bVar5 = (*pcVar2)();
            return bVar5;
          }
          if ((int)plVar12[3] == 0) {
            FUN_7fff5f47d650();
            pcVar2 = (code *)swi(3);
            bVar5 = (*pcVar2)();
            return bVar5;
          }
          plVar12[4] = lVar9;
          thunk_FUN_7fff5f491fd0();
          _loadFieldData_d__125_System_IDisposable_Dispose(_DAT_7fff62453f28,(undefined *)plVar12);
          uVar16 = func_0x7fff5f44ff00(_DAT_7fff62406568);
          FUN_7fff618b74f0(uVar16,_DAT_7fff61b52b74,0);
          *(undefined8 *)(self + 0x18) = uVar16;
          thunk_FUN_7fff5f491fd0();
          *(undefined4 *)(self + 0x10) = 2;
          return 1;
        }
        puVar13 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff62445000);
        _loadFieldData_d__125_System_IDisposable_Dispose(puVar13,(undefined *)0x0);
        *(undefined **)(self + 0x40) = puVar13;
        thunk_FUN_7fff5f491fd0();
        if (*(longlong *)(self + 0x40) == 0) goto LAB_7fff6037f4eb;
        *(undefined1 *)(*(longlong *)(self + 0x40) + 0x10) = 0;
        puVar13 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff6245a460);
        if (puVar13 == (undefined *)0x0) goto LAB_7fff6037f4eb;
        plVar10 = (longlong *)LocalizeManager_Get(puVar13,(undefined *)0x0,(undefined *)0x0);
        if (plVar10 != (longlong *)0x0) {
          if ((*(byte *)(*plVar10 + 0x130) < *(byte *)(_DAT_7fff62468308 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(*plVar10 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7fff62468308 + 0x130) * 8) != _DAT_7fff62468308)) {
            bVar3 = false;
          }
          else {
            bVar3 = true;
          }
          if (bVar3) {
            plVar12 = plVar10;
          }
          lVar9 = FUN_7fff60c4bc00(_DAT_7fff6245dce0);
          if (plVar12 == (longlong *)0x0) goto LAB_7fff6037f4eb;
          uVar7 = FUN_7fff5f568150(plVar12,_DAT_7fff6244b2e0,0);
          uVar15 = FUN_7fff5f568150(plVar12,_DAT_7fff6244b098,0);
          uVar16 = *(undefined8 *)(self + 0x40);
          uVar11 = func_0x7fff5f44ff00(_DAT_7fff62436790);
          FUN_7fff5f4f6880(uVar11,uVar16,_DAT_7fff62437f28,0);
          if (lVar9 == 0) goto LAB_7fff6037f4eb;
          FUN_7fff5fdd4a60(lVar9,uVar7,uVar15,uVar11,0);
          goto LAB_7fff6037ed4b;
        }
      }
      else {
        lVar14 = FUN_7fff60c4bc00(_DAT_7fff6245bdd8);
        if (lVar14 == 0) goto LAB_7fff6037f4eb;
        in_stack_ffffffffffffffb8 = in_stack_ffffffffffffffb8 & 0xffffffffffffff00;
        plVar6 = (longlong *)
                 FUN_7fff5f5deba0(lVar14,*(undefined8 *)(self + 0x60),*(undefined8 *)(self + 0x68),4
                                  ,in_stack_ffffffffffffffb8,1,0);
        plVar10 = plVar12;
        if ((plVar6 != (longlong *)0x0) && (*plVar6 == _DAT_7fff62414030)) {
          plVar10 = plVar6;
        }
        if (self[0x48] != '\0') {
          lVar14 = FUN_7fff60c4bc00(_DAT_7fff6245bdd8);
          aiStackX_8[0] = *(int *)(self + 0x58);
          uVar16 = *(undefined8 *)(self + 0x60);
          uVar7 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,aiStackX_8);
          uVar7 = FUN_7fff60e74b00(_DAT_7fff62458930,uVar7,0);
          if (lVar14 == 0) {
            FUN_7fff5f47d660();
            pcVar2 = (code *)swi(3);
            bVar5 = (*pcVar2)();
            return bVar5;
          }
          plVar8 = (longlong *)
                   FUN_7fff5f5deba0(lVar14,uVar16,uVar7,0,
                                    in_stack_ffffffffffffffb8 & 0xffffffffffffff00,1,0);
          plVar6 = plVar12;
          if (plVar8 != (longlong *)0x0) {
            if ((*(byte *)(*plVar8 + 0x130) < *(byte *)(_DAT_7fff6246a948 + 0x130)) ||
               (*(longlong *)
                 (*(longlong *)(*plVar8 + 200) + -8 +
                 (ulonglong)*(byte *)(_DAT_7fff6246a948 + 0x130) * 8) != _DAT_7fff6246a948)) {
              bVar3 = false;
            }
            else {
              bVar3 = true;
            }
            if (bVar3) {
              plVar6 = plVar8;
            }
          }
          if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
            func_0x7fff5f47d6f0();
          }
          cVar4 = FUN_7fff618ab2e0(plVar6,0);
          if (cVar4 != '\0') {
            if (plVar6 == (longlong *)0x0) goto LAB_7fff6037f4eb;
            uVar16 = FUN_7fff618b0e20(plVar6,0);
            *(undefined8 *)(self + 0x50) = uVar16;
            thunk_FUN_7fff5f491fd0();
          }
        }
        lVar14 = FUN_7fff60c4bc00(_DAT_7fff6245bdd8);
        if (lVar14 == 0) goto LAB_7fff6037f4eb;
        FUN_7fff5f5e0fd0(lVar14,*(undefined8 *)(self + 0x60),0,0);
        if (*(longlong *)(self + 0x38) == 0) goto LAB_7fff6037f4eb;
        if (*(char *)(*(longlong *)(self + 0x38) + 0x10) != '\0') {
          if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
            func_0x7fff5f47d6f0();
          }
          cVar4 = FUN_7fff618ab2e0(plVar10);
          if (cVar4 != '\0') {
            if (plVar10 != (longlong *)0x0) {
              FUN_7fff618a4510(plVar10,1,0);
              lVar14 = FUN_7fff618a4a10(plVar10,0);
              if ((lVar9 != 0) && (uVar16 = FUN_7fff618a1b90(lVar9,0), lVar14 != 0)) {
                FUN_7fff618c8fd0(lVar14,uVar16,0);
                uVar16 = FUN_7fff606a6750(plVar10,_DAT_7fff62468fe0);
                *(undefined8 *)(lVar9 + 0x20) = uVar16;
                thunk_FUN_7fff5f491fd0();
                if (self[0x48] == '\0') {
                  return 0;
                }
                lVar9 = FUN_7fff60c4bc00(_DAT_7fff6245d4e8);
                if (lVar9 != 0) {
                  FUN_7fff60365190(lVar9,*(undefined4 *)(self + 0x58),*(undefined8 *)(self + 0x50),0
                                  );
                  return 0;
                }
              }
            }
            goto LAB_7fff6037f4eb;
          }
        }
        puVar13 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff624450c0);
        _loadFieldData_d__125_System_IDisposable_Dispose(puVar13,(undefined *)0x0);
        if (puVar13 == (undefined *)0x0) goto LAB_7fff6037f4eb;
        puVar13[0x10] = 0;
        self_00 = (undefined *)FUN_7fff60c4bc00(_DAT_7fff6245a460);
        if (self_00 == (undefined *)0x0) goto LAB_7fff6037f4eb;
        plVar10 = (longlong *)LocalizeManager_Get(self_00,(undefined *)0x0,(undefined *)0x0);
        if (plVar10 != (longlong *)0x0) {
          if ((*(byte *)(*plVar10 + 0x130) < *(byte *)(_DAT_7fff62468308 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(*plVar10 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7fff62468308 + 0x130) * 8) != _DAT_7fff62468308)) {
            bVar3 = false;
          }
          else {
            bVar3 = true;
          }
          if (bVar3) {
            plVar12 = plVar10;
          }
          lVar9 = FUN_7fff60c4bc00(_DAT_7fff6245dce0);
          if (plVar12 == (longlong *)0x0) goto LAB_7fff6037f4eb;
          uVar16 = FUN_7fff5f568150(plVar12,_DAT_7fff6244b2e0,0);
          uVar7 = FUN_7fff5f568150(plVar12,_DAT_7fff6244b098,0);
          uVar15 = func_0x7fff5f44ff00(_DAT_7fff62436790);
          FUN_7fff5f4f6880(uVar15,puVar13,_DAT_7fff62437ff0,0);
          if (lVar9 == 0) goto LAB_7fff6037f4eb;
          FUN_7fff5fdd4a60(lVar9,uVar16,uVar7,uVar15,0);
          goto LAB_7fff6037eb91;
        }
      }
      FUN_7fff60c4bc00(_DAT_7fff6245dce0);
      goto LAB_7fff6037f4eb;
    }
    if (iVar1 != 2) {
      if (iVar1 != 3) {
        return 0;
      }
      *(undefined4 *)(self + 0x10) = 0xffffffff;
LAB_7fff6037ed4b:
      if (*(longlong *)(self + 0x40) != 0) {
        if (*(char *)(*(longlong *)(self + 0x40) + 0x10) == '\0') {
          *(undefined8 *)(self + 0x18) = 0;
          thunk_FUN_7fff5f491fd0();
          *(undefined4 *)(self + 0x10) = 3;
          return 1;
        }
LAB_7fff6037eb91:
        if (*(int *)(_DAT_7fff6243b8b8 + 0xe0) == 0) {
          func_0x7fff5f47d6f0();
        }
        FUN_7fff61880a90(0);
        return 0;
      }
      goto LAB_7fff6037f4eb;
    }
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    *(int *)(self + 0x70) = *(int *)(self + 0x70) + 1;
    goto LAB_7fff6037f3d0;
  }
  *(undefined8 *)(self + 0x50) = 0;
  *(undefined4 *)(self + 0x10) = 0xffffffff;
  self[0x48] = 0;
  thunk_FUN_7fff5f491fd0();
  *(undefined4 *)(self + 0x58) = 0xffffffff;
  *(undefined8 *)(self + 0x60) = _DAT_7fff623f7f60;
  thunk_FUN_7fff5f491fd0();
  *(undefined8 *)(self + 0x68) = _DAT_7fff623f7f60;
  thunk_FUN_7fff5f491fd0();
  iVar1 = *(int *)(self + 0x20);
  switch(iVar1) {
  case 4:
    *(undefined8 *)(self + 0x60) = uRam00007fff62458310;
    thunk_FUN_7fff5f491fd0();
    aiStackX_8[0] = 0;
    uVar7 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,aiStackX_8);
    uVar16 = uRam00007fff62467fc8;
    goto LAB_7fff6037ef2d;
  case 5:
    *(undefined8 *)(self + 0x60) = uRam00007fff62458498;
    thunk_FUN_7fff5f491fd0();
    aiStackX_8[0] = CONCAT31(aiStackX_8[0]._1_3_,self[0x24]);
    uVar7 = func_0x7fff5f47c7a0(_DAT_7fff62454290,aiStackX_8);
    uVar16 = uRam00007fff623f7b60;
    goto LAB_7fff6037ef2d;
  case 6:
  case 7:
  case 9:
LAB_7fff6037f320:
    aiStackX_8[0] = *(int *)(self + 0x28) / 1000;
    *(int *)(self + 0x58) = aiStackX_8[0];
    uVar16 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,aiStackX_8);
    uVar16 = FUN_7fff60e74b00(_DAT_7fff624583d8,uVar16,0);
    *(undefined8 *)(self + 0x60) = uVar16;
    thunk_FUN_7fff5f491fd0();
    auStackX_18[0] = *(undefined4 *)(self + 0x28);
    uVar16 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,auStackX_18);
    uVar16 = FUN_7fff60e74b00(_DAT_7fff6241f290,uVar16,0);
    *(undefined8 *)(self + 0x68) = uVar16;
    thunk_FUN_7fff5f491fd0();
    lVar14 = FUN_7fff60c4bc00(_DAT_7fff6245d4e8);
    if (lVar14 == 0) {
      FUN_7fff5f47d660();
      pcVar2 = (code *)swi(3);
      bVar5 = (*pcVar2)();
      return bVar5;
    }
    self[0x48] = *(int *)(lVar14 + 0x28) != *(int *)(self + 0x58);
    break;
  case 8:
    *(undefined8 *)(self + 0x60) = uRam00007fff62458250;
    thunk_FUN_7fff5f491fd0();
    aiStackX_8[0] = 0;
    uVar7 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,aiStackX_8);
    uVar16 = uRam00007fff624635b8;
LAB_7fff6037ef2d:
    uVar16 = FUN_7fff60e74b00(uVar16,uVar7,0);
code_r0x7fff6037ef38:
    *(undefined8 *)(self + 0x68) = uVar16;
    thunk_FUN_7fff5f491fd0();
    break;
  case 10:
    *(undefined8 *)(self + 0x60) = uRam00007fff624586e8;
    thunk_FUN_7fff5f491fd0();
    *(undefined8 *)(self + 0x68) = uRam00007fff62471fd8;
    thunk_FUN_7fff5f491fd0();
    break;
  default:
    if (iVar1 == 0x11) {
      *(undefined8 *)(self + 0x60) = _DAT_7fff62458870;
      thunk_FUN_7fff5f491fd0();
      aiStackX_8[0] = 0;
      uVar7 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,aiStackX_8);
      uVar16 = _DAT_7fff6245d0c8;
      goto LAB_7fff6037ef2d;
    }
    switch(iVar1) {
    case 0x16:
      *(undefined8 *)(self + 0x60) = uRam00007fff62458000;
      thunk_FUN_7fff5f491fd0();
      lVar14 = FUN_7fff60c4bc00(uRam00007fff6245c360);
      if (lVar14 == 0) goto LAB_7fff6037f4eb;
      plVar12 = *(longlong **)(lVar14 + 0x28);
      if (plVar12 != (longlong *)0x0) {
        if (((*(byte *)(lRam00007fff6244df18 + 0x130) <= *(byte *)(*plVar12 + 0x130)) &&
            (*(longlong *)
              (*(longlong *)(*plVar12 + 200) + -8 +
              (ulonglong)*(byte *)(lRam00007fff6244df18 + 0x130) * 8) == lRam00007fff6244df18)) &&
           ((char)plVar12[0xf] == '\x01')) {
          uVar16 = FUN_7fff6100e780(self + 0x28,0);
          uVar16 = FUN_7fff60e71970(uRam00007fff6246a0a8,uVar16,0);
          goto code_r0x7fff6037ef38;
        }
      }
      *(undefined8 *)(self + 0x68) = uRam00007fff6246a178;
      thunk_FUN_7fff5f491fd0();
      break;
    default:
      goto LAB_7fff6037f320;
    case 0x1b:
      uVar16 = FUN_7fff618af100(uRam00007fff62444220,0);
      if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
        func_0x7fff5f47d6f0();
      }
      plVar10 = (longlong *)FUN_7fff618aa420(uVar16,0);
      if (plVar10 != (longlong *)0x0) {
        if (*plVar10 == _DAT_7fff62414030) {
          plVar12 = plVar10;
        }
        if (plVar12 != (longlong *)0x0) {
          FUN_7fff618a4510(plVar12,1,0);
          lVar14 = FUN_7fff618a4a10(plVar12,0);
          if ((lVar9 != 0) && (uVar16 = FUN_7fff618a1b90(lVar9,0), lVar14 != 0)) {
            FUN_7fff618c8fd0(lVar14,uVar16,0);
            uVar16 = FUN_7fff606a6750(plVar12,_DAT_7fff62468fe0);
            *(undefined8 *)(lVar9 + 0x20) = uVar16;
            thunk_FUN_7fff5f491fd0();
            return 0;
          }
        }
      }
      goto LAB_7fff6037f4eb;
    case 0x1e:
      *(undefined8 *)(self + 0x60) = uRam00007fff62458498;
      thunk_FUN_7fff5f491fd0();
      aiStackX_8[0] = (uint)(byte)self[0x24] + ((byte)self[0x24] / 10) * -10;
      uVar7 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,aiStackX_8);
      uVar16 = uRam00007fff623f7a90;
      goto LAB_7fff6037ef2d;
    case 0x1f:
      *(undefined8 *)(self + 0x60) = uRam00007fff624580c8;
      thunk_FUN_7fff5f491fd0();
      uVar16 = FUN_7fff60f8f420(self + 0x24,0);
      uVar16 = FUN_7fff60e71970(uRam00007fff62400410,uVar16,0);
      goto code_r0x7fff6037ef38;
    case 0x20:
      *(undefined8 *)(self + 0x60) = uRam00007fff62458620;
      thunk_FUN_7fff5f491fd0();
      if (*(int *)(self + 0x28) == 0x17250) {
        *(undefined8 *)(self + 0x68) = uRam00007fff6246b388;
        thunk_FUN_7fff5f491fd0();
      }
      else {
        *(undefined8 *)(self + 0x68) = uRam00007fff6246b2c0;
        thunk_FUN_7fff5f491fd0();
      }
      break;
    case 0x21:
      *(undefined8 *)(self + 0x60) = uRam00007fff62458188;
      thunk_FUN_7fff5f491fd0();
      *(undefined8 *)(self + 0x68) = uRam00007fff6241a8e0;
      thunk_FUN_7fff5f491fd0();
      break;
    case 0x22:
      *(undefined8 *)(self + 0x60) = uRam00007fff624587a8;
      thunk_FUN_7fff5f491fd0();
      aiStackX_8[0] = *(int *)(self + 0x28);
      uVar7 = func_0x7fff5f47c7a0(_DAT_7fff624532c0,aiStackX_8);
      uVar16 = uRam00007fff62437f38;
      goto LAB_7fff6037ef2d;
    case 0x24:
      *(undefined8 *)(self + 0x60) = uRam00007fff62458560;
      thunk_FUN_7fff5f491fd0();
      *(undefined8 *)(self + 0x68) = uRam00007fff6244ee10;
      thunk_FUN_7fff5f491fd0();
    }
  }
  *(undefined4 *)(self + 0x70) = 0;
LAB_7fff6037f3d0:
  if (4 < *(int *)(self + 0x70)) {
    return 0;
  }
  puVar13 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff62444f38);
  _loadFieldData_d__125_System_IDisposable_Dispose(puVar13,(undefined *)0x0);
  *(undefined **)(self + 0x38) = puVar13;
  thunk_FUN_7fff5f491fd0();
  if (*(longlong *)(self + 0x38) != 0) {
    *(undefined1 *)(*(longlong *)(self + 0x38) + 0x10) = 0;
    lVar14 = FUN_7fff60c4bc00(_DAT_7fff6245bdd8);
    uVar16 = *(undefined8 *)(self + 0x60);
    uVar7 = *(undefined8 *)(self + 0x38);
    uVar15 = func_0x7fff5f44ff00(_DAT_7fff623fb4c8);
    FUN_7fff60739100(uVar15,uVar7,_DAT_7fff62437e68,0);
    if ((lVar14 != 0) && (uVar16 = FUN_7fff5f5e0250(lVar14,uVar16,1,uVar15,0), lVar9 != 0)) {
      uVar16 = FUN_7fff618a87c0(lVar9,uVar16,0);
      *(undefined8 *)(self + 0x18) = uVar16;
      thunk_FUN_7fff5f491fd0();
      *(undefined4 *)(self + 0x10) = 1;
      return 1;
    }
  }
LAB_7fff6037f4eb:
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  bVar5 = (*pcVar2)();
  return bVar5;
}

