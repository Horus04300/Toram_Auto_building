
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte _OnBossMenuCommand_d__263_MoveNext(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  byte bVar3;
  undefined1 uVar4;
  char cVar5;
  byte bVar6;
  short sVar7;
  undefined4 uVar8;
  undefined8 *puVar9;
  longlong lVar10;
  undefined8 uVar11;
  longlong *plVar12;
  int iVar13;
  undefined4 uVar14;
  undefined4 uVar15;
  undefined4 uVar16;
  bool bStackX_8;
  short sStackX_18;
  undefined4 uStackX_20;
  undefined8 in_stack_ffffffffffffff80;
  undefined8 uStack_68;
  undefined8 uStack_58;
  undefined4 uStack_50;
  
  if (DAT_7fff625e7d9f == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62451190);
    FUN_7fff5f47d450(&DAT_7fff62451318);
    FUN_7fff5f47d450(&DAT_7fff6246e380);
    FUN_7fff5f47d450(&DAT_7fff6246e5e8);
    FUN_7fff5f47d450(&DAT_7fff6240e4b0);
    FUN_7fff5f47d450(&DAT_7fff6245c360);
    FUN_7fff5f47d450(&DAT_7fff6245d9b0);
    FUN_7fff5f47d450(&DAT_7fff623f7f60);
    DAT_7fff625e7d9f = '\x01';
  }
  iVar13 = *(int *)(self + 0x10);
  lVar1 = *(longlong *)(self + 0x20);
  if (iVar13 == 0) {
    *(undefined4 *)(self + 0x10) = 0xffffffff;
    if (lVar1 == 0) goto LAB_7fff605394e7;
    if (*(int *)(lVar1 + 0xdc) == 0) {
      FUN_7fff6051a620(lVar1,1);
    }
    uVar4 = 0;
    self[0x2c] = *(undefined1 *)(lVar1 + 0xe2);
    lVar10 = *(longlong *)(lVar1 + 0x40);
    *(undefined1 *)(lVar1 + 0xe2) = 2;
    bStackX_8 = false;
    if (lVar10 == 0) goto LAB_7fff605394e7;
    if (*(int *)(lVar10 + 0x18) < 0xf) {
      if (*(int *)(lVar10 + 0x18) < 0xe) {
        sVar7 = FUN_7fff60506a30();
        iVar13 = (int)sVar7;
      }
      else {
        iVar13 = FUN_7fff60506890();
      }
      if (*(longlong *)(lVar1 + 0x40) == 0) goto LAB_7fff605394e7;
      bVar3 = FUN_7fff60506580(*(longlong *)(lVar1 + 0x40),0);
      if (*(longlong *)(lVar1 + 0x40) == 0) goto LAB_7fff605394e7;
      puVar9 = (undefined8 *)FUN_7fff60506b50(&uStack_58,*(longlong *)(lVar1 + 0x40),0);
      uVar15 = (undefined4)*puVar9;
      uVar16 = (undefined4)((ulonglong)*puVar9 >> 0x20);
      uStackX_20 = *(undefined4 *)(puVar9 + 1);
      if (*(longlong *)(lVar1 + 0x40) == 0) goto LAB_7fff605394e7;
      sStackX_18 = FUN_7fff60506a30(*(longlong *)(lVar1 + 0x40),0);
      if (*(longlong *)(lVar1 + 0x40) == 0) goto LAB_7fff605394e7;
      FUN_7fff60506a30(*(longlong *)(lVar1 + 0x40),0);
      uStack_68 = FUN_7fff6051b190(lVar1,0);
      if (*(longlong *)(lVar1 + 0x40) == 0) goto LAB_7fff605394e7;
      uVar8 = FUN_7fff60506890(*(longlong *)(lVar1 + 0x40),0);
    }
    else {
      bVar6 = FUN_7fff60506580(lVar10,0);
      if (*(longlong *)(lVar1 + 0x40) == 0) goto LAB_7fff605394e7;
      FUN_7fff60506580(*(longlong *)(lVar1 + 0x40),0);
      if (*(longlong *)(lVar1 + 0x40) == 0) goto LAB_7fff605394e7;
      iVar13 = FUN_7fff60506890(*(longlong *)(lVar1 + 0x40),0);
      if (*(longlong *)(lVar1 + 0x40) == 0) goto LAB_7fff605394e7;
      bVar3 = FUN_7fff60506580(*(longlong *)(lVar1 + 0x40),0);
      if (*(longlong *)(lVar1 + 0x40) == 0) goto LAB_7fff605394e7;
      puVar9 = (undefined8 *)FUN_7fff60506b50(&uStack_58,*(longlong *)(lVar1 + 0x40),0);
      uVar15 = (undefined4)*puVar9;
      uVar16 = (undefined4)((ulonglong)*puVar9 >> 0x20);
      uStackX_20 = *(undefined4 *)(puVar9 + 1);
      if (*(longlong *)(lVar1 + 0x40) == 0) goto LAB_7fff605394e7;
      sStackX_18 = FUN_7fff60506a30(*(longlong *)(lVar1 + 0x40),0);
      if (*(longlong *)(lVar1 + 0x40) == 0) goto LAB_7fff605394e7;
      FUN_7fff60506a30(*(longlong *)(lVar1 + 0x40),0);
      uStack_68 = FUN_7fff6051b190(lVar1,0);
      if (*(longlong *)(lVar1 + 0x40) == 0) goto LAB_7fff605394e7;
      uVar8 = FUN_7fff60506890(*(longlong *)(lVar1 + 0x40),0);
      if (0xe < bVar6) {
        if (*(longlong *)(lVar1 + 0x40) == 0) goto LAB_7fff605394e7;
        uVar4 = FUN_7fff60506580(*(longlong *)(lVar1 + 0x40),0);
        if (0xf < bVar6) {
          if (*(longlong *)(lVar1 + 0x40) == 0) goto LAB_7fff605394e7;
          cVar5 = FUN_7fff60506580(*(longlong *)(lVar1 + 0x40),0);
          bStackX_8 = cVar5 != '\0';
        }
      }
    }
    lVar10 = FUN_7fff60c4bc00(_DAT_7fff6245c360);
    if (lVar10 == 0) goto LAB_7fff605394e7;
    plVar12 = *(longlong **)(lVar10 + 0x28);
    if (plVar12 == (longlong *)0x0) {
LAB_7fff60538f3d:
      lVar10 = FUN_7fff60c4bc00(_DAT_7fff6245c360);
      if (lVar10 == 0) goto LAB_7fff605394e7;
      plVar12 = *(longlong **)(lVar10 + 0x28);
      uVar14 = 0;
      if (plVar12 != (longlong *)0x0) {
        if ((*(byte *)(_DAT_7fff62451190 + 0x130) <= *(byte *)(*plVar12 + 0x130)) &&
           (uVar14 = 0,
           *(longlong *)
            (*(longlong *)(*plVar12 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7fff62451190 + 0x130) * 8) == _DAT_7fff62451190)) {
          if ((int)plVar12[7] != iVar13) {
            func_0x7fff600d33e0(plVar12,0);
          }
          uVar14 = *(undefined4 *)((longlong)plVar12 + 0xa4);
        }
      }
    }
    else {
      if ((*(byte *)(*plVar12 + 0x130) < *(byte *)(_DAT_7fff62451318 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar12 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7fff62451318 + 0x130) * 8
           ) != _DAT_7fff62451318)) goto LAB_7fff60538f3d;
      if ((int)plVar12[7] != iVar13) {
        func_0x7fff600d4660(plVar12,0);
      }
      uVar14 = *(undefined4 *)((longlong)plVar12 + 0xac);
    }
    *(undefined2 *)(self + 0x2d) = 0;
    if (((uint)bVar3 == *(uint *)(lVar1 + 200)) && (iVar13 == *(int *)(lVar1 + 0xc4))) {
      plVar12 = (longlong *)FUN_7fff60c4bc00(_DAT_7fff6245d9b0);
      if (plVar12 == (longlong *)0x0) goto LAB_7fff605394e7;
      (**(code **)(*plVar12 + 0x278))(plVar12,0x7a,*(undefined8 *)(*plVar12 + 0x280));
      lVar10 = FUN_7fff60c4bc00(_DAT_7fff6245d9b0);
      if ((lVar10 == 0) || (lVar10 = FUN_7fff5fda8ae0(lVar10,0), lVar10 == 0))
      goto LAB_7fff605394e7;
      uVar11 = FUN_7fff606a6750(lVar10,_DAT_7fff6246e380);
      *(undefined8 *)(self + 0x30) = uVar11;
      thunk_FUN_7fff5f491fd0();
      if (*(longlong *)(self + 0x30) == 0) goto LAB_7fff605394e7;
      uStack_50 = uStackX_20;
      uStack_58 = CONCAT44(uVar16,uVar15);
      FUN_7fff5f603280(*(longlong *)(self + 0x30),iVar13,bVar3,&uStack_58,(float)(int)sStackX_18,
                       uStack_68,uVar8,uVar14,1,_DAT_7fff623f7f60,uVar4,
                       CONCAT71((int7)((ulonglong)in_stack_ffffffffffffff80 >> 8),
                                ~*(byte *)(lVar1 + 0xcc)) & 0xffffffffffffff01,
                       *(undefined8 *)(lVar1 + 0xd0),0);
      goto LAB_7fff605390cd;
    }
    plVar12 = (longlong *)FUN_7fff60c4bc00(_DAT_7fff6245d9b0);
    if (plVar12 == (longlong *)0x0) goto LAB_7fff605394e7;
    (**(code **)(*plVar12 + 0x278))(plVar12,0x40,*(undefined8 *)(*plVar12 + 0x280));
    lVar10 = FUN_7fff60c4bc00(_DAT_7fff6245d9b0);
    if ((lVar10 == 0) || (lVar10 = FUN_7fff5fda8ae0(lVar10,0), lVar10 == 0)) goto LAB_7fff605394e7;
    uVar11 = FUN_7fff606a6750(lVar10,_DAT_7fff6246e5e8);
    *(undefined8 *)(self + 0x38) = uVar11;
    thunk_FUN_7fff5f491fd0();
    if (*(longlong *)(self + 0x38) == 0) goto LAB_7fff605394e7;
    uStack_50 = uStackX_20;
    uStack_58 = CONCAT44(uVar16,uVar15);
    FUN_7fff5f78f670(*(longlong *)(self + 0x38),iVar13,bVar3,&uStack_58,(float)(int)sStackX_18,
                     uStack_68,uVar8,uVar14,1,_DAT_7fff623f7f60,uVar4,*(undefined8 *)(lVar1 + 0xd0),
                     bStackX_8,0);
LAB_7fff605392ff:
    uVar11 = *(undefined8 *)(self + 0x38);
    if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    cVar5 = FUN_7fff618ab2e0(uVar11,0,0);
    if (cVar5 != '\0') {
      lVar10 = *(longlong *)(self + 0x38);
      if (lVar10 == 0) goto LAB_7fff605394e7;
      if (*(char *)(lVar10 + 0x1d9) == '\0') {
        self[0x2d] = *(undefined1 *)(lVar10 + 0x1d8);
        self[0x2e] = *(undefined1 *)(lVar10 + 0x210);
        if (((lVar1 == 0) || (*(longlong *)(lVar1 + 0x20) == 0)) ||
           (plVar12 = (longlong *)FUN_7fff5ff8ac30(*(longlong *)(lVar1 + 0x20),0),
           plVar12 == (longlong *)0x0)) goto LAB_7fff605394e7;
        cVar5 = (**(code **)(*plVar12 + 0x248))(plVar12,*(undefined8 *)(*plVar12 + 0x250));
        if (cVar5 != '\0') {
          plVar12 = *(longlong **)(self + 0x38);
          if (plVar12 == (longlong *)0x0) goto LAB_7fff605394e7;
          (**(code **)(*plVar12 + 0x188))(plVar12,*(undefined8 *)(*plVar12 + 400));
        }
        if (self[0x2d] == '\0') {
          *(undefined8 *)(self + 0x18) = 0;
          thunk_FUN_7fff5f491fd0();
          *(undefined4 *)(self + 0x10) = 2;
          return 1;
        }
      }
    }
    *(undefined8 *)(self + 0x38) = 0;
  }
  else {
    if (iVar13 != 1) {
      if (iVar13 != 2) {
        return 0;
      }
      *(undefined4 *)(self + 0x10) = 0xffffffff;
      goto LAB_7fff605392ff;
    }
    *(undefined4 *)(self + 0x10) = 0xffffffff;
LAB_7fff605390cd:
    uVar11 = *(undefined8 *)(self + 0x30);
    if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    cVar5 = FUN_7fff618ab2e0(uVar11,0,0);
    if (cVar5 != '\0') {
      lVar10 = *(longlong *)(self + 0x30);
      if (lVar10 == 0) goto LAB_7fff605394e7;
      if (*(char *)(lVar10 + 0x1e9) == '\0') {
        cVar5 = *(char *)(lVar10 + 0x1e8);
        self[0x2d] = cVar5;
        self[0x2e] = *(undefined1 *)(lVar10 + 0x220);
        if (cVar5 == '\0') {
          if (((lVar1 != 0) && (*(longlong *)(lVar1 + 0x20) != 0)) &&
             (plVar12 = (longlong *)FUN_7fff5ff8ac30(*(longlong *)(lVar1 + 0x20),0),
             plVar12 != (longlong *)0x0)) {
            cVar5 = (**(code **)(*plVar12 + 0x248))(plVar12,*(undefined8 *)(*plVar12 + 0x250));
            if (cVar5 != '\0') {
              plVar12 = *(longlong **)(self + 0x30);
              if (plVar12 == (longlong *)0x0) goto LAB_7fff605394e7;
              (**(code **)(*plVar12 + 0x188))(plVar12,*(undefined8 *)(*plVar12 + 400));
            }
            *(undefined8 *)(self + 0x18) = 0;
            thunk_FUN_7fff5f491fd0();
            *(undefined4 *)(self + 0x10) = 1;
            return 1;
          }
          goto LAB_7fff605394e7;
        }
      }
    }
    *(undefined8 *)(self + 0x30) = 0;
  }
  thunk_FUN_7fff5f491fd0();
  if (lVar1 != 0) {
    *(undefined *)(lVar1 + 0xe2) = self[0x2c];
    FUN_7fff60523c70(lVar1,*(undefined4 *)(self + 0x28),0);
    if ((*(longlong *)(lVar1 + 0x20) != 0) &&
       (plVar12 = (longlong *)FUN_7fff5ff8ac30(*(longlong *)(lVar1 + 0x20),0),
       plVar12 != (longlong *)0x0)) {
      cVar5 = (**(code **)(*plVar12 + 0x248))(plVar12,*(undefined8 *)(*plVar12 + 0x250));
      if (cVar5 != '\0') {
        return 0;
      }
      plVar12 = (longlong *)FUN_7fff60c4bc00(_DAT_7fff6245d9b0);
      if (plVar12 != (longlong *)0x0) {
        (**(code **)(*plVar12 + 0x278))(plVar12,2,*(undefined8 *)(*plVar12 + 0x280));
        if (self[0x2d] == '\0') {
          plVar12 = (longlong *)FUN_7fff60c4bc00(_DAT_7fff6245d9b0);
          if (plVar12 != (longlong *)0x0) {
            (**(code **)(*plVar12 + 0x248))(plVar12,0,5,*(undefined8 *)(*plVar12 + 0x250));
            return 0;
          }
        }
        else {
          if (self[0x2e] == '\0') {
            return 0;
          }
          plVar12 = (longlong *)FUN_7fff60c4bc00(_DAT_7fff6245d9b0);
          if (plVar12 != (longlong *)0x0) {
            (**(code **)(*plVar12 + 0x278))(plVar12,0x5d,*(undefined8 *)(*plVar12 + 0x280));
            return 0;
          }
        }
      }
    }
  }
LAB_7fff605394e7:
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  bVar6 = (*pcVar2)();
  return bVar6;
}

