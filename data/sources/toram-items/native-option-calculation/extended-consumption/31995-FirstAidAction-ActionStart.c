
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void FirstAidAction_ActionStart
               (undefined *self,undefined *actarAction,undefined *target,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  undefined *puVar6;
  longlong *plVar7;
  longlong lVar8;
  undefined8 *puVar9;
  longlong *plVar10;
  undefined *puVar11;
  longlong *plVar12;
  undefined8 uVar13;
  undefined4 uVar14;
  double dVar15;
  undefined1 auVar16 [16];
  float fVar17;
  float fVar18;
  longlong *plStack_78;
  longlong lStack_70;
  longlong lStack_68;
  undefined8 uStack_60;
  float fStack_58;
  undefined1 auStack_48 [8];
  float fStack_40;
  
  if (DAT_7ffe9caddeaa == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f3938,actarAction,target,0);
    FUN_7ffe9996d590(&DAT_7ffe9c92eda0);
    FUN_7ffe9996d590(&DAT_7ffe9c961b90);
    FUN_7ffe9996d590(&DAT_7ffe9c9341c8);
    FUN_7ffe9996d590(&DAT_7ffe9c8feb30);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    FUN_7ffe9996d590(&DAT_7ffe9c9685a0);
    FUN_7ffe9996d590(&DAT_7ffe9c969198);
    FUN_7ffe9996d590(&DAT_7ffe9c8fc158);
    FUN_7ffe9996d590(&DAT_7ffe9c8fc228);
    FUN_7ffe9996d590(&DAT_7ffe9c8fc2f8);
    FUN_7ffe9996d590(&DAT_7ffe9c8fc3c8);
    FUN_7ffe9996d590(&DAT_7ffe9c910408);
    FUN_7ffe9996d590(&DAT_7ffe9c8fc498);
    FUN_7ffe9996d590(&DAT_7ffe9c9104d8);
    DAT_7ffe9caddeaa = '\x01';
  }
  plVar12 = (longlong *)0x0;
  plStack_78 = (longlong *)0x0;
  lStack_68 = 0;
  lStack_70 = 0;
  puVar6 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c910408);
  AvoidBreaker_Reset(puVar6,(undefined *)0x0);
  if (puVar6 == (undefined *)0x0) goto LAB_7ffe9a4a747a;
  *(undefined **)(puVar6 + 0x18) = self;
  il2cpp_write_barrier_0();
  uVar14 = FUN_7ffe9bda7d40(0);
  *(undefined4 *)(self + 0xf0) = uVar14;
  if (actarAction == (undefined *)0x0) {
    *(undefined8 *)(puVar6 + 0x10) = 0;
  }
  else {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    plVar7 = plVar12;
    if (bVar2) {
      plVar7 = (longlong *)actarAction;
    }
    *(longlong **)(puVar6 + 0x10) = plVar7;
  }
  plVar7 = (longlong *)(puVar6 + 0x10);
  il2cpp_write_barrier_0();
  PlayerAttackBase_SetSendAtkParam(self,(undefined *)*plVar7,(undefined *)0x0);
  if (DAT_7ffe9cad9b47 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8fc068);
    DAT_7ffe9cad9b47 = '\x01';
  }
  uStack_60 = **(undefined8 **)(_DAT_7ffe9c8fc068 + 0xb8);
  fVar17 = (float)uStack_60;
  fVar18 = *(float *)(*(undefined8 **)(_DAT_7ffe9c8fc068 + 0xb8) + 1);
  fStack_58 = fVar18;
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar3 = FUN_7ffe9bda2160(target,0,0);
  if (cVar3 != '\0') {
    if ((actarAction == (undefined *)0x0) || (lVar8 = FUN_7ffe9bd98a10(actarAction,0), lVar8 == 0))
    goto LAB_7ffe9a4a747a;
    puVar9 = (undefined8 *)FUN_7ffe9bdbf710(auStack_48,lVar8,0);
    uStack_60 = *puVar9;
    fStack_58 = *(float *)(puVar9 + 1);
    if ((target == (undefined *)0x0) || (lVar8 = FUN_7ffe9bd9b890(target,0), lVar8 == 0))
    goto LAB_7ffe9a4a747a;
    puVar9 = (undefined8 *)FUN_7ffe9bdbf710(auStack_48,lVar8,0);
    fStack_40 = *(float *)(puVar9 + 1);
    fVar17 = (float)uStack_60 - (float)*puVar9;
    fVar18 = fStack_58 - fStack_40;
  }
  if (DAT_7ffe9cad9b48 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    DAT_7ffe9cad9b48 = '\x01';
  }
  if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  dVar15 = (double)(fVar17 * fVar17 + 0.0 + fVar18 * fVar18);
  if (dVar15 < 0.0) {
    dVar15 = (double)FUN_7ffe999979e0();
  }
  else {
    auVar16._8_8_ = 0;
    auVar16._0_8_ = dVar15;
    auVar16 = sqrtpd(ZEXT816(0),auVar16);
    dVar15 = auVar16._0_8_;
  }
  *(float *)(self + 0x74) = (float)dVar15;
  plVar10 = (longlong *)*plVar7;
  if (((plVar10 == (longlong *)0x0) ||
      (plVar10 = (longlong *)
                 (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
      plVar10 == (longlong *)0x0)) ||
     (lVar8 = (**(code **)(*plVar10 + 0x1e8))(plVar10,*(undefined8 *)(*plVar10 + 0x1f0)), lVar8 == 0
     )) goto LAB_7ffe9a4a747a;
  cVar3 = FUN_7ffe9a4daa60(lVar8,9);
  if (cVar3 != '\0') {
    plVar10 = (longlong *)*plVar7;
    if (((plVar10 == (longlong *)0x0) ||
        (plVar10 = (longlong *)
                   (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
        plVar10 == (longlong *)0x0)) ||
       (lVar8 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
       lVar8 == 0)) goto LAB_7ffe9a4a747a;
    cVar3 = FUN_7ffe9a7c6d00(lVar8,0x4c7);
    if (cVar3 == '\0') {
      iVar5 = func_0x7ffe9a8fec10(self,0);
      *(int *)(self + 0x78) = (int)((float)iVar5 * _DAT_7ffe9c049cd8);
    }
  }
  cVar3 = (**(code **)(*(longlong *)self + 0x358))(self,*(undefined8 *)(*(longlong *)self + 0x360));
  if (cVar3 == '\0') {
    if (((*(uint *)(self + 0x108) & 0x100) == 0) && ((*(uint *)(self + 0x108) & 0x400) == 0)) {
      plVar10 = (longlong *)*plVar7;
      if ((plVar10 == (longlong *)0x0) ||
         (((plVar10 = (longlong *)
                      (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
           plVar10 == (longlong *)0x0 ||
           (lVar8 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
           lVar8 == 0)) || (*(longlong *)(lVar8 + 0x40) == 0)))) goto LAB_7ffe9a4a747a;
      cVar3 = FUN_7ffe9ad5f0a0(*(longlong *)(lVar8 + 0x40),0x26b,_DAT_7ffe9c9341c8);
      if (cVar3 != '\0') {
        iVar5 = (**(code **)(*(longlong *)self + 0x188))
                          (self,*(undefined8 *)(*(longlong *)self + 400));
        if (iVar5 == 0) {
          puVar11 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c8f3938);
          FUN_7ffe9ac2ed50(puVar11,puVar6,_DAT_7ffe9c8fc158,0);
          PlayerAttackBase_add_EndFunction(self,puVar11,(undefined *)0x0);
        }
        else {
          plVar10 = (longlong *)*plVar7;
          if (((plVar10 == (longlong *)0x0) ||
              (plVar10 = (longlong *)
                         (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
              plVar10 == (longlong *)0x0)) ||
             (lVar8 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
             lVar8 == 0)) goto LAB_7ffe9a4a747a;
          FUN_7ffe9a7cafa0(lVar8,0x26b,0);
        }
      }
      puVar11 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c92eda0);
      FUN_7ffe999e6880(puVar11,puVar6,_DAT_7ffe9c8fc228,0);
      PlayerAttackBase_add_MotionEndFunction(self,puVar11,(undefined *)0x0);
      if ((self[0x108] & 0x10) == 0) {
        iVar5 = (**(code **)(*(longlong *)self + 0x188))
                          (self,*(undefined8 *)(*(longlong *)self + 400));
        plVar10 = (longlong *)*plVar7;
        if (iVar5 == 0) {
          if (((plVar10 == (longlong *)0x0) ||
              (plVar10 = (longlong *)
                         (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
              plVar10 == (longlong *)0x0)) ||
             (lVar8 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
             lVar8 == 0)) goto LAB_7ffe9a4a747a;
          cVar3 = FUN_7ffe9abc2210(lVar8,0x36e,&lStack_68,_DAT_7ffe9c9685a0);
          if (cVar3 != '\0') {
            if (lStack_68 == 0) goto LAB_7ffe9a4a747a;
            FUN_7ffe9a78c380(lStack_68,0);
            plVar10 = (longlong *)*plVar7;
            if (((plVar10 == (longlong *)0x0) ||
                (plVar10 = (longlong *)
                           (**(code **)(*plVar10 + 0x298))
                                     (plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
                plVar10 == (longlong *)0x0)) ||
               (lVar8 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
               lVar8 == 0)) goto LAB_7ffe9a4a747a;
            FUN_7ffe9a7cafa0(lVar8,0x36e);
          }
        }
        else {
          if (((plVar10 == (longlong *)0x0) ||
              (plVar10 = (longlong *)
                         (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
              plVar10 == (longlong *)0x0)) ||
             (lVar8 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)),
             lVar8 == 0)) goto LAB_7ffe9a4a747a;
          cVar3 = FUN_7ffe9abc2210(lVar8,0x69,&lStack_70,_DAT_7ffe9c969198);
          if (cVar3 != '\0') {
            if (lStack_70 == 0) goto LAB_7ffe9a4a747a;
            if (*(char *)(lStack_70 + 0x21) != '\0') {
              iVar5 = (**(code **)(*(longlong *)self + 0x188))(self);
              bVar4 = PlayerAttackBase_ContainsNotApplicableSkill(iVar5,(undefined *)0x0);
              if (bVar4 == 0) {
                *(uint *)(self + 0xf4) = *(uint *)(self + 0xf4) | 4;
                *(undefined4 *)(self + 0x78) = 0x32;
                self[0xf8] = 0xff;
              }
            }
          }
          PlayerAttackBase_ActionStartMagicSkill(self,(undefined *)*plVar7,(undefined *)0x0);
          PlayerAttackBase_RemoveAfterSkillBuf(self,(undefined *)*plVar7,(undefined *)0x0);
        }
      }
    }
    if ((*(uint *)(self + 0x108) & 0x400) != 0) {
      PlayerAttackBase_ActionStartMagicSkill(self,(undefined *)*plVar7,(undefined *)0x0);
    }
    PlayerAttackBase_RemoveUnannouncedDestinationBuf(self,(undefined *)*plVar7,(undefined *)0x0);
    if ((*(uint *)(self + 0x108) & 0x2400) == 0) {
      cVar3 = (**(code **)(*(longlong *)self + 0x208))
                        (self,*(undefined8 *)(*(longlong *)self + 0x210));
      if (cVar3 == '\0') {
        puVar11 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c8f3938);
        FUN_7ffe9ac2ed50(puVar11,puVar6,_DAT_7ffe9c8fc3c8,0);
        PlayerAttackBase_add_EndFunction(self,puVar11,(undefined *)0x0);
      }
      else {
        puVar11 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c92eda0);
        FUN_7ffe999e6880(puVar11,puVar6,_DAT_7ffe9c8fc2f8,0);
        PlayerAttackBase_add_MotionEndFunction(self,puVar11,(undefined *)0x0);
      }
    }
  }
  plVar10 = (longlong *)*plVar7;
  if (((plVar10 == (longlong *)0x0) ||
      (plVar10 = (longlong *)
                 (**(code **)(*plVar10 + 0x298))(plVar10,*(undefined8 *)(*plVar10 + 0x2a0)),
      plVar10 == (longlong *)0x0)) ||
     (lVar8 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0)), lVar8 == 0
     )) goto LAB_7ffe9a4a747a;
  cVar3 = FUN_7ffe9a7cbb30(lVar8,0x22e,&plStack_78,0);
  if (cVar3 != '\0') {
    puVar11 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c9104d8);
    AvoidBreaker_Reset(puVar11,(undefined *)0x0);
    if (puVar11 == (undefined *)0x0) goto LAB_7ffe9a4a747a;
    *(undefined **)(puVar11 + 0x18) = puVar6;
    il2cpp_write_barrier_0();
    if (plStack_78 != (longlong *)0x0) {
      if ((*(byte *)(*plStack_78 + 0x130) < *(byte *)(_DAT_7ffe9c8feb30 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plStack_78 + 200) + -8 +
           (ulonglong)*(byte *)(_DAT_7ffe9c8feb30 + 0x130) * 8) != _DAT_7ffe9c8feb30)) {
        bVar2 = false;
      }
      else {
        bVar2 = true;
      }
      if (bVar2) {
        plVar12 = plStack_78;
      }
    }
    *(longlong **)(puVar11 + 0x10) = plVar12;
    il2cpp_write_barrier_0();
    if (*(longlong *)(puVar11 + 0x10) == 0) goto LAB_7ffe9a4a747a;
    cVar3 = func_0x7ffe99ad7b20(*(longlong *)(puVar11 + 0x10),2);
    if (cVar3 != '\0') {
      puVar6 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c8f3938);
      FUN_7ffe9ac2ed50(puVar6,puVar11,_DAT_7ffe9c8fc498,0);
      PlayerAttackBase_add_EndFunction(self,puVar6,(undefined *)0x0);
    }
  }
  iVar5 = (**(code **)(*(longlong *)self + 0x588))(self,*(undefined8 *)(*(longlong *)self + 0x590));
  if (((iVar5 == 9) && ((self[0x108] & 0x10) == 0)) &&
     (iVar5 = (**(code **)(*(longlong *)self + 0x188))
                        (self,*(undefined8 *)(*(longlong *)self + 400)), iVar5 != 0x13f)) {
    plVar7 = (longlong *)*plVar7;
    if (((plVar7 == (longlong *)0x0) ||
        (plVar12 = (longlong *)
                   (**(code **)(*plVar7 + 0x298))(plVar7,*(undefined8 *)(*plVar7 + 0x2a0)),
        plVar12 == (longlong *)0x0)) ||
       (lVar8 = (**(code **)(*plVar12 + 0x1c8))(plVar12,*(undefined8 *)(*plVar12 + 0x1d0)),
       lVar8 == 0)) {
LAB_7ffe9a4a747a:
      FUN_7ffe9996d7a0();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    cVar3 = FUN_7ffe9a7cbb30(lVar8,0x12d,&plStack_78,0);
    plVar12 = plStack_78;
    if ((cVar3 != '\0') && (plStack_78 != (longlong *)0x0)) {
      if ((*(byte *)(_DAT_7ffe9c961b90 + 0x130) <= *(byte *)(*plStack_78 + 0x130)) &&
         (((*(longlong *)
             (*(longlong *)(*plStack_78 + 200) + -8 +
             (ulonglong)*(byte *)(_DAT_7ffe9c961b90 + 0x130) * 8) == _DAT_7ffe9c961b90 &&
           (plStack_78 != (longlong *)0x0)) &&
          (lVar8 = plStack_78[4],
          (**(code **)(*plStack_78 + 0x2a8))(plStack_78,*(undefined8 *)(*plStack_78 + 0x2b0)),
          (int)lVar8 != (int)plVar12[4])))) {
        if (actarAction == (undefined *)0x0) goto LAB_7ffe9a4a747a;
        uVar13 = FUN_7ffe9bd98960(actarAction,0);
        FUN_7ffe9a6a3940(uVar13,(int)plVar12[4],0);
      }
    }
  }
  return;
}

