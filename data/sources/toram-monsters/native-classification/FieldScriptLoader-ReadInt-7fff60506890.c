
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int FieldScriptLoader_ReadInt(undefined *self,undefined *methodInfo)

{
  int iVar1;
  
  if (*(longlong *)(self + 0x20) != 0) {
    iVar1 = FUN_7fff60f8d040(*(longlong *)(self + 0x20),*(undefined4 *)(self + 0x2c),0);
    *(int *)(self + 0x2c) = *(int *)(self + 0x2c) + 4;
    return iVar1;
  }
  return -1;
}

