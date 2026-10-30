
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void AutoDeviceAttackAction_ActionPreparation
               (undefined *thisObject,undefined *actarAction,undefined *target,undefined *methodInfo
               )

{
  uint uVar1;
  float fVar2;
  longlong lVar3;
  code *pcVar4;
  bool bVar5;
  longlong lVar6;
  char cVar7;
  byte bVar8;
  longlong *plVar9;
  longlong lVar10;
  undefined8 uVar11;
  undefined *thisObject_00;
  undefined8 *puVar12;
  longlong *plVar13;
  float fVar14;
  float fVar15;
  longlong lStackX_8;
  longlong *plStackX_10;
  float fStack_88;
  undefined1 auStack_78 [8];
  float fStack_70;
  
  if (DAT_7ffe9cadf2c4 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c91ffd0);
    FUN_7ffe9996d590(&DAT_7ffe9c934418);
    FUN_7ffe9996d590(&DAT_7ffe9c935bd0);
    FUN_7ffe9996d590(&DAT_7ffe9c962758);
    FUN_7ffe9996d590(&DAT_7ffe9c9132e8);
    FUN_7ffe9996d590(&DAT_7ffe9c9724e0);
    FUN_7ffe9996d590(&DAT_7ffe9c903520);
    FUN_7ffe9996d590(&DAT_7ffe9c906b90);
    FUN_7ffe9996d590(&DAT_7ffe9c922720);
    DAT_7ffe9cadf2c4 = '\x01';
  }
  plVar13 = (longlong *)0x0;
  plStackX_10 = (longlong *)0x0;
  lStackX_8 = 0;
  FUN_7ffe9a4a5ca0(thisObject,actarAction,target,0);
  *(uint *)(thisObject + 0x108) = *(uint *)(thisObject + 0x108) & 0xffffffef;
  if (actarAction != (undefined *)0x0) {
    if ((*(byte *)(*(longlong *)actarAction + 0x130) < *(byte *)(_DAT_7ffe9c922720 + 0x130)) ||
       (*(longlong *)
         (*(longlong *)(*(longlong *)actarAction + 200) + -8 +
         (ulonglong)*(byte *)(_DAT_7ffe9c922720 + 0x130) * 8) != _DAT_7ffe9c922720)) {
      bVar5 = false;
    }
    else {
      bVar5 = true;
    }
    plVar13 = (longlong *)0x0;
    if (bVar5) {
      plVar13 = (longlong *)actarAction;
    }
  }
  if (*(int *)(_DAT_7ffe9c906b90 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  cVar7 = FUN_7ffe9bda2160(plVar13,0,0);
  if (cVar7 == '\0') {
    return;
  }
  if ((((plVar13 == (longlong *)0x0) ||
       (plVar9 = (longlong *)
                 (**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0)),
       plVar9 == (longlong *)0x0)) ||
      (lVar10 = (**(code **)(*plVar9 + 0x1c8))(plVar9,*(undefined8 *)(*plVar9 + 0x1d0)), lVar10 == 0
      )) || (*(longlong *)(lVar10 + 0x50) == 0)) goto LAB_7ffe9a76466c;
  cVar7 = FUN_7ffe9ad8e670(*(longlong *)(lVar10 + 0x50),0x268,&plStackX_10,_DAT_7ffe9c934418);
  plVar9 = plStackX_10;
  if (cVar7 != '\0') {
    if (plStackX_10 == (longlong *)0x0) goto LAB_7ffe9a76466c;
    if (((*(byte *)(*plStackX_10 + 0x130) < *(byte *)(_DAT_7ffe9c903520 + 0x130)) ||
        (*(longlong *)
          (*(longlong *)(*plStackX_10 + 200) + -8 +
          (ulonglong)*(byte *)(_DAT_7ffe9c903520 + 0x130) * 8) != _DAT_7ffe9c903520)) ||
       (plStackX_10 == (longlong *)0x0)) {
      FUN_7ffe9996c950(plStackX_10);
      pcVar4 = (code *)swi(3);
      (*pcVar4)();
      return;
    }
    lVar10 = *(longlong *)(thisObject + 0x50);
    lVar6 = plStackX_10[4];
    uVar11 = func_0x7ffe99940040(_DAT_7ffe9c91ffd0);
    FUN_7ffe9a8edff0(uVar11,0x268,plVar9,(int)lVar6,0);
    lVar6 = _DAT_7ffe9c9132e8;
    if (lVar10 == 0) goto LAB_7ffe9a76466c;
    *(int *)(lVar10 + 0x1c) = *(int *)(lVar10 + 0x1c) + 1;
    lVar3 = *(longlong *)(lVar10 + 0x10);
    uVar1 = *(uint *)(lVar10 + 0x18);
    if (lVar3 == 0) goto LAB_7ffe9a76466c;
    if (uVar1 < *(uint *)(lVar3 + 0x18)) {
      *(uint *)(lVar10 + 0x18) = uVar1 + 1;
      if (*(uint *)(lVar3 + 0x18) <= uVar1) {
        FUN_7ffe9996d790();
        pcVar4 = (code *)swi(3);
        (*pcVar4)();
        return;
      }
      *(undefined8 *)(lVar3 + (longlong)(int)uVar1 * 8 + 0x20) = uVar11;
      il2cpp_write_barrier_0();
    }
    else {
      FUN_7ffe9afd58b0(lVar10,uVar11,
                       *(undefined8 *)(*(longlong *)(*(longlong *)(lVar6 + 0x20) + 0xc0) + 0x70));
    }
  }
  plVar9 = (longlong *)(**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
  if ((plVar9 != (longlong *)0x0) &&
     (thisObject_00 =
           (undefined *)(**(code **)(*plVar9 + 0x218))(plVar9,*(undefined8 *)(*plVar9 + 0x220)),
     thisObject_00 != (undefined *)0x0)) {
    bVar8 = GemCartBufferManager_ContainsBuffer(thisObject_00,0xcf,(undefined *)0x0);
    if (bVar8 != 0) {
      return;
    }
    plVar9 = (longlong *)(**(code **)(*plVar13 + 0x298))(plVar13,*(undefined8 *)(*plVar13 + 0x2a0));
    if (((plVar9 != (longlong *)0x0) &&
        (lVar10 = (**(code **)(*plVar9 + 0x1b8))(plVar9,*(undefined8 *)(*plVar9 + 0x1c0)),
        lVar10 != 0)) && (*(longlong *)(lVar10 + 0x68) != 0)) {
      cVar7 = FUN_7ffe9ad8e670(*(longlong *)(lVar10 + 0x68),0x6b,&lStackX_8,_DAT_7ffe9c935bd0);
      if (cVar7 == '\0') {
        return;
      }
      fVar15 = 0.0;
      if (target != (undefined *)0x0) {
        lVar10 = FUN_7ffe9ab9c3a0(target,_DAT_7ffe9c962758);
        if (lVar10 != 0) {
          fVar15 = (float)FUN_7ffe99744d60(0,_DAT_7ffe9c9724e0,lVar10);
        }
        if ((lStackX_8 != 0) && (*(longlong *)(lStackX_8 + 0x10) != 0)) {
          FUN_7ffe999fc9a0((float)*(byte *)(*(longlong *)(lStackX_8 + 0x10) + 0x18) *
                           _DAT_7ffe9c049b4c,0);
          FUN_7ffe9a4ad740(plVar13,0xe);
          fVar14 = (float)func_0x7ffe99a4d6a0();
          lVar10 = FUN_7ffe9bd9b890(target,0);
          if (lVar10 != 0) {
            puVar12 = (undefined8 *)FUN_7ffe9bdbf710(auStack_78,lVar10,0);
            uVar11 = *puVar12;
            fVar2 = *(float *)(puVar12 + 1);
            if ((actarAction != (undefined *)0x0) &&
               (lVar10 = FUN_7ffe9bd98a10(actarAction,0), lVar10 != 0)) {
              puVar12 = (undefined8 *)FUN_7ffe9bdbf710(auStack_78,lVar10,0);
              fStack_88 = (float)uVar11;
              fStack_70 = *(float *)(puVar12 + 1);
              fStack_88 = fStack_88 - (float)*puVar12;
              fVar15 = *(float *)(thisObject + 0x20) + fVar15;
              if (fStack_88 * fStack_88 + 0.0 + (fVar2 - fStack_70) * (fVar2 - fStack_70) <=
                  fVar15 * fVar15) {
                return;
              }
              if (fVar14 <= *(float *)(thisObject + 0x20)) {
                return;
              }
              thisObject[0x128] = 1;
              if ((lStackX_8 != 0) && (*(longlong *)(lStackX_8 + 0x10) != 0)) {
                bVar8 = *(byte *)(*(longlong *)(lStackX_8 + 0x10) + 0x18);
                *(float *)(thisObject + 300) = (float)((uint)bVar8 + (uint)bVar8 * 4);
                cVar7 = FUN_7ffe9a4ad740(plVar13,0xe);
                if (cVar7 == '\0') {
                  cVar7 = FUN_7ffe9a4ad740(plVar13,0xf);
                  if (cVar7 == '\0') {
                    return;
                  }
                  fVar15 = *(float *)(thisObject + 300) + _DAT_7ffe9c049f0c;
                }
                else {
                  fVar15 = *(float *)(thisObject + 300) + _DAT_7ffe9c049dd0;
                }
                *(float *)(thisObject + 300) = fVar15;
                return;
              }
            }
          }
        }
      }
    }
  }
LAB_7ffe9a76466c:
  FUN_7ffe9996d7a0();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

