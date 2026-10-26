
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int MobCurrentHPRateAttack_CalcTemporaryDamage
              (undefined *self,undefined *mobAction,undefined *playerAction,undefined *methodInfo)

{
  code *pcVar1;
  bool bVar2;
  char cVar3;
  int iVar4;
  int iVar5;
  longlong lVar6;
  longlong *plVar7;
  longlong lVar8;
  undefined *puVar9;
  float fVar10;
  uint in_stack_ffffffffffffffdc;
  uint7 in_stack_ffffffffffffffe1;
  
  if (DAT_7ffe9cadd7eb == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8ff718);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    DAT_7ffe9cadd7eb = '\x01';
  }
  if (playerAction == (undefined *)0x0) {
LAB_7ffe9a3844ad:
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    iVar5 = (*pcVar1)();
    return iVar5;
  }
  lVar6 = (**(code **)(*(longlong *)playerAction + 0x298))
                    (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
  if (lVar6 != 0) {
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    if ((*(byte *)(*(longlong *)playerAction + 0x130) < *(byte *)(_DAT_7ffe9c8ff718 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)playerAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c8ff718 + 0x130) * 8) != _DAT_7ffe9c8ff718)) {
      bVar2 = false;
    }
    else {
      bVar2 = true;
    }
    puVar9 = (undefined *)0x0;
    if (bVar2) {
      puVar9 = playerAction;
    }
    cVar3 = FUN_7ffe9bda2160(puVar9,0,0);
    if (cVar3 == '\0') {
      if (*(longlong *)(self + 0xa0) != 0) {
        pcVar1 = *(code **)(*(longlong *)playerAction + 0x298);
        if ((*(byte *)(*(longlong *)(self + 0xa0) + 0x6c) & 2) == 0) {
          plVar7 = (longlong *)(*pcVar1)();
          if (plVar7 != (longlong *)0x0) {
            lVar6 = (**(code **)(*plVar7 + 0x1a8))(plVar7,*(undefined8 *)(*plVar7 + 0x1b0));
            plVar7 = (longlong *)
                     (**(code **)(*(longlong *)playerAction + 0x298))
                               (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
            if ((plVar7 != (longlong *)0x0) &&
               (lVar8 = (**(code **)(*plVar7 + 0x178))(plVar7,*(undefined8 *)(*plVar7 + 0x180)),
               lVar8 != 0)) {
              if (*(int *)(lVar8 + 0x14) == 1) {
                return 0;
              }
              if (((*(longlong *)(self + 0xa0) != 0) &&
                  (plVar7 = (longlong *)
                            (**(code **)(*(longlong *)playerAction + 0x298))
                                      (playerAction,
                                       *(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
                  plVar7 != (longlong *)0x0)) &&
                 ((lVar8 = (**(code **)(*plVar7 + 0x178))(plVar7,*(undefined8 *)(*plVar7 + 0x180)),
                  lVar8 != 0 && (iVar5 = *(int *)(lVar8 + 0x14), mobAction != (undefined *)0x0)))) {
                puVar9 = (undefined *)func_0x7ffe9a2ef690(mobAction,0);
                iVar4 = MobAttackBase_CalcBaseAttack(self,puVar9,(undefined *)0x0);
                if (lVar6 != 0) {
                  iVar5 = FUN_7ffe99749320(0x2c,_DAT_7ffe9c940d40,lVar6,
                                           (int)((float)(iVar4 * iVar5) / _DAT_7ffe9c049cfc));
                  iVar4 = FUN_7ffe99742ec0(0x15,_DAT_7ffe9c940d40);
                  fVar10 = MobAttackBase_calcEquipDefPercent(self,(float)iVar4,(undefined *)0x0);
                  iVar5 = MobAttackBase_CalcLastDamage
                                    (self,mobAction,playerAction,(int)(fVar10 * (float)iVar5),
                                     (undefined *)((ulonglong)in_stack_ffffffffffffffdc << 0x20),
                                     (undefined *)((ulonglong)in_stack_ffffffffffffffe1 << 8),
                                     (undefined *)0x0);
                  if (iVar5 < 1) {
                    return 1;
                  }
                  return iVar5;
                }
              }
            }
          }
        }
        else {
          plVar7 = (longlong *)
                   (*pcVar1)(playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
          if ((plVar7 != (longlong *)0x0) &&
             (lVar6 = (**(code **)(*plVar7 + 0x178))(plVar7,*(undefined8 *)(*plVar7 + 0x180)),
             lVar6 != 0)) {
            if (*(int *)(lVar6 + 0x14) == 1) {
              return 0;
            }
            plVar7 = (longlong *)
                     (**(code **)(*(longlong *)playerAction + 0x298))
                               (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
            if (((plVar7 != (longlong *)0x0) &&
                (lVar6 = (**(code **)(*plVar7 + 0x178))(plVar7,*(undefined8 *)(*plVar7 + 0x180)),
                lVar6 != 0)) && (*(longlong *)(self + 0xa0) != 0)) {
              iVar5 = (int)((float)(*(int *)(*(longlong *)(self + 0xa0) + 0x14) *
                                   *(int *)(lVar6 + 0x14)) / _DAT_7ffe9c049cfc);
              if (iVar5 < 1) {
                return 1;
              }
              return iVar5;
            }
          }
        }
      }
      goto LAB_7ffe9a3844ad;
    }
  }
  return 0;
}

