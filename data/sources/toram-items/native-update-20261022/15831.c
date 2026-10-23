
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void BonusScriptData_AddBonus(undefined *self,int type,int val,byte instant,undefined *methodInfo)

{
  undefined4 uVar1;
  uint uVar2;
  undefined8 uVar3;
  longlong lVar4;
  code *pcVar5;
  longlong lVar6;
  undefined8 uVar7;
  longlong lVar8;
  longlong lVar9;
  
  if (DAT_7ffe9cade139 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c90b598);
    FUN_7ffe9996d590(&DAT_7ffe9c9419c0);
    FUN_7ffe9996d590(&DAT_7ffe9c94b160);
    FUN_7ffe9996d590(&DAT_7ffe9c94b530);
    FUN_7ffe9996d590(&DAT_7ffe9c92fc90);
    FUN_7ffe9996d590(&DAT_7ffe9c9199d8);
    FUN_7ffe9996d590(&DAT_7ffe9c925260);
    DAT_7ffe9cade139 = '\x01';
  }
  lVar6 = func_0x7ffe99940040(_DAT_7ffe9c925260);
  func_0x7ffe999c3920(lVar6,0);
  if (lVar6 != 0) {
    *(int *)(lVar6 + 0x10) = type;
    if (instant == 0) {
      uVar3 = *(undefined8 *)(self + 0x10);
      uVar7 = func_0x7ffe99940040(_DAT_7ffe9c9419c0);
      FUN_7ffe9af13420(uVar7,lVar6,_DAT_7ffe9c9199d8,0);
      lVar8 = FUN_7ffe9ab854c0(uVar3,uVar7,_DAT_7ffe9c90b598);
      if (0 < *(int *)(self + 0x74)) {
        if (lVar8 != 0) {
          val = val + *(int *)(lVar8 + 0x14);
        }
        *(int *)(self + 0x74) = *(int *)(self + 0x74) + -1;
      }
      if (*(longlong *)(self + 0x10) == 0) goto LAB_7ffe9a4f582c;
      FUN_7ffe9afdbfb0(*(longlong *)(self + 0x10),lVar8,_DAT_7ffe9c94b530);
    }
    lVar8 = *(longlong *)(self + 0x10);
    uVar1 = *(undefined4 *)(lVar6 + 0x10);
    lVar9 = func_0x7ffe99940040(_DAT_7ffe9c92fc90);
    func_0x7ffe999c3920(lVar9,0);
    *(undefined4 *)(lVar9 + 0x10) = uVar1;
    *(int *)(lVar9 + 0x14) = val;
    *(byte *)(lVar9 + 0x18) = instant;
    lVar6 = _DAT_7ffe9c94b160;
    if (lVar8 != 0) {
      *(int *)(lVar8 + 0x1c) = *(int *)(lVar8 + 0x1c) + 1;
      lVar4 = *(longlong *)(lVar8 + 0x10);
      uVar2 = *(uint *)(lVar8 + 0x18);
      if (lVar4 != 0) {
        if (uVar2 < *(uint *)(lVar4 + 0x18)) {
          *(uint *)(lVar8 + 0x18) = uVar2 + 1;
          if (*(uint *)(lVar4 + 0x18) <= uVar2) {
            FUN_7ffe9996d790();
            pcVar5 = (code *)swi(3);
            (*pcVar5)();
            return;
          }
          *(longlong *)(lVar4 + (longlong)(int)uVar2 * 8 + 0x20) = lVar9;
          il2cpp_write_barrier_0();
        }
        else {
          FUN_7ffe9afd58b0(lVar8,lVar9,
                           *(undefined8 *)(*(longlong *)(*(longlong *)(lVar6 + 0x20) + 0xc0) + 0x70)
                          );
        }
        return;
      }
    }
  }
LAB_7ffe9a4f582c:
  FUN_7ffe9996d7a0();
  pcVar5 = (code *)swi(3);
  (*pcVar5)();
  return;
}

