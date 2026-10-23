
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int BonusScriptData_get_Type(undefined *self,undefined *methodInfo)

{
  return *(int *)(self + 0x30);
}

