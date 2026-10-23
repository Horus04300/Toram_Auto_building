
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void FieldScriptLoader_set_Position(undefined *self,int value,undefined *methodInfo)

{
  *(int *)(self + 0x2c) = value;
  return;
}

