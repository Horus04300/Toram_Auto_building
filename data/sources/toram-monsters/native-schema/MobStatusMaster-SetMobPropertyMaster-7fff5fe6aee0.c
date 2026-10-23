
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobStatusMaster_SetMobPropertyMaster
               (undefined *self,undefined *masterData,undefined *methodInfo)

{
  code *pcVar1;
  
  if (*(longlong *)(self + 0xa0) != 0) {
    FUN_7fff5fe85780(*(longlong *)(self + 0xa0),*(undefined4 *)(self + 0x14),
                     *(undefined4 *)(self + 0x10),masterData,0);
    return;
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

