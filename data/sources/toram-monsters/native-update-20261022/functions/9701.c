
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte MobPropertyCriticalResist_TryGetValue
               (undefined *self,undefined *mobAction,undefined *criticalParcent,
               undefined *methodInfo)

{
  int iVar1;
  int iVar2;
  longlong lVar3;
  
  if (DAT_7ffe9cadd788 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c906868);
    DAT_7ffe9cadd788 = '\x01';
  }
  lVar3 = FUN_7ffe9ab85290(*(undefined8 *)(self + 0x10),_DAT_7ffe9c906868);
  if (lVar3 != 0) {
    iVar1 = MobPropertyCriticalResist_GetCriticalResist(self,mobAction,(undefined *)0x0);
    iVar2 = 0;
    if (-1 < *(int *)criticalParcent - iVar1) {
      iVar2 = *(int *)criticalParcent - iVar1;
    }
    *(int *)criticalParcent = iVar2;
    return 1;
  }
  return 0;
}

