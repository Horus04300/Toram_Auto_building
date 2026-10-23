
/* WARNING: Possible PIC construction at 0x7fff5fc98ddd: Changing call to branch */
/* WARNING: Possible PIC construction at 0x7fff5fc98e45: Changing call to branch */
/* WARNING: Possible PIC construction at 0x7fff5fc98e95: Changing call to branch */
/* WARNING: Possible PIC construction at 0x7fff5fc98ee7: Changing call to branch */
/* WARNING: Possible PIC construction at 0x7fff5fc98f39: Changing call to branch */
/* WARNING: Possible PIC construction at 0x7fff5fc98f88: Changing call to branch */
/* WARNING: Possible PIC construction at 0x7fff5fc98fda: Changing call to branch */
/* WARNING: Possible PIC construction at 0x7fff5fc9904a: Changing call to branch */
/* WARNING: Removing unreachable block (ram,0x7fff5fc98fdf) */
/* WARNING: Removing unreachable block (ram,0x7fff5fc99170) */
/* WARNING: Removing unreachable block (ram,0x7fff5fc98f8d) */
/* WARNING: Removing unreachable block (ram,0x7fff5fc99160) */
/* WARNING: Removing unreachable block (ram,0x7fff5fc98f3e) */
/* WARNING: Removing unreachable block (ram,0x7fff5fc99150) */
/* WARNING: Removing unreachable block (ram,0x7fff5fc98eec) */
/* WARNING: Removing unreachable block (ram,0x7fff5fc99140) */
/* WARNING: Removing unreachable block (ram,0x7fff5fc98e9a) */
/* WARNING: Removing unreachable block (ram,0x7fff5fc99130) */
/* WARNING: Removing unreachable block (ram,0x7fff5fc98e4a) */
/* WARNING: Removing unreachable block (ram,0x7fff5fc99120) */
/* WARNING: Removing unreachable block (ram,0x7fff5fc98de2) */
/* WARNING: Removing unreachable block (ram,0x7fff5fc99110) */
/* WARNING: Removing unreachable block (ram,0x7fff5fc9904f) */
/* WARNING: Removing unreachable block (ram,0x7fff5fc99180) */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined *
RecipeDBDataManager_getData
          (undefined *self,undefined *datas,int proficiency,byte isShop,byte isSmith,
          undefined *methodInfo)

{
  short sVar1;
  undefined8 *puVar2;
  code *pcVar3;
  float fVar4;
  float fVar5;
  char cVar6;
  int iVar7;
  longlong lVar8;
  longlong lVar9;
  longlong lVar10;
  undefined *puVar11;
  longlong *plVar12;
  longlong *plVar13;
  undefined1 uVar14;
  uint uVar15;
  longlong *unaff_RBX;
  ulonglong unaff_RSI;
  ulonglong uVar16;
  longlong *unaff_RDI;
  bool bVar17;
  float fVar18;
  undefined2 auStackX_18 [4];
  byte bStackX_20;
  undefined8 auStack_d0 [5];
  int iStack_a8;
  int iStack_a4;
  int iStack_a0;
  undefined4 uStack_9c;
  float fStack_98;
  int iStack_94;
  int iStack_90;
  int iStack_8c;
  undefined4 uStack_88;
  undefined4 auStack_84 [19];
  
  bStackX_20 = isShop;
  if (DAT_7fff625e42c2 == '\0') {
    auStack_d0[0] = 0x7fff5fc98aa9;
    FUN_7fff5f47d450(&DAT_7fff624485c8);
    auStack_d0[0] = 0x7fff5fc98ab5;
    FUN_7fff5f47d450(&DAT_7fff62453138);
    auStack_d0[0] = 0x7fff5fc98ac1;
    FUN_7fff5f47d450(&DAT_7fff624532c0);
    auStack_d0[0] = 0x7fff5fc98acd;
    FUN_7fff5f47d450(&DAT_7fff624509b8);
    auStack_d0[0] = 0x7fff5fc98ad9;
    FUN_7fff5f47d450(&DAT_7fff62450cc8);
    auStack_d0[0] = 0x7fff5fc98ae5;
    FUN_7fff5f47d450(&DAT_7fff624508f8);
    auStack_d0[0] = 0x7fff5fc98af1;
    FUN_7fff5f47d450(&DAT_7fff62478320);
    auStack_d0[0] = 0x7fff5fc98afd;
    FUN_7fff5f47d450(&DAT_7fff62422c48);
    auStack_d0[0] = 0x7fff5fc98b09;
    FUN_7fff5f47d450(&DAT_7fff62424348);
    auStack_d0[0] = 0x7fff5fc98b15;
    FUN_7fff5f47d450(&DAT_7fff62450b30);
    auStack_d0[0] = 0x7fff5fc98b21;
    FUN_7fff5f47d450(&DAT_7fff62459938);
    auStack_d0[0] = 0x7fff5fc98b2d;
    FUN_7fff5f47d450(&DAT_7fff62464120);
    auStack_d0[0] = 0x7fff5fc98b39;
    FUN_7fff5f47d450(&DAT_7fff62403ea0);
    auStack_d0[0] = 0x7fff5fc98b45;
    FUN_7fff5f47d450(&DAT_7fff623f7f60);
    DAT_7fff625e42c2 = '\x01';
  }
  sVar1 = (short)(proficiency >> 0x1f);
  iStack_a0 = (int)(short)(((short)(proficiency / 100) + sVar1) -
                          ((short)((short)(proficiency / 0x640000) + sVar1) >> 0xf));
  auStack_d0[0] = 0x7fff5fc98b9f;
  lVar9 = func_0x7fff5f44ff00(_DAT_7fff62478320);
  auStack_d0[0] = 0x7fff5fc98bb1;
  FUN_7fff60a943d0(lVar9);
  auStack_d0[0] = 0x7fff5fc98bbd;
  lVar10 = FUN_7fff60c4bc00(_DAT_7fff62459938);
  if (lVar10 != 0) {
    auStack_d0[0] = 0x7fff5fc98bd0;
    uStack_88 = FUN_7fff603e5dd0(lVar10);
    auStack_d0[0] = 0x7fff5fc98bde;
    puVar11 = RecipeDBDataManager_get_Status(self,(undefined *)0x0);
    if (puVar11 != (undefined *)0x0) {
      auStack_d0[0] = 0x7fff5fc98bf1;
      plVar12 = (longlong *)FUN_7fff5ff8ac30(puVar11,0);
      if (plVar12 != (longlong *)0x0) {
        auStack_d0[0] = 0x7fff5fc98c11;
        lVar10 = (**(code **)(*plVar12 + 0x198))(plVar12,*(undefined8 *)(*plVar12 + 0x1a0));
        if (lVar10 != 0) {
          auStack_d0[0] = 0x7fff5fc98c2e;
          iVar7 = FUN_7fff5f252ec0(9,_DAT_7fff624485c8,lVar10);
          auStack_d0[0] = 0x7fff5fc98c3e;
          iStack_a8 = iVar7;
          puVar11 = RecipeDBDataManager_get_Status(self,(undefined *)0x0);
          if (puVar11 != (undefined *)0x0) {
            auStack_d0[0] = 0x7fff5fc98c51;
            plVar12 = (longlong *)FUN_7fff5ff8ac30(puVar11,0);
            if (plVar12 != (longlong *)0x0) {
              auStack_d0[0] = 0x7fff5fc98c71;
              lVar10 = (**(code **)(*plVar12 + 0x198))(plVar12,*(undefined8 *)(*plVar12 + 0x1a0));
              if (lVar10 != 0) {
                auStack_d0[0] = 0x7fff5fc98c8e;
                iStack_a4 = FUN_7fff5f252ec0(5,_DAT_7fff624485c8,lVar10);
                fVar5 = _DAT_7fff61b52b78;
                fVar4 = _DAT_7fff61b52b4c;
                uVar16 = 0;
                if (datas != (undefined *)0x0) {
LAB_7fff5fc98cc0:
                  do {
                    uVar15 = (uint)uVar16;
                    if ((int)*(uint *)(datas + 0x18) <= (int)uVar15) goto LAB_7fff5fc99099;
                    if (*(uint *)(datas + 0x18) <= uVar15) {
                      auStack_d0[0] = 0x7fff5fc991a1;
                      FUN_7fff5f47d650();
                      pcVar3 = (code *)swi(3);
                      puVar11 = (undefined *)(*pcVar3)();
                      return puVar11;
                    }
                    lVar10 = (longlong)(int)uVar15;
                    puVar11 = *(undefined **)(datas + lVar10 * 8 + 0x20);
                    if (puVar11 == (undefined *)0x0) break;
                    sVar1 = *(short *)(puVar11 + 0x16);
                    fVar18 = ((float)iVar7 * fVar4 + (float)iStack_a0 +
                             (float)(int)((float)iStack_a4 / fVar5)) -
                             (float)(int)*(short *)(puVar11 + 0x1c);
                    if (isShop == 0) {
                      bVar17 = *(short *)(puVar11 + 0x1c) == 0;
LAB_7fff5fc98d41:
                      if (!bVar17) {
                        auStack_d0[0] = 0x7fff5fc98d4a;
                        puVar11 = RecipeDBData_Clone(puVar11,(undefined *)0x0);
                        if ((0.0 <= fVar18) || (isShop != 0)) {
                          if (puVar11 == (undefined *)0x0) break;
                          uVar14 = 1;
                        }
                        else {
                          if (puVar11 == (undefined *)0x0) break;
                          uVar14 = 0;
                        }
                        puVar11[0x27] = uVar14;
                        if (lVar9 == 0) break;
                        auStack_d0[0] = 0x7fff5fc98d8a;
                        FUN_7fff5f253100(lVar9,puVar11,_DAT_7fff624509b8);
                        uVar16 = (ulonglong)(uVar15 + 1);
                        goto LAB_7fff5fc98cc0;
                      }
                    }
                    else if (sVar1 != 0) {
                      bVar17 = *(int *)(puVar11 + 0x18) == 0;
                      goto LAB_7fff5fc98d41;
                    }
                    auStack_d0[0] = 0x7fff5fc98da8;
                    plVar13 = (longlong *)func_0x7fff5f47c850(_DAT_7fff62422c48,8);
                    puVar11 = _DAT_7fff62403ea0;
                    plVar12 = _DAT_7fff62464120;
                    if (isShop == 0) {
                      plVar12 = _DAT_7fff623f7f60;
                    }
                    if (plVar13 == (longlong *)0x0) {
LAB_7fff5fc99196:
                      auStack_d0[0] = 0x7fff5fc9919b;
                      FUN_7fff5f47d660();
                      pcVar3 = (code *)swi(3);
                      puVar11 = (undefined *)(*pcVar3)();
                      return puVar11;
                    }
                    if (plVar12 != (longlong *)0x0) {
                      register0x00000020 = (BADSPACEBASE *)auStack_d0;
                      auStack_d0[0] = 0x7fff5fc98de2;
                      lVar9 = *(longlong *)(*plVar13 + 0x40);
                      unaff_RBX = plVar13;
                      unaff_RSI = uVar16;
                      unaff_RDI = plVar12;
                      goto FUN_7fff5f44eb30;
                    }
                    if ((int)plVar13[3] == 0) {
LAB_7fff5fc99190:
                      auStack_d0[0] = 0x7fff5fc99195;
                      FUN_7fff5f47d650();
                      pcVar3 = (code *)swi(3);
                      puVar11 = (undefined *)(*pcVar3)();
                      return puVar11;
                    }
                    plVar13[4] = 0;
                    auStack_d0[0] = 0x7fff5fc98e04;
                    thunk_FUN_7fff5f491fd0();
                    if (*(uint *)(datas + 0x18) <= uVar15) goto LAB_7fff5fc99190;
                    if (*(longlong *)(datas + lVar10 * 8 + 0x20) == 0) goto LAB_7fff5fc99196;
                    uStack_9c = *(undefined4 *)(*(longlong *)(datas + lVar10 * 8 + 0x20) + 0x20);
                    auStack_d0[0] = 0x7fff5fc98e33;
                    plVar12 = (longlong *)func_0x7fff5f47c7a0(_DAT_7fff624532c0,&uStack_9c);
                    if (plVar12 != (longlong *)0x0) {
                      register0x00000020 = (BADSPACEBASE *)auStack_d0;
                      auStack_d0[0] = 0x7fff5fc98e4a;
                      lVar9 = *(longlong *)(*plVar13 + 0x40);
                      unaff_RBX = plVar13;
                      unaff_RSI = uVar16;
                      unaff_RDI = plVar12;
                      goto FUN_7fff5f44eb30;
                    }
                    if (*(uint *)(plVar13 + 3) < 2) goto LAB_7fff5fc99190;
                    plVar13[5] = 0;
                    auStack_d0[0] = 0x7fff5fc98e6c;
                    thunk_FUN_7fff5f491fd0();
                    auStack_d0[0] = 0x7fff5fc98e83;
                    fStack_98 = fVar18;
                    plVar12 = (longlong *)func_0x7fff5f47c7a0(_DAT_7fff62450b30,&fStack_98);
                    if (plVar12 != (longlong *)0x0) {
                      register0x00000020 = (BADSPACEBASE *)auStack_d0;
                      auStack_d0[0] = 0x7fff5fc98e9a;
                      lVar9 = *(longlong *)(*plVar13 + 0x40);
                      unaff_RBX = plVar13;
                      unaff_RSI = uVar16;
                      unaff_RDI = plVar12;
                      goto FUN_7fff5f44eb30;
                    }
                    if (*(uint *)(plVar13 + 3) < 3) goto LAB_7fff5fc99190;
                    plVar13[6] = 0;
                    auStack_d0[0] = 0x7fff5fc98ebc;
                    thunk_FUN_7fff5f491fd0();
                    iStack_94 = iStack_a8;
                    auStack_d0[0] = 0x7fff5fc98ed5;
                    plVar12 = (longlong *)func_0x7fff5f47c7a0(_DAT_7fff624532c0,&iStack_94);
                    if (plVar12 != (longlong *)0x0) {
                      register0x00000020 = (BADSPACEBASE *)auStack_d0;
                      auStack_d0[0] = 0x7fff5fc98eec;
                      lVar9 = *(longlong *)(*plVar13 + 0x40);
                      unaff_RBX = plVar13;
                      unaff_RSI = uVar16;
                      unaff_RDI = plVar12;
                      goto FUN_7fff5f44eb30;
                    }
                    if (*(uint *)(plVar13 + 3) < 4) goto LAB_7fff5fc99190;
                    plVar13[7] = 0;
                    auStack_d0[0] = 0x7fff5fc98f0e;
                    thunk_FUN_7fff5f491fd0();
                    iStack_90 = iStack_a4;
                    auStack_d0[0] = 0x7fff5fc98f27;
                    plVar12 = (longlong *)func_0x7fff5f47c7a0(_DAT_7fff624532c0,&iStack_90);
                    if (plVar12 != (longlong *)0x0) {
                      register0x00000020 = (BADSPACEBASE *)auStack_d0;
                      auStack_d0[0] = 0x7fff5fc98f3e;
                      lVar9 = *(longlong *)(*plVar13 + 0x40);
                      unaff_RBX = plVar13;
                      unaff_RSI = uVar16;
                      unaff_RDI = plVar12;
                      goto FUN_7fff5f44eb30;
                    }
                    if (*(uint *)(plVar13 + 3) < 5) goto LAB_7fff5fc99190;
                    plVar13[8] = 0;
                    auStack_d0[0] = 0x7fff5fc98f60;
                    thunk_FUN_7fff5f491fd0();
                    auStack_d0[0] = 0x7fff5fc98f76;
                    iStack_8c = (int)sVar1;
                    plVar12 = (longlong *)func_0x7fff5f47c7a0(_DAT_7fff624532c0,&iStack_8c);
                    if (plVar12 != (longlong *)0x0) {
                      register0x00000020 = (BADSPACEBASE *)auStack_d0;
                      auStack_d0[0] = 0x7fff5fc98f8d;
                      lVar9 = *(longlong *)(*plVar13 + 0x40);
                      unaff_RBX = plVar13;
                      unaff_RSI = uVar16;
                      unaff_RDI = plVar12;
                      goto FUN_7fff5f44eb30;
                    }
                    if (*(uint *)(plVar13 + 3) < 6) goto LAB_7fff5fc99190;
                    plVar13[9] = 0;
                    auStack_d0[0] = 0x7fff5fc98faf;
                    thunk_FUN_7fff5f491fd0();
                    auStack_84[0] = uStack_88;
                    auStack_d0[0] = 0x7fff5fc98fc8;
                    plVar12 = (longlong *)func_0x7fff5f47c7a0(_DAT_7fff624532c0,auStack_84);
                    if (plVar12 != (longlong *)0x0) {
                      register0x00000020 = (BADSPACEBASE *)auStack_d0;
                      auStack_d0[0] = 0x7fff5fc98fdf;
                      lVar9 = *(longlong *)(*plVar13 + 0x40);
                      unaff_RBX = plVar13;
                      unaff_RSI = uVar16;
                      unaff_RDI = plVar12;
                      goto FUN_7fff5f44eb30;
                    }
                    if (*(uint *)(plVar13 + 3) < 7) goto LAB_7fff5fc99190;
                    plVar13[10] = 0;
                    auStack_d0[0] = 0x7fff5fc99001;
                    thunk_FUN_7fff5f491fd0();
                    if (*(uint *)(datas + 0x18) <= uVar15) goto LAB_7fff5fc99190;
                    if (*(longlong *)(datas + lVar10 * 8 + 0x20) == 0) goto LAB_7fff5fc99196;
                    auStackX_18[0] =
                         *(undefined2 *)(*(longlong *)(datas + lVar10 * 8 + 0x20) + 0x1c);
                    auStack_d0[0] = 0x7fff5fc99038;
                    plVar12 = (longlong *)func_0x7fff5f47c7a0(_DAT_7fff62453138,auStackX_18);
                    if (plVar12 != (longlong *)0x0) {
                      register0x00000020 = (BADSPACEBASE *)auStack_d0;
                      auStack_d0[0] = 0x7fff5fc9904f;
                      lVar9 = *(longlong *)(*plVar13 + 0x40);
                      unaff_RBX = plVar13;
                      unaff_RSI = uVar16;
                      unaff_RDI = plVar12;
                      goto FUN_7fff5f44eb30;
                    }
                    if (*(uint *)(plVar13 + 3) < 8) goto LAB_7fff5fc99190;
                    plVar13[0xb] = 0;
                    auStack_d0[0] = 0x7fff5fc99071;
                    thunk_FUN_7fff5f491fd0();
                    auStack_d0[0] = 0x7fff5fc9907f;
                    SmithManufacture_Update(puVar11,(undefined *)plVar13);
                    uVar16 = (ulonglong)(uVar15 + 1);
                    isShop = bStackX_20;
                    iVar7 = iStack_a8;
                  } while( true );
                }
              }
            }
          }
        }
      }
    }
  }
LAB_7fff5fc9910a:
  auStack_d0[0] = 0x7fff5fc9910f;
  FUN_7fff5f47d660();
  pcVar3 = (code *)swi(3);
  puVar11 = (undefined *)(*pcVar3)();
  return puVar11;
LAB_7fff5fc99099:
  if (lVar9 != 0) {
    auStack_d0[0] = 0x7fff5fc990ad;
    lVar9 = FUN_7fff60a940e0(lVar9,_DAT_7fff62450cc8);
    if (lVar9 != 0) {
      auStack_d0[0] = 0x7fff5fc990bc;
      plVar12 = (longlong *)func_0x7fff60f8fd60(lVar9,0);
      lVar9 = _DAT_7fff62424348;
FUN_7fff5f44eb30:
      *(longlong **)((longlong)register0x00000020 + 0x10) = unaff_RBX;
      *(ulonglong *)((longlong)register0x00000020 + 0x18) = unaff_RSI;
      *(longlong **)((longlong)register0x00000020 + -8) = unaff_RDI;
      if (plVar12 != (longlong *)0x0) {
        lVar10 = *plVar12;
        *(undefined8 *)((longlong)register0x00000020 + -0x30) = 0x7fff5f44eb5c;
        cVar6 = FUN_7fff5f431250(lVar9,lVar10);
        if (cVar6 != '\0') {
          return (undefined *)plVar12;
        }
        if ((*(byte *)(lVar10 + 0x136) & 0x10) != 0) {
          if (((((*(byte *)(lVar9 + 0x118) & 0x20) != 0) || (*(char *)(lVar9 + 0x2a) == '\x13')) ||
              (*(char *)(lVar9 + 0x2a) == '\x1e')) &&
             ((*(longlong *)(lVar9 + 0x70) != 0 &&
              (lVar10 = *(longlong *)(*(longlong *)(lVar9 + 0x70) + 0x28), lVar10 != 0)))) {
            *(undefined8 *)((longlong)register0x00000020 + -0x30) = 0x7fff5f44eba3;
            lVar8 = FUN_7fff5f45ebe0(plVar12,lVar10);
            *(longlong *)((longlong)register0x00000020 + 8) = lVar8;
            if (lVar8 != 0) {
              return (undefined *)plVar12;
            }
            puVar2 = (undefined8 *)plVar12[2];
            pcVar3 = *(code **)*puVar2;
            *(undefined8 *)((longlong)register0x00000020 + -0x30) = 0x7fff5f44ebbe;
            iVar7 = (*pcVar3)(puVar2,lVar10,(undefined1 *)((longlong)register0x00000020 + 8));
            if (-1 < iVar7) {
              *(undefined8 *)((longlong)register0x00000020 + -0x30) = 0x7fff5f44ebd2;
              cVar6 = FUN_7fff5f45ab90(plVar12,lVar10,
                                       *(undefined8 *)((longlong)register0x00000020 + 8));
              if (cVar6 == '\0') {
                pcVar3 = *(code **)(**(longlong **)((longlong)register0x00000020 + 8) + 0x10);
                *(undefined8 *)((longlong)register0x00000020 + -0x30) = 0x7fff5f44ebe1;
                (*pcVar3)();
                *(undefined8 *)((longlong)register0x00000020 + -0x30) = 0x7fff5f44ebec;
                lVar10 = FUN_7fff5f45ebe0(plVar12,lVar10);
              }
              else {
                lVar10 = *(longlong *)((longlong)register0x00000020 + 8);
              }
              if (lVar10 != 0) {
                return (undefined *)plVar12;
              }
            }
          }
          plVar13 = (longlong *)0x0;
          if (lVar9 == _DAT_7fff625f4150) {
            plVar13 = plVar12;
          }
          return (undefined *)plVar13;
        }
      }
      return (undefined *)0x0;
    }
  }
  goto LAB_7fff5fc9910a;
}

