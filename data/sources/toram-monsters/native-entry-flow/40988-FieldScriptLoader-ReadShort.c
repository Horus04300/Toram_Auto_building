
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

short FieldScriptLoader_ReadShort(undefined *self,undefined *methodInfo)

{
  short sVar1;
  
  if (*(longlong *)(self + 0x20) != 0) {
    sVar1 = FUN_7ffe9b482c10(*(longlong *)(self + 0x20),*(undefined4 *)(self + 0x2c),0);
    *(int *)(self + 0x2c) = *(int *)(self + 0x2c) + 2;
    return sVar1;
  }
  return -1;
}

