
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobAttackBase_CalcLastDamage
              (undefined *self,undefined *mobAction,undefined *playerAction,int damage,
              undefined *hitReactionType,undefined *allowBuffChanges,undefined *methodInfo)

{
  undefined *skillMaster;
  code *pcVar1;
  bool bVar2;
  float fVar3;
  char cVar4;
  byte bVar5;
  int iVar6;
  int iVar7;
  undefined4 uVar8;
  int iVar9;
  int iVar10;
  longlong *plVar11;
  longlong lVar12;
  longlong *plVar13;
  longlong *plVar14;
  undefined8 *puVar15;
  undefined8 uVar16;
  undefined *puVar17;
  ulonglong *puVar18;
  ushort uVar19;
  undefined8 uVar20;
  float fVar21;
  double dVar22;
  float fVar23;
  float fVar24;
  longlong *plStackX_18;
  int iStackX_20;
  longlong *plStack_a8;
  undefined8 uStack_a0;
  ulonglong uStack_98;
  float fStack_90;
  undefined1 auStack_88 [8];
  float fStack_80;
  
  iStackX_20 = damage;
  if (DAT_7ffe9cadd7cd == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92d838);
    FUN_7ffe9996d590(&DAT_7ffe9c935b00);
    FUN_7ffe9996d590(&DAT_7ffe9c9368c8);
    FUN_7ffe9996d590(&DAT_7ffe9c9442f0);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c90ea00);
    FUN_7ffe9996d590(&DAT_7ffe9c917ea0);
    FUN_7ffe9996d590(&DAT_7ffe9c928ba0);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c946798);
    FUN_7ffe9996d590(&DAT_7ffe9c954730);
    FUN_7ffe9996d590(&DAT_7ffe9c954998);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c91a2e8);
    FUN_7ffe9996d590(&DAT_7ffe9c8ed488);
    FUN_7ffe9996d590(&DAT_7ffe9c8ee328);
    FUN_7ffe9996d590(&DAT_7ffe9c8ee3f8);
    FUN_7ffe9996d590(&DAT_7ffe9c8eeb48);
    FUN_7ffe9996d590(&DAT_7ffe9c8feb30);
    FUN_7ffe9996d590(&DAT_7ffe9c904080);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c90f9b8);
    FUN_7ffe9996d590(&DAT_7ffe9c9228b0);
    FUN_7ffe9996d590(&DAT_7ffe9c94c0a0);
    FUN_7ffe9996d590(&DAT_7ffe9c955db8);
    FUN_7ffe9996d590(&DAT_7ffe9c9632c0);
    FUN_7ffe9996d590(&DAT_7ffe9c945d08);
    DAT_7ffe9cadd7cd = '\x01';
  }
  plStackX_18 = (longlong *)0x0;
  plStack_a8 = (longlong *)0x0;
  uStack_a0 = 0;
  if (playerAction == (undefined *)0x0) goto LAB_7ffe9a372ee9;
  plVar11 = (longlong *)
            (**(code **)(*(longlong *)playerAction + 0x298))
                      (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  fVar24 = _DAT_7ffe9c049b18;
  if (mobAction != (undefined *)0x0) {
    lVar12 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,mobAction);
    if (lVar12 == 0) goto LAB_7ffe9a372ee9;
    cVar4 = FUN_7ffe9a4daa60(lVar12,0xf,0);
    if (cVar4 != '\0') {
      fVar24 = _DAT_7ffe9c049e54;
    }
    lVar12 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,mobAction);
    if (lVar12 == 0) goto LAB_7ffe9a372ee9;
    cVar4 = FUN_7ffe9a4daa60(lVar12,0x1e);
    if (cVar4 != '\0') {
      lVar12 = FUN_7ffe99742ec0(10,_DAT_7ffe9c9724e0,mobAction);
      if (lVar12 == 0) goto LAB_7ffe9a372ee9;
      plVar13 = (longlong *)FUN_7ffe9a4dae70(lVar12,0x1e);
      if (plVar13 != (longlong *)0x0) {
        if ((*(byte *)(_DAT_7ffe9c92d838 + 0x130) <= *(byte *)(*plVar13 + 0x130)) &&
           (*(longlong *)
             (*(longlong *)(*plVar13 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c92d838 + 0x130) * 8) == _DAT_7ffe9c92d838)) {
          plVar14 = (longlong *)FUN_7ffe9ab6e260(playerAction,_DAT_7ffe9c9442f0);
          if (plVar14 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
          lVar12 = *plVar14;
          uVar19 = 0;
          if (*(ushort *)(lVar12 + 0x12e) != 0) {
            do {
              if (*(longlong *)(*(longlong *)(lVar12 + 0xb0) + (ulonglong)uVar19 * 0x10) ==
                  _DAT_7ffe9c946798) {
                puVar15 = (undefined8 *)
                          ((longlong)
                           (*(int *)(*(longlong *)(lVar12 + 0xb0) + 8 + (ulonglong)uVar19 * 0x10) +
                           1) * 0x10 + 0x138 + lVar12);
                goto LAB_7ffe9a3707a9;
              }
              uVar19 = uVar19 + 1;
            } while (uVar19 < *(ushort *)(lVar12 + 0x12e));
          }
          puVar15 = (undefined8 *)FUN_7ffe998ce540(plVar14,_DAT_7ffe9c946798,1);
LAB_7ffe9a3707a9:
          uStack_a0 = (*(code *)*puVar15)(plVar14,puVar15[1]);
          cVar4 = func_0x7ffe9bb9e750(&uStack_a0,(char)plVar13[5],
                                      *(undefined4 *)((longlong)plVar13 + 0x2c),0);
          if (cVar4 == '\0') {
            fVar24 = fVar24 + _DAT_7ffe9c049ec4;
          }
        }
      }
    }
    damage = (int)((float)damage * fVar24);
    iStackX_20 = damage;
  }
  iVar9 = 0;
  fVar24 = 0.0;
  if (((plVar11 == (longlong *)0x0) ||
      (lVar12 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
      lVar12 == 0)) || (*(longlong *)(lVar12 + 0x50) == 0)) goto LAB_7ffe9a372ee9;
  cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x50),0xea,&plStackX_18,_DAT_7ffe9c934418);
  fVar3 = _DAT_7ffe9c049cfc;
  if (cVar4 != '\0') {
    lVar12 = (**(code **)(*plVar11 + 0x198))(plVar11,*(undefined8 *)(*plVar11 + 0x1a0));
    if ((lVar12 == 0) ||
       (iVar6 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar12), plStackX_18 == (longlong *)0x0))
    goto LAB_7ffe9a372ee9;
    iVar7 = (**(code **)(*plStackX_18 + 0x1f8))
                      (plStackX_18,0x28,*(undefined8 *)(*plStackX_18 + 0x200));
    if (damage <= (int)(((float)iVar7 / fVar3) * (float)iVar6)) {
      if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
      iVar6 = (**(code **)(*plStackX_18 + 0x1f8))
                        (plStackX_18,5,*(undefined8 *)(*plStackX_18 + 0x200));
      if (0.0 < (float)iVar6) {
        iVar9 = 0xea;
        fVar24 = (float)iVar6;
      }
    }
  }
  lVar12 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
  if ((lVar12 == 0) || (*(longlong *)(lVar12 + 0x50) == 0)) goto LAB_7ffe9a372ee9;
  cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x50),0x445,&plStackX_18,_DAT_7ffe9c934418);
  if (cVar4 != '\0') {
    if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
    if (((*(byte *)(*plStackX_18 + 0x130) < *(byte *)(_DAT_7ffe9c928ba0 + 0x130)) ||
        (*(longlong *)
          (*(longlong *)(*plStackX_18 + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c928ba0 + 0x130) * 8) != _DAT_7ffe9c928ba0)) ||
       (plStackX_18 == (longlong *)0x0)) {
      FUN_7ffe9996c950(plStackX_18);
      pcVar1 = (code *)swi(3);
      iVar9 = (*pcVar1)();
      return iVar9;
    }
    cVar4 = FUN_7ffe9a7900f0(plStackX_18,0);
    if (cVar4 != '\0') {
      if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
      iVar6 = (**(code **)(*plStackX_18 + 0x1f8))
                        (plStackX_18,5,*(undefined8 *)(*plStackX_18 + 0x200));
      if (fVar24 < (float)iVar6) {
        iVar9 = 0x445;
        fVar24 = (float)iVar6;
      }
    }
  }
  plVar13 = (longlong *)0x0;
  lVar12 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
  if ((lVar12 == 0) || (*(longlong *)(lVar12 + 0x50) == 0)) goto LAB_7ffe9a372ee9;
  cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x50),0x3c6,&plStackX_18,_DAT_7ffe9c934418);
  if ((cVar4 != '\0') &&
     (cVar4 = (**(code **)(*(longlong *)self + 0x568))
                        (self,*(undefined8 *)(*(longlong *)self + 0x570)), cVar4 == '\0')) {
    if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
    iVar6 = (**(code **)(*plStackX_18 + 0x1f8))(plStackX_18,5,*(undefined8 *)(*plStackX_18 + 0x200))
    ;
    if (fVar24 < (float)iVar6) {
      iVar9 = 0x3c6;
      fVar24 = (float)iVar6;
    }
  }
  lVar12 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
  if ((lVar12 == 0) || (*(longlong *)(lVar12 + 0x50) == 0)) goto LAB_7ffe9a372ee9;
  cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x50),0x486,&plStackX_18,_DAT_7ffe9c934418);
  if (cVar4 != '\0') {
    if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
    if (((*(byte *)(*plStackX_18 + 0x130) < *(byte *)(_DAT_7ffe9c917ea0 + 0x130)) ||
        (*(longlong *)
          (*(longlong *)(*plStackX_18 + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c917ea0 + 0x130) * 8) != _DAT_7ffe9c917ea0)) ||
       (plStackX_18 == (longlong *)0x0)) {
      FUN_7ffe9996c950(plStackX_18);
      pcVar1 = (code *)swi(3);
      iVar9 = (*pcVar1)();
      return iVar9;
    }
    if (*(char *)((longlong)plStackX_18 + 0x2c) == '\0') {
      cVar4 = (**(code **)(*(longlong *)self + 0x568))
                        (self,*(undefined8 *)(*(longlong *)self + 0x570));
      if (cVar4 == '\0') {
        if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
        uVar20 = 5;
      }
      else {
        if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
        if (((*(byte *)(*plStackX_18 + 0x130) < *(byte *)(_DAT_7ffe9c917ea0 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*plStackX_18 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c917ea0 + 0x130) * 8) != _DAT_7ffe9c917ea0)) ||
           (plStackX_18 == (longlong *)0x0)) {
          FUN_7ffe9996c950(plStackX_18);
          pcVar1 = (code *)swi(3);
          iVar9 = (*pcVar1)();
          return iVar9;
        }
        cVar4 = FUN_7ffe9a78e7a0(plStackX_18,0);
        if (cVar4 == '\0') goto LAB_7ffe9a370c08;
        if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
        uVar20 = 6;
      }
      iVar6 = (**(code **)(*plStackX_18 + 0x1f8))
                        (plStackX_18,uVar20,*(undefined8 *)(*plStackX_18 + 0x200));
      if (fVar24 < (float)iVar6) {
        iVar9 = 0x486;
        fVar24 = (float)iVar6;
      }
    }
  }
LAB_7ffe9a370c08:
  lVar12 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
  if ((lVar12 == 0) || (*(longlong *)(lVar12 + 0x50) == 0)) goto LAB_7ffe9a372ee9;
  cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x50),0x91,&plStackX_18,_DAT_7ffe9c934418);
  if (cVar4 != '\0') {
    if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
    if (((*(byte *)(*plStackX_18 + 0x130) < *(byte *)(_DAT_7ffe9c9368c8 + 0x130)) ||
        (*(longlong *)
          (*(longlong *)(*plStackX_18 + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c9368c8 + 0x130) * 8) != _DAT_7ffe9c9368c8)) ||
       (plStackX_18 == (longlong *)0x0)) {
      FUN_7ffe9996c950(plStackX_18);
      pcVar1 = (code *)swi(3);
      iVar9 = (*pcVar1)();
      return iVar9;
    }
    if ((char)plStackX_18[5] != '\0') {
      lVar12 = (**(code **)(*plVar11 + 0x178))(plVar11,*(undefined8 *)(*plVar11 + 0x180));
      if (lVar12 == 0) goto LAB_7ffe9a372ee9;
      fVar23 = (float)(*(int *)(lVar12 + 0x18) / 100) * _DAT_7ffe9c049d14;
      fVar21 = _DAT_7ffe9c049d94;
      if (fVar23 <= _DAT_7ffe9c049d94) {
        fVar21 = fVar23;
      }
      if (fVar24 < fVar21) {
        iVar9 = 0x91;
        fVar24 = fVar21;
      }
    }
  }
  lVar12 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
  if (lVar12 == 0) goto LAB_7ffe9a372ee9;
  cVar4 = FUN_7ffe9a7cbb30(lVar12,0x74,&plStackX_18);
  if ((cVar4 != '\0') &&
     (cVar4 = (**(code **)(*(longlong *)self + 0x568))
                        (self,*(undefined8 *)(*(longlong *)self + 0x570)), cVar4 == '\0')) {
    lVar12 = (**(code **)(*plVar11 + 0x1f8))(plVar11,*(undefined8 *)(*plVar11 + 0x200));
    if ((lVar12 == 0) || (*(longlong *)(lVar12 + 0x18) == 0)) goto LAB_7ffe9a372ee9;
    iVar6 = func_0x7ffe99c1ed70(*(longlong *)(lVar12 + 0x18),0);
    if ((iVar6 == 0xe) || (iVar6 == 0xf)) {
      if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
      iVar6 = (**(code **)(*plStackX_18 + 0x1f8))
                        (plStackX_18,5,*(undefined8 *)(*plStackX_18 + 0x200));
      if (fVar24 < (float)iVar6) {
        iVar9 = 0x74;
        fVar24 = (float)iVar6;
      }
    }
  }
  lVar12 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
  if (lVar12 == 0) goto LAB_7ffe9a372ee9;
  cVar4 = FUN_7ffe9a7cbb30(lVar12,0x10a,&plStackX_18,0);
  if (cVar4 != '\0') {
    if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
    iVar6 = (**(code **)(*plStackX_18 + 0x1f8))(plStackX_18,5,*(undefined8 *)(*plStackX_18 + 0x200))
    ;
    if (fVar24 < (float)iVar6) {
      iVar9 = 0x10a;
      fVar24 = (float)iVar6;
    }
  }
  lVar12 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
  if (lVar12 == 0) goto LAB_7ffe9a372ee9;
  cVar4 = FUN_7ffe9a7cbb30(lVar12,0x22e,&plStackX_18,0);
  if (cVar4 != '\0') {
    if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
    if (((*(byte *)(*plStackX_18 + 0x130) < *(byte *)(_DAT_7ffe9c8feb30 + 0x130)) ||
        (*(longlong *)
          (*(longlong *)(*plStackX_18 + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c8feb30 + 0x130) * 8) != _DAT_7ffe9c8feb30)) ||
       (plStackX_18 == (longlong *)0x0)) {
      FUN_7ffe9996c950(plStackX_18);
      pcVar1 = (code *)swi(3);
      iVar9 = (*pcVar1)();
      return iVar9;
    }
    cVar4 = func_0x7ffe99ad7b20(plStackX_18,2);
    if (cVar4 != '\0') {
      if (self != (undefined *)0x0) {
        lVar12 = *(longlong *)self;
        if (((*(byte *)(_DAT_7ffe9c8ed488 + 0x130) <= *(byte *)(lVar12 + 0x130)) &&
            (*(longlong *)
              (*(longlong *)(lVar12 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c8ed488 + 0x130) * 8) == _DAT_7ffe9c8ed488)) ||
           ((*(byte *)(_DAT_7ffe9c8ee3f8 + 0x130) <= *(byte *)(lVar12 + 0x130) &&
            (*(longlong *)
              (*(longlong *)(lVar12 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c8ee3f8 + 0x130) * 8) == _DAT_7ffe9c8ee3f8))))
        goto LAB_7ffe9a370f83;
      }
      if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
      iVar6 = (**(code **)(*plStackX_18 + 0x1f8))
                        (plStackX_18,5,*(undefined8 *)(*plStackX_18 + 0x200));
      if (fVar24 < (float)iVar6) {
        iVar9 = 0x22e;
        fVar24 = (float)iVar6;
      }
    }
  }
LAB_7ffe9a370f83:
  lVar12 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
  if (lVar12 == 0) goto LAB_7ffe9a372ee9;
  cVar4 = FUN_7ffe9a7cbb30(lVar12,0x36a,&plStackX_18,0);
  if (cVar4 != '\0') {
    if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
    iVar6 = (**(code **)(*plStackX_18 + 0x1f8))(plStackX_18,5,*(undefined8 *)(*plStackX_18 + 0x200))
    ;
    if (fVar24 < (float)iVar6) {
      iVar9 = 0x36a;
      fVar24 = (float)iVar6;
    }
  }
  lVar12 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
  if (lVar12 == 0) goto LAB_7ffe9a372ee9;
  cVar4 = FUN_7ffe9a7cbb30(lVar12,0x38);
  if (cVar4 != '\0') {
    if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
    if (((*(byte *)(*plStackX_18 + 0x130) < *(byte *)(_DAT_7ffe9c90f9b8 + 0x130)) ||
        (*(longlong *)
          (*(longlong *)(*plStackX_18 + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c90f9b8 + 0x130) * 8) != _DAT_7ffe9c90f9b8)) ||
       (plStackX_18 == (longlong *)0x0)) {
      FUN_7ffe9996c950(plStackX_18);
      pcVar1 = (code *)swi(3);
      iVar9 = (*pcVar1)();
      return iVar9;
    }
    cVar4 = func_0x7ffe9a79d550(plStackX_18,0);
    if (cVar4 != '\0') {
      if ((*(longlong *)(playerAction + 0x30) == 0) ||
         (plVar14 = *(longlong **)(*(longlong *)(playerAction + 0x30) + 0x30),
         plVar14 == (longlong *)0x0)) goto LAB_7ffe9a372ee9;
      plVar14 = (longlong *)(**(code **)(*plVar14 + 0x188))(plVar14,*(undefined8 *)(*plVar14 + 400))
      ;
      if (plVar14 != (longlong *)0x0) {
        if ((*(byte *)(_DAT_7ffe9c904080 + 0x130) <= *(byte *)(*plVar14 + 0x130)) &&
           (*(longlong *)
             (*(longlong *)(*plVar14 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c904080 + 0x130) * 8) == _DAT_7ffe9c904080)) {
          if ((*(longlong *)(playerAction + 0x30) == 0) ||
             ((plVar14 = *(longlong **)(*(longlong *)(playerAction + 0x30) + 0x30),
              plVar14 == (longlong *)0x0 ||
              (plVar14 = (longlong *)
                         (**(code **)(*plVar14 + 0x188))(plVar14,*(undefined8 *)(*plVar14 + 400)),
              plVar14 == (longlong *)0x0)))) goto LAB_7ffe9a372ee9;
          if ((*(byte *)(*plVar14 + 0x130) < *(byte *)(_DAT_7ffe9c904080 + 0x130)) ||
             (*(longlong *)
               (*(longlong *)(*plVar14 + 200) + -8 +
               (ulonglong)*(byte *)(_DAT_7ffe9c904080 + 0x130) * 8) != _DAT_7ffe9c904080)) {
            FUN_7ffe9996c950(plVar14,_DAT_7ffe9c904080);
            pcVar1 = (code *)swi(3);
            iVar9 = (*pcVar1)();
            return iVar9;
          }
          bVar5 = PlayerAttackBase_CheckSkillIndividualFlag((undefined *)plVar14,2,(undefined *)0x0)
          ;
          if (bVar5 != 0) {
            iVar9 = 0x38;
            fVar24 = _DAT_7ffe9c04ab80;
          }
        }
      }
    }
  }
  if ((*(longlong *)(playerAction + 0x30) == 0) ||
     (plVar14 = *(longlong **)(*(longlong *)(playerAction + 0x30) + 0x30),
     plVar14 == (longlong *)0x0)) goto LAB_7ffe9a372ee9;
  plVar14 = (longlong *)(**(code **)(*plVar14 + 0x188))(plVar14,*(undefined8 *)(*plVar14 + 400));
  if (plVar14 != (longlong *)0x0) {
    if ((*(byte *)(*plVar14 + 0x130) < *(byte *)(_DAT_7ffe9c9228b0 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*plVar14 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c9228b0 + 0x130) * 8)
        != _DAT_7ffe9c9228b0)) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    if (bVar2) {
      plVar13 = plVar14;
    }
  }
  cVar4 = FUN_7ffe9a8fecd0(plVar13,0);
  if (cVar4 != '\0') {
    if (plVar13 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
    bVar5 = PlayerAttackBase_CheckSkillParamFlag((undefined *)plVar13,0x2000,(undefined *)0x0);
    if (bVar5 != 0) {
      lVar12 = (**(code **)(*plVar11 + 0x1b8))(plVar11,*(undefined8 *)(*plVar11 + 0x1c0));
      if (lVar12 == 0) goto LAB_7ffe9a372ee9;
      iVar6 = FUN_7ffe9a7fd580(lVar12,0x72);
      if ((0 < iVar6) && (fVar24 < _DAT_7ffe9c049cf4)) {
        iVar9 = 0x72;
        fVar24 = _DAT_7ffe9c049cf4;
      }
    }
    iVar6 = (**(code **)(*plVar13 + 0x188))(plVar13,*(undefined8 *)(*plVar13 + 400));
    if (((iVar6 == 0) &&
        (bVar5 = PlayerAttackBase_CheckSkillIndividualFlag((undefined *)plVar13,2,(undefined *)0x0),
        bVar5 != 0)) && (fVar24 < _DAT_7ffe9c049d70)) {
      iVar9 = 0x29;
      fVar24 = _DAT_7ffe9c049d70;
    }
  }
  plVar13 = (longlong *)
            (**(code **)(*(longlong *)playerAction + 0x298))
                      (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if ((plVar13 == (longlong *)0x0) ||
     (lVar12 = (**(code **)(*plVar13 + 0x1c8))(plVar13,*(undefined8 *)(*plVar13 + 0x1d0)),
     lVar12 == 0)) goto LAB_7ffe9a372ee9;
  cVar4 = FUN_7ffe9a7cbb30(lVar12,0x20f,&plStackX_18,0);
  if (cVar4 != '\0') {
    if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
    iVar6 = (**(code **)(*plStackX_18 + 0x1f8))(plStackX_18,5,*(undefined8 *)(*plStackX_18 + 0x200))
    ;
    if (fVar24 < (float)iVar6 / fVar3) {
      iVar9 = 0x20f;
      fVar24 = (float)iVar6 / fVar3;
    }
  }
  plVar13 = (longlong *)
            (**(code **)(*(longlong *)playerAction + 0x298))
                      (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if ((plVar13 == (longlong *)0x0) ||
     (lVar12 = (**(code **)(*plVar13 + 0x1c8))(plVar13,*(undefined8 *)(*plVar13 + 0x1d0)),
     lVar12 == 0)) goto LAB_7ffe9a372ee9;
  cVar4 = FUN_7ffe9a7cbb30(lVar12,0x305,&plStackX_18,0);
  if (cVar4 != '\0') {
    if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
    iVar6 = (**(code **)(*plStackX_18 + 0x1f8))(plStackX_18,5,*(undefined8 *)(*plStackX_18 + 0x200))
    ;
    if (fVar24 < (float)iVar6) {
      iVar9 = 0x305;
      fVar24 = (float)iVar6;
    }
  }
  iVar6 = FUN_7ffe9a7d1f00(playerAction,0);
  if (0 < iVar6) {
    if (mobAction == (undefined *)0x0) goto LAB_7ffe9a372ee9;
    uVar20 = FUN_7ffe99742ec0(0xd,_DAT_7ffe9c9724e0,mobAction);
    uVar16 = FUN_7ffe9bd98960(playerAction,0);
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    cVar4 = FUN_7ffe9bda2160(uVar20,uVar16,0);
    if ((cVar4 != '\0') && (fVar24 < (float)iVar6)) {
      iVar9 = 0x309;
      fVar24 = (float)iVar6;
    }
  }
  plVar13 = (longlong *)
            (**(code **)(*(longlong *)playerAction + 0x298))
                      (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if ((plVar13 == (longlong *)0x0) ||
     (lVar12 = (**(code **)(*plVar13 + 0x1c8))(plVar13,*(undefined8 *)(*plVar13 + 0x1d0)),
     lVar12 == 0)) goto LAB_7ffe9a372ee9;
  cVar4 = FUN_7ffe9a7cbb30(lVar12,0x12e,&plStackX_18,0);
  if (cVar4 != '\0') {
    if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
    iVar6 = (**(code **)(*plStackX_18 + 0x1f8))(plStackX_18,5,*(undefined8 *)(*plStackX_18 + 0x200))
    ;
    if (fVar24 < (float)iVar6) {
      iVar9 = 0x12e;
      fVar24 = (float)iVar6;
    }
  }
  lVar12 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
  if ((lVar12 == 0) || (*(longlong *)(lVar12 + 0x50) == 0)) goto LAB_7ffe9a372ee9;
  cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x50),iVar9,&plStackX_18,_DAT_7ffe9c934418);
  if (cVar4 == '\0') {
    if ((iVar9 == 0x29) || (iVar6 = iStackX_20, iVar9 == 0x309)) goto LAB_7ffe9a371557;
  }
  else {
    if ((char)allowBuffChanges != '\0') {
      if (iVar9 == 0x445) {
        if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
        if (((*(byte *)(*plStackX_18 + 0x130) < *(byte *)(_DAT_7ffe9c928ba0 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*plStackX_18 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c928ba0 + 0x130) * 8) != _DAT_7ffe9c928ba0)) ||
           (plStackX_18 == (longlong *)0x0)) {
          FUN_7ffe9996c950(plStackX_18);
          pcVar1 = (code *)swi(3);
          iVar9 = (*pcVar1)();
          return iVar9;
        }
        func_0x7ffe99c3b550(plStackX_18,0);
      }
      else if (iVar9 == 0x486) {
        if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
        if (((*(byte *)(*plStackX_18 + 0x130) < *(byte *)(_DAT_7ffe9c917ea0 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*plStackX_18 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c917ea0 + 0x130) * 8) != _DAT_7ffe9c917ea0)) ||
           (plStackX_18 == (longlong *)0x0)) {
          FUN_7ffe9996c950(plStackX_18);
          pcVar1 = (code *)swi(3);
          iVar9 = (*pcVar1)();
          return iVar9;
        }
        func_0x7ffe9a35c040(plStackX_18,0);
      }
      else if (iVar9 == 0x22e) {
        if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
        if (((*(byte *)(*plStackX_18 + 0x130) < *(byte *)(_DAT_7ffe9c8feb30 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*plStackX_18 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c8feb30 + 0x130) * 8) != _DAT_7ffe9c8feb30)) ||
           (plStackX_18 == (longlong *)0x0)) {
          FUN_7ffe9996c950(plStackX_18);
          pcVar1 = (code *)swi(3);
          iVar9 = (*pcVar1)();
          return iVar9;
        }
        func_0x7ffe9a79b740(plStackX_18,playerAction,0);
      }
      else if (iVar9 == 0x20f) {
        if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
        if (((*(byte *)(*plStackX_18 + 0x130) < *(byte *)(_DAT_7ffe9c954730 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*plStackX_18 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c954730 + 0x130) * 8) != _DAT_7ffe9c954730)) ||
           (plStackX_18 == (longlong *)0x0)) {
          FUN_7ffe9996c950(plStackX_18);
          pcVar1 = (code *)swi(3);
          iVar9 = (*pcVar1)();
          return iVar9;
        }
        uVar8 = func_0x7ffe9a795a00(plStackX_18,0);
        *(undefined4 *)(self + 0xd8) = uVar8;
      }
    }
LAB_7ffe9a371557:
    iVar6 = (int)((fVar3 - fVar24) * _DAT_7ffe9c049b34 * (float)iStackX_20);
  }
  fVar24 = 0.0;
  lVar12 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
  if ((lVar12 != 0) && (*(longlong *)(lVar12 + 0x50) != 0)) {
    cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x50),0x109,&plStackX_18,_DAT_7ffe9c934418);
    if (cVar4 != '\0') {
      if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
      iVar9 = func_0x7ffe9a7a2140(plStackX_18,7);
      fVar24 = (float)iVar9 + 0.0;
    }
    lVar12 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
    if ((lVar12 != 0) && (*(longlong *)(lVar12 + 0x50) != 0)) {
      cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x50),0xe6,&plStackX_18,_DAT_7ffe9c934418);
      if (cVar4 != '\0') {
        if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
        iVar9 = func_0x7ffe9a7a2140(plStackX_18,7);
        fVar24 = fVar24 + (float)iVar9;
      }
      lVar12 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
      if ((lVar12 != 0) && (*(longlong *)(lVar12 + 0x50) != 0)) {
        cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x50),0x8e,&plStackX_18,_DAT_7ffe9c934418);
        if (cVar4 != '\0') {
          if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
          iVar9 = func_0x7ffe9a7a2140(plStackX_18,7);
          fVar24 = fVar24 + (float)iVar9;
        }
        lVar12 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
        if ((lVar12 != 0) && (*(longlong *)(lVar12 + 0x50) != 0)) {
          cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x50),0x307,&plStackX_18,_DAT_7ffe9c934418
                                  );
          if (cVar4 != '\0') {
            if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
            iVar9 = func_0x7ffe9a7a2140(plStackX_18,7);
            fVar24 = fVar24 + (float)iVar9;
          }
          lVar12 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
          if ((lVar12 != 0) && (*(longlong *)(lVar12 + 0x50) != 0)) {
            cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x50),0x4c7,&plStackX_18,
                                     _DAT_7ffe9c934418);
            if (cVar4 != '\0') {
              uVar20 = func_0x7ffe9996c990(_DAT_7ffe9c91a2e8,4);
              FUN_7ffe9b436460(uVar20,_DAT_7ffe9c945d08,0);
              cVar4 = (**(code **)(*(longlong *)self + 0x578))
                                (self,uVar20,*(undefined8 *)(*(longlong *)self + 0x580));
              if (cVar4 != '\0') {
                if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
                iVar9 = (**(code **)(*plStackX_18 + 0x1f8))
                                  (plStackX_18,7,*(undefined8 *)(*plStackX_18 + 0x200));
                fVar24 = fVar24 + (float)iVar9;
              }
            }
            lVar12 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
            if ((lVar12 != 0) && (*(longlong *)(lVar12 + 0x50) != 0)) {
              cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x50),0x2c9,&plStackX_18);
              if (cVar4 != '\0') {
                if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
                iVar9 = func_0x7ffe9a7a2140(plStackX_18,7);
                fVar24 = fVar24 + (float)iVar9;
              }
              if (fVar3 < fVar24) {
                fVar24 = fVar24 - fVar3;
                if (fVar24 < 0.0) {
                  fVar24 = 0.0;
                }
                fVar24 = fVar24 / _DAT_7ffe9c049ce4;
                if (DAT_7ffe9cad9e25 == '\0') {
                  FUN_7ffe9996d590(&DAT_7ffe9c968830);
                  DAT_7ffe9cad9e25 = '\x01';
                }
                if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
                  func_0x7ffe9996d830();
                }
                dVar22 = (double)func_0x7ffe99997768((double)fVar24);
                fVar24 = (float)((int)dVar22 + 100);
              }
              iVar9 = MobAttackBase_calcResistDamage(self,iVar6,fVar24,(undefined *)0x0);
              fVar24 = 0.0;
              lVar12 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
              if ((lVar12 != 0) && (*(longlong *)(lVar12 + 0x50) != 0)) {
                cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x50),0x325,&plStackX_18,
                                         _DAT_7ffe9c934418);
                if (cVar4 != '\0') {
                  if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
                  iVar6 = func_0x7ffe9a7a2140(plStackX_18,6);
                  fVar24 = (float)iVar6 + 0.0;
                }
                plVar13 = (longlong *)
                          (**(code **)(*(longlong *)playerAction + 0x298))
                                    (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)
                                    );
                if (((plVar13 != (longlong *)0x0) &&
                    (lVar12 = (**(code **)(*plVar13 + 0x1b8))
                                        (plVar13,*(undefined8 *)(*plVar13 + 0x1c0)), lVar12 != 0))
                   && (*(longlong *)(lVar12 + 0x68) != 0)) {
                  cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x68),0x203,&plStack_a8,
                                           _DAT_7ffe9c935bd0);
                  if ((cVar4 != '\0') && (self != (undefined *)0x0)) {
                    if (((*(byte *)(_DAT_7ffe9c8eeb48 + 0x130) <=
                          *(byte *)(*(longlong *)self + 0x130)) &&
                        (*(longlong *)
                          (*(longlong *)(*(longlong *)self + 200) + -8 +
                          (ulonglong)*(byte *)(_DAT_7ffe9c8eeb48 + 0x130) * 8) == _DAT_7ffe9c8eeb48)
                        ) && ((((int)hitReactionType - 2U & 0xfffffff9) != 0 ||
                              ((int)hitReactionType == 8)))) {
                      if ((plStack_a8 == (longlong *)0x0) ||
                         (((iVar6 = (**(code **)(*plStack_a8 + 0x178))
                                              (plStack_a8,0,*(undefined8 *)(*plStack_a8 + 0x180)),
                           plStack_a8 == (longlong *)0x0 ||
                           (iVar7 = (**(code **)(*plStack_a8 + 0x178))
                                              (plStack_a8,0x19,*(undefined8 *)(*plStack_a8 + 0x180))
                           , plStack_a8 == (longlong *)0x0)) || (plStack_a8[2] == 0))))
                      goto LAB_7ffe9a372ee9;
                      if (*(char *)(plStack_a8[2] + 0x18) == '\n') {
                        plVar13 = (longlong *)
                                  (**(code **)(*(longlong *)playerAction + 0x298))
                                            (playerAction,
                                             *(undefined8 *)(*(longlong *)playerAction + 0x2a0));
                        if (((plVar13 == (longlong *)0x0) ||
                            (lVar12 = (**(code **)(*plVar13 + 0x1b8))
                                                (plVar13,*(undefined8 *)(*plVar13 + 0x1c0)),
                            lVar12 == 0)) || (*(longlong *)(lVar12 + 0x68) == 0))
                        goto LAB_7ffe9a372ee9;
                        cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x68),0x208,&plStack_a8,
                                                 _DAT_7ffe9c935bd0);
                        if (cVar4 != '\0') {
                          lVar12 = FUN_7ffe9b15c270(_DAT_7ffe9c9632c0);
                          if (lVar12 == 0) goto LAB_7ffe9a372ee9;
                          cVar4 = FUN_7ffe9a33a880(lVar12,0);
                          if (cVar4 != '\0') {
                            plVar13 = (longlong *)
                                      (**(code **)(*(longlong *)playerAction + 0x298))
                                                (playerAction,
                                                 *(undefined8 *)(*(longlong *)playerAction + 0x2a0))
                            ;
                            if (((plVar13 == (longlong *)0x0) ||
                                (lVar12 = (**(code **)(*plVar13 + 0x1f8))
                                                    (plVar13,*(undefined8 *)(*plVar13 + 0x200)),
                                lVar12 == 0)) || (*(longlong *)(lVar12 + 0x20) == 0))
                            goto LAB_7ffe9a372ee9;
                            iVar10 = func_0x7ffe99c1ed70(*(longlong *)(lVar12 + 0x20),0);
                            if (plStack_a8 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
                            if (((*(byte *)(*plStack_a8 + 0x130) <
                                  *(byte *)(_DAT_7ffe9c954998 + 0x130)) ||
                                (*(longlong *)
                                  (*(longlong *)(*plStack_a8 + 200) + -8 +
                                  (ulonglong)*(byte *)(_DAT_7ffe9c954998 + 0x130) * 8) !=
                                 _DAT_7ffe9c954998)) || (plStack_a8 == (longlong *)0x0)) {
                              FUN_7ffe9996c950(plStack_a8,_DAT_7ffe9c954998,iVar10 == 0x11);
                              pcVar1 = (code *)swi(3);
                              iVar9 = (*pcVar1)();
                              return iVar9;
                            }
                            iVar10 = FUN_7ffe9a7b4880(plStack_a8,1);
                            iVar6 = iVar6 + iVar10;
                          }
                        }
                      }
                      cVar4 = FUN_7ffe9a8fea70(self,100,iVar6);
                      if (cVar4 != '\0') {
                        fVar24 = fVar24 + (float)iVar7;
                      }
                    }
                  }
                  lVar12 = (**(code **)(*plVar11 + 0x1c8))
                                     (plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
                  if ((lVar12 != 0) && (*(longlong *)(lVar12 + 0x50) != 0)) {
                    cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x50),0x207,&plStackX_18,
                                             _DAT_7ffe9c934418);
                    if ((cVar4 != '\0') && (self != (undefined *)0x0)) {
                      lVar12 = *(longlong *)self;
                      if (((*(byte *)(_DAT_7ffe9c8ed488 + 0x130) <= *(byte *)(lVar12 + 0x130)) &&
                          (*(longlong *)
                            (*(longlong *)(lVar12 + 200) + -8 +
                            (ulonglong)*(byte *)(_DAT_7ffe9c8ed488 + 0x130) * 8) ==
                           _DAT_7ffe9c8ed488)) ||
                         ((*(byte *)(_DAT_7ffe9c8ee3f8 + 0x130) <= *(byte *)(lVar12 + 0x130) &&
                          (*(longlong *)
                            (*(longlong *)(lVar12 + 200) + -8 +
                            (ulonglong)*(byte *)(_DAT_7ffe9c8ee3f8 + 0x130) * 8) ==
                           _DAT_7ffe9c8ee3f8)))) {
                        if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
                        iVar6 = func_0x7ffe9a7a2140(plStackX_18,6);
                        fVar24 = fVar24 + (float)iVar6;
                      }
                    }
                    lVar12 = (**(code **)(*plVar11 + 0x1c8))
                                       (plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
                    if ((lVar12 != 0) && (*(longlong *)(lVar12 + 0x50) != 0)) {
                      cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x50),999,&plStackX_18,
                                               _DAT_7ffe9c934418);
                      if (cVar4 != '\0') {
                        if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
                        iVar6 = func_0x7ffe9a7a2140(plStackX_18,6);
                        fVar24 = fVar24 + (float)iVar6;
                      }
                      lVar12 = (**(code **)(*plVar11 + 0x1c8))
                                         (plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
                      if ((lVar12 != 0) && (*(longlong *)(lVar12 + 0x50) != 0)) {
                        cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x50),0x26d,&plStackX_18,
                                                 _DAT_7ffe9c934418);
                        if (cVar4 != '\0') {
                          if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
                          iVar6 = func_0x7ffe9a7a2140(plStackX_18,6);
                          fVar24 = fVar24 + (float)iVar6;
                        }
                        lVar12 = (**(code **)(*plVar11 + 0x1c8))
                                           (plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
                        if ((lVar12 != 0) && (*(longlong *)(lVar12 + 0x50) != 0)) {
                          cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x50),0x503,&plStackX_18,
                                                   _DAT_7ffe9c934418);
                          if (cVar4 != '\0') {
                            if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
                            iVar6 = func_0x7ffe9a7a2140(plStackX_18,6);
                            fVar24 = fVar24 + (float)iVar6;
                          }
                          lVar12 = (**(code **)(*plVar11 + 0x1b8))
                                             (plVar11,*(undefined8 *)(*plVar11 + 0x1c0));
                          if ((lVar12 != 0) && (*(longlong *)(lVar12 + 0x68) != 0)) {
                            cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x68),0x449,&plStack_a8,
                                                     _DAT_7ffe9c935bd0);
                            if (cVar4 != '\0') {
                              puVar17 = (undefined *)
                                        (**(code **)(*plVar11 + 0x1f8))
                                                  (plVar11,*(undefined8 *)(*plVar11 + 0x200));
                              if ((plStack_a8 == (longlong *)0x0) || (plStack_a8[2] == 0))
                              goto LAB_7ffe9a372ee9;
                              skillMaster = *(undefined **)(plStack_a8[2] + 0x10);
                              if (*(int *)(_DAT_7ffe9c94c0a0 + 0xe0) == 0) {
                                func_0x7ffe9996d830();
                              }
                              bVar5 = SkillUtil_CheckSkillEquipLimit
                                                (puVar17,skillMaster,(undefined *)0x0);
                              if ((bVar5 != 0) && (mobAction != (undefined *)0x0)) {
                                uVar20 = FUN_7ffe99742ec0(0xd,_DAT_7ffe9c9724e0,mobAction);
                                if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                                  func_0x7ffe9996d830();
                                }
                                cVar4 = FUN_7ffe9bda2160(uVar20,0,0);
                                if (cVar4 != '\0') {
                                  uVar20 = *(undefined8 *)(playerAction + 0x30);
                                  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                                    func_0x7ffe9996d830();
                                  }
                                  cVar4 = FUN_7ffe9bda2160(uVar20,0,0);
                                  if (cVar4 != '\0') {
                                    if (*(longlong *)(playerAction + 0x30) == 0)
                                    goto LAB_7ffe9a372ee9;
                                    cVar4 = func_0x7ffe99a43990(*(longlong *)(playerAction + 0x30),0
                                                               );
                                    if (cVar4 != '\0') {
                                      uVar20 = FUN_7ffe99742ec0(0xd,_DAT_7ffe9c9724e0,mobAction);
                                      uVar16 = FUN_7ffe9bd98960(playerAction,0);
                                      if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                                        func_0x7ffe9996d830();
                                      }
                                      cVar4 = FUN_7ffe9bda1fa0(uVar20,uVar16,0);
                                      if (cVar4 != '\0') {
                                        if ((*(longlong *)(playerAction + 0x30) == 0) ||
                                           (lVar12 = *(longlong *)
                                                      (*(longlong *)(playerAction + 0x30) + 0x48),
                                           lVar12 == 0)) goto LAB_7ffe9a372ee9;
                                        uVar20 = *(undefined8 *)(lVar12 + 0x18);
                                        uVar16 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c9724e0,mobAction);
                                        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                                          func_0x7ffe9996d830();
                                        }
                                        cVar4 = FUN_7ffe9bda1fa0(uVar20,uVar16,0);
                                        if (cVar4 != '\0') {
                                          if (plStack_a8 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
                                          iVar6 = func_0x7ffe99744f30(4,plStack_a8,8);
                                          fVar24 = fVar24 + (float)iVar6;
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                            lVar12 = (**(code **)(*plVar11 + 0x1c8))
                                               (plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
                            if ((lVar12 != 0) && (*(longlong *)(lVar12 + 0x50) != 0)) {
                              cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x50),0x4c8,
                                                       &plStackX_18,_DAT_7ffe9c934418);
                              if (cVar4 != '\0') {
                                iVar6 = 0;
                                if (mobAction != (undefined *)0x0) {
                                  lVar12 = FUN_7ffe9bd98a10(playerAction,0);
                                  if (lVar12 == 0) goto LAB_7ffe9a372ee9;
                                  puVar18 = (ulonglong *)FUN_7ffe9bdbf710(auStack_88,lVar12,0);
                                  uStack_98 = *puVar18;
                                  fStack_90 = *(float *)(puVar18 + 1);
                                  lVar12 = FUN_7ffe99742ec0(0x16,_DAT_7ffe9c9724e0,mobAction);
                                  if (lVar12 == 0) goto LAB_7ffe9a372ee9;
                                  puVar15 = (undefined8 *)FUN_7ffe9bdbf710(auStack_88,lVar12,0);
                                  fStack_80 = *(float *)(puVar15 + 1);
                                  fStack_90 = fStack_90 - fStack_80;
                                  uStack_98 = (ulonglong)(uint)((float)uStack_98 - (float)*puVar15);
                                  FUN_7ffe999e62d0(&uStack_98,0);
                                  FUN_7ffe99744d60(0,_DAT_7ffe9c9724e0,mobAction);
                                  uVar20 = func_0x7ffe99a4d6b0();
                                  iVar6 = FUN_7ffe99a43d50(uVar20,0);
                                }
                                if ((_DAT_7ffe9c049b7c <= (float)iVar6) &&
                                   (self != (undefined *)0x0)) {
                                  lVar12 = *(longlong *)self;
                                  if (((*(byte *)(_DAT_7ffe9c8eeb48 + 0x130) <=
                                        *(byte *)(lVar12 + 0x130)) &&
                                      (*(longlong *)
                                        (*(longlong *)(lVar12 + 200) + -8 +
                                        (ulonglong)*(byte *)(_DAT_7ffe9c8eeb48 + 0x130) * 8) ==
                                       _DAT_7ffe9c8eeb48)) ||
                                     ((*(byte *)(_DAT_7ffe9c8ee328 + 0x130) <=
                                       *(byte *)(lVar12 + 0x130) &&
                                      (*(longlong *)
                                        (*(longlong *)(lVar12 + 200) + -8 +
                                        (ulonglong)*(byte *)(_DAT_7ffe9c8ee328 + 0x130) * 8) ==
                                       _DAT_7ffe9c8ee328)))) {
                                    if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
                                    iVar6 = (**(code **)(*plStackX_18 + 0x1f8))
                                                      (plStackX_18,6,
                                                       *(undefined8 *)(*plStackX_18 + 0x200));
                                    fVar24 = fVar24 + (float)iVar6;
                                  }
                                }
                                if ((char)allowBuffChanges != '\0') {
                                  self[200] = 1;
                                }
                              }
                              lVar12 = (**(code **)(*plVar11 + 0x1c8))
                                                 (plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
                              if ((lVar12 != 0) && (*(longlong *)(lVar12 + 0x50) != 0)) {
                                cVar4 = FUN_7ffe9ad8e670(*(longlong *)(lVar12 + 0x50),0xe2,
                                                         &plStackX_18);
                                if (cVar4 != '\0') {
                                  if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
                                  iVar6 = func_0x7ffe9a7a2140(plStackX_18,6);
                                  fVar24 = fVar24 - (float)iVar6;
                                }
                                lVar12 = (**(code **)(*plVar11 + 0x1c8))
                                                   (plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
                                if (lVar12 != 0) {
                                  cVar4 = FUN_7ffe9a7cbb30(lVar12,0x209,&plStackX_18);
                                  if ((cVar4 != '\0') &&
                                     (cVar4 = (**(code **)(*(longlong *)self + 0x568))
                                                        (self,*(undefined8 *)
                                                               (*(longlong *)self + 0x570)),
                                     cVar4 != '\0')) {
                                    if (*(longlong *)(playerAction + 0x30) == 0)
                                    goto LAB_7ffe9a372ee9;
                                    if ((*(longlong *)(*(longlong *)(playerAction + 0x30) + 0x48) !=
                                         0) && (mobAction != (undefined *)0x0)) {
                                      uVar20 = FUN_7ffe99742ec0(0xd,_DAT_7ffe9c9724e0,mobAction);
                                      uVar16 = FUN_7ffe9bd98960(playerAction,0);
                                      if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                                        func_0x7ffe9996d830();
                                      }
                                      cVar4 = FUN_7ffe9bda1fa0(uVar20,uVar16,0);
                                      if (cVar4 != '\0') {
                                        if ((*(longlong *)(playerAction + 0x30) == 0) ||
                                           (lVar12 = *(longlong *)
                                                      (*(longlong *)(playerAction + 0x30) + 0x48),
                                           lVar12 == 0)) goto LAB_7ffe9a372ee9;
                                        uVar20 = *(undefined8 *)(lVar12 + 0x18);
                                        uVar16 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c9724e0,mobAction);
                                        if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
                                          func_0x7ffe9996d830();
                                        }
                                        cVar4 = FUN_7ffe9bda1fa0(uVar20,uVar16,0);
                                        if (cVar4 != '\0') {
                                          if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
                                          iVar6 = func_0x7ffe99744f30(0xc,plStackX_18,0x4a);
                                          fVar24 = fVar24 + (float)iVar6;
                                        }
                                      }
                                    }
                                  }
                                  plVar13 = (longlong *)
                                            (**(code **)(*(longlong *)playerAction + 0x298))
                                                      (playerAction,
                                                       *(undefined8 *)
                                                        (*(longlong *)playerAction + 0x2a0));
                                  if ((plVar13 != (longlong *)0x0) &&
                                     (lVar12 = (**(code **)(*plVar13 + 0x1c8))
                                                         (plVar13,*(undefined8 *)(*plVar13 + 0x1d0))
                                     , lVar12 != 0)) {
                                    cVar4 = FUN_7ffe9a7cbb30(lVar12,0x33,&plStackX_18);
                                    if (cVar4 != '\0') {
                                      if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
                                      iVar6 = func_0x7ffe9a7a2140(plStackX_18,6);
                                      fVar24 = fVar24 + (float)iVar6;
                                    }
                                    lVar12 = (**(code **)(*plVar11 + 0x1c8))
                                                       (plVar11,*(undefined8 *)(*plVar11 + 0x1d0));
                                    if (lVar12 != 0) {
                                      cVar4 = FUN_7ffe9a7cbb30(lVar12,0x270,&plStackX_18);
                                      if ((cVar4 != '\0') &&
                                         (cVar4 = (**(code **)(*(longlong *)self + 0x568))
                                                            (self,*(undefined8 *)
                                                                   (*(longlong *)self + 0x570)),
                                         cVar4 == '\0')) {
                                        if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372ee9;
                                        iVar6 = (**(code **)(*plStackX_18 + 0x1f8))
                                                          (plStackX_18,6,
                                                           *(undefined8 *)(*plStackX_18 + 0x200));
                                        fVar24 = fVar24 + (float)iVar6;
                                        if ((char)allowBuffChanges != '\0') {
                                          self[0xd4] = 1;
                                        }
                                      }
                                      lVar12 = (**(code **)(*plVar11 + 0x1c8))
                                                         (plVar11,*(undefined8 *)(*plVar11 + 0x1d0))
                                      ;
                                      if (lVar12 != 0) {
                                        cVar4 = FUN_7ffe9a7cbb30(lVar12,0x2c2,&plStackX_18);
                                        if (cVar4 != '\0') {
                                          if (plStackX_18 == (longlong *)0x0) goto LAB_7ffe9a372f91;
                                          iVar6 = (**(code **)(*plStackX_18 + 0x1f8))
                                                            (plStackX_18,6,
                                                             *(undefined8 *)(*plStackX_18 + 0x200));
                                          fVar24 = fVar24 + (float)iVar6;
                                        }
                                        lVar12 = (**(code **)(*plVar11 + 0x1c8))
                                                           (plVar11,*(undefined8 *)
                                                                     (*plVar11 + 0x1d0));
                                        if (lVar12 != 0) {
                                          cVar4 = FUN_7ffe9a7cbb30(lVar12,0x2a7,&plStackX_18);
                                          if ((cVar4 != '\0') &&
                                             (cVar4 = (**(code **)(*(longlong *)self + 0x568))
                                                                (self,*(undefined8 *)
                                                                       (*(longlong *)self + 0x570)),
                                             cVar4 != '\0')) {
                                            if (plStackX_18 == (longlong *)0x0)
                                            goto LAB_7ffe9a372f91;
                                            iVar6 = (**(code **)(*plStackX_18 + 0x1f8))
                                                              (plStackX_18,0x4a,
                                                               *(undefined8 *)(*plStackX_18 + 0x200)
                                                              );
                                            fVar24 = fVar24 + (float)iVar6;
                                          }
                                          lVar12 = (**(code **)(*plVar11 + 0x1c8))
                                                             (plVar11,*(undefined8 *)
                                                                       (*plVar11 + 0x1d0));
                                          if (lVar12 != 0) {
                                            cVar4 = FUN_7ffe9a7cbb30(lVar12,0x20d,&plStackX_18);
                                            if (cVar4 != '\0') {
                                              if (plStackX_18 == (longlong *)0x0)
                                              goto LAB_7ffe9a372f91;
                                              iVar6 = (**(code **)(*plStackX_18 + 0x1f8))
                                                                (plStackX_18,6,
                                                                 *(undefined8 *)
                                                                  (*plStackX_18 + 0x200));
                                              fVar24 = fVar24 + (float)iVar6;
                                            }
                                            lVar12 = (**(code **)(*plVar11 + 0x1c8))
                                                               (plVar11,*(undefined8 *)
                                                                         (*plVar11 + 0x1d0));
                                            if (lVar12 != 0) {
                                              cVar4 = FUN_7ffe9a7cbb30(lVar12,0x20e,&plStackX_18);
                                              if ((cVar4 != '\0') &&
                                                 (cVar4 = (**(code **)(*(longlong *)self + 0x568))
                                                                    (self,*(undefined8 *)
                                                                           (*(longlong *)self +
                                                                           0x570)), cVar4 != '\0'))
                                              {
                                                if (plStackX_18 == (longlong *)0x0)
                                                goto LAB_7ffe9a372f91;
                                                iVar6 = (**(code **)(*plStackX_18 + 0x1f8))
                                                                  (plStackX_18,0x4a,
                                                                   *(undefined8 *)
                                                                    (*plStackX_18 + 0x200));
                                                fVar24 = fVar24 + (float)iVar6;
                                              }
                                              fVar21 = (float)FUN_7ffe9a7b57b0(self,plVar11,0);
                                              iVar6 = FUN_7ffe9a7a6ec0(self,mobAction,playerAction);
                                              fVar24 = (float)iVar6 + fVar21 + fVar24;
                                              lVar12 = (**(code **)(*plVar11 + 0x1c8))
                                                                 (plVar11,*(undefined8 *)
                                                                           (*plVar11 + 0x1d0));
                                              if (lVar12 != 0) {
                                                cVar4 = FUN_7ffe9a7cbb30(lVar12,0x293,&plStackX_18);
                                                if (cVar4 != '\0') {
                                                  if (plStackX_18 == (longlong *)0x0)
                                                  goto LAB_7ffe9a372f91;
                                                  iVar6 = (**(code **)(*plStackX_18 + 0x1f8))
                                                                    (plStackX_18,6,
                                                                     *(undefined8 *)
                                                                      (*plStackX_18 + 0x200));
                                                  fVar24 = fVar24 + (float)iVar6;
                                                }
                                                iVar6 = FUN_7ffe9a841f50(self,plVar11,0);
                                                iVar7 = FUN_7ffe9a77d840(plVar11,0);
                                                fVar24 = (float)iVar7 + (float)iVar6 + fVar24;
                                                if (fVar3 < fVar24) {
                                                  iVar6 = FUN_7ffe99a43d50();
                                                  fVar24 = (float)(iVar6 + 100);
                                                }
                                                iVar9 = MobAttackBase_calcResistDamage
                                                                  (self,iVar9,fVar24,
                                                                   (undefined *)0x0);
                                                puVar17 = (undefined *)
                                                          (**(code **)(*plVar11 + 0x1d8))
                                                                    (plVar11,*(undefined8 *)
                                                                              (*plVar11 + 0x1e0));
                                                if (puVar17 != (undefined *)0x0) {
                                                  iVar6 = BonusManager_GetBonusValue
                                                                    (puVar17,0xc0,(undefined *)0x0);
                                                  if (mobAction == (undefined *)0x0) {
                                                    uVar20 = 0;
                                                  }
                                                  else {
                                                    uVar20 = FUN_7ffe99742ec0(0x16,_DAT_7ffe9c9724e0
                                                                              ,mobAction);
                                                  }
                                                  lVar12 = (**(code **)(*plVar11 + 0x218))
                                                                     (plVar11,*(undefined8 *)
                                                                               (*plVar11 + 0x220));
                                                  if (lVar12 != 0) {
                                                    fVar24 = (float)FUN_7ffe9a5b2600(lVar12,plVar11,
                                                                                     uVar20,self,0);
                                                    iVar9 = (int)((fVar24 + _DAT_7ffe9c049b18) *
                                                                 (float)(int)((float)((iVar6 + 100)
                                                                                     * iVar9) /
                                                                             fVar3));
                                                    lVar12 = (**(code **)(*plVar11 + 0x1c8))
                                                                       (plVar11,*(undefined8 *)
                                                                                 (*plVar11 + 0x1d0))
                                                    ;
                                                    if ((lVar12 != 0) &&
                                                       (*(longlong *)(lVar12 + 0x50) != 0)) {
                                                      cVar4 = FUN_7ffe9ad8e670(*(longlong *)
                                                                                (lVar12 + 0x50),
                                                                               0x481,&plStackX_18,
                                                                               _DAT_7ffe9c934418);
                                                      if (cVar4 != '\0') {
                                                        lVar12 = (**(code **)(*plVar11 + 0x198))
                                                                           (plVar11,*(undefined8 *)
                                                                                     (*plVar11 +
                                                                                     0x1a0));
                                                        if ((lVar12 == 0) ||
                                                           (iVar6 = FUN_7ffe99742ec0(10,
                                                  _DAT_7ffe9c940d40,lVar12),
                                                  plStackX_18 == (longlong *)0x0))
                                                  goto LAB_7ffe9a372f91;
                                                  iVar7 = func_0x7ffe9a7a2140(plStackX_18,0x32);
                                                  iVar6 = iVar9 - (int)((float)(iVar7 * iVar6) *
                                                                       _DAT_7ffe9c049b34);
                                                  iVar9 = 0;
                                                  if (-1 < iVar6) {
                                                    iVar9 = iVar6;
                                                  }
                                                  if ((char)allowBuffChanges != '\0') {
                                                    if (plStackX_18 == (longlong *)0x0)
                                                    goto LAB_7ffe9a372f91;
                                                    func_0x7ffe9a7a2130(plStackX_18,0);
                                                  }
                                                  }
                                                  lVar12 = (**(code **)(*plVar11 + 0x1c8))
                                                                     (plVar11,*(undefined8 *)
                                                                               (*plVar11 + 0x1d0));
                                                  if ((lVar12 != 0) &&
                                                     (*(longlong *)(lVar12 + 0x50) != 0)) {
                                                    cVar4 = FUN_7ffe9ad8e670(*(longlong *)
                                                                              (lVar12 + 0x50),0x488,
                                                                             &plStackX_18,
                                                                             _DAT_7ffe9c934418);
                                                    if (cVar4 != '\0') {
                                                      if ((char)allowBuffChanges == '\0') {
                                                        if (plStackX_18 == (longlong *)0x0)
                                                        goto LAB_7ffe9a372f91;
                                                        if (((*(byte *)(*plStackX_18 + 0x130) <
                                                              *(byte *)(_DAT_7ffe9c90ea00 + 0x130))
                                                            || (*(longlong *)
                                                                 (*(longlong *)(*plStackX_18 + 200)
                                                                  + -8 + (ulonglong)
                                                                         *(byte *)(_DAT_7ffe9c90ea00
                                                                                  + 0x130) * 8) !=
                                                                _DAT_7ffe9c90ea00)) ||
                                                           (plStackX_18 == (longlong *)0x0)) {
                                                          FUN_7ffe9996c950(plStackX_18);
                                                          pcVar1 = (code *)swi(3);
                                                          iVar9 = (*pcVar1)();
                                                          return iVar9;
                                                        }
                                                        iVar9 = func_0x7ffe9a78d410(plStackX_18,
                                                                                    iVar9,0);
                                                      }
                                                      else {
                                                        if ((plStackX_18 == (longlong *)0x0) ||
                                                           (iVar6 = (**(code **)(*plStackX_18 +
                                                                                0x1f8))(plStackX_18,
                                                                                        0x32,*(
                                                  undefined8 *)(*plStackX_18 + 0x200)),
                                                  plStackX_18 == (longlong *)0x0))
                                                  goto LAB_7ffe9a372f91;
                                                  if ((*(byte *)(*plStackX_18 + 0x130) <
                                                       *(byte *)(_DAT_7ffe9c90ea00 + 0x130)) ||
                                                     ((*(longlong *)
                                                        (*(longlong *)(*plStackX_18 + 200) + -8 +
                                                        (ulonglong)
                                                        *(byte *)(_DAT_7ffe9c90ea00 + 0x130) * 8) !=
                                                       _DAT_7ffe9c90ea00 ||
                                                      (plStackX_18 == (longlong *)0x0)))) {
                                                    FUN_7ffe9996c950(plStackX_18,_DAT_7ffe9c90ea00);
                                                    pcVar1 = (code *)swi(3);
                                                    iVar9 = (*pcVar1)();
                                                    return iVar9;
                                                  }
                                                  iVar9 = func_0x7ffe9a78d460(plStackX_18,iVar9,0);
                                                  if (plStackX_18 == (longlong *)0x0)
                                                  goto LAB_7ffe9a372f91;
                                                  iVar7 = (**(code **)(*plStackX_18 + 0x1f8))
                                                                    (plStackX_18,0x32,
                                                                     *(undefined8 *)
                                                                      (*plStackX_18 + 0x200));
                                                  *(int *)(self + 0xd0) = iVar6 - iVar7;
                                                  }
                                                  }
                                                  lVar12 = (**(code **)(*plVar11 + 0x1c8))
                                                                     (plVar11,*(undefined8 *)
                                                                               (*plVar11 + 0x1d0));
                                                  if ((lVar12 != 0) &&
                                                     (*(longlong *)(lVar12 + 0x50) != 0)) {
                                                    cVar4 = FUN_7ffe9ad8e670(*(longlong *)
                                                                              (lVar12 + 0x50),0x406,
                                                                             &plStackX_18,
                                                                             _DAT_7ffe9c934418);
                                                    if (cVar4 != '\0') {
                                                      if ((char)allowBuffChanges == '\0') {
                                                        if (plStackX_18 == (longlong *)0x0)
                                                        goto LAB_7ffe9a372f91;
                                                        if (((*(byte *)(*plStackX_18 + 0x130) <
                                                              *(byte *)(_DAT_7ffe9c955db8 + 0x130))
                                                            || (*(longlong *)
                                                                 (*(longlong *)(*plStackX_18 + 200)
                                                                  + -8 + (ulonglong)
                                                                         *(byte *)(_DAT_7ffe9c955db8
                                                                                  + 0x130) * 8) !=
                                                                _DAT_7ffe9c955db8)) ||
                                                           (plStackX_18 == (longlong *)0x0)) {
                                                          FUN_7ffe9996c950(plStackX_18);
                                                          pcVar1 = (code *)swi(3);
                                                          iVar9 = (*pcVar1)();
                                                          return iVar9;
                                                        }
                                                        iVar9 = func_0x7ffe9a7a40f0(plStackX_18,
                                                                                    iVar9,0);
                                                      }
                                                      else {
                                                        if ((plStackX_18 == (longlong *)0x0) ||
                                                           (iVar6 = (**(code **)(*plStackX_18 +
                                                                                0x1f8))(plStackX_18,
                                                                                        0x32,*(
                                                  undefined8 *)(*plStackX_18 + 0x200)),
                                                  plStackX_18 == (longlong *)0x0))
                                                  goto LAB_7ffe9a372f91;
                                                  if ((*(byte *)(*plStackX_18 + 0x130) <
                                                       *(byte *)(_DAT_7ffe9c955db8 + 0x130)) ||
                                                     ((*(longlong *)
                                                        (*(longlong *)(*plStackX_18 + 200) + -8 +
                                                        (ulonglong)
                                                        *(byte *)(_DAT_7ffe9c955db8 + 0x130) * 8) !=
                                                       _DAT_7ffe9c955db8 ||
                                                      (plStackX_18 == (longlong *)0x0)))) {
                                                    FUN_7ffe9996c950(plStackX_18,_DAT_7ffe9c955db8);
                                                    pcVar1 = (code *)swi(3);
                                                    iVar9 = (*pcVar1)();
                                                    return iVar9;
                                                  }
                                                  iVar9 = FUN_7ffe9a7a4120(plStackX_18,iVar9,0);
                                                  if (plStackX_18 == (longlong *)0x0)
                                                  goto LAB_7ffe9a372f91;
                                                  iVar7 = (**(code **)(*plStackX_18 + 0x1f8))
                                                                    (plStackX_18,0x32,
                                                                     *(undefined8 *)
                                                                      (*plStackX_18 + 0x200));
                                                  *(int *)(self + 0xc4) = iVar6 - iVar7;
                                                  }
                                                  }
                                                  lVar12 = (**(code **)(*plVar11 + 0x1c8))
                                                                     (plVar11,*(undefined8 *)
                                                                               (*plVar11 + 0x1d0));
                                                  if (lVar12 != 0) {
                                                    cVar4 = FUN_7ffe9a7cbb30(lVar12,0x291,
                                                                             &plStackX_18,0);
                                                    if (cVar4 == '\0') {
                                                      return iVar9;
                                                    }
                                                    if (plStackX_18 != (longlong *)0x0) {
                                                      iVar6 = func_0x7ffe9a7a2140(plStackX_18,0x32);
                                                      *(int *)(self + 0xcc) =
                                                           iVar9 - (iVar6 * iVar9) / 100;
                                                      if ((char)allowBuffChanges == '\0') {
                                                        *(undefined4 *)(self + 0xcc) = 0;
                                                        return 0;
                                                      }
                                                      lVar12 = (**(code **)(*plVar11 + 0x178))
                                                                         (plVar11,*(undefined8 *)
                                                                                   (*plVar11 + 0x180
                                                                                   ));
                                                      if (lVar12 != 0) {
                                                        iVar9 = *(int *)(lVar12 + 0x18);
                                                        lVar12 = (**(code **)(*plVar11 + 0x178))
                                                                           (plVar11,*(undefined8 *)
                                                                                     (*plVar11 +
                                                                                     0x180));
                                                        if (lVar12 != 0) {
                                                          if (*(int *)(self + 0xcc) <=
                                                              *(int *)(lVar12 + 0x28) + iVar9) {
                                                            return 0;
                                                          }
                                                          if (plStackX_18 != (longlong *)0x0) {
                                                            if (((*(byte *)(_DAT_7ffe9c935b00 +
                                                                           0x130) <=
                                                                  *(byte *)(*plStackX_18 + 0x130))
                                                                && (*(longlong *)
                                                                     (*(longlong *)
                                                                       (*plStackX_18 + 200) + -8 +
                                                                     (ulonglong)
                                                                     *(byte *)(_DAT_7ffe9c935b00 +
                                                                              0x130) * 8) ==
                                                                    _DAT_7ffe9c935b00)) &&
                                                               (plStackX_18 != (longlong *)0x0)) {
                                                              FUN_7ffe9a779a20(plStackX_18,0);
                                                              return 0;
                                                            }
                                                            FUN_7ffe9996c950(plStackX_18);
                                                            pcVar1 = (code *)swi(3);
                                                            iVar9 = (*pcVar1)();
                                                            return iVar9;
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
LAB_7ffe9a372f91:
                                      FUN_7ffe9996d7a0();
                                      pcVar1 = (code *)swi(3);
                                      iVar9 = (*pcVar1)();
                                      return iVar9;
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
  }
LAB_7ffe9a372ee9:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  iVar9 = (*pcVar1)();
  return iVar9;
}

