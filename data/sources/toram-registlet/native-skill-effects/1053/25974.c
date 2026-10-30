
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SkullShakerAction_calcPlayerToMobDamage
               (undefined *thisObject,undefined *playerAction,undefined *mobAction,
               undefined *methodInfo)

{
  uint uVar1;
  longlong lVar2;
  longlong lVar3;
  code *pcVar4;
  bool bVar5;
  longlong lVar6;
  byte bVar7;
  char cVar8;
  undefined2 uVar9;
  undefined4 uVar10;
  undefined4 uVar11;
  int iVar12;
  int iVar13;
  longlong *plVar14;
  longlong lVar15;
  undefined *puVar16;
  undefined8 uVar17;
  undefined *puVar18;
  undefined8 uVar19;
  undefined4 uVar20;
  float afStackX_10 [2];
  undefined8 in_stack_ffffffffffffff98;
  undefined8 in_stack_ffffffffffffffa0;
  undefined4 uVar21;
  longlong *aplStack_38 [2];
  
  uVar20 = (undefined4)((ulonglong)in_stack_ffffffffffffff98 >> 0x20);
  uVar21 = (undefined4)((ulonglong)in_stack_ffffffffffffffa0 >> 0x20);
  if (DAT_7ffe9cadf0f9 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92dfe0);
    FUN_7ffe9996d590(&DAT_7ffe9c955398);
    FUN_7ffe9996d590(&DAT_7ffe9c920098);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c913488);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c94a078);
    FUN_7ffe9996d590(&DAT_7ffe9c94aa68);
    FUN_7ffe9996d590(&DAT_7ffe9c94c228);
    DAT_7ffe9cadf0f9 = '\x01';
  }
  puVar18 = (undefined *)0x0;
  iVar12 = 0;
  afStackX_10[0] = 0.0;
  aplStack_38[0] = (longlong *)0x0;
  if (((playerAction != (undefined *)0x0) &&
      (plVar14 = (longlong *)
                 (**(code **)(*(longlong *)playerAction + 0x298))
                           (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
      plVar14 != (longlong *)0x0)) &&
     (lVar15 = (**(code **)(*plVar14 + 0x1a8))(plVar14,*(undefined8 *)(*plVar14 + 0x1b0)),
     lVar15 != 0)) {
    uVar10 = FUN_7ffe99742ec0(0x1b,_DAT_7ffe9c940d40,lVar15);
    bVar7 = FUN_7ffe9a4b33f0(thisObject,uVar10,mobAction,0);
    puVar16 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c94a078);
    FUN_7ffe9a6596c0(puVar16,0);
    uVar10 = (**(code **)(*(longlong *)thisObject + 0x198))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
    uVar11 = (**(code **)(*(longlong *)thisObject + 0x588))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x590));
    puVar16 = PlayerAttackBase_TemplateAssignment
                        (thisObject,puVar16,playerAction,mobAction,
                         (undefined *)CONCAT44(uVar20,uVar10),(undefined *)CONCAT44(uVar21,uVar11),0
                         ,bVar7,(undefined *)0x0);
    if (puVar16 != (undefined *)0x0) {
      SkillCalcTemplate_AddRate
                (puVar16,(undefined *)0x12,(float)*(int *)(thisObject + 0x124) / 100.0,
                 (undefined *)0x0);
      FUN_7ffe9a657a50(puVar16,8);
      uVar17 = func_0x7ffe99940040(_DAT_7ffe9c920098);
      FUN_7ffe9a8f6350(uVar17,mobAction,0);
      lVar15 = FUN_7ffe9a4b4370(thisObject,uVar17,puVar16,1,0);
      if (lVar15 != 0) {
        iVar13 = *(int *)(lVar15 + 0x1c);
        if ((iVar13 != 0) && (*(int *)(lVar15 + 0x34) != 1)) {
          bVar5 = false;
          cVar8 = FUN_7ffe9a4b2fb0(thisObject,0xe,*(undefined4 *)(thisObject + 300),playerAction,
                                   mobAction,afStackX_10,0);
          if (cVar8 != '\0') {
            if (*(longlong *)(lVar15 + 0x38) == 0) goto LAB_7ffe9a717072;
            FUN_7ffe9a8ffe30(*(longlong *)(lVar15 + 0x38),0xe);
            bVar5 = true;
          }
          cVar8 = FUN_7ffe9a4b2fb0(thisObject,3,*(undefined4 *)(thisObject + 0x130),playerAction,
                                   mobAction,afStackX_10,0);
          if (cVar8 == '\0') {
            if ((mobAction == (undefined *)0x0) ||
               (puVar18 = (undefined *)FUN_7ffe99742ec0(0xb,_DAT_7ffe9c9724e0,mobAction),
               puVar18 == (undefined *)0x0)) goto LAB_7ffe9a717072;
            bVar7 = FUN_7ffe9a2ac880(puVar18,0x12,(undefined *)aplStack_38,(undefined *)0x0);
            if (bVar7 != 0) {
              if (aplStack_38[0] == (longlong *)0x0) goto LAB_7ffe9a717072;
              iVar12 = (**(code **)(*aplStack_38[0] + 0x1a8))
                                 (aplStack_38[0],*(undefined8 *)(*aplStack_38[0] + 0x1b0));
            }
            if ((*(undefined **)(thisObject + 0x140) == (undefined *)0x0) ||
               (iVar13 = GemCartBufferBase_GetValue
                                   (*(undefined **)(thisObject + 0x140),(undefined *)0x2,
                                    (undefined *)0x0), iVar12 < iVar13)) {
              lVar2 = *(longlong *)(lVar15 + 0x38);
              uVar17 = func_0x7ffe99940040(_DAT_7ffe9c94c228);
              FUN_7ffe9a2acde0(uVar17,iVar12 + 1,0);
              if (lVar2 == 0) goto LAB_7ffe9a717072;
              *(undefined8 *)(lVar2 + 0xb0) = uVar17;
              il2cpp_write_barrier_0();
            }
          }
          else {
            if (bVar5) {
              if (*(longlong *)(thisObject + 0x80) == 0) goto LAB_7ffe9a717072;
              FUN_7ffe99743100(*(longlong *)(thisObject + 0x80),lVar15,_DAT_7ffe9c913488);
              lVar15 = func_0x7ffe99940040(_DAT_7ffe9c920098);
              if (mobAction != (undefined *)0x0) {
                if ((*(byte *)(*(longlong *)mobAction + 0x130) <
                     *(byte *)(_DAT_7ffe9c955398 + 0x130)) ||
                   (*(longlong *)
                     (*(longlong *)(*(longlong *)mobAction + 200) + -8 +
                     (ulonglong)*(byte *)(_DAT_7ffe9c955398 + 0x130) * 8) != _DAT_7ffe9c955398)) {
                  bVar5 = false;
                }
                else {
                  bVar5 = true;
                }
                if (bVar5) {
                  puVar18 = mobAction;
                }
              }
              FUN_7ffe9a8f6490(lVar15,puVar18,0);
              if (lVar15 == 0) goto LAB_7ffe9a717072;
              uVar17 = *(undefined8 *)(lVar15 + 0x48);
              *(int *)(lVar15 + 0x1c) = iVar13;
              *(undefined4 *)(lVar15 + 0x34) = 0;
              uVar19 = func_0x7ffe99940040(_DAT_7ffe9c94aa68);
              FUN_7ffe9a8fff70(uVar19,uVar17,0);
              *(undefined8 *)(lVar15 + 0x38) = uVar19;
              il2cpp_write_barrier_0();
              if (*(longlong *)(lVar15 + 0x38) == 0) goto LAB_7ffe9a717072;
              *(undefined1 *)(*(longlong *)(lVar15 + 0x38) + 0x38) = 1;
              if (*(longlong *)(lVar15 + 0x38) == 0) goto LAB_7ffe9a717072;
              func_0x7ffe9a900040(*(longlong *)(lVar15 + 0x38),0,0);
              if (*(longlong *)(lVar15 + 0x38) == 0) goto LAB_7ffe9a717072;
              *(int *)(*(longlong *)(lVar15 + 0x38) + 0x14) = iVar13;
              lVar2 = *(longlong *)(lVar15 + 0x38);
              uVar9 = FUN_7ffe9a4ada90(thisObject,0);
              if (lVar2 == 0) goto LAB_7ffe9a717072;
              func_0x7ffe9a8fbbf0(lVar2,uVar9,0);
            }
            if (*(longlong *)(lVar15 + 0x38) == 0) goto LAB_7ffe9a717072;
            *(undefined4 *)(*(longlong *)(lVar15 + 0x38) + 0x8c) = 3;
            lVar2 = *(longlong *)(lVar15 + 0x38);
            if (*(int *)(_DAT_7ffe9c92dfe0 + 0xe0) == 0) {
              func_0x7ffe9996d830();
            }
            uVar20 = FUN_7ffe9a4db1f0(3);
            if (lVar2 == 0) goto LAB_7ffe9a717072;
            *(undefined4 *)(lVar2 + 0x94) = uVar20;
            lVar2 = *(longlong *)(lVar15 + 0x38);
            uVar20 = FUN_7ffe9a4db080(3);
            if (lVar2 == 0) goto LAB_7ffe9a717072;
            *(undefined4 *)(lVar2 + 0x98) = uVar20;
            lVar2 = *(longlong *)(lVar15 + 0x38);
            if (lVar2 == 0) goto LAB_7ffe9a717072;
            *(float *)(lVar2 + 0x9c) = afStackX_10[0] + *(float *)(lVar2 + 0x9c);
          }
        }
        lVar6 = _DAT_7ffe9c913488;
        lVar2 = *(longlong *)(thisObject + 0x80);
        if (lVar2 != 0) {
          *(int *)(lVar2 + 0x1c) = *(int *)(lVar2 + 0x1c) + 1;
          lVar3 = *(longlong *)(lVar2 + 0x10);
          uVar1 = *(uint *)(lVar2 + 0x18);
          if (lVar3 != 0) {
            if (uVar1 < *(uint *)(lVar3 + 0x18)) {
              *(uint *)(lVar2 + 0x18) = uVar1 + 1;
              if (*(uint *)(lVar3 + 0x18) <= uVar1) {
                FUN_7ffe9996d790();
                pcVar4 = (code *)swi(3);
                (*pcVar4)();
                return;
              }
              *(longlong *)(lVar3 + 0x20 + (longlong)(int)uVar1 * 8) = lVar15;
              il2cpp_write_barrier_0();
            }
            else {
              FUN_7ffe9afd58b0(lVar2,lVar15,
                               *(undefined8 *)
                                (*(longlong *)(*(longlong *)(lVar6 + 0x20) + 0xc0) + 0x70));
            }
            return;
          }
        }
      }
    }
  }
LAB_7ffe9a717072:
  FUN_7ffe9996d7a0();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

