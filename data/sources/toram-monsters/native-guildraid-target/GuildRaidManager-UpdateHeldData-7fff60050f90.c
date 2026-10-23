
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void GuildRaidManager_UpdateHeldData(undefined *self,undefined *data,undefined *methodInfo)

{
  code *pcVar1;
  
  if (DAT_7fff625e5b60 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff6245def8);
    DAT_7fff625e5b60 = '\x01';
  }
  if (data != (undefined *)0x0) {
    *(undefined4 *)(self + 0x10) = *(undefined4 *)(data + 0x24);
    self[0x14] = data[0x38];
    *(uint *)(self + 0x18) = (uint)(byte)data[0x20];
    if (*(longlong *)(self + 0x28) == 0) {
      FUN_7fff5f47d660();
      pcVar1 = (code *)swi(3);
      (*pcVar1)();
      return;
    }
    FUN_7fff607d86f0(*(longlong *)(self + 0x28),_DAT_7fff6245def8);
  }
  return;
}

