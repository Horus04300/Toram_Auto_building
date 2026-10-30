
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobaPlayerActionManager_Damaged
               (undefined *thisObject,undefined *actor,undefined *action,undefined *damageData,
               byte id,undefined *methodInfo)

{
  code *pcVar1;
  longlong *plVar2;
  float fVar3;
  char cVar4;
  char cVar5;
  char cVar6;
  char cVar7;
  byte bVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  longlong *plVar13;
  longlong lVar14;
  undefined8 uVar15;
  undefined8 *puVar16;
  longlong lVar17;
  undefined *puVar18;
  undefined1 uVar19;
  bool bVar20;
  bool bVar21;
  undefined4 uVar22;
  undefined4 uVar23;
  undefined4 uVar24;
  ulonglong uVar25;
  undefined8 uVar26;
  undefined8 in_stack_ffffffffffffff30;
  undefined4 uVar28;
  ulonglong uVar27;
  ulonglong in_stack_ffffffffffffff38;
  ulonglong in_stack_ffffffffffffff40;
  undefined4 auStack_a8 [2];
  longlong *plStack_a0;
  longlong *plStack_98;
  longlong *plStack_90;
  undefined8 uStack_88;
  float fStack_80;
  undefined8 uStack_78;
  float fStack_70;
  undefined8 uStack_68;
  float fStack_60;
  
  uVar28 = (undefined4)((ulonglong)in_stack_ffffffffffffff30 >> 0x20);
  if (DAT_7ffe9caddc03 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92dfe0);
    FUN_7ffe9996d590(&DAT_7ffe9c92ee68);
    FUN_7ffe9996d590(&DAT_7ffe9c960fa0);
    FUN_7ffe9996d590(&DAT_7ffe9c9612c8);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c95f2c8);
    FUN_7ffe9996d590(&DAT_7ffe9c969548);
    FUN_7ffe9996d590(&DAT_7ffe9c9279a8);
    FUN_7ffe9996d590(&DAT_7ffe9c928ba0);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c9530e0);
    FUN_7ffe9996d590(&DAT_7ffe9c972b60);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c93cd40);
    FUN_7ffe9996d590(&DAT_7ffe9c956ad0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f6978);
    DAT_7ffe9caddc03 = '\x01';
  }
  puVar18 = (undefined *)0x0;
  iVar12 = 0;
  plStack_a0 = (longlong *)0x0;
  plStack_90 = (longlong *)0x0;
  plStack_98 = (longlong *)0x0;
  auStack_a8[0] = 0;
  uStack_78 = 0;
  fStack_70 = 0.0;
  if (*(longlong *)(thisObject + 0xa8) == 0) goto LAB_7ffe9a4235e4;
  FUN_7ffe9a40cb40(*(longlong *)(thisObject + 0xa8),0);
  if (damageData == (undefined *)0x0) {
    return;
  }
  pcVar1 = *(code **)(*(longlong *)thisObject + 0x298);
  if (*(int *)(damageData + 0x14) == 0) {
    plVar13 = (longlong *)(*pcVar1)(thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar13 != (longlong *)0x0) &&
       (lVar14 = (**(code **)(*plVar13 + 0x1c8))(plVar13,*(undefined8 *)(*plVar13 + 0x1d0)),
       lVar14 != 0)) {
      cVar4 = FUN_7ffe9a7cbb30(lVar14,0x40f,&plStack_a0,0);
      if (cVar4 != '\0') {
        if (plStack_a0 == (longlong *)0x0) goto LAB_7ffe9a4235e4;
        if (((*(byte *)(*plStack_a0 + 0x130) < *(byte *)(_DAT_7ffe9c960fa0 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*plStack_a0 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c960fa0 + 0x130) * 8) != _DAT_7ffe9c960fa0)) ||
           (plStack_a0 == (longlong *)0x0)) {
          FUN_7ffe9996c950(plStack_a0);
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        (**(code **)(*plStack_a0 + 0x2a8))(plStack_a0,*(undefined8 *)(*plStack_a0 + 0x2b0));
      }
      if (*(int *)(damageData + 0x18) != 1) {
        return;
      }
      plVar13 = *(longlong **)(thisObject + 0x30);
      if (plVar13 != (longlong *)0x0) {
        (**(code **)(*plVar13 + 0x2e8))(plVar13,actor,*(undefined8 *)(*plVar13 + 0x2f0));
        return;
      }
    }
    goto LAB_7ffe9a4235e4;
  }
  plVar13 = (longlong *)(*pcVar1)();
  if (plVar13 == (longlong *)0x0) goto LAB_7ffe9a4235e4;
  cVar4 = (**(code **)(*plVar13 + 0x268))(plVar13,*(undefined8 *)(*plVar13 + 0x270));
  if (cVar4 != '\0') {
    func_0x7ffe9a8ffdb0(damageData,0);
    plVar13 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar13 != (longlong *)0x0) &&
       (lVar14 = (**(code **)(*plVar13 + 0x1c8))(plVar13,*(undefined8 *)(*plVar13 + 0x1d0)),
       lVar14 != 0)) {
      cVar4 = FUN_7ffe9a7cbb30(lVar14,0x40f,&plStack_a0,0);
      if (cVar4 == '\0') {
        return;
      }
      if (plStack_a0 != (longlong *)0x0) {
        if (((*(byte *)(_DAT_7ffe9c960fa0 + 0x130) <= *(byte *)(*plStack_a0 + 0x130)) &&
            (*(longlong *)
              (*(longlong *)(*plStack_a0 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c960fa0 + 0x130) * 8) == _DAT_7ffe9c960fa0)) &&
           (plStack_a0 != (longlong *)0x0)) {
          (**(code **)(*plStack_a0 + 0x2a8))(plStack_a0,*(undefined8 *)(*plStack_a0 + 0x2b0));
          return;
        }
        FUN_7ffe9996c950(plStack_a0);
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
    }
    goto LAB_7ffe9a4235e4;
  }
  lVar14 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
  if (lVar14 == 0) goto LAB_7ffe9a4235e4;
  if (*(int *)(lVar14 + 0x8c) == 0xe) {
    lVar14 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
    if ((lVar14 == 0) || (lVar14 = FUN_7ffe9a29dca0(lVar14,0), lVar14 == 0)) goto LAB_7ffe9a4235e4;
    lVar14 = FUN_7ffe9ab9c3a0(lVar14,_DAT_7ffe9c969548);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar4 = FUN_7ffe9bda2160(lVar14,0,0);
    if (cVar4 != '\0') {
      if (lVar14 == 0) goto LAB_7ffe9a4235e4;
      FUN_7ffe99debdf0(lVar14,0);
    }
  }
  else {
    lVar14 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
    if (lVar14 == 0) goto LAB_7ffe9a4235e4;
    if (*(int *)(lVar14 + 0x8c) == 0x2a) {
      if ((*(longlong *)(thisObject + 0x98) == 0) ||
         (lVar14 = *(longlong *)(*(longlong *)(thisObject + 0x98) + 0x180), lVar14 == 0))
      goto LAB_7ffe9a4235e4;
      FUN_7ffe9a844b20(lVar14,0);
    }
    else {
      lVar14 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
      if (lVar14 == 0) goto LAB_7ffe9a4235e4;
      if (*(int *)(lVar14 + 0x8c) == 0x1e) {
        if ((*(longlong *)(thisObject + 0x98) == 0) ||
           (lVar14 = *(longlong *)(*(longlong *)(thisObject + 0x98) + 0x180), lVar14 == 0))
        goto LAB_7ffe9a4235e4;
        FUN_7ffe9a844030(lVar14,0);
      }
    }
  }
  if ((*(int *)(damageData + 0x18) - 2U & 0xfffffffb) == 0) {
    plVar13 = *(longlong **)(thisObject + 0x30);
    if (plVar13 == (longlong *)0x0) goto LAB_7ffe9a4235e4;
    (**(code **)(*plVar13 + 0x2c8))(plVar13,actor,damageData);
  }
  FUN_7ffe9a80e8d0(thisObject,damageData,0);
  FUN_7ffe9a8032a0(thisObject,0);
  cVar4 = FUN_7ffe9a6e01d0(thisObject,0);
  if (cVar4 != '\0') {
    FUN_7ffe9a6e0580(thisObject,0);
    CutOffTheDisasterAction_DamageCut(thisObject,action,damageData,(undefined *)0x0);
  }
  cVar4 = FUN_7ffe9a7229f0(thisObject,damageData,0);
  FUN_7ffe9a70d450(thisObject,damageData,0);
  FUN_7ffe9a670570(thisObject,damageData,0);
  FUN_7ffe9a662e60(thisObject,damageData,0);
  FUN_7ffe9a710750(thisObject,damageData,0);
  cVar5 = FUN_7ffe9a7d2fc0(thisObject,damageData,0);
  bVar20 = cVar5 == '\0' && cVar4 == '\0';
  plVar13 = (longlong *)
            (**(code **)(*(longlong *)thisObject + 0x298))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if ((plVar13 == (longlong *)0x0) ||
     (lVar14 = (**(code **)(*plVar13 + 0x1c8))(plVar13,*(undefined8 *)(*plVar13 + 0x1d0)),
     lVar14 == 0)) goto LAB_7ffe9a4235e4;
  cVar6 = FUN_7ffe9a7cbb30(lVar14,0x5e,&plStack_a0);
  if (cVar6 != '\0') {
    if (plStack_a0 == (longlong *)0x0) goto LAB_7ffe9a4235e4;
    if (((*(byte *)(*plStack_a0 + 0x130) < *(byte *)(_DAT_7ffe9c9530e0 + 0x130)) ||
        (*(longlong *)
          (*(longlong *)(*plStack_a0 + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c9530e0 + 0x130) * 8) != _DAT_7ffe9c9530e0)) ||
       (plStack_a0 == (longlong *)0x0)) {
      FUN_7ffe9996c950(plStack_a0);
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    if ((char)plStack_a0[4] != '\0') {
      func_0x7ffe9a900040(damageData,0,0);
      *(uint *)(damageData + 0x70) = *(uint *)(damageData + 0x70) | 0x100;
      *(undefined4 *)(damageData + 0x1c) = 4;
    }
  }
  FUN_7ffe9a7ab320(thisObject,damageData,0);
  FUN_7ffe9a67dc30(thisObject,damageData,0);
  FUN_7ffe9a74a080(thisObject,damageData,0);
  FUN_7ffe9a69d7d0(thisObject,damageData,0);
  plVar13 = (longlong *)
            (**(code **)(*(longlong *)thisObject + 0x298))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if (((plVar13 == (longlong *)0x0) ||
      (lVar14 = (**(code **)(*plVar13 + 0x1c8))(plVar13,*(undefined8 *)(*plVar13 + 0x1d0)),
      lVar14 == 0)) || (*(longlong *)(lVar14 + 0x40) == 0)) goto LAB_7ffe9a4235e4;
  cVar6 = FUN_7ffe9ad8e670(*(longlong *)(lVar14 + 0x40),0x445,&plStack_a0,_DAT_7ffe9c934418);
  if (cVar6 != '\0') {
    if (plStack_a0 == (longlong *)0x0) goto LAB_7ffe9a4235e4;
    if (((*(byte *)(*plStack_a0 + 0x130) < *(byte *)(_DAT_7ffe9c928ba0 + 0x130)) ||
        (*(longlong *)
          (*(longlong *)(*plStack_a0 + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c928ba0 + 0x130) * 8) != _DAT_7ffe9c928ba0)) ||
       (plStack_a0 == (longlong *)0x0)) {
      FUN_7ffe9996c950(plStack_a0);
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    FUN_7ffe9a7901e0(plStack_a0,actor,thisObject,damageData,0);
  }
  uVar23 = 0;
  FUN_7ffe9a82a710(actor,thisObject,action,damageData,0);
  plVar13 = (longlong *)
            (**(code **)(*(longlong *)thisObject + 0x298))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if ((plVar13 == (longlong *)0x0) ||
     (lVar14 = (**(code **)(*plVar13 + 0x1c8))(plVar13,*(undefined8 *)(*plVar13 + 0x1d0)),
     lVar14 == 0)) goto LAB_7ffe9a4235e4;
  cVar6 = FUN_7ffe9a7cbb30(lVar14,0x2c9,&plStack_a0,0);
  if (cVar6 != '\0') {
    if (plStack_a0 == (longlong *)0x0) goto LAB_7ffe9a4235e4;
    func_0x7ffe9a7a2130(plStack_a0,0);
  }
  FUN_7ffe9a6c7c00(*(undefined8 *)(thisObject + 0xc0),damageData,0);
  FUN_7ffe9a6551d0(thisObject,damageData,0);
  FUN_7ffe9a6b38f0(thisObject,0);
  if (*(int *)(damageData + 0x8c) == -1) {
    *(undefined4 *)(damageData + 0x8c) = 0;
    if (*(longlong *)(thisObject + 0x30) == 0) goto LAB_7ffe9a4235e4;
    cVar6 = FUN_7ffe9a7e1140(*(longlong *)(thisObject + 0x30),0);
    if (cVar6 != '\0') {
      if ((*(longlong *)(thisObject + 0x30) == 0) ||
         (plVar13 = *(longlong **)(*(longlong *)(thisObject + 0x30) + 0x30),
         plVar13 == (longlong *)0x0)) goto LAB_7ffe9a4235e4;
      plVar13 = (longlong *)(**(code **)(*plVar13 + 0x188))(plVar13,*(undefined8 *)(*plVar13 + 400))
      ;
      if (plVar13 == (longlong *)0x0) goto LAB_7ffe9a4235e4;
      iVar9 = (**(code **)(*plVar13 + 0x2e8))(plVar13,*(undefined8 *)(*plVar13 + 0x2f0));
      bVar21 = false;
      if (iVar9 == 1) {
        if ((*(longlong *)(thisObject + 0x30) == 0) ||
           (plVar2 = *(longlong **)(*(longlong *)(thisObject + 0x30) + 0x30),
           plVar2 == (longlong *)0x0)) goto LAB_7ffe9a4235e4;
        cVar6 = (**(code **)(*plVar2 + 0x198))(plVar2,*(undefined8 *)(*plVar2 + 0x1a0));
        bVar21 = false;
        if (cVar6 != '\0') {
          bVar21 = true;
        }
      }
      iVar9 = (**(code **)(*plVar13 + 0x188))(plVar13,*(undefined8 *)(*plVar13 + 400));
      if (iVar9 == 0x36a) {
        if ((*(byte *)(*plVar13 + 0x130) < *(byte *)(_DAT_7ffe9c8f6978 + 0x130)) ||
           (*(longlong *)
             (*(longlong *)(*plVar13 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c8f6978 + 0x130) * 8) != _DAT_7ffe9c8f6978)) {
          FUN_7ffe9996c950(plVar13);
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        bVar21 = bVar21 || *(char *)((longlong)plVar13 + 0x154) != '\0';
      }
      if ((bVar21) && (iVar9 = FUN_7ffe9bda4580(0,100), iVar9 < 100)) {
        *(undefined4 *)(damageData + 0x8c) = 1;
        if (*(int *)(_DAT_7ffe9c92dfe0 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        uVar22 = FUN_7ffe9a4db1f0(1,0);
        *(undefined4 *)(damageData + 0x94) = uVar22;
        uVar22 = FUN_7ffe9a4db080(1,0);
        *(undefined4 *)(damageData + 0x98) = uVar22;
      }
    }
  }
  plVar13 = (longlong *)
            (**(code **)(*(longlong *)thisObject + 0x298))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if ((plVar13 == (longlong *)0x0) ||
     (lVar14 = (**(code **)(*plVar13 + 0x1c8))(plVar13,*(undefined8 *)(*plVar13 + 0x1d0)),
     lVar14 == 0)) goto LAB_7ffe9a4235e4;
  cVar6 = FUN_7ffe9a7c6d00(lVar14,0x426,0);
  if (*(longlong *)(thisObject + 0x88) == 0) goto LAB_7ffe9a4235e4;
  cVar7 = func_0x7ffe9a4ceea0(*(longlong *)(thisObject + 0x88),0);
  if (((cVar7 != '\0') && (cVar5 == '\0' && cVar4 == '\0')) && (*(int *)(damageData + 0x14) != 0)) {
    if (*(longlong *)(thisObject + 0x88) == 0) goto LAB_7ffe9a4235e4;
    cVar4 = FUN_7ffe9a7ef910(*(longlong *)(thisObject + 0x88),0);
    if (cVar4 != '\0') {
      lVar14 = FUN_7ffe9a42cc20(thisObject,0);
      if ((actor == (undefined *)0x0) ||
         (uVar15 = FUN_7ffe9ab9c3a0(actor,_DAT_7ffe9c95f2c8), lVar14 == 0)) goto LAB_7ffe9a4235e4;
      FUN_7ffe9a43cb40(lVar14,uVar15,0);
    }
  }
  plVar13 = (longlong *)
            (**(code **)(*(longlong *)thisObject + 0x298))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if (((plVar13 == (longlong *)0x0) ||
      (lVar14 = (**(code **)(*plVar13 + 0x1c8))(plVar13,*(undefined8 *)(*plVar13 + 0x1d0)),
      lVar14 == 0)) || (*(longlong *)(lVar14 + 0x40) == 0)) goto LAB_7ffe9a4235e4;
  bVar8 = FUN_7ffe9ad8e670(*(longlong *)(lVar14 + 0x40),0x3ce,&plStack_a0);
  if ((bVar20 & bVar8) != 0) {
    if (plStack_a0 == (longlong *)0x0) goto LAB_7ffe9a4235e4;
    if (((*(byte *)(*plStack_a0 + 0x130) < *(byte *)(_DAT_7ffe9c9279a8 + 0x130)) ||
        (*(longlong *)
          (*(longlong *)(*plStack_a0 + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c9279a8 + 0x130) * 8) != _DAT_7ffe9c9279a8)) ||
       (plStack_a0 == (longlong *)0x0)) {
      FUN_7ffe9996c950(plStack_a0);
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    HandlingerOfGodspeedBuf_DamageFunction
              ((undefined *)plStack_a0,thisObject,damageData,(undefined *)0x0);
  }
  if (bVar20) {
    if ((*(longlong *)(thisObject + 0xc0) == 0) ||
       (lVar14 = *(longlong *)(*(longlong *)(thisObject + 0xc0) + 0x90), lVar14 == 0))
    goto LAB_7ffe9a4235e4;
    uVar25 = 0;
    cVar4 = FUN_7ffe9a58d6a0(lVar14,4,&plStack_90,&plStack_98,0);
    if (cVar4 != '\0') {
      iVar9 = iVar12;
      if (plStack_90 == (longlong *)0x0) {
LAB_7ffe9a422626:
        plVar13 = plStack_98;
        if (plStack_98 != (longlong *)0x0) goto LAB_7ffe9a42262f;
      }
      else {
        if (plStack_98 == (longlong *)0x0) {
          iVar9 = (**(code **)(*plStack_90 + 0x198))
                            (plStack_90,*(undefined8 *)(*plStack_90 + 0x1a0));
          goto LAB_7ffe9a422626;
        }
        plVar13 = plStack_90;
        if (*(byte *)(plStack_90 + 2) < *(byte *)(plStack_98 + 2)) {
          plVar13 = plStack_98;
        }
        if (plVar13 == (longlong *)0x0) goto LAB_7ffe9a4235e4;
LAB_7ffe9a42262f:
        iVar9 = (**(code **)(*plVar13 + 0x198))(plVar13,*(undefined8 *)(*plVar13 + 0x1a0));
      }
      plVar13 = *(longlong **)(thisObject + 0xc0);
      if ((plVar13 == (longlong *)0x0) ||
         (lVar14 = (**(code **)(*plVar13 + 0x198))(plVar13,*(undefined8 *)(*plVar13 + 0x1a0)),
         lVar14 == 0)) goto LAB_7ffe9a4235e4;
      iVar10 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar14);
      iVar9 = (int)((float)iVar10 * ((float)iVar9 / _DAT_7ffe9c049cfc));
      if (*(int *)(damageData + 0x84) <= iVar9) {
        iVar9 = *(int *)(damageData + 0x84);
      }
      func_0x7ffe9a900040(damageData,iVar9,0);
    }
    lVar14 = *(longlong *)(thisObject + 0xc0);
    if ((lVar14 == 0) || (*(longlong *)(lVar14 + 0x90) == 0)) goto LAB_7ffe9a4235e4;
    cVar4 = FUN_7ffe9a58d4a0(*(longlong *)(lVar14 + 0x90),lVar14,auStack_a8);
    if (cVar4 != '\0') {
      lVar14 = (**(code **)(*(longlong *)thisObject + 0x2a8))
                         (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2b0));
      if (lVar14 == 0) goto LAB_7ffe9a4235e4;
      in_stack_ffffffffffffff40 = 0;
      in_stack_ffffffffffffff38 = 0;
      uVar25 = uVar25 & 0xffffffffffffff00;
      FUN_7ffe9a4d8d20(lVar14,0x1b);
    }
    FUN_7ffe9a7b4560(thisObject,actor,damageData,0,uVar25);
    lVar14 = (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if (lVar14 == 0) goto LAB_7ffe9a4235e4;
    FUN_7ffe9a4a1500(lVar14,*(undefined4 *)(damageData + 0x84),cVar6);
    plVar13 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar13 == (longlong *)0x0) ||
       (lVar14 = (**(code **)(*plVar13 + 0x1e8))(plVar13,*(undefined8 *)(*plVar13 + 0x1f0)),
       lVar14 == 0)) goto LAB_7ffe9a4235e4;
    FUN_7ffe9a4dacc0(lVar14,0);
    plVar13 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar13 == (longlong *)0x0) ||
       (lVar14 = (**(code **)(*plVar13 + 0x1c8))(plVar13,*(undefined8 *)(*plVar13 + 0x1d0)),
       lVar14 == 0)) goto LAB_7ffe9a4235e4;
    cVar4 = FUN_7ffe9a7c6d00(lVar14,0x205,0);
    plVar13 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar13 == (longlong *)0x0) ||
       (lVar14 = (**(code **)(*plVar13 + 0x1c8))(plVar13,*(undefined8 *)(*plVar13 + 0x1d0)),
       lVar14 == 0)) goto LAB_7ffe9a4235e4;
    FUN_7ffe9a7c9e70(lVar14,thisObject,0);
    if (cVar4 != '\0') {
      if (*(longlong *)(thisObject + 0x58) == 0) goto LAB_7ffe9a4235e4;
      FUN_7ffe9a9b8750(*(longlong *)(thisObject + 0x58),0);
      FUN_7ffe9a6ac810(thisObject,0);
    }
    FUN_7ffe9a7274d0(thisObject,damageData,0);
    FUN_7ffe9a74b860(thisObject,actor,damageData);
    FUN_7ffe9a824d50(thisObject,0);
    plVar13 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar13 == (longlong *)0x0) ||
       (lVar14 = (**(code **)(*plVar13 + 0x1c8))(plVar13,*(undefined8 *)(*plVar13 + 0x1d0)),
       lVar14 == 0)) goto LAB_7ffe9a4235e4;
    cVar4 = FUN_7ffe9a7cbb30(lVar14,0x2c3,&plStack_a0);
    if ((cVar4 != '\0') && (cVar4 = FUN_7ffe99b1ccd0(thisObject,0), cVar4 == '\0')) {
      if (plStack_a0 == (longlong *)0x0) goto LAB_7ffe9a4235e4;
      if (((*(byte *)(*plStack_a0 + 0x130) < *(byte *)(_DAT_7ffe9c9612c8 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*plStack_a0 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7ffe9c9612c8 + 0x130) * 8) != _DAT_7ffe9c9612c8)) ||
         (plStack_a0 == (longlong *)0x0)) {
        FUN_7ffe9996c950(plStack_a0);
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      FUN_7ffe9a77f650(plStack_a0,actor,0);
    }
    GemCartBuffer_InflexibilityEmergingBuff_Damaged
              (thisObject,*(int *)(damageData + 0x84),
               (undefined *)(ulonglong)*(uint *)(damageData + 0x18),(undefined *)0x0);
    uVar23 = 0;
    HorizontalCutAction_Damaged(thisObject,actor,action,damageData,(undefined *)0x0);
  }
  else {
    *(uint *)(damageData + 0x70) = *(uint *)(damageData + 0x70) & 0xf7;
    *(undefined4 *)(damageData + 0x1c) = 4;
  }
  cVar4 = (**(code **)(*(longlong *)thisObject + 0x188))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
  if (cVar4 == '\0') {
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    bVar8 = FUN_7ffe9bda2160(actor,0,0);
    if ((bVar20 & bVar8) != 0) {
      if (*(longlong *)(thisObject + 0x20) == 0) goto LAB_7ffe9a4235e4;
      puVar16 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_68,*(longlong *)(thisObject + 0x20),0);
      uStack_88 = *puVar16;
      fStack_80 = *(float *)(puVar16 + 1);
      if ((actor == (undefined *)0x0) || (lVar14 = FUN_7ffe9bd9b890(actor,0), lVar14 == 0))
      goto LAB_7ffe9a4235e4;
      puVar16 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_68,lVar14,0);
      fStack_80 = fStack_80 - *(float *)(puVar16 + 1);
      lVar14 = *(longlong *)(thisObject + 0x48);
      iVar12 = *(int *)(damageData + 0x84);
      uStack_68 = CONCAT44(uStack_88._4_4_ - (float)((ulonglong)*puVar16 >> 0x20),
                           (float)uStack_88 - (float)*puVar16);
      fStack_60 = fStack_80;
      plVar13 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar13 == (longlong *)0x0) ||
         (lVar17 = (**(code **)(*plVar13 + 0x198))(plVar13,*(undefined8 *)(*plVar13 + 0x1a0)),
         lVar17 == 0)) goto LAB_7ffe9a4235e4;
      iVar9 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar17);
      puVar16 = (undefined8 *)FUN_7ffe999fca00(&uStack_88,&uStack_68,0);
      if (lVar14 == 0) goto LAB_7ffe9a4235e4;
      uStack_68 = *puVar16;
      fStack_60 = *(float *)(puVar16 + 1);
      uVar23 = 0;
      uVar15 = FUN_7ffe9a9f43c0(lVar14,fStack_60,(float)iVar12 / (float)iVar9,&uStack_68,0);
      FUN_7ffe9bd9f640(thisObject,uVar15,0);
    }
    if (action != (undefined *)0x0) {
      if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c972b60 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*(longlong *)action + 200) + -8 +
           (ulonglong)*(byte *)(_DAT_7ffe9c972b60 + 0x130) * 8) != _DAT_7ffe9c972b60)) {
        bVar20 = false;
      }
      else {
        bVar20 = true;
      }
      if (bVar20) {
        puVar18 = action;
      }
    }
    FUN_7ffe9a80c200(thisObject,puVar18,0);
    FUN_7ffe9a655ad0(thisObject,damageData,0);
  }
  else {
    plVar13 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if (((plVar13 == (longlong *)0x0) ||
        (lVar14 = (**(code **)(*plVar13 + 0x1c8))(plVar13,*(undefined8 *)(*plVar13 + 0x1d0)),
        lVar14 == 0)) || (*(longlong *)(lVar14 + 0x40) == 0)) goto LAB_7ffe9a4235e4;
    cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar14 + 0x40),0x28e,&plStack_a0,_DAT_7ffe9c934418);
    if (cVar4 != '\0') {
      if (plStack_a0 == (longlong *)0x0) goto LAB_7ffe9a4235e4;
      if (((*(byte *)(*plStack_a0 + 0x130) < *(byte *)(_DAT_7ffe9c93cd40 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*plStack_a0 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7ffe9c93cd40 + 0x130) * 8) != _DAT_7ffe9c93cd40)) ||
         (plStack_a0 == (longlong *)0x0)) {
        FUN_7ffe9996c950(plStack_a0);
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      iVar12 = 0;
      if ((char)plStack_a0[10] == '\0') {
        iVar12 = 1;
      }
    }
    plVar13 = *(longlong **)(thisObject + 0x30);
    bVar20 = true;
    if (plVar13 == (longlong *)0x0) goto LAB_7ffe9a4235e4;
    iVar9 = (**(code **)(*plVar13 + 0x178))(plVar13,*(undefined8 *)(*plVar13 + 0x180));
    fVar3 = _DAT_7ffe9c049b34;
    if ((iVar9 == 0) && (*(int *)(damageData + 0x18) == 5)) {
      bVar20 = false;
      plVar13 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar13 == (longlong *)0x0) ||
         (lVar14 = (**(code **)(*plVar13 + 0x198))(plVar13,*(undefined8 *)(*plVar13 + 0x1a0)),
         lVar14 == 0)) goto LAB_7ffe9a4235e4;
      iVar9 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar14);
      plVar13 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar13 == (longlong *)0x0) ||
         (lVar14 = (**(code **)(*plVar13 + 0x178))(plVar13,*(undefined8 *)(*plVar13 + 0x180)),
         lVar14 == 0)) goto LAB_7ffe9a4235e4;
      func_0x7ffe9a480d40(lVar14,(int)((float)iVar9 * fVar3),0,0);
    }
    plVar13 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar13 == (longlong *)0x0) ||
       (puVar18 = (undefined *)
                  (**(code **)(*plVar13 + 0x218))(plVar13,*(undefined8 *)(*plVar13 + 0x220)),
       puVar18 == (undefined *)0x0)) goto LAB_7ffe9a4235e4;
    puVar18 = GemCartBufferManager_GetGemCartBuffer(puVar18,0x26,(undefined *)0x0);
    if ((puVar18 == (undefined *)0x0) ||
       (iVar9 = GemCartBufferBase_GetValue(puVar18,(undefined *)0x2,(undefined *)0x0), iVar9 == 0))
    {
      if (bVar20) {
        uVar15 = *(undefined8 *)(*(longlong *)thisObject + 0x3d0);
        (**(code **)(*(longlong *)thisObject + 0x3c8))
                  (thisObject,actor,id,*(undefined4 *)(damageData + 0x84),uVar15);
        uVar23 = (undefined4)((ulonglong)uVar15 >> 0x20);
      }
    }
    else {
      plVar13 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar13 == (longlong *)0x0) ||
         (lVar14 = (**(code **)(*plVar13 + 0x198))(plVar13,*(undefined8 *)(*plVar13 + 0x1a0)),
         lVar14 == 0)) goto LAB_7ffe9a4235e4;
      iVar9 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar14);
      plVar13 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar13 == (longlong *)0x0) ||
         (lVar14 = (**(code **)(*plVar13 + 0x178))(plVar13,*(undefined8 *)(*plVar13 + 0x180)),
         lVar14 == 0)) goto LAB_7ffe9a4235e4;
      func_0x7ffe9a480d40(lVar14,(int)((float)iVar9 * fVar3),0,0);
      *(undefined4 *)(damageData + 0x8c) = 1;
      if (*(int *)(_DAT_7ffe9c92dfe0 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      uVar22 = FUN_7ffe9a4db1f0(1,0);
      *(undefined4 *)(damageData + 0x94) = uVar22;
      uVar22 = FUN_7ffe9a4db080(1,0);
      *(undefined4 *)(damageData + 0x98) = uVar22;
    }
    iVar9 = 0;
    if (cVar6 == '\0') {
      iVar9 = iVar12;
    }
    if (iVar9 != 0) {
      if (plStack_a0 == (longlong *)0x0) goto LAB_7ffe9a4235e4;
      if (((*(byte *)(*plStack_a0 + 0x130) < *(byte *)(_DAT_7ffe9c93cd40 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*plStack_a0 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7ffe9c93cd40 + 0x130) * 8) != _DAT_7ffe9c93cd40)) ||
         (plStack_a0 == (longlong *)0x0)) {
        FUN_7ffe9996c950(plStack_a0);
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      FUN_7ffe9a7a0830(plStack_a0,0);
      thisObject[0x40] = 0;
      thisObject[0x70] = 0;
      if (*(longlong *)(thisObject + 0x30) == 0) goto LAB_7ffe9a4235e4;
      func_0x7ffe9a7e0410(*(longlong *)(thisObject + 0x30),0);
      plVar13 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar13 == (longlong *)0x0) ||
         (lVar14 = (**(code **)(*plVar13 + 0x198))(plVar13,*(undefined8 *)(*plVar13 + 0x1a0)),
         lVar14 == 0)) goto LAB_7ffe9a4235e4;
      iVar12 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar14);
      plVar13 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar13 == (longlong *)0x0) ||
         (lVar14 = (**(code **)(*plVar13 + 0x178))(plVar13,*(undefined8 *)(*plVar13 + 0x180)),
         lVar14 == 0)) goto LAB_7ffe9a4235e4;
      func_0x7ffe9a480d40(lVar14,(int)((float)iVar12 * fVar3),0,0);
    }
  }
  cVar4 = (**(code **)(*(longlong *)thisObject + 0x188))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
  if (cVar4 == '\0') {
    FUN_7ffe9a7ab7c0(thisObject,0);
  }
  if (*(int *)(damageData + 0x8c) == 0) {
    FUN_7ffe9a41f620(thisObject,actor,damageData,0);
  }
  else {
    cVar4 = (**(code **)(*(longlong *)thisObject + 0x188))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
    if ((cVar4 == '\0') ||
       ((cVar4 = (**(code **)(*(longlong *)thisObject + 0x188))
                           (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400)),
        cVar4 != '\0' && (*(int *)(damageData + 0x8c) != 4)))) {
      if (*(longlong *)(thisObject + 0xe8) == 0) goto LAB_7ffe9a4235e4;
      uVar11 = FUN_7ffe99aaea90(*(longlong *)(thisObject + 0xe8),0);
      uVar22 = (undefined4)(in_stack_ffffffffffffff38 >> 0x20);
      if (uVar11 == 0xffffffff) {
        return;
      }
      uVar19 = (undefined1)uVar11;
      if (*(int *)(damageData + 0x8c) == 4) {
        if (*(longlong *)(thisObject + 0x20) == 0) goto LAB_7ffe9a4235e4;
        uVar15 = FUN_7ffe9bd98960(*(longlong *)(thisObject + 0x20),0);
        uVar26 = 0;
        cVar4 = FUN_7ffe99b1cb30(thisObject,action,uVar15,&uStack_78,0);
        uVar23 = (undefined4)((ulonglong)uVar26 >> 0x20);
        uVar22 = (undefined4)(in_stack_ffffffffffffff38 >> 0x20);
        if (cVar4 == '\0') goto LAB_7ffe9a423137;
        uVar28 = 0;
        uStack_68 = uStack_78;
        fStack_60 = fStack_70;
        uVar15 = CONCAT71((int7)((ulonglong)uVar26 >> 8),uVar19);
        cVar4 = FUN_7ffe9a41e510(thisObject,actor,damageData,&uStack_68,uVar15,0);
        uVar23 = (undefined4)((ulonglong)uVar15 >> 0x20);
      }
      else {
LAB_7ffe9a423137:
        in_stack_ffffffffffffff40 = CONCAT71((int7)(in_stack_ffffffffffffff40 >> 8),uVar19);
        in_stack_ffffffffffffff38 = CONCAT44(uVar22,*(undefined4 *)(damageData + 0x9c));
        uVar26 = CONCAT44(uVar28,*(undefined4 *)(damageData + 0x98));
        uVar15 = CONCAT44(uVar23,*(undefined4 *)(damageData + 0x94));
        cVar4 = FUN_7ffe99744fb0(0x10,thisObject,actor,*(undefined4 *)(damageData + 0x8c),uVar15,
                                 uVar26,in_stack_ffffffffffffff38,in_stack_ffffffffffffff40,
                                 damageData[0xa1]);
        uVar28 = (undefined4)((ulonglong)uVar26 >> 0x20);
        uVar23 = (undefined4)((ulonglong)uVar15 >> 0x20);
      }
      if (cVar4 == '\0') {
        if (*(longlong *)(thisObject + 0xe8) == 0) goto LAB_7ffe9a4235e4;
        FUN_7ffe99aaebf0(*(longlong *)(thisObject + 0xe8),uVar11 & 0xff,0);
      }
      else {
        plVar13 = (longlong *)
                  (**(code **)(*(longlong *)thisObject + 0x298))
                            (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
        if ((plVar13 == (longlong *)0x0) ||
           (lVar14 = (**(code **)(*plVar13 + 0x1e8))(plVar13,*(undefined8 *)(*plVar13 + 0x1f0)),
           lVar14 == 0)) goto LAB_7ffe9a4235e4;
        uVar23 = FUN_7ffe9a4db490(lVar14,*(undefined4 *)(damageData + 0x8c),0);
        *(undefined4 *)(damageData + 0x94) = uVar23;
        damageData[0xa0] = uVar19;
        lVar14 = *(longlong *)thisObject;
        (**(code **)(lVar14 + 0x358))
                  (thisObject,*(undefined4 *)(damageData + 0x8c),lVar14,(damageData[0x70] & 1) != 0,
                   *(undefined8 *)(lVar14 + 0x360));
        lVar14 = func_0x7ffe99940040(_DAT_7ffe9c92ee68);
        FUN_7ffe9bc60410(lVar14,0);
        puVar18 = (undefined *)(**(code **)(*(longlong *)thisObject + 0x298))(thisObject);
        bVar8 = GemCartBuffer_BerserkSuppressionBuff_Exemption(puVar18,(undefined *)0x0);
        if (bVar8 != 0) {
          if (lVar14 == 0) goto LAB_7ffe9a4235e4;
          FUN_7ffe9bc5ffd0(lVar14,0x2e,1,0);
          *(uint *)(damageData + 0x70) = *(uint *)(damageData + 0x70) | 0x20;
        }
        lVar17 = *(longlong *)thisObject;
        uVar15 = *(undefined8 *)(lVar17 + 0x350);
        (**(code **)(lVar17 + 0x348))
                  (thisObject,*(undefined4 *)(damageData + 0x8c),lVar17,lVar14,uVar15);
        uVar23 = (undefined4)((ulonglong)uVar15 >> 0x20);
      }
    }
  }
  plVar13 = *(longlong **)(thisObject + 0x30);
  if (plVar13 != (longlong *)0x0) {
    iVar12 = (**(code **)(*plVar13 + 0x178))(plVar13,*(undefined8 *)(*plVar13 + 0x180));
    if ((((iVar12 != 2) &&
         (cVar4 = func_0x7ffe9a4deb00(*(undefined4 *)(damageData + 0x8c),0), cVar4 == '\0')) &&
        (cVar4 = FUN_7ffe99b1ccd0(thisObject,0), cVar4 == '\0')) &&
       (*(int *)(damageData + 0x18) - 4U < 2)) {
      if (*(int *)(_DAT_7ffe9c92dfe0 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      uVar22 = FUN_7ffe9a4db1f0(1,0);
      uVar24 = FUN_7ffe9a4db080(1,0);
      in_stack_ffffffffffffff38 = in_stack_ffffffffffffff38 & 0xffffffff00000000;
      uVar27 = CONCAT44(uVar28,uVar24);
      uVar25 = CONCAT44(uVar23,uVar22);
      FUN_7ffe99744fb0(0x10,thisObject,actor,1,uVar25,uVar27,in_stack_ffffffffffffff38,
                       in_stack_ffffffffffffff40 & 0xffffffffffffff00,1);
      plVar13 = *(longlong **)(thisObject + 0x30);
      if (plVar13 == (longlong *)0x0) goto LAB_7ffe9a4235e4;
      iVar12 = (**(code **)(*plVar13 + 0x178))(plVar13,*(undefined8 *)(*plVar13 + 0x180));
      if (iVar12 == 0) {
        (**(code **)(*(longlong *)thisObject + 0x238))
                  (thisObject,actor,0x1b,_DAT_7ffe9c049b70,uVar25 & 0xffffffff00000000,
                   uVar27 & 0xffffffff00000000,in_stack_ffffffffffffff38 & 0xffffffffffffff00,1,
                   *(undefined8 *)(*(longlong *)thisObject + 0x240));
      }
    }
    lVar14 = FUN_7ffe9a42cc20(thisObject,0);
    if (lVar14 != 0) {
      FUN_7ffe9a4316c0(lVar14,*(undefined4 *)(damageData + 0x84),0);
      return;
    }
  }
LAB_7ffe9a4235e4:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

