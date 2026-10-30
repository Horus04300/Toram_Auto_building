
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

undefined * GemCartBufferManager_GetGemCartBuffer(undefined *self,short id,undefined *methodInfo)

{
  code *pcVar1;
  char cVar2;
  undefined *puVar3;
  undefined6 in_register_00000012;
  undefined8 uStackX_8;
  
  if (DAT_7ffe9cade791 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c9658b0,CONCAT62(in_register_00000012,id));
    FUN_7ffe9996d590(&DAT_7ffe9c965980);
    DAT_7ffe9cade791 = '\x01';
  }
  uStackX_8 = 0;
  if (*(longlong *)(self + 0x18) != 0) {
    cVar2 = FUN_7ffe9ad1e480(*(longlong *)(self + 0x18),id,&uStackX_8,_DAT_7ffe9c9658b0);
    if (cVar2 == '\0') {
      return (undefined *)0x0;
    }
    if (*(longlong *)(self + 0x18) != 0) {
      puVar3 = (undefined *)FUN_7ffe9ad24760(*(longlong *)(self + 0x18),id,_DAT_7ffe9c965980);
      return puVar3;
    }
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  puVar3 = (undefined *)(*pcVar1)();
  return puVar3;
}

