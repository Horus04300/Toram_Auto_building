
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int SmithGrant_getSuccessSkillRate(undefined *self,undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  longlong lVar5;
  int iVar6;
  
  if (*(longlong *)(self + 0x140) != 0) {
    lVar5 = FUN_7fff5ff8b150(*(longlong *)(self + 0x140),0);
    if (lVar5 != 0) {
      iVar2 = FUN_7fff60307a10(lVar5,0x16d,1,0);
      iVar3 = FUN_7fff60307a10(lVar5,0x16e,1,0);
      iVar4 = FUN_7fff60307a10(lVar5,0x16f,1,0);
      iVar6 = 0;
      if (0 < iVar2) {
        iVar6 = iVar2;
      }
      if (0 < iVar3) {
        iVar6 = iVar6 + 10 + iVar3;
      }
      if (0 < iVar4) {
        iVar6 = iVar6 + 0x14 + iVar4;
      }
      return iVar6;
    }
  }
  FUN_7fff5f47d660();
  pcVar1 = (code *)swi(3);
  iVar6 = (*pcVar1)();
  return iVar6;
}

