
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void SkillBufferManager_ClearFirstAidBuffer(undefined *self,undefined *methodInfo)

{
  undefined4 uVar1;
  longlong lVar2;
  longlong lVar3;
  code *pcVar4;
  uint uVar5;
  undefined4 uVar6;
  uint uVar7;
  uint uVar8;
  char cVar9;
  uint uVar10;
  longlong lVar11;
  longlong lVar12;
  longlong *plVar13;
  uint uVar14;
  undefined4 auStackX_10 [2];
  longlong lStackX_18;
  longlong lStackX_20;
  
  if (DAT_7ffe9cadf589 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c934350);
    DAT_7ffe9cadf589 = '\x01';
  }
  if (*(longlong *)(self + 0x40) != 0) {
    FUN_7ffe9ad86f60(*(longlong *)(self + 0x40),9,_DAT_7ffe9c934350);
    lVar12 = _DAT_7ffe9c934350;
    lVar2 = *(longlong *)(self + 0x50);
    if (lVar2 != 0) {
      lStackX_18 = _DAT_7ffe9c934350;
      auStackX_10[0] = 9;
      if (*(longlong *)(lVar2 + 0x10) != 0) {
        lVar3 = *(longlong *)(lVar2 + 0x30);
        if (lVar3 == 0) {
          uVar10 = func_0x7ffe9a331500(auStackX_10,0);
        }
        else {
          lVar11 = *(longlong *)(*(longlong *)(*(longlong *)(_DAT_7ffe9c934350 + 0x20) + 0xc0) + 8);
          if ((*(byte *)(lVar11 + 0x135) & 1) == 0) {
            lVar11 = FUN_7ffe998ced40(lVar11);
          }
          uVar10 = FUN_7ffe99749320(1,lVar11,lVar3,9);
        }
        lVar3 = *(longlong *)(lVar2 + 0x10);
        if (lVar3 == 0) {
LAB_7ffe9ad87187:
          FUN_7ffe9996d7a0();
          pcVar4 = (code *)swi(3);
          (*pcVar4)();
          return;
        }
        uVar14 = (int)(uVar10 & 0x7fffffff) % *(int *)(lVar3 + 0x18);
        if (*(uint *)(lVar3 + 0x18) <= uVar14) {
LAB_7ffe9ad8718d:
          FUN_7ffe9996d790();
          pcVar4 = (code *)swi(3);
          (*pcVar4)();
          return;
        }
        lStackX_20 = (longlong)(int)uVar14 * 4 + 0x20;
        uVar8 = *(int *)(lStackX_20 + lVar3) - 1;
        uVar6 = auStackX_10[0];
        uVar7 = 0xffffffff;
        while (uVar5 = uVar8, -1 < (int)uVar5) {
          lVar3 = *(longlong *)(lVar2 + 0x18);
          auStackX_10[0] = uVar6;
          if (lVar3 == 0) goto LAB_7ffe9ad87187;
          if (*(uint *)(lVar3 + 0x18) <= uVar5) goto LAB_7ffe9ad8718d;
          lVar11 = lVar3 + (longlong)(int)uVar5 * 0x18;
          if (*(uint *)(lVar3 + 0x20 + (longlong)(int)uVar5 * 0x18) == (uVar10 & 0x7fffffff)) {
            lVar3 = *(longlong *)(lVar2 + 0x30);
            if (lVar3 == 0) {
              plVar13 = (longlong *)
                        FUN_7ffe99755f20(*(undefined8 *)
                                          (*(longlong *)(*(longlong *)(lVar12 + 0x20) + 0xc0) + 0x18
                                          ));
              if (plVar13 == (longlong *)0x0) goto LAB_7ffe9ad87187;
              cVar9 = (**(code **)(*plVar13 + 0x1b8))
                                (plVar13,*(undefined4 *)(lVar11 + 0x28),auStackX_10[0],
                                 *(undefined8 *)(*plVar13 + 0x1c0));
            }
            else {
              uVar1 = *(undefined4 *)(lVar11 + 0x28);
              lVar12 = *(longlong *)(*(longlong *)(*(longlong *)(lStackX_18 + 0x20) + 0xc0) + 8);
              if ((*(byte *)(lVar12 + 0x135) & 1) == 0) {
                lVar12 = FUN_7ffe998ced40(lVar12);
              }
              cVar9 = FUN_7ffe99747010(0,lVar12,lVar3,uVar1,uVar6);
              lVar12 = lStackX_18;
            }
            if (cVar9 != '\0') {
              if ((int)uVar7 < 0) {
                lVar12 = *(longlong *)(lVar2 + 0x10);
                if (lVar12 == 0) goto LAB_7ffe9ad87187;
                if (*(uint *)(lVar12 + 0x18) <= uVar14) goto LAB_7ffe9ad8718d;
                *(int *)(lStackX_20 + lVar12) = *(int *)(lVar11 + 0x24) + 1;
              }
              else {
                lVar12 = *(longlong *)(lVar2 + 0x18);
                if (lVar12 == 0) goto LAB_7ffe9ad87187;
                if (*(uint *)(lVar12 + 0x18) <= uVar7) goto LAB_7ffe9ad8718d;
                *(undefined4 *)(lVar12 + 0x24 + (longlong)(int)uVar7 * 0x18) =
                     *(undefined4 *)(lVar11 + 0x24);
              }
              *(undefined4 *)(lVar11 + 0x20) = 0xffffffff;
              *(undefined4 *)(lVar11 + 0x24) = *(undefined4 *)(lVar2 + 0x24);
              *(undefined8 *)(lVar11 + 0x30) = 0;
              *(int *)(lVar2 + 0x28) = *(int *)(lVar2 + 0x28) + 1;
              *(int *)(lVar2 + 0x2c) = *(int *)(lVar2 + 0x2c) + 1;
              *(uint *)(lVar2 + 0x24) = uVar5;
              return;
            }
          }
          uVar6 = auStackX_10[0];
          uVar7 = uVar5;
          uVar8 = *(uint *)(lVar11 + 0x24);
        }
      }
      return;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar4 = (code *)swi(3);
  (*pcVar4)();
  return;
}

