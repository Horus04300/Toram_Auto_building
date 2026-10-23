
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void MobStatusMaster_SetMobPropertyMaster
               (undefined *self,undefined *masterData,undefined *methodInfo)

{
  code *pcVar1;
  
  if (*(undefined **)(self + 0xa0) != (undefined *)0x0) {
    MobPropertyManager_SetMasterData
              (*(undefined **)(self + 0xa0),*(int *)(self + 0x14),*(int *)(self + 0x10),masterData,
               (undefined *)0x0);
    return;
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  (*pcVar1)();
  return;
}

