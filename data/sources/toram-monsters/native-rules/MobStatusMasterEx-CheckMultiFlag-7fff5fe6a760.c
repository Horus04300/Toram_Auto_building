
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MobStatusMasterEx_CheckMultiFlag(undefined *master,undefined *flag,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  
  if (master != (undefined *)0x0) {
    return (*(uint *)(master + 0x58) & (uint)flag) == (uint)flag;
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  bVar2 = (*pcVar1)();
  return bVar2;
}

