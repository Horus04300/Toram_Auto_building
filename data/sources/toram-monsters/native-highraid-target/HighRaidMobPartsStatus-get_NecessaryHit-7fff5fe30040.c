
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int HighRaidMobPartsStatus_get_NecessaryHit(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  longlong alStackX_8 [4];
  
  if (DAT_7fff625e4ca8 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff624309c0);
    DAT_7fff625e4ca8 = '\x01';
  }
  alStackX_8[0] = 0;
  if ((*(longlong *)(self + 0x28) == 0) ||
     (lVar1 = *(longlong *)(*(longlong *)(self + 0x28) + 0xa0), lVar1 == 0)) goto LAB_7fff5fe300ff;
  cVar3 = FUN_7fff606c2a90(lVar1,0x20,alStackX_8,_DAT_7fff624309c0);
  if (cVar3 != '\0') {
    if (alStackX_8[0] == 0) goto LAB_7fff5fe300ff;
    cVar3 = FUN_7fff5fe84a40(alStackX_8[0],0);
    if (cVar3 != '\0') {
      if (*(longlong *)(self + 0x28) != 0) {
        return *(int *)(*(longlong *)(self + 0x28) + 0x38);
      }
      goto LAB_7fff5fe300ff;
    }
  }
  if (*(longlong *)(self + 0x28) != 0) {
    return (int)(((float)*(int *)(*(longlong *)(self + 0x28) + 0x38) / _DAT_7fff61b52cfc) *
                (float)*(int *)(self + 0x38) * _DAT_7fff61b52cd8);
  }
LAB_7fff5fe300ff:
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  iVar4 = (*pcVar2)();
  return iVar4;
}

