
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SmithGrant_SetSelected(undefined *self,int step,int index,undefined *methodInfo)

{
  uint uVar1;
  int itemId;
  ulonglong uVar2;
  undefined *name;
  code *pcVar3;
  char cVar4;
  undefined2 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  int grantnum;
  longlong lVar9;
  undefined *puVar10;
  undefined8 uVar11;
  longlong lVar12;
  int iVar13;
  int potential;
  longlong *plVar14;
  undefined8 uVar15;
  byte buttonEnabled;
  ulonglong uStack_58;
  undefined4 uStack_50;
  
  if (DAT_7fff625e4220 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62436790);
    FUN_7fff5f47d450(&DAT_7fff62462c40);
    FUN_7fff5f47d450(&DAT_7fff6244ce08);
    FUN_7fff5f47d450(&DAT_7fff6246bee0);
    FUN_7fff5f47d450(&DAT_7fff62420f50);
    FUN_7fff5f47d450(&DAT_7fff624335c0);
    FUN_7fff5f47d450(&DAT_7fff62433810);
    FUN_7fff5f47d450(&DAT_7fff62433438);
    FUN_7fff5f47d450(0x7fff62425768);
    FUN_7fff5f47d450(0x7fff62401320);
    FUN_7fff5f47d450(0x7fff62434cb0);
    FUN_7fff5f47d450(&DAT_7fff624013f0);
    FUN_7fff5f47d450(&DAT_7fff62434d78);
    FUN_7fff5f47d450(&DAT_7fff62425830);
    FUN_7fff5f47d450(&DAT_7fff62472b10);
    FUN_7fff5f47d450(0x7fff62447340);
    FUN_7fff5f47d450(0x7fff62447400);
    FUN_7fff5f47d450(&DAT_7fff62473110);
    FUN_7fff5f47d450(&DAT_7fff62473370);
    DAT_7fff625e4220 = '\x01';
  }
  lVar9 = *(longlong *)(self + 0x128);
  if (lVar9 == 0) goto LAB_7fff5fc74924;
  if (*(uint *)(lVar9 + 0x18) <= (uint)step) {
LAB_7fff5fc7491e:
    FUN_7fff5f47d650();
    pcVar3 = (code *)swi(3);
    (*pcVar3)();
    return;
  }
  *(int *)(lVar9 + 0x20 + (longlong)step * 4) = index;
  if (step == 0) {
    SmithGrant_SetEquipEnhance(self,(undefined *)0x0);
    if (*(longlong *)(self + 0x70) == 0) goto LAB_7fff5fc74924;
    potential = 0;
    iVar13 = 0;
    if (*(int *)(*(longlong *)(self + 0x70) + 0x18) < 1) {
      if (*(longlong *)(self + 0xb8) == 0) goto LAB_7fff5fc74924;
      FUN_7fff5fc86880(*(longlong *)(self + 0xb8),0);
    }
    else {
      if (*(longlong *)(self + 0x140) == 0) goto LAB_7fff5fc74924;
      lVar9 = FUN_7fff5ff8a8a0(*(longlong *)(self + 0x140),0);
      if (((*(longlong *)(self + 0x70) == 0) ||
          (lVar12 = FUN_7fff60a94f50(*(longlong *)(self + 0x70),index,_DAT_7fff624013f0),
          lVar12 == 0)) || (lVar9 == 0)) goto LAB_7fff5fc74924;
      lVar9 = FUN_7fff6007b880(lVar9,*(undefined4 *)(lVar12 + 0x18),0);
      *(longlong *)(self + 0x148) = lVar9;
      thunk_FUN_7fff5f491fd0();
      buttonEnabled = 1;
      lVar12 = func_0x7fff5f44ff00(_DAT_7fff62472b10);
      FUN_7fff60a943d0(lVar12,_DAT_7fff62433438);
      if ((lVar9 == 0) || (uVar5 = FUN_7fff5fd06df0(lVar9,0), lVar12 == 0)) goto LAB_7fff5fc74924;
      FUN_7fff5f254790(lVar12,uVar5,_DAT_7fff624335c0);
      uVar5 = FUN_7fff5fd06e20(lVar9,0);
      FUN_7fff5f254790(lVar12,uVar5,_DAT_7fff624335c0);
      uVar5 = FUN_7fff5fd06e50(lVar9,0);
      FUN_7fff5f254790(lVar12,uVar5,_DAT_7fff624335c0);
      uVar5 = FUN_7fff5fd06e80(lVar9,0);
      FUN_7fff5f254790(lVar12,uVar5,_DAT_7fff624335c0);
      uVar5 = FUN_7fff5fd06eb0(lVar9,0);
      FUN_7fff5f254790(lVar12,uVar5,_DAT_7fff624335c0);
      uVar5 = FUN_7fff5fd06ee0(lVar9,0);
      FUN_7fff5f254790(lVar12,uVar5,_DAT_7fff624335c0);
      uVar5 = FUN_7fff5fd06f10(lVar9,0);
      FUN_7fff5f254790(lVar12,uVar5,_DAT_7fff624335c0);
      uVar5 = FUN_7fff5fd06f40(lVar9,0);
      FUN_7fff5f254790(lVar12,uVar5,_DAT_7fff624335c0);
      uVar5 = FUN_7fff5fd06f70(lVar9,0);
      FUN_7fff5f254790(lVar12,uVar5,_DAT_7fff624335c0);
      uVar5 = FUN_7fff5fd06dc0(lVar9,0);
      FUN_7fff5f254790(lVar12,uVar5,_DAT_7fff624335c0);
      cVar4 = FUN_7fff60ad2a50(lVar12,0xb,_DAT_7fff62433810);
      if ((cVar4 == '\0') && (cVar4 = FUN_7fff60ad2a50(lVar12,0xe,_DAT_7fff62433810), cVar4 == '\0')
         ) {
        potential = (int)*(short *)(lVar9 + 0x50);
      }
      else {
        buttonEnabled = 0;
      }
      puVar10 = *(undefined **)(self + 0xb8);
      itemId = *(int *)(lVar9 + 0x34);
      if ((*(longlong *)(self + 0x70) == 0) ||
         (lVar9 = FUN_7fff60a94f50(*(longlong *)(self + 0x70),index,_DAT_7fff624013f0), lVar9 == 0))
      goto LAB_7fff5fc74924;
      name = *(undefined **)(lVar9 + 0x10);
      grantnum = FUN_7fff5fc75100(self,0);
      if (puVar10 == (undefined *)0x0) goto LAB_7fff5fc74924;
      SmithGrantInfoWindow_SetWeaponData
                (puVar10,itemId,name,potential,grantnum,buttonEnabled,(undefined *)0x0);
    }
    lVar9 = *(longlong *)(self + 0x138);
    while (lVar9 != 0) {
      if (*(int *)(lVar9 + 0x18) <= iVar13) {
        return;
      }
      if (((*(longlong *)(self + 0x138) == 0) ||
          (lVar9 = FUN_7fff60a94f50(*(longlong *)(self + 0x138),iVar13,_DAT_7fff62425830),
          lVar9 == 0)) || (lVar9 = FUN_7fff606a6750(lVar9,_DAT_7fff6246bee0), lVar9 == 0)) break;
      FUN_7fff5fc845e0(lVar9,index == iVar13,0);
      iVar13 = iVar13 + 1;
      lVar9 = *(longlong *)(self + 0x138);
    }
    goto LAB_7fff5fc74924;
  }
  if (step == 1) {
    if (*(longlong *)(self + 0x120) == 0) goto LAB_7fff5fc74924;
    if (index < 10) {
      *(int *)(*(longlong *)(self + 0x120) + 0x18) = index;
    }
    lVar9 = *(longlong *)(self + 0x120);
    if (lVar9 == 0) goto LAB_7fff5fc74924;
    uVar1 = *(uint *)(lVar9 + 0x18);
    lVar9 = *(longlong *)(lVar9 + 0x10);
    if ((lVar9 == 0) || ((int)*(uint *)(lVar9 + 0x18) <= (int)uVar1)) goto LAB_7fff5fc74924;
    if (*(uint *)(lVar9 + 0x18) <= uVar1) goto LAB_7fff5fc7491e;
    lVar9 = *(longlong *)(lVar9 + 0x20 + (longlong)(int)uVar1 * 8);
    if ((lVar9 == 0) || (*(longlong *)(self + 0xb8) == 0)) goto LAB_7fff5fc74924;
    func_0x7fff5fc859a0(*(longlong *)(self + 0xb8),*(undefined4 *)(lVar9 + 0x30),0);
    SmithGrant_InitMaterialTypeSelect(self,(undefined *)0x0);
    plVar14 = *(longlong **)(self + 0x28);
    uVar11 = func_0x7fff5f44ff00(_DAT_7fff62436790);
    uVar15 = _DAT_7fff62473370;
  }
  else {
    if (step != 2) {
      if (step != 3) {
        return;
      }
      lVar9 = *(longlong *)(self + 0x138);
      uVar8 = 0;
      iVar13 = 0;
      if (lVar9 != 0) {
        while (iVar13 < *(int *)(lVar9 + 0x18)) {
          if (((*(longlong *)(self + 0x138) == 0) ||
              (lVar9 = FUN_7fff60a94f50(*(longlong *)(self + 0x138),iVar13), lVar9 == 0)) ||
             (lVar9 = FUN_7fff606a6750(lVar9,_DAT_7fff6246bee0), lVar9 == 0)) goto LAB_7fff5fc74924;
          FUN_7fff5fc845e0(lVar9,index == iVar13);
          lVar9 = *(longlong *)(self + 0x138);
          iVar13 = iVar13 + 1;
          if (lVar9 == 0) goto LAB_7fff5fc74924;
        }
        lVar9 = *(longlong *)(self + 0x128);
        if (lVar9 != 0) {
          if (*(uint *)(lVar9 + 0x18) < 3) goto LAB_7fff5fc7491e;
          if (*(int *)(lVar9 + 0x28) != 10) {
            lVar12 = *(longlong *)(self + 0x130);
            if (lVar12 == 0) goto LAB_7fff5fc74924;
            if (*(int *)(lVar12 + 0x18) < 1) {
              if (*(longlong *)(self + 0x108) != 0) {
                FUN_7fff618a4510(*(longlong *)(self + 0x108),1,0);
                return;
              }
              goto LAB_7fff5fc74924;
            }
            uVar6 = FUN_7fff60a94fa0(lVar12,index,_DAT_7fff62434d78);
            if (*(uint *)(lVar9 + 0x18) < 4) goto LAB_7fff5fc7491e;
            *(undefined4 *)(lVar9 + 0x2c) = uVar6;
          }
          puVar10 = *(undefined **)(self + 0xb8);
          if (*(longlong *)(self + 0x130) != 0) {
            iVar13 = FUN_7fff60a94fa0(*(longlong *)(self + 0x130),index,_DAT_7fff62434d78);
            lVar9 = *(longlong *)(self + 0x128);
            if (lVar9 != 0) {
              if (*(uint *)(lVar9 + 0x18) < 3) goto LAB_7fff5fc7491e;
              if (puVar10 != (undefined *)0x0) {
                puVar10 = SmithGrantInfoWindow_SetDetailType
                                    (puVar10,iVar13,*(int *)(lVar9 + 0x28) == 10,(undefined *)0x0);
                FUN_7fff618a87c0(self,puVar10,0);
                if (*(longlong *)(self + 0x130) != 0) {
                  uVar6 = FUN_7fff60a94fa0(*(longlong *)(self + 0x130),index,_DAT_7fff62434d78);
                  lVar9 = *(longlong *)(self + 0x128);
                  if (lVar9 != 0) {
                    if (*(int *)(lVar9 + 0x18) == 0) goto LAB_7fff5fc7491e;
                    if ((*(longlong *)(self + 0x70) != 0) &&
                       (lVar9 = FUN_7fff60a94f50(*(longlong *)(self + 0x70),
                                                 *(undefined4 *)(lVar9 + 0x20),_DAT_7fff624013f0),
                       lVar9 != 0)) {
                      uVar7 = *(undefined4 *)(lVar9 + 0x18);
                      uVar15 = *(undefined8 *)(self + 0x140);
                      if (*(int *)(_DAT_7fff62420f50 + 0xe0) == 0) {
                        func_0x7fff5f47d6f0();
                      }
                      uVar6 = FUN_7fff5fc80ba0(uVar6,uVar7,uVar15,0);
                      if (*(longlong *)(self + 0x130) != 0) {
                        uVar7 = FUN_7fff60a94fa0(*(longlong *)(self + 0x130),index,_DAT_7fff62434d78
                                                );
                        if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) != 0) {
                          FUN_7fff6088c670(&uStack_58,**(longlong **)(_DAT_7fff62420f50 + 0xb8),
                                           uVar7,_DAT_7fff6244ce08);
                          uVar2 = uStack_58;
                          if (**(longlong **)(_DAT_7fff62420f50 + 0xb8) != 0) {
                            FUN_7fff6088c670(&uStack_58,**(longlong **)(_DAT_7fff62420f50 + 0xb8),
                                             uVar7,_DAT_7fff6244ce08);
                            lVar9 = *(longlong *)(self + 0x128);
                            if (lVar9 != 0) {
                              if (*(uint *)(lVar9 + 0x18) < 3) goto LAB_7fff5fc7491e;
                              if (*(int *)(lVar9 + 0x28) == 10) {
                                if (*(int *)(_DAT_7fff62420f50 + 0xe0) == 0) {
                                  func_0x7fff5f47d6f0(_DAT_7fff62420f50);
                                }
                                lVar9 = *(longlong *)(*(longlong *)(_DAT_7fff62420f50 + 0xb8) + 8);
                                if (lVar9 == 0) goto LAB_7fff5fc74924;
                                FUN_7fff6088c670(&uStack_58,lVar9,uVar7,_DAT_7fff62462c40);
                                lVar9 = *(longlong *)(*(longlong *)(_DAT_7fff62420f50 + 0xb8) + 8);
                                if (lVar9 == 0) goto LAB_7fff5fc74924;
                                FUN_7fff6088c670(&uStack_58,lVar9,uVar7,_DAT_7fff62462c40);
                                if (*(longlong *)(self + 0x130) == 0) goto LAB_7fff5fc74924;
                                uVar6 = FUN_7fff60a94fa0(*(longlong *)(self + 0x130),index,
                                                         _DAT_7fff62434d78);
                                lVar9 = *(longlong *)(self + 0x128);
                                if (lVar9 == 0) goto LAB_7fff5fc74924;
                                if (*(int *)(lVar9 + 0x18) == 0) goto LAB_7fff5fc7491e;
                                if ((*(longlong *)(self + 0x70) == 0) ||
                                   (lVar9 = FUN_7fff60a94f50(*(longlong *)(self + 0x70),
                                                             *(undefined4 *)(lVar9 + 0x20),
                                                             _DAT_7fff624013f0), lVar9 == 0))
                                goto LAB_7fff5fc74924;
                                uVar6 = FUN_7fff5fc804e0(uVar6,*(undefined4 *)(lVar9 + 0x18),
                                                         *(undefined8 *)(self + 0x140),0);
                                uVar2 = uStack_58;
                              }
                              if (*(longlong *)(self + 0xb8) != 0) {
                                FUN_7fff5fc85a40(*(longlong *)(self + 0xb8),uStack_50,uVar2 >> 0x20,
                                                 0);
                                lVar9 = *(longlong *)(self + 0x120);
                                lVar12 = *(longlong *)(self + 0xb8);
                                if (lVar9 != 0) {
                                  uVar1 = *(uint *)(lVar9 + 0x18);
                                  lVar9 = *(longlong *)(lVar9 + 0x10);
                                  if ((lVar9 != 0) && ((int)uVar1 < (int)*(uint *)(lVar9 + 0x18))) {
                                    if (*(uint *)(lVar9 + 0x18) <= uVar1) goto LAB_7fff5fc7491e;
                                    lVar9 = *(longlong *)(lVar9 + 0x20 + (longlong)(int)uVar1 * 8);
                                    if (lVar9 != 0) {
                                      if ((*(char *)(lVar9 + 0x2c) != '\0') ||
                                         (*(int *)(lVar9 + 0x30) + *(int *)(lVar9 + 0x28) != 0)) {
                                        uVar8 = *(undefined4 *)(lVar9 + 0x20);
                                      }
                                      uVar8 = FUN_7fff5fc6ed00(self,uVar8,0);
                                      if (lVar12 != 0) {
                                        FUN_7fff5fc856e0(lVar12,uVar6,uVar8,0);
                                        return;
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
            }
          }
        }
      }
      goto LAB_7fff5fc74924;
    }
    SmithGrant_InitDetailSelect(self,(undefined *)0x0);
    if ((*(longlong *)(self + 0x130) == 0) || (*(longlong *)(self + 0xb8) == 0))
    goto LAB_7fff5fc74924;
    FUN_7fff5fc859b0(*(longlong *)(self + 0xb8),
                     (0 < *(int *)(*(longlong *)(self + 0x130) + 0x18)) + '\x01',0);
    plVar14 = *(longlong **)(self + 0x28);
    uVar11 = func_0x7fff5f44ff00(_DAT_7fff62436790);
    uVar15 = _DAT_7fff62473110;
  }
  FUN_7fff5f4f6880(uVar11,self,uVar15,0);
  if (plVar14 != (longlong *)0x0) {
    (**(code **)(*plVar14 + 0x1c8))(plVar14,uVar11,*(undefined8 *)(*plVar14 + 0x1d0));
    return;
  }
LAB_7fff5fc74924:
  FUN_7fff5f47d660();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

