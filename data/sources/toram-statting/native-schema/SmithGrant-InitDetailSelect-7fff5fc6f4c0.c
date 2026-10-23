
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithGrant_InitDetailSelect(undefined *self,undefined *methodInfo)

{
  undefined8 *puVar1;
  longlong *plVar2;
  float fVar3;
  undefined4 uVar4;
  uint uVar5;
  uint uVar6;
  longlong lVar7;
  longlong lVar8;
  code *pcVar9;
  undefined8 uVar10;
  undefined8 uVar11;
  float fVar12;
  int iVar13;
  undefined *self_00;
  undefined8 uVar14;
  undefined8 uVar15;
  longlong lVar16;
  longlong *plVar17;
  longlong *plVar18;
  longlong lVar19;
  int iVar20;
  int iVar21;
  bool bVar22;
  uint unaff_XMM7_Da;
  undefined8 uStack_a8;
  undefined4 uStack_a0;
  undefined8 uStack_98;
  undefined4 uStack_90;
  undefined8 uStack_88;
  undefined8 uStack_80;
  undefined4 uStack_78;
  undefined8 uStack_70;
  uint uStack_48;
  undefined1 *puStack_40;
  undefined4 uStack_38;
  undefined4 uStack_30;
  
  if (DAT_7fff625e421e == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62450860);
    FUN_7fff5f47d450(&DAT_7fff623fc188);
    FUN_7fff5f47d450(&DAT_7fff6241d1f0);
    FUN_7fff5f47d450(&DAT_7fff6241d2c0);
    FUN_7fff5f47d450(&DAT_7fff6242a1a8);
    FUN_7fff5f47d450(&DAT_7fff6242ef00);
    FUN_7fff5f47d450(&DAT_7fff6242d3a8);
    FUN_7fff5f47d450(&DAT_7fff6242d600);
    FUN_7fff5f47d450(&DAT_7fff6243b0c8);
    FUN_7fff5f47d450(&DAT_7fff62443ed8);
    FUN_7fff5f47d450(&DAT_7fff6243a9e0);
    FUN_7fff5f47d450(&DAT_7fff6243b188);
    FUN_7fff5f47d450(&DAT_7fff6243aaa8);
    FUN_7fff5f47d450(&DAT_7fff6246bee0);
    FUN_7fff5f47d450(&DAT_7fff62420f50);
    FUN_7fff5f47d450(&DAT_7fff62424ed0);
    FUN_7fff5f47d450(0x7fff62425128);
    FUN_7fff5f47d450(0x7fff62434cb0);
    FUN_7fff5f47d450(&DAT_7fff62434d78);
    FUN_7fff5f47d450(&DAT_7fff62422c48);
    FUN_7fff5f47d450(&DAT_7fff62443180);
    FUN_7fff5f47d450(&DAT_7fff6240e4b0);
    FUN_7fff5f47d450(&DAT_7fff6245cb58);
    FUN_7fff5f47d450(&DAT_7fff62409dd8);
    FUN_7fff5f47d450(&DAT_7fff624163d0);
    FUN_7fff5f47d450(&DAT_7fff624164a0);
    FUN_7fff5f47d450(&DAT_7fff624167e0);
    FUN_7fff5f47d450(&DAT_7fff624168b0);
    FUN_7fff5f47d450(&DAT_7fff62416980);
    FUN_7fff5f47d450(&DAT_7fff62416a50);
    FUN_7fff5f47d450(&DAT_7fff6242a150);
    FUN_7fff5f47d450(&DAT_7fff6242a088);
    FUN_7fff5f47d450(&DAT_7fff623f6340);
    FUN_7fff5f47d450(&DAT_7fff623fda58);
    FUN_7fff5f47d450(&DAT_7fff623f61a0);
    FUN_7fff5f47d450(&DAT_7fff623f7f60);
    DAT_7fff625e421e = '\x01';
  }
  uStack_48 = unaff_XMM7_Da;
  self_00 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff6242a150);
  SmithGrantInfoWindow_Start(self_00,(undefined *)0x0);
  if (self_00 != (undefined *)0x0) {
    *(undefined **)(self_00 + 0x10) = self;
    thunk_FUN_7fff5f491fd0();
    if (*(longlong *)(self + 0x78) != 0) {
      func_0x7fff5fdcfc90(*(longlong *)(self + 0x78),0);
      lVar16 = *(longlong *)(self + 0x138);
      if (lVar16 != 0) {
        iVar21 = *(int *)(lVar16 + 0x18);
        *(int *)(lVar16 + 0x1c) = *(int *)(lVar16 + 0x1c) + 1;
        *(undefined4 *)(lVar16 + 0x18) = 0;
        if (0 < iVar21) {
          FUN_7fff61022d30(*(undefined8 *)(lVar16 + 0x10),0);
        }
        self_00[0x18] = 0;
        lVar16 = *(longlong *)(self + 0x128);
        if (lVar16 != 0) {
          if (*(uint *)(lVar16 + 0x18) < 3) {
LAB_7fff5fc70215:
            FUN_7fff5f47d650();
            pcVar9 = (code *)swi(3);
            (*pcVar9)();
            return;
          }
          if (*(int *)(lVar16 + 0x28) == 10) {
            if (*(int *)(_DAT_7fff62420f50 + 0xe0) == 0) {
              func_0x7fff5f47d6f0(_DAT_7fff62420f50);
            }
            uVar15 = *(undefined8 *)(*(longlong *)(_DAT_7fff62420f50 + 0xb8) + 8);
            uVar14 = func_0x7fff5f44ff00(_DAT_7fff6243b0c8);
            FUN_7fff60a1fc30(uVar14,self_00,_DAT_7fff624167e0);
            uVar15 = FUN_7fff6069dae0(uVar15,uVar14,_DAT_7fff6242d600);
            if (*(int *)(_DAT_7fff6242a088 + 0xe0) == 0) {
              func_0x7fff5f47d6f0(_DAT_7fff6242a088);
            }
            lVar16 = *(longlong *)(*(longlong *)(_DAT_7fff6242a088 + 0xb8) + 0x18);
            if (lVar16 == 0) {
              if (*(int *)(_DAT_7fff6242a088 + 0xe0) == 0) {
                func_0x7fff5f47d6f0(_DAT_7fff6242a088);
              }
              uVar14 = **(undefined8 **)(_DAT_7fff6242a088 + 0xb8);
              lVar16 = func_0x7fff5f44ff00(_DAT_7fff6243b188);
              FUN_7fff60a1e7b0(lVar16,uVar14,_DAT_7fff624163d0);
              *(longlong *)(*(longlong *)(_DAT_7fff6242a088 + 0xb8) + 0x18) = lVar16;
              thunk_FUN_7fff5f491fd0();
            }
            uVar15 = FUN_7fff606965b0(uVar15,lVar16,_DAT_7fff6241d2c0);
          }
          else {
            if (*(int *)(_DAT_7fff62420f50 + 0xe0) == 0) {
              func_0x7fff5f47d6f0(_DAT_7fff62420f50);
            }
            uVar15 = **(undefined8 **)(_DAT_7fff62420f50 + 0xb8);
            uVar14 = func_0x7fff5f44ff00(_DAT_7fff6243a9e0);
            FUN_7fff60a1fc30(uVar14,self_00,_DAT_7fff624168b0);
            uVar15 = FUN_7fff6069dae0(uVar15,uVar14,_DAT_7fff6242d3a8);
            if (*(int *)(_DAT_7fff6242a088 + 0xe0) == 0) {
              func_0x7fff5f47d6f0(_DAT_7fff6242a088);
            }
            lVar16 = *(longlong *)(*(longlong *)(_DAT_7fff6242a088 + 0xb8) + 0x20);
            if (lVar16 == 0) {
              if (*(int *)(_DAT_7fff6242a088 + 0xe0) == 0) {
                func_0x7fff5f47d6f0(_DAT_7fff6242a088);
              }
              uVar14 = **(undefined8 **)(_DAT_7fff6242a088 + 0xb8);
              lVar16 = func_0x7fff5f44ff00(_DAT_7fff6243aaa8);
              FUN_7fff60a1e7b0(lVar16,uVar14,_DAT_7fff624164a0);
              *(longlong *)(*(longlong *)(_DAT_7fff6242a088 + 0xb8) + 0x20) = lVar16;
              thunk_FUN_7fff5f491fd0();
            }
            uVar15 = FUN_7fff606965b0(uVar15,lVar16,_DAT_7fff6241d1f0);
            uVar15 = FUN_7fff6069ca90(uVar15,_DAT_7fff6242a1a8);
            puVar1 = (undefined8 *)(self + 0x130);
            *puVar1 = uVar15;
            thunk_FUN_7fff5f491fd0();
            uVar15 = *puVar1;
            uVar14 = func_0x7fff5f44ff00(_DAT_7fff62443ed8);
            FUN_7fff60a1f970(uVar14,self_00,_DAT_7fff62416980);
            uVar15 = FUN_7fff6069d430(uVar15,uVar14,_DAT_7fff6242ef00);
            uVar15 = FUN_7fff6069ca90(uVar15,_DAT_7fff6242a1a8);
            *puVar1 = uVar15;
            thunk_FUN_7fff5f491fd0();
            uVar15 = *puVar1;
            uVar14 = func_0x7fff5f44ff00(_DAT_7fff62443ed8);
            FUN_7fff60a1f970(uVar14,self_00,_DAT_7fff62416a50);
            uVar15 = FUN_7fff6069d430(uVar15,uVar14,_DAT_7fff6242ef00);
          }
          lVar16 = FUN_7fff6069ca90(uVar15,_DAT_7fff6242a1a8);
          plVar2 = (longlong *)(self + 0x130);
          *plVar2 = lVar16;
          thunk_FUN_7fff5f491fd0();
          uVar6 = _DAT_7fff61b52c00;
          fVar12 = _DAT_7fff61b52b4c;
          lVar16 = *plVar2;
          iVar21 = 0;
          if (lVar16 != 0) {
            while (iVar21 < *(int *)(lVar16 + 0x18)) {
              lVar16 = *(longlong *)(self + 0x128);
              if (lVar16 == 0) goto LAB_7fff5fc70221;
              if (*(uint *)(lVar16 + 0x18) < 3) goto LAB_7fff5fc70215;
              lVar19 = *(longlong *)(self + 0x88);
              lVar7 = *(longlong *)(self + 0x30);
              lVar8 = *plVar2;
              if (*(int *)(lVar16 + 0x28) == 10) {
                if (lVar8 == 0) {
LAB_7fff5fc70253:
                  FUN_7fff5f47d660();
                  pcVar9 = (code *)swi(3);
                  (*pcVar9)();
                  return;
                }
                uStack_78 = FUN_7fff60a94fa0(lVar8,iVar21,_DAT_7fff62434d78);
                uStack_88 = _DAT_7fff623fc188;
                uStack_80 = 0xffffffffffffffff;
                uVar15 = FUN_7fff6104ddb0(&uStack_88,0);
                uVar15 = FUN_7fff60e71970(_DAT_7fff623f6340,uVar15,0);
                if (lVar7 == 0) goto LAB_7fff5fc70253;
                plVar17 = (longlong *)FUN_7fff5f2550e0(_DAT_7fff62409dd8,lVar7,uVar15);
                plVar18 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
                if (plVar18 == (longlong *)0x0) goto LAB_7fff5fc70253;
                if ((_DAT_7fff623f7f60 != 0) &&
                   (lVar16 = func_0x7fff5f47c7e0(_DAT_7fff623f7f60,*(undefined8 *)(*plVar18 + 0x40))
                   , lVar16 == 0)) {
                  uVar15 = func_0x7fff5f47d0b0();
                  FUN_7fff5f47d620(uVar15,0);
                  pcVar9 = (code *)swi(3);
                  (*pcVar9)();
                  return;
                }
                if ((int)plVar18[3] == 0) {
                  FUN_7fff5f47d650();
                  pcVar9 = (code *)swi(3);
                  (*pcVar9)();
                  return;
                }
                plVar18[4] = _DAT_7fff623f7f60;
                thunk_FUN_7fff5f491fd0();
                if ((plVar17 == (longlong *)0x0) ||
                   (uVar15 = (**(code **)(*plVar17 + 0x1a8))
                                       (plVar17,plVar18,*(undefined8 *)(*plVar17 + 0x1b0)),
                   lVar19 == 0)) goto LAB_7fff5fc70253;
              }
              else {
                if (lVar8 == 0) {
LAB_7fff5fc7021b:
                  FUN_7fff5f47d660();
                  pcVar9 = (code *)swi(3);
                  (*pcVar9)();
                  return;
                }
                uStack_78 = FUN_7fff60a94fa0(lVar8,iVar21,_DAT_7fff62434d78);
                uStack_88 = _DAT_7fff62450860;
                uStack_80 = 0xffffffffffffffff;
                uVar15 = FUN_7fff6104ddb0(&uStack_88,0);
                uVar15 = FUN_7fff60e71970(_DAT_7fff623f61a0,uVar15,0);
                if (lVar7 == 0) goto LAB_7fff5fc7021b;
                plVar17 = (longlong *)FUN_7fff5f2550e0(_DAT_7fff62409dd8,lVar7,uVar15);
                plVar18 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,1);
                if (plVar18 == (longlong *)0x0) goto LAB_7fff5fc7021b;
                if ((_DAT_7fff623f7f60 != 0) &&
                   (lVar16 = func_0x7fff5f47c7e0(_DAT_7fff623f7f60,*(undefined8 *)(*plVar18 + 0x40))
                   , lVar16 == 0)) {
                  uVar15 = func_0x7fff5f47d0b0();
                  FUN_7fff5f47d620(uVar15,0);
                  pcVar9 = (code *)swi(3);
                  (*pcVar9)();
                  return;
                }
                if ((int)plVar18[3] == 0) {
                  FUN_7fff5f47d650();
                  pcVar9 = (code *)swi(3);
                  (*pcVar9)();
                  return;
                }
                plVar18[4] = _DAT_7fff623f7f60;
                thunk_FUN_7fff5f491fd0();
                if ((plVar17 == (longlong *)0x0) ||
                   (uVar15 = (**(code **)(*plVar17 + 0x1a8))
                                       (plVar17,plVar18,*(undefined8 *)(*plVar17 + 0x1b0)),
                   lVar19 == 0)) goto LAB_7fff5fc7021b;
              }
              FUN_7fff5ff0eed0(lVar19,uVar15,0);
              uVar15 = *(undefined8 *)(self + 0x80);
              if (DAT_7fff625e12c7 == '\0') {
                FUN_7fff5f47d450(&DAT_7fff62403718);
                DAT_7fff625e12c7 = '\x01';
              }
              uVar14 = **(undefined8 **)(_DAT_7fff62403718 + 0xb8);
              uVar4 = *(undefined4 *)(*(undefined8 **)(_DAT_7fff62403718 + 0xb8) + 1);
              if (DAT_7fff625e12cf == '\0') {
                FUN_7fff5f47d450(&DAT_7fff624318b0);
                DAT_7fff625e12cf = '\x01';
              }
              uVar10 = **(undefined8 **)(_DAT_7fff624318b0 + 0xb8);
              uVar11 = (*(undefined8 **)(_DAT_7fff624318b0 + 0xb8))[1];
              if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
                func_0x7fff5f47d6f0();
              }
              uStack_a8 = uVar14;
              uStack_a0 = uVar4;
              uStack_88 = uVar10;
              uStack_80 = uVar11;
              lVar16 = FUN_7fff606c5700(uVar15,&uStack_a8,&uStack_88);
              fVar3 = *(float *)(self + 0xa0);
              if ((lVar16 == 0) || (lVar19 = FUN_7fff618a4a10(lVar16,0), lVar19 == 0))
              goto LAB_7fff5fc70221;
              uStack_98 = CONCAT44((float)((uint)fVar3 ^ uVar6) * (float)iVar21 - fVar3 * fVar12,
                                   0x42c80000);
              uStack_90 = 0;
              FUN_7fff618c8e40(lVar19,&uStack_98,0);
              lVar19 = FUN_7fff606a6750(lVar16,_DAT_7fff6246bee0);
              if (lVar19 == 0) goto LAB_7fff5fc70221;
              *(undefined **)(lVar19 + 0x38) = self;
              *(int *)(lVar19 + 0x28) = iVar21;
              thunk_FUN_7fff5f491fd0();
              *(undefined4 *)(lVar19 + 0x2c) = 3;
              lVar7 = *(longlong *)(self + 0x120);
              if (lVar7 == 0) goto LAB_7fff5fc70221;
              uVar5 = *(uint *)(lVar7 + 0x18);
              lVar7 = *(longlong *)(lVar7 + 0x10);
              if ((lVar7 == 0) || ((int)*(uint *)(lVar7 + 0x18) <= (int)uVar5))
              goto LAB_7fff5fc70221;
              if (*(uint *)(lVar7 + 0x18) <= uVar5) goto LAB_7fff5fc70215;
              lVar7 = *(longlong *)(lVar7 + 0x20 + (longlong)(int)uVar5 * 8);
              if (lVar7 == 0) goto LAB_7fff5fc70221;
              if (*(char *)(lVar7 + 0x2c) == '\0') {
                bVar22 = true;
              }
              else {
                if (*plVar2 == 0) goto LAB_7fff5fc70221;
                iVar13 = FUN_7fff60a94fa0(*plVar2,iVar21,_DAT_7fff62434d78);
                lVar7 = *(longlong *)(self + 0x120);
                if (lVar7 == 0) goto LAB_7fff5fc70221;
                uVar5 = *(uint *)(lVar7 + 0x18);
                lVar7 = *(longlong *)(lVar7 + 0x10);
                if ((lVar7 == 0) || ((int)*(uint *)(lVar7 + 0x18) <= (int)uVar5))
                goto LAB_7fff5fc70221;
                if (*(uint *)(lVar7 + 0x18) <= uVar5) goto LAB_7fff5fc70215;
                lVar7 = *(longlong *)(lVar7 + 0x20 + (longlong)(int)uVar5 * 8);
                if (lVar7 == 0) goto LAB_7fff5fc70221;
                if ((*(char *)(lVar7 + 0x2c) == '\0') &&
                   (*(int *)(lVar7 + 0x30) + *(int *)(lVar7 + 0x28) == 0)) {
                  iVar20 = 0;
                }
                else {
                  iVar20 = *(int *)(lVar7 + 0x20);
                }
                bVar22 = iVar13 == iVar20;
              }
              FUN_7fff5fc84350(lVar19,bVar22,0);
              if (*(longlong *)(self + 0x78) == 0) goto LAB_7fff5fc70221;
              FUN_7fff5fdcf5e0(*(longlong *)(self + 0x78),lVar16,0);
              if (*(longlong *)(self + 0x138) == 0) goto LAB_7fff5fc70221;
              FUN_7fff5f253100(*(longlong *)(self + 0x138),lVar16,_DAT_7fff62424ed0);
              lVar16 = *plVar2;
              iVar21 = iVar21 + 1;
              if (lVar16 == 0) goto LAB_7fff5fc70221;
            }
            lVar16 = *(longlong *)(self + 0x78);
            if (DAT_7fff625e12ce == '\0') {
              FUN_7fff5f47d450(&DAT_7fff62403718);
              DAT_7fff625e12ce = '\x01';
            }
            uVar15 = *(undefined8 *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0xc);
            uVar4 = *(undefined4 *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0x14);
            if (DAT_7fff625e142c == '\0') {
              FUN_7fff5f47d450(&DAT_7fff62403718);
              DAT_7fff625e142c = '\x01';
            }
            if (*plVar2 != 0) {
              uStack_98 = *(undefined8 *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0x18);
              uStack_90 = *(undefined4 *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0x20);
              if (lVar16 != 0) {
                uStack_98 = uVar15;
                uStack_90 = uVar4;
                FUN_7fff5fdd0230(lVar16,&uStack_98);
                if (*(longlong *)(self + 0x78) != 0) {
                  FUN_7fff5fdcfec0(*(longlong *)(self + 0x78),_DAT_7fff623fda58);
                  lVar16 = *(longlong *)(self + 0x120);
                  if (lVar16 != 0) {
                    uVar6 = *(uint *)(lVar16 + 0x18);
                    lVar16 = *(longlong *)(lVar16 + 0x10);
                    if ((lVar16 != 0) && ((int)uVar6 < (int)*(uint *)(lVar16 + 0x18))) {
                      if (*(uint *)(lVar16 + 0x18) <= uVar6) goto LAB_7fff5fc70215;
                      lVar16 = *(longlong *)(lVar16 + 0x20 + (longlong)(int)uVar6 * 8);
                      if (lVar16 != 0) {
                        if (((*(char *)(lVar16 + 0x2c) == '\0') &&
                            (*(int *)(lVar16 + 0x30) + *(int *)(lVar16 + 0x28) == 0)) ||
                           (*(int *)(lVar16 + 0x20) == 0)) goto LAB_7fff5fc70195;
                        lVar16 = *plVar2;
                        bVar22 = false;
                        iVar21 = 0;
                        if (lVar16 != 0) goto LAB_7fff5fc70090;
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
  goto LAB_7fff5fc70221;
  while( true ) {
    iVar13 = FUN_7fff60a94fa0(*plVar2,iVar21,_DAT_7fff62434d78);
    lVar16 = *(longlong *)(self + 0x120);
    if (lVar16 == 0) break;
    uVar6 = *(uint *)(lVar16 + 0x18);
    lVar16 = *(longlong *)(lVar16 + 0x10);
    if ((lVar16 == 0) || ((int)*(uint *)(lVar16 + 0x18) <= (int)uVar6)) break;
    if (*(uint *)(lVar16 + 0x18) <= uVar6) goto LAB_7fff5fc70215;
    lVar16 = *(longlong *)(lVar16 + 0x20 + (longlong)(int)uVar6 * 8);
    if (lVar16 == 0) break;
    if ((*(char *)(lVar16 + 0x2c) == '\0') &&
       (*(int *)(lVar16 + 0x30) + *(int *)(lVar16 + 0x28) == 0)) {
      iVar20 = 0;
    }
    else {
      iVar20 = *(int *)(lVar16 + 0x20);
    }
    if (iVar13 == iVar20) {
      SmithGrant_SetSelected(self,3,iVar21,(undefined *)0x0);
      lVar16 = *(longlong *)(self + 0x120);
      if (lVar16 == 0) break;
      uVar6 = *(uint *)(lVar16 + 0x18);
      lVar16 = *(longlong *)(lVar16 + 0x10);
      if ((lVar16 == 0) || ((int)*(uint *)(lVar16 + 0x18) <= (int)uVar6)) break;
      if (*(uint *)(lVar16 + 0x18) <= uVar6) goto LAB_7fff5fc70215;
      lVar16 = *(longlong *)(lVar16 + 0x20 + (longlong)(int)uVar6 * 8);
      if ((lVar16 == 0) || (*(longlong *)(self + 0xb8) == 0)) break;
      FUN_7fff5fc85820(*(longlong *)(self + 0xb8),*(undefined4 *)(lVar16 + 0x28));
      bVar22 = true;
    }
    lVar16 = *plVar2;
    iVar21 = iVar21 + 1;
    if (lVar16 == 0) break;
LAB_7fff5fc70090:
    if (*(int *)(lVar16 + 0x18) <= iVar21) {
      if (!bVar22) {
LAB_7fff5fc70195:
        SmithGrant_SetSelected(self,3,0,(undefined *)0x0);
      }
      lVar16 = FUN_7fff60c4bc00(_DAT_7fff6245cb58);
      if (lVar16 != 0) {
        puStack_40 = &stack0xffffffffffffffe8;
        uStack_30 = _DAT_7fff61b52d1c;
        uStack_38 = 0;
        uStack_48 = uStack_48 & 0xffffff00;
        uStack_70 = 0x7fff5f54153b;
        FUN_7fff5f5412c0(lVar16,4,0);
        return;
      }
      break;
    }
    if (*plVar2 == 0) break;
  }
LAB_7fff5fc70221:
  FUN_7fff5f47d660();
  pcVar9 = (code *)swi(3);
  (*pcVar9)();
  return;
}

