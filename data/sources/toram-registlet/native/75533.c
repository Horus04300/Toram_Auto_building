
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GemCartBuffer_TheSameBoatBuff_OnGetValue(undefined *self,undefined *id,undefined *methodInfo)

{
  code *pcVar1;
  int iVar2;
  longlong lVar3;
  
  if (DAT_7ffe9cadd3d6 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c968830);
    FUN_7ffe9996d590(&DAT_7ffe9c954a30);
    DAT_7ffe9cadd3d6 = '\x01';
  }
  lVar3 = FUN_7ffe9b141840(_DAT_7ffe9c954a30);
  if (lVar3 == 0) {
    FUN_7ffe9996d7a0();
    pcVar1 = (code *)swi(3);
    iVar2 = (*pcVar1)();
    return iVar2;
  }
  iVar2 = FUN_7ffe9a5a46d0(lVar3,0);
  if (*(int *)(_DAT_7ffe9c968830 + 0xe0) == 0) {
    func_0x7ffe9996d830();
  }
  iVar2 = func_0x7ffe9b506b70(0,iVar2 + -1,0);
  if (0 < iVar2) {
    if ((int)id != 2) {
      iVar2 = 0;
    }
    return iVar2;
  }
  return 0;
}

