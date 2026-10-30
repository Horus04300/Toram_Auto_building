
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int GemCartBufferManager_GetBufferLevel(undefined *self,short id,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  int iVar3;
  longlong lVar4;
  undefined6 in_register_00000012;
  
  if (DAT_7ffe9cade792 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c965650,CONCAT62(in_register_00000012,id));
    FUN_7ffe9996d590(&DAT_7ffe9c965980);
    DAT_7ffe9cade792 = '\x01';
  }
  if (*(longlong *)(self + 0x18) != 0) {
    cVar2 = FUN_7ffe9ad11000(*(longlong *)(self + 0x18),id,_DAT_7ffe9c965650);
    if (cVar2 == '\0') {
      return 0;
    }
    if (*(longlong *)(self + 0x18) != 0) {
      lVar4 = FUN_7ffe9ad24760(*(longlong *)(self + 0x18),id,_DAT_7ffe9c965980);
      if (lVar4 != 0) {
        return (int)*(short *)(lVar4 + 0x14);
      }
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  iVar3 = (*pcVar1)();
  return iVar3;
}

