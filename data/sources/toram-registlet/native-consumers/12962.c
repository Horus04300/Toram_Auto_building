
/* WARNING: Type propagation algorithm not settling */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PlayerActionManager_Damaged
               (undefined *thisObject,undefined *actor,undefined *action,undefined *damageData,
               byte id,undefined *methodInfo)

{
  code *pcVar1;
  float fVar2;
  char cVar3;
  char cVar4;
  byte bVar5;
  int iVar6;
  uint uVar7;
  int iVar8;
  uint uVar9;
  int iVar10;
  longlong *plVar11;
  undefined8 uVar12;
  longlong lVar13;
  longlong *plVar14;
  undefined *puVar15;
  undefined8 *puVar16;
  longlong lVar17;
  longlong *plVar18;
  undefined1 uVar19;
  byte bVar20;
  bool bVar21;
  undefined4 uVar22;
  undefined4 uVar23;
  undefined4 uVar24;
  undefined4 uVar25;
  float fVar26;
  byte bStackX_8;
  undefined8 uVar27;
  undefined8 in_stack_ffffffffffffff00;
  ulonglong uVar28;
  longlong *plStack_d8;
  char cStack_d0;
  undefined8 uStack_c8;
  float fStack_c0;
  longlong lStack_b8;
  undefined8 uStack_b0;
  float fStack_a8;
  int iStack_a0;
  longlong lStack_98;
  undefined8 uStack_90;
  float fStack_88;
  longlong *plStack_80;
  longlong lStack_78;
  longlong lStack_70;
  longlong alStack_68 [6];
  
  if (DAT_7ffe9caddca1 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92dfe0);
    FUN_7ffe9996d590(&DAT_7ffe9c92ee68);
    FUN_7ffe9996d590(&DAT_7ffe9c9368c8);
    FUN_7ffe9996d590(&DAT_7ffe9c960fa0);
    FUN_7ffe9996d590(&DAT_7ffe9c9612c8);
    FUN_7ffe9996d590(&DAT_7ffe9c966a68);
    FUN_7ffe9996d590(&DAT_7ffe9c973c28);
    FUN_7ffe9996d590(&DAT_7ffe9c935988);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c8f0840);
    FUN_7ffe9996d590(&DAT_7ffe9c8f3dd8);
    FUN_7ffe9996d590(&DAT_7ffe9c8f42b8);
    FUN_7ffe9996d590(&DAT_7ffe9c92d5c8);
    FUN_7ffe9996d590(&DAT_7ffe9c95f2c8);
    FUN_7ffe9996d590(&DAT_7ffe9c917ea0);
    FUN_7ffe9996d590(&DAT_7ffe9c9279a8);
    FUN_7ffe9996d590(&DAT_7ffe9c928ba0);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c9530e0);
    FUN_7ffe9996d590(&DAT_7ffe9c9573c0);
    FUN_7ffe9996d590(&DAT_7ffe9c972b60);
    FUN_7ffe9996d590(&DAT_7ffe9c8feb30);
    FUN_7ffe9996d590(&DAT_7ffe9c900bb0);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c912320);
    FUN_7ffe9996d590(&DAT_7ffe9c914fd0);
    FUN_7ffe9996d590(&DAT_7ffe9c9690c8);
    FUN_7ffe9996d590(&DAT_7ffe9c969990);
    FUN_7ffe9996d590(&DAT_7ffe9c969a58);
    FUN_7ffe9996d590(&DAT_7ffe9c969d88);
    FUN_7ffe9996d590(&DAT_7ffe9c95f380);
    FUN_7ffe9996d590(&DAT_7ffe9c8f6978);
    DAT_7ffe9caddca1 = '\x01';
  }
  plVar18 = (longlong *)0x0;
  iVar10 = 0;
  plStack_d8 = (longlong *)0x0;
  plStack_80 = (longlong *)0x0;
  lStack_b8 = 0;
  lStack_78 = 0;
  lStack_98 = 0;
  alStack_68[0] = 0;
  alStack_68[1] = 0;
  lStack_70 = 0;
  uStack_90 = 0;
  fStack_88 = 0.0;
  if (*(longlong *)(thisObject + 0xc0) == 0) {
LAB_7ffe9a44b91a:
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    (*pcVar1)();
    return;
  }
  FUN_7ffe9a40cb40(*(longlong *)(thisObject + 0xc0),0);
  if (damageData == (undefined *)0x0) {
    return;
  }
  pcVar1 = *(code **)(*(longlong *)thisObject + 0x298);
  if (*(int *)(damageData + 0x14) == 0) {
    plVar18 = (longlong *)(*pcVar1)(thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar18 != (longlong *)0x0) &&
       (lVar13 = (**(code **)(*plVar18 + 0x1c8))(plVar18,*(undefined8 *)(*plVar18 + 0x1d0)),
       lVar13 != 0)) {
      cVar3 = FUN_7ffe9a7cbb30(lVar13,0x40f,&plStack_d8,0);
      if (cVar3 != '\0') {
        if (plStack_d8 == (longlong *)0x0) goto LAB_7ffe9a44b91a;
        if (((*(byte *)(*plStack_d8 + 0x130) < *(byte *)(_DAT_7ffe9c960fa0 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*plStack_d8 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c960fa0 + 0x130) * 8) != _DAT_7ffe9c960fa0)) ||
           (plStack_d8 == (longlong *)0x0)) {
          FUN_7ffe9996c950(plStack_d8);
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        (**(code **)(*plStack_d8 + 0x2a8))(plStack_d8,*(undefined8 *)(*plStack_d8 + 0x2b0));
      }
      if (*(int *)(damageData + 0x18) != 1) {
        return;
      }
      uVar12 = (**(code **)(*(longlong *)thisObject + 0x298))
                         (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      cVar3 = FUN_7ffe9a7b7640(uVar12,0);
      if (cVar3 != '\0') {
        *(uint *)(damageData + 0x70) = *(uint *)(damageData + 0x70) | 0x20000;
        uVar12 = (**(code **)(*(longlong *)thisObject + 0x298))
                           (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
        FUN_7ffe9a7b7780(uVar12,0);
      }
      plVar18 = *(longlong **)(thisObject + 0x30);
      if (plVar18 != (longlong *)0x0) {
        (**(code **)(*plVar18 + 0x2e8))(plVar18,actor,*(undefined8 *)(*plVar18 + 0x2f0));
        return;
      }
    }
    goto LAB_7ffe9a44b91a;
  }
  plVar11 = (longlong *)(*pcVar1)();
  if (plVar11 == (longlong *)0x0) goto LAB_7ffe9a44b91a;
  cVar3 = (**(code **)(*plVar11 + 0x268))(plVar11,*(undefined8 *)(*plVar11 + 0x270));
  if (cVar3 != '\0') {
    *(undefined8 *)(damageData + 0x14) = 0;
    *(undefined4 *)(damageData + 0x1c) = 3;
    *(undefined4 *)(damageData + 0x8c) = 0;
    *(undefined4 *)(damageData + 0x6c) = 0;
    plVar18 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar18 != (longlong *)0x0) &&
       (lVar13 = (**(code **)(*plVar18 + 0x1c8))(plVar18,*(undefined8 *)(*plVar18 + 0x1d0)),
       lVar13 != 0)) {
      cVar3 = FUN_7ffe9a7cbb30(lVar13,0x2c2,&plStack_d8,0);
      if (cVar3 != '\0') {
        if (plStack_d8 == (longlong *)0x0) goto LAB_7ffe9a44b91a;
        (**(code **)(*plStack_d8 + 0x208))
                  (plStack_d8,thisObject,*(undefined8 *)(*plStack_d8 + 0x210));
      }
      plVar18 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar18 != (longlong *)0x0) &&
         (lVar13 = (**(code **)(*plVar18 + 0x1c8))(plVar18,*(undefined8 *)(*plVar18 + 0x1d0)),
         lVar13 != 0)) {
        cVar3 = FUN_7ffe9a7cbb30(lVar13,0x40f,&plStack_d8,0);
        if (cVar3 != '\0') {
          if (plStack_d8 == (longlong *)0x0) goto LAB_7ffe9a44b91a;
          if (((*(byte *)(*plStack_d8 + 0x130) < *(byte *)(_DAT_7ffe9c960fa0 + 0x130)) ||
              (*(longlong *)
                (*(longlong *)(*plStack_d8 + 200) + -8 +
                (ulonglong)*(byte *)(_DAT_7ffe9c960fa0 + 0x130) * 8) != _DAT_7ffe9c960fa0)) ||
             (plStack_d8 == (longlong *)0x0)) {
            FUN_7ffe9996c950(plStack_d8);
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
          (**(code **)(*plStack_d8 + 0x2a8))(plStack_d8,*(undefined8 *)(*plStack_d8 + 0x2b0));
        }
        plVar18 = (longlong *)
                  (**(code **)(*(longlong *)thisObject + 0x298))
                            (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
        if ((plVar18 != (longlong *)0x0) &&
           (lVar13 = (**(code **)(*plVar18 + 0x1c8))(plVar18,*(undefined8 *)(*plVar18 + 0x1d0)),
           lVar13 != 0)) {
          cVar3 = FUN_7ffe9a7cbb30(lVar13,0x486,&plStack_d8,0);
          if (cVar3 != '\0') {
            if (plStack_d8 == (longlong *)0x0) goto LAB_7ffe9a44b91a;
            if (((*(byte *)(*plStack_d8 + 0x130) < *(byte *)(_DAT_7ffe9c917ea0 + 0x130)) ||
                (*(longlong *)
                  (*(longlong *)(*plStack_d8 + 200) + -8 +
                  (ulonglong)*(byte *)(_DAT_7ffe9c917ea0 + 0x130) * 8) != _DAT_7ffe9c917ea0)) ||
               (plStack_d8 == (longlong *)0x0)) {
              FUN_7ffe9996c950(plStack_d8);
              pcVar1 = (code *)swi(3);
              (*pcVar1)();
              return;
            }
            FUN_7ffe9a78e290(plStack_d8,damageData,0);
          }
          FUN_7ffe9a824800(thisObject,0);
          return;
        }
      }
    }
    goto LAB_7ffe9a44b91a;
  }
  FUN_7ffe9a447f90(thisObject,0);
  if ((*(int *)(damageData + 0x18) - 2U & 0xfffffffb) == 0) {
    plVar11 = *(longlong **)(thisObject + 0x30);
    if (plVar11 == (longlong *)0x0) goto LAB_7ffe9a44b91a;
    (**(code **)(*plVar11 + 0x2c8))(plVar11,actor,damageData,*(undefined8 *)(*plVar11 + 0x2d0));
  }
  bVar20 = 1;
  bVar21 = true;
  bStackX_8 = 1;
  uVar12 = (**(code **)(*(longlong *)thisObject + 0x298))
                     (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  FUN_7ffe9a7a68d0(uVar12,damageData,0);
  plVar11 = (longlong *)
            (**(code **)(*(longlong *)thisObject + 0x298))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if ((plVar11 == (longlong *)0x0) ||
     (lVar13 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
     lVar13 == 0)) goto LAB_7ffe9a44b91a;
  cVar3 = FUN_7ffe9a7c6d00(lVar13,0x325,0);
  if (cVar3 != '\0') {
    if ((*(longlong *)(thisObject + 0x30) == 0) ||
       (plVar11 = *(longlong **)(*(longlong *)(thisObject + 0x30) + 0x30),
       plVar11 == (longlong *)0x0)) goto LAB_7ffe9a44b91a;
    plVar14 = (longlong *)(**(code **)(*plVar11 + 0x188))(plVar11,*(undefined8 *)(*plVar11 + 400));
    plVar11 = plVar18;
    if (plVar14 != (longlong *)0x0) {
      if ((*(byte *)(*plVar14 + 0x130) < *(byte *)(_DAT_7ffe9c8f42b8 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar14 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8f42b8 + 0x130) * 8
           ) != _DAT_7ffe9c8f42b8)) {
        bVar21 = false;
      }
      if (bVar21) {
        plVar11 = plVar14;
      }
    }
    cVar3 = FUN_7ffe9a8fecd0(plVar11,0,0);
    if (cVar3 != '\0') {
      if (plVar11 == (longlong *)0x0) goto LAB_7ffe9a44b91a;
      (**(code **)(*plVar11 + 0x428))(plVar11,thisObject,4,*(undefined8 *)(*plVar11 + 0x430));
      iVar6 = *(int *)(damageData + 0x84);
      plVar11 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar11 == (longlong *)0x0) ||
         (lVar13 = (**(code **)(*plVar11 + 0x178))(plVar11,*(undefined8 *)(*plVar11 + 0x180)),
         lVar13 == 0)) goto LAB_7ffe9a44b91a;
      if (*(int *)(lVar13 + 0x10) <= iVar6) {
        plVar11 = (longlong *)
                  (**(code **)(*(longlong *)thisObject + 0x298))
                            (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
        if ((plVar11 == (longlong *)0x0) ||
           (lVar13 = (**(code **)(*plVar11 + 0x178))(plVar11,*(undefined8 *)(*plVar11 + 0x180)),
           lVar13 == 0)) goto LAB_7ffe9a44b91a;
        func_0x7ffe9a900040(damageData,*(int *)(lVar13 + 0x10) + -1,0);
      }
    }
  }
  plVar11 = (longlong *)
            (**(code **)(*(longlong *)thisObject + 0x298))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if ((plVar11 == (longlong *)0x0) ||
     (lVar13 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
     lVar13 == 0)) goto LAB_7ffe9a44b91a;
  cVar3 = FUN_7ffe9a7cbb30(lVar13,0x91,&plStack_d8,0);
  if (cVar3 != '\0') {
    plVar11 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar11 == (longlong *)0x0) ||
       (lVar13 = (**(code **)(*plVar11 + 0x178))(plVar11,*(undefined8 *)(*plVar11 + 0x180)),
       lVar13 == 0)) goto LAB_7ffe9a44b91a;
    if (99 < *(int *)(lVar13 + 0x18)) {
      if (plStack_d8 == (longlong *)0x0) goto LAB_7ffe9a44b91a;
      if (((*(byte *)(*plStack_d8 + 0x130) < *(byte *)(_DAT_7ffe9c9368c8 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*plStack_d8 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7ffe9c9368c8 + 0x130) * 8) != _DAT_7ffe9c9368c8)) ||
         (plStack_d8 == (longlong *)0x0)) {
        FUN_7ffe9996c950(plStack_d8);
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      FUN_7ffe9a77a290(plStack_d8,100);
    }
  }
  plVar11 = (longlong *)
            (**(code **)(*(longlong *)thisObject + 0x298))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if ((plVar11 == (longlong *)0x0) ||
     (lVar13 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
     lVar13 == 0)) goto LAB_7ffe9a44b91a;
  cVar3 = FUN_7ffe9a7c6d00(lVar13,0x267,0);
  fVar2 = _DAT_7ffe9c049b34;
  if (cVar3 != '\0') {
    plVar11 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar11 == (longlong *)0x0) ||
       (lVar13 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
       lVar13 == 0)) goto LAB_7ffe9a44b91a;
    FUN_7ffe9a7cafa0(lVar13,0x267,0);
    if ((*(longlong *)(thisObject + 0x30) == 0) ||
       (plVar11 = *(longlong **)(*(longlong *)(thisObject + 0x30) + 0x30),
       plVar11 == (longlong *)0x0)) goto LAB_7ffe9a44b91a;
    plVar14 = (longlong *)(**(code **)(*plVar11 + 0x188))(plVar11,*(undefined8 *)(*plVar11 + 400));
    plVar11 = plVar18;
    if (plVar14 != (longlong *)0x0) {
      if ((*(byte *)(*plVar14 + 0x130) < *(byte *)(_DAT_7ffe9c966a68 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*plVar14 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c966a68 + 0x130) * 8
           ) != _DAT_7ffe9c966a68)) {
        bVar21 = false;
      }
      else {
        bVar21 = true;
      }
      if (bVar21) {
        plVar11 = plVar14;
      }
    }
    cVar3 = FUN_7ffe9a8fecd0(plVar11,0,0);
    if (cVar3 != '\0') {
      if (plVar11 == (longlong *)0x0) goto LAB_7ffe9a44b91a;
      (**(code **)(*plVar11 + 0x428))(plVar11,thisObject,0,*(undefined8 *)(*plVar11 + 0x430));
    }
    plVar11 = plVar18;
    if (action != (undefined *)0x0) {
      if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c972b60 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*(longlong *)action + 200) + -8 +
           (ulonglong)*(byte *)(_DAT_7ffe9c972b60 + 0x130) * 8) != _DAT_7ffe9c972b60)) {
        bVar21 = false;
      }
      else {
        bVar21 = true;
      }
      if (bVar21) {
        plVar11 = (longlong *)action;
      }
    }
    cVar3 = FUN_7ffe9a8fecd0(plVar11,0,0);
    if (cVar3 != '\0') {
      if (plVar11 == (longlong *)0x0) goto LAB_7ffe9a44b91a;
      iVar6 = (**(code **)(*plVar11 + 0x198))(plVar11,*(undefined8 *)(*plVar11 + 0x1a0));
      if (iVar6 == 2) {
        iVar6 = 0x2d;
        plVar11 = (longlong *)
                  (**(code **)(*(longlong *)thisObject + 0x298))
                            (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
        if ((plVar11 == (longlong *)0x0) ||
           (puVar15 = (undefined *)
                      (**(code **)(*plVar11 + 0x218))(plVar11,*(undefined8 *)(*plVar11 + 0x220)),
           puVar15 == (undefined *)0x0)) goto LAB_7ffe9a44b91a;
        puVar15 = GemCartBufferManager_GetGemCartBuffer(puVar15,0xd7,(undefined *)0x0);
        if (puVar15 != (undefined *)0x0) {
          iVar6 = GemCartBufferBase_GetValue(puVar15,(undefined *)0x2,(undefined *)0x0);
          iVar6 = iVar6 + 0x2d;
        }
        fVar26 = (_DAT_7ffe9c049b18 - (float)iVar6 * fVar2) * (float)*(int *)(damageData + 0x84);
      }
      else {
        fVar26 = (float)*(int *)(damageData + 0x84) * _DAT_7ffe9c04a474;
      }
      func_0x7ffe9a900040(damageData,(int)fVar26,0);
      lVar13 = (**(code **)(*(longlong *)thisObject + 0x298))
                         (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if (lVar13 == 0) goto LAB_7ffe9a44b91a;
      fVar26 = (float)FUN_7ffe9a4a22c0(lVar13,0);
      if (_DAT_7ffe9c049b88 <= fVar26) {
        plVar11 = (longlong *)
                  (**(code **)(*(longlong *)thisObject + 0x298))
                            (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
        if ((plVar11 == (longlong *)0x0) ||
           (lVar13 = (**(code **)(*plVar11 + 0x178))(plVar11,*(undefined8 *)(*plVar11 + 0x180)),
           lVar13 == 0)) goto LAB_7ffe9a44b91a;
        if (*(int *)(lVar13 + 0x14) <= *(int *)(damageData + 0x84)) {
          plVar11 = (longlong *)
                    (**(code **)(*(longlong *)thisObject + 0x298))
                              (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
          if ((plVar11 == (longlong *)0x0) ||
             (lVar13 = (**(code **)(*plVar11 + 0x178))(plVar11,*(undefined8 *)(*plVar11 + 0x180)),
             lVar13 == 0)) goto LAB_7ffe9a44b91a;
          func_0x7ffe9a900040(damageData,*(int *)(lVar13 + 0x14) + -1,0);
        }
      }
    }
    FUN_7ffe9a8ffe30(damageData,0);
  }
  plVar11 = (longlong *)
            (**(code **)(*(longlong *)thisObject + 0x298))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if ((plVar11 == (longlong *)0x0) ||
     (lVar13 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
     lVar13 == 0)) goto LAB_7ffe9a44b91a;
  cVar3 = FUN_7ffe9a7c6d00(lVar13,0x26a,0);
  if (cVar3 != '\0') {
    plVar11 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar11 == (longlong *)0x0) ||
       (lVar13 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
       lVar13 == 0)) goto LAB_7ffe9a44b91a;
    FUN_7ffe9a7cafa0(lVar13,0x26a,0);
    func_0x7ffe9a900040(damageData,0,0);
    *(uint *)(damageData + 0x70) = *(uint *)(damageData + 0x70) | 2;
    bVar20 = 0;
    bStackX_8 = 0;
    cVar3 = func_0x7ffe9a8ffdd0(damageData,0);
    if (cVar3 != '\0') {
      FUN_7ffe9a8ffe30(damageData,0);
    }
  }
  FUN_7ffe9a70d450(thisObject,damageData,0);
  FUN_7ffe9a6e9ee0(thisObject,damageData,0);
  plVar11 = (longlong *)
            (**(code **)(*(longlong *)thisObject + 0x298))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if (((plVar11 == (longlong *)0x0) ||
      (lVar13 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
      lVar13 == 0)) || (*(longlong *)(lVar13 + 0x40) == 0)) goto LAB_7ffe9a44b91a;
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar13 + 0x40),0x283,&plStack_d8,_DAT_7ffe9c934418);
  if (cVar3 != '\0') {
    if (plStack_d8 == (longlong *)0x0) goto LAB_7ffe9a44b91a;
    bVar5 = *(byte *)(_DAT_7ffe9c914fd0 + 0x130);
    if (((*(byte *)(*plStack_d8 + 0x130) < bVar5) ||
        (lVar13 = *(longlong *)(*plStack_d8 + 200),
        *(longlong *)(lVar13 + -8 + (ulonglong)bVar5 * 8) != _DAT_7ffe9c914fd0)) ||
       (plStack_d8 == (longlong *)0x0)) goto LAB_7ffe9a44b91a;
    plVar11 = plVar18;
    if (*(longlong *)(lVar13 + -8 + (ulonglong)bVar5 * 8) == _DAT_7ffe9c914fd0) {
      plVar11 = plStack_d8;
    }
    if ((*(char *)((longlong)plVar11 + 0x25) != '\0') &&
       (cVar3 = func_0x7ffe9a8ffdd0(damageData,0), cVar3 != '\0')) {
      FUN_7ffe9a8ffe30(damageData,0);
    }
  }
  FUN_7ffe9a662e60(thisObject,damageData,0);
  FUN_7ffe9a710750(thisObject,damageData,0);
  plVar11 = (longlong *)
            (**(code **)(*(longlong *)thisObject + 0x298))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if ((plVar11 == (longlong *)0x0) ||
     (lVar13 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
     lVar13 == 0)) goto LAB_7ffe9a44b91a;
  cVar3 = FUN_7ffe9a7cbb30(lVar13,0x27f,&plStack_d8,0);
  if (cVar3 != '\0') {
    if (plStack_d8 == (longlong *)0x0) goto LAB_7ffe9a44b91a;
    if (((*(byte *)(*plStack_d8 + 0x130) < *(byte *)(_DAT_7ffe9c95f380 + 0x130)) ||
        (*(longlong *)
          (*(longlong *)(*plStack_d8 + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c95f380 + 0x130) * 8) != _DAT_7ffe9c95f380)) ||
       (plStack_d8 == (longlong *)0x0)) {
      FUN_7ffe9996c950(plStack_d8);
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    if ((char)plStack_d8[4] != '\0') {
      func_0x7ffe9a900040(damageData,0,0);
      *(uint *)(damageData + 0x70) = *(uint *)(damageData + 0x70) | 0x80;
      bVar20 = 0;
      bStackX_8 = 0;
      if (plStack_d8 == (longlong *)0x0) goto LAB_7ffe9a44b91a;
      if (((*(byte *)(*plStack_d8 + 0x130) < *(byte *)(_DAT_7ffe9c95f380 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*plStack_d8 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7ffe9c95f380 + 0x130) * 8) != _DAT_7ffe9c95f380)) ||
         (plStack_d8 == (longlong *)0x0)) {
        FUN_7ffe9996c950(plStack_d8);
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      func_0x7ffe99a998f0(plStack_d8,0);
    }
  }
  plVar11 = (longlong *)
            (**(code **)(*(longlong *)thisObject + 0x298))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if ((plVar11 == (longlong *)0x0) ||
     (lVar13 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
     lVar13 == 0)) goto LAB_7ffe9a44b91a;
  cVar3 = FUN_7ffe9a7cbb30(lVar13,0x5e,&plStack_d8);
  if (cVar3 != '\0') {
    if (plStack_d8 == (longlong *)0x0) goto LAB_7ffe9a44b91a;
    if (((*(byte *)(*plStack_d8 + 0x130) < *(byte *)(_DAT_7ffe9c9530e0 + 0x130)) ||
        (*(longlong *)
          (*(longlong *)(*plStack_d8 + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c9530e0 + 0x130) * 8) != _DAT_7ffe9c9530e0)) ||
       (plStack_d8 == (longlong *)0x0)) {
      FUN_7ffe9996c950(plStack_d8);
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    if ((char)plStack_d8[4] != '\0') {
      func_0x7ffe9a900040(damageData,0,0);
      *(uint *)(damageData + 0x70) = *(uint *)(damageData + 0x70) | 0x100;
      *(undefined4 *)(damageData + 0x1c) = 4;
    }
  }
  plVar11 = (longlong *)
            (**(code **)(*(longlong *)thisObject + 0x298))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if ((plVar11 == (longlong *)0x0) ||
     (lVar13 = (**(code **)(*plVar11 + 0x1e8))(plVar11,*(undefined8 *)(*plVar11 + 0x1f0)),
     lVar13 == 0)) goto LAB_7ffe9a44b91a;
  if (*(char *)(lVar13 + 0x51) != '\0') {
    plVar11 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if (((plVar11 == (longlong *)0x0) ||
        (lVar13 = (**(code **)(*plVar11 + 0x1b8))(plVar11,*(undefined8 *)(*plVar11 + 0x1c0)),
        lVar13 == 0)) || (*(longlong *)(lVar13 + 0x68) == 0)) goto LAB_7ffe9a44b91a;
    cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar13 + 0x68),0x1e8,&plStack_80,_DAT_7ffe9c935bd0);
    if (cVar3 != '\0') {
      if (plStack_80 == (longlong *)0x0) goto LAB_7ffe9a44b91a;
      iVar6 = (**(code **)(*plStack_80 + 0x178))
                        (plStack_80,0x19,*(undefined8 *)(*plStack_80 + 0x180));
      func_0x7ffe9a900040(damageData,
                          (int)(((_DAT_7ffe9c049cfc - (float)iVar6) / _DAT_7ffe9c049cfc) *
                               (float)*(int *)(damageData + 0x84)),0);
    }
  }
  if ((*(longlong *)(thisObject + 0x30) == 0) ||
     (plVar11 = *(longlong **)(*(longlong *)(thisObject + 0x30) + 0x30), plVar11 == (longlong *)0x0)
     ) goto LAB_7ffe9a44b91a;
  plVar11 = (longlong *)(**(code **)(*plVar11 + 0x188))(plVar11,*(undefined8 *)(*plVar11 + 400));
  if (plVar11 != (longlong *)0x0) {
    if (((*(byte *)(_DAT_7ffe9c8f0840 + 0x130) <= *(byte *)(*plVar11 + 0x130)) &&
        (*(longlong *)
          (*(longlong *)(*plVar11 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c8f0840 + 0x130) * 8)
         == _DAT_7ffe9c8f0840)) && (*(int *)(damageData + 0x8c) - 1U < 3)) {
      FUN_7ffe9a8ffe30(damageData,0);
    }
  }
  FUN_7ffe9a74a080(thisObject,damageData,0);
  FUN_7ffe9a69d7d0(thisObject,damageData,0);
  plVar11 = (longlong *)
            (**(code **)(*(longlong *)thisObject + 0x298))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if (((plVar11 == (longlong *)0x0) ||
      (lVar13 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
      lVar13 == 0)) || (*(longlong *)(lVar13 + 0x40) == 0)) goto LAB_7ffe9a44b91a;
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar13 + 0x40),0x486,&plStack_d8,_DAT_7ffe9c934418);
  if (cVar3 != '\0') {
    if (plStack_d8 == (longlong *)0x0) goto LAB_7ffe9a44b91a;
    if (((*(byte *)(*plStack_d8 + 0x130) < *(byte *)(_DAT_7ffe9c917ea0 + 0x130)) ||
        (*(longlong *)
          (*(longlong *)(*plStack_d8 + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c917ea0 + 0x130) * 8) != _DAT_7ffe9c917ea0)) ||
       (plStack_d8 == (longlong *)0x0)) {
      FUN_7ffe9996c950(plStack_d8,_DAT_7ffe9c917ea0);
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    uVar12 = FUN_7ffe99744bb0(plStack_d8,_DAT_7ffe9c917ea0);
    FUN_7ffe9a78e290(uVar12,damageData,0);
    plVar11 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if (((plVar11 == (longlong *)0x0) ||
        (lVar13 = (**(code **)(*plVar11 + 0x1b8))(plVar11,*(undefined8 *)(*plVar11 + 0x1c0)),
        lVar13 == 0)) || (*(longlong *)(lVar13 + 0x68) == 0)) goto LAB_7ffe9a44b91a;
    cVar3 = FUN_7ffe9ad5f0a0(*(longlong *)(lVar13 + 0x68),0x489,_DAT_7ffe9c935988);
    plVar11 = plStack_d8;
    if (cVar3 != '\0') {
      lVar13 = FUN_7ffe99744bb0(plStack_d8,_DAT_7ffe9c917ea0);
      if (lVar13 == 0) goto LAB_7ffe9a44b91a;
      lVar13 = FUN_7ffe99744bb0(plVar11,_DAT_7ffe9c917ea0);
      if ((*(char *)(lVar13 + 0x2c) == '\0') && (*(int *)(damageData + 0x8c) - 1U < 4)) {
        FUN_7ffe9a8ffe30(damageData,0);
      }
    }
  }
  plVar11 = (longlong *)
            (**(code **)(*(longlong *)thisObject + 0x298))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if (((plVar11 == (longlong *)0x0) ||
      (lVar13 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
      lVar13 == 0)) || (*(longlong *)(lVar13 + 0x40) == 0)) goto LAB_7ffe9a44b91a;
  cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar13 + 0x40),0x445,&plStack_d8,_DAT_7ffe9c934418);
  plVar11 = plStack_d8;
  if (cVar3 != '\0') {
    lVar13 = FUN_7ffe99744bb0(plStack_d8,_DAT_7ffe9c928ba0);
    if (lVar13 == 0) goto LAB_7ffe9a44b91a;
    uVar12 = FUN_7ffe99744bb0(plVar11,_DAT_7ffe9c928ba0);
    FUN_7ffe9a7901e0(uVar12,actor,thisObject,damageData,0);
  }
  uVar23 = 0;
  FUN_7ffe9a82a710(actor,thisObject,action,damageData,0);
  plVar11 = (longlong *)
            (**(code **)(*(longlong *)thisObject + 0x298))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if ((plVar11 == (longlong *)0x0) ||
     (lVar13 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
     lVar13 == 0)) goto LAB_7ffe9a44b91a;
  cVar3 = FUN_7ffe9a7cbb30(lVar13,0x2c9,&plStack_d8,0);
  if (cVar3 != '\0') {
    if (plStack_d8 == (longlong *)0x0) goto LAB_7ffe9a44b91a;
    func_0x7ffe9a7a2130(plStack_d8,0);
  }
  plVar11 = (longlong *)
            (**(code **)(*(longlong *)thisObject + 0x298))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if ((plVar11 == (longlong *)0x0) ||
     (lVar13 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
     lVar13 == 0)) goto LAB_7ffe9a44b91a;
  cVar3 = FUN_7ffe9a7cbb30(lVar13,0x22e,&plStack_d8,0);
  plVar11 = plStack_d8;
  if (cVar3 != '\0') {
    lVar13 = FUN_7ffe99744bb0(plStack_d8,_DAT_7ffe9c8feb30);
    if (lVar13 == 0) goto LAB_7ffe9a44b91a;
    uVar12 = FUN_7ffe99744bb0(plVar11,_DAT_7ffe9c8feb30);
    FUN_7ffe9a79b7d0(uVar12,damageData,0);
  }
  FUN_7ffe9a824800(thisObject,0);
  uVar12 = (**(code **)(*(longlong *)thisObject + 0x298))
                     (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  FUN_7ffe9a6c7c00(uVar12,damageData,0);
  FUN_7ffe9a6551d0(thisObject,damageData,0);
  if ((*(longlong *)(thisObject + 0x30) == 0) ||
     (plVar11 = *(longlong **)(*(longlong *)(thisObject + 0x30) + 0x30), plVar11 == (longlong *)0x0)
     ) goto LAB_7ffe9a44b91a;
  plVar14 = (longlong *)(**(code **)(*plVar11 + 0x188))(plVar11,*(undefined8 *)(*plVar11 + 400));
  plVar11 = plVar18;
  if (plVar14 != (longlong *)0x0) {
    if ((*(byte *)(*plVar14 + 0x130) < *(byte *)(_DAT_7ffe9c973c28 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*plVar14 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c973c28 + 0x130) * 8)
        != _DAT_7ffe9c973c28)) {
      bVar21 = false;
    }
    else {
      bVar21 = true;
    }
    if (bVar21) {
      plVar11 = plVar14;
    }
  }
  cVar3 = FUN_7ffe9a8fecd0(plVar11,0,0);
  if (cVar3 != '\0') {
    if (plVar11 == (longlong *)0x0) goto LAB_7ffe9a44b91a;
    if (*(char *)((longlong)plVar11 + 0x121) != '\0') {
      func_0x7ffe9a900040(damageData,0,0);
      *(undefined4 *)(damageData + 0x1c) = 4;
      func_0x7ffe9a70b030(plVar11,0);
    }
  }
  FUN_7ffe9a6b38f0(thisObject,0);
  if (*(int *)(damageData + 0x8c) == -1) {
    *(undefined4 *)(damageData + 0x8c) = 0;
    if (*(longlong *)(thisObject + 0x30) == 0) goto LAB_7ffe9a44b91a;
    cVar3 = FUN_7ffe9a7e1140(*(longlong *)(thisObject + 0x30),0);
    if (cVar3 != '\0') {
      if ((*(longlong *)(thisObject + 0x30) == 0) ||
         (plVar11 = *(longlong **)(*(longlong *)(thisObject + 0x30) + 0x30),
         plVar11 == (longlong *)0x0)) goto LAB_7ffe9a44b91a;
      plVar11 = (longlong *)(**(code **)(*plVar11 + 0x188))(plVar11,*(undefined8 *)(*plVar11 + 400))
      ;
      bVar21 = false;
      if (plVar11 == (longlong *)0x0) goto LAB_7ffe9a44b91a;
      iVar6 = (**(code **)(*plVar11 + 0x2e8))(plVar11,*(undefined8 *)(*plVar11 + 0x2f0));
      if (iVar6 == 1) {
        if ((*(longlong *)(thisObject + 0x30) == 0) ||
           (plVar14 = *(longlong **)(*(longlong *)(thisObject + 0x30) + 0x30),
           plVar14 == (longlong *)0x0)) goto LAB_7ffe9a44b91a;
        cVar3 = (**(code **)(*plVar14 + 0x198))(plVar14,*(undefined8 *)(*plVar14 + 0x1a0));
        if (cVar3 != '\0') {
          bVar21 = true;
        }
      }
      iVar6 = (**(code **)(*plVar11 + 0x188))(plVar11,*(undefined8 *)(*plVar11 + 400));
      if (iVar6 == 0x36a) {
        lVar13 = FUN_7ffe99744bb0(plVar11,_DAT_7ffe9c8f6978);
        if (lVar13 == 0) goto LAB_7ffe9a44b91a;
        lVar13 = FUN_7ffe99744bb0(plVar11,_DAT_7ffe9c8f6978);
        bVar21 = bVar21 || *(char *)(lVar13 + 0x154) != '\0';
      }
      bVar20 = bStackX_8;
      if ((bVar21) && (iVar6 = FUN_7ffe9bda4580(0,100), iVar6 < 100)) {
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
  plVar11 = (longlong *)
            (**(code **)(*(longlong *)thisObject + 0x298))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if ((plVar11 == (longlong *)0x0) ||
     (lVar13 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
     lVar13 == 0)) goto LAB_7ffe9a44b91a;
  cVar3 = FUN_7ffe9a7c6d00(lVar13,0x426,0);
  cStack_d0 = cVar3;
  if (*(longlong *)(thisObject + 0x118) == 0) goto LAB_7ffe9a44b91a;
  cVar4 = func_0x7ffe9a4ceea0(*(longlong *)(thisObject + 0x118),0);
  if (((cVar4 != '\0') && (bVar20 != 0)) && (*(int *)(damageData + 0x14) != 0)) {
    if (*(longlong *)(thisObject + 0x118) == 0) goto LAB_7ffe9a44b91a;
    cVar4 = FUN_7ffe9a7ef910(*(longlong *)(thisObject + 0x118),0);
    if (cVar4 != '\0') {
      lVar13 = FUN_7ffe9a4565c0(thisObject,0);
      if ((actor == (undefined *)0x0) ||
         (uVar12 = FUN_7ffe9ab9c3a0(actor,_DAT_7ffe9c95f2c8), lVar13 == 0)) goto LAB_7ffe9a44b91a;
      FUN_7ffe9a46afb0(lVar13,uVar12,0);
    }
  }
  plVar11 = (longlong *)
            (**(code **)(*(longlong *)thisObject + 0x298))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
  if (((plVar11 == (longlong *)0x0) ||
      (lVar13 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
      lVar13 == 0)) || (*(longlong *)(lVar13 + 0x40) == 0)) goto LAB_7ffe9a44b91a;
  bVar5 = FUN_7ffe9ad8e670(*(longlong *)(lVar13 + 0x40),0x3ce);
  plVar11 = plStack_d8;
  if ((bVar20 & bVar5) != 0) {
    lVar13 = FUN_7ffe99744bb0(plStack_d8,_DAT_7ffe9c9279a8);
    if (lVar13 == 0) goto LAB_7ffe9a44b91a;
    puVar15 = (undefined *)FUN_7ffe99744bb0(plVar11,_DAT_7ffe9c9279a8);
    HandlingerOfGodspeedBuf_DamageFunction(puVar15,thisObject,damageData,(undefined *)0x0);
  }
  uVar22 = (undefined4)((ulonglong)in_stack_ffffffffffffff00 >> 0x20);
  if (bVar20 == 0) {
    *(uint *)(damageData + 0x70) = *(uint *)(damageData + 0x70) & 0xf7;
    *(undefined4 *)(damageData + 0x1c) = 4;
    *(undefined4 *)(damageData + 0x6c) = 0;
    bStackX_8 = 0;
    iVar6 = 0;
  }
  else {
    FUN_7ffe9a448100(thisObject,actor,damageData,0);
    uVar9 = FUN_7ffe9a7b5380(thisObject,damageData,*(undefined4 *)(damageData + 0x84),0);
    lStack_b8 = 0;
    plVar11 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar11 == (longlong *)0x0) ||
       (lVar13 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
       lVar13 == 0)) goto LAB_7ffe9a44b91a;
    cVar4 = FUN_7ffe9abc2210(lVar13,0x34e,&lStack_b8,_DAT_7ffe9c969a58);
    plVar11 = (longlong *)(ulonglong)uVar9;
    if (cVar4 != '\0') {
      if (lStack_b8 == 0) goto LAB_7ffe9a44b91a;
      iVar6 = func_0x7ffe99744f30(0xc,lStack_b8,0x33);
      plVar14 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar14 == (longlong *)0x0) ||
         (lVar13 = (**(code **)(*plVar14 + 0x178))(plVar14,*(undefined8 *)(*plVar14 + 0x180)),
         lVar13 == 0)) goto LAB_7ffe9a44b91a;
      iVar8 = *(int *)(lVar13 + 0x14);
      plVar14 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar14 == (longlong *)0x0) ||
         (lVar13 = (**(code **)(*plVar14 + 0x178))(plVar14,*(undefined8 *)(*plVar14 + 0x180)),
         lVar13 == 0)) goto LAB_7ffe9a44b91a;
      func_0x7ffe9a480d40(lVar13,iVar8 + iVar6,0,0);
      plVar14 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar14 == (longlong *)0x0) ||
         (lVar13 = (**(code **)(*plVar14 + 0x178))(plVar14,*(undefined8 *)(*plVar14 + 0x180)),
         lVar13 == 0)) goto LAB_7ffe9a44b91a;
      cVar3 = cStack_d0;
      if (0 < *(int *)(lVar13 + 0x24)) {
        plVar11 = (longlong *)
                  (**(code **)(*(longlong *)thisObject + 0x298))
                            (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
        if ((plVar11 == (longlong *)0x0) ||
           (lVar13 = (**(code **)(*plVar11 + 0x178))(plVar11,*(undefined8 *)(*plVar11 + 0x180)),
           lVar13 == 0)) goto LAB_7ffe9a44b91a;
        plVar11 = plVar18;
        cVar3 = cStack_d0;
        if ((int)(*(int *)(lVar13 + 0x24) - uVar9) < 0) {
          plVar11 = (longlong *)
                    (**(code **)(*(longlong *)thisObject + 0x298))
                              (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
          if ((plVar11 == (longlong *)0x0) ||
             (lVar13 = (**(code **)(*plVar11 + 0x178))(plVar11,*(undefined8 *)(*plVar11 + 0x180)),
             lVar13 == 0)) goto LAB_7ffe9a44b91a;
          plVar11 = (longlong *)(ulonglong)(uVar9 - *(int *)(lVar13 + 0x24));
          cVar3 = cStack_d0;
        }
      }
    }
    plVar14 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar14 == (longlong *)0x0) ||
       (lVar13 = (**(code **)(*plVar14 + 0x178))(plVar14,*(undefined8 *)(*plVar14 + 0x180)),
       lVar13 == 0)) goto LAB_7ffe9a44b91a;
    iVar6 = *(int *)(lVar13 + 0x20);
    plVar14 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar14 == (longlong *)0x0) ||
       (lVar13 = (**(code **)(*plVar14 + 0x178))(plVar14,*(undefined8 *)(*plVar14 + 0x180)),
       lVar13 == 0)) goto LAB_7ffe9a44b91a;
    iVar6 = (uVar9 - iVar6) - *(int *)(lVar13 + 0x14);
    iStack_a0 = 0;
    if (0 < iVar6) {
      iStack_a0 = iVar6;
    }
    lVar13 = (**(code **)(*(longlong *)thisObject + 0x298))
                       (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if (lVar13 == 0) goto LAB_7ffe9a44b91a;
    FUN_7ffe9a4a1500(lVar13,uVar9,cVar3,0);
    if (lStack_b8 != 0) {
      func_0x7ffe9a7a1530(lStack_b8,plVar11,0);
      if (lStack_b8 == 0) goto LAB_7ffe9a44b97a;
      iVar6 = func_0x7ffe99744f30(0xc,lStack_b8,0x33);
      if (0 < iVar6) {
        lVar13 = func_0x7ffe99742fe0(0x16,thisObject);
        if ((lVar13 == 0) || (lVar13 = func_0x7ffe99742fe0(4,lVar13), lVar13 == 0))
        goto LAB_7ffe9a44b97a;
        iVar8 = *(int *)(lVar13 + 0x14);
        lVar13 = func_0x7ffe99742fe0(0x16,thisObject);
        if ((lVar13 == 0) || (lVar13 = func_0x7ffe99742fe0(4,lVar13), lVar13 == 0))
        goto LAB_7ffe9a44b97a;
        func_0x7ffe9a480d40(lVar13,iVar8 - iVar6,0,0);
      }
    }
    plVar11 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar11 == (longlong *)0x0) ||
       (lVar13 = (**(code **)(*plVar11 + 0x1e8))(plVar11,*(undefined8 *)(*plVar11 + 0x1f0)),
       lVar13 == 0)) goto LAB_7ffe9a44b97a;
    FUN_7ffe9a4dacc0(lVar13,0);
    plVar11 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar11 == (longlong *)0x0) ||
       (lVar13 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
       lVar13 == 0)) goto LAB_7ffe9a44b97a;
    cVar3 = FUN_7ffe9a7c6d00(lVar13,0x205,0);
    plVar11 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar11 == (longlong *)0x0) ||
       (lVar13 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
       lVar13 == 0)) goto LAB_7ffe9a44b97a;
    FUN_7ffe9a7c9e70(lVar13,thisObject,0);
    uVar22 = (undefined4)((ulonglong)in_stack_ffffffffffffff00 >> 0x20);
    if (cVar3 != '\0') {
      if (*(longlong *)(thisObject + 0x58) == 0) goto LAB_7ffe9a44b97a;
      FUN_7ffe9a9b8750(*(longlong *)(thisObject + 0x58),0);
      lVar13 = func_0x7ffe99742fe0(0x16,thisObject);
      if ((lVar13 == 0) || (lVar13 = func_0x7ffe99742fe0(8,lVar13), lVar13 == 0))
      goto LAB_7ffe9a44b97a;
      uVar7 = FUN_7ffe9a7fd580(lVar13,0x20b,1,0);
      uVar22 = (undefined4)((ulonglong)in_stack_ffffffffffffff00 >> 0x20);
      if (0 < (int)uVar7) {
        iVar6 = 1;
        lVar13 = func_0x7ffe99742fe0(0x16,thisObject);
        if ((lVar13 == 0) || (lVar13 = func_0x7ffe99742fe0(9,lVar13), lVar13 == 0))
        goto LAB_7ffe9a44b97a;
        cVar3 = FUN_7ffe9a7cbb30(lVar13,0x20b,&plStack_d8,0);
        plVar11 = plVar18;
        if (cVar3 == '\0') {
          plVar14 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c9573c0);
          FUN_7ffe9a7967c0(plVar14,uVar7 & 0xff,0);
          plStack_d8 = plVar14;
          lVar13 = func_0x7ffe99742fe0(0x16,thisObject);
          if ((lVar13 == 0) || (lVar13 = func_0x7ffe99742fe0(9,lVar13), lVar13 == 0))
          goto LAB_7ffe9a44b97a;
          FUN_7ffe9a7c26c0(lVar13,plStack_d8,0,0);
        }
        else {
          if (plStack_d8 == (longlong *)0x0) goto LAB_7ffe9a44b97a;
          if (uVar7 != *(byte *)(plStack_d8 + 2)) {
            iVar6 = func_0x7ffe99744f30(0xc,plStack_d8,0x14);
            iVar6 = iVar6 + 1;
            lVar13 = func_0x7ffe99742fe0(0x16,thisObject);
            if ((lVar13 == 0) || (lVar13 = func_0x7ffe99742fe0(9,lVar13), lVar13 == 0))
            goto LAB_7ffe9a44b97a;
            FUN_7ffe9a7cafa0(lVar13,0x20b,0);
            plVar14 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c9573c0);
            FUN_7ffe9a7967c0(plVar14,uVar7 & 0xff,0);
            plStack_d8 = plVar14;
            lVar13 = func_0x7ffe99742fe0(0x16,thisObject);
            if ((lVar13 == 0) || (lVar13 = func_0x7ffe99742fe0(9,lVar13), lVar13 == 0))
            goto LAB_7ffe9a44b97a;
            FUN_7ffe9a7c26c0(lVar13,plStack_d8,0,0);
            uVar22 = (undefined4)((ulonglong)in_stack_ffffffffffffff00 >> 0x20);
            if (iVar6 < 1) goto LAB_7ffe9a44a192;
          }
        }
        do {
          if (plStack_d8 == (longlong *)0x0) goto LAB_7ffe9a44b97a;
          if (((*(byte *)(*plStack_d8 + 0x130) < *(byte *)(_DAT_7ffe9c9573c0 + 0x130)) ||
              (*(longlong *)
                (*(longlong *)(*plStack_d8 + 200) + -8 +
                (ulonglong)*(byte *)(_DAT_7ffe9c9573c0 + 0x130) * 8) != _DAT_7ffe9c9573c0)) ||
             (plStack_d8 == (longlong *)0x0)) {
            FUN_7ffe9996c950(plStack_d8);
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
          (**(code **)(*plStack_d8 + 0x2a8))(plStack_d8,*(undefined8 *)(*plStack_d8 + 0x2b0));
          uVar22 = (undefined4)((ulonglong)in_stack_ffffffffffffff00 >> 0x20);
          uVar7 = (int)plVar11 + 1;
          plVar11 = (longlong *)(ulonglong)uVar7;
        } while ((int)uVar7 < iVar6);
      }
    }
LAB_7ffe9a44a192:
    if ((damageData[0x70] & 8) != 0) {
      plVar11 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if (((plVar11 == (longlong *)0x0) ||
          (lVar13 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
          lVar13 == 0)) || (*(longlong *)(lVar13 + 0x50) == 0)) goto LAB_7ffe9a44b97a;
      cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar13 + 0x50),0x4c8,&plStack_d8,_DAT_7ffe9c934418);
      if (cVar3 != '\0') {
        if (plStack_d8 == (longlong *)0x0) goto LAB_7ffe9a44b97a;
        if (((*(byte *)(*plStack_d8 + 0x130) < *(byte *)(_DAT_7ffe9c8f3dd8 + 0x130)) ||
            (*(longlong *)
              (*(longlong *)(*plStack_d8 + 200) + -8 +
              (ulonglong)*(byte *)(_DAT_7ffe9c8f3dd8 + 0x130) * 8) != _DAT_7ffe9c8f3dd8)) ||
           (plStack_d8 == (longlong *)0x0)) {
          FUN_7ffe9996c950(plStack_d8);
          pcVar1 = (code *)swi(3);
          (*pcVar1)();
          return;
        }
        FUN_7ffe9a782350(plStack_d8,0);
      }
    }
    plVar11 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if (((plVar11 == (longlong *)0x0) ||
        (lVar13 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
        lVar13 == 0)) || (*(longlong *)(lVar13 + 0x50) == 0)) goto LAB_7ffe9a44b97a;
    cVar3 = FUN_7ffe9ad8e670(*(longlong *)(lVar13 + 0x50),0x34c,&plStack_d8);
    if ((cVar3 != '\0') && (*(int *)(damageData + 0x18) != 1)) {
      if (plStack_d8 == (longlong *)0x0) goto LAB_7ffe9a44b97a;
      if (((*(byte *)(*plStack_d8 + 0x130) < *(byte *)(_DAT_7ffe9c900bb0 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*plStack_d8 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7ffe9c900bb0 + 0x130) * 8) != _DAT_7ffe9c900bb0)) ||
         (plStack_d8 == (longlong *)0x0)) {
        FUN_7ffe9996c950(plStack_d8);
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      cVar3 = FUN_7ffe9a79c340(plStack_d8,actor,damageData);
      if (cVar3 != '\0') {
        *(uint *)(damageData + 0x70) = *(uint *)(damageData + 0x70) | 0x10;
      }
    }
    FUN_7ffe9a824d50(thisObject,0);
    plVar11 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar11 == (longlong *)0x0) ||
       (lVar13 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
       lVar13 == 0)) goto LAB_7ffe9a44b97a;
    cVar3 = FUN_7ffe9a7cbb30(lVar13,0x2c3,&plStack_d8);
    if ((cVar3 != '\0') && (cVar3 = FUN_7ffe99b1ccd0(thisObject,0), cVar3 == '\0')) {
      if (plStack_d8 == (longlong *)0x0) goto LAB_7ffe9a44b97a;
      if (((*(byte *)(*plStack_d8 + 0x130) < *(byte *)(_DAT_7ffe9c9612c8 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*plStack_d8 + 200) + -8 +
            (ulonglong)*(byte *)(_DAT_7ffe9c9612c8 + 0x130) * 8) != _DAT_7ffe9c9612c8)) ||
         (plStack_d8 == (longlong *)0x0)) {
        FUN_7ffe9996c950(plStack_d8);
        pcVar1 = (code *)swi(3);
        (*pcVar1)();
        return;
      }
      FUN_7ffe9a77f650(plStack_d8,actor,0);
    }
    GemCartBuffer_InflexibilityEmergingBuff_Damaged
              (thisObject,uVar9,(undefined *)(ulonglong)*(uint *)(damageData + 0x18),
               (undefined *)0x0);
    plVar11 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar11 == (longlong *)0x0) ||
       (lVar13 = (**(code **)(*plVar11 + 0x1c8))(plVar11,*(undefined8 *)(*plVar11 + 0x1d0)),
       lVar13 == 0)) goto LAB_7ffe9a44b97a;
    cVar3 = FUN_7ffe9abc2210(lVar13,0x6f,&lStack_78,_DAT_7ffe9c9690c8);
    if ((cVar3 != '\0') && (cVar3 = FUN_7ffe99b1ccd0(thisObject,0), cVar3 == '\0')) {
      if (lStack_78 == 0) goto LAB_7ffe9a44b97a;
      FUN_7ffe9a797ad0(lStack_78,actor,0);
    }
    uVar23 = 0;
    HorizontalCutAction_Damaged(thisObject,actor,action,damageData,(undefined *)0x0);
    iVar6 = iStack_a0;
  }
  cVar3 = (**(code **)(*(longlong *)thisObject + 0x188))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
  if (cVar3 == '\0') {
    if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    bVar20 = FUN_7ffe9bda2160(actor,0);
    if ((bStackX_8 & bVar20) != 0) {
      if (*(longlong *)(thisObject + 0x20) == 0) goto LAB_7ffe9a44b97a;
      puVar16 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_c8,*(longlong *)(thisObject + 0x20),0);
      uStack_b0 = *puVar16;
      fStack_a8 = *(float *)(puVar16 + 1);
      if ((actor == (undefined *)0x0) || (lVar13 = FUN_7ffe9bd9b890(actor,0), lVar13 == 0))
      goto LAB_7ffe9a44b97a;
      puVar16 = (undefined8 *)FUN_7ffe9bdbf710(&uStack_c8,lVar13,0);
      fStack_c0 = fStack_a8 - *(float *)(puVar16 + 1);
      lVar13 = *(longlong *)(thisObject + 0x48);
      iVar10 = *(int *)(damageData + 0x84);
      uStack_c8 = CONCAT44(uStack_b0._4_4_ - (float)((ulonglong)*puVar16 >> 0x20),
                           (float)uStack_b0 - (float)*puVar16);
      fStack_a8 = fStack_c0;
      plVar11 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar11 == (longlong *)0x0) ||
         (lVar17 = (**(code **)(*plVar11 + 0x198))(plVar11,*(undefined8 *)(*plVar11 + 0x1a0)),
         lVar17 == 0)) goto LAB_7ffe9a44b97a;
      iVar6 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40);
      puVar16 = (undefined8 *)FUN_7ffe999fca00(&uStack_b0,&uStack_c8);
      if (lVar13 == 0) goto LAB_7ffe9a44b97a;
      uStack_c8 = *puVar16;
      fStack_c0 = *(float *)(puVar16 + 1);
      uVar23 = 0;
      uVar12 = FUN_7ffe9a9f43c0(lVar13,fStack_c0,(float)iVar10 / (float)iVar6,&uStack_c8,0);
      FUN_7ffe9bd9f640(thisObject,uVar12);
    }
    if (action != (undefined *)0x0) {
      if ((*(byte *)(*(longlong *)action + 0x130) < *(byte *)(_DAT_7ffe9c972b60 + 0x130)) ||
         (*(longlong *)
           (*(longlong *)(*(longlong *)action + 200) + -8 +
           (ulonglong)*(byte *)(_DAT_7ffe9c972b60 + 0x130) * 8) != _DAT_7ffe9c972b60)) {
        bVar21 = false;
      }
      else {
        bVar21 = true;
      }
      if (bVar21) {
        plVar18 = (longlong *)action;
      }
    }
    FUN_7ffe9a80c200(thisObject,plVar18);
    FUN_7ffe9a655ad0(thisObject,damageData);
  }
  else {
    plVar18 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar18 == (longlong *)0x0) ||
       (lVar13 = (**(code **)(*plVar18 + 0x1c8))(plVar18,*(undefined8 *)(*plVar18 + 0x1d0)),
       lVar13 == 0)) goto LAB_7ffe9a44b97a;
    cVar3 = FUN_7ffe9abc2210(lVar13,0x28e,&lStack_98,_DAT_7ffe9c969990);
    if (cVar3 != '\0') {
      if (lStack_98 == 0) goto LAB_7ffe9a44b97a;
      iVar10 = 0;
      if (*(char *)(lStack_98 + 0x50) == '\0') {
        iVar10 = 1;
      }
    }
    plVar18 = *(longlong **)(thisObject + 0x30);
    bVar21 = true;
    if (plVar18 == (longlong *)0x0) goto LAB_7ffe9a44b97a;
    iVar8 = (**(code **)(*plVar18 + 0x178))(plVar18,*(undefined8 *)(*plVar18 + 0x180));
    if ((iVar8 == 0) && (*(int *)(damageData + 0x18) == 5)) {
      bVar21 = false;
      plVar18 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar18 == (longlong *)0x0) ||
         (lVar13 = (**(code **)(*plVar18 + 0x198))(plVar18,*(undefined8 *)(*plVar18 + 0x1a0)),
         lVar13 == 0)) goto LAB_7ffe9a44b97a;
      iVar8 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar13);
      plVar18 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar18 == (longlong *)0x0) ||
         (lVar13 = (**(code **)(*plVar18 + 0x178))(plVar18,*(undefined8 *)(*plVar18 + 0x180)),
         lVar13 == 0)) goto LAB_7ffe9a44b97a;
      func_0x7ffe9a480d40(lVar13,(int)((float)iVar8 * fVar2),0,0);
    }
    plVar18 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar18 == (longlong *)0x0) ||
       (puVar15 = (undefined *)
                  (**(code **)(*plVar18 + 0x218))(plVar18,*(undefined8 *)(*plVar18 + 0x220)),
       puVar15 == (undefined *)0x0)) goto LAB_7ffe9a44b97a;
    puVar15 = GemCartBufferManager_GetGemCartBuffer(puVar15,0x26,(undefined *)0x0);
    if ((puVar15 != (undefined *)0x0) &&
       (iVar8 = GemCartBufferBase_GetValue(puVar15,(undefined *)0x2,(undefined *)0x0), iVar8 != 0))
    {
      bVar21 = false;
      plVar18 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar18 == (longlong *)0x0) ||
         (lVar13 = (**(code **)(*plVar18 + 0x198))(plVar18,*(undefined8 *)(*plVar18 + 0x1a0)),
         lVar13 == 0)) goto LAB_7ffe9a44b97a;
      iVar8 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar13);
      plVar18 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar18 == (longlong *)0x0) ||
         (lVar13 = (**(code **)(*plVar18 + 0x178))(plVar18,*(undefined8 *)(*plVar18 + 0x180)),
         lVar13 == 0)) goto LAB_7ffe9a44b97a;
      func_0x7ffe9a480d40(lVar13,(int)((float)iVar8 * fVar2),0,0);
      *(undefined4 *)(damageData + 0x8c) = 1;
      if (*(int *)(_DAT_7ffe9c92dfe0 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      uVar24 = FUN_7ffe9a4db1f0(1,0);
      *(undefined4 *)(damageData + 0x94) = uVar24;
      uVar24 = FUN_7ffe9a4db080(1,0);
      *(undefined4 *)(damageData + 0x98) = uVar24;
    }
    plVar18 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if (((plVar18 == (longlong *)0x0) ||
        (lVar13 = (**(code **)(*plVar18 + 0x1b8))(plVar18,*(undefined8 *)(*plVar18 + 0x1c0)),
        lVar13 == 0)) || (*(longlong *)(lVar13 + 0x68) == 0)) goto LAB_7ffe9a44b97a;
    cVar3 = FUN_7ffe9ad5f0a0(*(longlong *)(lVar13 + 0x68),1099,_DAT_7ffe9c935988);
    if ((cVar3 != '\0') && (cVar3 = FUN_7ffe9a7b82c0(thisObject,0), cVar3 != '\0')) {
      bVar21 = false;
      plVar18 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar18 == (longlong *)0x0) ||
         (lVar13 = (**(code **)(*plVar18 + 0x198))(plVar18,*(undefined8 *)(*plVar18 + 0x1a0)),
         lVar13 == 0)) goto LAB_7ffe9a44b97a;
      iVar8 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar13);
      plVar18 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar18 == (longlong *)0x0) ||
         (lVar13 = (**(code **)(*plVar18 + 0x178))(plVar18,*(undefined8 *)(*plVar18 + 0x180)),
         lVar13 == 0)) goto LAB_7ffe9a44b97a;
      func_0x7ffe9a480d40(lVar13,(int)((float)iVar8 * fVar2),0,0);
      damageData[0x61] = 1;
    }
    plVar18 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar18 == (longlong *)0x0) ||
       (lVar13 = (**(code **)(*plVar18 + 0x1c8))(plVar18,*(undefined8 *)(*plVar18 + 0x1d0)),
       lVar13 == 0)) goto LAB_7ffe9a44b97a;
    cVar3 = FUN_7ffe9a7cbb30(lVar13,0x2d0,&plStack_d8,0);
    if (cVar3 != '\0') {
      bVar21 = false;
      plVar18 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar18 == (longlong *)0x0) ||
         (lVar13 = (**(code **)(*plVar18 + 0x198))(plVar18,*(undefined8 *)(*plVar18 + 0x1a0)),
         lVar13 == 0)) goto LAB_7ffe9a44b97a;
      iVar8 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar13);
      plVar18 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar18 == (longlong *)0x0) ||
         (lVar13 = (**(code **)(*plVar18 + 0x178))(plVar18,*(undefined8 *)(*plVar18 + 0x180)),
         lVar13 == 0)) goto LAB_7ffe9a44b97a;
      func_0x7ffe9a480d40(lVar13,(int)((float)iVar8 * fVar2),0,0);
    }
    plVar18 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar18 == (longlong *)0x0) ||
       (lVar13 = (**(code **)(*plVar18 + 0x1c8))(plVar18,*(undefined8 *)(*plVar18 + 0x1d0)),
       lVar13 == 0)) goto LAB_7ffe9a44b97a;
    cVar3 = FUN_7ffe9a7c6d00(lVar13,0x46b,0);
    if (cVar3 != '\0') {
      lVar13 = *(longlong *)(thisObject + 0x90);
      if (lVar13 == 0) goto LAB_7ffe9a44b97a;
      lVar17 = *(longlong *)(lVar13 + 0x70);
      uVar24 = FUN_7ffe9a47fef0(lVar13,0);
      if (lVar17 == 0) goto LAB_7ffe9a44b97a;
      uVar23 = 0;
      cVar3 = FUN_7ffe99a231d0(lVar17,0xf,uVar24,alStack_68 + 1,0);
      if (cVar3 != '\0') {
        if ((*(longlong *)(thisObject + 0x90) == 0) ||
           (lVar13 = FUN_7ffe9a47f670(*(longlong *)(thisObject + 0x90),0), lVar13 == 0))
        goto LAB_7ffe9a44b97a;
        cVar3 = FUN_7ffe9ab94d80(lVar13,0x46b,&lStack_70,_DAT_7ffe9c92d5c8);
        if (cVar3 != '\0') {
          if (lStack_70 == 0) goto LAB_7ffe9a44b97a;
          cVar3 = FUN_7ffe9a5224e0(lStack_70,7);
          if (cVar3 != '\0') {
            lVar13 = func_0x7ffe99742fe0(0x16,thisObject);
            if ((lVar13 == 0) || (lVar13 = func_0x7ffe99742fe0(4,lVar13), lVar13 == 0))
            goto LAB_7ffe9a44b97a;
            func_0x7ffe9a480d40(lVar13,1,0);
            bVar21 = false;
          }
        }
      }
    }
    plVar18 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar18 == (longlong *)0x0) ||
       (lVar13 = (**(code **)(*plVar18 + 0x1c8))(plVar18,*(undefined8 *)(*plVar18 + 0x1d0)),
       lVar13 == 0)) goto LAB_7ffe9a44b97a;
    cVar3 = FUN_7ffe9abc2210(lVar13,0x303,alStack_68,_DAT_7ffe9c969d88);
    lVar13 = alStack_68[0];
    if (cVar3 != '\0') {
      plVar18 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if (((plVar18 == (longlong *)0x0) ||
          (lVar17 = (**(code **)(*plVar18 + 0x198))(plVar18,*(undefined8 *)(*plVar18 + 0x1a0)),
          lVar17 == 0)) || (uVar24 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar17), lVar13 == 0))
      goto LAB_7ffe9a44b97a;
      iVar8 = func_0x7ffe9a7a3d50(lVar13,uVar24,0);
      if (0 < iVar6 - iVar8) {
        bVar21 = false;
        plVar18 = (longlong *)
                  (**(code **)(*(longlong *)thisObject + 0x298))
                            (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
        if ((plVar18 == (longlong *)0x0) ||
           (lVar13 = (**(code **)(*plVar18 + 0x178))(plVar18,*(undefined8 *)(*plVar18 + 0x180)),
           lVar13 == 0)) goto LAB_7ffe9a44b97a;
        func_0x7ffe9a480d40(lVar13,iVar6 - iVar8,0,0);
      }
    }
    plVar18 = (longlong *)
              (**(code **)(*(longlong *)thisObject + 0x298))
                        (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
    if ((plVar18 == (longlong *)0x0) ||
       (lVar13 = (**(code **)(*plVar18 + 0x1c8))(plVar18,*(undefined8 *)(*plVar18 + 0x1d0)),
       lVar13 == 0)) goto LAB_7ffe9a44b97a;
    cVar3 = FUN_7ffe9a7cbb30(lVar13,0x486,&plStack_d8,0);
    if (cVar3 == '\0') {
LAB_7ffe9a44b07d:
      if (bVar21) {
        uVar12 = CONCAT44(uVar23,*(undefined4 *)(damageData + 0x84));
        FUN_7ffe9974ab00(0x29,thisObject,actor,id,uVar12);
        uVar23 = (undefined4)((ulonglong)uVar12 >> 0x20);
      }
    }
    else {
      plVar18 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar18 == (longlong *)0x0) ||
         (lVar13 = (**(code **)(*plVar18 + 0x178))(plVar18,*(undefined8 *)(*plVar18 + 0x180)),
         plVar18 = plStack_d8, lVar13 == 0)) goto LAB_7ffe9a44b97a;
      if (0 < *(int *)(lVar13 + 0x14)) goto LAB_7ffe9a44b07d;
      lVar13 = FUN_7ffe99744bb0(plStack_d8,_DAT_7ffe9c917ea0);
      if (lVar13 == 0) goto LAB_7ffe9a44b97a;
      uVar12 = FUN_7ffe99744bb0(plVar18,_DAT_7ffe9c917ea0);
      cVar3 = FUN_7ffe9a78e2e0(uVar12,0);
      if (cVar3 == '\0') goto LAB_7ffe9a44b07d;
      *(uint *)(damageData + 0x70) = *(uint *)(damageData + 0x70) | 0x40000;
      lVar13 = func_0x7ffe99742fe0(0x16,thisObject);
      if ((lVar13 == 0) || (lVar13 = func_0x7ffe99742fe0(4,lVar13), lVar13 == 0))
      goto LAB_7ffe9a44b97a;
      func_0x7ffe9a480d40(lVar13,1);
    }
    iVar6 = 0;
    if (cStack_d0 == '\0') {
      iVar6 = iVar10;
    }
    if ((iVar6 != 0) && (lStack_98 != 0)) {
      FUN_7ffe9a7a0830(lStack_98,0);
      thisObject[0x40] = 0;
      thisObject[0x70] = 0;
      if (*(longlong *)(thisObject + 0x30) == 0) goto LAB_7ffe9a44b97a;
      func_0x7ffe9a7e0410(*(longlong *)(thisObject + 0x30),0);
      plVar18 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar18 == (longlong *)0x0) ||
         (lVar13 = (**(code **)(*plVar18 + 0x198))(plVar18,*(undefined8 *)(*plVar18 + 0x1a0)),
         lVar13 == 0)) goto LAB_7ffe9a44b97a;
      iVar10 = FUN_7ffe99742ec0(10,_DAT_7ffe9c940d40,lVar13);
      plVar18 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar18 == (longlong *)0x0) ||
         (lVar13 = (**(code **)(*plVar18 + 0x178))(plVar18,*(undefined8 *)(*plVar18 + 0x180)),
         lVar13 == 0)) goto LAB_7ffe9a44b97a;
      func_0x7ffe9a480d40(lVar13,(int)((float)iVar10 * fVar2),0,0);
    }
  }
  cVar3 = (**(code **)(*(longlong *)thisObject + 0x188))
                    (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
  if (cVar3 == '\0') {
    FUN_7ffe9a7ab7c0(thisObject,0);
  }
  if (*(int *)(damageData + 0x8c) == 0) {
    FUN_7ffe9a444c10(thisObject,actor,damageData,0);
  }
  else {
    cVar3 = (**(code **)(*(longlong *)thisObject + 0x188))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400));
    if ((cVar3 == '\0') ||
       ((cVar3 = (**(code **)(*(longlong *)thisObject + 0x188))
                           (thisObject,*(undefined8 *)(*(longlong *)thisObject + 400)),
        cVar3 != '\0' && (*(int *)(damageData + 0x8c) != 4)))) {
      if (*(longlong *)(thisObject + 0x108) == 0) goto LAB_7ffe9a44b97a;
      uVar9 = FUN_7ffe99aaea90(*(longlong *)(thisObject + 0x108),0);
      if (uVar9 == 0xffffffff) {
        return;
      }
      PlayerActionManager_CalcAbnormalKnockBackDistance(thisObject,damageData,(undefined *)0x0);
      uVar19 = (undefined1)uVar9;
      if (*(int *)(damageData + 0x8c) == 4) {
        if (*(longlong *)(thisObject + 0x20) == 0) goto LAB_7ffe9a44b97a;
        uVar12 = FUN_7ffe9bd98960(*(longlong *)(thisObject + 0x20),0);
        uVar27 = 0;
        cVar3 = FUN_7ffe99b1cb30(thisObject,action,uVar12,&uStack_90,0);
        uVar23 = (undefined4)((ulonglong)uVar27 >> 0x20);
        if (cVar3 == '\0') goto LAB_7ffe9a44b188;
        uVar22 = 0;
        uStack_c8 = uStack_90;
        fStack_c0 = fStack_88;
        uVar12 = CONCAT71((int7)((ulonglong)uVar27 >> 8),uVar19);
        cVar3 = FUN_7ffe9a443040(thisObject,actor,damageData,&uStack_c8,uVar12,0);
        uVar23 = (undefined4)((ulonglong)uVar12 >> 0x20);
      }
      else {
LAB_7ffe9a44b188:
        uVar27 = CONCAT44(uVar22,*(undefined4 *)(damageData + 0x98));
        uVar12 = CONCAT44(uVar23,*(undefined4 *)(damageData + 0x94));
        cVar3 = FUN_7ffe99744fb0(0x10,thisObject,actor,*(undefined4 *)(damageData + 0x8c),uVar12,
                                 uVar27,*(undefined4 *)(damageData + 0x9c),uVar19,damageData[0xa1]);
        uVar22 = (undefined4)((ulonglong)uVar27 >> 0x20);
        uVar23 = (undefined4)((ulonglong)uVar12 >> 0x20);
      }
      if (cVar3 == '\0') {
        if (*(longlong *)(thisObject + 0x108) == 0) goto LAB_7ffe9a44b97a;
        FUN_7ffe99aaebf0(*(longlong *)(thisObject + 0x108),uVar9 & 0xff,0);
      }
      else {
        lVar13 = func_0x7ffe99742fe0(0x16,thisObject);
        if ((lVar13 == 0) || (lVar13 = func_0x7ffe99742fe0(0xb,lVar13), lVar13 == 0))
        goto LAB_7ffe9a44b97a;
        uVar23 = FUN_7ffe9a4db490(lVar13,*(undefined4 *)(damageData + 0x8c),0);
        *(undefined4 *)(damageData + 0x94) = uVar23;
        damageData[0xa0] = uVar19;
        lVar13 = *(longlong *)thisObject;
        (**(code **)(lVar13 + 0x358))
                  (thisObject,*(undefined4 *)(damageData + 0x8c),lVar13,(damageData[0x70] & 1) != 0,
                   *(undefined8 *)(lVar13 + 0x360));
        uVar9 = *(uint *)(damageData + 0x8c);
        if (DAT_7ffe9caddcbc == '\0') {
          FUN_7ffe9996d590(&DAT_7ffe9c956ad0);
          DAT_7ffe9caddcbc = '\x01';
        }
        if (((uVar9 < 0x27) && ((0x6b409dfffeU >> ((longlong)(int)uVar9 & 0x3fU) & 1) != 0)) ||
           (uVar9 - 0x28 < 5)) {
          lVar13 = FUN_7ffe9b141840(_DAT_7ffe9c956ad0);
          if ((lVar13 == 0) || (*(longlong *)(lVar13 + 0x188) == 0)) goto LAB_7ffe9a44b97a;
          FUN_7ffe9a502150(*(longlong *)(lVar13 + 0x188),uVar9,0);
        }
        lVar13 = func_0x7ffe99940040(_DAT_7ffe9c92ee68);
        FUN_7ffe9bc60410(lVar13,0);
        puVar15 = (undefined *)func_0x7ffe99742fe0(0x16);
        bVar20 = GemCartBuffer_BerserkSuppressionBuff_Exemption(puVar15,(undefined *)0x0);
        if (bVar20 != 0) {
          if (lVar13 == 0) goto LAB_7ffe9a44b97a;
          FUN_7ffe9bc5ffd0(lVar13,0x2e,1,0);
          *(uint *)(damageData + 0x70) = *(uint *)(damageData + 0x70) | 0x20;
        }
        lVar17 = *(longlong *)thisObject;
        uVar12 = *(undefined8 *)(lVar17 + 0x350);
        (**(code **)(lVar17 + 0x348))
                  (thisObject,*(undefined4 *)(damageData + 0x8c),lVar17,lVar13,uVar12);
        uVar23 = (undefined4)((ulonglong)uVar12 >> 0x20);
      }
    }
  }
  plVar18 = *(longlong **)(thisObject + 0x30);
  if (plVar18 != (longlong *)0x0) {
    iVar10 = (**(code **)(*plVar18 + 0x178))(plVar18,*(undefined8 *)(*plVar18 + 0x180));
    if (iVar10 != 2) {
      cVar3 = func_0x7ffe9a4deb00(*(undefined4 *)(damageData + 0x8c),0);
      if (((cVar3 == '\0') && (cVar3 = FUN_7ffe99b1ccd0(thisObject,0), cVar3 == '\0')) &&
         (*(int *)(damageData + 0x18) - 4U < 2)) {
        if (*(int *)(_DAT_7ffe9c92dfe0 + 0xe0) == 0) {
          func_0x7ffe9996d830();
        }
        uVar24 = FUN_7ffe9a4db1f0(1,0);
        uVar25 = FUN_7ffe9a4db080(1,0);
        uVar28 = CONCAT44(uVar22,uVar25);
        uVar12 = CONCAT44(uVar23,uVar24);
        FUN_7ffe99744fb0(0x10,thisObject,actor,1,uVar12,uVar28,0,0,1);
        uVar23 = (undefined4)((ulonglong)uVar12 >> 0x20);
        if (*(longlong *)(thisObject + 0x30) == 0) goto LAB_7ffe9a44b97a;
        iVar10 = func_0x7ffe99742fe0(4);
        if (iVar10 == 0) {
          FUN_7ffe99744fb0(0x10,thisObject,actor,0x1b,CONCAT44(uVar23,_DAT_7ffe9c049b70),
                           uVar28 & 0xffffffff00000000,0,0,1);
        }
      }
      plVar18 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar18 == (longlong *)0x0) ||
         (lVar13 = (**(code **)(*plVar18 + 0x1c8))(plVar18,*(undefined8 *)(*plVar18 + 0x1d0)),
         lVar13 == 0)) goto LAB_7ffe9a44b97a;
      cVar3 = FUN_7ffe9a7cbb30(lVar13,0x10b,&plStack_d8,0);
      plVar18 = plStack_d8;
      if ((cVar3 != '\0') && (*(int *)(damageData + 0x18) - 4U < 2)) {
        lVar13 = FUN_7ffe99744bb0(plStack_d8,_DAT_7ffe9c912320);
        if (lVar13 == 0) goto LAB_7ffe9a44b97a;
        uVar12 = FUN_7ffe99744bb0(plVar18,_DAT_7ffe9c912320);
        FUN_7ffe9a79d960(uVar12,0);
      }
    }
    lVar13 = FUN_7ffe9a4565c0(thisObject,0);
    if (lVar13 != 0) {
      FUN_7ffe9a45bd40(lVar13,*(undefined4 *)(damageData + 0x84),0);
      plVar18 = (longlong *)
                (**(code **)(*(longlong *)thisObject + 0x298))
                          (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x2a0));
      if ((plVar18 != (longlong *)0x0) &&
         (lVar13 = (**(code **)(*plVar18 + 0x1c8))(plVar18,*(undefined8 *)(*plVar18 + 0x1d0)),
         lVar13 != 0)) {
        cVar3 = FUN_7ffe9a7cbb30(lVar13,0x5e,&plStack_d8);
        if (cVar3 != '\0') {
          if (plStack_d8 == (longlong *)0x0) goto LAB_7ffe9a44b97a;
          if (((*(byte *)(*plStack_d8 + 0x130) < *(byte *)(_DAT_7ffe9c9530e0 + 0x130)) ||
              (*(longlong *)
                (*(longlong *)(*plStack_d8 + 200) + -8 +
                (ulonglong)*(byte *)(_DAT_7ffe9c9530e0 + 0x130) * 8) != _DAT_7ffe9c9530e0)) ||
             (plStack_d8 == (longlong *)0x0)) {
            FUN_7ffe9996c950(plStack_d8);
            pcVar1 = (code *)swi(3);
            (*pcVar1)();
            return;
          }
          func_0x7ffe99a998f0(plStack_d8,0);
        }
        return;
      }
    }
  }
LAB_7ffe9a44b97a:
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

