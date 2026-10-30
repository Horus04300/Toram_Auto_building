
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

byte GemCartBufferManager_ContainsBuffer(undefined *self,short id,undefined *methodInfo)

{
  code *pcVar1;
  byte bVar2;
  int iVar3;
  undefined6 in_register_00000012;
  
  if (DAT_7ffe9cade790 == '\0') {
    FUN_7ffe9996d590(&DAT_7ffe9c965650,CONCAT62(in_register_00000012,id));
    DAT_7ffe9cade790 = '\x01';
  }
  if (*(longlong *)(self + 0x18) != 0) {
    iVar3 = FUN_7ffe9ad11880(*(longlong *)(self + 0x18),id,
                             *(undefined8 *)
                              (*(longlong *)(*(longlong *)(_DAT_7ffe9c965650 + 0x20) + 0xc0) + 0x110
                              ));
    return -1 < iVar3;
  }
  FUN_7ffe9996d7a0();
  pcVar1 = (code *)swi(3);
  bVar2 = (*pcVar1)();
  return bVar2;
}

