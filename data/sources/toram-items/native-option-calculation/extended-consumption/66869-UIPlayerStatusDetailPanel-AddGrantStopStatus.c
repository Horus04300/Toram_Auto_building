
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UIPlayerStatusDetailPanel_AddGrantStopStatus(undefined *self,undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  longlong lVar4;
  longlong *plVar5;
  longlong lVar6;
  code *pcVar7;
  uint uVar8;
  undefined *self_00;
  longlong lVar9;
  uint uVar10;
  undefined8 *puVar11;
  uint uVar12;
  uint uVar13;
  
  plVar5 = *(longlong **)(self + 0x70);
  if ((plVar5 == (longlong *)0x0) ||
     (lVar9 = (**(code **)(*plVar5 + 0x208))(plVar5,*(undefined8 *)(*plVar5 + 0x210)), lVar9 == 0))
  {
    FUN_7ffe9996d7a0();
    pcVar7 = (code *)swi(3);
    (*pcVar7)();
    return;
  }
  func_0x7ffe9a51e2e0(lVar9,1);
  FUN_7ffe9a08ef60(self);
  func_0x7ffe9a51e2e0(lVar9,2);
  FUN_7ffe9a08ef60(self);
  func_0x7ffe9a51e2e0(lVar9,3);
  FUN_7ffe9a08ef60(self);
  if (DAT_7ffe9cadc4cf == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f6c78);
    FUN_7ffe9996d590(&DAT_7ffe9c91fe10);
    DAT_7ffe9cadc4cf = '\x01';
  }
  lVar9 = *(longlong *)(self + 0x88);
  self_00 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c8f6c78);
  AvoidBreaker_Reset(self_00,(undefined *)0x0);
  *(undefined4 *)(self_00 + 0x10) = 0;
  *(undefined8 *)(self_00 + 0x20) = 0xbff0000000000000;
  *(undefined8 *)(self_00 + 0x28) = 0xbff0000000000000;
  *(undefined4 *)(self_00 + 0x14) = 0xbf800000;
  *(undefined4 *)(self_00 + 0x18) = 0xbf800000;
  *(undefined4 *)(self_00 + 0x1c) = 0xbf800000;
  *(undefined4 *)(self_00 + 0x30) = 5;
  lVar6 = _DAT_7ffe9c91fe10;
  if (lVar9 != 0) {
    *(int *)(lVar9 + 0x1c) = *(int *)(lVar9 + 0x1c) + 1;
    lVar4 = *(longlong *)(lVar9 + 0x10);
    uVar13 = *(uint *)(lVar9 + 0x18);
    if (lVar4 != 0) {
      if (uVar13 < *(uint *)(lVar4 + 0x18)) {
        *(uint *)(lVar9 + 0x18) = uVar13 + 1;
        if (*(uint *)(lVar4 + 0x18) <= uVar13) {
          FUN_7ffe9996d790();
          pcVar7 = (code *)swi(3);
          (*pcVar7)();
          return;
        }
        puVar11 = (undefined8 *)(lVar4 + (longlong)(int)uVar13 * 8 + 0x20);
        *puVar11 = self_00;
il2cpp_write_barrier_0:
        if (_DAT_7ffe9caee1a8 != 0) {
          uVar13 = (uint)((ulonglong)puVar11 >> 0xc);
          puVar1 = (ulonglong *)((ulonglong)((uVar13 & 0x1fffff) >> 6) * 8 + 0x7ffe9cb35fe0);
          do {
            uVar3 = *puVar1;
            LOCK();
            uVar2 = *puVar1;
            if (uVar3 == uVar2) {
              *puVar1 = uVar3 | 1L << (uVar13 & 0x3f);
            }
            UNLOCK();
          } while (uVar3 != uVar2);
        }
        return;
      }
      uVar13 = *(uint *)(lVar9 + 0x18);
      lVar4 = *(longlong *)(lVar9 + 0x10);
      uVar12 = uVar13 + 1;
      if (lVar4 != 0) {
        if (*(int *)(lVar4 + 0x18) < (int)uVar12) {
          if (*(longlong *)(lVar4 + 0x18) == 0) {
            uVar10 = 4;
          }
          else {
            uVar10 = *(int *)(lVar4 + 0x18) * 2;
            if (0x7fefffff < uVar10) {
              uVar10 = 0x7fefffff;
            }
          }
          uVar8 = uVar12;
          if ((int)uVar12 <= (int)uVar10) {
            uVar8 = uVar10;
          }
          FUN_7ffe997b8720(lVar9,uVar8,
                           *(undefined8 *)
                            (*(longlong *)
                              (*(longlong *)
                                (*(longlong *)
                                  (*(longlong *)
                                    (*(longlong *)
                                      (*(longlong *)
                                        (*(longlong *)(*(longlong *)(lVar6 + 0x20) + 0xc0) + 0x70) +
                                      0x20) + 0xc0) + 0x78) + 0x20) + 0xc0) + 0xf0));
        }
        lVar6 = *(longlong *)(lVar9 + 0x10);
        *(uint *)(lVar9 + 0x18) = uVar12;
        if (lVar6 != 0) {
          if (*(uint *)(lVar6 + 0x18) <= uVar13) {
            FUN_7ffe9996d790();
            pcVar7 = (code *)swi(3);
            (*pcVar7)();
            return;
          }
          puVar11 = (undefined8 *)(lVar6 + 0x20 + (longlong)(int)uVar13 * 8);
          *puVar11 = self_00;
          goto il2cpp_write_barrier_0;
        }
      }
      FUN_7ffe9996d7a0();
      pcVar7 = (code *)swi(3);
      (*pcVar7)();
      return;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar7 = (code *)swi(3);
  (*pcVar7)();
  return;
}

