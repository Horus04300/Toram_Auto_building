
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UIBuildPanel_AddStatusPointCheck
               (undefined *self,int addPoint,int selectType,undefined *methodInfo)

{
  int iVar1;
  code *pcVar2;
  float fVar3;
  char cVar4;
  int iVar5;
  longlong lVar6;
  longlong *plVar7;
  longlong lVar8;
  undefined *puVar9;
  undefined8 uVar10;
  uint uVar11;
  uint uVar12;
  longlong lVar13;
  int iVar14;
  byte flag;
  int iVar15;
  float fVar16;
  undefined8 uStack_58;
  undefined8 uStack_50;
  
  lVar13 = (longlong)selectType;
  if (DAT_7fff625e3c1e == '\0') {
    FUN_7fff5f47d450(&DAT_7fff62414ed0);
    FUN_7fff5f47d450(&DAT_7fff6240e4b0);
    FUN_7fff5f47d450(&DAT_7fff62478a78);
    DAT_7fff625e3c1e = '\x01';
  }
  uVar10 = *(undefined8 *)(self + 0x38);
  if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
    func_0x7fff5f47d6f0();
  }
  cVar4 = FUN_7fff618ab2e0(uVar10);
  if (cVar4 != '\0') {
    if (*(undefined **)(self + 0x38) == (undefined *)0x0) goto LAB_7fff5fb7d70b;
    UIStatusBar_SliderEnable(*(undefined **)(self + 0x38),0,(undefined *)0x0);
  }
  lVar8 = *(longlong *)(self + 0x30);
  if (lVar8 == 0) goto LAB_7fff5fb7d70b;
  if (*(uint *)(lVar8 + 0x18) <= (uint)selectType) goto LAB_7fff5fb7d711;
  *(undefined8 *)(self + 0x38) = *(undefined8 *)(lVar8 + 0x20 + lVar13 * 8);
  thunk_FUN_7fff5f491fd0();
  lVar8 = *(longlong *)(self + 0x40);
  if (lVar8 == 0) goto LAB_7fff5fb7d70b;
  if (*(uint *)(lVar8 + 0x18) <= (uint)selectType) goto LAB_7fff5fb7d711;
  uVar12 = 0;
  *(int *)(lVar8 + 0x20 + lVar13 * 4) = addPoint;
  lVar8 = *(longlong *)(self + 0x40);
  iVar14 = 0;
  uVar11 = 0;
  do {
    if (lVar8 == 0) goto LAB_7fff5fb7d70b;
    if (*(uint *)(lVar8 + 0x18) <= uVar11) goto LAB_7fff5fb7d711;
    lVar6 = (longlong)(int)uVar11;
    uVar11 = uVar11 + 1;
    iVar14 = iVar14 + *(int *)(lVar8 + 0x20 + lVar6 * 4);
  } while ((int)uVar11 < 6);
  flag = 1;
  if (*(undefined **)(self + 0xd0) == (undefined *)0x0) goto LAB_7fff5fb7d70b;
  plVar7 = (longlong *)
           PlayerDataManager_get_PlayerStatus(*(undefined **)(self + 0xd0),(undefined *)0x0);
  if (plVar7 == (longlong *)0x0) goto LAB_7fff5fb7d70b;
  lVar8 = (**(code **)(*plVar7 + 0x188))(plVar7);
  if (lVar8 == 0) goto LAB_7fff5fb7d70b;
  iVar15 = *(int *)(self + 0xe0) + *(int *)(lVar8 + 0x38);
  iVar5 = UIBuildPanel_GetOverBuildPoint(self,(undefined *)0x0);
  if (self[0x158] == '\0') {
    if (*(int *)(_DAT_7fff62478a78 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    if (iVar15 <= iVar5 + *(int *)(*(longlong *)(_DAT_7fff62478a78 + 0xb8) + 8))
    goto LAB_7fff5fb7d3f3;
    iVar1 = *(int *)(lVar8 + 0x38);
    if (*(int *)(_DAT_7fff62478a78 + 0xe0) == 0) {
      func_0x7fff5f47d6f0();
    }
    iVar5 = (*(int *)(*(longlong *)(_DAT_7fff62478a78 + 0xb8) + 8) - iVar15) + iVar1 + iVar5;
  }
  else {
LAB_7fff5fb7d3f3:
    iVar5 = *(int *)(lVar8 + 0x38);
  }
  if (iVar5 <= iVar14) {
    addPoint = addPoint + (iVar5 - iVar14);
    lVar6 = *(longlong *)(self + 0x40);
    if (lVar6 == 0) goto LAB_7fff5fb7d70b;
    if (*(uint *)(lVar6 + 0x18) <= (uint)selectType) {
LAB_7fff5fb7d711:
      FUN_7fff5f47d650();
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    *(int *)(lVar6 + 0x20 + lVar13 * 4) = addPoint;
    flag = 0;
    iVar14 = iVar5;
  }
  fVar3 = _DAT_7fff61b52cfc;
  lVar13 = *(longlong *)(self + 0x118);
  if (iVar14 == 0) {
    if (DAT_7fff625e12c7 == '\0') {
      FUN_7fff5f47d450(&DAT_7fff62403718);
      DAT_7fff625e12c7 = '\x01';
    }
    uVar10 = **(undefined8 **)(_DAT_7fff62403718 + 0xb8);
    fVar16 = *(float *)(*(undefined8 **)(_DAT_7fff62403718 + 0xb8) + 1);
  }
  else {
    if (DAT_7fff625e142c == '\0') {
      FUN_7fff5f47d450(&DAT_7fff62403718);
      DAT_7fff625e142c = '\x01';
    }
    uStack_58 = *(undefined8 *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0x18);
    fVar16 = *(float *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0x20) * fVar3;
    uStack_50 = CONCAT44(uStack_50._4_4_,fVar16);
    uVar10 = CONCAT44((float)((ulonglong)uStack_58 >> 0x20) * fVar3,(float)uStack_58 * fVar3);
  }
  if (lVar13 != 0) {
    uStack_50 = CONCAT44(uStack_50._4_4_,fVar16);
    uStack_58 = uVar10;
    FUN_7fff5f51ed20(lVar13,&uStack_58,_DAT_7fff61b52b40,0);
    lVar13 = *(longlong *)(self + 0x120);
    if ((iVar14 == 0) && ((0 < *(int *)(self + 0xe0) || (*(int *)(lVar8 + 0x40) != 0)))) {
      if (DAT_7fff625e142c == '\0') {
        FUN_7fff5f47d450(&DAT_7fff62403718);
        DAT_7fff625e142c = '\x01';
      }
      uStack_58 = *(undefined8 *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0x18);
      fVar16 = *(float *)(*(longlong *)(_DAT_7fff62403718 + 0xb8) + 0x20) * fVar3;
      uStack_50 = CONCAT44(uStack_50._4_4_,fVar16);
      uVar10 = CONCAT44((float)((ulonglong)uStack_58 >> 0x20) * fVar3,(float)uStack_58 * fVar3);
    }
    else {
      if (DAT_7fff625e12c7 == '\0') {
        FUN_7fff5f47d450(&DAT_7fff62403718);
        DAT_7fff625e12c7 = '\x01';
      }
      uVar10 = **(undefined8 **)(_DAT_7fff62403718 + 0xb8);
      fVar16 = *(float *)(*(undefined8 **)(_DAT_7fff62403718 + 0xb8) + 1);
    }
    if (lVar13 != 0) {
      uStack_50 = CONCAT44(uStack_50._4_4_,fVar16);
      uStack_58 = uVar10;
      FUN_7fff5f51ed20(lVar13,&uStack_58,_DAT_7fff61b52b40,0);
      UIBuildPanel_SetStatusPointLabel(self,(undefined *)0x0);
      lVar13 = *(longlong *)(self + 0x30);
      if (lVar13 != 0) {
        for (; (int)uVar12 < *(int *)(lVar13 + 0x18); uVar12 = uVar12 + 1) {
          if (*(uint *)(lVar13 + 0x18) <= uVar12) goto LAB_7fff5fb7d711;
          puVar9 = *(undefined **)(lVar13 + 0x20 + (longlong)(int)uVar12 * 8);
          if (*(int *)(_DAT_7fff6240e4b0 + 0xe0) == 0) {
            func_0x7fff5f47d6f0();
          }
          cVar4 = FUN_7fff618ab2e0(puVar9,0);
          if (cVar4 != '\0') {
            if (puVar9 == (undefined *)0x0) goto LAB_7fff5fb7d70b;
            UIStatusBar_EnableBuildPoint(puVar9,flag,(undefined *)0x0);
          }
        }
        if (*(undefined **)(self + 0x38) != (undefined *)0x0) {
          UIStatusBar_SetBuildParameter(*(undefined **)(self + 0x38),addPoint,(undefined *)0x0);
          plVar7 = *(longlong **)(self + 0xd8);
          puVar9 = UIBuildPanel_GetBuildPrimaryStatus(self,(undefined *)0x0);
          uVar10 = func_0x7fff5f44ff00(_DAT_7fff62414ed0);
          func_0x7fff616a8460(uVar10,0);
          if (plVar7 != (longlong *)0x0) {
            (**(code **)(*plVar7 + 0x278))(plVar7,puVar9,uVar10,0,*(undefined8 *)(*plVar7 + 0x280));
            plVar7 = *(longlong **)(self + 0xd8);
            if (plVar7 != (longlong *)0x0) {
              lVar13 = (**(code **)(*plVar7 + 0x198))(plVar7,*(undefined8 *)(*plVar7 + 0x1a0));
              if (DAT_7fff625e3c1d == '\0') {
                uStack_50 = 0x7fff5fb7db82;
                FUN_7fff5f47d450(&DAT_7fff624485c8,lVar13,0);
                DAT_7fff625e3c1d = '\x01';
              }
              if (*(undefined **)(self + 0xd0) != (undefined *)0x0) {
                uStack_50 = 0x7fff5fb7dbaf;
                plVar7 = (longlong *)
                         PlayerDataManager_get_PlayerStatus
                                   (*(undefined **)(self + 0xd0),(undefined *)0x0);
                if (plVar7 != (longlong *)0x0) {
                  uStack_50 = 0x7fff5fb7dbcf;
                  lVar8 = (**(code **)(*plVar7 + 0x198))(plVar7,*(undefined8 *)(*plVar7 + 0x1a0));
                  if (lVar13 != 0) {
                    uStack_50 = 0x7fff5fb7dbef;
                    iVar14 = FUN_7fff5f252ec0(10,_DAT_7fff624485c8,lVar13);
                    uStack_50 = 0x7fff5fb7dc05;
                    iVar5 = FUN_7fff5f252ec0(10,_DAT_7fff624485c8,lVar13);
                    if (lVar8 != 0) {
                      uStack_50 = 0x7fff5fb7dc29;
                      iVar15 = FUN_7fff5f252ec0(10,_DAT_7fff624485c8,lVar8);
                      uStack_50 = 0x7fff5fb7dc44;
                      UIBuildPanel_SetParamLabel
                                (self,(undefined *)0x0,iVar14,iVar5 == iVar15,(undefined *)0x0);
                      uStack_50 = 0x7fff5fb7dc57;
                      iVar14 = FUN_7fff5f252ec0(0xb,_DAT_7fff624485c8,lVar13);
                      uStack_50 = 0x7fff5fb7dc6c;
                      iVar5 = FUN_7fff5f252ec0(0xb,_DAT_7fff624485c8,lVar13);
                      uStack_50 = 0x7fff5fb7dc81;
                      iVar15 = FUN_7fff5f252ec0(0xb,_DAT_7fff624485c8,lVar8);
                      uStack_50 = 0x7fff5fb7dc9b;
                      UIBuildPanel_SetParamLabel
                                (self,(undefined *)0x1,iVar14,iVar5 == iVar15,(undefined *)0x0);
                      uStack_50 = 0x7fff5fb7dcae;
                      iVar14 = FUN_7fff5f252ec0(0xe,_DAT_7fff624485c8,lVar13);
                      uStack_50 = 0x7fff5fb7dcc3;
                      iVar5 = FUN_7fff5f252ec0(0xe,_DAT_7fff624485c8,lVar13);
                      uStack_50 = 0x7fff5fb7dcd8;
                      iVar15 = FUN_7fff5f252ec0(0xe,_DAT_7fff624485c8,lVar8);
                      uStack_50 = 0x7fff5fb7dcf2;
                      UIBuildPanel_SetParamLabel
                                (self,(undefined *)0x2,iVar14,iVar5 == iVar15,(undefined *)0x0);
                      uStack_50 = 0x7fff5fb7dd05;
                      iVar14 = FUN_7fff5f252ec0(0x10,_DAT_7fff624485c8,lVar13);
                      uStack_50 = 0x7fff5fb7dd1a;
                      iVar5 = FUN_7fff5f252ec0(0x10,_DAT_7fff624485c8,lVar13);
                      uStack_50 = 0x7fff5fb7dd2f;
                      iVar15 = FUN_7fff5f252ec0(0x10,_DAT_7fff624485c8,lVar8);
                      uStack_50 = 0x7fff5fb7dd49;
                      UIBuildPanel_SetParamLabel
                                (self,(undefined *)0x3,iVar14,iVar5 == iVar15,(undefined *)0x0);
                      uStack_50 = 0x7fff5fb7dd5c;
                      iVar14 = FUN_7fff5f252ec0(0x13,_DAT_7fff624485c8,lVar13);
                      uStack_50 = 0x7fff5fb7dd71;
                      iVar5 = FUN_7fff5f252ec0(0x13,_DAT_7fff624485c8,lVar13);
                      uStack_50 = 0x7fff5fb7dd86;
                      iVar15 = FUN_7fff5f252ec0(0x13,_DAT_7fff624485c8,lVar8);
                      uStack_50 = 0x7fff5fb7dda0;
                      UIBuildPanel_SetParamLabel
                                (self,(undefined *)0x4,iVar14,iVar5 == iVar15,(undefined *)0x0);
                      uStack_50 = 0x7fff5fb7ddb3;
                      iVar14 = FUN_7fff5f252ec0(0x14,_DAT_7fff624485c8,lVar13);
                      uStack_50 = 0x7fff5fb7ddc8;
                      iVar5 = FUN_7fff5f252ec0(0x14,_DAT_7fff624485c8,lVar13);
                      uStack_50 = 0x7fff5fb7dddd;
                      iVar15 = FUN_7fff5f252ec0(0x14,_DAT_7fff624485c8,lVar8);
                      uStack_50 = 0x7fff5fb7ddf7;
                      UIBuildPanel_SetParamLabel
                                (self,(undefined *)0x5,iVar14,iVar5 == iVar15,(undefined *)0x0);
                      uStack_50 = 0x7fff5fb7de0a;
                      iVar14 = FUN_7fff5f252ec0(0x16,_DAT_7fff624485c8,lVar13);
                      uStack_50 = 0x7fff5fb7de1f;
                      iVar5 = FUN_7fff5f252ec0(0x16,_DAT_7fff624485c8,lVar13);
                      uStack_50 = 0x7fff5fb7de34;
                      iVar15 = FUN_7fff5f252ec0(0x16,_DAT_7fff624485c8,lVar8);
                      uStack_50 = 0x7fff5fb7de4e;
                      UIBuildPanel_SetParamLabel
                                (self,(undefined *)0x7,iVar14,iVar5 == iVar15,(undefined *)0x0);
                      uStack_50 = 0x7fff5fb7de61;
                      iVar14 = FUN_7fff5f252ec0(0x17,_DAT_7fff624485c8,lVar13);
                      uStack_50 = 0x7fff5fb7de76;
                      iVar5 = FUN_7fff5f252ec0(0x17,_DAT_7fff624485c8,lVar13);
                      uStack_50 = 0x7fff5fb7de8b;
                      iVar15 = FUN_7fff5f252ec0(0x17,_DAT_7fff624485c8,lVar8);
                      uStack_50 = 0x7fff5fb7dea5;
                      UIBuildPanel_SetParamLabel
                                (self,(undefined *)0x8,iVar14,iVar5 == iVar15,(undefined *)0x0);
                      uStack_50 = 0x7fff5fb7deb8;
                      iVar14 = FUN_7fff5f252ec0(0x12,_DAT_7fff624485c8,lVar13);
                      uStack_50 = 0x7fff5fb7decd;
                      iVar5 = FUN_7fff5f252ec0(0x12,_DAT_7fff624485c8,lVar13);
                      uStack_50 = 0x7fff5fb7dee2;
                      iVar15 = FUN_7fff5f252ec0(0x12,_DAT_7fff624485c8,lVar8);
                      uStack_50 = 0x7fff5fb7defc;
                      UIBuildPanel_SetParamLabel
                                (self,(undefined *)0x9,iVar14,iVar5 == iVar15,(undefined *)0x0);
                      uStack_50 = 0x7fff5fb7df0f;
                      iVar14 = FUN_7fff5f252ec0(0x11,_DAT_7fff624485c8,lVar13);
                      uStack_50 = 0x7fff5fb7df24;
                      iVar5 = FUN_7fff5f252ec0(0x11,_DAT_7fff624485c8,lVar13);
                      uStack_50 = 0x7fff5fb7df39;
                      iVar15 = FUN_7fff5f252ec0(0x11,_DAT_7fff624485c8,lVar8);
                      uStack_50 = 0x7fff5fb7df53;
                      UIBuildPanel_SetParamLabel
                                (self,(undefined *)0x6,iVar14,iVar5 == iVar15,(undefined *)0x0);
                      return;
                    }
                  }
                }
              }
              uStack_50 = 0x7fff5fb7df73;
              FUN_7fff5f47d660();
              pcVar2 = (code *)swi(3);
              (*pcVar2)();
              return;
            }
          }
        }
      }
    }
  }
LAB_7fff5fb7d70b:
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

