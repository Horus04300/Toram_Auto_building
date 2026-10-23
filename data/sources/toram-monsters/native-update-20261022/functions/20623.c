
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidRoomData_ReceiveRaidEndBattleData
               (undefined *self,undefined *endEvent,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  
  *(undefined **)(self + 0x80) = endEvent;
  il2cpp_write_barrier_0();
  if (endEvent != (undefined *)0x0) {
    *(undefined8 *)(self + 0x78) = *(undefined8 *)(endEvent + 0x50);
    il2cpp_write_barrier_0();
    lVar1 = *(longlong *)(self + 0x80);
    if ((lVar1 != 0) && (*(longlong *)(lVar1 + 0x38) != 0)) {
      *(undefined4 *)(self + 0x9c) = *(undefined4 *)(*(longlong *)(lVar1 + 0x38) + 0x20);
      self[0xa0] = *(undefined1 *)(lVar1 + 0x5d);
      self[0x88] = 0;
      return;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  (*pcVar2)();
  return;
}

