
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int HighRaidMobPartsStatus_get_MagicDef(undefined *self,undefined *methodInfo)

{
  longlong lVar1;
  code *pcVar2;
  char cVar3;
  byte bVar4;
  int iVar5;
  undefined *apuStackX_8 [4];
  
  if (DAT_7ffe9cadd552 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c929b20);
    DAT_7ffe9cadd552 = '\x01';
  }
  apuStackX_8[0] = (undefined *)0x0;
  if ((*(longlong *)(self + 0x28) == 0) ||
     (lVar1 = *(longlong *)(*(longlong *)(self + 0x28) + 0xa0), lVar1 == 0)) goto LAB_7ffe9a325363;
  cVar3 = FUN_7ffe9abb86e0(lVar1,0x20,apuStackX_8,_DAT_7ffe9c929b20);
  if (cVar3 != '\0') {
    if (apuStackX_8[0] == (undefined *)0x0) goto LAB_7ffe9a325363;
    bVar4 = MobPropertyHighRaidCalcExceptionFlag_FixedMagicDefFlag(apuStackX_8[0],(undefined *)0x0);
    if (bVar4 != 0) {
      if (*(longlong *)(self + 0x28) != 0) {
        return *(int *)(*(longlong *)(self + 0x28) + 0x40);
      }
      goto LAB_7ffe9a325363;
    }
  }
  if (*(longlong *)(self + 0x28) != 0) {
    return (int)(((float)*(int *)(*(longlong *)(self + 0x28) + 0x40) / _DAT_7ffe9c049cfc) *
                (float)*(int *)(self + 0x38));
  }
LAB_7ffe9a325363:
  FUN_7ffe9996d7a0();
  pcVar2 = (code *)swi(3);
  iVar5 = (*pcVar2)();
  return iVar5;
}

