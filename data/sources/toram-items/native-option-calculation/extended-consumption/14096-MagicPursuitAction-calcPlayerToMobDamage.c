
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MagicPursuitAction_calcPlayerToMobDamage
               (undefined *self,undefined *playerAction,undefined *mobAction,undefined *methodInfo)

{
  uint uVar1;
  longlong lVar2;
  code *pcVar3;
  bool bVar4;
  longlong lVar5;
  char cVar6;
  int iVar7;
  longlong *plVar8;
  longlong lVar9;
  undefined *puVar10;
  undefined *puVar11;
  float fVar12;
  longlong lStackX_10;
  undefined8 in_stack_ffffffffffffffa8;
  undefined4 uVar13;
  uint in_stack_ffffffffffffffb4;
  undefined4 in_stack_ffffffffffffffb8;
  undefined4 in_stack_ffffffffffffffbc;
  ulonglong in_stack_ffffffffffffffc0;
  
  uVar13 = (undefined4)((ulonglong)in_stack_ffffffffffffffa8 >> 0x20);
  if (DAT_7ffe9cadde7b == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c920098);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c913488);
    FUN_7ffe9996d590(&DAT_7ffe9c8f6ba0);
    FUN_7ffe9996d590(&DAT_7ffe9c94a078);
    DAT_7ffe9cadde7b = '\x01';
  }
  lStackX_10 = 0;
  if (playerAction == (undefined *)0x0) goto LAB_7ffe9a492f8c;
  plVar8 = (longlong *)
           (**(code **)(*(longlong *)playerAction + 0x298))
                     (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if (plVar8 == (longlong *)0x0) goto LAB_7ffe9a492f8c;
  lVar9 = (**(code **)(*plVar8 + 0x208))(plVar8,*(undefined8 *)(*plVar8 + 0x210));
  if (lVar9 == 0) goto LAB_7ffe9a492f8c;
  iVar7 = FUN_7ffe9a51e120(lVar9,0x9a,0);
  fVar12 = (float)iVar7 + 0.0;
  plVar8 = (longlong *)
           (**(code **)(*(longlong *)playerAction + 0x298))
                     (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if (plVar8 == (longlong *)0x0) goto LAB_7ffe9a492f8c;
  lVar9 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0));
  if ((lVar9 == 0) || (*(longlong *)(lVar9 + 0x40) == 0)) goto LAB_7ffe9a492f8c;
  cVar6 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x40),0x401,&lStackX_10,_DAT_7ffe9c934418);
  if (cVar6 == '\0') {
    plVar8 = (longlong *)
             (**(code **)(*(longlong *)playerAction + 0x298))
                       (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if (plVar8 == (longlong *)0x0) goto LAB_7ffe9a492f8c;
    lVar9 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0));
    if ((lVar9 == 0) || (*(longlong *)(lVar9 + 0x40) == 0)) goto LAB_7ffe9a492f8c;
    cVar6 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x40),0x408,&lStackX_10,_DAT_7ffe9c934418);
    if (cVar6 != '\0') goto LAB_7ffe9a492d21;
  }
  else {
LAB_7ffe9a492d21:
    if (lStackX_10 == 0) goto LAB_7ffe9a492f8c;
    iVar7 = func_0x7ffe9a7a2140(lStackX_10,0x32);
    fVar12 = fVar12 + (float)iVar7;
  }
  plVar8 = (longlong *)
           (**(code **)(*(longlong *)playerAction + 0x298))
                     (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if (plVar8 != (longlong *)0x0) {
    lVar9 = (**(code **)(*plVar8 + 0x1c8))(plVar8,*(undefined8 *)(*plVar8 + 0x1d0));
    if ((lVar9 != 0) && (*(longlong *)(lVar9 + 0x40) != 0)) {
      cVar6 = FUN_7ffe9ad8e670(*(longlong *)(lVar9 + 0x40),0x3d6,&lStackX_10,_DAT_7ffe9c934418);
      if (cVar6 != '\0') {
        if (lStackX_10 == 0) goto LAB_7ffe9a492f8c;
        iVar7 = func_0x7ffe9a7a2140(lStackX_10,0x56);
        fVar12 = fVar12 + (float)iVar7;
      }
      puVar10 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c94a078);
      FUN_7ffe9a6596c0(puVar10,0);
      puVar11 = (undefined *)CONCAT44(uVar13,2);
      puVar10 = PlayerAttackBase_HitReactionAssign
                          (self,puVar10,playerAction,mobAction,puVar11,0,
                           (undefined *)
                           (CONCAT44(in_stack_ffffffffffffffbc,in_stack_ffffffffffffffb8) &
                           0xffffffffffffff00),
                           (undefined *)(in_stack_ffffffffffffffc0 & 0xffffffffffffff00),
                           (undefined *)0x0);
      puVar10 = PlayerAttackBase_TemplateAssignment
                          (self,puVar10,playerAction,mobAction,
                           (undefined *)CONCAT44((int)((ulonglong)puVar11 >> 0x20),2),
                           (undefined *)((ulonglong)in_stack_ffffffffffffffb4 << 0x20),0,
                           (undefined *)0x0);
      if (puVar10 != (undefined *)0x0) {
        FUN_7ffe9a657c40(puVar10,0x12,fVar12 / _DAT_7ffe9c049cfc);
        puVar11 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c920098);
        FUN_7ffe9a8f6350(puVar11,mobAction,0);
        puVar10 = PlayerAttackBase_templateToDamageData
                            (self,puVar11,puVar10,*(int *)(self + 0x120),(undefined *)0x0);
        if (self[0x118] != '\0') {
          if ((puVar10 == (undefined *)0x0) || (*(longlong *)(puVar10 + 0x38) == 0))
          goto LAB_7ffe9a492f8c;
          puVar11 = (undefined *)0x0;
          if (mobAction != (undefined *)0x0) {
            if ((*(byte *)(*(longlong *)mobAction + 0x130) < *(byte *)(_DAT_7ffe9c8f6ba0 + 0x130))
               || (*(longlong *)
                    (*(longlong *)(*(longlong *)mobAction + 200) + -8 +
                    (ulonglong)*(byte *)(_DAT_7ffe9c8f6ba0 + 0x130) * 8) != _DAT_7ffe9c8f6ba0)) {
              bVar4 = false;
            }
            else {
              bVar4 = true;
            }
            if (bVar4) {
              puVar11 = mobAction;
            }
          }
          *(bool *)(*(longlong *)(puVar10 + 0x38) + 0x38) = puVar11 != (undefined *)0x0;
        }
        lVar5 = _DAT_7ffe9c913488;
        lVar9 = *(longlong *)(self + 0x80);
        if (lVar9 != 0) {
          *(int *)(lVar9 + 0x1c) = *(int *)(lVar9 + 0x1c) + 1;
          lVar2 = *(longlong *)(lVar9 + 0x10);
          uVar1 = *(uint *)(lVar9 + 0x18);
          if (lVar2 != 0) {
            if (uVar1 < *(uint *)(lVar2 + 0x18)) {
              *(uint *)(lVar9 + 0x18) = uVar1 + 1;
              if (*(uint *)(lVar2 + 0x18) <= uVar1) {
                FUN_7ffe9996d790();
                pcVar3 = (code *)swi(3);
                (*pcVar3)();
                return;
              }
              *(undefined **)(lVar2 + 0x20 + (longlong)(int)uVar1 * 8) = puVar10;
              il2cpp_write_barrier_0();
            }
            else {
              FUN_7ffe9afd58b0(lVar9,puVar10,
                               *(undefined8 *)
                                (*(longlong *)(*(longlong *)(lVar5 + 0x20) + 0xc0) + 0x70));
            }
            *(int *)(self + 0x104) = (int)fVar12;
            return;
          }
        }
      }
    }
  }
LAB_7ffe9a492f8c:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

