
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidManager_UpdateHeldData(undefined *self,undefined *data,undefined *methodInfo)

{
  code *pcVar1;
  
  if (DAT_7ffe9cade408 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c957010);
    DAT_7ffe9cade408 = '\x01';
  }
  if (data != (undefined *)0x0) {
    *(undefined4 *)(self + 0x10) = *(undefined4 *)(data + 0x24);
    self[0x14] = data[0x38];
    *(uint *)(self + 0x18) = (uint)(byte)data[0x20];
    if (*(longlong *)(self + 0x28) == 0) {
      FUN_7ffe9996d7a0();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    FUN_7ffe9acce330(*(longlong *)(self + 0x28),_DAT_7ffe9c957010);
  }
  return;
}

