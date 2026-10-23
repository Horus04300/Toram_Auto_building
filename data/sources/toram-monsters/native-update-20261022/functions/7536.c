
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * EnemyMobActionManagerBase_get_MobStatusMaster(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  undefined *puVar2;
  
  while( true ) {
    if (self[0x151] == '\0') {
      return *(undefined **)(self + 0x70);
    }
    self = *(undefined **)(self + 0xf8);
    if (self == (undefined *)0x0) break;
    methodInfo = (undefined *)0x0;
  }
  FUN_7ffe9996d7a0(0,methodInfo);
  pcVar1 = (code *)swi(3);
  puVar2 = (undefined *)(*pcVar1)();
  return puVar2;
}

