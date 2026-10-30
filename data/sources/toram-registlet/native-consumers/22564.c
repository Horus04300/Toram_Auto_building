
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void AuraBladeAction_calcPlayerToMobDamage
               (undefined *thisObject,undefined *playerAction,undefined *mobAction,
               undefined *methodInfo)

{
  int iVar1;
  uint uVar2;
  longlong lVar3;
  code *pcVar4;
  longlong lVar5;
  char cVar6;
  undefined1 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  int iVar10;
  longlong *plVar11;
  longlong lVar12;
  undefined8 uVar13;
  undefined *puVar14;
  longlong lStackX_8;
  undefined8 in_stack_ffffffffffffffa8;
  undefined4 uVar15;
  
  uVar15 = (undefined4)((ulonglong)in_stack_ffffffffffffffa8 >> 0x20);
  if (DAT_7ffe9cadeb5e == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c920098);
    FUN_7ffe9996d590(&DAT_7ffe9c928aa8);
    FUN_7ffe9996d590(&DAT_7ffe9c928b70);
    FUN_7ffe9996d590(&DAT_7ffe9c940d40);
    FUN_7ffe9996d590(&DAT_7ffe9c913488);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c94a078);
    DAT_7ffe9cadeb5e = '\x01';
  }
  lStackX_8 = 0;
  if (*(longlong *)(thisObject + 0x130) == 0) goto LAB_7ffe9a6341dd;
  cVar6 = FUN_7ffe9adb0cf0(*(longlong *)(thisObject + 0x130),mobAction,&lStackX_8,_DAT_7ffe9c928b70)
  ;
  if (cVar6 == '\0') {
    uVar8 = FUN_7ffe9a4adee0(thisObject,playerAction,mobAction,0);
    *(undefined4 *)(thisObject + 0x30) = uVar8;
    if (((playerAction == (undefined *)0x0) ||
        (plVar11 = (longlong *)
                   (**(code **)(*(longlong *)playerAction + 0x298))
                             (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0)),
        plVar11 == (longlong *)0x0)) ||
       (lVar12 = (**(code **)(*plVar11 + 0x1a8))(plVar11,*(undefined8 *)(*plVar11 + 0x1b0)),
       lVar12 == 0)) goto LAB_7ffe9a6341dd;
    uVar8 = FUN_7ffe99742ec0(0x1b,_DAT_7ffe9c940d40,lVar12);
    uVar7 = FUN_7ffe9a4b33f0(thisObject,uVar8,mobAction,0);
    uVar13 = func_0x7ffe99940040(_DAT_7ffe9c94a078);
    FUN_7ffe9a6596c0(uVar13,0);
    uVar8 = (**(code **)(*(longlong *)thisObject + 0x198))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x1a0));
    uVar9 = (**(code **)(*(longlong *)thisObject + 0x588))
                      (thisObject,*(undefined8 *)(*(longlong *)thisObject + 0x590));
    lVar12 = FUN_7ffe9a4b1c10(thisObject,uVar13,playerAction,mobAction,CONCAT44(uVar15,uVar8),uVar9,
                              0,uVar7,0);
    if (lVar12 == 0) goto LAB_7ffe9a6341dd;
    FUN_7ffe9a657c40(lVar12,0x12,*(float *)(thisObject + 0x120) / _DAT_7ffe9c049cfc,0);
    FUN_7ffe9a657a50(lVar12,8);
    uVar13 = func_0x7ffe99940040(_DAT_7ffe9c920098);
    FUN_7ffe9a8f6350(uVar13,mobAction,0);
    lStackX_8 = FUN_7ffe9a4b4370(thisObject,uVar13,lVar12,*(undefined4 *)(thisObject + 0x128),0);
    if (lStackX_8 == 0) goto LAB_7ffe9a6341dd;
    if ((*(int *)(lStackX_8 + 0x1c) == 0) || (*(int *)(lStackX_8 + 0x34) == 1)) {
LAB_7ffe9a634090:
      if (1 < *(int *)(thisObject + 0x128)) {
        if (((lStackX_8 == 0) || (*(longlong *)(lStackX_8 + 0x38) == 0)) ||
           ((lVar12 = FUN_7ffe9a8ffa40(*(longlong *)(lStackX_8 + 0x38),0), lVar12 == 0 ||
            ((((func_0x7ffe9a900040(lVar12,0,0), lStackX_8 == 0 ||
               (*(longlong *)(lStackX_8 + 0x38) == 0)) ||
              (*(undefined4 *)(lVar12 + 0x18) =
                    *(undefined4 *)(*(longlong *)(lStackX_8 + 0x38) + 0x18), lStackX_8 == 0)) ||
             (*(longlong *)(lStackX_8 + 0x38) == 0)))))) goto LAB_7ffe9a6341dd;
        *(undefined4 *)(lVar12 + 0x14) = *(undefined4 *)(*(longlong *)(lStackX_8 + 0x38) + 0x14);
      }
    }
    else {
      if (mobAction == (undefined *)0x0) goto LAB_7ffe9a6341dd;
      cVar6 = FUN_7ffe99742ec0(0x14,_DAT_7ffe9c9724e0,mobAction);
      if (cVar6 != '\0') goto LAB_7ffe9a634090;
      if ((*(undefined **)(thisObject + 0x138) != (undefined *)0x0) &&
         (*(undefined **)(thisObject + 0x138) == mobAction)) {
        plVar11 = (longlong *)
                  (**(code **)(*(longlong *)playerAction + 0x298))
                            (playerAction,*(undefined8 *)(*(longlong *)playerAction + 0x2a0));
        if ((plVar11 == (longlong *)0x0) ||
           (puVar14 = (undefined *)
                      (**(code **)(*plVar11 + 0x218))(plVar11,*(undefined8 *)(*plVar11 + 0x220)),
           puVar14 == (undefined *)0x0)) goto LAB_7ffe9a6341dd;
        puVar14 = GemCartBufferManager_GetGemCartBuffer(puVar14,0x411,(undefined *)0x0);
        lVar12 = lStackX_8;
        if (puVar14 != (undefined *)0x0) {
          if (lStackX_8 == 0) goto LAB_7ffe9a6341dd;
          iVar1 = *(int *)(lStackX_8 + 0x18);
          iVar10 = GemCartBufferBase_GetValue(puVar14,(undefined *)0x2,(undefined *)0x0);
          lVar5 = lStackX_8;
          *(int *)(lVar12 + 0x18) = (int)((float)(iVar10 * iVar1) / _DAT_7ffe9c049cfc);
          if (lStackX_8 == 0) goto LAB_7ffe9a6341dd;
          uVar15 = *(undefined4 *)(lStackX_8 + 0x18);
          uVar13 = FUN_7ffe9a4adac0(thisObject,*(undefined4 *)(thisObject + 0x128),0);
          FUN_7ffe9a8f6510(lVar5,uVar15,uVar13,0);
        }
      }
    }
    if (*(longlong *)(thisObject + 0x130) == 0) goto LAB_7ffe9a6341dd;
    FUN_7ffe9ada6d80(*(longlong *)(thisObject + 0x130),mobAction,lStackX_8,_DAT_7ffe9c928aa8);
  }
  else {
    if (lStackX_8 == 0) goto LAB_7ffe9a6341dd;
    FUN_7ffe9a8f6320(lStackX_8,0);
  }
  lVar5 = _DAT_7ffe9c913488;
  lVar12 = *(longlong *)(thisObject + 0x80);
  if (lVar12 != 0) {
    *(int *)(lVar12 + 0x1c) = *(int *)(lVar12 + 0x1c) + 1;
    lVar3 = *(longlong *)(lVar12 + 0x10);
    uVar2 = *(uint *)(lVar12 + 0x18);
    if (lVar3 != 0) {
      if (uVar2 < *(uint *)(lVar3 + 0x18)) {
        *(uint *)(lVar12 + 0x18) = uVar2 + 1;
        if (*(uint *)(lVar3 + 0x18) <= uVar2) {
          FUN_7ffe9996d790();
          pcVar4 = (code *)swi(3);
          (*pcVar4)();
          return;
        }
        *(longlong *)(lVar3 + 0x20 + (longlong)(int)uVar2 * 8) = lStackX_8;
        il2cpp_write_barrier_0();
      }
      else {
        FUN_7ffe9afd58b0(lVar12,lStackX_8,
                         *(undefined8 *)(*(longlong *)(*(longlong *)(lVar5 + 0x20) + 0xc0) + 0x70));
      }
      return;
    }
  }
LAB_7ffe9a6341dd:
  FUN_7ffe9996d7a0();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

