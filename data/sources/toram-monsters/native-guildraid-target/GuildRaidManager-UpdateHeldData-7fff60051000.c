
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidManager_UpdateHeldData(undefined *self,undefined *held,undefined *methodInfo)

{
  undefined1 uVar1;
  code *pcVar2;
  char cVar3;
  undefined4 uVar4;
  undefined *puVar5;
  undefined8 uVar6;
  undefined *puStackX_10;
  undefined8 uStackX_20;
  undefined8 auStack_28 [2];
  
  if (DAT_7fff625e5b66 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6245de28);
    FUN_7fff5f47d450(&DAT_7fff6245dfc0);
    FUN_7fff5f47d450(&DAT_7fff62461a30);
    DAT_7fff625e5b66 = '\x01';
  }
  if ((held == (undefined *)0x0) || (held[0x20] == '\0')) {
    return;
  }
  puStackX_10 = (undefined *)0x0;
  if (*(longlong *)(self + 0x28) != 0) {
    cVar3 = FUN_7fff60801490(*(longlong *)(self + 0x28),held[0x20],&puStackX_10,_DAT_7fff6245dfc0);
    if (cVar3 == '\0') {
      uVar1 = held[0x20];
      puVar5 = (undefined *)func_0x7fff5f44ff00(_DAT_7fff62461a30);
      if (DAT_7fff625e5b6b == '\0') {
        FUN_7fff5f47d450(&DAT_7fff6246eb60);
        DAT_7fff625e5b6b = '\x01';
      }
      if (*(int *)(_DAT_7fff6246eb60 + 0xe0) == 0) {
        func_0x7fff5f47d6f0(_DAT_7fff6246eb60);
      }
      *(undefined8 *)(puVar5 + 0x18) = **(undefined8 **)(_DAT_7fff6246eb60 + 0xb8);
      *(undefined8 *)(puVar5 + 0x20) = **(undefined8 **)(_DAT_7fff6246eb60 + 0xb8);
      GuildRaidRoomData_LoadAsset(puVar5,(undefined *)0x0);
      puVar5[0x10] = uVar1;
      puStackX_10 = puVar5;
      if (*(longlong *)(self + 0x28) == 0) goto LAB_7fff60051228;
      FUN_7fff607f5cf0(*(longlong *)(self + 0x28),held[0x20],puVar5,_DAT_7fff6245de28);
    }
    puVar5 = puStackX_10;
    if (puStackX_10 != (undefined *)0x0) {
      if (DAT_7fff625e5b6c == '\0') {
        FUN_7fff5f47d450(&DAT_7fff62474d00);
        DAT_7fff625e5b6c = '\x01';
      }
      if (held[0x20] != puVar5[0x10]) {
        return;
      }
      puVar5[0x11] = held[0x21];
      puVar5[0x30] = held[0x22];
      uVar4 = (**(code **)(*(longlong *)held + 0x1b8))
                        (held,*(undefined8 *)(*(longlong *)held + 0x1c0));
      uStackX_20 = 0;
      FUN_7fff610337e0(&uStackX_20,0,0,uVar4,0);
      *(undefined8 *)(puVar5 + 0x18) = uStackX_20;
      uVar4 = (**(code **)(*(longlong *)held + 0x1d8))
                        (held,*(undefined8 *)(*(longlong *)held + 0x1e0));
      auStack_28[0] = 0;
      FUN_7fff610337e0(auStack_28,0,0,uVar4,0);
      *(undefined8 *)(puVar5 + 0x20) = auStack_28[0];
      if (*(int *)(_DAT_7fff62474d00 + 0xe0) == 0) {
        func_0x7fff5f47d6f0();
      }
      uVar6 = FUN_7fff61006310(0);
      *(undefined8 *)(puVar5 + 0x28) = uVar6;
      return;
    }
  }
LAB_7fff60051228:
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

