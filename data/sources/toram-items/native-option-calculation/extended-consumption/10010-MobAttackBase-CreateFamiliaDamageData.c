
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobAttackBase_CreateFamiliaDamageData
               (undefined *self,undefined *familiaAction,undefined *methodInfo)

{
  uint uVar1;
  undefined8 uVar2;
  longlong lVar3;
  longlong lVar4;
  code *pcVar5;
  char cVar6;
  longlong lVar7;
  longlong lVar8;
  int iVar9;
  undefined4 uVar10;
  float fVar11;
  
  if (DAT_7ffe9cadd7d7 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c92dfe0);
    FUN_7ffe9996d590(&DAT_7ffe9c920098);
    FUN_7ffe9996d590(&DAT_7ffe9c913488);
    FUN_7ffe9996d590(&DAT_7ffe9c94aa68);
    DAT_7ffe9cadd7d7 = '\x01';
  }
  lVar7 = func_0x7ffe99940040(_DAT_7ffe9c920098);
  FUN_7ffe9a8f6490(lVar7,familiaAction,0);
  if (lVar7 == 0) goto LAB_7ffe9a3752b7;
  uVar2 = *(undefined8 *)(lVar7 + 0x48);
  lVar8 = func_0x7ffe99940040(_DAT_7ffe9c94aa68);
  FUN_7ffe9a8fff70(lVar8,uVar2,0);
  if (lVar8 == 0) goto LAB_7ffe9a3752b7;
  func_0x7ffe9a900040(lVar8,0,0);
  *(undefined8 *)(lVar8 + 0x14) = 1;
  *(longlong *)(lVar7 + 0x38) = lVar8;
  il2cpp_write_barrier_0();
  *(undefined4 *)(lVar7 + 0x1c) = 1;
  lVar3 = *(longlong *)(self + 0xa0);
  if ((lVar3 == 0) || ((iVar9 = *(int *)(lVar3 + 0x30), 1 < iVar9 - 1U && (iVar9 != 3)))) {
    *(undefined4 *)(lVar8 + 0x8c) = 0xffffffff;
    if (*(longlong *)(self + 0xa0) == 0) goto LAB_7ffe9a3752b7;
    fVar11 = (float)*(int *)(*(longlong *)(self + 0xa0) + 0x38);
    *(float *)(lVar8 + 0x94) = fVar11;
    iVar9 = *(int *)(lVar8 + 0x8c);
LAB_7ffe9a375211:
    if (*(int *)(_DAT_7ffe9c92dfe0 + 0xe0) == 0) {
      func_0x7ffe9996d830();
    }
    uVar10 = FUN_7ffe9a4daf00(iVar9,fVar11,0);
    *(undefined4 *)(lVar8 + 0x98) = uVar10;
  }
  else {
    cVar6 = FUN_7ffe9a8fea70(self,100,*(undefined4 *)(lVar3 + 0x34));
    if (cVar6 != '\0') {
      *(int *)(lVar8 + 0x8c) = iVar9;
      lVar3 = *(longlong *)(self + 0xa0);
      if (iVar9 == 4) {
        if (lVar3 == 0) goto LAB_7ffe9a3752b7;
        fVar11 = (float)*(int *)(lVar3 + 0x38) / _DAT_7ffe9c049ce4;
        *(float *)(lVar8 + 0x94) = fVar11;
      }
      else {
        if (lVar3 == 0) goto LAB_7ffe9a3752b7;
        fVar11 = (float)*(int *)(lVar3 + 0x38);
        *(float *)(lVar8 + 0x94) = fVar11;
      }
      goto LAB_7ffe9a375211;
    }
  }
  lVar3 = _DAT_7ffe9c913488;
  lVar8 = *(longlong *)(self + 0x80);
  if (lVar8 != 0) {
    *(int *)(lVar8 + 0x1c) = *(int *)(lVar8 + 0x1c) + 1;
    lVar4 = *(longlong *)(lVar8 + 0x10);
    uVar1 = *(uint *)(lVar8 + 0x18);
    if (lVar4 != 0) {
      if (uVar1 < *(uint *)(lVar4 + 0x18)) {
        *(uint *)(lVar8 + 0x18) = uVar1 + 1;
        if (*(uint *)(lVar4 + 0x18) <= uVar1) {
          FUN_7ffe9996d790();
          pcVar5 = (code *)swi(3);
          (*pcVar5)();
          return;
        }
        *(longlong *)(lVar4 + 0x20 + (longlong)(int)uVar1 * 8) = lVar7;
        il2cpp_write_barrier_0();
      }
      else {
        FUN_7ffe9afd58b0(lVar8,lVar7,
                         *(undefined8 *)(*(longlong *)(*(longlong *)(lVar3 + 0x20) + 0xc0) + 0x70));
      }
      return;
    }
  }
LAB_7ffe9a3752b7:
  FUN_7ffe9996d7a0();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}

