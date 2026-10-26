
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void UIPlayerStatusDetailPanel_AddResistStatus(undefined *self,undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  longlong lVar4;
  longlong lVar5;
  longlong *plVar6;
  longlong lVar7;
  code *pcVar8;
  uint uVar9;
  undefined *puVar10;
  uint uVar11;
  undefined8 *puVar12;
  uint uVar13;
  uint uVar14;
  
  plVar6 = *(longlong **)(self + 0x70);
  if ((plVar6 == (longlong *)0x0) ||
     (puVar10 = (undefined *)(**(code **)(*plVar6 + 0x1d8))(plVar6,*(undefined8 *)(*plVar6 + 0x1e0))
     , puVar10 == (undefined *)0x0)) {
    FUN_7ffe9996d7a0();
    pcVar8 = (code *)swi(3);
    (*pcVar8)();
    return;
  }
  BonusManager_GetBonusValue(puVar10,0x79,(undefined *)0x0);
  FUN_7ffe9a08ef60(self,0x3c);
  BonusManager_GetBonusValue(puVar10,0x7a,(undefined *)0x0);
  FUN_7ffe9a08ef60(self,0x3d);
  BonusManager_GetBonusValue(puVar10,0x7b,(undefined *)0x0);
  FUN_7ffe9a08ef60(self,0x3e);
  BonusManager_GetBonusValue(puVar10,0x7c,(undefined *)0x0);
  FUN_7ffe9a08ef60(self,0x3f);
  BonusManager_GetBonusValue(puVar10,0x7d,(undefined *)0x0);
  FUN_7ffe9a08ef60(self,0x40);
  BonusManager_GetBonusValue(puVar10,0x7e,(undefined *)0x0);
  FUN_7ffe9a08ef60(self,0x41);
  BonusManager_GetBonusValue(puVar10,0x7f,(undefined *)0x0);
  FUN_7ffe9a08ef60(self,0x42);
  BonusManager_GetBonusValue(puVar10,0x80,(undefined *)0x0);
  FUN_7ffe9a08ef60(self,0x43);
  BonusManager_GetBonusValue(puVar10,0x81,(undefined *)0x0);
  FUN_7ffe9a08ef60(self,0x44);
  BonusManager_GetBonusValue(puVar10,0x82,(undefined *)0x0);
  FUN_7ffe9a08ef60(self,0x45);
  BonusManager_GetBonusValue(puVar10,0x83,(undefined *)0x0);
  FUN_7ffe9a08ef60(self);
  if (DAT_7ffe9cadc4cf == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c8f6c78);
    FUN_7ffe9996d590(&DAT_7ffe9c91fe10);
    DAT_7ffe9cadc4cf = '\x01';
  }
  lVar4 = *(longlong *)(self + 0x88);
  puVar10 = (undefined *)func_0x7ffe99940040(_DAT_7ffe9c8f6c78);
  AvoidBreaker_Reset(puVar10,(undefined *)0x0);
  *(undefined4 *)(puVar10 + 0x10) = 0;
  *(undefined8 *)(puVar10 + 0x20) = 0xbff0000000000000;
  *(undefined8 *)(puVar10 + 0x28) = 0xbff0000000000000;
  *(undefined4 *)(puVar10 + 0x14) = 0xbf800000;
  *(undefined4 *)(puVar10 + 0x18) = 0xbf800000;
  *(undefined4 *)(puVar10 + 0x1c) = 0xbf800000;
  *(undefined4 *)(puVar10 + 0x30) = 5;
  lVar7 = _DAT_7ffe9c91fe10;
  if (lVar4 != 0) {
    *(int *)(lVar4 + 0x1c) = *(int *)(lVar4 + 0x1c) + 1;
    lVar5 = *(longlong *)(lVar4 + 0x10);
    uVar14 = *(uint *)(lVar4 + 0x18);
    if (lVar5 != 0) {
      if (uVar14 < *(uint *)(lVar5 + 0x18)) {
        *(uint *)(lVar4 + 0x18) = uVar14 + 1;
        if (*(uint *)(lVar5 + 0x18) <= uVar14) {
          FUN_7ffe9996d790();
          pcVar8 = (code *)swi(3);
          (*pcVar8)();
          return;
        }
        puVar12 = (undefined8 *)(lVar5 + (longlong)(int)uVar14 * 8 + 0x20);
        *puVar12 = puVar10;
il2cpp_write_barrier_0:
        if (_DAT_7ffe9caee1a8 != 0) {
          uVar14 = (uint)((ulonglong)puVar12 >> 0xc);
          puVar1 = (ulonglong *)((ulonglong)((uVar14 & 0x1fffff) >> 6) * 8 + 0x7ffe9cb35fe0);
          do {
            uVar3 = *puVar1;
            LOCK();
            uVar2 = *puVar1;
            if (uVar3 == uVar2) {
              *puVar1 = uVar3 | 1L << (uVar14 & 0x3f);
            }
            UNLOCK();
          } while (uVar3 != uVar2);
        }
        return;
      }
      uVar14 = *(uint *)(lVar4 + 0x18);
      lVar5 = *(longlong *)(lVar4 + 0x10);
      uVar13 = uVar14 + 1;
      if (lVar5 != 0) {
        if (*(int *)(lVar5 + 0x18) < (int)uVar13) {
          if (*(longlong *)(lVar5 + 0x18) == 0) {
            uVar11 = 4;
          }
          else {
            uVar11 = *(int *)(lVar5 + 0x18) * 2;
            if (0x7fefffff < uVar11) {
              uVar11 = 0x7fefffff;
            }
          }
          uVar9 = uVar13;
          if ((int)uVar13 <= (int)uVar11) {
            uVar9 = uVar11;
          }
          FUN_7ffe997b8720(lVar4,uVar9,
                           *(undefined8 *)
                            (*(longlong *)
                              (*(longlong *)
                                (*(longlong *)
                                  (*(longlong *)
                                    (*(longlong *)
                                      (*(longlong *)
                                        (*(longlong *)(*(longlong *)(lVar7 + 0x20) + 0xc0) + 0x70) +
                                      0x20) + 0xc0) + 0x78) + 0x20) + 0xc0) + 0xf0));
        }
        lVar7 = *(longlong *)(lVar4 + 0x10);
        *(uint *)(lVar4 + 0x18) = uVar13;
        if (lVar7 != 0) {
          if (*(uint *)(lVar7 + 0x18) <= uVar14) {
            FUN_7ffe9996d790();
            pcVar8 = (code *)swi(3);
            (*pcVar8)();
            return;
          }
          puVar12 = (undefined8 *)(lVar7 + 0x20 + (longlong)(int)uVar14 * 8);
          *puVar12 = puVar10;
          goto il2cpp_write_barrier_0;
        }
      }
      FUN_7ffe9996d7a0();
      pcVar8 = (code *)swi(3);
      (*pcVar8)();
      return;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar8 = (code *)swi(3);
  (*pcVar8)();
  return;
}

