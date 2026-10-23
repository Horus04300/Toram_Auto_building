
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SmithGrant_getUsableSlotCount(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  longlong lVar3;
  double dVar4;
  double dVar5;
  float fVar6;
  
  if (*(longlong *)(self + 0x140) != 0) {
    lVar3 = FUN_7fff5ff8b150(*(longlong *)(self + 0x140),0);
    if (lVar3 != 0) {
      FUN_7fff60307a10(lVar3,0x16d,1,0);
      iVar2 = FUN_7fff60307a10(lVar3,0x16e,1,0);
      if (DAT_7fff625e1392 == '\0') {
        FUN_7fff5f47d450(&DAT_7fff624700a0);
        DAT_7fff625e1392 = '\x01';
      }
      fVar6 = (float)(iVar2 + 2) * _DAT_7fff61b52d88;
      if (*(int *)(_DAT_7fff624700a0 + 0xe0) == 0) {
        func_0x7fff5f47d6f0();
      }
      dVar4 = (double)func_0x7fff5f4a7774((double)fVar6);
      iVar2 = FUN_7fff60307a10(lVar3,0x16f,1,0);
      if (DAT_7fff625e1392 == '\0') {
        FUN_7fff5f47d450(&DAT_7fff624700a0);
        DAT_7fff625e1392 = '\x01';
      }
      fVar6 = (float)(iVar2 + 4) * _DAT_7fff61b52cc0;
      if (*(int *)(_DAT_7fff624700a0 + 0xe0) == 0) {
        func_0x7fff5f47d6f0();
      }
      dVar5 = (double)func_0x7fff5f4a7774((double)fVar6);
      return (int)dVar5 + (int)dVar4 + 3;
    }
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  iVar2 = (*pcVar1)();
  return iVar2;
}

