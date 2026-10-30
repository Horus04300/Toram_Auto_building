
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GemCartBag_InitializeEquip(undefined *self,undefined *equips,byte slot,undefined *methodInfo)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  undefined8 uVar4;
  longlong lVar5;
  longlong lVar6;
  code *pcVar7;
  longlong lVar8;
  longlong lVar9;
  
  if (DAT_7ffe9cade7b8 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c909038);
    FUN_7ffe9996d590(&DAT_7ffe9c93ad18);
    FUN_7ffe9996d590(&DAT_7ffe9c90ddd0);
    FUN_7ffe9996d590(&DAT_7ffe9c91f468);
    FUN_7ffe9996d590(0x7ffe9c91f530);
    FUN_7ffe9996d590(&DAT_7ffe9c945660);
    FUN_7ffe9996d590(&DAT_7ffe9c9561f8);
    DAT_7ffe9cade7b8 = '\x01';
  }
  lVar8 = func_0x7ffe99940040(_DAT_7ffe9c9561f8);
  func_0x7ffe999c3920(lVar8,0);
  if (lVar8 != 0) {
    *(undefined **)(lVar8 + 0x10) = equips;
    il2cpp_write_barrier_0();
    lVar9 = *(longlong *)(self + 0x18);
    self[0x20] = slot;
    if (lVar9 != 0) {
      iVar2 = *(int *)(lVar9 + 0x18);
      *(int *)(lVar9 + 0x1c) = *(int *)(lVar9 + 0x1c) + 1;
      *(undefined4 *)(lVar9 + 0x18) = 0;
      if (0 < iVar2) {
        FUN_7ffe9b518970(*(undefined8 *)(lVar9 + 0x10),0,iVar2,0);
      }
      if ((*(longlong *)(lVar8 + 0x10) == 0) ||
         (*(longlong *)(*(longlong *)(lVar8 + 0x10) + 0x18) == 0)) {
        return;
      }
      *(undefined4 *)(lVar8 + 0x18) = 0;
      while (lVar9 = *(longlong *)(lVar8 + 0x10), lVar9 != 0) {
        uVar3 = *(uint *)(lVar8 + 0x18);
        if ((int)*(uint *)(lVar9 + 0x18) <= (int)uVar3) {
          return;
        }
        if (*(uint *)(lVar9 + 0x18) <= uVar3) {
LAB_7ffe9a5adde3:
          FUN_7ffe9996d790();
          pcVar7 = (code *)swi(3);
          (*pcVar7)();
          return;
        }
        lVar9 = *(longlong *)(lVar9 + 0x20 + (longlong)(int)uVar3 * 8);
        if (lVar9 == 0) break;
        if (*(longlong *)(lVar9 + 0x28) != 0) {
          lVar9 = *(longlong *)(lVar8 + 0x20);
          uVar4 = *(undefined8 *)(self + 0x10);
          if (lVar9 == 0) {
            lVar9 = func_0x7ffe99940040(_DAT_7ffe9c93ad18);
            FUN_7ffe9af13420(lVar9,lVar8,_DAT_7ffe9c945660,0);
            *(longlong *)(lVar8 + 0x20) = lVar9;
            il2cpp_write_barrier_0();
          }
          lVar9 = FUN_7ffe9ab854c0(uVar4,lVar9,_DAT_7ffe9c909038);
          if (lVar9 != 0) {
            lVar5 = *(longlong *)(lVar8 + 0x10);
            lVar6 = *(longlong *)(self + 0x18);
            if (lVar5 == 0) break;
            if (*(uint *)(lVar5 + 0x18) <= *(uint *)(lVar8 + 0x18)) goto LAB_7ffe9a5adde3;
            lVar5 = *(longlong *)(lVar5 + 0x20 + (longlong)(int)*(uint *)(lVar8 + 0x18) * 8);
            uVar1 = *(undefined2 *)(lVar9 + 0x20);
            lVar9 = func_0x7ffe99940040(_DAT_7ffe9c90ddd0);
            func_0x7ffe999c3920(lVar9,0);
            if (lVar5 == 0) break;
            *(undefined1 *)(lVar9 + 0x10) = *(undefined1 *)(lVar5 + 0x20);
            *(undefined8 *)(lVar9 + 0x18) = *(undefined8 *)(lVar5 + 0x28);
            *(undefined2 *)(lVar9 + 0x20) = uVar1;
            if (lVar6 == 0) break;
            FUN_7ffe99743100(lVar6,lVar9,_DAT_7ffe9c91f468);
          }
        }
        *(int *)(lVar8 + 0x18) = *(int *)(lVar8 + 0x18) + 1;
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar7 = (code *)swi(3);
  (*pcVar7)();
  return;
}

