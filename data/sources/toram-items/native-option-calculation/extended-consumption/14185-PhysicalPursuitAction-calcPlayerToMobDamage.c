
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PhysicalPursuitAction_calcPlayerToMobDamage
               (undefined *self,undefined *playerAction,undefined *mobAction,undefined *methodInfo)

{
  uint uVar1;
  longlong lVar2;
  code *pcVar3;
  bool bVar4;
  longlong lVar5;
  char cVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  longlong *plVar10;
  longlong lVar11;
  undefined *puVar12;
  undefined *puVar13;
  longlong *plStackX_10;
  undefined8 in_stack_ffffffffffffff98;
  undefined4 uVar14;
  uint in_stack_ffffffffffffffa4;
  longlong *aplStack_48 [4];
  
  uVar14 = (undefined4)((ulonglong)in_stack_ffffffffffffff98 >> 0x20);
  if (DAT_7ffe9caddea1 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c920098);
    FUN_7ffe9996d590(&DAT_7ffe9c91aa80);
    FUN_7ffe9996d590(&DAT_7ffe9c93ed20);
    FUN_7ffe9996d590(&DAT_7ffe9c913488);
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f6ba0);
    FUN_7ffe9996d590(&DAT_7ffe9c94a078);
    DAT_7ffe9caddea1 = '\x01';
  }
  plStackX_10 = (longlong *)0x0;
  aplStack_48[0] = (longlong *)0x0;
  if (playerAction != (undefined *)0x0) {
    plVar10 = (longlong *)
              (**(code **)(*(longlong *)playerAction + 0x298))
                        (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
    if (plVar10 != (longlong *)0x0) {
      lVar11 = (**(code **)(*plVar10 + 0x208))(plVar10,*(undefined8 *)(*plVar10 + 0x210));
      if (lVar11 != 0) {
        iVar7 = FUN_7ffe9a51e120(lVar11,0x99,0);
        plVar10 = (longlong *)
                  (**(code **)(*(longlong *)playerAction + 0x298))
                            (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if (plVar10 != (longlong *)0x0) {
          lVar11 = (**(code **)(*plVar10 + 0x1c8))(plVar10,*(undefined8 *)(*plVar10 + 0x1d0));
          if (lVar11 != 0) {
            cVar6 = FUN_7ffe9a7cbb30(lVar11,0x32,&plStackX_10,0);
            if (cVar6 != '\0') {
              if (plStackX_10 == (longlong *)0x0) goto LAB_7ffe9a4a5c89;
              iVar8 = (**(code **)(*plStackX_10 + 0x1f8))
                                (plStackX_10,0x55,*(undefined8 *)(*plStackX_10 + 0x200));
              iVar7 = iVar7 + iVar8;
            }
            puVar12 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c94a078);
            FUN_7ffe9a6596c0(puVar12,0);
            if (puVar12 != (undefined *)0x0) {
              FUN_7ffe9a658f90(puVar12,0,1,0);
              FUN_7ffe9a658f90(puVar12,4,0);
              FUN_7ffe9a658f90(puVar12,6,0);
              if (mobAction != (undefined *)0x0) {
                lVar11 = FUN_7ffe99742ec0(9,_DAT_7ffe9c9724e0,mobAction);
                if (lVar11 != 0) {
                  uVar9 = FUN_7ffe99742ec0(7,_DAT_7ffe9c93ed20,lVar11);
                  cVar6 = FUN_7ffe9a8fea70(self,100,0);
                  if (cVar6 == '\0') {
                    cVar6 = FUN_7ffe9a8fea70(self,100,uVar9);
                    if (cVar6 != '\0') {
                      FUN_7ffe9a658f90(puVar12,0x20,1);
                      lVar11 = FUN_7ffe99742ec0(0xb,_DAT_7ffe9c9724e0,mobAction);
                      if (lVar11 == 0) goto LAB_7ffe9a4a5c89;
                      cVar6 = FUN_7ffe9a2ac880(lVar11,4,aplStack_48);
                      if (cVar6 != '\0') {
                        if (aplStack_48[0] == (longlong *)0x0) goto LAB_7ffe9a4a5c89;
                        if (((*(byte *)(*aplStack_48[0] + 0x130) <
                              *(byte *)(_DAT_7ffe9c91aa80 + 0x130)) ||
                            (*(longlong *)
                              (*(longlong *)(*aplStack_48[0] + 200) + -8 +
                              (ulonglong)*(byte *)(_DAT_7ffe9c91aa80 + 0x130) * 8) !=
                             _DAT_7ffe9c91aa80)) || (aplStack_48[0] == (longlong *)0x0)) {
                          FUN_7ffe9996c950(aplStack_48[0]);
                          pcVar3 = (code *)swi(3);
                          (*pcVar3)();
                          return;
                        }
                        FUN_7ffe9a2ea460(aplStack_48[0],0);
                        if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
                          func_0x7ffe9996d830();
                        }
                        func_0x7ffe9b506c10();
                      }
                      FUN_7ffe9a658e30(puVar12,0x21);
                    }
                  }
                  puVar12 = PlayerAttackBase_TemplateAssignment
                                      (self,puVar12,playerAction,mobAction,
                                       (undefined *)CONCAT44(uVar14,1),
                                       (undefined *)((ulonglong)in_stack_ffffffffffffffa4 << 0x20),0
                                       ,(undefined *)0x0);
                  if (puVar12 != (undefined *)0x0) {
                    FUN_7ffe9a657c40(puVar12,0x12,(float)iVar7 / _DAT_7ffe9c049cfc);
                    puVar13 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c920098);
                    FUN_7ffe9a8f6350(puVar13,mobAction,0);
                    puVar12 = PlayerAttackBase_templateToDamageData
                                        (self,puVar13,puVar12,1,(undefined *)0x0);
                    if (self[0x118] != '\0') {
                      if ((puVar12 == (undefined *)0x0) || (*(longlong *)(puVar12 + 0x38) == 0))
                      goto LAB_7ffe9a4a5c89;
                      if ((*(byte *)(*(longlong *)mobAction + 0x130) <
                           *(byte *)(_DAT_7ffe9c8f6ba0 + 0x130)) ||
                         (*(longlong *)
                           (*(longlong *)(*(longlong *)mobAction + 200) + -8 +
                           (ulonglong)*(byte *)(_DAT_7ffe9c8f6ba0 + 0x130) * 8) != _DAT_7ffe9c8f6ba0
                         )) {
                        bVar4 = false;
                      }
                      else {
                        bVar4 = true;
                      }
                      puVar13 = (undefined *)0x0;
                      if (bVar4) {
                        puVar13 = mobAction;
                      }
                      *(bool *)(*(longlong *)(puVar12 + 0x38) + 0x38) = puVar13 != (undefined *)0x0;
                    }
                    lVar5 = _DAT_7ffe9c913488;
                    lVar11 = *(longlong *)(self + 0x80);
                    if (lVar11 != 0) {
                      *(int *)(lVar11 + 0x1c) = *(int *)(lVar11 + 0x1c) + 1;
                      lVar2 = *(longlong *)(lVar11 + 0x10);
                      uVar1 = *(uint *)(lVar11 + 0x18);
                      if (lVar2 != 0) {
                        if (uVar1 < *(uint *)(lVar2 + 0x18)) {
                          *(uint *)(lVar11 + 0x18) = uVar1 + 1;
                          if (*(uint *)(lVar2 + 0x18) <= uVar1) {
                            FUN_7ffe9996d790();
                            pcVar3 = (code *)swi(3);
                            (*pcVar3)();
                            return;
                          }
                          *(undefined **)(lVar2 + 0x20 + (longlong)(int)uVar1 * 8) = puVar12;
                          il2cpp_write_barrier_0();
                        }
                        else {
                          FUN_7ffe9afd58b0(lVar11,puVar12,
                                           *(undefined8 *)
                                            (*(longlong *)(*(longlong *)(lVar5 + 0x20) + 0xc0) +
                                            0x70));
                        }
                        *(int *)(self + 0x104) = iVar7;
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
LAB_7ffe9a4a5c89:
  FUN_7ffe9996d7a0();
  pcVar3 = (code *)swi(3);
  (*pcVar3)();
  return;
}

