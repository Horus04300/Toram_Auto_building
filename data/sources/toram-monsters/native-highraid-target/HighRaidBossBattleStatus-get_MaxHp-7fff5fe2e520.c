
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int HighRaidBossBattleStatus_get_MaxHp(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  float fVar5;
  float fVar6;
  longlong alStackX_8 [4];
  
  alStackX_8[0] = 0;
  if (DAT_7fff625e4ca0 == '\0') {
    FUN_7fff5f47d450(&DAT_7fff624309c0);
    DAT_7fff625e4ca0 = '\x01';
  }
  if ((*(longlong *)(self + 0x10) == 0) ||
     (lVar1 = *(longlong *)(*(longlong *)(self + 0x10) + 0xa0), lVar1 == 0)) goto LAB_7fff5fe2e64d;
  cVar3 = FUN_7fff606c2a90(lVar1,0x20,alStackX_8,_DAT_7fff624309c0);
  if (cVar3 != '\0') {
    if (alStackX_8[0] == 0) goto LAB_7fff5fe2e64d;
    cVar3 = FUN_7fff5fe84960(alStackX_8[0],0);
    if (cVar3 != '\0') {
      if (*(longlong *)(self + 0x10) != 0) {
        return *(int *)(*(longlong *)(self + 0x10) + 0x30);
      }
      goto LAB_7fff5fe2e64d;
    }
  }
  if (*(longlong *)(self + 0x10) != 0) {
    iVar4 = *(int *)(self + 0x30);
    fVar6 = (float)*(int *)(*(longlong *)(self + 0x10) + 0x30) / _DAT_7fff61b52cfc;
    fVar5 = ((float)(iVar4 + 0x51) + (float)(iVar4 * iVar4) / _DAT_7fff61b52ef0) *
            ((float)iVar4 / _DAT_7fff61b52ce4 + _DAT_7fff61b52e64);
    if (0x95 < iVar4) {
      return (int)(fVar6 * fVar5 * _DAT_7fff61b52cd8);
    }
    return (int)(fVar6 * fVar5 * _DAT_7fff61b52b18);
  }
LAB_7fff5fe2e64d:
  FUN_7fff5f47d660();
  pcVar2 = (code *)swi(3);
  iVar4 = (*pcVar2)();
  return iVar4;
}

