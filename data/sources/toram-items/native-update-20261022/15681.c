
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BonusData_UpdateBonusList(undefined *self,undefined *methodInfo)

{
  undefined4 uVar1;
  uint uVar2;
  longlong lVar3;
  longlong lVar4;
  code *pcVar5;
  int iVar6;
  undefined8 uVar7;
  longlong lVar8;
  longlong *plVar9;
  undefined8 *puVar10;
  ushort uVar11;
  int iVar13;
  ulonglong uVar12;
  
  if (DAT_7ffe9cade0f4 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c948b58);
    FUN_7ffe9996d590(&DAT_7ffe9c950ba0);
    FUN_7ffe9996d590(&DAT_7ffe9c95e388);
    FUN_7ffe9996d590(&DAT_7ffe9c94b220);
    FUN_7ffe9996d590(&DAT_7ffe9c9085a0);
    FUN_7ffe9996d590(0x7ffe9c94b2e8);
    FUN_7ffe9996d590(0x7ffe9c908810);
    FUN_7ffe9996d590(0x7ffe9c94b780);
    FUN_7ffe9996d590(&DAT_7ffe9c94b840);
    DAT_7ffe9cade0f4 = '\x01';
  }
  lVar8 = *(longlong *)(self + 0x20);
  if (lVar8 != 0) {
    iVar13 = *(int *)(lVar8 + 0x18);
    *(int *)(lVar8 + 0x1c) = *(int *)(lVar8 + 0x1c) + 1;
    *(undefined4 *)(lVar8 + 0x18) = 0;
    if (0 < iVar13) {
      FUN_7ffe9b518970(*(undefined8 *)(lVar8 + 0x10),0,iVar13,0);
    }
    lVar8 = *(longlong *)(self + 0x20);
    if ((*(longlong *)(self + 0x10) != 0) &&
       (uVar7 = FUN_7ffe9a4f6530(*(longlong *)(self + 0x10),0), lVar8 != 0)) {
      func_0x7ffe9afd5600(lVar8,uVar7,_DAT_7ffe9c94b220);
      lVar8 = *(longlong *)(self + 0x30);
      if (lVar8 != 0) {
        iVar13 = *(int *)(lVar8 + 0x18);
        *(int *)(lVar8 + 0x1c) = *(int *)(lVar8 + 0x1c) + 1;
        *(undefined4 *)(lVar8 + 0x18) = 0;
        if (0 < iVar13) {
          FUN_7ffe9b518970(*(undefined8 *)(lVar8 + 0x10),0,iVar13,0);
        }
        lVar8 = *(longlong *)(self + 0x10);
        iVar13 = 0;
        if (lVar8 != 0) {
          while (lVar8 = FUN_7ffe9a4f6610(lVar8,0), lVar8 != 0) {
            if (*(int *)(lVar8 + 0x18) <= iVar13) {
              lVar8 = *(longlong *)(self + 0x38);
              if (lVar8 != 0) {
                iVar13 = *(int *)(lVar8 + 0x18);
                *(int *)(lVar8 + 0x1c) = *(int *)(lVar8 + 0x1c) + 1;
                *(undefined4 *)(lVar8 + 0x18) = 0;
                if (0 < iVar13) {
                  FUN_7ffe9b518970(*(undefined8 *)(lVar8 + 0x10),0,iVar13,0);
                }
                lVar8 = *(longlong *)(self + 0x10);
                iVar13 = 0;
                if (lVar8 != 0) goto LAB_7ffe9a4e5bc1;
              }
              break;
            }
            if (((*(longlong *)(self + 0x10) == 0) ||
                (lVar8 = FUN_7ffe9a4f6610(*(longlong *)(self + 0x10),0), lVar8 == 0)) ||
               (lVar8 = FUN_7ffe9af8ab90(lVar8,iVar13,_DAT_7ffe9c94b840), lVar8 == 0)) break;
            uVar1 = *(undefined4 *)(lVar8 + 0x10);
            if (((*(longlong *)(self + 0x10) == 0) ||
                (lVar8 = FUN_7ffe9a4f6610(*(longlong *)(self + 0x10),0), lVar8 == 0)) ||
               (lVar8 = FUN_7ffe9af8ab90(lVar8,iVar13,_DAT_7ffe9c94b840), lVar8 == 0)) break;
            uVar2 = *(uint *)(lVar8 + 0x14);
            uVar7 = func_0x7ffe99940040(_DAT_7ffe9c948b58);
            FUN_7ffe9aae8db0(uVar7,uVar1,uVar2 & 0xffff);
            lVar4 = _DAT_7ffe9c9085a0;
            lVar8 = *(longlong *)(self + 0x30);
            if (lVar8 == 0) break;
            *(int *)(lVar8 + 0x1c) = *(int *)(lVar8 + 0x1c) + 1;
            lVar3 = *(longlong *)(lVar8 + 0x10);
            uVar2 = *(uint *)(lVar8 + 0x18);
            if (lVar3 == 0) break;
            if (uVar2 < *(uint *)(lVar3 + 0x18)) {
              *(uint *)(lVar8 + 0x18) = uVar2 + 1;
              if (*(uint *)(lVar3 + 0x18) <= uVar2) goto LAB_7ffe9a4e5e6d;
              *(undefined8 *)(lVar3 + 0x20 + (longlong)(int)uVar2 * 8) = uVar7;
              il2cpp_write_barrier_0();
            }
            else {
              FUN_7ffe9afd58b0(lVar8,uVar7,
                               *(undefined8 *)
                                (*(longlong *)(*(longlong *)(lVar4 + 0x20) + 0xc0) + 0x70));
            }
            lVar8 = *(longlong *)(self + 0x10);
            iVar13 = iVar13 + 1;
            if (lVar8 == 0) break;
          }
        }
      }
    }
  }
LAB_7ffe9a4e5e67:
  FUN_7ffe9996d7a0();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
LAB_7ffe9a4e5bc1:
  plVar9 = (longlong *)FUN_7ffe9a4f67f0(lVar8,0);
  if (plVar9 == (longlong *)0x0) goto LAB_7ffe9a4e5e67;
  lVar8 = *plVar9;
  uVar12 = 0;
  if (*(ushort *)(lVar8 + 0x12e) != 0) {
    do {
      if (*(longlong *)(*(longlong *)(lVar8 + 0xb0) + uVar12 * 0x10) == _DAT_7ffe9c950ba0) {
        puVar10 = (undefined8 *)
                  (lVar8 + 0x138 +
                  (longlong)*(int *)(*(longlong *)(lVar8 + 0xb0) + 8 + uVar12 * 0x10) * 0x10);
        goto LAB_7ffe9a4e5c26;
      }
      uVar11 = (short)uVar12 + 1;
      uVar12 = (ulonglong)uVar11;
    } while (uVar11 < *(ushort *)(lVar8 + 0x12e));
  }
  puVar10 = (undefined8 *)FUN_7ffe998ce540(plVar9,_DAT_7ffe9c950ba0,0);
LAB_7ffe9a4e5c26:
  iVar6 = (*(code *)*puVar10)(plVar9,puVar10[1]);
  if (iVar6 <= iVar13) {
    return;
  }
  if ((*(longlong *)(self + 0x10) == 0) ||
     (plVar9 = (longlong *)FUN_7ffe9a4f67f0(*(longlong *)(self + 0x10),0), plVar9 == (longlong *)0x0
     )) goto LAB_7ffe9a4e5e67;
  lVar8 = *plVar9;
  uVar12 = 0;
  if (*(ushort *)(lVar8 + 0x12e) != 0) {
    do {
      if (*(longlong *)(*(longlong *)(lVar8 + 0xb0) + uVar12 * 0x10) == _DAT_7ffe9c95e388) {
        puVar10 = (undefined8 *)
                  (lVar8 + 0x138 +
                  (longlong)*(int *)(*(longlong *)(lVar8 + 0xb0) + 8 + uVar12 * 0x10) * 0x10);
        goto LAB_7ffe9a4e5ca6;
      }
      uVar11 = (short)uVar12 + 1;
      uVar12 = (ulonglong)uVar11;
    } while (uVar11 < *(ushort *)(lVar8 + 0x12e));
  }
  puVar10 = (undefined8 *)FUN_7ffe998ce540(plVar9,_DAT_7ffe9c95e388,0);
LAB_7ffe9a4e5ca6:
  lVar8 = (*(code *)*puVar10)(plVar9,iVar13,puVar10[1]);
  if (lVar8 == 0) goto LAB_7ffe9a4e5e67;
  uVar1 = *(undefined4 *)(lVar8 + 0x10);
  if ((*(longlong *)(self + 0x10) == 0) ||
     (plVar9 = (longlong *)FUN_7ffe9a4f67f0(*(longlong *)(self + 0x10),0), plVar9 == (longlong *)0x0
     )) goto LAB_7ffe9a4e5e67;
  lVar8 = *plVar9;
  uVar12 = 0;
  if (*(ushort *)(lVar8 + 0x12e) != 0) {
    do {
      if (*(longlong *)(*(longlong *)(lVar8 + 0xb0) + uVar12 * 0x10) == _DAT_7ffe9c95e388) {
        puVar10 = (undefined8 *)
                  (lVar8 + 0x138 +
                  (longlong)*(int *)(*(longlong *)(lVar8 + 0xb0) + 8 + uVar12 * 0x10) * 0x10);
        goto LAB_7ffe9a4e5d36;
      }
      uVar11 = (short)uVar12 + 1;
      uVar12 = (ulonglong)uVar11;
    } while (uVar11 < *(ushort *)(lVar8 + 0x12e));
  }
  puVar10 = (undefined8 *)FUN_7ffe998ce540(plVar9,_DAT_7ffe9c95e388,0);
LAB_7ffe9a4e5d36:
  lVar8 = (*(code *)*puVar10)(plVar9,iVar13,puVar10[1]);
  if (lVar8 == 0) goto LAB_7ffe9a4e5e67;
  uVar2 = *(uint *)(lVar8 + 0x14);
  uVar7 = func_0x7ffe99940040(_DAT_7ffe9c948b58);
  FUN_7ffe9aae8db0(uVar7,uVar1,uVar2 & 0xffff,0);
  lVar8 = *(longlong *)(self + 0x38);
  if (lVar8 == 0) goto LAB_7ffe9a4e5e67;
  *(int *)(lVar8 + 0x1c) = *(int *)(lVar8 + 0x1c) + 1;
  lVar4 = *(longlong *)(lVar8 + 0x10);
  uVar2 = *(uint *)(lVar8 + 0x18);
  if (lVar4 == 0) goto LAB_7ffe9a4e5e67;
  if (uVar2 < *(uint *)(lVar4 + 0x18)) {
    *(uint *)(lVar8 + 0x18) = uVar2 + 1;
    if (*(uint *)(lVar4 + 0x18) <= uVar2) {
LAB_7ffe9a4e5e6d:
      FUN_7ffe9996d790();
      pcVar5 = (code *)swi(3);
      (*pcVar5)();
      return;
    }
    *(undefined8 *)(lVar4 + 0x20 + (longlong)(int)uVar2 * 8) = uVar7;
    il2cpp_write_barrier_0();
  }
  else {
    FUN_7ffe9afd58b0();
  }
  lVar8 = *(longlong *)(self + 0x10);
  iVar13 = iVar13 + 1;
  if (lVar8 == 0) goto LAB_7ffe9a4e5e67;
  goto LAB_7ffe9a4e5bc1;
}

