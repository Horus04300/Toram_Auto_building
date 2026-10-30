
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void PhotonListener_OnCheckTreasureHuntRoom
               (undefined *self,undefined *game,undefined *response,undefined *methodInfo)

{
  ulonglong *puVar1;
  ulonglong uVar2;
  ulonglong uVar3;
  undefined8 uVar4;
  longlong lVar5;
  code *pcVar6;
  longlong lVar7;
  longlong *plVar8;
  undefined8 uVar9;
  uint uVar10;
  
  lVar5 = *(longlong *)(self + 0x20);
  if (lVar5 == 0) {
    FUN_7ffe9996d7a0();
    pcVar6 = (code *)swi(3);
    (*pcVar6)();
    return;
  }
  if (DAT_7ffe9cadfcf6 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c923098,response,0);
    FUN_7ffe9996d590(&DAT_7ffe9c954d60);
    FUN_7ffe9996d590(&DAT_7ffe9c955480);
    FUN_7ffe9996d590(&DAT_7ffe9c96c9c0);
    DAT_7ffe9cadfcf6 = '\x01';
  }
  lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
  if (lVar7 == 0) goto LAB_7ffe9a8c9472;
  plVar8 = *(longlong **)(lVar7 + 0x28);
  if (plVar8 == (longlong *)0x0) {
LAB_7ffe9a8c93ba:
    plVar8 = (longlong *)func_0x7ffe99940040(_DAT_7ffe9c96c9c0);
    FUN_7ffe9a628390(plVar8,0);
    lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c955480);
    if (lVar7 == 0) goto LAB_7ffe9a8c9472;
    *(longlong **)(lVar7 + 0x28) = plVar8;
    il2cpp_write_barrier_0();
  }
  else if ((*(byte *)(*plVar8 + 0x130) < *(byte *)(_DAT_7ffe9c96c9c0 + 0x130)) ||
          (*(longlong *)
            (*(longlong *)(*plVar8 + 200) + -8 + (ulonglong)*(byte *)(_DAT_7ffe9c96c9c0 + 0x130) * 8
            ) != _DAT_7ffe9c96c9c0)) goto LAB_7ffe9a8c93ba;
  lVar7 = FUN_7ffe9b141840(_DAT_7ffe9c954d60);
  if ((lVar7 != 0) && (FUN_7ffe9aae7e50(lVar7,0xb7,0x6c,0), response != (undefined *)0x0)) {
    uVar4 = *(undefined8 *)(response + 0x20);
    uVar9 = FUN_7ffe9ab92be0(*(undefined8 *)(response + 0x28),_DAT_7ffe9c923098);
    FUN_7ffe9a8da810(lVar5,uVar4,uVar9,0);
    if (plVar8 != (longlong *)0x0) {
      lVar5 = *(longlong *)(response + 0x40);
      *(undefined *)((longlong)plVar8 + 0xda) = response[0x30];
      plVar8[0x1c] = lVar5;
      if (_DAT_7ffe9caee1a8 != 0) {
        uVar10 = (uint)((ulonglong)(plVar8 + 0x1c) >> 0xc);
        puVar1 = (ulonglong *)((ulonglong)((uVar10 & 0x1fffff) >> 6) * 8 + 0x7ffe9cb35fe0);
        do {
          uVar3 = *puVar1;
          LOCK();
          uVar2 = *puVar1;
          if (uVar3 == uVar2) {
            *puVar1 = uVar3 | 1L << (uVar10 & 0x3f);
          }
          UNLOCK();
        } while (uVar3 != uVar2);
      }
      return;
    }
  }
LAB_7ffe9a8c9472:
  FUN_7ffe9996d7a0();
  pcVar6 = (code *)swi(3);
  (*pcVar6)();
  return;
}

