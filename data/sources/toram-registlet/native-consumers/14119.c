
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void NormalAttackAction_OnInitialize
               (undefined *thisObject,undefined *actarAction,undefined *methodInfo)

{
  undefined4 *puVar1;
  code *pcVar2;
  float fVar3;
  char cVar4;
  byte bVar5;
  bool bVar6;
  undefined4 uVar7;
  int iVar8;
  uint uVar9;
  longlong lVar10;
  longlong *plVar11;
  undefined *puVar12;
  bool bVar13;
  float fVar14;
  undefined4 uVar15;
  undefined1 auVar16 [16];
  undefined1 auVar17 [16];
  float fVar18;
  longlong *aplStackX_10 [2];
  undefined8 uStackX_20;
  undefined8 extraout_XMM0_Qb;
  
  if (DAT_7ffe9cadde7d == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c949490);
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c946d38);
    FUN_7ffe9996d590(&DAT_7ffe9c94b460);
    FUN_7ffe9996d590(&DAT_7ffe9c96e9e0);
    DAT_7ffe9cadde7d = '\x01';
  }
  bVar13 = false;
  uStackX_20 = 0;
  aplStackX_10[0] = (longlong *)0x0;
  if (actarAction == (undefined *)0x0) goto LAB_7ffe9a496ca5;
  if (((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
      (*(longlong *)
        (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
        (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) ||
     (lVar10 = (**(code **)(*(longlong *)actarAction + 0x298))
                         (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0)),
     lVar10 == 0)) goto LAB_7ffe9a496ca5;
  uVar7 = FUN_7ffe9a4a1cc0(lVar10,0);
  *(undefined4 *)(thisObject + 0x30) = uVar7;
  uVar7 = FUN_7ffe9a4adfc0(actarAction,&uStackX_20,0);
  *(undefined4 *)(thisObject + 0xfc) = uVar7;
  uVar7 = FUN_7ffe9a4ade20(actarAction,0);
  *(undefined4 *)(thisObject + 0x150) = uVar7;
  uVar7 = FUN_7ffe9a4adf80(uStackX_20,0);
  *(undefined4 *)(thisObject + 0x20) = uVar7;
  plVar11 = (longlong *)
            (**(code **)(*(longlong *)actarAction + 0x298))
                      (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
  if ((plVar11 == (longlong *)0x0) ||
     (lVar10 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
     lVar10 == 0)) goto LAB_7ffe9a496ca5;
  cVar4 = FUN_7ffe9a7cbb30(lVar10,0x29,aplStackX_10,0);
  if ((cVar4 != '\0') && (*(int *)(thisObject + 0xfc) - 10U < 2)) {
    if (aplStackX_10[0] == (longlong *)0x0) goto LAB_7ffe9a496ca5;
    iVar8 = (**(code **)(*aplStackX_10[0] + 0x1f8))
                      (aplStackX_10[0],0x32,*(undefined8 *)(*aplStackX_10[0] + 0x200));
    plVar11 = (longlong *)
              (**(code **)(*(longlong *)actarAction + 0x298))
                        (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
    if ((plVar11 == (longlong *)0x0) ||
       (puVar12 = (undefined *)
                  (**(code **)(*plVar11 + 0x218))(plVar11,*(undefined8 *)(*plVar11 + 0x220)),
       puVar12 == (undefined *)0x0)) goto LAB_7ffe9a496ca5;
    bVar5 = GemCartBufferManager_ContainsBuffer(puVar12,0x12e,(undefined *)0x0);
    if ((bVar5 == 0) && (iVar8 == 1)) {
      uVar9 = *(uint *)(thisObject + 0x104) | 2;
    }
    else {
      uVar9 = *(uint *)(thisObject + 0x104) | 1;
    }
    *(uint *)(thisObject + 0x104) = uVar9;
  }
  plVar11 = (longlong *)
            (**(code **)(*(longlong *)actarAction + 0x298))
                      (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
  if ((plVar11 == (longlong *)0x0) ||
     (lVar10 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
     lVar10 == 0)) goto LAB_7ffe9a496ca5;
  cVar4 = FUN_7ffe9a7cbb30(lVar10,0x52,aplStackX_10);
  if (cVar4 != '\0') {
    if (aplStackX_10[0] == (longlong *)0x0) goto LAB_7ffe9a496ca5;
    if (((*(byte *)(*aplStackX_10[0] + 0x130) < *(byte *)(_DAT_7ffe9c96e9e0 + 0x130)) ||
        (*(longlong *)
          (*(longlong *)(*aplStackX_10[0] + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c96e9e0 + 0x130) * 8) != _DAT_7ffe9c96e9e0)) ||
       (aplStackX_10[0] == (longlong *)0x0)) {
      FUN_7ffe9996c950(aplStackX_10[0]);
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    if ((char)aplStackX_10[0][9] != '\0') {
      *(uint *)(thisObject + 0x104) = *(uint *)(thisObject + 0x104) | 0x10;
    }
  }
  plVar11 = (longlong *)
            (**(code **)(*(longlong *)actarAction + 0x298))
                      (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
  if ((plVar11 == (longlong *)0x0) ||
     (lVar10 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
     lVar10 == 0)) goto LAB_7ffe9a496ca5;
  cVar4 = FUN_7ffe9a7c6d00(lVar10,299,0);
  if (cVar4 != '\0') {
    *(uint *)(thisObject + 0x104) = *(uint *)(thisObject + 0x104) | 0x400;
    uVar7 = func_0x7ffe99a4d6a0();
    *(undefined4 *)(thisObject + 0x20) = uVar7;
  }
  plVar11 = (longlong *)
            (**(code **)(*(longlong *)actarAction + 0x298))
                      (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
  if ((plVar11 == (longlong *)0x0) ||
     (lVar10 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
     lVar10 == 0)) goto LAB_7ffe9a496ca5;
  cVar4 = FUN_7ffe9a7cbb30(lVar10,0x10b,aplStackX_10,0);
  if (cVar4 != '\0') {
    plVar11 = (longlong *)
              (**(code **)(*(longlong *)actarAction + 0x298))
                        (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
    if ((plVar11 == (longlong *)0x0) ||
       (lVar10 = (**(code **)(*plVar11 + 0x1f8))(plVar11,*(undefined8 *)(*plVar11 + 0x200)),
       lVar10 == 0)) goto LAB_7ffe9a496ca5;
    iVar8 = FUN_7ffe99c08f50(lVar10,0);
    if (iVar8 == 0x11) {
      auVar16._0_8_ = func_0x7ffe99a4d6a0();
      auVar16._8_8_ = extraout_XMM0_Qb;
      if (*(float *)(thisObject + 0x20) <= (float)auVar16._0_8_) {
        auVar17._4_12_ = auVar16._4_12_;
        auVar17._0_4_ = *(float *)(thisObject + 0x20);
        auVar16._0_8_ = auVar17._0_8_;
      }
      *(uint *)(thisObject + 0x104) = *(uint *)(thisObject + 0x104) | 0x2000;
      *(int *)(thisObject + 0x20) = (int)auVar16._0_8_;
    }
  }
  iVar8 = 0;
  if ((thisObject[0x104] & 3) == 0) {
    plVar11 = (longlong *)
              (**(code **)(*(longlong *)actarAction + 0x298))
                        (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
    if ((plVar11 == (longlong *)0x0) ||
       (puVar12 = (undefined *)
                  (**(code **)(*plVar11 + 0x218))(plVar11,*(undefined8 *)(*plVar11 + 0x220)),
       puVar12 == (undefined *)0x0)) goto LAB_7ffe9a496ca5;
    bVar5 = GemCartBufferManager_ContainsBuffer(puVar12,0xcf,(undefined *)0x0);
    if (bVar5 != 0) goto LAB_7ffe9a49680d;
    plVar11 = (longlong *)
              (**(code **)(*(longlong *)actarAction + 0x298))
                        (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
    if (((plVar11 == (longlong *)0x0) ||
        (lVar10 = (**(code **)(*plVar11 + 0x1b8))(plVar11,*(undefined8 *)(*plVar11 + 0x1c0)),
        lVar10 == 0)) || (*(longlong *)(lVar10 + 0x68) == 0)) goto LAB_7ffe9a496ca5;
    cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar10 + 0x68),0x6b,thisObject + 0x138,_DAT_7ffe9c935bd0)
    ;
    if (cVar4 == '\0') goto LAB_7ffe9a49680d;
    cVar4 = FUN_7ffe9a4ad740(actarAction,0xe);
    if (cVar4 == '\0') {
      cVar4 = FUN_7ffe9a4ad740(actarAction,0xf);
      if (cVar4 != '\0') {
        iVar8 = 0xf;
      }
    }
    else {
      iVar8 = 0xe;
    }
    lVar10 = *(longlong *)(thisObject + 0x138);
    *(undefined4 *)(thisObject + 0x128) = *(undefined4 *)(thisObject + 0x20);
    fVar14 = _DAT_7ffe9c049ce0;
    if ((lVar10 == 0) || (*(longlong *)(lVar10 + 0x10) == 0)) goto LAB_7ffe9a496ca5;
    fVar18 = (float)*(byte *)(*(longlong *)(lVar10 + 0x10) + 0x18) * _DAT_7ffe9c049b4c +
             _DAT_7ffe9c049ce0;
    *(float *)(thisObject + 0x20) = fVar18;
    if (*(longlong *)(lVar10 + 0x10) == 0) goto LAB_7ffe9a496ca5;
    fVar14 = (float)*(byte *)(*(longlong *)(lVar10 + 0x10) + 0x18) * fVar14;
    *(float *)(thisObject + 300) = fVar14;
    fVar3 = _DAT_7ffe9c049dd0;
    if (iVar8 == 0xe) {
      *(float *)(thisObject + 0x20) = fVar18 + _DAT_7ffe9c049b70;
LAB_7ffe9a4967cd:
      *(float *)(thisObject + 300) = fVar14 + fVar3;
    }
    else {
      fVar3 = _DAT_7ffe9c049f0c;
      if (iVar8 == 0xf) goto LAB_7ffe9a4967cd;
    }
    *(float *)(thisObject + 300) = *(float *)(thisObject + 300) / _DAT_7ffe9c049cfc;
    fVar14 = (float)func_0x7ffe99a4d6a0(lVar10,0);
    if (fVar14 <= *(float *)(thisObject + 0x128)) {
      fVar14 = *(float *)(thisObject + 0x128);
    }
    *(float *)(thisObject + 0x20) = fVar14;
  }
LAB_7ffe9a49680d:
  puVar1 = (undefined4 *)(thisObject + 0x124);
  *puVar1 = 1;
  iVar8 = FUN_7ffe9bda4580(0,2);
  if (iVar8 == 0) {
    *(uint *)(thisObject + 0x104) = *(uint *)(thisObject + 0x104) | 0x80;
  }
  uVar7 = func_0x7ffe9a495f70(*(undefined4 *)(thisObject + 0xfc),*(undefined4 *)(thisObject + 0x150)
                              ,iVar8 == 0,puVar1,0);
  if (*(int *)(thisObject + 0xfc) == 8) {
    auVar16._0_8_ = func_0x7ffe99940040(_DAT_7ffe9c946d38);
    FUN_7ffe9a7c1be0(auVar16._0_8_,8,0xbfe3891,0);
    *(undefined8 *)(thisObject + 0x158) = auVar16._0_8_;
    il2cpp_write_barrier_0();
    *(undefined2 *)(thisObject + 0x72) = 0x101;
  }
  cVar4 = func_0x7ffe9a4ad2d0(thisObject,0x2000,0);
  if (cVar4 != '\0') {
    uVar7 = 0xc0bb1c8;
    *puVar1 = 3;
    *(undefined2 *)(thisObject + 0x72) = 0;
  }
  auVar16._0_8_ =
       (**(code **)(*(longlong *)actarAction + 0x298))
                 (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
  cVar4 = FUN_7ffe9a791c30(auVar16._0_8_,thisObject + 0x178,thisObject + 0x17c,0);
  if (cVar4 != '\0') {
    if (*(longlong *)(thisObject + 0x138) != 0) {
      *(longlong *)(thisObject + 0x138) = 0;
      il2cpp_write_barrier_0();
      thisObject[0x130] = 0;
      *(undefined8 *)(thisObject + 0x128) = 0;
    }
    *(uint *)(thisObject + 0x104) = *(uint *)(thisObject + 0x104) | 0x8000;
    *(uint *)(thisObject + 0x108) = *(uint *)(thisObject + 0x108) & 0xfffffffd;
    thisObject[0x176] = 1;
    thisObject[0x140] = 1;
    auVar16._0_8_ = uStackX_20;
    if (*(int *)(thisObject + 0xfc) != 8) {
      plVar11 = (longlong *)
                (**(code **)(*(longlong *)actarAction + 0x298))
                          (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
      if (((plVar11 == (longlong *)0x0) ||
          (lVar10 = (**(code **)(*plVar11 + 0x1f8))(plVar11,*(undefined8 *)(*plVar11 + 0x200)),
          lVar10 == 0)) || (*(longlong *)(lVar10 + 0x20) == 0)) goto LAB_7ffe9a496ca5;
      iVar8 = func_0x7ffe99c1ed70(*(longlong *)(lVar10 + 0x20),0);
      auVar16._0_8_ = uStackX_20;
      if (iVar8 == 8) {
        plVar11 = (longlong *)
                  (**(code **)(*(longlong *)actarAction + 0x298))
                            (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
        if ((plVar11 == (longlong *)0x0) ||
           (lVar10 = (**(code **)(*plVar11 + 0x1f8))(plVar11,*(undefined8 *)(*plVar11 + 0x200)),
           lVar10 == 0)) goto LAB_7ffe9a496ca5;
        auVar16._0_8_ = FUN_7ffe99c08fe0(lVar10,0);
      }
    }
    uVar15 = FUN_7ffe9a4adf80(auVar16._0_8_,0);
    *(undefined4 *)(thisObject + 0x20) = uVar15;
    *(uint *)(thisObject + 0x104) = *(uint *)(thisObject + 0x104) & 0xfffffe7f;
    iVar8 = *(int *)(thisObject + 0x178);
    if (iVar8 == 0) {
      uVar7 = 0xbfe6f40;
      *puVar1 = 2;
      uVar9 = *(uint *)(thisObject + 0x104) | 0x80;
LAB_7ffe9a496a54:
      *(uint *)(thisObject + 0x104) = uVar9;
    }
    else if (iVar8 == 1) {
      uVar7 = 0xbfe7328;
      *puVar1 = 2;
    }
    else if (iVar8 == 2) {
      uVar7 = 0xbfe7710;
      *puVar1 = 3;
      uVar9 = *(uint *)(thisObject + 0x104) | 0x100;
      goto LAB_7ffe9a496a54;
    }
  }
  if ((*(uint *)(thisObject + 0x104) & 3) != 0) {
    iVar8 = *(int *)(thisObject + 0xfc);
    *puVar1 = 4;
    bVar6 = bVar13;
    if (iVar8 == 10) {
      bVar13 = *(int *)(thisObject + 0x150) == 10;
      bVar6 = !bVar13;
      if (!bVar6) goto LAB_7ffe9a496a8d;
      uVar7 = 0x34008;
    }
    else {
LAB_7ffe9a496a8d:
      if (iVar8 == 0xb) {
        uVar7 = 0x4c6a8;
      }
      else if (bVar13) {
        *puVar1 = 7;
        uVar7 = 0xf7508;
      }
    }
    if ((*(uint *)(thisObject + 0x104) & 2) != 0) {
      *puVar1 = 3;
      if (bVar6 || bVar13) {
        uVar7 = 0x320cb;
      }
      else if (iVar8 == 0xb) {
        uVar7 = 0x4a76a;
      }
      thisObject[0x154] = 0;
    }
  }
  auVar16._0_8_ = func_0x7ffe99940040(_DAT_7ffe9c94b460);
  FUN_7ffe9a9002e0(auVar16._0_8_,uVar7,0);
  *(undefined8 *)(thisObject + 0x58) = auVar16._0_8_;
  il2cpp_write_barrier_0();
  if ((*(longlong *)(thisObject + 0x58) == 0) ||
     (lVar10 = *(longlong *)(*(longlong *)(thisObject + 0x58) + 0x50), lVar10 == 0))
  goto LAB_7ffe9a496ca5;
  FUN_7ffe9ad10e00(lVar10,7,*(undefined4 *)(thisObject + 0x30),_DAT_7ffe9c949490);
  if ((thisObject[0x104] & 2) == 0) {
    plVar11 = (longlong *)
              (**(code **)(*(longlong *)actarAction + 0x298))
                        (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
    if (plVar11 == (longlong *)0x0) goto LAB_7ffe9a496ca5;
    lVar10 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
    if (lVar10 == 0) goto LAB_7ffe9a496ca5;
    FUN_7ffe9a7cb960(lVar10,0x2a6,1,0);
  }
  auVar16._0_8_ =
       (**(code **)(*(longlong *)actarAction + 0x298))
                 (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
  uVar7 = FUN_7ffe9a4aabb0(auVar16._0_8_,0);
  *(undefined4 *)(thisObject + 0x78) = uVar7;
  plVar11 = (longlong *)
            (**(code **)(*(longlong *)actarAction + 0x298))
                      (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
  if ((plVar11 != (longlong *)0x0) &&
     (lVar10 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
     lVar10 != 0)) {
    FUN_7ffe9a7cb960(lVar10,0x2a6,0,0);
    if ((*(int *)(thisObject + 0xfc) == 0xc) && (*(int *)(thisObject + 0x150) == 8)) {
      plVar11 = (longlong *)
                (**(code **)(*(longlong *)actarAction + 0x298))
                          (actarAction,*(undefined8 *)(*(longlong *)actarAction + 0x2a0));
      if ((((plVar11 == (longlong *)0x0) ||
           (lVar10 = (**(code **)(*plVar11 + 0x1f8))(plVar11,*(undefined8 *)(*plVar11 + 0x200)),
           lVar10 == 0)) || (lVar10 = FUN_7ffe99c08fe0(lVar10,0), lVar10 == 0)) ||
         (*(longlong *)(lVar10 + 0x28) == 0)) goto LAB_7ffe9a496ca5;
      *(uint *)(thisObject + 0x28) = (uint)*(byte *)(*(longlong *)(lVar10 + 0x28) + 0x41);
    }
    if ((*(int *)(thisObject + 0xfc) == 8) && (thisObject[0x176] == '\0')) {
      *(uint *)(thisObject + 0x108) = *(uint *)(thisObject + 0x108) | 2;
      thisObject[0x140] = 1;
    }
    return;
  }
LAB_7ffe9a496ca5:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

