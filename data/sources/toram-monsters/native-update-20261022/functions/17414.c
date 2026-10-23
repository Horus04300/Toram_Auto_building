
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidManager_UpdateHeldData(undefined *self,undefined *held,undefined *methodInfo)

{
  undefined1 uVar1;
  code *pcVar2;
  char cVar3;
  undefined4 uVar4;
  longlong lVar5;
  undefined8 uVar6;
  longlong lStackX_10;
  undefined8 uStackX_20;
  undefined8 auStack_28 [2];
  
  if (DAT_7ffe9cade40e == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c956f48);
    FUN_7ffe9996d590(&DAT_7ffe9c9570e0);
    FUN_7ffe9996d590(&DAT_7ffe9c95a680);
    DAT_7ffe9cade40e = '\x01';
  }
  if ((held == (undefined *)0x0) || (held[0x20] == '\0')) {
    return;
  }
  lStackX_10 = 0;
  if (*(longlong *)(self + 0x28) != 0) {
    cVar3 = FUN_7ffe9acf70d0(*(longlong *)(self + 0x28),held[0x20],&lStackX_10,_DAT_7ffe9c9570e0);
    if (cVar3 == '\0') {
      uVar1 = held[0x20];
      lVar5 = func_0x7ffe99940040(_DAT_7ffe9c95a680);
      if (DAT_7ffe9cade413 == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c967620);
        DAT_7ffe9cade413 = '\x01';
      }
      if (*(int *)(_DAT_7ffe9c967620 + 0xe0) == 0) {
        func_0x7ffe9996d830(_DAT_7ffe9c967620);
      }
      *(undefined8 *)(lVar5 + 0x18) = **(undefined8 **)(_DAT_7ffe9c967620 + 0xb8);
      *(undefined8 *)(lVar5 + 0x20) = **(undefined8 **)(_DAT_7ffe9c967620 + 0xb8);
      func_0x7ffe999c3920(lVar5,0);
      *(undefined1 *)(lVar5 + 0x10) = uVar1;
      lStackX_10 = lVar5;
      if (*(longlong *)(self + 0x28) == 0) goto LAB_7ffe9a546a28;
      FUN_7ffe9aceb930(*(longlong *)(self + 0x28),held[0x20],lVar5,_DAT_7ffe9c956f48);
    }
    lVar5 = lStackX_10;
    if (lStackX_10 != 0) {
      if (DAT_7ffe9cade414 == '\0') {
        FUN_7ffe9996d590(&DAT_7ffe9c96d390);
        DAT_7ffe9cade414 = '\x01';
      }
      if (held[0x20] != *(char *)(lVar5 + 0x10)) {
        return;
      }
      *(undefined *)(lVar5 + 0x11) = held[0x21];
      *(undefined *)(lVar5 + 0x30) = held[0x22];
      uVar4 = (**(code **)(*(longlong *)held + 0x1b8))
                        (held,*(undefined8 *)(*(longlong *)held + 0x1c0));
      uStackX_20 = 0;
      FUN_7ffe9b529420(&uStackX_20,0,0,uVar4,0);
      *(undefined8 *)(lVar5 + 0x18) = uStackX_20;
      uVar4 = (**(code **)(*(longlong *)held + 0x1d8))
                        (held,*(undefined8 *)(*(longlong *)held + 0x1e0));
      auStack_28[0] = 0;
      FUN_7ffe9b529420(auStack_28,0,0,uVar4,0);
      *(undefined8 *)(lVar5 + 0x20) = auStack_28[0];
      if (*(int *)(_DAT_7ffe9c96d390 + 0xe0) == 0) {
        func_0x7ffe9996d830();
      }
      uVar6 = FUN_7ffe9b4fbf50(0);
      *(undefined8 *)(lVar5 + 0x28) = uVar6;
      return;
    }
  }
LAB_7ffe9a546a28:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

